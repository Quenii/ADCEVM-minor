;/*******************************************************************************
;* Copyright (c) 2001 PLX Technology, Inc.
;*
;* PLX Technology Inc. licenses this software under specific terms and
;* conditions.  Use of any of the software or derviatives thereof in any
;* product without a PLX Technology chip is strictly prohibited.
;*
;* PLX Technology, Inc. provides this software AS IS, WITHOUT ANY WARRANTY,
;* EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF
;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  PLX makes no guarantee
;* or representations regarding the use of, or the results of the use of,
;* the software and documentation in terms of correctness, accuracy,
;* reliability, currentness, or otherwise; and you rely on the software,
;* documentation and results solely at your own risk.
;*
;* IN NO EVENT SHALL PLX BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
;* LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
;* OF ANY KIND.  IN NO EVENT SHALL PLX'S TOTAL LIABILITY EXCEED THE SUM
;* PAID TO PLX FOR THE PRODUCT LICENSED HEREUNDER.
;*
;******************************************************************************/

;/***************************************************************************
; *
; * File Name:
; *
; *      Cpu860.inc
; *
; * Description:
; *
; *      MPC860 Register definitions (for assemblers)
; *
; * Revision History:
; *
; *      09-31-01 : PCI SDK v3.40
; *
; * Notes:
; *
; *     The definitions in this file represent offsets for CPU execution
; *     in Big Endian mode.  If the CPU is intended to be setup for Little
; *     Endian mode, some offsets will need to be modified.  These are
; *     primarily the 8-bit and 16-bit registers.
; *
; ***************************************************************************/




;
;  Special Purpose Registers - User Level
;

SPR_XER                 .equ      1                 ; Fixed-point Exception
SPR_LR                  .equ      8                 ; Link Register
SPR_CTR                 .equ      9                 ; Count Register
SPR_TBL_READ            .equ    268                 ; Time-Base Low for Reads
SPR_TBU_READ            .equ    269                 ; Time-Base Upper for Reads


;
;  Special Purpose Registers - Supervisor Level
;

SPR_DSISR               .equ     18                 ; Data Storage Exception Status
SPR_DAR                 .equ     19                 ; Data Address
SPR_DEC                 .equ     22                 ; Decrementer
SPR_SRR0                .equ     26                 ; Machine Status Save/Restore 0
SPR_SRR1                .equ     27                 ; Machine Status Save/Restore 1
SPR_SPGR0               .equ    272                 ; Special Purpose General 0
SPR_SPGR1               .equ    273                 ; Special Purpose General 1
SPR_SPGR2               .equ    274                 ; Special Purpose General 2
SPR_SPGR3               .equ    275                 ; Special Purpose General 3
SPR_TBL_WRITE           .equ    284                 ; Time-Base Low for Writes
SPR_TBU_WRITE           .equ    285                 ; Time-Base Upper for Writes
SPR_PVR                 .equ    287                 ; Processor Version Register


;
;  Special Purpose Registers - 860-Specific
;

SPR_EIE                 .equ     80                 ; SPR for enabling EE of MSR
SPR_EID                 .equ     81                 ; SPR for disabling EE of MSR
SPR_NRI                 .equ     82                 ; SPR for clearing EE & RI of MSR
SPR_ICR                 .equ    148                 ; Interrupt Cause Register
SPR_DER                 .equ    149                 ; Debug Enable Register
SPR_ICTRL               .equ    158                 ; Instruction Support Control Register
SPR_IC_CST              .equ    560                 ; Instruction Cache Command/Status
SPR_IC_ADR              .equ    561                 ; Instruction Cache Address register
SPR_DC_CST              .equ    568                 ; Data Cache Command/Status
SPR_DC_ADR              .equ    569                 ; Data Cache Address register
SPR_DC_DAT              .equ    570                 ; Data Cache Data Register
SPR_DPDR                .equ    630                 ; Development Port Data Register
SPR_IMMR                .equ    638                 ; Special Purpose Reg
SPR_MI_CTR              .equ    784                 ; MMU Instruction Cache Control register
SPR_MI_AP               .equ    786                 ; MMU Instruction Access Permission Register
SPR_MI_EPN              .equ    787                 ; MMU Instruction Effective Page Number Reg
SPR_MI_TWC              .equ    789                 ; MMU Instruction Tablewalk Control Register
SPR_MI_RPN              .equ    790                 ; MMU Instruction Real Page Number Register
SPR_MI_DTR              .equ    792                 ; MMU Data Cache Control register
SPR_MD_AP               .equ    794                 ; MMU Data Access Permission Register
SPR_MD_EPN              .equ    795                 ; MMU Data Effective Page Number Register
SPR_MD_TWC              .equ    797                 ; MMU Data Tablewalk Control Register
SPR_MD_RPN              .equ    798                 ; MMU Instruction Real Page Number Register


;
;  SIU - System interface unit
;

IMMR_SIU_SIUMCR         .equ    0x00                ; Module Configuration Reg
IMMR_SIU_SYPCR          .equ    0x04                ; System Protection Ctrl
IMMR_SIU_RSVD1L         .equ    0x08                ; Reserved (4 bytes)
IMMR_SIU_RSVD1H         .equ    0x0c                ; Reserved (2 bytes)
IMMR_SIU_SWSR           .equ    0x0e                ; Software Service Reg
IMMR_SIU_SIPEND         .equ    0x10                ; SIU Interrupt Pending
IMMR_SIU_SIMASK         .equ    0x14                ; SIU Interrupt Mask
IMMR_SIU_SIEL           .equ    0x18                ; SIU Int. Edge Level
IMMR_SIU_SIVEC          .equ    0x1C                ; SIU Interrupt Vector
IMMR_SIU_TESR           .equ    0x20                ; Transfer Error Status
IMMR_SIU_RSVD2          .equ    0x24                ; Reserved (12 bytes)
IMMR_SIU_SDCR           .equ    0x30                ; SDMA Configuration Reg.
IMMR_SIU_RSVD3          .equ    0x34                ; Reserved (48 bytes)


;
;  MEMC - Memory Controller
;

IMMR_MEMC_BR0           .equ    0x0100              ; Bank 0
IMMR_MEMC_OR0           .equ    0x0104
IMMR_MEMC_BR1           .equ    0x0108              ; Bank 1
IMMR_MEMC_OR1           .equ    0x010c
IMMR_MEMC_BR2           .equ    0x0110              ; Bank 2
IMMR_MEMC_OR2           .equ    0x0114
IMMR_MEMC_BR3           .equ    0x0118              ; Bank 3
IMMR_MEMC_OR3           .equ    0x011c
IMMR_MEMC_BR4           .equ    0x0120              ; Bank 4
IMMR_MEMC_OR4           .equ    0x0124
IMMR_MEMC_BR5           .equ    0x0128              ; Bank 5
IMMR_MEMC_OR5           .equ    0x012c
IMMR_MEMC_BR6           .equ    0x0130              ; Bank 6
IMMR_MEMC_OR6           .equ    0x0134
IMMR_MEMC_BR7           .equ    0x0138              ; Bank 7
IMMR_MEMC_OR7           .equ    0x013c
IMMR_MEMC_RSVD1         .equ    0x0140              ; Reserved (36 bytes)
IMMR_MEMC_MAR           .equ    0x0164              ; Memory Address Register
IMMR_MEMC_MCR           .equ    0x0168              ; Memory Command Register
IMMR_MEMC_RSVD2         .equ    0x016c              ; Reserved (4 bytes)
IMMR_MEMC_MAMR          .equ    0x0170              ; Machine A Mode Register
IMMR_MEMC_MBMR          .equ    0x0174              ; Machine B Mode Register
IMMR_MEMC_MSTAT         .equ    0x0178              ; Memory Status Register
IMMR_MEMC_MPTPR         .equ    0x017a              ; Periodic Timer Prescaler
IMMR_MEMC_MDR           .equ    0x017c              ; Memory Data Register
IMMR_MEMC_RSVD3         .equ    0x0180              ; Reserved (128 bytes)


;
;  CLKR - Clocks and Reset
;

IMMR_CLKR_SCCR          .equ    0x0280              ; System Clock Control Reg
IMMR_CLKR_PLPRCR        .equ    0x0284              ; PLL/Low Power/Reset Ctrl
IMMR_CLKR_RSR           .equ    0x0288              ; Reset Status Register
IMMR_CLKR_RSVD          .equ    0x028c              ; Reserved (116 bytes)


;
; Constants for Cache Commands
;

CacheCmdReserved_1          .equ    0x0000
CacheCmdSetWriteThrough     .equ    0x0100
CacheCmdEnable              .equ    0x0200
CacheCmdClearWriteThrough   .equ    0x0300
CacheCmdDisable             .equ    0x0400
CacheCmdSetLE               .equ    0x0500
CacheCmdLoadAndLock         .equ    0x0600
CacheCmdClearLE             .equ    0x0700
CacheCmdUnlockBlock         .equ    0x0800
CacheCmdReserved_2          .equ    0x0900
CacheCmdUnlockAll           .equ    0x0a00
CacheCmdReserved_3          .equ    0x0b00
CacheCmdInvAll              .equ    0x0c00
CacheCmdReserved_4          .equ    0x0d00
CacheCmdFlushBlock          .equ    0x0e00
CacheCmdReserved_5          .equ    0x0f00
