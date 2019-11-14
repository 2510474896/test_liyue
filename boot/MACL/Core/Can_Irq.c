/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Can_Irq.c $
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
*   @file    Can_Irq.c
*   @implements Can_Irq.c_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Can - module interface
*   @details Interrupt routines for Can driver.
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
* @section Can_Irq_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Can_Irq_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Can_Irq_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Can_Irq_c_REF_4
* Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used
* This violation is due to the structure of the types used.
*
* @section Can_Irq_c_REF_5
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_Irq_c_REF_6
* Violates MISRA 2004 Required Rule 10.1 , The value of an expression of integer type shall not be implicitly
* converted to a different underlying type if: a) it is not a
* conversion to a wider integer type of the same signedness, or b)
* the expression is complex, or c) the expression is not constant
* and is a function argument, or d) the expression is not constant
* and is a return expression
*
* @section Can_Irq_c_REF_7
* Violates MISRA 2004 Required Rule 13.7 , Boolean operations whose results are invariant shall not be permitted
* This violation is due to the results of boolean operations are invariant.
*
* @section Can_Irq_c_REF_8
* Violates MISRA 2004 Required Rule 14.9 , An if (expression) shall be followed by a compound statement.
* The else keyword shall be followed by either a compound statement, or another if statement.
* This violation is due to the if (and else) (expression) were not followed by a compound statement.
*
* @section Can_Irq_c_REF_9
* Violates MISRA 2004 Advisory Rule 12.1, Use of mixed mode arithmetic
* This violation is due to the macro CAN_BIT_ASSIGN and no explicit cast operation used for the parameters passed
* to the macro. The care is taken for the parameters sent as inputs to the macro and hence unintended truncation of values
* would not result.
*
* @section Can_Irq_c_REF_10
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
*/

/*
(CAN035) The module Can_Irq.c contains the implementation of interrupt frames.The implementation of the interrupt service routine shall be in Can.c
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           Can_Irq.c
*/
#include "Can.h"
#include "Can_IPW.h"
#include "CanIf_Cbk.h"
#include "Mcal.h"
#if (CAN_WAKEUP_SUPPORT == STD_ON)
#include "EcuM_Cbk.h"
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */



/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* The integration of incompatible files shall be avoided. */
/* @violates @ref Can_Irq_c_REF_3 Violates MISRA 2004 Rule 1.4, Identifier clash */
#define CAN_VENDOR_ID_IRQ_C                      43
#define CAN_AR_RELEASE_MAJOR_VERSION_IRQ_C       4
#define CAN_AR_RELEASE_MINOR_VERSION_IRQ_C       0
/* @violates @ref Can_Irq_c_REF_3 Violates MISRA 2004 Rule 1.4, Identifier clash */
#define CAN_AR_RELEASE_REVISION_VERSION_IRQ_C    3
#define CAN_SW_MAJOR_VERSION_IRQ_C               1
#define CAN_SW_MINOR_VERSION_IRQ_C               0
#define CAN_SW_PATCH_VERSION_IRQ_C               0


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN header file are of the same vendor */
#if (CAN_VENDOR_ID_IRQ_C != CAN_VENDOR_ID)
    #error "Can_Irq.c and Can.h have different vendor ids"
#endif
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_AR_RELEASE_MINOR_VERSION_IRQ_C    != CAN_AR_RELEASE_MINOR_VERSION) || \
     (CAN_AR_RELEASE_REVISION_VERSION_IRQ_C != CAN_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Can_Irq.c and Can.h are different"
#endif
/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_IRQ_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_SW_MINOR_VERSION_IRQ_C != CAN_SW_MINOR_VERSION) || \
     (CAN_SW_PATCH_VERSION_IRQ_C != CAN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Can_Irq.c and Can.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
    #if ((CAN_AR_RELEASE_MAJOR_VERSION_IRQ_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_AR_RELEASE_MINOR_VERSION_IRQ_C != DET_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can_Irq.c and Det.h are different"
    #endif
#endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
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
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/*
   (CAN033) The Can module shall implement the interrupt service routines for all CAN Hardware Unit
   interrupts that are needed. The Can module shall disable all unused interrupts in the CAN controller.
   The Can module shall reset the interrupt flag at the end of the ISR (if not done automatically by
   hardware). The Can module shall not set the configuration (i.e. priority) of the vector table entry.
*/
/**
* @brief          CAN controller A interrupts
* @details        CAN controller A interrupts
*
*
*/
/* CAN controller A interrupts */
#ifdef CAN_FCA_INDEX
  #if (CAN_A_ERROR_NOTIFICATION_ENABLE == STD_ON)
    ISR(Can_IsrFCA_ERR);
  #endif
    #if (CAN_A_BUSOFFINT_SUPPORTED == STD_ON)
        ISR(Can_IsrFCA_BO);
    #endif /* (CAN_A_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_A_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            ISR(Can_IsrFCA_WKP);
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_A_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCA_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCA_FrameAv);
                    ISR(Can_IsrFCA_Overf);
                    ISR(Can_IsrFCA_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCA_MB_00_03);
                    ISR(Can_IsrFCA_MB_04_07);                      
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCA_MB_08_11);
                    ISR(Can_IsrFCA_MB_12_15);
                    ISR(Can_IsrFCA_MB_16_31);
                    ISR(Can_IsrFCA_MB_32_39);
                    ISR(Can_IsrFCA_MB_40_47);
                    ISR(Can_IsrFCA_MB_48_55);               
                    ISR(Can_IsrFCA_MB_56_63);

        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_OFF) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCA_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCA_FrameAv);
                    ISR(Can_IsrFCA_Overf);
                    ISR(Can_IsrFCA_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCA_MB_00_03);
                    ISR(Can_IsrFCA_MB_04_07);                      
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCA_MB_08_11);
                    ISR(Can_IsrFCA_MB_12_15);
                    ISR(Can_IsrFCA_MB_16_31);
                    ISR(Can_IsrFCA_MB_32_39);
                    ISR(Can_IsrFCA_MB_40_47);
                    ISR(Can_IsrFCA_MB_48_55);               
                    ISR(Can_IsrFCA_MB_56_63);
                   
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCA_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_OFF)
                   ISR(Can_IsrFCA_MB_00_03);
                   ISR(Can_IsrFCA_MB_04_07);                      
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
                   ISR(Can_IsrFCA_MB_08_11);
                   ISR(Can_IsrFCA_MB_12_15);
                   ISR(Can_IsrFCA_MB_16_31);
                    ISR(Can_IsrFCA_MB_32_39);
                    ISR(Can_IsrFCA_MB_40_47);
                    ISR(Can_IsrFCA_MB_48_55);               
                    ISR(Can_IsrFCA_MB_56_63);
                   
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */
    #endif /* ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF)) */
#endif /* CAN_FCA_INDEX */

/**
* @brief          CAN controller B interrupts
* @details        CAN controller B interrupts
*
*
*/
/* CAN controller B interrupts */
#ifdef CAN_FCB_INDEX
  #if (CAN_B_ERROR_NOTIFICATION_ENABLE == STD_ON)
    ISR(Can_IsrFCB_ERR);
  #endif
    #if (CAN_B_BUSOFFINT_SUPPORTED == STD_ON)
        ISR(Can_IsrFCB_BO);
    #endif /* (CAN_B_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_B_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            ISR(Can_IsrFCB_WKP);
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_B_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCB_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_B_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCB_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCB_FrameAv);
                    ISR(Can_IsrFCB_Overf);
                    ISR(Can_IsrFCB_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_B_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCB_MB_00_03);
                    ISR(Can_IsrFCB_MB_04_07);                      
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCB_MB_08_11);
                    ISR(Can_IsrFCB_MB_12_15);
                    ISR(Can_IsrFCB_MB_16_31);
                    ISR(Can_IsrFCB_MB_32_39);
                    ISR(Can_IsrFCB_MB_40_47);
                    ISR(Can_IsrFCB_MB_48_55);               
                    ISR(Can_IsrFCB_MB_56_63);
                    
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_B_TXINT_SUPPORTED == STD_OFF) && (CAN_B_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCB_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_B_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCB_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCB_FrameAv);
                    ISR(Can_IsrFCB_Overf);
                    ISR(Can_IsrFCB_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_B_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCB_MB_00_03);
                    ISR(Can_IsrFCB_MB_04_07);                      
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCB_MB_08_11);
                    ISR(Can_IsrFCB_MB_12_15);
                    ISR(Can_IsrFCB_MB_16_31);
                    ISR(Can_IsrFCB_MB_32_39);
                    ISR(Can_IsrFCB_MB_40_47);
                    ISR(Can_IsrFCB_MB_48_55);               
                    ISR(Can_IsrFCB_MB_56_63);
                       
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCB_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_B_FIFO_EN == STD_OFF)
                    ISR(Can_IsrFCB_MB_00_03);
                    ISR(Can_IsrFCB_MB_04_07);                      
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCB_MB_08_11);
                    ISR(Can_IsrFCB_MB_12_15);
                    ISR(Can_IsrFCB_MB_16_31);
                    ISR(Can_IsrFCB_MB_32_39);
                    ISR(Can_IsrFCB_MB_40_47);
                    ISR(Can_IsrFCB_MB_48_55);               
                    ISR(Can_IsrFCB_MB_56_63);
                     
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */
    #endif /* ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_OFF)) */
#endif /* CAN_FCB_INDEX */

/**
* @brief          CAN controller C interrupts
* @details        CAN controller C interrupts
**/
/* CAN controller C interrupts */
#ifdef CAN_FCC_INDEX
  #if (CAN_C_ERROR_NOTIFICATION_ENABLE == STD_ON)
    ISR(Can_IsrFCC_ERR);
  #endif
    #if (CAN_C_BUSOFFINT_SUPPORTED == STD_ON)
        ISR(Can_IsrFCC_BO);
    #endif /* (CAN_C_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_C_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            ISR(Can_IsrFCC_WKP);
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_C_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCC_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCC_FrameAv);
                    ISR(Can_IsrFCC_Overf);
                    ISR(Can_IsrFCC_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCC_MB_00_03);
                    ISR(Can_IsrFCC_MB_04_07);                      
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCC_MB_08_11);
                    ISR(Can_IsrFCC_MB_12_15);
                    ISR(Can_IsrFCC_MB_16_31);
                    ISR(Can_IsrFCC_MB_32_39);
                    ISR(Can_IsrFCC_MB_40_47);
                    ISR(Can_IsrFCC_MB_48_55);               
                    ISR(Can_IsrFCC_MB_56_63);
                       
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_OFF) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    ISR(Can_IsrFCC_RxFifoEvents);
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                    ISR(Can_IsrFCC_FrameAv);
                    ISR(Can_IsrFCC_Overf);
                    ISR(Can_IsrFCC_Warn);
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCC_MB_00_03);
                    ISR(Can_IsrFCC_MB_04_07);                      
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCC_MB_08_11);
                    ISR(Can_IsrFCC_MB_12_15);
                    ISR(Can_IsrFCC_MB_16_31);
                    ISR(Can_IsrFCC_MB_32_39);
                    ISR(Can_IsrFCC_MB_40_47);
                    ISR(Can_IsrFCC_MB_48_55);               
                    ISR(Can_IsrFCC_MB_56_63);
                       
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            ISR(Can_IsrFCC_UNI);
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_OFF)
                    ISR(Can_IsrFCC_MB_00_03);
                    ISR(Can_IsrFCC_MB_04_07);                      
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
                    ISR(Can_IsrFCC_MB_08_11);
                    ISR(Can_IsrFCC_MB_12_15);
                    ISR(Can_IsrFCC_MB_16_31);
                    ISR(Can_IsrFCC_MB_32_39);
                    ISR(Can_IsrFCC_MB_40_47);
                    ISR(Can_IsrFCC_MB_48_55);               
                    ISR(Can_IsrFCC_MB_56_63);
                       
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */
    #endif /* ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF)) */
#endif /* CAN_FCC_INDEX */


#define CAN_START_SEC_CODE
/* @violates @ref Can_Irq_c_REF_1 MISRA 2004 Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Irq_c_REF_2 MISRA 2004 Rule 19.15, Repeated include file MemMap.h  */
#include "MemMap.h"


/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR FLEXCAN A
==================================================================================================*/
#ifdef CAN_FCA_INDEX
  #if (CAN_A_ERROR_NOTIFICATION_ENABLE == STD_ON)
    /* Error */
    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
    CAN_ERRISR(A)
  #endif
    #if (CAN_A_BUSOFFINT_SUPPORTED == STD_ON)
        /* Bus Off */
        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
        CAN_BOISR(A)
    #endif /* (CAN_A_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_A_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* Internal Wake-Up */
            CAN_WKPISR(A)
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_A_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                    CAN_RXFIFO_EVENTS(A)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_FRAV(A)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXOVER(A)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXWARN(A)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_04_07, 4U, 7U)                
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_16_31,16U,31U)
                   /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_56_63,56U,63U)
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_OFF) && (CAN_A_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIRXISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_A_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    CAN_RXFIFO_EVENTS(A)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_FRAV(A)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_RXOVER(A)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_RXWARN(A)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_A_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(A, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(A, MB_04_07, 4U, 7U)                
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(A, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(A, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(A, MB_16_31,16U,31U)
                   /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_56_63,56U,63U) 
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNITXISRS(A)
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_A_FIFO_EN == STD_OFF)
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(A, MB_00_03, 0U, 3U)
                   
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(A, MB_04_07, 4U, 7U)                
            #endif /* (CAN_A_FIFO_EN == STD_OFF) */
            
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(A, MB_08_11, 8U,11U)
                   
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(A, MB_12_15,12U,15U)
                   
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(A, MB_16_31,16U,31U)
                   
                   /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(A, MB_56_63,56U,63U)                 
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_A_TXINT_SUPPORTED == STD_ON) && (CAN_A_RXINT_SUPPORTED == STD_ON)) */
#endif /* CAN_FCA_INDEX */


/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR FLEXCAN B
==================================================================================================*/
#ifdef CAN_FCB_INDEX
  #if (CAN_B_ERROR_NOTIFICATION_ENABLE == STD_ON)
    /* Error */
    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
    CAN_ERRISR(B)
  #endif
    #if (CAN_B_BUSOFFINT_SUPPORTED == STD_ON)
        /* Bus Off */
        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
        CAN_BOISR(B)
    #endif /* (CAN_B_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_B_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* Internal Wake-Up */
            CAN_WKPISR(B)
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_B_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIISRS(B)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_B_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    CAN_RXFIFO_EVENTS(B)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_FRAV(B)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_RXOVER(B)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        CAN_MB_RXWARN(B)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_B_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_04_07, 4U, 7U)                
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_16_31,16U,31U)
                   
                   /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_56_63,56U,63U)                  
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_B_TXINT_SUPPORTED == STD_OFF) && (CAN_B_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIRXISRS(B)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_B_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                    CAN_RXFIFO_EVENTS(B)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_FRAV(B)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXOVER(B)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXWARN(B)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_B_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(B, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(B, MB_04_07, 4U, 7U)                
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(B, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(B, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(B, MB_16_31,16U,31U)
                  /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_56_63,56U,63U)                    
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNITXISRS(B)
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_B_FIFO_EN == STD_OFF)
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(B, MB_00_03, 0U, 3U)
                   
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(B, MB_04_07, 4U, 7U)                
            #endif /* (CAN_B_FIFO_EN == STD_OFF) */
            
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(B, MB_08_11, 8U,11U)
                   
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(B, MB_12_15,12U,15U)
                   
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(B, MB_16_31,16U,31U)
                  /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(B, MB_56_63,56U,63U)                    
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_B_TXINT_SUPPORTED == STD_ON) && (CAN_B_RXINT_SUPPORTED == STD_ON)) */
#endif /* CAN_FCB_INDEX */


/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR FLEXCAN C
==================================================================================================*/
#ifdef CAN_FCC_INDEX
  #if (CAN_C_ERROR_NOTIFICATION_ENABLE == STD_ON)
    /* Error */
    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
    CAN_ERRISR(C)
  #endif
    #if (CAN_C_BUSOFFINT_SUPPORTED == STD_ON)
        /* Bus Off */
        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
        CAN_BOISR(C)
    #endif /* (CAN_C_BUSOFFINT_SUPPORTED == STD_ON) */

    #if (CAN_C_WAKEUPINT_SUPPORTED == STD_ON)
        #if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* Internal Wake-Up */
            CAN_WKPISR(C)
        #endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
    #endif /* (CAN_C_WAKEUPINT_SUPPORTED == STD_ON) */

    #if ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                    CAN_RXFIFO_EVENTS(C)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_FRAV(C)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXOVER(C)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXWARN(C)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_04_07, 4U, 7U)                
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_16_31,16U,31U)
                  /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_56_63,56U,63U)                           
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_OFF) && (CAN_C_RXINT_SUPPORTED == STD_ON))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNIRXISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_ON) */
            #if (CAN_C_FIFO_EN == STD_ON)
                #if (CAN_RXFIFO_EVENT_UNIFIED == STD_ON)
                    /* All events of Rx fifo */
                    /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                    /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                    /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                    CAN_RXFIFO_EVENTS(C)
                #else /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
                        /* Rx Fifo Frame Available Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_FRAV(C)
                        /* RX Fifo Overflow Interrupt*/
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXOVER(C)
                        /* Rx Fifo Warning Interrupt */
                        /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                        /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                        CAN_MB_RXWARN(C)
                #endif /* (CAN_RXFIFO_EVENT_UNIFIED == STD_OFF) */
            #else /* (CAN_C_FIFO_EN == STD_OFF) */
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(C, MB_00_03, 0U, 3U)
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(C, MB_04_07, 4U, 7U)                
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(C, MB_08_11, 8U,11U)
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(C, MB_12_15,12U,15U)
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_RXISRS(C, MB_16_31,16U,31U)
                  /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_56_63,56U,63U)                        
        #endif /* (CAN_ISROPTCODESIZE == STD_ON) */

    #elif ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_OFF))
        #if (CAN_ISROPTCODESIZE == STD_ON)
            /* All MBs */
            CAN_MB_UNITXISRS(C)
        #else /* (CAN_ISROPTCODESIZE == STD_OFF) */
            #if (CAN_C_FIFO_EN == STD_OFF)
                   /* Message Buffer 00_03 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(C, MB_00_03, 0U, 3U)
                   
                   /* Message Buffer 04_07 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(C, MB_04_07, 4U, 7U)                
            #endif /* (CAN_C_FIFO_EN == STD_OFF) */
            
                   /* Message Buffer 08_11 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(C, MB_08_11, 8U,11U)
                   
                   /* Message Buffer 12_15 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(C, MB_12_15,12U,15U)
                   
                   /* Message Buffer 16_31 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_TXISRS(C, MB_16_31,16U,31U)
                   
                  /* Message Buffer 32_39 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_32_39,32U,39U)
                   /* Message Buffer 40_47 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_40_47,40U,47U)
                   /* Message Buffer 48_55 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_48_55,48U,55U)
                   /* Message Buffer 56_63 */
                   /* @violates @ref Can_Irq_c_REF_5  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */    
                   /* @violates @ref Can_Irq_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                   /* @violates @ref Can_Irq_c_REF_6 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */    
                   /* @violates @ref Can_Irq_c_REF_7 Violates MISRA 2004 Required Rule 13.7 , the results of boolean operations are invariant. */
                   /* @violates @ref Can_Irq_c_REF_8 Violates MISRA 2004 Required Rule 14.9 , the if (and else) (expression) were not followed by a compound statement. */
                   /* @violates @ref Can_Irq_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
                   /* @violates @ref Can_Irq_c_REF_9 Violates MISRA 2004 Rule 12.1, due to the macro CAN_BIT_ASSIGN */
                   CAN_MB_ISRS(C, MB_56_63,56U,63U)                      
        #endif /* (CAN_ISROPTCODESIZE == STD_OFF) */
    #endif /* ((CAN_C_TXINT_SUPPORTED == STD_ON) && (CAN_C_RXINT_SUPPORTED == STD_ON)) */
#endif /* CAN_FCC_INDEX */




#define CAN_STOP_SEC_CODE
/* @violates @ref Can_Irq_c_REF_1 MISRA 2004 Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Irq_c_REF_2 MISRA 2004 Rule 19.15, Repeated include file MemMap.h  */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
