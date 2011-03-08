-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : lb.vhd
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

entity lb is
  generic (
    FIFO_WR_PORT : std_logic_vector(1 downto 0) := "01";
    FIFO_RD_PORT : std_logic_vector(1 downto 0) := "00"
    );
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
    -- 68013 slave fifo port
    fifo_emp_i     : in  std_logic;
    fifo_ful_i     : in  std_logic;
    fifo_progful_i : in  std_logic;
    fifo_progemp_i : in  std_logic;
    PKTEND_o       : out std_logic;
    fifo_wr_o      : out std_logic;
    fifo_rd_o      : out std_logic;
    fifo_adr_o     : out std_logic_vector(1 downto 0);
    fifo_din_i     : in  std_logic_vector(15 downto 0);
    fifo_dout_o    : out std_logic_vector(15 downto 0)
    );

end lb;

architecture behave of lb is
  component lb_arbiter
    port (
      sys_rst_i      : in  std_logic;
      LB_Clk_i       : in  std_logic;
      LB_Addr_o      : out std_logic_vector(15 downto 0);
      LB_Write_o     : out std_logic;
      LB_Read_o      : out std_logic;
      LB_Ready_i     : in  std_logic;
      LB_DataW_o     : out std_logic_vector(15 downto 0);
      LB_DataR_i     : in  std_logic_vector(15 downto 0);
      rd_en_i        : in  std_logic;
      wr_en_i        : in  std_logic;
      lb_conv_busy_o : out std_logic;
      addr_i         : in  std_logic_vector(15 downto 0);
      dat_i          : in  std_logic_vector(15 downto 0);
      PKTEND_o       : out std_logic;
      fifo_wr_o      : out std_logic;
      fifo_dout_o    : out std_logic_vector(15 downto 0);
      fifo_progful_i : in  std_logic);
  end component;
  --

  -- FSM define
  type FSMState is (
    IDLE,
    RD_SOF,
    CHK_SOF,
    RD_ADR,
    GET_ADR,
    GET_CMD,
    RD_GET_DAT,
    WR_GET_DAT,
    WT_READY
    );                 
  signal cs, ns : FSMState;

  signal clk            : std_logic                     := '0';
  signal rst_n          : std_logic                     := '0';
  signal fifo_wr        : std_logic                     := '0';
  signal fifo_rd        : std_logic                     := '0';
  signal fifo_adr       : std_logic_vector(1 downto 0)  := (others => '0');
  signal adr            : std_logic_vector(15 downto 0) := (others => '0');
  signal dat            : std_logic_vector(15 downto 0) := (others => '0');
  signal wr_en          : std_logic                     := '0';
  signal rd_en          : std_logic                     := '0';
  signal lb_conv_busy   : std_logic                     := '0';
  signal lb_conv_busy_r : std_logic                     := '0';

begin  -- behave
  fifo_adr_o <= fifo_adr;
  fifo_rd_o  <= fifo_rd;
  clk        <= LB_Clk_i;
  rst_n      <= not sys_rst_i;

-- purpose: Generate next cs state
  FSM_CS_GEN : process (clk, rst_n)
  begin  -- process FSM_CS_GEN
    if rst_n = '0' then                 -- asynchronous reset (active low)
      cs             <= IDLE;
      lb_conv_busy_r <= '0';
    elsif clk'event and clk = '1' then  -- rising clock edge
      cs             <= ns;
      lb_conv_busy_r <= lb_conv_busy;
    end if;
  end process FSM_CS_GEN;

-- purpose: Generate output
  FSM_OUTPUT_GEN : process (clk, rst_n)
  begin  -- process FSM_NS_GEN
    if rst_n = '0' then                 -- asynchronous reset (active low)
      fifo_rd  <= '0';
      fifo_adr <= (others => '0');
      rd_en    <= '0';
      wr_en    <= '0';
      adr      <= (others => '0');
      dat      <= (others => '0');
    elsif clk'event and clk = '1' then  -- rising clock edge
      case cs is
        when IDLE =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= (others => '0');
          dat      <= (others => '0');
        when RD_SOF =>
          fifo_rd  <= '1';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= (others => '0');
          dat      <= (others => '0');
        when CHK_SOF =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= (others => '0');
          dat      <= (others => '0');
        when RD_ADR =>
          fifo_rd  <= '1';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= (others => '0');
          dat      <= (others => '0');
        when GET_ADR =>
          fifo_rd  <= '1';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= fifo_din_i;
          dat      <= (others => '0');
        when GET_CMD =>
          fifo_rd  <= '1';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= adr;
          dat      <= (others => '0');
        when RD_GET_DAT =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_WR_PORT;
          rd_en    <= '1';
          wr_en    <= '0';
          adr      <= adr;
          dat      <= fifo_din_i;
        when WR_GET_DAT =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_WR_PORT;
          rd_en    <= '0';
          wr_en    <= '1';
          adr      <= adr;
          dat      <= fifo_din_i;
        when WT_READY =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_WR_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= adr;
          dat      <= dat;
        when others =>
          fifo_rd  <= '0';
          fifo_adr <= FIFO_RD_PORT;
          rd_en    <= '0';
          wr_en    <= '0';
          adr      <= (others => '0');
          dat      <= (others => '0');
      end case;
    end if;
  end process FSM_OUTPUT_GEN;

-- purpose: Generate next ns state
  FSM_NS_GEN : process (cs, fifo_din_i, fifo_emp_i, lb_conv_busy,
                        lb_conv_busy_r)
  begin  -- process FSM_NS_GEN
    case cs is
      when IDLE =>
        if fifo_emp_i = '0' then
          ns <= RD_SOF;
        else
          ns <= IDLE;
        end if;
      when RD_SOF =>
        ns <= CHK_SOF;
      when CHK_SOF =>
        if fifo_din_i = x"BC95" then
          ns <= RD_ADR;
        else
          ns <= IDLE;
        end if;
      when RD_ADR =>
        ns <= GET_ADR;
      when GET_ADR =>
        ns <= GET_CMD;
      when GET_CMD =>
        if fifo_din_i = x"FF00" then     -- read command
          ns <= RD_GET_DAT;
        elsif fifo_din_i = x"00FF" then  -- write command
          ns <= WR_GET_DAT;
        else
          ns <= IDLE;                    -- error
        end if;
      when RD_GET_DAT =>
        ns <= WT_READY;
      when WR_GET_DAT =>
        ns <= WT_READY;
      when WT_READY =>
        if lb_conv_busy = '0' and lb_conv_busy_r = '1' then
          ns <= IDLE;
        else
          ns <= WT_READY;
        end if;
      when others =>
        ns <= IDLE;
    end case;
  end process FSM_NS_GEN;

  -- local bus arbiter
  lb_arbiter_1 : lb_arbiter
    port map (
      sys_rst_i      => sys_rst_i,
      LB_Clk_i       => LB_Clk_i,
      LB_Addr_o      => LB_Addr_o,
      LB_Write_o     => LB_Write_o,
      LB_Read_o      => LB_Read_o,
      LB_Ready_i     => LB_Ready_i,
      LB_DataW_o     => LB_DataW_o,
      LB_DataR_i     => LB_DataR_i,
      rd_en_i        => rd_en,
      wr_en_i        => wr_en,
      lb_conv_busy_o => lb_conv_busy,
      addr_i         => adr,
      dat_i          => dat,
      PKTEND_o       => PKTEND_o,
      fifo_wr_o      => fifo_wr_o,
      fifo_dout_o    => fifo_dout_o,
      fifo_progful_i => fifo_progful_i);

end behave;
