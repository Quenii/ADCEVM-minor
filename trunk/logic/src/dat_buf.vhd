-------------------------------------------------------------------------------
-- Title      : 
-- Project    : 
-------------------------------------------------------------------------------
-- File       : dat_buf.vhd
-- Author     :   <Administrator@CHINA-6C7FF0513>
-- Company    : 
-- Created    : 2010-05-17
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
-- 2010-05-17  1.0      Administrator   Created
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity dat_buf is
  
  port (
    clk_i            : in  std_logic;   -- clk for ADC lvds port
    rst_i            : in  std_logic;
    -- cmd port
    task_start       : in  std_logic;
    task_length      : in  std_logic_vector(15 downto 0);
    -- data in port
    din_i            : in  std_logic_vector(63 downto 0);
    rd_clk_i         : in  std_logic;
    rd_i             : in  std_logic;
    empty_o          : out std_logic;
    dout_o           : out std_logic_vector(15 downto 0);
    -- SSRAM 0
    ssram_din_i      : in  std_logic_vector(63 downto 0);
    ssram_dout_o     : out std_logic_vector(63 downto 0);
    ssram0_adr_o     : out std_logic_vector(18 downto 0);
    ssram0_dout_en_o : out std_logic;
    ssram0_adv_n_o   : out std_logic;
    ssram0_adsp_n_o  : out std_logic;
    ssram0_adsc_n_o  : out std_logic;
    ssram0_gw_n_o    : out std_logic;
    ssram0_clk_o     : out std_logic;
    ssram0_ce_n_o    : out std_logic;
    ssram0_ce2_n_o   : out std_logic;
    ssram0_ce2_o     : out std_logic;
    ssram0_bwa_n_o   : out std_logic;
    ssram0_bwb_n_o   : out std_logic;
    ssram0_bwc_n_o   : out std_logic;
    ssram0_bwd_n_o   : out std_logic;
    ssram0_bwe_n_o   : out std_logic;
    ssram0_oe_n_o    : out std_logic;
    ssram0_zz_o      : out std_logic;
    ssram0_mode_o    : out std_logic;
    -- SSRAM 1
    ssram1_bwa_n_o   : out std_logic;
    ssram1_bwb_n_o   : out std_logic;
    ssram1_bwc_n_o   : out std_logic;
    ssram1_bwd_n_o   : out std_logic
    );

end dat_buf;

architecture behave of dat_buf is
  -- fifo define, 64bit input, 16bit output
  component fifo64to16
    port (
      aclr    : in  std_logic := '0';
      data    : in  std_logic_vector (63 downto 0);
      rdclk   : in  std_logic;
      rdreq   : in  std_logic;
      wrclk   : in  std_logic;
      wrreq   : in  std_logic;
      q       : out std_logic_vector (15 downto 0);
      rdempty : out std_logic;
      rdusedw : out std_logic_vector (14 downto 0);
      wrfull  : out std_logic;
      wrusedw : out std_logic_vector (12 downto 0));
  end component;
  --
  signal rdclk     : std_logic;
  signal rdreq     : std_logic;
  signal wrclk     : std_logic;
  signal wrreq     : std_logic;
  signal wrreq_new : std_logic;

  signal rdempty      : std_logic;
--  signal almost_empty : std_logic;
  signal rdusedw      : std_logic_vector (14 downto 0);

  signal wrfull         : std_logic;
  signal almost_full    : std_logic;
  signal wrusedw        : std_logic_vector (12 downto 0);
  signal buf_dout       : std_logic_vector(15 downto 0);
  signal LB_Ready_buf_o : std_logic;
  signal selected       : std_logic;

  -- FSM define
  type FSMState is (
    IDLE,
    STORE,
    MID_STATE,
    RECEPTION,
    WT_RECEPTION);

  signal cs, ns         : FSMState;
  -- 
  signal ssram_adr      : std_logic_vector(18 downto 0);  -- 
  signal ssram_dout_en  : std_logic;
  signal ssram_adv_n_o  : std_logic;                      -- 
  signal ssram_adsp_n_o : std_logic;                      -- 
  signal ssram_adsc_n_o : std_logic;                      -- 
  signal ssram_gw_n_o   : std_logic;                      -- 
  signal ssram_ce_n_o   : std_logic;                      -- 
  signal ssram_bwa_n_o  : std_logic;                      --
  signal ssram_bwb_n_o  : std_logic;                      --
  signal ssram_bwc_n_o  : std_logic;                      --
  signal ssram_bwd_n_o  : std_logic;                      --
  signal ssram_bwe_n_o  : std_logic;                      -- 
  signal ssram_oe_n_o   : std_logic;                      -- 
  signal ssram_zz_o     : std_logic;                      -- 
  signal ssram_mode_o   : std_logic;                      --

  --
  signal task_start_r, task_start_rr, task_start_r3 : std_logic;
  signal temp                                       : std_logic_vector(63 downto 0);

  component dcm45
    port (
      areset : in  std_logic := '0';
      inclk0 : in  std_logic := '0';
      c0     : out std_logic;
      c1     : out std_logic;
      locked : out std_logic);
  end component;

begin  -- behave

  dcm45_1 : dcm45
    port map (
      areset => rst_i,
      inclk0 => clk_i,
      c0     => ssram0_clk_o,
      c1     => open,
      locked => open);
  -- ssram0
  ssram0_bwa_n_o  <= ssram_gw_n_o;
  ssram0_bwb_n_o  <= ssram_gw_n_o;
  ssram0_bwc_n_o  <= ssram_gw_n_o;
  ssram0_bwd_n_o  <= ssram_gw_n_o;
  ssram0_zz_o     <= '0';
  ssram0_bwe_n_o  <= '0';
  ssram0_mode_o   <= '0';                              -- liner burst
  ssram0_adsp_n_o <= '1';
  ssram0_adv_n_o  <= (ssram_gw_n_o and ssram_oe_n_o);  --ssram_gw_n_o;
  ssram0_adsc_n_o <= ssram_gw_n_o and ssram_oe_n_o;    --ssram_adsc_n_o;
  ssram0_gw_n_o   <= ssram_gw_n_o;
  ssram0_oe_n_o   <= ssram_oe_n_o;

  ssram0_ce_n_o    <= '0';              --ssram_ce_n_o;
  ssram0_ce2_n_o   <= '0';              --ssram_ce_n_o;
  ssram0_ce2_o     <= '1';              --not ssram_ce_n_o;
  ssram0_dout_en_o <= ssram_dout_en;
  -- ssram1
  ssram1_bwa_n_o   <= ssram_gw_n_o;
  ssram1_bwb_n_o   <= ssram_gw_n_o;
  ssram1_bwc_n_o   <= ssram_gw_n_o;
  ssram1_bwd_n_o   <= ssram_gw_n_o;


-- FSM
-- purpose: Generate next cs state
  FSM_CS_GEN : process (clk_i, rst_i)
  begin  -- process FSM_CS_GEN
    if rst_i = '1' then                     -- asynchronous reset (active low)
      cs            <= IDLE;
      task_start_r  <= '0';
      task_start_rr <= '0';
      task_start_r3 <= '0';
      ssram0_adr_o  <= (others => '0');
    elsif clk_i'event and clk_i = '1' then  -- rising clock edge
      cs            <= ns;
      task_start_r  <= task_start;
      task_start_rr <= task_start_r;
      task_start_r3 <= task_start_rr;
      ssram0_adr_o  <= ssram_adr;
    end if;
  end process FSM_CS_GEN;
-- purpose: Generate output
  FSM_OUTPUT_GEN : process (clk_i, rst_i)
  begin  -- process FSM_NS_GEN
    if rst_i = '1' then                     -- asynchronous reset (active low)
      ssram_adr     <= (others => '0');
      ssram_gw_n_o  <= '1';
      ssram_oe_n_o  <= '1';
      ssram_dout_en <= '0';
      ssram_dout_o  <= (others => '0');
      wrreq         <= '0';
    elsif clk_i'event and clk_i = '1' then  -- rising clock edge
      case cs is
        when IDLE =>
          ssram_adr     <= (others => '0');
          ssram_gw_n_o  <= '1';
          ssram_oe_n_o  <= '1';
          ssram_dout_en <= '0';
          ssram_dout_o  <= (others => '0');
          wrreq         <= '0';
        when STORE =>
          ssram_adr     <= ssram_adr + 1;
          ssram_gw_n_o  <= '0';
          ssram_oe_n_o  <= '1';
          ssram_dout_en <= '1';
          ssram_dout_o  <= din_i;
          wrreq         <= '0';
        when MID_STATE =>
          ssram_adr     <= (others => '0');
          ssram_gw_n_o  <= '1';
          ssram_oe_n_o  <= '1';
          ssram_dout_en <= '1';
          ssram_dout_o  <= din_i;
          wrreq         <= '0';
        when WT_RECEPTION =>
          ssram_adr     <= ssram_adr;
          ssram_gw_n_o  <= '1';
          ssram_oe_n_o  <= '0';
          ssram_dout_en <= '0';
--          ssram_dout_o   <= din_i;
          wrreq         <= '0';
        when RECEPTION =>
          ssram_adr     <= ssram_adr + 1;
          ssram_gw_n_o  <= '1';
          ssram_oe_n_o  <= '0';
          ssram_dout_en <= '0';
--          ssram_dout_o   <= din_i;
          wrreq         <= '1';
        when others => null;
      end case;
    end if;
  end process FSM_OUTPUT_GEN;
-- purpose: Generate next ns state
  FSM_NS_GEN : process (almost_full, cs, ssram_adr, task_start_r3, task_length,
                        task_start_rr)
  begin  -- process FSM_NS_GEN
    case cs is
      when IDLE =>
        if task_start_rr = '1' and task_start_r3 = '0' then
          ns <= STORE;
        else
          ns <= IDLE;
        end if;
      when STORE =>
        if ssram_adr(18 downto 3) = task_length - 1 and ssram_adr(2 downto 0) = "111" then
          ns <= MID_STATE;
        else
          ns <= STORE;
        end if;
      when MID_STATE =>
        ns <= WT_RECEPTION;
      when WT_RECEPTION =>
        if almost_full = '0' then
          ns <= RECEPTION;
        else
          ns <= WT_RECEPTION;
        end if;
      when RECEPTION =>
        if almost_full = '1' then
          ns <= WT_RECEPTION;
        else
          if ssram_adr(18 downto 3) /= task_length - 1 then
            ns <= RECEPTION;
          elsif ssram_adr(2 downto 0) /= "111" then
            ns <= RECEPTION;
          else
            ns <= IDLE;
          end if;
        end if;
      when others =>
        ns <= IDLE;
    end case;
  end process FSM_NS_GEN;

  wrreq_new <= (not ssram_gw_n_o) and (not wrfull);
  -- fifo
  fifo64to16_1 : fifo64to16
    port map (
      aclr    => rst_i,
      wrclk   => clk_i,
      wrreq   => wrreq_new,
      wrfull  => wrfull,
      wrusedw => wrusedw,
      data    => din_i,
      --
      rdclk   => rd_clk_i,
      rdreq   => rd_i,
      rdempty => rdempty,
      rdusedw => rdusedw,
      q       => dout_o
      );

  almost_full  <= '1' when wrusedw > x"0f0" or wrfull = '1'  else '0';  --ext("1", wrusedw'length) or wrfull = '1'  else '0';
--  almost_empty <= '1' when rdusedw < x"040" or rdempty = '1' else '0';  --ext("1", rdusedw'length) or rdempty = '1' else '0';
  empty_o      <= rdempty;              --almost_empty;

  
end behave;
