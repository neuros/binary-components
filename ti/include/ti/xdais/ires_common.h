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
 *  @file       ti/xdais/ires_common.h
 *
 *  @brief      IRES Resource Protocol Definitions (C64P) - IRES Resource 
 */

#ifndef IRES_COMMON_
#define IRES_COMMON_

/** @ingroup    DSPIRES */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include "ialg.h"


/**
 *  @brief      IRES_Status defines the standard error and success codes 
 *              returned by IRES APIs.
 */
typedef enum IRES_Status {
    IRES_OK = 0,                /**< Success */
    IRES_EALG = 1,              /**< Error in algorithm IRES_Fxns functions */
    IRES_EEXISTS = 2,           /**< Error, already exists      */
    IRES_EFAIL = 3,             /**< Generic Error Message      */
    IRES_EINIT = 4,             /**< Error, already initialized */
    IRES_ENOINIT = 5,           /**< Error, not initialized     */
    IRES_ENOMEM = 6,            /**< Error, not enough memory   */
    IRES_ENORESOURCE = 7,       /**< Error, resource unavailable*/
    IRES_ENOTFOUND = 8          /**< Error, not found           */
} IRES_Status;

/**
 *  @brief      Protocol revision type.
 *              Used to ensure the given 'protocol' revision can be validated. 
 */
typedef struct IRES_ProtocolRevision {
    unsigned int Major;
    unsigned int Source;
    unsigned int Radius;                /* Using unsigned int here to support
                                         * xdc/std.h as well as tistdtypes.h
                                         */
} IRES_ProtocolRevision;

/**
 *  @brief      Resources can be requested as scratch or persistent, using the
 *              IRES_RequestMode type.
 */
typedef enum IRES_RequestMode  {
    IRES_SCRATCH, 
    IRES_PERSISTENT 
} IRES_RequestMode;

/**
 *  @brief      Abstract Protocol Arguments structure/pointer definition.
 *              Actual arguments passed by the algorithm to request a resource 
 *              from a specific IRES Protocol will extend and supply the 
 *              concrete definitions.
 */
typedef struct IRES_ProtocolArgs {

    Int32 size;   /* size of this structure */

    /**
     *  When persistent the resource will be allocated exclusively for this 
     *  algorithm. 
     *  The mode can be either IRES_SCRATCH or IRES_PERSISTENT.
     */
    IRES_RequestMode mode; 

} IRES_ProtocolArgs;

/**
 *  @brief      Descriptor to Logical Resource.
 */
typedef struct IRES_ResourceDescriptor {

    /**
     *  String containing the package name to identify the resource.
     */
    String resourceName;

    /**
     *  Pointer to the Resource Protocol Arguments.  
     *  The Resource Manager selects the appropriate Resource Protocol
     *  based on the supplied "resourceName", and uses the protocol to 
     *  construct the IRES Resource Handle. 
     */
    struct IRES_ProtocolArgs  *protocolArgs;

    /**
     *  The revision of the IRES_ResourceProtocol Interface expected by the
     *  client algorithm.
     */
    IRES_ProtocolRevision *revision;

    /**
     *  The handle to the object representing the requested resource.
     *  The handle is initially set to 'null' by the requesting algorithm.
     *  The 'resource manager' allocates the resource and constructs the
     *  handle.
     */
    struct IRES_Obj * handle;
     
} IRES_ResourceDescriptor;

/**
 *  @brief      Abstract Resource Properties structure/pointer definition.
 *              Actual resource protocol will supply the concrete property
 *              definitions.
 *              The list of attributes for the actual resource will expose the
 *              relevant features that needs to be known to a client to use the
 *              resource, such as: resource register base addresses and offsets,
 *              critical register and memory region addresses, ...
 */
typedef struct IRES_Properties {
    Int32 size;   /* size of this structure */
 
} IRES_Properties;

/**
 *  @brief      IRES_Obj holds the private state associated with each
 *              logical resource.
 */
typedef struct IRES_Obj {

    /**
     * Indicates if the resource has been allocated as persistent.
     */
    Int32 persistent;

    /**
     *  Obtain the static properties associated with this resource 
     *  This could include information like the register layer of the
     *  device etc.
     */
    Void (*getStaticProperties) (struct IRES_Obj * resourceHandle, 
        IRES_Properties * resourceProperties);
    
} IRES_Obj;

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_Obj *IRES_Handle;



#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif  /* IRES_COMMON_ */
/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

