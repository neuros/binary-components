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
 *  @file       ti/xdais/dm/ispeech1_evrc.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for EVRC
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_EVRC  xDM 1.00 Speech/Voice Interface (EVRC)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various EVRC
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_EVRC_
#define ti_xdais_dm_ISPEECH1_EVRC_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_EVRC */
/*@{*/


/**
 *  @brief      Enable/disable noise suppression.
 */
typedef enum {
    ISPEECH1_EVRC_NOISEPREPROC_OFF = 0, /**< The noise suppression is
                                         *   disabled.
                                         */
    ISPEECH1_EVRC_NOISEPREPROC_ON = 1,  /**< The noise suppression is
                                         *   enabled.
                                         */

    /** Default setting. */
    ISPEECH1_EVRC_NOISEPREPROC_DEFAULT = ISPEECH1_EVRC_NOISEPREPROC_ON
} ISPEECH1_EVRC_NoisePreProc;


/**
 *  @brief      TTY/TDD mode selection.
 */
typedef enum {
    ISPEECH1_EVRC_TTYMODE_OFF = 0,      /**< Off */
    ISPEECH1_EVRC_TTYMODE_45P45BPS = 1, /**< 45.45 baud rate */
    ISPEECH1_EVRC_TTYMODE_50BPS = 2,    /**< 50 baud rate */

    /** Default setting. */
    ISPEECH1_EVRC_TTYMODE_DEFAULT = ISPEECH1_EVRC_TTYMODE_OFF
} ISPEECH1_EVRC_TTYMode;


/**
 *  @brief      Mode selection
 *
 *  @remarks    This is used for rate reduction mode in EVRC codecs.  The
 *              average bit rate of speech encoding is controlled by these
 *              different modes.
 */
typedef enum {
    ISPEECH1_EVRC_MODE_PREMIUM = 0,        /**< Premium mode. */
    ISPEECH1_EVRC_MODE_STANDARD = 1,       /**< Standard mode. */
    ISPEECH1_EVRC_MODE_ECONOMY = 2,        /**< Economy mode. */
    ISPEECH1_EVRC_MODE_CAPACITYSAVE = 3,   /**< Capacity saving mode. */
    ISPEECH1_EVRC_MODE_HALFRATE_MAX = 4,   /**< Half rate max mode. */

    /** Default setting. */
    ISPEECH1_EVRC_MODE_DEFAULT = ISPEECH1_EVRC_MODE_PREMIUM
} ISPEECH1_EVRC_Mode;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_EVRC_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

