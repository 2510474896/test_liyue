/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_IPW_Types.h $
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
*   @file    Mcu_IPW_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from IPW.
*   @details Public data types exported outside of the Mcu driver.
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


#ifndef MCU_IPW_TYPES_H
#define MCU_IPW_TYPES_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_IPW_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_IPW_Types_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory
* section
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
#include "Mcu_MC_CGM_Types.h"
#include "Mcu_MC_ME_Types.h"
#include "Mcu_MC_RGM_Types.h"
#include "Mcu_MC_PCU_Types.h"
#include "Mcu_STCU_Types.h"
#if (MCU_SRAMC_SUPPORT == STD_ON)
  #include "Mcu_PRAM_Types.h"
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
#include "Mcu_FLASH_Types.h"
#include "Mcu_PLLDIG_Types.h"
#include "Mcu_XOSC_Types.h"
#include "Mcu_SSCM_Types.h"
#include "Mcu_CMU_Types.h"
#include "Mcu_SIUL2_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_IPW_TYPES_VENDOR_ID                       43
#define MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION        0
#define MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION     3
#define MCU_IPW_TYPES_SW_MAJOR_VERSION                1
#define MCU_IPW_TYPES_SW_MINOR_VERSION                0
#define MCU_IPW_TYPES_SW_PATCH_VERSION                0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The MCU module's implementer shall avoid the integration of incompatible files.
*/

/* Check if current file and Mcu_MC_CGM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_MC_CGM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_MC_CGM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_MC_CGM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_MC_CGM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_MC_CGM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_MC_CGM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_MC_CGM_Types.h are different"
#endif

/* Check if current file and Mcu_MC_CGM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_MC_CGM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_MC_CGM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_MC_CGM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_MC_CGM_Types.h are different"
#endif

/* Check if current file and Mcu_MC_ME_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_MC_ME_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_MC_ME_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_MC_ME_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_MC_ME_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_MC_ME_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_MC_ME_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_MC_ME_Types.h are different"
#endif

/* Check if current file and Mcu_MC_ME_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_MC_ME_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_MC_ME_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_MC_ME_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_MC_ME_Types.h are different"
#endif

/* Check if current file and Mcu_MC_RGM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_MC_RGM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_MC_RGM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_MC_RGM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_MC_RGM_Types.h are different"
#endif

/* Check if current file and Mcu_MC_RGM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_MC_RGM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_MC_RGM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_MC_RGM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_MC_RGM_Types.h are different"
#endif

/* Check if current file and Mcu_MC_PCU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_MC_PCU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_MC_PCU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_MC_PCU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_MC_PCU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_MC_PCU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_MC_PCU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_MC_PCU_Types.h are different"
#endif

/* Check if current file and Mcu_MC_PCU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_MC_PCU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_MC_PCU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_MC_PCU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_MC_PCU_Types.h are different"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_CMU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_CMU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_CMU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_CMU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CMU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_CMU_Types.h are different"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_CMU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_CMU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_CMU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_CMU_Types.h are different"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_STCU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_STCU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_STCU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_STCU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_STCU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_STCU_Types.h are different"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_STCU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_STCU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_STCU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_STCU_Types.h are different"
#endif

#if (MCU_SRAMC_SUPPORT == STD_ON)
/* Check if current file and Mcu_PRAM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_PRAM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_PRAM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_PRAM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_PRAM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_PRAM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_PRAM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_PRAM_Types.h are different"
#endif

/* Check if current file and Mcu_PRAM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_PRAM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_PRAM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_PRAM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_PRAM_Types.h are different"
#endif
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_FLASH_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_FLASH_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_FLASH_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_FLASH_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_FLASH_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_FLASH_Types.h are different"
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_FLASH_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_FLASH_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_FLASH_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_FLASH_Types.h are different"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_PLLDIG_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_PLLDIG_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_PLLDIG_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_PLLDIG_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h are different"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_PLLDIG_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_PLLDIG_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_PLLDIG_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h are different"
#endif

/* Check if current file and Mcu_XOSC_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_XOSC_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_XOSC_Types.h have different vendor ids"
#endif
/* Check if current file and Mcu_XOSC_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_XOSC_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_XOSC_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_XOSC_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_XOSC_Types.h are different"
#endif
/* Check if current file and Mcu_XOSC_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_XOSC_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_XOSC_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_XOSC_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_XOSC_Types.h are different"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_SSCM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_SSCM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_SSCM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_SSCM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_SSCM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_SSCM_Types.h are different"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_SSCM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_SSCM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_SSCM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_SSCM_Types.h are different"
#endif

/* Check if current file and Mcu_SIUL2_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_SIUL2_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_SIUL2_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_SIUL2_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_SIUL2_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_SIUL2_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_SIUL2_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_SIUL2_Types.h are different"
#endif

/* Check if current file and Mcu_SIUL2_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_SIUL2_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_SIUL2_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_SIUL2_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_SIUL2_Types.h are different"
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define MCU_IPW_IRC_UNDER_MCU_CONTROL               ((uint8)0x01U)
#define MCU_IPW_IRC_NOT_UNDER_MCU_CONTROL           ((uint8)0x00U)
#define MCU_IPW_XOSC_UNDER_MCU_CONTROL              ((uint8)0x04U)
#define MCU_IPW_XOSC_NOT_UNDER_MCU_CONTROL          ((uint8)0x00U)
#define MCU_IPW_PLL0_UNDER_MCU_CONTROL              ((uint8)0x10U)
#define MCU_IPW_PLL0_NOT_UNDER_MCU_CONTROL          ((uint8)0x00U)
#define MCU_IPW_PLL1_UNDER_MCU_CONTROL              ((uint8)0x20U)
#define MCU_IPW_PLL1_NOT_UNDER_MCU_CONTROL          ((uint8)0x00U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Mcu_ClockNotificationType
* @details      Clock failure notification.
*               Enable/disable clock failure interrupt generated by the MCU.
*/
typedef enum
{
    MCU_CLK_NOTIF_DIS = 0x5AU,   /**< @brief Disable clock notification. */
    MCU_CLK_NOTIF_EN = 0xA5U  /**< @brief Enable clock notification. */

} Mcu_ClockNotificationType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            Mcu driver configuration structure.
* @details          Configuration for Mode Entry Module (MC_ME) module:
*                       - ME_RUN_PC0...7 registers
*                       - ME_LP_PC0...7 registers
*                       - ME_PCTLx registers
*                   Configuration for MC_RGM module.
*                   Configuration for power management and SSCM.
*                   Configuration for FLASH controller.
*                   Used by "Mcu_ConfigType" structure.
*
*/
typedef struct
{
    /**< @brief Configuration for MC_ME (Mode Entry Module) hardware IP. */
    P2CONST( Mcu_MC_ME_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_ME_pConfig;
    /**< @brief Configuration for MC_RGM (Reset Generation Module) hardware IP. */
    P2CONST( Mcu_MC_RGM_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_RGM_pConfig;
    /**< @brief Configuration for MC_PCU/PMU (Power Management Unit) hardware IP, part of PCU. */
    P2CONST( Mcu_MC_PCU_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_PCU_pConfig;
    /**< @brief Configuration for FLASH (Flash Memory) hardware IP. */
    P2CONST( Mcu_FLASH_ConfigType, MCU_VAR, MCU_APPL_CONST) FLASH_pConfig;
    /**< @brief Configuration for SSCM module */
    P2CONST( Mcu_SSCM_ConfigType, MCU_VAR, MCU_APPL_CONST) SSCM_pConfig ;

} Mcu_HwIPsConfigType;


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            Definition of a Clock configuration.
* @details          This configuration is transmitted as parameter to Mcu_IPW_InitClock() API.
*                   Used by "Mcu_ConfigType" structure.
*
* @note             The structure Mcu_ConfigType shall provide a configurable (enable/ disable)
*                   clock failure notification if the MCU provides an interrupt for such detection.
*
*/
typedef struct
{
    /**< @brief The ID for Clock configuration. */
    VAR( Mcu_ClockType, MCU_VAR) Mcu_ClkConfigId;
    /**< @brief Clock error notification enable configuration. */
    VAR( Mcu_ClockNotificationType, MCU_VAR) Mcu_ClkNotification;
    /**
    * < @brief System Clock for current Clock configuration.
    * This affect the Mode settings from MC_ME IP.
    */
    VAR( uint32, MCU_VAR ) Mcu_u32SystemClkSource;
    /**< @brief MC_CGM IP Clock settings. */
    P2CONST( Mcu_MC_CGM_ClockConfigType, MCU_VAR, MCU_APPL_CONST) MC_CGM_pClockConfig;
    /**< @brief XOSC IP Clock settings. */
    P2CONST( Mcu_XOSC_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_XOSC_pClockConfig;
    /**< @brief PLLDIG IP Clock settings. */
    P2CONST( Mcu_PLLDIG_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_PLLDIG_pClockConfig;
    /**< @brief CMU IP Clock settings. */
    P2CONST( Mcu_CMU_ConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_CMU_pConfig;
#if (MCU_ECSM_SUPPORT == STD_ON)
    /**< @brief ECSM IP Clock settings. */
    P2CONST( ECSM_Clock_ConfigType, MCU_VAR, MCU_APPL_CONST) ECSM_pClockConfig;
#endif /* (MCU_ECSM_SUPPORT == STD_ON) */
#if (MCU_SRAMC_SUPPORT == STD_ON)
    /**< @brief SRAMC IP Clock settings. */
    P2CONST( Mcu_PRAM_ClockConfigType, MCU_VAR, MCU_APPL_CONST) SRAMC_pClockConfig;
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
    /**< @brief FLASH IP Clock settings. */
    P2CONST( Mcu_FLASH_ClockConfigType, MCU_VAR, MCU_APPL_CONST) FLASH_pClockConfig;
    /**< @brief Clock sources and PLLs under mcu control. */
    VAR( uint8, MCU_VAR) u8ClockSourcesControl;

} Mcu_ClockConfigType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_IPW_TYPES_H */


/** @} */
