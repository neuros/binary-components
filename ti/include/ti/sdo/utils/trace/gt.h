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
 *  ======== gt.h ========
 */

/**
 *  @file       ti/sdo/utils/trace/gt.h
 *
 *  @brief      The "Generic Tracing" module.  Provides producers of content
 *              the ability to, in a runtime-independant way, add tracing.
 *              Also provides consumers of trace-enabled content the
 *              mechanisms necessary to enable/disable the various trace
 *              statements.
 */
/**
 *  @defgroup   ti_sdo_utils_trace_GT        Generic Trace Support
 *
 *  @brief      The "Generic Tracing" module.  Provides producers of content
 *              the ability to, in a runtime-independant way, add tracing.
 *              Also provides consumers of trace-enabled content the
 *              mechanisms necessary to enable/disable the various trace
 *              statements.
 *
 *  @remarks    Note that the public APIs (e.g. GT_create()) are implemented
 *              as macros around private services of a similar name, but
 *              prefixed with an underscore (e.g. _GT_create()).  This enables
 *              GT tracing to be conditionally compiled out of code bases.
 *              Users of the GT APIs should never call the private services
 *              (indicated by convention with a leading underscore '_').
 *              Rather, they should restrict usage to the public APIs
 *              (i.e., call GT_1trace(), not _GT_trace()).
 */
/*  Note        There are two definitions that affect which portions of trace
 *              are actually compiled into the client: @c GT_TRACE and
 *              @c GT_ASSERT. If @c GT_TRACE is set to 0 then all trace
 *              statements (except for assertions) will be compiled
 *              out of the client. If @c GT_ASSERT is set to 0 then
 *              assertions will be compiled out of the
 *              client.  @c GT_ASSERT can not be set to 0 unless @c GT_TRACE
 *              is also set to 0 (i.e. @c GT_TRACE == 1 implies @c GT_ASSERT
 *              == 1).
 */

#ifndef ti_sdo_utils_trace_GT_
#define ti_sdo_utils_trace_GT_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_utils_trace_GT */
/*@{*/

/** @cond INTERNAL */

#ifndef GT_TRACE
#define GT_TRACE 1  /* 0 = "trace compiled out"; 1 = "trace active" */
#endif

#if !defined(GT_ASSERT) || GT_TRACE
#define GT_ASSERT 1
#endif

typedef Void   (*GT_PrintFxn)(String fmt, ...);
typedef Ptr    (*GT_MallocFxn)(Int size);
typedef Void   (*GT_FreeFxn)(Ptr addr, Int size);
typedef UInt32 (*GT_TimeFxn)(Void);

typedef struct {
    GT_PrintFxn  PRINTFXN;
    Fxn          PIDFXN;
    Fxn          TIDFXN;
    GT_PrintFxn  ERRORFXN;
    GT_MallocFxn MALLOCFXN;
    GT_FreeFxn   FREEFXN;
    GT_TimeFxn   TIMEFXN;
    Fxn          LOCKFXN;
    Fxn          UNLOCKFXN;
    Fxn          INITFXN;
} GT_Config;

#if (GT_TRACE != 0) || (GT_ASSERT !=0 ) 
extern __FAR__ GT_Config *GT;
#endif 

/** @endcond */

/**
 *  @brief      Object representing a GT module instance.
 *
 *  @remarks    This is initialized by GT_create().
 *
 *  @remarks    This structure should not be modified directly.  Rather, it
 *              should be manipulated internally via API calls.  It is
 *              documented only because storage space must be
 *              allocated prior to initializing it via GT_create().
 *
 *  @sa         GT_create()
 */
typedef struct {
    String      modName;    /**< Name of this module instance. */
    UInt8      *flags;      /**< The current state of this instance */
} GT_Mask;


/*
 *  New GT Class definitions.
 *
 * [dm]TODO:H new proposal for how we should use different tracing classes: {
 *
 * - GT_ENTER (class 0): On entry to *and exit from* functions: consider
 *                       in general this class to be of interest to users
 *
 * - GT_1CLASS : debugging info of interest to module developer only
 *
 * - GT_2CLASS : info for developer that *might* be of interest to users
 *
 * - GT_3CLASS : open (module developer can creatively use this one)
 *
 * - GT_4CLASS : info for developer that's likely to be important to the users
 *
 * - GT_5CLASS : benchmarking
 *
 * - GT_6CLASS : warnings
 *
 * - GT_7CLASS : errors
 *
 * }
 */

/**
 * @brief       Mask for tracing entry and exit points within functions.
 */
#define GT_ENTER        ((UInt8)0x01)

#define GT_1CLASS       ((UInt8)0x02)   /**< User mask 1. */
#define GT_2CLASS       ((UInt8)0x04)   /**< User mask 2. */
#define GT_3CLASS       ((UInt8)0x08)   /**< User mask 3. */
#define GT_4CLASS       ((UInt8)0x10)   /**< User mask 4. */

/**
 * @brief       User mask 5.  By convention, used for benchmarking related
 *              tracing.
 */
#define GT_5CLASS       ((UInt8)0x20)

/**
 * @brief       User mask 6.  By convention, used for internal warning related
 *              tracing.
 */
#define GT_6CLASS       ((UInt8)0x40)

/**
 * @brief       User mask 7.  By convention, used for internal error related
 *              tracing.
 */
#define GT_7CLASS       ((UInt8)0x80)

/*
 *  ======== _GT_create ========
 */
/**
 *  @brief      Initialize a GT mask.
 *
 *  @param[in]  mask    Address of an existing GT_Mask structure.
 *  @param[in]  modName Module name to be associated with this mask.
 *
 *  @pre        @c mask must point to a pre-allocated GT_Mask structure.
 *              Typically this memory is set aside as a static global
 *              variable for simplicity, althought that need not be
 *              the case.
 *
 *  @remarks    This function should not be called directly.  Users should
 *              use the GT_create() macro wrapping this function instead,
 *              to enable conditional removal of tracing from the client
 *              binaries.
 *
 *  @remarks    @c modName must be unique within the entire system.  To
 *              that end, it typically contains the client package's name.
 */
extern Void _GT_create(GT_Mask *mask, String modName);


/** @cond INTERNAL */

extern UInt32 GT_curTime(Void);

#define GT_exit()

/** @endcond */

/*
 *  ======== GT_init ========
 */
/**
 *  @brief      Initialize the GT module.
 *
 *  @remarks    GT_init() can be called multiple times, and should be called
 *              by all explicit users of GT.
 */
extern Void GT_init(Void);


/*
 *  ======== _GT_set ========
 */
/**
 *  @brief      Modify the current trace mask settings.
 *
 *  @param[in]  str     New trace format string.
 *
 *  @remarks    _GT_set() should not be called directly.  Users should
 *              use the GT_set() macro which wraps _GT_set() instead,
 *              to enable conditional removal of tracing from the client
 *              binaries.
 */
extern Void _GT_set(String str);


/*
 *  ======== _GT_trace ========
 */
/**
 *  @brief      Conditionally emit a trace statement.
 *
 *  @param[in]  mask    Mask associated with this trace statement.
 *  @param[in]  classId class of this trace statement.
 *  @param[in]  format  printf-style format string.
 *
 *  @remarks    This function should not be called directly.  Users should
 *              use the macros wrapping this function instead (e.g. GT_1trace())
 *              to enable conditional removal of tracing from the client
 *              binaries.
 *
 *  @remarks    @c classId can be a logically OR'd set of classes.  Doing so
 *              will cause the trace to be emitted if any of the @c classId
 *              classes are enabled in the current settings of the @c mask.
 *
 *  @remarks    Most, but not all printf format strings are supported.
 *
 *  @pre        @c mask must have been initialized with GT_create().
 *
 *  @sa         GT_create()
 */
extern Int _GT_trace(GT_Mask *mask, Int classId, String format, ...);

/** @cond INTERNAL */
extern Void GT_disable(Void);
extern Void GT_enable(Void);
extern Bool GT_getModNameFlags(String modName, UInt8 *flags);

#if GT_ASSERT == 0

#define GT_assert( mask, expr )
#define GT_config( config )
#define GT_configInit( config )
#define GT_seterror( fxn )

#else

extern GT_Config _ti_sdo_utils_trace_GT_params;

#define GT_assert( mask, expr ) \
        (!(expr) ? \
            (*GT->ERRORFXN)("assertion violation: %s, line %d\n", \
                            __FILE__, __LINE__), NULL : NULL)

#define GT_config(config)     (_ti_sdo_utils_trace_GT_params = *(config))
#define GT_configInit(config) (*(config) = _ti_sdo_utils_trace_GT_params)
#define GT_seterror(fxn) (_ti_sdo_utils_trace_GT_params.ERRORFXN = (Fxn)(fxn))

#endif

/** @endcond */

#if GT_TRACE == 0

/** @cond INTERNAL */

#define GT_curLine()                ((MdUns)__LINE__)
#define GT_curTime()                ((UInt32)0)
#define GT_create(mask, modName)
#define GT_exit()
#define GT_init()
#define GT_set(str)
#define GT_setprintf( fxn )

#define GT_query( mask, classId )     FALSE

#define GT_0trace( mask, classId, format )
#define GT_1trace( mask, classId, format, arg1 )
#define GT_2trace( mask, classId, format, arg1, arg2 )
#define GT_3trace( mask, classId, format, arg1, arg2, arg3 )
#define GT_4trace( mask, classId, format, arg1, arg2, arg3, arg4 )
#define GT_5trace( mask, classId, format, arg1, arg2, arg3, arg4, arg5 )
#define GT_6trace( mask, classId, format, arg1, arg2, arg3, arg4, arg5, arg6 )

/** @endcond */

#else   /* GT_TRACE == 1 */

/** @cond INTERNAL */

extern String GT_format;

#define GT_curLine()      ((MdUns)__LINE__)
#define GT_setprintf(fxn) (_ti_sdo_utils_trace_GT_params.PRINTFXN = (fxn))

#define GT_query(mask, classId) ((*(mask).flags & (classId)))

/** @endcond */

/**
 *  @copydoc    _GT_create
 */
#define GT_create(mask, modName)    _GT_create((mask), (modName))

/**
 *  @copydoc    _GT_set
 */
#define GT_set(str)                 _GT_set(str)

/**
 *  @sa         _GT_trace()
 */
#define GT_0trace( mask, classId, format ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_1trace( mask, classId, format, arg1 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_2trace( mask, classId, format, arg1, arg2 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1), (arg2)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_3trace( mask, classId, format, arg1, arg2, arg3 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1), (arg2), (arg3)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_4trace( mask, classId, format, arg1, arg2, arg3, arg4 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1), (arg2), (arg3), (arg4)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_5trace( mask, classId, format, arg1, arg2, arg3, arg4, arg5 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1), (arg2), (arg3), (arg4), (arg5)) : 0)

/**
 *  @sa         _GT_trace()
 */
#define GT_6trace( mask, classId, format, arg1, arg2, arg3, arg4, arg5, arg6 ) \
    ((*(mask).flags & (classId)) ? \
    _GT_trace(&(mask), (classId), (format), (arg1), (arg2), (arg3), (arg4), \
        (arg5), (arg6)) : 0)



#endif /* GT_TRACE */

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif

/*
 */
/*
 *  @(#) ti.sdo.utils.trace; 1, 0, 0,61; 12-22-2007 16:16:20; /db/atree/library/trees/fc-d36x/src/
 */

