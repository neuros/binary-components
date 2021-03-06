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
 *  ======== auddec.h ========
 */
/**
 *  @file       ti/sdo/ce/audio/auddec.h
 *
 *  @brief      The 0.9 Audio Decoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 0.9 audio decoder interface.
 */
/**
 *  @defgroup   AUDDEC    0.9 Audio Decoder Codec Interface
 *
 *  This is the 0.9 audio decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef AUDDEC_
#define AUDDEC_

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
#include <ti/xdais/dm/iauddec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    AUDDEC */
/*@{*/

/**
 *  @copydoc    IAUDDEC_Status
 */
typedef IAUDDEC_Status AUDDEC_Status;

#define AUDDEC_EOK      IAUDDEC_EOK         /**< @copydoc IAUDDEC_EOK */
#define AUDDEC_EFAIL    IAUDDEC_EFAIL       /**< @copydoc IAUDDEC_EFAIL */
#define AUDDEC_ERUNTIME IAUDDEC_ERUNTIME    /**< @copydoc IAUDDEC_ERUNTIME */

/**
 *  @brief      Opaque handle to a AUDDEC codec.
 */
typedef VISA_Handle AUDDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a 0.9 audio decoder object.
 */
typedef struct IAUDDEC_Params AUDDEC_Params;

/**
 * @copydoc IAUDDEC_InArgs
 */
typedef IAUDDEC_InArgs          AUDDEC_InArgs;

/**
 * @copydoc IAUDDEC_OutArgs
 */
typedef IAUDDEC_OutArgs         AUDDEC_OutArgs;

/**
 * @copydoc IAUDDEC_Cmd
 */
typedef IAUDDEC_Cmd             AUDDEC_Cmd;

/**
 * @copydoc IAUDDEC_DynamicParams
 */
typedef IAUDDEC_DynamicParams   AUDDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDDEC_SKEL;

/**
 *  @brief      Implementation of the IAUDDEC interface that is run remotely.
 */
extern IAUDDEC_Fxns AUDDEC_STUBS;

/** @endcond */

/*
 *  ======== AUDDEC_create ========
 */
/**
 *  @brief      Create an instance of a audio decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDDEC_create()) or
 *  explicitly serialize access to a shared handle.  
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern AUDDEC_Handle AUDDEC_create(Engine_Handle e, String name,
    AUDDEC_Params *params);


/*
 *  ======== AUDDEC_process ========
 */
/**
 *  @brief      Execute the "process" method in this instance of a audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to AUDDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         AUDDEC_create(), AUDDEC_delete(), AUDDEC_control()
 */
extern Int32 AUDDEC_process(AUDDEC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs);

/*
 *  ======== AUDDEC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC_EOK         Success.
 *  @retval     #AUDDEC_EFAIL       Failure.
 *  @retval     #AUDDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         AUDDEC_create(), AUDDEC_delete()
 */
extern Int32 AUDDEC_control(AUDDEC_Handle handle, AUDDEC_Cmd id,
    AUDDEC_DynamicParams *params, AUDDEC_Status *status);


/*
 *  ======== AUDDEC_delete ========
 */
/**
 *  @brief      Delete the instance of a audio decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the audio
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the AUDDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDDEC_create()
 */
extern Void AUDDEC_delete(AUDDEC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.audio; 1, 0, 1,244; 1-14-2008 09:49:12; /db/atree/library/trees/ce-g30x/src/
 */

