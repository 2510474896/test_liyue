/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Mcu_Cfg.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:19CST $

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
*  @file    Mcu_Cfg.h
*  @implements Mcu_Cfg.h_Artifact
*  @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Configuration file for the driver.
*   @details Precompile parameters and extern configuration.
*
*  @addtogroup MCU
*  @{
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


#ifndef MCU_CFG_H
#define MCU_CFG_H

#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_CFG_H_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_CFG_H_REF_2
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to braced initialiser,
* a constant, a parenthesised expression, a type qualifier, a storage class specifier, or
* a do-while-zero construct
*
* @section Mcu_CFG_H_REF_3
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function
*
* @section Mcu_CFG_H_REF_4
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_CFG_H_REF_5
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_CFG_H_REF_6
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
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
/** @violates @ref Mcu_CFG_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcal.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_CFG_VENDOR_ID                        43
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION         4
#define MCU_CFG_AR_RELEASE_MINOR_VERSION         0
#define MCU_CFG_AR_RELEASE_REVISION_VERSION      3
#define MCU_CFG_SW_MAJOR_VERSION                 1
#define MCU_CFG_SW_MINOR_VERSION                 0
#define MCU_CFG_SW_PATCH_VERSION                 0
#define MCU_MODULE_ID                            101

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcal header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_CFG_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Cfg.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
#define MCU_INSTANCE_ID                 ((uint8)0x0U)

/**
@{
* @brief            Service Ids for MCU APIs.
*/
#define MCU_INIT_ID                     ((uint8)0x00U)
#define MCU_INITRAMSECTION_ID           ((uint8)0x01U)
#define MCU_INITCLOCK_ID                ((uint8)0x02U)
#define MCU_DISTRIBUTEPLLCLOCK_ID       ((uint8)0x03U)
#define MCU_GETPLLSTATUS_ID             ((uint8)0x04U)
#define MCU_GETRESETREASON_ID           ((uint8)0x05U)
#define MCU_GETRESETRAWVALUE_ID         ((uint8)0x06U)
#define MCU_PERFORMRESET_ID             ((uint8)0x07U)
#define MCU_SETMODE_ID                  ((uint8)0x08U)
#define MCU_GETVERSIONINFO_ID           ((uint8)0x09U)
#define MCU_GETRAMSTATE_ID              ((uint8)0x0AU)

#define MCU_GETPOWERDOMAIN_ID           ((uint8)0x0BU)
#define MCU_GETPERIPHERALSTATE_ID       ((uint8)0x0CU)
#define MCU_GETSYSTEMSTATE_ID           ((uint8)0x0DU)
#define MCU_GETPOWERMODESTATE_ID        ((uint8)0x0EU)
#define MCU_GETMEMCONFIG_ID             ((uint8)0x13U)
#define MCU_GETMIDRSTRUCTURE_ID         ((uint8)0x14U)
#define MCU_SSCMGETSTATUS_ID            ((uint8)0x15U)
#define MCU_SSCMGETUOPS_ID              ((uint8)0x16U)
#define MCU_DISABLECMU_ID               ((uint8)0x17U)
/**@}*/

/**
@{
* @brief            Development error values are of type uint8.
*                   The following errors and exceptions shall be detectable by the MCU module depending on its
*                   build version (development/production mode).
*
*/
#define MCU_E_PARAM_CONFIG              ((uint8)0x0AU)
#define MCU_E_PARAM_CLOCK               ((uint8)0x0BU)
#define MCU_E_PARAM_MODE                ((uint8)0x0CU)
#define MCU_E_PARAM_RAMSECTION          ((uint8)0x0DU)
#define MCU_E_PLL_NOT_LOCKED            ((uint8)0x0EU)
#define MCU_E_UNINIT                    ((uint8)0x0FU)
#define MCU_E_PARAM_POINTER             ((uint8)0x10U)
#define MCU_E_CLOCK_UNINIT              ((uint8)0x11U)
#define MCU_E_SWITCH_MODE_INVALID       ((uint8)0x12U)
#define MCU_E_ALLREADY_INITIALIZED      ((uint8)0x13U)
#define MCU_E_TRANSITION                ((uint8)0x20U)
#define MCU_E_CMU_INDEX_OUT_OF_RANGE    ((uint8)0x22U)
/**@}*/

/**
@{
* @brief            Error ISR values are of type uint8.
*                   The following error codes are reported by the error ISR.
*/
#define MCU_E_ISR_CLOCK_FAILURE                 ((uint8)0x01U)
#define MCU_E_ISR_PLL_LOCK_FAILURE              ((uint8)0x02U)
#define MCU_E_ISR_SAFE_MODE                     ((uint8)0x03U)
#define MCU_E_ISR_INVALID_MODE                  ((uint8)0x04U)
#define MCU_E_ISR_INVALID_MODE_CONFIG           ((uint8)0x05U)
#define MCU_E_ISR_VOLTAGE_ERROR                 ((uint8)0x06U)
#define MCU_E_ISR_TEMPERATURE_MONITOR_ERROR     ((uint8)0x07U)
#define MCU_E_ISR_FUNC_RESET_ALT_FAILURE        ((uint8)0x08U)
#define MCU_E_ISR_DEST_RESET_ALT_FAILURE        ((uint8)0x09U)
/**@}*/


/**
* @brief            Pre-processor switch for enabling the development error detection and reporting to the DET.
*                   The detection of development errors is configurable (ON / OFF) at pre-compile time.
*/
#define MCU_DEV_ERROR_DETECT   (STD_OFF)


/**
* @brief            Pre-processor switch to enable/disable the API to read out the modules version information.
*/
#define MCU_VERSION_INFO_API   (STD_OFF)


/**
* @brief            Pre-processor switch to enable/disable the API Mcu_GetRamState.
*/
#define MCU_GET_RAM_STATE_API   (STD_OFF)


/**
* @brief            If this parameter is set to FALSE, the clock initialization has to be disabled from the MCU driver.
*/
#define MCU_INIT_CLOCK   (STD_ON)


/**
* @brief            This parameter shall be set True, if the H/W does not have a PLL or the PLL circuitry is enabled after the power on without S/W intervention.
*/
#define MCU_NO_PLL   (STD_OFF)


/**
* @brief            Support for Low Power mode.
*                   If this parameter has been configured to 'TRUE', the function 'Mcu_SetMode()' shall not be impacted and behave as specified.
* @requirements     PR-MCAL-3184
*/
#define MCU_ENTER_LOW_POWER_MODE   (STD_ON)


/**
* @brief            The function Mcu_PerformReset is only available if the runtime parameter McuPerformResetApi is set to TRUE.
*/
#define MCU_PERFORM_RESET_API   (STD_ON)


/**
* @brief            Timeout representing the number of loops for preventing to lock inside am infinite while/for.
*/
#define MCU_TIMEOUT_LOOPS   ((uint32)10000U)


/**
* @brief            The user callout reset is/isn't available (STD_ON/STD_OFF) - called by MCU right before Mcu_PerformReset().
*/
#define MCU_RESET_CALLOUT_USED   (STD_OFF)








/**
* @brief            ISR Mcu_ModeTransitionComplete_ISR complete is/isn't available (STD_ON/STD_OFF).
*                   If at least one McuModuleConfiguration has the McuTransitionComplete parameter set true,
*                       then this precompile define is set to STD_ON.
*/
#define MCU_TRANSITION_COMPLETE_ISR_USED   (STD_OFF)
/**
* @brief            ISR Mcu_ModeEnterSafe_ISR is/isn't available (STD_ON/STD_OFF).
*/
#define MCU_SAFE_MODE_ISR_USED   (STD_OFF)
/**
* @brief            ISR Mcu_ModeInvalid_ISR is/isn't available (STD_ON/STD_OFF).
*/
#define MCU_INVALID_MODE_ISR_USED   (STD_OFF)
/**
* @brief            ISR Mcu_ModeInvalidConfig_ISR is/isn't available (STD_ON/STD_OFF).
*/
#define MCU_INVALID_CONFIGURATION_ISR_USED   (STD_OFF)
/**
* @brief            ISR Mcu_ModeInvalidConfig_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_INVALID_CLK_CONFIGURATION_ISR_USED   (STD_OFF)

/**
* @brief            ISR Mcu_ModeInvalidConfig_ISR is/isn't available (STD_ON/STD_OFF).
*/
#define MCU_INVALID_CORE_CONFIGURATION_ISR_USED   (STD_OFF)

/**
* @brief            ISR Mcu_ResetAlternate_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_RESET_ALTERNATE_ISR_USED   (STD_OFF)

/**
* @brief            ISR Mcu_VoltageError_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_VOLTAGE_ERROR_ISR_USED   (STD_OFF)
/**
* @brief            ISR Mcu_VoltageError_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_TEMPERATURE_ERROR_ISR_USED   (STD_OFF)

/**
* @brief            ISR Mcu_CmuClockFail_ISR is always available
*/
#define MCU_CMU_ERROR_ISR_USED (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPeripheral_State() for getting infos about peripheral state from MC_ME module.
*/
#define MCU_GET_PERIPH_STATE_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetSystem_State() for getting infos system platform configuration.
*/
#define MCU_GET_SYSTEM_STATE_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPowerMode_State() for getting infos system platform configuration.
*/
#define MCU_POWERMODE_STATE_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_GetPowerDomain_Status. Get PMU state: operable or not.
*/
#define MCU_GET_POWER_DOMAIN_API   (STD_OFF)

/**
* @brief            ISR Mcu_PllDigPll0_PowerDownComplete_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_PLLDIG_PLL0_EXTPD_ISR_USED (STD_OFF)

/**
* @brief            ISR Mcu_PllDigPll0_LossOfLock_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_PLLDIG_PLL0_LOL_ISR_USED (STD_OFF)

/**
* @brief            ISR Mcu_PllDigPll1_PowerDownComplete_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_PLLDIG_PLL1_EXTPD_ISR_USED (STD_OFF)

/**
* @brief            ISR Mcu_PllDigPll1_LossOfLock_ISR is/isn't available (STD_ON/STD_OFF)
*/
#define MCU_PLLDIG_PLL1_LOL_ISR_USED (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetMemConfig(). Get SSCM_MEMCONFIG.
*/
#define MCU_GET_MEM_CONFIG_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetStatus(). Get SSCM_STATUS.
*/
#define MCU_SSCM_GET_STATUS_API   (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API Mcu_SscmGetUops(). Get SSCM_UOPS.
*/
#define MCU_SSCM_GET_UOPS_API     (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API  Mcu_GetMidrStructure(). Returns .
*/
#define MCU_GET_MIDR_API    (STD_OFF)

/**
* @brief            Enable the usage of Non-Autosar API  Mcu_Disable_CMU().
*/
#define MCU_DISABLE_CMU_API    (STD_OFF)

/**
* @brief            Enable/Disable the API for reporting the Dem Error.
*/
#define MCU_DISABLE_DEM_REPORT_ERROR_STATUS     (STD_OFF)

/**
* @brief            Configure CADDRN registers - read only on panther
*/
#define MCU_CONFIGURE_CADDRN    (STD_OFF)

/**
* @brief           This define controls the availability of the Mcu_MC_ME_FastModeConfig function
*/
#define MCU_FAST_MODE_CONFIG   (STD_OFF)

/**
* @brief           This define controls the availability of the Low Power Subsystem
*/
#define MCU_LPU_SUPPORT        (STD_OFF)

/**
* @brief            Maximum number of MCU Clock configurations.
*/
#define MCU_MAX_CLKCONFIGS   ((uint32)1U)


/**
* @brief            Maximum number of MCU Mode configurations.
*/
#define MCU_MAX_MODECONFIGS   ((uint32)1U)


/**
* @brief            Maximum number of MCU Ram configurations.
*/
#define MCU_MAX_RAMCONFIGS   ((uint32)1U)




/**
* @brief            Pre-compile Support ON.
*/
#define MCU_PRECOMPILE_SUPPORT   (STD_ON)





/**
* @brief            Pre-Compile structure from Mcu_Cfg.c file.
*/
/** @violates @ref Mcu_CFG_H_REF_2 MISRA 2004 Required Rule 19.4, C macros ... */
#define MCU_CONF_PC extern CONST(Mcu_ConfigType, MCU_CONST) Mcu_Config_PC;




/**
* @brief            The DMA is/not available on the platform.
*/
#define MCU_DMA_SUPPORT     (STD_OFF)



/**
* @brief            The ECSM is/not available on the platform.
*/
#define MCU_ECSM_SUPPORT    (STD_OFF)



/**
* @brief            The SRAMC is/not available on the platform.
*/
#define MCU_SRAMC_SUPPORT   (STD_ON)



/**
* @brief            Number of available CMU units.
*/
#define MCU_CMU_UNITS                           ((uint8)5U)



/**
* @brief            max number of prog. clock switch regs.
*/
#define MCU_CGM_NUMBER_OF_PCS_REGS              ((uint8)9U)



/**
* @brief            max number of system clock regs
*/
#define MCU_CGM_NUMBER_OF_SYSTEM_CLOCK_REGS     ((uint8)1U)



/**
* @brief            number of PCTL regs used on the current platform
*/
#define MCU_MC_ME_NUMBER_OF_PCTL_REGS           ((uint8)31U) /* number of PCTL regs used on the current platform */



/**
* @brief            number of PLL regs used on the current platform
*/
#define MCU_CGM_NUMBER_OF_PLL_REGS              ((uint8)6U)


#define MCU_IRC_UNDER_MCU_CONTROL               (STD_OFF)
#define MCU_XOSC_UNDER_MCU_CONTROL              (STD_OFF)
#define MCU_PLL0_UNDER_MCU_CONTROL              (STD_ON)
#define MCU_PLL1_UNDER_MCU_CONTROL              (STD_ON)

#define MCU_CMU_CLEAR_CLOCK_IRQ_FLAG            (STD_OFF)
#define MCU_RGM_CLEAR_CLOCK_IRQ_FLAG            (STD_OFF)


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            The Mcu_ModeType specifies the identification (ID) for a MCU mode, configured via configuration structure.
* @details          The type shall be uint8, uint16 or uint32.
*
* @implements     Mcu_ModeType_typedef
*
*/
typedef uint32 Mcu_ModeType;


/**
* @brief            The Mcu_RamSectionType specifies the identification (ID) for a RAM section, configured via the configuration structure.
*                   The type shall be uint8, uint16 or uint32, based on best performance.
* @implements Mcu_RamSectionType_typedef
*/
typedef uint32 Mcu_RamSectionType;


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief          Defines the identification (ID) for clock setting configured via the configuration structure.
* @details        The type shall be uint8, uint16 or uint32, depending on uC platform.
*
* @implements Mcu_ClockType_typedef
*/
typedef uint32 Mcu_ClockType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/**
* @brief            Definition of a RAM section within the configuration structure.
*                   The definitions for each RAM section within the structure Mcu_ConfigType shall contain:
*                   - RAM section base address
*                   - Section size
*                   - Data pre-setting to be initialized
*
*/
typedef struct
{
    VAR( Mcu_RamSectionType, MCU_VAR) Mcu_RamSectorId;   /**< @brief The ID for Ram Sector configuration. */
    P2VAR( uint8, MCU_VAR, MCU_APPL_VAR) Mcu_pu8RamBaseAddr;   /**< @brief RAM section base address. */
    VAR( uint32, MCU_VAR) Mcu_u32RamSize;   /**< @brief RAM section size. */
    VAR( uint8, MCU_VAR) Mcu_u8RamDefaultValue;   /**< @brief RAM default value for initialization. */

} Mcu_RamConfigType;



/**
* @brief            The type Mcu_RawResetType specifies the reset reason in raw register format, read from a reset status register.
* @details          The type shall be uint8, uint16 or uint32 based on best performance.
*
* @implements Mcu_RawResetType_typedef
*
*/
typedef uint32 Mcu_RawResetType;   /**< @brief Destructive and Functional Reset Events Log. */

/**
* @brief            DEM error reporting configuration.
* @details          This structure contains information DEM error reporting
*/
typedef struct
{
    VAR( Mcal_DemErrorType, MCU_VAR) Mcu_E_TimeoutFailureCfg;
    VAR( Mcal_DemErrorType, MCU_VAR) Mcu_E_InvalidModeConfigCfg;
    VAR( Mcal_DemErrorType, MCU_VAR) Mcu_E_SscmCerFailureCfg;

} Mcu_DemConfigType;

/*==================================================================================================
                                       CONSTANTS
==================================================================================================*/

/**
* @brief            Create defines with the IDs assigned to Mcu Clock configurations.
*                   These IDs will be transmitted as input parameters for Mcu_InitClock() API.
*/

/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuClockSettingConfig   ((Mcu_ClockType)0U)
/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuConf_McuClockSettingConfig_McuClockSettingConfig   ((Mcu_ClockType)0U)


/**
* @brief            Create defines with the IDs assigned to Mcu Mode configurations.
*                   These IDs will be transmitted as input parameters for Mcu_SetMode() API.
*/
/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuModeSettingConf_0   ((Mcu_ModeType)0U)
/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuConf_McuModeSettingConf_McuModeSettingConf_0   ((Mcu_ModeType)0U)


/**
* @brief            Create defines with the IDs assigned to Mcu RAM Section configurations.
*                   These IDs will be transmitted as input parameters for Mcu_InitRamSection() API.
*/

/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuRamSectorSettingConf_0   ((Mcu_RamSectionType)0U)
/** @violates @ref Mcu_CFG_H_REF_4 MISRA 2004 Required Rule 1.4 */
#define McuConf_McuRamSectorSettingConf_McuRamSectorSettingConf_0   ((Mcu_RamSectionType)0U)




/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/**
* @brief            Type of the return value of the function Mcu_GetPllStatus.
* @details          The type of Mcu_PllStatusType is an enumeration with the following values:
*                       MCU_PLL_LOCKED, MCU_PLL_UNLOCKED, MCU_PLL_STATUS_UNDEFINED.
*
* @implements     Mcu_PllStatusType_enumeration
*
*/
typedef enum
{
    MCU_PLL_LOCKED = 0x33U,   /**< @brief PLL is locked. */
    MCU_PLL_UNLOCKED = 0xCCU,   /**< @brief PLL is unlocked. */
    MCU_PLL_STATUS_UNDEFINED = 0x5AU   /**< @brief PLL Status is unknown. */

} Mcu_PllStatusType;


/**
* @brief            The type Mcu_ResetType, represents the different reset that a specified MCU can have.
* @details          The MCU module shall provide at least the values MCU_POWER_ON_RESET and MCU_RESET_UNDEFINED for the enumeration Mcu_ResetType.
*
* @implements Mcu_ResetType_enumeration
*/
typedef enum
{
    /* 'Destructive' Event Status Register (MC_RGM_DES) */
    MCU_POWER_ON_RESET=0x00U,   /**< @brief Power on event. RGM_DES[F_POR]. */
    MCU_SOFT_DEST_RESET,        /**< @brief Software destructive reset. RGM_DES[F_SOFT_DESC]. */
    MCU_FFRR_RESET,             /**< @brief FCCU failure to react reset. RGM_DES[F_FFRR]. */
    MCU_SUF_RESET,              /**< @brief Functional reset escalation. RGM_DES[F_SUF]. */
    MCU_EDR_RESET,              /**< @brief Functional reset escalation. RGM_DES[F_EDR]. */
    MCU_FIF_RESET,              /**< @brief Functional reset escalation. RGM_DES[F_FIF]. */
    MCU_TSR_DEST_RESET,         /**< @brief Temperature sensor destructive reset. RGM_DES[F_TSR_DEST]. */
    MCU_VOR_DEST_RESET,         /**< @brief Voltage out of range destructive reset. RGM_DES[F_VOR_DEST]. */
    /* 'Functional' Event Status Register (MC_RGM_FES) */
    MCU_EXR_RESET,              /**< @brief External reset event. RGM_FES[F_EXR]. */
    MCU_ST_DONE_RESET,          /**< @brief Self-test completed event. RGM_FES[F_ST_DONE]. */
    MCU_SOFT_FUNC_RESET,        /**< @brief Software destrutive event. RGM_FES[F_SOFT_FUNC]. */
    MCU_FCCU_HARD_RESET,        /**< @brief FCCU hard reaction request event. RGM_FES[F_FCCU_HARD]. */
    MCU_FCCU_SOFT_RESET,        /**< @brief FCCU soft reaction request event. RGM_FES[F_FCCU_SOFT]. */
    MCU_JTAG_RESET,             /**< @brief JTAG initiated reset event. RGM_FES[F_JTAG]. */
    MCU_TSR_FUNC_RESET,         /**< @brief Temperature sensor functional reset. RGM_FES[F_TSR_FUNC]. */
    MCU_VOR_FUNC_RESET,         /**< @brief Voltage out of range functional reset. RGM_FES[F_VOR_FUNC]. */

    MCU_RESET_UNDEFINED         /**< @brief Undefined reset source. */

} Mcu_ResetType;

#if (MCU_GET_RAM_STATE_API == STD_ON)
/**
* @brief            Ram State of the microcontroller.
* @details          This is the Ram State data type returned by the function Mcu_GetRamState() of the Mcu module.
*/
typedef enum
{
    MCU_RAMSTATE_INVALID = 0U,   /**< @brief RAM content is not valid or unknown (default). */
    MCU_RAMSTATE_VALID   /**< @brief RAM content is valid. */

} Mcu_RamStateType;
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     EXTERN SECTION
==================================================================================================*/
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Mcu_CFG_H_REF_5 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' MemMap.h*/
/** @violates @ref Mcu_CFG_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "MemMap.h"
/**
* @brief            Local copy of the pointer to the configuration data
*/
extern P2CONST(Mcu_DemConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_pDemCfgPtr;

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Mcu_CFG_H_REF_5 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include' MemMap.h*/
/** @violates @ref Mcu_CFG_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "MemMap.h"
#endif








#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_CFG_H */

/** @} */
