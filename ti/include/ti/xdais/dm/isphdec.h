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
 *  @file       ti/xdais/dm/isphdec.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the speech/voice decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPHDEC    xDM 0.9 Speech/Voice Decoder Interface
 *
 *  This is the xDM 0.9 Speech/Voice Decoder Interface.
 *
 *  @deprecated This 0.9 xDM speech decoder interface has been deprecated, and
 *              superceeded by the 1.00 xDM speech decoder interface.
 */

#ifndef ISPHDEC_
#define ISPHDEC_

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

/** @ingroup    ti_xdais_dm_ISPHDEC */
/*@{*/

#define ISPHDEC_CID      "ti.xdais.dm.ISPHDEC"  /**< ISPHDEC Class ID */

#define ISPHDEC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define ISPHDEC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define ISPHDEC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all ISPHDEC
 *              instance objects.
 */
typedef struct ISPHDEC_Obj {
    struct ISPHDEC_Fxns *fxns;
} ISPHDEC_Obj;


/**
 *  @brief      Opaque handle to an ISPHDEC objects.
 */
typedef struct ISPHDEC_Obj  *ISPHDEC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all ISPHDEC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @remarks    This structure may be extended by individual codec
 *              implementation allowing customization with vendor
 *              specific parameters.  The presence of vendor specific
 *              extensions will be detected by the value of
 *              the @c size parameter.
 *
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct ISPHDEC_Params {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 dataEnable;      /**< TTY/DTMF enabled flag.
                                 *   Set to 1 to enable, 0 to disable.
                                 */
    XDAS_Int32 compandingLaw;   /**< Companding Law.
                                 *   See #ISPEECH_CompoundLaw.
                                 */
    XDAS_Int32 packingType;     /**< Packing Format Option (for codecs
                                 *   that support multiple packing formats -
                                 *   used for selection, 0, 1, 2...)
                                 */
} ISPHDEC_Params;

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
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct ISPHDEC_DynamicParams {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 postFilter;      /**< Post filter enabled flag.
                                 *   Set to 1 to enable, 0 to disable.
                                 */
} ISPHDEC_DynamicParams;

/**
 *  @brief      Defines the input arguments for all ISPHDEC instance
 *              process function.
 *
 *  @remarks    This structure may be extended by individual codec
 *              implementation allowing customization with vendor
 *              specific parameters.
 *
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct ISPHDEC_InArgs {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 frameType;       /**< Input frame type. */
    XDAS_Int32 inBufferSize;    /**< Size of valid input data in bytes to
                                 *   be processed.
                                 */
    XDAS_Int32 bfiFlag;         /**< Bad frame indicator.  BFI = 1 indicates
                                 *   bad frame.
                                 */
} ISPHDEC_InArgs;

/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @remarks    This structure may be extended by individual codec
 *              implementation allowing customization with vendor
 *              specific parameters.
 *
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct ISPHDEC_Status {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 extendedError;   /**< @copydoc XDM_ErrorBit. */
    XDAS_Int32 postFilter;      /**< Post filter enabled flag.
                                 *   Set to 1 to enable, 0 to disable.
                                 */
    XDAS_Int32 dataMode;        /**< To indicate in bavd data reception */
    XDM_AlgBufInfo  bufInfo;    /**< Input and output buffer information.
                                 *   See #XDM_AlgBufInfo.
                                 */
} ISPHDEC_Status;

/**
 *  @brief      Defines the run time output arguments for
 *              all ISPHDEC instance objects.
 *
 *  @remarks    This structure may be extended by individual codec
 *              implementations allowing customization with vendor
 *              specific parameters.
 *
 *  @remarks    The @c size field @b must be correctly set by the caller.
 */
typedef struct ISPHDEC_OutArgs {
    XDAS_Int32 size;            /**< Size of this structure in bytes.
                                 *   Because this structure can be extended,
                                 *   this field @b must be correctly set
                                 *   by the caller.
                                 */
    XDAS_Int32 mode;            /**< Speech voice mode.
                                 *   See #ISPEECH_VoiceMode.
                                 */
} ISPHDEC_OutArgs;


/**
 *  @brief      Defines the control commands for the ISPHDEC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 */
typedef  IALG_Cmd ISPHDEC_Cmd;


/**
 *  @brief      Defines all of the operations on ISPHDEC objects.
 */
typedef struct ISPHDEC_Fxns{
    IALG_Fxns   ialg;             /**< Traditional xDAIS algorithm interface. */

/**
 *  @brief      Basic speech/voice decoding call.
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
 *              ISPHDEC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              ISPHDEC_OutArgs structure.
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
 *  @retval     IALG_EFAIL      Failure.  See ISPHDEC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*process)(ISPHDEC_Handle handle, XDM_BufDesc *inBufs,
            XDM_BufDesc *outBufs, ISPHDEC_InArgs *inArgs,
            ISPHDEC_OutArgs *outArgs);

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
 *              ISPHDEC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              ISPHDEC_Status structure.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See ISPHDEC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*control)(ISPHDEC_Handle handle, ISPHDEC_Cmd id,
            ISPHDEC_DynamicParams *params, ISPHDEC_Status *status);
} ISPHDEC_Fxns;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ISPHDEC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

