-------------------------------------------------------------------------------
-- Title      : Testbench for design "spi24_v2"
-- Project    : 
-------------------------------------------------------------------------------
-- File       : spi24_v2_tb.vhd
-- Author     :   <Administrator@HEAVEN>
-- Company    : 
-- Created    : 2010-08-22
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
-- 2010-08-22  1.0      Administrator   Created
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------------------------------------

entity spi24_v2_tb is

end spi24_v2_tb;

-------------------------------------------------------------------------------

architecture tb_spi24_v2 of spi24_v2_tb is

    -- component generics
    constant C_SCK_RATIO : integer := 8;
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


    -- component ports
    signal clk_i        : std_logic;
    signal rst_i        : std_logic := '1';
    signal task_start_i : std_logic := '0';
    signal data_i       : std_logic_vector(C_REG_WIDTH-1 downto 0);
    signal data_o       : std_logic_vector(C_REG_WIDTH-1 downto 0);
    signal spi_wren_i   : std_logic;
    signal sck_o        : std_logic;
    signal sdi_i        : std_logic;
    signal sdo_o        : std_logic;
    signal spi_en_o     : std_logic;
    signal cs_n_o       : std_logic;

    -- clock
    signal Clk   : std_logic := '1';

begin  -- tb_spi24_v2

    -- component instantiation
    DUT : spi24_v2
        generic map (
            C_SCK_RATIO => C_SCK_RATIO,
            C_REG_WIDTH => C_REG_WIDTH)
        port map (
            clk_i        => clk,
            rst_i        => rst_i,
            task_start_i => task_start_i,
            data_i       => data_i,
            data_o       => data_o,
            spi_wren_i   => spi_wren_i,
            sck_o        => sck_o,
            sdi_i        => sdi_i,
            sdo_o        => sdo_o,
            spi_en_o     => spi_en_o,
            cs_n_o       => cs_n_o);

    -- clock generation
    Clk <= not Clk after 10 ns;

    -- waveform generation
    WaveGen_Proc : process
    begin
        -- insert signal assignments here

        wait until Clk = '1';
    end process WaveGen_Proc;

    process
    begin
        wait for 175 ns;
        rst_i <= '0';
        data_i <= x"AAAAAA";
        wait for 300 ns;
        task_start_i <= '1';
        wait for 20 ns;
        task_start_i <= '0';
        wait for 10 us;
    end process;

    

end tb_spi24_v2;

-------------------------------------------------------------------------------

configuration spi24_v2_tb_tb_spi24_v2_cfg of spi24_v2_tb is
    for tb_spi24_v2
    end for;
end spi24_v2_tb_tb_spi24_v2_cfg;

-------------------------------------------------------------------------------
