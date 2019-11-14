/**
*   @file    Adc.c
*   @implements        Adc_HLD_unit
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - Common Level Driver source file.
*   @details Autosar layer of ADC MCAL driver.
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
* @section Adc_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before 
* '#include'. This is an Autosar memory management requirement
*
* @section Adc_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
* contents of a header being included twice. 
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Adc_c_REF_3
* Violates MISRA 2004 Required Rule 8.10,
* All declarations and definitions of objects or functions at file scope shall
* have internal linkage unless external linkage is required.
* State variables may be used by IPV layer.
*
* @section Adc_c_REF_4
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer 
* arithmetic but used due to the code complexity.
*
* @section Adc_c_REF_5
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
* 
* @section Adc_c_REF_6
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* This violation  is not  fixed since  the inclusion  of MemMap.h
* is as  per Autosar  requirement MEMMAP003.
* 
* @section Adc_c_REF_7
* Violates MISRA 2004 Required Rule 1.2, No reliance shall be placed on undefined or unspecified behaviour.
* The local address passed as parameter is used in a safe way.
*
* @section Adc_c_REF_8
* Violates MISRA 2004 Required Rule 14.7, Return statement before end of function.
* The return statement are used to simplify the code structure and easier readability.
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
#include "Adc.h"
#include "Adc_Ipw.h"
#include "SchM_Adc.h"
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_C                         43
#define ADC_AR_RELEASE_MAJOR_VERSION_C          4
#define ADC_AR_RELEASE_MINOR_VERSION_C          0
/**
* @violates @ref Adc_c_REF_5 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_REVISION_VERSION_C       3
#define ADC_SW_MAJOR_VERSION_C                  1
#define ADC_SW_MINOR_VERSION_C                  0
#define ADC_SW_PATCH_VERSION_C                  0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_C != ADC_VENDOR_ID)
#error "Adc.c and Adc.h have different vendor ids"
#endif

/* Check if source file and ADC header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_C != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_AR_RELEASE_MINOR_VERSION_C != ADC_AR_RELEASE_MINOR_VERSION) || \
     (ADC_AR_RELEASE_REVISION_VERSION_C != ADC_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Adc.c and Adc.h are different"
#endif

/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_C != ADC_SW_PATCH_VERSION) \
    )
#error "Software Version Numbers of Adc.c and Adc.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same vendor */
#if (ADC_VENDOR_ID_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_MINOR_VERSION_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_REVISION_VERSION_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
#error "AutoSar Version Numbers of Adc.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_SW_MINOR_VERSION_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_SW_PATCH_VERSION_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
#error "Software Version Numbers of Adc.c and Adc_Ipw.h are different"
#endif

/** @violates @ref Adc_c_REF_5 Identifier clash */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and DET header file are of the same version */
 #if (ADC_DEV_ERROR_DETECT == STD_ON)
    #if ((ADC_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (ADC_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
    #error "AutoSar Version Numbers of Adc.c and Det.h are different"
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

#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"

/**
* @brief          Global Configuration Pointer.
* @details        Data structure containing the set of configuration parameters required for 
*                 initializing the ADC Driver and ADC HW Unit(s).
*
*/
P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) Adc_CfgPtr = NULL_PTR;

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
/**
* @brief          Global Driver Status.
* @details        Data structure containing the ADC driver status
*                 uninit, during init or already init.
*
*/
STATIC VAR(Adc_GlobalStateType, ADC_VAR) Adc_GlobalState = ADC_STATE_UNINIT;
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"  

/**
* @brief          Group status array structure
* @details        Array to hold all the group status information.
*/
VAR(Adc_GroupStatusType, ADC_VAR) Adc_GroupStatus[ADC_MAX_GROUPS];

/**
* @brief          Unit status structure
* @details         Structure for the unit status.
*/
VAR(Adc_UnitStatusType, ADC_VAR) Adc_UnitStatus[ADC_MAX_HW_UNITS];

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
/**
* @brief          Unit status structure
* @details        Structure for the unit status.
*
*/
VAR(Adc_NCMRType, ADC_VAR) Adc_NCMRxMask[ADC_NO_OF_ENABLE_CH_DISABLE_CH_GROUPS];
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"

#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
#define ADC_START_SEC_VAR_NO_INIT_8
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"  
/**
* @brief          Active BCTU triggers for the group in the HW queue 
* @details        This array is used in Adc_Adcdig_EnableCtuTrigger. For the group currently in the HW queue,
*                 if an element is 1 in this array, the corresponding trigger from the group's configuration structure 
*                 has been activated.
* @violates @ref Adc_c_REF_3 internal linkage vs external linkage.
*/
VAR(uint8, ADC_VAR) Adc_u8BctuGroupTriggersActive[ADC_MAX_HW_UNITS][ADC_MAX_HADRWARE_TRIGGERS];

#define ADC_STOP_SEC_VAR_NO_INIT_8
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"
#endif /* ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON */
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#if ((ADC_VALIDATE_PARAMS == STD_ON) && \
     ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || \
      (ADC_HW_TRIGGER_API == STD_ON) || \
      (ADC_ENABLE_CTUTRIG_NONAUTO_API ==STD_ON) || \
      (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) \
     ) \
    )
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateExtraParams
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(uint32, AUTOMATIC) u32ErrorIdList,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateCallAndGroup
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_NotifyCapablity
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#define ADC_START_SEC_CODE
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/**
* @brief      This function reports an error to the Det module and records the failure in the local structure.
* @details    This function reports an error to the Det module and records the failure in the local structure.
*
* @param[in]  u8ServiceId       The service id of the caller function
* @param[in]  u8ErrorId         The error id to be reported
*
* @return     void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ReportDetError
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(uint8, AUTOMATIC) u8ErrorId
)
{
    Det_ReportError((uint16)ADC_MODULE_ID, (uint8)0U, u8ServiceId, u8ErrorId);
}
#endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */

#if ((ADC_DEV_ERROR_DETECT == STD_ON) && \
     ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || \
      (ADC_HW_TRIGGER_API == STD_ON) || \
      (ADC_ENABLE_CTUTRIG_NONAUTO_API ==STD_ON) || \
      (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) \
     ) \
    )
/**
* @brief      This function reports an error to the Det module and records the failure in the local structure.
* @details    This function reports an error to the Det module and records the failure in the local structure.
*
* @param[in]  u8ServiceId       The service id of the caller function
* @param[in]  u8ErrorId         The error id to be reported
* @param[in]  pResult           Pointer to the structure where the failure must be recorded
*
* @return     void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ReportValidationError
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pResult,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(uint8, AUTOMATIC) u8ErrorId
)
{
    pResult->bEndValidations = (boolean)TRUE;
    pResult->ValidParams = (Std_ReturnType)E_NOT_OK;

    Adc_ReportDetError(u8ServiceId, u8ErrorId);
}
#endif

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
/**
* @brief      This function validates the global call parameters.
* @details    This service is a non reentrant function used for validating the calls for functions
*               like Adc_Init, Adc_DeInit.
*
* @param[in]  u8ServiceId       The service id of the caller function
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid call
* @retval     E_NOT_OK:       Invalid call
*
* @api
*
* @note       Non Re-entrant function.
* @implements  Adc_ValidateGlobalCall_Activity
*
*/ 
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateGloballCall
(
    VAR(uint8, AUTOMATIC) u8ServiceId
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
    
    if (ADC_STATE_UNINIT == Adc_GlobalState)
    {
        if (ADC_INIT_ID == u8ServiceId)
        {
            ValidState = (Std_ReturnType)E_OK;
        }
        else
        {
            Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_UNINIT);
        }
    }
    else
    {
        if (ADC_INIT_ID == u8ServiceId)
        {
            /* Error: ADC already initialized */
            Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_ALREADY_INITIALIZED);
        }
        else
        {
            ValidState = (Std_ReturnType)E_OK;
        }
    }

    return ValidState;
}
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
/**
* @brief      This function validates the global call parameters.
* @details    This service is a non reentrant function used for validating parameters
*               for Adc_Init.
*
* @param[in]  pConfigPtr   Pointer to configuration set in Variant PB
*                         (Variant PC requires a NULL_PTR). 
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid parameter
* @retval     E_NOT_OK:       Invalid parameter
*
* @api
*
* @note       Non Reentrant function.
* @implements  Adc_ValidatePtrInit_Activity
*
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidatePtrInit
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidPtr = (Std_ReturnType)E_OK;

#ifdef ADC_PRECOMPILE_SUPPORT
    /* ADC344 */
    if (NULL_PTR != pConfigPtr)
    {
#else
    /* ADC343 */
    if (NULL_PTR == pConfigPtr)
    {
#endif /* ADC_PRECOMPILE_SUPPORT */
        ValidPtr = (Std_ReturnType)E_NOT_OK; 
        Adc_ReportDetError((uint8)ADC_INIT_ID, (uint8) ADC_E_PARAM_CONFIG);
    }
    return ValidPtr;
}

/**
* @brief      This function validates ...
* @details    This service is a ...
*               ...
*
* @param[in]  PtrVal          Pointer to validate
* @param[in]  u8ServiceId       The service id of the caller function
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid parameter
* @retval     E_NOT_OK:       Invalid parameter
*
* @api
*
* @note       ...
* ADC_VALUEREADGROUP_ID
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidatePtr
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    P2CONST(void, AUTOMATIC, ADC_APPL_DATA) pPtrVal
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidPtr = (Std_ReturnType)E_OK;

    if (NULL_PTR == pPtrVal)
    {
        ValidPtr = (Std_ReturnType)E_NOT_OK;
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_PARAM_POINTER);
    }
    
    return ValidPtr;
}

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))  
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ValidateBufferUninit
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pReturnValue,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    switch (u8ServiceId)
    {
        case ADC_STARTGROUPCONVERSION_ID:
#if (ADC_HW_TRIGGER_API == STD_ON)             
        case ADC_ENABLEHARDWARETRIGGER_ID:
#endif /* ADC_HW_TRIGGER_API == STD_ON */
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (NULL_PTR == Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group])
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_BUFFER_UNINIT);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}
#endif

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || \
      (ADC_HW_TRIGGER_API == STD_ON) || \
      (ADC_ENABLE_CTUTRIG_NONAUTO_API ==STD_ON) || \
      (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) \
     )
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ValidateTriggerSrc
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pReturnValue,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    switch (u8ServiceId)
    {
        case ADC_STARTGROUPCONVERSION_ID:
        case ADC_STOPGROUPCONVERSION_ID:            
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)            
        case ADC_ENABLE_CHANNEL_ID:
        case ADC_DISABLE_CHANNEL_ID:            
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_TRIGG_SRC_SW != Adc_CfgPtr->pGroups[Group].eTriggerSource)
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_WRONG_TRIGG_SRC);
            }
            break;
        }
#if (ADC_HW_TRIGGER_API == STD_ON)
        case ADC_ENABLEHARDWARETRIGGER_ID:
        case ADC_DISABLEHARDWARETRIGGER_ID:
#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
        case ADC_ENABLECTUTRIGGER_ID:
        case ADC_DISABLECTUTRIGGER_ID:
#endif /* ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON */
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_TRIGG_SRC_SW == (Adc_CfgPtr->pGroups[Group].eTriggerSource))
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_WRONG_TRIGG_SRC);
            }
            break;
        }
#endif /* ADC_HW_TRIGGER_API == STD_ON */
        default:
        {
            break;
        }
    }
    return;
}
#endif

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))  
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ValidateQueueNotFull
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pReturnValue,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_HW_TRIGGER_API == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInHWQueue = (Adc_QueueIndexType)0;
#endif
    
    switch (u8ServiceId)
    {
        case ADC_STARTGROUPCONVERSION_ID:
        {
            if (Adc_UnitStatus[Unit].QueueIndex >= (ADC_QUEUE_MAX_DEPTH_MAX))
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_QUEUE_FULL);
             }
            break;
        }
#if (ADC_HW_TRIGGER_API == STD_ON)
        case ADC_ENABLEHARDWARETRIGGER_ID:
        {
            /* Get HW queue sizes */
            NoGroupsInHWQueue = Adc_GroupsInHwQueue(Unit);
            if (NoGroupsInHWQueue >= (Adc_QueueIndexType)ADC_HW_QUEUE)
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_QUEUE_FULL);
            }
            break;
        }
#endif /* ADC_HW_TRIGGER_API == STD_ON */

        default:
        {
            break;
        }
    }
    return;
}
#endif

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON) || \
    (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ValidateConvMode
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pReturnValue,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    switch (u8ServiceId)
    {
#if (ADC_HW_TRIGGER_API == STD_ON)         
        case ADC_ENABLEHARDWARETRIGGER_ID:    
        case ADC_DISABLEHARDWARETRIGGER_ID:
#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
        case ADC_ENABLECTUTRIGGER_ID:
        case ADC_DISABLECTUTRIGGER_ID:
#endif /* ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON */
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_CONV_MODE_ONESHOT != (Adc_CfgPtr->pGroups[Group].eMode))
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_WRONG_CONV_MODE);
            }
            break;
        }
#endif /* ADC_HW_TRIGGER_API == STD_ON */
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
        case ADC_ENABLE_CHANNEL_ID:
        case ADC_DISABLE_CHANNEL_ID:
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if(ADC_CONV_TYPE_NORMAL != Adc_CfgPtr->pGroups[Group].eType)
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_WRONG_CONV_MODE);
            }
            break;
        }
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */
    
        default:
        {
            break;
        }
    }
    return;
}
#endif

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) 
/** @brief @implements Adc_ValidateEnableDisbleGroupList_Activity */
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_ValidateEnableDisbleGroupList
(
    P2VAR(Adc_ValidationResultType, AUTOMATIC, ADC_APPL_DATA) pReturnValue,
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    switch (u8ServiceId)
    {
        case ADC_ENABLE_CHANNEL_ID:
        case ADC_DISABLE_CHANNEL_ID:
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if((Adc_GroupType)ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX == \
               Adc_CfgPtr->pGroups[Group].EnableChDisableChGroupIndex
              )
            {
                Adc_ReportValidationError(pReturnValue, u8ServiceId, (uint8)ADC_E_WRONG_ENABLE_CH_DISABLE_CH_GROUP);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)  
/** @brief @implements Adc_ValidateEnableDisbleIdList_Activity */
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateEnableDisbleIdList
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_ChannelType, AUTOMATIC) Channel
)
{
    P2CONST(Adc_GroupDefType, AUTOMATIC, ADC_APPL_CONST) pGroupChIndexPtr;
    VAR(Adc_ChannelType, AUTOMATIC) Index = 0U;
    VAR(boolean, AUTOMATIC) bChannelFound = (boolean)FALSE;
    VAR(Std_ReturnType, AUTOMATIC) ReturnValue = (Std_ReturnType)E_NOT_OK;

    switch (u8ServiceId)
    {
        case ADC_ENABLE_CHANNEL_ID:
        case ADC_DISABLE_CHANNEL_ID:
        {
            /** @violates @ref Adc_c_REF_4 Array indexing */
            pGroupChIndexPtr = Adc_CfgPtr->pGroups[Group].pAssignment;
            /* Check if ChannelId is valid: assigned to that group */
            /** @violates @ref Adc_c_REF_4 Array indexing */
            for (Index = 0U; Index < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; Index++)
            {
                /** @violates @ref Adc_c_REF_4 Array indexing */
                if ((Adc_ChannelType)Channel == (Adc_ChannelType)pGroupChIndexPtr[Index])
                {
                    bChannelFound = (boolean)TRUE;
                    break;
                }
            }
            if ((boolean)TRUE == bChannelFound)
            {
                ReturnValue = (Std_ReturnType)E_OK;
            }
            else
            {
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_WRONG_ENABLE_CH_DISABLE_CH_ID);
            }
            break;
        }

        default:
        {
            break;
        }
    }
    return ReturnValue;
}
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || \
      (ADC_HW_TRIGGER_API == STD_ON) || \
      (ADC_ENABLE_CTUTRIG_NONAUTO_API ==STD_ON) || \
      (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) \
     )
/**
* @brief      This function validates ...
* @details    This service is a ...
*               ...
*
* @param[in]    ...
* @param[in]    ...
* @param[in]    ...
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid params
* @retval     E_NOT_OK:       Invalid params
*
* @api
*
* @note       ...
*
*/
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateExtraParams
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(uint32, AUTOMATIC) u32ErrorIdList,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_ValidationResultType, AUTOMATIC) ValidationStatus; 
    
    ValidationStatus.bEndValidations = (boolean)FALSE;
    ValidationStatus.ValidParams = (Std_ReturnType)E_OK; 

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
    if ((0U != (u32ErrorIdList & ADC_E_BUFFER_UNINIT_LIST)) && ((boolean)FALSE == ValidationStatus.bEndValidations))
    {
        /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
        Adc_ValidateBufferUninit(&ValidationStatus, u8ServiceId, Group);
    }
#endif
    if ((0U != (u32ErrorIdList & ADC_E_WRONG_TRIGG_SRC_LIST)) && ((boolean)FALSE == ValidationStatus.bEndValidations))
    {
        /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
       Adc_ValidateTriggerSrc(&ValidationStatus, u8ServiceId, Group);
    }
#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
    if ((0U != (u32ErrorIdList & ADC_E_QUEUE_FULL_LIST)) && ((boolean)FALSE == ValidationStatus.bEndValidations))
    {
        /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
        /** @violates @ref Adc_c_REF_4 Array indexing  */
        Adc_ValidateQueueNotFull(&ValidationStatus, u8ServiceId, Adc_GroupUnit(Group));
    }
#endif
#if ((ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON) || (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON))
    if ((0U != (u32ErrorIdList & ADC_E_WRONG_CONV_MODE_LIST)) && ((boolean)FALSE == ValidationStatus.bEndValidations))
    {
        /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
        Adc_ValidateConvMode(&ValidationStatus, u8ServiceId, Group);
    }
#endif

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
    if ((0U != (u32ErrorIdList & ADC_E_WRONG_ENABLE_CH_DISABLE_CH_GROUP_LIST)) && ((boolean)FALSE == ValidationStatus.bEndValidations))
    {
        /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
        Adc_ValidateEnableDisbleGroupList(&ValidationStatus, u8ServiceId, Group);
    }
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */

    return ValidationStatus.ValidParams;
}
#endif

#if (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON)
/** @brief @implements Adc_ValidateCallAndTrigger_Activity */
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateCallAndTrigger
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(uint8, AUTOMATIC) u8Trigger
)
{
    VAR(Std_ReturnType, AUTOMATIC) ReturnValue = (Std_ReturnType)E_OK;
    
    if (Adc_CfgPtr == NULL_PTR)
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_UNINIT);
        ReturnValue = (Std_ReturnType)E_NOT_OK;
    }
    else if ((uint8)ADC_CTU2_MAX_TRIGGERS_U8 <= u8Trigger)
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_WRONG_CTUV2_TRIGGER);
        ReturnValue = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* do nothing for MISRA*/
    }
    return ReturnValue;
}
#endif /* ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON */

#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
/** @brief @implements Adc_ValidateCtuTriggerSrc_Activity */
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateCtuTriggerSrc
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) Trigger
)
{
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) Index = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Std_ReturnType, AUTOMATIC) ReturnValue = (Std_ReturnType)E_NOT_OK;

    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    for(Index = 0U; Index < Adc_CfgPtr->pGroups[Group].AssignedTriggerCount; Index++)
    {
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        if(Trigger == Adc_CfgPtr->pGroups[Group].pHwResource[Index])
        {
            /* This trigger is configured for this group */
            ReturnValue = (Std_ReturnType)E_OK;
            break;
        }
    }
    if ((Std_ReturnType)E_NOT_OK == ReturnValue)
    {
        /* Report error to DET */
        Adc_ReportDetError(u8ServiceId, (uint8) ADC_E_PARAM_TRIGGER);
    }
    else
    {
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        Unit = Adc_GroupUnit(Group);
        /* Trigger should not be already enabled*/
        if ((ADC_ENABLECTUTRIGGER_ID == u8ServiceId) && (0U != Adc_u8BctuGroupTriggersActive[Unit][Index]))
        {
            /* This trigger has already been for this group */
            ReturnValue = (Std_ReturnType)E_NOT_OK;
            Adc_ReportDetError(u8ServiceId, (uint8) ADC_E_PARAM_TRIGGER);
        }
        /* Trigger should be enabled*/
        else if ((ADC_DISABLECTUTRIGGER_ID == u8ServiceId) && (0U == Adc_u8BctuGroupTriggersActive[Unit][Index]))
        {
            /* This trigger was not enabled for this group */
            ReturnValue = (Std_ReturnType)E_NOT_OK;
            Adc_ReportDetError(u8ServiceId, (uint8) ADC_E_PARAM_TRIGGER);
        }
        else
        {
            /* Do nothing for Misra*/
        }
    }
    return ReturnValue;
}
#endif /* ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON */
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_SET_MODE_API == STD_ON)
/**
* @brief      This function validates the Adc_SetMode call.
* @details    This function validates the Adc_SetMode call.
*
* @param[in]  u8ServiceId   The service id of the caller function
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The Adc_SetMode call is valid
* @retval     E_NOT_OK:       The Adc_SetMode call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateSetMode
(
    VAR(Adc_SetModeType, AUTOMATIC) eSetMode
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_GroupType, AUTOMATIC) Group = 0U;
    VAR(Std_ReturnType, AUTOMATIC) SleepModeStatus = (Std_ReturnType)E_OK;
    
    if(NULL_PTR == Adc_CfgPtr)
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* Report error to DET */
        Adc_ReportDetError((uint8)ADC_SETMODE_ID, (uint8)ADC_E_UNINIT);
#endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
        SleepModeStatus = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        if ((ADC_NORMAL_MODE != eSetMode) && (ADC_POWER_DOWN_MODE != eSetMode))
        {
            SleepModeStatus = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Enter critical section to protect against Adc_UnitStatus modifications */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_04();

            for (Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
            {
                if ((ADC_BUSY == Adc_UnitStatus[Unit].eStatus)
#if (ADC_HW_TRIGGER_API == STD_ON)
                    || (Adc_GroupsInHwQueue(Unit) != (Adc_QueueIndexType)0)
#endif /* ADC_HW_TRIGGER_API == STD_ON */
                   )
                {
                    /* Ongoing conversion */
                    SleepModeStatus = (Std_ReturnType)E_NOT_OK;
                    break;
                }
            }
            for(Group = 0U; ((Group < ((Adc_GroupType)ADC_MAX_GROUPS)) && ((Std_ReturnType)E_OK == SleepModeStatus)); Group++)
            {
                if((Adc_GroupStatus[Group].eConversion != ADC_IDLE) && (Adc_GroupStatus[Group].eConversion != ADC_STREAM_COMPLETED))
                {
                    SleepModeStatus = (Std_ReturnType)E_NOT_OK;
                    break;
                }
            }
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_04();                    
        }
#if (ADC_DEV_ERROR_DETECT == STD_ON) 
        if ((Std_ReturnType)E_NOT_OK == SleepModeStatus)
        {
            Adc_ReportDetError((uint8)ADC_SETMODE_ID, (uint8)ADC_E_SET_MODE);
        }
#endif
    }
    return SleepModeStatus;
}
#endif /* ADC_SET_MODE_API == STD_ON */


#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
/**
* @brief        This function ends the validation of the global call parameters.
* @details      This service is a non reentrant function used for end the validation the calls 
*               for functions like Adc_Init, Adc_DeInit.
*
* @param[in]    ValidCall validity of the call
* @param[in]    u8ServiceId The service id of the caller function
*
* @return void
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_EndValidateGloballCall
(
    VAR(Std_ReturnType, AUTOMATIC) ValidCall,
    VAR(uint8, AUTOMATIC) u8ServiceId
)
{
    if ((Std_ReturnType)E_OK == ValidCall)
    {
        if (ADC_DEINIT_ID == u8ServiceId)
        {
            Adc_GlobalState = ADC_STATE_UNINIT;
        }
        else
        {
            Adc_GlobalState = ADC_STATE_IDLE;
        }
    }
}
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/**
* @brief        This function validates the state of a group when priorities are used.
* @details      This service is a non reentrant function used for validating the state of a group 
*                when priorities are used
*
* @param[in]    Unit          The hardware unit
* @param[in]    Group         The group id
* @param[in]    bImplicitly    Indicates if the group can be implicitly stopped
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateNotBusyWithPrio
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(boolean, AUTOMATIC) bImplicitly
)
{
    VAR(boolean, AUTOMATIC) bFlag = (boolean)FALSE;
    VAR(Adc_QueueIndexType, AUTOMATIC) Index = 0U;
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);

    if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0)
    {
        for (Index = 0U; Index < Adc_UnitStatus[Unit].QueueIndex; Index++)
        {
            if (Group == Adc_GroupInQueue(Unit,Index))
            {
                bFlag = (boolean)TRUE;
            }
        }
    }
    if ((((Group == Adc_UnitStatus[Unit].Queue[0]) &&
          (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0)
         ) || ((boolean)TRUE == bFlag)
        ) && ((boolean)FALSE == bImplicitly)
       )
    {
        Adc_ReportDetError((uint8)ADC_STARTGROUPCONVERSION_ID, (uint8)ADC_E_BUSY);
    }
    else if (((Adc_GroupStatus[Group].eConversion != ADC_IDLE
              ) && (Adc_GroupStatus[Group].eConversion != ADC_STREAM_COMPLETED)
             ) && ((boolean)TRUE == bImplicitly)
            )
    {
        Adc_ReportDetError((uint8)ADC_STARTGROUPCONVERSION_ID, (uint8)ADC_E_BUSY);
    }
    else
    {
        ValidState = (Std_ReturnType)E_OK;
    }
    return ValidState;
}    
#endif    
#endif

#if (ADC_VALIDATE_STATE == STD_ON)
#if  (ADC_HW_TRIGGER_API == STD_ON)
#if (ADC_ENABLE_QUEUING == STD_OFF)
/**
* @brief        This function validates the state of a group when the queue is not used.
* @details      This service is a non reentrant function used for validating the state of a group 
*                when the queue is not used
*
* @param[in]    Unit          The hardware unit
* @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateNotBusyNoQueue
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8ServiceId
)
{
    VAR(boolean, AUTOMATIC) bErrorFound = (boolean)FALSE;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInHWQueue = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWQueue = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWInjQueue = 0U;

    /* Enter critical section to protect against queue modifications */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_20();
    /* Get HW and SW queue sizes */
    NoGroupsInHWQueue = Adc_GroupsInHwQueue(Unit);
    NoGroupsInSWQueue = Adc_UnitStatus[Unit].QueueIndex;
    NoGroupsInSWInjQueue = Adc_UnitStatus[Unit].SwInjQueueIndex;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_20();
    /* Check for ongoing conversions */
    if ((NoGroupsInSWQueue != (Adc_QueueIndexType)0) ||
        (NoGroupsInHWQueue != (Adc_QueueIndexType)0) ||
        (NoGroupsInSWInjQueue != (Adc_QueueIndexType)0)
       )
    {
       Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
       bErrorFound =  (boolean)TRUE;
    }
    return bErrorFound;
}
#endif /* ADC_ENABLE_QUEUING == STD_OFF */
#endif
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
#if (ADC_VALIDATE_STATE == STD_ON)
/**
* @brief        This function validates the state of a group when the hardware trigger is enabled.
* @details      This service is a non reentrant function used for validating the state of a group 
*                when the hardware trigger is enabled.
*
 @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateNotBusyEnableHwTrig
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInHWQueue = 0U;
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);
#if (ADC_ENABLE_QUEUING == STD_OFF)
    VAR(boolean, AUTOMATIC) bErrorFound = (boolean)FALSE;
#endif /* ADC_ENABLE_QUEUING == STD_OFF  */

    /* Get HW queue sizes */
    NoGroupsInHWQueue = Adc_GroupsInHwQueue(Unit);

#if (ADC_ENABLE_QUEUING == STD_OFF)
    bErrorFound = Adc_ValidateNotBusyNoQueue(Unit, ADC_ENABLEHARDWARETRIGGER_ID);
    if ((boolean) FALSE == bErrorFound)
#endif /* ADC_ENABLE_QUEUING == STD_OFF  */
    {
#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
        /* The queue is not empty, check the type of the group that will be (or not) en-queued */
        /* Different group type or more than one regular group not allowed */
        /** @violates @ref Adc_c_REF_4 Array indexing */
        if ((Adc_UnitStatus[Unit].HwQueueIndex != (Adc_QueueIndexType)0) && \
            ((Adc_UnitStatus[Unit].HwQueueGroupType != Adc_CfgPtr->pGroups[Group].IsMHTGroup) || \
             ((Adc_MhtGroupType)ADC_REGULAR_GROUP_TYPE == Adc_UnitStatus[Unit].HwQueueGroupType)
            )
           )
        {
            Adc_ReportDetError((uint8)ADC_ENABLEHARDWARETRIGGER_ID, (uint8)ADC_E_BUSY);
        }

        else if ((ADC_HWTRIGGER_ENABLED == Adc_GroupStatus[Group].eHwTriggering) || ((uint8)ADC_HW_QUEUE <= NoGroupsInHWQueue))
#else
        if ((ADC_HWTRIGGER_ENABLED == Adc_GroupStatus[Group].eHwTriggering) && (0U != NoGroupsInHWQueue))
#endif /* ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON */
        {
            Adc_ReportDetError((uint8)ADC_ENABLEHARDWARETRIGGER_ID, (uint8)ADC_E_BUSY);
        }
        else
        {
            ValidState = (Std_ReturnType)E_OK;
        }
    }
    return ValidState;
}
#endif /* (ADC_VALIDATE_STATE == STD_ON) */
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
/**
* @brief        This function validates the state of a group when the ctu trigger is enabled.
* @details      This service is a non reentrant function used for validating the state of a group 
*                when the ctu trigger is enabled.
*
 @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateNotBusyEnableCtuTrig
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
    VAR(Adc_GroupType, AUTOMATIC) GroupInQueue;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);
#if (ADC_ENABLE_QUEUING == STD_OFF)
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWQueue = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWInjQueue = 0U;
#endif /* ADC_ENABLE_QUEUING == STD_OFF */

#if (ADC_ENABLE_QUEUING == STD_OFF) 
 /* Enter critical section to protect against queue modifications */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_20();
    /* Get HW and SW queue sizes */
    NoGroupsInSWQueue = Adc_UnitStatus[Unit].QueueIndex;
    NoGroupsInSWInjQueue = Adc_UnitStatus[Unit].SwInjQueueIndex;
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_20();
    /* Check for ongoing conversions */
    if ((0U != NoGroupsInSWQueue) || (0U != NoGroupsInSWInjQueue))
    {
       Adc_ReportDetError((uint8)ADC_ENABLECTUTRIGGER_ID, (uint8)ADC_E_BUSY);
    }
    else
#endif /* ADC_ENABLE_QUEUING == STD_OFF */
    {
        if (0U != Adc_GroupsInHwQueue(Unit))
        {
            GroupInQueue = Adc_UnitStatus[Unit].HwQueue[0];
            if ((Group != GroupInQueue) || (ADC_HWTRIGGER_ENABLED == Adc_GroupStatus[GroupInQueue].eHwTriggering))
            {
                Adc_ReportDetError((uint8)ADC_ENABLECTUTRIGGER_ID, (uint8)ADC_E_BUSY);
            }
            else
            {
                ValidState = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            ValidState = (Std_ReturnType)E_OK;
        }
    }
    return ValidState;    
}
#endif

#if (ADC_VALIDATE_STATE == STD_ON)
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
/**
* @brief        This function validates the state of a group when priorities are not used.
* @details      This service is a non reentrant function used for validating the state of a group 
*                when priorities are not used
*
* @param[in]    Unit          The hardware unit
* @param[in]    Group         The group id
* @param[in]    bImplicitly   Indicates if the group can be implicitly stopped
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE)Adc_ValidateNotBusyNoPrio
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(boolean, AUTOMATIC) bImplicitly
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
#if (ADC_ENABLE_QUEUING == STD_OFF)
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);
    VAR(boolean, AUTOMATIC) bQueuesEmpty = (boolean)TRUE;
#endif

#if (ADC_ENABLE_QUEUING == STD_OFF)
    if (Adc_UnitStatus[Unit].QueueIndex != (Adc_QueueIndexType)0)
    {
        bQueuesEmpty = (boolean)FALSE;
    }
    if (Adc_UnitStatus[Unit].SwInjQueueIndex != (Adc_QueueIndexType)0)        
    {
        bQueuesEmpty = (boolean)FALSE;
    }
    #if (STD_ON==ADC_HW_TRIGGER_API)
    if (Adc_UnitStatus[Unit].HwQueueIndex != (Adc_QueueIndexType)0)
    {
        bQueuesEmpty = (boolean)FALSE;
    }
    #endif  

    /* Check if any queue is non-empty*/
    if ((boolean)FALSE == bQueuesEmpty)
    {
        Adc_ReportDetError((uint8)ADC_STARTGROUPCONVERSION_ID, (uint8)ADC_E_BUSY);
    }
    else
    {
        ValidState = (Std_ReturnType)E_OK;
    }
    (void)bImplicitly;
    (void)Group;
#else /* ADC_ENABLE_QUEUING == STD_ON */
    if (((boolean)FALSE == bImplicitly) && (ADC_IDLE != Adc_GroupStatus[Group].eConversion))
    {
        Adc_ReportDetError((uint8)ADC_STARTGROUPCONVERSION_ID, (uint8)ADC_E_BUSY);
    }
    else if (((boolean)TRUE == bImplicitly) && (ADC_IDLE != Adc_GroupStatus[Group].eConversion) &&
             (ADC_STREAM_COMPLETED != Adc_GroupStatus[Group].eConversion)
            )
    {
        Adc_ReportDetError((uint8)ADC_STARTGROUPCONVERSION_ID, (uint8)ADC_E_BUSY);
    }
    else
    {
        ValidState = (Std_ReturnType)E_OK;
    }                    
#endif /* ADC_ENABLE_QUEUING  */
    return ValidState;
}
#endif
#endif

#if (ADC_VALIDATE_STATE == STD_ON)
/**
* @brief        This function validates the state of a group (should not be busy).
* @details      This service is a non reentrant function used for validating the state of a group 
*
* @param[in]    u8ServiceId     The service id of the caller function
* @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateStateNotBusy
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_NOT_OK;
    VAR(boolean, AUTOMATIC) bUnderConversion = (boolean)FALSE;
    VAR(Adc_GroupType,AUTOMATIC) GroupId = 0U;
    VAR(boolean, AUTOMATIC) bImplicitly = (boolean)FALSE;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;

    switch (u8ServiceId)
    {
        case ADC_DEINIT_ID:
        {
            /*  Check if ADC is still converting */
            for (GroupId = 0U; GroupId < (Adc_GroupType)ADC_MAX_GROUPS; GroupId++)
            {
                if ((ADC_IDLE != Adc_GroupStatus[GroupId].eConversion) &&
                    (ADC_STREAM_COMPLETED != Adc_GroupStatus[GroupId].eConversion)
                   )
                {
                    bUnderConversion = (boolean)TRUE;
                    break;
                }
            }
            if ((boolean)TRUE == bUnderConversion)
            {
                 /* ADC112 */
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
            }
            else
            {
                ValidState = (Std_ReturnType)E_OK;
            }
            break;
        }
        case ADC_SETUPRESULTBUFFER_ID:
        {
            if (ADC_IDLE != Adc_GroupStatus[Group].eConversion)
            {
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
            }
            else
            {
                ValidState = (Std_ReturnType)E_OK;
            }
            break;
        }
        case ADC_STARTGROUPCONVERSION_ID:
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if ((ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode) || \
                ((ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode) && \
                 (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode) && \
                 (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
                )
               )
            {
                /* The current group can be implicitly stopped */
                bImplicitly = (boolean)TRUE;
            }


            /* Get the unit to which the group belongs to */
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            Unit = Adc_GroupUnit(Group);
#if (STD_ON == ADC_HW_TRIGGER_API)
            /* SW Injected conversions should be entertained only if there are no other HW or CTU injected chains enabled*/
            if ((Adc_UnitStatus[Unit].SwInjQueueIndex != (Adc_QueueIndexType)0) || \
                /** @violates @ref Adc_c_REF_4 Array indexing */
                (((Adc_GroupConvType)ADC_CONV_TYPE_INJECTED == (Adc_CfgPtr->pGroups[Group].eType)) && \
                 (Adc_UnitStatus[Unit].HwQueueIndex != (Adc_QueueIndexType)0)
                )
               )
            #else
            /* Check for ongoing injected conversion */
            if (Adc_UnitStatus[Unit].SwInjQueueIndex != (Adc_QueueIndexType)0) 
            #endif /* #if (STD_ON==ADC_HW_TRIGGER_API) */ 
            {
                /* Return the Group status as IDLE */
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
            }
#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)            
            else if ((boolean)TRUE == Adc_UnitStatus[Unit].bCtuControlOngoing)
            {
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
            }
#endif /* (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON) */
            else
            {
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
                ValidState = Adc_ValidateNotBusyNoPrio(Group, bImplicitly);
#else /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
                ValidState = Adc_ValidateNotBusyWithPrio(Group, bImplicitly);
#endif  /* ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE */
            }
            break;
        }
#if (ADC_HW_TRIGGER_API == STD_ON)
        case ADC_ENABLEHARDWARETRIGGER_ID:
        {
#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
            if ((boolean)TRUE == Adc_UnitStatus[Unit].bCtuControlOngoing)
            {
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_BUSY);
            }
            else
#endif /* (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON) */
            {
                ValidState = Adc_ValidateNotBusyEnableHwTrig(Group);
            }
            break;
        }
#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
        case ADC_ENABLECTUTRIGGER_ID:
        {
            ValidState = Adc_ValidateNotBusyEnableCtuTrig(Group);
            break;
        }
#endif /* ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON */
#endif /* ADC_HW_TRIGGER_API == STD_ON */
        default:
        {
            ValidState = (Std_ReturnType)E_OK;
            break;
        }
   }
   return ValidState;
}
#endif /* ADC_VALIDATE_STATE == STD_ON */


#if (ADC_VALIDATE_STATE == STD_ON)
/**
* @brief        This function validates the state of a group (should not be idle).
* @details      This service is a non reentrant function used for validating the state of a group 
*
* @param[in]    u8ServiceId     The service id of the caller function
* @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           The call is valid
* @retval     E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateStateNotIdle
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_OK;

    switch (u8ServiceId)
    {
#if (ADC_READ_GROUP_API == STD_ON)        
        case ADC_VALUEREADGROUP_ID:
        {
            if ((ADC_IDLE == Adc_GroupStatus[Group].eConversion) &&
                (ADC_NOT_YET_CONVERTED == Adc_GroupStatus[Group].eAlreadyConverted)
               )
            {
                /* ADC388 */
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_IDLE);
                ValidState = (Std_ReturnType)E_NOT_OK;
            }
            break;
        }
#endif /* ADC_READ_GROUP_API == STD_ON */
        case ADC_STOPGROUPCONVERSION_ID:
        {
            if (ADC_IDLE == Adc_GroupStatus[Group].eConversion)
            {
                /* ADC241 */
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_IDLE);
                ValidState = (Std_ReturnType)E_NOT_OK;
            }
            break;
        }
#if (ADC_HW_TRIGGER_API == STD_ON)
        case ADC_DISABLEHARDWARETRIGGER_ID:
        {
            if (ADC_HWTRIGGER_DISABLED == Adc_GroupStatus[Group].eHwTriggering)
            {
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_IDLE);
                ValidState = (Std_ReturnType)E_NOT_OK;
            }
            break;
        }
#endif /* ADC_HW_TRIGGER_API == STD_ON */
        case ADC_GETSTREAMLASTPOINTER_ID:
        {
             if (ADC_IDLE == Adc_GroupStatus[Group].eConversion)
             {
                 Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_IDLE);
                 ValidState = (Std_ReturnType)E_NOT_OK;
             }
            break;
        }
        default:
        {
            break;
        }
    }
    
    return ValidState;
}
#endif

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
/**
* @brief        This function validates the call for a specific group
* @details      This service is non reentrant function on channel used for validating the calls
*               for functions that use a group
*
* @param[in]    u8ServiceId     The service id of the caller function
* @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid call and group
* @retval     E_NOT_OK:       Invalid call or group
*
* @api
* @implements     Adc_ValidateCallAndGroup_Activity
*/
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateCallAndGroup
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidCallAndGroup = (Std_ReturnType)E_NOT_OK;

    if (NULL_PTR == Adc_CfgPtr)
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_UNINIT);
    }
    else if (Group >= Adc_CfgPtr->GroupCount)
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_PARAM_GROUP);
    }
    else
    {
        ValidCallAndGroup = (Std_ReturnType)E_OK;
    }    
      
    return ValidCallAndGroup;
}
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_GET_INJECTED_CONVERSION_STATUS_API == STD_ON) || \
    (ADC_CALIBRATION == STD_ON) || \
    (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON) || \
    defined(__DOXYGEN__)
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
/**
* @brief        This function validates the call for a specific unit
* @details      This service is non reentrant function on channel used for validating the calls
*               for functions that use a unit
*
* @param[in]    u8ServiceId     The service id of the caller function
* @param[in]    Unit          The unit id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid call and group
* @retval     E_NOT_OK:       Invalid call or group
*
* @api
* @implements     Adc_ValidateCallAndUnit_Activity
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateCallAndUnit
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidCallAndUnit = (Std_ReturnType)E_NOT_OK;
    VAR(boolean, AUTOMATIC) bFoundUnit = (boolean)FALSE;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;

    if (NULL_PTR == Adc_CfgPtr)
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_UNINIT);
    }
    else
    {
        for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
        {
            /* Get the index of hardware unit in structure which will match with the hardware unit ID*/
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if(Unit == Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId)
            {
                bFoundUnit = (boolean)TRUE;
                break;
            }
        }
        if ((boolean)FALSE == bFoundUnit)
        {
            Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_PARAM_UNIT);
        }
        else
        {
            ValidCallAndUnit = (Std_ReturnType)E_OK;
        }    
    }
      
    return ValidCallAndUnit;
}
#endif /* ADC_VALIDATE_CALL_AND_UNIT */
#endif /* (ADC_GET_INJECTED_CONVERSION_STATUS_API == STD_ON) || (ADC_CALIBRATION == STD_ON) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
/**
* @brief        This function checks the notification capability of a group.
* @details      This service is non reentrant function on channel used for validating the 
*               notification capability of a group.
*
* @param[in]    u8ServiceId     The service id of the caller function
* @param[in]    Group         The group id
*
* @return     Std_ReturnType  Standard return type.
* @retval     E_OK:           Valid notification capability
* @retval     E_NOT_OK:       Invalid notification capability
*/
STATIC FUNC(Std_ReturnType, ADC_CODE) Adc_NotifyCapablity
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidCapability = (Std_ReturnType)E_OK;

    switch (u8ServiceId)
    {
        case ADC_ENABLEGROUPNOTIFICATION_ID:
        case ADC_DISABLEGROUPNOTIFICATION_ID:
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (NULL_PTR == Adc_CfgPtr->pGroups[Group].Notification)
            {
                ValidCapability = (Std_ReturnType)E_NOT_OK;
                Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_NOTIF_CAPABILITY);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return ValidCapability;
}        
#endif /* ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON */
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */

#ifdef ADC_DMA_SUPPORTED
/**
* @brief          Checks if the the channels of a group are assigned consecutively.
* @details        Return true if the channels in a group form a continuous group, otherwise false.
*
* @param[in]      Group       Adc Group Id.
*
* @return         Adc_DmaContinuousType     Group channels are continuous?.
* @retval         STD_ON        if group channels are continuous.
* @retval         STD_OFF       if group channels are not continuous.
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE FUNC(Adc_DmaContinuousType, ADC_CODE) Adc_CheckGroupContinuous
(
    CONST(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_HwUnitType,  AUTOMATIC) Unit;
    VAR(Adc_ChannelType, AUTOMATIC) ChIdx;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelType, AUTOMATIC) OldChIndex;
    VAR(Adc_DmaContinuousType, AUTOMATIC) RetVal = (Adc_DmaContinuousType)STD_ON;

    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    Unit = Adc_GroupUnit(Group);
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    if ((Adc_CfgPtr->pGroups[Group].LastCh - Adc_CfgPtr->pGroups[Group].FirstCh) == \
        (Adc_CfgPtr->pGroups[Group].AssignedChannelCount - 1U) \
       )
    {
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        for(ChIdx = 1U; ChIdx < Adc_CfgPtr->pGroups[Group].AssignedChannelCount; ChIdx++)
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            ChIndex = Adc_CfgPtr->pGroups[Group].pAssignment[ChIdx];
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            OldChIndex = Adc_CfgPtr->pGroups[Group].pAssignment[ChIdx-1U];

            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (Adc_CfgPtr->pChannels[Unit][ChIndex].ChId !=  (Adc_CfgPtr->pChannels[Unit][OldChIndex].ChId + 1U))
            {
                RetVal = (Adc_DmaContinuousType)STD_OFF;
                break;
            }
        }
    }
    else
    {
        RetVal = (Adc_DmaContinuousType)STD_OFF;
    }
    return RetVal;
}
#endif /* ADC_DMA_SUPPORTED */

/**
* @brief          Initializes the group status structures.
* @details        Initializes the group status structures with the default values.
*
* @param[in]      void
*
* @return         void
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_InitGroupsStatus(void)
{
    VAR(Adc_GroupType,AUTOMATIC) Group = 0U;

    /* Initialize Group Status structures to beginning values */
    for (Group = 0U; Group < Adc_CfgPtr->GroupCount; Group++)
    {
        Adc_GroupStatus[Group].eConversion = ADC_IDLE;
        /* this group was not converted yet */
        Adc_GroupStatus[Group].eAlreadyConverted = ADC_NOT_YET_CONVERTED;

        Adc_GroupStatus[Group].ResultIndex = 0U;
        Adc_GroupStatus[Group].CurrentChannel = 0U;

#ifdef ADC_DMA_SUPPORTED
        Adc_GroupStatus[Group].Adc_DmaContinuous = Adc_CheckGroupContinuous(Group);
#endif /* ADC_DMA_SUPPORTED */

#if (ADC_HW_TRIGGER_API == STD_ON)
        Adc_GroupStatus[Group].eHwTriggering = ADC_HWTRIGGER_DISABLED;
    #if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON)
        Adc_GroupStatus[Group].eCtuTriggering = ADC_HWTRIGGER_DISABLED;
    #endif  /* ADC_ENABLE_CTUTRIG_API == STD_ON */ 
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_DISABLED;
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */
    }
}

/**
* @brief          Initializes the Unit status structures.
* @details        Initializes the Unit status structures with the default values.
*
* @param[in]      void
*
* @return         void
*
* @pre            Driver must be initialized.
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_InitUnitStatus(void)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) QueueIdx = 0U;

    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        /* Mark the HW Unit as IDLE */
        Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
        /* Filled slots in the queue */
        Adc_UnitStatus[Unit].QueueIndex = 0U;
        /* Mark all the queue slots as "empty" */
        for(QueueIdx = 0U; QueueIdx < Adc_CfgPtr->Misc.Adc_QueueMaxDepth; QueueIdx++)
        {
            Adc_UnitStatus[Unit].Queue[QueueIdx] = 0U;
        }
        
        /* SW Injected queue initialization */
        Adc_UnitStatus[Unit].SwInjQueue[0] =0U;
           /* Filled slots in the sw injected queue */
        Adc_UnitStatus[Unit].SwInjQueueIndex = 0U;

#if (ADC_HW_TRIGGER_API == STD_ON)
        Adc_UnitStatus[Unit].HwQueue[0] = 0U;
        /* Filled slots in the Hw queue */
        Adc_UnitStatus[Unit].HwQueueIndex = 0U;
    #if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
        /* by default consider all groups regular groups */
        Adc_UnitStatus[Unit].HwQueueGroupType = ADC_REGULAR_GROUP_TYPE;
    #endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

        Adc_UnitStatus[Unit].bInjConvOngoing = (boolean)FALSE;
    }
}

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/**
* @brief          Checks if conversion values are in the configured range.
* @details        Return true if conversion values are in the configured range, otherwise false.
*
* @param[in]      value       Adc conversion value.
*                 Unit        Adc Hardware Unit.
*                 Index       Adc channel index assigned to a group.
*
* @return         boolean     Conversion value in range flag.
* @retval         TRUE        if conversion values are in the configured range.
* @retval         FALSE       if conversion values are not in the configured range.
*
* @pre            Driver must be initialized.
*/
FUNC(boolean, ADC_CODE) Adc_CheckConversionValuesInRange
(
    VAR(Adc_ValueGroupType, AUTOMATIC) Value,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_ChannelType, AUTOMATIC) Index
)
{
    VAR(boolean, AUTOMATIC) bValInRange = (boolean)FALSE;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_ChannelRangeSelectType, AUTOMATIC) eChRange = Adc_CfgPtr->pChannels[Unit][Index].eChannelRange;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_ValueGroupType, AUTOMATIC) LowLimit = Adc_CfgPtr->pChannels[Unit][Index].ChannelLowLimit;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_ValueGroupType, AUTOMATIC) HighLimit = Adc_CfgPtr->pChannels[Unit][Index].ChannelHighLimit;

    switch (eChRange)
    {
        /* Complete range - independent from channel limit settings. */
        case ADC_RANGE_ALWAYS:
        {
            bValInRange = (boolean)TRUE;
            break;
        }
        /* Range between low limit and high limit - high limit value included. */
        case ADC_RANGE_BETWEEN:
        {
            if ((Value > LowLimit) && (Value <= HighLimit))
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Range above high limit or below low limit - low limit value included. */
        case ADC_RANGE_NOT_BETWEEN:
        {
            if ((Value > HighLimit) || (Value <= LowLimit))
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Range below high limit -high limit value included. */
        case ADC_RANGE_NOT_OVER_HIGH:
        {
            if (Value <= HighLimit)
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Range above low limit. */
        case ADC_RANGE_NOT_UNDER_LOW:
        {
            if (Value > LowLimit)
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Range above high limit. */
        case ADC_RANGE_OVER_HIGH:
        {
            if (Value > HighLimit)
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Range below low limit - low limit value included. */
        case ADC_RANGE_UNDER_LOW:
        {
            if (Value <= LowLimit)
            {
                bValInRange = (boolean)TRUE;
            }
            else
            {
                bValInRange = (boolean)FALSE;
            }
            break;
        }
        /* Unexpected value */
        default:
        {
            break;
        }
    }
    return (boolean)bValInRange;
}
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

#if (ADC_ENABLE_QUEUING == STD_ON)
/**
* @brief          This function performs the dequeue operation on the internal ADC queue.
* @details        This function performs the dequeue operation on the internal ADC queue.
*
* @param[in]      Unit            The used hw Unit.
* @param[in]      CurQueueIndex   The current queue index.
*
* @return         void
*
* @pre This function must be called from a critical region. It is not protecting itself against interruptions.
* @violates @ref Adc_c_REF_3 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_RemoveFromQueue
(
    CONST(Adc_HwUnitType, AUTOMATIC) Unit,
    CONST(Adc_QueueIndexType, AUTOMATIC) CurQueueIndex
)
{
    VAR(Adc_QueueIndexType, AUTOMATIC) PositionIndex = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) CurrentIndex = Adc_UnitStatus[Unit].QueueIndex;

    if((Adc_QueueIndexType)1U >= CurrentIndex)
    {
        /* Zero or one element present in the queue */
        Adc_UnitStatus[Unit].QueueIndex = 0U;
    }
    else
    {
        /* More than one element in the queue */
        /* Move all elements after the one to remove (from CurQueueIndex position) one place to the left */
        for(PositionIndex = (CurQueueIndex + 1U); PositionIndex < CurrentIndex; PositionIndex++)
        {
            Adc_UnitStatus[Unit].Queue[PositionIndex - 1U] =
            (Adc_GroupType)Adc_UnitStatus[Unit].Queue[PositionIndex];
        }
        Adc_UnitStatus[Unit].QueueIndex--;
    }
}
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE))
/**
* @brief          This function inserts a group into the queue.
* @details        This function inserts a group into the queue.
*
* @param[in]      Unit      The hardware Unit.
* @param[in]      Group     The group id.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_InsertIntoQueue
(
    CONST(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* Temporary index in the Queue */
    VAR(Adc_QueueIndexType, AUTOMATIC) QueueTemp = 0U;
    /* Position of the new Group in the Queue */
    VAR(Adc_QueueIndexType, AUTOMATIC) Pos = 0U;
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_GroupPriorityType, AUTOMATIC) gPri = Adc_GroupPriority(Group);
    VAR(Adc_QueueIndexType, AUTOMATIC) qPtr = Adc_UnitStatus[Unit].QueueIndex;

    /* Find the right place in Queue */
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    while((Pos < qPtr) && (Adc_GroupPriority(Adc_GroupInQueue(Unit, Pos)) >= gPri))
    {
        Pos++;
    }
    if(0U == Pos)
    {
        /* Highest priority group detected */
        (void)Adc_Ipw_StopCurrentConversion(Unit, Group, (boolean)TRUE);
    }
    /* Make space for the new Group */
    if(qPtr > Pos)
    {
        for(QueueTemp = qPtr; QueueTemp > Pos; QueueTemp--)
        {
            /* Move elements to the right */
            Adc_UnitStatus[Unit].Queue[QueueTemp] = (Adc_GroupType)Adc_UnitStatus[Unit].Queue[QueueTemp- 1U];
        }
    }
    /* Place the Group in the Queue */
    Adc_UnitStatus[Unit].Queue[Pos] = Group;
    /* Increase the Queue Index */
    Adc_UnitStatus[Unit].QueueIndex++;
}
#endif  /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
* @brief          This function update queue before start a group conversion.
* @details        This function update queue before start a group conversion.
*
* @param[in]      Group     The group id.
* @param[in]      Unit      The hardware Unit.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_UpdateStatusStartConversion
(
    CONST(Adc_GroupType, AUTOMATIC) Group,
    CONST(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* First available slot in the Queue */
    VAR(Adc_QueueIndexType, AUTOMATIC) qPtr = 0U;
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */

    /* Enter critical region to work on queue, DMA, ADC registers */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_07();
    /* Mark the Group as BUSY when the Group goes to the Queue or gets started */
    Adc_GroupStatus[Group].eConversion = ADC_BUSY;
    
    /* Injected conversion mode */
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    if ((Adc_GroupConvType)ADC_CONV_TYPE_INJECTED == Adc_CfgPtr->pGroups[Group].eType)
    {
#ifdef ADC_DMA_SUPPORTED
        if (ADC_DMA == Adc_CfgPtr->Misc.u8Adc_DmaInterruptSoftware)
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U)
            {
                /* Queue is NOT Empty */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                (void)Adc_Ipw_StopCurrentConversion(Unit, Adc_UnitStatus[Unit].Queue[0], (boolean)TRUE);
            }
        }
#endif
        /* Place the Group in the SW Inj Queue */
        Adc_UnitStatus[Unit].SwInjQueue[0] = Group;
        /* Increase the Queue Index */
        Adc_UnitStatus[Unit].SwInjQueueIndex++;
        
        Adc_Ipw_StartInjectedConversion(Unit);
        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();
        /** @violates @ref Adc_c_REF_8 Return statement before end of function. */
        return;
    }
    /* Normal conversion*/
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    qPtr = Adc_UnitStatus[Unit].QueueIndex;
    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Queue is NOT Empty */
        Adc_InsertIntoQueue(Unit, Group);
    }
#else /* ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE */
 #if (ADC_ENABLE_QUEUING == STD_ON)
    qPtr = Adc_UnitStatus[Unit].QueueIndex;
    if (qPtr > (Adc_QueueIndexType)0U)
    {
        /* Place the Group in the Queue */
        Adc_UnitStatus[Unit].Queue[qPtr] = Group;
        /* Increase the Queue Index */
        Adc_UnitStatus[Unit].QueueIndex++;
    }
 #else /* ADC_ENABLE_QUEUING == STD_OFF*/
  /* In this case all the StartConversion should be rejected by DET */
 #endif /* (ADC_ENABLE_QUEUING == STD_ON) */
#endif /* ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE */

#if (ADC_ENABLE_QUEUING == STD_ON)
    if((Adc_UnitStatus[Unit].Queue[0] == Group) ||
       (Adc_UnitStatus[Unit].QueueIndex == (Adc_QueueIndexType)0)
      )
    {
        /* No_priorities OR Queue_is_empty */
        /* Indicate a new group was added to the queue */
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
        if (Adc_UnitStatus[Unit].QueueIndex == (Adc_QueueIndexType)0)
        {
            /* Place the Group in the Queue */
            Adc_UnitStatus[Unit].Queue[0] = Group;
            Adc_UnitStatus[Unit].QueueIndex++;
        }

        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();

        /* ADC will not be running - no ISR can occur now */
        Adc_Ipw_StartNormalConversion(Unit);

#if (ADC_ENABLE_QUEUING == STD_ON)
    }
    else
    {
        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();
    }
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
}

/**
* @brief          This function update queue before start a group conversion.
* @details        This function update queue before start a group conversion.
*
* @param[in]      Group     The group id.
* @param[in]      Unit      The hardware Unit.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_UpdateStatusStopConversion
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) QueueIndex = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) RemovedPos = 0U;
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */

    /* Enter critical region to protect against queue changes from ISRs */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_08();
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of 
        pointer arithmetic */
    if(((ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)|| \
        ((ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode) && \
        (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode))) && \
        (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion) \
      )
    {
        /* group is stopped, change its status to IDLE  */
        Adc_GroupStatus[Group].eConversion = ADC_IDLE;
        /* Stream Completed*/
        Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
        /* FD reset number of samples completed */
        Adc_GroupStatus[Group].ResultIndex = 0U;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* disable group notification (ADC155) */
        Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_DISABLED;
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
        /** @violates @ref Adc_c_REF_8 Return statement before end of function. */
        return;
    }
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Find the Group in the Queue */
    RemovedPos = Adc_UnitStatus[Unit].QueueIndex;  /* initialize with something invalid */
    /* Last valid Group in the Queue */
    QueueIndex = Adc_UnitStatus[Unit].QueueIndex - 1U;

    while (QueueIndex < (Adc_QueueIndexType)ADC_QUEUE_INDEX_TYPE_MAXIMUM)
    {
        if (Group == Adc_UnitStatus[Unit].Queue[QueueIndex] )
        {
            /* The group is found in the Queue */
            /* Store the position of the group to be removed */
            RemovedPos = QueueIndex;
    
            /* Stop the conversion of all channels belonging to this group */
            if((Adc_QueueIndexType)0U == QueueIndex) /* In this case the group might be under conversion */
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
            {
                (void)Adc_Ipw_StopCurrentConversion(Unit, Group, (boolean)FALSE);

                Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
            }
#if (ADC_ENABLE_QUEUING == STD_ON)
            /* Remove group from Queue */
            Adc_RemoveFromQueue(Unit, QueueIndex);
        }
        QueueIndex--;
    }
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */

    /* group is stopped, change its status to IDLE  */
    Adc_GroupStatus[Group].eConversion = ADC_IDLE;
    /* FD reset number of samples completed */
    Adc_GroupStatus[Group].ResultIndex = 0U;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* disable group notification (ADC155) */
    Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_DISABLED;
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Start the next qroup in the Queue (if any) */
    if(((Adc_QueueIndexType)0U == RemovedPos) && (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0U))
    {
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
        /* Structures and pointers will be initialized when the next Group starts */
        Adc_Ipw_StartNormalConversion(Unit);
    }
    else
    {
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
    }
#else
    /* No element will be present in the queue */
    Adc_UnitStatus[Unit].QueueIndex = 0U;

    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
}
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_READ_GROUP_API == STD_ON)
/**
* @brief          This function updates the status variables after the read group operation.
* @details        This function updates the status variables after the read group operation.
*
* @param[in]      Group       The group of which conversion will be started.
* @param[in]      bFlag        Indicates if the values are in the configured limit range.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_UpdateStatusAfterReadGroup
(
    CONST(Adc_GroupType, AUTOMATIC) Group,
    CONST(boolean, AUTOMATIC) bFlag
)
{
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = Adc_GroupUnit(Group);
#if (ADC_ENABLE_QUEUING == STD_ON)
    VAR(Adc_QueueIndexType, AUTOMATIC) QueueIndex = 0U;
#endif
    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
    if((uint8)STD_ON == Adc_CfgPtr->pGroups[Group].u8AdcWithoutInterrupt)
    {
        /* at least once the group was converted */
        Adc_GroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
        /* Update conversion status*/
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /* (bFlag = (boolean)FALSE) => conversion values are not in the configured range */
        if ((boolean)FALSE == bFlag)
        {
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if(ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)
            {
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                if(ADC_TRIGG_SRC_SW == Adc_CfgPtr->pGroups[Group].eTriggerSource)
                {
                    /* ADC449 */
                    Adc_GroupStatus[Group].eConversion = ADC_BUSY;
                }
                else
                {
                    /* ADC450 */
                    Adc_GroupStatus[Group].eConversion = ADC_IDLE;
                }
            }
            else
            {
                /* ADC448 */
                Adc_GroupStatus[Group].eConversion = ADC_BUSY;
            }
            /** @violates @ref Adc_c_REF_8 Return statement before end of function. */
            return;
        } /* ADC447: (bFlag = (boolean)TRUE) => conversion values are in the configured range */
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        if(ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode)
        {
            Adc_GroupStatus[Group].eConversion = ADC_BUSY;
        }
#else
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        if(ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode)
        {
            Adc_GroupStatus[Group].eConversion = ADC_BUSY;
        }
        (void)bFlag;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
        /* NOTE: Streaming groups are NOT allowed without interrupts in configuration */
        /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode) && \
             ( ADC_TRIGG_SRC_SW == Adc_CfgPtr->pGroups[Group].eTriggerSource) \
           )
        {
            Adc_GroupStatus[Group].eConversion = ADC_IDLE;
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if ((Adc_GroupConvType)ADC_CONV_TYPE_INJECTED == Adc_CfgPtr->pGroups[Group].eType)
            {
                if (Adc_UnitStatus[Unit].SwInjQueueIndex > (Adc_QueueIndexType)0)
                {
                    /* empty queue of  SW injected conversions */
                    Adc_UnitStatus[Unit].SwInjQueueIndex--;
                }
            }
            else /* SW NORMAL CONVERSION */
            {
                if (Adc_UnitStatus[Unit].QueueIndex > (Adc_QueueIndexType)0)
                {
#if (ADC_ENABLE_QUEUING == STD_ON)  
                    QueueIndex = Adc_UnitStatus[Unit].QueueIndex - 1U;
                    /* remove group without interrupts from queue  */
                    while (QueueIndex < (Adc_QueueIndexType)ADC_QUEUE_INDEX_TYPE_MAXIMUM)
                    {
                        if (Group == Adc_UnitStatus[Unit].Queue[QueueIndex] )
                        {
                            /* The group is found in the Queue */
                            Adc_RemoveFromQueue(Unit, QueueIndex);
                            break;
                        }
                        QueueIndex--;
                    }
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
                    /* Start / restore next conversion in the queue*/
                    if ((0U == QueueIndex) && (Adc_UnitStatus[Unit].QueueIndex > 0U))
                    {
                        Adc_Ipw_StartNormalConversion(Unit);
                    }
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#else
                    Adc_UnitStatus[Unit].QueueIndex--;
#endif                    
                }
            }
        } 
        else
        {
            Adc_GroupStatus[Group].eConversion = ADC_BUSY;
        }
    }
    else /* (pGroupPtr->u8AdcWithoutInterrupt  == (uint8)STD_ON) */
    {
        /* The following code has been added to respect the State Diagram of Streaming Access Mode */
        if (ADC_COMPLETED == Adc_GroupStatus[Group].eConversion)
        {
            Adc_GroupStatus[Group].ResultIndex = 0U;
            /* ADC331 -- ADC222*/
            Adc_GroupStatus[Group].eConversion = ADC_BUSY;
        }
        else
        {
            /* Compliance with State Diagram */
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            if (ADC_TRIGG_SRC_SW == Adc_CfgPtr->pGroups[Group].eTriggerSource)
            {
                if (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion)
                {
                    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                    if((ADC_CONV_MODE_ONESHOT == Adc_CfgPtr->pGroups[Group].eMode)|| \
                       ((ADC_CONV_MODE_CONTINUOUS == Adc_CfgPtr->pGroups[Group].eMode) && \
                        (ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode) && \
                        (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
                       )
                      )
                    {
                        /* ADC330 - ADC221 */
                        Adc_GroupStatus[Group].eConversion = ADC_IDLE;
                    }
                    else
                    { /* Continuous*/
                        /* ADC329 -- ADC222 */
                        Adc_GroupStatus[Group].eConversion = ADC_BUSY;
                    }
                }
            }
#if (ADC_HW_TRIGGER_API == STD_ON)
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
            else if (ADC_TRIGG_SRC_HW == Adc_CfgPtr->pGroups[Group].eTriggerSource)
            {
                /* Hw Trigger*/
                if (ADC_STREAM_COMPLETED == Adc_GroupStatus[Group].eConversion)
                {
                    /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                    if((ADC_ACCESS_MODE_STREAMING == Adc_CfgPtr->pGroups[Group].eAccessMode)&& \
                       (ADC_STREAM_BUFFER_LINEAR == Adc_CfgPtr->pGroups[Group].eBufferMode)
                      )
                    {
                        /* ADC330 - ADC221*/
                        Adc_GroupStatus[Group].eConversion = ADC_IDLE;
                    }
                    else
                    { /* Simple One-shot mode, in other words in single access mode*/
                        /* ADC329 -- ADC222*/
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
    }
}
#endif /* (ADC_READ_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_UpdateStatusEnableHardware
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    /* Enter critical section */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_10();

#if (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON)
    /* if the queue is empty than simply copy into the groups in queue type the first group type */
    if ((Adc_QueueIndexType)0 == Adc_UnitStatus[Unit].HwQueueIndex)
    {
        Adc_UnitStatus[Unit].HwQueueGroupType = pGroupPtr->IsMHTGroup;
    }
#endif /* (ADC_MULTIPLE_HARDWARE_TRIGGERS == STD_ON) */

    Adc_UnitStatus[Unit].HwQueue[Adc_UnitStatus[Unit].HwQueueIndex] = Group;
    Adc_UnitStatus[Unit].HwQueueIndex++;

    /* Mark the Group as BUSY when the Group goes to the Queue or gets started */
    /* ADC222 */
    Adc_GroupStatus[Group].eConversion = ADC_BUSY;
    /* if HW trigger is enabled for a group, its HW trigger status becoms ENABLED */
    Adc_GroupStatus[Group].eHwTriggering = ADC_HWTRIGGER_ENABLED;
    /* ADC432 */
    /* Put the conversion results from Results Buffer Base Address */
    Adc_GroupStatus[Group].ResultIndex = 0U;
    /*Mark the Unit as BUSY */
    Adc_UnitStatus[Unit].eStatus = ADC_BUSY;
    
    /* Exit critical section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_10();
}

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_UpdateStatusDisableHardware
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    /* Enter critical section */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [ADC157] if HW trigger is disabled for a group, its HW trigger status becoms DISABLED */
    Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_DISABLED;
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* ADC361*/
    /* Mark the Group status as IDLE */
    Adc_GroupStatus[Group].eConversion = ADC_IDLE;

    /* Hardware trigger is disabled */
    Adc_GroupStatus[Group].eHwTriggering = ADC_HWTRIGGER_DISABLED;

    if(Adc_UnitStatus[Unit].HwQueueIndex > 0U)
    {
        /* ADC429 */
        Adc_UnitStatus[Unit].HwQueueIndex--;
    }

    if(0U == Adc_UnitStatus[Unit].HwQueueIndex)
    {
        /* Mark the Unit status as IDLE */
        Adc_UnitStatus[Unit].eStatus = ADC_IDLE;
    }
    
    /* Exit critical section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();
}
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief          Initializes the ADC hardware unit and the driver.
* @details        This function will initialize both the ADC HW unit and the driver structures.
*
* @param[in]      pConfigPtr   Pointer to configuration set in Variant PB
*                             (Variant PC requires a NULL_PTR).
* @return         void
*
* @api            
*
* @post           Initializes the driver.
*
*
* @note           The function Autosar Service ID[hex]: 0x00.
* @note           Synchronous.
* @note           Non Re-entrant function.
* @implements  Adc_Init_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_Init
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr
)
{
#if ((ADC_VALIDATE_GLOBAL_CALL == STD_ON) || (ADC_VALIDATE_PARAMS == STD_ON))
    VAR(Std_ReturnType, AUTOMATIC) ValidStatus = (Std_ReturnType)E_NOT_OK;
#endif
    
#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    ValidStatus = Adc_ValidateGloballCall(ADC_INIT_ID);
    if ((Std_ReturnType)E_OK == ValidStatus)
    {
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        ValidStatus = Adc_ValidatePtrInit(pConfigPtr);          
        if ((Std_ReturnType)E_OK == ValidStatus)
        {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#ifdef ADC_PRECOMPILE_SUPPORT
            /* ADC342 */
            Adc_CfgPtr = &Adc_ConfigPC;
            (void)pConfigPtr;
#else
            /* ADC054 */
            Adc_CfgPtr = pConfigPtr;
#endif /* ADC_PRECOMPILE_SUPPORT */

            /* Initialize the unit status for all units */
            Adc_InitUnitStatus();
            /* Initialize the group status for all groups */
            Adc_InitGroupsStatus();
            /* Call the low level function to initialize driver */
            Adc_Ipw_Init(Adc_CfgPtr);

#if (ADC_VALIDATE_PARAMS == STD_ON)
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }    
    Adc_EndValidateGloballCall(ValidStatus, ADC_INIT_ID);
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */
}

/**
* @brief          Initializes the group specific ADC result buffer pointer as
*                 configured to point to the pDataBufferPtr address which is
*                 passed as parameter.
* @details        Initializes ADC driver with the group specific result buffer 
*                 start address where the conversion results will be stored. 
*                 The application has to ensure that the application buffer, 
*                 where pDataBufferPtr points to, can hold all the conversion 
*                 results of the specified group. The initialization with 
*                 Adc_SetupResultBuffer is required after reset, before a group 
*                 conversion can be started.
*
* @param[in]      Group           Numeric ID of requested ADC channel group.
* @param[in]      pDataBufferPtr   Pointer to result data buffer
*
* @return         Std_ReturnType  Standard return type.
* @retval         E_OK:           Result buffer pointer initialized correctly.
* @retval         E_NOT_OK:       Operation failed or development error
*                                 occurred.
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x0C.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements  Adc_SetupResultBuffer_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/

FUNC(Std_ReturnType, ADC_CODE) Adc_SetupResultBuffer
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataBufferPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_NOT_OK;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_SETUPRESULTBUFFER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidatePtr(ADC_SETUPRESULTBUFFER_ID, pDataBufferPtr))
        {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateStateNotBusy(ADC_SETUPRESULTBUFFER_ID, Group))
            {
#endif /* ADC_VALIDATE_STATE == STD_ON */

                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                pGroupPtr = &Adc_CfgPtr->pGroups[Group];
                /* ADC420 */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                (pGroupPtr->pResultsBufferPtr[Group]) = pDataBufferPtr;
                TempReturn = (Std_ReturnType)E_OK;
#if (ADC_VALIDATE_STATE == STD_ON)
            }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

    return TempReturn;
}

#if (ADC_DEINIT_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Returns all ADC HW Units to a state comparable to their
*                 power on reset state.
* @details        Returns all ADC HW Units to a state comparable to their
*                 power on reset state, and de-initialize the ADC MCAL driver.
*
* @return         void
*
* @api
*
* @note          The function Autosar Service ID[hex]: 0x01.
* @note          Synchronous.
* @note          Non Re-entrant function.
* @implements    Adc_DeInit_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/

FUNC(void, ADC_CODE) Adc_DeInit(void)
{
    VAR(Adc_GroupType,AUTOMATIC) Group = 0U;
#if ((ADC_VALIDATE_GLOBAL_CALL == STD_ON) || (ADC_VALIDATE_STATE == STD_ON))
    VAR(Std_ReturnType, AUTOMATIC) ValidStatus = (Std_ReturnType)E_NOT_OK;
#endif

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    ValidStatus = Adc_ValidateGloballCall(ADC_DEINIT_ID);
    if ((Std_ReturnType)E_OK == ValidStatus)
    {
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        ValidStatus = Adc_ValidateStateNotBusy(ADC_DEINIT_ID, Group);
        if ((Std_ReturnType)E_OK == ValidStatus)
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */

            Adc_Ipw_DeInit(); 
            for (Group = 0U; Group < Adc_CfgPtr->GroupCount; Group++)
            {
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
                Adc_CfgPtr->pGroups[Group].pResultsBufferPtr[Group] = NULL_PTR;
            }
            /* Undefined the global pointer to the configuration */
            Adc_CfgPtr = NULL_PTR;
            
#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }    
    Adc_EndValidateGloballCall(ValidStatus, ADC_DEINIT_ID);
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */
}
#endif /* (ADC_DEINIT_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Starts the conversion of all channels of
*                 the requested ADC Channel group.
* @details        This function will start the SW conversion of all channels
*                 of the requested ADC channel group.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x02.
* @note           Asynchronous.
* @note           Re-entrant function.
* @implements     Adc_StartGroupConversion_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_StartGroupConversion
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware unit on which the requested group will run */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = (Adc_HwUnitType)0;
   
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_STARTGROUPCONVERSION_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotBusy(ADC_STARTGROUPCONVERSION_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_STARTGROUPCONVERSION_ID,
                                                                ADC_E_BUFFER_UNINIT_LIST | \
                                                                ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                                ADC_E_QUEUE_FULL_LIST,
                                                                Group
                                                               )
               )
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
   
                /* Get the unit to which the group belongs to */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                Unit = Adc_GroupUnit(Group);
                /* Update queue */
                Adc_UpdateStatusStartConversion(Group, Unit);
                
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */
}

/**
* @brief          Stops the conversion of all channels of the requested ADC
*                 Channel group.
* @details        This function will stop the SW conversion of all channels
*                 of the requested ADC channel group.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x03.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_StopGroupConversion_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/

FUNC(void, ADC_CODE) Adc_StopGroupConversion
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware unit on which the requested group will run */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = (Adc_HwUnitType)0;
   
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_STOPGROUPCONVERSION_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotIdle(ADC_STOPGROUPCONVERSION_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_STOPGROUPCONVERSION_ID, 
                                                                ADC_E_WRONG_TRIGG_SRC_LIST,
                                                                Group
                                                               )
               )
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
   
                /* Get the unit to which the group belongs to */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                Unit = Adc_GroupUnit(Group);
                Adc_UpdateStatusStopConversion(Group, Unit);
                
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */
}
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_READ_GROUP_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Reads the group conversion results.
* @details        Reads the group conversion results of the last completed
                  conversion round of the requested group and stores the
                  channel values starting at the pDataBufferPtr address.
                  The group channel values are stored in ascending channel
                  number order (in contrast to the storage layout of the
                  result buffer if streaming access is configured).
*
* @param[in]      Group          Numeric ID of requested ADC Channel group.
* @param[in]      pDataBufferPtr  ADC results of all channels of the selected group 
*                                are stored in the data buffer addressed with the pointer.
* @return         Std_ReturnType Standard return type.
* @retval         E_OK:          results are available and written to the
*                                data buffer.
* @retval         E_NOT_OK:      no results are available or development
*                                error occured.
* @api
* @pre            Preconditions as text description. Optional tag.
* @post           Postconditions as text description. Optional tag.
*
* @note           The function Autosar Service ID[hex]: 0x04.
* @note           Synchronous.
* @note           Reentrant function.
* @implements     Adc_ReadGroup_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataBufferPtr
)
{
    /* Return Value */
    VAR(Std_ReturnType, AUTOMATIC) GroupRet = (Std_ReturnType)E_NOT_OK;
    VAR(boolean, AUTOMATIC) bFlag = (boolean)TRUE;
    
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_VALUEREADGROUP_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidatePtr(ADC_VALUEREADGROUP_ID, pDataBufferPtr))
        {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateStateNotIdle(ADC_VALUEREADGROUP_ID, Group))
            {
#endif /* ADC_VALIDATE_STATE == STD_ON */

                /** @violates @ref Adc_c_REF_7 MISRA-C:2004 Rule 1.4: Undefined behaviour.*/
                GroupRet = Adc_Ipw_ReadGroup(Group, pDataBufferPtr, &bFlag);                
                Adc_UpdateStatusAfterReadGroup(Group, bFlag);

#if (ADC_VALIDATE_STATE == STD_ON)
            }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */

    return(GroupRet);
}
#endif /* (ADC_READ_GROUP_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Enables the hardware trigger for the requested ADC Channel group.
* @details        This function will enable the HW trigger source for the requested
*                 ADC channel group. This function does set the CTU register for all 
*                 platform that have the CTU Hw Unit.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x05.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_EnableHardwareTrigger_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware unit on which the requested group will run */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_ENABLEHARDWARETRIGGER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotBusy(ADC_ENABLEHARDWARETRIGGER_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_ENABLEHARDWARETRIGGER_ID, 
                                                                ADC_E_BUFFER_UNINIT_LIST | \
                                                                ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                                ADC_E_WRONG_CONV_MODE_LIST | \
                                                                ADC_E_QUEUE_FULL_LIST,
                                                                Group
                                                               )
               )
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
   
                /* Get the unit to which the group belongs to */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                Unit = Adc_GroupUnit(Group);
                Adc_UpdateStatusEnableHardware(Group, Unit);

                Adc_Ipw_EnableHardwareTrigger(Group, Unit);
                
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_GLOBAL_CALL == STD_ON)
    }
#endif /* ADC_VALIDATE_GLOBAL_CALL == STD_ON */
}

/**
* @brief          Disables the hardware trigger for the requested ADC Channel group.
* @details        This function will disable the HW trigger source for the requested
*                 ADC channel group.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x06.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_DisableHardwareTrigger_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    /* ADC Hardware unit on which the requested group will run */
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = (Adc_HwUnitType)0;
   
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_DISABLEHARDWARETRIGGER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotIdle(ADC_DISABLEHARDWARETRIGGER_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_DISABLEHARDWARETRIGGER_ID, 
                                                                ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                                ADC_E_WRONG_CONV_MODE_LIST,
                                                                Group
                                                               )
               )
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
   
                /* Get the unit to which the group belongs to */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of pointer arithmetic */
                Unit = Adc_GroupUnit(Group);
                Adc_UpdateStatusDisableHardware(Group, Unit);

                Adc_Ipw_DisableHardwareTrigger(Group, Unit);
                
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}
#endif /* (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Enables the notification mechanism for the requested ADC
*                 channel group.
* @details        This function will enable the notification mechanism only for
*                 the requested ADC channel group.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x07.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_EnableGroupNotification_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_EnableGroupNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_ENABLEGROUPNOTIFICATION_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_NotifyCapablity(ADC_ENABLEGROUPNOTIFICATION_ID, Group))
        {
#endif /* ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON */

            /* Enter critical section to protect agains Adc_GroupStatus modifications */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_00();
            Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_ENABLED;
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_00();

#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
        }
#endif /* ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}

/**
* @brief          Disables the notification mechanism for the requested ADC
*                 channel group.
* @details        This function will disable the notification mechanism only for
*                 the requested ADC channel group.
*
* @param[in]      Group       Numeric ID of requested ADC channel group.
* @return         void
*
* @api
*
* @note           The function Autosar Service ID[hex]: 0x08.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_DisableGroupNotification_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_DisableGroupNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_DISABLEGROUPNOTIFICATION_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_NotifyCapablity(ADC_DISABLEGROUPNOTIFICATION_ID, Group))
        {
#endif /* ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON */

            /* Enter critical section to protect against Adc_GroupStatus modifications */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_01();
            Adc_GroupStatus[Group].eNotification = ADC_NOTIFICATION_DISABLED;
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_01();
            
#if (ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON)
        }
#endif /* ADC_VALIDATE_NOTIFY_CAPABILITY == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) || defined(__DOXYGEN__) */

/**
* @brief          Returns the conversion status of the requested ADC Channel group.
* @details        This function will return the conversion status of the requested
*                 ADC channel group.
*
* @param[in]      Group             Numeric ID of requested ADC channel group.
* @return         Adc_StatusType    Conversion status for the requested group.
* @retval         ADC_IDLE          in case of errors.
* @retval         conversion status in case of no errors.
* @api
*
* @note           The function Autosar Service ID[hex]: 0x09.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_GetGroupStatus_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_StatusType, AUTOMATIC) eTempReturn = ADC_IDLE;

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_GETGROUPSTATUS_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

        /* Enter critical section to protect Adc_GroupStatus read */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_02();
        eTempReturn = Adc_GroupStatus[Group].eConversion;    
         /* Exit critical section */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_02();

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
    
    return(eTempReturn);
}

/**
* @brief          Returns the number of valid samples per channel.
* @details        Returns the number of valid samples per channel, stored in
*                 the result buffer. Reads a pointer, pointing to a position
*                 in the group result buffer. With the pointer position, the
*                 results of all group channels of the last completed conversion
*                 round can be accessed. With the pointer and the return value,
*                 all valid group conversion results can be accessed (the user
*                 has to take the layout of the result buffer into account).
*
* @param[in]      Group              Numeric ID of requested ADC channel group.
* @param[out]     PtrToSamplePtr     Pointer to result buffer pointer.
*
* @return         Adc_StreamNumSampleType Number of valid samples per channel.
* @retval         0                 in case of errors.
* @retval         >0                Number of valid samples per channel.
* @api
*
* @note           The function Autosar Service ID[hex]: 0x0B.
* @note           Synchronous.
* @note           Reentrant function.
* @implements     Adc_GetStreamLastPointer_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_GetStreamLastPointer
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
)
{
    /* Number of samples to return */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) NumberOfResults = 0U;

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_GETSTREAMLASTPOINTER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotIdle(ADC_GETSTREAMLASTPOINTER_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
            NumberOfResults = Adc_Ipw_GetStreamLastPointer(Group, PtrToSamplePtr); 
   
#if (ADC_VALIDATE_STATE == STD_ON)
        }
        else
        {
            *PtrToSamplePtr = NULL_PTR;
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
    else
    {
        *PtrToSamplePtr = NULL_PTR;
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
    
    return (NumberOfResults);
}

#if (ADC_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Returns the version information of this module.
* @details        Returns the version information of this module.
*
* @param[out]     pVersionInfo    Pointer to where to store the version
*                                 information of this module.
* @retval         structure       in case of no errors.
* @api
*
* @note           The function Autosar Service ID[hex]: 0x0A.
* @note           Synchronous.
* @note           Reentrant function.
* @implements     Adc_GetVersionInfo_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_GetVersionInfo
(
    P2VAR(Std_VersionInfoType , AUTOMATIC, ADC_APPL_DATA) pVersionInfo
)
{
#if (ADC_VALIDATE_PARAMS == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidatePtr(ADC_GETVERSIONINFO_ID, pVersionInfo))
    {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

        (pVersionInfo)->vendorID = (uint16)ADC_VENDOR_ID;
        (pVersionInfo)->moduleID = (uint16)ADC_MODULE_ID;
        (pVersionInfo)->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
        (pVersionInfo)->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
        (pVersionInfo)->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;

#if (ADC_VALIDATE_PARAMS == STD_ON)
    }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
}
#endif /* (ADC_VERSION_INFO_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_SET_MODE_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Set the ADC mode either to powerdown or normal.
* @details        Set the ADC either to powerdown or normal mode.
*
* @param[in]      SetMode         Normal or powerdown mode.
*
* @return         Std_ReturnType  Standard return type.
* @retval         E_OK:           In case of successful settings.
* @retval         E_NOT_OK:       In case of unsuccessful settings.
*
* @api
*
* @note           The function Non Autosar Service ID[hex]: 0x10.
* @note           Synchronous.
* @note           Non Re-entrant function.
* @implements     Adc_SetMode_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_SetMode
(
    VAR(Adc_SetModeType, AUTOMATIC) SetMode
)
{
    /* Return standard value */
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_NOT_OK;
    
    if ((Std_ReturnType)E_OK == Adc_ValidateSetMode(SetMode))
    { 
        TempReturn = Adc_Ipw_SetMode(SetMode);
    }
    return TempReturn;
}
#endif /* (ADC_SET_MODE_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Enable the TriggerSource for group selected by Group parameter.
* @details        This non Autosar API is used to enable any one of the configured
*                 TriggerSource of the Group. When this non Autosar API is used to
*                 enable the trigger source the CTU interrupt will be disabled by the driver.
*                 So user has to call the non Autosar API Adc_HwResultReadGroup to read
*                 the converted result from the ADC hardware register.
*
* @param[in]      Group            Index of group.
* @param[in]      TriggerSource    Trigger source to be used for the group.
*                                  (Configuration file should contain it for that group).
* @return         void
*
* @api
*
* @note           The function Service ID[hex]: 0x0E.
* @note           Synchronous.
* @note           Non Re-entrant function.
* @implements     Adc_EnableCTUTrigger_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_EnableCTUTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_ENABLECTUTRIGGER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateStateNotBusy(ADC_ENABLECTUTRIGGER_ID, Group))
        {
#endif /* ADC_VALIDATE_STATE == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
            if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_ENABLECTUTRIGGER_ID, 
                                                                ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                                ADC_E_WRONG_CONV_MODE_LIST,
                                                                Group
                                                               )
               )
            {
                if ((Std_ReturnType)E_OK == Adc_ValidateCtuTriggerSrc(ADC_ENABLECTUTRIGGER_ID, Group, TriggerSource))
                {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
                    Adc_Ipw_EnableCtuTrigger(Group, TriggerSource);                
#if (ADC_VALIDATE_PARAMS == STD_ON)
                }
            }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_STATE == STD_ON)
        }
#endif /* ADC_VALIDATE_STATE == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}

/**
* @brief          Disable the TriggerSource for group selected by Group parameter.
* @details        This non Autosar API is used to disable the already enabled
*                 TriggerSource of the Group.
*
* @param[in]      Group            Index of group.
* @param[in]      TriggerSource    Trigger source to be disabled for the group.
*                                  (Configuration file should contain it for that group).
* @return         void
*
* @api
*
* @note           The function Service ID[hex]: 0x0F.
* @note           Synchronous.
* @note           Non Re-entrant function.
* @implements     Adc_DisableCTUTrigger_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_DisableCTUTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwTriggerTimerType, AUTOMATIC) TriggerSource
)
{
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_DISABLECTUTRIGGER_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_DISABLECTUTRIGGER_ID, 
                                                            ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                            ADC_E_WRONG_CONV_MODE_LIST,
                                                            Group
                                                           )
           )
        {
            if ((Std_ReturnType)E_OK == Adc_ValidateCtuTriggerSrc(ADC_DISABLECTUTRIGGER_ID, Group, TriggerSource))
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
                Adc_Ipw_DisableCtuTrigger(Group, TriggerSource);
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}

/**
* @brief          Read the result of the hardware triggered groups conversion result.
* @details        This non Autosar API is used to read the result of the hardware
*                 triggered groups conversion result from the ADC hardware register
*                 in this case the CTU interrupt will be disabled for the group.
*                 The VALID bit CDR register will be cleared automatically when we read the results
*                 from the channel data register. If the user calls non-Autosar function
*                 Adc_HwResultReadGroup() once again before the next conversion takes place, the
*                 Adc_HwResultReadGroup() returns E_NOT_OK.
*
* @param[in]      Group      Index of group.
* @param[in]      pDataPtr    Pointer to a buffer which will be filled by the
*                            conversion results.
* @return         Std_ReturnType Standard return type.
* @retval         E_OK:          results are available and written to the
*                                data buffer.
* @retval         E_NOT_OK:      no results are available or development
*                                error occurred.
* @api
* @note           The function Service ID[hex]: 0x0D.
* @note           Synchronous.
* @note           Non Re-entrant function.
* @implements     Adc_HwResultReadGroup_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_HwResultReadGroup
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataPtr
)
{
    /* Standard return value */
    VAR(Std_ReturnType, AUTOMATIC) GroupRet = (Std_ReturnType)E_NOT_OK;
    
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_HWRESULTREADGROUP_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */

#if (ADC_VALIDATE_PARAMS == STD_ON)
        if (NULL_PTR == pDataPtr)
        {
            GroupRet = (Std_ReturnType)E_NOT_OK;
        }
        else
#endif
        {
            GroupRet = Adc_Ipw_HwResultReadGroup(Group, pDataPtr);
        }
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
    return(GroupRet);
}
#endif /* (ADC_ENABLE_CTUTRIG_NONAUTO_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Enable a channel inside a group.
* @details        This function allows to active a channel assigned to a group for SW normal 
*                 conversion
*
* @param[in]      Group         Symbolic name of group.
* @param[in]      Channel       Symbolic name of channel.
* @return         void
*
* @api
*
* @note           The function Service ID[hex]: 0x12.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_EnableChannel_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_EnableChannel
(
   VAR(Adc_GroupType, AUTOMATIC) Group,
   VAR(Adc_ChannelType, AUTOMATIC) Channel
)
{  
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = (Adc_HwUnitType)0;
    VAR(Adc_ChannelType, AUTOMATIC) ChId;
    VAR(Adc_GroupType, AUTOMATIC) GroupId = ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX;
    
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_ENABLE_CHANNEL_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_ENABLE_CHANNEL_ID, 
                                                            ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                            ADC_E_WRONG_CONV_MODE_LIST | \
                                                            ADC_E_WRONG_ENABLE_CH_DISABLE_CH_GROUP_LIST | \
                                                            ADC_E_WRONG_ENABLE_CH_DISABLE_CH_ID_LIST, \
                                                            Group \
                                                           )
           )
        {
            if ((Std_ReturnType)E_OK == Adc_ValidateEnableDisbleIdList(ADC_ENABLE_CHANNEL_ID, Group, Channel))
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

                /* Get the unit to which the group belongs to */
                /** @violates @ref Adc_c_REF_4 Array indexing */
                Unit = Adc_GroupUnit(Group);
                /** @violates @ref Adc_c_REF_4 Array indexing */
                ChId = Adc_CfgPtr->pChannels[Unit][Channel].ChId;
                /** @violates @ref Adc_c_REF_4 Array indexing */
                GroupId = (Adc_GroupType)Adc_CfgPtr->pGroups[Group].EnableChDisableChGroupIndex;
                /* Global Interrupt disable to protect code section */
                SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_25();
                if(ChId < ADC_ST_EXTENDED_CH)
                {
                    /* Precision channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR0 = ((Adc_NCMRxMask[GroupId].Adc_NCMR0) | (1UL << ChId));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25();
                }
                else if ((ChId >= ADC_ST_EXTENDED_CH) && (ChId <= ADC_ED_EXTENDED_CH))
                {
                    /* Standard channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR1 = ((Adc_NCMRxMask[GroupId].Adc_NCMR1) | (1UL << (ChId - ADC_ST_EXTENDED_CH)));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25();
                }
                else if ((ChId >= ADC_ST_EXTERNAL_CH) && (ChId <= ADC_ED_EXTERNAL_CH))
                {
                    /* External multiplexed channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR2 = ((Adc_NCMRxMask[GroupId].Adc_NCMR2) | (1UL << (ChId - ADC_ST_EXTERNAL_CH)));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25();
                }
                else
                {
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25();
                }
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}

/**
* @brief          Disable a channel inside a group.
* @details        This function allows to de-active a channel assigned to a group for SW normal 
*                 conversion
*
* @param[in]      Group        Symbolic name of group.
* @param[in]      Channel      Symbolic name of channel.
*
* @return         void
*
* @api
* @note           The function Service ID[hex]: 0x13.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_DisableChannel_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_DisableChannel
(
    VAR(Adc_GroupType, AUTOMATIC)Group,
    VAR(Adc_ChannelType, AUTOMATIC)Channel
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) ChId;
    VAR(Adc_GroupType, AUTOMATIC) GroupId = ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX;
    
#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndGroup(ADC_DISABLE_CHANNEL_ID, Group))
    {
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
   
#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidateExtraParams(ADC_DISABLE_CHANNEL_ID, 
                                                            ADC_E_WRONG_TRIGG_SRC_LIST | \
                                                            ADC_E_WRONG_CONV_MODE_LIST | \
                                                            ADC_E_WRONG_ENABLE_CH_DISABLE_CH_GROUP_LIST | \
                                                            ADC_E_WRONG_ENABLE_CH_DISABLE_CH_ID_LIST, \
                                                            Group \
                                                           )
           )
        {
            if ((Std_ReturnType)E_OK == Adc_ValidateEnableDisbleIdList(ADC_DISABLE_CHANNEL_ID, Group, Channel))
            {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

                /** @violates @ref Adc_c_REF_4 Array indexing */
                Unit = Adc_GroupUnit(Group);
                /** @violates @ref Adc_c_REF_4 Array indexing */
                ChId = Adc_CfgPtr->pChannels[Unit][Channel].ChId;
                /** @violates @ref Adc_c_REF_4 Array indexing */
                GroupId = (Adc_GroupType)Adc_CfgPtr->pGroups[Group].EnableChDisableChGroupIndex;
                /* Global Interrupt disable to protect code section */
                SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_18();
                if (ChId < ADC_ST_EXTENDED_CH)
                {   /* Precision channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR0 = ((Adc_NCMRxMask[GroupId].Adc_NCMR0) & (~(1UL << ChId)));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18();
                }
                else if ((ChId >= ADC_ST_EXTENDED_CH) && (ChId <= ADC_ED_EXTENDED_CH))
                {   /* Standard channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR1 = ((Adc_NCMRxMask[GroupId].Adc_NCMR1) & (~(1UL << (ChId - ADC_ST_EXTENDED_CH))));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18();
                }
                else if ((ChId >= ADC_ST_EXTERNAL_CH) && (ChId <= ADC_ED_EXTERNAL_CH))
                {   /* External multiplexed channel */
                    Adc_NCMRxMask[GroupId].Adc_NCMR2 = ((Adc_NCMRxMask[GroupId].Adc_NCMR2) & (~(1UL << (ChId - ADC_ST_EXTERNAL_CH))));
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18();
                }
                else
                {
                    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18();
                }
#if (ADC_VALIDATE_PARAMS == STD_ON)
            }
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

#if (ADC_VALIDATE_CALL_AND_GROUP == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_GROUP == STD_ON */
}
#endif /* (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON) || defined(__DOXYGEN__) */

#if (ADC_GET_INJECTED_CONVERSION_STATUS_API == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          Get the injected conversions status.
* @details        This function checks if an injected conversion (HW,SW) is ongoing
*
* @param[in]      unit            ADC Unit id.
*
* @return         Adc_StatusType  Status of the ADC HW unit.
* @retval         ADC_IDLE:       SW,HW Injection or Hardware Trigger group are idle.
* @retval         ADC_BUSY:       SW,HW Injection or Hardware Trigger is inprogress.
*
* @api
* @note           The function Service ID[hex]: 0x14.
* @note           Synchronous.
* @note           Re-entrant function.
* @implements     Adc_GetInjectedConversionStatus_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Adc_StatusType, ADC_CODE) Adc_GetInjectedConversionStatus
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Adc_StatusType, AUTOMATIC) eTempReturn = (Adc_StatusType)ADC_IDLE;

#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndUnit(ADC_GETINJECTEDCONVERSIONSTATUS_ID, Unit))
    {
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */
        
        /* Global Interrupt disable to protect code section */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_19();

        if (Adc_UnitStatus[Unit].SwInjQueueIndex > (Adc_QueueIndexType)0)
        {
            eTempReturn = (Adc_StatusType)ADC_BUSY;
        }
#if (ADC_HW_TRIGGER_API == STD_ON)
        else if (Adc_UnitStatus[Unit].HwQueueIndex > (Adc_QueueIndexType)0)
        {
            eTempReturn = (Adc_StatusType)ADC_BUSY;
        }
#endif
        else
        {
            /* nothing for Mirsa */
        }
        
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_19();
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */    

    return (eTempReturn);
}
#endif /* (ADC_GET_INJECTED_CONVERSION_STATUS_API) || defined(__DOXYGEN__) */

#if (ADC_CALIBRATION == STD_ON)
/**
* @brief          Executes high accuracy calibration of a ADC HW unit.
* @details        This function calibrates the ADC HW unit and updates calibration related registers
*
* @param[in]      Unit      ADC Unit Id.
* @param[in]      pStatus    Status of the ADC HW unit calibration and 
*                           list of failed and passed tests.
*
* @return         void
*
* @api
*
* @note           The function Service ID[hex]: 0x15.
* @implements  Adc_Calibrate_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(void, ADC_CODE) Adc_Calibrate
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    P2VAR(Adc_CalibrationStatusType , AUTOMATIC, ADC_APPL_DATA) pStatus  
)
{
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndUnit(ADC_CALIBRATE_ID, Unit))
    {
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */   

#if (ADC_VALIDATE_PARAMS == STD_ON)
        if ((Std_ReturnType)E_OK == Adc_ValidatePtr(ADC_CALIBRATE_ID, pStatus))
        {
#endif /* ADC_VALIDATE_PARAMS == STD_ON */

            pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType) E_NOT_OK;

            Adc_Ipw_Calibrate(Unit, pStatus);


#if (ADC_VALIDATE_PARAMS == STD_ON)            
        }
#endif /* ADC_VALIDATE_PARAMS == STD_ON */
        
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */    
    
    return;
}
#endif /* ADC_CALIBRATION == STD_ON */

#if (ADC_SELF_TEST == STD_ON)
/**
* @brief          Executes hardware Self Test of a ADC HW unit.
* @details        This function checks if the ADC HW unit is functioning correctly
*
* @param[in]      Unit    ADC Unit Id.
*
* @return         Std_ReturnType. Status of the ADC HW unit Self Test.
*
* @api
*
* @note           The function Service ID[hex]: 0x16.
* @implements  Adc_SelfTest_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_SelfTest
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Std_ReturnType, AUTOMATIC) ReturnValue = (Std_ReturnType)E_NOT_OK;

#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndUnit(ADC_CALIBRATE_ID, Unit))
    {
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */   

        ReturnValue = Adc_Ipw_SelfTest(Unit);  
    
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    }
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */        
    return ReturnValue;
}
#endif


#if (ADC_ENABLE_CONFIGURE_THRESHOLD_NONAUTO_API == STD_ON) || defined(__DOXYGEN__)
/**
 * @brief   Function to reconfigure High and Low thresholds for a given group.
 *
 * @details This Non Autosar API is used to reconfigure High and Low thresholds for a given group.
 *
 * @note    The function Service ID[hex]: 0x14.
 *
 * @param[in]  GroupId          Index of group
 * @param[in]  LowValue         Low threshold value for channels in the group
 * @param[in]  HighValue        High threshold value for channels in the group
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful Configure Threshold.
 * @retval         E_NOT_OK        In case of unsuccessful ConfigureThreshold.
 *
 * @implements Adc_ConfigureThreshold_Activity
 *
 * @api 
 */
/** @violates @ref Adc_c_REF_3 All declarations and definitions of objects or */
FUNC(Std_ReturnType, ADC_CODE) Adc_ConfigureThreshold
(
    VAR(Adc_GroupType, AUTOMATIC) GroupId,
    VAR(Adc_ValueGroupType, AUTOMATIC) LowValue,
    VAR(Adc_ValueGroupType, AUTOMATIC) HighValue
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) ChCount = 0U;
    VAR(Adc_ChannelType, AUTOMATIC) Ch = 0U;
    VAR(boolean, AUTOMATIC) bErrorFlag = (boolean)FALSE;
    VAR(boolean, AUTOMATIC) bThresholdEnabled = (boolean)FALSE;
    VAR(uint32, AUTOMATIC) u32MaxHighValue = 0U;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex = 0U;
#endif /* if (ADC_DEV_ERROR_DETECT == STD_ON) */
    VAR(Std_ReturnType, AUTOMATIC) ConThdRet = (Std_ReturnType)E_NOT_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (Adc_CfgPtr == NULL_PTR)
    {
        /* Error (ADC302): called prior to initializing */
        Adc_ReportDetError((uint8)ADC_CONFIGURE_THRESHOLD_ID, (uint8)ADC_E_UNINIT);
        bErrorFlag = (boolean)TRUE;
    }
    else if (GroupId >= Adc_CfgPtr->GroupCount)
    {
        /* Error (ADC218): non-existing group ID */
        Adc_ReportDetError(ADC_CONFIGURE_THRESHOLD_ID, (uint8)ADC_E_PARAM_GROUP);
        bErrorFlag = (boolean)TRUE;
    }
    else if (HighValue < LowValue)
    {
        /* Error if High Threshold value is less than Low Threshold value */
        Adc_ReportDetError((uint8)ADC_CONFIGURE_THRESHOLD_ID, (uint8)ADC_E_WRONG_CONF_THRHLD_VALUE);
        bErrorFlag = (boolean)TRUE;
    }
    else
    {
      /* Check for Error: group has no channels with threshold enabled */
      /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
        Unit = Adc_GroupUnit(GroupId);
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            for(HwIndex = 0U; HwIndex < Adc_CfgPtr->Misc.Adc_MaxHwCfg; HwIndex++)
            {
                /* Get the index of hardware unit in structure which will match with the hardware unit ID*/
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
                if(Adc_CfgPtr->pAdc[HwIndex].AdcHardwareUnitId == Unit)
                {
                    break;
                }
            }
            /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
            for(ChCount = 0U; ((boolean)FALSE == bThresholdEnabled) && \
                (ChCount <Adc_CfgPtr->pGroups[GroupId].AssignedChannelCount); \
                ChCount++
               )
            {
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
                Ch = Adc_CfgPtr->pGroups[GroupId].pAssignment[ChCount];
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
                if(ADC_UNUSED_THRESHOLD != Adc_CfgPtr->pChannels[Unit][Ch].u8ThReg)
                {
                    bThresholdEnabled = (boolean)TRUE;
                }
            }

            if ((boolean)FALSE == bThresholdEnabled)
            {
                Adc_ReportDetError((uint8)ADC_CONFIGURE_THRESHOLD_ID, (uint8)ADC_E_WRONG_CONF_THRHLD_GROUP);
                bErrorFlag = (boolean)TRUE;
            }
            else
            {
                /* Test that the High value is within range */
                /** @violates @ref Adc_c_REF_4 Array indexing shall be the only allowed form of */
                u32MaxHighValue = ADC_HIGH_TH_VALUE_U32(((1UL << Adc_CfgPtr->pAdc[HwIndex].Res) - 1UL));

                if (u32MaxHighValue < ADC_HIGH_TH_VALUE_U32((uint32)HighValue))
                {
                    Adc_ReportDetError((uint8)ADC_CONFIGURE_THRESHOLD_ID, (uint8)ADC_E_WRONG_CONF_THRHLD_VALUE);
                    bErrorFlag = (boolean)TRUE;
                }
            }
        }
    }

    if((boolean)FALSE == bErrorFlag)
    {
  #endif /* if (ADC_DEV_ERROR_DETECT == STD_ON) */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_26();
        ConThdRet = Adc_Ipw_ConfigureThreshold(GroupId, LowValue, HighValue);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_26();
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
    }
  #endif

    return ConThdRet;
}
#endif /* ADC_ENABLE_CONFIGURE_THRESHOLD_NONAUTO_API == STD_ON || defined(__DOXYGEN__) */

#if (ADC_DUAL_CLOCK_MODE == STD_ON) 
/**
* @brief          Set the ADC clock prescaler if available and modify the conversion timings.
* @details        This function sets the ADC clock prescaler (Analog clock frequency selector)
*
* @param[in]      eClockMode      Normal or Alternate mode.
*
* @return         Std_ReturnType  Standard return type.
* @retval         E_OK:           In case of successful settings.
* @retval         E_NOT_OK:       In case of unsuccessful settings.
*
* @api
*
* @implements     Adc_SetClockMode_Activity
*/
/**
* @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_SetClockMode
(
    VAR(Adc_DualClockModeType, AUTOMATIC) ClockMode
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Adc_CfgPtr)
    {
        Adc_ReportDetError((uint8)ADC_SETCLOCKMODE_ID, (uint8)ADC_E_UNINIT);
        Ret = (Std_ReturnType)E_NOT_OK;
    }
    else if ((ADC_NORMAL != ClockMode) && (ADC_ALTERNATE != ClockMode))
    {
        Adc_ReportDetError((uint8)ADC_SETCLOCKMODE_ID, (uint8)ADC_E_INVALID_CLOCK_MODE);
        Ret = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Nothing for misra */
    }
    if ((Std_ReturnType)E_OK == Ret)
    {
#endif /* ADC_DEV_ERROR_DETECT == STD_ON*/
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_27();
        Ret = Adc_Ipw_SetClockMode(ClockMode);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_27();
#if (ADC_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* STD_ON == ADC_DEV_ERROR_DETECT */
    return Ret;
}
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */

#if (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON) 
/**
 * @brief   Function to set the trigger handler control registers of the CTUV2 IP.
 *
 * @details Full configurability of CTU THCR1 & THCR2 registers of the CTUv2 IP.
 *          This function has in input the CTU trigger (0...7) and the mask (8 bit)
 *          to enable the External Trigger and Timer output for that Trigger, without considering
 *          the ADC command output enable.
 *          See from the RM the THCR1 and THCR2 registers for the right Thcr_value to use.
 *
 * @note    The function Service ID[hex]: 0x35.
 *
 * @param[in]  Trigger      Index of the trigger: 0...7.
 * @param[in]  ThcrValue   THCRx mask value (only with bits for Ext. Trigger and Timer) for the selected input trigger.
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful settings.
 * @retval         E_NOT_OK        In case of unsuccessful settings.
 *
 * @implements Adc_SetCTU2TriggerHandlerCtrlRegs_Activity
 *
 * @api
 */
/** @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required */
/** @violates @ref Adc_c_REF_5 Identifier clash */
FUNC(Std_ReturnType, ADC_CODE) Adc_SetCtu2TriggerHandlerCtrlRegs
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(uint8, AUTOMATIC) u8ThcrValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_OK;
  
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Ret = Adc_ValidateCallAndTrigger(ADC_CTUV2_SET_TRG_HANDLER_CTRL_REGS_ID, u8Trigger);
    if((Std_ReturnType)E_OK == Ret)
#endif
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28();
        Ret = Adc_Ipw_SetCtu2TriggerHandlerCtrlRegs(u8Trigger, u8ThcrValue);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28();
    }  
    return Ret;
}

/**
* @brief   Function to set or clear the bit Tx_E of the trigger handler control registers of the CTUV2 IP.
 *
 * @details Full configurability of CTU THCR1 & THCR2 registers of the CTUv2 IP.
 *          This function has in input the CTU trigger (0...7) and a Boolean to set to clear the right trigger bit.
 *          See from the RM the THCR1 and THCR2 registers for the right API use.
 *
 * @param[in]  Trigger      Index of the trigger: 0...7.
 * @param[in]  bEnable      if True, the bit Tx_E shall be set to 1, 0 otherwise
 *
 * @note    The function Service ID[hex]: 0x36.
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful settings.
 * @retval         E_NOT_OK        In case of unsuccessful settings.
 *
 * @implements Adc_CTU2TriggerHandlerCtrlRegsEnableDisable_Activity
 *
 * @api
 */
/** @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
 * functions at file scope shall have internal linkage unless external linkage is required
 * @violates @ref Adc_c_REF_5 Identifier clash
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2TriggerHandlerCtrlRegsEnableDisable
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(boolean, AUTOMATIC) bEnable
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Ret = Adc_ValidateCallAndTrigger(ADC_CTUV2_EN_DIS_TRG_HANDLER_CTRL_REGS_ID, u8Trigger);
    if((Std_ReturnType)E_OK == Ret)
#endif
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28();
        Ret = Adc_Ipw_Ctu2TriggerHandlerCtrlRegsEnableDisable(u8Trigger, bEnable);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28();
    }
    return Ret;
}

/**
* @brief   Function to set the cmd list handler control registers of the CTUV2 IP.
 *
 * @details Full configurability of CLCR1 & CLCR2 registers of the CTUv2 IP.
 *          This function has in input the CTU trigger (0...7) and  the position of the first
 *          command in the command list.
 *          See from the RM the CLCR1 and CLCR2 registers for the right API use.
 *
 * @param[in]  u8Trigger      Index of the trigger: 0...7.
 * @param[in]  u8ClcrValue   Position of the first command
 *
 * @note    The function Service ID[hex]: 0x37.
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful settings.
 * @retval         E_NOT_OK        In case of unsuccessful settings.
 *
 * @implements Adc_SetCTU2CmdListHandlerCtrlRegs_Activity
 *
 * @api
 */
/** @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
 * functions at file scope shall have internal linkage unless external linkage is required
 * @violates @ref Adc_c_REF_5 Identifier clash
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_SetCtu2CmdListHandlerCtrlRegs
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(uint8, AUTOMATIC) u8ClcrValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Ret = Adc_ValidateCallAndTrigger(ADC_CTUV2_SET_CMD_LIST_HANDLER_CTRL_REGS_ID, u8Trigger);
    if((Std_ReturnType)E_OK == Ret)
    {
        if ((uint32)u8ClcrValue > ADC_CTU2_CLCR_MAX_VALUE_U8)
        {
            Adc_ReportDetError(ADC_CTUV2_SET_CMD_LIST_HANDLER_CTRL_REGS_ID, ADC_E_WRONG_CTUV2_CLCR_TRIGGER);
            Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
    if((Std_ReturnType)E_OK == Ret)
#endif
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28();
        Ret = Adc_Ipw_SetCtu2CmdListHandlerCtrlRegs(u8Trigger, u8ClcrValue);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28();
    }
    return Ret;
}
/**
 * @brief   Function to set the trigger compare registers of the CTUV2 IP.
 *
 * @details Full configurability of CTU TxCR registers of the CTUv2 IP.
 *          This function has in input the CTU trigger (0...7) and the comparator value
 *          See from the RM the TxCR trigger compare registers for the right compare_value to use.
 *
 * @note    The function Service ID[hex]: 0x38.
 *
 * @param[in]  u8Trigger      Index of the trigger: 0...7.
 * @param[in]  u16CompareValue  value to set in the register TxCR.
 *
 * @return         Std_ReturnType  E_OK or E_NOT_OK.
 * @retval         E_OK            In case of successful settings.
 * @retval         E_NOT_OK        In case of unsuccessful settings.
 *
 * @implements Adc_SetCTU2TriggerCompareRegs_Activity
 *
 * @api
 */
 /** @violates @ref Adc_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required */
FUNC(Std_ReturnType, ADC_CODE) Adc_SetCtu2TriggerCompareRegs
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(uint16, AUTOMATIC) u16CompareValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Ret = Adc_ValidateCallAndTrigger(ADC_CTUV2_SET_TRIGGER_COMPARE_REGS_ID, u8Trigger);
    if((Std_ReturnType)E_OK == Ret)
#endif
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28();
        Ret = Adc_Ipw_SetCtu2TriggerCompareRegs(u8Trigger, u16CompareValue);
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28();
    }
    return Ret;
}
#endif /* if (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON)  */

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
#if (ADC_DEV_ERROR_DETECT == STD_ON)
/**
* @brief        This function validates the Adc unit is activated for Ctu control mode.
* @details      This service is a non reentrant function used for validating the Adc unit when
*               Ctu control mode is used.
*
* @param[in]    Unit            The unit id
*
* @return       Std_ReturnType  Standard return type.
* @retval       E_OK:           The call is valid
* @retval       E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateUnitActive
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Std_ReturnType, AUTOMATIC) Return = (Std_ReturnType)E_OK;

    if ((uint8)STD_OFF == Adc_CfgPtr->pCtuCfgPtr->au8AdcUnitActive[Unit])
    {
        Adc_ReportDetError(u8ServiceId, (uint8)ADC_E_PARAM_UNIT);
        Return = (Std_ReturnType)E_NOT_OK;
    }

    return Return;
}

/**
* @brief        This function validates the state of s unit when the Ctu Control is enabled.
* @details      This service is a non reentrant function used for validating the state of a unit 
*               when the ctu control is enabled.
*
* @param[in]    Unit            The unit id
*
* @return       Std_ReturnType  Standard return type.
* @retval       E_OK:           The call is valid
* @retval       E_NOT_OK:       The call is not valid
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_ValidateStateCtuControlMode
(
    VAR(uint8, AUTOMATIC) u8ServiceId,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(Std_ReturnType, AUTOMATIC) ValidState = (Std_ReturnType)E_OK;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWQueue = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInSWInjQueue = 0U;
    VAR(Adc_QueueIndexType, AUTOMATIC) NoGroupsInHwQueue = 0U;

    switch(u8ServiceId)
    {
        case ADC_ENABLECTUCONTROLMODE_ID:
        {
            /* Enter critical section to protect against queue modifications */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_29();
            /* Get HW and SW queue sizes */
            NoGroupsInSWQueue = Adc_UnitStatus[Unit].QueueIndex;
            NoGroupsInSWInjQueue = Adc_UnitStatus[Unit].SwInjQueueIndex;
            NoGroupsInHwQueue = Adc_UnitStatus[Unit].HwQueueIndex;
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_29();
            
            /* Check for ongoing conversions */
            if ((NoGroupsInSWQueue != (Adc_QueueIndexType)0) ||
                (NoGroupsInSWInjQueue != (Adc_QueueIndexType)0) ||
                (NoGroupsInHwQueue != (Adc_QueueIndexType)0) ||
                ((boolean)TRUE == Adc_UnitStatus[Unit].bCtuControlOngoing)
               )
            {
                ValidState = (Std_ReturnType)E_NOT_OK;
                Adc_ReportDetError((uint8)ADC_ENABLECTUCONTROLMODE_ID, (uint8)ADC_E_BUSY);
            }
            break;
        }
        case ADC_DISABLECTUCONTROLMODE_ID:
        {
            /* Ctu control mode is not already enabled for this unit */
            if((boolean)FALSE == Adc_UnitStatus[Unit].bCtuControlOngoing)
            {
                ValidState = (Std_ReturnType)E_NOT_OK;
                Adc_ReportDetError((uint8)ADC_DISABLECTUCONTROLMODE_ID, (uint8)ADC_E_IDLE);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return ValidState;    
}
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */

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
 * @implements Adc_EnableCtuControlMode_Activity
 *
 * @api
 */
/** @violates @ref Adc_c_REF_3 internal linkage vs external linkage. */
FUNC(void, ADC_CODE) Adc_EnableCtuControlMode
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndUnit(ADC_ENABLECTUCONTROLMODE_ID, Unit))
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if ((Std_ReturnType)E_OK == Adc_ValidateUnitActive(ADC_ENABLECTUCONTROLMODE_ID, Unit))
        {
            if ((Std_ReturnType)E_OK == Adc_ValidateStateCtuControlMode(ADC_ENABLECTUCONTROLMODE_ID, Unit))
            {
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */
                Adc_Ipw_EnableCtuControlMode(Unit);
#if (ADC_DEV_ERROR_DETECT == STD_ON)
            }
        }
    }
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */
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
 * @implements Adc_DisableCtuControlMode_Activity
 *
 * @api
 */
/** @violates @ref Adc_c_REF_3 internal linkage vs external linkage. */
FUNC(void, ADC_CODE) Adc_DisableCtuControlMode
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
#if (ADC_VALIDATE_CALL_AND_UNIT == STD_ON)
    if ((Std_ReturnType)E_OK == Adc_ValidateCallAndUnit(ADC_DISABLECTUCONTROLMODE_ID, Unit))
#endif /* ADC_VALIDATE_CALL_AND_UNIT == STD_ON */
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if ((Std_ReturnType)E_OK == Adc_ValidateUnitActive(ADC_DISABLECTUCONTROLMODE_ID, Unit))
        {
            if ((Std_ReturnType)E_OK == Adc_ValidateStateCtuControlMode(ADC_DISABLECTUCONTROLMODE_ID, Unit))
            {
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */
                Adc_Ipw_DisableCtuControlMode(Unit);
#if (ADC_DEV_ERROR_DETECT == STD_ON)
            }
        }
    }
#endif /* ADC_DEV_ERROR_DETECT == STD_ON */
}
#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */


#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_c_REF_6 Repeated include file MemMap.h*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
