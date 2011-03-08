#ifndef __LOCALAPI_H
#define __LOCALAPI_H

/*******************************************************************************
 * Copyright (c) 2006 PLX Technology, Inc.
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
 *      LocalApi.h
 *
 * Description:
 *
 *      Local API functions declarations
 *
 * Revision:
 *
 *      02-01-06 : PCI SDK v4.40
 *
 ******************************************************************************/


#include "PlxTypes.h"


#ifdef __cplusplus
extern "C" {
#endif




/******************************************
* Miscellaneous Functions
******************************************/
RETURN_CODE
PlxSdkVersion(
    U8 *VersionMajor,
    U8 *VersionMinor,
    U8 *VersionRevision
    );

VOID
PlxChipTypeGet(
    BUS_INDEX  busIndex,
    U32       *pChipType,
    U8        *pRevision
    );

U32
PlxChipBaseAddressGet(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

VOID
PlxVerifyEndianAccess(
    BUS_INDEX busIndex
    );


/******************************************
* Initialization Functions
******************************************/
RETURN_CODE
PlxInitApi(
    API_PARMS *ApiParms
    );

RETURN_CODE
PlxInitPciBusProperties(
    BUS_INDEX     busIndex,
    PCI_BUS_PROP *PciBusProp
    );

RETURN_CODE
PlxInitPciSpace(
    BUS_INDEX busIndex,
    PCI_SPACE PciSpace,
    U32       PciWindowBase,
    U32       size
    );

RETURN_CODE
PlxInitIopBusProperties(
    BUS_INDEX     busIndex,
    IOP_SPACE     IopSpace,
    IOP_BUS_PROP *IopBusProp
    );

RETURN_CODE
PlxInitIopArbitration(
    BUS_INDEX       busIndex,
    IOP_ARBIT_DESC *ArbDesc
    );

RETURN_CODE
PlxInitLocalSpace(
    BUS_INDEX busIndex,
    IOP_SPACE IopSpace,
    U32       LocalBase,
    U32       size
    );

RETURN_CODE
PlxInitIopEndian(
    BUS_INDEX        busIndex,
    IOP_ENDIAN_DESC *IopEndianDesc
    );

RETURN_CODE
PlxInitPowerManagement(
    BUS_INDEX  busIndex,
    PM_PROP   *PmProp
    );

RETURN_CODE
PlxInitVPDAddress(
    BUS_INDEX busIndex,
    U32       VpdBaseAddress
    );

RETURN_CODE
PlxInitDone(
    BUS_INDEX busIndex
    );


/******************************************
* Register Access Functions
******************************************/
RETURN_CODE
PlxPciConfigRegisterRead(
    U8   bus,
    U8   slot,
    U16  offset,
    U32 *pValue
    );

RETURN_CODE
PlxPciConfigRegisterWrite(
    U8   bus,
    U8   slot,
    U16  offset,
    U32 *pValue
    );

U32
PlxRegisterRead(
    BUS_INDEX    busIndex,
    U16          offset,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxRegisterWrite(
    BUS_INDEX busIndex,
    U16       offset,
    U32       value
    );

U32
PlxRegisterMailboxRead(
    BUS_INDEX    busIndex,
    MAILBOX_ID   MailboxId,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxRegisterMailboxWrite(
    BUS_INDEX  busIndex,
    MAILBOX_ID MailboxId,
    U32        value
    );

U32
PlxRegisterDoorbellRead(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxRegisterDoorbellSet(
    BUS_INDEX busIndex,
    U32       value
    );


/******************************************
* Interrupt Support Functions
******************************************/
RETURN_CODE
PlxIntrEnable(
    BUS_INDEX  busIndex,
    PLX_INTR  *pPlxIntr
    );

RETURN_CODE
PlxIntrDisable(
    BUS_INDEX  busIndex,
    PLX_INTR  *pPlxIntr
    );

BOOLEAN
PlxIntrStatusGet(
    BUS_INDEX    busIndex,
    PLX_INTR    *pPlxIntr,
    RETURN_CODE *rc
    );


/******************************************
* PCI Memory Access Functions
******************************************/
RETURN_CODE
PlxBusPciRead(
    BUS_INDEX    busIndex,
    PCI_SPACE    PciSpace,
    U32          PciAddress,
    VOID        *pBuffer,
    U32          ByteCount,
    ACCESS_TYPE  AccessType
    );

RETURN_CODE
PlxBusPciWrite(
    BUS_INDEX    busIndex,
    PCI_SPACE    PciSpace,
    U32          PciAddress,
    VOID        *pBuffer,
    U32          ByteCount,
    ACCESS_TYPE  AccessType
    );


/******************************************
* Serial EEPROM Access Functions
******************************************/
BOOLEAN
PlxSerialEepromPresent(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxSerialEepromReadByOffset(
    BUS_INDEX  busIndex,
    U16        offset,
    U32       *pValue
    );

RETURN_CODE
PlxSerialEepromWriteByOffset(
    BUS_INDEX busIndex,
    U16       offset,
    U32       value
    );


/******************************************
* DMA Functions
******************************************/
void
PlxDmaIsr(
    DMA_CHANNEL channel
    );

RETURN_CODE
PlxDmaControl(
    DMA_CHANNEL channel,
    DMA_COMMAND DmaCommand
    );

RETURN_CODE
PlxDmaStatus(
    DMA_CHANNEL channel
    );


/******************************************
* Block DMA Functions
******************************************/
RETURN_CODE
PlxDmaBlockChannelOpen(
    DMA_CHANNEL       channel,
    DMA_CHANNEL_DESC *pDesc
    );

RETURN_CODE
PlxDmaBlockTransfer(
    DMA_CHANNEL           channel,
    DMA_TRANSFER_ELEMENT *pDmaData,
    BOOLEAN               ReturnImmediate
    );

RETURN_CODE
PlxDmaBlockChannelClose(
    DMA_CHANNEL channel
    );


/******************************************
* Messaging Unit Functions
******************************************/
RETURN_CODE
PlxMuInit(
    BUS_INDEX busIndex,
    U32       FifoSize,
    U32       LocalAddr
    );

RETURN_CODE
PlxMuInboundPortRead(
    BUS_INDEX  busIndex,
    U32       *pFrame
    );

RETURN_CODE
PlxMuInboundPortWrite(
    BUS_INDEX  busIndex,
    U32       *pFrame
    );

RETURN_CODE
PlxMuOutboundPortRead(
    BUS_INDEX  busIndex,
    U32       *pFrame
    );

RETURN_CODE
PlxMuOutboundPortWrite(
    BUS_INDEX  busIndex,
    U32       *pFrame
    );


/******************************************
* Power Management Functions
******************************************/
BOOLEAN
PlxIsPowerLevelSupported(
    BUS_INDEX       busIndex,
    PLX_POWER_LEVEL PowerLevel
    );

PLX_POWER_LEVEL
PlxPowerLevelGet(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxPowerLevelSet(
    BUS_INDEX       busIndex,
    PLX_POWER_LEVEL PowerLevel
    );


/******************************************
* New Capabilities Functions
******************************************/
BOOLEAN
PlxIsNewCapabilityEnabled(
    BUS_INDEX busIndex,
    U8        CapabilityToVerify
    );


/******************************************
* Hot Swap Functions
******************************************/
U8
PlxHotSwapNcpRead(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxHotSwapNcpWrite(
    BUS_INDEX busIndex,
    U8        value
    );

U8
PlxHotSwapStatus(
    BUS_INDEX busIndex
    );

RETURN_CODE
PlxHotSwapEnable(
    BUS_INDEX busIndex
    );

RETURN_CODE
PlxHotSwapDisable(
    BUS_INDEX busIndex
    );


/******************************************
* VPD Functions
******************************************/
U8
PlxVpdNcpRead(
    BUS_INDEX    busIndex,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxVpdNcpWrite(
    BUS_INDEX busIndex,
    U8        value
    );

U32
PlxVpdRead(
    BUS_INDEX    busIndex,
    U16          offset,
    RETURN_CODE *rc
    );

RETURN_CODE
PlxVpdWrite(
    BUS_INDEX busIndex,
    U16       offset,
    U32       value
    );

RETURN_CODE
PlxVpdEnable(
    BUS_INDEX busIndex
    );

RETURN_CODE
PlxVpdDisable(
    BUS_INDEX busIndex
    );




#ifdef __cplusplus
}
#endif

#endif
