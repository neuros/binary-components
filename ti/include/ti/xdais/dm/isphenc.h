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
 *  @file       ti/xdais/dm/isphenc.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the speech/voice encoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPHENC    xDM 0.9 Speech/Voice Encoder Interface
 *
 *  This is the 0.9 xDM Speech/Voice Encoder Interface.
 *
 *  @deprecated This 0.9 xDM speech encoder interface has been deprecated, and
 *              superceeded by the 1.00 xDM speech encoder interface.
 */

#ifndef ISPHENC_
#define ISPHENC_

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
#include "ispeech.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPHENC */
/*@{*/

#define ISPHENC_CID      "ti.xdais.dm.ISPHENC"  /**< ISPHENC Class ID */

#define ISPHENC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define ISPHENC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define ISPHENC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all ISPHENC
 *              instance objects.
 */
typedef struct ISPHENC_Obj {
    struct ISPHENC_Fxns *fxns;
} ISPHENC_Obj;


/**
 *  @brief      Opaque handle to an ISPHENC objects.
 */
typedef struct ISPHENC_Obj  *ISPHENC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all ISPHENC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @extensibleStruct
 */
typedef struct ISPHENC_Params {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 frameSize;       /**< Input frame size in bytes
                                 *   for sample based codecs.
                                 */
    XDAS_Int32 compandingLaw;   /**< Companding Law.
                                 *   See #ISPEECH_CompoundLaw.
                                 */
    XDAS_Int32 packingType;     /**< Packing Format Option (for codecs
                                 *   that support multiple packing formats -
                                 *   used for selection, 0, 1, 2...)
                                 */
    XDAS_Int32 vadSelection;    /**< VAD A/VAD B, VAD 1/ VAD 2 etc */
} ISPHENC_Params;


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
 */
typedef struct ISPHENC_DynamicParams {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 frameSize;       /**< Input frame size in bytes for sample
                                 *   based codecs.
                                 */
    XDAS_Int32 bitRate;         /**< Rate selection for multi_rate codecs  */
    XDAS_Int32 mode;            /**< Mode selection for multi_mode codecs  */
    XDAS_Int32 vadFlag;         /**< VAD_On =1, VAD_OFF = 0 */
    XDAS_Int32 noiseSuppressionMode; /**< 0 - OFF, 1 = NS-A, 2 = NS-B  etc */
    XDAS_Int32 ttyTddMode;      /**< 0 = TTY OFF, 1 = 45.45bauds 2 = 50 bauds */
    XDAS_Int32 dtmfMode;        /**< 0 = DTMF_OFF, 1 = DTMF_ON */
    XDAS_Int32 dataTransmit;    /**< 1 = ON, 0 = OFF */
    XDAS_Int32 homingMode;      /**< 0 - DISABLED; 1 - ENABLED */
} ISPHENC_DynamicParams;

/**
 *  @brief      Defines the input arguments for all ISPHENC instance
 *              process function.
 *
 *  @extensibleStruct
 */
typedef struct ISPHENC_InArgs {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 nullTrafficChannel; /**< 1 = ON, 0 = OFF */
} ISPHENC_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @extensibleStruct
 */
typedef struct ISPHENC_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @copydoc XDM_ErrorBit. */
    XDAS_Int32 frameSize;       /**< Input frame size in bytes for sample based codecs */
    XDAS_Int32 bitRate;         /**< Rate selection for multi_rate codecs  */
    XDAS_Int32 mode;            /**< Mode selection for multi_mode codecs  */
    XDAS_Int32 vadFlag;         /**< VAD_On =1, VAD_OFF = 0 */
    XDAS_Int32 noiseSuppressionMode; /**< 0 - OFF, 1 = NS-A, 2 = NS-B  etc */
    XDAS_Int32 ttyTddMode;      /**< 0 = TTY OFF, 1 = 45.45bauds 2 = 50 bauds */
    XDAS_Int32 dtmfMode;        /**< 0 = DTMF_OFF, 1 = DTMF_ON */
    XDAS_Int32 dataTransmit;    /**< 1 = ON, 0 = OFF */
    XDAS_Int32 homingMode;      /**< 0 - DISABLED; 1 - ENABLED */
    XDM_AlgBufInfo  bufInfo;    /**< Input and output buffer information.
                                 *   See #XDM_AlgBufInfo.
                                 */
} ISPHENC_Status;

/**
 *  @brief      Defines the run time output arguments for
 *              all ISPHENC instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         ISPHENC_Fxns::process()
 */
typedef struct ISPHENC_OutArgs {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32   rate;          /**< Current frame bit rate. */
    XDAS_Int32   frameType;     /**< Current frame type.  */
    XDAS_Int32   outbufferSize; /**< Output buffer size in bytes. */
} ISPHENC_OutArgs;


/**
 *  @brief      Defines the control commands for the ISPHENC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         ISPHENC_Fxns::control()
 */
typedef  IALG_Cmd ISPHENC_Cmd;


/**
 *  @brief      Defines all of the operations on ISPHENC objects.
 */
typedef struct ISPHENC_Fxns{
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic speech/voice encoding call.
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
 *              ISPHENC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              ISPHENC_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        @c inBufs.buf[0] must not be NULL, and must point to a valid
 *              buffer of data that is at least @c inBufs.bufSizes[0] bytes in
 *              length.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        @c outBufs.buf[0] must not be NULL, and must point to a valid
 *              buffer of data that is at least @c outBufs.bufSizes[0] bytes in
 *              length.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inBufs.
 *              That is, the data and buffers
 *              pointed to by these parameters must be treated as read-only.
 *
 *  @post       The buffers in @c inBufs and @c outBufs are
 *              owned by the calling application.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See ISPHENC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32  (*process)(ISPHENC_Handle handle,  XDM_BufDesc *inBufs,
            XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs,
            ISPHENC_OutArgs *outArgs);


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
 *              ISPHENC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              ISPHENC_Status structure.
 *
 *  @post       The algorithm *must* not modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See ISPHENC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32  (*control)(ISPHENC_Handle handle, ISPHENC_Cmd id,
            ISPHENC_DynamicParams *params, ISPHENC_Status *status);
} ISPHENC_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ISPHENC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

