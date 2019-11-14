/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_Reg_eSys_SIUL2.h $
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
*   @file    Mcu_Reg_eSys_SIUL2.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Macros for memory access.
*   @details Macros/Defines used for registry and memory read/write.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : M4_SRC_FAMILY
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

#ifndef MCU_REG_ESYS_SIUL2_H
#define MCU_REG_ESYS_SIUL2_H


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_Reg_eSys_SIUL2_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_Reg_eSys_SIUL2_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
*
* @section Mcu_Reg_eSys_SIUL2_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_1 Repeated include files.*/
#include "Reg_eSys.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIUL2_VENDOR_ID                       43
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIUL2_AR_RELEASE_MAJOR_VERSION        4
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIUL2_AR_RELEASE_MINOR_VERSION        0
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIUL2_AR_RELEASE_REVISION_VERSION     3
/** @violates @ref Mcu_Reg_eSys_SIUL2_h_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIUL2_SW_MAJOR_VERSION                1
#define MCU_REG_ESYS_SIUL2_SW_MINOR_VERSION                0
#define MCU_REG_ESYS_SIUL2_SW_PATCH_VERSION                0


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Reg_eSys header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_REG_ESYS_SIUL2_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_REG_ESYS_SIUL2_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Reg_eSys_SIUL2.h and Reg_eSys.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#define SIUL2_MIDR1_ADDR32              ((uint32)( SIUL2_BASEADDR + 0x0004U ))
#define SIUL2_MIDR2_ADDR32              ((uint32)( SIUL2_BASEADDR + 0x0008U ))

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

#endif /* MCU_REG_ESYS_SIUL2_H */

/** @} */

