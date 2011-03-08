#ifndef __ASCII_H
#define __ASCII_H

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
 *      Ascii.h
 *
 * Description:
 *
 *      Constants and macros for ASCII token convertions.
 *
 * Revision:
 *
 *      05-31-01 : PCI SDK v3.30
 *
 *****************************************************************************/




/*****************************************************************
 *  Constants, used in serial downloads
 ****************************************************************/
#define NUL         0x00     /* NULL */
#define SOH         0x01     /* Start of Header */
#define STX         0x02
#define EXT         0x03
#define EOT         0x04     /* End of Transmission */
#define ENQ         0x05
#define ACK         0x06     /* Acnowledge */
#define BEL         0x07     /* Bell */
#define BS          0x08
#define TAB         0x09     /* Tab */
#define LF          0x0A
#define VT          0x0B
#define FF          0x0C
#define CR          0x0D
#define SO          0x0E
#define SI          0x0F
#define DLE         0x10
#define DC1         0x11
#define DC2         0x12
#define DC3         0x13
#define DC4         0x14
#define NAK         0x15     /* No Acnowledge */
#define SYN         0x16
#define ETB         0x17
#define CAN         0x18     /* Cancel */
#define EM          0x19
#define SUB         0x1A
#define ESC         0x1B     /* Escape */
#define FS          0x1C
#define GS          0x1D
#define RS          0x1E
#define US          0x1F
#define SP          0x20
#define DEL         0x7F     /* Delete */



#endif
