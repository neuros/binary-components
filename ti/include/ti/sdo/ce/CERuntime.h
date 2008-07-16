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
 *  ======== ti/sdo/ce/CERuntime.h ========
 */

/**
 *  @file       ti/sdo/ce/CERuntime.h
 *
 *  @brief      The Codec Engine Runtime init module.  Provides system
 *              wide initialization of the Codec Engine Runtime.
 */
/**
 *  @addtogroup   CODECENGINE     Codec Engine Runtime
 */

#ifndef CERuntime_
#define CERuntime_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    CODECENGINE */
/*@{*/

/*
 *  ======== CERuntime_exit ========
 */
/**
 *  @brief      Exit the Codec Engine Runtime.
 *
 *  @remarks    This function finalizes the Codec Engine modules used in
 *              the current configuration.
 */
extern Void CERuntime_exit(Void);


/*
 *  ======== CERuntime_init ========
 */
/**
 *  @brief      Initialize the Codec Engine Runtime.
 *
 *  @remarks    This function must be called prior to using any Codec Engine
 *              APIs; it initializes all Codec Engine modules used in the
 *              the current configuration.
 */
extern Void CERuntime_init(Void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce; 1, 0, 5,267; 1-14-2008 09:48:55; /db/atree/library/trees/ce-g30x/src/
 */

