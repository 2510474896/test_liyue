/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_IPW.h $
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
*   @file    Mcu_IPW.h
*   @implements Mcu_IPW.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Midle layer interface for Higher layer.
*   @details File contains function prototypes used by HLD only.
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


#ifndef MCU_IPW_H
#define MCU_IPW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_IPW_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
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
/** @violates @ref Mcu_IPW_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_IPW_Types.h"
/** @violates @ref Mcu_IPW_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_EnvCfg.h"
/** @violates @ref Mcu_IPW_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcal.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_IPW_VENDOR_ID                       43
#define MCU_IPW_AR_RELEASE_MAJOR_VERSION        4
#define MCU_IPW_AR_RELEASE_MINOR_VERSION        0
#define MCU_IPW_AR_RELEASE_REVISION_VERSION     3
#define MCU_IPW_SW_MAJOR_VERSION                1
#define MCU_IPW_SW_MINOR_VERSION                0
#define MCU_IPW_SW_PATCH_VERSION                0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The MCU module's implementer shall avoid the integration of incompatible files.
*/

/* Check if current file and Mcu_IPW_Types header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID != MCU_IPW_TYPES_VENDOR_ID)
    #error "Mcu_IPW.h and Mcu_IPW_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_IPW_Types header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION    != MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION    != MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION != MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.h and Mcu_IPW_Types.h are different"
#endif

/* Check if current file and Mcu_IPW_Types header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION != MCU_IPW_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION != MCU_IPW_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION != MCU_IPW_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.h and Mcu_IPW_Types.h are different"
#endif

/* Check if current file and Mcu_EnvCfg header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_IPW.h and Mcu_EnvCfg.h have different vendor ids"
#endif

/* Check if current file and Mcu_EnvCfg header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION    != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION    != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.h and Mcu_EnvCfg.h are different"
#endif

/* Check if current file and Mcu_EnvCfg header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.h and Mcu_EnvCfg.h are different"
#endif

/* Check if current file and Mcal header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_IPW_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_IPW.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


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
/** @violates @ref Mcu_IPW_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"


FUNC( void, MCU_CODE) Mcu_IPW_Init(P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pHwIPsConfigPtr);

#if (MCU_INIT_CLOCK == STD_ON)
FUNC( void, MCU_CODE) Mcu_IPW_InitClock(P2CONST( Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pClockConfigPtr);
#endif /* (MCU_INIT_CLOCK == STD_ON) */

FUNC( void, MCU_CODE) Mcu_IPW_SetMode(P2CONST( Mcu_MC_ME_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pModeConfigPtr);

#if (MCU_INIT_CLOCK == STD_ON)
    #if (MCU_NO_PLL == STD_OFF)
FUNC( void, MCU_CODE) Mcu_IPW_DistributePllClock( VAR( void, AUTOMATIC));
    #endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
FUNC( Mcu_PllStatusType, MCU_CODE) Mcu_IPW_GetPllStatus( VAR( void, AUTOMATIC));
#endif /* (MCU_NO_PLL == STD_OFF) */

#if MCU_PERFORM_RESET_API == STD_ON
FUNC( void, MCU_CODE) Mcu_IPW_PerformReset(P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pHwIPsConfigPtr);
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

FUNC( Mcu_ResetType, MCU_CODE) Mcu_IPW_GetResetReason( VAR( void, AUTOMATIC));

FUNC( Mcu_RawResetType, MCU_CODE) Mcu_IPW_GetResetRawValue( VAR( void, AUTOMATIC));


#if (MCU_GET_RAM_STATE_API == STD_ON)
FUNC (Mcu_RamStateType, MCU_CODE) Mcu_IPW_GetRamState( VAR( void, AUTOMATIC));
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#if (MCU_GET_PERIPH_STATE_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_IPW_GetPeripheralState(VAR( Mcu_PeripheralId, AUTOMATIC) Mcu_PeriphId);
#endif /* (MCU_GET_PERIPH_STATE_API == STD_ON) */

#if (MCU_GET_SYSTEM_STATE_API == STD_ON)
FUNC( uint32, MCU_CODE) Mcu_IPW_GetSystemState ( VAR( void, AUTOMATIC));
#endif /* (MCU_GET_SYSTEM_STATE_API == STD_ON) */

#if (MCU_POWERMODE_STATE_API == STD_ON)
FUNC( Mcu_PowerModeStateType, MCU_CODE) Mcu_IPW_GetPowerModeState( VAR( void, AUTOMATIC));
#endif /* (MCU_POWERMODE_STATE_API == STD_ON) */

#if (MCU_GET_POWER_DOMAIN_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_IPW_GetPowerDomainState( VAR( void, AUTOMATIC));
#endif /* (MCU_GET_POWER_DOMAIN_API == STD_ON) */

#if (MCU_GET_MEM_CONFIG_API == STD_ON)
FUNC( Mcu_SSCM_MemConfigType, MCU_CODE ) Mcu_IPW_SscmGetMemConfig( VAR( void, AUTOMATIC) );
#endif /* (MCU_GET_MEM_CONFIG_API == STD_ON) */

#if (MCU_SSCM_GET_STATUS_API == STD_ON)
FUNC( Mcu_SSCM_StatusType, MCU_CODE ) Mcu_IPW_SscmGetStatus( VAR( void, AUTOMATIC) );
#endif /* (MCU_SSCM_GET_STATUS_API == STD_ON) */

#ifdef MCU_SSCM_GET_UOPS_API
#if (MCU_SSCM_GET_UOPS_API == STD_ON)
FUNC( Mcu_SSCM_UopsType, MCU_CODE ) Mcu_IPW_SscmGetUops( VAR( void, AUTOMATIC) );
#endif /* (MCU_SSCM_GET_UOPS_API == STD_ON) */
#endif /* MCU_SSCM_GET_UOPS_API */

#if (MCU_GET_MIDR_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_IPW_GetMidrStructure(P2VAR( Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr);
#endif /*(MCU_GET_MIDR_API == STD_ON)*/

#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
FUNC( void, MCU_CODE ) Mcu_IPW_Disable_CMU(VAR (uint8, AUTOMATIC) u8IndexCmu);
#endif
#endif

#define MCU_STOP_SEC_CODE
/** @violates @ref Mcu_IPW_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* MCU_IPW_H */

/** @} */
