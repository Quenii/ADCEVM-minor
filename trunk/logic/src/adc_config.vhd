-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : adc_config.vhd
-- Author     :   <Administrator@CHINA-E8466F2CE>
-- Company    : 
-- Created    : 2010-07-11
-- Last update: 2010-08-22
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

entity adc_config is
    
    port (
        -- lb
        LB_Clk_i     : in  std_logic;
        LB_Reset_i   : in  std_logic;
        LB_Addr_i    : in  std_logic_vector(15 downto 0);
        LB_Write_i   : in  std_logic;
        LB_Read_i    : in  std_logic;
        LB_Ready_o   : out std_logic;
        LB_DataW_i   : in  std_logic_vector(15 downto 0);
        LB_DataR_o   : out std_logic_vector(15 downto 0);
        -- had SPI port
        clk_500K_i   : in  std_logic;
        tm_o         : out std_logic;
        gpio1_o      : out std_logic;   -- tie it to gnd
        gpio3_o      : out std_logic;   -- tie it to gnd
        adc_rst_n_o  : out std_logic;
        spi_clk_o    : out std_logic;
        spi_out_en_o : out std_logic;
        spi_di_i     : in  std_logic;
        spi_do_o     : out std_logic;
        spi_cs_n_o   : out std_logic;
        i2c_sdo_o    : out std_logic;
        i2c_scl_o    : out std_logic;
        i2c_sda_o    : out std_logic
        );

end adc_config;

architecture behave of adc_config is

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
    --
    signal updated_had_spi_h  : std_logic                     := '0';
    signal spi24_din          : std_logic_vector(31 downto 0) := (others => '0');
    signal spi24_dout         : std_logic_vector(31 downto 0) := (others => '0');
    signal LB_Ready_had_spi_l : std_logic                     := '0';
    signal LB_Ready_had_spi_h : std_logic                     := '0';
    signal LB_DataR_had_spi_l : std_logic_vector(15 downto 0) := (others => '0');
    signal LB_DataR_had_spi_h : std_logic_vector(15 downto 0) := (others => '0');
    signal LB_Ready_adc_rst   : std_logic                     := '0';
    signal LB_Ready_jtag_ctr  : std_logic                     := '0';

    component adc_jtag_ctr
        port (
            clk_i        : in  std_logic;
            rst_i        : in  std_logic;
            task_start_i : in  std_logic;
            tm_o         : out std_logic;
            spi_clk_o    : out std_logic;
            spi_cs_n_o   : out std_logic;
            spi_sdo_o    : out std_logic);
    end component;
    --
    signal jtag_task_start_i : std_logic := '0';
    signal jtag_rst_i        : std_logic := '0';
    signal jtag_tm_o         : std_logic := '0';
    signal jtag_spi_clk_o    : std_logic := '0';
    signal jtag_spi_cs_n_o   : std_logic := '0';
    signal jtag_spi_sdo_o    : std_logic := '0';

  component spi24
    port (
      clk_i        : in  std_logic;
      rst_i        : in  std_logic;
      task_start_i : in  std_logic;
      data_i       : in  std_logic_vector(23 downto 0);
      data_o       : out std_logic_vector(23 downto 0);
      spi_wren_i   : in  std_logic;
      sck_o        : out std_logic;
      sdi_i        : in  std_logic;
      sdo_o        : out std_logic;
      spi_en_o     : out std_logic;
      cs_n_o       : out std_logic);
  end component;

    constant C_SCK_RATIO : integer := 64;
    constant C_REG_WIDTH : integer := 24;

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
    --
    signal sck_o : std_logic;
    signal spi24_task_start_i : std_logic                     := '0';
    signal spi24_rst_i        : std_logic                     := '0';
    signal spi24_clk_o        : std_logic                     := '0';
    signal spi24_cs_n_o       : std_logic                     := '0';
    signal spi24_spi_en_o     : std_logic                     := '0';
    signal spi24sdo_o         : std_logic                     := '0';
    --
    signal rst_net            : std_logic_vector(15 downto 0) := (others => '0');
    signal tri_reset_n_i      : std_logic                     := '0';
    signal adc_rst_n          : std_logic                     := '0';
    
begin  -- behave
    -- NC
    gpio1_o     <= '0';
    gpio3_o     <= '0';
    i2c_scl_o   <= 'Z';
    i2c_sda_o   <= '0'            when tri_reset_n_i = '1' else 'Z';
    -- jtag special
    tm_o        <= jtag_tm_o      when tri_reset_n_i = '1' else 'Z';
    i2c_sdo_o   <= jtag_spi_sdo_o when tri_reset_n_i = '1' else 'Z';
    -- pc special
    adc_rst_n_o <= adc_rst_n;           -- controled by reg
    -- jtag and spi both used
    spi_clk_o   <= 'Z'            when tri_reset_n_i = '0' else
                   jtag_spi_clk_o when jtag_rst_i = '0'
                   else sck_o;
--                   else not clk_500K_i;
    spi_cs_n_o   <= spi24_cs_n_o and jtag_spi_cs_n_o when tri_reset_n_i = '1' else 'Z';
    -- spi sdio port, make it in top module
    spi_out_en_o <= spi24_spi_en_o                   when tri_reset_n_i = '1' else '0';

-- registers
    adc_rst : lb_target_reg
        generic map (
            ADDR => x"1000")
        port map (
            LB_Clk_i   => LB_Clk_i,
            LB_Reset_i => '0',
            LB_Addr_i  => LB_Addr_i,
            LB_Write_i => LB_Write_i,
            LB_Read_i  => LB_Read_i,
            LB_Ready_o => LB_Ready_adc_rst,
            LB_DataW_i => LB_DataW_i,
            LB_DataR_o => open,
            updated_o  => open,
            ctrl_o     => rst_net,
            sta_i      => x"0000");

    jtag_ctr : lb_target_reg
        generic map (
            ADDR => x"1001")
        port map (
            LB_Clk_i   => LB_Clk_i,
            LB_Reset_i => '0',
            LB_Addr_i  => LB_Addr_i,
            LB_Write_i => LB_Write_i,
            LB_Read_i  => LB_Read_i,
            LB_Ready_o => LB_Ready_jtag_ctr,
            LB_DataW_i => LB_DataW_i,
            LB_DataR_o => open,
            updated_o  => jtag_task_start_i,
            ctrl_o     => open,
            sta_i      => x"0000"
            );

    lb_target_had_spi_wr_l : lb_target_reg
        generic map (
            ADDR => x"1002")
        port map (
            LB_Clk_i   => LB_Clk_i,
            LB_Reset_i => '0',
            LB_Addr_i  => LB_Addr_i,
            LB_Write_i => LB_Write_i,
            LB_Read_i  => LB_Read_i,
            LB_Ready_o => LB_Ready_had_spi_l,
            LB_DataW_i => LB_DataW_i,
            LB_DataR_o => LB_DataR_had_spi_l,
            updated_o  => open,
            ctrl_o     => spi24_din(15 downto 0),
            sta_i      => spi24_dout(15 downto 0));

    lb_target_had_spi_wr_h : lb_target_reg
        generic map (
            ADDR => x"1003")
        port map (
            LB_Clk_i   => LB_Clk_i,
            LB_Reset_i => '0',
            LB_Addr_i  => LB_Addr_i,
            LB_Write_i => LB_Write_i,
            LB_Read_i  => LB_Read_i,
            LB_Ready_o => LB_Ready_had_spi_h,
            LB_DataW_i => LB_DataW_i,
            LB_DataR_o => LB_DataR_had_spi_h,
            updated_o  => spi24_task_start_i,
            ctrl_o     => spi24_din(31 downto 16),
            sta_i      => spi24_dout(31 downto 16));

    LB_DataR_o <= LB_DataR_had_spi_l or LB_DataR_had_spi_h;
    LB_Ready_o <= LB_Ready_had_spi_l or LB_Ready_had_spi_h or LB_Ready_adc_rst or LB_Ready_jtag_ctr;

-------------------------------------------------------------------------------
-- reset reg 
-------------------------------------------------------------------------------
    adc_rst_n     <= rst_net(0);
    tri_reset_n_i <= rst_net(1);
    jtag_rst_i    <= not rst_net(2);
    spi24_rst_i   <= not rst_net(3);

-------------------------------------------------------------------------------
-- jtag and register
-------------------------------------------------------------------------------  
    adc_jtag_ctr_1 : adc_jtag_ctr
        port map (
            clk_i        => clk_500K_i,
            rst_i        => jtag_rst_i,
            task_start_i => jtag_task_start_i,  -- async support
            tm_o         => jtag_tm_o,
            spi_clk_o    => jtag_spi_clk_o,
            spi_cs_n_o   => jtag_spi_cs_n_o,
            spi_sdo_o    => jtag_spi_sdo_o);

-------------------------------------------------------------------------------
-- spi and register
-------------------------------------------------------------------------------
--  spi24_1 : spi24
--    port map (
--      clk_i        => clk_500K_i,
--      rst_i        => spi24_rst_i,
--      task_start_i => spi24_task_start_i,  -- async support
--      data_i       => spi24_din(23 downto 0),
--      data_o       => spi24_dout(23 downto 0),
--      spi_wren_i   => spi24_din(23),       -- set to '1' when read
--      sck_o        => open,
--      sdi_i        => spi_di_i,
--      sdo_o        => spi_do_o,
--      spi_en_o     => spi24_spi_en_o,
--      cs_n_o       => spi24_cs_n_o);

    spi24_v2_1 : spi24_v2
        generic map (
            C_SCK_RATIO => C_SCK_RATIO,
            C_REG_WIDTH => C_REG_WIDTH)
        port map (
            clk_i        => LB_Clk_i,
            rst_i        => spi24_rst_i,
            task_start_i => spi24_task_start_i,  -- async support
            data_i       => spi24_din(23 downto 0),
            data_o       => spi24_dout(23 downto 0),
            spi_wren_i   => spi24_din(23),       -- set to '1' when read
            sck_o        => sck_o,
            sdi_i        => spi_di_i,
            sdo_o        => spi_do_o,
            spi_en_o     => spi24_spi_en_o,
            cs_n_o       => spi24_cs_n_o);

end behave;

