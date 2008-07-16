/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== ti/targets/std.h ========
 *  Standard types for supported TI compilers
 *
 */

#ifndef ti_targets_STD_
#define ti_targets_STD_

/* include target-specific "portable" macros */
#if defined(xdc_target_name__) & !defined(xdc_target_macros_include__)
#include xdc__local_include(xdc_target_name__)
#endif

#include <stdint.h>     /* C99 standard integer types */

/*
 * xdc__LONGLONG__ indicates if compiler supports 'long long' type
 * xdc__BITS<n> __ indicates if compiler supports 'uint<n>_t' type
 */
#if defined(_TMS320C28X)                        /* 28x */
    #define xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

    #define xdc__ARG__
    typedef void *xdc_Arg;      /* deprecated, but compatible with BIOS 5.x */
#elif defined(_TMS320C5XX)                      /* 54x */
    #undef xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

    #define xdc__ARG__
    typedef int xdc_Arg;        /* deprecated, but compatible with BIOS 5.x */
#elif defined(__TMS320C55X__)                   /* 55x */
    #define xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

    #define xdc__ARG__
    typedef void *xdc_Arg;      /* deprecated, but compatible with BIOS 5.x */
#elif defined(__TMS320C55X_PLUS_BYTE__)         /* 55x+ byte mode */
    #undef xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

    #define xdc__ARG__
    typedef void *xdc_Arg;      /* deprecated, but compatible with BIOS 5.x */
#elif defined(_TMS320C6X)                       /* all C6x */
    #define xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

    #define xdc__ARG__
    typedef int xdc_Arg;        /* deprecated, but compatible with BIOS 5.x */

    #define __FAR__ far
#elif defined(__TMS470__)                       /* ARM */
    #define xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
#elif defined(__MSP430__)                       /* MSP430 */
    #undef xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
#else
    #error <ti/targets/std.h> is not supported for this target
#endif

/*
 *  ======== [U]Int<n> ========
 */
typedef int_least8_t    xdc_Int8;
typedef uint_least8_t   xdc_UInt8;
typedef int_least16_t   xdc_Int16;
typedef uint_least16_t  xdc_UInt16;
typedef int_least32_t   xdc_Int32;
typedef uint_least32_t  xdc_UInt32;

#ifdef INT40_C
    typedef int_least40_t   xdc_Int40;
  #ifndef xdc__nolocalnames
    typedef xdc_Int40           Int40;
  #endif
#endif
#ifdef UINT40_C
    typedef uint_least40_t  xdc_UInt40;
  #ifndef xdc__nolocalnames
    typedef xdc_UInt40          UInt40;
  #endif
#endif
#ifdef INT64_C
    typedef int_least64_t   xdc_Int64;
  #ifndef xdc__nolocalnames
    typedef xdc_Int64           Int64;
  #endif
#endif
#ifdef UINT64_C
    typedef int_least64_t   xdc_UInt64;
  #ifndef xdc__nolocalnames
    typedef xdc_UInt64          UInt64;
  #endif
#endif

/*
 *  ======== Bits<n> ========
 */
#ifdef xdc__BITS8__
    typedef uint8_t     xdc_Bits8;
#endif
#ifdef xdc__BITS16__
    typedef uint16_t    xdc_Bits16;
#endif
#ifdef xdc__BITS32__
    typedef uint32_t    xdc_Bits32;
#endif

/*
 *  ======== [UI]Arg ========
 */
typedef intptr_t        xdc_IArg;
typedef uintptr_t       xdc_UArg;

/*
 *  ======== restrict ========
 */
#define xdc__RESTRICT__


/*
 *  ======== xdc__CODESECT ========
 */
#if defined(_TMS320C28X) && !defined(__cplusplus)

#ifdef __cplusplus
#define __mkop(fn,sn) CODE_SECTION(".text:" sn)
#else
#define __mkop(fn,sn) CODE_SECTION(fn , ".text:" sn)
#endif
#define __mkpragma(a) _Pragma(a)

#define xdc__CODESECT(fn,sn) \
__mkpragma(__STR__(__mkop(fn,sn))) \
asm("   .sect \".text:" sn "\""); \
asm("    .clink"); \

#endif


/*
 *  ======== __ti__ ========
 *  These symbols are used by RTSC tools to indicate presence/absence of
 *  assorted #pragma options in TI compiler.  The current (Aug/05) 2xx compiler
 *  and TMS470 compiler do not have full set of #pragma's.
 */
#define __ti__
#define __ti__align
#define __ti__sect

#if defined(_TMS320C28X)
#undef __ti__align
#endif

#endif /* ti_targets_STD_ */
/*
 *  @(#) ti.targets; 1, 0, 0, 1,26; 10-28-2007 20:42:49; /db/ztree/library/trees/xdc-q10x/src/packages/
 */

