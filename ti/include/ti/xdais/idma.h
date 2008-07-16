/* 
 *  Copyright 2007
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== idma.h ========
 *  Declaration of the IDMA interface.
 */
#ifndef IDMA_
#define IDMA_

#include "ialg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== IDMA_Handle ========
 *  Handle to "logical" DMA channel.
 */
typedef struct IDMA_Obj *IDMA_Handle;

/*
 *  ======== IDMA_ElementSize ========
 *  8, 16 or 32-bit aligned transfer.
 */
typedef enum IDMA_ElementSize {
    IDMA_ELEM8,         /* 8-bit data element */
    IDMA_ELEM16,        /* 16-bit data element */
    IDMA_ELEM32         /* 32-bit data element */
} IDMA_ElementSize;

/*
 *  ======== IDMA_TransferType ========
 *  Type of the DMA transfer.
 */
typedef enum IDMA_TransferType {
    IDMA_1D1D,          /* 1-dimensional to 1-dimensional transfer */
    IDMA_1D2D,          /* 1-dimensional to 2-dimensional transfer */
    IDMA_2D1D,          /* 2-dimensional to 1-dimensional transfer */
    IDMA_2D2D           /* 2-dimensional to 2-dimensional transfer */
} IDMA_TransferType;

/*
 *  ======== IDMA_Params ========
 *  DMA transfer specific parameters. Defines the configuration of a
 *  logical channel.
 */
typedef struct IDMA_Params {
    IDMA_TransferType  xType;           /* 1D1D, 1D2D, 2D1D or 2D2D */
    IDMA_ElementSize   elemSize;        /* Element transfer size */
    Int                numFrames;       /* Num of frames for 2D transfers */
    Int                stride;          /* Jump in elemSize for 2D transfers */
} IDMA_Params;

/*
 *  ======== IDMA_ChannelRec ========
 *  DMA record used to describe the logical channels.
 */
typedef struct IDMA_ChannelRec {
    Int          depth;         /* Num max (concurrent) queued transfers */
    Bool         dimensions;    /* 0 = only 1D transfers, 2D otherwise */
    IDMA_Handle  handle;        /* Handle to logical DMA channel */
} IDMA_ChannelRec;

/*
 *  ======== IDMA_Fxns ========
 *  These fxns are used to query/grant the DMA resources requested by
 *  the algorithm at initialization time, and to change these resources
 *  at runtime. All these fxns are implemented by the algorithm, and
 *  called by the client of the algorithm.
 *
 *    implementationId    - unique pointer that identifies the module
 *                          implementing this interface.
 *    dmaChangeChannels() - apps call this whenever the logical channels
 *                          are moved at runtime.
 *    dmaGetChannelCnt()  - apps call this to query algorithm about max
 *                          number of logical dma channel requested.
 *    dmaGetChannels()    - apps call this to query algorithm about its
 *                          dma channel requests at init time, or to get
 *                          the current channel holdings.
 *    dmaInit()           - apps call this to grant dma handle(s) to the
 *                          algorithm at initialization. Algorithm initializes
 *                          the instance object.
 */
typedef struct IDMA_Fxns {
    Void        *implementationId;
    Void        (*dmaChangeChannels)(IALG_Handle, IDMA_ChannelRec *);
    Int         (*dmaGetChannelCnt)(Void);
    Int         (*dmaGetChannels)(IALG_Handle, IDMA_ChannelRec *);
    Int         (*dmaInit)(IALG_Handle, IDMA_ChannelRec *);
} IDMA_Fxns;

#ifdef __cplusplus
}
#endif

#endif  /* IDMA_ */

/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

