-------------------------------------------------------------------------------
-- Title      : Local Bus Target Register
-- Project    : 
-------------------------------------------------------------------------------
-- File       : lb_target_reg.vhd
-- Author     :   <Liu Peng@GKHY-LIUPENG>
-- Company    : 
-- Created    : 2010-01-11
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
-- 2010-01-11  1.0      Liu Peng        Created
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lb_target_fifo_rome is

  generic (
    ADDR : std_logic_vector(15 downto 0));
  port (
    LB_Clk_i    : in  std_logic;
    LB_Reset_i  : in  std_logic;
    LB_Addr_i   : in  std_logic_vector(15 downto 0);
    LB_Write_i  : in  std_logic;
    LB_Read_i   : in  std_logic;
    LB_Ready_o  : out std_logic;
    LB_DataW_i  : in  std_logic_vector(15 downto 0);
    LB_DataR_o  : out std_logic_vector(15 downto 0);
    --
    fifo_emp_i  : in  std_logic;
    fifo_rd_o   : out std_logic;
    fifo_din_i  : in  std_logic_vector(15 downto 0);
    --
    fifo_ful_i  : in  std_logic;
    fifo_wr_o   : out std_logic;
    fifo_dout_o : out std_logic_vector(15 downto 0)
    );

end lb_target_fifo_rome;

architecture archi of lb_target_fifo_rome is

  signal selected : std_logic := '0';
  
begin  -- archi

  selected <= '1' when ADDR = LB_Addr_i else '0';
--  LB_Ready_o <= selected;

  LB_DataR_o <= fifo_din_i when selected = '1' and LB_Read_i = '1' else
                (others => '0');
  
  LB_Ready_o <= not fifo_emp_i when selected = '1' and LB_Read_i = '1' else
                not fifo_ful_i when selected = '1' and LB_Write_i = '1' else
                '0';
  
  fifo_rd_o <= not fifo_emp_i and LB_Read_i  when selected = '1' else '0';
  fifo_wr_o <= not fifo_ful_i and LB_write_i when selected = '1' else '0';

  fifo_dout_o <= LB_DataW_i;
  
end archi;
