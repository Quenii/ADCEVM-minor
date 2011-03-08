-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : lb_arbiter.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-05-25
-- Last update: 2010-07-19
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2010 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2010-05-25  1.0      Administrator   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lb_arbiter is
  
  port (
    sys_rst_i      : in  std_logic;
    -- lb
    LB_Clk_i       : in  std_logic;
    LB_Addr_o      : out std_logic_vector(15 downto 0);
    LB_Write_o     : out std_logic;
    LB_Read_o      : out std_logic;
    LB_Ready_i     : in  std_logic;
    LB_DataW_o     : out std_logic_vector(15 downto 0);
    LB_DataR_i     : in  std_logic_vector(15 downto 0);
    --
    rd_en_i        : in  std_logic;
    wr_en_i        : in  std_logic;
    lb_conv_busy_o : out std_logic;
    addr_i         : in  std_logic_vector(15 downto 0);
    dat_i          : in  std_logic_vector(15 downto 0);
    --
    PKTEND_o       : out std_logic;
    fifo_wr_o      : out std_logic;
    fifo_dout_o    : out std_logic_vector(15 downto 0);
    fifo_progful_i : in  std_logic
    );

end lb_arbiter;

architecture behave of lb_arbiter is
-- FSM define
  type FSMState is (
    IDLE,
    USB_WR2LOC,
    LOC_WR2USB
    );    
  signal cs, ns : FSMState;

  signal clk      : std_logic                     := '0';
  signal rst_n    : std_logic                     := '0';
  signal LB_Write : std_logic                     := '0';
  signal LB_Read  : std_logic                     := '0';
  signal LB_DataW : std_logic_vector(15 downto 0) := (others => '0');
  signal cnt      : std_logic_vector(15 downto 0) := (others => '0');

  signal wdt_cnt          : integer   := 0;
  signal LB_Read_tmp      : std_logic := '0';
  signal wdt_rst          : std_logic := '0';
  signal fifo_progful_i_r : std_logic := '0';
begin  -- behave
  clk   <= LB_Clk_i;
  rst_n <= not sys_rst_i;

-- purpose: Generate next cs state
  FSM_CS_GEN : process (clk, rst_n)
  begin  -- process FSM_CS_GEN
    if rst_n = '0' then                 -- asynchronous reset (active low)
      cs             <= IDLE;
      lb_conv_busy_o <= '0';
    elsif clk'event and clk = '1' then  -- rising clock edge
      cs <= ns;
      if cs /= IDLE then
        lb_conv_busy_o <= '1';
      else
        lb_conv_busy_o <= '0';
      end if;
    end if;
  end process FSM_CS_GEN;

-- purpose: Generate output
  FSM_OUTPUT_GEN : process (clk, rst_n)
  begin  -- process FSM_NS_GEN
    if rst_n = '0' then                 -- asynchronous reset (active low)
      LB_Write <= '0';
      LB_Read  <= '0';
    elsif clk'event and clk = '1' then  -- rising clock edge
      case ns is
        when IDLE =>
          LB_Write <= '0';
          LB_Read  <= '0';
        when USB_WR2LOC =>
          LB_Write <= '1';
          LB_Read  <= '0';
        when LOC_WR2USB =>
          LB_Write <= '0';
          LB_Read  <= '1';
        when others =>
          LB_Write <= '0';
          LB_Read  <= '0';
      end case;
    end if;
  end process FSM_OUTPUT_GEN;

-- purpose: Generate next ns state
  FSM_NS_GEN : process (cnt, cs, dat_i, rd_en_i, wr_en_i, LB_Ready_i, LB_DataW)
  begin  -- process FSM_NS_GEN
    case cs is
      when IDLE =>
        if rd_en_i = '1' then
          ns <= LOC_WR2USB;
        elsif wr_en_i = '1' then
          ns <= USB_WR2LOC;
        else
          ns <= IDLE;
        end if;
      when USB_WR2LOC =>
        if LB_Ready_i = '0' then
          ns <= USB_WR2LOC;
        else
          ns <= IDLE;
        end if;
      when LOC_WR2USB =>
        if cnt /= LB_DataW - 1 then
          ns <= LOC_WR2USB;
        else
          ns <= IDLE;
        end if;
      when others =>
        ns <= IDLE;
    end case;
  end process FSM_NS_GEN;

  process (clk, rst_n)
  begin  -- process
    if rst_n = '0' then                 -- asynchronous reset (active high)
      cnt              <= (others => '0');
      LB_DataW         <= (others => '0');
      PKTEND_o         <= '1';
      fifo_progful_i_r <= '0';
    elsif clk'event and clk = '1' then  -- rising clock edge
      fifo_progful_i_r <= fifo_progful_i;
      LB_DataW         <= dat_i;
      if cs = LOC_WR2USB and ns = IDLE then
        PKTEND_o <= '0';
      else
        PKTEND_o <= '1';
      end if;

      if cs = IDLE then
        cnt <= (others => '0');
      elsif (LB_Read = '1' or LB_Write = '1') and (LB_Ready_i = '1') then
        cnt <= cnt + 1;
      else
        cnt <= cnt;
      end if;
    end if;
  end process;

  LB_Read_o   <= (LB_Read) when cnt < dat_i and fifo_progful_i_r = '0' else '0';
  LB_Read_tmp <= (LB_Read) when cnt < dat_i and fifo_progful_i_r = '0' else '0';

  LB_Write_o <= LB_Write;
  LB_Addr_o  <= addr_i;
--  LB_DataW <= dat_i when wr_en_i = '1' else LB_DataW;
  LB_DataW_o <= LB_DataW;

  fifo_dout_o <= LB_DataR_i;

  fifo_wr_o <= (LB_Ready_i and LB_Read_tmp);  -- or wdt_rst;

  wdi : process (LB_Clk_i, sys_rst_i)
  begin  -- process wdi
    if sys_rst_i = '1' then             -- asynchronous reset (active low)
      wdt_rst <= '0';
      wdt_cnt <= 0;
    elsif LB_Clk_i'event and LB_Clk_i = '1' then  -- rising clock edge
      if cs = LOC_WR2USB and LB_Ready_i = '0' then
        if wdt_cnt /= 10000 then
          wdt_cnt <= wdt_cnt + 1;
        else
          wdt_cnt <= wdt_cnt;
        end if;
      else
        wdt_cnt <= 0;
      end if;
      if wdt_cnt /= 10000 then
        wdt_rst <= '0';
      else
        wdt_rst <= '1';
      end if;
    end if;
  end process wdi;
  
end behave;
