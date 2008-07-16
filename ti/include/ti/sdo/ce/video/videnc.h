/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== videnc.h ========
 */
/**
 *  @file       ti/sdo/ce/video/videnc.h
 *
 *  @brief      The 0.9 Video Encoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 0.9 video encoder interface.
 */
/**
 *  @defgroup   VIDENC    0.9 Video Encoder Codec Interface
 *
 *  This is the 0.9 video encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef VIDENC_
#define VIDENC_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * By definition, this interface is 0.9 xDM.  Before including xdm.h,
 * define XDM_INCLUDE_DOT9_SUPPORT
 */
#ifndef XDM_INCLUDE_DOT9_SUPPORT
#define XDM_INCLUDE_DOT9_SUPPORT
#endif
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    VIDENC */
/*@{*/

/**
 *  @copydoc    IVIDENC_Status
 */
typedef IVIDENC_Status VIDENC_Status;

#define VIDENC_EOK      IVIDENC_EOK         /**< @copydoc IVIDENC_EOK */
#define VIDENC_EFAIL    IVIDENC_EFAIL       /**< @copydoc IVIDENC_EFAIL */
#define VIDENC_ERUNTIME IVIDENC_ERUNTIME    /**< @copydoc IVIDENC_ERUNTIME */

/**
 *  @brief      Opaque handle to a VIDENC codec.
 */
typedef VISA_Handle VIDENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Video Encoder object.
 */
typedef struct IVIDENC_Params VIDENC_Params;

/**
 * @copydoc IVIDENC_InArgs
 */
typedef IVIDENC_InArgs          VIDENC_InArgs;

/**
 * @copydoc IVIDENC_OutArgs
 */
typedef IVIDENC_OutArgs         VIDENC_OutArgs;

/**
 * @copydoc IVIDENC_Cmd
 */
typedef IVIDENC_Cmd             VIDENC_Cmd;

/**
 * @copydoc IVIDENC_DynamicParams
 */
typedef IVIDENC_DynamicParams   VIDENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDENC_SKEL;

/**
 *  @brief      Implementation of the IVIDENC interface that is run remotely.
 */
extern IVIDENC_Fxns VIDENC_STUBS;


/**
 *  @brief      Definition of IVIDENC codec class configurable parameters
 */
typedef struct IVIDENC_CodecClassConfig {
    Bool manageInBufsCache   [ XDM_MAX_IO_BUFFERS ];  
    Bool manageOutBufsCache  [ XDM_MAX_IO_BUFFERS ];  
    Bool manageReconBufsCache[ XDM_MAX_IO_BUFFERS ];  
} IVIDENC_CodecClassConfig;



/** @endcond */

/*
 *  ======== VIDENC_create ========
 */
/**
 *  @brief      Create an instance of a video encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDENC_create) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video encoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this call
 *              may create a local or remote instance of the video encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern VIDENC_Handle VIDENC_create(Engine_Handle e, String name,
    VIDENC_Params *params);


/*
 *  ======== VIDENC_process ========
 */
/**
 *  @brief      Execute the "process" method in this instance of a video
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video encoder handle
 *              and the video encoder is in the created state.
 *
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDENC_create(), VIDENC_delete(), VIDENC_control()
 */
extern Int32 VIDENC_process(VIDENC_Handle handle,
        XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
        VIDENC_InArgs *inArgs, VIDENC_OutArgs *outArgs);

/*
 *  ======== VIDENC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a video
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video encoder handle
 *              and the video encoder is in the created state.
 *
 *  @retval     #VIDENC_EOK         Success.
 *  @retval     #VIDENC_EFAIL       Failure.
 *  @retval     #VIDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDENC_create(), VIDENC_delete()
 */
extern Int32 VIDENC_control(VIDENC_Handle handle, VIDENC_Cmd id,
        VIDENC_DynamicParams *params, VIDENC_Status *status);


/*
 *  ======== VIDENC_delete ========
 */
/**
 *  @brief      Delete the instance of a video encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDENC_create()
 */
extern Void VIDENC_delete(VIDENC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.video; 1, 0, 2,251; 1-14-2008 09:57:58; /db/atree/library/trees/ce-g30x/src/
 */

