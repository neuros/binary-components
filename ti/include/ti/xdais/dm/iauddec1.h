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
 *  @file       ti/xdais/dm/iauddec1.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the audio decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IAUDDEC1   xDM 1.00 Audio Decoder Interface
 *
 *  This is the xDM 1.00 Audio Decoder Interface.
 */

#ifndef ti_xdais_dm_IAUDDEC1_
#define ti_xdais_dm_IAUDDEC1_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"
#include "iaudio.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IAUDDEC1 */
/*@{*/

#define IAUDDEC1_EOK      XDM_EOK              /**< @copydoc XDM_EOK */
#define IAUDDEC1_EFAIL    XDM_EFAIL            /**< @copydoc XDM_EFAIL */
#define IAUDDEC1_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IAUDDEC1
 *              instance objects.
 */
typedef struct IAUDDEC1_Obj {
    struct IAUDDEC1_Fxns *fxns;
} IAUDDEC1_Obj;


/**
 *  @brief      Opaque handle to an IAUDDEC1 objects.
 */
typedef struct IAUDDEC1_Obj  *IAUDDEC1_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IAUDDEC1 instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IAUDDEC1_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 outputPCMWidth;  /**< Number of bits per output PCM Sample. */
    XDAS_Int32 pcmFormat;       /**< Output PCM Format Block/Interleaved.
                                 *
                                 *   @sa    IAUDIO_PcmFormat
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
} IAUDDEC1_Params;


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
 *  @sa         IAUDDEC1_Fxns::control()
 */
typedef struct IAUDDEC1_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 downSampleSbrFlag;/**< Flag to indicate downsampling for SBR.
                                 *
                                 *   Valid values for this field are XDAS_TRUE
                                 *   and XDAS_FALSE.
                                 */
} IAUDDEC1_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IAUDDEC1 instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IAUDDEC1_Fxns::process()
 */
typedef struct IAUDDEC1_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numBytes;        /**< Size of input data in bytes, provided
                                 *   to the algorithm for decoding.
                                 */
    XDAS_Int32 desiredChannelMode;/**< Desired Channel Configuration.
                                 *
                                 *   @sa    IAUDIO_ChannelMode
                                 */
    XDAS_Int32 lfeFlag;         /**< Flag indicating whether LFE channel data
                                 *   is desired in the output.
                                 *
                                 *   Valid values for this field are XDAS_TRUE
                                 *   and XDAS_FALSE.
                                 */
} IAUDDEC1_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @extensibleStruct
 *
 *  @sa         IAUDDEC1_Fxns::control()
 */
typedef struct IAUDDEC1_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_SingleBufDesc data;    /**< Buffer descriptor for data passing.
                                 *
                                 *   @remarks   This buffer can be used as
                                 *              either input or output,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffer will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
    XDAS_Int32 validFlag;       /**< Reflects the validity of this status
                                 *   structure.
                                 *
                                 *   @remarks   In some cases (e.g. erroneous
                                 *              data streams), just after
                                 *              an error has been detected,
                                 *              the complete status provided
                                 *              by the algorithm may be
                                 *              incorrect (e.g. because of
                                 *              header corruption, etc).
                                 *              This field can "warn"
                                 *              the calling application that
                                 *              the contents of this structure
                                 *              are not valid.  (Ideally,
                                 *              the algorithm makes a best
                                 *              attempt to always provide valid
                                 *              data, and this field is always
                                 *              set to XDAS_TRUE.)
                                 *
                                 *
                                 *   @remarks   Valid values for this field are
                                 *              XDAS_TRUE and XDAS_FALSE.
                                 */
    XDAS_Int32 lfeFlag;         /**< Flag indicating the presence of LFE
                                 *   channel in the output.  When the LFE
                                 *   channel is not in the output, this is set
                                 *   to XDAS_FALSE.
                                 *
                                 *   Valid values for this field are XDAS_TRUE
                                 *   and XDAS_FALSE.
                                 */
    XDAS_Int32 bitRate;         /**< Average bit rate, in bits per second. */
    XDAS_Int32 sampleRate;      /**< Sampling frequency, in Hz.
                                 *   For example, if the sampling
                                 *   frequency is 44.1 kHz, this field will
                                 *   be 44100.
                                 */
    XDAS_Int32 channelMode;     /**< Output Channel Configuration.
                                 *
                                 *   @sa    IAUDIO_ChannelMode
                                 */
    XDAS_Int32 pcmFormat;       /**< Output PCM Format Block/Interleaved.
                                 *
                                 *   @sa    IAUDIO_PcmFormat
                                 */
    XDAS_Int32 numSamples;      /**< Number of samples in the output. */
    XDAS_Int32 outputBitsPerSample; /**< Number of bits per output sample.
                                 *   For example, if the value of the field is
                                 *   16, there are 16 output bits per PCM
                                 *   sample.
                                 */
    XDM_AlgBufInfo  bufInfo;    /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
    XDAS_Int32 dualMonoMode;    /**< Mode to indicate type of Dual Mono.
                                 *   Only used in case of Dual Mono Output.
                                 *
                                 *   @sa IAUDIO_DualMonoMode
                                 */
} IAUDDEC1_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IAUDDEC1 instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IAUDDEC1_Fxns::process()
 */
typedef struct IAUDDEC1_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesConsumed;   /**< Number of bytes consumed during the
                                 *   process() call.
                                 */
    XDAS_Int32 numSamples;      /**< Number of output samples per channel. */
    XDAS_Int32 channelMode;     /**< Output Channel Configuration.
                                 *
                                 *   @sa    IAUDIO_ChannelMode
                                 */
    XDAS_Int32 lfeFlag;         /**< Flag indicating the precense of LFE
                                 *   channel in the output.  When the LFE
                                 *   channel is not in the output, this is set
                                 *   to XDAS_FALSE.
                                 *
                                 *   Valid values for this field are XDAS_TRUE
                                 *   and XDAS_FALSE.
                                 */
    XDAS_Int32 dualMonoMode;    /**< Mode to indicate type of Dual Mono.
                                 *   Only used in case of Dual Mono output.
                                 *
                                 *   @sa IAUDIO_DualMonoMode
                                 */
    XDAS_Int32 sampleRate;      /**< Sampling frequency, in Hz.
                                 *   For example, if the sampling
                                 *   frequency is 44.1 kHz, this field will
                                 *   be 44100.
                                 */
} IAUDDEC1_OutArgs;


/**
 *  @brief      Defines the control commands for the IAUDDEC1 module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IAUDDEC1_Fxns::control()
 */
typedef  IALG_Cmd IAUDDEC1_Cmd;


/**
 *  @brief      Defines all of the operations on IAUDDEC1 objects.
 */
typedef struct IAUDDEC1_Fxns{
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic audio decoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] inBufs       Input buffer descriptors.
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
 *              IAUDDEC1_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IAUDDEC1_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c inBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c inBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c outBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c outBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs, with the exception of @c inBufs.descs[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> appropriately set/clear the
 *              @c XDM1_BufDesc::descs[].accessMask field in both @c inBufs
 *              and @c outBufs.
 *              For example, if the algorithm only read from
 *              @c inBufs.descs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs and @c outBufs are
 *              owned by the calling application.
 *
 *  @retval     IAUDDEC1_EOK            @copydoc IAUDDEC1_EOK
 *  @retval     IAUDDEC1_EFAIL          @copydoc IAUDDEC1_EFAIL
 *                                      See IAUDDEC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IAUDDEC1_EUNSUPPORTED   @copydoc IAUDDEC1_EUNSUPPORTED
 */
    XDAS_Int32   (*process)(IAUDDEC1_Handle handle, XDM1_BufDesc *inBufs,
        XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs,
        IAUDDEC1_OutArgs *outArgs);


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
 *              IAUDDEC1_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IAUDDEC1_Status structure.
 *
 *  @pre        If a buffer is provided in the @c status->data field,
 *              it must be physically contiguous and owned by the calling
 *              application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @post       If a buffer was provided in the @c status->data field,
 *              it is owned by the calling application.
 *
 *  @retval     IAUDDEC1_EOK            @copydoc IAUDDEC1_EOK
 *  @retval     IAUDDEC1_EFAIL          @copydoc IAUDDEC1_EFAIL
 *                                      See IAUDDEC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IAUDDEC1_EUNSUPPORTED   @copydoc IAUDDEC1_EUNSUPPORTED
 */
    XDAS_Int32   (*control)(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id,
        IAUDDEC1_DynamicParams *params, IAUDDEC1_Status *status);

} IAUDDEC1_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IAUDDEC1_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

