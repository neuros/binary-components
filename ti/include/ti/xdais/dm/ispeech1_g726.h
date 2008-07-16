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
 *  @file       ti/xdais/dm/ispeech1_g726.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for G.726
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_G726  xDM 1.00 Speech/Voice Interface (G.726)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various G.726
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_G726_
#define ti_xdais_dm_ISPEECH1_G726_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_G726 */
/*@{*/


/**
 *  @brief      Bit rate selection for G726.
 */
typedef enum {
    ISPEECH1_G726_BITRATE_16  = 0,     /**<  16  kbps */
    ISPEECH1_G726_BITRATE_24  = 1,     /**<  24  kbps */
    ISPEECH1_G726_BITRATE_32  = 2,     /**<  32  kbps */
    ISPEECH1_G726_BITRATE_40  = 3,     /**<  40  kbps */

    /** Default setting. */
    ISPEECH1_G726_BITRATE_DEFAULT = ISPEECH1_G726_BITRATE_40
} ISPEECH1_G726_BitRate;


/**
 *  @brief      Companding law of encoder input and decoder output samples.
 */
typedef enum {
    ISPEECH1_G726_COMPAND_LINEAR = 0,      /**< Linear */
    ISPEECH1_G726_COMPAND_ALAW = 1,        /**< A-law */
    ISPEECH1_G726_COMPAND_ULAW = 2,        /**< Mu-law */

    /** Default setting. */
    ISPEECH1_G726_COMPAND_DEFAULT = ISPEECH1_G726_COMPAND_LINEAR
} ISPEECH1_G726_CompandingLaw;


/**
 *  @brief      Packing Type defintions for G.726
 */
typedef enum {
    ISPEECH1_G726_PACKTYPE_LINEAR = 0,     /**< Linear packing. */
    ISPEECH1_G726_PACKTYPE_RTPSPECIAL = 1, /**< RTP special format. */

    /** Default setting. */
    ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT = ISPEECH1_G726_PACKTYPE_LINEAR
} ISPEECH1_G726_PackingType;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_G726_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

