/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_MC_Irq.c $
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
*   @file    Mcu_MC_Irq.c
*
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Interrupt handlers.
*   @details Interrupt handlers that should be managed by the Mcu driver.
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
* @section Mcu_Mc_IRQ_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_Mc_IRQ_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_Mc_IRQ_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between
* a pointer to a function and any type other than an integral type.
* This conversion is specific to the interrupt handler entry / exit code.
*
* @section Mcu_Mc_IRQ_c_REF_4
* Violates MISRA 2004 Required Rule 10.1, The value of an expression of integer type shall not be
* implicitly converted to a different underlying type. Integer to pointer conversion, specific to
* the ISR entry / exit code.
*
* @section Mcu_Mc_IRQ_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
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

/** @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcal.h"

/** @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_MC_ME.h"

/** @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_MC_CGM.h"

/** @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_MC_RGM.h"

/** @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_MC_PCU.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_MC_IRQ_VENDOR_ID_C                     43
#define MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C      4
#define MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C      0
#define MCU_MC_IRQ_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_MC_IRQ_SW_MAJOR_VERSION_C              1
#define MCU_MC_IRQ_SW_MINOR_VERSION_C              0
#define MCU_MC_IRQ_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcal header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_MC_Irq.c and Mcal.h are different"
    #endif
#endif

/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if (MCU_MC_IRQ_VENDOR_ID_C != MCU_MC_CGM_VENDOR_ID)
    #error "Mcu_MC_Irq.c and Mcu_MC_CGM.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if ((MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_CGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_CGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_REVISION_VERSION_C != MCU_MC_CGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_Irq.c and Mcu_MC_CGM.h are different"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Software version */
#if ((MCU_MC_IRQ_SW_MAJOR_VERSION_C != MCU_MC_CGM_SW_MAJOR_VERSION) || \
     (MCU_MC_IRQ_SW_MINOR_VERSION_C != MCU_MC_CGM_SW_MINOR_VERSION) || \
     (MCU_MC_IRQ_SW_PATCH_VERSION_C != MCU_MC_CGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_Irq.c and Mcu_MC_CGM.h are different"
#endif

/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if (MCU_MC_IRQ_VENDOR_ID_C != MCU_MC_ME_VENDOR_ID)
    #error "Mcu_MC_Irq.c and Mcu_MC_ME.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if ((MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_REVISION_VERSION_C != MCU_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_Irq.c and Mcu_MC_ME.h are different"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Software version */
#if ((MCU_MC_IRQ_SW_MAJOR_VERSION_C != MCU_MC_ME_SW_MAJOR_VERSION) || \
     (MCU_MC_IRQ_SW_MINOR_VERSION_C != MCU_MC_ME_SW_MINOR_VERSION) || \
     (MCU_MC_IRQ_SW_PATCH_VERSION_C != MCU_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_Irq.c and Mcu_MC_ME.h are different"
#endif

/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if (MCU_MC_IRQ_VENDOR_ID_C != MCU_MC_PCU_VENDOR_ID)
    #error "Mcu_MC_Irq.c and Mcu_MC_PCU.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if ((MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_PCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_PCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_REVISION_VERSION_C != MCU_MC_PCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_Irq.c and Mcu_MC_PCU.h are different"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Software version */
#if ((MCU_MC_IRQ_SW_MAJOR_VERSION_C != MCU_MC_PCU_SW_MAJOR_VERSION) || \
     (MCU_MC_IRQ_SW_MINOR_VERSION_C != MCU_MC_PCU_SW_MINOR_VERSION) || \
     (MCU_MC_IRQ_SW_PATCH_VERSION_C != MCU_MC_PCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_Irq.c and Mcu_MC_PCU.h are different"
#endif

/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if (MCU_MC_IRQ_VENDOR_ID_C != MCU_MC_RGM_VENDOR_ID)
    #error "Mcu_MC_Irq.c and Mcu_MC_RGM.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Autosar version */
#if ((MCU_MC_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_IRQ_AR_RELEASE_REVISION_VERSION_C != MCU_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_Irq.c and Mcu_MC_RGM.h are different"
#endif
/* Check if current file and Mcu_MC_Irq header file are of the same Software version */
#if ((MCU_MC_IRQ_SW_MAJOR_VERSION_C != MCU_MC_RGM_SW_MAJOR_VERSION) || \
     (MCU_MC_IRQ_SW_MINOR_VERSION_C != MCU_MC_RGM_SW_MINOR_VERSION) || \
     (MCU_MC_IRQ_SW_PATCH_VERSION_C != MCU_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_Irq.c and Mcu_MC_RGM.h are different"
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
#if (MCU_SAFE_MODE_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_ModeEnterSafe_ISR );
#endif /* (MCU_SAFE_MODE_ISR_USED == STD_ON) */

#if (MCU_TRANSITION_COMPLETE_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_ModeTransitionComplete_ISR );
#endif /* (MCU_TRANSITION_COMPLETE_ISR_USED == STD_ON) */

#if (MCU_INVALID_MODE_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_InvalidMode_ISR );
#endif /* (MCU_INVALID_MODE_ISR_USED == STD_ON) */

#if ((MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) || \
     (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON) || \
     (MCU_INVALID_CORE_CONFIGURATION_ISR_USED == STD_ON) \
    )
ISR( Mcu_Mcv4_InvalidConfiguration_ISR );
#endif /* (MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) ||
          (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON) */

#if (IPV_MC == IPV_MC_05_00_00_10)
#if ((MCU_SAFE_MODE_ISR_USED == STD_ON ) || (MCU_INVALID_MODE_ISR_USED == STD_ON ) || \
     (MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) || (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON) || \
     (MCU_INVALID_CORE_CONFIGURATION_ISR_USED == STD_ON) \
    )
ISR( Mcu_Mcv4_McMe_ISR );
#endif
#endif

#if (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_VoltageError_ISR );
#endif /* (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON) */

#if (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_TemperatureError_ISR );
#endif /* (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON) */

#if (MCU_RESET_ALTERNATE_ISR_USED == STD_ON)
ISR( Mcu_Mcv4_AlternateReset_ISR );
#endif /* (MCU_RESET_ALTERNATE_ISR_USED == STD_ON) */

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Mc_IRQ_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00) || \
     (IPV_MC == IPV_MC_05_00_00_07) \
    )

#if (MCU_SAFE_MODE_ISR_USED == STD_ON)
/**
* @brief        This function represents the ISR for entering safe mode.
* @details      When entering safe mode, if enabled, an interrupt is triggered.
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_ModeEnterSafe_ISR)
{
    Mcu_MC_ME_SafeMode_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_SAFE_MODE_ISR_USED == STD_ON) */


#if (MCU_TRANSITION_COMPLETE_ISR_USED == STD_ON)
/**
* @brief        Mode transition complete ISR.
* @details      Mode transition complete interrupt - This ISR is called whenever the mode
*               transition process completes (S_MTRANS transits from 1 to 0).
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_ModeTransitionComplete_ISR )
{
    Mcu_MC_ME_TransitionComplete_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_TRANSITION_COMPLETE_ISR_USED == STD_ON) */


#if (MCU_INVALID_MODE_ISR_USED == STD_ON)
/**
* @brief        Invalid mode ISR.
* @details      Invalid mode interrupt - This bit is set whenever an invalid mode transition is
*               requested.
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_InvalidMode_ISR )
{
    Mcu_MC_ME_InvalidMode_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_INVALID_MODE_ISR_USED == STD_ON) */


#if ((MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) || (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON) || \
     (MCU_INVALID_CORE_CONFIGURATION_ISR_USED == STD_ON) \
    )
/**
* @brief        Invalid mode configuration ISR.
* @details      Invalid mode configuration interrupt - This bit is set whenever a write operation
*               to ME_<mode>_MC registers with invalid mode configuration is attempted, during a
*               mode transition if a clock which is required to be on by an enabled peripheral is
*               configured to be turned off or if a write access to one of the ME_CCTLn registers
*               is attempted while a mode transition is in progress.
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_InvalidConfiguration_ISR )
{
    Mcu_MC_ME_InvalidModeConfig_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* ((MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) ||
          (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON)) */


#if (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON)
/**
* @brief        Internal voltage out of range ISR.
* @details      This ISR is generated when the PMC monitor detects an out of range voltage
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_VoltageError_ISR )
{
    Mcu_PMU_VoltageError_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON) */


#if (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON)
/**
* @brief        Chip temperature ISR.
* @details      This ISR is generated by the PMC monitor when one of the temperature sensors rises
*               above it's corresponding threshold.
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_TemperatureError_ISR )
{
    Mcu_PMU_TemperatureError_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON) */


#if (MCU_RESET_ALTERNATE_ISR_USED == STD_ON)
/**
* @brief        Alternate Reset event ISR.
* @details      This ISR is generated by the MC_RGM IP when some events are configured to generate
*               an interrupt request.
*
* @isr
*
*/
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_AlternateReset_ISR )
{
    Mcu_MC_RGM_ResetAlt_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_RESET_ALTERNATE_ISR_USED == STD_ON) */
#endif /* ... */


#if (IPV_MC == IPV_MC_05_00_00_10)
#if ((MCU_SAFE_MODE_ISR_USED == STD_ON ) || (MCU_INVALID_MODE_ISR_USED == STD_ON) || \
     (MCU_INVALID_CONFIGURATION_ISR_USED == STD_ON) || (MCU_INVALID_CLK_CONFIGURATION_ISR_USED == STD_ON) || \
     (MCU_INVALID_CORE_CONFIGURATION_ISR_USED == STD_ON) \
    )
    /*
    */
/** @violates @ref Mcu_Mc_IRQ_c_REF_5 The IRQ handler is used by external code */
ISR( Mcu_Mcv4_McMe_ISR )
{
    Mcu_MC_ME_Int();
    /** @violates @ref Mcu_Mc_IRQ_c_REF_3 Conversion from pointer to integer */
    /** @violates @ref Mcu_Mc_IRQ_c_REF_4 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif
#endif

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_Mc_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Mc_IRQ_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
