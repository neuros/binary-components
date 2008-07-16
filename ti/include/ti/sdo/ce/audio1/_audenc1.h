/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== _audenc1.h ========
 */
#ifndef ti_sdo_ce_audio1__AUDENC1_
#define ti_sdo_ce_audio1__AUDENC1_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/iaudenc1.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _AUDENC1_CPROCESS        0
#define _AUDENC1_CCONTROL        1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDM1_BufDesc        inBufs;
            XDM1_BufDesc        outBufs;

            IAUDENC1_InArgs     inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IAUDENC1_OutArgs    outArgs;
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
            IAUDENC1_Cmd           id;

            IAUDENC1_DynamicParams params;  /* size def'd by 1st field */

            /*
             * status follows params
             * IAUDENC1_Status      status;
             *
             * Similar to above, allow for a 256B pad here for status and
             * "extended args".
             */
            UInt8               pad[256];
        } control;
    } cmd;
} _AUDENC1_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.audio1; 1, 0, 0,118; 1-14-2008 09:49:23; /db/atree/library/trees/ce-g30x/src/
 */

