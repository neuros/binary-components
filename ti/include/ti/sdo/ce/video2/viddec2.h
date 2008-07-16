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
 *  ======== viddec2.h ========
 */
/**
 *  @file       ti/sdo/ce/video2/viddec2.h
 *
 *  @brief      The VIDDEC2 video decoder codec interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM IVIDDEC2 video decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_video2_VIDDEC2    Video 1.20 decoder codec interface
 *
 *  This is the VIDDEC2 video decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_video2_VIDDEC2_
#define ti_sdo_ce_video2_VIDDEC2_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ividdec2.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_video2_VIDDEC2 */
/*@{*/

typedef IVIDDEC2_Status VIDDEC2_Status;       /**< @copydoc IVIDDEC2_Status */

#define VIDDEC2_EOK      IVIDDEC2_EOK         /**< @copydoc IVIDDEC2_EOK */
#define VIDDEC2_EFAIL    IVIDDEC2_EFAIL       /**< @copydoc IVIDDEC2_EFAIL */

/**< @copydoc IVIDDEC2_EUNSUPPORTED */
#define VIDDEC2_EUNSUPPORTED IVIDDEC2_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a VIDDEC2 codec.
 */
typedef VISA_Handle VIDDEC2_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Video Decoder object.
 */
typedef struct IVIDDEC2_Params VIDDEC2_Params;

/**
 * @copydoc IVIDDEC2_InArgs
 */
typedef IVIDDEC2_InArgs          VIDDEC2_InArgs;

/**
 * @copydoc IVIDDEC2_OutArgs
 */
typedef IVIDDEC2_OutArgs         VIDDEC2_OutArgs;

/**
 * @copydoc IVIDDEC2_Cmd
 */
typedef IVIDDEC2_Cmd             VIDDEC2_Cmd;

/**
 * @copydoc IVIDDEC2_DynamicParams
 */
typedef IVIDDEC2_DynamicParams   VIDDEC2_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns VIDDEC2_SKEL;

/**
 *  @brief      Implementation of the IVIDDEC2 interface that is run remotely.
 */
extern IVIDDEC2_Fxns VIDDEC2_STUBS;

/** @endcond */

/*
 *  ======== VIDDEC2_create ========
 */
/**
 *  @brief      Create an instance of a video decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via VIDDEC2_create) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of video decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created video decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the video
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern VIDDEC2_Handle VIDDEC2_create(Engine_Handle e, String name,
    VIDDEC2_Params *params);


/*
 *  ======== VIDDEC2_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to VIDDEC2_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         VIDDEC2_create()
 *  @sa         VIDDEC2_delete()
 *  @sa         VIDDEC2_control()
 *  @sa         IVIDDEC2_Fxns::process()
 */
extern Int32 VIDDEC2_process(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs);


/*
 *  ======== VIDDEC2_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of a video
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) video decoder handle
 *              and the video decoder is in the created state.
 *
 *  @retval     #VIDDEC2_EOK         Success.
 *  @retval     #VIDDEC2_EFAIL       Failure.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         VIDDEC2_create()
 *  @sa         VIDDEC2_delete()
 *  @sa         IVIDDEC2_Fxns::process()
 */
extern Int32 VIDDEC2_control(VIDDEC2_Handle handle, VIDDEC2_Cmd id,
    VIDDEC2_DynamicParams *params, VIDDEC2_Status *status);


/*
 *  ======== VIDDEC2_delete ========
 */
/**
 *  @brief      Delete the instance of a video decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created video decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the video
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the VIDDEC2_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         VIDDEC2_create()
 */
extern Void VIDDEC2_delete(VIDDEC2_Handle handle);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video2; 1, 0, 0,15; 1-14-2008 09:58:15; /db/atree/library/trees/ce-g30x/src/
 */

