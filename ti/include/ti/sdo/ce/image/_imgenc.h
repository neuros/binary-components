/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== _imgenc.h ========
 */
#ifndef ti_sdo_ce_image_IMGENC_
#define ti_sdo_ce_image_IMGENC_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/iimgenc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IMGENC_CPROCESS        0
#define _IMGENC_CCONTROL        1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            /* must flatten the above structs b/c they contain pointers */
            XDAS_Int8          *inBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numInBufs;
            XDAS_Int32          inBufSizes[XDM_MAX_IO_BUFFERS];

            XDAS_Int8          *outBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numOutBufs;
            XDAS_Int32          outBufSizes[XDM_MAX_IO_BUFFERS];

            IIMGENC_InArgs  inArgs;

            /*
             * outArgs follows inArgs
             * IIMGENC_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 512B, as the default
             * Link msg size is 4kB, the default BIOS-only config msg size is
             * 1kB... and "512B ought to be big enough for anybody".  :P
             */
            UInt8               pad[512];
        } process;
        struct {
            IIMGENC_Cmd            id;

            IIMGENC_DynamicParams  params;

            /*
             * status follows params
             * IIMGENC_Status      status;
             *
             * Similar to above, allow for a 512B pad here for status and
             * "extended args".
             */
            UInt8               pad[512];
        } control;
    } cmd;
} _IMGENC_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 2,191; 1-14-2008 09:55:04; /db/atree/library/trees/ce-g30x/src/
 */

