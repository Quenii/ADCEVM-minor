-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : adc_jtag_ctr.vhd
-- Author     :   <Administrator@CHINA-E8466F2CE>
-- Company    : 
-- Created    : 2010-07-11
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
-- 2010-07-11  1.0      Administrator   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity adc_jtag_ctr is
  
  port (
    clk_i        : in  std_logic;       -- 500KHz
    rst_i        : in  std_logic;
    task_start_i : in  std_logic;
    tm_o         : out std_logic;
    spi_clk_o    : out std_logic;
    spi_cs_n_o   : out std_logic;
    spi_sdo_o    : out std_logic
    );

end adc_jtag_ctr;

architecture behave of adc_jtag_ctr is
  
  signal cnt            : integer range 0 to 65535   := 0;
  signal task_start_i_r : std_logic := '0';
  signal spi_sdo        : std_logic := '0';

begin  -- behave
  task_start_i_r <= '1' when task_start_i = '1' else
                    '0' when cnt = 2700 else
                    task_start_i_r;

  tm_o <= '1' when cnt > 10 and cnt <= 2649
          else '0';
  spi_clk_o <= '1' when cnt > 10 and cnt <= 2649
               else '0';
  spi_cs_n_o <= '0' when (cnt > 10 and cnt <= 516) or (cnt >= 527 and cnt <= 2648)
                else '1';
  spi_sdo_o <= spi_sdo;

  process (clk_i, rst_i)
  begin  -- process
    if rst_i = '1' then                     -- asynchronous reset (active low)
      spi_sdo <= '1';
      cnt     <= 0;
    elsif clk_i'event and clk_i = '1' then  -- rising clock edge
      if task_start_i_r = '1' and cnt /= 2700 then
        cnt <= cnt + 1;
      else
        cnt <= 0;
      end if;
      if cnt >= 11 and cnt <= 2644 then
        spi_sdo <= not spi_sdo;
      else
        spi_sdo <= '1';
      end if;
    end if;
  end process;
  

end behave;
