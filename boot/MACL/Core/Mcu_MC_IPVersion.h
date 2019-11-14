/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_MC_IPVersion.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:31CST $

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
*   @file    Mcu_MC_IPVersion.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Platform version definitions, used inside IPV_MC.
*   @details Public data types exported outside of the Mcu driver.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MC
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_HF2_ASR_REL_4_0_REV_0003_20150723
*
*   (c) Copyright 2006-2015 Freescale Inc
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef MCU_MC_IPVERSION_H
#define MCU_MC_IPVERSION_H


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_MC_IPVERSION_VENDOR_ID                       43
#define MCU_MC_IPVERSION_AR_RELEASE_MAJOR_VERSION        4
#define MCU_MC_IPVERSION_AR_RELEASE_MINOR_VERSION        0
#define MCU_MC_IPVERSION_AR_RELEASE_REVISION_VERSION     3
#define MCU_MC_IPVERSION_SW_MAJOR_VERSION                1
#define MCU_MC_IPVERSION_SW_MINOR_VERSION                0
#define MCU_MC_IPVERSION_SW_PATCH_VERSION                0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define IPV_MC_04_03_00_00      (0x04030000UL)
#define IPV_MC_04_04_01_00      (0x04040100UL)
#define IPV_MC_04_00_15_15      (0x04001515UL)
#define IPV_MC_04_01_00_00      (0x04010000UL)
#define IPV_MC_04_06_01_00      (0x04060100UL)
#define IPV_MC_04_06_05_00      (0x04060500UL)
#define IPV_MC_05_00_00_10      (0x05000010UL)
#define IPV_MC_05_00_00_07      (0x05000007UL)


/*==================================================================================================
*                                             ENUMS
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

#endif /* MCU_MC_IPVERSION_H */