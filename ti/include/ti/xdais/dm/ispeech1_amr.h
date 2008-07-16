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
 *  @file       ti/xdais/dm/ispeech1_amr.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for AMR.
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_AMR  xDM 1.00 Speech/Voice Interface (AMR)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various AMR
 *  codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_AMR_
#define ti_xdais_dm_ISPEECH1_AMR_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_AMR */
/*@{*/


/**
 *  @brief      Bitrate selection for AMR
 */
typedef enum {
    ISPEECH1_AMR_BITRATE_4P75 = 0,     /**<  4.75 kbps */
    ISPEECH1_AMR_BITRATE_5P15 = 1,     /**<  5.15 kbps */
    ISPEECH1_AMR_BITRATE_5P9  = 2,     /**<  5.9  kbps */
    ISPEECH1_AMR_BITRATE_6P7  = 3,     /**<  6.7  kbps */
    ISPEECH1_AMR_BITRATE_7P4  = 4,     /**<  7.4  kbps */
    ISPEECH1_AMR_BITRATE_7P95 = 5,     /**<  7.95 kbps */
    ISPEECH1_AMR_BITRATE_10P2 = 6,     /**< 10.2  kbps */
    ISPEECH1_AMR_BITRATE_12P2 = 7,     /**< 12.2  kbps */

    /** Default setting. */
    ISPEECH1_AMR_BITRATE_DEFAULT = ISPEECH1_AMR_BITRATE_12P2
} ISPEECH1_AMR_BitRate;


/**
 *  @brief      Codec selection.
 *
 *  @remarks    This parameter is used to select the codec in cases where
 *              multiple codecs are supported from the same code base.
 */
typedef enum {
    ISPEECH1_AMR_CODECSELECT_PRIMARY = 0,      /**< Primary mode - AMR. */
    ISPEECH1_AMR_CODECSELECT_SECONDARY = 1,    /**< Secondary mode - EFR. */

    /** Default setting. */
    ISPEECH1_AMR_CODECSELECT_DEFAULT = ISPEECH1_AMR_CODECSELECT_PRIMARY
} ISPEECH1_AMR_CodecSelect;


/**
 *  @brief      Packing type options for AMR.
 */
typedef enum {
    ISPEECH1_AMR_PACKTYPE_IF1_NOCRC = 0,     /**< Interface format 1,
                                              *   without CRC check (as per
                                              *   3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC = 1,   /**< Interface format 1,
                                              *   with CRC check (as per
                                              *   3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_IF2 = 2,           /**< Interface format 2 (as
                                              *   per 3GPP 26.101).
                                              */
    ISPEECH1_AMR_PACKTYPE_MIME = 3,          /**< MIME/MMSIO/file storage
                                              *   format.
                                              */

    /** Default setting. */
    ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT = ISPEECH1_AMR_PACKTYPE_IF1_NOCRC
} ISPEECH1_AMR_PackingType;


/**
 *  @brief      Voice activity detector (VAD) selection.
 */
typedef enum {
    ISPEECH1_AMR_VADSELECT_VAD1 = 1,    /**< VAD 1 */
    ISPEECH1_AMR_VADSELECT_VAD2 = 2,    /**< VAD 2 */

    /** Default setting. */
    ISPEECH1_AMR_VADSELECT_DEFAULT = ISPEECH1_AMR_VADSELECT_VAD1
} ISPEECH1_AMR_VADSelect;


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_AMR_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

