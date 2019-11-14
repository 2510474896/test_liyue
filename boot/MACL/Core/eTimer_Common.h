/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: eTimer_Common.h $
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
*   @file    eTimer_Common.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcl - eTIMER driver header file.
*   @details eTIMER driver interface.
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

#ifndef ETIMER_COMMON_H
#define ETIMER_COMMON_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section ETIMER_COMMON_H_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
*/

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
* @file           eTimer_Common.h  
*/
#define ETIMER_COMMON_VENDOR_ID                       43
#define ETIMER_COMMON_AR_RELEASE_MAJOR_VERSION        4
#define ETIMER_COMMON_AR_RELEASE_MINOR_VERSION        0
#define ETIMER_COMMON_AR_RELEASE_REVISION_VERSION     3
#define ETIMER_COMMON_SW_MAJOR_VERSION                1
#define ETIMER_COMMON_SW_MINOR_VERSION                0
#define ETIMER_COMMON_SW_PATCH_VERSION                0
/** @} */

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#define MCL_START_SEC_CODE
/** @violates @ref ETIMER_COMMON_H_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

FUNC (void, MCL_CODE) eTimer_StartChannel(VAR(uint8, AUTOMATIC) u8HwChannel);
FUNC (void, MCL_CODE) eTimer_StopChannel(VAR(uint8, AUTOMATIC) u8HwChannel);

#define MCL_STOP_SEC_CODE
/** @violates @ref ETIMER_COMMON_H_REF_1 Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*ETIMER_COMMON_H*/

/** @} */
