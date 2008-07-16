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
 *  ======== _videnc1.h ========
 */
#ifndef ti_sdo_ce_video1__VIDENC1_
#define ti_sdo_ce_video1__VIDENC1_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividenc1.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _VIDENC1_CPROCESS        0
#define _VIDENC1_CCONTROL        1

/* msgq message to encode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            IVIDEO1_BufDescIn   inBufs;

            /* must flatten outBufs struct b/c they contain pointers */
            XDAS_Int8          *outBufs[XDM_MAX_IO_BUFFERS];
            XDAS_Int32          numOutBufs;
            XDAS_Int32          outBufSizes[XDM_MAX_IO_BUFFERS];

            IVIDENC1_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * IVIDENC1_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 2kB, as the default
             * Link msg size is 4kB.
             */
            UInt8               pad[2096];
        } process;
        struct {
            IVIDENC1_Cmd            id;

            IVIDENC1_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * IVIDENC1_Status      status;
             *
             * Similar to above, allow for a 2kB pad here for status and
             * "extended args".
             */
            UInt8               pad[2096];
        } control;
    } cmd;
} _VIDENC1_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.video1; 1, 0, 0,112; 1-14-2008 09:58:06; /db/atree/library/trees/ce-g30x/src/
 */

