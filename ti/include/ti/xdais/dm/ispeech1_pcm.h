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
 *  @file       ti/xdais/dm/ispeech1_pcm.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across all G.711/PCM speech codecs.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_PCM  xDM 1.00 Speech/Voice Interface (PCM)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various PCM
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_PCM_
#define ti_xdais_dm_ISPEECH1_PCM_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_PCM */
/*@{*/


/**
 *  @brief      Companding law of encoder input and decoder output samples.
 */
typedef enum {
    ISPEECH1_PCM_COMPAND_LINEAR = 0,       /**< Linear */
    ISPEECH1_PCM_COMPAND_ALAW = 1,         /**< A-law */
    ISPEECH1_PCM_COMPAND_ULAW = 2,         /**< Mu-law */

    /** Default setting. */
    ISPEECH1_PCM_COMPAND_DEFAULT = ISPEECH1_PCM_COMPAND_LINEAR
} ISPEECH1_PCM_CompandingLaw;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_PCM_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

