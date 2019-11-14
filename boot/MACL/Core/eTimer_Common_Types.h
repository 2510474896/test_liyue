/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: eTimer_Common_Types.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:55CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/
/**
*   @file    eTimer_Common_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcl - eTIMER driver header file.
*   @details eTIMER defines.
*
*   @addtogroup ETIMER_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : eDMA
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_ASR_REL_4_0_REV_0003_20141024
*
*   (c) Copyright 2006-2014 Freescale Inc
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef ETIMER_COMMON_TYPES_H
#define ETIMER_COMMON_TYPES_H
/**
*   @file    eTimer_Common_Types.h
*/
/**
* @page misra_violations MISRA-C:2004 violations
* 
* @section eTIMER_COMMON_TYPES_H_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure 
* that 31 character significance and case sensitivity are supported for external identifiers.
* Compilers and linkers checked. Feature is supported 
*
*/
#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @{
* @file           eTimer_Common_Types.h
* @brief          Source file version information
* 
*/
#define ETIMER_COMMON_TYPES_VENDOR_ID                       43
/** @violates @ref eTIMER_COMMON_TYPES_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be 
*checked to ensure that 31 character significance and case sensitivity are supported for external identifiers. */
#define ETIMER_COMMON_TYPES_AR_RELEASE_MAJOR_VERSION        4
/** @violates @ref eTIMER_COMMON_TYPES_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be 
*checked to ensure that 31 character significance and case sensitivity are supported for external identifiers. */
#define ETIMER_COMMON_TYPES_AR_RELEASE_MINOR_VERSION        0
/** @violates @ref eTIMER_COMMON_TYPES_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be 
*checked to ensure that 31 character significance and case sensitivity are supported for external identifiers. */
#define ETIMER_COMMON_TYPES_AR_RELEASE_REVISION_VERSION     3
#define ETIMER_COMMON_TYPES_SW_MAJOR_VERSION                1
#define ETIMER_COMMON_TYPES_SW_MINOR_VERSION                0
#define ETIMER_COMMON_TYPES_SW_PATCH_VERSION                0
/** @} */

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @{
* @brief          ETIMER channels defines
* @details        There are defines used for the ETIMER channel encoding -> channel_id
*
* @note           an ETIMER module generally has only 6 channels so by using this method 
*                 there will be gaps of 2 channels between different ETIMER modules because
*                 [              5 bit  | 3 bit               ]
*                 [ module id: 31 ... 0 | channel id: 7 ... 0 ]
*/
#define ETIMER_MOD_MASK_U8  (uint8)0xF8
#define ETIMER_MOD_SHIFT (uint8)3U
#define ETIMER_CH_MASK_U8   (uint8)0x7
#define ETIMER_CH_SHIFT  (uint8)0U
/** @} */



/**
* @brief ETIMER 0 channel 0
*/
#define ETIMER_0_CH_0    (uint8)0x00
/**
* @brief ETIMER 0 channel 1 
*/
#define ETIMER_0_CH_1    (uint8)0x01
/**
* @brief ETIMER 0 channel 2 
*/
#define ETIMER_0_CH_2    (uint8)0x02
/**
* @brief ETIMER 0 channel 3 
*/
#define ETIMER_0_CH_3    (uint8)0x03
/**
* @brief ETIMER 0 channel 4 
*/
#define ETIMER_0_CH_4    (uint8)0x04
/**
* @brief ETIMER 0 channel 5 
*/
#define ETIMER_0_CH_5    (uint8)0x05

/**
* @brief ETIMER 1 channel 0
*/
#define ETIMER_1_CH_0    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x00)
/**
* @brief ETIMER 1 channel 1
*/
#define ETIMER_1_CH_1    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x01)
/**
* @brief ETIMER 1 channel 2
*/
#define ETIMER_1_CH_2    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x02)
/**
* @brief ETIMER 1 channel 3
*/
#define ETIMER_1_CH_3    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x03)
/**
* @brief ETIMER 1 channel 4
*/
#define ETIMER_1_CH_4    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x04)
/**
* @brief ETIMER 1 channel 5
*/
#define ETIMER_1_CH_5    (uint8)((uint8)(1U<<ETIMER_MOD_SHIFT) + (uint8)0x05)

/**
* @brief ETIMER 2 channel 0
*/
#define ETIMER_2_CH_0    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x00)
/**
* @brief ETIMER 2 channel 1
*/
#define ETIMER_2_CH_1    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x01)
/**
* @brief ETIMER 2 channel 2
*/
#define ETIMER_2_CH_2    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x02)
/**
* @brief ETIMER 2 channel 3
*/
#define ETIMER_2_CH_3    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x03)
/**
* @brief ETIMER 2 channel 4
*/
#define ETIMER_2_CH_4    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x04)
/**
* @brief ETIMER 2 channel 5
*/
#define ETIMER_2_CH_5    (uint8)((uint8)(2U<<ETIMER_MOD_SHIFT) + (uint8)0x05)


/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif 

/** @} */
