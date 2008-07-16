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
 *  @file       ti/xdais/dm/ividdec.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDDEC   xDM 0.9 Video Decoder Interface
 *
 *  This is the 0.9 xDM Video Decoder Interface.
 *
 *  @deprecated This 0.9 xDM video decoder interface has been deprecated, and
 *              superceeded by the 1.00 xDM video decoder interface.
 */

#ifndef ti_xdais_dm_IVIDDEC_
#define ti_xdais_dm_IVIDDEC_

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
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDDEC */
/*@{*/

#define IVIDDEC_CID      "ti.xdais.dm.IVIDDEC"  /**< IVIDDEC Class ID */

#define IVIDDEC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define IVIDDEC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define IVIDDEC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all IVIDDEC
 *              instance objects.
 */
typedef struct IVIDDEC_Obj {
    struct IVIDDEC_Fxns *fxns;
} IVIDDEC_Obj;


/**
 *  @brief      Opaque handle to an IVIDDEC objects.
 */
typedef struct IVIDDEC_Obj  *IVIDDEC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDDEC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @remarks    This structure may be extended by individual codec
 *              implementation allowing customization with vendor
 *              specific parameters.
 *
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct IVIDDEC_Params {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000. */
    XDAS_Int32 maxBitRate;      /**< Maximum bit rate, bits per second.
                                 *   For example, if bit rate is 10 Mbps, set
                                 *   this field to 10000000
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of input data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 forceChromaFormat;/**< Force decode in given Chroma format.
                                 *
                                 *   @sa    XDM_ChromaFormat
                                 */
} IVIDDEC_Params;


/**
 *  @brief      This structure defines the codec parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that a given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC_Fxns::control()
 */
typedef struct IVIDDEC_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 decodeHeader;    /**< Number of access units to decode.
                                 *
                                 *   @sa XDM_DecMode
                                 */
    XDAS_Int32 displayWidth;    /**< Pitch.  If set to zero, use the decoded
                                 *   image width.  Else, use given display
                                 *   width in pixels.
                                 */
    XDAS_Int32 frameSkipMode;   /**< Frame skip mode.
                                 *
                                 *   @sa IVIDEO_FrameSkip
                                 */
} IVIDDEC_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDDEC instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC_Fxns::process()
 */
typedef struct IVIDDEC_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numBytes;        /**< Size of input data in bytes, provided
                                 *   to the algorithm for decoding.
                                 */
    XDAS_Int32 inputID;         /**< The decoder will attach
                                 *   this ID with the corresponding output
                                 *   frames.
                                 *
                                 *   @remarks   This is useful when frames
                                 *   require re-ordering (e.g. B frames).
                                 *
                                 *   @remarks   When there is no re-ordering,
                                 *   IVIDDEC1_OutArgs#outputID will be same
                                 *   as this inputID field.
                                 *
                                 *   @remarks   Zero (0) is not a supported
                                 *              inputID.  This value is
                                 *              reserved for cases when there
                                 *              is no output buffer provided in
                                 *              IVIDDEC1_OutArgs::displayBufs.
                                 *
                                 *   @sa IVIDDEC_OutArgs::outputID.
                                 */
} IVIDDEC_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC_Fxns::control()
 */
typedef struct IVIDDEC_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 outputHeight;    /**< Output height in pixels. */
    XDAS_Int32 outputWidth;     /**< Output width in pixels. */
    XDAS_Int32 frameRate;       /**< Average frame rate in fps * 1000. */
    XDAS_Int32 bitRate;         /**< Average bit rate in bits/second. */
    XDAS_Int32 contentType;     /**< Video Content type.
                                 *
                                 *   @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 outputChromaFormat; /**< Chroma format of output.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDM_AlgBufInfo  bufInfo;    /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
} IVIDDEC_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDDEC instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC_Fxns::process()
 */
typedef struct IVIDDEC_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @copydoc XDM_ErrorBit. */
    XDAS_Int32 bytesConsumed;   /**< Bytes consumed. */
    XDAS_Int32 decodedFrameType;/**< Decoded frame type.
                                 *   See #IVIDEO_FrameType. */
    XDAS_Int32 outputID;        /**< Output ID.  Refer to comment
                                 *   IVIDDEC_InArgs#inputID.
                                 */
    IVIDEO_BufDesc displayBufs; /**< The decoder fills this structure
                                 *   to denote the buffer pointers for
                                 *   current displayable frames.  In
                                 *   case of sequences having I & P
                                 *   frames only, these values are
                                 *   identical to outBufs passed in
                                 *   process().
                                 */
} IVIDDEC_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDDEC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDDEC_Fxns::control()
 */
typedef  IALG_Cmd IVIDDEC_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDDEC objects.
 */
typedef struct IVIDDEC_Fxns {
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call.
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
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDDEC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDDEC_OutArgs structure.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs or @c inArgs.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The buffers in @c inBufs are
 *              owned by the calling application.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IVIDDEC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*process)(IVIDDEC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IVIDDEC_InArgs *inArgs,
        IVIDDEC_OutArgs *outArgs);


/**
 *  @brief      Control behavior of an algorithm.
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
 *              IVIDDEC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDDEC_Status structure.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IVIDDEC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*control)(IVIDDEC_Handle handle, IVIDDEC_Cmd id,
        IVIDDEC_DynamicParams *params, IVIDDEC_Status *status);

} IVIDDEC_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDDEC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

