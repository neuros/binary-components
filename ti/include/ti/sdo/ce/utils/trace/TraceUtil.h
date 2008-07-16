/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== TraceUtil.h ========
 */
/**
 *  @file       ti/sdo/ce/utils/trace/TraceUtil.h
 *
 *  @brief      The Codec Engine utility module for trace.
 */
/**
 *  @defgroup   ti_sdo_ce_utils_trace_TraceUtil Codec Engine Tracing Utility
 */

#ifndef _TRACEUTIL_H
#define _TRACEUTIL_H

#include <ti/sdo/ce/Engine.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_utils_trace_TraceUtil */
/*@{*/


#define TRACEUTIL_SUCCESS 0     /**< Success. */
#define TRACEUTIL_FAILURE -1    /**< General system error. */

/*
 *  ======== TraceUtil_start ========
 */
/**
 *  @brief      Begin using the TraceUtil module; create thread that
 *              periodically collects DSP trace
 *
 *  @param[in]  engineName      Name of the engine.  This uses the same
 *                              name conventions as Engine_open()'s name.
 *
 *  @retval     TRACEUTIL_SUCCESS       Success.
 *  @retval     TRACEUTIL_FAILURE       Failed to initialize the necessary
 *                                      tracing resources.
 *
 *  @sa         TraceUtil_stop()
 */
extern Int  TraceUtil_start(String engineName);

/*
 *  ======== TraceUtil_stop ========
 */
/**
 *  @brief      Finish using the TraceUtil module, stop the collecting thread
 *
 *  @retval     TRACEUTIL_SUCCESS       Success.
 *  @retval     TRACEUTIL_FAILURE       Failed to free the necessary
 *                                      tracing resources.
 *
 *  @sa         TraceUtil_start()
 */
extern Int  TraceUtil_stop(Void);

/** @cond INTERNAL */

extern Void TraceUtil_exit();
extern Void TraceUtil_init();

/** @endcond */

/*@}*/

#ifdef __cplusplus
}
#endif

#endif

/*
 *  @(#) ti.sdo.ce.utils.trace; 1, 0, 1,150; 1-14-2008 09:57:32; /db/atree/library/trees/ce-g30x/src/
 */

