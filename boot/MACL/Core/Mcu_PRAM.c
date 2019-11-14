/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_PRAM.c $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:34CST $

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
*   @file    Mcu_PRAM.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - PRAM functions implementation.
*   @details Specific functions for PRAM configuration and control.
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
extern "C"
{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_PRAM_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_PRAM_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_PRAM_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers. The defines
* are validated.
*
* @section Mcu_PRAM_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer to a
* function and any type other than an integral type. Appears when accessing memory-mapped registers
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
#include "Mcu_PRAM.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_PRAM_VENDOR_ID_C                        43
/** @violates @ref Mcu_PRAM_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_PRAM_AR_RELEASE_MAJOR_VERSION_C         4
/** @violates @ref Mcu_PRAM_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_PRAM_AR_RELEASE_MINOR_VERSION_C         0
/** @violates @ref Mcu_PRAM_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_PRAM_AR_RELEASE_REVISION_VERSION_C      3
#define MCU_PRAM_SW_MAJOR_VERSION_C                 1
#define MCU_PRAM_SW_MINOR_VERSION_C                 0
#define MCU_PRAM_SW_PATCH_VERSION_C                 0


/*==================================================================================================
                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcu_PRAM header file are of the same vendor */
#if (MCU_PRAM_VENDOR_ID_C != MCU_PRAM_VENDOR_ID)
    #error "Mcu_PRAM.c and Mcu_PRAM.h have different vendor ids"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Autosar version */
#if ((MCU_PRAM_AR_RELEASE_MAJOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_MINOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_REVISION_VERSION_C != MCU_PRAM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_PRAM.c and Mcu_PRAM.h are different"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Software version */
#if ((MCU_PRAM_SW_MAJOR_VERSION_C != MCU_PRAM_SW_MAJOR_VERSION) || \
     (MCU_PRAM_SW_MINOR_VERSION_C != MCU_PRAM_SW_MINOR_VERSION) || \
     (MCU_PRAM_SW_PATCH_VERSION_C != MCU_PRAM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_PRAM.c and Mcu_PRAM.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_PRAM_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_PRAM_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_PRAM.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_PRAM_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_PRAM_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_PRAM.c and SilRegMacros.h are different"
    #endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
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
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_PRAM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_PRAM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"

#if (MCU_INIT_CLOCK == STD_ON)

/**
* @brief            This function configure MUDCR register from PRAM.
* @details          The MUDCR provides a program-visible register for user-defined control
*                   functions. It typically is used as configuration control for miscellaneous
*                   SoC-level modules.
*                       - Mcu_IPW_InitClock() from IPW.
*
* @param[in]        PRAM_pClockConfigPtr   Pointer to PRAM configuration structure.
*
* @return           void
*
*/
FUNC(void, MCU_CODE) Mcu_PRAM_SetRamWS(P2CONST( Mcu_PRAM_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) PRAM_pClockConfigPtr)
{
#if ((IPV_MC == IPV_MC_04_04_01_00) || (IPV_MC == IPV_MC_04_00_15_15) ||\
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) ||\
     (IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_05_00_00_10) \
    )
    /* PRAM0 is always enabled. */
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR1_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32RamWS) );
#elif (IPV_MC == IPV_MC_04_06_05_00)
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR1_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr1) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR2_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr2) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR3_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr3) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR4_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr4) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR5_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr5) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR6_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr6) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR7_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr7) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRCR8_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32PramcPrcr8) );
#elif (IPV_MC == IPV_MC_05_00_00_07)
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRAM0_PRCR1_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32Pramc0Prcr1) );
#if (MCU_PRAM_MULTIPLE_PRAM == STD_ON)
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRAM1_PRCR1_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32Pramc1Prcr1) );
    /** @violates @ref Mcu_PRAM_c_REF_4 MISRA 2004 Required Rule 11.1, Conversion from  */
    REG_WRITE32( PRAM2_PRCR1_ADDR32, (uint32)(PRAM_pClockConfigPtr->u32Pramc2Prcr1) );
#endif
#endif /*( IPV_MC == IPV_MC_04_03_00_00 )*/
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_PRAM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_PRAM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
