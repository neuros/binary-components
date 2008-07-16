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
 *  @file       ti/xdais/dm/ispeech.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across the various speech codecs.
 *
 *  @version    0.4
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH   xDM Speech/Voice Interface
 *
 *  This is the xDM speech/voice interface shared between the various codecs.
 */

#ifndef ti_xdais_dm_ISPEECH_
#define ti_xdais_dm_ISPEECH_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH */
/*@{*/

/**
 *  @brief      xDM supported voice modes for speech
 */
typedef enum {
    ISPEECH_VOICED = 0,
    ISPEECH_UNVOICED
} ISPEECH_VoiceMode;

typedef enum {
    ISPEECH_LINEAR = 0,
    ISPEECH_ALAW,
    ISPEECH_ULAW
} ISPEECH_CompoundLaw;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

