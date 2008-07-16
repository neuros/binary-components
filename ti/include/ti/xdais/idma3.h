/* 
 *  Copyright 2007
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/**
 *  @file       ti/xdais/idma3.h
 *
 *  @brief      IDMA3 Interface Definitions (C64P) - Allows algorithms to
 *              request and receive handles representing private logical DMA
 *              resources.
 */

/**
 *  @defgroup   DSPIDMA3 IDMA3 (C64P)
 *
 *              The IDMA3 interface enables algorithms to request and receive
 *              handles representing private logical DMA resources.
 */
#ifndef IDMA3_
#define IDMA3_

/** @ingroup    DSPIDMA3 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include "ialg.h"

/**
 *  @brief      Memory space descriptors for IDMA3_MemRec.
 */
typedef enum IDMA3_MemType {
    IDMA3_INTERNAL,             /**< Internal data memory. */
    IDMA3_EXTERNAL              /**< External data memory. */
} IDMA3_MemType;


/**
 *  @brief      Record containing attributes of the IDMA3 Channel environment
 *              memory when (optionally) the IDMA3 Channel is requested with
 *              a non-NULL IDMA3_ProtocolObj.
 */
typedef struct IDMA3_MemRec {

    /** Base address of allocated memory. */
    Void *base;

    /** Size of buffer to allocate (MAUs).  */
    Uns size;

    /**
     *  Buffer alignment (0 or a power of 2). Use the values of 0 or 1 to
     *  indicate no alignment requirements.
     */
    Uns align;

    /** Type of memory to use for allocation. */
    IDMA3_MemType memType;

} IDMA3_MemRec;


/**
 *  @brief      Handle to "logical" DMA channel.
 */
typedef struct IDMA3_Obj *IDMA3_Handle;


/**
 *  @brief      Handle to IDMA3 protocol object
 */
typedef struct IDMA3_ProtocolObj *IDMA3_ProtocolHandle;


/**
 *  @brief      NULL protocol definition
 *
 *              The NULL protocol can be used when no protocol is needed,
 *              e.g. when the algorithm directly accesses the eDMA PaRAM
 *              registers, or when the DMA driver library used does not retain
 *              any state. When the NULL protocol is used 'env' buffer is not
 *              allocated
 */
#define IDMA3_PROTOCOL_NULL ((IDMA3_ProtocolHandle)NULL)


/**
 *  @brief      IDMA3 Priority Levels.
 */
typedef enum IDMA3_Priority {

    IDMA3_PRIORITY_URGENT,
    IDMA3_PRIORITY_HIGH,
    IDMA3_PRIORITY_MEDIUM,
    IDMA3_PRIORITY_LOW

} IDMA3_Priority;


/**
 *  @brief      DMA Channel Descriptor to logical DMA channels.
 */
typedef struct IDMA3_ChannelRec {

    /** Handle to logical DMA channel */
    IDMA3_Handle handle;

    /**
     *  Number of DMA transfers that are submitted using this logical channel
     *  handle. <tt>Single (==1) or Linked ( >= 2).</tt>
     */
    Int numTransfers;

    /**
     *  Number of individual transfers that can be waited in a linked start.
     *  (1 for single transfers or for waiting all)
     */
    Int numWaits;

    /** Relative priority recommendation: High, Medium, Low. */
    IDMA3_Priority priority;

    /**
     *  When non-NULL, the protocol object provides interface for querying and
     *  initializing logical DMA channel for use by the given protocol. The
     *  protocol can be IDMA3_PROTOCOL_NULL in this case no 'env' is allocated
     *
     *  For example, when requesting a logical channel to be used with ACPY3
     *  APIs, the protocol needs to be set to &ACPY3_PROTOCOL.
     */
    IDMA3_ProtocolHandle protocol;

    /**
     *  When persistent is set to TRUE, the PaRAMs and TCCs will be allocated
     *  exclusively for this channel. They cannot be shared with any other
     *  IDMA3 channel.
     */
    Bool persistent;

} IDMA3_ChannelRec;


/**
 *  @brief      These fxns are used to query/grant the DMA resources requested
 *              by the algorithm at initialization time, and to change these
 *              resources at runtime. All these fxns are implemented by the
 *              algorithm, and called by the client of the algorithm.
 */
typedef struct IDMA3_Fxns {

    /**
     *  @brief  Unique pointer that identifies the module implementing this
     *          interface.
     */
    Void *implementationId;

    /**
     *  @brief  Apps call this whenever the logical channels are moved at
     *          runtime.
     */
    Void (*dmaChangeChannels)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec);

    /**
     *  @brief  Apps call this to query algorithm about the maximum number
     *          of logical dma channel requested.
     */
    Uns (*dmaGetChannelCnt)(Void);

    /**
     *  @brief  Apps call this to query algorithm about its dma channel
     *          requests at init time, or to get the current channel holdings.
     */
    Uns (*dmaGetChannels)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec);

    /**
     *  @brief  Apps call this to grant dma handle(s) to the algorithm at
     *          initialization. Algorithm initializes the instance object.
     */
    Int (*dmaInit)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec);

} IDMA3_Fxns;


/**
 *  @brief      These functions are used to determine memory requirements for
 *              and initialize the IDMA3 protocol's environment that will be
 *              allocated by the DMA manager.
 *
 *  @remarks    These fxns are implemented by the IDMA3
 *              protocol that is used for a given channel (e.g, ACPY3), and
 *              are passed in the IDMA3_ChannelRec structure to request a
 *              logical DMA channel. If the IDMA3 protocol does not require
 *              any particular one of these functions, it may be set to NULL.
 *
 *  @remarks    getEnvMemRec() - Called by the DMA manager when creating a
 *              logical DMA channel, to query the IDMA3 protocol's memory
 *              requirements for its environment.
 *
 *  @remarks    initHandle() - Called by the DMA manager after allocation the
 *              environment, to allow the IDMA3 protocol to do any
 *              initialization of its environment.
 *
 *  @remarks    deInitHandle() - Called by the DMA manager when a channel is
 *              freed, so that the IDMA3 protocol can do any required
 *              de-initialization or freeing any memory that may have been
 *              allocated in initHandle().
 */
typedef struct IDMA3_ProtocolObj {

    /**
     *  Name of the protocol
     */
    String name;

    /**
     *  Fill in the IDMA3_MemRec with the memory attributes needed for
     *  allocation of the IDMA3 protocol's environment buffer.
     */
    Void (*getEnvMemRec)(IDMA3_ChannelRec *chnlRec, IDMA3_MemRec *memRec);

    /**
     *  Initialize the env stored in the IDMA3 channel handle. Return TRUE on
     *  success, FALSE otherwise. If FALSE is returned channel creation will
     *  fail.
     *
     *  When (and if) the framework/resource manager allocates requested
     *  internal 'env' memory as 'scratch', the 'env' pointer passed in the
     *  IDMA3_Handle points to a persistent, private memory which contains
     *  the address of the 'scratch' allocated 'internal' 'env' memory in the
     *  first word of the 'persistent' 'env' pointer.
     *  If the first word of the env memory is NULL, then no separate 'scratch'
     *  memory has been allocated and 'env' memory itself is 'persistent'.
     */
    Bool (*initHandle)(IDMA3_Handle handle);

    /**
     *  De-Initialize the env stored in the IDMA3 channel handle, before it is
     *  freed by the DMA manager.
     */
    Bool (*deInitHandle)(IDMA3_Handle handle);

} IDMA3_ProtocolObj;


/**
 *  @brief      IDMA3_Obj holds the private state associated with each
 *              logical DMA channel.
 */
typedef struct IDMA3_Obj {

    /** The number of TCCs allocated to this channel. */
    unsigned short numTccs;

    /** The number of PaRam entries allocated to this channel. */
    unsigned short numPaRams;

    /** TCCs assigned to channel */
    unsigned char *tccTable;

    /** PaRAMs assigned to channel */
    Uns *paRamAddr;

    /** Physical QDMA Channel assigned to handle */
    unsigned short qdmaChan;

    /**
     *  Set to true when a new transfer is started on this channel. Set to
     *  false when a wait/sync operation is performed on this channel.
     */
    Bool transferPending;

    /**
     *  IDMA3_ProtocolHandle ('protocol') dependent private channel memory.
     *  The memory for the 'env' is allocated and reclaimed by the framework
     *  when this IDMA3 channel has been requested with a non-NULL 'protocol'.
     *
     *  The size, type and alignment of the allocated 'env' memory is
     *  obtained by calling the channel's 'protocol'->getEnvMemRec() function.
     *
     *  During channel creation, the 'env' pointer must always be created as a
     *  private & persistent memory assigned to the IDMA3 channel object.
     *  However, the framework/resource manager is also allowed to allocate
     *  requested internal 'env' memory as 'scratch' memory which can
     *  only be used when the channel is in active state.
     *  In the 'scratch' allocation case, the framework/resource manager
     *  must still allocate the 'env' as 'persistent',  possibly in
     *  external memory, and must pass the address of the 'scratch' 'internal'
     *  'env' memory in the first word of the 'env' memory.
     *
     *  If the channel 'env' memory is created as 'persistent' with no
     *  'scratch' shadow, then the first word  of the env memory must be
     *  set to NULL.
     */
    Void *env;

    /**
     *  The channel protocol functions used by the DMA manager to determine
     *  memory requirements for the 'env'
     */
    IDMA3_ProtocolHandle protocol;

    /** Indicates if the channel has been allocated with persistent property.*/
    Bool persistent;

} IDMA3_Obj;


/*@}*/


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* IDMA3_ */

/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

