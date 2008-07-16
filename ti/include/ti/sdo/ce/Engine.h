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
 *  ======== Engine.h ========
 */

/**
 *  @file       ti/sdo/ce/Engine.h
 *
 *  @brief      The Codec Engine Runtime.  Provides the user an inteface to
 *              open and manipulate an engine which can instantiate
 *              and communicate with xDAIS algorithms that run either
 *              on the local CPU or on a "remote" DSP Server.
 */
/**
 *  @addtogroup   CODECENGINE     Codec Engine Runtime
 */

#ifndef Engine_
#define Engine_

#ifdef __cplusplus
extern "C" {
#endif


#include <ti/sdo/ce/Server.h>
#include <ti/sdo/ce/osal/Comm.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/ce/node/node.h>

#include <stddef.h> /* def of size_t */
#include <stdio.h>  /* def of FILE * */

/** @ingroup    CODECENGINE */
/*@{*/

/**
 *  @brief      Trace name for the Engine module
 */
#define Engine_GTNAME "CE"

/**
 *  @brief      Opaque handle to an engine.
 */
typedef struct Engine_Obj *Engine_Handle;

/**
 *  @brief      Engine error code
 */
typedef Int Engine_Error;

#define Engine_EOK          0   /**< Success. */
#define Engine_EEXIST       1   /**< Name does not exist. */
#define Engine_ENOMEM       2   /**< Unable to allocate memory. */
#define Engine_EDSPLOAD     3   /**< Unable to load the DSP. */
#define Engine_ENOCOMM      4   /**< Unable to create a comm connection to
                                 *   the DSP.
                                 */
#define Engine_ENOSERVER    5   /**< Unable to locate the server on the DSP. */
#define Engine_ECOMALLOC    6   /**< Unable to allocate communication buffer. */
#define Engine_ERUNTIME     7   /**< Internal engine runtime failure. */
#define Engine_ECODECCREATE 8   /**< Creation of the Codec failed. */
#define Engine_ECODECSTART  9   /**< Start of the Codec failed.  For codecs
                                 *   which are implemented as a thread, this
                                 *   implies that the codec thread of execution
                                 *   failed to start.
                                 */
#define Engine_EINVAL       10  /**< Bad paramater passed to method. */
#define Engine_EBADSERVER   11  /**< Incompatible server specified. */
#define Engine_ENOTAVAIL    12  /**< Service not available. */
#define Engine_EWRONGSTATE  13  /**< Call can not be made at this time. */
#define Engine_EINUSE       14  /**< Call can't be made at this time because
                                 *   a required resource is in use.
                                 */
#define Engine_ENOTFOUND    15  /**< Entity was not found. */

/** @cond INTERNAL */

/**
 *  @brief      Opaque handle to a node.
 */
typedef struct Engine_NodeObj *Engine_Node;

/** @endcond */

/**
 *  @brief      Attributes of an Engine
 *
 *  @sa         Engine_open() and Engine_ATTRS.
 */
typedef struct Engine_Attrs {
    String procId;  /**< id of the processor that runs the server; only
                     *   needed in the case that there's more than one
                     *   processor that can provide the same server.
                     */
} Engine_Attrs;

/**
 *  @brief      Properties of an Engine algorithm
 *
 *  @sa         Engine_getAlgInfo()
 */
typedef struct Engine_AlgInfo {
    Int         algInfoSize;    /**< Size of this structure. */
    String      name;           /**< Name of algorithm. */
    String      *typeTab;       /**< Inheritance hierarchy. */
    Bool        isLocal;        /**< If TRUE, run locally. */
} Engine_AlgInfo;

/**
 *  @brief      Default engine attributes.
 */
extern Engine_Attrs Engine_ATTRS;    /**< Default attrs. */

/** @cond INTERNAL */

typedef Int Engine_Ctrl;

#define Engine_CEXIT    0
#define Engine_MAXSEGNAMELENGTH 32

/*
 *  ======== Engine_AlgDesc ========
 */
typedef struct Engine_AlgDesc {
    String      name;           /**< Name of algorithm. */
    NODE_Uuid   uuid;           /**< Fixed length perfect hash of name. */
    IALG_Fxns   *fxns;          /**< If null, served by RMS. */
    Ptr         idmaFxns;       /**< DMA resource negotiation when not null. */
    String      *typeTab;       /**< inheritance hierarchy. */
    Bool        isLocal;        /**< if TRUE, run locally. */
    Int         groupId;        /**< Resource sharing group Id. */
    Int         rpcProtocolVersion; /**< Protocol version. */
    Ptr         iresFxns;       /**< IRES_Fxns when not null. */
    Void        *codecClassConfig; /**< codec class config data, if any */
} Engine_AlgDesc;

/*
 *  ======== Engine_AlgCreateAttrs ========
 */
typedef struct Engine_AlgCreateAttrs {
    Bool            useExtHeap; /**< Use a single external heap for alg's
                                 *   memory requests if TRUE, otherwise attempt
                                 *   to honor the alg's algAlloc() function for
                                 *   memory heap assignments.
                                 */
    Int             priority;   /**< Alg instance priority (-1: use value from
                                 *   configuration). */
} Engine_AlgCreateAttrs;

/*
 *  ======== Engine_Desc ========
 */
typedef struct Engine_Desc {
    String          name;       /**< Name of this server. */
    Engine_AlgDesc  *algTab;    /**< Table of algs served by this server. */
    String          remoteName; /**< Name of remote DSP RMS server. */
    String          linkCfg;    /**< Link config for DSP (when using LAD). */
    Int             numAlgs;    /**< Number of algorithms served by this
                                 *   server. */
} Engine_Desc;

/*
 *  ======== Engine_Config ========
 */
typedef struct Engine_Config {
    Engine_Desc *engineTab;
    String      localEngine;
} Engine_Config;

/*
 *  ======== Engine_MemStat ========
 *  This structure must match Server_MemStat.
 */
typedef struct Engine_MemStat {
    Char   name[Engine_MAXSEGNAMELENGTH + 1]; /* Name of memory segment */
    Uint32 base;           /* Base address of memory segment */
    Uint32 size;           /* Original size of the memory segment. */
    Uint32 used;           /* Number of bytes used. */
    Uint32 maxBlockLen;    /* Size of the largest contiguous free block. */
} Engine_MemStat;

/* Default alg create attributes */
extern Engine_AlgCreateAttrs Engine_ALGCREATEATTRS;

/*
 *  ======== Engine_config ========
 */
extern Engine_Config Engine_config;

/*
 *  ======== Engine_call ========
 */
extern Int Engine_call(Engine_Node node, Comm_Msg *msg);

/*
 *  ======== Engine_ctrlNode ========
 */
extern Int Engine_ctrlNode(Engine_Node node, Comm_Msg *msg, Engine_Ctrl code);

/** @endcond */

/*
 *  ======== Engine_close ========
 */
/**
 *  @brief      Close an Engine.
 *
 *  @param[in]  engine          The handle to an engine, previously acquired
 *                              by a call to Engine_open().
 *
 *  @pre        @c engine must not be referenced by any codec instance
 *              object; i.e., you must first delete all codec instances
 *              associated with @c engine before closing it.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle which is
 *              in the open state.
 *
 */
extern Void Engine_close(Engine_Handle engine);

/** @cond INTERNAL */
/*
 *  ======== Engine_createNode ========
 */
/**
 *  @brief      Create a remote algorithm.
 *
 *  @param[in]  engine          The handle to an engine, previously acquired
 *                              by a call to Engine_open().
 *  @param[in]  name            Name of the algorithm to create.
 *  @param[in]  msgSize         Size of the internal message required to
 *                              communicate with the remote algorithm.
 *  @param[in]  nodeAttrs       Creation parameters for the remote algorithm.
 *  @param[in]  attrs           Attributes used by the framework for creating
 *                              the remote algorithm.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle which is
 *              in the open state.
 */
extern Engine_Node Engine_createNode(Engine_Handle engine, String name,
    size_t msgSize, IALG_Params *nodeAttrs, Engine_AlgCreateAttrs *attrs);


/*
 *  ======== Engine_createNode2 ========
 */
/**
 *  @brief      Create a remote algorithm.
 *
 *  @param[in]  engine          The handle to an engine, previously acquired
 *                              by a call to Engine_open().
 *  @param[in]  name            Name of the algorithm to create.
 *  @param[in]  msgSize         Size of the internal message required to
 *                              communicate with the remote algorithm.
 *  @param[in]  nodeAttrs       Creation parameters for the remote algorithm.
 *  @param[in]  nodeAttrsSize   Size of @c nodeAttrs.
 *  @param[in]  attrs           Attributes used by the framework for creating
 *                              the remote algorithm.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle which is
 *              in the open state.
 *
 *  @remark     Engine_createNode() is the preferred method to create remote
 *              algorithms.  However, some algorithm interfaces incorrectly
 *              fail to provide a size field of type "Int" as the first field
 *              in their creation parameters, which the xDAIS spec defines.
 *              This service allows the creation of remote algorithms where the
 *              size of the creation params is specified "some other way" than
 *              the xDAIS spec defines.
 *
 */
extern Engine_Node Engine_createNode2(Engine_Handle engine, String name,
    size_t msgSize, IALG_Params *nodeAttrs, Int nodeAttrsSize,
    Engine_AlgCreateAttrs *attrs);


/*
 *  ======== Engine_deleteNode ========
 */
extern Void Engine_deleteNode(Engine_Node node);


/*
 *  ======== Engine_getConstName ========
 */
extern String Engine_getConstName(Engine_Handle engine, String name,
    String type);

/*
 *  ======== Engine_getFxns ========
 */
extern IALG_Fxns *Engine_getFxns(Engine_Handle svr, String name,
    String type, Bool *isLocal, Ptr *idmaFxns, Ptr *iresFxns, Int *groupId);

/*
 *  ======== Engine_getMemId ========
 */
extern Int Engine_getMemId(Engine_Handle engine);

/*
 *  ======== Engine_getLocalEngine ========
 */
extern Engine_Handle Engine_getLocalEngine(Void);

/*
 *  ======== Engine_getEngine ========
 */
extern Engine_Handle Engine_getEngine(Engine_Node node);

/*
 *  ======== Engine_getMemStat ========
 */
extern Engine_Error Engine_getMemStat(Server_Handle server, Int segNum,
    Engine_MemStat *stat);

/*
 *  ======== Engine_getNumMemSegs ========
 */
extern Engine_Error Engine_getNumMemSegs(Server_Handle server, Int *numSegs);

/*
 *  ======== Engine_hasServer ========
 */
extern Bool Engine_hasServer(Engine_Handle engine);

/*
 *  ======== Engine_init ========
 */
extern Void Engine_init(Void);

/*
 *  ======== Engine_getRemoteVisa ========
 */
extern UInt32 Engine_getRemoteVisa(Engine_Node node);

/*
 *  ======== Engine_getCodecClassConfig ========
 */
extern Ptr Engine_getCodecClassConfig(Engine_Handle engine, String name,
    String type);

/*
 *  ======== Engine_getNodeQueues ========
 */
extern Void Engine_getNodeQueues(Engine_Node node, Comm_Queue *stdIn, Comm_Queue *stdOut);

/*
 *  ======== Engine_redefineHeap ========
 */
extern Engine_Error Engine_redefineHeap(Server_Handle server, String name,
        Uint32 base, Uint32 size);

/*
 *  ======== Engine_releaseTraceToken ========
 */
extern Bool Engine_releaseTraceToken(Server_Handle server);

/*
 *  ======== Engine_requestTraceToken ========
 */
extern Engine_Error Engine_requestTraceToken(Server_Handle server);

/*
 *  ======== Engine_restoreHeap ========
 */
extern Engine_Error Engine_restoreHeap(Server_Handle server, String name);

/** @endcond */

/*
 *  ======== Engine_open ========
 */
/**
 *  @brief Open an Engine.
 *
 *  The handle returned may be used to create one or more instances of a codec
 *  "contained" in the specified engine.
 *
 *  An engine may be opened more than once; each open returns a unique
 *  handle that can be used to create codec instances or get status of any
 *  underlying server.
 *
 *  Engine handles must not be concurrently accessed by multiple threads; each
 *  thread must either obtain its own handle (via Engine_open()) or explicitly
 *  serialize access to a shared handle.
 *
 *  @param[in]  name            The name of the engine to open.  @c name is
 *                              specified in the engine configuration.
 *  @param[in]  attrs           Attributes for the open engine.
 *  @param[out] ec              Optional output error code
 *
 *  @retval     NULL            An error has occurred.
 *  @retval     non-NULL        The handle to the opened engine.
 *
 *  @pre        @c name is a non-NULL string.
 *
 *  @pre        @c name is a valid, pre-configured name of an engine.
 *
 *  @pre        As with all Codec Engine API's, CERuntime_init() must have
 *              previously been called.
 *
 *  @post       If the return handle is NULL and @c ec is non-NULL, @c *ec
 *              is set to a non-zero value indicating the cause of the failure.
 *
 *  @post       If @c ec is non-NULL, the Engine_Error value is set to one of
 *              the following values:
 *                - #Engine_EOK         success
 *                - #Engine_EEXIST      name does not exist
 *                - #Engine_ENOMEM      can't allocate memory
 *                - #Engine_EDSPLOAD    can't load the DSP
 *                - #Engine_ENOCOMM     can't create a comm connection to DSP
 *                - #Engine_ENOSERVER   can't locate the server on the DSP
 *                - #Engine_ECOMALLOC   can't allocate communication buffer
 */
extern Engine_Handle Engine_open(String name, Engine_Attrs *attrs,
    Engine_Error *ec);

/*
 *  ======== Engine_fwriteTrace ========
 */
/**
 *  @brief              Write Server's trace buffer to specifed file stream
 *
 *  @param[in]  engine  The handle to the opened engine.
 *
 *  @param[in]  prefix  A string to prepend to each line output; this
 *                      allows one to easily identify trace from the
 *                      server from the application's trace, for
 *                      example.
 *  @param[in]  out     A open FILE stream used to output the
 *                      Server's trace characters.
 *
 *  @retval             Integer number of characters copied to the specified
 *                      FILE stream.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 *
 *  @post       In the event a negative value is returned,
 *              Engine_getLastError() will return one of the following values:
 *                - #Engine_ERUNTIME    Either an internal runtime error
 *                                      occured or the underlying server
 *                                      error occured.
 *                - #Engine_EINUSE      Server trace resource is already in use.
 */
extern Int Engine_fwriteTrace(Engine_Handle engine, String prefix, FILE *out);

/*
 *  ======== Engine_getAlgInfo ========
 */
/**
 *  @brief Get details of an algorithm configured into an engine.
 *
 *  @param[in]  name            The name of the engine.  @c name is
 *                              specified in the engine configuration.
 *  @param[out] algInfo         Structure to store algorithm details. The
 *                              @c algInfoSize field of this structure must
 *                              be set to @c sizeof(Engine_AlgInfo) by the
 *                              application.
 *  @param[out] index           The index of the algorithm to get the
 *                              information.
 *
 *  @retval     Engine_EOK        Success.
 *  @retval     Engine_EEXIST     There is no engine with the given name.
 *  @retval     Engine_ENOTFOUND  @c index is greater than or equal to the
 *                                total number of algorithms configured for
 *                                the engine, or @c index < 0.
 *  @retval     Engine_EINVAL     The value of @c algInfoSize passed to this
 *                                function does not match the CE library's
 *                                @c sizeof(Engine_AlgInfo).
 *
 *  @pre        @c name is a non-NULL string.
 *
 *  @pre        @c algInfo is non-NULL.
 *
 *  @pre        As with all Codec Engine API's, CERuntime_init() must have
 *              previously been called.
 *
 *  @post       If @c name is a valid engine name and 0 <= @c index < the
 *              total number of algorithms configured for the engine, then
 *              @c algInfo will contain the information for the engine's
 *              ith (i = @c index) algorithm.
 *
 *  @sa         Engine_getNumAlgs().
 */
extern Engine_Error Engine_getAlgInfo(String name, Engine_AlgInfo *algInfo,
    Int index);

/*
 *  ======== Engine_getCpuLoad ========
 */
/**
 *  @brief              Get Server's cpu usage in percent
 *
 *  @param[in]  engine  The handle to the opened engine.
 *
 *  @retval             integer between 0-100 indicating percentage
 *                      of time the Server is processing measured
 *                      over a period of approximately 1 second.  If
 *                      the load is unavailable, a negative value is
 *                      returned.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 *
 *  @post       In the event a negative value is returned,
 *              Engine_getLastError() will return one of the following values:
 *                - #Engine_ERUNTIME    Either an internal runtime error
 *                                      occured or the underlying server
 *                                      error occured.
 *                - #Engine_ENOTAVAIL   The CPU load can not be computed.
 */
extern Int Engine_getCpuLoad(Engine_Handle engine);

/*
 *  ======== Engine_getLastError ========
 */
/**
 *  @brief              Get error code of the last failed operation
 *
 *  @param[in]  engine  The handle to the opened engine.
 *
 *  @retval             error code (Engine_Error) of the last failed
 *                      engine operation.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 */
extern Engine_Error Engine_getLastError(Engine_Handle engine);

/*
 *  ======== Engine_getNumAlgs ========
 */
/**
 *  @brief Get the number of algorithms configured into an engine.
 *
 *  @param[in]  name            The name of the engine.  @c name is
 *                              specified in the engine configuration.
 *  @param[out] numAlgs         The number of algorithms that are configured
 *                              in the given engine.
 *
 *  @retval     Engine_EOK      Success.
 *  @retval     Engine_EEXIST   There is no engine with the given name.
 *
 *  @pre        @c name is a non-NULL string.
 *
 *  @pre        @c numAlgs is non-NULL.
 *
 *  @pre        As with all Codec Engine API's, CERuntime_init() must have
 *              previously been called.
 *
 *  @post       If @c name is a valid engine name, then numAlgs will contain
 *              the number of algorithms configured for the given engine.
 *
 *  @sa         Engine_getAlgs().
 */
extern Engine_Error Engine_getNumAlgs(String name, Int *numAlgs);

/*
 *  ======== Engine_getServer ========
 */
/**
 *  @brief              Get handle to an Engine's server.
 *
 *  This function returns the handle to an Engines server, that can be used
 *  with Server APIs to obtain information from and control the remote DSP
 *  server.
 *
 *  @param[in]  engine  The handle to the opened engine.
 *
 *  @retval             Handle to engine's server.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 */
extern Server_Handle Engine_getServer(Engine_Handle engine);


/*
 *  ======== Engine_getUsedMem ========
 */
/**
 *  @brief              Get Server's total memory usage
 *
 *  @param[in]  engine  The handle to the opened engine.
 *
 *  @retval             Total amount of used memory (in MAUs).  If
 *                      the amount is not available, 0 is returned
 *                      and the reason can be retrieved via
 *                      Engine_getLastError().
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 *
 *  @post       in the event that 0 is returned, Engine_getLastError() will
 *              return one of the following values:
 *                - #Engine_ERUNTIME    Either an internal runtime error
 *                                      occured or the underlying server
 *                                      error occured.
 *                - #Engine_ENOTAVAIL   The memory usage can not be computed.
 */
extern UInt32 Engine_getUsedMem(Engine_Handle engine);


/*
 *  ======== Engine_setTrace ========
 */
/**
 *  @brief              Set Server's trace mask
 *
 *  @param[in]  engine  The handle to the opened engine.
 *  @param[in]  mask    Trace mask, e.g. "*=01234567"
 *
 *  @retval     Engine_ENOSERVER   No server for this engine.
 *  @retval     Engine_EINUSE      Trace resource is already in use.
 *  @retval     Engine_ERUNTIME    Internal runtime error has occurred.
 *
 *  @pre        @c engine is a valid (non-NULL) engine handle and the engine
 *              is in the open state.
 *
 *  @remarks    This only sets the trace for a remote server.  To change
 *              the trace mask for the application-side of the framework,
 *              use GT_set().
 *
 *  @sa         GT_set()
 */
extern Int Engine_setTrace(Engine_Handle engine, String mask);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce; 1, 0, 5,267; 1-14-2008 09:48:55; /db/atree/library/trees/ce-g30x/src/
 */

