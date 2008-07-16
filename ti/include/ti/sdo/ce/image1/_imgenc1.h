/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== _imgenc1.h ========
 */
#ifndef ti_sdo_ce_image1__IMGENC1_
#define ti_sdo_ce_image1__IMGENC1_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/iimgenc1.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IMGENC1_CPROCESS        0
#define _IMGENC1_CCONTROL        1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDM1_BufDesc        inBufs;
            XDM1_BufDesc        outBufs;

            IIMGENC1_InArgs     inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IIMGENC1_OutArgs    outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 256B, as the
             * default.
             *
             * Link msg size is 4kB, the default BIOS-only config msg size is
             * 1kB... and "256B ought to be big enough for anybody".  :P
             */
            UInt8               pad[256];
        } process;
        struct {
            IIMGENC1_Cmd           id;

            IIMGENC1_DynamicParams params;  /* size def'd by 1st field */

            /*
             * status follows params
             * IIMGENC1_Status      status;
             *
             * Similar to above, allow for a 256B pad here for status and
             * "extended args".
             */
            UInt8               pad[256];
        } control;
    } cmd;
} _IMGENC1_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 0,115; 1-14-2008 09:55:15; /db/atree/library/trees/ce-g30x/src/
 */

