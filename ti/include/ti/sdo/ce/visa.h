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
 *  ======== visa.h ========
 */
/**
 *  @file       ti/sdo/ce/visa.h
 *
 *  @brief      The Codec Engine System Programming Interface.  Provides
 *              system developers with services necessary to implement
 *              stubs and skeletons.
 */
/**
 *  @defgroup   ti_sdo_ce_VISA_GEN      CE SPI (common)
 *
 *  Codec Engine System Programming Interface (SPI) shared definitions.
 */
/**
 *  @defgroup   ti_sdo_ce_VISA_STUB     CE Stub SPI
 *
 *  Codec Engine System Programming Interface (SPI) for stub implementors.
 */
/**
 *  @defgroup   ti_sdo_ce_VISA_API      CE interface SPI
 *
 *  Codec Engine System Programming Interface (SPI) for class interface
 *  implementors.
 */

#ifndef ti_sdo_ce_VISA_
#define ti_sdo_ce_VISA_

#include <stddef.h>     /* for size_t */

#include <ti/sdo/ce/node/node.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/ce/Engine.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief      VISA result data type
 *  @ingroup    ti_sdo_ce_VISA_GEN
 */
typedef Int VISA_Status;

/**
 *  @brief      Success.
 *  @ingroup    ti_sdo_ce_VISA_GEN
 */
#define VISA_EOK        0

/**
 *  @brief      Internal runtime error.
 *  @ingroup    ti_sdo_ce_VISA_GEN
 */
#define VISA_ERUNTIME   -1

/**
 *  @brief      General system error.
 *  @ingroup    ti_sdo_ce_VISA_GEN
 */
#define VISA_EFAIL   -2

/**
 *  @brief      Opaque handle to a node.
 */
typedef struct VISA_Obj *VISA_Handle;

/**
 *  @brief      VISA message header.
 *
 *  @ingroup    ti_sdo_ce_VISA_STUB
 *
 *  @remarks    This must be the first field in a message
 */
typedef struct VISA_MsgHeader {
    NODE_MsgHeader  header;
    Int             cmd;        /**< Command id */
    VISA_Status     status;     /**< Return status */
} VISA_MsgHeader;

/*
 *  ======== VISA_Msg ========
 */
typedef VISA_MsgHeader *VISA_Msg;

/*
 *  ======== VISA_allocMsg ========
 */
/**
 *  @brief      Obtain an algorithm instance's message.
 *
 *  @ingroup    ti_sdo_ce_VISA_STUB
 *
 *  @param[in]  visa        Handle to an algorithm instance.
 *
 *  @retval     NULL        General system error
 *  @retval     non-NULL    The remote algorithm's message.
 *
 *  @remarks    This is typically called by an algorithm class' stub.
 *
 *  @sa         VISA_allocMsg()
 */
extern VISA_Msg VISA_allocMsg(VISA_Handle visa);

/*
 *  ======== VISA_call ========
 */
/**
 *  @brief      Invoke the operation specified in the message and wait for
 *              it to complete.
 *
 *  @ingroup    ti_sdo_ce_VISA_STUB
 *
 *  @param[in]  visa    Handle to an algorithm instance.
 *  @param[out] msg     The remote algorithm's message,
 *                          to be sent to the skeleton.
 *
 *  @remarks    This is typically called by an algorithm class' stub.
 *
 *  @retval         VISA_EOK        Success
 *  @retval         VISA_ERUNTIME   General system error
 *
 */
extern VISA_Status VISA_call(VISA_Handle visa, VISA_Msg *msg);

/*
 *  ======== VISA_freeMsg ========
 */
/**
 *  @brief      Release an algorithm instance's message.
 *
 *  @ingroup    ti_sdo_ce_VISA_STUB
 *
 *  @param[in]  visa    Handle to an algorithm instance.
 *  @param[in]  msg     Message to free, obtained through a call to
 *                      VISA_allocMsg().
 *
 *  @retval     NULL        General system error
 *  @retval     non-NULL    The remote algorithm's message.
 *
 *  @remarks    This is typically called by an algorithm class' stub.
 *
 *  @sa         VISA_allocMsg()
 */
extern Void VISA_freeMsg(VISA_Handle visa, VISA_Msg msg);


/** @ingroup    ti_sdo_ce_VISA_API */
/*@{*/

/*
 *  ======== VISA_create ========
 */
/**
 *  @brief      Create a new instance of an algorithm.
 *
 *  @param[in]  engine  Handle to an engine in which the algorithm has been
 *                      configured.
 *  @param[in]  name    Name of the algorithm to create.  @c name is
 *                      specified in the engine configuration.
 *  @param[in]  params  Creation parameters.
 *  @param[in]  msgSize Size of the message which will be allocated in
 *                      the event that this algorithm is configured to
 *                      run remotely.
 *  @param[in]  type    String name of the "type" of algorithm.
 *
 *  @retval     NULL            General failure.
 *  @retval     non-NULL        Handle to an algorithm instance.
 *
 *  @remarks    @c type <b>must</b> match the package/module name of the
 *              interface which the algorithm implements.  For example, the VISA
 *              interface shipped with CE to support xDM video
 *              decoders is named "ti.sdo.ce.video.IVIDDEC".  That is,
 *              the module IVIDDEC is in the package "ti.sdo.ce.video".
 *              You will, by definition, find a file named IVIDDEC.xdc in the
 *              ti.sdo.ce.video package.
 *
 *  @remarks    When calling VISA_create(), a string comparison is done
 *              between the @c type parameter and the actual name of the
 *              module (described in the previous paragraph).  If these strings
 *              don't match exactly, VISA_create() will fail.
 *
 *  @sa         VISA_delete()
 */
extern VISA_Handle VISA_create(Engine_Handle engine, String name,
    IALG_Params *params, size_t msgSize, String type);

/*
 *  ======== VISA_delete ========
 */
/**
 *  @brief      Delete an instance of an algorithm.
 *
 *  @param[in]  visa    Handle to an algorithm instance to delete.
 *
 *  @sa         VISA_create()
 */
extern Void VISA_delete(VISA_Handle visa);


/*
 *  ======== VISA_create2 ========
 */
/**
 *  @brief      Create a new instance of an algorithm.
 *
 *  @param[in]  engine      Handle to an engine in which the algorithm has been
 *                          configured.
 *  @param[in]  name        Name of the algorithm to create.  @c name is
 *                          specified in the engine configuration.
 *  @param[in]  params      Creation parameters.
 *  @param[in]  paramsSize  Size of @c params.
 *  @param[in]  msgSize     Size of the message which will be allocated in
 *                          the event that this algorithm is configured to
 *                          run remotely.
 *  @param[in]  type        String name of the "type" of algorithm.
 *
 *  @retval     NULL            General failure.
 *  @retval     non-NULL        Handle to an algorithm instance.
 *
 *  @remarks    @c type <b>must</b> match the package/module name of the
 *              interface which the algorithm implements.  For example, the VISA
 *              interface shipped with CE to support xDM video
 *              decoders is named "ti.sdo.ce.video.IVIDDEC".  That is,
 *              the module IVIDDEC is in the package "ti.sdo.ce.video".
 *              You will, by definition, find a file named IVIDDEC.xdc in the
 *              ti.sdo.ce.video package.
 *
 *  @remarks    When calling VISA_create2(), a string comparison is done
 *              between the @c type parameter and the actual name of the
 *              module (described in the previous paragraph).  If these strings
 *              don't match exactly, VISA_create2() will fail.
 *
 *  @remarks    VISA_create() is the preferred method to create algorithms.
 *              VISA_create2() is provided to enable creation of algorithms
 *              which violate the xDAIS spec and do <b>not</b> have a @c size
 *              field of type "Int" as the first field of @c params.
 *
 *  @sa         VISA_create()
 *  @sa         VISA_delete()
 */
extern VISA_Handle VISA_create2(Engine_Handle engine, String name,
    IALG_Params *params, Int paramsSize, size_t msgSize, String type);


/*
 *  ======== VISA_enter ========
 */
/**
 *  @brief      Enter an algorithm's critical section.  This must be called
 *              before any of the algorithm's IALG_Fxns are invoked.
 *
 *  @param[in]  visa    Handle to an algorithm instance.
 *
 *  @remarks    This is typically called by an algorithm class' application API.
 *
 *  @remarks    This call has the same semantics as IALG's activate fxn.
 *
 *  @sa         VISA_exit()
 */
extern Void VISA_enter(VISA_Handle visa);

/*
 *  ======== VISA_exit ========
 */
/**
 *  @brief      Leave an algorithm's critical section.  This must be called
 *              after the API has completed calling an algorithm's IALG_Fxns.
 *
 *  @param[in]  visa    Handle to an algorithm instance.
 *
 *  @remarks    This call has the same semantics as IALG's de-activate fxn.
 *
 *  @sa         VISA_enter()
 */
extern Void VISA_exit(VISA_Handle visa);

/*
 *  ======== VISA_getAlgHandle ========
 */
/**
 *  @brief      Obtains an algorithm's handle.  This is the handle required
 *              to be passed to the algorithm's IALG_Fxns.
 *
 *  @param[in]  visa        Handle to an algorithm instance.
 *
 *  @retval     NULL        General system error
 *  @retval     non-NULL    The remote algorithm's message.
 *
 *  @remarks    This is typically called by an algorithm class' application API.
 *
 *  @sa         VISA_getAlgFxns()
 */
extern Ptr VISA_getAlgHandle(VISA_Handle visa);

/*
 *  ======== VISA_getAlgFxns ========
 */
/**
 *  @brief      Get implementation functions for this algorithm
 *
 *  @param[in]  visa    Handle to an algorithm instance.
 *
 *  @retval     NULL        An error has occurred.
 *  @retval     non-NULL    The algorithm's IALG_Fxns.
 *
 *  @remarks    This is typically called by an algorithm class' application API.
 *
 *  @remarks    Both local and remote implementations return a non-NULL
 *              pointer.  However, the IALG_Fxns functions may be NULL.
 *
 *  @remarks    In the case of a local algorithm, the algorithm's IALG_Fxns
 *              returned.  In the case of a remote algorithm, its stubs are
 *              returned.  In either case, the handle passed as the first arg
 *              to the IALG_Fxns must be the value returned by
 *              VISA_getAlgHandle().
 *
 *  @sa         VISA_getAlgHandle()
 */
extern IALG_Fxns *VISA_getAlgFxns(VISA_Handle visa);

/*@}*/  /* ingroup */

/*
 *  ======== VISA_getContext ========
 */
/**
 *  @brief      Get optional context parameter.
 *
 *  @ingroup    ti_sdo_ce_VISA_GEN
 *
 *  @param[in]  visa        Handle to an algorithm instance.
 *  @param[out] pContext    Location to store context.
 *
 *  @pre        @c visa <b>must</b> be a valid algorithm instance handle.
 *
 *  @pre        @c pContext <b>must</b> be a valid pointer.
 *
 *  @remarks    The VISA_setContext() / VISA_getContext() pair does <b>not</b>
 *              work across processors.  That is, the context can only be
 *              stored and retrieved on the local processor.
 *
 *  @sa         VISA_setContext()
 */
extern Void VISA_getContext(VISA_Handle visa, UInt32 * pContext);

/*
 *  ======== VISA_getCodecClassConfig ========
 */
/**
 *  @brief      Get codec-specific values for the VISA class-specific
 *              (or codec-specific if the codec doesn't extend VISA) stub-and/
 *              or-skeleton configuration data (that some classes have)
 *
 *  @ingroup    ti_sdo_ce_VISA_GEN
 *
 *  @param[in]  visa        Handle to an algorithm instance.
 *
 *  @retval     address of the codec class config data structure, or NULL if
 *              codec class config data not defined for the codec; the format
 *              of the structure is class-specific, and the data in it is codec-
 *              specific
 *
 *  @pre        @c visa <b>must</b> be a valid algorithm instance handle.
 */
extern Ptr VISA_getCodecClassConfig(VISA_Handle visa);

/*
 *  ======== VISA_isChecked ========
 */
/**
 *  @brief      Indicates whether VISA libraries were built with
 *              debug + additional checking enabled
 *
 *  @ingroup    ti_sdo_ce_VISA_GEN
 *
 *  @retval     false       VISA libraries with no debug/checking are used
 *  @retval     true        VISA libraries with debug/checking are used
 *
 *  @remarks    This is typically called by an algorithm class' stub.
 *
 *  @sa         VISA_allocMsg()
 */
static inline Bool VISA_isChecked(Void)
{
    extern Bool VISA_checked;  /* generated by Settings.xdt based 'checked' */

    return VISA_checked;
}

/*
 *  ======== VISA_setContext ========
 */
/**
 *  @brief      Set optional context parameter.
 *
 *  @ingroup    ti_sdo_ce_VISA_GEN
 *
 *  @param[in]  visa        Handle to an algorithm instance.
 *  @param[in]  context     Context.
 *
 *  @pre        @c visa <b>must</b> be a valid algorithm instance handle.
 *
 *  @remarks    The VISA_setContext() / VISA_getContext() pair does <b>not</b>
 *              work across processors.  That is, the context can only be
 *              stored and retrieved on the local processor.
 *
 *  @sa         VISA_getContext()
 */
extern Void VISA_setContext(VISA_Handle visa, UInt32 context);


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce; 1, 0, 5,267; 1-14-2008 09:48:56; /db/atree/library/trees/ce-g30x/src/
 */

