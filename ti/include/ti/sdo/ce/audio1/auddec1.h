/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== auddec1.h ========
 */

/**
 *  @file       ti/sdo/ce/audio1/auddec1.h
 *
 *  @brief      The 1.00 audio decoder codec interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 1.00 Audio Decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_audio1_AUDDEC1  1.00 Audio Decoder Codec Interface
 *
 *  This is the 1.00 audio decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 1.00 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_audio1_AUDDEC1_
#define ti_sdo_ce_audio1_AUDDEC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iauddec1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_audio1_AUDDEC1 */
/*@{*/

#define AUDDEC1_EOK      IAUDDEC1_EOK         /**< @copydoc IAUDDEC1_EOK */
#define AUDDEC1_EFAIL    IAUDDEC1_EFAIL       /**< @copydoc IAUDDEC1_EFAIL */

/** @copydoc IAUDDEC1_EUNSUPPORTED */
#define AUDDEC1_EUNSUPPORTED IAUDDEC1_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a AUDDEC1 codec.
 */
typedef VISA_Handle AUDDEC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a 1.0 audio decoder object.
 */
typedef struct IAUDDEC1_Params AUDDEC1_Params;


typedef IAUDDEC1_InArgs  AUDDEC1_InArgs;    /**< @copydoc IAUDDEC1_InArgs */
typedef IAUDDEC1_OutArgs AUDDEC1_OutArgs;   /**< @copydoc IAUDDEC1_OutArgs */
typedef IAUDDEC1_Cmd     AUDDEC1_Cmd;       /**< @copydoc IAUDDEC1_Cmd */
typedef IAUDDEC1_Status  AUDDEC1_Status;    /**< @copydoc IAUDDEC1_Status */

/** @copydoc IAUDDEC1_DynamicParams */
typedef IAUDDEC1_DynamicParams AUDDEC1_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns AUDDEC1_SKEL;

/**
 *  @brief      Implementation of the IAUDDEC1 interface that is run remotely.
 */
extern IAUDDEC1_Fxns AUDDEC1_STUBS;

/** @endcond */


/*
 *  ======== AUDDEC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an audio1
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
 *  @retval     #AUDDEC1_EOK         Success.
 *  @retval     #AUDDEC1_EFAIL       Failure.
 *  @retval     #AUDDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         AUDDEC1_create()
 *  @sa         AUDDEC1_delete()
 *  @sa         IAUDDEC1_Fxns()::control()
 */
extern Int32 AUDDEC1_control(AUDDEC1_Handle handle, AUDDEC1_Cmd id,
    AUDDEC1_DynamicParams *params, AUDDEC1_Status *status);


/*
 *  ======== AUDDEC1_create ========
 */
/**
 *  @brief      Create an instance of an audio decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via AUDDEC1_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of audio decoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created audio decoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the audio
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         AUDDEC1_delete()
 */
extern AUDDEC1_Handle AUDDEC1_create(Engine_Handle e, String name,
    AUDDEC1_Params *params);


/*
 *  ======== AUDDEC1_delete ========
 */
/**
 *  @brief      Delete the instance of an audio decoder algorithm.
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
 *  @post       All resources allocated as part of the AUDDEC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         AUDDEC1_create()
 */
extern Void AUDDEC1_delete(AUDDEC1_Handle handle);


/*
 *  ======== AUDDEC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of a audio
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created audio decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) audio decoder handle
 *              and the audio decoder is in the created state.
 *
 *  @retval     #AUDDEC1_EOK         Success.
 *  @retval     #AUDDEC1_EFAIL       Failure.
 *  @retval     #AUDDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to AUDDEC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         AUDDEC1_create()
 *  @sa         AUDDEC1_delete()
 *  @sa         AUDDEC1_control()
 *  @sa         IAUDDEC1_Fxns()::process()
 */
extern Int32 AUDDEC1_process(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.audio1; 1, 0, 0,118; 1-14-2008 09:49:23; /db/atree/library/trees/ce-g30x/src/
 */

