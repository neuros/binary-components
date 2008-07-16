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
 *  @file       ti/xdais/dm/ividdec2.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDDEC2   xDM 1.20 Video Decoder Interface
 *
 *  This is the xDM 1.20 Video Decoder Interface.
 */

#ifndef ti_xdais_dm_IVIDDEC2_
#define ti_xdais_dm_IVIDDEC2_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif


#define IVIDDEC2_MAX_IO_BUFFERS                20
/** @ingroup    ti_xdais_dm_IVIDDEC2 */
/*@{*/

#define IVIDDEC2_EOK       XDM_EOK             /**< @copydoc XDM_EOK */
#define IVIDDEC2_EFAIL     XDM_EFAIL           /**< @copydoc XDM_EFAIL */
#define IVIDDEC2_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IVIDDEC2
 *              instance objects.
 */
typedef struct IVIDDEC2_Obj {
    struct IVIDDEC2_Fxns *fxns;
} IVIDDEC2_Obj;


/**
 *  @brief      Opaque handle to an IVIDDEC2 objects.
 */
typedef struct IVIDDEC2_Obj  *IVIDDEC2_Handle;


/**
 *  @brief      Video decoder output frame order.
 *
 *  @enumWarning
 *
 *  @sa IVIDDEC2_DynamicParams::frameOrder
 */
typedef enum {
    IVIDDEC2_DISPLAY_ORDER = 0, /**< The decoder provides decoded output in
                                 *   in the actual order of displaying the
                                 *   output buffer.  The codec assumes the
                                 *   responsibility of reordering the frames.
                                 *
                                 *   @remarks   The output buffer will be
                                 *              delayed by one frame,
                                 *              regardless of whether the frame
                                 *              contains I/P or I/P/B frames.
                                 *
                                 *   @remarks   This is the default mode.
                                 *
                                 *   @remarks   This mode is required to be
                                 *              supported by all video decoder
                                 *              codecs.
                                 */
    IVIDDEC2_DECODE_ORDER = 1,  /**< The decoder provides decoded output in the
                                 *   the order of decoding.  There will be no
                                 *   delay in the output buffers.
                                 *
                                 *   @remarks   It is the application's
                                 *              responsibility to handle the
                                 *              frame re-ordering.
                                 *
                                 *   @remarks   This mode is optional.  If it
                                 *              is not supported by the
                                 *              decoder, IVIDDEC_EUNSUPPORTED
                                 *              will be returned.
                                 */

    /** Default setting. */
    IVIDDEC2_FRAMEORDER_DEFAULT = IVIDDEC2_DISPLAY_ORDER
} IVIDDEC2_FrameOrder;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDDEC2 instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDDEC2_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 maxBitRate;      /**< Maximum bit rate, bits per second.
                                 *   For example, if bit rate is 10 Mbps, set
                                 *   this field to 10000000
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 forceChromaFormat;/**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa    XDM_ChromaFormat
                                 */
} IVIDDEC2_Params;


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
 *  @sa         IVIDDEC2_Fxns::control()
 */
typedef struct IVIDDEC2_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 decodeHeader;    /**< @copydoc XDM_DecMode
                                 *
                                 *   @sa XDM_DecMode
                                 */
    XDAS_Int32 displayWidth;    /**< Pitch.  If set to zero, use the decoded
                                 *   image width.  Else, use given display
                                 *   width in pixels.
                                 */
    XDAS_Int32 frameSkipMode;   /**< @copydoc IVIDEO_FrameSkip
                                 *
                                 *   @sa IVIDEO_FrameSkip
                                 */
    XDAS_Int32 frameOrder;      /**< @copydoc IVIDDEC2_FrameOrder
                                 *
                                 *   @sa IVIDDEC2_FrameOrder
                                 */
    XDAS_Int32 newFrameFlag;    /**< Flag to indicate that the algorithm should
                                 *   start a new frame.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @remarks   This is useful for error
                                 *              recovery, for example when the
                                 *              end of frame cannot be detected
                                 *              by the codec but is known to the
                                 *              application.
                                 */
    XDAS_Int32 mbDataFlag;      /**< Flag to indicate that the algorithm should
                                 *   generate MB Data in addition to decoding
                                 *   the data.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @sa IVIDDEC2_OutArgs::mbDataBuf
                                 */
} IVIDDEC2_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDDEC2 instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC2_Fxns::process()
 */
typedef struct IVIDDEC2_InArgs {
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
                                 *   IVIDDEC2_OutArgs#outputID will be same
                                 *   as this inputID field.
                                 *
                                 *   @remarks   Zero (0) is not a supported
                                 *              inputID.  This value is
                                 *              reserved for cases when there
                                 *              is no output buffer provided in
                                 *              IVIDDEC2_OutArgs::displayBufs.
                                 *
                                 *   @sa IVIDDEC2_OutArgs::outputID.
                                 */
} IVIDDEC2_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @remarks    All fields correspond to latest IVIDDEC2_Fxns::process() call
 *              on the particular instance of the decoder.
 *
 *  @sa         IVIDDEC2_Fxns::control()
 */
typedef struct IVIDDEC2_Status {
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
                                 *              IVIDDEC2_Fxns.control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
    XDAS_Int32 maxNumDisplayBufs; /**< The maximum number of buffers that will
                                 *   be required by the codec.
                                 *
                                 *   @remarks   The maximum number of buffers
                                 *              can be IVIDDEC2_MAX_IO_BUFFERS.
                                 */
    XDAS_Int32 outputHeight;    /**< Output height in pixels. */
    XDAS_Int32 outputWidth;     /**< Output width in pixels. */
    XDAS_Int32 frameRate;       /**< Average frame rate in fps * 1000.
                                 *   For example, if average frame rate is 30
                                 *   frames per second, this field should be
                                 *   30000.
                                 */
    XDAS_Int32 bitRate;         /**< Average bit rate, in bits per second. */
    XDAS_Int32 contentType;     /**< @copydoc IVIDEO_ContentType
                                 *
                                 *   @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 outputChromaFormat; /**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
} IVIDDEC2_Status;



/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDDEC2 instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC2_Fxns::process()
 */
typedef struct IVIDDEC2_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 bytesConsumed;   /**< Number of bytes consumed during the
                                 *   process() call.
                                 */
 
    XDAS_Int32 outputID[IVIDDEC2_MAX_IO_BUFFERS]; /**< Output ID corresponding
                                 *   to displayBufs[].
                                 *
                                 *   @remarks   A value of zero (0) indicates
                                 *              an invalid ID.  The first zero
                                 *              entry in array will indicate
                                 *              end of valid outputIDs within
                                 *              the array.  Hence the
                                 *              application can stop reading the
                                 *              array when it encounters the
                                 *              first zero entry.
                                 *
                                 *   @sa IVIDDEC2_InArgs#inputID
                                 */
    IVIDEO1_BufDesc decodedBufs; /**< The decoder fills this structure with
                                 *   buffer pointers to the decoded frame.
                                 *   Related information fields for the
                                 *   decoded frame are also populated.
                                 *
                                 *   When frame decoding is not complete, as
                                 *   indicated by @c outBufsInUseFlag,
                                 *   the frame data in this structure will be
                                 *   incomplete.  However, the algorithm will
                                 *   provide incomplete decoded frame data
                                 *   in case application may choose to use
                                 *   it for error recovery purposes.
                                 */
    IVIDEO1_BufDesc displayBufs[IVIDDEC2_MAX_IO_BUFFERS]; /**< Array
                                 *   containing display frames
                                 *   corresponding to valid ID entries
                                 *   in the @c outputID[] array.
                                 *
                                 *   @remarks   Entries in the array
                                 *              corresponding to invalid
                                 *              ID values (zero) in
                                 *              @c outputID[ ] will set
                                 *              zero value for the following
                                 *              fields in the IVIDEO1_BufDesc
                                 *              structure:  @c numBufs,
                                 *              @c frameWidth, @c frameHeight,
                                 *              and @c framePitch.
                                 */
    XDAS_Int32 outputMbDataID;  /**< Output ID corresponding with the MB Data
                                 *
                                 *   @remarks   This will be set to zero when
                                 *              there is no MB Data Buffer
                                 */
    XDM1_SingleBufDesc mbDataBuf; /**< The decoder populates the last buffer
                                 *   among the buffers supplied within
                                 *   outBufs->bufs[] with the decoded MB data
                                 *   generated by the ECD module. The pointer
                                 *   buffer along with the buffer size is
                                 *   output via this buffer descriptor.
                                 */
    XDAS_Int32 freeBufID[IVIDDEC2_MAX_IO_BUFFERS]; /**< This is an
                                 *   array of inputID's corresponding to the
                                 *   frames that have been unlocked in the
                                 *   current process call.
                                 *
                                 *   @remarks   Default value of all array
                                 *              elements is zero.
                                 *              A value other than zero indicates
                                 *              the value of the inputID
                                 *              corresponding to the un-locked
                                 *              buffer
                                 *
                                 *   @remarks   If no buffer was unlocked in
                                 *              the process call, all array
                                 *              elements will have a value of
                                 *              zero.
                                 */
    XDAS_Int32 outBufsInUseFlag; /**< Flag to indicate that the @c outBufs
                                 *   provided with the process() call are in
                                 *   use.  No outBufs are required to be
                                 *   supplied with the next process() call.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 */

} IVIDDEC2_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDDEC2 module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDDEC2_Fxns::control()
 */
typedef  IALG_Cmd IVIDDEC2_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDDEC2 objects.
 */
typedef struct IVIDDEC2_Fxns {
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
 *  @pre        @c inBufs->numBufs will indicate the total number of input
 *              buffers supplied for input frame, and conditionally, the
 *              encoders MB data buffer.
 *
 *  @pre        If IVIDDEC2_DynamicParams::mbDataFlag was set to #XDAS_FALSE
 *              in a previous control() call, the application only needs to
 *              provide buffers for reconstruction frames.
 *
 *  @pre        If IVIDDEC2_DynamicParams::mbDataFlag was set to #XDAS_TRUE
 *              in a previous control() call,
 *              @c outBufs->bufs[outBufs->numBufs - 1] is a buffer descriptor
 *              into which the algorithm will write MB data for each macro
 *              block.  The size of the MB data buffer will vary based on the
 *              decoder type.  H.264 may generate N264 bytes per MB, while
 *              Mpeg2 may generate NMP2 bytes.  The exact size of the buffers
 *              should be obtained by calling the algorithm's control() method
 *              with XDM_GETBUFINFO.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDDEC2_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDDEC2_OutArgs structure.
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
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
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
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDDEC2_Handle handle, XDM1_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs,
        IVIDDEC2_OutArgs *outArgs);


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
 *              IVIDDEC2_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDDEC2_Status structure.
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
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDDEC2_Handle handle, IVIDDEC2_Cmd id,
        IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status);

} IVIDDEC2_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDDEC2_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

