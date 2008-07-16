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
 *  ======== acpy.h ========
 *  ACPY module interface declarations.
 */
#ifndef ACPY_
#define ACPY_

#include "idma.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== ACPY_complete ========
 *  Check to see if all dma transfers on logical channel are finished. This
 *  is a non-blocking call.
 */
extern Int ACPY_complete(IDMA_Handle);

/*
 *  ======= ACPY_configure ========
 *  Configure logical channel.
 */
extern Void ACPY_configure(IDMA_Handle, IDMA_Params *);

/*
 *  ======= ACPY_start ========
 *  Submit the transfer specific information. The DMA manager will handle
 *  the request, and program the DMA device.
 */
extern Void ACPY_start(IDMA_Handle, Void *, Void *, Uns, IDMA_Params *);

/*
 *  ======= ACPY_wait ========
 *  Wait for all data transfer on logical channel to complete. This is a
 *  blocking call.
 */
extern Void ACPY_wait(IDMA_Handle);

#ifdef __cplusplus
}
#endif

#endif /* ACPY_ */

/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

