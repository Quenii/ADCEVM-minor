-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : spi16.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-07-03
-- Last update: 2010-07-11
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2010 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2010-07-03  1.0      Administrator   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity spi16 is
  
  port (
    clk_i        : in  std_logic;
    rst_i        : in  std_logic;
    -- local bus port
    task_start_i : in  std_logic;       -- spi request
    data_i       : in  std_logic_vector(15 downto 0);
    data_o       : out std_logic_vector(15 downto 0);
    -- SPI port
    sck_o        : out std_logic;
    sdi_i        : in  std_logic;
    sdo_o        : out std_logic;
    -- LTC2656 configuration port
    cs_n_o       : out std_logic
    );

end spi16;

architecture behave of spi16 is
  -- state machine define
  type FSMState is (
    IDLE,
    TRANSFER,
    UPDATA);

  signal cs, ns         : FSMState;
  signal cnt            : integer range 0 to 63         := 0;
  signal task_start_i_r : std_logic                     := '0';
  signal rec_shift_reg  : std_logic_vector(15 downto 0) := (others => '0');
  signal send_shift_reg : std_logic_vector(15 downto 0) := (others => '0');
  
begin  -- behave

  sck_o  <= clk_i;
  data_o <= rec_shift_reg;

-- purpose: Generate next cs state
  FSM_CS_GEN : process (clk_i, rst_i)
  begin  -- process FSM_CS_GEN
    if rst_i = '1' then
      cs <= IDLE;
    elsif clk_i'event and clk_i = '1' then
      cs <= ns;
    end if;
  end process FSM_CS_GEN;

  task_start_i_r <= '1' when task_start_i = '1' else
                    '0' when cs = UPDATA;

-- purpose: Generate output
  FSM_OUTPUT_GEN : process (clk_i, rst_i)
  begin  -- process FSM_NS_GEN
    if rst_i = '1' then
      sdo_o          <= '0';
      cs_n_o         <= '1';
      send_shift_reg <= (others => '0');
      cnt            <= 0;
    elsif clk_i'event and clk_i = '1' then
      case cs is
        when IDLE =>
          sdo_o          <= '1';
          cs_n_o         <= '1';
          send_shift_reg <= data_i;
          cnt            <= 0;
        when TRANSFER =>                -- TRANSFER data
          sdo_o                       <= send_shift_reg(15);
          send_shift_reg(15 downto 1) <= send_shift_reg(14 downto 0);
          cs_n_o                      <= '0';
          cnt                         <= cnt + 1;
        when UPDATA =>
          sdo_o  <= '1';
          cs_n_o <= '0';
          cnt    <= cnt + 1;
        when others => null;
      end case;
    end if;
  end process FSM_OUTPUT_GEN;
-- purpose: Generate next ns state
  FSM_NS_GEN : process (cnt, cs, task_start_i_r)
  begin  -- process FSM_NS_GEN
    case cs is
      when IDLE =>
        if task_start_i_r = '1' then
          ns <= TRANSFER;
        else
          ns <= IDLE;
        end if;
      when TRANSFER =>                  -- TRANSFER data
        if cnt = 15 then
          ns <= UPDATA;
        else
          ns <= TRANSFER;
        end if;
      when UPDATA =>
        if cnt = 63 then
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
      rec_shift_reg <= (others => '0');
    elsif clk_i'event and clk_i = '1' then  -- rising clock       
      if cnt > 1 and cnt <= 17 then
        rec_shift_reg(0)           <= sdi_i;
        rec_shift_reg(15 downto 1) <= rec_shift_reg(14 downto 0);
      else
        rec_shift_reg <= rec_shift_reg;
      end if;
    end if;
  end process;


end behave;
