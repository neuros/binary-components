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
 *  @file       /ti/xdais/dm/ivideo.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across the various video codecs.
 */
/**
 *  @addtogroup   ti_xdais_dm_IVIDEO    xDM 1.00 Video Interface
 *
 *  This is the xDM 1.00 video interface shared between the various codecs.
 */

#ifndef ti_xdais_dm_IVIDEO_
#define ti_xdais_dm_IVIDEO_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDEO */
/*@{*/

/**
 *  @brief      Video frame skip features for video decoder.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_NO_SKIP = 0,     /**< Do not skip any frame types. */
    IVIDEO_SKIP_P = 1,      /**< Decode the P frame/skip frames internally,
                             *   but do not copy the decoded output to the
                             *   output buffers.  This should be indicated
                             *   by setting the output buffers to NULL.
                             *
                             *   @remarks       For example, if a B frame is
                             *                  dependant on the
                             *                  previously decoded P
                             *                  frame, the B frame
                             *                  shall be decoded and
                             *                  displayed
                             *                  successfully.  For
                             *                  this, the P frame
                             *                  needs to be decoded,
                             *                  but not copied to the
                             *                  output buffer.
                             */
    IVIDEO_SKIP_B = 2,      /**< Skip B, BI frames.  For B frames, the
                             *   decoder will decode the frame
                             *   bitstream, and return as soon as the
                             *   frame type is decisively decoded.
                             *   Internally, the algorithm will modify
                             *   its state, so that subsequent
                             *   decoding of other frames is possible.
                             */
    IVIDEO_SKIP_I = 3,      /**< Skip intra coded frame. */
    IVIDEO_SKIP_IP = 4,     /**< Skip I and P frame/field(s). */
    IVIDEO_SKIP_IB = 5,     /**< Skip I and B frame/field(s). */
    IVIDEO_SKIP_PB = 6,     /**< Skip P and B frame/field(s). */
    IVIDEO_SKIP_IPB = 7,    /**< Skip I/P/B/BI frames. */
    IVIDEO_SKIP_IDR = 8,    /**< Skip IDR Frame. */

    /** Default settings. */
    IVIDEO_SKIP_DEFAULT = IVIDEO_NO_SKIP
} IVIDEO_FrameSkip;

/**
 *  @brief      Video frame types.
 *
 *  @remarks    For the various @c IVIDEO_xy_FRAME values, this frame type is
 *              interlaced where both top and bottom fields are
 *              provided in a single frame.  The first field is an "x"
 *              frame, the second field is "y" field.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_NA_FRAME = -1,   /**< Frame type not available. */
    IVIDEO_I_FRAME = 0,     /**< Intra coded frame. */
    IVIDEO_P_FRAME = 1,     /**< Forward inter coded frame. */
    IVIDEO_B_FRAME = 2,     /**< Bi-directional inter coded frame. */
    IVIDEO_IDR_FRAME = 3,   /**< Intra coded frame that can be used for
                             *   refreshing video content.
                             */
    IVIDEO_II_FRAME = 4,    /**< Interlaced Frame, both fields are I frames */
    IVIDEO_IP_FRAME = 5,    /**< Interlaced Frame, first field is an I frame,
                             *   second field is a P frame.
                             */
    IVIDEO_IB_FRAME = 6,    /**< Interlaced Frame, first field is an I frame,
                             *   second field is a B frame.
                             */
    IVIDEO_PI_FRAME = 7,    /**< Interlaced Frame, first field is a P frame,
                             *   second field is a I frame.
                             */
    IVIDEO_PP_FRAME = 8,    /**< Interlaced Frame, both fields are P frames. */
    IVIDEO_PB_FRAME = 9,    /**< Interlaced Frame, first field is a P frame,
                             *   second field is a B frame.
                             */
    IVIDEO_BI_FRAME = 10,   /**< Interlaced Frame, first field is a B frame,
                             *   second field is an I frame.
                             */
    IVIDEO_BP_FRAME = 11,   /**< Interlaced Frame, first field is a B frame,
                             *   second field is a P frame.
                             */
    IVIDEO_BB_FRAME = 12,   /**< Interlaced Frame, both fields are B frames. */
    IVIDEO_MBAFF_I_FRAME = 13,   /**< Intra coded MBAFF frame. */
    IVIDEO_MBAFF_P_FRAME = 14,   /**< Forward inter coded MBAFF frame. */
    IVIDEO_MBAFF_B_FRAME = 15,   /**< Bi-directional inter coded MBAFF frame.*/
    IVIDEO_MBAFF_IDR_FRAME = 16, /**< Intra coded MBAFF frame that can be used
                                  *   for refreshing video content.
                                  */
    /** Default setting. */
    IVIDEO_FRAMETYPE_DEFAULT = IVIDEO_I_FRAME
} IVIDEO_FrameType;

/**
 *  @brief      Video content types.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_CONTENTTYPE_NA = -1,/**< Frame type is not available. */
    IVIDEO_PROGRESSIVE = 0,    /**< Progressive frame. */
    IVIDEO_PROGRESSIVE_FRAME = IVIDEO_PROGRESSIVE, /**< Progressive Frame. */
    IVIDEO_INTERLACED = 1,     /**< Interlaced frame. */
    IVIDEO_INTERLACED_FRAME = IVIDEO_INTERLACED,   /**< Interlaced frame. */
    IVIDEO_INTERLACED_TOPFIELD = 2,    /**< Interlaced picture, top field. */
    IVIDEO_INTERLACED_BOTTOMFIELD = 3, /**< Interlaced picture, bottom field. */

    /**Default setting. */
    IVIDEO_CONTENTTYPE_DEFAULT = IVIDEO_PROGRESSIVE
} IVIDEO_ContentType;


/**
 *  @brief      Video rate control presets.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_LOW_DELAY = 1,   /**< CBR rate control for video conferencing. */
    IVIDEO_STORAGE = 2,     /**< VBR rate control for local storage (DVD)
                             *   recording.
                             */
    IVIDEO_TWOPASS = 3,     /**< Two pass rate control for non real time
                             *   applications.
                             */
    IVIDEO_NONE = 4,        /**< No configurable video rate control
                              *  mechanism.
                              */
    IVIDEO_USER_DEFINED = 5,/**< User defined configuration using extended
                             *   parameters.
                             */

    /** Default setting. */
    IVIDEO_RATECONTROLPRESET_DEFAULT = IVIDEO_LOW_DELAY
} IVIDEO_RateControlPreset;


/**
 *  @brief      Video frame skipping modes.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_FRAME_ENCODED = 0,   /**< Input video frame successfully encoded. */
    IVIDEO_FRAME_SKIPPED = 1,   /**< Input video frame dropped.  There is no
                                 *   encoded bitstream corresponding to the
                                 *   input frame.
                                 */

    /** Default setting. */
    IVIDEO_SKIPMODE_DEFAULT = IVIDEO_FRAME_ENCODED
} IVIDEO_SkipMode;


/**
 *  @brief      Video output buffer status.
 *
 *  @remarks    Ownership of the buffers, either by application or algorithm,
 *              is conveyed via these values.
 *
 *  @remarks    This reflects the status of ALL output buffers.  For example,
 *              if video decoded output is in 4:2:0 format, all the 3
 *              output buffers' status is described by this value.
 *              Similarly, for 4:2:2 formatted buffers, this value
 *              describes the single buffer's status.
 *
 *  @enumWarning
 */
typedef enum {
    IVIDEO_FRAME_NOERROR = 0,   /**< The output buffer is available.
                                 */
    IVIDEO_FRAME_NOTAVAILABLE = 1, /**< The codec doesn't have any output
                                 *   buffers.
                                 */
    IVIDEO_FRAME_ERROR = 2,     /**< The output buffer is available and
                                 *   corrupted.
                                 *
                                 *   @remarks   For example, if a bitstream
                                 *              is erroneous and
                                 *              partially decoded, a
                                 *              portion of the decoded
                                 *              image may be available
                                 *              for display.  Another
                                 *              example is if the
                                 *              bitstream for a given
                                 *              frame decode may be
                                 *              decoded without error,
                                 *              but the previously
                                 *              decoded dependant
                                 *              frames weren't
                                 *              successfully decoded.
                                 *              This would result in
                                 *              an incorrectly decoded
                                 *              frame.
                                 */

    /** Default setting. */
    IVIDEO_OUTPUTFRAMESTATUS_DEFAULT = IVIDEO_FRAME_NOERROR
} IVIDEO_OutputFrameStatus;

/**
 *  @brief      Video Picture types.
 *
 */
typedef enum {
    IVIDEO_NA_PICTURE = -1,   /**< Frame type not available. */
    IVIDEO_I_PICTURE = 0,     /**< Intra coded picture. */
    IVIDEO_P_PICTURE = 1,     /**< Forward inter coded picture. */
    IVIDEO_B_PICTURE = 2,     /**< Bi-directional inter coded picture. */
    /** Default setting. */
    IVIDEO_PICTURE_TYPE_DEFAULT = IVIDEO_I_PICTURE
} IVIDEO_PictureType;


/**
 *  @brief      Video Format types.
 */
typedef enum {
    IVIDEO_MPEG1 = 1,       /**< Video format is Mpeg1 stream */
    IVIDEO_MPEG2SP = 2,     /**< Video format is Mpeg2 stream, Simple Profile */
    IVIDEO_MPEG2MP = 3,     /**< Video format is Mpeg2 stream, Main Profile */
    IVIDEO_MPEG2HP = 4,     /**< Video format is Mpeg2 stream, High Profile */
    IVIDEO_MPEG4SP = 5,     /**< Video format is Mpeg4 stream, Simple Profile */
    IVIDEO_MPEG4ASP = 6,    /**< Video format is Mpeg4 stream, Advanced Simple Profile */
    IVIDEO_H264BP = 7,      /**< Video format is H.264 stream, Base Profile */
    IVIDEO_H264MP = 8,      /**< Video format is H.264 stream, Main Profile */
    IVIDEO_H264HP = 9,      /**< Video format is H.264 stream, High Profile */
    IVIDEO_VC1SP = 10,      /**< Video format is VC1 stream, Simple Profile */
    IVIDEO_VC1MP = 11,      /**< Video format is VC1 stream, Main Profile */
    IVIDEO_VC1AP = 12       /**< Video format is VC1 stream, Advanced Profile */
} IVIDEO_Format;


/**
 *  @brief      Buffer descriptor for video buffers.
 */
typedef struct IVIDEO_BufDesc {
    XDAS_Int32  numBufs;    /**< Number of buffers. */
    XDAS_Int32  width;      /**< Added width of a video frame. */
    XDAS_Int8  *bufs[XDM_MAX_IO_BUFFERS];  /**< Pointer to vector
                                            *   containing buffer addresses.
                                            */
    XDAS_Int32  bufSizes[XDM_MAX_IO_BUFFERS]; /**< Size of each buffer
                                            *   in 8-bit bytes.
                                            */

} IVIDEO_BufDesc;

/**
 *  @brief      Buffer descriptor for input video buffers.
 */

typedef struct IVIDEO1_BufDescIn {
    XDAS_Int32  numBufs;        /**< Number of buffers in bufDesc[]. */
    XDAS_Int32  frameWidth;     /**< Width of the video frame. */
    XDAS_Int32  frameHeight;    /**< Height of the video frame. */
    XDAS_Int32  framePitch;     /**< Frame pitch used to store the frame.
                                 *
                                 *   @remarks   This field can also be used to
                                 *              indicate the padded width.
                                 */
    XDM1_SingleBufDesc bufDesc[XDM_MAX_IO_BUFFERS]; /**< Picture buffers. */
} IVIDEO1_BufDescIn;


/**
 *  @brief      Max YUV buffers - one each for 'Y', 'U', and 'V'.
 */
#define IVIDEO_MAX_YUV_BUFFERS  3

/**
 *  @brief      Detailed buffer descriptor for video buffers.
 */
typedef struct IVIDEO1_BufDesc {
    XDAS_Int32  numBufs;        /**< Number of buffers in bufDesc[]. */
    XDAS_Int32  frameWidth;     /**< Width of the video frame. */
    XDAS_Int32  frameHeight;    /**< Height of the video frame. */
    XDAS_Int32  framePitch;     /**< Frame pitch used to store the frame.
                                 *
                                 *   @remarks   This field can also be used to
                                 *              indicate the padded width.
                                 */
    XDM1_SingleBufDesc bufDesc[IVIDEO_MAX_YUV_BUFFERS]; /**< Picture buffers. */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 frameType;       /**< @copydoc IVIDEO_FrameType
                                 *
                                 *   @sa IVIDEO_FrameType
                                 */
    XDAS_Int32 topFieldFirstFlag;/**< Flag to indicate when the application
                                 *   should display the top field first.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @remarks   This field is only applicable
                                 *              for interlaced content, not
                                 *              progressive.
                                 *
                                 *   @remarks   This field does not apply to
                                 *              encoder recon bufs.
                                 */
    XDAS_Int32 repeatFirstFieldFlag;/**< Flag to indicate when the first field
                                 *   should be repeated.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @remarks   This field is only applicable
                                 *              for interlaced content, not
                                 *              progressive.
                                 *
                                 *   @remarks   This field does not apply to
                                 *              encoder recon bufs.
                                 */
    XDAS_Int32 frameStatus;     /**< @copydoc  IVIDEO_OutputFrameStatus
                                 *
                                 *   @sa IVIDEO_OutputFrameStatus
                                 *
                                 *   @remarks   This field does not apply to
                                 *              encoder recon bufs.
                                 */
    XDAS_Int32 repeatFrame;     /**< Number of times the display process
                                 *   needs to repeat the displayed progressive
                                 *   frame.
                                 *
                                 *   @remarks   This information is useful
                                 *              for progressive
                                 *              content when the
                                 *              decoder expects the
                                 *              display process to
                                 *              repeat the displayed
                                 *              frame for a certain
                                 *              number of times. This
                                 *              is useful for pulldown
                                 *              (frame/field
                                 *              repetition by display
                                 *              system) support
                                 *              where the display
                                 *              frame rate is
                                 *              increased without
                                 *              increasing the decode
                                 *              frame rate.
                                 *
                                 *   @remarks   The default value is 0.
                                 *
                                 *   @remarks   This field does not apply to
                                 *              encoder recon bufs.
                                 */
    XDAS_Int32 contentType;     /**< Content type of the buffer.
                                 *
                                 *   @remarks   This is useful when the
                                 *              content is both
                                 *              interlaced and
                                 *              progressive.  The
                                 *              display process can
                                 *              use this field to
                                 *              determine how to
                                 *              render the display
                                 *              buffer.
                                 *
                                 *   @sa        IVIDEO_ContentType
                                 */
    XDAS_Int32 chromaFormat;    /**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
} IVIDEO1_BufDesc;


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDEO_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

