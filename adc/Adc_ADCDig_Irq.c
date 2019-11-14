/**
*   @file    Adc_Adcdig_Irq.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - ADCDig Interrupt source file.
*   @details  Autosar Adc Interrupt source file.
*
*   @addtogroup ADC
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : ADCDIG
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
* @section Adc_Adcdig_Irq_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section Adc_Adcdig_Irq_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* There are different kinds of execution code sections.
*
* @section Adc_Adcdig_Irq_c_REF_3
* Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware offset of the controller.
* The address calculated as an unsigned int is passed to  a macro for initializing the
* pointer with that address (ex: see REG_WRITE32 macro).
*
* @section Adc_Adcdig_Irq_c_REF_4
* Violates MISRA 2004 Required Rule 14.7, Return statement before end of function.
* The return statement are used to simplify the code structure and easier readability.
*
* @section Adc_Adcdig_Irq_c_REF_5
* Violates MISRA 2004 Required Rule 19.15, Repeated include file.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Adc_Adcdig_Irq_c_REF_6
* Violates MISRA 2004 Required Rule 14.2, Expected void type, assignment, increment or decrement.
* This is used to read an unused value from an register.
*
* @section Adc_Adcdig_Irq_c_REF_7
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Adcdig_Irq_c_REF_8
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
* arithmetic but used due to the code complexity.
*
* @section Adc_Adcdig_Irq_c_REF_9
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to a macro for initializing the pointer with that address.
*
* @section Adc_Adcdig_Irq_c_REF_10
* Violates MISRA 2004 Required Rule 12.4, the right-hand operand of a logical "&&" or "||" operator
* shall not contain side effects. This is necessary to simplify the code structure and easier
* readability.
*
* @section Adc_Adcdig_Irq_c_REF_11
* Violates MISRA 2004 Required Rule 10.1, cast from integer type to different type or a wider integer type
* This is used for the Speed optimization of the memory access.
*
* @section Adc_Adcdig_Irq_c_REF_12
* Violates MISRA 2004 Required Rule 8.10, all declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
* This violation occurs because of the interaction with MCL module / ISR symbols
* need to be exported .
*
* @section Adc_Adcdig_Irq_c_REF_13
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared
* in one and only one file.
* This violation cannot be removed due to the interaction with MCL module.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. All compilers used support more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external Units
* 3) internal and external interfaces from this Unit
==================================================================================================*/
#include "Adc_Ipw.h"
#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"
/** @violates @ref Adc_Adcdig_Irq_c_REF_2 Repeated include file MemMap.h */
#include "Mcal.h"
#include "SchM_Adc.h"
#ifdef ADC_DMA_SUPPORTED
  #include "CDD_Mcl.h"
#endif

#if (ADC_BCTU_AVAILABLE == STD_ON)
  #if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON)
    #include "Adc_Reg_eSys_Bctu.h"
  #endif
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_ADCDIG_AR_VENDOR_ID_IRQ_C                 43
/**
* @violates @ref Adc_Adcdig_Irq_c_REF_7 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C     4
/**
* @violates @ref Adc_Adcdig_Irq_c_REF_7 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C     0
/**
* @violates @ref Adc_Adcdig_Irq_c_REF_7 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_ADCDIG_AR_RELEASE_REVISION_VERSION_IRQ_C  3
#define ADC_ADCDIG_SW_MAJOR_VERSION_IRQ_C             1
#define ADC_ADCDIG_SW_MINOR_VERSION_IRQ_C             0
#define ADC_ADCDIG_SW_PATCH_VERSION_IRQ_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC IPW header file are from the same vendor */
#if (ADC_ADCDIG_AR_VENDOR_ID_IRQ_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Adcdig_Irq.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_ADCDIG_AR_RELEASE_REVISION_VERSION_IRQ_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig_Irq.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_ADCDIG_SW_MAJOR_VERSION_IRQ_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_ADCDIG_SW_MINOR_VERSION_IRQ_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_ADCDIG_SW_PATCH_VERSION_IRQ_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Adcdig_Irq.c and Adc_Ipw.h are different"
#endif

/** @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Adcdig_Irq.c and Mcal.h are different"
 #endif 
 /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Adcdig_Irq.c and SilRegMacros.h are different"
 #endif 
 
 #ifdef ADC_DMA_SUPPORTED
  /* Check if source file and DMA header file are of the same Autosar version */
  #if ((ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C != MCL_AR_RELEASE_MINOR_VERSION)  \
      )
      #error "AutoSar Version Numbers of Adc_Adcdig_Irq.c and CDD_Mcl.h are different"
  #endif
  /* Check if source file and Mcl_Types.h are of the same Autosar version */
  #if ((ADC_ADCDIG_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_ADCDIG_AR_RELEASE_MINOR_VERSION_IRQ_C != MCL_TYPES_AR_RELEASE_MINOR_VERSION)  \
      )
      #error "AutoSar Version Numbers of Adc_Adcdig_Irq.c and Mcl_Types.h are different"
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
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Adcdig_Irq_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
    )
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndGroupConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndNormalConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndSwInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
#if (ADC_HW_TRIGGER_API == STD_ON)
FUNC(void, ADC_CODE) Adc_Adcdig_EndInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
);
#endif /* ADC_HW_TRIGGER_API == STD_ON */
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#ifdef ADC_UNIT_0_ISR_USED
ISR(Adc_Adcdig_EndGroupConvUnit0);
#endif /* ADC_UNIT_0_ISR_USED */
#ifdef ADC_UNIT_1_ISR_USED
ISR(Adc_Adcdig_EndGroupConvUnit1);
#endif /* ADC_UNIT_1_ISR_USED */
#ifdef ADC_UNIT_2_ISR_USED
ISR(Adc_Adcdig_EndGroupConvUnit2);
#endif /* ADC_UNIT_2_ISR_USED */
#ifdef ADC_UNIT_3_ISR_USED
ISR(Adc_Adcdig_EndGroupConvUnit3);
#endif /* ADC_UNIT_3_ISR_USED */

#ifdef ADC_WDG_SUPPORTED
#if ((defined(ADC_UNIT_0_WDG_ISR_USED)) || (defined(ADC_UNIT_1_WDG_ISR_USED)) || \
     (defined(ADC_UNIT_2_WDG_ISR_USED)) || (defined(ADC_UNIT_3_WDG_ISR_USED)) || \
     ((defined(ADC_WDG_GROUP_SHARED_ISR)) && ((defined(ADC_UNIT_0_ISR_USED)) || \
      (defined(ADC_UNIT_1_ISR_USED)) || (defined(ADC_UNIT_2_ISR_USED)) || \
      (defined(ADC_UNIT_3_ISR_USED)))) \
     )
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_WdgThresholdHandler
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
STATIC FUNC(void, ADC_CODE) Adc_Adcdig_EndWdgInterrupt
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
#endif /*  defined(ADC_UNIT_0_WDG_ISR_USED)) || ....  */

  #ifndef ADC_WDG_GROUP_SHARED_ISR
    #ifdef ADC_UNIT_0_WDG_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash */    
ISR(Adc_Adcdig_WatchDogThresholdUnit0);
    #endif /* ADC_UNIT_0_WDG_ISR_USED */
    #ifdef ADC_UNIT_1_WDG_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash */
ISR(Adc_Adcdig_WatchDogThresholdUnit1);
    #endif /* ADC_UNIT_1_WDG_ISR_USED */
    #ifdef ADC_UNIT_2_WDG_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash */    
ISR(Adc_Adcdig_WatchDogThresholdUnit2);
    #endif /* ADC_UNIT_2_WDG_ISR_USED */
    #ifdef ADC_UNIT_3_WDG_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash */    
ISR(Adc_Adcdig_WatchDogThresholdUnit3);
    #endif /* ADC_UNIT_3_WDG_ISR_USED */
  #endif  /* ADC_WDG_GROUP_SHARED_ISR */
#endif /* ADC_WDG_SUPPORTED */


#ifdef ADC_DMA_SUPPORTED
#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
    )
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndNormalConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#if(ADC_HW_TRIGGER_API == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndGroupConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
#endif /* defined(ADC_UNIT_0_ISR_USED)... */
#endif /* ADC_DMA_SUPPORTED */

#ifdef ADC_UNIT_0_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete0(void);
#endif /* ADC_UNIT_0_ISR_USED */
#ifdef ADC_UNIT_1_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete1(void);
#endif /* ADC_UNIT_1_ISR_USED */
#ifdef ADC_UNIT_2_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete2(void);
#endif /* ADC_UNIT_2_ISR_USED */
#ifdef ADC_UNIT_3_ISR_USED
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete3(void);
#endif /* ADC_UNIT_3_ISR_USED */
/*==================================================================================================
*                                   GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
#ifdef ADC_MULTIPLE_HARDWARE_TRIGGERS
#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
FUNC(void, ADC_CODE) Adc_Adcdig_EndMultipleCtuConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32TrgSrc
/** @violates @ref Adc_Adcdig_Irq_c_REF_13 Function declaration */
);
#endif /* ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON */
#endif

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )
/**
* @brief @implements Adc_ADCDig_RecordResult_Activity */
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_RecordResult
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples
)
{
    VAR(Adc_ChannelType, AUTOMATIC) Ch = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex = 0U;
    VAR(uint32, AUTOMATIC) u32CdrValue;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Std_ReturnType, AUTOMATIC) ReturnValue = (Std_ReturnType)E_OK;
    VAR(uint32, AUTOMATIC) u32CdrMask = ADC_CDR_DATA_MASK_U32;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
    P2CONST(Adc_Adcdig_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr = Adc_CfgPtr->pAdc;
    VAR(Adc_ChannelType, AUTOMATIC) Shift = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;
#endif /* ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /* Flag to set if ADC results are in the range selected */
    VAR(boolean,AUTOMATIC) bFlag = (boolean)TRUE;
    VAR(uint16, AUTOMATIC) u16CdrValueTemp;
#endif /* ADC_ENABLE_LIMIT_CHECK == STD_ON */

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pResult = Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group] + Adc_GroupStatus[Group].ResultIndex;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
    for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
    {
        /* Get the index of hardware Unit in structure which will match with the hardware Unit ID*/
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(Unit == pConfigPtr[HwIndex].AdcHardwareUnitId)
        {
            break;
        }
    }
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    Shift = (16U - (pConfigPtr[HwIndex].Res));
    u32CdrMask = (uint32)(ADC_CDR_DATA_MASK_U32 << Shift);
#endif

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for (Ch = 0U; Ch < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; Ch++)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndex = Adc_GroupChannelIndex(Group,Ch);
        /**
        * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
        */
        u32CdrValue = REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)Adc_CfgPtr->pChannels[Unit][ChIndex].ChId));

        /** @violates @ref Adc_Adcdig_Irq_c_REF_3 cast from unsigned long to pointer */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((boolean)TRUE == Adc_CfgPtr->pChannels[Unit][ChIndex].bChannelLimitCheck)
        {
    #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
            u16CdrValueTemp = (uint16)(((u32CdrValue)&ADC_SHIFT_MASK_U32) >> Shift);
    #else
            u16CdrValueTemp = (uint16)(u32CdrValue&ADC_CDR_DATA_MASK_U32);
    #endif /* ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT */
            bFlag = (boolean)Adc_CheckConversionValuesInRange(u16CdrValueTemp, Unit, ChIndex);
            if ((boolean)TRUE == bFlag)
            {
                /**
                * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
                */
                *(pResult+(Ch*(GroupSamples))) = (uint16)(u32CdrValue&u32CdrMask);
            }
            else
            {
                Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
                /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
                return (Std_ReturnType)E_NOT_OK;
            }
        }
        else /* In case of bChannelLimitCheck = FALSE) */
        {
            /**
            * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
            */
            *(pResult+(Ch*(GroupSamples)))=(uint16)(u32CdrValue&u32CdrMask);
        }
#else
        /**
        * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
        */
        *(pResult+(Ch*(GroupSamples))) = (uint16)(u32CdrValue&u32CdrMask);
#endif /* ADC_ENABLE_LIMIT_CHECK == STD_ON */
    }
    return ReturnValue;
}
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) || \
     (defined(ADC_DMA_SUPPORTED)) \
     )
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
LOCAL_INLINE FUNC(boolean, ADC_CODE) Adc_Adcdig_CheckNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(boolean, AUTOMATIC) bCallNotification = (boolean) FALSE;

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if ((ADC_NOTIFICATION_ENABLED == Adc_GroupStatus[Group].eNotification) && \
        (NULL_PTR != Adc_CfgPtr->pGroups[Group].Notification)
       )
    {
        bCallNotification = (boolean) TRUE;
    }
    return bCallNotification;
}
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_UpdateQueue
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_ENABLE_QUEUING == STD_ON)
    Adc_RemoveFromQueue(Unit, 0U);

    if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
    {
        Adc_Adcdig_StartNormalConversion((Adc_HwUnitType)Unit);
    }
#else
    /* no element will be present in the queue */
    Adc_UnitStatus[Unit].QueueIndex= (Adc_QueueIndexType)0;
#endif /* ADC_ENABLE_QUEUING == STD_ON */
}
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_ClearValidBit
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_ChannelType, AUTOMATIC) ChTemp;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndexTemp;

    /* Clear VALID bit from ADC result registers for all channels assigned to the group when
    conversion is aborted */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for (ChTemp = 0U; ChTemp < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; ChTemp++)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndexTemp = Adc_CfgPtr->pGroups[Group].pAssignment[ChTemp];
        /**
        * @violates @ref Adc_Adcdig_Irq_c_REF_6 Expected void type, assignment, increment or decrement
        * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer
        */
        REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)Adc_CfgPtr->pChannels[Unit][ChIndexTemp].ChId));
    }
}
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )
/**
* @brief @implements Adc_ADCDig_UpdateGroupState_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_UpdateGroupState
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples
)
{
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC)  bCallNotification = (boolean)FALSE;
#endif
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;

    /* At least once the group was converted */
    Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;

    if(ADC_BUSY == Adc_GroupStatus[Group].eConversion)
    {
        Adc_GroupStatus[Group].eConversion = ADC_COMPLETED;
    }

    if (GroupSamples <= Adc_GroupStatus[Group].ResultIndex)
    {
        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if((ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode) && \
           (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)
          )
        {
            /* the following code stop the conversion and abort the current group conversion,
                is important to abort the current, otherwise, another interrupt occurs after the stop */
           /**
            * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
            * @violates @ref Adc_Adcdig_Irq_c_REF_10 the right-hand operand of a logical "&&" or "||" operator
            * shall not contain side effects.
            */
            while((ADC_NORMAL_CONV_ONGOING_U32 == ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_NORMAL_CONV_STATUS_U32)) && (0UL < u32Timeout))
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_RMW32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_CONV_MASK_U32 | ADC_ABORT_CHAIN_U32, ADC_ABORT_CHAIN_U32);
                u32Timeout--;
            }
            /* If the ongoing conversion is not aborted, report the production error */
            if (0UL == u32Timeout)
            {
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();
                /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
                return;
            }

            Adc_Adcdig_ClearValidBit(Unit, Group);

            /* Disable Interrupt Mask */
            /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
            REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32);
            /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
            REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);
            
            Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
            Adc_Adcdig_UpdateQueue(Unit);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            bCallNotification = Adc_Adcdig_CheckNotification(Group);

            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();

            if ((boolean)TRUE == bCallNotification)
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                Adc_CfgPtr->pGroups[Group].Notification();
            }
#else
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */

            /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
            return;
        }
        Adc_GroupStatus[Group].ResultIndex = 0U;
    }

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if (ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)
    {
        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
        Adc_UnitStatus[Unit].eStatus = ADC_COMPLETED;
        /* Disable Interrupt Mask*/
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32);

        Adc_Adcdig_UpdateQueue(Unit);
    }
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);

    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    if ((boolean)TRUE == bCallNotification)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_CfgPtr->pGroups[Group].Notification();
    }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
}
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )
/**
* @brief          This function handles the normal conversion ending.
* @details        When a normal (not injected) conversion ends, and the end of
*                 conversion ISR is called, this function takes care about the
*                 driver and the module state transitions.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_ADCDig_EndNormalConv_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndNormalConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    /* Streaming num samples should be at least 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = 1U;
    VAR(Std_ReturnType, AUTOMATIC) Test = (Std_ReturnType) E_OK;

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_14();

    Group = Adc_UnitStatus[Unit].Queue[0];
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupSamples = Adc_CfgPtr->pGroups[Group].NumSamples;
    Test = Adc_Adcdig_RecordResult(Unit, Group, GroupSamples);

    if ((Std_ReturnType)E_NOT_OK == Test)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if (ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)
        {
            /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
            REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32);
#if (ADC_ENABLE_QUEUING == STD_ON)
            Adc_RemoveFromQueue(Unit, 0U);
            if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
            {
              Adc_Adcdig_StartNormalConversion((Adc_HwUnitType)Unit);
            }
#else
            /* No element will be present in the queue */
            Adc_UnitStatus[Unit].QueueIndex = 0U;
#endif /* ADC_ENABLE_QUEUING == STD_ON */
        }
         /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);

        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();
        /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
        return;
    }
    /* Increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
    Adc_GroupStatus[Group].ResultIndex++;
    Adc_Adcdig_UpdateGroupState(Unit, Group, GroupSamples);
}

/**
* @brief          This function handles the injected conversion ending.
* @details        When a SW injected conversion ends, and the end of
*                 conversion ISR is called, this function takes care about the
*                 driver and the module state transitions.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_ADCDig_EndSwInjectedConv_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndSwInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    /* Streaming num samples should be at least 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = 1U;
    VAR(Std_ReturnType, AUTOMATIC) Test = (Std_ReturnType) E_OK;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC)  bCallNotification = (boolean) FALSE;
#endif

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_24();

    Group = (Adc_UnitStatus[Unit].SwInjQueue[0]);
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupSamples = (Adc_CfgPtr->pGroups[Group].NumSamples);
    Test = Adc_Adcdig_RecordResult(Unit, Group, GroupSamples);

#ifdef ADC_DMA_SUPPORTED
    if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
    {
        if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
        {
            /* Restart normal conversion */
            Adc_Adcdig_StartNormalConversion((Adc_HwUnitType)Unit);
        }
    }
#endif
    if ((Std_ReturnType)E_NOT_OK == Test)
    {
        Adc_GroupStatus[Group].ResultIndex = 0U;
        Adc_UnitStatus[Unit].SwInjQueueIndex = 0U;

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_24();
        /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
        return;
    }

    /* At least once the group was converted */
    Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;

    Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;

    Adc_GroupStatus[Group].ResultIndex = 0U;

    Adc_UnitStatus[Unit].eStatus = ADC_COMPLETED;

    Adc_UnitStatus[Unit].bInjConvOngoing = (boolean)FALSE;

    /* No element will be present in the sw inj queue */
    Adc_UnitStatus[Unit].SwInjQueueIndex = 0U;
    /* Disable Interrupt*/
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_EN_U32);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_24();
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    if ((boolean)TRUE == bCallNotification)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_CfgPtr->pGroups[Group].Notification();
    }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
}

#if (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the injected conversion ending.
* @details        When a HW injected conversion ends, and the end of
*                 conversion ISR is called, this function takes care about the
*                 driver and the module state transitions.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_ADCDig_EndInjectedConv_Activity
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Adcdig_EndInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    /* Streaming num samples should be at least 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = 1U;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC)  bCallNotification = (boolean) FALSE;
#endif
    VAR(Std_ReturnType, AUTOMATIC)  Test = (Std_ReturnType) E_OK;

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_15();

    Group = (Adc_UnitStatus[Unit].HwQueue[0]);
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupSamples = (Adc_CfgPtr->pGroups[Group].NumSamples);
    Test = Adc_Adcdig_RecordResult(Unit, Group, GroupSamples);

    if ((Std_ReturnType)E_NOT_OK == Test)
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
        /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
        return;
    }

    /* Increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
    Adc_GroupStatus[Group].ResultIndex++;
    /* At least once the group was converted */
    Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
    if (ADC_BUSY == Adc_GroupStatus[Group].eConversion)
    {
        Adc_GroupStatus[Group].eConversion = ADC_COMPLETED;
    }

    /* If all samples completed, wrap to 0 */
    if (Adc_GroupStatus[Group].ResultIndex >= GroupSamples)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
        Adc_UnitStatus[Unit].bInjConvOngoing = (boolean)FALSE;

        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if((ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)&& \
           (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)
          )
        {
            /* Stop Conversion */
            /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if(Adc_CfgPtr->pGroups[Group].pHwResource[0] < (Adc_HwTriggerTimerType)ADC_MAX_CTU_EVTCFGREGS)
            {
#if (ADC_BCTU_AVAILABLE == STD_ON)
                /**
                 * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                 * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer
                 */
                Adc_Bctu_DisableInputTrigger(Adc_CfgPtr->pGroups[Group].pHwResource[0]);
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
                /* TODO: Implementation for CTU2 */
#endif /* ADC_BCTU_AVAILABLE == STD_ON */
            }
            else
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);
                /* Disable Interrupt Mask*/
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32);
            }
            Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
            Adc_GroupsInHwQueue(Unit) = 0U;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            if ((boolean) TRUE == bCallNotification)
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                Adc_CfgPtr->pGroups[Group].Notification();
            }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
            /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
            return;
        }
        Adc_GroupStatus[Group].ResultIndex = 0U;
    }

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    if ((boolean) TRUE == bCallNotification)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_CfgPtr->pGroups[Group].Notification();
    }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
}
#endif /* ADC_HW_TRIGGER_API == STD_ON */
#endif /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
    )
#ifdef ADC_DMA_SUPPORTED
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_TransferToInternalBuffer
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_ChannelType, AUTOMATIC) Ch;
    VAR(Adc_ChannelType, AUTOMATIC) FirstChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) PhChIndex;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pResult = Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group] + \
             (Adc_GroupStatus[Group].ResultIndex - 1U);
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    FirstChIndex = (Adc_ChannelType)Adc_CfgPtr->pGroups[Group].FirstCh;
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for (Ch = 0U; Ch < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; Ch++)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndex = (Adc_ChannelType)Adc_CfgPtr->pGroups[Group].pAssignment[Ch];
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        PhChIndex = Adc_CfgPtr->pChannels[Unit][ChIndex].ChId;
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        *(pResult+(Ch*(Adc_CfgPtr->pGroups[Group].NumSamples))) = \
        Adc_Adcdig_DmaInternalResultBuffer[Unit][PhChIndex-FirstChIndex];
    }
}

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaCheckNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC)  bCallNotification = (boolean) FALSE;
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    if ((boolean) TRUE == bCallNotification)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_CfgPtr->pGroups[Group].Notification();
    }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
}
#endif
#endif /* (defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
    )
#if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_ClearDmarRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR0_REG_ADDR32(Unit),ADC_DMAR_RESET_VALUE_U32);
    }
#if (ADC_DMAR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR1_REG_ADDR32(Unit),ADC_DMAR_RESET_VALUE_U32);
    }
#endif /* (ADC_DMAR1_AVAILABLE == STD_ON) */

#if (ADC_DMAR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR2_REG_ADDR32(Unit),ADC_DMAR_RESET_VALUE_U32);
    }
#endif /* (ADC_DMAR2_AVAILABLE == STD_ON) */

    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMAE_RESET_VALUE_U32);
}
/**
* @brief          This function handles the normal conversion via DMA ending.
* @details        When a normal (not injected) conversion ends, and the end of
*                 conversion DMA ISR is called, this function takes care about
*                 the driver and the module state transitions.
*
* @param[in]      Unit        the current HW Unit.
* @param[in]      Group       the handled group.
*
* @return         void
*
* @api
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndNormalConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
    STATIC VAR(Mcl_DmaTcdType *, AUTOMATIC) TcdAddress;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel = 0U;

    /* Increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
    Adc_GroupStatus[Group].ResultIndex++;
    /* At least once the group was converted */
    Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;

    if (ADC_BUSY == Adc_GroupStatus[Group].eConversion)
    {
        Adc_GroupStatus[Group].eConversion = ADC_COMPLETED;
    }

    /* If the current group does not contain continuous ADC data channels, that means that the DMA
    transfer copied from the first configured ADC channel till the last one, every result,
    and for the user we should give back only the configured channels results.
    DMA, transfers in this case to an internal buffer, not directly to the user defined buffer. */
    if ((Adc_DmaContinuousType)STD_OFF == Adc_GroupStatus[Group].Adc_DmaContinuous)
    {
        Adc_Adcdig_TransferToInternalBuffer(Unit, Group);
    }

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    DmaChannel = (Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit];
    /* If all samples completed, wrap to 0 */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if (Adc_GroupStatus[Group].ResultIndex >= Adc_CfgPtr->pGroups[Group].NumSamples)
    {
        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)
        {
            /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
            {
                /* The following code stop the conversion and abort the current group conversion,
                    is important to abort the current, otherwise, another interrupt occurs after the stop */
                Adc_Adcdig_ClearDmarRegisters(Unit);

                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
                * @violates @ref Adc_Adcdig_Irq_c_REF_10 the right-hand operand of a logical "&&" or "||" operator
                * shall not contain side effects.
                */
                while((ADC_NORMAL_CONV_ONGOING_U32 == ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_NORMAL_CONV_STATUS_U32)) && (0UL < u32Timeout))
                {
                    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                    REG_RMW32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_CONV_MASK_U32 | ADC_ABORT_CHAIN_U32, ADC_ABORT_CHAIN_U32);
                    u32Timeout--;
                }
                /* If the ongoing conversion is not aborted, report the production error */
                if (0UL == u32Timeout)
                {
                    /* Exit critical region */
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
                    /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
                    return;
                }

                Adc_Adcdig_ClearValidBit(Unit, Group);

                if (Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit] == (uint8)STD_ON) 
                {
                    Mcl_DmaDisableHwRequest(DmaChannel);
                    Mcl_DmaDisableNotification(DmaChannel);
                }

                Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
#if (ADC_ENABLE_QUEUING == STD_ON)
                Adc_RemoveFromQueue(Unit, 0U);
                if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
                {
                    Adc_Adcdig_StartNormalConversion(Unit);
                }
#else
                /* no element will be present in the queue */
                Adc_UnitStatus[Unit].QueueIndex = 0U;
#endif /* ADC_ENABLE_QUEUING == STD_ON */

                Adc_Adcdig_DmaCheckNotification(Group);
                /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
                return;
            }
            else if ((Adc_DmaContinuousType)STD_ON == Adc_GroupStatus[Group].Adc_DmaContinuous)
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                TcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress(DmaChannel);
                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                pResult = Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group];
                /* Configure the destination result address in TCD of the DMA channels */
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                /** Compiler_Warning: It is intended for the address of the element to be passed
                    to the function as an unsigned integer. */
                Mcl_DmaTcdSetDaddr(TcdAddress, (uint32)pResult);
            }
            else
            {
                /* Do nothing for misra check*/
            }
        }
        Adc_GroupStatus[Group].ResultIndex = 0U;
    }
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if (ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode)
    {
        Adc_Adcdig_DmaCheckNotification(Group);

        /* Start the DMA channel */
        if (((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit]) && \
            (ADC_IDLE != Adc_GroupStatus[Group].eConversion) \
           )
        {
            Mcl_DmaEnableHwRequest(DmaChannel);
        }

    }
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    else if (ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)
    {
        Adc_Adcdig_ClearDmarRegisters(Unit);

        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
        {
            /* Disable DMA interrupt */
            Mcl_DmaDisableHwRequest(DmaChannel);
            Mcl_DmaDisableNotification(DmaChannel);
        }

        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
        Adc_UnitStatus[Unit].eStatus = ADC_COMPLETED;
#if (ADC_ENABLE_QUEUING == STD_ON)
        Adc_RemoveFromQueue(Unit, (uint8)0);
        if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
        {
            Adc_Adcdig_StartNormalConversion(Unit);
        }
#else
        /* no element will be present in the queue */
        Adc_UnitStatus[Unit].QueueIndex = 0U;
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
        /* If any conversion is in queue */
        if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
        {
            Adc_Adcdig_StartNormalConversion(Unit);
            /* exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
            /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
            return;
        }
        Adc_Adcdig_DmaCheckNotification(Group);
    }
    else
    {
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
    }
}
#endif /* defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__) */

#ifdef ADC_DMA_SUPPORTED
#if(ADC_HW_TRIGGER_API == STD_ON)
/**
 * @brief   This function handles the Injected conversion via DMA ending.
 * @details When a Injected conversion ends, and the end of
 *          conversion DMA ISR is called, this function takes care about
 *          the driver and the module state.
 *
 * @param[in]   Unit        the current HW Unit.
 * @param[in]   Group       the handled group.
 *
 * @api
 */
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndInjectedConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(volatile uint32, AUTOMATIC) u32Timeout;
    STATIC VAR(Mcl_DmaTcdType *, AUTOMATIC) TcdAddress;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel = 0U;

    Adc_GroupStatus[Group].ResultIndex++;
    /* at least once the group was converted */
    Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;

    if (ADC_BUSY == Adc_GroupStatus[Group].eConversion)
    {
        Adc_GroupStatus[Group].eConversion = ADC_COMPLETED;
    }

    /* If the current group does not contain continuous ADC data channels, that means that
       the DMA transfer copied from the first configured ADC channel till the last one,
       every result, and for the user we should give back only the configured channels results.
       DMA, transfers in this case to an internal buffer, not directly to the user defined buffer.
    */
    if ((Adc_DmaContinuousType)STD_OFF == Adc_GroupStatus[Group].Adc_DmaContinuous)
    {
        Adc_Adcdig_TransferToInternalBuffer(Unit, Group);
    }

    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    DmaChannel = (Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit];

    /* if all samples completed, wrap to 0 */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Pointer arithmetic other than array indexing used */
    if (Adc_GroupStatus[Group].ResultIndex >= Adc_CfgPtr->pGroups[Group].NumSamples)
    {
        Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;

        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)
        {
            /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
            {
                /* The following code stop the conversion and abort the current group conversion,
                is important to abort the current, otherwise, another interrupt occurs after the stop */
                Adc_Adcdig_ClearDmarRegisters(Unit);

                Adc_Adcdig_ClearValidBit(Unit, Group);

                if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
                {
                    Mcl_DmaDisableHwRequest(DmaChannel);
                    Mcl_DmaDisableNotification(DmaChannel);
                }
                /** @violates @ref Adc_Adcdig_Irq_c_REF_6 expected conversion between pointers to a functions
                * @violates @ref Adc_Adcdig_Irq_c_REF_10 Conversion shall not be performed between a pointer
                * to a function and any type other than an integral type */
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);
                Adc_UnitStatus[Unit].eStatus = ADC_IDLE;

                Adc_GroupsInHwQueue(Unit) = 0U;

                Adc_Adcdig_DmaCheckNotification(Group);

                /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
                return;
            }
            else if ((Adc_DmaContinuousType)STD_ON == Adc_GroupStatus[Group].Adc_DmaContinuous)
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                TcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress(DmaChannel);
                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                pResult = Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group];
                /* Configure the destination result address in TCD of the DMA channels */
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                /** Compiler_Warning: It is intended for the address of the element to be passed
                    to the function as an unsigned integer. */
                Mcl_DmaTcdSetDaddr(TcdAddress, (uint32)pResult);
            }
            else
            {
                /* Do nothing for misra check*/
            }
        }
        Adc_GroupStatus[Group].ResultIndex = 0U;
    }

    Adc_Adcdig_DmaCheckNotification(Group);

    /* Start the DMA channel */
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit]) 
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        Mcl_DmaEnableHwRequest(DmaChannel);
    }
}
#endif /* (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__) */
#endif /* defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* (defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || ... */

#if ((defined(ADC_UNIT_0_WDG_ISR_USED)) || (defined(ADC_UNIT_1_WDG_ISR_USED)) || \
     (defined(ADC_UNIT_2_WDG_ISR_USED)) || (defined(ADC_UNIT_3_WDG_ISR_USED)) || \
     ((defined(ADC_WDG_GROUP_SHARED_ISR)) && ((defined(ADC_UNIT_0_ISR_USED)) || \
      (defined(ADC_UNIT_1_ISR_USED)) || (defined(ADC_UNIT_2_ISR_USED)) || \
      (defined(ADC_UNIT_3_ISR_USED)))) \
     )
#if defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
/**
* @brief          This function handles the watchdog interrupt.
* @details        This function handles the watchdog interrupt (clears the
*                 current channel interrupt, and calls the callback function
*                 (if defined).
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_ADCDig_EndWDGInterrupt_Activity
*/
STATIC FUNC(void, ADC_CODE) Adc_Adcdig_EndWdgInterrupt
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(uint32, AUTOMATIC) u32AworReg[3];
    VAR(uint32, AUTOMATIC) u32AworMasks[3] = {0UL, 0UL, 0UL};
    VAR(Adc_ChannelType, AUTOMATIC) Ch = 0U;
    VAR(uint32, AUTOMATIC) u32Mask = 0UL;
    VAR(uint32, AUTOMATIC) u32RegisterIndex = 0UL;

    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    u32AworReg[0] = REG_READ32(ADC_AWORR0_REG_ADDR32(Unit));

#if (ADC_AWORR1_AVAILABLE == STD_ON)
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    u32AworReg[1] = REG_READ32(ADC_AWORR1_REG_ADDR32(Unit));
#endif /* (ADC_AWORR1_AVAILABLE == STD_ON) */

#if (ADC_AWORR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_AworrPresent[Unit][ADC_AWORR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        u32AworReg[2] = REG_READ32(ADC_AWORR2_REG_ADDR32(Unit));
    }
#endif /* (ADC_AWORR2_AVAILABLE == STD_ON) */

    for (Ch = 0U; Ch < Adc_CfgPtr->Misc.aAdc_Channels[Unit]; Ch++)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if (ADC_UNUSED_THRESHOLD != Adc_CfgPtr->pChannels[Unit][Ch].u8ThReg)
        {
            u32RegisterIndex = Adc_Adcdig_u8WdgChannelDescRegIndex[Unit][Ch];
            u32Mask = Adc_Adcdig_u32WdgChannelDescMask[Unit][Ch];
    
            /* Check if watchdog triggered for current channel */
            if((uint32)u32Mask == (u32AworReg[u32RegisterIndex]&(uint32)u32Mask))
            {
                /* Add channel mask to clear the register */
                u32AworMasks[u32RegisterIndex] |= u32Mask;
                /* Call notification (if available) */
                /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                if (Adc_CfgPtr->pChannels[Unit][Ch].WdogNotification != NULL_PTR)
                {
                    /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                    Adc_CfgPtr->pChannels[Unit][Ch].WdogNotification();
                }
            }
        }
    }

    /* Acknowledge all processed channels */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_AWORR0_REG_ADDR32(Unit), u32AworMasks[0]);

#if (ADC_AWORR1_AVAILABLE == STD_ON)
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_AWORR1_REG_ADDR32(Unit), u32AworMasks[1]);
#endif /* (ADC_AWORR1_AVAILABLE == STD_ON) */

#if (ADC_AWORR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_AworrPresent[Unit][ADC_AWORR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_AWORR2_REG_ADDR32(Unit), u32AworMasks[2]);
    }
#endif /* (ADC_AWORR2_AVAILABLE == STD_ON) */
}
#endif /* defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* defined(ADC_UNIT_0_WDG_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
     )
/**
* @brief          This function implements the ISR for the conversion.
* @details        The function implements the ISR for the given hardware Unit.
*                 It's used on both ADC Hardware Units.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_ADCDig_EndGroupConversion_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_EndGroupConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer. */
    VAR(volatile uint32, AUTOMATIC) u32IsrValue = (uint32)REG_READ32(ADC_ISR_REG_ADDR32(Unit));
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer. */
    VAR(volatile uint32, AUTOMATIC) u32ImrValue = (uint32)REG_READ32(ADC_IMR_REG_ADDR32(Unit));
    VAR(boolean, AUTOMATIC) bIsrSpurious = (boolean)TRUE;

    if(NULL_PTR != Adc_CfgPtr)
    {
        if ((ADC_ISR_END_CHAIN_INJ_CONV_U32 == (u32IsrValue&ADC_ISR_END_CHAIN_INJ_CONV_U32)) &&
            (Adc_UnitStatus[Unit].SwInjQueueIndex > (Adc_QueueIndexType)0)
           )
        {
            if (ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32 == (u32ImrValue&ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32))
            {
                Adc_Adcdig_EndSwInjectedConv(Unit);
                /* To get again the right ISR status */
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_CLEAN_U32);
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer. */
                u32IsrValue = REG_READ32(ADC_ISR_REG_ADDR32(Unit));
            }
            else
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_CLEAN_U32);
            }
            bIsrSpurious = (boolean)FALSE;
        }

        if(ADC_ISR_END_CHAIN_NORM_CONV_U32 == (u32IsrValue&ADC_ISR_END_CHAIN_NORM_CONV_U32))
        {
            if (ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32 == (u32ImrValue&ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32))
            {
                Adc_Adcdig_EndNormalConv(Unit);
            }
            else
            {
                /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
                REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);
            }
            bIsrSpurious = (boolean)FALSE;
        }

#if (ADC_HW_TRIGGER_API == STD_ON)
        if ((ADC_ISR_END_CHAIN_INJ_CONV_U32 == (u32IsrValue&ADC_ISR_END_CHAIN_INJ_CONV_U32)) && \
            (Adc_UnitStatus[Unit].HwQueueIndex > (Adc_QueueIndexType)0) \
           )
        {
            if (ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32 == (u32ImrValue&ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32))
            {
                Adc_Adcdig_EndInjectedConv(Unit);
            }
            /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
            REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_CLEAN_U32 | \
                                                  ADC_ISR_END_CHANNEL_INJ_CONV_CLEAN_U32 \
                       );
            bIsrSpurious = (boolean)FALSE;
        }
#endif /* ADC_HW_TRIGGER_API == STD_ON */
    }
    if ((boolean)TRUE == bIsrSpurious)
    {
        /* Clear Interrupt status flags */
        /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32 | \
                                              ADC_ISR_END_CHANNEL_NORM_CONV_U32 | \
                                              ADC_ISR_END_CHAIN_INJ_CONV_CLEAN_U32 | \
                                              ADC_ISR_END_CHANNEL_INJ_CONV_CLEAN_U32 \
                   );
    }
}
#endif  /* (defined(ADC_UNIT_0_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_WDG_ISR_USED)) || (defined(ADC_UNIT_1_WDG_ISR_USED)) || \
     (defined(ADC_UNIT_2_WDG_ISR_USED)) || (defined(ADC_UNIT_3_WDG_ISR_USED)) || \
     ((defined(ADC_WDG_GROUP_SHARED_ISR)) && ((defined(ADC_UNIT_0_ISR_USED)) || \
      (defined(ADC_UNIT_1_ISR_USED)) || (defined(ADC_UNIT_2_ISR_USED)) || \
      (defined(ADC_UNIT_3_ISR_USED)))) \
     )
#if defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
/**
* @brief          This function implements the ISR processing function for the
*                 Wdg interrupts.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements    Adc_ADCDig_WDGThresholdHandler_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_WdgThresholdHandler
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(uint32, AUTOMATIC) u32ActiveInterrupts = 0UL;
    VAR(uint32, AUTOMATIC) u32WtimrValue = 0UL;
   

    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    u32ActiveInterrupts = REG_READ32(ADC_WTISR_REG_ADDR32(Unit));

    /* Read Watchdog Threshold Interrupt Mask Register */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    u32WtimrValue = REG_READ32(ADC_WTIMR_REG_ADDR32(Unit));

    if(NULL_PTR != Adc_CfgPtr)
    {
        if ((u32WtimrValue > 0UL) && (u32ActiveInterrupts > 0UL))
        {
            Adc_Adcdig_EndWdgInterrupt(Unit);
        }
    }
    
    /* Acknowledge all WDG irqs */
    /** @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_WTISR_REG_ADDR32(Unit), u32ActiveInterrupts);    
}
#endif /* defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* defined(ADC_UNIT_0_WDG_ISR_USED) || ... */

#if ((defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || \
     (defined(ADC_UNIT_2_ISR_USED)) || (defined(ADC_UNIT_3_ISR_USED)) \
    )
#if defined( ADC_DMA_SUPPORTED) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR processing function for the
*                 DMA conversions.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_Adcdig_DmaEndGroupConversion_Activity
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DmaEndGroupConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;

    if(NULL_PTR != Adc_CfgPtr)
    {
        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_13();

        if (Adc_UnitStatus[Unit].QueueIndex > 0U)
        {
            Group=Adc_UnitStatus[Unit].Queue[0];
            Adc_Adcdig_DmaEndNormalConv(Unit, Group);
        }
#if(ADC_HW_TRIGGER_API == STD_ON)
        /** @violates @ref Adc_Adcdig_Irq_c_REF_11 The value of an expression of integer type not be implicitly converted */
        else if (Adc_UnitStatus[Unit].HwQueueIndex > 0U)
        {
            Group=Adc_UnitStatus[Unit].HwQueue[0];
            Adc_Adcdig_DmaEndInjectedConv(Unit, Group);
        }
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
        else
        {
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
        }
    }
}
#endif /* defined( ADC_DMA_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* (defined(ADC_UNIT_0_ISR_USED)) || (defined(ADC_UNIT_1_ISR_USED)) || ... */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef ADC_MULTIPLE_HARDWARE_TRIGGERS
#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
/**
* @brief          This function handles the end of a CTU conversion in the case
*                 of multiple hardware trigger.
* @details        When a CTU conversion ends, and the end of
*                 conversion ISR is called, this function takes care about the
*                 driver and the module state transitions.
*
* @param[in]      Unit        the current HW Unit.
*
* @return         void
*
* @api
* @implements     Adc_Adcdig_EndMultipleCtuConv_Activity
*/
FUNC(void, ADC_CODE) Adc_Adcdig_EndMultipleCtuConv
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32TrgSrc
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    VAR(Std_ReturnType, AUTOMATIC) Test = (Std_ReturnType)E_NOT_OK;
    VAR(Adc_GroupType, AUTOMATIC) GrpIndex = 0U;
    /* Streaming num samples should be at least 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = 1U;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC) bCallNotification = (boolean) FALSE;
#endif

    if(NULL_PTR != Adc_CfgPtr)
    {
        /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */ 
        for(GrpIndex = 0U; GrpIndex < Adc_CfgPtr->Misc.aAdc_HwQueueMaxDepth[Unit]; GrpIndex++)
        {
            Group = Adc_Adcdig_MhtChannelGroup[Unit][GrpIndex];
            /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */ 
            pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

            /* check if the current channel is triggered or not... */
            /** @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if(u32TrgSrc == (uint32)pGroupPtr->pHwResource[0])
            {
                break;
            }
        }

        GroupSamples = pGroupPtr->NumSamples;
        /* enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_17();

        Test = Adc_Adcdig_RecordResult(Unit, Group, GroupSamples);

        if((Std_ReturnType)E_NOT_OK == Test)
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_17();
            /** @violates @ref Adc_Adcdig_Irq_c_REF_4 Return statement before end of function. */
            return;
        }
        /*Increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed*/
        Adc_GroupStatus[Group].ResultIndex++;
        /* At least once the group was converted */
        Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;

        if (ADC_BUSY == Adc_GroupStatus[Group].eConversion)
        {
            Adc_GroupStatus[Group].eConversion = ADC_COMPLETED;
        }
        /* If all samples completed, wrap to 0 */
        if (Adc_GroupStatus[Group].ResultIndex >= GroupSamples)
        {
            Adc_GroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;

            if((ADC_STREAM_BUFFER_LINEAR == pGroupPtr->eBufferMode) && \
               (ADC_ACCESS_MODE_STREAMING == pGroupPtr->eAccessMode)
              )
            {
                /* Stop Conversion */
                /**
                 * @violates @ref Adc_Adcdig_Irq_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                 * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer
                 */
                Adc_Bctu_DisableInputTrigger(pGroupPtr->pHwResource[0]);

                Adc_UnitStatus[Unit].HwQueueIndex--;

                if ((Adc_QueueIndexType)0U == Adc_UnitStatus[Unit].HwQueueIndex)
                {
                    Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
                }
            }
            Adc_GroupStatus[Group].ResultIndex = 0U;
        }
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        bCallNotification = Adc_Adcdig_CheckNotification(Group);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_17();
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        if ((boolean) TRUE == bCallNotification)
        {
            /* Call the notification function */
            pGroupPtr->Notification();
        }
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
    }
}
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */
#endif /* ifdef ADC_MULTIPLE_HARDWARE_TRIGGERS  */


#ifdef ADC_UNIT_0_ISR_USED
/*==================================================================================================
                                          ADC HW UNIT 0
==================================================================================================*/
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 0.
* @details        The function implements the ISR for the ADC Hardware Unit 0.
*
* @return         void
*
* @isr
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
ISR(Adc_Adcdig_EndGroupConvUnit0)
{
#ifdef ADC_WDG_GROUP_SHARED_ISR
#ifdef ADC_WDG_SUPPORTED    
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_0);
#endif 
#endif /* ADC_WDG_GROUP_SHARED_ISR */
    Adc_Adcdig_EndGroupConversion((Adc_HwUnitType)ADC_UNIT_0);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}

#ifndef ADC_WDG_GROUP_SHARED_ISR
#if defined( ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
#ifdef ADC_UNIT_0_WDG_ISR_USED
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 0.
* @details        The function implements the ISR for the ADC Hardware Unit 0.
*
* @return         void
*
* @isr
*
* @note           This ISR is only defined if the ADC_WDG_SUPPORTED
*                 is enabled.
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
* @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash 
*/
ISR(Adc_Adcdig_WatchDogThresholdUnit0)
{
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_0);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}
#endif /* ADC_UNIT_0_WDG_ISR_USED */
#endif /* defined( ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* ADC_WDG_GROUP_SHARED_ISR */

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the ADC Hardware Unit 0.
*
* @return         void
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete0()
{
#if defined(ADC_DMA_SUPPORTED)
    Adc_Adcdig_DmaEndGroupConversion((Adc_HwUnitType)ADC_UNIT_0);
#endif
}
#endif /* ADC_UNIT_0_ISR_USED */

#ifdef ADC_UNIT_1_ISR_USED
/*==================================================================================================
                                          ADC HW UNIT 1
==================================================================================================*/
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 1
* @details        The function implements the ISR for the ADC Hardware Unit 1.
*
* @return         void
*
* @isr
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
ISR(Adc_Adcdig_EndGroupConvUnit1)
{
#ifdef ADC_WDG_GROUP_SHARED_ISR
#ifdef ADC_WDG_SUPPORTED    
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_1);
#endif 
#endif /* ADC_WDG_GROUP_SHARED_ISR */    
    Adc_Adcdig_EndGroupConversion((Adc_HwUnitType)ADC_UNIT_1);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}

#ifndef ADC_WDG_GROUP_SHARED_ISR
#if defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
#ifdef ADC_UNIT_1_WDG_ISR_USED
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 1.
* @details        The function implements the ISR for the ADC Hardware Unit 1.
*
* @return         void
*
* @isr
*
* @note           This ISR is only defined if the ADC_WDG_SUPPORTED
*                 is enabled.
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
* @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash 
*/
ISR(Adc_Adcdig_WatchDogThresholdUnit1)
{
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_1);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}
#endif /* ADC_UNIT_1_WDG_ISR_USED */
#endif /* defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* ADC_WDG_GROUP_SHARED_ISR */

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the ADC Hardware Unit 1.
*
* @return         void
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete1()
{
#if defined(ADC_DMA_SUPPORTED)
    Adc_Adcdig_DmaEndGroupConversion((Adc_HwUnitType)ADC_UNIT_1);
#endif
}
#endif /* ADC_UNIT_1_ISR_USED */

#ifdef ADC_UNIT_2_ISR_USED
/*==================================================================================================
                                          ADC HW UNIT 2
==================================================================================================*/
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 2
* @details        The function implements the ISR for the ADC Hardware Unit 2.
*
* @return         void
*
* @isr
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
ISR(Adc_Adcdig_EndGroupConvUnit2)
{
#ifdef ADC_WDG_GROUP_SHARED_ISR
#ifdef ADC_WDG_SUPPORTED    
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_2);
#endif 
#endif /* ADC_WDG_GROUP_SHARED_ISR */
    Adc_Adcdig_EndGroupConversion((Adc_HwUnitType)ADC_UNIT_2);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}

#ifndef ADC_WDG_GROUP_SHARED_ISR
#if defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
#ifdef ADC_UNIT_2_WDG_ISR_USED
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 2.
* @details        The function implements the ISR for the ADC Hardware Unit 2.
*
* @return         void
*
* @isr
*
* @note           This ISR is only defined if the ADC_WDG_SUPPORTED
*                 is enabled.
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
* @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash 
*/
ISR(Adc_Adcdig_WatchDogThresholdUnit2)
{
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_2);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}
#endif /* ADC_UNIT_2_WDG_ISR_USED */
#endif /* defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* ADC_WDG_GROUP_SHARED_ISR */

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the ADC Hardware Unit 2.
*
* @return         void
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete2()
{
#if defined(ADC_DMA_SUPPORTED)
    Adc_Adcdig_DmaEndGroupConversion((Adc_HwUnitType)ADC_UNIT_2);
#endif
}
#endif /* ADC_UNIT_2_ISR_USED  */


#ifdef ADC_UNIT_3_ISR_USED
/*==================================================================================================
                                          ADC HW UNIT 3
==================================================================================================*/
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 3
* @details        The function implements the ISR for the ADC Hardware Unit 3.
*
* @return         void
*
* @isr
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
ISR(Adc_Adcdig_EndGroupConvUnit3)
{
#ifdef ADC_WDG_GROUP_SHARED_ISR
#ifdef ADC_WDG_SUPPORTED    
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_3);
#endif 
#endif /* ADC_WDG_GROUP_SHARED_ISR */    
    Adc_Adcdig_EndGroupConversion((Adc_HwUnitType)ADC_UNIT_3);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}

#ifndef ADC_WDG_GROUP_SHARED_ISR
#if defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__)
#ifdef ADC_UNIT_3_WDG_ISR_USED
/**
* @brief          This function implements the ISR for the conversion done of
*                 the ADC Hardware Unit 3.
* @details        The function implements the ISR for the ADC Hardware Unit 3.
*
* @return         void
*
* @isr
*
* @note           This ISR is only defined if the ADC_WDG_SUPPORTED
*                 is enabled.
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
* @violates @ref Adc_Adcdig_Irq_c_REF_7 Identifier clash 
*/
ISR(Adc_Adcdig_WatchDogThresholdUnit3)
{
    Adc_Adcdig_WdgThresholdHandler((Adc_HwUnitType)ADC_UNIT_3);
    /**
    * @violates @ref Adc_Adcdig_Irq_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_Irq_c_REF_11 cast from int to a different type
    */
    EXIT_INTERRUPT();
}
#endif /* ADC_UNIT_3_WDG_ISR_USED */
#endif /* defined(ADC_WDG_SUPPORTED) || defined(__DOXYGEN__) */
#endif /* ADC_WDG_GROUP_SHARED_ISR */

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the ADC Hardware Unit 3.
*
* @return         void
* @violates @ref Adc_Adcdig_Irq_c_REF_12 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DmaTransferComplete3()
{
#if defined(ADC_DMA_SUPPORTED)
    Adc_Adcdig_DmaEndGroupConversion((Adc_HwUnitType)ADC_UNIT_3);
#endif
}
#endif /*  ADC_UNIT_3_ISR_USED */

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Adcdig_Irq_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_Irq_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif


/** @} */
