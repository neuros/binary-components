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
 *  ======== imgenc.h ========
 */
/**
 *  @file       ti/sdo/ce/image/imgenc.h
 *
 *  @brief      The 0.9 Image Encoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 0.9 image encoder interface.
 */
/**
 *  @defgroup   IMGENC    0.9 Image Encoder Codec Interface
 *
 *  This is the 0.9 image encoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef IMGENC_
#define IMGENC_

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
#include <ti/xdais/dm/iimgenc.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    IMGENC */
/*@{*/

/**
 *  @copydoc    IIMGENC_Status
 */
typedef IIMGENC_Status IMGENC_Status;

#define IMGENC_EOK      IIMGENC_EOK         /**< @copydoc IIMGENC_EOK */
#define IMGENC_EFAIL    IIMGENC_EFAIL       /**< @copydoc IIMGENC_EFAIL */
#define IMGENC_ERUNTIME IIMGENC_ERUNTIME    /**< @copydoc IIMGENC_ERUNTIME */

/**
 *  @brief      Opaque handle to a IMGENC codec.
 */
typedef VISA_Handle IMGENC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Image Encoder object.
 */
typedef struct IIMGENC_Params IMGENC_Params;

/**
 * @copydoc IIMGENC_InArgs
 */
typedef IIMGENC_InArgs          IMGENC_InArgs;

/**
 * @copydoc IIMGENC_OutArgs
 */
typedef IIMGENC_OutArgs         IMGENC_OutArgs;

/**
 * @copydoc IIMGENC_Cmd
 */
typedef IIMGENC_Cmd             IMGENC_Cmd;

/**
 * @copydoc IIMGENC_DynamicParams
 */
typedef IIMGENC_DynamicParams   IMGENC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGENC_SKEL;

/**
 *  @brief      Implementation of the IIMGENC interface that is run remotely.
 */
extern IIMGENC_Fxns IMGENC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGDEC codec class configurable parameters
 */
typedef struct IIMGENC_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];  
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];  
} IIMGENC_CodecClassConfig;

/*
 *  ======== IMGENC_create ========
 */
/**
 *  @brief      Create an instance of a image encoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGENC_create()) or
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
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              encoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern IMGENC_Handle IMGENC_create(Engine_Handle e, String name,
    IMGENC_Params *params);


/*
 *  ======== IMGENC_process ========
 */
/**
 *  @brief      Execute the "process" method in this instance of a image
 *              encoder algorithm.
 *
 *  @param[in]  handle  Handle to a created image encoder instance.
 *  @param[in]  inBufs  A buffer describer containing input buffers.
 *  @param[out] outBufs A buffer describer containing output buffers.
 *  @param[in]  inArgs  Input Arguments.
 *  @param[out] outArgs Output Arguments.
 *
 *  @pre        @c handle is a valid (non-NULL) image encoder handle
 *              and the image encoder is in the created state.
 *
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been encoded.
 *
 *  @remark     The buffers supplied to IMGENC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *
 *  @sa         IMGENC_create(), IMGENC_delete(), IMGENC_control()
 */
extern Int32 IMGENC_process(IMGENC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    IMGENC_InArgs *inArgs, IMGENC_OutArgs *outArgs);

/*
 *  ======== IMGENC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a image
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
 *  @retval     #IMGENC_EOK         Success.
 *  @retval     #IMGENC_EFAIL       Failure.
 *  @retval     #IMGENC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGENC_create(), IMGENC_delete()
 */
extern Int32 IMGENC_control(IMGENC_Handle handle, IMGENC_Cmd id,
    IMGENC_DynamicParams *params, IMGENC_Status *status);


/*
 *  ======== IMGENC_delete ========
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
 *  @post       All resources allocated as part of the IMGENC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGENC_create()
 */
extern Void IMGENC_delete(IMGENC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 2,191; 1-14-2008 09:55:04; /db/atree/library/trees/ce-g30x/src/
 */

