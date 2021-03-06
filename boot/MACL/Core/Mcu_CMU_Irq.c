/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_CMU_Irq.c $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:30CST $

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
*   @file    Mcu_CMU_Irq.c
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
* @section Mcu_CMU_IRQ_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_CMU_IRQ_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_CMU_IRQ_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer to a
* function and any type other than an integral type. This conversion is specific to the interrupt
* handler entry / exit code.
*
* @section Mcu_CMU_IRQ_c_REF_4
* Violates MISRA 2004 Required Rule 10.1, The value of an expression of integer type shall not be
* implicitly converted to a different underlying type. Integer to pointer conversion, specific to
* the ISR entry / exit code.
*
* @section Mcu_CMU_IRQ_c_REF_5
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

/** @violates @ref Mcu_CMU_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcal.h"
/** @violates @ref Mcu_CMU_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_CMU.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define MCU_CMU_IRQ_VENDOR_ID_C                     43
#define MCU_CMU_IRQ_AR_RELEASE_MAJOR_VERSION_C      4
#define MCU_CMU_IRQ_AR_RELEASE_MINOR_VERSION_C      0
#define MCU_CMU_IRQ_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_CMU_IRQ_SW_MAJOR_VERSION_C              1
#define MCU_CMU_IRQ_SW_MINOR_VERSION_C              0
#define MCU_CMU_IRQ_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcal header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_CMU_IRQ_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_CMU_IRQ_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_CMU_Irq.c and Mcal.h are different"
    #endif
#endif

/* Check if current file and Mcu_CMU_Irq header file are of the same Autosar version */
#if (MCU_CMU_IRQ_VENDOR_ID_C != MCU_CMU_VENDOR_ID)
    #error "Mcu_CMU_Irq.c and Mcu_CMU.h have different vendor ids"
#endif
/* Check if current file and Mcu_CMU_Irq header file are of the same Autosar version */
#if ((MCU_CMU_IRQ_AR_RELEASE_MAJOR_VERSION_C    != MCU_CMU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CMU_IRQ_AR_RELEASE_MINOR_VERSION_C    != MCU_CMU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CMU_IRQ_AR_RELEASE_REVISION_VERSION_C != MCU_CMU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_CMU_Irq.c and Mcu_CMU.h are different"
#endif
/* Check if current file and Mcu_CMU_Irq header file are of the same Software version */
#if ((MCU_CMU_IRQ_SW_MAJOR_VERSION_C != MCU_CMU_SW_MAJOR_VERSION) || \
     (MCU_CMU_IRQ_SW_MINOR_VERSION_C != MCU_CMU_SW_MINOR_VERSION) || \
     (MCU_CMU_IRQ_SW_PATCH_VERSION_C != MCU_CMU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_CMU_Irq.c and Mcu_CMU.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
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

#if (MCU_CMU_ERROR_ISR_USED == STD_ON)
ISR( Mcu_Cmu_ClockFail_ISR );
#endif /* (MCU_CMU_ERROR_ISR_USED == STD_ON) */


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_CMU_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_CMU_IRQ_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (MCU_CMU_ERROR_ISR_USED == STD_ON)
/**
* @brief       This function represents the ISR handler for CMU related events.
* @details     This interrupt is triggered if one of the enabled CMU's detect an out of range clock.
*
*
* @isr
*
*/
/** @violates @ref Mcu_CMU_IRQ_c_REF_5 MISRA 2004 The IRQ handler is used by external code */
ISR( Mcu_Cmu_ClockFail_ISR )
{
    Mcu_CMU_ClockFail_Int();
    /** @violates @ref Mcu_CMU_IRQ_c_REF_3 MISRA 2004 Conversion from pointer to integer */
    /** @violates @ref Mcu_CMU_IRQ_c_REF_4 MISRA 2004 Conversion from integer to pointer */
    EXIT_INTERRUPT();
}
#endif /* (MCU_CMU_ERROR_ISR_USED == STD_ON) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_CMU_IRQ_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_CMU_IRQ_c_REF_2 MISRA 2004 Only preprocessor statements and comments before
* '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
