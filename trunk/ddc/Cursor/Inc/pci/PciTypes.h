#ifndef __PCITYPES_H
#define __PCITYPES_H

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
 *      PciTypes.h
 *
 * Description:
 *
 *      This file defines the basic types available to the PCI code.
 *
 * Revision:
 *
 *      03-01-06 : PCI SDK v4.40
 *
 ******************************************************************************/


#include "PlxError.h"


#if defined(PLX_WDM_DRIVER)
    #include <wdm.h>            // WDM Driver types
#endif

#if defined(PLX_NT_DRIVER)
    #include <ntddk.h>          // NT Kernel Mode Driver types
#endif

#if defined(PLX_VXD_DRIVER)
    #include <basedef.h>        // Win9x/Me VxD Driver types
#endif

#if defined(_WIN32) || defined(_WIN64)
    #if !defined(PLX_DRIVER)
        #include <wtypes.h>     // Windows application level types
    #endif
#endif

// Must be placed before <linux/types.h> to prevent compile errors
#if defined(PLX_LINUX) && !defined(PLX_LINUX_DRIVER)
    #include <memory.h>         // To automatically add mem*() set of functions
#endif

#if defined(PLX_LINUX) || defined(PLX_LINUX_DRIVER)
    #include <linux/types.h>    // Linux types
#endif


#ifdef __cplusplus
extern "C" {
#endif



/******************************************
 *   Linux Application Level Definitions
 ******************************************/
#if defined(PLX_LINUX)
    typedef __s8             S8;
    typedef __u8             U8;
    typedef __s16            S16;
    typedef __u16            U16;
    typedef __s32            S32;
    typedef __u32            U32;
    typedef __s64            S64;
    typedef __u64            U64;
    typedef unsigned long    PLX_UINT_PTR;          // For 32/64-bit code compatability

    typedef int              HANDLE;
    typedef int              PLX_DRIVER_HANDLE;     // Linux-specific driver handle

    #define INVALID_HANDLE_VALUE    (HANDLE)-1
#endif



/******************************************
 *    Linux Kernel Level Definitions
 ******************************************/
#if defined(PLX_LINUX_DRIVER)
    typedef s8               S8;
    typedef u8               U8;
    typedef s16              S16;
    typedef u16              U16;
    typedef s32              S32;
    typedef u32              U32;
    typedef s64              S64;
    typedef u64              U64;
    typedef unsigned long    PLX_UINT_PTR;          // For 32/64-bit code compatability
#endif



/******************************************
 *      Windows Type Definitions
 ******************************************/
#if defined(_WIN32) || defined(_WIN64)
    typedef signed char      S8;
    typedef unsigned char    U8;
    typedef signed short     S16;
    typedef unsigned short   U16;
    typedef signed long      S32;
    typedef unsigned long    U32;
    typedef signed _int64    S64;
    typedef unsigned _int64  U64;
 #if defined(PLX_VXD_DRIVER) || defined(PLX_NT_DRIVER)
    typedef unsigned long    PLX_UINT_PTR;          // For NT 4.0 32/64-bit code compatability
 #else
    typedef UINT_PTR         PLX_UINT_PTR;          // For 32/64-bit code compatability
 #endif

    typedef HANDLE           PLX_DRIVER_HANDLE;     // Windows-specific driver handle
#endif



/******************************************
 *        PLX Local-side Definitions
 ******************************************/
#if defined(PLX_IOP_CODE)
    typedef signed char             S8;
    typedef unsigned char           U8;
    typedef signed short            S16;
    typedef unsigned short          U16;
    typedef signed long             S32;
    typedef unsigned long           U32;
    typedef signed long long        S64;
    typedef unsigned long long      U64;
#endif



/******************************************
 *        DOS Type Definitions
 ******************************************/
#if defined(PLX_DOS)
    typedef signed char      S8;
    typedef unsigned char    U8;
    typedef signed short     S16;
    typedef unsigned short   U16;
    typedef signed long      S32;
    typedef unsigned long    U32;
    typedef U32              PLX_UINT_PTR;          // For 32/64-bit code compatability

    typedef struct _PLX_DEVICE_OBJECT *HANDLE;
    typedef void                      *PLX_DRIVER_HANDLE;

    #define INVALID_HANDLE_VALUE       (NULL)

    #if !defined(_far)
        #define _far
    #endif
#endif



/******************************************
 *    Volatile Basic Type Definitions
 ******************************************/
typedef volatile S8           VS8;
typedef volatile U8           VU8;
typedef volatile S16          VS16;
typedef volatile U16          VU16;
typedef volatile S32          VS32;
typedef volatile U32          VU32;
#if !defined(PLX_DOS)
    typedef volatile S64      VS64;
    typedef volatile U64      VU64;
#endif



/******************************************
 *   Definitions for Code Portability
 ******************************************/
// Convert pointer to an integer
#define PLX_PTR_TO_INT( ptr )    ((PLX_UINT_PTR)(ptr))

// Convert integer to a pointer
#define PLX_INT_TO_PTR( int )    ((VOID*)(PLX_UINT_PTR)(int))




/******************************************
 *      Miscellaneous definitions
 ******************************************/
#if !defined(VOID)
    typedef void              VOID;
#endif

#if (!defined(_WIN32) && !defined(_WIN64)) || defined(PLX_VXD_DRIVER)
    #if !defined(BOOLEAN)
        typedef S8            BOOLEAN;
    #endif
#endif

#if !defined(_WIN32) && !defined(_WIN64)
    #if !defined(BOOL)
        typedef S8            BOOL;
    #endif
#endif

#if !defined(NULL)
    #define NULL              ((VOID *) 0x0)
#endif

#if !defined(TRUE)
    #define TRUE              1
#endif

#if !defined(FALSE)
    #define FALSE             0
#endif




// Remaining structures do no apply to Local-side
#if !defined(PLX_IOP_CODE)

/******************************************
 * PCI SDK Defined Structures
 ******************************************/

// Device Location Structure
typedef struct _DEVICE_LOCATION
{
    U8  BusNumber;
    U8  SlotNumber;
    U16 DeviceId;
    U16 VendorId;
    U8  SerialNumber[20];
} DEVICE_LOCATION;


// PCI Memory Structure
typedef struct _PLX_PHYSICAL_MEM
{
    U64 UserAddr;                    // User-mode virtual address
    U64 PhysicalAddr;                // Bus physical address
    U64 CpuPhysical;                 // CPU physical address
    U32 Size;                        // Size of the buffer
} PLX_PHYSICAL_MEM;

// For portability to previous SDK versions (PCI_MEMORY should not be used)
typedef PLX_PHYSICAL_MEM      PCI_MEMORY;


// Used for PCI BAR user-mode virtual address mapping
typedef struct _PLX_PCI_BAR_SPACE
{
    U64 va;                          // Virtual address of space
    U32 size;                        // Size of mapped region
} PLX_PCI_BAR_SPACE;


// PCI Device Key Identifier
typedef struct _PLX_DEVICE_KEY
{
    U32 IsValidTag;                  // Magic number to determine validity
    U8  bus;                         // Physical device location
    U8  slot;
    U8  function;
    U16 VendorId;                    // Device Identifier
    U16 DeviceId;
    U16 SubVendorId;
    U16 SubDeviceId;
    U8  Revision;
    U8  ApiIndex;                    // Index used internally by the API
    U8  DeviceNumber;                // Number used internally by the device driver
} PLX_DEVICE_KEY;


#if !defined(PLX_DRIVER) && !defined(PLX_LINUX_DRIVER)
// PLX Device Object Structure
typedef struct _PLX_DEVICE_OBJECT
{
    U32                IsValidTag;   // Magic number to determine validity
    PLX_DEVICE_KEY     Key;          // Device location key identifier
    PLX_DRIVER_HANDLE  hDevice;      // Handle to driver
    PLX_PCI_BAR_SPACE  PciBar[6];    // Used for PCI BAR user-mode virtual address mapping
 #if defined(PLX_DOS)
    U32                PlxChipType;
    U8                 Revision;
 #endif
} PLX_DEVICE_OBJECT;
#endif


// PLX Notification Object
typedef struct _PLX_NOTIFY_OBJECT
{
    U32 IsValidTag;                  // Magic number to determine validity
    U64 pWaitObject;                 // -- INTERNAL -- Wait object used by the driver
    U64 hEvent;                      // User event handle (HANDLE can be 32 or 64 bit)
} PLX_NOTIFY_OBJECT;

#endif // !defined(PLX_IOP_CODE)



#ifdef __cplusplus
}
#endif

#endif
