/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== ti/targets/arm/std.h ========
 *  Standard types for supported TI Arm compilers
 */

#ifndef ti_targets_arm_STD_
#define ti_targets_arm_STD_

/*  Define target-specific "portable" macros
 *
 *  The build command-line define xdc_target_name__ to be the value
 *  of the target's name config parameter.  We use this to include the
 *  target-specific definitions for the required target-independent
 *  xdc_target* macros.
 */
#if defined(xdc_target_name__) & !defined(xdc_target_macros_include__)
#include xdc__local_include(xdc_target_name__)
#endif

/* "inherit" (i.e., include) all ti.targets standard types */
#include <ti/targets/std.h>

#endif /* ti_targets_arm_STD_ */
/*
 *  @(#) ti.targets.arm; 1, 0, 0, 0,26; 10-28-2007 20:42:48; /db/ztree/library/trees/xdc-q10x/src/packages/
 */

