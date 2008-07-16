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
 *  @file       ti/xdais/dm/iimgdec.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the image decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IIMGDEC   xDM 0.9 Image Decoder Interface
 *
 *  This is the xDM 0.9 Image Decoder Interface.
 *
 *  @deprecated This 0.9 xDM image decoder interface has been deprecated, and
 *              superceeded by the 1.00 xDM image decoder interface.
 */

#ifndef ti_xdais_dm_IIMGDEC_
#define ti_xdais_dm_IIMGDEC_

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

/** @ingroup    ti_xdais_dm_IIMGDEC */
/*@{*/

#define IIMGDEC_CID      "ti.xdais.dm.IIMGDEC"  /**< IIMGDEC Class ID */

#define IIMGDEC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define IIMGDEC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define IIMGDEC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all IIMGDEC
 *              instance objects.
 */
typedef struct IIMGDEC_Obj {
    struct IIMGDEC_Fxns *fxns;
} IIMGDEC_Obj;


/**
 *  @brief      Opaque handle to an IIMGDEC objects.
 */
typedef struct IIMGDEC_Obj  *IIMGDEC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IIMGDEC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @extensibleStruct
 */
typedef struct IIMGDEC_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum image height. */
    XDAS_Int32 maxWidth;        /**< Maximum image width. */
    XDAS_Int32 maxScans;        /**< Maximum number of scans. */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 forceChromaFormat;/**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa XDM_ChromaFormat.
                                 */
}IIMGDEC_Params;


/**
 *  @brief      This structure defines the codec parameters that can be
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
 *  @sa         IIMGDEC_Fxns::control()
 */
typedef struct IIMGDEC_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numAU;           /**< Number of Access unit to decode.
                                 *   Set to #XDM_DEFAULT to decode the
                                 *   entire frame.
                                 */
    XDAS_Int32 decodeHeader;    /**< @copydoc XDM_DecMode
                                 *
                                 *   @sa XDM_DecMode
                                 */
    XDAS_Int32 displayWidth;    /**< Pitch.  If set to zero, imageWidth is
                                 *   used; else, this field (assuming it's
                                 *   larger than imageWidth) is used.
                                 */
} IIMGDEC_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IIMGDEC instance
 *              process() function.
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGDEC_Fxns::process()
 */
typedef struct IIMGDEC_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numBytes;        /**< Size of input data in bytes, provided
                                 *   to the algorithm for decoding.
                                 */
} IIMGDEC_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGDEC_Fxns::control()
 */
typedef struct IIMGDEC_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 outputHeight;    /**< Output height. */
    XDAS_Int32 outputWidth;     /**< Output width.  Padding should be taken
                                 *   care of by the decoder.
                                 */
    XDAS_Int32 imageWidth;      /**< Image width. */
    XDAS_Int32 outChromaformat; /**< Output chroma format.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDAS_Int32 totalAU;         /**< Total number of Access Units. */
    XDAS_Int32 totalScan;       /**< Total number of scans. */
    XDM_AlgBufInfo  bufInfo;    /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
} IIMGDEC_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IIMGDEC instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IIMGDEC1_Fxns::process()
 */
typedef struct IIMGDEC_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesconsumed;   /**< Number of bytes consumed during the
                                 *   process() call.
                                 */
    XDAS_Int32 currentAU;       /**< Current access unit number. */
    XDAS_Int32 currentScan;     /**< Current scan number. */
} IIMGDEC_OutArgs;


/**
 *  @brief      Defines the control commands for the IIMGDEC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IIMGDEC_Fxns::control()
 */
typedef  IALG_Cmd IIMGDEC_Cmd;


/**
 *  @brief      Defines all of the operations on IIMGDEC objects.
 */
typedef struct IIMGDEC_Fxns{
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic image decoding call.
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
 *              IIMGDEC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IIMGDEC_OutArgs structure.
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
 *  @retval     IALG_EFAIL      Failure.  See IIMGDEC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*process)(IIMGDEC_Handle handle, XDM_BufDesc *inBufs,
            XDM_BufDesc *outBufs, IIMGDEC_InArgs *inArgs,
            IIMGDEC_OutArgs *outArgs);


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
 *              IIMGDEC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IIMGDEC_Status structure.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IIMGDEC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*control)(IIMGDEC_Handle handle, IIMGDEC_Cmd id,
            IIMGDEC_DynamicParams *params, IIMGDEC_Status *status);

}IIMGDEC_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IIMGDEC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

