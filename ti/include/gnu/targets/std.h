/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== gnu/targets/std.h ========
 *
 */

#ifndef gnu_targets_STD_
#define gnu_targets_STD_

/* include target-specific "portable" macros */
#if defined(xdc_target_name__) & !defined(xdc_target_macros_include__)
#include xdc__local_include(xdc_target_name__)
#endif

/*
 * xdc__LONGLONG__ indicates if compiler supports 'long long' type
 * xdc__BITS<n> __ indicates if compiler supports 'uint<n>_t' type
 */
#define xdc__LONGLONG__
#define xdc__BITS8__
#define xdc__BITS16__
#define xdc__BITS32__

/*
 *  ======== [U]Int<n> ========
 */
typedef signed char     xdc_Int8;
typedef unsigned char   xdc_UInt8;
typedef short           xdc_Int16;
typedef unsigned short  xdc_UInt16;
typedef long            xdc_Int32;
typedef unsigned long   xdc_UInt32;

/*
 *  ======== Bits<n> ========
 */
typedef unsigned char   xdc_Bits8;
typedef unsigned short  xdc_Bits16;
typedef unsigned long   xdc_Bits32;

/*
 *  ======== [IU]Arg ========
 */
typedef long            xdc_IArg;
typedef unsigned long   xdc_UArg;

#define xdc__ARG__
typedef xdc_IArg xdc_Arg;       /* deprecated, but compatible with BIOS 5.x */

#endif /* gnu_targets_STD_ */

/*
 *  @(#) gnu.targets; 1, 0, 0, 2,26; 10-28-2007 20:41:14; /db/ztree/library/trees/xdc-q10x/src/packages/
 */

