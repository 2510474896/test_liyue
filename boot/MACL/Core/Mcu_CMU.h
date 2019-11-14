/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_CMU.h $
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
*   @file    Mcu_CMU.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from IPV_CMU.
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

#ifndef MCU_CMU_H
#define MCU_CMU_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_CMU_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions.
*
* @section Mcu_CMU_h_REF_4
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
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

/** @violates @ref Mcu_CMU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_CMU_Types.h"

/** @violates @ref Mcu_CMU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_EnvCfg.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_CMU_VENDOR_ID                    43
#define MCU_CMU_AR_RELEASE_MAJOR_VERSION     4
#define MCU_CMU_AR_RELEASE_MINOR_VERSION     0
#define MCU_CMU_AR_RELEASE_REVISION_VERSION  3
#define MCU_CMU_SW_MAJOR_VERSION             1
#define MCU_CMU_SW_MINOR_VERSION             0
#define MCU_CMU_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_CMU_VENDOR_ID != MCU_CMU_TYPES_VENDOR_ID)
    #error "Mcu_CMU.h and Mcu_CMU_Types.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_CMU_AR_RELEASE_MAJOR_VERSION != MCU_CMU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CMU_AR_RELEASE_MINOR_VERSION != MCU_CMU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CMU_AR_RELEASE_REVISION_VERSION != MCU_CMU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_CMU.h and Mcu_CMU_Types.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_CMU_SW_MAJOR_VERSION != MCU_CMU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_CMU_SW_MINOR_VERSION != MCU_CMU_TYPES_SW_MINOR_VERSION) || \
     (MCU_CMU_SW_PATCH_VERSION != MCU_CMU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_CMU.h and Mcu_CMU_Types.h are different"
#endif

/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_CMU_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_CMU.h and Mcu_EnvCfg.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_CMU_AR_RELEASE_MAJOR_VERSION != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CMU_AR_RELEASE_MINOR_VERSION != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CMU_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_CMU.h and Mcu_EnvCfg.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_CMU_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_CMU_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_CMU_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_CMU.h and Mcu_EnvCfg.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
FUNC( void, MCU_CODE) Mcu_CMU_DeInit(VAR( void, AUTOMATIC));
FUNC( void, MCU_CODE) Mcu_CMU_Init(P2CONST(Mcu_CMU_ConfigType, AUTOMATIC, MCU_APPL_DATA) pCmu_ConfigPtr);
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
FUNC( void, MCU_CODE ) Mcu_CMU_Disable_CMU(VAR (uint8, AUTOMATIC) u8IndexCmu);
#endif
#endif

/* isr handler */
#if (MCU_CMU_ERROR_ISR_USED == STD_ON)
FUNC( void, MCU_CODE) Mcu_CMU_ClockFail_Int( VAR( void, AUTOMATIC) );
#endif

#if ((MCU_CMU_ERROR_ISR_USED == STD_ON) || (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON))
FUNC(Std_ReturnType, MCU_CODE) Mcu_CMU_ClearClockFailIrqFlags(VAR(uint8, AUTOMATIC) u8CmuIdx, VAR(uint32, AUTOMATIC) u32IsrMask);
#endif /* ((MCU_CMU_ERROR_ISR_USED == STD_ON) || (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)) */

#ifdef __cplusplus
}
#endif

#endif /* MCU_CMU_H */

/** @} */
