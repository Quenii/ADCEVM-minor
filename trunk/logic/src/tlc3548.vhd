-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : tlc3548.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-07-03
-- Last update: 2011-01-09
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
use ieee.std_logic_unsigned.all;

entity tlc3548 is
  
  port (
    -- lb
    LB_Clk_i          : in  std_logic;
    LB_Reset_i        : in  std_logic;
    LB_Addr_i         : in  std_logic_vector(15 downto 0);
    LB_Write_i        : in  std_logic;
    LB_Read_i         : in  std_logic;
    LB_Ready_o        : out std_logic;
    LB_DataW_i        : in  std_logic_vector(15 downto 0);
    LB_DataR_o        : out std_logic_vector(15 downto 0);
    -- spi port
    TLC3548_sck_o     : out std_logic;
    TLC3548_sdi_i     : in  std_logic;
    TLC3548_sdo_o     : out std_logic;
    TLC3548_cs_n_o    : out std_logic;
    TLC3548_fs_o      : out std_logic;
    TLC3548_start_n_o : out std_logic;  -- do not use it, pull it up
    TLC3548_eco       : in  std_logic
    );

end tlc3548;

architecture behave of tlc3548 is
  component dcm_1M
    port (
      areset : in  std_logic := '0';
      inclk0 : in  std_logic := '0';
      c0     : out std_logic);
  end component;

    constant C_SCK_RATIO : integer := 64;
    constant C_REG_WIDTH : integer := 16;

    component spi24_v2
        generic (
            C_SCK_RATIO : integer;
            C_REG_WIDTH : integer);
        port (
            clk_i        : in  std_logic;
            rst_i        : in  std_logic;
            task_start_i : in  std_logic;
            data_i       : in  std_logic_vector(C_REG_WIDTH-1 downto 0);
            data_o       : out std_logic_vector(C_REG_WIDTH-1 downto 0);
            spi_wren_i   : in  std_logic;
            sck_o        : out std_logic;
            sdi_i        : in  std_logic;
            sdo_o        : out std_logic;
            spi_en_o     : out std_logic;
            cs_n_o       : out std_logic);
    end component;
     
  -- spi16 define
  component spi16
    port (
      clk_i        : in  std_logic;
      rst_i        : in  std_logic;
      task_start_i : in  std_logic;
      data_i       : in  std_logic_vector(15 downto 0);
      data_o       : out std_logic_vector(15 downto 0);
      sck_o        : out std_logic;
      sdi_i        : in  std_logic;
      sdo_o        : out std_logic;
      cs_n_o       : out std_logic);
  end component;
  -- signal define
  signal clk_i : std_logic;

  -- register define
  component lb_target_reg
    generic (
      ADDR : std_logic_vector(15 downto 0));
    port (
      LB_Clk_i   : in  std_logic;
      LB_Reset_i : in  std_logic;
      LB_Addr_i  : in  std_logic_vector(15 downto 0);
      LB_Write_i : in  std_logic;
      LB_Read_i  : in  std_logic;
      LB_Ready_o : out std_logic;
      LB_DataW_i : in  std_logic_vector(15 downto 0);
      LB_DataR_o : out std_logic_vector(15 downto 0);
      updated_o  : out std_logic;
      ctrl_o     : out std_logic_vector(15 downto 0);
      sta_i      : in  std_logic_vector(15 downto 0));
  end component;
  -- signal define
  signal spi_din      : std_logic_vector(15 downto 0) := (others => '0');
  signal spi_dout     : std_logic_vector(15 downto 0) := (others => '0');
  signal task_start_i : std_logic                     := '0';
begin  -- behave

  TLC3548_start_n_o <= '1';
  TLC3548_fs_o      <= '1';

  dcm_1M_1 : dcm_1M                     
    port map (
      areset => LB_Reset_i,
      inclk0 => LB_Clk_i,               -- 40M
      c0     => clk_i);                 -- actually 5M output

  spi16_1 : spi16
    port map (
      clk_i        => clk_i,
      rst_i        => LB_Reset_i,
      task_start_i => task_start_i,
      data_i       => spi_din,
      data_o       => spi_dout,
      sck_o        => TLC3548_sck_o,
      sdi_i        => TLC3548_sdi_i,
      sdo_o        => TLC3548_sdo_o,
      cs_n_o       => TLC3548_cs_n_o);
--  spi24_v2_1: spi24_v2
--      generic map (
--          C_SCK_RATIO => C_SCK_RATIO,
--          C_REG_WIDTH => C_REG_WIDTH)
--      port map (
--          clk_i        => LB_Clk_i,
--          rst_i        => LB_Reset_i,
--          task_start_i => task_start_i,
--          data_i       => spi_din,
--          data_o       => spi_dout,
--          spi_wren_i   => '0',
--          sck_o        => TLC3548_sck_o,
--          sdi_i        => TLC3548_sdi_i,
--          sdo_o        => TLC3548_sdo_o,
--          spi_en_o     => open,
--          cs_n_o       => TLC3548_cs_n_o);
  
  lb_target_3548_spi_wr : lb_target_reg
    generic map (
      ADDR => x"0009")
    port map (
      LB_Clk_i   => LB_Clk_i,
      LB_Reset_i => LB_Reset_i,
      LB_Addr_i  => LB_Addr_i,
      LB_Write_i => LB_Write_i,
      LB_Read_i  => LB_Read_i,
      LB_Ready_o => LB_Ready_o,
      LB_DataW_i => LB_DataW_i,
      LB_DataR_o => LB_DataR_o,
      updated_o  => task_start_i,
      ctrl_o     => spi_din,
      sta_i      => spi_dout);

end behave;
