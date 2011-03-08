-------------------------------------------------------------------------------
-- Title      : SPI controller
-- Project    : 
-------------------------------------------------------------------------------
-- File       : spi.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-05-08
-- Last update: 2010-07-19
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: translate SPI bus to local bus
-------------------------------------------------------------------------------
-- Copyright (c) 2010 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2010-05-08  1.0      LuoQi   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity spi is
  
  port (
    clk_i         : in  std_logic;
    rst_i         : in  std_logic;
    -- local bus port
    task_start_i  : in  std_logic;      -- spi request
    ack_o         : out std_logic;
    updata_da_n_i : in  std_logic;
    data_i        : in  std_logic_vector(23 downto 0);
    data_o        : out std_logic_vector(23 downto 0);
    -- SPI port
    sck_o         : out std_logic;
    sdi_i         : in  std_logic;
    sdo_o         : out std_logic;
    -- LTC2656 configuration port
    ld_cs_n_o     : out std_logic;
    ldac_n_o      : out std_logic
    );

end spi;

architecture behave of spi is
  -- state machine define
  type FSMState is (
    IDLE,
    DC,
    TRANSFER,
    UPDATA);

  signal cs, ns : FSMState;
  signal cnt    : integer range 0 to 63 := 0;
  signal dc_cnt : integer range 0 to 7  := 0;

--  signal sdi_i_r : std_logic := '0';
--  signal sdi_i_rr : std_logic := '0';
  signal task_start_i_r : std_logic                     := '0';
  signal rec_shift_reg  : std_logic_vector(23 downto 0) := (others => '0');
  signal send_shift_reg : std_logic_vector(23 downto 0) := (others => '0');
  
begin  -- behave

  sck_o  <= not clk_i;
  data_o <= rec_shift_reg;
-- purpose: Generate next cs state
  FSM_CS_GEN : process (clk_i, rst_i)
  begin  -- process FSM_CS_GEN
    if rst_i = '1' then
      cs             <= IDLE;
      task_start_i_r <= '0';
--      sdi_i_r        <= '0';
--      sdi_i_rr       <= '0';
    elsif clk_i'event and clk_i = '1' then
      cs             <= ns;
      task_start_i_r <= task_start_i;
--      sdi_i_r        <= sdi_i;
--      sdi_i_rr       <= sdi_i_r;
    end if;
  end process FSM_CS_GEN;
-- purpose: Generate output
  FSM_OUTPUT_GEN : process (clk_i, rst_i)
  begin  -- process FSM_NS_GEN
    if rst_i = '1' then
      sdo_o          <= '0';
      ld_cs_n_o      <= '1';
      send_shift_reg <= (others => '0');
      cnt            <= 0;
      dc_cnt         <= 0;
    elsif clk_i'event and clk_i = '1' then
      case cs is
        when IDLE =>
          sdo_o          <= '1';
          ld_cs_n_o      <= '1';
          send_shift_reg <= data_i;
          --rec_shift_reg  <= (others => '0');
          cnt            <= 0;
          dc_cnt         <= 0;
        when DC =>
          ld_cs_n_o <= '0';
          dc_cnt    <= dc_cnt + 1;
        when TRANSFER =>                -- TRANSFER data
          sdo_o                       <= send_shift_reg(23);
          send_shift_reg(23 downto 1) <= send_shift_reg(22 downto 0);
          ld_cs_n_o                   <= '0';
          cnt                         <= cnt + 1;
        when UPDATA =>
          sdo_o     <= '1';
          ld_cs_n_o <= '1';
          cnt       <= cnt + 1;
        when others => null;
      end case;
    end if;
  end process FSM_OUTPUT_GEN;
-- purpose: Generate next ns state
  FSM_NS_GEN : process (cnt, cs, task_start_i, task_start_i_r, dc_cnt)
  begin  -- process FSM_NS_GEN
    case cs is
      when IDLE =>
        if task_start_i = '1' and task_start_i_r = '0' then
          ns <= DC;
        else
          ns <= IDLE;
        end if;
      when DC =>
        if dc_cnt = 7 then
          ns <= TRANSFER;
        else
          ns <= DC;
        end if;
      when TRANSFER =>                  -- TRANSFER data
        if cnt = 23 then
          ns <= UPDATA;
        else
          ns <= TRANSFER;
        end if;
      when UPDATA =>
        if cnt = 36 then
          ns <= IDLE;
        else
          ns <= UPDATA;
        end if;
      when others =>
        ns <= IDLE;
    end case;
  end process FSM_NS_GEN;

-- Generate ldac_n_o and ack_o, updata data_o to register
  process (clk_i, rst_i)
  begin  -- process
    if rst_i = '1' then                     -- asynchronous reset (active high)
      ldac_n_o      <= '1';
      ack_o         <= '0';
      rec_shift_reg <= (others => '0');
    elsif clk_i'event and clk_i = '1' then  -- rising clock       
      if cnt = 36 then                      -- updata register
        ldac_n_o <= updata_da_n_i;
      else
        ldac_n_o <= '1';
      end if;
      if cnt = 35 then                      -- ack for local bus
        ack_o <= '1';
      else
        ack_o <= '0';
      end if;
      if cnt > 1 and cnt <= 25 then
        rec_shift_reg(0)           <= sdi_i;
        rec_shift_reg(23 downto 1) <= rec_shift_reg(22 downto 0);
      else
        rec_shift_reg <= rec_shift_reg;
      end if;
    end if;
  end process;


end behave;
