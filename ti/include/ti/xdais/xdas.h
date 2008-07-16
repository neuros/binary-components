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
 *  @file       ti/xdais/xdas.h
 *
 *  @brief      This header defines all types and constants used in the
 *              XDAS interfaces.
 *
 *  @remarks    The types are mapped to the types defined in std.h.
 */
/**
 *  @addtogroup   ti_xdais_XDAS xDAIS Types and Constants
 */

#ifndef ti_xdais_XDAS_
#define ti_xdais_XDAS_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_XDAS_ */
/*@{*/


#define XDAS_TRUE       1
#define XDAS_FALSE      0


typedef Void            XDAS_Void;
typedef Uint8           XDAS_Bool;


typedef Int8            XDAS_Int8;      /**< Actual size chip dependent. */
typedef Uint8           XDAS_UInt8;     /**< Actual size chip dependent. */
typedef Int16           XDAS_Int16;     /**< Actual size of type is 16 bits. */
typedef Uint16          XDAS_UInt16;    /**< Actual size of type is 16 bits. */
typedef Int32           XDAS_Int32;     /**< Actual size of type is 32 bits. */
typedef Uint32          XDAS_UInt32;    /**< Actual size of type is 32 bits. */


/*@}*/


#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_XDAS_ */
/*
 *  @(#) ti.xdais; 1, 2.0, 1,148; 11-25-2007 20:44:02; /db/wtree/library/trees/dais-i23x/src/
 */

