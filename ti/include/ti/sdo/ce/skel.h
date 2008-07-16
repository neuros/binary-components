/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== skel.h ========
 */
/**
 *  @file       ti/sdo/ce/skel.h
 *
 *  @brief      The Codec Engine System Programming Interface (SPI) for
 *              skeleton developers.
 */
/**
 *  @addtogroup ti_sdo_ce_SKEL      CE Skeleton SPI
 */

#ifndef ti_sdo_ce_SKEL_
#define ti_sdo_ce_SKEL_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/ce/visa.h>

/** @ingroup    ti_sdo_ce_SKEL */
/*@{*/

/**
 *  @brief  Prototype for a skeleton's call() implementation
 *
 *  @param[in]      handle  A handle to the current skeleton.
 *  @param[in]      msg     A message sent by the algorithm's stub
 */
typedef VISA_Status (*SKEL_CALLFXN)(VISA_Handle handle, VISA_Msg msg);

/**
 *  @brief  Prototype for a skeleton's create() API.
 *
 *  @param[in]      reserved    Reserved.
 *  @param[in]      name        Name of the algorithm to create.
 *  @param[in]      params      Creation parameters for the algorithm.
 *
 *  @retval         NULL        Error, unable to create the algorithm.
 *  @retval         non-NULL    Handle to the successfully created algorithm.
 */
typedef VISA_Handle (*SKEL_CREATEFXN)(Void *reserved, String name,
    Void *params);

/**
 *  @brief  Prototype for a skeleton's destroy() API.
 *
 *  @param[in]      handle  A handle to the current skeleton.
 *  @param[in]      msg     A message sent by the algorithm's stub
 */
typedef Void (*SKEL_DESTROYFXN)(VISA_Handle handle);


/*
 *  ======== SKEL_Fxns ========
 */
/**
 *  @brief      Table of functions defining the interface of a skeleton.
 */
typedef struct SKEL_Fxns {
    SKEL_CALLFXN    call;       /**< A skeleton's "call" implementation. */
    SKEL_CREATEFXN  apiCreate;  /**< A skeleton's "create" API. */
    SKEL_DESTROYFXN apiDestroy; /**< A skeleton's "destroy" API. */
} SKEL_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _SKEL_ */
/*
 *  @(#) ti.sdo.ce; 1, 0, 5,267; 1-14-2008 09:48:56; /db/atree/library/trees/ce-g30x/src/
 */

