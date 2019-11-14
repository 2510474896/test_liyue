/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Mcu_Cfg.c $
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
*   @file    Mcu_Cfg.c
*   @implements Mcu_Cfg.c_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Data structures for the Mcu driver.
*   @details Precompile structure configuration for the driver initalization.
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


#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_Cfg_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a violation
* since all header files are protected against multiple inclusions
*
* @section Mcu_Cfg_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_Cfg_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_Cfg_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between
* a pointer to a function and any type other than an integral type.
* Appears when accessing memory-mapped registers.
*
* @section Mcu_Cfg_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, A cast should not be performed
* between a pointer to object type and a different pointer to object type.
*
* @section Mcu_Cfg_c_REF_6
* Violates MISRA 2004 Required Rule 20.2, The names of standard macros, objects and
* functions shall not be reused
*
* @section Mcu_Cfg_c_REF_7
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is requiered.
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
#include "Mcu.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

#define MCU_CFG_VENDOR_ID_C                     43
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION_C      4
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_MINOR_VERSION_C      0
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_CFG_SW_MAJOR_VERSION_C              1
#define MCU_CFG_SW_MINOR_VERSION_C              0
#define MCU_CFG_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The MCU module's implementer shall avoid the integration of incompatible files.
*/
/* Check if current file and MCU header file are of the same vendor */
#if (MCU_CFG_VENDOR_ID_C != MCU_VENDOR_ID)
    #error "Mcu_Cfg.c and Mcu.h have different vendor ids"
#endif

/* Check if current file and MCU header file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != MCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION_C != MCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif

/* Check if current file and MCU header file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif

/* Check if current file and DEM header file are of the same version */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Cfg.c and Dem.h are different"
    #endif
#endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Mcu_Cfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Cfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/





#if (MCU_PRECOMPILE_SUPPORT == STD_ON)







#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
STATIC CONST( Mcu_DemConfigType, MCU_CONST) Mcu_Dem_ConfigPC0 =
{

    /* DEM error reporting MCU_E_TIMEOUT_FAILURE */
    {(uint32)STD_ON, DemConf_DemEventParameter_MCU_E_TIMEOUT_FAILURE},

    /* DEM error reporting MCU_E_INVALIDMODE_CONFIG */
    {(uint32)STD_ON, DemConf_DemEventParameter_MCU_E_INVALIDMODE_CONFIG},

    /* DEM error reporting MCU_E_SSCM_CER_FAILURE */
    {(uint32)STD_ON, DemConf_DemEventParameter_MCU_E_SSCM_CER_FAILURE}

};
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */





/**
* @brief        Definition of RAM sections within the configuration structure.
* @details      Blocks of memory are initialized with a default data.
*               Configuration set by calling Mcu_InitClock() API.
*
*/
STATIC CONST(Mcu_RamConfigType, MCU_CONST) Mcu_Ram_ConfigPC0[1] =
{

    {
        /* The ID for Ram Sector configuration. */
        (uint8)0U,

        /* RAM section base address: Start of Mcu_RamConfig[0]. */
        /** @violates @ref Mcu_Cfg_c_REF_4 MISRA 2004 Required Rule 11.1, conversion from pointer to integer */
        /** @violates @ref Mcu_Cfg_c_REF_5 MISRA 2004 Advisory Rule 11.4, cast between pointer and object */
        (uint8*)0x40000000U,

        /* RAM section size: Section base address (must be aligned to 4 bytes). */
        (uint32)0x00000400U,

        /* RAM default value: Section size in bytes (must be multiple of 4). */
        (uint8)0xbaU
    } /* End of Mcu_Ram_ConfigPC[0]. */
                
};




/**
* @brief        Definition of MCU mode sections in the configuration structure.
* @details      Specifies the system behaviour during the selected target mode.
*               Configuration set by calling Mcu_SetMode() API.
*/
STATIC CONST( Mcu_MC_ME_ModeConfigType, MCU_CONST) Mcu_Mode_ConfigPC0[1] =
{

    /* Start of Mcu_ModeConfig[0] - HALT0 */
    {
        /* The ID for Power Mode configuration. */
        (uint8)0U,

        /* The selected magic target mode. Configure the ME_MCTL[TARGET_MODE] register filed. */
        (MCU_HALT0_MODE),

        /* Specifies the system behaviour for this configured state. */
        (
            /* Configure the MC_<mode>_MC[PDO] register field. */
            (MC_ME_OUT_POWER_CONTROL_DIS_U32) |

            /* Configure the MC_<mode>_MC[MVRON] register field. */
            (MC_ME_MAIN_VOLTAGE_REG_EN_U32) | 

            /* Configure the MC_<mode>_MC[CFLAON] register field. */
            (MC_ME_CODE_FLASH_NORMAL_POWER_U32) |

            /* Configure the MC_<mode>_MC[PLL1ON] register field. */
            (MC_ME_FMPLL1_DIS_U32) | 

            /* Configure the MC_<mode>_MC[PLL0ON] register field. */
            (MC_ME_FMPLL0_DIS_U32) | 

            /* Configure the MC_<mode>_MC[XOSCON] register field. */
            (MC_ME_XOSC_DIS_U32) | 

            /* Configure the MC_<mode>_MC[IRCOSCON] register field. */
            (MC_ME_IRCOSC_EN_U32) | 

            /* Configure the MC_<mode>_MC[SYSCLK] register field. */
            (MC_ME_SYSCLK_IRCOSC_U32) |

            /* configure the MC_<mode>_MC[PWRLVL] register field. */
            MC_ME_POWER_LEVEL_U32( (uint32)0U )
        ),
#if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
        /* Fast transition supported (from Low Power to Run mode). */
        (boolean)FALSE,

        /* Specifies the system behaviour for this RUN state that will be after wakeup (exit from low power mode - STOP0/HALT0). */
        (MC_ME_FAST_MODE_CONFIG_DEFAULT_U32),
#endif /* (MCU_ENTER_LOW_POWER_MODE == STD_ON) */
#if (MCU_CONFIGURE_CADDRN == STD_ON)
        /* MC_ME_CADDR0 */
        MC_ME_CADDR_UNUSED_MASK32,
        /* MC_ME_CADDR1 */
        MC_ME_CADDR_UNUSED_MASK32,
        /* MC_ME_CADDR2 */
        MC_ME_CADDR_UNUSED_MASK32,
        /* MC_ME_CADDR3 */
        MC_ME_CADDR_UNUSED_MASK32,
        /* MC_ME_CADDR4 */
        MC_ME_CADDR_UNUSED_MASK32
#endif /* MCU_CONFIGURE_CADDRN == STD_ON */
    }/* end of Mcu_Mode_ConfigPC0[0]. */

};




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Timing configuration for FLASH hw IP.
* @details      Set the Pipeline/Write/Read wait states for FLASH controller.
*               Configuration set by calling Mcu_InitClock API.
*/
STATIC CONST( Mcu_FLASH_ClockConfigType, MCU_CONST) FLASH_Clock_ConfigPC0_0 =
{
    /* Flash Controller timing settings.
       PFCR1 configuration register: Address Pipelining Control & Read Wait State Control. */
    (
        MCU_FLASH_ADDR_PIPELINE_WS_U32(2) |
        MCU_FLASH_READ_WS_U32(5)
    )
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
STATIC CONST( Mcu_MC_CGM_RegisterConfigType, MCU_CONST) MC_CGM_PcsClock_ConfigPC0_0[MCU_CGM_NUMBER_OF_PCS_REGS] =
{

    /* PCS Divider Change Register 1. */
    {
        MC_CGM_PCS_DIVC1_ADDR32,
        MC_CGM_PCS_DIVC_U32
        (
            MC_CGM_PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            MC_CGM_PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 1. */
    {
        MC_CGM_PCS_DIVS1_ADDR32,
        MC_CGM_PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 1. */
    {
        MC_CGM_PCS_DIVE1_ADDR32,
        MC_CGM_PCS_DIVE_U32((uint32)0x000003e7U)
    },

    /* PCS Divider Change Register 2. */
    {
        MC_CGM_PCS_DIVC2_ADDR32,
        MC_CGM_PCS_DIVC_U32
        (
            MC_CGM_PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            MC_CGM_PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 2. */
    {
        MC_CGM_PCS_DIVS2_ADDR32,
        MC_CGM_PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 2. */
    {
        MC_CGM_PCS_DIVE2_ADDR32,
        MC_CGM_PCS_DIVE_U32((uint32)0x000003e7U)
    },

    /* PCS Divider Change Register 4. */
    {
        MC_CGM_PCS_DIVC4_ADDR32,
        MC_CGM_PCS_DIVC_U32
        (
            MC_CGM_PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            MC_CGM_PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 4. */
    {
        MC_CGM_PCS_DIVS4_ADDR32,
        MC_CGM_PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 4. */
    {
        MC_CGM_PCS_DIVE4_ADDR32,
        MC_CGM_PCS_DIVE_U32((uint32)0x000003e7U)
    }

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
STATIC CONST( Mcu_MC_CGM_RegisterConfigType, MCU_CONST) MC_CGM_SystemClock_ConfigPC0_0[MCU_CGM_NUMBER_OF_SYSTEM_CLOCK_REGS] =
{
    /* System Clock Divider 0 Configuration. */
    {
        MC_CGM_SC_DC0_ADDR32,
        MC_CGM_SYSCLK_DC0_DIVISOR_U32(4U)
    }
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
STATIC CONST( Mcu_MC_CGM_RegisterConfigType, MCU_CONST) MC_CGM_AuxClock_ConfigPC0_0[17] =
{

    
    /* Auxiliary Clock0 Source Selection. CGM_AC0_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC0_SC_ADDR32,
        MC_CGM_AUXCLK0_U32(MC_CGM_AUXCLK0_SOURCE_PLL0_U32)
    }

    ,
    /* Auxiliary Clock0 Divider0 Configuration. CGM_AC0_DC0 Register. */
    {
        MC_CGM_AC0_DC0_ADDR32,
        MC_CGM_AC0_DC0_U32
        (
            MC_CGM_AUXCLK0_DIV0_EN_U32 | 
            MC_CGM_AUXCLK0_DIV0_U32(1U)
        )
    }

    ,
    /* Auxiliary Clock0 Divider1 Configuration. CGM_AC0_DC1 Register. */
    {
        MC_CGM_AC0_DC1_ADDR32,
        MC_CGM_AC0_DC1_U32
        (
            MC_CGM_AUXCLK0_DIV1_EN_U32 | 
            MC_CGM_AUXCLK0_DIV1_U32(8U)
        )
    }

    ,
    /* Auxiliary Clock0 Divider2 Configuration. CGM_AC0_DC2 Register. */
    {
        MC_CGM_AC0_DC2_ADDR32,
        MC_CGM_AC0_DC2_U32
        (
            MC_CGM_AUXCLK0_DIV2_EN_U32 | 
            MC_CGM_AUXCLK0_DIV2_U32(2U)
        )
    }

    ,
    /* Auxiliary Clock1 Divider0 Configuration. CGM_AC1_DC0 Register. */
    {
        MC_CGM_AC1_DC0_ADDR32,
        MC_CGM_AC1_DC0_U32
        (
            MC_CGM_AUXCLK1_DIV0_EN_U32 | 
            MC_CGM_AUXCLK1_DIV0_U32(2U)
        )
    }

    ,
    /* Auxiliary Clock1 Divider1 Configuration. CGM_AC1_DC1 Register. */
    {
        MC_CGM_AC1_DC1_ADDR32,
        MC_CGM_AC1_DC1_U32
        (
            MC_CGM_AUXCLK1_DIV1_EN_U32 | 
            MC_CGM_AUXCLK1_DIV1_U32(4U)
        )
    }

    ,
    /* Auxiliary Clock2 Divider0 Configuration. CGM_AC2_DC0 Register. */
    {
        MC_CGM_AC2_DC0_ADDR32,
        MC_CGM_AC2_DC0_U32
        (
            MC_CGM_AUXCLK2_DIV0_EN_U32 | 
            MC_CGM_AUXCLK2_DIV0_U32(8U)
        )
    }

    ,
    /* Auxiliary Clock3 Source Selection. CGM_AC3_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC3_SC_ADDR32,
        MC_CGM_AUXCLK3_U32(MC_CGM_AUXCLK3_SOURCE_XTAL_U32)
    }

    ,
    /* Auxiliary Clock4 Source Selection. CGM_AC4_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC4_SC_ADDR32,
        MC_CGM_AUXCLK4_U32(MC_CGM_AUXCLK4_SOURCE_XTAL_U32)
    }

    ,
    /* Auxiliary Clock5 Source Selection. CGM_AC5_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC5_SC_ADDR32,
        MC_CGM_AUXCLK5_U32(MC_CGM_AUXCLK5_SOURCE_XTAL_U32)
    }

    ,
    /* Auxiliary Clock5 Divider0 Configuration. CGM_AC5_DC0 Register. */
    {
        MC_CGM_AC5_DC0_ADDR32,
        MC_CGM_AC5_DC0_U32
        (
            MC_CGM_AUXCLK5_DIV0_EN_U32 | 
            MC_CGM_AUXCLK5_DIV0_U32(1U)
        )
    }

    ,
    /* Auxiliary Clock6 Source Selection. CGM_AC6_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC6_SC_ADDR32,
        MC_CGM_AUXCLK6_U32(MC_CGM_AUXCLK6_SOURCE_PLL1_U32)
    }

    ,
    /* Auxiliary Clock6 Divider0 Configuration. CGM_AC6_DC0 Register. */
    {
        MC_CGM_AC6_DC0_ADDR32,
        MC_CGM_AC6_DC0_U32
        (
            MC_CGM_AUXCLK6_DIV0_EN_U32 | 
            MC_CGM_AUXCLK6_DIV0_U32(20U)
        )
    }

    ,
    /* Auxiliary Clock10 Source Selection. CGM_AC10_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC10_SC_ADDR32,
        MC_CGM_AUXCLK10_U32(MC_CGM_AUXCLK10_SOURCE_IRC_U32)
    }

    ,
    /* Auxiliary Clock10 Divider0 Configuration. CGM_AC10_DC0 Register. */
    {
        MC_CGM_AC10_DC0_ADDR32,
        MC_CGM_AC10_DC0_U32
        (
            MC_CGM_AUXCLK10_DIV0_DIS_U32 | 
            MC_CGM_AUXCLK10_DIV0_U32(1U)
        )
    }

    ,
    /* Auxiliary Clock11 Source Selection. CGM_AC11_SC[SELCTL] Field Register. */
    {
        MC_CGM_AC11_SC_ADDR32,
        MC_CGM_AUXCLK11_U32(MC_CGM_AUXCLK11_SOURCE_IRC_U32)
    }

    ,
    /* Auxiliary Clock11 Divider0 Configuration. CGM_AC11_DC0 Register. */
    {
        MC_CGM_AC11_DC0_ADDR32,
        MC_CGM_AC11_DC0_U32
        (
            MC_CGM_AUXCLK11_DIV0_DIS_U32 | 
            MC_CGM_AUXCLK11_DIV0_U32(1U)
        )
    }

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            MC_CGM IP clock configuration.
* @details          This structure contains information for IRCOSC, XOSC, PLL, Output Clocks, CMUs
*
*/
STATIC CONST( Mcu_MC_CGM_ClockConfigType, MCU_CONST) MC_CGM_Clock_ConfigPC0_0 =
{
    /* These clock sources must be powered on for the current clock setting */
    (
        MC_ME_XOSC_EN_U32   |
        MC_ME_FMPLL0_EN_U32 |
        MC_ME_FMPLL1_EN_U32  
    ),

    /* Progressive Clock Switching (CGM_PCS_SDUR[SDUR]) */
    MC_CGM_PCS_SDUR_U8(0x00U),

    /* number of pcs registers unde mcu control */
    MCU_CGM_NUMBER_OF_PCS_REGS,

    /* pcs registers */
    &MC_CGM_PcsClock_ConfigPC0_0,

    /* number of sys clock regs unde mcu control */
    MCU_CGM_NUMBER_OF_SYSTEM_CLOCK_REGS,

    /* system clock configuration */
    &MC_CGM_SystemClock_ConfigPC0_0,

    /* number of configurable aux clock regs */
    ((uint8)17U),

    /* auxiliary clock dividers */
     &MC_CGM_AuxClock_ConfigPC0_0
    

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            PLLDIG Registers configuration.
* @details          This structure contains configuration for PLLDIG Registers.
*
*/
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Required Rule 1.4, 31 characters limit.*/
STATIC CONST( Mcu_PLLDIG_RegisterConfigType, MCU_CONST) Mcu_PLLDIG_Registers_Config_PC0_0[MCU_CGM_NUMBER_OF_PLL_REGS] =
{
    
    /* PLL0 configuration */
    {
        PLLDIG_PLL0CR_ADDR32,
        MCU_PLLDIG_PLL0CR_U32
        (
            MCU_PLLDIG_PLL0CR_LOLIE_DIS_U32 |
            MCU_PLLDIG_PLL0CR_LOCIE_DIS_U32
        )
    },
    /* PLL0 dividers */
    {
        PLLDIG_PLL0DV_ADDR32,
        MCU_PLLDIG_PLL0DV_U32
        (
            MCU_PLLDIG_PLL0DV_RFDPHI1_U32( (uint32)15U ) |
            MCU_PLLDIG_PLL0DV_RFDPHI_U32( (uint32)4U ) |
            MCU_PLLDIG_PLL0DV_PREDIV_U32( (uint32)1U ) |
            MCU_PLLDIG_PLL0DV_MFD_U32( (uint32)10U )
        )
    },
    /* PLL1 configuration */
    {
        PLLDIG_PLL1CR_ADDR32,
        MCU_PLLDIG_PLL1CR_U32
        (
            MCU_PLLDIG_PLL1CR_LOLIE_DIS_U32 |
            MCU_PLLDIG_PLL1CR_LOCIE_DIS_U32
        )
    },
    /* PLL1 dividers */
    {
        PLLDIG_PLL1DV_ADDR32,
        MCU_PLLDIG_PLL1DV_U32
        (
            MCU_PLLDIG_PLL1DV_RFDPHI_U32( (uint32)2U ) |
            MCU_PLLDIG_PLL1DV_MFD_U32( (uint32)20U )
        )
    },
    /* PLL1 frequency modulation */
    {
        PLLDIG_PLL1FM_ADDR32,
        MCU_PLLDIG_PLL1FM_U32( MCU_PLLDIG_PLL1FM_MODEN_DIS_U32 )
    },
    /* PLL1 fractional divider */
    {
        PLLDIG_PLL1FD_ADDR32,
        MCU_PLLDIG_PLL1FD_U32( MCU_PLLDIG_PLL1FD_FDEN_DIS_U32 )
    }
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            PLLDIG clock configuration.
* @details          This structure contains information for PLLDIG PLL0 and FMPLL1.
*
*/
STATIC CONST( Mcu_PLLDIG_ConfigType, MCU_CONST) MC_PLLDIG_pClockConfigPC0_0 =
{
    /* number of pll regs under mcu control */
    0x06U,
    /* configuration for PLLDIG registers */
    &Mcu_PLLDIG_Registers_Config_PC0_0
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            CMU configuration.
* @details          This structure contains information for CMU[n].
*                   The number of CMU's is defined in the resource files,
*
*/
STATIC CONST( Mcu_CMU_ConfigType, MCU_CONST) CMU_ConfigPC0_0 =
{
    {

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
        ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
        ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
        ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
        ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
        )

    },
    {

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        )

    },
    {

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        )

    }
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */







#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Timing configuration for SRAMC hw IP.
* @details      Set the Read wait states for RAM.
*               Configuration set by calling Mcu_InitClock API.
*/
STATIC CONST( Mcu_PRAM_ClockConfigType, MCU_CONST) SRAMC_pClockConfigPC0_0 =
{
    /* SRAMC Controller timing settings. PRCR1 configuration register. */
    PRAMC_PRCR1_VALUE_U32
    (
        PRAMC_PRCR1_PRI_VALUE_U32( (uint32)2U ) |
        PRAMC_PRCR1_P1_BO_ENA_U32 |
        PRAMC_PRCR1_P0_BO_ENA_U32 |
        PRAMC_PRCR1_FT_ENA_U32
    )
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief          Initialization clock data.
* @details        Static configuration realized by calling Mcu_InitClock() API.
*
*/
STATIC CONST( Mcu_ClockConfigType, MCU_CONST) Mcu_Clock_ConfigPC0[1] =
{
    
    /* Start of Mcu_ClockConfig[0]. */
    {
            
        /* ID Clock Configuration. */
        (uint8)0U,

        /* Globally enable/disable SCM, loss of clock and loss of lock notification. */
        (MCU_CLK_NOTIF_DIS),

        /* System Clock Selection.
           This affect the Mode settings from MC_ME IP. */
        (MC_ME_SYSCLK_PLL1_U32 | MC_ME_FMPLL1_EN_U32 ),

        /* MC_CGM IP Clock settings. */
        &MC_CGM_Clock_ConfigPC0_0,

        /* XOSC IP Clock settings. */
        (NULL_PTR),

        /* PLLDIG IP Clock settings. */
        &MC_PLLDIG_pClockConfigPC0_0,

        /* CMU IP Clock settings. */
        &CMU_ConfigPC0_0,

#if (MCU_SRAMC_SUPPORT == STD_ON)
        /* SRAMC IP Clock settings. */
        &SRAMC_pClockConfigPC0_0,
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */

        /* FLASH IP Clock settings. */
        &FLASH_Clock_ConfigPC0_0,

        (MCU_IPW_IRC_NOT_UNDER_MCU_CONTROL |
         MCU_IPW_XOSC_NOT_UNDER_MCU_CONTROL |
         MCU_IPW_PLL0_UNDER_MCU_CONTROL |
         MCU_IPW_PLL1_UNDER_MCU_CONTROL)

    } /* end of Mcu_ClockConfig[0] */
            
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
        



/**
* @brief          Initialization data for MC_RGM hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
STATIC CONST( Mcu_MC_RGM_ConfigType, MCU_CONST) MC_RGM_ConfigPC0 =
{
#if (MCU_PERFORM_RESET_API == STD_ON)
    /* MC_ResetType: Functional vs Destructive. */
    (MCU_FUNC_RESET),
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */
    /* destructive reset config */
    /* MCRGM_Dest_ResetOpt: RGM_DERD Register Configuration. */
    MC_RGM_DEST_U32
    (
        ((uint32)0x00000000U) /* not option available */
    ),

    /* MCRGM_Dest_SafeIsrOpt: RGM_DEAR Register Configuration. */
    ((uint32)0x00000000U),

    /* MCRGM_Dest_ExtPinReset: RGM_DBRE Register Configuration. */
    MC_RGM_DBRE_U32
    (
        ((uint32)0x00000000U)
    ),

    /* functional reset config */
    /* Func_ResetOpt: FERD Register Configuration. */
    MC_RGM_FERD_U32
    (
        (MC_RGM_VOR_FUNC_EVENT_RESET_U32) |
        (MC_RGM_TSR_FUNC_EVENT_RESET_U32) |
        (MC_RGM_JTAG_FUNC_EVENT_RESET_U32)
    ),

    /* MCRGM_Func_SafeIsrOpt: RGM_FEAR Register Configuration. */
    MC_RGM_FEAR_U32
    (
        (MC_RGM_VOR_FUNC_EVENT_SAFE_U32) |
        (MC_RGM_TSR_FUNC_EVENT_SAFE_U32) |
        (MC_RGM_JTAG_FUNC_EVENT_SAFE_U32)
    ),

    /* MCRGM_Func_ExtPinReset: RGM_FBRE Register Configuration. */
    MC_RGM_FBRE_U32
    (
        (MC_RGM_VOR_FUNC_EXT_RESET_B_DIS_U32) |
        (MC_RGM_TSR_FUNC_EXT_RESET_B_DIS_U32) |
        (MC_RGM_JTAG_EXT_RESET_B_DIS_U32) |
        (MC_RGM_FCCU_SOFT_EXT_RESET_B_DIS_U32) |
        (MC_RGM_FCCU_HARD_EXT_RESET_B_EN_U32) |
        (MC_RGM_SOFT_FUNC_EXT_RESET_B_DIS_U32)
    ),

    /* MCRGM_Func_Phase1or3Opt: RGM_FESS Register Configuration. */
    MC_RGM_FESS_U32
    (
        (MC_RGM_VOR_FUNC_RESET_PHASE3_U32) |
        (MC_RGM_TSR_FUNC_RESET_PHASE3_U32) |
        (MC_RGM_JTAG_FUNC_RESET_PHASE3_U32) |
        (MC_RGM_SOFT_FUNC_RESET_PHASE3_U32) |
        (MC_RGM_EXR_RESET_PHASE3_U32)
    ),

    /* MCRGM_Threshold_Reset: RGM_FRET Register Configuration. */
    MC_RGM_FRET_U8((uint8)0U),

    /* MCRGM_Threshold_Reset: RGM_DRET Register Configuration. */
    MC_RGM_DRET_U8((uint8)0U)
};




STATIC CONST( Mcu_MC_ME_RegisterConfigType, MCU_CONST) MC_ME_PCTL_ConfigPC0_0[MCU_MC_ME_NUMBER_OF_PCTL_REGS] =
{

    /* PCTL9_LFAST_0 */
    {
        MC_ME_PCTL9_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL11_SIPI_0 */
    {
        MC_ME_PCTL11_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL12_ENET_0 */
    {
        MC_ME_PCTL12_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL30_PIT_0 */
    {
        MC_ME_PCTL30_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL36_DMAMUX_0 */
    {
        MC_ME_PCTL36_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL38_CRC_0 */
    {
        MC_ME_PCTL38_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL77_CAN_2 */
    {
        MC_ME_PCTL77_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL78_CAN_1 */
    {
        MC_ME_PCTL78_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL79_CAN_0 */
    {
        MC_ME_PCTL79_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL91_LINFLEX_1 */
    {
        MC_ME_PCTL91_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL98_DSPI_1 */
    {
        MC_ME_PCTL98_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL99_DSPI_0 */
    {
        MC_ME_PCTL99_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL104_SENT_0 */
    {
        MC_ME_PCTL104_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL107_FLEXRAY */
    {
        MC_ME_PCTL107_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL124_ADC_3 */
    {
        MC_ME_PCTL124_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL126_ADC_1 */
    {
        MC_ME_PCTL126_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL137_ETIMER_1 */
    {
        MC_ME_PCTL137_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL141_CTU_1 */
    {
        MC_ME_PCTL141_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL144_PWM_1 */
    {
        MC_ME_PCTL144_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL146_DMAMUX_1 */
    {
        MC_ME_PCTL146_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL204_LINFLEX_0 */
    {
        MC_ME_PCTL204_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL208_DSPI_3 */
    {
        MC_ME_PCTL208_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL209_DSPI_2 */
    {
        MC_ME_PCTL209_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL214_SENT_1 */
    {
        MC_ME_PCTL214_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL235_ADC_2 */
    {
        MC_ME_PCTL235_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL237_ADC_0 */
    {
        MC_ME_PCTL237_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL239_SGEN_0 */
    {
        MC_ME_PCTL239_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL245_ETIMER_2 */
    {
        MC_ME_PCTL245_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL247_ETIMER_0 */
    {
        MC_ME_PCTL247_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL251_CTU_0 */
    {
        MC_ME_PCTL251_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    },

    /* PCTL255_PWM_0 */
    {
        MC_ME_PCTL255_ADDR32,
        MC_ME_PCTLn_U8(MC_ME_CFG_RUN_PC0_U8, MC_ME_CFG_LP_PC0_U8)
    }

};

/**
* @brief            Configuration of MC_ME hw IP.
* @details          This data configuration is set at module initialization phase.
*
*/
STATIC CONST( Mcu_MC_ME_ConfigType, MCU_CONST) MC_ME_ConfigPC0 =
{

    /* ME_RUN_PC0: Run Config Mode0 : McuRunConfig_0. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC1: Run Config Mode1 : McuRunConfig_1. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC2: Run Config Mode2 : McuRunConfig_2. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC3: Run Config Mode3 : McuRunConfig_3. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC4: Run Config Mode4 : McuRunConfig_4. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC5: Run Config Mode5 : McuRunConfig_5. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC6: Run Config Mode6 : McuRunConfig_6. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_RUN_PC7: Run Config Mode7 : McuRunConfig_7. */
    (
        (MC_ME_RUN3_CLK_ACTIVE_U32) |
        (MC_ME_RUN2_CLK_ACTIVE_U32) |
        (MC_ME_RUN1_CLK_ACTIVE_U32) |
        (MC_ME_RUN0_CLK_ACTIVE_U32) |
        (MC_ME_DRUN_CLK_ACTIVE_U32) |
        (MC_ME_SAFE_CLK_ACTIVE_U32) |
        (MC_ME_TEST_CLK_GATED_U32)
    ),

    /* ME_LP_PC0: Low Power Mode 0. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC1: Low Power Mode 1. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC2: Low Power Mode 2. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC3: Low Power Mode 3. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC4: Low Power Mode 4. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC5: Low Power Mode 5. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC6: Low Power Mode 6. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    /* ME_LP_PC7: Low Power Mode 7. */
    (
        (MC_ME_STOP0_CLK_GATED_U32) |
        (MC_ME_HALT0_CLK_GATED_U32)
    ),

    MCU_MC_ME_NUMBER_OF_PCTL_REGS,
    &MC_ME_PCTL_ConfigPC0_0,

    /* Modes Enabled according to ME_ME details. RUN0/DRUN/SAFE/RESET/RESET_DEST are always ON. Configuration of ME_ME register. */
    MC_ME_ME_ENABLE
    (
        (MC_ME_STOP0_MODE_EN_U32) |
        (MC_ME_HALT0_MODE_EN_U32) |
        (MC_ME_RUN3_MODE_EN_U32) |
        (MC_ME_RUN2_MODE_EN_U32) |
        (MC_ME_RUN1_MODE_EN_U32) |
        (MC_ME_TEST_MODE_DIS_U32)
    ),

    /* Enable Mode Transition Interrupts: Configure the ME_IM Register. */
    MC_ME_INT_ENABLE
    (
        (MC_ME_TRANSITION_MODE_INT_DIS_U32) |
        (MC_ME_SAFE_MODE_INT_DIS_U32) |
        (MC_ME_INVALID_MODE_INT_DIS_U32) |
        (MC_ME_INVALID_MODE_CFG_INT_DIS_U32) |
        (MC_ME_INVALID_MODE_CLK_INT_DIS_U32) |
        (MC_ME_INVALID_MODE_CPU_INT_DIS_U32)
    ),

    /* Core Control Register (ME_CCTL0) */
    MC_ME_CCTL_UNUSED_MASK16,

    /* Core Control Register (ME_CCTL1) */
    MC_ME_CCTL_UNUSED_MASK16,

    /* Core Control Register (ME_CCTL2) */
    MC_ME_CCTL_UNUSED_MASK16,

    /* Core Control Register (ME_CCTL3) */
    MC_ME_CCTL_UNUSED_MASK16,

    /* Core Control Register (ME_CCTL4) */
    MC_ME_CCTL_UNUSED_MASK16
};




/**
* @brief            Platform FLASH hw IP configuration.
* @details          Configure prefetch mechanism, buffers, access protection.
*                   Configuration set by calling Mcu_Init API.
*/
STATIC CONST( Mcu_FLASH_ConfigType, MCU_CONST) FLASH_ConfigPC0 =
{
    /* Platform Flash Configuration Register 1 (PFCR1). */
    MCU_FLASH_PFCR1_U32
    (
        MCU_FLASH_P0_MASTER15_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER14_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER13_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER12_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER11_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER10_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER9_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER8_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER7_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER6_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER5_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER4_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER3_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER2_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER1_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER0_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_DATA_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_INSTR_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_PFLIM_U32( (uint32)0U ) |
        MCU_FLASH_P0_BUFFER_EN_U32
    ),

    /* Platform Flash Configuration Register 3 (PFCR3). */
    MCU_FLASH_PFCR3_U32
    (
        MCU_FLASH_P0_WCFG_U32( (uint32)0U )
    ),

    /* Platform Flash Access Protection Register (PFAPR). */
    MCU_FLASH_PFAPR_U32
    (
        MCU_FLASH_M0AP_U32( (uint32)3U ) |
        MCU_FLASH_M1AP_U32( (uint32)3U ) |
        MCU_FLASH_M2AP_U32( (uint32)3U ) |
        MCU_FLASH_M3AP_U32( (uint32)3U ) |
        MCU_FLASH_M4AP_U32( (uint32)3U ) |
        MCU_FLASH_M5AP_U32( (uint32)3U ) |
        MCU_FLASH_M6AP_U32( (uint32)3U ) |
        MCU_FLASH_M7AP_U32( (uint32)3U ) |
        MCU_FLASH_M8AP_U32( (uint32)3U ) |
        MCU_FLASH_M9AP_U32( (uint32)3U ) |
        MCU_FLASH_M10AP_U32( (uint32)3U ) |
        MCU_FLASH_M11AP_U32( (uint32)3U ) |
        MCU_FLASH_M12AP_U32( (uint32)3U ) |
        MCU_FLASH_M13AP_U32( (uint32)3U ) |
        MCU_FLASH_M14AP_U32( (uint32)3U ) |
        MCU_FLASH_M15AP_U32( (uint32)3U )
    )
};
        



/**
* @brief          Initialization data for MC_PCU/PMU hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
STATIC CONST( Mcu_MC_PCU_ConfigType, MCU_CONST) MC_PCU_ConfigPC0 =
{
    /* Low/high voltage detection enable register. PMCCR register. */
    PMC_PMCCR_CONFIG_U32
    (
        PMC_PMCCR_INT_AUX_REG_BYPASS_U32 |
        PMC_PMCCR_INT_REG_ACTIVE_U32
    ),

    /* Reset event interrupt enable register. PMC_IER register. */
    PMC_IER_CONFIG_U32
    (
        PMC_IER_TS1_3IE_DIS_U32 |
        PMC_IER_TS1_2IE_DIS_U32 |
        PMC_IER_TS1_0IE_DIS_U32 |
        PMC_IER_TS0_3IE_DIS_U32 |
        PMC_IER_TS0_2IE_DIS_U32 |
        PMC_IER_TS0_0IE_DIS_U32 |
        PMC_IER_VD6IE_O_DIS_U32 |
        PMC_IER_VD6IE_ADC_DIS_U32 |
        PMC_IER_VD6IE_IM_DIS_U32 |
        PMC_IER_VD6IE_F_DIS_U32 |
        PMC_IER_VD6IE_C_DIS_U32 |
        PMC_IER_VD4IE_C_DIS_U32 |
        PMC_IER_VD3IE_H_DIS_U32 |
        PMC_IER_VD3IE_C_DIS_U32
    ),

    /* Reset event enable register. PMC_REE_0 register. */
    PMC_REE_0_CONFIG_U32
    (
        PMC_REE_0_VD6RE_O_DIS_U32 |
        PMC_REE_0_VD6RE_ADC_DIS_U32 |
        PMC_REE_0_VD6RE_IM_DIS_U32 |
        PMC_REE_0_VD6RE_F_DIS_U32 |
        PMC_REE_0_VD6RE_C_DIS_U32 |
        PMC_REE_0_VD4RE_C_DIS_U32 |
        PMC_REE_0_VD3RE_H_DIS_U32 |
        PMC_REE_0_VD3RE_C_DIS_U32
    ),

    /* Reset event selection register. PMC_RES_0 register. */
    PMC_RES_0_CONFIG_U32
    (
        PMC_RES_0_VD6RE_O_ENA_U32 |
        PMC_RES_0_VD6RE_ADC_ENA_U32 |
        PMC_RES_0_VD6RE_IM_ENA_U32 |
        PMC_RES_0_VD6RE_F_ENA_U32 |
        PMC_RES_0_VD6RE_C_ENA_U32 |
        PMC_RES_0_VD4RE_C_ENA_U32 |
        PMC_RES_0_VD3RE_H_ENA_U32 |
        PMC_RES_0_VD3RE_C_ENA_U32
    ),

    /* Temperature reset event enable register. PMC_REE_TD register. */
    PMC_REE_TD_CONFIG_U32
    (
        PMC_REE_TD_TEMP1_3_DIS_U32 |
        PMC_REE_TD_TEMP1_2_DIS_U32 |
        PMC_REE_TD_TEMP1_0_DIS_U32 |
        PMC_REE_TD_TEMP0_3_DIS_U32 |
        PMC_REE_TD_TEMP0_2_DIS_U32 |
        PMC_REE_TD_TEMP0_0_DIS_U32
    ),

    /* Temperature reset event selection register. PMC_RES_TD register. */
    PMC_RES_TD_CONFIG_U32
    (
        PMC_RES_TD_TEMP1_3_ENA_U32 |
        PMC_RES_TD_TEMP1_2_ENA_U32 |
        PMC_RES_TD_TEMP1_0_ENA_U32 |
        PMC_RES_TD_TEMP0_3_ENA_U32 |
        PMC_RES_TD_TEMP0_2_ENA_U32 |
        PMC_RES_TD_TEMP0_0_ENA_U32
    ),

    /* Temperature detector configuration register. PMC_CTL_TD register. */
    PMC_CTL_TD_CONFIG_U32
    (
        PMC_CTL_TD_TS1_TRIM_ADJ_U32((uint32)0U) |
        PMC_CTL_TD_TS1_DOUT_ENA_U32 |
        PMC_CTL_TD_TS1_AOUT_ENA_U32 |
        PMC_CTL_TD_TS0_TRIM_ADJ_U32((uint32)0U) |
        PMC_CTL_TD_TS0_DOUT_ENA_U32 |
        PMC_CTL_TD_TS0_AOUT_ENA_U32
    )
};
        



/**
* @brief          Initialization data for SSCM hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
STATIC CONST( Mcu_SSCM_ConfigType, MCU_CONST) MC_SSCM_ConfigPC0 =
{
    /* SSCM configuration */
    SSCM_ERROR_U16(
        SSCM_ERROR_PAE_DISABLE_U16 |
        SSCM_ERROR_RAE_DISABLE_U16
    )

};




/**
* @brief          Initialization data for different hw IPs.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
STATIC CONST( Mcu_HwIPsConfigType, MCU_CONST) Mcu_HwIPs_ConfigPC0 =
{
    /* Configuration for MC_ME (Mode Entry Module) hardware IP. */
    &MC_ME_ConfigPC0,

    /* Configuration for MC_RGM (Reset Generation Module) hardware IP. */
    &MC_RGM_ConfigPC0,

    /* Configuration for MC_PCU/PMU (Power Management Unit) hardware IP, part of PCU. */
    &MC_PCU_ConfigPC0,

    /* Configuration for FLASH (Flash Memory) hardware IP. */
    &FLASH_ConfigPC0,

    /* Configuration for SSCM hardware IP. */
    &MC_SSCM_ConfigPC0
};




/**
* @brief          Initialization data for the MCU driver.
* @details        A pointer to such a structure is provided to the MCU initialization routines for configuration.
*
*/
/** @violates @ref Mcu_Cfg_c_REF_7 MISRA 2004 Required Rule 8.10, external linkage ... */
CONST(Mcu_ConfigType, MCU_CONST) Mcu_Config_PC =
{
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &Mcu_Dem_ConfigPC0,
#endif

    /* Number of RAM Sections configurations. */
    (Mcu_RamSectionType)1U,

    /* Number of Power Modes configurations. */
    (Mcu_ModeType)1U,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Number of Clock Setting configurations. */
    (Mcu_ClockType)1U,
#endif /* (MCU_INIT_CLOCK == STD_ON) */

    /* Pointer to RAM Section configurations. */
    &Mcu_Ram_ConfigPC0,

    /* Pointer to Power Mode configurations. */
    &Mcu_Mode_ConfigPC0,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Pointer to Clock configurations. */
    &Mcu_Clock_ConfigPC0,
#endif /* (MCU_INIT_CLOCK == STD_ON) */

    /* Pointer to Low Level Mcu driver configuration. */
    &Mcu_HwIPs_ConfigPC0
};



#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */


#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Mcu_Cfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Cfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

