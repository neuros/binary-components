/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgdec1.h ========
 */

/**
 *  @file       ti/sdo/ce/image1/imgdec1.h
 *
 *  @brief      The 1.00 image decoder codec interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 1.00 image decoder interface.
 */
/**
 *  @defgroup   ti_sdo_ce_image1_IMGDEC1  Image 1.00 decoder codec interface
 *
 *  This is the 1.00 image decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 1.00 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef ti_sdo_ce_image1_IMGDEC1_
#define ti_sdo_ce_image1_IMGDEC1_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iimgdec1.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    ti_sdo_ce_image1_IMGDEC1 */
/*@{*/

#define IMGDEC1_EOK      IIMGDEC1_EOK         /**< @copydoc IIMGDEC1_EOK */
#define IMGDEC1_EFAIL    IIMGDEC1_EFAIL       /**< @copydoc IIMGDEC1_EFAIL */

/** @copydoc IIMGDEC1_EUNSUPPORTED */
#define IMGDEC1_EUNSUPPORTED IIMGDEC1_EUNSUPPORTED


/**
 *  @brief      Opaque handle to a IMGDEC1 codec.
 */
typedef VISA_Handle IMGDEC1_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of an image decoder object.
 */
typedef struct IIMGDEC1_Params IMGDEC1_Params;


typedef IIMGDEC1_InArgs  IMGDEC1_InArgs;    /**< @copydoc IIMGDEC1_InArgs */
typedef IIMGDEC1_OutArgs IMGDEC1_OutArgs;   /**< @copydoc IIMGDEC1_OutArgs */
typedef IIMGDEC1_Cmd     IMGDEC1_Cmd;       /**< @copydoc IIMGDEC1_Cmd */
typedef IIMGDEC1_Status  IMGDEC1_Status;    /**< @copydoc IIMGDEC1_Status */

/** @copydoc IIMGDEC1_DynamicParams */
typedef IIMGDEC1_DynamicParams IMGDEC1_DynamicParams;


/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGDEC1_SKEL;

/**
 *  @brief      Implementation of the IIMGDEC1 interface that is run remotely.
 */
extern IIMGDEC1_Fxns IMGDEC1_STUBS;

/** @endcond */


/*
 *  ======== IMGDEC1_control ========
 */
/**
 *  @brief      Execute the control() method in this instance of an image1
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  id      Command id for xDM control operation.
 *  @param[in]  params  Runtime control parameters used for decoding.
 *  @param[out] status  Status info upon completion of decode operation.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IIMGDEC1_Fxns()::control()
 */
extern Int32 IMGDEC1_control(IMGDEC1_Handle handle, IMGDEC1_Cmd id,
    IMGDEC1_DynamicParams *params, IMGDEC1_Status *status);


/*
 *  ======== IMGDEC1_create ========
 */
/**
 *  @brief      Create an instance of an image decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGDEC1_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image decoder.
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image decoder
 *                              instance.
 *
 *  @remarks    @c params is optional.  If it's not supplied, codec-specific
 *              default params will be used.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 *  @sa         IMGDEC1_delete()
 */
extern IMGDEC1_Handle IMGDEC1_create(Engine_Handle e, String name,
    IMGDEC1_Params *params);


/*
 *  ======== IMGDEC1_delete ========
 */
/**
 *  @brief      Delete the instance of an image decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may delete a local or remote instance of the image
 *              decoder.
 *
 *  @pre        @c handle is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the IMGDEC1_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGDEC1_create()
 */
extern Void IMGDEC1_delete(IMGDEC1_Handle handle);


/*
 *  ======== IMGDEC1_process ========
 */
/**
 *  @brief      Execute the process() method in this instance of an image
 *              decoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image decoder instance.
 *  @param[in]  inBufs  A buffer descriptor containing input buffers.
 *  @param[out] outBufs A buffer descriptor containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image decoder handle
 *              and the image decoder is in the created state.
 *
 *  @retval     #IMGDEC1_EOK         Success.
 *  @retval     #IMGDEC1_EFAIL       Failure.
 *  @retval     #IMGDEC1_EUNSUPPORTED Unsupported request.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to IMGDEC1_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         IMGDEC1_create()
 *  @sa         IMGDEC1_delete()
 *  @sa         IMGDEC1_control()
 *  @sa         IIMGDEC1_Fxns()::process()
 */
extern Int32 IMGDEC1_process(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 0,115; 1-14-2008 09:55:15; /db/atree/library/trees/ce-g30x/src/
 */

