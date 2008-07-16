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
 *  ======== sphenc.h ========
 */
/**
 *  @file       ti/sdo/ce/speech/sphenc.h
 *
 *  @brief      The 0.9 Speech/Voice Encoder Codec Interface.  Provides the
 *              user an interface to create and interact with xDAIS algorithms
 *              that are compliant with the xDM 0.9 Speech/Voice Encoder
 *              interface.
 */
/**
 *  @defgroup   SPHENC    0.9 Speech/Voice Encoder Codec Interface
 *
 *  This is the 0.9 speech/voice encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef SPHENC_
#define SPHENC_

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
#include <ti/xdais/dm/isphenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    SPHENC */
/*@{*/

/**
 *  @copydoc    ISPHENC_Status
 */
typedef ISPHENC_Status SPHENC_Status;

#define SPHENC_EOK      ISPHENC_EOK         /**< @copydoc ISPHENC_EOK */
#define SPHENC_EFAIL    ISPHENC_EFAIL       /**< @copydoc ISPHENC_EFAIL */
#define SPHENC_ERUNTIME ISPHENC_ERUNTIME    /**< @copydoc ISPHENC_ERUNTIME */

/**
 *  @brief      Opaque handle to a SPHENC codec.
 */
typedef VISA_Handle SPHENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Speech/Voice Encoder object.
 */
typedef struct ISPHENC_Params SPHENC_Params;

/**
 * @copydoc ISPHENC_InArgs
 */
typedef ISPHENC_InArgs          SPHENC_InArgs;

/**
 * @copydoc ISPHENC_OutArgs
 */
typedef ISPHENC_OutArgs         SPHENC_OutArgs;

/**
 * @copydoc ISPHENC_Cmd
 */
typedef ISPHENC_Cmd             SPHENC_Cmd;

/**
 * @copydoc ISPHENC_DynamicParams
 */
typedef ISPHENC_DynamicParams   SPHENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHENC_SKEL;

/**
 *  @brief      Implementation of the ISPHENC interface that is run remotely.
 */
extern ISPHENC_Fxns SPHENC_STUBS;

/** @endcond */

/*
 *  ======== SPHENC_create ========
 */
/**
 *  @brief      Create an instance of a speech/voice encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHENC_create()) or
 *  explicitly serialize access to a shared handle.  
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of speech encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created speech encoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open(), SPHENC_delete()
 */
extern SPHENC_Handle SPHENC_create(Engine_Handle e, String name,
    SPHENC_Params *params);


/*
 *  ======== SPHENC_process ========
 */
/**
 *  @brief      Execute the process method in this instance of a speech/voice
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to SPHENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHENC_create(), SPHENC_delete()
 */
extern Int32 SPHENC_process(SPHENC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    SPHENC_InArgs *inArgs, SPHENC_OutArgs *outArgs);

/*
 *  ======== SPHENC_control ========
 */
/**
 *  @brief      Execute the control method in this instance of a speech/voice
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) speech encoder handle
 *              and the speech encoder is in the created state.
 *
 *  @retval     #SPHENC_EOK         Success.
 *  @retval     #SPHENC_EFAIL       Failure.
 *  @retval     #SPHENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHENC_create(), SPHENC_delete()
 */
extern Int32 SPHENC_control(SPHENC_Handle handle, SPHENC_Cmd id,
    SPHENC_DynamicParams *params, SPHENC_Status *status);


/*
 *  ======== SPHENC_delete ========
 */
/**
 *  @brief      Delete the instance of a speech/voice encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the speech
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the SPHENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHENC_create()
 */
extern Void SPHENC_delete(SPHENC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 1,257; 1-14-2008 09:55:56; /db/atree/library/trees/ce-g30x/src/
 */

