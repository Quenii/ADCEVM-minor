#ifndef __PLX_PROTOCOL_H
#define __PLX_PROTOCOL_H

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

/******************************************************************************
 *
 * File Name:
 *
 *      PlxProtocol.h
 *
 * Description:
 *
 *      This header file contains the constants and function prototypes
 *      for on-board programming of FLASH memory, query of on-board EEPROM
 *      type and downloading of RAM applications.
 *
 * Revision:
 *
 *      09-31-01 : PCI SDK v3.40
 *
 ******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif



/*
    The FLASH re-programming protocol used by PLX RDKs is as follows:

    If a host application wants to PROGRAM the FLASH, the
    application should follow the steps below:
      1) Determine if the IOP supports FLASH programming by writing
         HOST_QUERY_FLASH_SUPPORT to mailbox 5.
      2) Generate a local interrupt by writing to PCI-to-Local doorbell register
         with FLASH_WRITE.
      3) Wait until the doorbell register is cleared.  When it is cleared, check
         if mailbox 5 contains IOP_SUPPORTS_FLASH.  mailbox 6 will contain
         the base address of the temporary window to store the binary image at.
         The host application should timeout if the doorbell register is not
         cleared within a reasonable amount of time.
      4) Copy the binary image to DRAM using Direct Slave accesses to the
         address obtained in step 3.
      5) Write to mailbox 5 with the FLASH offset that you wish to start
         programming at.
      6) Write to mailbox 6 with the size.
      7) Write to mailbox 7 with the FLASH type if multiple types of FLASH are
         supported by IOP. The FLASH type is optional.
      8) Write to PCI-to-Local doorbell register with FLASH_WRITE. This will
         program the FLASH with the binary image located at the temporary
         storage location.
      9) Wait until mailbox 6 is set to FLASH_DONE. mailbox 5 will contain an
         error code.

    If a host application wants to READ the FLASH, the
    application should follow the steps below:
      1) Determine if the IOP supports FLASH programming by writing
         HOST_QUERY_FLASH_SUPPORT to mailbox 5.
      2) Generate a local interrupt by writing to PCI-to-Local doorbell register
         with FLASH_READ.
      3) Wait until the doorebell register is cleared.  When it is cleared check
         if mailbox 5 contains IOP_SUPPORTS_FLASH.  mailbox 6 will contain
         the base address of the temporary window to store the binary image at.
         The host application should timeout if the doorbell register is not
         cleared within a reasonable amount of time.
      4) Write to mailbox 5 with the FLASH offset that you wish to start
         reading from.
      5) Write to mailbox 6 with the size.
      6) Write to PCI-to-Local doorbell register with FLASH_READ. This will
         read the FLASH into the temporary storage location.
      7) Wait until mailbox 6 is set to FLASH_DONE. mailbox 5 will contain an
         error code if reading did not work correctly.
      8) If mailbox 5 contains no errors, do a Direct Slave access from
         the temporary storage location obtained in step 3 to the appropriate
         Host memory space (eg. a file).
*/

/*
    The on-board EEPROM type query protocol used by PLX RDKs is as follows:

    If a host application wants to know what EEPROM type exists on board, the
    application should follow the steps below:
      1) Zero out mailbox 5.
      2) Generate a local interrupt by writing to PCI-to-Local doorbell register
         with QUERY_EEPROM_TYPE.
      3) Wait until the doorebell register is cleared.  When it is cleared check
         if mailbox 6 contains FLASH_DONE.
      4) If mailbox 6 contains FLASH_DONE, then mailbox 5 contains the
         EEPROM type on board. The EEPROM type is defined in plxtypes.h file.
      5) If mailbox 6 contains other than FLASH_DONE, then you probably have to
         assume the on-board EEPROM is 93CS46.
*/

/*
   Host aplication writes HOST_QUERY_FLASH_SUPPORT to FLASH_PROTOCOL_REG1.
   If it receives IOP_SUPPORTS_FLASH at FLASH_PROTOCOL_REG1
   then the IOP supports FLASH W/R accesses.
*/
#define FLASH_PROTOCOL_REG1             MailBox5
#define FLASH_PROTOCOL_REG2             MailBox6
#define FLASH_PROTOCOL_REG3             MailBox7

#define HOST_QUERY_FLASH_SUPPORT        0x46594553L          // "FYES"
#define IOP_SUPPORTS_FLASH              0x45534659L          // "ESFY"


/*
   These constants are used by host applications to inform the BSP that
   it wants to do one of the following:
        1). Write to FLASH;
        2). Read from FLASH;
        3). Query on-board EEPROM type.
*/
#define FLASH_WRITE                     0x32466C53L          // "2FLS"
#define FLASH_READ                      0x34466C53L          // "4FLS"
#define QUERY_EEPROM_TYPE               0xEE545950L          // ee"TYP"

// FLASH_DONE status
#define FLASH_DONE                      0x444F4E45L

// FLASH status codes
#define FLASH_OK                        0
#define FLASH_ERR_OFFSET                1
#define FLASH_ERR_SIZE                  2
#define FLASH_ERR_INVALID_ID            3
#define FLASH_ERR_UNKNOWN               4

// FLASH types
#define FLASH_AT49LV040                 0xA0490040L
#define FLASH_AM29F040                  0xA029F040L
#define FLASH_MBM29LV160                0xB0290160L
#define FLASH_AM29LV040B                0xA029040BL

/*
    The following protocol is for downloading a RAM application using Direct
    Slave access.

    1). Host application writes Mailbox 6 with IOP_PREPARE_FOR_DWLD;
    2). Host application resets the embedded microprocessor and waits until
        Mailbox 6 contains IOP_READY or it times out.
    3). Upon the reset, either hardware or software, the IOP will check
        Mailbox 6 contains IOP_PREPARE_FOR_DWLD. If the Mailbox 6 does contain
        IOP_PREPARE_FOR_DWLD, the IOP then will write IOP_READY to mailbox 6 and
        the IOP will wait until Mailbox 6 is changed to IOP_START_APP.
    4). Then, the host application downloads binary executable image to RAM
        using Direct Slave accesses or DMA. Then, the host application writes
        the program entry point to Mailbox 7 and writes IOP_START_APP to
        Mailbox 6.
    5). When the IOP notices that Mailbox 6 is changed to IOP_START_APP, then
        it reads Mailbox 7 and casts it into a function pointer as
        int RamApp(void) and calls it.
*/
#define DOWNLOAD_PROTOCOL_REG1         MailBox6
#define DOWNLOAD_PROTOCOL_REG2         MailBox7
#define DOWNLOAD_PROTOCOL_REG3         MailBox5

#define IOP_READY                      0x44444444
#define IOP_START_APP                  0x55555555
#define IOP_PREPARE_FOR_DWLD           0xaaaaaaaa

/*
    The following protocol is for downloading a RAM application using serial
    communication port.
    
    Binary Block Format (Warning: blockOffset and blockSize endianness should
    be the same as the data itself):
                
        type define _PLX_BLOCK_FORMAT
        {
            U32     BlockOffset;            where to put this block in memory
            U32     BlockSize;              the block size
            char[BlockSize];                data itself
        } PLX_BLOCK_FORMAT, *PPLX_BLOCK_FORMAT;
    
    The above structure will be transmitted as follows:

        Offset (char-based)
        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | ..... n | 0 | 1 | 2 | 3 | ...
        |  blockOffset  |   blockSize   | data    |  blockOffset  |
        
        ..... | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        data  | last blockOff | last blockSiz |
    WARNING:
        1. The above data stream should be ended with 8 bytes of zero to
           facilitate the transmission using XModem protocol and the
           interpretation by IOP software.
        2. The data itself must be aligned on a 4-byte boundary. So, the real
           data size is (blockSize + 3) & 0xFFFFFFFC. The reason for this
           is the IOP software can easily retrieve necessary data from the
           data stream.

    The serial download protocol for RAM application is as follows:
    1). Host application reads one of the following supported file formats:
        COFF, ELF, Motorola S-Record, pure binary and converts it into a file
        according to the structure PLX_BLOCK_FORMAT defined above.
    2). Host application writes Mailbox 7 with the RAM application entry
        point using BEM command BEM_WRITE_BIT_32;
    3). Host application writes Mailbox 6 with IOP_SERIAL_DWLD_PROTOCOL using
        BEM command BEM_WRITE_BIT_32;
    4). Host application resets the embedded microprocessor using BEM command
        BEM_RESET_CPU and waits until it receives a XNAK (0x15h, defined in
        ASCII.h header file). Upon the receipt of a XNAK or XNAKs, the host
        application begins to transfer data to the IOP side using X-Modem
        protocol.
    5). Upon the reset, either hardware or software, the IOP will check
        Mailbox 6 contains IOP_SERIAL_DWLD_PROTOCOL. If the Mailbox 6 does
        contain IOP_SERIAL_DWLD_PROTOCOL, the IOP will begin to initiate the file
        transfer using X-Modem protocol (Checksum method) by sending out XNAK
        (0x15h) periodially or until timeout. The file MUST be in the block
        format PLX_BLOCK_FORMAT so that the IOP can put the data to wherever
        they should be.
    6). When the IOP notices that the binary file has been downloaded completely
        and successfully using serial port, it reads Mailbox 7 and casts it into
        a function pointer as int RamApp(void) and calls it.

    The serial download protocol for FLASH programming is as follows:
    1). Host application reads the binary image file and converts it into a file
        according to the structure PLX_BLOCK_FORMAT defined above. The
        blockOffset is the temporary RAM space pointed by the
        FlashBufferAddressLow which is returned by BEM command BEM_HOST_INQUIRY.
    2). Host application writes Mailbox 7 with the FLASH offset, where the FLASH
        programming should start, using BEM command BEM_WRITE_BIT_32;
    3). Host application writes Mailbox 6 with IOP_SERIAL_FLASH_PROTOCOL using
        BEM command BEM_WRITE_BIT_32;
    4). Host application writes Mailbox 5 with the FLASH image size to be
        programmed.
    5). Host application resets the embedded microprocessor using BEM command
        BEM_RESET_CPU and waits until it receives a XNAK (0x15h, defined in
        ASCII.h header file). Upon the receipt of a XNAK or XNAKs, the host
        application begins to transfer data to the IOP side using X-Modem
        protocol.
    6). Upon the reset, either hardware or software, the IOP will check
        Mailbox 6 contains IOP_SERIAL_FLASH_PROTOCOL. If the Mailbox 6 does
        contain IOP_SERIAL_FLASH_PROTOCOL, the IOP will begin to initiate the
        file transfer using X-Modem protocol (Checksum method) by sending out
        XNAK (0x15h) periodially or until timeout. The file MUST be in the block
        format PLX_BLOCK_FORMAT so that the IOP can put the data to the
        temporary RAM area.
    7). When the IOP notices that the binary file has been downloaded completely
        and successfully using serial port, it reads Mailbox 7 and Mailbox 5
        and call OemProgramFlash to program the FLASH.
    8). When the FLASH programming is done successfully, it resets itself.
*/
#define IOP_SERIAL_DWLD_PROTOCOL        0xaaaaBCDE
#define IOP_SERIAL_FLASH_PROTOCOL       0xaaaaFAFA




#ifdef __cplusplus
}
#endif

#endif
