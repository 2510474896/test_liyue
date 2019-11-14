/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Can_IPW.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:24CST $

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
*   @file    Can_IPW.h
*   @implements Can_IPW.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Can - module interface
*   @details Main header file - can include different IPV models.
*
*   @addtogroup CAN_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : FLEXCAN
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_HF3_ASR_REL_4_0_REV_0003_20151120
*
*   (c) Copyright 2006-2015 Freescale Inc
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef CAN_IPW_H
#define CAN_IPW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section CAN_IPW_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section CAN_IPW_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
* Precautions shall be taken in order to prevent the contents of a header file 
* being included twice This is not a violation since all header files are 
* protected against multiple inclusions
*
* @section CAN_IPW_h_REF_3
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
* Middle layer between AUTOSAR and hardware needs a way to map HLD
* functions to LLD functions.
*
* @section CAN_IPW_h_REF_4
* Violates MISRA 2004 Required Rule 19.10 , In the definition of a function-like macro each instance of 
* a parameter shall be enclosed in parantheses UNLESS it is used as the operand of # or ##.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can_Flexcan.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @{
* @file           Can_IPW.h
*/
#define CAN_IPW_VENDOR_ID_H                    43
#define CAN_IPW_MODULE_ID_H                    80
#define CAN_IPW_AR_RELEASE_MAJOR_VERSION_H     4
#define CAN_IPW_AR_RELEASE_MINOR_VERSION_H     0
/*
* @violates @ref CAN_IPW_h_REF_1 Violates MISRA 2004 Advisory Rule 1.4
*/
#define CAN_IPW_AR_RELEASE_REVISION_VERSION_H  3
#define CAN_IPW_SW_MAJOR_VERSION_H             1
#define CAN_IPW_SW_MINOR_VERSION_H             0
#define CAN_IPW_SW_PATCH_VERSION_H             0
/**@}*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN configuration header file are of the same vendor */
#if (CAN_IPW_VENDOR_ID_H != CAN_VENDOR_ID_CFG)
#error "Can_IPW.h and Can_Cfg.h have different vendor ids"
#endif
/* Check if current file and CAN configuration header file are of the same Autosar version */
#if ((CAN_IPW_AR_RELEASE_MAJOR_VERSION_H    != CAN_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (CAN_IPW_AR_RELEASE_MINOR_VERSION_H    != CAN_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (CAN_IPW_AR_RELEASE_REVISION_VERSION_H != CAN_AR_RELEASE_REVISION_VERSION_CFG_H))
#error "AutoSar Version Numbers of Can_IPW.h and Can_Cfg.h are different"
#endif
/* Check if current file and CAN configuration header file are of the same software version */
#if ((CAN_IPW_SW_MAJOR_VERSION_H != CAN_SW_MAJOR_VERSION_CFG_H) || \
     (CAN_IPW_SW_MINOR_VERSION_H != CAN_SW_MINOR_VERSION_CFG_H) || \
     (CAN_IPW_SW_PATCH_VERSION_H != CAN_SW_PATCH_VERSION_CFG_H))
#error "Software Version Numbers of Can_IPW.h and Can_Cfg.h are different"
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
    #define     CAN_NULL_OFFSET      (FLEXCAN_NULL_OFFSET_U8)
    #define     CAN_MB_DATABYTES     (FLEXCAN_MB_DATABYTES_U8)

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define Can_IPW_ProcessRx( controller, mbindex_start, mbindex_end )                              (Can_FlexCan_ProcessRx( controller, mbindex_start, mbindex_end))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define Can_IPW_ProcessTx(controller, mbindex_start, mbindex_end)                                (Can_FlexCan_ProcessTx( controller, mbindex_start, mbindex_end ))
 
#if (CAN_RXFIFO_ENABLE == STD_ON)

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define Can_IPW_RxFifoFrameAvNotif(controller)                                                    (Can_FlexCan_RxFifoFrameAvNotif( controller))
 
#endif

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define Can_IPW_ProcessBusOff(controller)                                                         (Can_FlexCan_ProcessBusOff( controller))
    
        #if (CAN_WAKEUP_SUPPORT == STD_ON)

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_ProcessWakeup(controller)                                         (Can_FlexCan_ProcessWakeup(controller))
    #endif

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_InitVariables()                                                   (Can_FlexCan_InitVariables())

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_Init(Controller)                                                  (Can_FlexCan_Init(Controller))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_ResetController(Controller)                                       (Can_FlexCan_ResetController(Controller))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_ChangeBaudrate(Controller)                                        (Can_FlexCan_ChangeBaudrate(Controller))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_SetControllerMode(Controller, pCanControlerDescriptor, Transition, canif_notification_required) \
                        (Can_FlexCan_SetControllerMode((Controller), (pCanControlerDescriptor), (Transition), (canif_notification_required)))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_DisableControllerInterrupts(Controller, pCanControlerDescriptor) \
                        (Can_FlexCan_DisableControllerInterrupts((Controller), (pCanControlerDescriptor)))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_EnableControllerInterrupts(Controller, pCanControlerDescriptor) \
                        (Can_FlexCan_EnableControllerInterrupts((Controller), (pCanControlerDescriptor)))

    #if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)   

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_Cancel(controller, mbindex)                                       (Can_FlexCan_Cancel((controller), (mbindex)))
    #endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */

    #if ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_AbortMb(Hth)                                                      (Can_FlexCan_AbortMb(Hth))
    #endif

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_Write(Hth, PduInfo)                                               (Can_FlexCan_Write((Hth), (PduInfo)))
       
    
    #if (CAN_TXPOLL_SUPPORTED == STD_ON)

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_MainFunctionWrite()                                               (Can_FlexCan_MainFunctionWrite())

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_MainFunctionMultipleWritePoll(writepoll)                          (Can_FlexCan_MainFunctionMultipleWritePoll(writepoll))
    #endif
    
    #if (CAN_RXPOLL_SUPPORTED == STD_ON)
/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_MainFunctionRead()                                                (Can_FlexCan_MainFunctionRead())

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_MainFunctionMultipleReadPoll(readpoll)                            (Can_FlexCan_MainFunctionMultipleReadPoll(readpoll))
    #endif

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_MainFunctionMode()                                                (Can_FlexCan_MainFunctionMode())

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_CheckWakeup(controller)                                           (Can_FlexCan_CheckWakeup(controller))

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_CheckBusOff(controller)                                           (Can_FlexCan_CheckBusOff(controller))
    
    #if (CAN_DUAL_CLOCK_MODE == STD_ON)

/* @violates @ref CAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_IPW_SetClockMode(u8Controller, can_clk_mode)                        (Can_FlexCan_SetClockMode((u8Controller), (can_clk_mode)))
    #endif


    

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (CAN_PRECOMPILE_SUPPORT == STD_OFF)
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref  CAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"


#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref  CAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"
#endif

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_START_SEC_CODE
/* @violates @ref  CAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"
#define CAN_STOP_SEC_CODE
/* @violates @ref  CAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*TEMPLATE_H*/

/** @} */
