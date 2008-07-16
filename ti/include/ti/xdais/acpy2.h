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
 *  ======== acpy2.h ========
 *  Declaration of the ACPY2 interface.
 */

#ifndef ACPY2_
#define ACPY2_

#include "idma2.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== ACPY2_complete ========
 *  Check to see if all dma transfers on logical channel are finished. This
 *  is a non-blocking call.
 */
extern Int ACPY2_complete(IDMA2_Handle handle);

/*
 *  ======= ACPY2_configure ========
 *  Configure logical channel.
 */
extern Void ACPY2_configure(IDMA2_Handle handle, IDMA2_Params *params);

/*
 *  ======== ACPY2_exit ========
 *  Finalization of the ACPY2 module
 */
extern Void ACPY2_exit(Void);

/*
 *  ======== ACPY2_getChanObjSize ========
 *  Called by framework. Returns the channel object size.
 */
extern Uns ACPY2_getChanObjSize(Void);

/*
 *  ======== ACPY2_init ========
 *  Initialize the ACPY2 module.  Called by framework
 */
extern Void ACPY2_init(Void);

/*
 *  ======== ACPY2_initChannel ========
 *  Called by the framework. Initialize the channel state.
 *  Associate the channel with the provided queueId.
 */
extern Void ACPY2_initChannel(IDMA2_Handle handle, Int queueId);

/*
 * ======== ACPY2_setDstFrameIndex ========
 * Set the Destination Frame Index.
 */
extern Void ACPY2_setDstFrameIndex(IDMA2_Handle handle, Int frameIndex);

/*
 * ======== ACPY2_setNumFrames ========
 * Set the Number of Frames
 */
extern Void ACPY2_setNumFrames(IDMA2_Handle handle, Uns numFrames);

/*
 * ======== ACPY2_setSrcFrameIndex ========
 * Set the Source Frame Index.
 */
extern Void ACPY2_setSrcFrameIndex(IDMA2_Handle handle, Int frameIndex);

/*
 *  ======= ACPY2_start ========
 *  Submit the transfer specific information. The DMA manager will handle
 *  the request, and program the DMA device.
 */
extern Void ACPY2_start(IDMA2_Handle handle,IDMA2_AdrPtr src,
    IDMA2_AdrPtr dst, Uns count);

/*
 *  ======= ACPY2_startAligned ========
 *  Submit the transfer specific information. The DMA manager will
 *  handle the request, and program the DMA device.  Requires aligned
 *  addresses and index parameters
 */
extern Void ACPY2_startAligned(IDMA2_Handle handle,IDMA2_AdrPtr src,
    IDMA2_AdrPtr dst, Uns count);

/*
 *  ======= ACPY2_wait ========
 *  Wait for all data transfer on logical channel to complete. This is a
 *  blocking call.
 */
extern Void ACPY2_wait(IDMA2_Handle handle);

#ifdef __cplusplus
}
#endif

#endif /* ACPY2_ */


/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

