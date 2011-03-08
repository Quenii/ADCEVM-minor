#ifndef __PCIREGS_H
#define __PCIREGS_H

/*******************************************************************************
 * Copyright (c) 2005 PLX Technology, Inc.
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

/******************************************************************************
 *
 * File Name:
 *
 *      PciRegs.h
 *
 * Description:
 *
 *      This file defines the generic PCI Configuration Registers
 *
 * Revision:
 *
 *      06-01-05 : PCI SDK v4.40
 *
 ******************************************************************************/


// PCI offsets for Type 0 Header
#define CFG_VENDOR_ID           0x000
#define CFG_COMMAND             0x004
#define CFG_REV_ID              0x008
#define CFG_CACHE_SIZE          0x00C
#define CFG_BAR0                0x010
#define CFG_BAR1                0x014
#define CFG_BAR2                0x018
#define CFG_BAR3                0x01C
#define CFG_BAR4                0x020
#define CFG_BAR5                0x024
#define CFG_CIS_PTR             0x028
#define CFG_SUB_VENDOR_ID       0x02C
#define CFG_EXP_ROM_BASE        0x030
#define CFG_CAP_PTR             0x034
#define CFG_RESERVED1           0x038
#define CFG_INT_LINE            0x03C


// PCI Extended Capability IDs
#define CAP_ID_POWER_MAN        0x01
#define CAP_ID_AGP              0x02
#define CAP_ID_VPD              0x03
#define CAP_ID_SLOT_ID          0x04
#define CAP_ID_MSI              0x05
#define CAP_ID_HOT_SWAP         0x06
#define CAP_ID_PCIX             0x07
#define CAP_ID_HYPER_TRANSPORT  0x08
#define CAP_ID_VENDOR_SPECIFIC  0x09
#define CAP_ID_DEBUG_PORT       0x0A
#define CAP_ID_RESOURCE_CTRL    0x0B
#define CAP_ID_HOT_PLUG         0x0C
#define CAP_ID_BRIDGE_SUB_ID    0x0D
#define CAP_ID_AGP_8X           0x0E
#define CAP_ID_SECURE_DEVICE    0x0F
#define CAP_ID_PCI_EXPRESS      0x10
#define CAP_ID_MSI_X            0x11


// PCI Express Extended Capability IDs
#define PCIE_CAP_ID_ERROR_REPORTING         0x001
#define PCIE_CAP_ID_VIRTUAL_CHANNEL         0x002
#define PCIE_CAP_ID_DEV_SERIAL_NUMBER       0x003
#define PCIE_CAP_ID_POWER_BUDGETING         0x004
#define PCIE_CAP_ID_RC_LINK_DECLARATION     0x005
#define PCIE_CAP_ID_RC_INT_LINK_CONTROL     0x006
#define PCIE_CAP_ID_RC_EVENT_COLLECTOR      0x007
#define PCIE_CAP_ID_MF_VIRTUAL_CHANNEL      0x008
#define PCIE_CAP_ID_VC_WITH_MULTI_FN        0x009
#define PCIE_CAP_ID_RC_REG_BLOCK_HEADER     0x00A
#define PCIE_CAP_ID_VENDOR_SPECIFIC         0x00B



#endif
