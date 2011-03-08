-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : spi24_v2.vhd
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
use ieee.std_logic_arith.all;

entity spi24_v2 is
    generic (
        C_SCK_RATIO : integer;
        C_REG_WIDTH : integer := 24
        );

    port (
        clk_i        : in  std_logic;
        rst_i        : in  std_logic;
        -- local bus port
        task_start_i : in  std_logic;   -- spi request
        data_i       : in  std_logic_vector(C_REG_WIDTH-1 downto 0);
        data_o       : out std_logic_vector(C_REG_WIDTH-1 downto 0);
        -- SPI port
        spi_wren_i   : in  std_logic;
        sck_o        : out std_logic;
        sdi_i        : in  std_logic;
        sdo_o        : out std_logic;
        spi_en_o     : out std_logic;
        -- spi cs out
        cs_n_o       : out std_logic
        );

end spi24_v2;

architecture impl of spi24_v2 is

    constant cpol : std_logic := '0';   -- clock porlarity
    constant cpha : std_logic := '1';   -- clock phase


    type SPIState is (SIDLE, SSTROBE, STRANS, SWAIT);

    signal cstate, nstate : SPIState;

    signal bit_cnt : integer range 0 to C_REG_WIDTH-1;
    signal rat_cnt : integer range 0 to C_SCK_RATIO;

    signal enable  : std_logic;
    signal sck_int : std_logic;
    signal csn_int : std_logic;

    signal trans_reg : std_logic_vector(C_REG_WIDTH-1 downto 0);
    signal rcv_reg   : std_logic_vector(C_REG_WIDTH-1 downto 0);

begin  -- impl

    sck_o  <= sck_int;
    cs_n_o <= csn_int;

    -- purpose: Clk ratio counter
    -- type   : sequential
    -- inputs : clk_i, rst_i
    -- outputs: 
    process (clk_i, rst_i)
    begin  -- process
        if rst_i = '1' then             -- asynchronous reset (active low)
            rat_cnt <= 0;
        elsif clk_i'event and clk_i = '1' then  -- rising clock edge
            if rat_cnt /= 0 then
                rat_cnt <= rat_cnt - 1;
            else
                rat_cnt <= (C_SCK_RATIO/2 -2);
            end if;
        end if;
    end process;

    enable <= '1' when rat_cnt = 0
              else '0';

    sdo_o <= trans_reg(C_REG_WIDTH-1);

    process (clk_i, rst_i)
    begin  -- process
        if rst_i = '1' then             -- asynchronous reset (active low)
            cstate    <= SIDLE;
            csn_int   <= '1';
            trans_reg <= (others => '0');
            rcv_reg   <= (others => '0');
            data_o    <= (others => '0');
        elsif clk_i'event and clk_i = '1' then  -- rising clock edge
            case cstate is
                when SIDLE =>
                    if task_start_i = '1' then
                        cstate    <= SSTROBE;
                        csn_int   <= '0';
                        trans_reg <= data_i;
                        if cpha = '1' then
                            sck_int <= not sck_int;
                        end if;
                    else
                        cstate  <= SIDLE;
                        csn_int <= '1';
                    end if;
                    bit_cnt <= C_REG_WIDTH - 1;
                    sck_int <= cpol;    --set clock polarity;
                when SSTROBE =>
                    if enable = '1' then
                        cstate  <= STRANS;
                        sck_int <= not sck_int;
                        rcv_reg <= rcv_reg(C_REG_WIDTH-2 downto 0) & sdi_i;
                    end if;
                when STRANS =>
                    if enable = '1' then
                        trans_reg <= trans_reg(C_REG_WIDTH-2 downto 0) & '0';

                        if bit_cnt = 0 then
                            sck_int <= cpol;
                            cstate  <= SWAIT;
                        else
                            bit_cnt <= bit_cnt - 1;
                            sck_int <= not sck_int;
                            cstate  <= SSTROBE;
                        end if;
                    end if;
                when SWAIT =>
                    cstate <= SIDLE;
                    data_o <= rcv_reg;
                when others => null;
            end case;
        end if;
    end process;

    process (clk_i, rst_i)
    begin  -- process
        if rst_i = '1' then             -- asynchronous reset (active high)
            spi_en_o      <= '0';
        elsif clk_i'event and clk_i = '1' then  -- rising clock       
            if spi_wren_i = '1' then    -- spi read op
                if (bit_cnt >= 0 and bit_cnt <= 7)
                    or cstate = SIDLE then
                    spi_en_o <= '0';
                else
                    spi_en_o <= '1';
                end if;
            else
                if cstate = SIDLE then
                    spi_en_o <= '0';
                else
                    spi_en_o <= '1';
                end if;
            end if;
        end if;
    end process;
    
    
end impl;
