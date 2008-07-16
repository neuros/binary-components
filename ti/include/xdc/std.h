/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== std.h ========
 *
 */

#ifndef xdc_std__include
#define xdc_std__include

#include <stdarg.h>
#include <stddef.h>

/* macros to simplify "stringification" and computed includes */
#define xdc__stringify(a) #a
#define xdc__local_include(a) xdc__stringify(a.h)
#define xdc__system_include(m) <m.h>

/* TitleCase standard types */

#define xdc_Void        void

typedef char            xdc_Char;
typedef unsigned char   xdc_UChar;
typedef short           xdc_Short;
typedef unsigned short  xdc_UShort;
typedef int             xdc_Int;
typedef unsigned int    xdc_UInt;
typedef long            xdc_Long;
typedef unsigned long   xdc_ULong;
typedef float           xdc_Float;
typedef double          xdc_Double;
typedef long double     xdc_LDouble;
typedef size_t          xdc_SizeT;
typedef va_list         xdc_VaList;

/* Generic Extended Types */

typedef unsigned short  xdc_Bool;
typedef int             (*xdc_Fxn)();   /* function pointer */
typedef void            *xdc_Ptr;       /* data pointer */
typedef char            *xdc_String;    /* null terminated string */

/*
 * Import the target-specific std.h
 *
 * 'xdc_target__' is defined by build world to reference the
 * target-specific <std.h> file (i.e. <ti/targets/std.h>).
 */
#ifdef xdc_target_types__
#define xdc_target__ <xdc_target_types__>
#endif
#ifdef xdc_target__
#include xdc_target__
#endif

/* Long Long Types */

#ifdef xdc__LONGLONG__
typedef long long               xdc_LLong;
typedef unsigned long long      xdc_ULLong;
#else
typedef long                    xdc_LLong;
typedef unsigned long           xdc_ULLong;
#endif

/* restrict keyword */
#ifndef xdc__RESTRICT__
#define restrict
#endif

/* Unprefixed Aliases */

#ifndef xdc__nolocalnames

#define Void xdc_Void

typedef xdc_Char        Char;
typedef xdc_UChar       UChar;
typedef xdc_Short       Short;
typedef xdc_UShort      UShort;
typedef xdc_Int         Int;
typedef xdc_UInt        UInt;
typedef xdc_Long        Long;
typedef xdc_ULong       ULong;
typedef xdc_LLong       LLong;
typedef xdc_ULLong      ULLong;
typedef xdc_Float       Float;
typedef xdc_Double      Double;
typedef xdc_LDouble     LDouble;
typedef xdc_SizeT       SizeT;
typedef xdc_VaList      VaList;

typedef xdc_IArg        IArg;
typedef xdc_UArg        UArg;
typedef xdc_Bool        Bool;
typedef xdc_Int8        Int8;
typedef xdc_Int16       Int16;
typedef xdc_Int32       Int32;
typedef xdc_Fxn         Fxn;
typedef xdc_Ptr         Ptr;
typedef xdc_String      String;

typedef xdc_UInt8       UInt8;
typedef xdc_UInt16      UInt16;
typedef xdc_UInt32      UInt32;

/* DEPRECATED Aliases */
#ifndef XDC__STRICTYPES__
#undef  xdc_DEPRECATEDTYPES
#define xdc_DEPRECATEDTYPES 1
#define _TI_STD_TYPES

/* xdc_Arg is defined only in ti/targets/std.h */
#ifdef xdc__ARG__
typedef xdc_Arg         Arg;
#endif

typedef xdc_UInt8       Uint8;
typedef xdc_UInt16      Uint16;
typedef xdc_UInt32      Uint32;
typedef xdc_UInt        Uns;
#endif

#ifdef xdc__BITS8__
typedef xdc_Bits8       Bits8;
#endif

#ifdef xdc__BITS16__
typedef xdc_Bits16      Bits16;
#endif

#ifdef xdc__BITS32__
typedef xdc_Bits32      Bits32;
#endif

#endif /* xdc__nolocalnames */

/* Standard Constants */

#undef NULL
#define NULL 0

#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE 1

/* Declaration Qualifiers */

#ifndef __FAR__
#define __FAR__
#endif

/* Code-Section Directive */

#ifndef xdc__CODESECT
#define xdc__CODESECT( fn, sn ) 
#endif

#endif /* xdc_std__include */
/*
 *  @(#) xdc; 1, 1, 0, 0,26; 10-28-2007 20:44:03; /db/ztree/library/trees/xdc-q10x/src/packages/
 */

