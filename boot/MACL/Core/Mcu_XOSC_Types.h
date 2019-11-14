/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_XOSC_Types.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:36CST $

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
*   @file    Mcu_XOSC_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from XOSC.
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


#ifndef MCU_XOSC_TYPES_H
#define MCU_XOSC_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_XOSC_Types_H_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_XOSC_Types_H_REF_2
*       Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
*       This violation is due to function like macros defined for register operations.
*       Function like macros are used to reduce code complexity.
*
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
/** @violates @ref Mcu_XOSC_Types_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_Cfg.h"
/** @violates @ref Mcu_XOSC_Types_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Reg_eSys_XOSC.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_XOSC_TYPES_VENDOR_ID                     43
#define MCU_XOSC_TYPES_AR_RELEASE_MAJOR_VERSION      4
#define MCU_XOSC_TYPES_AR_RELEASE_MINOR_VERSION      0
#define MCU_XOSC_TYPES_AR_RELEASE_REVISION_VERSION   3
#define MCU_XOSC_TYPES_SW_MAJOR_VERSION              1
#define MCU_XOSC_TYPES_SW_MINOR_VERSION              0
#define MCU_XOSC_TYPES_SW_PATCH_VERSION              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_Cfg header file are from the same vendor */
#if (MCU_XOSC_TYPES_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_XOSC_Types.h and Mcu_Cfg.h have different vendor ids"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Autosar version */
#if ((MCU_XOSC_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_XOSC_TYPES_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_XOSC_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_XOSC_Types.h and Mcu_Cfg.h are different"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Software version */
#if ((MCU_XOSC_TYPES_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_XOSC_TYPES_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_XOSC_TYPES_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_XOSC_Types.h and Mcu_Cfg.h are different"
#endif

/* Check if source file and Reg_eSys_XOSC header file are from the same vendor */
#if (MCU_XOSC_TYPES_VENDOR_ID != REG_ESYS_XOSC_VENDOR_ID)
    #error "Mcu_XOSC_Types.h and Reg_eSys_XOSC.h have different vendor ids"
#endif
/* Check if source file and Reg_eSys_XOSC header file are of the same Autosar version */
#if ((MCU_XOSC_TYPES_AR_RELEASE_MAJOR_VERSION != REG_ESYS_XOSC_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_XOSC_TYPES_AR_RELEASE_MINOR_VERSION != REG_ESYS_XOSC_AR_RELEASE_MINOR_VERSION) || \
     (MCU_XOSC_TYPES_AR_RELEASE_REVISION_VERSION != REG_ESYS_XOSC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_XOSC_Types.h and Reg_eSys_XOSC.h are different"
#endif
/* Check if source file and Reg_eSys_XOSC header file are of the same Software version */
#if ((MCU_XOSC_TYPES_SW_MAJOR_VERSION != REG_ESYS_XOSC_SW_MAJOR_VERSION) || \
     (MCU_XOSC_TYPES_SW_MINOR_VERSION != REG_ESYS_XOSC_SW_MINOR_VERSION) || \
     (MCU_XOSC_TYPES_SW_PATCH_VERSION != REG_ESYS_XOSC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_XOSC_Types.h and Reg_eSys_XOSC.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/** @violates @ref Mcu_XOSC_Types_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function like macro. */
#define XOSC_EOCV_VALUE_U32(value)      ( (uint32)( (uint32)( (value) << (uint32)16U ) & XOSC_CTL_EOCV_MASK32 ) )
/** @violates @ref Mcu_XOSC_Types_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function like macro. */
#define XOSC_CTL_VALUE_U32(value)       ( (uint32)( ( (value) & XOSC_CTL_RWBITS_MASK32) | XOSC_CTL_RESBITS_MASK32 ) )

#define XOSC_OSCBYP_ENABLE_MASK32       (XOSC_CTL_OSCBYP_MASK32)
#define XOSC_OSCBYP_DISABLE_MASK32      ((uint32)0x00000000U)

#define XOSC_MOSC_ENABLE_MASK32         (XOSC_CTL_MOSC_MASK32)
#define XOSC_MOSC_DISABLE_MASK32        ((uint32)0x00000000U)


#if (IPV_XOSC == IPV_XOSC_01_00_06_00)
#define XOSC_OSCM_ENABLE_MASK32         (XOSC_CTL_OSCM_MASK32)
#define XOSC_OSCM_DISABLE_MASK32        ((uint32)0x00000000U)

#define XOSC_MON_ENABLE_MASK32          (XOSC_CTL_MON_MASK32)
#define XOSC_MON_DISABLE_MASK32         ((uint32)0x00000000U)
#endif /* (IPV_XOSC == IPV_XOSC_01_00_06_00) */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief    a
* @details  b
*/
typedef struct
{
    VAR (uint32, MCU_VAR) u32Config;    /** @brief XOSC configuration register. */

}Mcu_XOSC_ConfigType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


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

#endif /* MCU_XOSC_TYPES_H */

/** @} */
