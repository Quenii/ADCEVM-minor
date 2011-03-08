-------------------------------------------------------------------------------
-- Title      : clock manager
-- Project    : 
-------------------------------------------------------------------------------
-- File       : clock_manager.vhd
-- Author     :   <Liu Peng@GKHY-LIUPENG>
-- Company    : 
-- Created    : 2009-12-31
-- Last update: 2010-09-04
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
-- Copyright (c) 2009 
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2009-12-31  1.0      Liu Peng        Created
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity clock_manager is
  generic (
    RST_CYC : integer := 80000000);
  port (
    clk125_i : in  std_logic;
    rst_i    : in  std_logic;
    rst_o    : out std_logic;
    clk125_o : out std_logic;
    clk_3M_o : out std_logic;
    clk20_o  : out std_logic
    );

end clock_manager;

architecture archi of clock_manager is
  
  component clk80
    port (
      areset : in  std_logic := '0';
      inclk0 : in  std_logic := '0';
      c0     : out std_logic;
      c1     : out std_logic;
      locked : out std_logic);
  end component;

  signal rst_cnt_125   : integer   := 0;
  signal clk125_locked : std_logic := '0';

  component dcm125
      port (
          inclk0 : in  std_logic := '0';
          c0     : out std_logic;
          c1     : out std_logic;
          locked : out std_logic);
  end component;
  
begin  -- archi

  dcm125_1 : dcm125
    port map (
      areset => rst_i,
      inclk0 => clk125_i,
      c0     => clk125_o,
      c1     => clk20_o,
      c2     => clk_3M_o,
      locked => clk125_locked);

  process (clk125_i, clk125_locked, rst_i)
  begin
    if clk80_locked = '0' or rst_i = '1' then
      rst_cnt <= 0;
      rst_o   <= '1';
    elsif clk125_i'event and clk125_i = '1' then
      if rst_cnt /= RST_CYC then
        rst_cnt <= rst_cnt + 1;
        rst_o   <= '1';
      else
        rst_o <= '0';
      end if;
    end if;
  end process;
  
end archi;
