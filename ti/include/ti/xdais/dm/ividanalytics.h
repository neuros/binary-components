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
 *  @file       ti/xdais/dm/ividanalytics.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video analytics
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDANALYTICS  xDM Beta Video Analytics Interface
 *
 *  This is the xDM Beta Video Analytics Interface.
 */

#ifndef ti_xdais_dm_IVIDANALYTICS_
#define ti_xdais_dm_IVIDANALYTICS_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDANALYTICS */
/*@{*/

#define IVIDANALYTICS_EOK       XDM_EOK        /**< @copydoc XDM_EOK */
#define IVIDANALYTICS_EFAIL     XDM_EFAIL      /**< @copydoc XDM_EFAIL */
#define IVIDANALYTICS_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IVIDANALYTICS
 *              instance objects.
 */
typedef struct IVIDANALYTICS_Obj {
    struct IVIDANALYTICS_Fxns *fxns;
} IVIDANALYTICS_Obj;


/**
 *  @brief      Opaque handle to an IVIDANALYTICS objects.
 */
typedef struct IVIDANALYTICS_Obj  *IVIDANALYTICS_Handle;


/**
 *  @brief      View status of the analytics engine.
 *
 *  @enumWarning
 *
 *  @todo       Should this be left undefined and viewState left algorithm
 *              specific?   See speech APIs for an example of how we might
 *              create 'classes' of a given type of algorithm.
 *
 *  @sa IVIDANALYTICS_OutArgs::viewState
 *  @sa IVIDANALYTICS_Status::viewState
 */
typedef enum {
    IVIDANALYTICS_BADSIGNAL = 0,/**< Bad signal.
                                 *
                                 *   @todo      Need to document this.
                                 */
    IVIDANALYTICS_UNKNOWNVIEW = 1,/**< Unknown view.
                                 *
                                 *   @todo      Need to document this.
                                 */
    IVIDANALYTICS_GOOD = 2,     /**< Good, known view.
                                 *
                                 *   @todo      Need to document this.
                                 */
    IVIDANALYTICS_INVALIDVIEW = 3,/**< Invalid view.
                                 *
                                 *   @todo      Need to document this.
                                 */
    IVIDANALYTICS_SEARCHING = 4 /**< Searching for Good view.
                                 *
                                 *   @todo      Need to document this.
                                 */
} IVIDANALYTICS_ViewState;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDANALYTICS instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDANALYTICS_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 inputChromaFormat;/**< Chroma format for the input buffer.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDAS_Int32 maxViews;         /**<  Maximum views available for analysis. */
    XDAS_Int32 maxRulesPerView;  /**<  Maximum rules allowed per view. */

}IVIDANALYTICS_Params;


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
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef struct IVIDANALYTICS_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 inputHeight;     /**< Input frame height. */
    XDAS_Int32 inputWidth;      /**< Input frame width. */
} IVIDANALYTICS_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDANALYTICS instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDANALYTICS_Fxns::process()
 */
typedef struct IVIDANALYTICS_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
}IVIDANALYTICS_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef struct IVIDANALYTICS_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_BufDesc data;          /**< Buffer descriptors for data passing.
                                 *
                                 *   @remarks   If this field is not used,
                                 *              the application <b>must</b>
                                 *              set @c data.numBufs to 0.
                                 *
                                 *   @remarks   These buffers can be used as
                                 *              either input or output,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffers will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the
                                 *              IVIDANALYTICS_Fxns.control()
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
                                 *   @sa        IVIDANALYTICS_Params
                                 *   @sa        XDM_AlgBufInfo
                                 *   @sa        IVIDANALYTICS_Fxns::control()
                                 */
    XDAS_Int32 viewState;       /**< @copydoc IVIDANALYTICS_ViewState
                                 *
                                 *   @sa IVIDANALYTICS_ViewState
                                 */
} IVIDANALYTICS_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDANALYTICS instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC1_Fxns::process()
 */
typedef struct IVIDANALYTICS_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 viewState;       /**< @copydoc IVIDANALYTICS_ViewState
                                 *
                                 *   @sa IVIDANALYTICS_ViewState
                                 */
} IVIDANALYTICS_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDANALYTICS module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDANALYTICS_Fxns::control()
 */
typedef  IALG_Cmd IVIDANALYTICS_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDANALYTICS objects.
 */
typedef struct IVIDANALYTICS_Fxns {
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
 *              buffers supplied for input frame.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDANALYTICS_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDANALYTICS_OutArgs structure.
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
 *  @post       The buffers in @c inBufs and @c outBufs are owned by the
 *              calling application.
 *
 *  @retval     IVIDANALYTICS_EOK       @copydoc IVIDANALYTICS_EOK
 *  @retval     IVIDANALYTICS_EFAIL     @copydoc IVIDANALYTICS_EFAIL
 *                                      See IVIDANALYTICS_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDANALYTICS_EUNSUPPORTED   @copydoc IVIDANALYTICS_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs,
        XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
        IVIDANALYTICS_OutArgs *outArgs);


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
 *              IVIDANALYTICS_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDANALYTICS_Status structure.
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
 *  @retval     IVIDANALYTICS_EOK       @copydoc IVIDANALYTICS_EOK
 *  @retval     IVIDANALYTICS_EFAIL     @copydoc IVIDANALYTICS_EFAIL
 *                                      See IVIDANALYTICS_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDANALYTICS_EUNSUPPORTED   @copydoc IVIDANALYTICS_EUNSUPPORTED
 */
    XDAS_Int32   (*control)(IVIDANALYTICS_Handle handle, IVIDANALYTICS_Cmd id,
            IVIDANALYTICS_DynamicParams *params, IVIDANALYTICS_Status *status);

} IVIDANALYTICS_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_IVIDANALYTICS_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

