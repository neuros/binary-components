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
 *  @file       ti/xdais/dm/ividenc1.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video encoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDENC1   xDM 1.00 Video Encoder Interface
 *
 *  This is the xDM 1.00 Video Encoder Interface.
 */

#ifndef ti_xdais_dm_IVIDENC1_
#define ti_xdais_dm_IVIDENC1_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDENC1 */
/*@{*/

#define IVIDENC1_EOK       XDM_EOK             /**< @copydoc XDM_EOK */
#define IVIDENC1_EFAIL     XDM_EFAIL           /**< @copydoc XDM_EFAIL */
#define IVIDENC1_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IVIDENC1
 *              instance objects.
 */
typedef struct IVIDENC1_Obj {
    struct IVIDENC1_Fxns *fxns;
} IVIDENC1_Obj;


/**
 *  @brief      Opaque handle to an IVIDENC1 objects.
 */
typedef struct IVIDENC1_Obj  *IVIDENC1_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDENC1 instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDENC1_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 encodingPreset;  /**< Encoding preset. */
    XDAS_Int32 rateControlPreset;/**< @copydoc IVIDEO_RateControlPreset
                                 *
                                 *   @sa IVIDEO_RateControlPreset
                                 */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 maxBitRate;      /**< Maximum bit rate, bits per second. */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 maxInterFrameInterval;/**< I to P frame distance. e.g. = 1 if
                                 *   no B frames, 2 to insert one B frame.
                                 *
                                 *   @remarks   This is used for setting the
                                 *              maximum number of B frames
                                 *              between two refererence frames.
                                 */
    XDAS_Int32 inputChromaFormat;/**< Chroma format for the input buffer.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDAS_Int32 inputContentType;/**< Video content type of the buffer being
                                 *   encoded.
                                 *
                                 *   @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 reconChromaFormat;/**< Chroma formats for the reconstruction
                                 *   buffers.
                                 *
                                 *   @remarks   The application should set
                                 *              this to #XDM_CHROMA_NA
                                 *              if reconstruction
                                 *              buffers are not
                                 *              required.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
} IVIDENC1_Params;


/**
 *  @brief      This structure defines the algorithm parameters that can be
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
 *  @sa         IVIDENC1_Fxns::control()
 */
typedef struct IVIDENC1_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 inputHeight;     /**< Input frame height. */
    XDAS_Int32 inputWidth;      /**< Input frame width. */
    XDAS_Int32 refFrameRate;    /**< Reference, or input, frame rate in
                                 *   fps * 1000.
                                 *
                                 *   @remarks   For example, if ref frame
                                 *              rate is 30 frames per second,
                                 *              this field will be 30000.
                                 */
    XDAS_Int32 targetFrameRate; /**< Target frame rate in
                                 *   fps * 1000.
                                 *
                                 *   @remarks   For example, if target frame
                                 *              rate is 30 frames per second,
                                 *              this field will be 30000.
                                 */
    XDAS_Int32 targetBitRate;   /**< Target bit rate in bits per second. */
    XDAS_Int32 intraFrameInterval;/**< The number of frames between two I
                                 *    frames.  For example, 30.
                                 *
                                 *    @remarks  For example, this field will be:
                                 *      - 0 - Only first frame to be intra
                                 *        coded.  e.g. IPPPPPP...
                                 *      - 1 - No inter frames (all intra
                                 *        frames).
                                 *      - 2 - Consecutive IPIPIP... sequence (if
                                 *        no B frames).
                                 *      - 3 - IPPIPP... or IPBIPBI... and so on.
                                 */
    XDAS_Int32 generateHeader;  /**< @copydoc XDM_EncMode
                                 *
                                 *   @sa XDM_EncMode
                                 */
    XDAS_Int32 captureWidth;    /**< DEFAULT(0): use imagewidth as
                                 *   pitch else use given capture
                                 *   width for pitch provided it
                                 *   is greater than image width.
                                 */
    XDAS_Int32 forceFrame;      /**< Force the current (immediate) frame to be
                                 *   encoded as a specific frame type.
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
                                 */
    XDAS_Int32 interFrameInterval;/**< Number of B frames between two reference
                                 *   frames; that is, the number of B frames
                                 *   between two P frames or I/P frames.
                                 *   DEFAULT(0).
                                 *
                                 *   @remarks   For example, this field will be:
                                 *     - 0 - to use maxInterFrameInterval.
                                 *     - 1 - 0 B frames between two reference
                                 *       frames.
                                 *     - 2 - 1 B frame between two reference
                                 *       frames.
                                 *     - 3 - 2 B frames between two reference
                                 *       frames.
                                 *     - and so on...
                                 *
                                 *   @sa IVIDENC1_Params.maxInterFrameInterval.
                                 */
    XDAS_Int32 mbDataFlag;      /**< Flag to indicate that the algorithm should
                                 *   use MB data supplied in additional buffer
                                 *   within inBufs.
                                 */
} IVIDENC1_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDENC1 instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC1_Fxns::process()
 */
typedef struct IVIDENC1_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 inputID;         /**< Identifier to attach with the corresponding
                                 *   encoded bitstream frames.
                                 *
                                 *   @remarks   This is useful when frames
                                 *              require buffering (e.g.
                                 *              B frames), and to support
                                 *              buffer management.
                                 *
                                 *   @remarks   When there is no re-ordering,
                                 *              IVIDENC1_OutArgs::outputID will
                                 *              be the same as this inputID
                                 *              field.
                                 *
                                 *   @remarks   Zero (0) is <b>not</b> a
                                 *              supported inputID.  This value
                                 *              is reserved for cases when
                                 *              there is no output buffer
                                 *              provided.
                                 *
                                 *   @sa IVIDENC1_OutArgs::outputID.
                                 */
    XDAS_Int32 topFieldFirstFlag;/**< Flag to indicate the field order in
                                 *    interlaced content.
                                 *
                                 *    @remarks  Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *    @remarks  This field is only applicable
                                 *              to the input image buffer.
                                 *
                                 *    @remarks  This field is only applicable
                                 *              for interlaced content, not
                                 *              progressive.
                                 */
} IVIDENC1_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC1_Fxns::control()
 */
typedef struct IVIDENC1_Status {
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
                                 *              IVIDENC1_Fxns.control()
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
                                 *   @remarks   When configured to generate
                                 *              reconstruction buffers (see
                                 *      IVIDENC1_Params::reconChromaFormat),
                                 *              the recontruction buffer
                                 *              information will also be
                                 *              reported here.
                                 *
                                 *   @sa        IVIDENC1_Params
                                 *   @sa        XDM_AlgBufInfo
                                 *   @sa        IVIDENC1_Fxns::process()
                                 */
} IVIDENC1_Status;


/**
 *  @brief      Defines the run time output arguments for all IVIDENC1
 *              instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC1_Fxns::process()
 */
typedef struct IVIDENC1_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesGenerated;  /**< Number of bytes generated during the
                                 *   IVIDENC1_Fxns::process() call.
                                 */
    XDAS_Int32 encodedFrameType;/**< @copydoc IVIDEO_FrameType
                                 *
                                 *   @sa IVIDEO_FrameType
                                 */
    XDAS_Int32 inputFrameSkip;  /**< @copydoc IVIDEO_SkipMode
                                 *
                                 *   @sa IVIDEO_SkipMode
                                 */
    XDAS_Int32 outputID;        /**< Output ID corresponding with the encoded
                                 *   buffer. This shall also be used to free
                                 *   up the corresponding image buffer for
                                 *   further use by client application code.
                                 *
                                 *   @remarks   This will be set to zero when
                                 *              there is no encoded buffer for
                                 *              passing to client application.
                                 *
                                 *   @sa IVIDENC1_InArgs::inputID.
                                 */
   XDM1_SingleBufDesc encodedBuf;/**< The encoder fills the buffer with the
                                 *   encoded bitstream.  In case of sequences
                                 *   having I & P frames only, these
                                 *   values are identical to @c outBufs
                                 *   passed in IVIDENC1_Fxns::process().
                                 *
                                 *   @remarks   The @c encodedbuf.bufSize
                                 *              field returned
                                 *              corresponds to the
                                 *              actual valid bytes
                                 *              available in the
                                 *              buffer.
                                 *
                                 *   @remarks   The bitstream is in encoded
                                 *              order.
                                 *
                                 *   @remarks   @c outputID and @c encodedBuf
                                 *              together provide info relating
                                 *              to the corresponding encoded
                                 *              image buffer.
                                 */

    IVIDEO1_BufDesc reconBufs;  /**< Reconstruction frames.
                                 *
                                 *   @remarks   These output buffers
                                 *              correspond to
                                 *              @c outBufs->bufs[1],
                                 *              @c outBufs->bufs[2],
                                 *              and @c outBufs->bufs[3].
                                 *
                                 *   @remarks   @c reconBufs.bufDesc[0].buf is
                                 *              equivalent to
                                 *              @c outBufs->bufs[1],
                                 *              @c reconBufs.bufDesc[1].buf is
                                 *              equivalent to
                                 *              @c outBufs->bufs[2], and
                                 *              @c reconBufs.bufDesc[2].buf is
                                 *              equivalent to
                                 *              @c outBufs->bufs[3].
                                 */
} IVIDENC1_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDENC1 module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDENC1_Fxns::control()
 */
typedef  IALG_Cmd IVIDENC1_Cmd;


/**
 *  @brief      Defines the structure that contains macroblock related encoding
 *              parameter estimates.
 *
 *  @remarks    An array of IVIDENC1_MbData is provided within the @c inBufs
 *              parameter to IVIDENC1_Fxns::process()
 *              when IVIDENC1_DynamicParams::mbDataFlag is set.
 *
 *  @sa         IVIDENC1_DynamicParams::mbDataFlag
 *  @sa         IVIDENC1_Fxns::process()
 *  @sa         IVIDENC1_Fxns::control()
 */
typedef struct IVIDENC1_MbData {
    XDAS_Int32 mbMode;          /**< MB encoding mode
                                 *   @remarks   Valid values are:
                                 *      - 0x00 for skip macroblock
                                 *      - 0x01 for I Frame macroblock
                                 *      - 0x02 for P Frame macroblock
                                 *      - 0x03 for B Frame macroblock
                                 *      - 0x04 for I Field macroblock
                                 *      - 0x05 for P Field macroblock
                                 *      - 0x06 for B Field macroblock
                                 *      - 0xFF for mbMode not specified
                                 */
    XDAS_Int32 QP;              /**< QP estimate.
                                 *
                                 *   @remarks   A value of 0xFF for QP is
                                 *              not specified.
                                 */
    XDAS_Int32 mvFwdXY;         /**< Forward Motion vector estimate.
                                 *
                                 *   @remarks   If MVx (XDAS_Int16) and MVy
                                 *              (XDAS_Int16) are the motion
                                 *              vectors in the x and y
                                 *              directions, in quarter pel
                                 *              units, then
                                 *   @code
                                 *   mvFwdXY = ((MVx & 0x0000FFFF) << 16) |
                                 *              (MVy & 0x0000FFFF);
                                 *   @endcode
                                 *
                                 *   @remarks   A value of 0x7FFF7FFF to
                                 *              indicate mvFwdXY is not
                                 *              specified.
                                 */
    XDAS_Int32 mvBwdXY;         /**< Backward motion vector estimate.
                                 *
                                 *   @remarks   The format is the same as
                                 *              IVIDENC1_MbData::mvFwdXY.
                                 */
} IVIDENC1_MbData;


/**
 *  @brief      Defines all of the operations on IVIDENC1 objects.
 */
typedef struct IVIDENC1_Fxns {
    IALG_Fxns   ialg;             /**< xDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video encoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] inBufs       Input video buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.  The algorithm
 *                              may modify the output buffer pointers.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c inBufs->numBufs will indicate the total number of input
 *              buffers supplied for input frame, and conditionally, the
 *              encoders MB data buffer.
 *
 *  @pre        If IVIDENC1_DynamicParams::mbDataFlag was set to #XDAS_FALSE
 *              in a previous control() call, the application only needs to
 *              provide the input frame.
 *
 *  @pre        If IVIDENC1_DynamicParams::mbDataFlag was set to #XDAS_TRUE
 *              in a previous control() call,
 *              @c inBufs->bufs[inBufs->numBufs - 1] is a buffer descriptor
 *              containing stacked structures of the type IVIDENC1_MbData,
 *              one for each macro block.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDENC1_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDENC1_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              IVIDEO1_BufDescIn structure.
 *
 *  @pre        @c inBufs->bufDesc[0].bufs must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c inBufs->bufDesc[0].bufSize bytes in length.
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
 *  @post       The algorithm <b>must</b> appropriately set/clear the
 *              IVIDEO1_BufDescIn::bufDesc[].accessMask field in @c inBufs to
 *              indicate the mode in which each of the buffers in @c inBufs
 *              were read.
 *              For example, if the algorithm only read from
 *              @c inBufs.bufDesc[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs are
 *              owned by the calling application.
 *
 *  @remarks    @c outBufs->bufs[0] may contain the encoded data buffer.  See
 *              IVIDENC1_OutArgs.encodedBufs for more details.
 *
 *  @remarks    @c outBufs->bufs[1], @c outBufs->bufs[2], and
 *              @c outBufs->bufs[3] are used when providing reconstruction
 *              buffers.
 *
 *  @retval     IVIDENC1_EOK            @copydoc IVIDENC1_EOK
 *  @retval     IVIDENC1_EFAIL          @copydoc IVIDENC1_EFAIL
 *                                      See IVIDENC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDENC1_EUNSUPPORTED   @copydoc IVIDENC1_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs,
        XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs,
        IVIDENC1_OutArgs *outArgs);


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
 *              IVIDENC1_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDENC1_Status structure.
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
 *  @retval     IVIDENC1_EOK            @copydoc IVIDENC1_EOK
 *  @retval     IVIDENC1_EFAIL          @copydoc IVIDENC1_EFAIL
 *                                      See IVIDENC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDENC1_EUNSUPPORTED   @copydoc IVIDENC1_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDENC1_Handle handle, IVIDENC1_Cmd id,
        IVIDENC1_DynamicParams *params, IVIDENC1_Status *status);

} IVIDENC1_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDENC1_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

