/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_XOSC.c $
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
*   @file    Mcu_XOSC.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - XOSC functions implementation.
*   @details Specific functions for XOSC configuration and control.
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


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_XOSC_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_XOSC_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory
* section
*
* @section Mcu_XOSC_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_XOSC_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer
* to a function and any other type than an integral type. Specific for accessing memory-mapped
* registers
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
#include "Mcu_XOSC.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_XOSC_VENDOR_ID_C                        43
/** @violates @ref Mcu_XOSC_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_XOSC_AR_RELEASE_MAJOR_VERSION_C         4
/** @violates @ref Mcu_XOSC_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_XOSC_AR_RELEASE_MINOR_VERSION_C         0
/** @violates @ref Mcu_XOSC_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_XOSC_AR_RELEASE_REVISION_VERSION_C      3
#define MCU_XOSC_SW_MAJOR_VERSION_C                 1
#define MCU_XOSC_SW_MINOR_VERSION_C                 0
#define MCU_XOSC_SW_PATCH_VERSION_C                 0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcu_XOSC header file are of the same vendor */
#if (MCU_XOSC_VENDOR_ID_C != MCU_XOSC_VENDOR_ID)
    #error "Mcu_XOSC.c and Mcu_XOSC.h have different vendor ids"
#endif
/* Check if current file and Mcu_XOSC header file are of the same Autosar version */
#if ((MCU_XOSC_AR_RELEASE_MAJOR_VERSION_C != MCU_XOSC_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_XOSC_AR_RELEASE_MINOR_VERSION_C != MCU_XOSC_AR_RELEASE_MINOR_VERSION) || \
     (MCU_XOSC_AR_RELEASE_REVISION_VERSION_C != MCU_XOSC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_XOSC.c and Mcu_XOSC.h are different"
#endif
/* Check if current file and Mcu_XOSC header file are of the same Software version */
#if ((MCU_XOSC_SW_MAJOR_VERSION_C != MCU_XOSC_SW_MAJOR_VERSION) || \
     (MCU_XOSC_SW_MINOR_VERSION_C != MCU_XOSC_SW_MINOR_VERSION) || \
     (MCU_XOSC_SW_PATCH_VERSION_C != MCU_XOSC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_XOSC.c and Mcu_XOSC.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_XOSC_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_XOSC_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_XOSC.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_XOSC_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_XOSC_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_XOSC.c and SilRegMacros.h are different"
    #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_XOSC_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_XOSC_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"

#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            This function check the XOSC registers
* @details          This function evaluate the status of each IP RAM area. The default XOSC
*                   configuration as it is located in the test flash memory leads to a full
*                   self-test after an XOSC reset event (running all MBISTs and LBISTs).
*                   MBIST - Boot-time Memory Built-In Self-Test (volatile memories (SRAMs) and ROMs
*                   test).
*                   MBIST Engine - Manages the testing of embedded memory blocks.
*
* @return           Status of the RAM Content.
* @retval           MCU_RAMSTATE_INVALID   Ram content is not valid or unknown (default).
* @retval           MCU_RAMSTATE_VALID   Ram content is valid.
*
*/
FUNC( void, MCU_CODE) Mcu_XOSC_Config(P2CONST( Mcu_XOSC_ConfigType, AUTOMATIC, MCU_APPL_DATA) XOSC_pConfigPtr)
{
    /* write XOSC configuration */
    /** @violates @ref Mcu_XOSC_c_REF_4 Cast from unsigned long to pointer.*/
    REG_WRITE32( XOSC_CTL_ADDR32, XOSC_pConfigPtr->u32Config );
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_XOSC_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_XOSC_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
