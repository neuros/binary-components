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
 *  ======== videnc1.h ========
 */
/**
 *  @file       ti/sdo/ce/video1/videnc1.h
 *
 *  @brief      The 1.0 video encoder codec interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 1.0 video encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_video1_VIDENC1    Video 1.0 encoder codec interface
 *
 *  This is the 1.0 video encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 1.0 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_video1_VIDENC1_
#define ti_sdo_ce_video1_VIDENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_video1_VIDENC1 */
/*@{*/

typedef IVIDENC1_Status VIDENC1_Status;       /**< @copydoc IVIDENC1_Status */

#define VIDENC1_EOK      IVIDENC1_EOK         /**< @copydoc IVIDENC1_EOK */
#define VIDENC1_EFAIL    IVIDENC1_EFAIL       /**< @copydoc IVIDENC1_EFAIL */

/**< @copydoc IVIDENC1_EUNSUPPORTED */
#define VIDENC1_EUNSUPPORTED IVIDENC1_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a VIDENC1 codec.
 */
typedef VISA_Handle VIDENC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Video Encoder object.
 */
typedef struct IVIDENC1_Params VIDENC1_Params;

/**
 * @copydoc IVIDENC1_InArgs
 */
typedef IVIDENC1_InArgs          VIDENC1_InArgs;

/**
 * @copydoc IVIDENC1_OutArgs
 */
typedef IVIDENC1_OutArgs         VIDENC1_OutArgs;

/**
 * @copydoc IVIDENC1_Cmd
 */
typedef IVIDENC1_Cmd             VIDENC1_Cmd;

/**
 * @copydoc IVIDENC1_DynamicParams
 */
typedef IVIDENC1_DynamicParams   VIDENC1_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDENC1_SKEL;

/**
 *  @brief      Implementation of the IVIDENC1 interface that is run remotely.
 */
extern IVIDENC1_Fxns VIDENC1_STUBS;

/** @endcond */

/*
 *  ======== VIDENC1_create ========
 */
/**
 *  @brief      Create an instance of a video encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDENC1_create) or
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
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern VIDENC1_Handle VIDENC1_create(Engine_Handle e, String name,
    VIDENC1_Params *params);


/*
 *  ======== VIDENC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
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
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to VIDENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         VIDENC1_control()
 *  @sa         IVIDENC1_Fxns::process()
 */
extern Int32 VIDENC1_process(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs,
    XDM_BufDesc *outBufs, VIDENC1_InArgs *inArgs, VIDENC1_OutArgs *outArgs);


/*
 *  ======== VIDENC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
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
 *  @retval     #VIDENC1_EOK         Success.
 *  @retval     #VIDENC1_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDENC1_create()
 *  @sa         VIDENC1_delete()
 *  @sa         IVIDENC1_Fxns::process()
 */
extern Int32 VIDENC1_control(VIDENC1_Handle handle, VIDENC1_Cmd id,
    VIDENC1_DynamicParams *params, VIDENC1_Status *status);


/*
 *  ======== VIDENC1_delete ========
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
 *  @post       All resources allocated as part of the VIDENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDENC1_create()
 */
extern Void VIDENC1_delete(VIDENC1_Handle handle);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video1; 1, 0, 0,112; 1-14-2008 09:58:06; /db/atree/library/trees/ce-g30x/src/
 */

