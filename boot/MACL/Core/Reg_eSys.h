/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Reg_eSys.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:51CST $

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
*   @file    Reg_eSys.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - BIP Memory and DMA mapping.
*   @details Memory mapping of the IP modules and DMA channels present on the MPC574XP 
*            hardware platform.
*
*   @addtogroup BASE_COMPONENT
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MPC574XP
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_ASR_REL_4_0_REV_0003_20141024
*
*   (c) Copyright 2006-2014 Freescale Inc
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/
/**
* @file        Reg_eSys.h
* 
*/

/** 
* @page misra_violations MISRA-C:2004 violations
* 
* @section Reg_eSys_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file 
* This comes from the order of includes in the .c file and from include dependencies. As a safe 
* approach, any file must include all its dependencies. Header files are already protected against 
* double inclusions.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters.The used compilers use more than 31 chars for
* identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused. The driver needs to use defines starting with letter E.
*/

#ifndef REG_ESYS_H
#define REG_ESYS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/** 
* @file        Reg_eSys.h
* @brief Include platform types
* @violates @ref Reg_eSys_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "Platform_Types.h"

/** 
* @file        Reg_eSys.h
* @brief Include IP module versions
*/
#include "Soc_Ips.h"


/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REG_ESYS_VENDOR_ID                    43
#define REG_ESYS_MODULE_ID                    0
#define REG_ESYS_AR_RELEASE_MAJOR_VERSION     4
#define REG_ESYS_AR_RELEASE_MINOR_VERSION     0
#define REG_ESYS_AR_RELEASE_REVISION_VERSION  3
#define REG_ESYS_SW_MAJOR_VERSION             1
#define REG_ESYS_SW_MINOR_VERSION             0
#define REG_ESYS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((REG_ESYS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (REG_ESYS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys.h and Platform_Types.h are different"
    #endif
#endif

/* Check if source file and Soc_Ips.h header file have same versions */
#if (REG_ESYS_VENDOR_ID != SOC_IPS_VENDOR_ID)
#error "Reg_eSys.h and Soc_Ips.h have different vendor IDs"
#endif
#if ((REG_ESYS_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
     (REG_ESYS_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION) || \
     (REG_ESYS_AR_RELEASE_REVISION_VERSION != SOC_IPS_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Reg_eSys.h and Soc_Ips.h are different"
#endif
#if ((REG_ESYS_SW_MAJOR_VERSION != SOC_IPS_SW_MAJOR_VERSION) || \
     (REG_ESYS_SW_MINOR_VERSION != SOC_IPS_SW_MINOR_VERSION) || \
     (REG_ESYS_SW_PATCH_VERSION != SOC_IPS_SW_PATCH_VERSION))
#error "Software Version Numbers of Reg_eSys.h and Soc_Ips.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief  Internal Flash
@details MPC574XP System Memory Map
*/
#define INTERNAL_FLASH_BASEADDR             ((uint32)0x00000000UL)

/**
@brief  Internal RAM
@details MPC574XP System Memory Map

*/
#define INTERNAL_RAM_BASEADDR               ((uint32)0x40000000UL)

/**
@brief  AIPS_A
@details MPC574XP System Memory Map

*/
#define AIPS_A_BASEADDR               ((uint32)0xFC000000UL)

/**
@brief  AIPS_B
@details MPC574XP System Memory Map

*/
#define AIPS_B_BASEADDR               ((uint32)0xF8000000UL)

/**
@brief  FlexPWM 0
@details MPC574XP System Memory Map

*/
#define FLEXPWM_0_BASEADDR                  ((uint32)0xFBC00000UL)

/**
@brief  FlexPWM 1
@details MPC574XP System Memory Map

*/
#define FLEXPWM_1_BASEADDR                  ((uint32)0xFFC04000UL)

/**
@brief  Cross triggering unit (CTU 0)
@details MPC574XP System Memory Map

*/
#define CTU0_BASEADDR                  ((uint32)0xFBC10000UL)

/**
@brief  Cross triggering unit (CTU 1)
@details MPC574XP System Memory Map

*/
#define CTU1_BASEADDR                  ((uint32)0xFFC14000UL)

/**
@brief  eTimer_0
@details MPC574XP System Memory Map

*/
#define ETIMER_0_BASEADDR                  ((uint32)0xFBC20000UL)

/**
@brief  eTimer_1
@details MPC574XP System Memory Map


*/
#define ETIMER_1_BASEADDR                  ((uint32)0xFFC24000UL)

/**
@brief  eTimer_2
@details MPC574XP System Memory Map


*/
#define ETIMER_2_BASEADDR                  ((uint32)0xFBC28000UL)

/**
@brief  SWG_0
@details MPC574XP System Memory Map

*/
#define SWG_BASEADDR                  ((uint32)0xFBC40000UL)

/**
@brief  SAR ADC 0 (ADC_0)
@details MPC574XP System Memory Map

*/
#define ADC0_BASEADDR                  ((uint32)0xFBE00000UL)

/**
@brief  SAR ADC 1 (ADC 1)
@details MPC574XP System Memory Map

*/
#define ADC1_BASEADDR                  ((uint32)0xFFE04000UL)

/**
@brief  SAR ADC 2 (ADC_2)
@details MPC574XP System Memory Map

*/
#define ADC2_BASEADDR                  ((uint32)0xFBE08000UL)

/**
@brief  SAR ADC 3 (ADC 3)
@details MPC574XP System Memory Map

*/
#define ADC3_BASEADDR                  ((uint32)0xFFE0C000UL)

/**
@brief  SAE J2716 Protocol (SENT 0)
@details MPC574XP System Memory Map

*/
#define SENT0_BASEADDR                  ((uint32)0xFFE5C000UL)

/**
@brief  SAE J2716 Protocol (SENT 1)
@details MPC574XP System Memory Map

*/
#define SENT1_BASEADDR                  ((uint32)0xFBE5C000UL)

/**
@brief  Deserial Serial Peripheral Interface 0 (DSPI_0)
@details MPC574XP System Memory Map

*/
#define DSPI0_BASEADDR                  ((uint32)0xFFE70000UL)

/**
@brief  Deserial Serial Peripheral Interface 1 (DSPI_1)
@details MPC574XP System Memory Map

*/
#define DSPI1_BASEADDR                  ((uint32)0xFFE74000UL)

/**
@brief  Deserial Serial Peripheral Interface 2 (DSPI_2)
@details MPC574XP System Memory Map

*/
#define DSPI2_BASEADDR                  ((uint32)0xFBE70000UL)

/**
@brief  Deserial Serial Peripheral Interface 3 (DSPI_3)
@details MPC574XP System Memory Map

*/
#define DSPI3_BASEADDR                  ((uint32)0xFBE74000UL)

/**
@brief  LIN Controller 0 (LINFlex_0)
@details MPC574XP System Memory Map

*/
#define LINFLEX0_BASEADDR                  ((uint32)0xFBE84000UL)

/**
@brief  LIN Controller 1 (LINFlex_1)
@details MPC574XP System Memory Map

*/
#define LINFLEX1_BASEADDR                  ((uint32)0xFFE90000UL)

/**
@brief  Fault Collection and Control Unit (FCCU)
@details MPC574XP System Memory Map

*/
#define FCCU_BASEADDR                  ((uint32)0xFBF58000UL)

/**
@brief  Direct Memory Access Controller Hardware Multiplexer (DMAMUX0)
@details MPC574XP System Memory Map

*/
#define DMAMUX0_BASEADDR                  ((uint32)0xFFF6C000UL)

/**
@brief  Direct Memory Access Controller Hardware Multiplexer (DMAMUX0) - duplicate of DMAMUX0
@details MPC574XP System Memory Map

*/
#define DMAMUX_BASEADDR                  (DMAMUX0_BASEADDR)

/**
@brief  Direct Memory Access Controller Hardware Multiplexer 1 (DMAMUX1)
@details MPC574XP System Memory Map

*/
#define DMAMUX1_BASEADDR                  ((uint32)0xFBF6C000UL)

/**
@brief  Clock Monitor Unit for Motor Clock (CMU)
@details MPC574XP System Memory Map

*/
#define CMU0_BASEADDR                  ((uint32)0xFBFB0200UL)

/**
@brief  Clock Monitor Unit for SYS_CLK (CMU_1)
@details MPC574XP System Memory Map

*/
#define CMU1_BASEADDR                  ((uint32)0xFBFB0240UL)

/**
@brief  Clock Monitor Unit for Peripheral Bridge (CMU_2)
@details MPC574XP System Memory Map

*/
#define CMU2_BASEADDR                  ((uint32)0xFBFB0280UL)

/**
@brief  Clock Monitor Unit for ADC Clock (CMU_3)
@details MPC574XP System Memory Map

*/
#define CMU3_BASEADDR                  ((uint32)0xFBFB02C0UL)

/**
@brief  Clock Monitor Unit for SENT (CMU_4)
@details MPC574XP System Memory Map

*/
#define CMU4_BASEADDR                  ((uint32)0xFBFB0300UL)

/**
@brief  Crossbar (XBAR)
@details MPC574XP System Memory Map

*/
#define XBAR_BASEADDR                  ((uint32)0xFC004000UL)

/**
@brief  System Memory Protection Unit 0 (SMPU_0)
@details MPC574XP System Memory Map

*/
#define SMPU_BASEADDR                  ((uint32)0xFC010000UL)

/**
@brief  Crossbar integrity checker (XBIC)
@details MPC574XP System Memory Map

*/
#define XBIC_BASEADDR                  ((uint32)0xFC018000UL)

/**
@brief  Platform RAM controller (PRAM)
@details MPC574XP System Memory Map

*/
#define PRAM_BASEADDR                  ((uint32)0xFC020000UL)

/**
@brief  Platform control module (PCM)
@details MPC574XP System Memory Map

*/
#define PCM_BASEADDR                  ((uint32)0xFC028000UL)

/**
@brief  Platform Flash controller (PFLASH)
@details MPC574XP System Memory Map

*/
#define PFLASH_BASEADDR                  ((uint32)0xFC030000UL)

/**
@brief  Interrupt Controller 0 (INTC0)
@details MPC574XP System Memory Map

*/
#define INTC_BASEADDR                  ((uint32)0xFC040000UL)

/**
@brief  Software Watchdog Timer 0 (SWT_0)
@details MPC574XP System Memory Map

*/
#define SWT_BASEADDR                  ((uint32)0xFC050000UL)

/**
@brief  System Timer Module 0 (STM_0)
@details MPC574XP System Memory Map

*/
#define STM_BASEADDR                  ((uint32)0xFC068000UL)

#define STM_0_BASEADDR                (STM_BASEADDR)

/**
@brief  Error Injection Module (EIM)
@details MPC574XP System Memory Map

*/
#define EIM_BASEADDR                  ((uint32)0xFC080000UL)

/**
@brief  Direct Memory Access Controller 0 (DMA_0)
@details MPC574XP System Memory Map

*/
#define DMA_BASEADDR                  ((uint32)0xFC0A0000UL)

/**
@brief  Ethernet 0 (ENET)
@details MPC574XP System Memory Map

*/
#define ENET_0_BASEADDR                  ((uint32)0xFC0B0000UL)

/**
@brief  FlexRay Communication Controller (FLEXRAY)
@details MPC574XP System Memory Map

*/
#define FLEXRAY_BASEADDR                  ((uint32)0xFFE50000UL)

/**
@brief  FlexCAN 0(CAN0)
@details MPC574XP System Memory Map

*/
#define FLEXCAN0_BASEADDR                  ((uint32)0xFFEC0000UL)


/**
@brief  FlexCAN 1(CAN1)
@details MPC574XP System Memory Map

*/
#define FLEXCAN1_BASEADDR                  ((uint32)0xFFEC4000UL)

/**
@brief  FlexCAN 2(CAN2)
@details MPC574XP System Memory Map

*/
#define FLEXCAN2_BASEADDR                  ((uint32)0xFFEC8000UL)

/**
@brief  Self Test Control Unit (STCU)
@details MPC574XP System Memory Map

*/
#define STCU_BASEADDR                  ((uint32)0xFFF44000UL)

/**
@brief  Memory Error Management Unit (MEMU)
@details MPC574XP System Memory Map

*/
#define MEMU_BASEADDR                  ((uint32)0xFFF50000UL)

/**
@brief  Cyclic Redundancy Check 0 (CRC_0)
@details MPC574XP System Memory Map

*/
#define CRC0_BASEADDR                  ((uint32)0xFFF64000UL)

/**
@brief  Periodic Interval Timer (PIT)
@details MPC574XP System Memory Map

*/
#define PIT_BASEADDR                  ((uint32)0xFFF84000UL)
#define PIT_0_BASEADDR                (PIT_BASEADDR)                  
/**
@brief  Wake-Up Unit (WKPU)
@details MPC574XP System Memory Map

*/
#define WKPU_BASEADDR                  ((uint32)0xFFF98000UL)

/**
@brief  Power Control Unit (PCU)
@details MPC574XP System Memory Map

*/
#define PCU_BASEADDR                  ((uint32)0xFFFA0000UL)

/**
@brief  Power Management Controller (PMC)
@details MPC574XP System Memory Map

*/
#define PMC_BASEADDR                  ((uint32)0xFFFA0400UL)

/**
@brief  Reset Generation Module (MC_RGM)
@details MPC574XP System Memory Map

*/
#define MC_RGM_BASEADDR                  ((uint32)0xFFFA8000UL)

/**
@brief  Clock Generation Module (MC_CGM)
@details MPC574XP System Memory Map

*/
#define MC_CGM_BASEADDR                  ((uint32)0xFFFB0000UL)

/**
@brief  Mode Entry Module (MC_ME)
@details MPC574XP System Memory Map

*/
#define MC_ME_BASEADDR                  ((uint32)0xFFFB8000UL)

/**
@brief  IRCOSC (Internal RC Oscillator)
@details MPC574XP System Memory Map

*/
#define IRCOSC_BASEADDR                  ((uint32)0xFFFB0000UL)

/**
@brief  OSC (Oscillator)
@details MPC574XP System Memory Map

*/
#define XOSC_BASEADDR                  ((uint32)0xFFFB0080UL)

/**
@brief  Dual PLL Digital Interface (PLLDIG)
@details MPC574XP System Memory Map

*/
#define PLLDIG_BASEADDR                  ((uint32)0xFFFB0100UL)

/**
@brief  System Integration Unit Lite 2 (SIUL2)
@details MPC574XP System Memory Map

*/
#define SIUL2_BASEADDR                  ((uint32)0xFFFC0000UL)

/**
@brief  Serial Interprocessor Interface (SIPI)
@details MPC574XP System Memory Map

*/
#define SIPI_BASEADDR                  ((uint32)0xFFFD0000UL)

/**
@brief  DigRF 0 (DIGRF_0)
@details MPC574XP System Memory Map

*/
#define DIGRF_BASEADDR                  ((uint32)0xFFFD8000UL)

/**
* @brief Flash main control registers
* @details MPC574XP System Memory Map
* 
*/
#define FMCR_BASEADDR             ((uint32)0xFFFE0000UL)

/**
@brief  System Status and Configuration Module (SSCM)
@details MPC574XP System Memory Map

*/
#define SSCM_BASEADDR                  ((uint32)0xFFFF8000UL)

/**
@brief  Boot Assist Module (BAM)
@details MPC574XP System Memory Map

*/
#define BAM_BASEADDR                  ((uint32)0xFFFFC000UL)


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef REG_ESYS_H*/

/** @} */
