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
 *  @file       ti/xdais/dm/ispeech1_smv.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for SMV
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_SMV  xDM 1.00 Speech/Voice Interface (SMV)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various SMV
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_SMV_
#define ti_xdais_dm_ISPEECH1_SMV_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_SMV */
/*@{*/


/**
 *  @brief      Enabling/disabling noise suppression, and selection of
 *              noise suppression if the codec supports multiple
 *              noise supression modules.
 */
typedef enum {
    ISPEECH1_SMV_NOISEPREPROC_OFF = 0,  /**< Noise suppression is disabled. */
    ISPEECH1_SMV_NOISEPREPROC_NSA = 1,  /**< Noise suppression is enabled,
                                         *   using option A.
                                         */
    ISPEECH1_SMV_NOISEPREPROC_NSB = 2,  /**< Noise suppression is enabled,
                                         *   using option B.
                                         */

    /** Default setting. */
    ISPEECH1_SMV_NOISEPREPROC_DEFAULT = ISPEECH1_SMV_NOISEPREPROC_NSA
} ISPEECH1_SMV_NoisePreProc;


/**
 *  @brief      Voice activity detection (VAD) selection.
 */
typedef enum {
    ISPEECH1_SMV_VADSELECT_VADA = 1,    /**< VAD A */
    ISPEECH1_SMV_VADSELECT_VADB = 2,    /**< VAD B */

    /** Default setting. */
    ISPEECH1_SMV_VADSELECT_DEFAULT = ISPEECH1_SMV_VADSELECT_VADA
} ISPEECH1_SMV_VADSelect;


/**
 *  @brief      TTY/TDD mode selection.
 */
typedef enum {
    ISPEECH1_SMV_TTYMODE_OFF = 0,       /**< TTY detection is disabled. */
    ISPEECH1_SMV_TTYMODE_45P45BPS = 1,  /**< TTY detection is enabled, with
                                         *   45.45 bauds/sec rate.
                                         */
    ISPEECH1_SMV_TTYMODE_50BPS =  2,    /**< TTY detection is enabled, with
                                         *   50 bauds/sec rate.
                                         */

    /** Default setting. */
    ISPEECH1_SMV_TTYMODE_DEFAULT = ISPEECH1_SMV_TTYMODE_OFF
} ISPEECH1_SMV_TTYMode;


/**
 *  @brief      DTMF mode selection.
 */
typedef enum {
    ISPEECH1_SMV_DTMFMODE_OFF = 0,         /**< DTMF detection is disabled. */
    ISPEECH1_SMV_DTMFMODE_ON = 1,          /**< DTMF detection is enabled. */

    /** Default setting. */
    ISPEECH1_SMV_DTMFMODE_DEFAULT = ISPEECH1_SMV_DTMFMODE_OFF
} ISPEECH1_SMV_DTMFMode;


/**
 *  @brief      Enable/disable in band data transmission and data rate
 *              selection.
 */
typedef enum {
    ISPEECH1_SMV_DATAMODE_OFF = 0,         /**< Data transmission is disabled */
    ISPEECH1_SMV_DATAMODE_HALFRATE = 1,    /**< Data transmission is enabled
                                            *   at half rate.
                                            */
    ISPEECH1_SMV_DATAMODE_FULLRATE = 1,    /**< Data transmission is enabled
                                            *   at full rate.
                                            */

    /** Default setting. */
    ISPEECH1_SMV_DATAMODE_DEFAULT = ISPEECH1_SMV_DATAMODE_OFF
} ISPEECH1_SMV_DataMode;


/**
 *  @brief      Rate reduction mode selection.
 */
typedef enum {
    ISPEECH1_SMV_MODE_PREMIUM = 0,         /**< Premium mode. */
    ISPEECH1_SMV_MODE_STANDARD = 1,        /**< Standard mode. */
    ISPEECH1_SMV_MODE_ECONOMY = 2,         /**< Economy mode. */
    ISPEECH1_SMV_MODE_CAPACITYSAVE = 3,    /**< Capacity saving mode. */
    ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX = 4, /**< Premium mode, with half
                                            *   rate maximum.
                                            */
    ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX = 5,/**< Standard mode, with half
                                            *   rate maximum.
                                            */

    /** Default setting. */
    ISPEECH1_SMV_MODE_DEFAULT = ISPEECH1_SMV_MODE_PREMIUM
} ISPEECH1_SMV_Mode;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_SMV_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

