/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== Comm.h ========
 */
#ifndef ti_sdo_ce_osal_Comm_
#define ti_sdo_ce_osal_Comm_

#ifdef __cplusplus
extern "C" {
#endif

#define Comm_GTNAME "OC"

/*
 *  ======== Comm_MSGSIZE ========
 *  Maximum size of communication buffers, defined by the configuration
 *  parameter in Global.xdc.
 */
extern UInt32 Comm_MSGSIZE;

/*
 *  ======== Comm_Queue ========
 */
typedef UInt32 Comm_Queue;

/*
 *  ======== Comm_Handle ========
 */
typedef struct Comm_Obj *Comm_Handle;

/*
 *  ======== Comm_QType ========
 */
typedef enum {
    Comm_PEND,
    Comm_CALL
} Comm_QType;

/*
 *  ======== Comm_CallFxn ========
 */
typedef Void (*Comm_CallFxn)(Ptr callHandle);

/*
 *  ======== Comm_Attrs ========
 */
typedef struct Comm_Attrs {
    Comm_QType      type;
    Ptr             callHandle;
    Comm_CallFxn    callFxn;
} Comm_Attrs;

extern Comm_Attrs Comm_ATTRS;   /* default attrs */

/*
 *  ======== Comm_MsgHeader ========
 * Comm header must be defined, but its fields are irrelevant for the user
 * Note: this header must be larger than all underlying msgq implementations
 * (which require a header to maintain message control/transport information)
 */
typedef struct Comm_MsgHeader {
    UInt32 reserved[2]; /* reserved[0] doubles as "next" in the linked list */
    UInt16 reserved1;   /* UInt16 srcProcId; */
    UInt16 reserved2;   /* UInt16 poolId; */
    UInt16 size;
    UInt32 reserved3;   /* UInt32 dstId; */
    UInt32 reserved4;   /* UInt32 srcId; */
    UInt16 msgId;
} Comm_MsgHeader, *Comm_Msg;

/*
 *  ======== Comm_INVALIDMSGQ ========
 */
#define Comm_INVALIDMSGQ    0xFFFF

/*
 *  ======== error status codes ========
 */
#define Comm_EOK            0
#define Comm_EFAIL          1

/*
 *  ======== timeout values ========
 */
#define Comm_FOREVER        ((UInt)-1)
#define Comm_POLL           ((UInt)0)

/*
 *  ======== Comm_locate ========
 *  Locate an existing communication queue
 */
extern Int Comm_locate(String queueName, Comm_Queue *queue);

/*
 *  ======== Comm_alloc ========
 *  Allocate a message that can be sent to a communication queue
 */
extern Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size);

/*
 *  ======== Comm_free ========
 *  Free a previously allocated (Comm_alloc) message
 */
extern Int Comm_free(Comm_Msg msg);

/*
 *  ======== Comm_put ========
 *  Send message to specified communication queue
 */
extern Int Comm_put(Comm_Queue queue, Comm_Msg msg);

/*
 *  ======== Comm_get ========
 *  Recieve a message from the specified queue
 */
extern Int Comm_get(Comm_Queue queue, Comm_Msg *msg, UInt timeout);

/*
 *  ======== Comm_getMsgSize ========
 *  Get size of the specified message
 */
extern Int Comm_getMsgSize(Comm_Msg msg);

/*
 *  ======== Comm_getSrcQueue ========
 *  Get id of sender queue from message
 */
extern Int Comm_getSrcQueue(Comm_Msg msg, Comm_Queue *queue);

/*
 *  ======== Comm_setSrcQueue ========
 *  Put id of sender queue into message
 */
extern Void Comm_setSrcQueue(Comm_Msg msg, Comm_Queue queue);

/*
 *  ======== Comm_create ========
 *  Create a new communication queue
 */
extern Comm_Handle Comm_create(String queueName, Comm_Queue *queue,
    Comm_Attrs *attrs);

/*
 *  ======== Comm_delete ========
 *  its evil twin, the delete() function
 */
extern Void Comm_delete(Comm_Handle msgq);

/*
 *  ======== Comm_init ========
 */
extern Bool Comm_init(Void);

/*
 *  ======== Comm_exit ========
 */
extern Void Comm_exit(Void);

/*
 *  ======== Comm_release ========
 */
extern Int Comm_release(Comm_Queue queue);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 1,267; 1-14-2008 09:55:32; /db/atree/library/trees/ce-g30x/src/
 */

