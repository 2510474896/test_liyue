/**
*   @file    Adc_Adcdig.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - low level driver source file.
*   @details This is the low level driver source file,mainly implemented for the ADCDig hardware IP.
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
* @section Adc_Adcdig_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section Adc_Adcdig_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* There are different kinds of execution code sections.
*
* @section Adc_Adcdig_c_REF_3
* Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware offset of the controller.
* The address calculated as an unsigned int is passed to  a macro for initializing the
* pointer with that address (ex: see REG_WRITE32 macro).
*
* @section Adc_Adcdig_c_REF_4
* Violates MISRA 2004 Required Rule 14.7, Return statement before end of function.
* The return statement are used to simplify the code structure and easier readability.
*
* @section Adc_Adcdig_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, Cast from pointer to pointer.
* This is used for the Speed optimization of the memory access.
*
* @section Adc_Adcdig_c_REF_6
* Violates MISRA 2004 Required Rule 19.15, Repeated include file .
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Adc_Adcdig_c_REF_7
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that
* 31 characters significance and case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Adcdig_c_REF_8
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
* arithmetic
* This violation is due to the code complexity.
*
* @section Adc_Adcdig_c_REF_9
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to a macro for initializing the pointer with that address.
*
* @section Adc_Adcdig_c_REF_10
* Violates MISRA 2004 Required Rule 8.10, all declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
* This violation is to be used by IPV layer.
*
* @section Adc_Adcdig_c_REF_11
* Violates MISRA 2004 Required Rule 10.1, cast from integer type to different type or
* a wider integer type
* This is used for the Speed optimization of the memory access.
*
* @section Adc_Adcdig_c_REF_12
* Violates MISRA 2004 Required Rule 1.2, place reliance on undefined or unspecified behaviour
* This is used for the code complexity.
*
* @section Adc_Adcdig_c_REF_13
* Violates MISRA 2004 Required Rule 12.4, contain side effects of right-hand operand of a logical && or ||
* This is used for the code complexity.
*
* @section Adc_Adcdig_c_REF_14
* Violates MISRA 2004 Required Rule 13.7, Boolean operations whose results are invariant
* shall not be permitted. The operation is not invariant.
*
* @section Adc_Adcdig_c_REF_15
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function. These objects are used in various parts of the code
*
* @section Adc_Adcdig_c_REF_16
* Violates MISRA 2004 Required Rule 10.3, The value of a complex expression of integer type may
* only be cast to a type that is narrower and of the same signedness as the underlying type of the
* expression.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. All compilers used support more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this Unit
==================================================================================================*/
#include "Adc_Ipw.h"
#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"
/** @violates @ref Adc_Adcdig_c_REF_6 Repeated include file  */
#include "Adc_Reg_eSys_Adcdig.h"
/** @violates @ref Adc_Adcdig_c_REF_6 Repeated include file  */
#include "Adc_Adcdig_CfgEx.h"
#include "SchM_Adc.h"
#include "Adc_Adcdig.h"
/** @violates @ref Adc_Adcdig_c_REF_6 Repeated include file  */
#include "Mcal.h"

#ifdef ADC_DMA_SUPPORTED
  #include "CDD_Mcl.h"
#endif

#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
  /** @violates @ref Adc_Adcdig_c_REF_6 Repeated include file  */
  #include "Dem.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_AR_VENDOR_ID_ADCDIG_C                 43
/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C     4
/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C     0
/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_C  3
#define ADC_SW_MAJOR_VERSION_ADCDIG_C             1
#define ADC_SW_MINOR_VERSION_ADCDIG_C             0
#define ADC_SW_PATCH_VERSION_ADCDIG_C             0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC IPW header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_ADCDIG_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Adcdig.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_ADCDIG_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_SW_MINOR_VERSION_ADCDIG_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_SW_PATCH_VERSION_ADCDIG_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Adcdig.c and Adc_Ipw.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Adcdig header file are of the same vendor */
#if (ADC_AR_VENDOR_ID_ADCDIG_C != ADC_VENDOR_ID_REG)
    #error "Adc_Adcdig.c and Adc_Reg_eSys_Adcdig.h have different vendor ids"
#endif

/* Check if source file and Adc_Reg_eSys_Adcdig header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_C != ADC_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and Adc_Reg_eSys_Adcdig.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Adcdig header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_ADCDIG_C != ADC_SW_MAJOR_VERSION_REG) || \
     (ADC_SW_MINOR_VERSION_ADCDIG_C != ADC_SW_MINOR_VERSION_REG) || \
     (ADC_SW_PATCH_VERSION_ADCDIG_C != ADC_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Adc_Adcdig.c and Adc_Reg_eSys_Adcdig.h are different"
#endif

/* Check if source file and Adc_Adcdig_CfgEx header file are of the same vendor */
#if (ADC_AR_VENDOR_ID_ADCDIG_C != ADC_VENDOR_ID_ADCDIG_CFGEX)
    #error "Adc_Adcdig.c and Adc_Adcdig_CfgEx.h have different vendor ids"
#endif

/* Check if source file and Adc_Adcdig_CfgEx header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_CFGEX) || \
     (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_CFGEX) || \
     (ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_C != ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_CFGEX) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and Adc_Adcdig_CfgEx.h are different"
#endif

/* Check if source file and Adc_Adcdig_CfgEx header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_ADCDIG_C != ADC_SW_MAJOR_VERSION_ADCDIG_CFGEX) || \
     (ADC_SW_MINOR_VERSION_ADCDIG_C != ADC_SW_MINOR_VERSION_ADCDIG_CFGEX) || \
     (ADC_SW_PATCH_VERSION_ADCDIG_C != ADC_SW_PATCH_VERSION_ADCDIG_CFGEX) \
    )
    #error "Software Version Numbers of Adc_Adcdig.c and Adc_Adcdig_CfgEx.h are different"
#endif

/* Check if source file and Adc_Adcdig header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_ADCDIG_C != ADC_VENDOR_ID_ADCDIG)
    #error "Adc_Adcdig.c and Adc_Adcdig.h have different vendor ids"
#endif

/* Check if source file and Adc_Adcdig header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != ADC_AR_RELEASE_MINOR_VERSION_ADCDIG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_ADCDIG_C != ADC_AR_RELEASE_REVISION_VERSION_ADCDIG) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and Adc_Adcdig.h are different"
#endif

/* Check if source file and Adc_Adcdig header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_ADCDIG_C != ADC_SW_MAJOR_VERSION_ADCDIG) || \
     (ADC_SW_MINOR_VERSION_ADCDIG_C != ADC_SW_MINOR_VERSION_ADCDIG) || \
     (ADC_SW_PATCH_VERSION_ADCDIG_C != ADC_SW_PATCH_VERSION_ADCDIG) \
    )
    #error "Software Version Numbers of Adc_Adcdig.c and Adc_Adcdig.h are different"
#endif

/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef ADC_DMA_SUPPORTED
/* Check if source file and DMA header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != MCL_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and CDD_Mcl.h are different"
#endif
#endif
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
 /* Check if source file and Dem header file are of the same version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != DEM_AR_RELEASE_MINOR_VERSION) \
     )
    #error "AutoSar Version Numbers of Adc_Adcdig.c and Dem.h are different"
 #endif
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
  /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Adcdig.c and Mcal.h are different"
 #endif 
   /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_ADCDIG_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_ADCDIG_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Adcdig.c and SilRegMacros.h are different"
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
#define ADC_START_SEC_VAR_NO_INIT_8
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
#include "MemMap.h"

#ifdef ADC_WDG_SUPPORTED
/**
* @brief          Channel descriptions for the WDG interrupts
* @details        Channel descriptions structure for the WDG interrupts.
*/
/** @violates @ref Adc_Adcdig_c_REF_10 internal linkage or external linkage */
/** @violates @ref Adc_Adcdig_c_REF_15 MISRA 2004 Required Rule 8.7, objects shall be defined at block scope */
VAR(uint8, ADC_VAR) Adc_Adcdig_u8WdgChannelDescRegIndex[ADC_MAX_HW_UNITS][ADC_MAX_CHANNEL_PER_HW_UNIT];
#endif /* ADC_WDG_SUPPORTED */

#define ADC_STOP_SEC_VAR_NO_INIT_8
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
#include "MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_32
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
#include "MemMap.h"

#ifdef ADC_WDG_SUPPORTED
/**
* @brief          Channel masks for the WDG interrupts
* @details        Channel masks structure for the WDG interrupts.
*/
/** @violates @ref Adc_Adcdig_c_REF_10 internal linkage or external linkage */
/** @violates @ref Adc_Adcdig_c_REF_15 MISRA 2004 Required Rule 8.7, objects shall be defined at block scope */
VAR(uint32, ADC_VAR) Adc_Adcdig_u32WdgChannelDescMask[ADC_MAX_HW_UNITS][ADC_MAX_CHANNEL_PER_HW_UNIT];
#endif /* ADC_WDG_SUPPORTED */

#define ADC_STOP_SEC_VAR_NO_INIT_32
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
#include "MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
#include "MemMap.h"

#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
/**
* @brief          MHT groups array.
* @details        This array is used to handle the MHT groups in an efficient manner
*                 through the driver code.
*/
/** @violates @ref Adc_Adcdig_c_REF_15 MISRA 2004 Required Rule 8.7, objects shall be defined at block scope */
/** @violates @ref Adc_Adcdig_c_REF_10 External linkage */
VAR(Adc_GroupType, ADC_VAR) Adc_Adcdig_MhtChannelGroup[ADC_MAX_HW_UNITS][ADC_MAX_GROUPS_PER_HW_UNIT];
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef ADC_DMA_SUPPORTED
/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/**
* @brief          Internal buffer used by DMA to transfer blocks with gaps
* @violates @ref Adc_Adcdig_c_REF_10 External linkage
*/
VAR(Adc_ValueGroupType, ADC_VAR) Adc_Adcdig_DmaInternalResultBuffer[ADC_MAX_HW_UNITS][ADC_MAXIMUM_HW_CHANNELS];

/** @violates @ref Adc_Adcdig_c_REF_7 MISRA-C:2004 Rule 1.4: Identifier clash. */
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"
#endif /* ADC_DMA_SUPPORTED */

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
LOCAL_INLINE FUNC(Adc_HwTriggerTimerType, ADC_CODE) Adc_Adcdig_GetIndexOfCtuTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
);
#endif 
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/**
* @brief          Initializes the conversion time registers.
* @details        Initializes the conversion time registers.
*
* @param[in]      Unit            the hardware Unit.
* @param[in]      ConvTime        the value to be written in ADC_CTR0.
* @param[in]      ConvTime1       the value to be written in ADC_CTR1.
* @param[in]      ConvTime2       the value to be written in ADC_CTR2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetCtrRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime,
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1,
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CtrPresent[Unit][ADC_CTR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CTR0_REG_ADDR32(Unit),ConvTime);
    }
#if (ADC_CTR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CtrPresent[Unit][ADC_CTR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CTR1_REG_ADDR32(Unit),ConvTime1);
    }
#else
    (void)ConvTime1;
#endif
#if (ADC_CTR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CtrPresent[Unit][ADC_CTR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_CTR2_REG_ADDR32(Unit),ConvTime2);
    }
#else
    (void)ConvTime2;
#endif
}

/**
* @brief          Initializes the presampling registers.
* @details        Initializes the presampling registers.
*
* @param[in]      Unit               the hardware Unit.
* @param[in]      u32Precision       the value to be written in ADC_PSR0.
* @param[in]      u32Extended        the value to be written in ADC_PSR1.
* @param[in]      u32External        the value to be written in ADC_PRS2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetPsrRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32Precision,
    VAR(uint32, AUTOMATIC) u32Extended,
    VAR(uint32, AUTOMATIC) u32External
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_PsrPresent[Unit][ADC_PSR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_PSR0_REG_ADDR32(Unit), u32Precision);
    }

#if (ADC_PSR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_PsrPresent[Unit][ADC_PSR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_PSR1_REG_ADDR32(Unit), u32Extended);
    }
#else
    (void)u32Extended;
#endif /* (ADC_PSR1_AVAILABLE == STD_ON) */

#if (ADC_PSR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_PsrPresent[Unit][ADC_PSR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_PSR2_REG_ADDR32(Unit), u32External);
    }
#else
    (void)u32External;
#endif /* (ADC_PSR2_AVAILABLE == STD_ON) */
}

/**
* @brief          Initializes the Normal Conversion Mask registers.
* @details        Initializes the Normal Conversion Mask registers.
*
* @param[in]      Unit               the hardware Unit.
* @param[in]      u32Precision       the value to be written in ADC_NCMR0.
* @param[in]      u32Extended        the value to be written in ADC_NCMR1.
* @param[in]      u32External        the value to be written in ADC_NCMR2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetNcmrRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32Precision,
    VAR(uint32, AUTOMATIC) u32Extended,
    VAR(uint32, AUTOMATIC) u32External
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_NcmrPresent[Unit][ADC_NCMR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_NCMR0_REG_ADDR32(Unit), u32Precision);
    }
#if (ADC_JCMR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_NcmrPresent[Unit][ADC_NCMR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_NCMR1_REG_ADDR32(Unit), u32Extended);
    }
#else
    (void)u32Extended;
#endif /* (ADC_JCMR1_AVAILABLE == STD_ON) */

#if (ADC_JCMR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_NcmrPresent[Unit][ADC_NCMR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_NCMR2_REG_ADDR32(Unit), u32External);
    }
#else
    (void)u32External;
#endif /* (ADC_JCMR2_AVAILABLE == STD_ON) */
}

/**
* @brief          Initializes the Injected Conversion Mask registers.
* @details        Initializes the Injected Conversion Mask registers.
*
* @param[in]      Unit               the hardware Unit.
* @param[in]      u32Precision       the value to be written in ADC_JCMR0.
* @param[in]      u32Extended        the value to be written in ADC_JCMR1.
* @param[in]      u32External        the value to be written in ADC_JCMR2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetJcmrRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32Precision,
    VAR(uint32, AUTOMATIC) u32Extended,
    VAR(uint32, AUTOMATIC) u32External
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_JcmrPresent[Unit][ADC_JCMR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_JCMR0_REG_ADDR32(Unit), u32Precision);
    }
#if (ADC_JCMR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_JcmrPresent[Unit][ADC_JCMR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_JCMR1_REG_ADDR32(Unit), u32Extended);
    }
#else
    (void)u32Extended;
#endif /* (ADC_NCMR1_AVAILABLE == STD_ON) */

#if (ADC_JCMR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_JcmrPresent[Unit][ADC_JCMR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_JCMR2_REG_ADDR32(Unit), u32External);
    }
#else
    (void)u32External;
#endif /* (ADC_NCMR2_AVAILABLE == STD_ON) */
}

#if ((ADC_HW_TRIGGER_API == STD_ON) || (ADC_DEINIT_API == STD_ON))
/**
* @brief          Initializes the Channel Interrupt Mask registers.
* @details        Initializes the Channel Interrupt Mask registers.
*
* @param[in]      Unit               the hardware Unit.
* @param[in]      u32Precision       the value to be written in ADC_CIMR0.
* @param[in]      u32Extended        the value to be written in ADC_CIMR1.
* @param[in]      u32External        the value to be written in ADC_CIMR2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetCimrRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32Precision,
    VAR(uint32, AUTOMATIC) u32Extended,
    VAR(uint32, AUTOMATIC) u32External
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CimrPresent[Unit][ADC_CIMR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CIMR0_REG_ADDR32(Unit), u32Precision);
    }
#if (ADC_CIMR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CimrPresent[Unit][ADC_CIMR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CIMR1_REG_ADDR32(Unit), u32Extended);
    }
#else
    (void)u32Extended;
#endif /* (ADC_CIMR1_AVAILABLE == STD_ON) */

#if (ADC_CIMR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CimrPresent[Unit][ADC_CIMR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CIMR2_REG_ADDR32(Unit), u32External);
    }
#else
    (void)u32External;
#endif /* (ADC_CIMR1_AVAILABLE == STD_ON) */
}
#endif /* (ADC_HW_TRIGGER_API == STD_ON) || (ADC_DEINIT_API == STD_ON) */


#if (defined(ADC_DMA_SUPPORTED) || (ADC_DEINIT_API == STD_ON))
/**
* @brief          Initializes the Dma Channel select registers.
* @details        Initializes the Dma Channel select registers.
*
* @param[in]      Unit               the hardware Unit.
* @param[in]      u32Precision       the value to be written in ADC_DMAR0.
* @param[in]      u32Extended        the value to be written in ADC_DMAR1.
* @param[in]      u32External        the value to be written in ADC_DMAR2.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetDmarRegisters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32Precision,
    VAR(uint32, AUTOMATIC) u32Extended,
    VAR(uint32, AUTOMATIC) u32External
)
{
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR0_REG_ADDR32(Unit), u32Precision);
    }
#if (ADC_DMAR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR1_REG_ADDR32(Unit), u32Extended);
    }
#else
    (void)u32Extended;
#endif /* (ADC_CIMR1_AVAILABLE == STD_ON) */

#if (ADC_DMAR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DMAR2_REG_ADDR32(Unit), u32External);
    }
#else
    (void)u32External;
#endif /* (ADC_CIMR1_AVAILABLE == STD_ON) */
}
#endif /* (defined(ADC_DMA_SUPPORTED) || (ADC_DEINIT_API == STD_ON)) */

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
/**
* @brief          Initializes the Ncmr mask for group.
* @details        Initializes the Ncmr mask for group.
*
* @param[in]      pCfgPtr       Pointer to configuration structure.
*
* @return         void
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitNcmrMask
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    volatile VAR(Adc_GroupType,AUTOMATIC) Group = 0U; /* Group Index */
    volatile VAR(Adc_GroupType,AUTOMATIC) GroupIndex = 0U; /* Group Index */

    /* Initialize Group Status structures to beginning values */
    for (Group = 0U; Group < pCfgPtr->GroupCount; Group++)  /* GroupCount = total number of groups */
    {
       /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
        GroupIndex = (Adc_GroupType)pCfgPtr->pGroups[Group].EnableChDisableChGroupIndex;
        if(ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX != GroupIndex)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_NCMRxMask[GroupIndex].Adc_NCMR0 = pCfgPtr->pGroups[Group].u32PrecisionChannel;
    #if (ADC_NCMR1_AVAILABLE == STD_ON)
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_NCMRxMask[GroupIndex].Adc_NCMR1 = pCfgPtr->pGroups[Group].u32ExtendedChannel;
    #endif /* (ADC_NCMR1_AVAILABLE == STD_ON) */
    #if (ADC_NCMR2_AVAILABLE == STD_ON)
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_NCMRxMask[GroupIndex].Adc_NCMR2 = pCfgPtr->pGroups[Group].u32ExternalChannel;
    #endif /* (ADC_NCMR2_AVAILABLE == STD_ON) */
        }
    }
}
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */

/**
* @brief          Initializes the ADC hardware.
* @details        Initializes the ADC hardware as per configuration.
*
* @param[in]      Unit         The hardware Unit.
* @param[in]      pConfigPtr   Pointer to the hardware configuratiojn structure to be used.
*
* @return         void
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitUnitHardware
(
    VAR(Adc_HwUnitType,AUTOMATIC)Unit,
    P2CONST(Adc_Adcdig_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U; /* Hardware index in the structure*/
    VAR(uint32, AUTOMATIC) u32PscrVal;
#ifdef ADC_WDG_SUPPORTED
    VAR(uint32, AUTOMATIC) u32WtimrValue = 0UL; /* watchdog timer temp variable */
#endif /* ADC_WDG_SUPPORTED */
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_ON)
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1 = 0U;
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2 = 0U;
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_ON */ 
#if (ADC_SET_ADC_PRESAMPLE_ONCE == STD_ON) 
    volatile VAR(Adc_GroupType,AUTOMATIC) Group = 0U; /* Group Index */
    VAR(uint32, AUTOMATIC)  u32Precision = 0U;
    VAR(uint32, AUTOMATIC)  u32Extended = 0U;
    VAR(uint32, AUTOMATIC)  u32External = 0U;
#endif /*ADC_SET_ADC_PRESAMPLE_ONCE == STD_ON) */        

    /* enter into power-down mode */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_MCR_REG_ADDR32(Unit),ADC_POWER_DOWN_U32 | ADC_CLOCK_PRESCALER_DIV1_U32);
    
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
    * shall not contain side effects.
    */
    while((ADC_POWERDOWN_STATUS_U32 != ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32)) && (u32Timeout > 0UL))
    {
        u32Timeout--;
    }
    if (0UL == u32Timeout)
    {
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Report production error and return from function. */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
        }
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return; 
    }

    for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
    {
        /* Get the index of hardware Unit in structure which will match with the hardware Unit ID*/
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(Unit == pConfigPtr[HwIndex].AdcHardwareUnitId)
        {
            break;
        }
    }
    /* Write the configured power down exit delay value into PDEDR register */
    /**
    * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
    */
    REG_WRITE32(ADC_PDEDR_REG_ADDR32(Unit),pConfigPtr[HwIndex].u8AdcPwrDownDelay);

    /* comes out from PowerDown */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);

    u32Timeout = ADC_TIMEOUT_COUNTER;
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
    * shall not contain side effects.
    */
    while((ADC_IDLE_OFFSET_STATUS_U32 != ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32)) && (u32Timeout > 0UL))
    {
        u32Timeout--;
    }
    if (0UL == u32Timeout)
    {
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Report production error and return from function. */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
        }
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return; 
    }    

#if (ADC_DSDR_AVAILABLE == STD_ON)
    /* Write the configured mux delay value into DSDR register */
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DsdrPresent[Unit])
    {
        /**
        * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer
        */
        REG_WRITE32(ADC_DSDR_REG_ADDR32(Unit),pConfigPtr[HwIndex].u16AdcMuxDelay);
    }
#endif /* (ADC_DSDR_AVAILABLE == STD_ON) */
    /*ClkPrescaler, Auto Clock Off , Offset Refresh, Right align and overwrite */
    /**
    * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
    */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit),pConfigPtr[HwIndex].u32AdcMainConfig);

#ifdef ADC_WDG_SUPPORTED
    /* Enable WatchDog Threshold Interrupt*/
    u32WtimrValue = ADC_WTH0_LOW_ISR_EN_U32 | ADC_WTH1_LOW_ISR_EN_U32 | ADC_WTH2_LOW_ISR_EN_U32 |
                    ADC_WTH3_LOW_ISR_EN_U32 | ADC_WTH4_LOW_ISR_EN_U32 | ADC_WTH5_LOW_ISR_EN_U32 |
                    ADC_WTH6_LOW_ISR_EN_U32 | ADC_WTH7_LOW_ISR_EN_U32 | ADC_WTH8_LOW_ISR_EN_U32 |
                    ADC_WTH9_LOW_ISR_EN_U32 | ADC_WTH10_LOW_ISR_EN_U32 | ADC_WTH11_LOW_ISR_EN_U32 |
                    ADC_WTH12_LOW_ISR_EN_U32 | ADC_WTH13_LOW_ISR_EN_U32 | ADC_WTH14_LOW_ISR_EN_U32 |
                    ADC_WTH15_LOW_ISR_EN_U32 | ADC_WTH0_HIGH_ISR_EN_U32 | ADC_WTH1_HIGH_ISR_EN_U32 |
                    ADC_WTH2_HIGH_ISR_EN_U32 | ADC_WTH3_HIGH_ISR_EN_U32 | ADC_WTH4_HIGH_ISR_EN_U32 |
                    ADC_WTH5_HIGH_ISR_EN_U32 | ADC_WTH6_HIGH_ISR_EN_U32 | ADC_WTH7_HIGH_ISR_EN_U32 |
                    ADC_WTH8_HIGH_ISR_EN_U32 | ADC_WTH9_HIGH_ISR_EN_U32 | ADC_WTH10_HIGH_ISR_EN_U32 |
                    ADC_WTH11_HIGH_ISR_EN_U32 | ADC_WTH12_HIGH_ISR_EN_U32 | ADC_WTH13_HIGH_ISR_EN_U32 |
                    ADC_WTH14_HIGH_ISR_EN_U32 | ADC_WTH15_HIGH_ISR_EN_U32;

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_WTIMR_REG_ADDR32(Unit), u32WtimrValue);
#endif /* ADC_WDG_SUPPORTED */

    /* Presampling related configurations/initializations */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    u32PscrVal = (uint32)(((uint32)(Adc_CfgPtr->pAdc[HwIndex].u8PreVal0) << 1U) | \
                          ((uint32)(Adc_CfgPtr->pAdc[HwIndex].u8PreVal1) << 3U) |
#if (ADC_EXTERNAL_CH_AVAILABLE == STD_ON)
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                          ((uint32)(Adc_CfgPtr->pAdc[HwIndex].u8PreVal2) << 5U) |
#endif
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                          (uint32)Adc_CfgPtr->pAdc[HwIndex].u8PreConv
                         );
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_PSCR_REG_ADDR32(Unit), u32PscrVal);

#if (ADC_SET_ONCE_REGISTERS_SUPPORTED == STD_ON)
    #if (ADC_SET_ADC_PRESAMPLE_ONCE == STD_ON) 
        for (Group = 0U; Group < Adc_CfgPtr->GroupCount; Group++)  /* GroupCount = total number of groups */
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if (Unit == Adc_GroupUnit(Group))
            {
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                u32Precision |= Adc_CfgPtr->pGroups[Group].u32PrecisionPsr;
        #if (ADC_PSR1_AVAILABLE == STD_ON)                
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                u32Extended |= Adc_CfgPtr->pGroups[Group].u32ExtendedPsr;
        #endif /* (ADC_PSR1_AVAILABLE == STD_ON) */ 
        #if (ADC_PSR2_AVAILABLE == STD_ON)               
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                u32External |= Adc_CfgPtr->pGroups[Group].u32ExternalPsr;
        #endif /* (ADC_PSR2_AVAILABLE == STD_ON) */
            }            
        }
        /* set once presampling for every ADC HW Unit using setting of the all groups belonging to the Unit */
        Adc_Adcdig_SetPsrRegisters(Unit, u32Precision, u32Extended, u32External); 
    #endif /* ADC_SET_ADC_PRESAMPLE_ONCE == STD_ON */  

    #if (ADC_SET_ADC_CONV_TIME_ONCE == STD_ON)
        #if (ADC_CTR1_AVAILABLE == STD_ON)
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ConvTime1 = Adc_CfgPtr->pAdc[HwIndex].ConvTimeNormal1;
        #endif /* (ADC_CTR1_AVAILABLE == STD_ON) */
        #if (ADC_CTR2_AVAILABLE == STD_ON)
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ConvTime2 = Adc_CfgPtr->pAdc[HwIndex].ConvTimeNormal2;
        #endif /* ADC_CTR2_AVAILABLE == STD_ON */
            /*  Program Conversion Time*/
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_Adcdig_SetCtrRegisters(Unit, Adc_CfgPtr->pAdc[HwIndex].ConvTimeNormal, ConvTime1, ConvTime2);
    #endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_ON */
#endif /* ADC_SET_ONCE_REGISTERS_SUPPORTED == STD_ON */  
}

#ifdef ADC_WDG_SUPPORTED
/**
* @brief          Set channel watchdog threshold registers.
* @details        Used to set channel watchdog threshold registers.
*
* @param[in]      Unit        The hardware Unit.
* @param[in]      u8Th        The Threshold register to be used.
* @param[in]      Ch          The hardware Adc channel .
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_SetThresholds
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8Th,
    VAR(Adc_ChannelType, AUTOMATIC) Ch
)
{
    VAR(uint32, AUTOMATIC) u32Mask ;
    VAR(uint32, AUTOMATIC) u32Index = ((uint32)Ch) / 8UL;

    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwselrPresent[Unit][u32Index])
    {
        u32Mask = ((uint32)(u8Th))<<((uint32)((((uint32)Ch)%8UL)*(0x4UL)));
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_CWSELRx_REG_ADDR32(Unit, u32Index), u32Mask);
    }
}

/**
* @brief          Initializes the limit checking hardware.
* @details        Initializes the limit checking hardware configured.
*
* @param[in]      pCfgPtr      Pointer to the configuration structure.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitUnitLimitChecking
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) Index = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) Ch = 0U;
    P2CONST(Adc_Adcdig_ChannelConfigurationType, AUTOMATIC, ADC_APPL_CONST)  pChConf;

    for(HwIndex = 0U; HwIndex < pCfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Unit = pCfgPtr->pAdc[HwIndex].AdcHardwareUnitId;
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        for (Index = 0U; Index < pCfgPtr->pAdc[HwIndex].ConfiguredThCount; Index++)
        {
            /**
             * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer
             * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
             */
            REG_WRITE32(ADC_THRHLRx_REG_ADDR32(Unit, pCfgPtr->pAdc[HwIndex].pThConfigured[Index].u8Register), \
                                                     pCfgPtr->pAdc[HwIndex].pThConfigured[Index].u32ThValues \
                       );
        }

        for(Ch = 0U; Ch < pCfgPtr->Misc.aAdc_Channels[Unit]; Ch++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            pChConf = &(pCfgPtr->pChannels[Unit][Ch]);
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if(ADC_UNUSED_THRESHOLD != pChConf->u8ThReg)
            {
                /* program the CWSEL register (channel watchdog select register) */
                Adc_Adcdig_SetThresholds(Unit, pChConf->u8ThReg, (Adc_ChannelType)pChConf->ChId);
            }
            /* initialize channel descriptions for the WDG ISR */
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_Adcdig_u8WdgChannelDescRegIndex[Unit][Ch]=(uint8)pCfgPtr->pChannels[Unit][Ch].ChId/(uint8)32;
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Adc_Adcdig_u32WdgChannelDescMask[Unit][Ch]=((uint32)1<<(uint32)(pCfgPtr->pChannels[Unit][Ch].ChId%(uint32)32));
        }
    }
}
#endif /* ADC_WDG_SUPPORTED */

#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
/**
* @brief          Initializes the multiple hardware triggers structures.
* @details        Initializes the multiple hardware triggers structures.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitUnitMht
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;

    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0;
            VAR(uint8, AUTOMATIC) u8PosGr = 0U;
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
            for(Group = 0U; Group < pCfgPtr->Misc.aAdc_Groups[Unit]; Group++)
            {
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
                if (ADC_MHT_GROUP_TYPE == pCfgPtr->pGroups[Group].IsMHTGroup)
                {
                    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
                    Adc_Adcdig_MhtChannelGroup[Unit][u8PosGr] = (Adc_GroupType)Group;
                    u8PosGr++;
                }
            }
        }
    }
}
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
#if (ADC_BCTU_AVAILABLE == STD_ON)
/**
* @brief          Initializes the BCTU hardware as configured.
* @details        Initializes the BCTU hardware as configured.
*
* @param[in]      pCfgPtr      Pointer to the configuration structure.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitBctu
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    /* Initialize the CTUV2 hardware units*/
    /** @violates @ref Adc_Adcdig_c_REF_5 Cast from pointer to pointer. */
    Adc_Bctu_Init((const Adc_Bctu_ConfigType *)pCfgPtr->pCtuCfgPtr); /* Initialize the BCTU hardware units*/
}
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
/**
* @brief          Initializes the CTU2 hardware as configured.
* @details        Initializes the CTU2 hardware as configured.
*
* @param[in]      pCfgPtr      Pointer to the configuration structure.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_InitCtu2
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    /* Initialize the CTUV2 hardware units*/
    /** @violates @ref Adc_Adcdig_c_REF_5 Cast from pointer to pointer. */
    Adc_Ctu2_Init((const Adc_Ctu2ConfigType *)pCfgPtr->pCtuCfgPtr); /* Initialize the CTUV2 hardware units*/
    Adc_Ctu2_SetupDma(); /* Also setup the DMA Transfer Descriptors */
}
#endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */

/**
* @brief          This function initializes the ADC hardware module, and the ADC driver.
* @details        This function initializes the ADC hardware module, and the ADC driver.
*
* @param[in]      pCfgPtr      Configuration data pointer.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_Init
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    volatile VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    P2CONST(Adc_Adcdig_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr = pCfgPtr->pAdc;

    /* Enter critical region to avoid ISRs during register reset */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
    Adc_Adcdig_InitNcmrMask(pCfgPtr);
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */

    /* Initialize Unit Status structures */
    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            Adc_Adcdig_InitUnitHardware(Unit, pConfigPtr);
        }
    }

#ifdef ADC_WDG_SUPPORTED
    Adc_Adcdig_InitUnitLimitChecking(pCfgPtr);
#endif /* ADC_WDG_SUPPORTED */

 /* If there are MHT then setup the relation between the physical channels and groups  */
#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
    Adc_Adcdig_InitUnitMht(pCfgPtr);
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
  #if (ADC_BCTU_AVAILABLE == STD_ON)
    Adc_Adcdig_InitBctu(pCfgPtr);
  #elif (ADC_CTUV2_AVAILABLE == STD_ON)
    Adc_Adcdig_InitCtu2(pCfgPtr);
  #endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */

    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();    
}

#if (ADC_DEINIT_API == STD_ON)
/**
* @brief          This function de-initializes the ADC hardware.
*
* @param[in]      Unit      The hardware Unit.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_DeInitHardware
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#ifdef ADC_WDG_SUPPORTED
    VAR(uint8,AUTOMATIC) u8WdgIndex = 0U;
#endif

    /* Enter ADC Unit to power down mode */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_MCR_REG_ADDR32(Unit), ADC_MCR_RESET_VALUE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_RESET_VALUE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_IMR_REG_ADDR32(Unit), ADC_IMR_RESET_VALUE_U32);
    
    Adc_Adcdig_SetCimrRegisters(Unit, ADC_CIMR_RESET_VALUE_U32, ADC_CIMR_RESET_VALUE_U32, ADC_CIMR_RESET_VALUE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_WRITE32(ADC_WTISR_REG_ADDR32(Unit), ADC_WTISR_RESET_VALUE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_WTIMR_REG_ADDR32(Unit), ADC_WTIMR_RESET_VALUE_U32);

#ifdef ADC_DMA_SUPPORTED
    if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
    {
        /* Disable DMA interrupt */
        Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
        Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
    }
#endif /* ifdef ADC_DMA_SUPPORTED */

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMAE_RESET_VALUE_U32);

    Adc_Adcdig_SetDmarRegisters(Unit, ADC_DMAR_RESET_VALUE_U32, ADC_DMAR_RESET_VALUE_U32,
                                ADC_DMAR_RESET_VALUE_U32
                               );
#ifdef ADC_WDG_SUPPORTED
    for (u8WdgIndex = 0U; u8WdgIndex < (uint8)ADC_THRHLR_REGS; u8WdgIndex++)
    {
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_ThrhlrPresent[Unit][u8WdgIndex])
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            REG_WRITE32(ADC_THRHLRx_REG_ADDR32(Unit, u8WdgIndex), ADC_THRHLRx_RESET_VALUE_U32(Unit));
        }
    }
#endif /* ADC_WDG_SUPPORTED */

    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CeocfrPresent[Unit][ADC_CEOCFR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CEOCFR0_REG_ADDR32(Unit),0xFFFFFFFFUL);
    }
#if (ADC_CEOCFR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CeocfrPresent[Unit][ADC_CEOCFR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CEOCFR1_REG_ADDR32(Unit),0xFFFFFFFFUL);
    }
#endif
#if (ADC_CEOCFR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CeocfrPresent[Unit][ADC_CEOCFR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_CEOCFR2_REG_ADDR32(Unit),0xFFFFFFFFUL);
    }
#endif
   /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
   REG_WRITE32(ADC_PSCR_REG_ADDR32(Unit), 0x0UL);

   Adc_Adcdig_SetPsrRegisters(Unit, 0x0UL, 0x0UL, 0x0UL);

   Adc_Adcdig_SetCtrRegisters(Unit, ADC_CTR0_RESET_VALUE_U32, ADC_CTR1_RESET_VALUE_U32, ADC_CTR2_RESET_VALUE_U32);

   Adc_Adcdig_SetNcmrRegisters(Unit, ADC_NCMR_RESET_VALUE_U32, ADC_NCMR_RESET_VALUE_U32, ADC_NCMR_RESET_VALUE_U32);

   Adc_Adcdig_SetJcmrRegisters(Unit, ADC_JCMR_RESET_VALUE_U32, ADC_JCMR_RESET_VALUE_U32, ADC_JCMR_RESET_VALUE_U32);

#ifdef ADC_WDG_SUPPORTED
    /* Watchdog registers */
    for (u8WdgIndex = 0U; u8WdgIndex < (uint8)ADC_CWENR_REGS; u8WdgIndex++)
    {
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwenrPresent[Unit][u8WdgIndex])
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_WRITE32(ADC_CWENRx_REG_ADDR32(Unit, (uint32)u8WdgIndex), ADC_CWENR_RESET_VALUE_U32);
        }
    }

    for (u8WdgIndex = 0U; u8WdgIndex < (uint8)ADC_CWSELR_REGS; u8WdgIndex++)
    {
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwselrPresent[Unit][u8WdgIndex])
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_WRITE32(ADC_CWSELRx_REG_ADDR32(Unit, (uint32)u8WdgIndex), ADC_CWSEL_RESET_VALUE_U32);
        }
    }
#endif /* ADC_WDG_SUPPORTED */

#if (ADC_DSDR_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DsdrPresent[Unit])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_DSDR_REG_ADDR32(Unit), ADC_DSDR_RESET_VALUE_U32);
    }
#endif /* (ADC_DSDR_AVAILABLE == STD_ON) */

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_WRITE32(ADC_PDEDR_REG_ADDR32(Unit), ADC_PDEDR_RESET_VALUE_U32);
    Adc_UnitStatus[Unit].bInjConvOngoing = (boolean)FALSE;
}
#endif /* ADC_DEINIT_API == STD_ON */

#if (ADC_DEINIT_API == STD_ON)
/**
* @brief          This function de-initializes the ADC driver, and the ADC hardware.
* @details        This function de-initializes the ADC driver, and ensures that the ADC hardware
*                 will be in the power on after reset state.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DeInit(void)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
#if ((ADC_GRP_NOTIF_CAPABILITY == STD_ON) || (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON))
    VAR(Adc_GroupType,AUTOMATIC) GroupIdx = 0U;
  #if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
    VAR(Adc_GroupType, AUTOMATIC) GroupIndex = 0U;
  #endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* Enter critical region to avoid ISRs during register reset */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_06();

    for(;Unit<(Adc_HwUnitType)ADC_MAX_HW_UNITS;Unit++)
    {
        /* ADC111-- ADC110*/
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            Adc_Adcdig_DeInitHardware(Unit);
        }
    }

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
  #if (ADC_BCTU_AVAILABLE == STD_ON)
    Adc_Bctu_DeInit();
  #elif (ADC_CTUV2_AVAILABLE == STD_ON)
    Adc_Ctu2_DeInit();
  #endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
#endif /* (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON) */

#if ((ADC_GRP_NOTIF_CAPABILITY == STD_ON) || (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON))
    for(GroupIdx = 0U; GroupIdx < (Adc_GroupType)ADC_MAX_GROUPS; GroupIdx++)
    {
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        Adc_GroupStatus[GroupIdx].eNotification = ADC_NOTIFICATION_DISABLED;
    #endif  /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    #if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
        GroupIndex = (Adc_GroupType)Adc_CfgPtr->pGroups[GroupIdx].EnableChDisableChGroupIndex;
        if(ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX != GroupIndex)
        {
            Adc_NCMRxMask[GroupIndex].Adc_NCMR0 = (uint32)ADC_NCMR_RESET_VALUE_U32;
        #if (ADC_NCMR1_AVAILABLE == STD_ON)
            Adc_NCMRxMask[GroupIndex].Adc_NCMR1 = (uint32)ADC_NCMR_RESET_VALUE_U32;
        #endif
        #if (ADC_NCMR2_AVAILABLE == STD_ON)
            Adc_NCMRxMask[GroupIndex].Adc_NCMR2 = (uint32)ADC_NCMR_RESET_VALUE_U32;
        #endif
        }
    #endif  /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
    }
#endif /* ((ADC_GRP_NOTIF_CAPABILITY == STD_ON) || (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON))*/

    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_06();
}
#endif /* #if (ADC_DEINIT_API == STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
* @brief          This function stops the current conversion.
* @details        This function stops the current conversion and checks if the hardware has responded to the command.
*
* @param[in]      Unit      The hardware Unit.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            If the conversion has stopped as expected.
* @retval         E_NOT_OK        In case of timeout while waiting for adc hardware to stop a conversion.
*
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_StopConversionCheckTimeout
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(boolean, AUTOMATIC) bStartApi
)
{
    VAR(uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;

    do
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_RMW32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_CONV_MASK_U32 | ADC_ABORT_CHAIN_U32, ADC_ABORT_CHAIN_U32); 
        u32Timeout--;
    }
    /**
     * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer
     * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator shall not contain side effects.
     */
    while((ADC_NORMAL_CONV_ONGOING_U32 == ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_NORMAL_CONV_STATUS_U32)) && (0UL < u32Timeout));

    if (0UL == u32Timeout)
    {
        if ((boolean)TRUE == bStartApi)
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();
        }
        else
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
        }
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            /* Report production error and return from function. */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
        }
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return (Std_ReturnType) E_NOT_OK;
    }
    return (Std_ReturnType) E_OK;
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
* @brief          This function stops the current conversion of a group.
* @details        This function stops the current conversion of a group.
*
* @param[in]      Unit      The hardware Unit.
* @param[in]      Group     The group id.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            If the conversion has stopped as expected.
* @retval         E_NOT_OK        In case of timeout while waiting for adc hardware to stop a conversion.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_StopCurrentConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(boolean, AUTOMATIC) bStartApi
)
{
    VAR(Std_ReturnType, AUTOMATIC) Test = (Std_ReturnType)E_OK;
    VAR(Adc_ChannelType, AUTOMATIC) ChTemp;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndexTemp;

#ifdef ADC_DMA_SUPPORTED
    if (ADC_INTERRUPT == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
#endif /* ADC_DMA_SUPPORTED */
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CONV_MASK_U32);
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);
    }
#ifdef ADC_DMA_SUPPORTED
    else /* Is DMA driven: Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware == ADC_DMA */
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMAE_RESET_VALUE_U32);

        Adc_Adcdig_SetDmarRegisters(Unit, ADC_DMAR_RESET_VALUE_U32, ADC_DMAR_RESET_VALUE_U32,
                                    ADC_DMAR_RESET_VALUE_U32
                                   );
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
        {
            Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
            Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
        }
    }
#endif /* ADC_DMA_SUPPORTED */
    /*  stop the conversion and abort the current group conversion */
#if (ADC_BYPASS_CONSISTENCY_LOOP == STD_ON)
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if((uint8)STD_ON == Adc_CfgPtr->pGroups[Group].u8AdcWithoutInterrupt)
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_RMW32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_CONV_MASK_U32 | ADC_ABORT_CHAIN_U32, ADC_ABORT_CHAIN_U32); 
    }
    else
    {
        Test = Adc_Adcdig_StopConversionCheckTimeout(Unit, bStartApi);
    }
#else /* (ADC_BYPASS_CONSISTENCY_LOOP == STD_ON) */
        Test = Adc_Adcdig_StopConversionCheckTimeout(Unit, bStartApi);
#endif /* (ADC_BYPASS_CONSISTENCY_LOOP == STD_OFF) */
    /* Clear the ABORT_CHAIN bit if set, otherwise the next chain will be ABORTED without any End of Chain Interrupt */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer. */
    if (REG_READ32(ADC_MCR_REG_ADDR32(Unit))&ADC_ABORT_CHAIN_U32)
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer. */
        REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_ABORT_CHAIN_U32);
    }

    if ((Std_ReturnType)E_NOT_OK == Test)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return Test;
    }
    /* clear VALID bit from ADC result registers for all channels assigned to the group
        when conversion is aborted */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for(ChTemp = 0U; ChTemp < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; ChTemp++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndexTemp = Adc_CfgPtr->pGroups[Group].pAssignment[ChTemp];
        /**
        * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer
        */
        REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)Adc_CfgPtr->pChannels[Unit][ChIndexTemp].ChId));
    }
    return Test;
}
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#ifdef ADC_WDG_SUPPORTED
/**
* @brief          This function configures the CWENRx registers.
* @details        This function configures the CWENRx registers.
*
* @param[in]      pGroupPtr   Pointer to group of which conversion will be started.
* @param[in]      Unit        The hardware Unit. (on other platforms there are more hw units)
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_ConfigureCwenrRegiters
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr
)
{
    /* Enable the Watchdog only on configured channels */
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwenrPresent[Unit][ADC_CWENR0_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_CWENR0_REG_ADDR32(Unit), pGroupPtr->u32Wer0);
    }
#if (ADC_CWENR1_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwenrPresent[Unit][ADC_CWENR1_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_CWENR1_REG_ADDR32(Unit), pGroupPtr->u32Wer1);
    }
#endif /* (ADC_CWENR1_AVAILABLE == STD_ON) */
#if (ADC_CWENR2_AVAILABLE == STD_ON)
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_CwenrPresent[Unit][ADC_CWENR2_INDEX])
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_CWENR2_REG_ADDR32(Unit), pGroupPtr->u32Wer2);
    }
#endif /* (ADC_CWENR2_AVAILABLE == STD_ON) */
}
#endif /* ADC_WDG_SUPPORTED */

#if (ADC_READ_GROUP_API == STD_ON)
/**
* @brief          This function reads the converted data for the requested group.
* @details        Reads the converted data for the requested group.
*
* @param[in]      Group           The group number.
* @param[in]      pDataPtr        Pointer to a buffer which will be filled by the
*                                 conversion results.
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful read of the converted data.
* @retval         E_NOT_OK        In case of an ongoing conversion.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_ReadGroup
(
    CONST(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataPtr,
    P2VAR(boolean, AUTOMATIC, ADC_APPL_DATA) pFlag
)
{
    VAR(Std_ReturnType, AUTOMATIC) ReadGroupRet = (Std_ReturnType)E_OK;
    /* Pointer to AdcGroup */
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

    /* If the group is configured for without interrupts*/
    if((uint8)STD_ON == pGroupPtr->u8AdcWithoutInterrupt)
    {
        VAR(uint32, AUTOMATIC) u32CdrValue;
        VAR(uint32, AUTOMATIC) u32CdrMask = ADC_CDR_DATA_MASK_U32;
        VAR(Adc_ChannelType, AUTOMATIC) Channel;
        VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
        VAR(Adc_HwUnitType, AUTOMATIC) Unit;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
        P2CONST(Adc_Adcdig_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr = Adc_CfgPtr->pAdc;
        VAR(Adc_ChannelType, AUTOMATIC) Shift = 0U;
        VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /* Flag to set if ADC results are in the selected range */
        VAR(boolean, AUTOMATIC) bWriteFlag = (boolean)TRUE;
        VAR(uint16, AUTOMATIC) u16CdrValueTemp = 0U;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_09();

        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Unit = Adc_GroupUnit(Group);

        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        u32CdrValue = REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)pGroupPtr->LastCh));
        if(0UL == (u32CdrValue&ADC_VALID_DATA_MASK_U32))
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();
            /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
            return (Std_ReturnType)E_NOT_OK;
        }
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
        for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
        {
            /* Get the index of hardware Unit in structure which will match with the hardware Unit ID*/
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if(Unit == pConfigPtr[HwIndex].AdcHardwareUnitId)
            {
                break;
            }
        }
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Shift = (16U - (pConfigPtr[HwIndex].Res));
        u32CdrMask = (uint32)(ADC_CDR_DATA_MASK_U32 << Shift);
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */

        /* Copy result direct from ADC result registers to output data array */
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        for(Channel = 0U; Channel < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; Channel++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ChIndex = Adc_CfgPtr->pGroups[Group].pAssignment[Channel];
            /**
            * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer
            */
            u32CdrValue = REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)Adc_CfgPtr->pChannels[Unit][ChIndex].ChId));
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if ((boolean)TRUE == Adc_CfgPtr->pChannels[Unit][ChIndex].bChannelLimitCheck)
            {
    #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
                u16CdrValueTemp = (uint16)((u32CdrValue&ADC_SHIFT_MASK_U32) >> Shift);
    #else
                u16CdrValueTemp = (uint16)(u32CdrValue&u32CdrMask);
    #endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */
                (*pFlag) = (boolean)Adc_CheckConversionValuesInRange(u16CdrValueTemp, Unit, ChIndex);
                if ((boolean)FALSE == (*pFlag))
                {
                    /* ADC448, ADC449, ADC450 */
                    ReadGroupRet = (Std_ReturnType)E_NOT_OK;
                    bWriteFlag = (boolean)FALSE;
                }
            }
            if((boolean)TRUE == bWriteFlag)
#else
            (*pFlag) = (boolean)TRUE;
#endif /* ADC_ENABLE_LIMIT_CHECK == STD_ON */
            {
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                *(pDataPtr + (Channel)) = (uint16)(u32CdrValue&u32CdrMask);
            }
        }
    }
    else  /* If the group is configured with interrupts*/
    {
        VAR(uint8, AUTOMATIC) u8Count = 0U;
        P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResultPtr = NULL_PTR;
        VAR(uint32, AUTOMATIC) u32DestOffset = 0UL;
        VAR(volatile Adc_StreamNumSampleType, AUTOMATIC) ResultIndex = 0U;

        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_09();
        if (ADC_BUSY == Adc_GroupStatus[Group].eConversion)
        {
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();
            /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
            return (Std_ReturnType)E_NOT_OK;
        }
        /* Get index of last completed sample */
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ResultIndex = Adc_GroupStatus[Group].ResultIndex - (Adc_StreamNumSampleType)1;
        if ((Adc_StreamNumSampleType)0 == Adc_GroupStatus[Group].ResultIndex)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ResultIndex = Adc_CfgPtr->pGroups[Group].NumSamples - (Adc_StreamNumSampleType)1;
        }

        /**
        * @violates @ref Adc_Adcdig_c_REF_5 Cast from pointer to pointer.
        * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
        */
        pResultPtr=(Adc_ValueGroupType *)(Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group]+ResultIndex);
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        u32DestOffset = Adc_CfgPtr->pGroups[Group].NumSamples;

        /* Copy results of last conversion from streaming buffer to internal buffer */
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        for(u8Count = 0U; u8Count < (Adc_CfgPtr->pGroups[Group].AssignedChannelCount); u8Count++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            pDataPtr[u8Count] = (*pResultPtr);
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            pResultPtr += u32DestOffset;
        }
    }
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();

    return(ReadGroupRet);
}
#endif /* (ADC_READ_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
/**
* @brief          This function enables the hardware triggers for the specified group.
* @details        This function enables the hardware triggers for the specified group.
*
* @param[in]      Group           The group for which the hardware triggers will be enabled.
* @param[in]      Unit            The hardware Unit. (on other platforms there are more hw units)
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_EnableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr; /* Pointer to AdcGroup */
    VAR(uint32, AUTOMATIC)  u32Mcr_ClearVal = 0UL;
    VAR(uint32, AUTOMATIC)  u32Mcr_SetVal = ADC_INJ_EXT_TRIGGER_EN_U32;
    VAR(uint32, AUTOMATIC)  u32Precision = 0x0UL;
    VAR(uint32, AUTOMATIC)  u32Extended = 0x0UL;
    VAR(uint32, AUTOMATIC)  u32External = 0x0UL;
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1 = 0U;
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2 = 0U;
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */

    /* Enter critical section */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_10();
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

#ifdef ADC_WDG_SUPPORTED
    Adc_Adcdig_ConfigureCwenrRegiters(Unit, pGroupPtr);
#endif /* ADC_WDG_SUPPORTED */

#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    #if (ADC_CTR1_AVAILABLE == STD_ON)
    ConvTime1 = pGroupPtr->ConvTime1;
    #endif
    #if (ADC_CTR2_AVAILABLE == STD_ON)
    ConvTime2 = pGroupPtr->ConvTime2;
    #endif
    /*  Program Conversion Time*/
    Adc_Adcdig_SetCtrRegisters(Unit, pGroupPtr->ConvTime, ConvTime1, ConvTime2);
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */

    /* If the triggers are come from CTU */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if(pGroupPtr->pHwResource[0] < (Adc_HwTriggerTimerType)ADC_MAX_CTU_EVTCFGREGS)
    {
        /* Switch to CTU trigger mode, ADC must be switched to power down mode to modify this bit */
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32 | ADC_CTU_TRIGGER_MODE_U32);
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
#ifdef ADC_DMA_SUPPORTED
        if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
        {
            /* If the group is configured for with interrupts*/
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
            if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
            {
                /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_SET32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMA_GLOBAL_EN_U32);
                Adc_Adcdig_StartDmaOperation(Unit);
            }
        }
#endif /* ADC_DMA_SUPPORTED */

#if (ADC_BCTU_AVAILABLE == STD_ON)
        /* Configure for BCTU trigger */
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_Bctu_EnableCtuTrigger(pGroupPtr, pGroupPtr->pHwResource[0], (boolean)TRUE, (boolean)TRUE);
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
        /* DODO: Implementation for CTU2 */
#endif /* ADC_BCTU_AVAILABLE == STD_ON */
    }
    else
    {
        /* Program the mask registers */
        u32Precision = pGroupPtr->u32PrecisionChannel;
#if (ADC_JCMR1_AVAILABLE == STD_ON)
        u32Extended = pGroupPtr->u32ExtendedChannel;
#endif /* (ADC_JCMR1_AVAILABLE == STD_ON) */
#if (ADC_JCMR2_AVAILABLE == STD_ON)
        u32External = pGroupPtr->u32ExternalChannel;
#endif /* (ADC_JCMR2_AVAILABLE == STD_ON) */
        /* Program the Injected Conversion Mask register */
        Adc_Adcdig_SetJcmrRegisters(Unit, u32Precision, u32Extended, u32External);
        /* Clear Interrupt status flag and CTU interrupt flag */
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_U32 | ADC_ISR_END_CHANNEL_CTU_CONV_CLEAN_U32);

        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
        {
            Adc_Adcdig_SetCimrRegisters(Unit, u32Precision, u32Extended, u32External);
        }
#ifdef ADC_DMA_SUPPORTED
        if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
        {
            /* If the group is configured for with interrupts*/
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
            if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
            {
                /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_SET32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMA_GLOBAL_EN_U32);
                Adc_Adcdig_StartDmaOperation(Unit);
            }
        }
        else
#endif /* ADC_DMA_SUPPORTED */
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
            {
                /* Enable Interrupt*/
                /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
                REG_BIT_SET32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_EN_U32);
            }
            else
            {
                /* Disable Interrupt*/
                /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
                REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_EN_U32);
            }
        }

        /* Select the Edge*/
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(ADC_HW_TRIG_RISING_EDGE == pGroupPtr->eTriggerEdge)
        {
            u32Mcr_SetVal = ADC_INJ_TRIGGER_EDGE_U32;
        }
        else
        {
            u32Mcr_ClearVal = ADC_INJ_TRIGGER_EDGE_U32;
        }

        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), u32Mcr_SetVal);
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), u32Mcr_ClearVal);
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);
    }
    /* Exit critical section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_10();
}
/**
* @brief          This function disables the hardware triggers for the specified group.
* @details        This function disables the hardware triggers for the specified group.
*
* @param[in]      Group           The group for which the hardware triggers will be enabled.
* @param[in]      Unit            The hardware Unit. (on other platforms there are more hw units)
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DisableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr; /* Pointer to AdcGroup */

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if(pGroupPtr->pHwResource[0] < (Adc_HwTriggerTimerType)ADC_MAX_CTU_EVTCFGREGS)
    {
#if (ADC_BCTU_AVAILABLE == STD_ON)
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_Bctu_DisableCtuTrigger(pGroupPtr, pGroupPtr->pHwResource[0], (boolean)TRUE);
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
        /* TODO: Implementation for CTU2 */
#endif /* ADC_BCTU_AVAILABLE == STD_ON */
    }

#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
    if ((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].HwQueueIndex)
    {
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */
#ifdef ADC_DMA_SUPPORTED
        if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
        {
            /* Disable DMA */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            REG_WRITE32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMAE_RESET_VALUE_U32);

            Adc_Adcdig_SetDmarRegisters(Unit, ADC_DMAR_RESET_VALUE_U32, ADC_DMAR_RESET_VALUE_U32,
                                        ADC_DMAR_RESET_VALUE_U32
                                       );
            if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
            {
                /* Disable DMA interrupt */
                Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
                Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit]);
            }
        }
#endif /* ADC_DMA_SUPPORTED */
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((Adc_HwTriggerTimerType)ADC_MAX_CTU_EVTCFGREGS > pGroupPtr->pHwResource[0])
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHANNEL_CTU_CONV_CLEAN_U32);
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            /* Disable CTU in ADC MCR register is done into deinit funtion */
            REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);
        }
        else
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);
        }
#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32);
        /* reset the queue group status to regular ones... */
        Adc_UnitStatus[Unit].HwQueueGroupType = (Adc_MhtGroupType)ADC_REGULAR_GROUP_TYPE;
    }
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */

    /* Clear interrupt flags Interrupt Status */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_RMW32(ADC_ISR_REG_ADDR32(Unit), (ADC_ISR_END_CHAIN_NORM_CONV_U32 |ADC_ISR_END_CHANNEL_NORM_CONV_U32), \
             (ADC_ISR_END_CHAIN_INJ_CONV_U32|ADC_ISR_END_CHANNEL_INJ_CONV_U32|ADC_ISR_END_CHANNEL_CTU_CONV_U32) \
             );
    /* Disable Interrupt Mask*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32);
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();
}

#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
LOCAL_INLINE FUNC(Adc_HwTriggerTimerType, ADC_CODE) Adc_Adcdig_GetIndexOfCtuTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) Index = 0U;
    
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for(Index = 0U; Index < Adc_CfgPtr->pGroups[Group].AssignedTriggerCount; Index++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(TriggerSource == Adc_CfgPtr->pGroups[Group].pHwResource[Index])
        {
            break;
        }
    }
    return Index;
}

/**
* @brief          This function enables the hardware trigger for the specified group.
* @details        Non autosar API to enable the trigger source configured for the group.
*
* @param[in]      Group           The group for which the hardware triggers will be enabled.
* @param[in]      TriggerSource   Trigger source to be use for the group
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_EnableCtuTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
    /* Pointer to AdcGroup */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);
    VAR(uint32, AUTOMATIC) u32Mcr_ClearVal = 0UL;
    VAR(uint32, AUTOMATIC) u32Mcr_SetVal = ADC_INJ_EXT_TRIGGER_EN_U32;
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1 = 0U;
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2 = 0U;
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) Index = 0U;
    VAR(boolean, AUTOMATIC) bFirstTrigger = (boolean)TRUE;
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for(Index = 0U; Index < Adc_CfgPtr->pGroups[Group].AssignedTriggerCount; Index++)
    {
        if(0U != Adc_u8BctuGroupTriggersActive[Unit][Index])
        {
            bFirstTrigger = (boolean)FALSE;
            break;
        }
    }    

    Index = Adc_Adcdig_GetIndexOfCtuTrigger(Group, TriggerSource);
    Adc_u8BctuGroupTriggersActive[Unit][Index] = 1U;

#if (ADC_BCTU_AVAILABLE == STD_ON)
    Adc_Bctu_EnableCtuTrigger(pGroupPtr, TriggerSource, (boolean)FALSE, bFirstTrigger);
#endif /* ADC_BCTU_AVAILABLE == STD_ON */

    if ((boolean)FALSE == bFirstTrigger)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }       
    /* Enter critical section */    
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_21();
    
    Adc_UnitStatus[Unit].HwQueue[Adc_UnitStatus[Unit].HwQueueIndex] = Group;
    Adc_UnitStatus[Unit].HwQueueIndex++;

    /* ADC222*/
    /* Mark the Group as BUSY when the Group goes to the Queue or gets started */
    Adc_GroupStatus[Group].eConversion = ADC_BUSY;

    /* if HW trigger is enabled for a group, its CTU trigger status becomes ENABLED */
    Adc_GroupStatus[Group].eCtuTriggering = ADC_HWTRIGGER_ENABLED;

    /* ADC432 */
    /* Put the conversion results from Results Buffer Base Address */
    Adc_GroupStatus[Group].ResultIndex = 0U;

    /*Mark the Unit as BUSY */
    Adc_UnitStatus[Unit].eStatus = ADC_BUSY;
    
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    #if (ADC_CTR1_AVAILABLE == STD_ON)
    ConvTime1 = pGroupPtr->ConvTime1;
    #endif
    #if (ADC_CTR2_AVAILABLE == STD_ON)
    ConvTime2 = pGroupPtr->ConvTime2;
    #endif
    /*  Program Conversion Time*/
    Adc_Adcdig_SetCtrRegisters(Unit, pGroupPtr->ConvTime, ConvTime1, ConvTime2);
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit),ADC_POWER_DOWN_U32);
    /* Enable CTU trigger, put ADC to CTU trigger mode */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32 | ADC_CTU_TRIGGER_MODE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);

    /* Disable Interrupt Mask*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_MASK_U32 | \
                                              ADC_ISR_END_CHANNEL_CTU_CONV_U32 \
                   );
    /* Select the Edge*/
    if(ADC_HW_TRIG_RISING_EDGE == pGroupPtr->eTriggerEdge)
    {
        u32Mcr_SetVal |= ADC_INJ_TRIGGER_EDGE_U32;
    }
    else
    {
        u32Mcr_ClearVal = ADC_INJ_TRIGGER_EDGE_U32;
    }

    /* Configure trigger edge for the group */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), u32Mcr_SetVal);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), u32Mcr_ClearVal);

    /* Exit critical section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_21();
    
}

/**
* @brief          This function disables the hardware trigger for the specified group.
* @details        Non autosar API to disable the trigger source configured for the group.
*
* @param[in]      Group           The group for which the hardware triggers will be disabled.
* @param[in]      TriggerSource   Trigger source to be use for the group
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_DisableCtuTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) Index = 0U;
    VAR(boolean, AUTOMATIC) bLastTrigger = (boolean)TRUE;
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for(Index = 0U; Index < Adc_CfgPtr->pGroups[Group].AssignedTriggerCount; Index++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((0U != Adc_u8BctuGroupTriggersActive[Unit][Index]) && \
            (TriggerSource != Adc_CfgPtr->pGroups[Group].pHwResource[Index])
           )
        {
            bLastTrigger = (boolean)FALSE;
            break;
        }
    }
    Index = Adc_Adcdig_GetIndexOfCtuTrigger(Group, TriggerSource);
    Adc_u8BctuGroupTriggersActive[Unit][Index] = 0U;
    
#if (ADC_BCTU_AVAILABLE == STD_ON)
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    Adc_Bctu_DisableCtuTrigger(&(Adc_CfgPtr->pGroups[Group]), TriggerSource, bLastTrigger);
#endif /* ADC_BCTU_AVAILABLE == STD_ON */

    if ((boolean)FALSE == bLastTrigger)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }
    
     /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_22();

    Adc_GroupStatus[Group].eCtuTriggering = ADC_HWTRIGGER_DISABLED;

    if(Adc_UnitStatus[Unit].HwQueueIndex > 0U)
    {
        /* ADC429 */
        Adc_UnitStatus[Unit].HwQueueIndex--;
    }
    
    /*Mark the group as IDLE */
    Adc_GroupStatus[Group].eConversion = ADC_IDLE;
    
    /*Mark the Unit as IDLE */
    Adc_UnitStatus[Unit].eStatus = ADC_IDLE;

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit),ADC_POWER_DOWN_U32);
    /* Disable CTU trigger, disable CTU trigger mode */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32 | ADC_CTU_TRIGGER_MODE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);

    /* Clear interrupt mask register*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHANNEL_CTU_CONV_CLEAN_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_EXT_TRIGGER_EN_U32);

    /* Clear Interrupt status flag and CTU interrupt flag */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_U32 | \
                                          ADC_ISR_END_CHANNEL_INJ_CONV_CLEAN_U32 | \
                                          ADC_ISR_END_CHANNEL_CTU_CONV_CLEAN_U32 \
               );
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_22();
}

/**
* @brief          This function reads the data from the ADC channel hardware data register.
* @details        This non Autosar API is used to copy the data from the ADC channel
*                 hardware data register to the ADC group result buffer.
*
* @param[in]      Group           The group for which the data will be read.
* @param[in]      pDataPtr        Pointer to a buffer which will be filled by the
*                                 conversion results.
*

* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful read of the converted data.
* @retval         E_NOT_OK        In case of an ongoing conversion.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_HwResultReadGroup
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataPtr
)
{
    VAR(Adc_ChannelType, AUTOMATIC) Ch;
    VAR(Adc_ChannelType, AUTOMATIC) PreviousCh;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) PreviousChIndex;
    VAR(boolean, AUTOMATIC) bFlagStatus = (boolean)FALSE;
    VAR(Std_ReturnType, AUTOMATIC) Adc_ReadGroupRet = (Std_ReturnType)E_OK;
    VAR(uint32, AUTOMATIC) u32CdrValue = 0UL;
    VAR(uint32, AUTOMATIC) u32CdrMask = ADC_CDR_DATA_MASK_U32;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
    VAR(Adc_ChannelType, AUTOMATIC) Shift = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;
#endif /* ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);

#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
    for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
    {
        /* Get the index of hardware unit in structure which will match with the hardware unit ID*/
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(Unit == Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId)
        {
            break;
        }
    }
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    Shift = (16U - Adc_CfgPtr->pAdc[HwIndex].Res);
    u32CdrMask = (uint32)(ADC_CDR_DATA_MASK_U32 << Shift);
#endif

    /* Global Interrupt disable to protect code section */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_23();

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for (Ch = 0U; Ch <Adc_CfgPtr->pGroups[Group].AssignedChannelCount; Ch++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndex = Adc_CfgPtr->pGroups[Group].pAssignment[Ch];
        /**
        * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic 
        * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
        */
        u32CdrValue = REG_READ32(ADC_CH_DATA_REG_ADDR32(Unit, (uint32)Adc_CfgPtr->pChannels[Unit][ChIndex].ChId));
        bFlagStatus = (boolean)FALSE;
        if(0U == (u32CdrValue&ADC_VALID_DATA_MASK_U32))
        {   
            for (PreviousCh = (Adc_ChannelType)0U; PreviousCh < Ch; PreviousCh++)
            {
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
                PreviousChIndex = Adc_CfgPtr->pGroups[Group].pAssignment[PreviousCh];
                if (PreviousChIndex == ChIndex)
                {
                    bFlagStatus = (boolean)TRUE;
                    break;
                }
            }
        }
        else
        {
            bFlagStatus = (boolean)TRUE;
        }
        if ((boolean)TRUE == bFlagStatus)
        {
            /**
            * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic 
            * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
            */
            *(pDataPtr+Ch) = (uint16)(u32CdrValue&u32CdrMask);
        }
        else
        {
            /* data are not measured yet -> VALID flag not set yet */
            Adc_ReadGroupRet = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }
    /* Global Interrupt enable to protect code section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_23();

    return(Adc_ReadGroupRet);
}
#endif /* (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON) */
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
/**
* @brief          This function updates the status variables after the getstreamlastpointer operation.
* @details        This function updates the status variables after the getstreamlastpointer operation.
*
* @param[in]      Group       The group of which conversion will be started.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_UpdateStatusAfterGetStream
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* The following code has been added to respect the State Diagram of Streaming Access Mode */
    if (ADC_COMPLETED == Adc_GroupStatus[Group].eConversion)
    {
        Adc_GroupStatus[Group].ResultIndex = 0U;
        /* ADC328 -- ADC222*/
        Adc_GroupStatus[Group].eConversion = ADC_BUSY;
    }

    /* Compliance with State Diagram */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    if (ADC_TRIGG_SRC_SW == Adc_CfgPtr->pGroups[Group].eTriggerSource)
    {
        if (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if((ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)|| \
               ((ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode)&& \
               (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)&& \
               (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode))
              )
            {
                /* ADC327 -- ADC221*/
                Adc_GroupStatus[Group].eConversion = ADC_IDLE;
            }
            else
            {
                /* Continuous*/
                /* ADC326 -- ADC222*/
                Adc_GroupStatus[Group].eConversion = ADC_BUSY;
            }
        }
    }
#if (ADC_HW_TRIGGER_API == STD_ON)
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    else if (ADC_TRIGG_SRC_HW == Adc_CfgPtr->pGroups[Group].eTriggerSource)
    {
        /* Hw Trigger*/
        if (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if((ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)&& \
               (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
              )
            {
                Adc_GroupStatus[Group].eConversion = ADC_IDLE;
            }
            else
            { /* Simple One-shot mode, in other words in single access mode*/
                Adc_GroupStatus[Group].eConversion = ADC_BUSY;
            }
        }
    }
    else
    {
        /* Nothing for misra */
    }
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
}

/**
* @brief          This function returns the first empty position in the result buffer.
* @details        This function returns the first empty position in the result buffer.
*
* @param[in]      Group            The group number.
* @param[in]      pPtrToSamplePtr  Pointer to the result buffer start address.
*
* @return         Adc_StreamNumSampleType  Number of samples from the result buffer.
* @retval         >= 0;
*
*/
FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_Adcdig_GetStreamLastPointer
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pPtrToSamplePtr
)
{
    VAR(Adc_StreamNumSampleType, AUTOMATIC) NumberOfResults = 0U;
    VAR(Adc_StreamNumSampleType, AUTOMATIC) ResultIndex = 0U;

    *pPtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_12();

    if ((ADC_COMPLETED == Adc_GroupStatus[Group].eConversion)|| \
        (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion)
       )
    {
        if ((Adc_StreamNumSampleType)0U == Adc_GroupStatus[Group].ResultIndex)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ResultIndex = Adc_CfgPtr->pGroups[Group].NumSamples - 1U;
            /* ADC387 Note*/
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            NumberOfResults = Adc_CfgPtr->pGroups[Group].NumSamples;
        }
        else
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            ResultIndex = Adc_GroupStatus[Group].ResultIndex - (Adc_StreamNumSampleType)1U;
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            NumberOfResults = Adc_GroupStatus[Group].ResultIndex;
        }
        /* ADC214 -- ADC418 -- ADC382*/
        /**
         * @violates @ref Adc_Adcdig_c_REF_5 Cast from pointer to pointer.
         * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
         */
        *pPtrToSamplePtr=(Adc_ValueGroupType *)(Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group]+ResultIndex);

        Adc_Adcdig_UpdateStatusAfterGetStream(Group);
    }
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_12();

    return(NumberOfResults);
}

/**
* @brief          This function performs general configurations to the adc hardware prior to starting a conversion.
* @details        This function performs general configurations to the adc hardware prior to starting a conversion.
*
* @param[in]      Group       The group of which conversion will be started.
* @param[in]      Unit        The hardware Unit.
* @param[in]      pGroupPtr    The pointer to the group configuration structure.
*
* @return         void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Adcdig_PrepareGroupStart
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr
)
{
#if (ADC_SET_ADC_PRESAMPLE_ONCE == STD_OFF) 
    VAR(uint32, AUTOMATIC) u32Extended = 0UL;
    VAR(uint32, AUTOMATIC) u32External = 0UL;
#endif /* #if ADC_SET_ADC_PRESAMPLE_ONCE == STD_OFF */
#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1 = 0U;
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2 = 0U;
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */

    /* Put the conversion results from Results Buffer Base Address */
    Adc_GroupStatus[Group].ResultIndex = 0U;

    /*Mark the Unit as BUSY */
    Adc_UnitStatus[Unit].eStatus = ADC_BUSY;

#ifdef ADC_WDG_SUPPORTED
        Adc_Adcdig_ConfigureCwenrRegiters(Unit, pGroupPtr);
#endif /* ADC_WDG_SUPPORTED */

#if (ADC_SET_ADC_PRESAMPLE_ONCE == STD_OFF) 
#if (ADC_PSR1_AVAILABLE == STD_ON)
    u32Extended = pGroupPtr->u32ExtendedPsr;
#endif
#if (ADC_PSR2_AVAILABLE == STD_ON)
    u32External = pGroupPtr->u32ExternalPsr;
#endif
    /* presampling related configurations/initializations */
    Adc_Adcdig_SetPsrRegisters(Unit, pGroupPtr->u32PrecisionPsr, u32Extended, u32External);
#endif /* #if ADC_SET_ADC_PRESAMPLE_ONCE == STD_OFF */

#if (ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF)
    #if (ADC_CTR1_AVAILABLE == STD_ON)
    ConvTime1 = pGroupPtr->ConvTime1;
    #endif
    #if (ADC_CTR2_AVAILABLE == STD_ON)
    ConvTime2 = pGroupPtr->ConvTime2;
    #endif
    /*  Program Conversion Time*/
    Adc_Adcdig_SetCtrRegisters(Unit, pGroupPtr->ConvTime, ConvTime1, ConvTime2);
#endif /* ADC_SET_ADC_CONV_TIME_ONCE == STD_OFF */
#if (!defined(ADC_WDG_SUPPORTED)) && (ADC_SET_ADC_PRESAMPLE_ONCE == STD_ON) && (ADC_SET_ADC_CONV_TIME_ONCE == STD_ON) 
    (void)pGroupPtr;
#endif
}


/**
* @brief          This function starts the conversion on the specified hardware Unit.
* @details        This function starts the conversion on the specified hardware Unit.
*                 This function should be called with the ADC Unit on standby (no ADC interruptions
*                 allowed because its code is not protected by critical regions) - no conversions must
*                 be running.
*
* @param[in]      Unit            the used hw Unit.
*
* @return         void
*
*/
/**
* @violates @ref Adc_Adcdig_c_REF_10 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_Adcdig_StartNormalConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr; /* Pointer to AdcGroup */
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U; /* Active group in the Queue */
    VAR(uint32, AUTOMATIC) u32Precision = 0UL;
    VAR(uint32, AUTOMATIC) u32Extended = 0UL;
    VAR(uint32, AUTOMATIC) u32External = 0UL;
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
    VAR(Adc_GroupType, AUTOMATIC) Adc_IndividualGroupId = 0U;
#endif

    if ((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].QueueIndex)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }

    /* Get the Group ID of the current active group */
    /* Load the first group in the queue (Adc_UnitStatus[Unit].Queue[0])*/
    Group=Adc_UnitStatus[Unit].Queue[0];

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

    Adc_Adcdig_PrepareGroupStart(Unit, Group, pGroupPtr);

    /* If the Individual group channel enable capability is ON*/
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing */
    Adc_IndividualGroupId = (Adc_GroupType)Adc_CfgPtr->pGroups[Group].EnableChDisableChGroupIndex;
    if(ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX != Adc_IndividualGroupId)
    {
        u32Precision = Adc_NCMRxMask[Adc_IndividualGroupId].Adc_NCMR0;
#if (ADC_NCMR1_AVAILABLE == STD_ON)
        u32Extended = Adc_NCMRxMask[Adc_IndividualGroupId].Adc_NCMR1;
#endif /* (ADC_NCMR1_AVAILABLE == STD_ON) */
#if (ADC_NCMR2_AVAILABLE == STD_ON)
        u32External = Adc_NCMRxMask[Adc_IndividualGroupId].Adc_NCMR2;
#endif /* (ADC_NCMR2_AVAILABLE == STD_ON) */
    }
    else
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) */
    {
        u32Precision = pGroupPtr->u32PrecisionChannel;
#if (ADC_NCMR1_AVAILABLE == STD_ON)
        u32Extended = pGroupPtr->u32ExtendedChannel;
#endif /* (ADC_NCMR1_AVAILABLE == STD_ON) */
#if (ADC_NCMR2_AVAILABLE == STD_ON)
        u32External = pGroupPtr->u32ExternalChannel;
#endif /* (ADC_NCMR2_AVAILABLE == STD_ON) */
    }
    /* Program the Normal Conversion Mask register */
    Adc_Adcdig_SetNcmrRegisters(Unit, u32Precision, u32Extended, u32External);

    /* Program the Mode */
    if(ADC_CONV_MODE_ONESHOT == pGroupPtr->eMode)
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit),ADC_CONVERSION_MODE_U32);
    }
    else
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit),ADC_CONVERSION_MODE_U32);
    }

#ifdef ADC_DMA_SUPPORTED
    if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
    {
        /* If the group is configured for with interrupts*/
        if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_BIT_SET32(ADC_DMAE_REG_ADDR32(Unit), ADC_DMA_GLOBAL_EN_U32);
            Adc_Adcdig_StartDmaOperation(Unit);
        }
    }
    else
#endif /* ADC_DMA_SUPPORTED */
  {
        /* Clear Interrupt status flag*/
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CLEAN_U32);

        /* If the group is configured for with interrupts*/
        if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
        {
            /* Enable Interrupt */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            REG_BIT_SET32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_NORM_CONV_EN_U32);
        }
    }

    /* Start Normal Conversion */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_START_CONV_EN_U32);
}

#ifdef ADC_DMA_SUPPORTED
/**
* @brief          This function programs the DMA transfers involved in the ADC conversion process.
* @details        This function should be called with the ADC Unit on standby (no ADC interruptions
*                 allowed because its code is not protected by critical regions) - no conversions must
*                 be running.
*
* @param[in]      Unit            the used hw Unit.
*
* @return         void
*
* @pre ADC Unit is not running anything.
*
* @violates @ref Adc_Adcdig_c_REF_10 internal linkage or external linkage
*/

FUNC(void, ADC_CODE) Adc_Adcdig_StartDmaOperation
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Mcl_DmaTcdAttributesType, AUTOMATIC) DmaTcdConfig;
    VAR(Mcl_DmaTcdType *, AUTOMATIC) TcdAddress;
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Adc_ChannelType, AUTOMATIC) ChCount = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) phChannel = 0U;
    VAR(uint16, AUTOMATIC) u16nBytes = 0U;
    VAR(uint32, AUTOMATIC) u32destAddr = 0UL;
    VAR(uint16, AUTOMATIC) u16destNextOffset = 0U;
    VAR(uint32, AUTOMATIC) u32Precision = 0UL;
    VAR(uint32, AUTOMATIC) u32Extended = 0UL;
    VAR(uint32, AUTOMATIC) u32External = 0UL;
    VAR(sint32, AUTOMATIC) s32Dlast = (sint32)0;
    VAR(uint32, AUTOMATIC) u32SourceAddr = 0UL;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel = 0U;
    
    if (((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].QueueIndex)
#if (STD_ON == ADC_HW_TRIGGER_API)
        && ((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].HwQueueIndex)
#endif
       )
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }

    if (Adc_UnitStatus[Unit].QueueIndex > 0U)
    {
        Group=Adc_UnitStatus[Unit].Queue[0];
    }
#if (STD_ON == ADC_HW_TRIGGER_API)
    else
    {
        Group=Adc_UnitStatus[Unit].HwQueue[0];
    }
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    ChCount = (Adc_CfgPtr->pGroups[Group].AssignedChannelCount);

    DmaChannel = (Mcl_ChannelType)Adc_CfgPtr->Misc.au8Adc_DmaChannel[Unit];
    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
    {
        /* Disable DMA interrupt */
        Mcl_DmaDisableHwRequest(DmaChannel);
        Mcl_DmaDisableNotification(DmaChannel);
    }

    /* Enable the last channel of the chain to transfer data in DMA mode */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    phChannel = (Adc_ChannelType)Adc_CfgPtr->pGroups[Group].LastCh;

    if (ADC_ST_EXTENDED_CH > phChannel)
    {
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        u32Precision = (1UL << phChannel);
    }
#if (ADC_DMAR1_AVAILABLE == STD_ON)
    else if ((ADC_ST_EXTENDED_CH <= phChannel) && (ADC_ED_EXTENDED_CH >= phChannel))
    {
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR1_INDEX])
        {
            u32Extended = (1UL << (phChannel - ADC_ST_EXTENDED_CH));
        }
    }
#endif /* (ADC_DMAR1_AVAILABLE == STD_ON) */

#if (ADC_DMAR2_AVAILABLE == STD_ON)
    else if ((ADC_ST_EXTERNAL_CH <= phChannel) && (ADC_ED_EXTERNAL_CH >= phChannel))
    {
        if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_DmarPresent[Unit][ADC_DMAR2_INDEX])
        {
            u32External = (1UL << (phChannel - ADC_ST_EXTERNAL_CH);
        }
    }
#endif /* (ADC_DMAR2_AVAILABLE == STD_ON) */
    else
    {
        /*Nothing for misra*/
    }
    Adc_Adcdig_SetDmarRegisters(Unit, u32Precision, u32Extended, u32External);
    /* update result address of ch 0 and destination offset to support format of streaming buffer */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pResult = Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group]+Adc_GroupStatus[Group].ResultIndex;

    if ((uint8)STD_ON == Adc_CfgPtr->Misc.au8Adc_HwUnit[Unit])
    {
        if ((Adc_DmaContinuousType)STD_ON == Adc_GroupStatus[Group].Adc_DmaContinuous)
        {
            /* There are no gaps into the group channels list, so it can be transferred without any
            problems directly to the user configured buffer. */
            /* n_bytes_to_transfer */
            u16nBytes = (uint16)((uint16)ChCount << 1U);
            /* dest_addr */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            /** Compiler_Warning: It is intended for the address of the element to be stored
                in another non pointer element. */
            u32destAddr = (uint32)(pResult);
            /* dest_next_offset */
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            u16destNextOffset = (uint16)(Adc_CfgPtr->pGroups[Group].NumSamples << 1U);
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            if(ADC_ACCESS_MODE_SINGLE == Adc_CfgPtr->pGroups[Group].eAccessMode)
            {
                s32Dlast = -(sint32)u16nBytes;
            }
            else
            {
                /**
                 * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                 * @violates @ref Adc_Adcdig_c_REF_16 It is needed for calculation value of go back space for destination address.
                 */
                s32Dlast = -(sint32)((uint32)((ChCount*Adc_CfgPtr->pGroups[Group].NumSamples) - 1U) << 1U);
            }
        }
        else if ((Adc_DmaContinuousType)STD_OFF == Adc_GroupStatus[Group].Adc_DmaContinuous)
        {
            /* There are gaps into the group channel list. In this case DMA will transfer all channels
            between the start channel and end channel into the intermediate buffer
            Adc_Adcdig_DmaInternalResultBuffer, and in the DMA ISR will be filtered out the unnecessary data. */
            /* n_bytes_to_transfer */
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            u16nBytes = (uint16)((uint16)((Adc_CfgPtr->pGroups[Group].LastCh + (uint16)1) - (Adc_CfgPtr->pGroups[Group].FirstCh)) << 1U);
            /* dest_addr */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            /** Compiler_Warning: It is intended for the address of the element to be stored
                in another non pointer element. */
            u32destAddr = (uint32)(Adc_Adcdig_DmaInternalResultBuffer[Unit]);
            /* dest_next_offset */
            u16destNextOffset = 2U;
            s32Dlast = -(sint32)u16nBytes;
        }
        else
        {
            /*do nothing*/
        }

        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        u32SourceAddr = (uint32)(ADC_ADDR32(Unit)+ADC_CH_DATA_REG_OFFSET_U32+(uint32)(((uint32)(Adc_CfgPtr->pGroups[Group].FirstCh)) << 2U));
#if CPU_BYTE_ORDER == LOW_BYTE_FIRST     
        u32SourceAddr = u32SourceAddr - 2UL;
#endif 
        DmaTcdConfig.saddr = u32SourceAddr;
        DmaTcdConfig.ssize = (uint32)DMA_SIZE_2BYTES;
        DmaTcdConfig.dsize = (uint32)DMA_SIZE_2BYTES;
        DmaTcdConfig.soff = (uint32)4;
        DmaTcdConfig.num_bytes = (uint32)u16nBytes;
        DmaTcdConfig.daddr = (uint32)u32destAddr;
        DmaTcdConfig.iter = (uint32)1;
        DmaTcdConfig.doff = (uint32)u16destNextOffset;
        DmaTcdConfig.smod = (uint32)0;
        DmaTcdConfig.dmod = (uint32)0;

        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        TcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress(DmaChannel);
        /** @violates @ref Adc_Adcdig_c_REF_12 place reliance on undefined or unspecified behaviour */
        Mcl_DmaConfigTcd(TcdAddress, &DmaTcdConfig);
        Mcl_DmaTcdSetFlags(TcdAddress, (uint8)(DMA_TCD_DISABLE_REQ | DMA_TCD_INT_HALF));
        /** @violates @ref Adc_Adcdig_c_REF_16 It is needed for calculation value of go back space for source address. */
        Mcl_DmaTcdSetSlast(TcdAddress, -(sint32)((uint32)u16nBytes << 1U));
        Mcl_DmaTcdSetDlast(TcdAddress, (sint32)s32Dlast);
        /* Start the DMA channel0 */
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
        Mcl_DmaEnableHwRequest(DmaChannel);
    }
}
#endif /* ADC_DMA_SUPPORTED */

/**
* @brief          This function starts the injected conversion on the specified hardware Unit.
* @details        This function starts the injected conversion on the specified hardware Unit.
*                 This function should be called with the ADC Unit on idle or busy.
*
* @param[in]      Unit            The used hw Unit.
*
* @return         void
* @violates @ref Adc_Adcdig_c_REF_10 u32External linkage
*/
FUNC(void, ADC_CODE) Adc_Adcdig_StartInjectedConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr; /* Pointer to AdcGroup */
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U; /* Active group in the Queue */
    VAR(uint32, AUTOMATIC) u32Extended = 0x0UL;
    VAR(uint32, AUTOMATIC) u32External = 0x0UL;

    if ((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].SwInjQueueIndex)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }

    /* Get the Group ID of the current active group */
    /* Load the first group in the queue (Adc_UnitStatus[Unit].Queue[0])*/
    Group=Adc_UnitStatus[Unit].SwInjQueue[0];

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_CfgPtr->pGroups[Group]);

    Adc_Adcdig_PrepareGroupStart(Unit, Group, pGroupPtr);

#if (ADC_JCMR1_AVAILABLE == STD_ON)
    u32Extended = pGroupPtr->u32ExtendedChannel;
#endif /* (ADC_JCMR1_AVAILABLE == STD_ON) */
#if (ADC_JCMR2_AVAILABLE == STD_ON)
    u32External = pGroupPtr->u32ExternalChannel;
#endif /* (ADC_JCMR2_AVAILABLE == STD_ON) */
    /* Program the Injected Conversion Mask register */
    Adc_Adcdig_SetJcmrRegisters(Unit, pGroupPtr->u32PrecisionChannel, u32Extended, u32External);

    /* Clear Interrupt status flag*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_ISR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_CLEAN_U32);

    /* If the group is configured for with interrupts*/
    if((uint8)STD_OFF == pGroupPtr->u8AdcWithoutInterrupt)
    {
        /* Enable Interrupt*/
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_BIT_SET32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_EN_U32);
    }
    else
    {
        /* Disable Interrupt*/
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        REG_BIT_CLEAR32(ADC_IMR_REG_ADDR32(Unit), ADC_ISR_END_CHAIN_INJ_CONV_EN_U32);
    }

    /* Start Injected Conversion */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_INJ_START_CONV_EN_U32);
}

#if (ADC_SET_MODE_API == STD_ON)
/**
* @brief          This function sets the PWDN bit while going in power down mode or clears it
*                 upon exit from power down mode.
* @details        Set power down/ normal mode.
*
* @param[in]      eSetMode         ADC_NORMAL_MODE,ADC_POWER_DOWN_MODE.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful set mode.
* @retval         E_NOT_OK        In case of unsuccessful set mode.
*
*/
FUNC (Std_ReturnType, ADC_CODE) Adc_Adcdig_SetMode
(
    VAR(Adc_SetModeType, AUTOMATIC) eSetMode
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U; /* Hardware Unit index */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U; /* Hardware Unit ID */
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_OK;
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
    
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_05();
    
    if(ADC_POWER_DOWN_MODE == eSetMode)
    {
        for (HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Unit = (Adc_HwUnitType)(Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId);
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            if (ADC_CTU_CONV_FINISH_U32 != ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_CTU_CONV_ONGOING_U32))
            {
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_05();
            #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
                if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
                {
                    /* Report production error and return from function. */
                    Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
                }
            #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
                /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
                return ((Std_ReturnType)E_NOT_OK);
            }
        }
        for (HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Unit = (Adc_HwUnitType)(Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId);
            /* enter into power-down Mode */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit),ADC_POWER_DOWN_U32);

            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
            * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
            * shall not contain side effects.
            */
            while((((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32) != ADC_POWERDOWN_STATUS_U32) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            if (0UL == u32Timeout)
            {
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_05();
            #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
                if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
                {
                    /* Report production error and return from function. */
                    Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
                }
            #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
                /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
                return ((Std_ReturnType)E_NOT_OK);
            }
        }
    }
    else
    {
        for (HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
        {
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
            Unit = (Adc_HwUnitType)(Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId);
            /* Exit from PowerDown Mode */
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
            REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);

            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
            * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
            * shall not contain side effects.
            */
            while((((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32) != ADC_IDLE_OFFSET_STATUS_U32) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            if (0UL == u32Timeout)
            {
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_05();
            #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
                if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
                {
                    /* Report production error and return from function. */
                    Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
                }
            #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
                /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
                return ((Std_ReturnType)E_NOT_OK);
            }
        }
    }
    
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_05();
#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
  #if (ADC_BCTU_AVAILABLE == STD_ON)
    /* Set mode for BCTU */
    TempReturn = Adc_Bctu_SetMode(eSetMode);
  #endif /* ADC_BCTU_AVAILABLE == STD_ON */
#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */

    return (TempReturn);
}
#endif /* (ADC_SET_MODE_API == STD_ON) */

#if (ADC_CALIBRATION == STD_ON)
/**
* @brief          Checks the ADC hardware status.
* @details        Checks the ADC hardware status and compares it with the flag parameter.
*
* @param[in]      Unit            The hardware Unit.
* @param[in]      u32testFlag     The flag that the status should be checked against.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of adc status read as expected.
* @retval         E_NOT_OK        In case of timeout while waiting for adc status to stabilize.
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE Std_ReturnType Adc_Adcdig_StatusTimeoutCalibration
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint32, AUTOMATIC) u32testFlag
)
{
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
    VAR(Std_ReturnType, AUTOMATIC) returnValue = (Std_ReturnType)E_OK;

    /**
    * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
    * @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
    * shall not contain side effects.
    */
    while((((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32) != u32testFlag) && (u32Timeout > 0UL))
    {
        u32Timeout--;
    }
    /* If the ongoing conversion is not aborted, report the production error */
    if (0UL == u32Timeout)
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
    #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            /* Report production error and return from function. */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
        }
    #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        returnValue = (Std_ReturnType)E_NOT_OK;
    }
    return returnValue;
}

/**
* @brief          Executes high accuracy calibration of a ADC HW Unit.
* @details        This function calibrates the ADC HW Unit and updates calibration related registers
*
* @param[in]      Unit      ADC Unit Id.
* @param[in]      pStatus   Status of the ADC HW Unit calibration and
*                           list of failed/passed tests.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Adcdig_Calibrate
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    P2VAR(Adc_CalibrationStatusType , AUTOMATIC, ADC_APPL_DATA) pStatus
)
{
#ifdef ADC_BIST1_AVAILABLE
    VAR(uint8, AUTOMATIC) u8Index;
#endif
    VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
    VAR(volatile uint32, AUTOMATIC) Adc_MSR_status;
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_OK;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
    pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;

    /* 1. Configure the ADC. */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    TempReturn = Adc_Adcdig_StatusTimeoutCalibration(Unit, ADC_POWERDOWN_STATUS_U32);
    if ((Std_ReturnType)E_NOT_OK == TempReturn)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return ;
    }
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CLOCK_PRESCALER_DIV1_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    TempReturn = Adc_Adcdig_StatusTimeoutCalibration(Unit, ADC_IDLE_OFFSET_STATUS_U32);
    if ((Std_ReturnType)E_NOT_OK == TempReturn)
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return ;
    }

    /* 2. Configure the Calibration, BIST Control, and status register (CALBISTREG) for
          TEST conditions. The default values are set for maximum accuracy (recommended). */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_RMW32(ADC_CALBISTREG_REG_ADDR32(Unit), ADC_CALBISTREG_REG_MASK_U32, \
              ADC_TSAMP_U32(2UL) | ADC_NR_SMPL_U32(3UL) | ADC_AVG_EN_U32 \
             );

    /* 3. Set the TEST_EN bit of CALBISTREG. (The routine will start immediately) */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_CALBISTREG_REG_ADDR32(Unit), ADC_TEST_EN_U32);


    /* 4. Poll the status of MSR.ADCSTATUS[2:0] (wait till it remains in 011b [Busy in Calibration]) */
    if ((Std_ReturnType) E_NOT_OK == Adc_Adcdig_StatusTimeoutCalibration(Unit, ADC_IDLE_OFFSET_STATUS_U32))
    {
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return;
    }
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    Adc_MSR_status = (REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32;
    /** @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
       shall not contain side effects.*/
    while((Adc_MSR_status != ADC_IDLE_OFFSET_STATUS_U32) && \
          (Adc_MSR_status != ADC_BUSY_IN_HIGH_ACCURACY_STATUS_U32) && (u32Timeout > (uint32)0U) \
         )
    {
        u32Timeout--;
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        Adc_MSR_status = (REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32;
    }

    if ((uint32)0U == u32Timeout)
    {
    #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            /* Report production error and return from function. */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
        }
    #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
    }
    else
    {
        /* 5. Check the value of MSR.CALIBRATED bit for successfulness of calibration. */
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        if (((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_CALIBRTD_STATUS_U32) == ADC_CALIBRTD_CALIBRATED_U32)
        {
            pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_OK;
        }
#ifdef ADC_BIST1_AVAILABLE
        /* 6. If the status of MSR.CALIBRATED is '1', calibration is successful, otherwise check
              the status bits (STAT_n, n= 1-12) of the BIST 1 Register (BIST1) to know the status
              of individual steps for further diagnosis. */
        for (u8Index = 0U; u8Index < (uint32)ADC_MAX_BIST_STEPS; u8Index++)
        {
            pStatus->Adc_BIST_Failed_Tests[u8Index] = 0U;
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
            if(((REG_READ32(ADC_BIST1_REG_ADDR(Unit)))&(uint32)ADC_STAT_MASK_U32((uint32)u8Index)) == \
               (uint32)ADC_STAT_FAIL_MASK_U32((uint32)u8Index)
              )
            {
                pStatus->Adc_BIST_Failed_Tests[u8Index] = 1U;
            }
        }
#endif
    }

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    TempReturn = Adc_Adcdig_StatusTimeoutCalibration(Unit, ADC_POWERDOWN_STATUS_U32);
    if ((Std_ReturnType)E_NOT_OK == TempReturn)
    {
        pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
        /** @violates @ref Adc_Adcdig_c_REF_4 Return statement before end of function. */
        return ;
    }
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CLOCK_PRESCALER_DIV1_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    TempReturn = Adc_Adcdig_StatusTimeoutCalibration(Unit, ADC_IDLE_OFFSET_STATUS_U32);
    if ((Std_ReturnType)E_NOT_OK == TempReturn)
    {
        pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
    }    
    return;
}
#endif /* ADC_CALIBRATION == STD_ON */

#if (ADC_SELF_TEST == STD_ON)
/**
* @brief          Executes hardware Self Test of a ADC HW Unit.
* @details        This function checks if the ADC HW Unit is functioning correctly
*
* @param[in]      Unit    ADC Unit Id.
*
* @return         Std_ReturnType. Status of the ADC HW Unit Self Test.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_SelfTest
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
   VAR(uint8, AUTOMATIC) u8Index = 0U;
   VAR(volatile uint32, AUTOMATIC) u32Timeout = ADC_TIMEOUT_COUNTER;
   VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_OK;

   /* 1. Program NCMR0 to select channels to be converted for normal conversion.*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_NCMR0_REG_ADDR32(Unit), 0x1UL);

    /* 2. Program MCR[MODE] = 1 to select Scan mode. ADC_ONE_SHOT_MODE_U32 ADC_CONTINUOUS_MODE_U32*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned  int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CONTINUOUS_MODE_U32);

    /* 3. Program sampling duration values in STCR1[INPSAMPx].*/
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_RMW32(ADC_STCR1_REG_ADDR32(Unit), ADC_STCR1_MASK_U32, (ADC_INPSAMP_C_U32(10UL) | ADC_INPSAMP_S_U32(10UL)));

    /* 4. Select the self-testing algorithm in STCR3[ALG]. */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_WRITE32(ADC_STCR3_REG_ADDR32(Unit),ADC_STCR3_ALG_C_U32);

    /* 5. Enable the self-testing channel by setting STCR2[EN]. */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_STCR2_REG_ADDR32(Unit), ADC_STCR2_EN_SET_U32);

    /* 6. Start the normal conversion by setting MCR[NSTART]. */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_START_CONV_EN_U32);

    u32Timeout = ADC_TIMEOUT_COUNTER;
    /* check that all algorithms have executed at least once */
    for (u8Index = 0U; u8Index < 2U; u8Index++)
    {
        /* Wait until Alg S has started*/
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        /** @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
        * shall not contain side effects.*/
        while((ADC_SELF_TEST_S_U32 != ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_SELF_TEST_S_U32)) && (u32Timeout > 0UL))
        {
            u32Timeout--;
        }
        /* Wait until Alg S has finished*/
        /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
        /** @violates @ref Adc_Adcdig_c_REF_13 the right-hand operand of a logical "&&" or "||" operator
        * shall not contain side effects.*/
        while((ADC_SELF_TEST_S_U32 == ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_SELF_TEST_S_U32)) && (u32Timeout > 0UL))
        {
            u32Timeout--;
        }
    }
    if (0UL == u32Timeout)
    {
        TempReturn = (Std_ReturnType)E_NOT_OK;
    }
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    if (0U != ((REG_READ32(ADC_STSR1_REG_ADDR32(Unit)))&\
               (ADC_STSR1_ERR_C_U32 | ADC_STSR1_ERR_S2_U32 | ADC_STSR1_ERR_S1_U32 | ADC_STSR1_ERR_S0_U32)
              )
       )
    {
        TempReturn = (Std_ReturnType)E_NOT_OK;
    }

    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_NORMAL_START_CONV_EN_U32);

    return TempReturn;
}
#endif /* ADC_SELF_TEST == STD_ON */

#if (ADC_ENABLE_CONFIGURE_THRESHOLD_NONAUTO_API == STD_ON)
/**
 * @brief   Function to reconfigure High and Low thresholds for a given group.
 * @details This Non Autosar API is used to reconfigure High and Low thresholds for a given group.
 *
 * @param[in]  GroupId          Index of group
 * @param[in]  LowValue         Low threshold value for channels in the group
 * @param[in]  HighValue        High threshold value for channels in the group
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful Configure Threshold.
 * @retval         E_NOT_OK        In case of unsuccessful ConfigureThreshold.
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_ConfigureThreshold
(
    VAR(Adc_GroupType, AUTOMATIC) GroupId,
    VAR(Adc_ValueGroupType, AUTOMATIC) LowValue,
    VAR(Adc_ValueGroupType, AUTOMATIC) HighValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) Adc_ConThdRet = (Std_ReturnType)E_NOT_OK;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) ChCount = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) Channel = 0U;
    VAR(uint32, AUTOMATIC) u32ThValue = ADC_LOW_TH_VALUE_U32(LowValue) | ADC_HIGH_TH_VALUE_U32((uint32)HighValue);

    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    Unit = Adc_GroupUnit(GroupId);

    /* Check the channels in the group one by one, set the threshold values if threshold is enabled */
    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
    for(ChCount = 0U; ChCount <Adc_CfgPtr->pGroups[GroupId].AssignedChannelCount; ChCount++)
    {
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        Channel = Adc_CfgPtr->pGroups[GroupId].pAssignment[ChCount];
        /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic */
        if(ADC_UNUSED_THRESHOLD != Adc_CfgPtr->pChannels[Unit][Channel].u8ThReg)
        {
            /**
            * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
            * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer
            */
            REG_WRITE32(ADC_THRHLRx_REG_ADDR32(Unit, Adc_CfgPtr->pChannels[Unit][Channel].u8ThReg), u32ThValue);
            Adc_ConThdRet = (Std_ReturnType)E_OK;
        }
    }
    return Adc_ConThdRet;
}
#endif /* if (ADC_ENABLE_CONFIGURE_THRESHOLD_NONAUTO_API == STD_ON) */

#if (ADC_DUAL_CLOCK_MODE == STD_ON)
/**
* @brief          This function sets the Prescaler value only when ADC is in power down mode.
* @details        Set prescaler clock divider only in power down mode.
*
* @param[in]      eClockMode       ADC_NORMAL, ADC_ALTERNATE.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful set mode.
* @retval         E_NOT_OK        In case of unsuccessful set mode.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Adcdig_SetClockMode
(
   VAR(Adc_DualClockModeType, AUTOMATIC) eClockMode
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U; /* Hardware Unit index */
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U; /* Index of hardware Unit */
    VAR(Std_ReturnType, AUTOMATIC) returnValue = (Std_ReturnType)E_OK;
    P2CONST(Adc_Adcdig_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) UnitConfigPtr; /* Pointer to Hw Unit config */
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime1 = 0U;
    VAR(Adc_ConversionTimeType, AUTOMATIC) ConvTime2 = 0U;

    for (Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer. */
            if (ADC_POWERDOWN_STATUS_U32 == ((REG_READ32(ADC_MSR_REG_ADDR32(Unit)))&ADC_STATUS_U32))
            {
                /* Get index of hardware Unit */
                for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
                {
                    /* Get the index of hardware Unit in structure which will match with the hardware Unit ID*/
                    /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall */
                    if(Unit == Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId)
                    {
                        break;
                    }
                }
                /** @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall */
                UnitConfigPtr = &(Adc_CfgPtr->pAdc[HwIndex]);
                if ((Adc_DualClockModeType)ADC_NORMAL == eClockMode)
                {
                    /* Write the configured power down exit delay value into PDEDR register */
                    /**
                    * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
                    */
                    REG_WRITE32(ADC_PDEDR_REG_ADDR32(Unit),UnitConfigPtr->u8AdcPwrDownDelay);
                    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
                    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), (uint32)ADC_CLOCK_PRESCALER_DIV1_U32);
#if (ADC_CTR1_AVAILABLE == STD_ON)
                    ConvTime1 = UnitConfigPtr->ConvTimeNormal1;
#endif /* ADC_CTR1_AVAILABLE == STD_ON */
#if (ADC_CTR2_AVAILABLE == STD_ON)
                    ConvTime2 = UnitConfigPtr->ConvTimeNormal2;
#endif /* ADC_CTR2_AVAILABLE == STD_ON */
                    /**
                     * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer
                     * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                     */
                    Adc_Adcdig_SetCtrRegisters(Unit, UnitConfigPtr->ConvTimeNormal, ConvTime1, ConvTime2);
                }
                else
                {
                    /**
                    * @violates @ref Adc_Adcdig_c_REF_8 Array indexing shall be the only allowed form of pointer arithmetic
                    * @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned int to pointer.
                    */
                    REG_WRITE32(ADC_PDEDR_REG_ADDR32(Unit),UnitConfigPtr->u8AdcAltPwrDownDelay);
                    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
                    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), (uint32)ADC_CLOCK_PRESCALER_DIV1_U32);
#if (ADC_CTR1_AVAILABLE == STD_ON)
                    ConvTime1 = UnitConfigPtr->ConvTimeAlternate1;
#endif /* ADC_CTR1_AVAILABLE == STD_ON */
#if (ADC_CTR2_AVAILABLE == STD_ON)
                    ConvTime2 = UnitConfigPtr->ConvTimeAlternate2;
#endif /* ADC_CTR2_AVAILABLE == STD_ON */
                    Adc_Adcdig_SetCtrRegisters(Unit, UnitConfigPtr->ConvTimeAlternate, ConvTime1, ConvTime2);
                }
            }
            else
            {
                returnValue = (Std_ReturnType)E_NOT_OK;
                break;
            }
        }
    }
    return returnValue;
}

#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
/**
 * @brief   Function to enable CTU control mode for an ADC unit. 
 *
 * @details Enable CTU control mode for an ADC unit.
 *          This function to enable CTU control mode for Adc. When a unit works in CTU control mode,
 *          no other conversions shall run in parallel(Adc). The only conversions occurring shall be
 *          the ones defined in the CTU configuration.
 *
 * @param[in]  Unit      ADC Unit Id.
 *
 * @note    The function Service ID[hex]: 0x39.
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_Adcdig_EnableCtuControlMode
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Index;
    VAR(boolean, AUTOMATIC) bAlreadyCall = (boolean)FALSE;

    /*Mark the Unit as BUSY */
    Adc_UnitStatus[Unit].eStatus = ADC_BUSY;

    /* Enter ADC to CTU control mode, ADC must be switched to power down mode to modify this bit */
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_TRIGGER_MODE_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_POWER_DOWN_U32);
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_SET32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32);

#if (ADC_BCTU_AVAILABLE == STD_ON)
    u8ResultIndex[Unit] = 0U;
#endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
    
    for (Index = 0U; Index < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Index++)
    {
        if ((boolean)TRUE == Adc_UnitStatus[Index].bCtuControlOngoing)
        {
            bAlreadyCall = (boolean)TRUE;
            break;
        }
    }
    /* Mark the unit as CTU control mode is ongoing */
    Adc_UnitStatus[Unit].bCtuControlOngoing = (boolean)TRUE;

    if((boolean)FALSE == bAlreadyCall)
    {
#if (ADC_BCTU_AVAILABLE == STD_ON)
        
        /* Start BCTU control */
        Adc_Bctu_StartCtu();
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
        /* Start CTU2 control */
        Adc_Ctu2_StartCtu();
#endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
    }
}

/**
 * @brief   Function to disable CTU control mode for an ADC unit. 
 *
 * @details Disable CTU control mode for an ADC unit.
 *          This function to disable CTU control mode for Adc. The other Adc conversions can run in
 *          software trigger normal mode, software trigger injected mode or hardware trigger mode.
 *
 * @param[in]  Unit      ADC Unit Id.
 *
 * @note    The function Service ID[hex]: 0x4A.
 *
 * @api
 */
FUNC(void, ADC_CODE) Adc_Adcdig_DisableCtuControlMode
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Index;
    VAR(boolean, AUTOMATIC) bLastCall = (boolean)TRUE;

    /* Mark the Unit as IDLE */
    Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
    /* Mark the unit as CTU control mode is not ongoing */
    Adc_UnitStatus[Unit].bCtuControlOngoing = (boolean)FALSE;

#if (ADC_BCTU_AVAILABLE == STD_ON)    
    u8ResultIndex[Unit] = 0U;
#endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
    
    for (Index = 0U; Index < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Index++)
    {
        if ((boolean)TRUE == Adc_UnitStatus[Index].bCtuControlOngoing)
        {
            bLastCall = (boolean)FALSE;
            break;
        }
    }

    if((boolean)TRUE == bLastCall)
    {
#if (ADC_BCTU_AVAILABLE == STD_ON)
        /* Stop BCTU control */
        Adc_Bctu_StopCtu();
#elif (ADC_CTUV2_AVAILABLE == STD_ON)
        /* Stop CTU2 control */
        Adc_Ctu2_StopCtu();
#endif /* (ADC_BCTU_AVAILABLE == STD_ON) */
    }
    
    /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
    REG_BIT_CLEAR32(ADC_MCR_REG_ADDR32(Unit), ADC_CTU_ENABLED_U32);
}
#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Adcdig_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Adcdig_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
