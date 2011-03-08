#ifndef __CPU860_H
#define __CPU860_H

/*******************************************************************************
 * Copyright (c) 2001 PLX Technology, Inc.
 *
 * PLX Technology Inc. licenses this software under specific terms and
 * conditions.  Use of any of the software or derviatives thereof in any
 * product without a PLX Technology chip is strictly prohibited.
 *
 * PLX Technology, Inc. provides this software AS IS, WITHOUT ANY WARRANTY,
 * EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  PLX makes no guarantee
 * or representations regarding the use of, or the results of the use of,
 * the software and documentation in terms of correctness, accuracy,
 * reliability, currentness, or otherwise; and you rely on the software,
 * documentation and results solely at your own risk.
 *
 * IN NO EVENT SHALL PLX BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.  IN NO EVENT SHALL PLX'S TOTAL LIABILITY EXCEED THE SUM
 * PAID TO PLX FOR THE PRODUCT LICENSED HEREUNDER.
 *
 ******************************************************************************/

/***************************************************************************
 *
 * File Name:
 *
 *      Cpu860.h
 *
 * Description:
 *
 *      MPC860 Register definitions
 *
 * Revision History:
 *
 *      09-31-01 : PCI SDK v3.40
 *
 * Notes:
 *
 *     The definitions in this file represent offsets for CPU execution
 *     in Big Endian mode.  If the CPU is intended to be setup for Little
 *     Endian mode, some offsets will need to be modified.  These are
 *     primarily the 8-bit and 16-bit registers.
 *
 ***************************************************************************/


#include "Plx.h"
#include "PlxTypes.h"




/*
 *  MPC860 Special Purpose Registers
 */

#define SPR_EIE                      80                 // SPR for enabling EE of MSR
#define SPR_EID                      81                 // SPR for disabling EE of MSR
#define SPR_NRI                      82                 // SPR for clearing EE & RI of MSR
#define SPR_ICR                     148                 // Interrupt Cause Register
#define SPR_DER                     149                 // Debug Enable Register
#define SPR_ICTRL                   158                 // Instruction Support Control Register
#define SPR_IC_CST                  560                 // Instruction Cache Command/Status
#define SPR_IC_ADR                  561                 // Instruction Cache Address register
#define SPR_DC_CST                  568                 // Data Cache Command/Status
#define SPR_DC_ADR                  569                 // Data Cache Address register
#define SPR_DC_DAT                  570                 // Data Cache Data Register
#define SPR_DPDR                    630                 // Development Port Data Register
#define SPR_IMMR                    638                 // Special Purpose Register
#define SPR_MI_CTR                  784                 // MMU Instruction Cache Control register
#define SPR_MI_AP                   786                 // MMU Instruction Access Permission Register
#define SPR_MI_EPN                  787                 // MMU Instruction Effective Page Number Reg
#define SPR_MI_TWC                  789                 // MMU Instruction Tablewalk Control Register
#define SPR_MI_RPN                  790                 // MMU Instruction Real Page Number Register
#define SPR_MI_DTR                  792                 // MMU Data Cache Control register
#define SPR_MD_AP                   794                 // MMU Data Access Permission Register
#define SPR_MD_EPN                  795                 // MMU Data Effective Page Number Register
#define SPR_MD_TWC                  797                 // MMU Data Tablewalk Control Register
#define SPR_MD_RPN                  798                 // MMU Instruction Real Page Number Register


/*
 *  SIU - System interface unit
 */

#define IMMR_SIU_SIUMCR             0x00                // Module Configuration Reg
#define IMMR_SIU_SYPCR              0x04                // System Protection Ctrl
#define IMMR_SIU_RSVD1L             0x08                // Reserved (4 bytes)
#define IMMR_SIU_RSVD1H             0x0c                // Reserved (2 bytes)
#define IMMR_SIU_SWSR               0x0e                // Software Service Reg
#define IMMR_SIU_SIPEND             0x10                // SIU Interrupt Pending
#define IMMR_SIU_SIMASK             0x14                // SIU Interrupt Mask
#define IMMR_SIU_SIEL               0x18                // SIU Int. Edge Level
#define IMMR_SIU_SIVEC              0x1C                // SIU Interrupt Vector
#define IMMR_SIU_TESR               0x20                // Transfer Error Status
#define IMMR_SIU_RSVD2              0x24                // Reserved (12 bytes)
#define IMMR_SIU_SDCR               0x30                // SDMA Configuration Reg
#define IMMR_SIU_RSVD3              0x34                // Reserved (48 bytes)


/*
 *  Bit definitions for IRQ and LEVEL values in SIPEND and SIMASK
 */

#define SIU_IRQ0                    0x80000000
#define SIU_LVL0                    0x40000000
#define SIU_IRQ1                    0x20000000
#define SIU_LVL1                    0x10000000
#define SIU_IRQ2                    0x08000000
#define SIU_LVL2                    0x04000000
#define SIU_IRQ3                    0x02000000
#define SIU_LVL3                    0x01000000
#define SIU_IRQ4                    0x00800000
#define SIU_LVL4                    0x00400000
#define SIU_IRQ5                    0x00200000
#define SIU_LVL5                    0x00100000
#define SIU_IRQ6                    0x00080000
#define SIU_LVL6                    0x00040000
#define SIU_IRQ7                    0x00020000
#define SIU_LVL7                    0x00010000


/*
 *  Bit definitions for the SIEL register:
 */

#define SIEL_ED0                    0x80000000
#define SIEL_WM0                    0x40000000
#define SIEL_ED1                    0x20000000
#define SIEL_WM1                    0x10000000
#define SIEL_ED2                    0x08000000
#define SIEL_WM2                    0x04000000
#define SIEL_ED3                    0x02000000
#define SIEL_WM3                    0x01000000
#define SIEL_ED4                    0x00800000
#define SIEL_WM4                    0x00400000
#define SIEL_ED5                    0x00200000
#define SIEL_WM5                    0x00100000
#define SIEL_ED6                    0x00080000
#define SIEL_WM6                    0x00040000
#define SIEL_ED7                    0x00020000
#define SIEL_WM7                    0x00010000


/*
 *  SIU Interrupt Numbers
 */

#define SIU_INT_IRQ0                0x0
#define SIU_INT_LEVEL0              0x1
#define SIU_INT_IRQ1                0x2
#define SIU_INT_LEVEL1              0x3
#define SIU_INT_IRQ2                0x4 
#define SIU_INT_LEVEL2              0x5 
#define SIU_INT_IRQ3                0x6 
#define SIU_INT_LEVEL3              0x7 
#define SIU_INT_IRQ4                0x8 
#define SIU_INT_LEVEL4              0x9 
#define SIU_INT_IRQ5                0xa 
#define SIU_INT_LEVEL5              0xb 
#define SIU_INT_IRQ6                0xc 
#define SIU_INT_LEVEL6              0xd 
#define SIU_INT_IRQ7                0xe 
#define SIU_INT_LEVEL7              0xf 
#define SIU_INT_TOTAL_NUM           0x10


/*
 *  PCMCIA
 */

#define IMMR_PCMCIA_PBR0            0x0080
#define IMMR_PCMCIA_POR0            0x0084
#define IMMR_PCMCIA_PBR1            0x0088
#define IMMR_PCMCIA_POR1            0x008C
#define IMMR_PCMCIA_PBR2            0x0090
#define IMMR_PCMCIA_POR2            0x0094
#define IMMR_PCMCIA_PBR3            0x0098
#define IMMR_PCMCIA_POR3            0x009C
#define IMMR_PCMCIA_PBR4            0x00A0
#define IMMR_PCMCIA_POR4            0x00A4
#define IMMR_PCMCIA_PBR5            0x00A8
#define IMMR_PCMCIA_POR5            0x00AC
#define IMMR_PCMCIA_PBR6            0x00B0
#define IMMR_PCMCIA_POR6            0x00B4
#define IMMR_PCMCIA_PBR7            0x00B8
#define IMMR_PCMCIA_POR7            0x00BC
#define IMMR_PCMCIA_PGCRA           0x00E0
#define IMMR_PCMCIA_PGCRB           0x00E4
#define IMMR_PCMCIA_PSCR            0x00E8
#define IMMR_PCMCIA_PIPR            0x00F0
#define IMMR_PCMCIA_PER             0x00F8


/*
 *  MEMC - Memory Controller
 */

#define IMMR_MEMC_BR0               0x0100              // Bank 0
#define IMMR_MEMC_OR0               0x0104
#define IMMR_MEMC_BR1               0x0108              // Bank 1
#define IMMR_MEMC_OR1               0x010c
#define IMMR_MEMC_BR2               0x0110              // Bank 2
#define IMMR_MEMC_OR2               0x0114
#define IMMR_MEMC_BR3               0x0118              // Bank 3
#define IMMR_MEMC_OR3               0x011c
#define IMMR_MEMC_BR4               0x0120              // Bank 4
#define IMMR_MEMC_OR4               0x0124
#define IMMR_MEMC_BR5               0x0128              // Bank 5
#define IMMR_MEMC_OR5               0x012c
#define IMMR_MEMC_BR6               0x0130              // Bank 6
#define IMMR_MEMC_OR6               0x0134
#define IMMR_MEMC_BR7               0x0138              // Bank 7
#define IMMR_MEMC_OR7               0x013c
#define IMMR_MEMC_RSVD1             0x0140              // Reserved (36 bytes)
#define IMMR_MEMC_MAR               0x0164              // Memory Address Register
#define IMMR_MEMC_MCR               0x0168              // Memory Command Register
#define IMMR_MEMC_RSVD2             0x016c              // Reserved (4 bytes)
#define IMMR_MEMC_MAMR              0x0170              // Machine A Mode Register
#define IMMR_MEMC_MBMR              0x0174              // Machine B Mode Register
#define IMMR_MEMC_MSTAT             0x0178              // Memory Status Register
#define IMMR_MEMC_MPTPR             0x017a              // Periodic Timer Prescaler
#define IMMR_MEMC_MDR               0x017c              // Memory Data Register
#define IMMR_MEMC_RSVD3             0x0180              // Reserved (128 bytes)


/*
 *  SIMT - System Integration Timers
 */

#define IMMR_SIMT_TBSCR             0x0200              // Timebase Status/Control
#define IMMR_SIMT_RSVD1             0x0202              // Reserved (2 bytes)
#define IMMR_SIMT_TBREFA            0x0204              // Timebase Reference A
#define IMMR_SIMT_TBREFL            0x0208              // Timebase Reference B
#define IMMR_SIMT_RSVD2             0x020c              // Reserved (20 bytes)
#define IMMR_SIMT_RTCSC             0x0220              // Real Time Clock CSR
#define IMMR_SIMT_RSVD3             0x0222              // Reserved (2 bytes)
#define IMMR_SIMT_RTC               0x0224              // Real Time Clock Register
#define IMMR_SIMT_RTSEC             0x0228              // Real Time Alarm Seconds
#define IMMR_SIMT_RTCAL             0x022c              // Real Time Alarm Register
#define IMMR_SIMT_RSVD4             0x0230              // Reserved (16 bytes)
#define IMMR_SIMT_PISCR             0x0240              // Periodic Int Status/Ctrl
#define IMMR_SIMT_RSVD5             0x0242              // Reserved (2 bytes)
#define IMMR_SIMT_PITC              0x0244              // Periodic Int Count
#define IMMR_SIMT_PITR              0x0248              // Periodic Int Timer
#define IMMR_SIMT_RSVD6             0x024c              // Reserved (52 bytes)


/*
 *  CLKR - Clocks and Reset
 */

#define IMMR_CLKR_SCCR              0x0280              // System Clock Control Reg
#define IMMR_CLKR_PLPRCR            0x0284              // PLL/Low Power/Reset Ctrl
#define IMMR_CLKR_RSR               0x0288              // Reset Status Register
#define IMMR_CLKR_RSVD              0x028c              // Reserved (116 bytes)


/*
 *  SIMT - System Integration Timer Keys
 */

#define IMMR_SIMTK_TBSCRK           0x0300              // Timebase Status/Control Key
#define IMMR_SIMTK_TBREFAK          0x0304              // Timebase Reference A Key
#define IMMR_SIMTK_TBREFBK          0x0308              // Timebase Reference B Key
#define IMMR_SIMTK_TBK              0x030c              // Timebase Decrementer Key
#define IMMR_SIMTK_RSVD1            0x0310              // Reserved (16 bytes)
#define IMMR_SIMTK_RTCSCK           0x0320              // Real Time Clock Status/Control Key
#define IMMR_SIMTK_RTCK             0x0324              // Real Time Clock Key
#define IMMR_SIMTK_RTSECK           0x0328              // Real Time Clock Alarm Seconds Key
#define IMMR_SIMTK_RTCALK           0x032c              // Real Time Clock Alarm Key
#define IMMR_SIMTK_RSVD2            0x0330              // Reserved (16 bytes)
#define IMMR_SIMTK_PISCRK           0x0340              // Periodic Interrupt Status/Control Key
#define IMMR_SIMTK_PITCK            0x0344              // Periodic Interrupt Count Key
#define IMMR_SIMTK_RSVD3            0x0348              // Reserved (56 bytes)


/*
 *  CLKR - Clocks and Reset Keys
 */

#define IMMR_CLKRK_SCCRK            0x0380              // System Clock Control Key
#define IMMR_CLKRK_PLPRCRK          0x0384              // PLL/Low Power/Reset Control Key
#define IMMR_CLKRK_RSRK             0x0388              // Reset Status Register Key
#define IMMR_CLKRK_RSVD             0x038c              // Reserved (1236 bytes)


/*
 *  IIC - I2C Controller
 */

#define IMMR_IIC_BASE               0x0860


/*
 *  DMA - DMA Controller
 */

#define IMMR_DMA_BASE               0x0900


/*
 *  CPMI - CPM Interrupt Control
 */

#define IMMR_CPMI_CIVR              0x930               // CPM Interrupt Vector Register
#define IMMR_CPMI_RSVD              0x932               // Reserved - 14 bytes
#define IMMR_CPMI_CICR              0x940               // CPM Interrupt Configuration Register
#define IMMR_CPMI_CIPR              0x944               // CPM Interrupt Pending Register
#define IMMR_CPMI_CIMR              0x948               // CPM Interrupt Mask Register
#define IMMR_CPMI_CISR              0x94C               // CPM Interrupt In-service Register


/*
 *  CPM Interrupt Numbers & Priorities
 */

#define CPM_INT_ERROR               0x00
#define CPM_INT_PC4                 0x01
#define CPM_INT_PC5                 0x02
#define CPM_INT_SMC2                0x03
#define CPM_INT_SMC1                0x04
#define CPM_INT_SP1                 0x05
#define CPM_INT_PC6                 0x06
#define CPM_INT_TIMER4              0x07
#define CPM_INT_RESERVED1           0x08
#define CPM_INT_PC7                 0x09
#define CPM_INT_PC8                 0x0a
#define CPM_INT_PC9                 0x0b
#define CPM_INT_TIMER3              0x0c
#define CPM_INT_RESERVED2           0x0d
#define CPM_INT_PC10                0x0e
#define CPM_INT_PC11                0x0f
#define CPM_INT_I2C                 0x10
#define CPM_INT_RISC                0x11
#define CPM_INT_TIMER2              0x12
#define CPM_INT_RESERVED3           0x13
#define CPM_INT_IDMA2               0x14
#define CPM_INT_IDMA1               0x15
#define CPM_INT_SDMA                0x16
#define CPM_INT_PC12                0x17
#define CPM_INT_PC13                0x18
#define CPM_INT_TIMER1              0x19
#define CPM_INT_PC14                0x1a
#define CPM_INT_SCC4                0x1b
#define CPM_INT_SCC3                0x1c
#define CPM_INT_SCC2                0x1d
#define CPM_INT_SCC1                0x1e
#define CPM_INT_PC15                0x1f
#define CPM_INT_TOTAL_NUM           0x20


/*
 *  CPM Command bit definitions
 */

#define CP_CMD_CPM_RESET            0x8000
#define CP_CMD_CPM_PROCESSING       0x0001


/*
 *  CPM Command Channel Numbers
 */

#define CP_CMD_CHANNEL_SCC1         0x0000
#define CP_CMD_CHANNEL_IDMA1        0x0010
#define CP_CMD_CHANNEL_SCC2         0x0040
#define CP_CMD_CHANNEL_IDMA2        0x0050
#define CP_CMD_CHANNEL_SCC3         0x0080
#define CP_CMD_CHANNEL_SMC1         0x0090
#define CP_CMD_CHANNEL_SCC4         0x00C0
#define CP_CMD_CHANNEL_SMC2         0x00D0


/*
 *  CPM SCC Command Opcodes
 */

#define CP_CMD_SCC_INIT_RX_TX       0x0000
#define CP_CMD_SCC_INIT_RX          0x0100
#define CP_CMD_SCC_INIT_TX          0x0200
#define CP_CMD_SCC_HUNT_MODE        0x0300
#define CP_CMD_SCC_STOP_TX          0x0400
#define CP_CMD_SCC_GRACE_STOP_TX    0x0500
#define CP_CMD_SCC_RESTART_TX       0x0600
#define CP_CMD_SCC_CLOSE_RX_BD      0x0700
#define CP_CMD_SCC_SET_GROUP_ADDR   0x0800
#define CP_CMD_SCC_RESET_BCS        0x0A00


/*
 *  PIO - I/O Port
 */

#define IMMR_PIO_PADIR              0x0950              // Port A Data Direction
#define IMMR_PIO_PAPAR              0x0952              // Port A Pin Assignment
#define IMMR_PIO_PAODR              0x0954              // Port A Open Drain Reg
#define IMMR_PIO_PADAT              0x0956              // Port A Data Register
#define IMMR_PIO_RSVD_1             0x0958              // Reserved (8 bytes)
#define IMMR_PIO_PCDIR              0x0960              // Port C Data Direction
#define IMMR_PIO_PCPAR              0x0962              // Port C Pin Assignment
#define IMMR_PIO_PCSO               0x0964              // Port C Special Options
#define IMMR_PIO_PCDAT              0x0966              // Port C Data Register
#define IMMR_PIO_PCINT              0x0968              // Port C Interrupt Cntrl
#define IMMR_PIO_RSVD_2             0x096a              // Reserved (6 bytes)
#define IMMR_PIO_PDDIR              0x0970              // Port D Data Direction 
#define IMMR_PIO_PDPAR              0x0972              // Port D Pin Assignment
#define IMMR_PIO_RSVD_3             0x0974              // Reserved (2 bytes)
#define IMMR_PIO_PDDAT              0x0976              // Port D Data Register
#define IMMR_PIO_RSVD_4             0x0978              // Reserved (8 bytes)


/*
 *  TIMR - CPM Timers
 */

#define IMMR_TIMR_BASE              0x0980


/*
 *  CP - Communications Processor
 */

#define IMMR_CP_CPCR                0x09c0              // CP Command Register
#define IMMR_CP_RSVD_1              0x09c2              // Reserved (2 bytes)
#define IMMR_CP_RCCR                0x09c4              // RISC Configuration Reg
#define IMMR_CP_RSVD2               0x09c6              // Reserved (3 bytes)
#define IMMR_CP_RCTR1               0x09cc              // RISC Ctrl Trap Reg 1
#define IMMR_CP_RCTR2               0x09ce              // RISC Ctrl Trap Reg 2
#define IMMR_CP_RCTR3               0x09d0              // RISC Ctrl Trap Reg 3
#define IMMR_CP_RCTR4               0x09d2              // RISC Ctrl Trap Reg 4
#define IMMR_CP_RSVD_3              0x09d4              // Reserved (2 bytes)
#define IMMR_CP_RTER                0x09d6              // RISC Timers Event Reg
#define IMMR_CP_RSVD_4              0x09d8              // Reserved (2 bytes)
#define IMMR_CP_RTMR                0x09da              // RISC Timers Mask Reg
#define IMMR_CP_RSVD_5              0x09dc              // Reserved (20 bytes)


/*
 *  BRG - Baud Rate Generators
 */

#define IMMR_BRG_BRGC1              0x09f0              // BRG1 Configuration
#define IMMR_BRG_BRGC2              0x09f4              // BRG2 Configuration
#define IMMR_BRG_BRGC3              0x09f8              // BRG3 Configuration
#define IMMR_BRG_BRGC4              0x09fc              // BRG4 Configuration


/*
 *  SCC - Serial Communication Controllers
 */

#define IMMR_SCC_GSMR_L1            0x0a00              // General Mode Register
#define IMMR_SCC_GSMR_H1            0x0a04              // General Mode Register
#define IMMR_SCC_PSMR1              0x0a08              // Protocol Specific Mode
#define IMMR_SCC_RSVD_1             0x0a0a              // Reserved (2 bytes)
#define IMMR_SCC_TODR1              0x0a0c              // Transmit-on-demand reg
#define IMMR_SCC_DSR1               0x0a0e              // Data Synch Register
#define IMMR_SCC_SCCE1              0x0a10              // SCC Event Register
#define IMMR_SCC_RSVD_2             0x0a12              // Reserved (2 bytes)
#define IMMR_SCC_SCCM1              0x0a14              // SCC Mask Register
#define IMMR_SCC_RSVD_3             0x0a16              // Reserved (1 byte)
#define IMMR_SCC_SCCS1              0x0a17              // SCC Status Register
#define IMMR_SCC_RSVD_4             0x0a18              // Reserved (8 bytes)

#define IMMR_SCC_GSMR_L2            0x0a20              // General Mode Register
#define IMMR_SCC_GSMR_H2            0x0a24              // General Mode Register
#define IMMR_SCC_PSMR2              0x0a28              // Protocol Specific Mode
#define IMMR_SCC_RSVD_5             0x0a2a              // Reserved (2 bytes)
#define IMMR_SCC_TODR2              0x0a2c              // Transmit-on-demand reg
#define IMMR_SCC_DSR2               0x0a2e              // Data Synch Register
#define IMMR_SCC_SCCE2              0x0a30              // SCC Event Register
#define IMMR_SCC_RSVD_6             0x0a32              // Reserved (2 bytes)
#define IMMR_SCC_SCCM2              0x0a34              // SCC Mask Register
#define IMMR_SCC_RSVD_7             0x0a36              // Reserved (1 byte)
#define IMMR_SCC_SCCS2              0x0a37              // SCC Status Register
#define IMMR_SCC_RSVD_8             0x0a38              // Reserved (8 bytes)


/*
 *  SCC3 - Serial Communication Controller
 */



/*
 *  SCC4 - Serial Communication Controller
 */



/*
 *  SMC - Serial Management Controllers
 */

#define IMMR_SMC1_SMCMR             0x0a82              // SMC Mode Register
#define IMMR_SMC1_RSVD_1            0x0a84
#define IMMR_SMC1_SMCE              0x0a86              // SMC or PIP Event Reg
#define IMMR_SMC1_RSVD_2            0x0a87
#define IMMR_SMC1_SMCM              0x0a8a              // SMC Mask Register
#define IMMR_SMC1_RSVD_3            0x0a8b

#define IMMR_SMC2_SMCMR             0x0a92              // SMC Mode Register
#define IMMR_SMC2_RSVD_1            0x0a94
#define IMMR_SMC2_SMCE              0x0a96              // SMC or PIP Event Reg
#define IMMR_SMC2_RSVD_2            0x0a97
#define IMMR_SMC2_SMCM              0x0a9a              // SMC Mask Register
#define IMMR_SMC2_RSVD_3            0x0a9b


/*
 *  SPI - Serial Peripheral Interface
 */

#define IMMR_SPI_BASE               0x0aa0


/*
 *  PIP - Parallel Interface Port
 */

#define IMMR_PIP_PIPC               0x0ab2              // PIP Configuration Reg
#define IMMR_PIP_RSVD_1             0x0ab4              // Unused (2 bytes)
#define IMMR_PIP_PTPR               0x0ab6              // PIP Timing Parameters
#define IMMR_PIP_PBDIR              0x0ab8              // Port B Data Direction Reg
#define IMMR_PIP_PBPAR              0x0abc              // Port B Pin Assignment
#define IMMR_PIP_RSVD_2             0x0ac0              // Unused (2 bytes)
#define IMMR_PIP_PBODR              0x0ac2              // Port B Open Drain Reg
#define IMMR_PIP_PBDAT              0x0ac4              // Port B Data Register
#define IMMR_PIP_RSVD4              0x0ac8              // Reserved (24 bytes)


/*
 *  SI - Serial Interface
 */

#define IMMR_SI_SIMODE              0x0ae0              // SI Mode Register
#define IMMR_SI_SIGMR               0x0ae4              // SI Global Mode Register
#define IMMR_SI_RSVD_1              0x0ae5              // Reserved (1 byte)
#define IMMR_SI_SISTR               0x0ae6              // SI Status Register
#define IMMR_SI_SICMR               0x0ae7              // SI Command Register
#define IMMR_SI_RSVD_2              0x0ae8              // Reserved (4 bytes)
#define IMMR_SI_SICR                0x0aec              // SI Clock Route
#define IMMR_SI_SIRP                0x0af0              // SI Ram Pointers
#define IMMR_SI_RSVD_3              0x0af4              // Reserved (12 bytes)


/*
 *  SIRAM - SI Routine RAM
 */

#define IMMR_SIRAM_BASE             0x0c00


/*
 *  FEC - Fast Ethernet Controller (only on MPC860T)
 */

#define IMMR_FEC_ADDR_LOW           0x0e00              // Ethernet address - lower bytes
#define IMMR_FEC_ADDR_HIGH          0x0e04              // Ethernet address - upper bytes
#define IMMR_FEC_HASH_TABLE_HIGH    0x0e08              // Hash table - upper 32-bits
#define IMMR_FEC_HASH_TABLE_LOW     0x0e0C              // Hash table - lower 32-bits
#define IMMR_FEC_R_DES_START        0x0e10              // Rx Buffer Descriptors base address
#define IMMR_FEC_X_DES_START        0x0e14              // Tx Buffer Descriptors base address
#define IMMR_FEC_R_BUFF_SIZE        0x0e18              // Rx Buffer Size
#define IMMR_FEC_ECNTRL             0x0e40              // Ethernet Control
#define IMMR_FEC_IEVENT             0x0e44              // FEC Interrupt Events
#define IMMR_FEC_IMASK              0x0e48              // FEC Interrupt Mask
#define IMMR_FEC_IVEC               0x0e4C              // FEC Interrupt Vector
#define IMMR_FEC_R_DES_ACTIVE       0x0e50              // Rx Ring updated flag
#define IMMR_FEC_X_DES_ACTIVE       0x0e54              // Tx Ring updated flag
#define IMMR_FEC_MII_DATA           0x0e80              // MII Data
#define IMMR_FEC_MII_SPEED          0x0e84              // MII Speed
#define IMMR_FEC_R_BOUND            0x0ecc              // End of FIFO RAM
#define IMMR_FEC_R_FSTART           0x0ed0              // FEC Rx FIFO base address
#define IMMR_FEC_X_WMRK             0x0ee4              // FEC Tx FIFO Watermark
#define IMMR_FEC_X_FSTART           0x0eec              // FEC Tx FIFO base address
#define IMMR_FEC_FUN_CODE           0x0f34              // DMA Function Code
#define IMMR_FEC_R_CNTRL            0x0f44              // FEC Rx Control
#define IMMR_FEC_R_HASH             0x0f48              // Rx Hash Register
#define IMMR_FEC_X_CNTRL            0x0f84              // FEC Tx Control


/*
 *  DPRAM - Dual Port RAM
 */

#define IMMR_DRAM_BASE              0x2000


/*
 *  SCC1 Parameter RAM
 */

#define IMMR_SCC1_PARAM_RBASE       0x3c00              // Receive BD Table base
#define IMMR_SCC1_PARAM_TBASE       0x3c02              // Transmit BD Table base
#define IMMR_SCC1_PARAM_RFCR        0x3c04              // Receive Function Code Register
#define IMMR_SCC1_PARAM_TFCR        0x3c05              // Transmit Function Code Register
#define IMMR_SCC1_PARAM_MRBLR       0x3c06              // Maximum Receive Buffer Length
#define IMMR_SCC1_PARAM_RBPTR       0x3c10              // Current CPM internal Rx BD pointer
#define IMMR_SCC1_PARAM_TBPTR       0x3c20              // Current CPM internal Tx BD pointer


/*
 *  SCC1 UART Mode-Specific Paramter RAM
 */

#define IMMR_SCC1_UART_MAX_IDL      0x3c38              // Max Idle characters
#define IMMR_SCC1_UART_IDLC         0x3c3a              // Temporary Idle counter
#define IMMR_SCC1_UART_BRKCR        0x3c3c              // Break Count register
#define IMMR_SCC1_UART_PAREC        0x3c3e              // Parity Error count
#define IMMR_SCC1_UART_FRMEC        0x3c40              // Frame Error count
#define IMMR_SCC1_UART_NOSEC        0x3c42              // Noise Error count
#define IMMR_SCC1_UART_BRKEC        0x3c44              // Break condition count
#define IMMR_SCC1_UART_BRKLN        0x3c46              // Last Break received length
#define IMMR_SCC1_UART_UADDR1       0x3c48              // UART address character 1
#define IMMR_SCC1_UART_UADDR2       0x3c4a              // UART address character 2
#define IMMR_SCC1_UART_RTEMP        0x3c4c              // Temporary Storage
#define IMMR_SCC1_UART_TOSEQ        0x3c4e              // Transmit Out-of-Sequence character
#define IMMR_SCC1_UART_CHAR1        0x3c50              // Control Character 1
#define IMMR_SCC1_UART_CHAR2        0x3c52              // Control Character 2
#define IMMR_SCC1_UART_CHAR3        0x3c54              // Control Character 3
#define IMMR_SCC1_UART_CHAR4        0x3c56              // Control Character 4
#define IMMR_SCC1_UART_CHAR5        0x3c58              // Control Character 5
#define IMMR_SCC1_UART_CHAR6        0x3c5a              // Control Character 6
#define IMMR_SCC1_UART_CHAR7        0x3c5c              // Control Character 7
#define IMMR_SCC1_UART_CHAR8        0x3c5e              // Control Character 8
#define IMMR_SCC1_UART_RCCM         0x3c60              // Receive Control Character Mask
#define IMMR_SCC1_UART_RCCR         0x3c62              // Receive Control Character register
#define IMMR_SCC1_UART_RLBC         0x3c64              // Receive last break character


/*
 *  SCC2 Parameter RAM
 */

#define IMMR_SCC2_PARAM_RBASE       0x3d00              // Receive BD Table base
#define IMMR_SCC2_PARAM_TBASE       0x3d02              // Transmit BD Table base
#define IMMR_SCC2_PARAM_RFCR        0x3d04              // Receive Function Code Register
#define IMMR_SCC2_PARAM_TFCR        0x3d05              // Transmit Function Code Register
#define IMMR_SCC2_PARAM_MRBLR       0x3d06              // Maximum Receive Buffer Length
#define IMMR_SCC2_PARAM_RBPTR       0x3c10              // Current CPM internal Rx BD pointer
#define IMMR_SCC2_PARAM_TBPTR       0x3c20              // Current CPM internal Tx BD pointer


/*
 *  SCC2 UART Mode-Specific Paramter RAM
 */

#define IMMR_SCC2_UART_MAX_IDL      0x3d38              // Max Idle characters
#define IMMR_SCC2_UART_IDLC         0x3d3a              // Temporary Idle counter
#define IMMR_SCC2_UART_BRKCR        0x3d3c              // Break Count register
#define IMMR_SCC2_UART_PAREC        0x3d3e              // Parity Error count
#define IMMR_SCC2_UART_FRMEC        0x3d40              // Frame Error count
#define IMMR_SCC2_UART_NOSEC        0x3d42              // Noise Error count
#define IMMR_SCC2_UART_BRKEC        0x3d44              // Break condition count
#define IMMR_SCC2_UART_BRKLN        0x3d46              // Last Break received length
#define IMMR_SCC2_UART_UADDR1       0x3d48              // UART address character 1
#define IMMR_SCC2_UART_UADDR2       0x3d4a              // UART address character 2
#define IMMR_SCC2_UART_RTEMP        0x3d4c              // Temporary Storage
#define IMMR_SCC2_UART_TOSEQ        0x3d4e              // Transmit Out-of-Sequence character
#define IMMR_SCC2_UART_CHAR1        0x3d50              // Control Character 1
#define IMMR_SCC2_UART_CHAR2        0x3d52              // Control Character 2
#define IMMR_SCC2_UART_CHAR3        0x3d54              // Control Character 3
#define IMMR_SCC2_UART_CHAR4        0x3d56              // Control Character 4
#define IMMR_SCC2_UART_CHAR5        0x3d58              // Control Character 5
#define IMMR_SCC2_UART_CHAR6        0x3d5a              // Control Character 6
#define IMMR_SCC2_UART_CHAR7        0x3d5c              // Control Character 7
#define IMMR_SCC2_UART_CHAR8        0x3d5e              // Control Character 8
#define IMMR_SCC2_UART_RCCM         0x3d60              // Receive Control Character Mask
#define IMMR_SCC2_UART_RCCR         0x3d62              // Receive Control Character register
#define IMMR_SCC2_UART_RLBC         0x3d64              // Receive last break character


/*
 *  Constants used in SCC configuration
 */

#define SCC_RX_EMPTY                BE_U16_BIT0
#define SCC_RX_WRAP                 BE_U16_BIT2
#define SCC_RX_INTERRUPT            BE_U16_BIT3
#define SCC_RX_CONTROL              BE_U16_BIT4
#define SCC_RX_ADDRESS              BE_U16_BIT5
#define SCC_RX_CONTINUOUS           BE_U16_BIT6
#define SCC_RX_IDLE_CLOSE           BE_U16_BIT7
#define SCC_RX_MATCH_ADDRESS        BE_U16_BIT8
#define SCC_RX_BREAK                BE_U16_BIT10
#define SCC_RX_FRAMING              BE_U16_BIT11
#define SCC_RX_PARITY               BE_U16_BIT12
#define SCC_RX_OVERRUN              BE_U16_BIT14
#define SCC_RX_LOST_CD              BE_U16_BIT15

#define SCC_TX_READY                BE_U16_BIT0
#define SCC_TX_WRAP                 BE_U16_BIT2
#define SCC_TX_INTERRUPT            BE_U16_BIT3
#define SCC_TX_CLEAR_REPORT         BE_U16_BIT4
#define SCC_TX_ADDRESS              BE_U16_BIT5
#define SCC_TX_CONTINUOUS           BE_U16_BIT6
#define SCC_TX_PREAMBLE             BE_U16_BIT7
#define SCC_TX_NO_STOP_BIT          BE_U16_BIT8
#define SCC_TX_LOST_CTS             BE_U16_BIT15


/*
 *  SCC UART event mask bits and event bits
 */

#define SCC_EVENT_TX                BE_U16_BIT14
#define SCC_EVENT_RX                BE_U16_BIT15


/*
 *  Constants used in FEC configuration
 */

#define FEC_RX_EMPTY                BE_U16_BIT0
#define FEC_RX_WRAP                 BE_U16_BIT2
#define FEC_RX_LAST                 BE_U16_BIT4
#define FEC_RX_MISS                 BE_U16_BIT7
#define FEC_RX_BROADCAST            BE_U16_BIT8
#define FEC_RX_MULTICAST            BE_U16_BIT9
#define FEC_RX_ERR_LEN              BE_U16_BIT10
#define FEC_RX_ERR_ALIGNMENT        BE_U16_BIT11
#define FEC_RX_ERR_SHORT            BE_U16_BIT12
#define FEC_RX_ERR_CRC              BE_U16_BIT13
#define FEC_RX_ERR_OVERRUN          BE_U16_BIT14
#define FEC_RX_ERR_TRUNCATE         BE_U16_BIT15

#define FEC_TX_READY                BE_U16_BIT0
#define FEC_TX_WRAP                 BE_U16_BIT2
#define FEC_TX_LAST                 BE_U16_BIT4
#define FEC_TX_TRANSMIT_CRC         BE_U16_BIT5
#define FEC_TX_DEFER                BE_U16_BIT6
#define FEC_TX_ERR_HEARTBEAT        BE_U16_BIT7
#define FEC_TX_ERR_LATE_COLLISION   BE_U16_BIT8
#define FEC_TX_ERR_RETRANS_LIMIT    BE_U16_BIT9
#define FEC_TX_ERR_UNDERRUN         BE_U16_BIT14
#define FEC_TX_ERR_LOST_CARRIER     BE_U16_BIT15


/*
 *  Constants for Cache Commands
 */

#define CacheCmdReserved_1          0x0000
#define CacheCmdSetWriteThrough     0x0100
#define CacheCmdEnable              0x0200
#define CacheCmdClearWriteThrough   0x0300
#define CacheCmdDisable             0x0400
#define CacheCmdSetLE               0x0500
#define CacheCmdLoadAndLock         0x0600
#define CacheCmdClearLE             0x0700
#define CacheCmdUnlockBlock         0x0800
#define CacheCmdReserved_2          0x0900
#define CacheCmdUnlockAll           0x0a00
#define CacheCmdReserved_3          0x0b00
#define CacheCmdInvAll              0x0c00
#define CacheCmdReserved_4          0x0d00
#define CacheCmdFlushBlock          0x0e00
#define CacheCmdReserved_5          0x0f00



/*
 *  SCC Buffer Descriptor structure
 */

typedef struct _SCC_BD
{
    volatile U16 Status;          // SCC receive or transmit status
    volatile U16 Length;          // Data Length
    volatile U32 DataBuffer;      // Data buffer pointer
} SCC_BD;


/*
 *  FEC Buffer Descriptor structure
 */

typedef SCC_BD      FEC_BD;


/*
 *  IDMA Buffer Descriptor structure
 */

typedef struct _IDMA_BD
{
    volatile U16  Status;         // Buffer Descriptor Status
    volatile U8   DestFx;         // Destination Function Code Register
    volatile U8   SourceFx;       // Source Function Code Register
    volatile U32  Length;         // Data Length
    volatile U32  SourceBuffer;   // Source Data Buffer Pointer
    volatile U32  DestBuffer;     // Destination Data Buffer Pointer
} IDMA_BD;




#endif
