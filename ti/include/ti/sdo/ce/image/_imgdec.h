/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== _imgdec.h ========
 */
#ifndef ti_sdo_ce_image_IMGDEC_
#define ti_sdo_ce_image_IMGDEC_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/iimgdec.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IMGDEC_CPROCESS        0
#define _IMGDEC_CCONTROL        1

/* msgq message to decode */
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

            IIMGDEC_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IIMGDEC_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 512B, as the default
             * Link msg size is 4kB, the default BIOS-only config msg size is
             * 1kB... and "512B ought to be big enough for anybody".  :P
             */
            UInt8               pad[512];
        } process;
        struct {
            IIMGDEC_Cmd            id;

            IIMGDEC_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * IIMGDEC_Status      status;
             *
             * Similar to above, allow for a 512B pad here for status and
             * "extended args".
             */
            UInt8               pad[512];
        } control;
    } cmd;
} _IMGDEC_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image; 1, 0, 2,191; 1-14-2008 09:55:04; /db/atree/library/trees/ce-g30x/src/
 */

