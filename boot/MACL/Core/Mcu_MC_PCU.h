/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_MC_PCU.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:32CST $

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
*   @file    Mcu_MC_PCU.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Function prototypes.
*   @details Interface available for IPW layer only.
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


#ifndef MCU_MC_PCU_H
#define MCU_MC_PCU_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_MC_PCU_h_REF_1
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
/** @violates @ref Mcu_MC_PCU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_MC_PCU_Types.h"

/** @violates @ref Mcu_MC_PCU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_EnvCfg.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_MC_PCU_VENDOR_ID                    43
#define MCU_MC_PCU_AR_RELEASE_MAJOR_VERSION     4
#define MCU_MC_PCU_AR_RELEASE_MINOR_VERSION     0
#define MCU_MC_PCU_AR_RELEASE_REVISION_VERSION  3
#define MCU_MC_PCU_SW_MAJOR_VERSION             1
#define MCU_MC_PCU_SW_MINOR_VERSION             0
#define MCU_MC_PCU_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_MC_PCU_Types header file are from the same vendor */
#if (MCU_MC_PCU_VENDOR_ID != MCU_MC_PCU_TYPES_VENDOR_ID)
    #error "Mcu_MC_PCU.h and Mcu_MC_PCU_Types.h have different vendor ids"
#endif
/* Check if source file and Mcu_MC_PCU_Types header file are of the same Autosar version */
#if ((MCU_MC_PCU_AR_RELEASE_MAJOR_VERSION != MCU_MC_PCU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_PCU_AR_RELEASE_MINOR_VERSION != MCU_MC_PCU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_PCU_AR_RELEASE_REVISION_VERSION != MCU_MC_PCU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_PCU.h and Mcu_MC_PCU_Types.h are different"
#endif
/* Check if source file and Mcu_MC_PCU_Types header file are of the same Software version */
#if ((MCU_MC_PCU_SW_MAJOR_VERSION != MCU_MC_PCU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_MC_PCU_SW_MINOR_VERSION != MCU_MC_PCU_TYPES_SW_MINOR_VERSION) || \
     (MCU_MC_PCU_SW_PATCH_VERSION != MCU_MC_PCU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_PCU.h and Mcu_MC_PCU_Types.h are different"
#endif

/* Check if source file and Mcu_EnvCfg header file are from the same vendor */
#if (MCU_MC_PCU_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_MC_PCU.h and Mcu_EnvCfg.h have different vendor ids"
#endif
/* Check if source file and Mcu_EnvCfg header file are of the same Autosar version */
#if ((MCU_MC_PCU_AR_RELEASE_MAJOR_VERSION != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_PCU_AR_RELEASE_MINOR_VERSION != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_PCU_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_PCU.h and Mcu_EnvCfg.h are different"
#endif
/* Check if source file and Mcu_EnvCfg header file are of the same Software version */
#if ((MCU_MC_PCU_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_MC_PCU_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_MC_PCU_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_PCU.h and Mcu_EnvCfg.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_MC_PCU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_MC_PCU_h_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements
* and comments before '#include' MemMap.h
*/
#include "MemMap.h"

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00) \
    )
FUNC( void, MCU_CODE)
Mcu_MC_PCU_PowerInit(P2CONST( Mcu_MC_PCU_ConfigType, AUTOMATIC, MCU_APPL_DATA) MC_PCU_pConfigPtr);
#endif

#if (MCU_GET_POWER_DOMAIN_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_MC_PCU_Get_PcuState( VAR( void, AUTOMATIC));
#endif /* (MCU_GET_POWER_DOMAIN_API == STD_ON) */

#if (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON)
FUNC( void, MCU_CODE) Mcu_PMU_VoltageError_Int( VAR( void, AUTOMATIC));
#endif /* (MCU_VOLTAGE_ERROR_ISR_USED == STD_ON) */

#if (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON)
FUNC( void, MCU_CODE) Mcu_PMU_TemperatureError_Int( VAR( void, AUTOMATIC) );
#endif /* ( (MCU_TEMPERATURE_ERROR_ISR_USED == STD_ON) ) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_MC_PCU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_MC_PCU_h_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements
* and comments before '#include' MemMap.h
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* MCU_MC_PCU_H */

/** @} */
