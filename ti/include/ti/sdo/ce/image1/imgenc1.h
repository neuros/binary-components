/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgenc1.h ========
 */

/**
 *  @file       ti/sdo/ce/image1/imgenc1.h
 *
 *  @brief      The Image 1.0 Encoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 1.0 Image Encoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_image1_IMGENC1    Image 1.0 Encoder Codec Interface
 *
 *  This is the Image 1.0 Encoder Codec Interface.  Several of the data
 *  types in this API are specified by the xDM 1.0 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_image1_IMGENC1_
#define ti_sdo_ce_image1_IMGENC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iimgenc1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_image1_IMGENC1 */
/*@{*/

#define IMGENC1_EOK      IIMGENC1_EOK         /**< @copydoc IIMGENC1_EOK */
#define IMGENC1_EFAIL    IIMGENC1_EFAIL       /**< @copydoc IIMGENC1_EFAIL */

/** @copydoc IIMGENC1_EUNSUPPORTED */
#define IMGENC1_EUNSUPPORTED IIMGENC1_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a IMGENC1 codec.
 */
typedef VISA_Handle IMGENC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of an image encoder.
 */
typedef struct IIMGENC1_Params IMGENC1_Params;


typedef IIMGENC1_InArgs  IMGENC1_InArgs;    /**< @copydoc IIMGENC1_InArgs */
typedef IIMGENC1_OutArgs IMGENC1_OutArgs;   /**< @copydoc IIMGENC1_OutArgs */
typedef IIMGENC1_Cmd     IMGENC1_Cmd;       /**< @copydoc IIMGENC1_Cmd */
typedef IIMGENC1_Status  IMGENC1_Status;    /**< @copydoc IIMGENC1_Status */

/** @copydoc IIMGENC1_DynamicParams */
typedef IIMGENC1_DynamicParams IMGENC1_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGENC1_SKEL;

/**
 *  @brief      Implementation of the IIMGENC1 interface that is run remotely.
 */
extern IIMGENC1_Fxns IMGENC1_STUBS;

/** @endcond */


/*
 *  ======== IMGENC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for encoding.
 *  @param[out] status  Status info upon completion of encode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IIMGENC1_Fxns::control()
 */
extern Int32 IMGENC1_control(IMGENC1_Handle handle, IMGENC1_Cmd id,
    IMGENC1_DynamicParams *params, IMGENC1_Status *status);


/*
 *  ======== IMGENC1_create ========
 */
/**
 *  @brief      Create an instance of an image encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGENC1_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image encoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image encoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGENC1_delete()
 */
extern IMGENC1_Handle IMGENC1_create(Engine_Handle e, String name,
    IMGENC1_Params *params);


/*
 *  ======== IMGENC1_delete ========
 */
/**
 *  @brief      Delete the instance of a image encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the image
 *              encoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the IMGENC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGENC1_create()
 */
extern Void IMGENC1_delete(IMGENC1_Handle handle);


/*
 *  ======== IMGENC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC1_EOK         Success.
 *  @retval     #IMGENC1_EFAIL       Failure.
 *  @retval     #IMGENC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to IMGENC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         IMGENC1_create()
 *  @sa         IMGENC1_delete()
 *  @sa         IMGENC1_control()
 *  @sa         IIMGENC1_Fxns::process()
 */
extern Int32 IMGENC1_process(IMGENC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IMGENC1_InArgs *inArgs, IMGENC1_OutArgs *outArgs);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 0,115; 1-14-2008 09:55:15; /db/atree/library/trees/ce-g30x/src/
 */

