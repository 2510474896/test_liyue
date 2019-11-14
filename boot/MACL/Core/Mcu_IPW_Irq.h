/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_IPW_Irq.h $
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
*   @file    Mcu_IPW_Irq.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Midle layer interface for interrupts.
*   @details File contains function prototypes used by IPV ISRs only.
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


#ifndef MCU_IPW_IRQ_H
#define MCU_IPW_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_IPW_Irq_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_IRQ_VENDOR_ID                       43
#define MCU_IPW_IRQ_AR_RELEASE_MAJOR_VERSION        4
#define MCU_IPW_IRQ_AR_RELEASE_MINOR_VERSION        0
#define MCU_IPW_IRQ_AR_RELEASE_REVISION_VERSION     3
#define MCU_IPW_IRQ_SW_MAJOR_VERSION                1
#define MCU_IPW_IRQ_SW_MINOR_VERSION                0
#define MCU_IPW_IRQ_SW_PATCH_VERSION                0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define MCU_IPW_CMU_UNMASK_VALUE_U32        ((uint32)0x00000000U)
#define MCU_IPW_CMU_ISR_FHHI_MASK32         ((uint32)0x00000004U)
#define MCU_IPW_CMU_ISR_FLLI_MASK32         ((uint32)0x00000002U)
#define MCU_IPW_CMU_ISR_OLRI_MASK32         ((uint32)0x00000001U)
/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/** @violates @ref Mcu_IPW_Irq_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#if (MCU_RGM_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
FUNC(void, MCU_CODE) Mcu_IPW_RGM_ClearClockFailIrqFlags(VAR( void, AUTOMATIC));
#endif

#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
FUNC(void, MCU_CODE) Mcu_IPW_CMU_ClearClockFailIrqFlags(VAR(uint8, AUTOMATIC) u8CmuIdx, VAR(uint32, AUTOMATIC) u32IsrMask);
#endif

#define MCU_STOP_SEC_CODE
/** @violates @ref Mcu_IPW_Irq_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* MCU_IPW_IRQ_H */

/** @} */

