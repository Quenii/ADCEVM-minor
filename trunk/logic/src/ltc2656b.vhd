-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : ltc2656b.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-06-04
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
-- 2010-06-04  1.0      Administrator   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity ltc2656b is
  
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
    -- LTC2656 SPI port
    LTC2656_sck_o     : out std_logic;
    LTC2656_sdi_i     : in  std_logic;
    LTC2656_sdo_o     : out std_logic;
    -- LTC2656 configuration port
    LTC2656_ld_cs_n_o : out std_logic;
    LTC2656_ldac_n_o  : out std_logic
    );

end ltc2656b;

architecture behave of ltc2656b is
  --
  component spi
    port (
      clk_i         : in  std_logic;
      rst_i         : in  std_logic;
      -- control port
      task_start_i  : in  std_logic;
      ack_o         : out std_logic;
      updata_da_n_i : in  std_logic;
      data_i        : in  std_logic_vector(23 downto 0);
      data_o        : out std_logic_vector(23 downto 0);
      -- SPI port
      sck_o         : out std_logic;
      sdi_i         : in  std_logic;
      sdo_o         : out std_logic;
      ld_cs_n_o     : out std_logic;
      ldac_n_o      : out std_logic);
  end component;

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
  signal updated_2656_spi_h  : std_logic                     := '0';
  signal spi_din             : std_logic_vector(31 downto 0) := (others => '0');
  signal spi_dout            : std_logic_vector(31 downto 0) := (others => '0');
  signal LB_Ready_2656_spi_l : std_logic                     := '0';
  signal LB_Ready_2656_spi_h : std_logic                     := '0';
  signal LB_DataR_2656_spi_l : std_logic_vector(15 downto 0) := (others => '0');
  signal LB_DataR_2656_spi_h : std_logic_vector(15 downto 0) := (others => '0');
  signal LB_Ready_dat_buf    : std_logic                     := '0';
  
begin  -- behave
  -- 2656 SPI
  spi_1 : spi
    port map (
      clk_i         => LB_Clk_i,
      rst_i         => '0',
      task_start_i  => updated_2656_spi_h,
      ack_o         => open,
      updata_da_n_i => spi_din(24),
      data_i        => spi_din(23 downto 0),
      data_o        => spi_dout(23 downto 0),
      --
      sck_o         => LTC2656_sck_o,
      sdi_i         => LTC2656_sdi_i,
      sdo_o         => LTC2656_sdo_o,
      ld_cs_n_o     => LTC2656_ld_cs_n_o,
      ldac_n_o      => LTC2656_ldac_n_o);

  LB_Ready_o <= LB_Ready_2656_spi_l or LB_Ready_2656_spi_h;
  LB_DataR_o <= LB_DataR_2656_spi_l or LB_DataR_2656_spi_h;

  lb_target_2656_spi_wr_l : lb_target_reg
    generic map (
      ADDR => x"0005")
    port map (
      LB_Clk_i   => LB_Clk_i,
      LB_Reset_i => '0',
      LB_Addr_i  => LB_Addr_i,
      LB_Write_i => LB_Write_i,
      LB_Read_i  => LB_Read_i,
      LB_Ready_o => LB_Ready_2656_spi_l,
      LB_DataW_i => LB_DataW_i,
      LB_DataR_o => LB_DataR_2656_spi_l,
      updated_o  => open,
      ctrl_o     => spi_din(15 downto 0),
      sta_i      => spi_dout(15 downto 0));  --spi_dout(15 downto 0));

  lb_target_2656_spi_wr_h : lb_target_reg
    generic map (
      ADDR => x"0006")
    port map (
      LB_Clk_i   => LB_Clk_i,
      LB_Reset_i => '0',
      LB_Addr_i  => LB_Addr_i,
      LB_Write_i => LB_Write_i,
      LB_Read_i  => LB_Read_i,
      LB_Ready_o => LB_Ready_2656_spi_h,
      LB_DataW_i => LB_DataW_i,
      LB_DataR_o => LB_DataR_2656_spi_h,
      updated_o  => updated_2656_spi_h,
      ctrl_o     => spi_din(31 downto 16),
      sta_i      => spi_dout(31 downto 16));

end behave;
