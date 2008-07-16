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
 *  ======== sphdec.h ========
 */
/**
 *  @file       ti/sdo/ce/speech/sphdec.h
 *
 *  @brief      The 0.9 Speech/Voice Decoder Codec Interface.  Provides the
 *              user an interface to create and interact with xDAIS algorithms
 *              that are compliant with the xDM 0.9 Speech/Voice Decoder
 *              interface.
 */
/**
 *  @defgroup   SPHDEC    0.9 Speech/Voice Decoder Codec Interface
 *
 *  This is the 0.9 speech/voice decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef SPHDEC_
#define SPHDEC_

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
#include <ti/xdais/dm/isphdec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    SPHDEC */
/*@{*/

/**
 *  @copydoc    ISPHDEC_Status
 */
typedef ISPHDEC_Status SPHDEC_Status;

#define SPHDEC_EOK      ISPHDEC_EOK         /**< @copydoc ISPHDEC_EOK */
#define SPHDEC_EFAIL    ISPHDEC_EFAIL       /**< @copydoc ISPHDEC_EFAIL */
#define SPHDEC_ERUNTIME ISPHDEC_ERUNTIME    /**< @copydoc ISPHDEC_ERUNTIME */

/**
 *  @brief      Opaque handle to a SPHDEC codec.
 */
typedef VISA_Handle SPHDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Speech/Voice Decoder object.
 */
typedef struct ISPHDEC_Params SPHDEC_Params;

/**
 * @copydoc ISPHDEC_InArgs
 */
typedef ISPHDEC_InArgs          SPHDEC_InArgs;

/**
 * @copydoc ISPHDEC_OutArgs
 */
typedef ISPHDEC_OutArgs         SPHDEC_OutArgs;

/**
 * @copydoc ISPHDEC_Cmd
 */
typedef ISPHDEC_Cmd             SPHDEC_Cmd;

/**
 * @copydoc ISPHDEC_DynamicParams
 */
typedef ISPHDEC_DynamicParams   SPHDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns SPHDEC_SKEL;

/**
 *  @brief      Implementation of the ISPHDEC interface that is run remotely.
 */
extern ISPHDEC_Fxns SPHDEC_STUBS;

/** @endcond */

/*
 *  ======== SPHDEC_create ========
 */
/**
 *  @brief      Create an instance of a speech/voice decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via SPHDEC_create()) or
 *  explicitly serialize access to a shared handle.  
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of speech decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created speech decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the speech
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open(), SPHDEC_delete()
 */
extern SPHDEC_Handle SPHDEC_create(Engine_Handle e, String name,
    SPHDEC_Params *params);


/*
 *  ======== SPHDEC_process ========
 */
/**
 *  @brief      Execute the process method in this instance of a speech/voice
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to SPHDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         SPHDEC_create(), SPHDEC_delete(), SPHDEC_control()
 */
extern Int32 SPHDEC_process(SPHDEC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs);

/*
 *  ======== SPHDEC_control ========
 */
/**
 *  @brief      Execute the control method in this instance of a speech
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) speech decoder handle
 *              and the speech decoder is in the created state.
 *
 *  @retval     #SPHDEC_EOK         Success.
 *  @retval     #SPHDEC_EFAIL       Failure.
 *  @retval     #SPHDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         SPHDEC_create(), SPHDEC_delete()
 */
extern Int32 SPHDEC_control(SPHDEC_Handle handle, SPHDEC_Cmd id,
    SPHDEC_DynamicParams *params, SPHDEC_Status *status);


/*
 *  ======== SPHDEC_delete ========
 */
/**
 *  @brief      Delete the instance of a speech/voice decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created speech decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the speech
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the SPHDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         SPHDEC_create()
 */
extern Void SPHDEC_delete(SPHDEC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 1,257; 1-14-2008 09:55:56; /db/atree/library/trees/ce-g30x/src/
 */

