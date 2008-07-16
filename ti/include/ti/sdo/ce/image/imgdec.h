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
 *  ======== imgdec.h ========
 */
/**
 *  @file       ti/sdo/ce/image/imgdec.h
 *
 *  @brief      The 0.9 Image Decoder Codec Interface.  Provides the user an
 *              interface to create and interact with xDAIS algorithms that are
 *              compliant with the xDM 0.9 image decoder interface.
 */
/**
 *  @defgroup   IMGDEC    0.9 Image Decoder Codec Interface
 *
 *  This is the 0.9 image decoder codec interface.  Several of the data
 *  types in this API are specified by the xDM 0.9 interface; please see
 *  the xDM documentation for those details.
 */

#ifndef IMGDEC_
#define IMGDEC_

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
#include <ti/xdais/dm/iimgdec.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/skel.h>

/** @ingroup    IMGDEC */
/*@{*/

/**
 *  @copydoc    IIMGDEC_Status
 */
typedef IIMGDEC_Status IMGDEC_Status;

#define IMGDEC_EOK      IIMGDEC_EOK         /**< @copydoc IIMGDEC_EOK */
#define IMGDEC_EFAIL    IIMGDEC_EFAIL       /**< @copydoc IIMGDEC_EFAIL */
#define IMGDEC_ERUNTIME IIMGDEC_ERUNTIME    /**< @copydoc IIMGDEC_ERUNTIME */

/**
 *  @brief      Opaque handle to a IMGDEC codec.
 */
typedef VISA_Handle IMGDEC_Handle;

/**
 *  @brief      This structure defines the parameters necessary to create an
 *              instance of a Image Decoder object.
 */
typedef struct IIMGDEC_Params IMGDEC_Params;

/**
 * @copydoc IIMGDEC_InArgs
 */
typedef IIMGDEC_InArgs          IMGDEC_InArgs;

/**
 * @copydoc IIMGDEC_OutArgs
 */
typedef IIMGDEC_OutArgs         IMGDEC_OutArgs;

/**
 * @copydoc IIMGDEC_Cmd
 */
typedef IIMGDEC_Cmd             IMGDEC_Cmd;

/**
 * @copydoc IIMGDEC_DynamicParams
 */
typedef IIMGDEC_DynamicParams   IMGDEC_DynamicParams;

/** @cond INTERNAL */

/**
 *  @brief      An implementation of the skel interface; the skeleton side
 *              of the stubs.
 */
extern SKEL_Fxns IMGDEC_SKEL;

/**
 *  @brief      Implementation of the IIMGDEC interface that is run remotely.
 */
extern IIMGDEC_Fxns IMGDEC_STUBS;

/** @endcond */

/**
 *  @brief      Definition of IIMGDEC codec class configurable parameters
 */
typedef struct IIMGDEC_CodecClassConfig {
    Bool manageInBufsCache [ XDM_MAX_IO_BUFFERS ];  
    Bool manageOutBufsCache[ XDM_MAX_IO_BUFFERS ];  
} IIMGDEC_CodecClassConfig;

/*
 *  ======== IMGDEC_create ========
 */
/**
 *  @brief      Create an instance of an image decoder algorithm.
 *
 *  Instance handles must not be concurrently accessed by multiple threads;
 *  each thread must either obtain its own handle (via IMGDEC_create()) or
 *  explicitly serialize access to a shared handle.
 *
 *  @param[in]  e       Handle to an opened engine.
 *  @param[in]  name    String identifier of the type of image decoder
 *                      to create.
 *  @param[in]  params  Creation parameters.
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the newly created image decoder
 *                              instance.
 *
 *  @remark     Depending on the configuration of the engine opened, this
 *              call may create a local or remote instance of the image
 *              decoder.
 *  @codecNameRemark
 *
 *  @sa         Engine_open()
 */
extern IMGDEC_Handle IMGDEC_create(Engine_Handle e, String name,
    IMGDEC_Params *params);


/*
 *  ======== IMGDEC_process ========
 */
/**
 *  @brief      Execute the "process" method in this instance of a image
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
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the data
 *              has been decoded.
 *
 *  @remark     The buffers supplied to IMGDEC_process() may have constraints
 *              put on them.  For example, in dual-processor, shared memory
 *              architectures, where the codec is running on a remote
 *              processor, the buffers may need to be physically contiguous.
 *              Additionally, the remote processor may place restrictions on
 *              buffer alignment.
 *
 *  @sa         IMGDEC_create(), IMGDEC_delete(), IMGDEC_control()
 */
extern Int32 IMGDEC_process(IMGDEC_Handle handle,
    XDM_BufDesc *inBufs, XDM_BufDesc *outBufs,
    IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs);

/*
 *  ======== IMGDEC_control ========
 */
/**
 *  @brief      Execute the "control" method in this instance of a image
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
 *  @retval     #IMGDEC_EOK         Success.
 *  @retval     #IMGDEC_EFAIL       Failure.
 *  @retval     #IMGDEC_ERUNTIME    Internal Runtime Error.
 *
 *  @remark     This is a blocking call, and will return after the control
 *              command has been executed.
 *
 *  @sa         IMGDEC_create(), IMGDEC_delete()
 */
extern Int32 IMGDEC_control(IMGDEC_Handle handle, IMGDEC_Cmd id,
    IMGDEC_DynamicParams *params, IMGDEC_Status *status);


/*
 *  ======== IMGDEC_delete ========
 */
/**
 *  @brief      Delete the instance of a image decoder algorithm.
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
 *  @post       All resources allocated as part of the IMGDEC_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         IMGDEC_create()
 */
extern Void IMGDEC_delete(IMGDEC_Handle handle);

#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 2,191; 1-14-2008 09:55:04; /db/atree/library/trees/ce-g30x/src/
 */

