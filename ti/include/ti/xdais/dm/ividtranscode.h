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
 *  @file       ti/xdais/dm/ividtranscode.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video transcoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDTRANSCODE   xDM 1.10 Video Transcoder Interface
 *
 *  This is the xDM 1.10 Video Transcoder Interface.
 */

#ifndef ti_xdais_dm_IVIDTRANSCODE_
#define ti_xdais_dm_IVIDTRANSCODE_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDTRANSCODE */
/*@{*/

#define IVIDTRANSCODE_EOK       XDM_EOK             /**< @copydoc XDM_EOK */
#define IVIDTRANSCODE_EFAIL     XDM_EFAIL           /**< @copydoc XDM_EFAIL */
#define IVIDTRANSCODE_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

#define IVIDTRANSCODE_MAXOUTSTREAMS 2               /**< @todo Document this. */

/**
 *  @brief      This must be the first field of all IVIDTRANSCODE
 *              instance objects.
 */
typedef struct IVIDTRANSCODE_Obj {
    struct IVIDTRANSCODE_Fxns *fxns;
} IVIDTRANSCODE_Obj;


/**
 *  @brief      Opaque handle to an IVIDTRANSCODE objects.
 */
typedef struct IVIDTRANSCODE_Obj  *IVIDTRANSCODE_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDTRANSCODE instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDTRANSCODE_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numOutputStreams; /**< Number of output transcoded streams
                                 *   This allows the possibility of generating
                                 *   more than one transcoded bit-streams from
                                 *   a single incoming bit-stream.
                                 */
    XDAS_Int32 formatInput;     /**< @copydoc IVIDEO_Format
                                 *
                                 *   @sa IVIDEO_Format
                                 *
                                 *   @remarks  This is the video standard of
                                 *             incoming bit stream.
                                 */

    XDAS_Int32 formatOutput[IVIDTRANSCODE_MAXOUTSTREAMS];  /**<
                                 *   @copydoc IVIDEO_Format
                                 *
                                 *   @sa IVIDEO_Format
                                 *
                                 *   @remarks  This array indicates the video
                                 *             standard for each of the
                                 *             transcoded bit streams.
                                 */

    XDAS_Int32 maxHeightInput;  /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidthInput;   /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRateInput; /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 maxBitRateInput;  /**< Maximum bit rate, bits per second.
                                 *   For example, if bit rate is 10 Mbps, set
                                 *   this field to 10000000
                                 */
    XDAS_Int32 maxHeightOutput[IVIDTRANSCODE_MAXOUTSTREAMS];  /**< Maximum
                                 *   output video height in pixels for each
                                 *   of the transcoded output. */
    XDAS_Int32 maxWidthOutput[IVIDTRANSCODE_MAXOUTSTREAMS];   /**< Maximum
                                 *   output video width in pixels for each of
                                 *   the transcoded output. */
    XDAS_Int32 maxFrameRateOutput[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Maximum
                                 *   frame rate in fps * 1000.
                                 *   for each out the output bitstreams
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 maxBitRateOutput[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Maximum bit
                                 *   rate, in bits per second for each of the
                                 *   transcoded bitstreams.
                                 *   For example, if bit rate is 10 Mbps, set
                                 *   this field to 10000000
                                 */

    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
} IVIDTRANSCODE_Params;


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
 *  @sa         IVIDTRANSCODE_Fxns::control()
 */
typedef struct IVIDTRANSCODE_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 readHeaderOnlyFlag; /**< Read the seq header, populate
                                 *   outargs, and return.
                                 *
                                 *   @remarks   Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 */
    XDAS_Int32 keepInputResolutionFlag[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Flag
                                 *   for each transcoded stream to indicate if
                                 *   the output frame resolution is to be kept
                                 *   equal to the input frame resolution
                                 *   (i.e. no resolution change).
                                 *
                                 *   @remarks   Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 */
    XDAS_Int32 outputHeight[IVIDTRANSCODE_MAXOUTSTREAMS];    /**< Output frame
                                 *   height for each of the transcoded outputs.
                                 *
                                 *   @remarks   Used for scaling.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputResolutionFlag is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 outputWidth[IVIDTRANSCODE_MAXOUTSTREAMS];     /**< Output frame
                                 *   for each of the transcoded outputs.
                                 *
                                 *   @remarks   Used for scaling.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputResolution is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 keepInputFrameRateFlag[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Flag
                                 *  for each transcoded stream to indicate if
                                 *  the input frame rate is to be maintained
                                 *  (i.e., no frame rate change).
                                 *
                                 *  @remarks    Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 */
    XDAS_Int32 inputFrameRate;  /**< Reference, or input, frame rate in
                                 *   fps * 1000.
                                 *
                                 *   @remarks   For example, if ref frame
                                 *              rate is 30 frames per second,
                                 *              this field will be 30000.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputFramerate field is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 outputFrameRate[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Target frame
                                 *   rate in fps * 1000, for each of the
                                 *   transcoded outputs.
                                 *
                                 *   @remarks   For example, if target frame
                                 *              rate is 30 frames per second,
                                 *              this field will be 30000.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputFramerate field is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 targetBitRate[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Target bit
                                 *   rate in bits per second, for each of the
                                 *   transcoded outputs.
                                 */
    XDAS_Int32 rateControl[IVIDTRANSCODE_MAXOUTSTREAMS];   /**< Rate control
                                 *   related selection for each of the
                                 *   transcoded outputs.
                                 *
                                 *   @sa IVIDEO_RateControlPreset
                                 */
    XDAS_Int32 keepInputGOPFlag[IVIDTRANSCODE_MAXOUTSTREAMS]; /**< Retain the
                                 *   input GOP structure (to the extent
                                 *   possible) flag for each transcoded output.
                                 *
                                 *   @remarks   Possible values are XDAS_TRUE,
                                 *              and XDAS_FALSE.
                                 */
    XDAS_Int32 intraFrameInterval[IVIDTRANSCODE_MAXOUTSTREAMS];/**< I frame
                                 *   interval for each of the transcoded
                                 *   outputs.
                                 *
                                 *   @remarks  For example, this field will be:
                                 *      - 0 - Only first frame to be intra
                                 *        coded.  e.g. IPPPPPP...
                                 *      - 1 - No inter frames (all intra
                                 *        frames).
                                 *      - 2 - Consecutive IPIPIP... sequence (if
                                 *        no B frames).
                                 *      - 3 - IPPIPP... or IPBIPBI... and so on.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputGOP field is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 interFrameInterval[IVIDTRANSCODE_MAXOUTSTREAMS];/**< Number of
                                 *   B frames between two reference frames for
                                 *   each of the transcoded output.
                                 *
                                 *   @remarks   For example, this field will be:
                                 *     - 0 - to use @c maxInterFrameInterval.
                                 *     - 1 - 0 B frames between two reference
                                 *       frames.
                                 *     - 2 - 1 B frame between two reference
                                 *       frames.
                                 *     - 3 - 2 B frames between two reference
                                 *       frames.
                                 *     - and so on...
                                 *
                                 *   @sa IVIDTRANSCODE_Params.maxInterFrameInterval.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputGOP field is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 forceFrame[IVIDTRANSCODE_MAXOUTSTREAMS];  /**< Force the current
                                 *   (immediate) frame within the specific
                                 *   transcoded output to be encoded as a
                                 *   specific frame type.
                                 *
                                 *   @remarks   For example, this field will be:
                                 *     - IVIDEO_NA_FRAME - No forcing of any
                                 *       specific frame type for the frame.
                                 *     - IVIDEO_I_FRAME - Force the frame to be
                                 *       encoded as I frame.
                                 *     - IVIDEO_IDR_FRAME - Force the frame to
                                 *       be encoded as an IDR frame (specific
                                 *       to H.264 codecs).
                                 *     - IVIDEO_P_FRAME - Force the frame to be
                                 *       encoded as a P frame.
                                 *     - IVIDEO_B_FRAME - Force the frame to be
                                 *       encoded as a B frame.
                                 *
                                 *   @sa IVIDEO_FrameType.
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputGOPFlag field is
                                 *              set to XDAS_TRUE.
                                 */
    XDAS_Int32 frameSkipTranscodeFlag[IVIDTRANSCODE_MAXOUTSTREAMS];   /**< A
                                 *   flag per transcoded output to enforce a
                                 *   frame skip.
                                 *
                                 *   @remarks   Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 *
                                 *   @remarks   This field is ignored when the
                                 *              @c keepInputGOPFlag field is
                                 *              set to XDAS_TRUE.
                                 *
                                 *   @sa IVIDEO_FrameSkipTranscode
                                 */
} IVIDTRANSCODE_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDTRANSCODE instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDTRANSCODE_Fxns::process()
 */
typedef struct IVIDTRANSCODE_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numBytes;        /**< Size of input data in bytes, provided
                                 *   to the algorithm for decoding.
                                 */
    XDAS_Int32 inputID;         /**< The decoder will attach
                                 *   this ID with the corresponding output
                                 *   frames.
                                 *
                                 */
} IVIDTRANSCODE_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDTRANSCODE_Fxns::control()
 */
typedef struct IVIDTRANSCODE_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_SingleBufDesc data;    /**< Buffer descriptor for data passing.
                                 *
                                 *   @remarks   If this field is not used,
                                 *              the application <b>must</b>
                                 *              set @c data.buf to NULL.
                                 *
                                 *   @remarks   This buffer can be used as
                                 *              either input or output,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffer will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the
                                 *              IVIDTRANSCODE_Fxns.control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @remarks   This field provides the
                                 *              application with the algorithm's
                                 *              buffer requirements.  The
                                 *              requirements may vary depending
                                 *              on the current configuration
                                 *              of the algorithm instance.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */

} IVIDTRANSCODE_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDTRANSCODE instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDTRANSCODE_Fxns::process()
 */
typedef struct IVIDTRANSCODE_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bitsConsumed;    /**< Number of bits consumed during the
                                 *   IVIDTRANSCODE_Fxns.process() call.
                                 */
    XDAS_Int32 bitsGenerated[IVIDTRANSCODE_MAXOUTSTREAMS];   /**< Number of
                                 *   bits generated during the
                                 *   IVIDTRANSCODE_Fxns.process() call
                                 *   for each transcode output.
                                 */
    XDAS_Int32 decodedPictureType;/**< Type of the decoded picture.
                                 *
                                 *  @sa IVIDEO_PictureType
                                 */
    XDAS_Int32 decodedPictureStructure; /**< Structure of the decoded picture.
                                 *
                                 * @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 encodedPictureType[IVIDTRANSCODE_MAXOUTSTREAMS];/**< Type of the
                                 *  encoded picture for each transcode output.
                                 *
                                 *  @sa IVIDEO_PictureType
                                 */
    XDAS_Int32 encodedPictureStructure[IVIDTRANSCODE_MAXOUTSTREAMS];/**<
                                 *  Structure of the encoded picture for each
                                 *  transcode output.
                                 *
                                 * @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 decodedHeight;   /**< Decoded frame height */
    XDAS_Int32 decodedWidth;    /**< Decoded frame width */
    XDAS_Int32 outputID[IVIDTRANSCODE_MAXOUTSTREAMS];        /**< This is the ID
                                 *   of the encoded buffer for each output. This
                                 *   field is also used by the client to
                                 *   identify the @c outBufs supplied with the
                                 *   IVIDTRANSCODE_Fxns.process() call that
                                 *   can be reused.
                                 *
                                 *   @remarks   This will be set to zero when
                                 *              there is no encoded buffer for
                                 *              passing to client application.
                                 *
                                 *   @sa IVIDTRANSCODE_InArgs::inputID.
                                 */
    XDAS_Int32 inputFrameSkipTranscodeFlag[IVIDTRANSCODE_MAXOUTSTREAMS]; /**<
                                 *   Flag to indicate if the current frame was
                                 *   skipped in specific transcode outputs.
                                 *
                                 *
                                 *   @remarks   Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 */
    XDM1_SingleBufDesc encodedBuf[IVIDTRANSCODE_MAXOUTSTREAMS];/**< When
                                 *   @c outputID for a specific transcode
                                 *   output is non-zero, the corresponding
                                 *   encoded buffer related information
                                 *   is populated here.
                                 */
    XDAS_Int32 outBufsInUseFlag; /**< Flag to indicate that the @c outBufs
                                 *   provided with the
                                 *   IVIDTRANSCODE_Fxns.process() call are in
                                 *   use.  No outBufs are required to be
                                 *   supplied with the next
                                 *   IVIDTRANSCODE_Fxns.process() call.
                                 *
                                 *   @remarks   Possible values XDAS_TRUE,
                                 *              XDAS_FALSE
                                 */
} IVIDTRANSCODE_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDTRANSCODE module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDTRANSCODE_Fxns::control()
 */
typedef  IALG_Cmd IVIDTRANSCODE_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDTRANSCODE objects.
 */
typedef struct IVIDTRANSCODE_Fxns {
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call.
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
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDTRANSCODE_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDTRANSCODE_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c inBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c inBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        @c outBufs->buf[0] must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c outBufs->bufSizes[0] bytes in length.
 *
 *  @pre        The buffers in @c inBuf and @c outBuf are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs, with the exception of @c inBufs.bufDesc[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> modify the contents of
 *              @c inBufs->descs[].accessMask and appropriately indicate the
 *              mode in which each of the buffers in @c inBufs were read.
 *              For example, if the algorithm only read from
 *              @c inBufs.descs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs are
 *              owned by the calling application.
 *
 *  @retval     IVIDTRANSCODE_EOK       @copydoc IVIDTRANSCODE_EOK
 *  @retval     IVIDTRANSCODE_EFAIL          @copydoc IVIDTRANSCODE_EFAIL
 *                                      See IVIDTRANSCODE_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDTRANSCODE_EUNSUPPORTED  @copydoc IVIDTRANSCODE_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
        IVIDTRANSCODE_OutArgs *outArgs);


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
 *              IVIDTRANSCODE_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDTRANSCODE_Status structure.
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
 *  @retval     IVIDTRANSCODE_EOK       @copydoc IVIDTRANSCODE_EOK
 *  @retval     IVIDTRANSCODE_EFAIL     @copydoc IVIDTRANSCODE_EFAIL
 *                                      See IVIDTRANSCODE_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDTRANSCODE_EUNSUPPORTED @copydoc IVIDTRANSCODE_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDTRANSCODE_Handle handle, IVIDTRANSCODE_Cmd id,
        IVIDTRANSCODE_DynamicParams *params, IVIDTRANSCODE_Status *status);

} IVIDTRANSCODE_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDTRANSCODE_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

