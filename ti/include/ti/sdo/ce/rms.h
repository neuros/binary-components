/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== rms.h ========
 *  Resource Manager Server (RMS) module header file
 */
#ifndef RMS_
#define RMS_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/ce/node/_node.h>


/*
 *  The RMS protocol version is used to ensure that the server and the codec
 *  engine can communicate with eachother. In order for the Codec Engine to
 *  operate with a given server, the RMS_VERSION_MAJOR must be the same, and
 *  the RMS_VERSION_MINOR of the server must be >= the RMS_VERSION_MINOR of
 *  the Codec Engine. The RMS_VERSION_SOURCE is always left as 0, and is only
 *  here for consistency with CE library versioning conventions.
 *
 *  When commands are added to the RMS server, the RMS_VERSION_MINOR must
 *  be updated. This will allow a server that supports more commands to work
 *  with an older Codec Engine.
 *  If compatibility is completely broken, then RMS_VERSION_MAJOR
 *  must be updated.
 */
#define RMS_VERSION_MAJOR 1
#define RMS_VERSION_SOURCE 0
#define RMS_VERSION_MINOR 2

/*
 *  DSP-side definitions.
 */
typedef UInt    RMS_Word;
typedef Char    RMS_Char;
typedef UInt32  RMS_Status;
typedef UInt32  RMS_Value;

/* GPP<->DSP Message Structure: */
typedef struct {
    RMS_Word cmd;                       /* Message code */
    RMS_Word arg1;                      /* First message argument */
    RMS_Word arg2;                      /* Second message argument */
} RMS_Msg;


/*
 *  RMS commands.
 */
typedef enum RMS_CmdSet {
    RMS_CREATENODE,     /* Create node */
    RMS_STARTNODE,      /* Start node running */
    RMS_DELETENODE,     /* Delete node */
    RMS_GETMEMSTAT,     /* Get total amount of memory used */
    RMS_GETCPUSTAT,     /* Get CPU load */
    RMS_GETTRACE,       /* Get contents of trace buffer */
    RMS_GETVERS,        /* Get CE library version string */
    RMS_WRITEWORD,      /* Write a single word to memory */
    RMS_SETTRACEMASK,   /* Set trace mask */
    RMS_GETNUMSEGS,     /* Get number of memory heaps */
    RMS_GETSEGSTAT,     /* Get MEM stats for a given heap segment */
    RMS_REDEFINEHEAP,   /* Redefine the base and size of a heap */
    RMS_RESTOREHEAP,    /* Reset heap base and size to original values */
    RMS_REQTRACETOKEN,  /* Request trace token for collecting trace & LOGs */
    RMS_RELTRACETOKEN   /* Release trace token back to RMS */
/*
 *  If a command is added here, RMS_VERSION_MINOR must be incremented!
 */

} RMS_CmdSet;

/* Note, this must be "big enough" to hold all node create params. */
#define RMS_MAXARGSLENGTH   32      /* in words */
#define RMS_READBUFSIZE     512     /* in chars */

#define RMS_MAXSEGNAMELENGTH 32   /* in chars */

typedef struct RMS_CmdSetCreateNodeIn {
    NODE_Uuid   uuid;
    RMS_Word    gppQueue;
    RMS_Word    nodePriority;          /* -1: ignore, use default */
    RMS_Word    nodeBlockingTimeout;   /* -1: ignore, use default */
    RMS_Word    argBuffer[RMS_MAXARGSLENGTH];
    RMS_Word    argLength;             /* in bytes, not RMS words */
    RMS_Word    rpcProtocolVersion;    /* -1: ignore, use default */
    RMS_Word    useExtHeap;            /* 1: use single external heap for
                                        * allocating alg's memory, 0: use
                                        * algAlloc() mem requests.
                                        */
    /* todo: include node attrs and other things */
} RMS_CmdSetCreateNodeIn;

/* todo: the above limits args to RMS_MAXARGSLENGTH. DSPNode and the RMS */
/* should have a protocol that if GPP wants to send more than that, */
/* arbitarily long data should arrive in a separate message. */
/* this wouldn't be an issue if all memory was shared. */

typedef struct RMS_CmdSetCreateNodeOut {
    RMS_Word node;
    RMS_Word nodeQueue;
    RMS_Word remoteVisa;
    /* todo: should this include node instance name or id? */
} RMS_CmdSetCreateNodeOut;

typedef struct RMS_CmdSetExecuteNodeIn {
    RMS_Word node;
} RMS_CmdSetExecuteNodeIn;

typedef struct RMS_CmdSetDeleteNodeIn {
    RMS_Word node;
} RMS_CmdSetDeleteNodeIn;

typedef struct RMS_CmdSetDeleteNodeOut {
    RMS_Word node;
    RMS_Word stackSize;
    RMS_Word stackUsed;
} RMS_CmdSetDeleteNodeOut;

typedef struct RMS_CmdSetGetCpuStatOut {
    RMS_Value cpuLoad;
} RMS_CmdSetGetCpuStatOut;

typedef struct RMS_CmdSetGetTraceIn {
    RMS_Value curTime;       /* remote time */
} RMS_CmdSetGetTraceIn;

typedef struct RMS_CmdSetGetTraceOut {
    RMS_Word size;          /* number of chars copied into buf */
    RMS_Word max;           /* max size of trace buffer */
    RMS_Word avail;         /* number of remaining chars to read */
    RMS_Word lost;          /* number of chars lost due to overflow */
    RMS_Word buf[RMS_READBUFSIZE / sizeof (RMS_Word)];
} RMS_CmdSetGetTraceOut;

#define RMS_MAXTRACEMASKSIZE RMS_READBUFSIZE

typedef struct RMS_CmdSetSetTraceMaskIn {
    RMS_Word traceMask[RMS_MAXTRACEMASKSIZE / sizeof (RMS_Word) + 1];
} RMS_CmdSetSetTraceMaskIn;

typedef struct RMS_CmdSetGetVersOut {
    /* String for CE library version */
    RMS_Word vers[RMS_READBUFSIZE / sizeof (RMS_Word)];

    /*
     *  RMS RPC protocol version. Consists of major, source, and minor
     *  version numbers.
     */
    RMS_Word rpcMajor;
    RMS_Word rpcSource;
    RMS_Word rpcMinor;
} RMS_CmdSetGetVersOut;

typedef struct RMS_CmdSetGetMemStatOut {
    RMS_Value used;
} RMS_CmdSetGetMemStatOut;

/* Out data for RMS_GETNUMSEGS */
typedef struct RMS_CmdSetGetNumSegsOut {
    RMS_Word numSegs;
} RMS_CmdSetGetNumSegsOut;

/* In data for RMS_GETSEGSTAT */
typedef struct RMS_CmdSetGetSegStatIn {
    RMS_Word segId;         /* Id of segment to get Memory stats for. */
} RMS_CmdSetGetSegStatIn;

/* Out data for RMS_GETSEGSTAT */
typedef struct RMS_CmdSetGetSegStatOut {
    /* name of memory segment */
    RMS_Word name[RMS_MAXSEGNAMELENGTH / sizeof(RMS_Word) + 1];
    RMS_Word base;                    /* Base address of memory segment */
    RMS_Word size;                    /* Original size of memory segment */
    RMS_Word used;                    /* number of (DSP) bytes used */
    RMS_Word maxBlockLen;             /* Size of largest free block */
} RMS_CmdSetGetSegStatOut;

/* In data for RMS_REDEFINEHEAP */
typedef struct RMS_CmdSetRedefineHeapIn {
    /* Name of heap (up to RMS_MAXSEGNAMELENGTH chars) */
    RMS_Word name[RMS_MAXSEGNAMELENGTH / sizeof(RMS_Word) + 1];
    RMS_Word base;                    /* New base address of DDRALGHEAP */
    RMS_Word size;                    /* New size of DDRALGHEAP */
} RMS_CmdSetRedefineHeapIn;

/* In data for RMS_RESTOREHEAP */
typedef struct RMS_CmdSetRestoreHeapIn {
    /* Name of heap (up to RMS_MAXSEGNAMELENGTH chars) */
    RMS_Word name[RMS_MAXSEGNAMELENGTH / sizeof(RMS_Word) + 1];
} RMS_CmdSetRestoreHeapIn;

typedef struct RMS_CmdSetWriteWordIn {
    RMS_Word addr;
    RMS_Word value;
} RMS_CmdSetWriteWordIn;

typedef struct RMS_CmdBuf {
    RMS_Word    cmd;                            /* command */
    RMS_Status  status;                         /* command return status */
    union {                                     /* command parameters */
        RMS_CmdSetCreateNodeIn   createNodeIn;
        RMS_CmdSetCreateNodeOut  createNodeOut;
        RMS_CmdSetExecuteNodeIn  startNodeIn;
        RMS_CmdSetDeleteNodeIn   deleteNodeIn;
        RMS_CmdSetDeleteNodeOut  deleteNodeOut;
        RMS_CmdSetWriteWordIn    writeWordIn;
        RMS_CmdSetGetMemStatOut  getMemStatOut;
        RMS_CmdSetGetCpuStatOut  getCpuStatOut;
        RMS_CmdSetGetTraceIn     getTraceIn;
        RMS_CmdSetGetTraceOut    getTraceOut;
        RMS_CmdSetGetVersOut     getVersOut;
        RMS_CmdSetSetTraceMaskIn setTraceMaskIn;

        /* MEM stat commands */
        RMS_CmdSetGetNumSegsOut  getNumSegsOut;
        RMS_CmdSetGetSegStatIn   getSegStatIn;
        RMS_CmdSetGetSegStatOut  getSegStatOut;

        /* Redefine and restore heap commands */
        RMS_CmdSetRedefineHeapIn redefineHeapIn;
        RMS_CmdSetRedefineHeapIn restoreHeapIn;
    } data;
} RMS_CmdBuf;

/* Memory Types: */
#define RMS_CODE                0    /* Program space */
#define RMS_DATA                1    /* Data space */
#define RMS_IO                  2    /* I/O space */

/* Pre-Defined Command/Response Codes: */
#define RMS_EXIT                0x80000000  /* GPP->Node: shutdown */
#define RMS_EXITACK             0x40000000  /* Node->GPP: ack shutdown */
#define RMS_USER                0x0     /* Start of user-defined msg codes */
#define RMS_MAXUSERCODES        0xfff   /* Maximum user defined C/R Codes */

/* Pre-Defined Return Codes: */
/*
 * NOTE: The following error codes are defined to map directly to the
 * DSP/BIOS Bridge API error codes, to eliminate a translation layer.  Any
 * changes must be synchronized to the API definition, and to the GPP-side
 * implementation.
 */
#define RMS_SBASE        0x00008000         /* Base for success codes */
#define RMS_EBASE        0x80008000         /* Base for error codes */

#define RMS_EOK          (RMS_SBASE + 0)    /* Success */

#define RMS_EFAIL        (RMS_EBASE + 0x8)  /* General failure */
#define RMS_EFREE        (RMS_EBASE + 0x2a) /* Memory free failure */
#define RMS_EIOFREE      (RMS_EBASE + 0x2b) /* I/O free failure */
#define RMS_EMULINST     (RMS_EBASE + 0x2c) /* Mult. instances not allowed*/
#define RMS_ENOTFOUND    (RMS_EBASE + 0x2d) /* Entity not found */
#define RMS_ENOTIMPL     (RMS_EBASE + 0x10) /* Not implemented yet */
#define RMS_EOUTOFIO     (RMS_EBASE + 0x2e) /* I/O resource not available */
#define RMS_EOUTOFMEMORY (RMS_EBASE + 0xc)  /* Memory allocation failed */
#define RMS_ERESOURCE    (RMS_EBASE + 0x28) /* Resource not available */
#define RMS_ESTREAM      (RMS_EBASE + 0x15) /* Stream create failed */
#define RMS_ETASK        (RMS_EBASE + 0x16) /* Task create failed */

#define RMS_EINVUUID     (RMS_EBASE + 0x17) /* Invalid DSP node UUID  */
#define RMS_EINVPROT     (RMS_EBASE + 0x18) /* Stub/Skel protocols dont match */
#define RMS_EWRONGSTATE  (RMS_EBASE + 0x19) /* Wrong state for server op. */
#define RMS_EINVAL       (RMS_EBASE + 0x1a) /* Bad input parameter */

#define RMS_EUSER1       (RMS_EBASE + 0x40) /* Node-specific error 1 */
#define RMS_EUSER2       (RMS_EBASE + 0x41) /* Node-specific error 2 */
#define RMS_EUSER3       (RMS_EBASE + 0x42) /* Node-specific error 3 */
#define RMS_EUSER4       (RMS_EBASE + 0x43) /* Node-specific error 4 */
#define RMS_EUSER5       (RMS_EBASE + 0x44) /* Node-specific error 5 */
#define RMS_EUSER6       (RMS_EBASE + 0x45) /* Node-specific error 6 */
#define RMS_EUSER7       (RMS_EBASE + 0x46) /* Node-specific error 7 */
#define RMS_EUSER8       (RMS_EBASE + 0x47) /* Node-specific error 8 */
#define RMS_EUSER9       (RMS_EBASE + 0x48) /* Node-specific error 9 */
#define RMS_EUSER10      (RMS_EBASE + 0x49) /* Node-specific error 10 */
#define RMS_EUSER11      (RMS_EBASE + 0x4a) /* Node-specific error 11 */
#define RMS_EUSER12      (RMS_EBASE + 0x4b) /* Node-specific error 12 */
#define RMS_EUSER13      (RMS_EBASE + 0x4c) /* Node-specific error 13 */
#define RMS_EUSER14      (RMS_EBASE + 0x4d) /* Node-specific error 14 */
#define RMS_EUSER15      (RMS_EBASE + 0x4e) /* Node-specific error 15 */
#define RMS_EUSER16      (RMS_EBASE + 0x4f) /* Node-specific error 16 */

/* name of the RMS server's input command queue */
#define RMS_CMDQNAME "rmsq"

/* RMS configuration data structure */
typedef struct RMS_Config {
    Int tskPriority;
    UInt tskStacksize;
    UInt tskStackseg;
} RMS_Config;

/* definition of the default RMS configuration data set */
#define RMS_CONFIGDEFAULT {        \
    1,    /* tskPriority  */       \
    2048, /* tskStacksize */       \
    0     /* tskStackseg  */       \
}

/* The format of the Comm message exchanged between the Engine and RMS */
typedef struct RMS_RmsMsg {
    NODE_MsgHeader  header;
    RMS_CmdBuf      cmdBuf;
} RMS_RmsMsg;

/* default RMS configuration set (== RMS_CONFIGDEFAULT) */
extern RMS_Config RMS_CONFIG;

/* RMS configuration set the user must provide; */
extern RMS_Config RMS_config;

/* database of all nodes in the system */
extern NODE_Desc RMS_nodeTab[];

/* function prototypes */
extern Void RMS_init(Void);
extern Void RMS_exit(Void);

#ifdef __cplusplus
}
#endif /* extern "C"  */

#endif /* RMS_ */

/*! Revision History
 *! ================
 *! 21-Feb-2005 dm      Created.
 *! */
/*
 *  @(#) ti.sdo.ce; 1, 0, 5,267; 1-14-2008 09:48:56; /db/atree/library/trees/ce-g30x/src/
 */

