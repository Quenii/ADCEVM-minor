#ifndef __BEM_H
#define __BEM_H

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
 *      Bem.h
 *
 * Description:
 *
 *      Defines the interface routines for the Back End Monitor. This 
 *      header file is used by Local and Host applications (i.e. PLXMon).
 *
 * Revision:
 *
 *      02-01-06 : PCI SDK v4.40
 *
 ******************************************************************************/


#include "PlxTypes.h"

#if defined(PLX_IOP_CODE)
    #include "PlxQueue.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif




/**************************************************************************
 * BEM Request Message Packet:
 *
 *   _____________________________________________________________________
 *  |    2 Bytes    |  1 Byte  |   ... Extra Bytes ...     |    1 Byte    |
 *  |---------------|----------|---------------------------|--------------|
 *  |  Header (~p)  | BEM CMD  |  Command-Specific Info    | End MSG <CR> |
 *  |_______________|__________|___________________________|______________|
 *
 *
 * BEM Reply Message Packet:
 *
 *   __________________________________________________________
 *  |    1 Byte     |   ... Extra Bytes ...     |    1 Byte    |
 *  |---------------|---------------------------|--------------|
 *  |  Header (p)   |  Data or status returned  | End MSG <CR> |
 *  |_______________|___________________________|______________|
 *
 *************************************************************************/


// BEM message headers
#define BEM_MSG_SEND_HEADER     "~p"
#define BEM_MSG_SEND_HEADER_0   '~'
#define BEM_MSG_SEND_HEADER_1   'p'
#define BEM_MSG_REPLY_HEADER    "\x1"
#define BEM_MSG_END_COMMAND     '\r'
#define BEM_END_COMMAND         BEM_MSG_END_COMMAND

// BEM Message Status
#define BEM_REPLY_SUCCESS       '!'
#define BEM_REPLY_ERROR         '@'

// BEM Command
#define BEM_RESET_CPU           '!'         // Reset the Local CPU
#define BEM_HOST_INQUIRY        '@'         // Host queries BEM Info

// BEM Read Commands
#define BEM_READ_BIT_8          'g'
#define BEM_READ_BIT_16         'h'
#define BEM_READ_BIT_32         'i'
#define BEM_READ_BIT_64         'j'
#define BEM_EEPROM_READ         'k'
#define BEM_EEP_READ_BY_OFFSET  'q'
#define BEM_FLASH_READ          'l'
#define BEM_BLOCK_READ_BIT_8    'm'
#define BEM_BLOCK_READ_BIT_16   'n'
#define BEM_BLOCK_READ_BIT_32   'o'
#define BEM_BLOCK_READ_BIT_64   'p'

// BEM Write Commands
#define BEM_WRITE_BIT_8         'G'
#define BEM_WRITE_BIT_16        'H'
#define BEM_WRITE_BIT_32        'I'
#define BEM_WRITE_BIT_64        'J'
#define BEM_EEPROM_WRITE        'K'
#define BEM_EEP_WRITE_BY_OFFSET 'Q'
#define BEM_FLASH_WRITE         'L'
#define BEM_BLOCK_WRITE_BIT_8   'M'
#define BEM_BLOCK_WRITE_BIT_16  'N'
#define BEM_BLOCK_WRITE_BIT_32  'O'
#define BEM_BLOCK_WRITE_BIT_64  'P'



typedef struct _PLATFORM_PARAMS
{
    U32 Version;                // BEM Version & Platform type
    U32 PlxAddressLow;          // Lower 32-bits of PLX Chip base address
    U32 PlxAddressHigh;         // Upper 32-bits of PLX Chip base address
    U16 PlxChipType;            // PLX Chip Type
    U16 Capability;             // Board Capabilities
    U8  EEPROMType;             // EEPROM type
    U8  FlashType;              // FLASH type
    U16 Reserved;               // Space for future use
    U32 FlashAddressLow;        // Lower 32-bits of FLASH base address
    U32 FlashAddressHigh;       // Upper 32-bits of FLASH base address
    U32 BufferAddressLow;       // Permanent buffer for EEPROM programming
    U32 BufferAddressHigh;
    U32 BufferSize;             // Permanent Buffer size
    U32 FlashBufferAddressLow;  // Temp. Buffer for FLASH programming
    U32 FlashBufferAddressHigh;
    U32 FlashBufferSize;        // Temp. FLASH buffer size
} PLATFORM_PARAMS, * PPLATFORM_PARAMS;


#if defined(PLX_IOP_CODE)           // The following is used only by Local code

typedef struct _BEM_INIT_PARAMS
{
    U8  Major;                      // Local API Major Version
    U8  Minor;                      // Local API Minor Version
    U8  Revision;                   // Local API Revision Number
    U8  Reserved;                   // Reserved for future use
    U8  FlashProgrammingSupported;  // 0 = Not Supported,  1 = Supported
    U8  EEPROMProgrammingSupported; // 0 = Not Supported,  1 = Supported
    U16 PlxChipType;                // PLX Chip type
    U32 PlxAddress;                 // Local bus address of PLX config. registers
    U32 FlashAddress;               // Local bus address of FLASH
    U32 FlashBufferAddress;         // Local bus address of temp FLASH buffer
    U32 FlashBufferSize;            // Temporary FLASH buffer size
} BEM_INIT_PARAMS;




/**********************************************
*               Functions
**********************************************/
BOOLEAN
BemInitialize(
    BEM_INIT_PARAMS *pBemParams
    );

void
BemMessageProcessingEnable(
    void
    );

void
BemMessageProcessingDisable(
    void
    );

void
BemCheckInput(
    U8         data,
    PLX_QUEUE *IoQueue
    );

#endif   // PLX_IOP_CODE



#ifdef __cplusplus
}
#endif

#endif
