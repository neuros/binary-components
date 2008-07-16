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
 *  ======== _viddec2.h ========
 */
#ifndef ti_sdo_ce_video2__VIDDEC2_
#define ti_sdo_ce_video2__VIDDEC2_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividdec2.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _VIDDEC2_CPROCESS        0
#define _VIDDEC2_CCONTROL        1

/* msgq message to decode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDM1_BufDesc        inBufs;

            /* must flatten outBufs struct b/c they contain pointers */
            XDAS_Int8          *outBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numOutBufs;
            XDAS_Int32          outBufSizes[XDM_MAX_IO_BUFFERS];

            IVIDDEC2_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IVIDDEC2_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 2kB, as the default
             * Link msg size is 4kB.
             */
            UInt8               pad[2096];
        } process;
        struct {
            IVIDDEC2_Cmd             id;

            IVIDDEC2_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * IVIDDEC2_Status      status;
             *
             * Similar to above, allow for a 2kB pad here for status and
             * "extended args".
             */
            UInt8               pad[2096];
        } control;
    } cmd;
} _VIDDEC2_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video2; 1, 0, 0,15; 1-14-2008 09:58:15; /db/atree/library/trees/ce-g30x/src/
 */

