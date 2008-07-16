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
 *  @file       ti/xdais/dm/ispeech1_wbamr.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are needed for WB-AMR
 */
/**
 *  @defgroup   ti_xdais_dm_ISPEECH1_WBAMR  xDM 1.00 Speech/Voice Interface (WBAMR)
 *
 *  This is the xDM 1.00 speech/voice interface shared between the various
 *  WB-AMR codecs.
 */

#ifndef ti_xdais_dm_ISPEECH1_WBAMR_
#define ti_xdais_dm_ISPEECH1_WBAMR_

#include "ispeech1.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_ISPEECH1_WBAMR */
/*@{*/


/**
 *  @brief      Packing Type defintions for AMR
 */
typedef enum {
    ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC = 0,  /**< Interface format 1,
                                              *   without CRC check (as per
                                              *   3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC = 1,/**< Interface format 1,
                                              *   with CRC check (as per
                                              *   3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_IF2 = 2,        /**< Interface format 2 (as
                                              *   per 3GPP 26.201).
                                              */
    ISPEECH1_WBAMR_PACKTYPE_MIME = 3,       /**< MIME/MMSIO/file storage
                                              *   format.
                                              */

    /** Default setting. */
    ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT = ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC
} ISPEECH1_WBAMR_PackingType;


/**
 *  @brief      Bitrate selection for AMR
 */
typedef enum {
    ISPEECH1_WBAMR_BITRATE_6P60  = 0,   /**<  6.60 kbps */
    ISPEECH1_WBAMR_BITRATE_8P85  = 1,   /**<  8.85 kbps */
    ISPEECH1_WBAMR_BITRATE_12P65 = 2,   /**< 12.65 kbps */
    ISPEECH1_WBAMR_BITRATE_14P25 = 3,   /**< 14.25 kbps */
    ISPEECH1_WBAMR_BITRATE_15P85 = 4,   /**< 15.85 kbps */
    ISPEECH1_WBAMR_BITRATE_18P25 = 5,   /**< 18.25 kbps */
    ISPEECH1_WBAMR_BITRATE_19P85 = 6,   /**< 19.85 kbps */
    ISPEECH1_WBAMR_BITRATE_23P05 = 7,   /**< 23.05 kbps */
    ISPEECH1_WBAMR_BITRATE_23P85 = 8,   /**< 23.85 kbps */

    /** Default setting. */
    ISPEECH1_WBAMR_BITRATE_DEFAULT = ISPEECH1_WBAMR_BITRATE_23P85
} ISPEECH1_WBAMR_BitRate;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* ti_xdais_dm_ISPEECH1_WBAMR_ */
/*
 *  @(#) ti.xdais.dm; 1, 0, 4,150; 11-25-2007 20:44:08; /db/wtree/library/trees/dais-i23x/src/
 */

