/* 
 *  Copyright 2007
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */

/**
 *  @file       ti/xdais/dm/iimgenc.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the image encoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IIMGENC   xDM 0.9 Image Encoder Interface
 *
 *  This is the xDM 0.9 Image Encoder Interface.
 *
 *  @deprecated This 0.9 xDM image encoder interface has been deprecated, and
 *              superceeded by the 1.00 xDM image encoder interface.
 */

#ifndef ti_xdais_dm_IIMGENC_
#define ti_xdais_dm_IIMGENC_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>

/*
 * By definition, this interface is 0.9 xDM.  Before including xdm.h,
 * define XDM_INCLUDE_DOT9_SUPPORT
 */
#ifndef XDM_INCLUDE_DOT9_SUPPORT
#define XDM_INCLUDE_DOT9_SUPPORT
#endif
#include "xdm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IIMGENC */
/*@{*/

#define IIMGENC_CID      "ti.xdais.dm.IIMGENC"  /**< IIMGENC Class ID */

#define IIMGENC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define IIMGENC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define IIMGENC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all IIMGENC
 *              instance objects.
 */
typedef struct IIMGENC_Obj {
    struct IIMGENC_Fxns *fxns;
} IIMGENC_Obj;


/**
 *  @brief      Opaque handle to an IIMGENC objects.
 */
typedef struct IIMGENC_Obj  *IIMGENC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IIMGENC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @extensibleStruct
 */
typedef struct IIMGENC_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum height. */
    XDAS_Int32 maxWidth;        /**< Maximum width. */
    XDAS_Int32 maxScans;        /**< Maximum number of scans. */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 forceChromaFormat;/**< Force encoding in given Chroma format.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
}IIMGENC_Params;


/**
 *  @brief      This structure defines the algorithm parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGENC_Fxns::control()
 */
typedef struct IIMGENC_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numAU;           /**< Number of Access unit to encode.
                                 *   Set to #XDM_DEFAULT to encode the
                                 *   entire frame.
                                 */
    XDAS_Int32 inputChromaFormat;/**< Input chroma format.
                                 *
                                 *    @sa   XDM_ChromaFormat
                                 */
    XDAS_Int32 inputHeight;     /**< Input frame height. */
    XDAS_Int32 inputWidth;      /**< Input frame width. */
    XDAS_Int32 captureWidth;    /**< Pitch.  If set to zero, imageWidth is
                                 *  used; else, this field (assuming it's
                                 *  larger than imageWidth) is used.
                                 */
    XDAS_Int32 generateHeader;  /**< Header generation mode.
                                 *
                                 *   @sa    XDM_EncMode
                                 */
    XDAS_Int32 qValue;          /**< Quality factor for encoder.
                                 *   Set to a value between 0 (lowest quality)
                                 *   and 100 (highest quality).
                                 */
} IIMGENC_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IIMGENC instance
 *              process() function.
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGENC_Fxns::process()
 */
typedef struct IIMGENC_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
} IIMGENC_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).

 *  @extensibleStruct
 *
 *  @sa         IIMGENC_Fxns::control()
 */
typedef struct IIMGENC_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 totalAU;         /**< Total number of Access Units. */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @sa        XDM_AlgBufInfo
                                 */
} IIMGENC_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IIMGENC instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGENC_Fxns::process()
 */
typedef struct IIMGENC_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesGenerated;  /**< Number of bytes generated during the
                                 *   process() call.
                                 */
    XDAS_Int32 currentAU;       /**< Current access unit number. */
} IIMGENC_OutArgs;


/**
 *  @brief      Defines the control commands for the IIMGENC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IIMGENC_Fxns::control()
 */
typedef  IALG_Cmd IIMGENC_Cmd;


/**
 *  @brief      Defines all of the operations on IIMGENC objects.
 */
typedef struct IIMGENC_Fxns{
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic image encoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  inBufs          Input buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.  The algorithm
 *                              may modify the output buffer pointers.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IIMGENC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IIMGENC_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The buffers in @c inBufs and @c outBufs are
 *              owned by the calling application.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IIMGENC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32  (*process)(IIMGENC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs,
        IIMGENC_OutArgs *outArgs);

/**
 *  @brief      Control behaviour of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  id              Command id.  See #XDM_CmdId.
 *  @param[in]  params          Dynamic parameters.  This is a required
 *                              parameter.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c params must not be NULL, and must point to a valid
 *              IIMGENC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IIMGENC_Status structure.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IIMGENC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32  (*control)(IIMGENC_Handle handle, IIMGENC_Cmd id,
        IIMGENC_DynamicParams *params, IIMGENC_Status *status);

} IIMGENC_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* IIMGENC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

