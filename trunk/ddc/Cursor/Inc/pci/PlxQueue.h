#ifndef _PLX_QUEUE_H_
#define _PLX_QUEUE_H_

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
 *      PlxQueue.h
 *
 * Description:
 *
 *      Header for the PLX Queue helper functions
 *
 * Revision History:
 *
 *      01-30-01 : PCI SDK v3.20
 *
 ******************************************************************************/


#include "PlxTypes.h"


#ifdef __cplusplus
extern "C" {
#endif




/*******************************************
*          Definitions
*******************************************/
typedef struct _PLX_QUEUE
{
    volatile U16  head;
    volatile U16  tail;
    volatile U16  size;
    volatile U8  *pBuffer;
} PLX_QUEUE;




/*******************************************
*        Public Functions
*******************************************/
void
PlxQueueInitialize(
    PLX_QUEUE *pQueue,
    U16        size,
    U8        *pBuffer
    );

void
PlxQueueAdd(
    PLX_QUEUE *pQueue,
    U8         data
    );

U8
PlxQueueRemove(
    PLX_QUEUE *pQueue
    );

void
PlxQueueFlush(
    PLX_QUEUE *pQueue
    );

void
PlxQueueAppendAndFlush(
    PLX_QUEUE *pQueue,
    PLX_QUEUE *pCopyQueue
    );

BOOLEAN
PlxQueueIsEmpty(
    PLX_QUEUE *pQueue
    );

BOOLEAN
PlxQueueIsFull(
    PLX_QUEUE *pQueue
    );



#ifdef __cplusplus
}
#endif

#endif
