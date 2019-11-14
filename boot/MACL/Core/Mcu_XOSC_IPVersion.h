/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_XOSC_IPVersion.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:35CST $

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
*   @file    Mcu_XOSC_IPVersion.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Platform version definitions, used inside IPV_XOSC.
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

#ifndef Mcu_XOSC_IPVERSION_H
#define Mcu_XOSC_IPVERSION_H


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_XOSC_IPVersion_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/* none */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_XOSC_IPVERSION_VENDOR_ID                       43
/** @violates @ref Mcu_XOSC_IPVersion_h_REF_1 The compiler/linker shall be checked ... */
#define MCU_XOSC_IPVERSION_AR_RELEASE_MAJOR_VERSION        4
/** @violates @ref Mcu_XOSC_IPVersion_h_REF_1 The compiler/linker shall be checked ... */
#define MCU_XOSC_IPVERSION_AR_RELEASE_MINOR_VERSION        0
/** @violates @ref Mcu_XOSC_IPVersion_h_REF_1 The compiler/linker shall be checked ... */
#define MCU_XOSC_IPVERSION_AR_RELEASE_REVISION_VERSION     3
#define MCU_XOSC_IPVERSION_SW_MAJOR_VERSION                1
#define MCU_XOSC_IPVERSION_SW_MINOR_VERSION                0
#define MCU_XOSC_IPVERSION_SW_PATCH_VERSION                0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define IPV_XOSC_00_00_14_64        (0x00001464UL)
#define IPV_XOSC_01_00_06_00        (0x01000600UL)


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

#endif /* Mcu_XOSC_IPVERSION_H */
