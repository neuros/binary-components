/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== audenc1.h ========
 */

/**
 *  @file       ti/sdo/ce/audio1/audenc1.h
 *
 *  @brief      The 1.0 audio encoder codec interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 1.0 audio encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_audio1_AUDENC1    Audio 1.0 Encoder Codec Interface
 *
 *  This is the 1.0 audio encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 1.0 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_audio1_AUDENC1_
#define ti_sdo_ce_audio1_AUDENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iaudenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_audio1_AUDENC1 */
/*@{*/

#define AUDENC1_EOK      IAUDENC1_EOK         /**< @copydoc IAUDENC1_EOK */
#define AUDENC1_EFAIL    IAUDENC1_EFAIL       /**< @copydoc IAUDENC1_EFAIL */

/** @copydoc IAUDENC1_EUNSUPPORTED */
#define AUDENC1_EUNSUPPORTED IAUDENC1_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a AUDENC1 codec.
 */
typedef VISA_Handle AUDENC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of an audio encoder.
 */
typedef struct IAUDENC1_Params AUDENC1_Params;


typedef IAUDENC1_InArgs  AUDENC1_InArgs;    /**< @copydoc IAUDENC1_InArgs */
typedef IAUDENC1_OutArgs AUDENC1_OutArgs;   /**< @copydoc IAUDENC1_OutArgs */
typedef IAUDENC1_Cmd     AUDENC1_Cmd;       /**< @copydoc IAUDENC1_Cmd */
typedef IAUDENC1_Status  AUDENC1_Status;    /**< @copydoc IAUDENC1_Status */

/** @copydoc IAUDENC1_DynamicParams */
typedef IAUDENC1_DynamicParams AUDENC1_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDENC1_SKEL;

/**
 *  @brief      Implementation of the IAUDENC1 interface that is run remotely.
 */
extern IAUDENC1_Fxns AUDENC1_STUBS;

/** @endcond */


/*
 *  ======== AUDENC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an audio
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
 *  @retval     #AUDENC1_EOK         Success.
 *  @retval     #AUDENC1_EFAIL       Failure.
 *  @retval     #AUDENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         AUDENC1_create()
 *  @sa         AUDENC1_delete()
 *  @sa         IAUDENC1_Fxns::control()
 */
extern Int32 AUDENC1_control(AUDENC1_Handle handle, AUDENC1_Cmd id,
    AUDENC1_DynamicParams *params, AUDENC1_Status *status);


/*
 *  ======== AUDENC1_create ========
 */
/**
 *  @brief      Create an instance of an audio encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDENC1_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio encoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio encoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         AUDENC1_delete()
 */
extern AUDENC1_Handle AUDENC1_create(Engine_Handle e, String name,
    AUDENC1_Params *params);


/*
 *  ======== AUDENC1_delete ========
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
 *  @post       All resources allocated as part of the AUDENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDENC1_create()
 */
extern Void AUDENC1_delete(AUDENC1_Handle handle);


/*
 *  ======== AUDENC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a audio
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio encoder handle
 *              and the audio encoder is in the created state.
 *
 *  @retval     #AUDENC1_EOK         Success.
 *  @retval     #AUDENC1_EFAIL       Failure.
 *  @retval     #AUDENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to AUDENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         AUDENC1_create()
 *  @sa         AUDENC1_delete()
 *  @sa         AUDENC1_control()
 *  @sa         IAUDENC1_Fxns::process()
 */
extern Int32 AUDENC1_process(AUDENC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.audio1; 1, 0, 0,118; 1-14-2008 09:49:24; /db/atree/library/trees/ce-g30x/src/
 */

