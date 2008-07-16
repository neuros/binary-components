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
 *  @file       ti/xdais/dm/ispeech1_g723.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.723
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G723  xDM 1.00 Speech/Voice Interface (G.723)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various G.723
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G723_
#define ti_xdais_dm_ISPEECH1_G723_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G723 */
/*@{*/


/**
 *  @brief      Bit rate selection for G723.
 */
typedef enum {
    ISPEECH1_G723_BITRATE_5P3 = 0,     /**< 5.3 kbps */
    ISPEECH1_G723_BITRATE_6P3 = 1,     /**< 6.3 kbps */

    /** Default setting. */
    ISPEECH1_G723_BITRATE_DEFAULT = ISPEECH1_G723_BITRATE_6P3
} ISPEECH1_G723_BitRate;


/**
 *  @brief      Enable/disable high pass filter for G723.
 */
typedef enum {
    ISPEECH1_G723_NOISEPREPROC_OFF = 0,/**< The high pass filter is disabled. */
    ISPEECH1_G723_NOISEPREPROC_ON = 1, /**< The high pass filter is enabled. */

    /** Default setting. */
    ISPEECH1_G723_NOISEPREPROC_DEFAULT = ISPEECH1_G723_NOISEPREPROC_ON
} ISPEECH1_G723_NoisePreProc;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_G723_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

