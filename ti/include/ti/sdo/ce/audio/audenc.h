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
 *  ======== audenc.h ========
 */
/**
 *  @file       ti/sdo/ce/audio/audenc.h
 *
 *  @brief      The 0.9 Audio Encoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 0.9 audio encoder interface.
 */
/**
 *  @defgroup   AUDENC    0.9 Audio Encoder Codec Interface
 *
 *  This is the 0.9 audio encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef AUDENC_
#define AUDENC_

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
#include <ti/xdais/dm/iaudenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    AUDENC */
/*@{*/

/**
 *  @copydoc    IAUDENC_Status
 */
typedef IAUDENC_Status AUDENC_Status;

#define AUDENC_EOK      IAUDENC_EOK         /**< @copydoc IAUDENC_EOK */
#define AUDENC_EFAIL    IAUDENC_EFAIL       /**< @copydoc IAUDENC_EFAIL */
#define AUDENC_ERUNTIME IAUDENC_ERUNTIME    /**< @copydoc IAUDENC_ERUNTIME */

/**
 *  @brief      Opaque handle to a AUDENC codec.
 */
typedef VISA_Handle AUDENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Audio Encoder object.
 */
typedef struct IAUDENC_Params AUDENC_Params;

/**
 * @copydoc IAUDENC_InArgs
 */
typedef IAUDENC_InArgs          AUDENC_InArgs;

/**
 * @copydoc IAUDENC_OutArgs
 */
typedef IAUDENC_OutArgs         AUDENC_OutArgs;

/**
 * @copydoc IAUDENC_Cmd
 */
typedef IAUDENC_Cmd             AUDENC_Cmd;

/**
 * @copydoc IAUDENC_DynamicParams
 */
typedef IAUDENC_DynamicParams   AUDENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDENC_SKEL;

/**
 *  @brief      Implementation of the IAUDENC interface that is run remotely.
 */
extern IAUDENC_Fxns AUDENC_STUBS;

/** @endcond */

/*
 *  ======== AUDENC_create ========
 */
/**
 *  @brief      Create an instance of a audio encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDENC_create()) or
 *  explicitly serialize access to a shared handle.  
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio encoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern AUDENC_Handle AUDENC_create(Engine_Handle e, String name,
    AUDENC_Params *params);


/*
 *  ======== AUDENC_process ========
 */
/**
 *  @brief      Execute the "process" method in this instance of a audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to AUDENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         AUDENC_create(), AUDENC_delete(), AUDENC_control()
 */
extern Int32 AUDENC_process(AUDENC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    AUDENC_InArgs *inArgs, AUDENC_OutArgs *outArgs);

/*
 *  ======== AUDENC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC_EOK         Success.
 *  @retval     #AUDENC_EFAIL       Failure.
 *  @retval     #AUDENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         AUDENC_create(), AUDENC_delete()
 */
extern Int32 AUDENC_control(AUDENC_Handle handle, AUDENC_Cmd id,
    AUDENC_DynamicParams *params, AUDENC_Status *status);


/*
 *  ======== AUDENC_delete ========
 */
/**
 *  @brief      Delete the instance of a audio encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the audio
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the AUDENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDENC_create()
 */
extern Void AUDENC_delete(AUDENC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.audio; 1, 0, 1,244; 1-14-2008 09:49:12; /db/atree/library/trees/ce-g30x/src/
 */

