/**
*   @file    Adc_Ipw.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - Separation source layer of high-low level drivers.
*   @details Source interface between common and low level driver.
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
* @section Adc_Ipw_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Adc_Ipw_c_REF_2
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character signifiance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
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
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc_Ipw.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_IPW_C                    43
/**
* @violates @ref Adc_Ipw_c_REF_2 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_MAJOR_VERSION_IPW_C     4
/**
* @violates @ref Adc_Ipw_c_REF_2 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_MINOR_VERSION_IPW_C     0
/**
* @violates @ref Adc_Ipw_c_REF_2 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_REVISION_VERSION_IPW_C  3
/**
* @violates @ref Adc_Ipw_c_REF_2 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers
*/
#define ADC_SW_MAJOR_VERSION_IPW_C             1
#define ADC_SW_MINOR_VERSION_IPW_C             0
#define ADC_SW_PATCH_VERSION_IPW_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC IPW header file are from the same vendor */
#if (ADC_VENDOR_ID_IPW_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Ipw.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_IPW_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_MINOR_VERSION_IPW_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_REVISION_VERSION_IPW_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Ipw.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_IPW_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_SW_MINOR_VERSION_IPW_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_SW_PATCH_VERSION_IPW_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
  #error "Software Version Numbers of Adc_Ipw.c and Adc_Ipw.h are different"
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
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Adc_Ipw_c_REF_1 Repeated include file MemMap.h
*/
#include "MemMap.h"

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Adc_Ipw_c_REF_1 Repeated include file MemMap.h
*/
#include "MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Ipw_c_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Ipw_c_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
