/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Can_FlexCan.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:23CST $

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
*   @file    Can_FlexCan.c
*   @implements FlexCAN.c_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Can - LLD module implementation.
*   @details Low Level Driver implementation.
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
* @section Can_Flexcan_c_REF_1
* Violates MISRA 2004 Advisory Rule 12.1, Use of mixed mode arithmetic
* This violation is due to the macro CAN_BIT_ASSIGN and no explicit cast operation used for the parameters passed
* to the macro. The care is taken for the parameters sent as inputs to the macro and hence unintended truncation of values
* would not result.
*
* @section Can_Flexcan_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Can_Flexcan_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_Flexcan_c_REF_5
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Can_Flexcan_c_REF_6
* Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable
* The code is not dynamically linked. An absolute stack address is obtained when taking the address of the near auto variable.
* A source of error in writing dynamic code is that the stack segment may be different from the data segment.
*
* @section Can_Flexcan_c_REF_7
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Can_Flexcan_c_REF_8
* Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used
* This violation is due to the structure of the types used.
*
* @section Can_Flexcan_c_REF_10
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
*
* @section Can_Flexcan_c_REF_11
* Violates MISRA 2004 Required Rule 10.1 , The value of an expression of integer type shall not be implicitly
* converted to a different underlying type if: a) it is not a
* conversion to a wider integer type of the same signedness, or b)
* the expression is complex, or c) the expression is not constant
* and is a function argument, or d) the expression is not constant
* and is a return expression
*
* @section Can_Flexcan_c_REF_12
* Violates MISRA 2004 Required Rule 10.3 , The value of a complex expression of integer type may only be cast
* to a type that is narrower and of the same signedness as the underlying type of the expression
* This violation is due to the value of a complex expression of integer type was cast to a type that is
* not narrower.
*
* @section Can_Flexcan_c_REF_13
* Violates MISRA 2004 Required Rule 10.5 , If the bitwise operators ~ and << are applied to an operand
* of underlying type unsigned char or unsigned shot, the result shall be immediately cast to the underlying type
* of the operand
* This violation is due to the operator << was used.
*
* @section Can_Flexcan_c_REF_14
* Violates MISRA 2004 Required Rule 12.4, The right hand operand of a logical && or || operator shall not
* contain side effects.
*
* @section Can_Flexcan_c_REF_15
* Violates MISRA 2004 Required Rule 14.3, Before preprocessing, a null statement shall only occur on a line
* by itself, it may be followed by a comment provided that the first character following the null statement
* is a white-space character.
*
* @section Can_Flexcan_c_REF_16
* Violates MISRA 2004 Required Rule 14.8, The statement forming the body of a switch, while, do...while or for
* statement shall be a compound statement.
*
* @section Can_Flexcan_c_REF_17
* Violates MISRA 2004 Required Rule 12.8, The right-hand operand of a shift operator shall lie between zero and
* one less than the wdith in bits of the underlying type of the left-hand operand
*
* @section Can_Flexcan_c_REF_18
* Violates MISRA 2004 Required Rule 13.7, Boolean operations whose results are invariant shall not be
* permitted
*
* @section Can_Flexcan_c_REF_19
* Violates MISRA 2004 Advisory Rule 11.4,  A cast should not be performed between a pointer to object type and a different pointer
* to object type.
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can.h"
#include "Can_IPW.h"
#include "CanIf_Cbk.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*
* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "Cer.h"
#include "SchM_Can.h"
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/**
* @file           Can_FlexCan.c
*/
#define CAN_FLEXCAN_VENDOR_ID_C                    43
#define CAN_FLEXCAN_MODULE_ID_C                    80
/*
* @violates @ref Can_Flexcan_c_REF_7 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
#define CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C     4
/*
* @violates @ref Can_Flexcan_c_REF_7 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
#define CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C     0
/*
* @violates @ref Can_Flexcan_c_REF_7 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
#define CAN_FLEXCAN_AR_RELEASE_REVISION_VERSION_C  3
#define CAN_FLEXCAN_SW_MAJOR_VERSION_C             1
#define CAN_FLEXCAN_SW_MINOR_VERSION_C             0
#define CAN_FLEXCAN_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and CAN header file are of the same vendor */
#if (CAN_FLEXCAN_VENDOR_ID_C != CAN_FLEXCAN_VENDOR_ID_H)
    #error "Can_FlexCan.c and Can_FlexCan.h have different vendor ids"
#endif
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C    != CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_FLEXCAN_AR_RELEASE_REVISION_VERSION_C != CAN_FLEXCAN_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of Can_FlexCan.c and Can_FlexCan.h are different"
#endif
/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_FLEXCAN_SW_MAJOR_VERSION_C != CAN_FLEXCAN_SW_MAJOR_VERSION_H) || \
     (CAN_FLEXCAN_SW_MINOR_VERSION_C != CAN_FLEXCAN_SW_MINOR_VERSION_H) || \
     (CAN_FLEXCAN_SW_PATCH_VERSION_C != CAN_FLEXCAN_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Can_FlexCan.c and Can_FlexCan.h are different"
#endif


/* Check if current file and CAN_IPW header file are of the same vendor */
#if (CAN_FLEXCAN_VENDOR_ID_C != CAN_IPW_VENDOR_ID_H)
    #error "Can.c and Can_IPW.h have different vendor ids"
#endif
/* Check if current file and CAN_IPW header file are of the same Autosar version */
#if ((CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C    != CAN_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_FLEXCAN_AR_RELEASE_REVISION_VERSION_C != CAN_IPW_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of Can.c and Can_IPW.h are different"
#endif
/* Check if current file and CAN_IPW header file are of the same Software version */
#if ((CAN_FLEXCAN_SW_MAJOR_VERSION_C != CAN_IPW_SW_MAJOR_VERSION_H) || \
     (CAN_FLEXCAN_SW_MINOR_VERSION_C != CAN_IPW_SW_MINOR_VERSION_H) || \
     (CAN_FLEXCAN_SW_PATCH_VERSION_C != CAN_IPW_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Can.c and Can_IPW.h are different"
#endif


#if (CAN_WAKEUP_SUPPORT == STD_ON)
/* Check if current file and ECUM_CBK header file are of the same Software version */
    #if ((CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C != ECUM_CBK_AR_RELEASE_MAJOR_VERSION) || \
        (CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C != ECUM_CBK_AR_MINOR_RELEASE_VERSION) || \
        #error "Software Version Numbers of Can.c and EcuM_Cbk.h are different"
    #endif
#endif


/* Check if current file and CANIF_CBK header file are of the same version */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C != CANIF_CBK_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C != CANIF_CBK_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can.c and CanIf_Cbk.h are different"
    #endif
  #endif
#endif



/* Check if current file and DET header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    #if ((CAN_FLEXCAN_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_FLEXCAN_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can_FlexCan.c and Det.h are different"
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

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"
/**
* @brief          Array holding current status/run-time configuration of individual FlexCAN controllers
* @details        Array holding current status/run-time configuration of individual FlexCAN controllers
*                 - information like Guard bits, Pre-calculated MB INT masks, Storage space for id, INT nesting level,
*                 Index of MB buffer being cancelled, Index of the first MB used for Tx , Controller Options.
*
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
VAR(Can_ControllerStatusType, CAN_VAR) Can_ControllerStatuses[CAN_MAXCTRL_CONFIGURED];

/**
* @brief          Array holding current MCR Register status
* @details        Array holding current MCR Register status. If the Can_SetControllerMode returns with CAN_NOT_OK,
*                 then the MCR Register is saved and the Can_MainFunction_Mode must be called to see a state change
*                 of the controller
*
*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
STATIC VAR(uint32, CAN_VAR) Can_u32McrConfiguration[CAN_MAXCTRL_SUPPORTED];
#endif


#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"


#define CAN_START_SEC_CONST_UNSPECIFIED
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"

/**
* @brief          CAN base address array
* @details        CAN base address array
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
CONST(uint32, CAN_CONST) Can_u32BaseAddress[] = {
#ifdef  FLEXCAN0_BASEADDR
        FLEXCAN0_BASEADDR,
#endif /* FLEXCAN0_BASEADDR */
#ifdef  FLEXCAN1_BASEADDR
        FLEXCAN1_BASEADDR,
#endif /* FLEXCAN1_BASEADDR */
#ifdef  FLEXCAN2_BASEADDR
        FLEXCAN2_BASEADDR,
#endif /* FLEXCAN2_BASEADDR */
#ifdef  FLEXCAN3_BASEADDR
        FLEXCAN3_BASEADDR,
#endif /* FLEXCAN3_BASEADDR */
#ifdef  FLEXCAN4_BASEADDR
        FLEXCAN4_BASEADDR,
#endif /* FLEXCAN4_BASEADDR */
#ifdef  FLEXCAN5_BASEADDR
        FLEXCAN5_BASEADDR,
#endif /* FLEXCAN5_BASEADDR */
#ifdef  FLEXCAN6_BASEADDR
        FLEXCAN6_BASEADDR,
#endif /* FLEXCAN6_BASEADDR */
#ifdef  FLEXCAN7_BASEADDR
        FLEXCAN7_BASEADDR
#endif /* FLEXCAN7_BASEADDR */
    };
    
    
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */  

CONST(Can_MaskFlag, CAN_CONST) Can_IflagImask[(uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8)][FLEXCAN_CONTROLLERS_NO] =
        {
                
                   {
                       #ifdef  FLEXCAN0_BASEADDR
                       {
                       (FLEXCAN0_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN0_BASEADDR + 0x28U )               
                       }
                       #endif
                       #ifdef  FLEXCAN1_BASEADDR
                       ,{
                       (FLEXCAN1_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN1_BASEADDR + 0x28U)
                       }
                       #endif
                       #ifdef  FLEXCAN2_BASEADDR
                       ,{
                       (FLEXCAN2_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN2_BASEADDR + 0x28U)
                       }
                       #endif
                       #ifdef  FLEXCAN3_BASEADDR
                       ,{
                       (FLEXCAN3_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN3_BASEADDR + 0x28U)
                       }
                       #endif
                       #ifdef  FLEXCAN4_BASEADDR
                       ,{
                       (FLEXCAN4_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN4_BASEADDR + 0x28U)
                       }
                       #endif 
                       #ifdef  FLEXCAN5_BASEADDR
                       ,{
                       (FLEXCAN5_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN5_BASEADDR + 0x28U)
                       }
                       #endif
                       #ifdef  FLEXCAN6_BASEADDR
                       ,{
                       (FLEXCAN6_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN6_BASEADDR + 0x28U )
                       }
                       #endif
                       #ifdef  FLEXCAN7_BASEADDR
                       ,{
                       (FLEXCAN7_BASEADDR + 0x30U)
                       ,
                       (FLEXCAN7_BASEADDR + 0x28U)
                       }
                       #endif
                   },
            #if ((CAN_MAXMB_SUPPORTED == FLEXCAN_MB_64_U8) || (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_96_U8 )) 
                   {
                       #ifdef  FLEXCAN0_BASEADDR
                       {
                       (FLEXCAN0_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN0_BASEADDR + 0x24U )
                       }
                       #endif
                       #ifdef  FLEXCAN1_BASEADDR
                       ,{
                       (FLEXCAN1_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN1_BASEADDR + 0x24U )
                       }
                       #endif
                       #ifdef  FLEXCAN2_BASEADDR
                       ,{
                       (FLEXCAN2_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN2_BASEADDR + 0x24U ) 
                       }
                       #endif
                       #ifdef  FLEXCAN3_BASEADDR
                       ,{
                       (FLEXCAN3_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN3_BASEADDR + 0x24U )
                       }
                       #endif
                       #ifdef  FLEXCAN4_BASEADDR
                       ,{
                       (FLEXCAN4_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN4_BASEADDR + 0x24U ) 
                       }
                       #endif
                       #ifdef  FLEXCAN5_BASEADDR
                       ,{
                       (FLEXCAN5_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN5_BASEADDR + 0x24U ) 
                       }
                       #endif
                       #ifdef  FLEXCAN6_BASEADDR
                       ,{
                       (FLEXCAN6_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN6_BASEADDR + 0x24U ) 
                       }
                       #endif
                       #ifdef  FLEXCAN7_BASEADDR
                       ,{
                       (FLEXCAN7_BASEADDR + 0x2CU )
                       ,
                       (FLEXCAN7_BASEADDR + 0x24U ) 
                       }
                       #endif
                   },
            #endif        
            #if  (CAN_MAXMB_SUPPORTED == FLEXCAN_MB_96_U8 )
                  {
                    #ifdef  FLEXCAN0_BASEADDR
                      {
                       (FLEXCAN0_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN0_BASEADDR + 0x6CU ) 
                      }
                       #endif
                       #ifdef  FLEXCAN1_BASEADDR
                       ,{
                       (FLEXCAN1_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN1_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN2_BASEADDR
                       ,{
                       (FLEXCAN2_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN2_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN3_BASEADDR
                       ,{
                       (FLEXCAN3_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN3_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN4_BASEADDR
                       ,{
                       (FLEXCAN4_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN4_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN5_BASEADDR
                       ,{
                       (FLEXCAN5_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN5_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN6_BASEADDR
                       ,{
                       (FLEXCAN6_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN6_BASEADDR + 0x6CU )
                       }
                       #endif
                       #ifdef  FLEXCAN7_BASEADDR
                       ,{
                       
                       (FLEXCAN7_BASEADDR + 0x74U )
                       ,
                       (FLEXCAN7_BASEADDR + 0x6CU )
                       }
                       #endif                       
                  }
            #endif    
    };
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"


#define CAN_START_SEC_CODE
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"


        


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
extern FUNC(boolean, COM_APPL_CODE) CanLPduReceiveCalloutFunction(uint8 Hrh,Can_IdType CanId,uint8 CanDlc,const uint8 *CanSduPtr);
/**
* @brief          Initialisation of indicator, statuses, etc.
* @details        Initialisation of indicator, statuses, etc.
*                 This routine is called by:
*                 - Can_Init() from Can.c file.
*
* @pre            At least one controller must be configured in the Driver structure.
* @post           Set variables into a definite state.
*
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_InitVariables( void )
    {

        /* Index CAN controllers from configuration. */
        VAR(uint8, AUTOMATIC) u8CtrlIndex = 0U;
        VAR(uint8, AUTOMATIC) u8MbIndex = 0U;

        /* Init all global varibales/statuses for all controllers. */
        for ( u8CtrlIndex = 0U; u8CtrlIndex < (uint8)Can_pCurrentConfig->u8ControllersConfigured; u8CtrlIndex++)
        {
            /* Init INT Disable nesting indicator. It is incremented after every call of Can_DisableControllerInterrupts().
               The function Can_EnableControllerInterrupts() shall perform no action when Can_DisableControllerInterrupts() has not been called before. */
            Can_ControllerStatuses[u8CtrlIndex].s8IntDisableLevel = (sint8)0;

            /* Set interrupt mode status to interrupt disabled mode. */
            Can_ControllerStatuses[u8CtrlIndex].u8ControllerSWFlag = (uint8)0U;

            /* Set to null the first Tx MB index for every controller. */
            Can_ControllerStatuses[u8CtrlIndex].u8FirstTxMBIndex = (uint8)0U;

            /* Set  interrupt mode status to interrupt disabled mode. */
            Can_ControllerStatuses[u8CtrlIndex].u8InterruptMode = (uint8)CAN_INTERRUPT_ENABLED;

            /* Set the controller state to STOP after power-up */
            Can_ControllerStatuses[u8CtrlIndex].ControllerState = CAN_STOPPED;

            /* Set the controller current baudrate index as default */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
            Can_ControllerStatuses[u8CtrlIndex].u8CurrentBaudRateIndex = (uint8)(Can_pControlerDescriptors[u8CtrlIndex].u8DefaultBaudRateIndex);

            for (u8MbIndex = 0U; u8MbIndex < (uint8)CAN_MAXMB_CONFIGURED; u8MbIndex++)
            {
            /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                Can_ControllerStatuses[u8CtrlIndex].u16MBMapping[u8MbIndex] = (uint32)0U;
           }

        }
    }


/*================================================================================================*/
/**
* @brief          Service for initializing the Can driver module according to a configuration set referenced by Config.
* @details        Driver Module Initialization - LLD Driver Module Initialization
*                 This routine is called by:
*                  - Can_Init() from Can.c file.
*
* @param[in]      Controller Can controller to be initialized
*
* @pre            At least one controller must be configured in the Driver structure.
* @post           Controller is enabled and set into Stop mode.
*
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_Init( VAR(uint8, AUTOMATIC) Controller )
    {
#if (CAN_MEMORY_ECC_SUPPORT == STD_ON)     
        VAR(uint32, AUTOMATIC)  i=0U;
#endif       
        VAR(uint8, AUTOMATIC)  u8HwOffset = 0U;/* Hardware Can controller offset. */

        VAR(uint32, AUTOMATIC)         u32TimeoutCount = 0U;/* Timeout counter. */

         /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used  */
        /* Get the hardware offset for this controller. */
        u8HwOffset = Can_pControlerDescriptors[Controller].u8ControllerOffset;  

        /* Enter Freeze mode after enabling, Self-Reception disabled, individual MB filter masks set. */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
   
        REG_WRITE32( FLEXCAN_MCR(u8HwOffset), (uint32)(FLEXCAN_RESERVED_MASK((uint32)(FLEXCAN_MCR_MDIS_U32_U32 | FLEXCAN_MCR_FRZ_U32 | FLEXCAN_MCR_HALT_U32 | FLEXCAN_MCR_SRXDIS_U32), FLEXCAN_MCR_NULL_MASK_U32, FLEXCAN_MCR_RESERVED_MASK_U32 )));


        /* load local time-out variable with configured time-out value*/
        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
        
        /* Wait until enter to low power mode */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        while ( (FLEXCAN_MCR_LPMACK_U32 != ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_LPMACK_U32)) &&
                (u32TimeoutCount > (uint32)0x0U) )
        {
            u32TimeoutCount--;
        }


        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_MDIS_U32_U32);
           
        
        /* load local time-out variable with configured time-out value*/
        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
        
        /* Wait until exit from low power mode */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        while ( (FLEXCAN_MCR_LPMACK_U32 == ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_LPMACK_U32)) &&
                (u32TimeoutCount > (uint32)0x0U) )
        {

            u32TimeoutCount--;
        }        

        /*
           (CAN259) The function Can_Init shall set all CAN controllers in the state CANIF_CS_STOPPED.
           (CAN260) The function Can_ChangeBaudrate shall maintain the CAN controller in the state CANIF_CS_STOPPED.
                 The function Can_ChangeBaudrate shall ensure that any settings that will cause the CAN controller to participate in the network are not set.
        */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */      
        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_FRZ_U32);        
        
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_HALT_U32);
                

        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        while ( (FLEXCAN_MCR_FRZACK_U32 != ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_FRZACK_U32)) &&
                (u32TimeoutCount > (uint32)0x0U) )
        {
            u32TimeoutCount--;
        }
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SRXDIS_U32);
        
#if (CAN_MEMORY_ECC_SUPPORT == STD_ON) 
        /* Enable access to internal RAM if the Flexcan hardware module */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        REG_BIT_SET32( FLEXCAN_CTRL2(u8HwOffset), FLEXCAN_CTRL2_WRMFRZ_U32);

        /*Initialize all the internal RAM memory of the Flexcan hardware module. Also the parity bits will be reset*/
        i=FLEXCAN_MEMORY_START_U32;
        while(i<=FLEXCAN_MEMORY_END_U32)
        {
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_WRITE32((CAN_GET_BASE_ADDRESS(u8HwOffset)+i), 0x00U);
            i=i+4U;
        }
        
        /* Clear the error status flags generated before RAM initialization by the error correction and detection feature
        included in the Flexcan module. */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        REG_WRITE32( FLEXCAN_ERRSR(u8HwOffset), (uint32)(REG_READ32( FLEXCAN_ERRSR(u8HwOffset))& FLEXCAN_ERRSR_CONFIG_MASK_U32));
 
#endif /*CAN_MEMORY_ECC_SUPPORT*/        
        

}


/*================================================================================================*/
/**
* @brief          Service for reset the controller.
* @details        Re-initialization must start with a reset (soft).
*                 This routine is called by:
*                  - Can_FlexCan_ChangeBaudrate() from Can_FlexCan.c file.
*
* @param[in]      Controller CAN controller for which the init shall be done (CAN_FCA_INDEX / CAN_FCB_INDEX).
*                 This ID depends by the order of the controller's definition in the Tresos 'CanController' list.
*                 If CanController_0 is assigned to CANB then CAN_FCB_INDEX is 0.
*                 These indexes are used for access inside 'Can_ControlerDescriptorType' structure.
*
* @post           Controller is enabled and reset.
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (Can_ReturnType, CAN_CODE) Can_FlexCan_ResetController( VAR(uint8, AUTOMATIC) Controller)
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, AUTOMATIC) eReturnValue = CAN_OK;
        /* Timeout counter. */
        VAR(uint32, AUTOMATIC)         u32TimeoutCount = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)          u8HwOffset = 0U;


        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset =  Can_pControlerDescriptors[Controller].u8ControllerOffset;


        /* The re-initialization of controller start with a Soft-Reset. Test if Can is not ready -> can be in any of disable, Doze/Stop/Freeze modes. */
        
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        if ( FLEXCAN_MCR_LPMACK_U32 == ((uint32)(REG_READ32( FLEXCAN_MCR(u8HwOffset))) & FLEXCAN_MCR_LPMACK_U32) )
        {
            /* Enable Can module. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_MDIS_U32_U32);
          

            
            /* load local time-out variable with configured time-out value*/
            u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
            
            /* Wait until exit from low power mode */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            while ( (FLEXCAN_MCR_LPMACK_U32 == ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_LPMACK_U32)) &&
                    (u32TimeoutCount > (uint32)0x0U) )
            {
                /* MCR[LPM_ACK] still not set -> controller disable is in-progress. */
                u32TimeoutCount--;
            }              
        }


        /* Test for Hardware failure. */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        if ( FLEXCAN_MCR_LPMACK_U32 != ((uint32)(REG_READ32( FLEXCAN_MCR(u8HwOffset))) & FLEXCAN_MCR_LPMACK_U32) )
        {
            /* Execute Controller Reset. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SOFTRST_U32);
            

            /* Wait the Reset end off. */
            u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            while ( (FLEXCAN_MCR_SOFTRST_U32 == ((uint32)(REG_READ32( FLEXCAN_MCR(u8HwOffset))) & FLEXCAN_MCR_SOFTRST_U32)) &&
                    (u32TimeoutCount > (uint32)0x0U) )
            {
                /* MCR[SOFT_RST] still set -> reset in progress. */
                u32TimeoutCount--;
            }

            if ( (uint32)0x0U == u32TimeoutCount )
            {
                eReturnValue = CAN_NOT_OK;
            }
        }
        else
        /* software timeout */
        {
            eReturnValue = CAN_NOT_OK;
        }

        return (eReturnValue);
    }


/*================================================================================================*/
/**
* @brief          Service for (re)initializing only CAN controller specific settings.
* @details        CAN controller (re-)initialization.
*                 This routine is called by:
*                  - Can_Init() from Can.c file.
*                  - Can_ChangeBaudrate() from Can.c file.
*
* @param[in]      Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @pre            At least one controller must be configured in the Driver structure.
* @post           Set the MBs and interrupts into predefinite state for Can bus communication.
*
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_ChangeBaudrate( VAR(uint8, AUTOMATIC) Controller)
    {

        /* Local copy of pointer to the controller descriptor. */
        VAR(Can_PtrControlerDescriptorType, AUTOMATIC) pCanControlerDescriptor = NULL_PTR;
        /* Pointer to the MB container structure. */
        VAR(Can_PtrMBConfigContainerType, AUTOMATIC)   pCanMbConfigContainer = NULL_PTR;
        /* Variable for indexing all the MBs fron hardware unit chain (all controllers). */
        VAR(uint16, AUTOMATIC)            u16MbGlobalIndex = 0U;
        /* Variable for indexing the MBs inside a single controller. */
        VAR(uint8, AUTOMATIC)             u8MbCtrlIndex = 0U;
        /* ID of current MB. */
        VAR(uint32, AUTOMATIC)            u32MbMessageId = 0U;
#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
        /* Variable for calculating the interrupt masks of IMASK1 & IMASK2 register s*/
        VAR(uint8, AUTOMATIC) u8RxglobalMskUpdate = 0U;
        VAR(uint8, AUTOMATIC) u8Temp14 = 0U;
        VAR(uint8, AUTOMATIC) u8Temp15 = 0U;
#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
#if (CAN_RXFIFO_ENABLE == STD_ON)
        /* Used to access configured table id and filtermask. */
        VAR(uint8, AUTOMATIC)             u8TempIndex = 0U;
        /* Used to save the the index pointing to the table id connfiguration. */
        VAR(uint8, AUTOMATIC)             u8RxFifoTableIdIndex = 0U;
        /* Used to index the Table ID for RxFifo. */
        VAR(uint8, AUTOMATIC)             u8RxFifoTableId = 0U;
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)             u8HwOffset = 0U;
        /* Max number of mb */
        VAR(uint8, AUTOMATIC)             u8MbMax = 0U;
        /* Temporary register value. */
        VAR(uint32, AUTOMATIC)            u32MbConfig = 0U;
        VAR(Can_ReturnType, AUTOMATIC)    eResetReturn = CAN_OK;/* Variable for return status. */
        VAR(uint8, AUTOMATIC) u8BaudrateIndex = 0U;/* Variable to hold the index of the current baudrate */
        
#if (CAN_RXFIFO_ENABLE == STD_ON)
        /*to skip first MB configured if FIFO enabled for configured controller*/
        VAR(uint8, AUTOMATIC)             u8MbSkip = 1U;
#endif
        VAR(uint8, AUTOMATIC)             u8RegCount = 0U;
     
        VAR(uint32, AUTOMATIC)         u32TimeoutCount = 0U;/* Timeout counter. */

        /* Fill the local pointer copy with address of the Controller Descriptor.  */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        pCanControlerDescriptor = &(Can_pCurrentConfig->ControlerDescriptors[Controller]);
        pCanMbConfigContainer   = &(Can_pCurrentConfig->MBConfigContainer);


        /* Get the hardware offset for this controller. */
        u8HwOffset = pCanControlerDescriptor->u8ControllerOffset;

        /* Reset Controller. */
        eResetReturn = Can_FlexCan_ResetController( Controller);

        /* Get the index of the current baudrate */
        u8BaudrateIndex = Can_ControllerStatuses[Controller].u8CurrentBaudRateIndex;

        if (eResetReturn == CAN_OK)
        {
             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_MDIS_U32_U32); 
           
            
            /* Load local time-out variable with configured time-out value*/
            u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
            /* After controller disable, wait until low power mode acknowledgement bit to set*/
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            while ( (FLEXCAN_MCR_LPMACK_U32 != ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_LPMACK_U32)) &&
                    (u32TimeoutCount > (uint32)0x0U) )
            {
                /* MCR[LPM_ACK] still not set -> controller disable is in-progress. */
                u32TimeoutCount--;
            }          
            
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        
            REG_WRITE32( FLEXCAN_CTRL(u8HwOffset), (uint32)(((uint32)(pCanControlerDescriptor->pControllerBaudrateConfigsPtr[u8BaudrateIndex].u32ControlRegister & FLEXCAN_CTRL_CLKSRC_U32)) & FLEXCAN_CTRL_CONFIG_MASK_U32));
          
            /* Enable access to module - clearing MCR[MDIS] bit. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_MDIS_U32_U32);
            
            u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
            /*Wait until exit from low power mode*/
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            while ( (FLEXCAN_MCR_LPMACK_U32 == ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_LPMACK_U32)) &&
                (u32TimeoutCount > (uint32)0x0U) )
            {
               
                u32TimeoutCount--;
            }  
            
            /* Enter in freeze mode  */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_FRZ_U32);
    
            
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_HALT_U32);
                           

            
            u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            while ( (FLEXCAN_MCR_FRZACK_U32 != ((uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_FRZACK_U32)) &&
                    (u32TimeoutCount > (uint32)0x0U) )
            {
                u32TimeoutCount--;
            }
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SRXDIS_U32);
            
            
            Can_ControllerStatuses[Controller].ControllerState = CAN_STOPPED;
            /* Reset software Flags. */
            Can_ControllerStatuses[Controller].u8ControllerSWFlag = (uint8)0x0U;
            
/*
* @ errata ERR_IPV_FLEXCAN_0008 software errata FlexCAN: Non-Correctable Errors In FlexCAN Access 
*        Put Device In Freeze Mode bit not working properly
*/            
#if defined(ERR_IPV_FLEXCAN_0008)
   #if (ERR_IPV_FLEXCAN_0008 == STD_ON) 
              /* Enable that the MECR register is updated */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_SET32( FLEXCAN_CTRL2(u8HwOffset), FLEXCAN_CTRL2_ECRWRE_U32);
              /* Enables writes on MECR register */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_CLEAR32( FLEXCAN_MECR(u8HwOffset), FLEXCAN_MECR_ECRWRDIS_U32);
              /* Keep normal operation */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_CLEAR32( FLEXCAN_MECR(u8HwOffset), FLEXCAN_MECR_NCEFAFRZ_U32);
            
              /* Disable Host Access With Non-Correctable Errors Interrupt Mask */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_CLEAR32( FLEXCAN_MECR(u8HwOffset), FLEXCAN_MECR_HANCEI_U32);
                           
              /* DisableFlexCAN Access With Non-Correctable Errors Interrupt Mask */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_CLEAR32( FLEXCAN_MECR(u8HwOffset), FLEXCAN_MECR_FANCEI_U32);
              
              /* Clear all interrupts statusflags generated by memory ECC */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_WRITE32( FLEXCAN_ERRSR(u8HwOffset), (uint32)((REG_READ32( FLEXCAN_ERRSR(u8HwOffset)))& FLEXCAN_ERRSR_CONFIG_MASK_U32));
              /* Disables writes on MECR register */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_SET32( FLEXCAN_MECR(u8HwOffset), FLEXCAN_MECR_ECRWRDIS_U32);
              /* Disable update on MECR register */
              /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
              REG_BIT_CLEAR32( FLEXCAN_CTRL2(u8HwOffset), FLEXCAN_CTRL2_ECRWRE_U32);
     #else
    #error : the define ERR_IPV_FLEXCAN_0008 must not be STD_OFF
   #endif
#endif /* ERR_IPV_FLEXCAN_0008 */ 

#if defined(CAN_USE_MCR_ABORT_ENABLE)
    #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
            /* If RFIFO is enabled then the first MBs will be used by the FIFO, initialize the
            u32CancelMBIndex to the value of Max. MB supported to avoid the false TX-MB cancellation */
            if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_RXFIFO_U32))
            {
                Can_ControllerStatuses[Controller].u32CancelMBIndex = CAN_MAXMB_SUPPORTED;
            }
            else /* RxFIFO is disabled */
            {
                /* Init the Cancelled MB index with a precalculated value - out of range for every controller. */
                Can_ControllerStatuses[Controller].u32CancelMBIndex = pCanMbConfigContainer->uMessageBufferConfigCount;
            }
    #else
        #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
    #endif
#else
            /* Init the Cancelled MB index with a precalculated value - out of range for every controller. */
            Can_ControllerStatuses[Controller].u32CancelMBIndex = pCanMbConfigContainer->uMessageBufferConfigCount;
#endif

            /* Clear Tx guard flags. */  
            for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8) ;u8RegCount++)
            {
                Can_ControllerStatuses[Controller].u32TxGuard[u8RegCount] = (uint32)0x0UL;
            }

#if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
            /* Check if BCC support is enabled in configuration */
            if ( CAN_CONTROLLERCONFIG_BCC_EN_U32 != (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_BCC_EN_U32) )
            {
                /* Enable individual MB filter masking. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_BCC_U32);
            }
#else /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                /* Enable individual MB filter masking. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_BCC_U32);

#endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* FlexCan uses the filtered RX input to detect recessive to dominant edges on the bus. */
            if ( CAN_CONTROLLERCONFIG_WAKEUP_SRC_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WAKEUP_SRC_U32) )
            {
                               REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_SRC_U32);
            }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* FlexCan uses local priority feature - extend the ID during the arbitration process with PRIO field from MB reg. */
            if ( CAN_CONTROLLERCONFIG_LPRIO_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_LPRIO_EN_U32) )
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_LPRIOEN_U32);
                
            }

            /* If WRN_EN is set the TWRN_INT and RWRN_INT will be set error counter transition from <96 to >= 96. */
            if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WRNEN_U32);
               
            }

            /* Set-up Control Register (CTRL - Controller Configuration) - pControllerBaudrateConfigsPtr->u32ControlRegister is configured by user using Tresos tool. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            
            REG_WRITE32( FLEXCAN_CTRL(u8HwOffset), (uint32)(((uint32)(pCanControlerDescriptor->pControllerBaudrateConfigsPtr[u8BaudrateIndex].u32ControlRegister)) & FLEXCAN_CTRL_CONFIG_MASK_U32));

            /* Loop Back Mode configuration. Clear also the MCR[SRCXDIS] to allow receiving frames transmitted by itself. */
             /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
            if ( FLEXCAN_CTRL_LPB_U32 == ((pCanControlerDescriptor->pControllerBaudrateConfigsPtr[u8BaudrateIndex].u32ControlRegister) & FLEXCAN_CTRL_LPB_U32) )
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SRXDIS_U32);
                
            }


            /* Stage1: init RxFifo ******************************************************************** */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /* If RX FIFO is used, then configure the Controller's registers for Rx Fifo. */
            if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_RXFIFO_U32) )
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_FEN_U32) ;
           
                
                /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_RMW32( FLEXCAN_CTRL2(u8HwOffset),(FLEXCAN_CTRL2_RFFN_U32) ,((uint32)(((uint32)((uint32)((Can_pCurrentConfig->ControlerDescriptors[Controller].u8RxFiFoUsedMb-8U)/2U)))<<24))); 
               
                
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_WRITE32(FLEXCAN_RXFGMASK(u8HwOffset), (((uint32)(Can_pCurrentConfig->ControlerDescriptors[Controller].u32RxFifoGlobalMask)) & FLEXCAN_RXFGMASK_CONFIG_MASK_U32));
                
                 
                /* Processing MB must start after the last MB used by the Rx Fifo filters */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                u8MbCtrlIndex += (Can_pCurrentConfig->ControlerDescriptors[Controller].u8RxFiFoUsedMb-1U);

                u8MbSkip = 0U;


                switch (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_IDAM_MASK_U32)
                {
                    case CAN_CONTROLLERCONFIG_IDAM_A_U32:
                        /* One full ID per filter element - clear IDAM bits. */
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_RMW32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_IDAM_U32, ((uint32)(FLEXCAN_MCR_IDAM32_U32))) ;
                        break;

                    case CAN_CONTROLLERCONFIG_IDAM_B_U32:
                        /* Two full standard IDs or two partial 14-bit exteneded IDs per filter element. */
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                         REG_RMW32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_IDAM_U32, ((uint32)(FLEXCAN_MCR_IDAM16_U32))) ;
                         break;

                    case CAN_CONTROLLERCONFIG_IDAM_C_U32:
                        /* Four partial 8-bit IDs (standard or extended) per filter element. */
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_RMW32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_IDAM_U32, ((uint32)(FLEXCAN_MCR_IDAM08_U32))) ;
                        break;

                    case CAN_CONTROLLERCONFIG_IDAM_D_U32:
                        /* RX Fifo is enabled, but all frames will be rejected. */
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_RMW32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_IDAM_U32, ((uint32)(FLEXCAN_MCR_IDAM_U32))) ;
                        break;

                    default:
                        /* This case should never occurs. */
                        Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_CHANGE_BAUDRATE, (uint8)CAN_E_DEFAULT);
                        /* Compiler_Warning: This warning is thrown due to the infinite loop while(1) in the
                                              Cer_ReportError() function implementation */
                } /* end switch. */

                /*Initialize the index used to acces the fifo Rx fifo filter list for all controllers*/
                u8RxFifoTableIdIndex = 0U;
                /* Calculate the index pointing to table id configuration. */    
                  
                for(u8TempIndex = 0U; u8TempIndex < Controller; u8TempIndex++)
                {            
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */                    
                    if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == (Can_pCurrentConfig->ControlerDescriptors[u8TempIndex].u32Options & CAN_CONTROLLERCONFIG_RXFIFO_U32) )
                    {
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        u8RxFifoTableIdIndex = u8RxFifoTableIdIndex + (4U*(Can_pCurrentConfig->ControlerDescriptors[u8TempIndex].u8RxFiFoUsedMb-6U));                        
                    }                            
                }               


                /* Init the IDTable and RXIMR registers of RxFifo. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                for ( u8TempIndex = u8RxFifoTableIdIndex; u8TempIndex < (u8RxFifoTableIdIndex + (4U*(Can_pCurrentConfig->ControlerDescriptors[Controller].u8RxFiFoUsedMb-6U))); u8TempIndex++)
                {
                    /* Calculate the physical address for each table to write the Table ID and FilterMask. */
                    REG_WRITE32( FLEXCAN_RXFIFO_ID((u8HwOffset), (uint32)(u8RxFifoTableId)), 
                     /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                     /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            (uint32)(((Can_pCurrentConfig->pRxFiFoTableIdConfig) + u8TempIndex)->u32TableId) );

    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                    /* Check if BCC support is enabled in configuration */
                    if ( CAN_CONTROLLERCONFIG_BCC_EN_U32 != (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_BCC_EN_U32) )
                    {
    #endif
                        REG_WRITE32(FLEXCAN_RXIMR((u8HwOffset), (uint32)(u8RxFifoTableId)), 
                         /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                            (uint32)((((Can_pCurrentConfig->pRxFiFoTableIdConfig) + u8TempIndex))->u32TableFilterMask));
    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                    }
    #endif

                    /* Increment the Table Id index for RxFifo configuration. */
                    u8RxFifoTableId++;
                }

                /* Configure Interrupt Mask Bits in case handling of RX is implemented by interrupts (not by polling). */
                if ( CAN_CONTROLLERCONFIG_RXPOL_EN_U32 != (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & pCanControlerDescriptor->u32Options) )
                {
                    /* Check if Overflow RxFifo interrupt is enabled and set the IMASK bit if yes. */
                    if ( CAN_CONTROLLERCONFIG_OVER_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_OVER_EN_U32) )
                    {
                        Can_ControllerStatuses[Controller].u32MBInterruptMask[FLEXCAN_IMASK1_INDEX_U8] |= FLEXCAN_FIFO_OVERFLOW_INT_MASK_U32;
                    }
                    /* Check if Warning RxFifo interrupt is enabled and set the IMASK bit if yes. */
                    if ( CAN_CONTROLLERCONFIG_WARN_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WARN_EN_U32) )
                    {
                        Can_ControllerStatuses[Controller].u32MBInterruptMask[FLEXCAN_IMASK1_INDEX_U8] |= FLEXCAN_FIFO_WARNING_INT_MASK_U32;
                    }
                    /* If RxFifo is enabled, then frames are implicitly enabled. IDAM bits can filter the messages or can block at all. */
                    Can_ControllerStatuses[Controller].u32MBInterruptMask[FLEXCAN_IMASK1_INDEX_U8] |= FLEXCAN_FIFO_AVAILABLE_INT_MASK_U32;
                }
            }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

            /* Stage2: Init Rx/Tx MBs ******************************************************************** */

            /* Parse all MBs that are of type RECEIVE from the chain list, but process only the MBs for controller transmitted as parameter in this function. */
            while ( (u8MbCtrlIndex < pCanControlerDescriptor->u8MaxMBCount) &&
                    (u16MbGlobalIndex < pCanMbConfigContainer->uMessageBufferConfigCount) )
            {
                /* u16MbGlobalIndex variable is incrementing based of existing HOH for MBs. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                if ( Controller == (((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->u8ControllerId))
                {
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    if (CAN_RECEIVE == ((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->eMBType )
                    {
                        
#if (CAN_RXFIFO_ENABLE == STD_ON)
                        /* Skip the MB configuration if FIFO is enabled and this is the FIRST RX MB configured . */
                        if(u8MbSkip == (uint8)1U)
                        {
#endif
                            /* Get the ID of the current MB. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                            u32MbMessageId = (uint32)((pCanMbConfigContainer->pMessageBufferConfigsPtr+u16MbGlobalIndex)->uMessageId);

                            /* Clear variable for every MB. */
                            u32MbConfig = (uint32)0U;

    #if (CAN_EXTENDEDID == STD_ON)
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                            if ( CAN_STANDARD == (((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdType) )
                            {
    #endif /* (CAN_EXTENDEDID == STD_ON) */

    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                /* Check if BCC support is enabled in configuration */
                                if ( CAN_CONTROLLERCONFIG_BCC_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_BCC_EN_U32) )
                                {
                                        if((u8MbCtrlIndex != FLEXCAN_MB_14_U8) && (u8MbCtrlIndex != FLEXCAN_MB_15_U8) && (u8RxglobalMskUpdate == 0U))
                                        {
                                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                            /* @violates @ref Can_Flexcan_c_REF_17 Violates MISRA 2004 Required Rule 12.8, shift operand check*/                                                                                     
                                            /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                                            /* @violates @ref Can_Flexcan_c_REF_13 Violates MISRA 2004 Required Rule 10.5, the operator << was used. */                 
                                            REG_WRITE32(FLEXCAN_RXGMASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex] << 18U)) & FLEXCAN_RXGMASK_CONFIG_MASK_U32));
                                            u8RxglobalMskUpdate++;
                                        }
                                        else if((u8MbCtrlIndex == FLEXCAN_MB_14_U8) && (u8Temp14 == 0U))
                                        {
                                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                            {  
                                             
                                                 /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                 /* @violates @ref Can_Flexcan_c_REF_17 Violates MISRA 2004 Required Rule 12.8, shift operand check*/                                                                                     
                                                 /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                                                 /* @violates @ref Can_Flexcan_c_REF_13 Violates MISRA 2004 Required Rule 10.5, the operator << was used. */        
                                                 REG_WRITE32(FLEXCAN_RX14MASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex] << 18U)) & FLEXCAN_RX14MASK_CONFIG_MASK_U32));
                                                 
                                            }
                                            else 
                                            {
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                REG_WRITE32(FLEXCAN_RX14MASK(u8HwOffset), ((FLEXCAN_NO_MASK_U32) & FLEXCAN_RX14MASK_CONFIG_MASK_U32));
                                               
                                            }                                                    
                                            u8Temp14++;
                                        }
                                        else if((u8MbCtrlIndex == FLEXCAN_MB_15_U8) && (u8Temp15 == 0U))
                                        {
                                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                            {  
                                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                /* @violates @ref Can_Flexcan_c_REF_17 Violates MISRA 2004 Required Rule 12.8, shift operand check*/                                                                                     
                                                /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                                                /* @violates @ref Can_Flexcan_c_REF_13 Violates MISRA 2004 Required Rule 10.5, the operator << was used. */  
                                                REG_WRITE32(FLEXCAN_RX15MASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex] << 18U)) & FLEXCAN_RX15MASK_CONFIG_MASK_U32));
                                                
                                            }
                                            else
                                            {
                                                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                 REG_WRITE32(FLEXCAN_RX15MASK(u8HwOffset), ((FLEXCAN_NO_MASK_U32) & FLEXCAN_RX15MASK_CONFIG_MASK_U32));
                                           
                                            }
                                            u8Temp15++;
                                        }
                                        else
                                        {
                                            /* Already the  RX Global MASK register is updated, its used as acceptance mask for all Rx MBs except for 14 and 15 MB's*/
                                        }
                                }
                                else
                                {
    #endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                
                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                {
                                    /* @violates @ref Can_Flexcan_c_REF_17 Violates MISRA 2004 Required Rule 12.8, shift operand check*/
                                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                    /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                                    /* @violates @ref Can_Flexcan_c_REF_13 Violates MISRA 2004 Required Rule 10.5, the operator << was used. */
                                    REG_WRITE32(FLEXCAN_RXIMR((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex] << 18U));
                  
                                }
                                else
                                {
                                    /* @violates @ref Can_Flexcan_c_REF_17 Violates MISRA 2004 Required Rule 12.8, shift operand check*/
                                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                    /* @violates @ref Can_Flexcan_c_REF_12 Violates MISRA 2004 Required Rule 10.3, the value of a complex expression was cast to a type that is not narrower */
                                    /* @violates @ref Can_Flexcan_c_REF_13 Violates MISRA 2004 Required Rule 10.5, the operator << was used. */
                                    REG_WRITE32(FLEXCAN_RXIMR((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)(FLEXCAN_NO_MASK_U32));
                                    
                                }
                                
    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                }
    #endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */

                                /* Copy the Message ID (serves as acceptance filter for Rx MBs). For Standard type, ID is placed on bits 28:18 on ID Reg of the MB structure. */
                                u32MbMessageId <<= FLEXCAN_STANDARD_ID_SHIFT_U32;
    #if (CAN_EXTENDEDID == STD_ON)
                            }
                            else
                            {
    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                /* Check if BCC support is enabled in configuration */
                                if ( CAN_CONTROLLERCONFIG_BCC_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_BCC_EN_U32) )
                                {
                                        if((u8MbCtrlIndex != FLEXCAN_MB_14_U8) && (u8MbCtrlIndex != FLEXCAN_MB_15_U8) && (u8RxglobalMskUpdate == 0U))
                                        {
                                             /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                             REG_WRITE32(FLEXCAN_RXGMASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex])) & FLEXCAN_RXGMASK_CONFIG_MASK_U32));
                                             u8RxglobalMskUpdate++;
                                        }
                                        else if((u8MbCtrlIndex == FLEXCAN_MB_14_U8) && (u8Temp14 == 0U))
                                        {
                                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                            {  
                                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                REG_WRITE32(FLEXCAN_RX14MASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex])) & FLEXCAN_RX14MASK_CONFIG_MASK_U32));
                                                
                                            }
                                            else 
                                            {
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                REG_WRITE32(FLEXCAN_RX14MASK(u8HwOffset), ((FLEXCAN_NO_MASK_U32) & FLEXCAN_RX14MASK_CONFIG_MASK_U32));
                                                
                                            }                                            
                                            u8Temp14++;
                                        }
                                        else if((u8MbCtrlIndex == FLEXCAN_MB_15_U8) && (u8Temp15 == 0U))
                                        {
                                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                            if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                            {                                          
                                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                REG_WRITE32(FLEXCAN_RX15MASK(u8HwOffset), (((uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex])) & FLEXCAN_RX15MASK_CONFIG_MASK_U32));
                                              
                                            }
                                            else 
                                            {
                                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                REG_WRITE32(FLEXCAN_RX15MASK(u8HwOffset), ((FLEXCAN_NO_MASK_U32) & FLEXCAN_RX15MASK_CONFIG_MASK_U32));
                            
                                            }                                            
                                            u8Temp15++;
                                        }
                                        else
                                        {
                                            /* Already the  RX Global MASK register is updated, its used as acceptance mask for all Rx MBs except for 14 and 15 MB's*/
                                        }
                                }
                                else
                                {
    #endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */
                                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                    if(CAN_MAXMASKCOUNT !=(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex))
                                    {                                   
                                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                        REG_WRITE32(FLEXCAN_RXIMR((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)((Can_pCurrentConfig->pFilterMasks)[((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->uIdMaskIndex]));
                                        
                                    }
                                    else
                                    {
                                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                        REG_WRITE32(FLEXCAN_RXIMR((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)(FLEXCAN_NO_MASK_U32));
                                     
                                    }
    #if (CAN_BCC_SUPPORT_ENABLE == STD_ON)
                                }
    #endif /* (CAN_BCC_SUPPORT_ENABLE == STD_ON) */

                                /* Set the IDE bit if the ID type is EXTENDED or MIXED. */
                                u32MbConfig = FLEXCAN_MBCS_IDE_U32 ;

                                /* For EXTENDED MB type the ID is placed starting from bits 0 ( unlike STANDARD type when is placed starting to bit 18). */
                            }
    #endif /* (CAN_EXTENDEDID == STD_ON) */

                            /* Enable the MB as a Rx object. MB is used for Rx & Mark the buffer as empty. */
                            u32MbConfig |= FLEXCAN_MBCS_CODERXEMPTY_U32;
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)(u32MbConfig));
                          

                            /* Copy the Message ID (serves as acceptance filter for Rx MBs). */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)((u32MbMessageId) | ((REG_READ32(FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbCtrlIndex)))) & 0xE0000000U) ));
                            
                            /* Save the mask bit from IMASK register for this MB used by Can_EnableControllerInterrupts() API. */
                            if ( CAN_CONTROLLERCONFIG_RXPOL_EN_U32 != (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & pCanControlerDescriptor->u32Options) )
                            {
                                Can_ControllerStatuses[Controller].u32MBInterruptMask[(uint8)((uint8)u8MbCtrlIndex >> FLEXCAN_MB_SHIFT5BIT_U8)] |= ((uint32)1U << (uint8)(u8MbCtrlIndex & FLEXCAN_MASK_32BITS_U32));                             
                            }
#if (CAN_RXFIFO_ENABLE == STD_ON)
                        }
                        else
                        {
                            u8MbSkip = (uint8)1U;
                        }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */

                        /* Record for current controller the HTH/HRH assigned foe every MB. */
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                        Can_ControllerStatuses[Controller].u16MBMapping[u8MbCtrlIndex] = ((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->u32HWObjID;

                        /* Increment current index for the controller on every RxMB configured. */
                        u8MbCtrlIndex++;

                        /* At this point "u8FirstTxMBIndex" is updated and considering RxFifo if enebaled also. */
                        Can_ControllerStatuses[Controller].u8FirstTxMBIndex = u8MbCtrlIndex;

                    }
                }
                /* Increment the MB index for the controller even is Tx or Rx MB.
                  "u16MbGlobalIndex" should parse all HOH or at least all the MBs for this controller are configured. */
                u16MbGlobalIndex++;
            }

            /*Reset the counter for global MBs. */
            u16MbGlobalIndex  = 0U;

            /* Parse all MBs that are of type TRANSMIT from the chain list, but process only the MBs for controller transmitted as parameter in this function. */
            while ( (u8MbCtrlIndex < pCanControlerDescriptor->u8MaxMBCount) &&
                    (u16MbGlobalIndex < pCanMbConfigContainer->uMessageBufferConfigCount) )
            {
                /* u16MbGlobalIndex variable is incrementing based of existing HOH for MBs. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used  */
                if ( Controller == (((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->u8ControllerId))
                {
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4 */
                    if (CAN_TRANSMIT == ((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->eMBType )
                    {
                            /* Enable the MB as an TX object. MB is used for Tx & SRR must be set for Tx buffers. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)(FLEXCAN_MBCS_CODETX_U32 | FLEXCAN_MBCS_SRR_U32));
                            
                            /* Configure only PRIO field of MBCS register of every Tx MB. */
                            if ( CAN_CONTROLLERCONFIG_LPRIO_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_LPRIO_EN_U32) )
                            {
                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
                                u32MbMessageId = (uint32)((uint32)(((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->u8LocalPriority) << FLEXCAN_MB_ID_PRIO_SHIFT_U32) ;
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                REG_WRITE32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)((u32MbMessageId) | ((REG_READ32(FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbCtrlIndex)))) & 0xE0000000U) ));
                                
                            }
                            if ( CAN_CONTROLLERCONFIG_TXPOL_EN_U32 != (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 & pCanControlerDescriptor->u32Options) )
                            {                              
                                Can_ControllerStatuses[Controller].u32MBInterruptMask[(uint8)((uint8)u8MbCtrlIndex >> FLEXCAN_MB_SHIFT5BIT_U8)] |= ((uint32)1U << (uint8)(u8MbCtrlIndex & FLEXCAN_MASK_32BITS_U32));                                
                              
                            }

                            /* Record for current controller the HTH/HRH assigned foe every MB. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                            /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            Can_ControllerStatuses[Controller].u16MBMapping[u8MbCtrlIndex] = ((pCanMbConfigContainer->pMessageBufferConfigsPtr) + u16MbGlobalIndex)->u32HWObjID;

                            /* Increment current index for the controller on every RxMB configured. */
                            u8MbCtrlIndex++;

                    }
                }

                /* Increment the MB index for the controller even is Tx or Rx MB.
                  "u16MbGlobalIndex" should parse all HOH or at least all the MBs for this controller are configured. */
                u16MbGlobalIndex++;
            }

            if(pCanControlerDescriptor->u8MaxMBCount > 0U)
            {
                u8MbMax = pCanControlerDescriptor->u8MaxMBCount - 1U;
            }
            else
            {
                u8MbMax = 0U;
            }
            /* Set the number of MBs configured for this controller (Rx + Tx MBs). */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_RMW32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_MAXMB_U32, ((uint32)u8MbMax)) ;
           

#if defined(CAN_USE_MCR_ABORT_ENABLE)
  #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
    /* Do not set the Abort Enable bit of the MCR */
  #else
    #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
  #endif
#else
    #if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
            /* Abort Enable: Tx Cancelation supported and used for this Controller. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_AEN_U32);
            
    #endif /* (CAN_HW_TRANSMIT_CANCELLATION==STD_ON) */
#endif

            /* Pre-calculated MB INT masks (used in Can_EnableControllerInterrupts) - If events are set for polling mode these bits are not set.
                Clear all INTs flags  .. for MBs (w1c bits). */
             for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8);u8RegCount++)
             {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanIflag, (uint32)(FLEXCAN_32BITMASK_U32) );
             }        
            

            /* Clear bits for Tx/Rx/BusOff/Err/WakeUp (w1c bits). */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */            
            REG_WRITE32( FLEXCAN_ESR(u8HwOffset), (uint32)(((uint32)(FLEXCAN_ESR_BOFFINT_U32 | FLEXCAN_ESR_ERRINT_U32 | FLEXCAN_ESR_WAK_INT_U32)) & FLEXCAN_ESR_CONFIG_MASK_U32));

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* After controller is (re-)initialized the state is CAN_T_STOP. For this state the Wakeup support must not be enabled.
            Wakeup is used for the transition out of CAN_T_SLEEP state. */

            /* If internal WakeUp is supported clear Wakeup status int flag (w1c bit). */
            REG_WRITE32( FLEXCAN_ESR(u8HwOffset), (FLEXCAN_ESR_WAK_INT_U32 & FLEXCAN_ESR_CONFIG_MASK_U32));

#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* Clear the Error Counters Register. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            
            REG_WRITE32( FLEXCAN_ECR(u8HwOffset), (uint32)(((uint32)0UL) & FLEXCAN_ECR_CONFIG_MASK_U32));


            /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
                unless the CPU reads the C/S word of another MB.*/
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_READ32( FLEXCAN_TIMER(u8HwOffset));

        } /* (eResetReturn == CAN_OK) */
    }


/*================================================================================================*/
/**
* @brief          Service to Perform software triggered state transitions of the CAN controller State machine.
* @details        Transition controller to another state/mode.
*                 This routine is called by:
*                  - Can_SetControllerMode() from Can.c file.
*                  - Can_IPW_ProcessBusOff() from Can_IPW.c file.
*                  - Can_IPW_Process_Wakeup() from Can_IPW.c file.
*
* @param[in]      Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      pCanControlerDescriptor Pointer to controller descriptor configuration
* @param[in]      Transition Possible transitions
*
* @return         Can_ReturnType
* @retval         CAN_OK transition initiated
* @retval         CAN_NOT_OK development or production error
*
* @pre            Controller is configured and must be into a state that permit the valid transition to another different state.
* @post           Shall enable interrupts that are needed in the new state. Shall disable interrupts that are not allowed in the new state.
*
* @requirements   CAN283
*
*/
FUNC (Can_ReturnType, CAN_CODE) Can_FlexCan_SetControllerMode( VAR(uint8, AUTOMATIC) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, AUTOMATIC, CAN_APPL_CONST) pCanControlerDescriptor,
                                                           VAR(Can_StateTransitionType, AUTOMATIC) Transition,
                                                           VAR(boolean, AUTOMATIC) canif_notification_required)
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, AUTOMATIC)  eReturnValue = CAN_NOT_OK;
        /* Variable for indexing the MBs. */
        VAR(uint8, AUTOMATIC)           u8MbCtrlIndex = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)           u8HwOffset = 0U;
        /* Temporary variable for CTRL register. */
        VAR(uint32, AUTOMATIC)          u32CtrlReg = 0U;
        /* Temporary variable for MB config register. */
        VAR(uint32, AUTOMATIC)          u32MbConfig = 0U;
        /* Timeout counter. */
        VAR(uint32, AUTOMATIC)          u32TimeoutCount = 0U;
        VAR(uint32, AUTOMATIC)          u32TempVar = 0U;
        VAR(uint8 , AUTOMATIC)          u8RegCount = 0U;



        /* Get the hardware offset for this controller. */
        u8HwOffset = pCanControlerDescriptor->u8ControllerOffset;

        /*
          (CAN017) The function Can_SetControllerMode shall perform software triggered state transitions of the CAN controller State machine.
        */
        switch (Transition)
        {
            /* CANIF_CS_STARTED -> CANIF_CS_STOPPED. */
            /*
               (CAN283) The function Can_SetControllerMode(CAN_T_STOP) shall not call a cancellation notification.
            */
            case (CAN_T_STOP):
                /*
                   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                */
                if ( CAN_STOPPED == Can_ControllerStatuses[Controller].ControllerState)
                {
                    /* If the controller is already in STOP state, return CAN_OK. */
                    eReturnValue = CAN_OK;
                }
                else
                {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Stop are only from Start and Wakeup. */
                    if ( CAN_STARTED != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                        /*
                          (CAN263) The function Can_SetControllerMode(CAN_T_STOP) shall set the bits inside the CAN hardware such that the CAN controller
                                   stops participating on the network.
                        */

                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_FRZ_U32);
                        
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_HALT_U32);
                        

                        /*
                           (CAN264) The function Can_SetControllerMode(CAN_T_STOP) shall wait for a limited time until the CAN controller is really switched off. Compare to CAN371
                        */
                        /* This means will wait until MCR[FRZ_ACK] is set. */
                        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
                        u32TempVar = (uint32)0U;
                        do {
                            /* ... stay in loop */
                            u32TimeoutCount--;
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32TempVar |= ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_FRZACK_U32);
                        } while ((u32TimeoutCount > (uint32)0x0U) && ( FLEXCAN_MCR_FRZACK_U32 != u32TempVar));
                        
                        if (FLEXCAN_MCR_FRZACK_U32 == u32TempVar)
                        {                      
                            eReturnValue = CAN_OK;
                        }
                        else
                        /* software timeout */
                        {
#if (CAN_WAKEUP_SUPPORT == STD_ON)                        
                         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            Can_u32McrConfiguration[Controller] = (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset));
#endif                            
                            eReturnValue = CAN_NOT_OK;
                        }
                        
                        /* Check if Software BusOff Recovery is enabled. */
                        if ( CAN_CONTROLLERCONFIG_BUSOFFSWREC_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_BUSOFFSWREC_U32) )
                        {
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFREC_U32);
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_BIT_SET32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFREC_U32);
                        }

                        /* Loop through all Tx MBs. -> must abort transmission for all MBs for Tx. */
                        for ( u8MbCtrlIndex = Can_ControllerStatuses[Controller].u8FirstTxMBIndex; u8MbCtrlIndex < pCanControlerDescriptor->u8MaxMBCount; u8MbCtrlIndex++)
                        {
                            /* Cancel the MB (just in case it is scheduled for Tx). This is a HARD ABORT, confirmation of whether the MB was transmitted or not is not required. */
                            /*
                               (CAN282) The function Can_SetControllerMode(CAN_T_STOP) shall cancel pending messages.
                               (CAN273)After bus-off detection, the Can module shall cancel still pending messages without raising a cancellation notification.
                            */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32MbConfig = ( ((uint32)REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbCtrlIndex))) & ~FLEXCAN_MBCS_CODE_U32) | FLEXCAN_MBCS_CODETX_U32 );
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbCtrlIndex)), (uint32)(u32MbConfig));                            
                        }

                        /*
                        The Can module shall track all individual enabling and disabling of  interrupts
                            in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
                        When Freeze mode (or Autosar equiv Stop mode) need to not participate on network ->
                            no interrupt is required to be enabled.
                        */
                        Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~(FLEXCAN_SWF_BOFF_MASK_U8 | FLEXCAN_SWF_ERR_MASK_U8 | FLEXCAN_SWF_MB_MASK_U8 | FLEXCAN_SWF_WRNINT_MASK_U8));
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~FLEXCAN_SWF_WAK_MASK_U8);
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/

                        /* Check if Ints are enabled by Can_EnableControllerInterrupts. */
                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                        {
                            /*
                               (CAN197) The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state.
                               (CAN426)  Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                            */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFMSK_U32);
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_ERRMSK_U32);
                            if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
                            {
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_TWRNMSK_U32);
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_RWRNMSK_U32);
                            }

                            /*Disable all TX/RX interrupts*/
                            for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8) ;u8RegCount++)
                            {
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask, (uint32)0U);
                            }
                          


#if (CAN_WAKEUP_SUPPORT == STD_ON)
                            /* No need for Wakeup support in Stop mode (only for Sleep). */
                           REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                            /**@}*/
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/
                        }

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        /* For internal wakeup the ESR[WAK_INT] bit is always activated  - it's a status bit that is masked by MCR[WAK_MSK].
                           This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */
                           REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);
                        
#endif /*  (CAN_WAKEUP_SUPPORT == STD_ON)*/                      

#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                }
                /* @violates @ref Can_Flexcan_c_REF_18 Results boolean operations whose results are maybe variant */
                if (CAN_OK == eReturnValue)                
                {
                    /* Set the Stop state to the controller. */
                    Can_ControllerStatuses[Controller].ControllerState = CAN_STOPPED;
                    /*Do not notify CanIf for bus off events*/
                    if((boolean)TRUE == canif_notification_required)
                    {
                        CanIf_ControllerModeIndication(Controller, CANIF_CS_STOPPED);
                    }   
                }
                break;

            /* CANIF_CS_STOPPED -> CANIF_CS_STARTED. */
            case (CAN_T_START):

#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Start mode are only from Stop state. */
                    if ( CAN_STOPPED != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
#if (CAN_DUAL_CLOCK_MODE == STD_OFF)
                        /* (CAN384) Each time the CAN controller state machine is triggered with the state transition value CAN_T_START, the function
                        Can_SetControllerMode shall re-initialize the CAN controller with the same controller configuration set previously used by functions
                        Can_ChangeBaudrate or Can_Init.*/
                       Can_FlexCan_ChangeBaudrate( Controller);
#endif
                        /*
                        (CAN261) The function Can_SetControllerMode(CAN_T_START) shall set the hardware registers in a way that makes the CAN controller participating on the network.
                        */
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_FRZ_U32);
                        
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_HALT_U32);
                        

                        /*
                        (CAN196) The function Can_SetControllerMode shall enable interrupts that are needed in the new state.
                        (CAN425)   Enabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                         */
                        /*
                        The Can module shall track all individual enabling and disabling of interrupts in
                            other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
                        */
                        Can_ControllerStatuses[Controller].u8ControllerSWFlag |= (uint8)(FLEXCAN_SWF_MB_MASK_U8);
                        if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
                        {
                            Can_ControllerStatuses[Controller].u8ControllerSWFlag |= (uint8)(FLEXCAN_SWF_WRNINT_MASK_U8);
                        }
                        
                        if ( CAN_CONTROLLERCONFIG_ERR_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_ERR_EN_U32) )
                        {
                            Can_ControllerStatuses[Controller].u8ControllerSWFlag |= (uint8)(FLEXCAN_SWF_ERR_MASK_U8);
                        }

                        if ( CAN_CONTROLLERCONFIG_BOPOL_EN_U32 != (CAN_CONTROLLERCONFIG_BOPOL_EN_U32 & pCanControlerDescriptor->u32Options))
                        {
                            Can_ControllerStatuses[Controller].u8ControllerSWFlag |= (uint8)(FLEXCAN_SWF_BOFF_MASK_U8);
                        }
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        /* Wakeup interrupt is not required in Start mode. */
                        Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~FLEXCAN_SWF_WAK_MASK_U8);

                        /* This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */

                           REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);


                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                        {

                            /* No need for Wakeup support in Run mode. */
                            REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                           
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32CtrlReg = (uint32)REG_READ32( FLEXCAN_CTRL(u8HwOffset));
                            if ( CAN_CONTROLLERCONFIG_ERR_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_ERR_EN_U32) )
                            {
                                u32CtrlReg |= FLEXCAN_CTRL_ERRMSK_U32;
                            }

                            if ( CAN_CONTROLLERCONFIG_BOPOL_EN_U32 != (CAN_CONTROLLERCONFIG_BOPOL_EN_U32 & pCanControlerDescriptor->u32Options))
                            {
                                u32CtrlReg |= FLEXCAN_CTRL_BOFFMSK_U32;
                            }
                            
                            if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
                            {
                                u32CtrlReg |= FLEXCAN_CTRL_TWRNMSK_U32 | FLEXCAN_CTRL_RWRNMSK_U32;
                            }
                            /*
                            * @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
                            */                            
                            REG_WRITE32( FLEXCAN_CTRL(u8HwOffset), (uint32)((u32CtrlReg) & FLEXCAN_CTRL_CONFIG_MASK_U32));

                            for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8) ;u8RegCount++)
                            {
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask, (uint32)(Can_ControllerStatuses[Controller].u32MBInterruptMask[u8RegCount]));
                            }  

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                        }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */


                        /* (CAN262) The function Can_SetControllerMode(CAN_T_START) shall wait for limited time until the CAN controller is fully operational. Compare to CAN371. */
                        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
                        u32TempVar = (uint32)0U;
                        do {
                            /* ... stay in loop */
                            u32TimeoutCount--;
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32TempVar = ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & (FLEXCAN_MCR_FRZ_U32 | FLEXCAN_MCR_HALT_U32 | FLEXCAN_MCR_NOTRDY_U32));
                        } while ((u32TimeoutCount > (uint32)0x0U) && ( 0x0U != u32TempVar));

                        if ((uint32)0x0U == u32TempVar)
                        {
                            /* Set the Start State. */
                            Can_ControllerStatuses[Controller].ControllerState = CAN_STARTED;
                            eReturnValue = CAN_OK;
                        }
                        else
                        /* software timeout */
                        {
#if (CAN_WAKEUP_SUPPORT == STD_ON)                        
                         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            Can_u32McrConfiguration[Controller] = (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset));
#endif                            
                            eReturnValue = CAN_NOT_OK;
                        }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                if (CAN_OK == eReturnValue)
                {
                    CanIf_ControllerModeIndication(Controller, CANIF_CS_STARTED);
                }
                break;

            /* CANIF_CS_STOPPED -> CANIF_CS_SLEEP. */
            case (CAN_T_SLEEP):

#if (CAN_WAKEUP_SUPPORT == STD_ON)
                /*
                   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                */
                if ( CAN_SLEEPED == Can_ControllerStatuses[Controller].ControllerState )
                {
                    /* If the controller is already in SLEEP state, return CAN_OK. */
                    eReturnValue = CAN_OK;
                }
                else
                {
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Sleep state are only from Stop state. */
                    if ( CAN_STOPPED != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                        /*
                           (CAN290)If the CAN HW does not support a sleep mode, the function Can_SetControllerMode(CAN_T_SLEEP) shall set the
                                    CAN controller to the logical sleep mode.
                           (CAN267) If the CAN HW does not support a sleep mode, the function Can_SetControllerMode(CAN_T_WAKEUP) shall return
                                    from the logical sleep mode, but have no effect to the CAN controller state (as the controller is already
                                    in stopped state).
                        */
                        /* If Wakeup is not supported no operation is done. */
                        if ( CAN_CONTROLLERCONFIG_WAKSUP_EN_U32 == (CAN_CONTROLLERCONFIG_WAKSUP_EN_U32 & pCanControlerDescriptor->u32Options))
                        {
                            if ( CAN_CONTROLLERCONFIG_WKPOL_EN_U32 != (CAN_CONTROLLERCONFIG_WKPOL_EN_U32 & pCanControlerDescriptor->u32Options))
                            {
                                /*
                                   (CAN294) The function Can_SetControllerMode shall disable the wake-up interrupt, while checking the wake-up status.
                                */
                                /* First of all, disable WakeUp interrupt. */
                                Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~FLEXCAN_SWF_WAK_MASK_U8);

                                if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                                {
                                    REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                                    REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);

                                }

                                /*
                                   (CAN048) In case of a CAN bus wake-up during sleep transition, the function Can_SetControllerMode(CAN_T_WAKEUP) shall return CAN_NOT_OK.
                                */
                                /* Init this value with CAN_OK = 0x00. */
                                eReturnValue = CAN_OK;

                                /* Check for Wakeup flag status. */
                                if ( FLEXCAN_ESR_WAK_INT_U32 == (FLEXCAN_ESR_WAK_INT_U32 & REG_READ32( FLEXCAN_ESR(u8HwOffset))) )
                                {
                                    /* Wakeup interrupt occurred, return with error. */
                                    eReturnValue = CAN_NOT_OK;
                                }

                                /*
                                  (CAN257) When the CAN hardware supports sleep mode, when transitioning into mode CANIF_CS_SLEEP, the Can module shall set the controller to a state from which the hardware can be woken over CAN Bus.
                                  (CAN197) The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state.
                                        Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by function CAN_DisableControllerInterrupts.
                                */
                                if ( CAN_OK == eReturnValue )
                                {
                                    /* Enable interrupts that are needed in this state. */
                                    Can_ControllerStatuses[Controller].u8ControllerSWFlag |= (uint8)FLEXCAN_SWF_WAK_MASK_U8;

                                    /* Disable interrupts that are not needed in this state. */
                                    Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~(FLEXCAN_SWF_BOFF_MASK_U8 | FLEXCAN_SWF_ERR_MASK_U8 | FLEXCAN_SWF_WRNINT_MASK_U8 | FLEXCAN_SWF_MB_MASK_U8));

                                    if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                                    {
                                        /* Enable the Wakeup interrupt generation. */
                                        REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                                        REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFMSK_U32);
                                        REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_ERRMSK_U32);
                                        if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
                                        {
                                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_TWRNMSK_U32);
                                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_RWRNMSK_U32);
                                        }

                                    /* Disable all Tx/Rx interrupts for message buffers */                  
                                    for (u8RegCount=(uint8)0; u8RegCount < (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8); u8RegCount++)
                                    {
                                        REG_WRITE32(Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask, (uint32)0U);
                                    }

                                    }
                                    /* This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode.
                                       If a transition from recessive to dominant is detected during Stop Mode, then FlexCAN generates, if enabled to do so, a Wake Up interrupt to the CPU so that it can resume the clocks globally. */
                                    REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);

                                    Can_ControllerStatuses[Controller].ControllerState = CAN_SLEEPED;

                                    /* The hardware settings only differ from CANIF_CS_STOPPED for CAN hardware that support a sleep mode (wake-up over CAN bus directly supported by CAN hardware).  */
                                    /*
                                       (CAN265)The function Can_SetControllerMode(CAN_T_SLEEP) shall put the controller into sleep mode.
                                    */
                                    eReturnValue = CAN_OK;
                                }
                            }
                            else
                            /* POLLING mode */
                            {
                                /* For internal wakeup the ESR[WAK_INT] bit is always activated  - it's a status bit that is masked by MCR[WAK_MSK].
                                   This bit enables the Self Wake Up feature when FlexCAN is in Doze/Stop Mode. */
                                REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);
                                

                                Can_ControllerStatuses[Controller].ControllerState = CAN_SLEEPED;
                                eReturnValue = CAN_OK;
                            }
                        }
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */


                    /*
                       (CAN266) If the CAN HW does support a sleep mode, the function Can_SetControllerMode(CAN_T_SLEEP) shall wait for a limited time until the CAN controller is in SLEEP state and it is assured that the CAN hardware is wake able. Compare to CAN371.
                    */
                    /* Now must assure that when return from this function Can controller is wakeable. For all state changes except the
                            change to state CANIF_CS_SLEEP, the function does not wait until the state change has really performed. */
                    u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
                    do {
                        /* ... stay in loop */
                        u32TimeoutCount--;
                        u32TempVar = (uint32)0U;

                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                        {
                            u32TempVar = ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_WAK_MSK_U32 );
                        }
                        /* Self Wakeup must be set. */
                        u32TempVar |= ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_SLF_WAK_U32 );
                    } while ((u32TimeoutCount > (uint32)0x0U) && ( (uint32)0x0U == u32TempVar));

                    if ((uint32)0x0U != u32TempVar)
                    {
                        eReturnValue = CAN_OK;
                    }
                    else
                    /* software timeout */
                    {
                        Can_u32McrConfiguration[Controller] = (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset));
                        eReturnValue = CAN_NOT_OK;
                    }
                }
                
                if (CAN_OK == eReturnValue)
                {
                    CanIf_ControllerModeIndication(Controller, CANIF_CS_SLEEP);
                }
#else /* (CAN_WAKEUP_SUPPORT == STD_OFF) */
 /*
                   (PR-MCAL-3057) The Can driver shall not create a development error if the CanIf requests a transision to a state that was already reached.
                */
                if ( CAN_SLEEPED == Can_ControllerStatuses[Controller].ControllerState )
                {
                    /* If the controller is already in SLEEP state, return CAN_OK. */
                    eReturnValue = CAN_OK;
                }
                else
                {
                
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* Valid transitions to Sleep state are only from Stop state. */
                    if ( CAN_STOPPED != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                        /*[CAN290]If the CAN HW does not support a sleep mode, the function Can_SetControllerMode(CAN_T_SLEEP) shall set the CAN controller to the logical sleep mode*/
                        /*[CAN405] This logical sleep mode shall left only, if function Can_SetControllerMode(CAN_T_WAKEUP) is called.*/
                        eReturnValue = CAN_OK;
                        Can_ControllerStatuses[Controller].ControllerState = CAN_SLEEPED;
                        CanIf_ControllerModeIndication(Controller, CANIF_CS_SLEEP);
    #if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
    #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                }
#endif /* (CAN_WAKEUP_SUPPORT == STD_OFF) */

                break;

            /* CANIF_CS_SLEEP -> CANIF_CS_STOPPED */
            case (CAN_T_WAKEUP):
                /*Controllers option for wakeup support(CAN_CONTROLLERCONFIG_WAKSUP_EN_U32) is not necessarly to be checked because if this is not supported,
                the controller cannot be in state CAN_SLEEPED, so the Det_ReportError will be raised*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                /*
                  (CAN268) The function Can_SetControllerMode(CAN_T_WAKEUP) shall be non-blocking.
                  (CAN270)On hardware wakeup (triggered by a wake-up event from CAN bus), the Can module shall transition into the state CAN_IF_CS_STOPPED.
                */
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                /* Valid transitions to Wakeup state are ony from Sleep state. */
                if (CAN_SLEEPED != Can_ControllerStatuses[Controller].ControllerState)
                {
                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                }
                else
                {
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */

                    /*
                       (CAN294) The function Can_SetControllerMode shall disable the wake-up interrupt, while checking the wake-up status.
                    */

                    /* The Can module shall track all individual enabling and disabling of  interrupts in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored. */
                    Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~FLEXCAN_SWF_WAK_MASK_U8);

                    Can_ControllerStatuses[Controller].u8ControllerSWFlag &= (uint8)(~(FLEXCAN_SWF_BOFF_MASK_U8 | FLEXCAN_SWF_ERR_MASK_U8 | FLEXCAN_SWF_WRNINT_MASK_U8 | FLEXCAN_SWF_MB_MASK_U8));

                    if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                    {
                        /* Disable WakeUp Interrupt. */
                        REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                        REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFMSK_U32);
                        REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_ERRMSK_U32);
            
                        if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
                        {
                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_TWRNMSK_U32);
                            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_RWRNMSK_U32);
                        }
                        
                        for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8) ;u8RegCount++)
                        {
                            REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask, (uint32)0);
                        }
                
                      
                    }

                    REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_SLF_WAK_U32);

                    /* Set the Stop state. */
                    Can_ControllerStatuses[Controller].ControllerState = CAN_STOPPED;

                    /* Report "transition initiated". */
                    eReturnValue = CAN_OK;

                    /*
                       CAN268: The function Can_SetControllerMode(CAN_T_WAKEUP) shall wait for a limited time until the CAN controller is in STOPPED state. Compare to CAN371.
                    */

                    u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
                    do {
                        /* ... stay in loop */
                        u32TimeoutCount--;
                        u32TempVar = (uint32)0U;
                        if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[Controller].u8InterruptMode )
                        {
                            u32TempVar = ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_WAK_MSK_U32 );
                        }
                        /* Self Wakeup must be set. */
                        u32TempVar |= ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_SLF_WAK_U32 );
                    } while ((u32TimeoutCount > (uint32)0x0U) && ( (uint32)0x0U != u32TempVar));

                    if ((uint32)0x0U == u32TempVar)
                    {
                        eReturnValue = CAN_OK;
                    }
                    else
                    /* software timeout */
                    {
                        Can_u32McrConfiguration[Controller] = (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset));
                        eReturnValue = CAN_NOT_OK;
                    }
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
                }
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */  
  
                if (CAN_OK == eReturnValue)
                {
                    CanIf_ControllerModeIndication(Controller, CANIF_CS_STOPPED);
                }
#else /* (CAN_WAKEUP_SUPPORT == STD_OFF) */

                if (CAN_STOPPED == Can_ControllerStatuses[Controller].ControllerState)
                {
                    /*CanIf shall be notified only for transitions.
                    [CAN373] The function Can_Mainfunction_Mode shall call the function CanIf_ControllerModeIndication to 
                    notify the upper layer about a successful state transition of the CAN controller, in case the state transition 
                    was triggered by function Can_SetControllerMode 
                    */
                    eReturnValue = CAN_OK;
                }
                else
                {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* 
                    Valid transitions to Wakeup state are only from Sleep state. 

                    */
                    if (CAN_SLEEPED != Can_ControllerStatuses[Controller].ControllerState)
                    {
                        Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
                    }
                    else
                    {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                        /* When Wakeup is not supported the driver should do nothing and return CAN_OK. */
                        eReturnValue = CAN_OK;
                        Can_ControllerStatuses[Controller].ControllerState = CAN_STOPPED;
                        CanIf_ControllerModeIndication(Controller, CANIF_CS_STOPPED);                        
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */                                
                }                                
#endif /* (CAN_WAKEUP_SUPPORT == STD_OFF) */
                break;
                
            /* Unknown transition requested. */
            default:
                /*
                   (CAN200) If development error detection for the Can module is enabled: if an invalid transition has been requested, the function Can_SetControllerMode shall raise the error CAN_E_TRANSITION and return CAN_NOT_OK.
                */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                break;

        } /* end switch */

        return (eReturnValue);
    }


/*================================================================================================*/
/**
* @brief          Service disables all interrupts for the given CAN controller.
* @details        This routine is called by:
*                 - Can_DisableControllerInterrupts() from Can.c file.
*
* @param[in]      Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      pCanControlerDescriptor Pointer to controller descriptor configuration
*
* @pre            Disable interrupts must be called prior to enable interrupts.
* @post           Clear all flags/bits that are needed for disabling the interrupts.
*
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_DisableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller,
                                                           P2CONST(Can_ControlerDescriptorType, AUTOMATIC, CAN_APPL_CONST) pCanControlerDescriptor)
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)   u8HwOffset = 0U;
        VAR(uint8, AUTOMATIC)   u8RegCount = 0U;


        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_00();
        /*
           (CAN202) When Can_DisableControllerInterrupts has been called several times, Can_EnableControllerInterrupts must be called
                    as many times before the interrupts are re-enabled.
        */
        Can_ControllerStatuses[Controller].s8IntDisableLevel++;

        /* If nesting level is zero or below zero; <0 needed for reentrancy. */
        /*
           (CAN049) The function Can_DisableControllerInterrupts shall disable all interrupts for this CAN controller only at the first call of this function.
        */
        if ( (sint8)1 == Can_ControllerStatuses[Controller].s8IntDisableLevel )
        {
            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_00();

            /* Switch to disabled mode. */
            Can_ControllerStatuses[Controller].u8InterruptMode = (uint8)CAN_INTERRUPT_DISABLED;

            /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
            u8HwOffset = pCanControlerDescriptor->u8ControllerOffset;

            /*
               (CAN033) The Can module shall implement the interrupt service routines for all CAN Hardware Unit interrupts that are needed.
                        The Can module shall disable all unused interrupts in the CAN controller.
                        The Can module shall reset the interrupt flag at the end of the ISR (if not done automatically by hardware).
                        The Can module shall not set the configuration (i.e. priority) of the vector table entry.
            */
            /* Can_DisableControllerInterrupts and Can_EnableControllerInterrupts should not modify the software flags. */
            /* Disable MB Rx/Tx interrupts. */
           
            for (u8RegCount=(uint8)0; u8RegCount< (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8);u8RegCount++)
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask, (uint32)(0UL));
            }

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* Disable Wakeup interrupts. */
            REG_BIT_CLEAR32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);

#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

            /* Disable BusOff, Error, TxW, RxW interrupts. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFMSK_U32);
            
             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_ERRMSK_U32);

            if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
            {
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_TWRNMSK_U32);
                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_CLEAR32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_RWRNMSK_U32);

            }
        }
        else
        {
            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_00();
        }
    }


/*================================================================================================*/
/**
* @brief          Service enables all interrupts that shall be enabled according the current software status.
* @details        This routine is called by:
*                  - Can_EnableControllerInterrupts() from Can.c file.
*
* @param[in]      Controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      pCanControlerDescriptor Pointer to controller descriptor configuration
*
* @pre            Can be executed only if disable interrupts was called before.
* @post           Enable all interrupts that must be enabled according the current sw status.
*
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_EnableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller,
                                                          P2CONST(Can_ControlerDescriptorType, AUTOMATIC, CAN_APPL_CONST) pCanControlerDescriptor )
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)   u8HwOffset = 0U;
        /* Variable that tells if disable ints was called at least once before. */
        VAR(uint8, AUTOMATIC)   u8DisCalledBefore = 0U;
        /* Variable that tells if at least one interrupt is enabled according to software flags - used only for Timeout checking. */
        VAR(uint8, AUTOMATIC)   u8IntSet = 0U;
        VAR(uint8, AUTOMATIC)   u8RegCount = 0U;


        /*
           (CAN202) When Can_DisableControllerInterrupts has been called several times, Can_EnableControllerInterrupts must be called as many
                   times before the interrupts are re-enabled.
        */
        if ( Can_ControllerStatuses[Controller].s8IntDisableLevel > (sint8)0 )
        {
            /* When s8IntDisableLevel is greater than 0  means Can_DisableControllerInterrupts was called at least once before this call of current function. */
            SchM_Enter_Can_CAN_EXCLUSIVE_AREA_01();
            /* Decrement the nesting level. */
            Can_ControllerStatuses[Controller].s8IntDisableLevel--;

            u8DisCalledBefore = (uint8)0x1U;
        }

        /* Can_DisableControllerInterrupts and Can_EnableControllerInterrupts do not modify the software flags. */

        /*
           (CAN208) The function Can_EnableControllerInterrupts shall perform no action when Can_DisableControllerInterrupts has not been called before.
        */
        if ( ((sint8)0 == Can_ControllerStatuses[Controller].s8IntDisableLevel) && ((uint8)0x1U == u8DisCalledBefore) )
        {
            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_01();

            /* Switch to enabled mode. */
            Can_ControllerStatuses[Controller].u8InterruptMode = (uint8)CAN_INTERRUPT_ENABLED;

            /*
               (CAN050) The function Can_EnableControllerInterrupts shall enable all interrupts that must be enabled according the current software status.
            */
            /* Get the hardware offset for this controller. */
            u8HwOffset = pCanControlerDescriptor->u8ControllerOffset;
            if ( (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 != (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 & pCanControlerDescriptor->u32Options)) ||
                 (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 != (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & pCanControlerDescriptor->u32Options)) )
            {
                if ( (uint8)FLEXCAN_SWF_MB_MASK_U8 == (Can_ControllerStatuses[Controller].u8ControllerSWFlag & (uint8)FLEXCAN_SWF_MB_MASK_U8) )
                {
                    /* Enable INTs from MBs. */
                     for (u8RegCount=(uint8)0; u8RegCount < (uint8)((uint8)CAN_MAXMB_SUPPORTED >> FLEXCAN_MB_SHIFT5BIT_U8) ;u8RegCount++)
                     {
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        REG_WRITE32( Can_IflagImask[u8RegCount][u8HwOffset].u32CanImask,  (uint32)((Can_ControllerStatuses[Controller].u32MBInterruptMask[u8RegCount])));
                     }
               
                    /* Mark flag that tells if at least one INT is enabled. */
                    u8IntSet |= (uint8)1U;
                }
            }

            /*
              (CAN204) The Can module shall track all individual enabling and disabling of interrupts in other functions (i.e. Can_SetControllerMode), so that the correct interrupt enable state can be restored.
            */
#if (CAN_WAKEUP_SUPPORT == STD_ON)
            if ( CAN_CONTROLLERCONFIG_WKPOL_EN_U32 != (CAN_CONTROLLERCONFIG_WKPOL_EN_U32 & pCanControlerDescriptor->u32Options) )
            {
                /* Check the software flag - if set then interrupt must be enabled. */
                if ( FLEXCAN_SWF_WAK_MASK_U8 == (Can_ControllerStatuses[Controller].u8ControllerSWFlag & FLEXCAN_SWF_WAK_MASK_U8) )
                {
                    /* WakeUp - enable the interrupt. */
                     REG_BIT_SET32( FLEXCAN_MCR(u8HwOffset), FLEXCAN_MCR_WAK_MSK_U32);
                    /* Mark flag that tells if at least one INT is enabled. */
                    u8IntSet |= (uint8)1U;
                }
            }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */
            if ( CAN_CONTROLLERCONFIG_BOPOL_EN_U32 != (CAN_CONTROLLERCONFIG_BOPOL_EN_U32 & pCanControlerDescriptor->u32Options))
            {
                /* Check the software flag - if set then interrupt must be enabled. */
                if ( FLEXCAN_SWF_BOFF_MASK_U8 == (Can_ControllerStatuses[Controller].u8ControllerSWFlag & FLEXCAN_SWF_BOFF_MASK_U8) )
                {
                    /* BusOff - enable the interrupt. */
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    REG_BIT_SET32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_BOFFMSK_U32);
                    
                    /* Mark flag that tells if at least one INT is enabled. */
                    u8IntSet |= (uint8)1U;
                }
            }
            if ( CAN_CONTROLLERCONFIG_ERR_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_ERR_EN_U32) )
            {
                /* Check the software flag - if set then interrupt must be enabled. */
                if ( FLEXCAN_SWF_ERR_MASK_U8 == (FLEXCAN_SWF_ERR_MASK_U8 & Can_ControllerStatuses[Controller].u8ControllerSWFlag))
                {
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                     REG_BIT_SET32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_ERRMSK_U32);
                    
                    /* Mark flag that tells if at least one INT is enabled. */
                    u8IntSet |= (uint8)1U;
                }
            }

            /* Check the software flag - if set then warning interrupts are enabled. */
            if ( CAN_CONTROLLERCONFIG_WRNINT_EN_U32 == (pCanControlerDescriptor->u32Options & CAN_CONTROLLERCONFIG_WRNINT_EN_U32) )
            {
                if ( FLEXCAN_SWF_WRNINT_MASK_U8 == (FLEXCAN_SWF_WRNINT_MASK_U8 & Can_ControllerStatuses[Controller].u8ControllerSWFlag) )
                {
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    REG_BIT_SET32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_TWRNMSK_U32);
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    REG_BIT_SET32( FLEXCAN_CTRL(u8HwOffset), FLEXCAN_CTRL_RWRNMSK_U32);
                    /* Mark flag that tells if at least one INT is enabled. */
                    u8IntSet |= (uint8)1U;
                }
            }
        }
        else
        {
            if ( Can_ControllerStatuses[Controller].s8IntDisableLevel > (sint8)0 )
            {
                SchM_Exit_Can_CAN_EXCLUSIVE_AREA_01();
            }
        }
    }


/*================================================================================================*/
/**
* @brief          Local function for canceling low priority msg during Can Write operation.
* @details        This routine is called by:
*                  - Can_FlexCan_Write() from Can_FlexCan.c file.
*                  - Can_AbortMb() from Can.c file.
*
* @param[in]      controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      mbindex index of the message buffer to be canceled
*
* @pre            A Tx message with a higher priority was requested for a MB.
* @post           Inform CanIf about cancellation in case of success.
*
*
*/
#if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (void, CAN_CODE) Can_FlexCan_Cancel( VAR(uint8, AUTOMATIC) controller,
                                      VAR(uint8, AUTOMATIC) mbindex)
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)    u8HwOffset = 0U;
        /* Some temporary variables for registers read/write.  */
        /* Configuration register for current MB. */
        VAR(uint32, AUTOMATIC)   u32MbConfig = 0U;

        /* Tell the interrupt routine that cancellation of this MB is in progress. */
        Can_ControllerStatuses[controller].u32CancelMBIndex = (Can_HwHandleType)mbindex;

        /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

    
        /* Check if the MB is still full. */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        if ( (uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(mbindex))) & (uint32)(FLEXCAN_MBCS_CODE_U32)) == (uint32)(FLEXCAN_MBCS_CODETX_U32 | FLEXCAN_MBCS_CODETXEN_U32) )
        {
    
    #if defined(CAN_USE_MCR_ABORT_ENABLE)
      #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
            /* MB still full -> deactivate it. */      
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u32MbConfig = ( REG_READ32( FLEXCAN_MB((u8HwOffset), (mbindex))) & (uint32)(~FLEXCAN_MBCS_CODE_U32)) | FLEXCAN_MBCS_CODETX_U32;
        #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
      #endif
    #else
            /* MB still full -> cancel it. */     
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u32MbConfig = ( REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(mbindex))) & (uint32)(~FLEXCAN_MBCS_CODE_U32)) | FLEXCAN_MBCS_CODETX_U32 | FLEXCAN_MBCS_CODETXABORT_U32;
    #endif
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* Send command to abort the message */
            REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(mbindex)), (uint32)(u32MbConfig));
            
        }
    }

#endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */

/*================================================================================================*/
/**
* @brief          Process a message buffer abort
* @details        This function write a abort code (b'1001) to MBCS[CODE] field of the MB.
*                This routine is called by:
*                - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Hth - HW-transmit handler
*
* @pre            Driver must be initialized and the current MB transmission should be ready for transmit.
*
*
*/
#if ((CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON))

FUNC(void, CAN_CODE) Can_FlexCan_AbortMb( VAR(Can_HwHandleType, AUTOMATIC) Hth )
{
    VAR(uint8, AUTOMATIC) u8Controller;
    /* Variable for indexing the MBs */
    VAR(uint8, AUTOMATIC) u8MbIndex = 0U;





    u8Controller = (Can_pCurrentConfig->u8ControllerIdMapping)[Hth];

    /* Here, we are positioning to the forst MessageBuffer that has ObjectId = Hth*/
    u8MbIndex = Can_ControllerStatuses[u8Controller].u8FirstTxMBIndex;
    while( (Can_ControllerStatuses[u8Controller].u16MBMapping[u8MbIndex] != Hth) &&
    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
           (u8MbIndex < Can_pCurrentConfig->ControlerDescriptors[u8Controller].u8MaxMBCount) )
    {
        u8MbIndex ++;
    }

#if (CAN_DEV_ERROR_DETECT == STD_ON)
            /* Test if controller is in valid range. */
            if ( (u8Controller >= (uint8)Can_pCurrentConfig->u8ControllersConfigured) ||
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                 (FLEXCAN_NULL_OFFSET_U8 == (Can_pControlerDescriptors[u8Controller].u8ControllerOffset)) )
            {
                Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_ABORT_MB, (uint8)CAN_E_PARAM_CONTROLLER);
            }
            else
            {
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */


                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        #if ((Can_Abort_Only_One_MB==STD_OFF) && (CAN_MULTIPLEXED_TRANSMISSION==STD_ON))
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */

                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                 while( (u8MbIndex < (Can_pControlerDescriptors[u8Controller].u8MaxMBCount)) &&
                    (Can_ControllerStatuses[u8Controller].u16MBMapping[u8MbIndex] == Hth) )
                {
                    Can_FlexCan_Cancel( u8Controller, u8MbIndex);
                    u8MbIndex++;
                }
                #else /* Can_Abort_Only_One_MB==STD_OFF */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
             if( (u8MbIndex < (Can_pControlerDescriptors[u8Controller].u8MaxMBCount)) &&
                    (Can_ControllerStatuses[u8Controller].u16MBMapping[u8MbIndex] == Hth) )
                {
                    Can_FlexCan_Cancel( u8Controller, u8MbIndex);
                }
                #endif   /* Can_Abort_Only_One_MB==STD_ON */

#if (CAN_DEV_ERROR_DETECT == STD_ON)
            }
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
}
#endif /* (CAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */
/*================================================================================================*/
/**
* @brief          Can_FlexCan_Write checks if hardware transmit object that is identified by the HTH is free.
* @details        Can_FlexCan_Write checks if hardware transmit object that is identified by the HTH is free.
*                     Can_Write checks if another Can_Write is ongoing for the same HTH.
*                     a) hardware transmit object is free:
*                         The mutex for that HTH is set to 'signaled' the ID, DLC and SDU are put in a format appropriate for
*                           the hardware (if necessary) and copied in the appropriate hardware registers/buffers.
*                         All necessary control operations to initiate the transmit are done.
*                         The mutex for that HTH is released. The function returns with CAN_OK.
*                     b) hardware transmit object is busy with another transmit request.
*                         The function returns with CAN_BUSY.
*                     c) A preemptive call of Can_Write has been issued, that could not be handled reentrant (i.e. a call with the same HTH).
*                         The function returns with CAN_BUSY the function is non blocking
*                     d) The hardware transmit object is busy with another transmit request for an L-PDU that has lower priority than that for the current request
*                         The transmission of the previous L-PDU is cancelled (asynchronously).
*                         The function returns with CAN_BUSY.
*                         This routine is called by:
*                         - Can_Write() from Can.c file.
*                     Algorithm Description:
*                     Case1: TxMUX supported = ON
*                           Can_Write receive the Hth handle and the PduInfo for transmission. It starts to check from the first MBs of the
*                           current controller to search for a free MB. On the first free MB it stops and place the PduInfo and activate the transmission.
*                           In this case function set CAN_OK for return value and all other functionality is skipped.
*                           If no MB is finded as free then the lowest priority MB is selected for comparing with the priority of the current PduInfo.
*                           If the current PduInfo has a higher priority than the current lower priority (from all MBs) then this lower priority MB is canceled.
*                    Case2: TxMUX supported = OFF
*                          CanWrite() receive the Hth handle and the PduInfo for transmission. It checks if MB with the same index as Hth is free and if yes prepare
*                          and sends the current PduInfo data. If that MB is bussy with another data then it checks the priority between these 2 structures.
*                          Depending by the last evaluation it decides what MB data to cancel.
*
* @param[in]      Hth information which HW-transmit handle shall be used for transmit.
*                 Implicitly this is also the information about the controller to use
*                 because the Hth numbers are unique inside one hardware unit.
* @param[in]      PduInfo Pointer to SDU user memory, DLC and Identifier
*
* @return          Can_ReturnType
* @retval          CAN_OK write command has been accepted
* @retval          CAN_NOT_OK development error occured
* @retval          CAN_BUSY no TX hardware buffer available or preemtive call of Can_Write() that can't be implemented reentrant
*
* @pre            The MB must be configured for Tx.
* @post           Transmit the data or ignore it in case of MB is full with another task.
*
*/
FUNC (Can_ReturnType, CAN_CODE) Can_FlexCan_Write( Can_HwHandleType Hth,
                                               P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfo )
    {

        /* Variable for return status. */
        VAR(Can_ReturnType, AUTOMATIC) eReturnValue = CAN_BUSY;
        /* Variable for keeping the controller Id. */
        VAR(uint8, AUTOMATIC)          u8CtrlId = 0U;
        /* Variable for indexing the MBs. */
        VAR(uint8, AUTOMATIC)          u8MbIndex = 0U;
        /* General purpose variable */
#if ((CAN_MULTIPLEXED_TRANSMISSION == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON))
        /* Variables for keeping track of the lowest prio message. */
        VAR(uint8, AUTOMATIC)          u8MbLprioIndex = 0U;
        VAR(uint32, AUTOMATIC)         u32MbLprioId = 0U;
#endif /* ((CAN_MULTIPLEXED_TRANSMISSION == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)) */
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)          u8HwOffset = 0U;
        /* Variable for determining the IFLAG register for every MB: IFLAGx */
        VAR(uint8, AUTOMATIC)          u8IflagRegIndex = 0U;
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, AUTOMATIC)         u32TempFlag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, AUTOMATIC)         u32IflagReg = 0U;
        /* Variable for storing the ID of the MB from MB structure. */
        VAR(uint32, AUTOMATIC)         u32MbMessageId = 0U;
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, AUTOMATIC)         u32MbConfig = 0U;
        /* Variable for byte index of the MB data. */
        VAR(uint8, AUTOMATIC)          u8MbDataByte = 0U;
        /* Get the Controller ID for the current Hth MB. */
        u8CtrlId = (Can_pCurrentConfig->u8ControllerIdMapping)[Hth];


#if ((CAN_MULTIPLEXED_TRANSMISSION == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON))
        /* Define variable for keeping track of the lowest prio message. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8MbLprioIndex = Can_pCurrentConfig->ControlerDescriptors[u8CtrlId].u8MaxMBCount - (uint8)0x1U;
#endif /* ((CAN_MULTIPLEXED_TRANSMISSION == STD_ON) && (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)) */

        /* Get the hardware offset for this controller. Note that hardware offset may not be the same with the controller index from the 'Can_ControlerDescriptorType' structure. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[u8CtrlId].u8ControllerOffset;

        /* Calculate the MB index. When transmit multiplex is enabled search any MB to be free, MBs that have the same ObjectID
        When Multiplex is disabled ,you can have more than one controller, everyone having MBs configured. In this case the index of the MB is different from the
                one in the plugin */
        u8MbIndex = Can_ControllerStatuses[u8CtrlId].u8FirstTxMBIndex;
        while( (Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8MbIndex] != Hth) &&
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
               (u8MbIndex < Can_pControlerDescriptors[u8CtrlId].u8MaxMBCount) )
        {
            u8MbIndex ++;
        }
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
        /* Need to find a free MB for transmission. This do-while block is executed only when multiplex transmission is ON because the data can be stored in any MB
                that has the same ObjectID. */
        do
        {
#endif /* (CAN_MULTIPLEXED_TRANSMISSION == STD_ON) */

            /* Is the MB empty?
                 This test is a bit early; the u32TxGuard is not set yet and someone else can grab this MB before we reserve it
                 but it saves setting the guard on full or cancelled MBs only to discover they are not empty and clearing the guard again. */
                  /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */

            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            if ( FLEXCAN_MBCS_CODETX_U32 == (uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32)) )

            {
                /*
                   (CAN212) The function Can_Write shall perform following actions if the hardware transmit object is free: The mutex for that HTH is set to 'signaled';
                         the ID, DLC and SDU are put in a format appropriate for the hardware; All necessary control operations to initiate the transmit are done;
                         The mutex for that HTH is released; The function returns with CAN_OK.
                */

                /* Calculate the index of the IFLAG register and u32TxGuard (index=0 for MB32...MB63, index=1 for MB0...MB31, index=2 for MBO64 ... 96). */
                u8IflagRegIndex = (uint8)((uint8)u8MbIndex >> FLEXCAN_MB_SHIFT5BIT_U8);
                                    
                /* Get the content of IFLAG register for which corresponds this MB. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                u32IflagReg = REG_READ32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag);
    
                /* Calculate the bit in the IFLAG register. */
                u32TempFlag = ((uint32)0x01U) << ((uint32)u8MbIndex & FLEXCAN_MASK_32BITS_U32);
                
                SchM_Enter_Can_CAN_EXCLUSIVE_AREA_02();

                /* Test the GUARD MASK and the INTERRUPT FLAG.
                     Cannot operate on locked out MBs (re-entry).. also cannot operate on MBs for which the Tx confirmation has not been sent yet.
                     Below is read-modify-write cycle for u32TxGuard flag which may be interrupted -> must use SchM_Enter_Can_CAN_EXCLUSIVE_AREA_XX() for preventing broken u32TxGuard value. */

                if ( (uint32)0x0U == (Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] & u32TempFlag) )
               {
                    /* This MB is not signaled as used by another message. */
                    if ( (uint32)0x0U == (u32IflagReg & u32TempFlag) )
                    {
                        /* Interrupt flag is not set for this MB this meaning MB is not in progress. */

                        /* The mutex for that HTH is set to 'signaled': The guard is 0, the MB is not locked out at the moment -> lock it out. */

                        Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] |= u32TempFlag;


                        /* u32TxGuard was set without any risk of broken data - now can free the Critical section. */
                        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_02();

                        /* Is the MB still empty? */
                         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        if ( FLEXCAN_MBCS_CODETX_U32 == (uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32)))
                        {
                            u32MbMessageId = (uint32)PduInfo->id;
                            u32MbConfig = (FLEXCAN_MBCS_CODETX_U32 | FLEXCAN_MBCS_CODETXEN_U32 | FLEXCAN_MBCS_SRR_U32 | (((uint32)PduInfo->length) << (uint32)16U));

                            /* Set-up the MB content for Tx. Remember the PduId for reporting when the frame is transmitted. */
                            Can_ControllerStatuses[u8CtrlId].u32TxPduId[u8MbIndex] = PduInfo->swPduHandle;

#if (CAN_EXTENDEDID == STD_ON)
                            if ( (u32MbMessageId & FLEXCAN_MBC_ID_IDE_U32) != (uint32)0U)
                            {
                                /* Set the IDE bit in the MBCS register of the MB */
                                u32MbConfig |= FLEXCAN_MBCS_IDE_U32;
                                /* Clear the MSB bit of the id - this is used for sending embedded information by CanIf to Can to say if it is an extended or standard message type. */
                                u32MbMessageId &= (~FLEXCAN_MBC_ID_IDE_U32);
                            }
                            else
                            {
#endif /* (CAN_EXTENDEDID == STD_ON) */
                                /* Standard ID - need to shift left 18 bits. */
                                u32MbMessageId <<= FLEXCAN_STANDARD_ID_SHIFT_U32;
#if (CAN_EXTENDEDID == STD_ON)
                            }
#endif /* (CAN_EXTENDEDID == STD_ON) */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex)), (uint32)((u32MbMessageId) | ((REG_READ32(FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex)))) & 0xE0000000U) ));
                         
                            /* Copy the data into the MB memory. The driver will not read from a null pointer SDU. */
                            for ( u8MbDataByte = (uint8)0U; u8MbDataByte < PduInfo->length; u8MbDataByte++)
                            {
                                 /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                 REG_WRITE8(FLEXCAN_MB_DATA((u8HwOffset), (uint32)(u8MbIndex), (uint32)(u8MbDataByte)), (uint8)((PduInfo->sdu)[u8MbDataByte]));
                               
                            }

                            /* Transmit the Data - now the data should be on Can Bus. Configure the DLC. */
                             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                             REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex)), (uint32)(u32MbConfig));
                            

                            /* When the Abort feature is enabled (AEN in MCR is asserted), after the Interrupt Flag is
                            asserted for a MB configured as transmit buffer, the MB is blocked, therefore the CPU is not able to update
                            it until the Interrupt Flag be negated by CPU. It means that the CPU must clear the corresponding IFLAG
                            before starting to prepare this MB for a new transmission or reception.
                            u32TxGuard is a software flag and IFLAG are hardware flags */

                            /* Clear the guard, end of critical section. */

                            Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] &= (uint32)(~u32TempFlag);

                            /* Set-up return value to indicate sucessful Tx.
                                The Transmit succesufull operation is signaled to CanIf when IFLAG bit will be handled by polling/interrupt routine (Can_FlexCan_ProcessRx).*/
                            eReturnValue = CAN_OK;
                        }
                        else
                        /* MB not empty anymore, preempting code has grabbed it before we managed to set the guard bit. Clear the guard bit. */
                        {
                            /*
                               (CAN213) The function Can_Write shall perform no actions if the hardware transmit object is busy with another transmit request for an L-PDU that has higher priority than that for the current request:
                                  - The transmission of the L-PDU with higher priority shall not be cancelled and the function Can_Write is left without any actions.
                                  - The function Can_Write shall return CAN_BUSY.
                            */

                            Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] &= (uint32)(~u32TempFlag);


                            /* MB not TX empty anymore, preempting code has grabbed it before we managed to set the guard bit. Clear the guard, end of critical section. */
                            eReturnValue = CAN_BUSY;
                        }
                    }
                    else /* else of "if((uint32)0x0U==(u32IflagReg&u32TempFlag))" */
                    /* MB is locked because it has the IFLAG bit set. */
                    {
                        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_02();
                        /*
                        The fact that the return value of the function is the same irrespective of whether the MB is locked out or busy with a lower prio message is a deficiency in the AutoSAR spec.
                        CanIf has no way of telling whether the message was cancelled or not in the special case and a priority inversion can occur.
                        */
                        /*
                           (CAN214) The function Can_Write shall return CAN_BUSY if a preemptive call of Can_Write has been issued, that could not be
                                    handled reentrant (i.e. a call with the same HTH).
                        */
                        eReturnValue = CAN_BUSY;
                    }
                }
                else /* else of "if((uint32)0x0U==(Can_ControllerStatuses[u8CtrlId].u32TxGuard[0]&u32TempFlag))" */
                {
                    /* MB is locked out because software flag (Guart bit) is set. */
                    eReturnValue = CAN_BUSY;

                    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_02();
#if ((CAN_HW_TRANSMIT_CANCELLATION == STD_ON) && (CAN_MULTIPLEXED_TRANSMISSION == STD_ON))
                    /* Do not Cancel the locked out message when TXMUX is enabled. */
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    u8MbLprioIndex = Can_pControlerDescriptors[u8CtrlId].u8MaxMBCount;
                    break;
#endif /* ((CAN_HW_TRANSMIT_CANCELLATION == STD_ON) && (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)) */
                }

            }
            else /* else of "if(FLEXCAN_MBCS_CODETX_U32==(uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32)))" */
            /* MB is not empty */
            {
                /*
                   (CAN286) The Can module shall initiate a cancellation, when all available hardware transmit objects are busy and an L-PDU with
                            higher priority is requested to be transmitted.
                */

#if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
                /* Keep track of the lowest prio message (highest ID). */
                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                u32MbMessageId = (((uint32)REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)FLEXCAN_MBCS_IDE_U32) != (uint32)FLEXCAN_MBCS_IDE_U32) ? /* condition to test */
                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                      (uint32)((REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_STANDARD_U32)) >> (uint32)(18U)) : /* value if condition is true */
                                       /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                      (uint32)(REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_EXTENDED_U32)); /* value if condition is false */

  #if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
                    /*
                       (CAN402) The Can module shall support multiplexed transmission mechanisms for devices where either
                                - Multiple transmit hardware objects, which are grouped to a transmit entity can be filled over the same register set,
                                and the microcontroller stores the L-PDU into a free buffer autonomously,
                                or
                                - The Hardware provides registers or functions to identify a free transmit hardware object within a transmit entity.
                        (CAN403) The Can module shall support multiplexed transmission for devices, which send L-PDUs in order of L-PDU priority.
                    */

                /* @violates @ref Can_Flexcan_c_REF_1 Violates MISRA 2004 Advisory Rule 12.1, se of mixed mode arithmetic. */
                if ( ((uint32)u32MbLprioId < (uint32)u32MbMessageId)
    #if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON)
                      || ((uint32)u32MbLprioId == (uint32)u32MbMessageId)
    #endif /* (CAN_IDENTICAL_ID_CANCELLATION == STD_ON) */
                    )
                {
                    /* Create a copy of the lowest priority ID and the index of MB which holds it. */
                    /* MISRA-C:2004 12.1 VIOLATION: Refer to REF 1 above */
                    u32MbLprioId = u32MbMessageId;
                    u8MbLprioIndex = u8MbIndex;
                }

  #else /* (CAN_MULTIPLEXED_TRANSMISSION == STD_OFF) */
                /* If cancellation is enabled and TxMux is disabled, make now the cancellation if it's the case.
                     Check the priority of the current message that is already in the MB (temp_id) with the priority of the new message (PduInfo). */
                if ( ((uint32)u32MbMessageId > (uint32)PduInfo->id)
    #if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON)
                    || ((uint32)u32MbMessageId == (uint32)PduInfo->id)
    #endif
                    )
                {
                    /*
                       (CAN215) The function Can_Write shall perform following actions if the hardware transmit object is busy with another
                    transmit request for an L-PDU that has lower priority than that for the current request:
                    - The transmission of the L-PDU with lower priority shall be cancelled (asynchronously).
                    - The function CAN_Write shall return CAN_BUSY.
                    */
                    Can_FlexCan_Cancel( u8CtrlId, u8MbIndex);
                }
  #endif /* (CAN_MULTIPLEXED_TRANSMISSION == STD_OFF) */

#endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */

                /* MB is not empty. */
                eReturnValue = CAN_BUSY;
            }

#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
            /* Increment the MB index. */
            u8MbIndex++;

        } while ( (Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8MbIndex] == Hth) && (CAN_BUSY == eReturnValue));
#endif /* (CAN_MULTIPLEXED_TRANSMISSION == STD_ON) */


#if ((CAN_HW_TRANSMIT_CANCELLATION == STD_ON) && (CAN_MULTIPLEXED_TRANSMISSION == STD_ON))
        /* Was the message scheduled for transmission? */
        if ( CAN_OK != eReturnValue )
        {
            /* Did the search find a lower priority message? */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            if ( u8MbLprioIndex < Can_pControlerDescriptors[u8CtrlId].u8MaxMBCount)
            {
                /* Calculate the index of the u32TxGuard (index = 0 for MB32...MB63, index = 1 fro MB0...MB31). */

                    u8IflagRegIndex = (uint8)(u8MbLprioIndex >> FLEXCAN_MB_SHIFT5BIT_U8) ;
                    /* Calculate the iflag value. */
                   u32TempFlag = ((uint32)0x01U) << ((uint32)u8MbLprioIndex & FLEXCAN_MASK_32BITS_U32);

                /* Cancel the lowest prio message providing it is of lower priority than the current message.
                  Lock the lowest prio MB out, no need to check if it is already locked (it was not locked during the search so it cannot be locked now). */


                    Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] |= u32TempFlag;


                /* @violates @ref Can_Flexcan_c_REF_1 Violates MISRA 2004 Advisory Rule 12.1, se of mixed mode arithmetic. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* Check if the current message is standard to shift accordingly. */
                u32MbMessageId = ((REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbLprioIndex))) & (uint32)FLEXCAN_MBCS_IDE_U32) != (uint32)FLEXCAN_MBCS_IDE_U32) ? /* condition to test */
                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                    (uint32)((REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbLprioIndex))) & (uint32)(FLEXCAN_MBID_ID_STANDARD_U32)) >> (uint32)(18U)) : /* value if condition is true */
                                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                    (uint32)(REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbLprioIndex))) & (uint32)(FLEXCAN_MBID_ID_EXTENDED_U32)); /* value if condition is false */

                /* Check the priority of the current message is greater that the one requested to send. */
                if ( ((uint32)u32MbMessageId > (uint32)PduInfo->id)
  #if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON)
                    || ((uint32)u32MbMessageId == (uint32)PduInfo->id)
  #endif
                    )
                {
                    /* Message currently in the MB has lower priority, cancel it.
                          If the message is transmitted in the meantime, the MB will be blocked until the interrupt flag is cleared.
                          However an interrupt may come in reaction to the flag and send Tx confirmation -> Can_Cancel must check that. */
                    Can_FlexCan_Cancel( u8CtrlId, u8MbLprioIndex);
                }

                /* Unlock the MB u32TxGuard. */

                    Can_ControllerStatuses[u8CtrlId].u32TxGuard[u8IflagRegIndex] &= (uint32)(~u32TempFlag);

            }
        }
#endif /* ((CAN_HW_TRANSMIT_CANCELLATION == STD_ON) && (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)) */

        return (eReturnValue);
    }


/*================================================================================================*/
/**
* @brief          Local function for calling notification function to notify upper layer during Can_MainFunction_Write if polling is selected or from ISR when Interrupt mode selected.
* @details        Processes Tx interrupt flags.
*               This routine is called by:
*                - Can_IPW_ProcessTx() from Can.c file.
*                - Can_FlexCan_MainFunctionWrite() from Can_FlexCan_IPW.c file.
*                - Can_IsrFC##FC##_UNI() / Can_IsrFC##FC##_##Name() from Can_Irq.c file.
*
* @param[in]      controller CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      mbindex_start first MB to process.
* @param[in]      mbindex_end last MB to process.
*
* @pre            MB is configured for Tx.
* @post           CanIf is informed with cancellation or transmit success.
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (void, CAN_CODE) Can_FlexCan_ProcessTx( CONST(uint8, AUTOMATIC) controller,
                                          CONST(uint8, AUTOMATIC) mbindex_start,
                                          CONST(uint8, AUTOMATIC) mbindex_end )
    {
#if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)    
        /* Unique identifier of a PDU within a software module */
        VAR(PduIdType, AUTOMATIC) u32PduId;
        /* Store the basic information about a PDU */
        VAR(PduInfoType, AUTOMATIC) CbkPduInfo;
        /* Pointer to the MBs structure configuration. */
        VAR(Can_PtrMBConfigContainerType, AUTOMATIC) pCanMbConfigContainer = NULL_PTR;
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, AUTOMATIC)           u32MbConfig = 0U;
        /* Variable for storing the data. */
        VAR(uint8, AUTOMATIC)            u8CanMbData[8]={0, 0, 0, 0, 0, 0, 0, 0};
        /* Index for data byte of MB. */
        VAR(uint8, AUTOMATIC)            u8DatabyteIndex = 0U;
    
#endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */    
        /* Variable for indexing the MBs. */
        VAR(uint8, AUTOMATIC)            u8MbIndex = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)            u8HwOffset = 0U;
        /* Variable for determining the IFLAG register for every MB: IFLAGx */
        VAR(uint8, AUTOMATIC)            u8IflagRegIndex = 0U;
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, AUTOMATIC)           u32TempFlag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, AUTOMATIC)           u32IflagReg = 0U;

#if (CAN_TXPOLL_SUPPORTED == STD_OFF)
        /* Variable for storing the value of IMASKx register. */
        VAR(uint32, AUTOMATIC)           u32ImaskReg = 0U;
#endif

#if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)    
        /* Get the address of the MBConfigContainer in local pointer */
        pCanMbConfigContainer = &(Can_pCurrentConfig->MBConfigContainer);       
#endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */   


        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /* Loop through all MBs to process. */
        for ( u8MbIndex = mbindex_start; u8MbIndex <= mbindex_end; u8MbIndex++)
        {
            /* Calculate the index of the IFLAG/IMASK register. */
            u8IflagRegIndex = (uint8)((uint8)u8MbIndex >> FLEXCAN_MB_SHIFT5BIT_U8) ;
            
            /* Get the content of IFLAG register for which corresponds this MB. */
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u32IflagReg = REG_READ32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag);

            /* Calculate the bit in the IFLAG/IMASK register allocated to a MB */
            u32TempFlag = ((uint32)0x01U) << ((uint32)u8MbIndex & FLEXCAN_MASK_32BITS_U32);
            
            /* Check the interrupt flag of the current MB. */
            if ( (uint32)0x0U != (u32IflagReg & u32TempFlag) )
            {
#if (CAN_TXPOLL_SUPPORTED == STD_OFF)
                /*Get the content of IMASK register for which corresponds this MB. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                u32ImaskReg = REG_READ32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanImask);

                /* Check for spurious interrupt. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
                if ( ((uint32)CAN_CONTROLLERCONFIG_TXPOL_EN_U32 == (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 & Can_pControlerDescriptors[controller].u32Options) )
                || ((uint32)u32TempFlag == (u32ImaskReg & u32TempFlag)) )               
                {               
#endif
                    /* The interrupt flag is set, message was either transmitted or cancelled.
                        This code does not check whether the u32TxGuard is set.
                        It does not have to do the check as it only operates on MBs with the interrupt flag set and CanWrite does not
                        operate on MBs which have the interrupt flag set.
                        Set the u32TxGuard. */
                    /*
                        (CAN031) The function Can_MainFunction_Write shall perform the polling of TX confirmation and TX cancellation confirmation when CanTxProcessing is set to POLLING.
                    */  

        #if defined(CAN_USE_MCR_ABORT_ENABLE)
            #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    /* @violates @ref Can_Flexcan_c_REF_14 MISRA 2004 Required Rule,Side effects of && and || */
                    if((((uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32))) == FLEXCAN_MBCS_CODETX_U32) && ( (Can_HwHandleType)u8MbIndex == Can_ControllerStatuses[controller].u32CancelMBIndex))          
            #else
                #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
        #endif
        #else
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    switch ( (uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32)) )
        #endif
                    {
    #if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
                    /* The frame was aborted (cancelled). */

        #if defined(CAN_USE_MCR_ABORT_ENABLE)
            #if (CAN_USE_MCR_ABORT_ENABLE== STD_ON)
            /*  {workaround - errata  specific code} */
            #else
                #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
            #endif
        #else
                        case ( FLEXCAN_MBCS_CODETX_U32 | FLEXCAN_MBCS_CODETXABORT_U32):
                        {
        #endif
                            /* The interrupt flag is set, message was either transmitted or cancelled.
                                This code does not check whether the u32TxGuard is set.
                                It does not have to do the check as it only operates on MBs with the interrupt flag set and CanWrite does not
                                operate on MBs which have the interrupt flag set.
                                Set the u32TxGuard. */

                                Can_ControllerStatuses[controller].u32TxGuard[u8IflagRegIndex] |= u32TempFlag;



                            /* Check if Can_Write is currently trying to cancel this MB. If so, tell it that there is no need as the MB has just transmitted (or cancelled). */
                            if ( (Can_HwHandleType)u8MbIndex == Can_ControllerStatuses[controller].u32CancelMBIndex)
                            {
                                Can_ControllerStatuses[controller].u32CancelMBIndex = pCanMbConfigContainer->uMessageBufferConfigCount;
                            }

                            /* Read Control and Status Register of the MB. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32MbConfig = (uint32)REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex)));

                            /* Transfer the DLC. */
                            /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            CbkPduInfo.SduLength = (uint8)((u32MbConfig & FLEXCAN_MBCS_LENGTH_U32) >> FLEXCAN_MBCS_LENGTH_SHIFT_U32);

                            /*
                            (CAN276) The function Can_Write shall store the swPduHandle that is given inside the parameter PduInfo until the Can module
                                calls the CanIf_TXConfirmation for this request where the swPduHandle is given as parameter.
                            */
                            u32PduId = Can_ControllerStatuses[controller].u32TxPduId[u8MbIndex];

                            /*
                            (CAN059) Data mapping by CAN to memory is defined in a way that the CAN data byte which is sent out first is array element 0,
                                the CAN data byte which is sent out last is array element 7.
                            */
                            for ( u8DatabyteIndex = (uint8)0U; u8DatabyteIndex < CbkPduInfo.SduLength; u8DatabyteIndex++)
                            {
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                u8CanMbData[u8DatabyteIndex] = REG_READ8(FLEXCAN_MB_DATA((u8HwOffset), (uint32)(u8MbIndex), (u8DatabyteIndex))) ;
                            }

                            /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            CbkPduInfo.SduDataPtr= u8CanMbData;

                            /* Clear the interrupt flag - w1c. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */        
                            REG_WRITE32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag, u32TempFlag);  
    
                            /* Clear the cancellation code. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex)), (uint32)((u32MbConfig & (uint32)(~FLEXCAN_MBCS_CODE_U32)) | FLEXCAN_MBCS_CODETX_U32));  

                            /* Release the MB, from now on the MB is free for Tx -> Clear u32TxGuard. */
                            Can_ControllerStatuses[controller].u32TxGuard[u8IflagRegIndex] &= (uint32)(~u32TempFlag);

                            /*
                            (CAN058) The Can module interacts among other modules (eg. Diagnostic Event Manager (DEM), Development Error Tracer (DET)) with the CanIf module in a direct way.
                                The driver only sees the CanIf module as origin and destination.
                            */
                            /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            /* @violates @ref Can_Flexcan_c_REF_19  Violates MISRA2004 rule 11.4, Cast should not be performed between a pointer to object type and a different pointer */

                            CanIf_CancelTxConfirmation(u32PduId , (const PduInfoType*)&CbkPduInfo);

        #if defined(CAN_USE_MCR_ABORT_ENABLE)
            #if (CAN_USE_MCR_ABORT_ENABLE== STD_ON)
                   /*  {workaround - errata  specific code} */
            #else
                #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
        #endif
        #else
                        }
                            break;
        #endif

    #endif /* (CAN_HW_TRANSMIT_CANCELLATION == STD_ON) */


        #if defined(CAN_USE_MCR_ABORT_ENABLE)
            #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
                    }
                        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                        /* @violates @ref Can_Flexcan_c_REF_14 MISRA 2004 Required Rule,Side effects of && and || */
                        else if((((uint32)(REG_READ32( FLEXCAN_MB((u8HwOffset), (u8MbIndex))) & (uint32)(FLEXCAN_MBCS_CODE_U32))) == FLEXCAN_MBCS_CODETX_U32) && ((Can_HwHandleType)u8MbIndex != Can_ControllerStatuses[controller].u32CancelMBIndex))
            #else
                #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
        #endif
        #else
                            /* Frame was transmitted */
                        case ( FLEXCAN_MBCS_CODETX_U32 ):
        #endif
                        {
                            /* Clear the interrupt flag - w1c. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag, u32TempFlag);  

                            /*
                                (CAN058) The Can module interacts among other modules (eg. Diagnostic Event Manager (DEM), Development Error Tracer (DET)) with the CanIf module in a direct way.
                                        The driver only sees the CanIf module as origin and destination.
                            */
                            CanIf_TxConfirmation( Can_ControllerStatuses[controller].u32TxPduId[u8MbIndex]);
                        }

        #if defined(CAN_USE_MCR_ABORT_ENABLE)
            #if (CAN_USE_MCR_ABORT_ENABLE == STD_ON)
                    else /* error condition, this should never occur */
                    {
                            /* This case should never occurs. */
                            Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_DEFAULT);
                            /* Compiler_Warning: This warning is thrown due to the infinite loop while(1) in the
                                                    Cer_ReportError() function implementation */
                    }
        #else
            #error : the define CAN_USE_MCR_ABORT_ENABLE must not be STD_OFF
            #endif
        #else
                            break;
                        default:
                            /* This case should never occurs. */
                            Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_WRITE, (uint8)CAN_E_DEFAULT);
                            /* Error condition, this should never occur. */
                            /* Compiler_Warning: This warning is thrown due to the infinite loop while(1) in the
                                                Cer_ReportError() function implementation */

                    } /* end switch */
        #endif
        
/*Support for spurious interrupt*/
#if (CAN_TXPOLL_SUPPORTED == STD_OFF)
                }
                else
                {
                    /*Clear interrupt status flag when spurious interrupt is detected*/
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    REG_WRITE32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag, u32TempFlag);
                }
#endif
            } /*if ( (uint32)0x0U != (u32IflagReg & u32TempFlag) )*/
        } /*for...*/
    }/*Can_FlexCan_ProcessTx*/


/*================================================================================================*/
/**
* @brief          Service to perform the polling of TX confirmation and TX cancellation confirmation
* @details        This routine is called by:
*               - Can_MainFunction_Write() from Can.c file.
*
* @pre            The controller must be configured for transmit in polling mode and at least one MB is configured for Tx.
* @post           Process the transmission data in case of availability.
*
*
*/
#if (CAN_TXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_FlexCan_MainFunctionWrite(void)
    {

        /* Variable for indexing the controllers. */
        VAR(uint8, AUTOMATIC)   u8CtrlIndex = 0U;
        /* First MB to process. */
        VAR(uint8, AUTOMATIC)   u8MbFirst = 0U;
        /* Last MB to process. */
        VAR(uint8, AUTOMATIC)   u8MbLast = 0U;

        /* Loop through all configured controller descriptors. */
        for ( u8CtrlIndex = 0U; u8CtrlIndex < (uint8)Can_pCurrentConfig->u8ControllersConfigured; u8CtrlIndex++)
        {
            /* Check whether the controller is enabled and whether Tx polling is used for this controller. */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            if ( (FLEXCAN_NULL_OFFSET_U8 != Can_pControlerDescriptors[u8CtrlIndex].u8ControllerOffset) &&
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                 ((uint32)0U != (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 & (Can_pControlerDescriptors[u8CtrlIndex].u32Options))) &&
                 /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                 ((uint8)0U != (Can_pControlerDescriptors[u8CtrlIndex].u8MaxMBCount)) )
            {
                /* Init indexes that should be parsed for polling mode for current controller.
                  "u8FirstTxMBIndex" and "u8MaxMBCount" are updated considering RxFifo. */
                u8MbFirst = (uint8)Can_ControllerStatuses[u8CtrlIndex].u8FirstTxMBIndex;
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                u8MbLast = (uint8)Can_pControlerDescriptors[u8CtrlIndex].u8MaxMBCount - (uint8)1U;

                /* Enabled & TxPoll used. Process Tx interrupt flags. Start with the first Tx MB and finish at the last used MB. */
                Can_FlexCan_ProcessTx( (uint8)u8CtrlIndex, (uint8)u8MbFirst, (uint8)u8MbLast );
            }
        }
    }

/*================================================================================================*/
/**
* @brief          Function called at fixed cyclic time, with polling of all the MessageBuffer referenced to writepoll
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @api
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (void, CAN_CODE) Can_FlexCan_MainFunctionMultipleWritePoll( VAR(uint8, AUTOMATIC) writepoll)
    {
        /* Variable for indexing the controllers. */
        VAR(uint8, AUTOMATIC)  u8CtrlId = 0U;
        /* First MB to process. */
        VAR(uint8, AUTOMATIC)  u8MbIndex = 0U;
        /* Can Object ID to process. */
        VAR(uint32, AUTOMATIC)  u32ObjectId = 0U;
        /* Can Process Index of MB for the controller to process. */
        VAR(uint8, AUTOMATIC)  u8TxProcessIndex[CAN_MAXCTRL_SUPPORTED];

        if ( NULL_PTR != Can_pCurrentConfig )
        {
            #if (CAN_DEV_ERROR_DETECT == STD_ON)
                /* Test whether the driver is already initialised. */
                if ( CAN_UNINIT == Can_eDriverStatus )
                {
                    /*
                       (CAN179) If development error detection for the module Can is enabled: The function Can_MainFunction_Write shall raise
                               the error CAN_E_UNINIT if the driver is not yet initialized.
                    */
                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_E_UNINIT);
                }
                else
                {
            #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                    /* initialise the u8TxProcessIndex for the configured controller. */
                    for ( u8CtrlId = (uint8)0U; u8CtrlId < CAN_MAXCTRL_SUPPORTED; u8CtrlId++)
                    {
                        u8TxProcessIndex[u8CtrlId] = 0U;
                        #if (CAN_RXFIFO_ENABLE == STD_ON)
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                        if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == ((uint32)(Can_pControlerDescriptors[u8CtrlId].u32Options) & CAN_CONTROLLERCONFIG_RXFIFO_U32) )
                        {
                            /* Processing MB must start from the first MB not used by the Rx Fifo. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            u8TxProcessIndex[u8CtrlId] = Can_pControlerDescriptors[u8CtrlId].u8RxFiFoUsedMb;
                            
                        }
                        #endif /* #if (CAN_RXFIFO_ENABLE == STD_ON) */
                    }
                    /* Parse through all TX configured message buffer */
                    for ( u8MbIndex = (uint8)0U; u8MbIndex < (uint8)Can_pCurrentConfig->MBConfigContainer.uMessageBufferConfigCount; u8MbIndex++)
                    {
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        u8CtrlId = Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u8ControllerId;
                        /*  Poll only the Tx MB which is referenced by Can_FlexCan_MainFunctionMultipleWritePoll */
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        if ((writepoll == Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u32CanMainFuncRWPeriodRef) &&
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            (FLEXCAN_NULL_OFFSET_U8 != Can_pControlerDescriptors[u8CtrlId].u8ControllerOffset) &&
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            ((uint32)0U != (CAN_CONTROLLERCONFIG_TXPOL_EN_U32 & (Can_pControlerDescriptors[u8CtrlId].u32Options))) &&
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            (CAN_TRANSMIT == (Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].eMBType )))
                        {
                            /* CanOnjectID of the polled MB */
                             /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            u32ObjectId = (Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u32HWObjID );
/* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            while ((u32ObjectId != (Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8TxProcessIndex[u8CtrlId]])) && (u8TxProcessIndex[u8CtrlId] < (Can_pControlerDescriptors[u8CtrlId].u8MaxMBCount)))
                            {
                                /* increase the u8TxProcessIndex to check next u32ObjectId present */
                                u8TxProcessIndex[u8CtrlId]++;
                            }
                            if (u32ObjectId == Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8TxProcessIndex[u8CtrlId]])
                            {
                                /* Enabled & TxPoll used : process Tx interrupt flags, */
                                Can_FlexCan_ProcessTx( (uint8)u8CtrlId, (uint8)u8TxProcessIndex[u8CtrlId], (uint8)u8TxProcessIndex[u8CtrlId]);
                                /* increase the u8TxProcessIndex to check next u32ObjectId present */
                                u8TxProcessIndex[u8CtrlId]++;
                            }
                        }
                    }
            #if (CAN_DEV_ERROR_DETECT == STD_ON)
                }
            #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
        }
    }
#endif /* (CAN_TXPOLL_SUPPORTED == STD_ON) */



/*================================================================================================*/
/**
* @brief          Local function for calling notification function to notify upper layer during Can_MainFunction_Read if polling is selected or from ISR when Interrupt mode selected.
* @details        Processes Rx interrupt flags.
                  This routine is called by:
                    - Can_IPW_ProcessRx() from Can.c file
                    - Can_FlexCan_MainFunctionRead() from Can_FlexCan.c file
                    - Can_IsrFC##FC##_UNI() / Can_IsrFC##FC##_##Name() from Can_Irq.c file
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      mbindex_start first MB to process
* @param[in]      mbindex_end last MB to process
*
* @pre            MB is configured for Rx.
* @post           Inform CanIf in case a data frame was received.
*
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (void, CAN_CODE) Can_FlexCan_ProcessRx( CONST(uint8, AUTOMATIC) controller,
                                          CONST(uint8, AUTOMATIC) mbindex_start,
                                          CONST(uint8, AUTOMATIC) mbindex_end )
{

        VAR(uint32, AUTOMATIC) u32TimeoutCount = 0U;/* Timeout counter. */       
        /* Variable for indexing the MBs. */
        VAR(Can_HwHandleType, AUTOMATIC)      u8MbIndex = 0U;
        /* Number of data bytes. */
        VAR(uint8, AUTOMATIC)      u8MbDataLength = 0U;
        /* Physical data bytes. */
        VAR(uint8, AUTOMATIC)      u8CanMbData[8]={0, 0, 0, 0, 0, 0, 0, 0};
        /* Index for data byte of MB. */
        VAR(uint8, AUTOMATIC)      u8DatabyteIndex = 0U;
        /* Variable for storing the Hrh. */
        VAR(Can_HwHandleType, AUTOMATIC)      u32MbHrh = 0U;
        /* Variables for storing the CanID. */
        VAR(Can_IdType, AUTOMATIC) u32MbMessageId = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)      u8HwOffset = 0U;
        /* Variable for determining the IFLAG register for every MB: IFLAGx. */
        VAR(uint8, AUTOMATIC)      u8IflagRegIndex = 0U;
        /* Variable for determining the mash bit in the IFLAGx register for current MB. */
        VAR(uint32, AUTOMATIC)     u32TempFlag = 0U;
        /* Variable for storing the value of IFLAG register. */
        VAR(uint32, AUTOMATIC)     u32IflagReg = 0U;
        /* Variable for storing the ConfigReg of the MB. */
        VAR(uint32, AUTOMATIC)     u32MbConfig = 0U;
        #if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Variable for detect overflow event */
        VAR(boolean, AUTOMATIC)      bMbOver = (VAR(boolean, AUTOMATIC))FALSE;  
        #endif
#if (CAN_RXFIFO_ENABLE == STD_ON)        
        /* Is set when process an warning or overflow for RxFifo only. */
        VAR(uint8, AUTOMATIC)      u8MbNodata = 0U;
#endif     

#if (CAN_RXPOLL_SUPPORTED == STD_OFF)
        /* Variable for storing the value of IMASKx register. */
        VAR(uint32, AUTOMATIC)     u32ImaskReg = 0U;
#endif



        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /*
        Loop through all MBs to process.
            Phase1: If RXFifo is activated Overflow and Warning interrupts are processed separated because implies no data transfer.
            Phase2: Frame Available Fifo and all other MB interrupts are processes after and have the logic of normal data read from buffer and transmit to CanIf.
        */
        u8MbIndex=mbindex_start;
        while(u8MbIndex <= mbindex_end)
        {
            /* Calculate the Index of the IFLAG register. */
            u8IflagRegIndex = (uint8)((uint8)u8MbIndex >> FLEXCAN_MB_SHIFT5BIT_U8);
            
            /* Get the content of IFLAG register for which corresponds this MB. */                
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u32IflagReg = REG_READ32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag);

            /* Calculate the Flag value. */
            u32TempFlag = ((uint32)0x1U) << ((uint32)u8MbIndex & FLEXCAN_MASK_32BITS_U32);

            /* Check the interrupt flag. */
            if ( (uint32)0x0U != (u32IflagReg & u32TempFlag) )
            {   
#if (CAN_RXPOLL_SUPPORTED == STD_OFF)
                /*Get the content of IMASK register for which corresponds this MB. */
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                u32ImaskReg = REG_READ32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanImask);

                /* Check for spurious interrupt in Interrupt mode */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
                if ( ((uint32)CAN_CONTROLLERCONFIG_RXPOL_EN_U32 == (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & Can_pControlerDescriptors[controller].u32Options) )
                || ((uint32)u32TempFlag == (u32ImaskReg & u32TempFlag)) )               
                {   
#endif

#if (CAN_RXFIFO_ENABLE == STD_ON)
                    /* ********************* Phase1 ********************* */
                    /* Check if "mbindex" corresponds to flags for Int Fifo status: Overflow or Warning.
                                If Fifo is disabled, then current flags are normal MB interrupt bits. */
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == ((Can_pControlerDescriptors[controller].u32Options) & CAN_CONTROLLERCONFIG_RXFIFO_U32) )
                    {
                        if ( FLEXCAN_FIFOOVERFLOW_INT_INDEX_U8 == (uint32)u8MbIndex )
                        {
                            /* Call the handling routine for Overflow fifo event. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
                            Can_pControlerDescriptors[controller].Can_RxFifoOverflowNotification();
                            u8MbNodata = (uint8)1U;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                            bMbOver = (VAR(boolean, AUTOMATIC))TRUE;
                            Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_E_DATALOST);
#endif
                        }

                        if ( FLEXCAN_FIFOWARNING_INT_INDEX_U8 == (uint32)u8MbIndex )
                        {
                            /* Call Rx FIFO warning Notification. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                            Can_pControlerDescriptors[controller].Can_RxFifoWarningNotification();
                            u8MbNodata = (uint8)1U;
                        }

                        if ( FLEXCAN_FIFOFRAME_INT_INDEX_U8 == (uint32)u8MbIndex )
                        {
                            /* Access data available in MB0 when there is Buffer MB5 Interrupt - Frames Available in FIFO. */
                            u32MbHrh = (Can_HwHandleType)u8MbIndex;
                            u8MbIndex = (Can_HwHandleType)0x0U;
                        }
                    }

                    /* ********************* Phase2 ********************* */
                    /* Check the interrupt flag. Execute this only if it is MB data or RxFifo data. */
                    if (u8MbNodata == (uint8)0U)
                    {
                    
    #endif /* (CAN_RXFIFO_ENABLE == STD_ON) */               

                        u32TimeoutCount = (uint32)CAN_TIMEOUT_DURATION;
                        /*Check and wait if the BUSY code is set during the move-in process*/
                        do
                        {
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            u32MbConfig = (uint32)REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex)));
                            u32TimeoutCount--;
                        }
                        while ((FLEXCAN_MBCS_CODERXBUSY_U32 == (u32MbConfig & FLEXCAN_MBCS_CODERXBUSY_U32)) &&
                        (u32TimeoutCount > (uint32)0x0U));       

#if (CAN_DEV_ERROR_DETECT == STD_ON)
                        /* CAN395: If the development error detection for the Can module is enabled, the Can module shall raise the error CAN_E_DATALOST in
                                   case of OVERWRITE or OVERRUN event detection.*/
                        /* Check if a MBs used to receive data was overwrite */
        #if (CAN_RXFIFO_ENABLE == STD_ON)                        
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        if (CAN_CONTROLLERCONFIG_RXFIFO_U32 == ((Can_pControlerDescriptors[controller].u32Options) & CAN_CONTROLLERCONFIG_RXFIFO_U32))
                        {
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                            if (Can_pControlerDescriptors[controller].u8RxFiFoUsedMb <= (uint8)u8MbIndex)
                            {
                                u8MbNodata = (uint8)1U;
                            }
                        }
                        else
                        {                     
                            u8MbNodata = (uint8)1U;                                
                        }
        #endif /* CAN_RXFIFO_ENABLE == STD_ON */ 

                        /*Set a flag value in order to identify if the current MB is used to receive data */
        #if (CAN_RXFIFO_ENABLE == STD_ON) 
                        if (u8MbNodata == (uint8)1U) 
                        {
        #endif /* CAN_RXFIFO_ENABLE == STD_ON */ 
                        
                            if(FLEXCAN_MBCS_CODERXOVRR_U32 == (u32MbConfig & FLEXCAN_MBCS_CODE_U32))
                            {
                                    bMbOver = (VAR(boolean, AUTOMATIC))TRUE;
                                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_E_DATALOST);
                            }
        #if (CAN_RXFIFO_ENABLE == STD_ON)                     
                        }                        
                        /*Reset the flag used to identify the MBs used to receive data*/
                        u8MbNodata = (uint8)0U;                        
        #endif /* CAN_RXFIFO_ENABLE == STD_ON */ 
        
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                            /* Create a local copy of the MB to ensure that it is locked out for minimum amount of time.
                                Read the DLC; this read access also locks the MB. */
                            u8MbDataLength = (uint8)( (u32MbConfig & FLEXCAN_MBCS_LENGTH_U32) >> FLEXCAN_MBCS_LENGTH_SHIFT_U32);
                            
                            /*Prevents that a buffer overflow to be generated by a CAN bus error affecting length field*/
                            if( u8MbDataLength > 8U )
                            {
                                u8MbDataLength = 8U;
                            }


                            /* Get the ID of the message.
                              For extended IDs the most significant bit mus tbe set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/

                            u32MbMessageId = ((uint32)0x0U == (u32MbConfig & (uint32)FLEXCAN_MBCS_IDE_U32)) ? /* condition to test */
                             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                (Can_IdType)((uint32)((REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_STANDARD_U32)) >> (uint32)(18U))) : /* value if condition is true */
                                                 /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                (Can_IdType)((uint32)(REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_EXTENDED_U32)) | FLEXCAN_MBC_ID_IDE_U32); /* value if condition is false */

                            /*
                               (CAN060) Data mapping by CAN to memory is defined in a way that the CAN data byte which is sent out first is array element 0,
                                       the CAN data byte which is sent out last is array element 7.
                               (CAN299) The Can module shall copy the L-SDU in a shadow buffer after reception, if the RX buffer cannot be protected (locked)
                                       by CAN Hardware against overwriting by a newly received message.
                               (CAN300) The Can module shall copy the L-SDU in a shadow buffer, if the CAN Hardware is not globally accessible.
                            */
                            for ( u8DatabyteIndex = (uint8)0U; u8DatabyteIndex < u8MbDataLength; u8DatabyteIndex++)
                            {
                                /* Copy the data  */
                                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                u8CanMbData[u8DatabyteIndex] = REG_READ8(FLEXCAN_MB_DATA((u8HwOffset), (uint32)(u8MbIndex), (uint32)(u8DatabyteIndex))) ;
                            }

                        /* Determine Hrh of the message. */
        #if (CAN_RXFIFO_ENABLE == STD_ON)
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used*/
                            if (CAN_CONTROLLERCONFIG_RXFIFO_U32 == ((Can_pControlerDescriptors[controller].u32Options) & CAN_CONTROLLERCONFIG_RXFIFO_U32))
                            {
                                if(u8MbIndex == (uint8)0U)
                                {
                                    /* Restore the MB index. */
                                    u8MbIndex = (Can_HwHandleType)u32MbHrh;
                                }
                                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                if(u8MbIndex < Can_pControlerDescriptors[controller].u8RxFiFoUsedMb)
                                {
                                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                                    u32MbHrh = (Can_HwHandleType)Can_ControllerStatuses[controller].u16MBMapping[Can_pControlerDescriptors[controller].u8RxFiFoUsedMb-1U];
                                }
                                else
                                {
                                /* determine Hrh of the message , required to skip 1-7 MB index to calculate the correct hrh in case of
                                                                              FIFO enabled for message buffers greater than 7 */
                                    u32MbHrh = (Can_HwHandleType)Can_ControllerStatuses[controller].u16MBMapping[u8MbIndex];
                                }
                            }
                            else
                            {
        #endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */
                                u32MbHrh = (Can_HwHandleType)Can_ControllerStatuses[controller].u16MBMapping[u8MbIndex];
        #if (CAN_RXFIFO_ENABLE == STD_ON)
                            }
        #endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */


                            /* Clear the interrupt flag - w1c. */
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_WRITE32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag, u32TempFlag);  

                            /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
                                unless the CPU reads the C/S word of another MB.*/
                            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                            REG_READ32( FLEXCAN_TIMER(u8HwOffset));

                          
                             #if (CAN_LPDU_NOTIFICATION_ENABLE == STD_ON)
                             /*[CAN444] If the L-PDU callout returns false, the L-PDU shall not be processed any further. */
                             /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            if (TRUE ==    CanLPduReceiveCalloutFunction(u32MbHrh, u32MbMessageId, u8MbDataLength, u8CanMbData))
                            {
                            #endif
                             /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            CanIf_RxIndication( u32MbHrh, u32MbMessageId, u8MbDataLength, u8CanMbData);
                            /* If the overflow event occurs */
                            #if (CAN_DEV_ERROR_DETECT == STD_ON)
                            if ((VAR(boolean, AUTOMATIC))TRUE == bMbOver)
                            {
                                u8MbIndex = mbindex_end;
                            }
                            #endif
                             #if (CAN_LPDU_NOTIFICATION_ENABLE == STD_ON)
                            }
                            #endif
                            
        #if (CAN_RXFIFO_ENABLE == STD_ON)
                    }
        #endif    

#if (CAN_RXPOLL_SUPPORTED == STD_OFF)
                }
                else
                {
                    /*Clear interrupt status flag when spurious interrupt is detected*/
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    REG_WRITE32(Can_IflagImask[u8IflagRegIndex][u8HwOffset].u32CanIflag, u32TempFlag);
                    
                }
#endif      
            }/*if ( (uint32)0x0U != (u32IflagReg & u32TempFlag) )*/
            
            u8MbIndex++;
        } /* end while */
    }



/*================================================================================================*/
/**
* @brief          Service to perform the polling of RX indications.
* @details        Processes Rx interrupt flags.
*                 This routine is called by:
*                    - Can_MainFunction_Read() from Can.c file.
*
* @pre            The controller must be configured for receive in polling mode and at least one MB is configured for Rx.
* @post           Process the reception data in case of availability.
*
*
*/
#if (CAN_RXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_CODE) Can_FlexCan_MainFunctionRead( void)
    {

        /* Variable for indexing the controllers. */
        VAR(uint8, AUTOMATIC)  u8CtrlIndex = 0U;
        /* First MB to process. */
        VAR(uint8, AUTOMATIC)  u8MbFirst = 0U;
        /* Last MB to process. */
        VAR(uint8, AUTOMATIC)  u8MbLast = 0U;

        /* Loop through all configured controller descriptors. */
        for ( u8CtrlIndex = (uint8)0U; u8CtrlIndex < (uint8)Can_pCurrentConfig->u8ControllersConfigured; u8CtrlIndex++)
        {
            /*
               (CAN108) The function Can_MainFunction_Read shall perform the polling of RX indications when CanRxProcessing is set to POLLING.
            */
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            if ( (FLEXCAN_NULL_OFFSET_U8 != Can_pControlerDescriptors[u8CtrlIndex].u8ControllerOffset) &&
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                 ((uint32)0U != (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & (Can_pControlerDescriptors[u8CtrlIndex].u32Options))) &&
                 /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                 ((Can_pControlerDescriptors[u8CtrlIndex].u8MaxMBCount) != (uint8)0U) )
            {
                /* Init last MB to process for RX. "u8FirstTxMBIndex" is updated considering RxFifo. */
                if (0U < Can_ControllerStatuses[u8CtrlIndex].u8FirstTxMBIndex)
                {
                    u8MbLast = (uint8)(Can_ControllerStatuses[u8CtrlIndex].u8FirstTxMBIndex - (uint8)1U);
                }
                else
                {
                    u8MbLast = (uint8)(Can_ControllerStatuses[u8CtrlIndex].u8FirstTxMBIndex);
                }

                /* Enabled & RxPoll used : process Rx interrupt flags, start with the first Rx MB (0) and finish before the first Tx MB. */
                Can_FlexCan_ProcessRx( (uint8)u8CtrlIndex, (uint8)u8MbFirst, (uint8)u8MbLast);
            }
        }
    }

/*================================================================================================*/
/**
* @brief          Function called at fixed cyclic time, with polling of all the MessageBuffer referenced to .readpoll
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @api
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
/**
* @violates @ref Can_Flexcan_c_REF_7 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
FUNC (void, CAN_CODE) Can_FlexCan_MainFunctionMultipleReadPoll( VAR(uint8, AUTOMATIC) readpoll)
    {
        /* Variable for indexing the controllers. */
        VAR(uint8, AUTOMATIC)  u8CtrlId = 0U;
        /* First MB to process. */
        VAR(uint8, AUTOMATIC)  u8MbIndex = 0U;
        /* Can Object ID to process. */
        VAR(uint32, AUTOMATIC)  u32ObjectId = 0U;
        /* Can Process Index of MB for the controller to process. */
        VAR(uint8, AUTOMATIC)  u8RxProcessIndex[CAN_MAXCTRL_SUPPORTED];

        if ( NULL_PTR != Can_pCurrentConfig )
        {
            #if (CAN_DEV_ERROR_DETECT == STD_ON)
                /* Test whether the driver is already initialised. */
                if ( CAN_UNINIT == Can_eDriverStatus )
                {
                    /*
                       (CAN181) If development error detection for the Can module is enabled: The function Can_MainFunction_Read shall raise the
                               error CAN_E_UNINIT if the driver not yet initialized.
                    */
                    Det_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_E_UNINIT);
                }
                else
                {
            #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
                    /* initialise the u8RxProcessIndex for all the configured controller. */
                    for ( u8CtrlId = (uint8)0U; u8CtrlId < CAN_MAXCTRL_SUPPORTED; u8CtrlId++)
                    {
                        u8RxProcessIndex[u8CtrlId] = 0U;
                        #if (CAN_RXFIFO_ENABLE == STD_ON)
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                        if ( CAN_CONTROLLERCONFIG_RXFIFO_U32 == ((uint32)(Can_pControlerDescriptors[u8CtrlId].u32Options) & CAN_CONTROLLERCONFIG_RXFIFO_U32) )
                        {
                            /* Processing MB must start after the last MB used by Fifo filter list. */
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            u8RxProcessIndex[u8CtrlId] = Can_pControlerDescriptors[u8CtrlId].u8RxFiFoUsedMb;
                        }
                        #endif /* #if (CAN_RXFIFO_ENABLE == STD_ON) */
                    }
                    /* Parse through all RX configured message buffer */
                    for ( u8MbIndex = (uint8)0U; u8MbIndex < (uint8)Can_pCurrentConfig->MBConfigContainer.uMessageBufferConfigCount; u8MbIndex++)
                    {
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        u8CtrlId = Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u8ControllerId;
                        /*  Poll only the Rx MB which is referenced by Can_FlexCan_MainFunctionMultipleReadPoll */
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                        if ((readpoll == Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u32CanMainFuncRWPeriodRef) &&
                        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            (FLEXCAN_NULL_OFFSET_U8 != Can_pControlerDescriptors[u8CtrlId].u8ControllerOffset) &&
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            ((uint32)0U != (CAN_CONTROLLERCONFIG_RXPOL_EN_U32 & (Can_pControlerDescriptors[u8CtrlId].u32Options))) &&
                            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            (CAN_RECEIVE == Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].eMBType ))
                        {
                            /* CanOnjectID of the polled MB */
                             /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            u32ObjectId = (Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr[u8MbIndex].u32HWObjID );
/* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
                            while ((u32ObjectId != (Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8RxProcessIndex[u8CtrlId]])) && (u8RxProcessIndex[u8CtrlId] < (Can_pControlerDescriptors[u8CtrlId].u8MaxMBCount)))
                            {
                                /* increase the u8RxProcessIndex to check next u32ObjectId present */
                                u8RxProcessIndex[u8CtrlId]++;
                            }
                            if (u32ObjectId == Can_ControllerStatuses[u8CtrlId].u16MBMapping[u8RxProcessIndex[u8CtrlId]])
                            {
                                /* Enabled & RxPoll used : process Rx interrupt flags, */
                                Can_FlexCan_ProcessRx( (uint8)u8CtrlId, (uint8)u8RxProcessIndex[u8CtrlId], (uint8)u8RxProcessIndex[u8CtrlId]);
                                /* increase the u8RxProcessIndex to check next u32ObjectId present */
                                u8RxProcessIndex[u8CtrlId]++;
                            }
                        }
                    }
            #if (CAN_DEV_ERROR_DETECT == STD_ON)
                }
            #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
        }
    }
#endif /* (CAN_RXPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
* @brief          Service to perform the polling of CAN status register flags to detect transition of CAN Controller state
* @details        The function Can_MainFunction_Mode shall implement the polling of CAN status register flags to detect transition of CAN Controller state
*
* @pre
* @post
*
*/

FUNC (void, CAN_CODE) Can_FlexCan_MainFunctionMode( void)
    {
        /* Variable for indexing the controllers. */
        VAR(uint8, AUTOMATIC)  u8CtrlIndex = 0U;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)  u8HwOffset = 0U;
        /* Old and new MCR status Register*/
        
#if (CAN_WAKEUP_SUPPORT == STD_ON)              
        VAR(uint32, AUTOMATIC)  u32OldMcr = 0U;        
#endif

        VAR(uint32, AUTOMATIC)  u32NewMcr = 0U;
        /* Controller descriptor */
        P2CONST(Can_ControlerDescriptorType, AUTOMATIC, CAN_APPL_CONST) pCanControlerDescriptor;

        /* Loop through all configured controller descriptors. */
        for ( u8CtrlIndex = (uint8)0U; u8CtrlIndex < (uint8)Can_pCurrentConfig->u8ControllersConfigured; u8CtrlIndex++)
        {
            /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            if ( (FLEXCAN_NULL_OFFSET_U8 != Can_pCurrentConfig->ControlerDescriptors[u8CtrlIndex].u8ControllerOffset) )
            {
                
                if(CAN_SLEEPED != Can_ControllerStatuses[u8CtrlIndex].ControllerState)
                {                
                    /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    pCanControlerDescriptor = &Can_pCurrentConfig->ControlerDescriptors[u8CtrlIndex];
                    /* Get the hardware offset for this controller. */

                    u8HwOffset = pCanControlerDescriptor->u8ControllerOffset;
                    /*
                        (CAN373) The function Can_Mainfunction_Mode shall call the function CanIf_ControllerModeIndication to notify the upper layer about a successful
                                 state transition of the CAN controller, in case the state transition was triggered by function Can_SetControllerMode.
                    */
                    
                    /* We have to look for all the possible transitions*/
                    
                    /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                    /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */                     
                     u32NewMcr = (uint32)(REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_NOTRDY_U32);                     
                     
                     
                    /*Check if logical state is synchronized with hardware state*/ 
                    if((FLEXCAN_MCR_NOTRDY_U32 == u32NewMcr) && (CAN_STARTED == Can_ControllerStatuses[u8CtrlIndex].ControllerState))
                    {
                        Can_ControllerStatuses[u8CtrlIndex].ControllerState = CAN_STOPPED;
                        CanIf_ControllerModeIndication(u8CtrlIndex, CANIF_CS_STOPPED);
                    }
                    else if ((FLEXCAN_MCR_NOTRDY_U32 != u32NewMcr) && (CAN_STOPPED == Can_ControllerStatuses[u8CtrlIndex].ControllerState))
                    {
                        Can_ControllerStatuses[u8CtrlIndex].ControllerState = CAN_STARTED;
                        CanIf_ControllerModeIndication(u8CtrlIndex, CANIF_CS_STARTED);
                    }   
                    else
                    {
                    /* deliberately left blank to avoid MISRA violation (Rule 14.10 ) */
                    }
                }

            
#if (CAN_WAKEUP_SUPPORT == STD_ON)
                /* from CAN_STOPPED to CAN_SLEEPED (in CAN_SLEEPED,  MCR[WAK_SMK] = 1 and MCR[SLF_WAK] = 1)*/
                u32OldMcr = 0U;
                u32NewMcr = 0U;
                if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[u8CtrlIndex].u8InterruptMode )
                {
                    u32NewMcr |= ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_WAK_MSK_U32 );
                    u32OldMcr |= (Can_u32McrConfiguration[u8CtrlIndex] & FLEXCAN_MCR_WAK_MSK_U32);
                }
                /* Self Wakeup must be set. */
                u32NewMcr |= ( (uint32)REG_READ32( FLEXCAN_MCR(u8HwOffset)) & FLEXCAN_MCR_SLF_WAK_U32 );
                u32OldMcr |= (Can_u32McrConfiguration[u8CtrlIndex] & FLEXCAN_MCR_SLF_WAK_U32) ;

                /* with this test i am assuring that this trasition is the write one, if CAN_INTERRUPT_ENABLED == OFF then SLF_WAK mask is
                the only one that can change, and the change accured*/
                if ( u32OldMcr != u32NewMcr )
                {
                    if ( (uint8)CAN_INTERRUPT_ENABLED == Can_ControllerStatuses[u8CtrlIndex].u8InterruptMode )
                    {
                        if( u32NewMcr ==  (FLEXCAN_MCR_WAK_MSK_U32 | FLEXCAN_MCR_SLF_WAK_U32) )
                        {
                            CanIf_ControllerModeIndication(u8CtrlIndex, CANIF_CS_SLEEP);
                        }

                    }
                    else /* polling mode */
                    {
                        CanIf_ControllerModeIndication(u8CtrlIndex, CANIF_CS_SLEEP);
                    }
                }

                /* from CAN_SLEEPED to CAN_STOPPED (in CAN_STOPPED,  MCR[WAK_SMK] = 0 and MCR[SLF_WAK] = 0)*/

                /* with this test i am assuring that this trasition is the write one, if CAN_INTERRUPT_ENABLED == OFF then SLF_WAK mask is
                the only one that can change, and the change accured*/
                if ( (u32OldMcr != u32NewMcr) && (u32NewMcr == 0U) )
                {
                    CanIf_ControllerModeIndication(u8CtrlIndex, CANIF_CS_STOPPED);
                }
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */  
            }
        }
    }

/*================================================================================================*/
/**
* @brief          Local function for calling notification function to notify upper layer during Can_MainFunction_BusOff if polling is selected or from ISR when Interrupt mode selected.
* @details        Local function for calling notification function to notify upper layer during
*                 Can_MainFunction_BusOff if polling is selected or from ISR when Interrupt mode selected.
*                 This routine is called by:
*                  - Can_IPW_ProcessBusOff() from Can.c file.
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @pre            A busoff condition must to be fulfilled.
* @post           Status flag is cleared.
*
*/
FUNC (void, CAN_CODE) Can_FlexCan_ProcessBusOff( CONST(uint8, AUTOMATIC) controller)
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) u8HwOffset = 0U;


        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /* Clear the ESR[BOFF_INT] bus off interrupt flag (w1c). */
         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
         REG_WRITE32( FLEXCAN_ESR(u8HwOffset), (FLEXCAN_ESR_BOFFINT_U32 & FLEXCAN_ESR_CONFIG_MASK_U32));
        
    }


/*================================================================================================*/
/**
* @brief          Local function for calling notification function to notify upper layer during Can_MainFunction_Wakeup if polling is selected or from ISR when Interrupt mode selected.
* @details        Local function for calling notification function to notify upper layer during
*                 Can_MainFunction_Wakeup if polling is selected or from ISR when Interrupt mode selected.
*                 This routine is called by:
*                  - Can_IPW_Process_Wakeup() from Can.c file.
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @pre            A wakeup condition must be fulfilled.
* @post           Clear the flag for wakeup condition.
*
*/
#if (CAN_WAKEUP_SUPPORT == STD_ON)

FUNC (void, CAN_CODE) Can_FlexCan_ProcessWakeup( CONST(uint8, AUTOMATIC) controller)
    {

        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) u8HwOffset = 0U;

        /* Get the hardware offset for this controller. */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /* Clear the ESR[WAK_INT]  WakeUp interrupt flag (w1c). */
        REG_WRITE32( FLEXCAN_ESR(u8HwOffset), (FLEXCAN_ESR_WAK_INT_U32 & FLEXCAN_ESR_CONFIG_MASK_U32));
    }

#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */


/*================================================================================================*/
/**
* @brief          This function checks if a Wakeup has occurred for the given controller.
* @details        This routine is called by:
*                  - Can_MainFunction_Wakeup() from Can.c file.
*                  - Can_CheckWakeup() from Can.c file.
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @return        Std_ReturnType
* @retval        E_OK wakeup detected
* @retval        E_NOT_OK wakeup not detected
*
* @pre            A request for wakeup checking is required.
* @post           Report the occurence or not for an wakeup event.
*
*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)
FUNC (Std_ReturnType, CAN_CODE) Can_FlexCan_CheckWakeup( VAR(uint8, AUTOMATIC) controller)
    {

        /* Return value. */
        Std_ReturnType        eReturnValue = (uint8)E_NOT_OK;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) u8HwOffset = 0U;

        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4,pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /*
           (CAN361) The function Can_CheckWakeup shall check if the requested CAN controller has detected a wakeup.
                    If a wakeup event was successfully detected, the function shall return E_OK, otherwise E_NOT_OK.
        */
        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            if ( FLEXCAN_ESR_WAK_INT_U32 == (FLEXCAN_ESR_WAK_INT_U32 & (uint32)REG_READ32( FLEXCAN_ESR(u8HwOffset))) )
        {
            /* Controller is in WakeUp state. */
            eReturnValue = (uint8)E_OK;
        }



        return (eReturnValue);
    }
#endif /* (CAN_WAKEUP_SUPPORTED == STD_ON) */

/*================================================================================================*/
/**
* @brief          This function checks if a BusOff has occurred for the given controller.
* @details        This routine is called by:
*                  - Can_MainFunction_BusOff() from Can.c file.
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @return        Std_ReturnType
* @retval        E_OK wakeup detected
* @retval        E_NOT_OK wakeup not detected
*
* @pre            A request for busoff checking is required.
* @post           Report the occurence or not for an busoff event.
*
*/
/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC (Std_ReturnType, CAN_CODE) Can_FlexCan_CheckBusOff( VAR(uint8, AUTOMATIC) controller)
    {

        /* Return value. */
        VAR(uint8, AUTOMATIC) eReturnValue = (uint8)E_NOT_OK;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC) u8HwOffset = 0U;


        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;

        /* Check Busoff flag if it's set. */
         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        if ( FLEXCAN_ESR_BOFFINT_U32 == (FLEXCAN_ESR_BOFFINT_U32 & (uint32)REG_READ32( FLEXCAN_ESR(u8HwOffset))) )
        {
            /* Controller is in BusOff state. */
            eReturnValue = (uint8)E_OK;
        }

        return (eReturnValue);
    }


/*================================================================================================*/
/**
* @brief          Process Rx Fifo FrameAvailable events.
* @details        This routine is called by:
*                  - Can_IPW_RxFifoFrameAvNotif() from Can.c file.
*
* @param[in]      controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
*
* @return        Std_ReturnType
* @retval        E_OK wakeup detected
* @retval        E_NOT_OK wakeup not detected
*
* @pre            Driver must be initialized and RxFifo should be enabled.
*
*/
#if (CAN_RXFIFO_ENABLE == STD_ON)

/* @violates @ref Can_Flexcan_c_REF_10 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_CODE) Can_FlexCan_RxFifoFrameAvNotif( CONST(uint8, AUTOMATIC) controller)
    {
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)  u8HwOffset = 0U;
        /* Variable for indexing the MBs. */
        VAR(uint8, AUTOMATIC)    u8MbIndex = 0U;
        /* Number of data bytes. */
        VAR(uint8, AUTOMATIC)    u8MbDataLength = 0U;
        /* Physical data bytes. */
        VAR(uint8, AUTOMATIC)    u8CanMbData[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        /* Index for data byte of MB. */
        VAR(uint8, AUTOMATIC)    u8DatabyteIndex = 0U;
        /* Variable for storing the Hrh. */
        VAR(Can_HwHandleType, AUTOMATIC)    u32Hrh = 0U;
        /* Variables for storing the CanID. */
        VAR(Can_IdType, AUTOMATIC) u32MbMessageId = 0U;
        /* Temporary variable. */
        VAR(uint32, AUTOMATIC)   u32MbConfig = 0U;

        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[controller].u8ControllerOffset;


        /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        u32MbConfig = (uint32)REG_READ32( FLEXCAN_MB((u8HwOffset), (uint32)(u8MbIndex)));

        /* Create a local copy of the MB to ensure that it is locked out for minimum amount of time. Read the DLC; this read access also locks the MB. */
        u8MbDataLength = (uint8)((u32MbConfig & FLEXCAN_MBCS_LENGTH_U32) >> FLEXCAN_MBCS_LENGTH_SHIFT_U32);
        
        /*Prevents that a buffer overflow to be generated by a CAN bus error affecting length field*/
        if( u8MbDataLength > 8U )
        {
            u8MbDataLength = 8U;
        }            

        /* Get the ID of the message.
        For extended IDs the most significant bit must be set - according to Can_IdType requirement - chapter8.2.4 of SWS CAN.*/
        u32MbMessageId = ((uint32)0x0U == (u32MbConfig & (uint32)FLEXCAN_MBCS_IDE_U32)) ? /* condition to test */
         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */

                                (Can_IdType)((uint32)((REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_STANDARD_U32)) >> (uint32)(18U))) : /* value if condition is true */
                                             /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                                                        (Can_IdType)((uint32)((uint32)(REG_READ32( FLEXCAN_MB_ID((u8HwOffset), (uint32)(u8MbIndex))) & (uint32)(FLEXCAN_MBID_ID_EXTENDED_U32)) | FLEXCAN_MBC_ID_IDE_U32)); /* value if condition is false */

        /* Copy the data. */
        for ( u8DatabyteIndex = (uint8)0U; u8DatabyteIndex < u8MbDataLength; u8DatabyteIndex++)
        {
            /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u8CanMbData[u8DatabyteIndex] = REG_READ8(FLEXCAN_MB_DATA((u8HwOffset), (uint32)(u8MbIndex), (uint32)(u8DatabyteIndex))) ;
        }


        /* Release the internal lock. Reading the Free Running Timer is not mandatory. If not executed the MB remains locked,
            unless the CPU reads the C/S word of another MB.*/
/* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */

        REG_READ32( FLEXCAN_TIMER(u8HwOffset));

        /*
        Call the RxIndication function - This service is implemented in the CAN Interface and called by the CAN Driver after a CAN L-PDU has been received.
        Within this service, the CAN Interface translates the CanId into the configured target PDU ID and routes this indication to the configured upper layer target service(s).
        */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u32Hrh = (Can_HwHandleType)Can_ControllerStatuses[controller].u16MBMapping[Can_pControlerDescriptors[controller].u8RxFiFoUsedMb-1U];



          #if (CAN_LPDU_NOTIFICATION_ENABLE == STD_ON)
                           /*[CAN444] ⌈If the L-PDU callout returns false, the L-PDU shall not be processed any further. */
                             /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            if (TRUE ==    CanLPduReceiveCalloutFunction(u32Hrh, u32MbMessageId, u8MbDataLength, u8CanMbData))
                            {
                            #endif
                             /* @violates @ref Can_Flexcan_c_REF_6 Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable */
                            /* @violates @ref Can_Flexcan_c_REF_11 Violates MISRA 2004 Required Rule 10.1 , Prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */
                            CanIf_RxIndication( u32Hrh, u32MbMessageId, u8MbDataLength, u8CanMbData);
                            
                            #if (CAN_LPDU_NOTIFICATION_ENABLE == STD_ON)
                            }
                            #endif
              
       
      
           

        /* Ack interrupt flag - w1c bit. */
         /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
         REG_WRITE32( FLEXCAN_IFLAG1(u8HwOffset), (uint32)((FLEXCAN_FIFO_AVAILABLE_INT_MASK_U32)));
        

    }
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */


/*================================================================================================*/
/*
* @brief          Process a transition from one clock source to another.
* @details        This function is configuring Can controllers to run on the same baudrate, but having a different MCU source clock.
*                 This routine is called by:
*                  - Can_SetClockMode() from Can.c file.
*
* @param[in]      u8Controller    CAN controller for which the init shall be done. Based on configuration order list (CanControllerId).
* @param[in]      can_clk_mode clock mode selection
*
* @return        Std_ReturnType Result of the clock switch operation.
* @retval        E_OK  Switch clock operation was ok.
* @retval        E_NOT_OK  Switch clock operation was not ok.
*
* @pre            Driver must be initialized and all the controllers must be in Stop state.
*
* @note           Not AUTOSAR required. This is user implementation.
*/

#if (CAN_DUAL_CLOCK_MODE == STD_ON)

FUNC(Std_ReturnType, CAN_CODE) Can_FlexCan_SetClockMode( VAR(uint8, AUTOMATIC) u8Controller, VAR(Can_ClockMode, AUTOMATIC) can_clk_mode)
    {
        /* Return the operation success. */
        VAR(Std_ReturnType, AUTOMATIC) eReturnValue = (uint8)E_OK;
        /* Controller hardware offset on chip. */
        VAR(uint8, AUTOMATIC)  u8HwOffset = 0U;
        /* Variable to hold the index of the current baudrate */
        VAR(uint8, AUTOMATIC) u8BaudrateIndex = 0U;

        /* Get the index of the current baudrate */
        u8BaudrateIndex = Can_ControllerStatuses[u8Controller].u8CurrentBaudRateIndex;

        /* Get the hardware offset for this controller. */
        /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
        u8HwOffset = Can_pControlerDescriptors[u8Controller].u8ControllerOffset;

        switch (can_clk_mode)
        {
            case (CAN_NORMAL):
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
               
                REG_WRITE32( FLEXCAN_CTRL(u8HwOffset), (uint32)(((uint32)(Can_pControlerDescriptors[u8Controller].pControllerBaudrateConfigsPtr[u8BaudrateIndex].u32ControlRegister)) & FLEXCAN_CTRL_CONFIG_MASK_U32));

                break;

            case (CAN_ALTERNATE):
                /* @violates @ref Can_Flexcan_c_REF_4 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_Flexcan_c_REF_8 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                REG_WRITE32( FLEXCAN_CTRL(u8HwOffset), (uint32)(((uint32)(Can_pControlerDescriptors[u8Controller].pControllerBaudrateConfigsPtr[u8BaudrateIndex].u32ControlRegisterAlternate)) & FLEXCAN_CTRL_CONFIG_MASK_U32));
                break;

            default:
                eReturnValue = (uint8)E_NOT_OK;
                Cer_ReportError( (uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, (uint8)CAN_SID_SETCLOCKMODE, (uint8)CAN_E_DEFAULT);
                /* Compiler_Warning: This warning is thrown due to the infinite loop while(1) in the
                                      Cer_ReportError() function implementation */

                break;
        }

        return (eReturnValue);

    }

#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

#define CAN_STOP_SEC_CODE
/* @violates @ref Can_Flexcan_c_REF_2 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_Flexcan_c_REF_5 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
