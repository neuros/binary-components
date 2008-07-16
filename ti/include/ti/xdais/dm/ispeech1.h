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
 *  @file       ti/xdais/dm/ispeech1.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across the various speech codecs.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1  xDM 1.00 Speech/Voice Interface
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_
#define ti_xdais_dm_ISPEECH1_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1 */
/*@{*/


/**
 *  @brief      Null traffic channel setting.
 *
 *  @sa         ISPHENC1_InArgs.nullTrafficChannel.
 */
typedef enum {
    ISPEECH1_NULLTRAFFICMODE_OFF = 0,  /**< Null traffic channel frames
                                        *   disabled, normal speech encoding
                                        *   is enabled.
                                        */
    ISPEECH1_NULLTRAFFICMODE_ON = 1,   /**< Null traffic channel frames
                                        *   enabled.
                                        */

    /** @copydoc ISPEECH1_NULLTRAFFICMODE_OFF */
    ISPEECH1_NULLTRAFFICMODE_DEFAULT = ISPEECH1_NULLTRAFFICMODE_OFF
} ISPEECH1_NullTrafficMode;


/**
 *  @brief      Post filter setting.
 *
 *  These values are used for enabling/disabling the post filter.
 */
typedef enum {
    ISPEECH1_POSTFILTER_OFF = 0,       /**< Post Filter disabled. */
    ISPEECH1_POSTFILTER_ON = 1,        /**< Post Filter enabled. */

    /** @copydoc ISPEECH1_POSTFILTER_ON */
    ISPEECH1_POSTFILTER_DEFAULT = ISPEECH1_POSTFILTER_ON
} ISPEECH1_PostFilter;



/**
 *  @brief      Voice Activity Detection (VAD) setting.
 */
typedef enum {
    ISPEECH1_VADFLAG_OFF = 0,          /**< Voice Activity Detection off. */
    ISPEECH1_VADFLAG_ON = 1,           /**< Voice Activity Detection on. */

    /** @copydoc ISPEECH1_VADFLAG_ON */
    ISPEECH1_VADFLAG_DEFAULT = ISPEECH1_VADFLAG_ON
} ISPEECH1_VADFlag;


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

