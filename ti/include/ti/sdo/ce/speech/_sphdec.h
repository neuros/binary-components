/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== _sphdec.h ========
 */
#ifndef ti_sdo_ce_speech_SPHDEC_
#define ti_sdo_ce_speech_SPHDEC_

#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/isphdec.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SPHDEC_CPROCESS        0
#define _SPHDEC_CCONTROL        1

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

            ISPHDEC_InArgs      inArgs;     /* size def'd by 1st field */

            /*
             * outArgs follows inArgs
             * ISPHDEC_OutArgs     outArgs;
             *
             * Add a pad here for outArgs, plus "extended args".
             * But, how big is "big enough"?!?  We'll guess 256B, as the default
             * Link msg size is 4kB, the default BIOS-only config msg size is
             * 1kB... and "256B ought to be big enough for anybody".  :P
             */
            UInt8               pad[256];
        } process;
        struct {
            ISPHDEC_Cmd            id;

            ISPHDEC_DynamicParams params;   /* size def'd by 1st field */

            /*
             * status follows params
             * ISPHDEC_Status      status;
             *
             * Similar to above, allow for a 256B pad here for status and
             * "extended args".
             */
            UInt8               pad[256];
        } control;
    } cmd;
} _SPHDEC_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 1,257; 1-14-2008 09:55:56; /db/atree/library/trees/ce-g30x/src/
 */

