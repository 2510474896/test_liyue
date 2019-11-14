/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Port_Cfg.h $
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
* @file    Port_Cfg.h
* @implements Port_Cfg.h_Artifact
*
* @version 1.0.0
* @brief   AUTOSAR Port - PORT driver configuration.
* @details This file contains the PORT driver precompile configuration.
*
* @addtogroup Port
* @{
*/
/*=================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : SIUL2
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
=================================================================================================*/
/*=================================================================================================
=================================================================================================*/


#ifndef PORT_CFG_H
#define PORT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_CFG_H_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linkershall be checked to ensure 
* that 31 character significance and case sensitivity are supported for external 
* identifiers. The defines are ok.
*
* @section PORT_CFG_H_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section PORT_CFG_H_REF_3
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section PORT_CFG_H_REF_4
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function.
* This happens because the data is generated in the conig layer and used in the LL driver.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Port_EnvCfg.h"
#include "Port_Siul2_Types.h"


/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
* @details The integration of incompatible files shall be avoided.
*/
#define PORT_VENDOR_ID_CFG_H                       43
#define PORT_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define PORT_AR_RELEASE_MINOR_VERSION_CFG_H        0
#define PORT_AR_RELEASE_REVISION_VERSION_CFG_H     3
#define PORT_SW_MAJOR_VERSION_CFG_H                1
#define PORT_SW_MINOR_VERSION_CFG_H                0
#define PORT_SW_PATCH_VERSION_CFG_H                0

/*=================================================================================================
*                               FILE VERSION CHECKS
=================================================================================================*/

/* Check if Port_Cfg.h and Port_SIUL_Types.h file are of the same vendor */
#if (PORT_VENDOR_ID_CFG_H != PORT_SIUL2_VENDOR_ID_TYPES_H)
    #error "Port_Cfg.h and Port_Siul2_Types.h have different vendor ids"
#endif
/* Check if Port_Cfg.h and Port_Siul2_Types.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_H != PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_H != PORT_SIUL2_AR_RELEASE_MINOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_H != PORT_SIUL2_AR_RELEASE_REVISION_VERSION_TYPES_H) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_Siul2_Types.h are different"
#endif
/* Check if Port_Cfg.h and Port_Siul2_Types.h file are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_H != PORT_SIUL2_SW_MAJOR_VERSION_TYPES_H) || \
     (PORT_SW_MINOR_VERSION_CFG_H != PORT_SIUL2_SW_MINOR_VERSION_TYPES_H) || \
     (PORT_SW_PATCH_VERSION_CFG_H != PORT_SIUL2_SW_PATCH_VERSION_TYPES_H)    \
    )
    #error "Software Version Numbers of Port_Cfg.h and Port_Siul2_Types.h are different"
#endif

/* Check if Port_Cfg.h file and Port_EnvCfg header file are of the same vendor */
#if (PORT_VENDOR_ID_CFG_H != PORT_ENVCFG_VENDOR_ID)
    #error "Port_Cfg.h and Port_EnvCfg.h have different vendor IDs"
#endif

#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_MAJOR_VERSION)      || \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_MINOR_VERSION)      || \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_REVISION_VERSION)   \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_EnvCfg.h are different"
#endif
/* Check if Port_Cfg.h and PORT header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_H != PORT_ENVCFG_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_CFG_H != PORT_ENVCFG_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_CFG_H != PORT_ENVCFG_SW_PATCH_VERSION)    \
    )
#error "Software Version Numbers of Port_Cfg.h and Port_EnvCfg.h are different"
#endif


/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief       Ensure better readability of the configuration
* @note 
*
* @violates @ref PORT_CFG_H_REF_3 Function-like macro defined.
*/
#define SHL_PAD_U16(x)                      ((uint16)(((uint16)1) << (x)))

/**
* @brief PSMI setting not available
* @note The current platform does not implement pad selection for multiplexed input for current pin.
*       Used for better readability of PSMI settings.
*
*/
#define NO_INPUTMUX_U16                     ((uint16)0xFFFFU)

/**
* @brief Show the Platform used.
* @note This define can be used by test phase.  
*
*/
#define PLATFORM_PANTHER
/**
* @brief Show the IPV used.
* @note This define can be used by test phase.
*
*/
#define IPV_SIUL2_USED


/** @brief Port GPIO Mode */
#define PORT_GPIO_MODE                  ((Port_PinModeType)0)
/** @brief Port Alternate 1 Mode */
#define PORT_ALT1_FUNC_MODE             ((Port_PinModeType)1)
/** @brief Port Alternate 2 Mode */
#define PORT_ALT2_FUNC_MODE             ((Port_PinModeType)2)
/** @brief Port Alternate 3 Mode */
#define PORT_ALT3_FUNC_MODE             ((Port_PinModeType)3)
/** @brief Port Alternate 4 Mode */
#define PORT_ALT4_FUNC_MODE             ((Port_PinModeType)4)
/** @brief Port Analog input Mode */
#define PORT_ANALOG_INPUT_MODE          ((Port_PinModeType)5)
/** @brief Port Input 1 Mode */
#define PORT_INPUT1_MODE                ((Port_PinModeType)6)
/** @brief Port Input 2 Mode */
#define PORT_INPUT2_MODE                ((Port_PinModeType)7)
/** @brief Port Input 3 Mode */
#define PORT_INPUT3_MODE                ((Port_PinModeType)8)
/** @brief Port Input 4 Mode */
#define PORT_INPUT4_MODE                ((Port_PinModeType)9)
/** @brief Port Input 5 Mode */
#define PORT_INPUT5_MODE                ((Port_PinModeType)10)

/** @brief Port Abstraction Modes */


#define PORT0_GPIO            (PORT_GPIO_MODE)
 #define PORT0_eTimer0_ETC0            (PORT_ALT1_FUNC_MODE)
 #define PORT0_DSPI2_SCK_OUT            (PORT_ALT2_FUNC_MODE)
 #define PORT0_eTimer0_ETC0_IN            (PORT_INPUT1_MODE)
 #define PORT0_DSPI2_SCK_IN            (PORT_INPUT2_MODE)
 #define PORT0_SIUL2_IRQ0            (PORT_INPUT3_MODE)
 #define PORT1_GPIO            (PORT_GPIO_MODE)
 #define PORT1_eTimer0_ETC1            (PORT_ALT1_FUNC_MODE)
 #define PORT1_DSPI2_SOUT            (PORT_ALT2_FUNC_MODE)
 #define PORT1_eTimer0_ETC1_IN            (PORT_INPUT1_MODE)
 #define PORT1_SIUL2_IRQ1            (PORT_INPUT2_MODE)
 #define PORT2_GPIO            (PORT_GPIO_MODE)
 #define PORT2_eTimer0_ETC2            (PORT_ALT1_FUNC_MODE)
 #define PORT2_FlexPWM0_A3            (PORT_ALT3_FUNC_MODE)
 #define PORT2_MC_RGM_ABS0            (PORT_INPUT1_MODE)
 #define PORT2_DSPI2_SIN            (PORT_INPUT2_MODE)
 #define PORT2_eTimer0_ETC2_IN            (PORT_INPUT3_MODE)
 #define PORT2_SIUL2_IRQ2            (PORT_INPUT4_MODE)
 #define PORT2_FlexPWM0_A3_IN            (PORT_INPUT5_MODE)
 #define PORT3_GPIO            (PORT_GPIO_MODE)
 #define PORT3_eTimer0_ETC3            (PORT_ALT1_FUNC_MODE)
 #define PORT3_DSPI2_CS0            (PORT_ALT2_FUNC_MODE)
 #define PORT3_FlexPWM0_B3            (PORT_ALT3_FUNC_MODE)
 #define PORT3_MC_RGM_ABS2            (PORT_INPUT1_MODE)
 #define PORT3_eTimer0_ETC3_IN            (PORT_INPUT2_MODE)
 #define PORT3_DSPI2_CS0_IN            (PORT_INPUT3_MODE)
 #define PORT3_SIUL2_IRQ3            (PORT_INPUT4_MODE)
 #define PORT3_FlexPWM0_B3_IN            (PORT_INPUT5_MODE)
 #define PORT4_GPIO            (PORT_GPIO_MODE)
 #define PORT4_eTimer1_ETC0            (PORT_ALT1_FUNC_MODE)
 #define PORT4_DSPI2_CS1            (PORT_ALT2_FUNC_MODE)
 #define PORT4_eTimer0_ETC4            (PORT_ALT3_FUNC_MODE)
 #define PORT4_FlexPWM1_A2            (PORT_ALT4_FUNC_MODE)
 #define PORT4_FlexPWM1_A2_IN            (PORT_INPUT1_MODE)
 #define PORT4_SIUL2_IRQ4            (PORT_INPUT2_MODE)
 #define PORT4_MC_RGM_FAB            (PORT_INPUT3_MODE)
 #define PORT4_eTimer0_ETC4_IN            (PORT_INPUT4_MODE)
 #define PORT4_eTimer1_ETC0_IN            (PORT_INPUT5_MODE)
 #define PORT5_GPIO            (PORT_GPIO_MODE)
 #define PORT5_DSPI1_CS0            (PORT_ALT1_FUNC_MODE)
 #define PORT5_eTimer1_ETC5            (PORT_ALT2_FUNC_MODE)
 #define PORT5_DSPI0_CS7            (PORT_ALT3_FUNC_MODE)
 #define PORT5_SIUL2_IRQ5            (PORT_INPUT1_MODE)
 #define PORT5_eTimer1_ETC5_IN            (PORT_INPUT2_MODE)
 #define PORT6_GPIO            (PORT_GPIO_MODE)
 #define PORT6_DSPI1_SCK            (PORT_ALT1_FUNC_MODE)
 #define PORT6_eTimer2_ETC2            (PORT_ALT2_FUNC_MODE)
 #define PORT6_SIUL2_IRQ6            (PORT_INPUT1_MODE)
 #define PORT6_eTimer2_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT7_GPIO            (PORT_GPIO_MODE)
 #define PORT7_DSPI1_SOUT            (PORT_ALT1_FUNC_MODE)
 #define PORT7_eTimer2_ETC3            (PORT_ALT2_FUNC_MODE)
 #define PORT7_SIUL2_IRQ7            (PORT_INPUT1_MODE)
 #define PORT7_eTimer2_ETC3_IN            (PORT_INPUT2_MODE)
 #define PORT8_GPIO            (PORT_GPIO_MODE)
 #define PORT8_eTimer2_ETC4            (PORT_ALT2_FUNC_MODE)
 #define PORT8_DSPI1_SIN            (PORT_INPUT1_MODE)
 #define PORT8_SIUL2_IRQ8            (PORT_INPUT2_MODE)
 #define PORT8_eTimer2_ETC4_IN            (PORT_INPUT3_MODE)
 #define PORT9_GPIO            (PORT_GPIO_MODE)
 #define PORT9_DSPI2_CS1            (PORT_ALT1_FUNC_MODE)
 #define PORT9_eTimer2_ETC5            (PORT_ALT2_FUNC_MODE)
 #define PORT9_FlexPWM0_B3            (PORT_ALT3_FUNC_MODE)
 #define PORT9_FlexPWM0_FAULT0            (PORT_INPUT1_MODE)
 #define PORT9_eTimer2_ETC5_IN            (PORT_INPUT2_MODE)
 #define PORT9_FlexPWM0_B3_IN            (PORT_INPUT3_MODE)
 #define PORT9_SENT0_RX1            (PORT_INPUT4_MODE)
 #define PORT10_GPIO            (PORT_GPIO_MODE)
 #define PORT10_DSPI2_CS0            (PORT_ALT1_FUNC_MODE)
 #define PORT10_FlexPWM0_B0            (PORT_ALT2_FUNC_MODE)
 #define PORT10_FlexPWM0_X2            (PORT_ALT3_FUNC_MODE)
 #define PORT10_DSPI2_CS0_IN            (PORT_INPUT1_MODE)
 #define PORT10_SIUL2_IRQ9            (PORT_INPUT2_MODE)
 #define PORT10_FlexPWM0_B0_IN            (PORT_INPUT3_MODE)
 #define PORT10_FlexPWM0_X2_IN            (PORT_INPUT4_MODE)
 #define PORT10_SENT1_RX1            (PORT_INPUT5_MODE)
 #define PORT11_GPIO            (PORT_GPIO_MODE)
 #define PORT11_DSPI2_SCK_OUT            (PORT_ALT1_FUNC_MODE)
 #define PORT11_FlexPWM0_A0            (PORT_ALT2_FUNC_MODE)
 #define PORT11_FlexPWM0_A2            (PORT_ALT3_FUNC_MODE)
 #define PORT11_DSPI2_SCK_IN            (PORT_INPUT1_MODE)
 #define PORT11_SIUL2_IRQ10            (PORT_INPUT2_MODE)
 #define PORT11_FlexPWM0_A0_IN            (PORT_INPUT3_MODE)
 #define PORT11_FlexPWM0_A2_IN            (PORT_INPUT4_MODE)
 #define PORT12_GPIO            (PORT_GPIO_MODE)
 #define PORT12_DSPI2_SOUT            (PORT_ALT1_FUNC_MODE)
 #define PORT12_FlexPWM0_A2            (PORT_ALT2_FUNC_MODE)
 #define PORT12_FlexPWM0_B2            (PORT_ALT3_FUNC_MODE)
 #define PORT12_SIUL2_IRQ11            (PORT_INPUT1_MODE)
 #define PORT12_FlexPWM0_A2_IN            (PORT_INPUT2_MODE)
 #define PORT12_FlexPWM0_B2_IN            (PORT_INPUT3_MODE)
 #define PORT13_GPIO            (PORT_GPIO_MODE)
 #define PORT13_FlexPWM0_B2            (PORT_ALT2_FUNC_MODE)
 #define PORT13_FlexPWM0_FAULT0            (PORT_INPUT1_MODE)
 #define PORT13_DSPI2_SIN            (PORT_INPUT2_MODE)
 #define PORT13_SIUL2_IRQ12            (PORT_INPUT3_MODE)
 #define PORT13_FlexPWM0_B2_IN            (PORT_INPUT4_MODE)
 #define PORT14_GPIO            (PORT_GPIO_MODE)
 #define PORT14_CAN1_TX            (PORT_ALT1_FUNC_MODE)
 #define PORT14_eTimer1_ETC4            (PORT_ALT2_FUNC_MODE)
 #define PORT14_SIUL2_IRQ13            (PORT_INPUT1_MODE)
 #define PORT14_eTimer1_ETC4_IN            (PORT_INPUT2_MODE)
 #define PORT15_GPIO            (PORT_GPIO_MODE)
 #define PORT15_eTimer1_ETC5            (PORT_ALT2_FUNC_MODE)
 #define PORT15_CAN0_RX            (PORT_INPUT1_MODE)
 #define PORT15_CAN1_RX            (PORT_INPUT2_MODE)
 #define PORT15_SIUL2_IRQ14            (PORT_INPUT3_MODE)
 #define PORT15_eTimer1_ETC5_IN            (PORT_INPUT4_MODE)
 #define PORT16_GPIO            (PORT_GPIO_MODE)
 #define PORT16_CAN0_TX            (PORT_ALT1_FUNC_MODE)
 #define PORT16_eTimer1_ETC2            (PORT_ALT2_FUNC_MODE)
 #define PORT16_SSCM_DEBUG0            (PORT_ALT3_FUNC_MODE)
 #define PORT16_SIUL2_IRQ15            (PORT_INPUT1_MODE)
 #define PORT16_eTimer1_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT17_GPIO            (PORT_GPIO_MODE)
 #define PORT17_eTimer1_ETC3            (PORT_ALT2_FUNC_MODE)
 #define PORT17_SSCM_DEBUG1            (PORT_ALT3_FUNC_MODE)
 #define PORT17_CAN0_RX            (PORT_INPUT1_MODE)
 #define PORT17_CAN1_RX            (PORT_INPUT2_MODE)
 #define PORT17_SIUL2_IRQ16            (PORT_INPUT3_MODE)
 #define PORT17_eTimer1_ETC3_IN            (PORT_INPUT4_MODE)
 #define PORT18_GPIO            (PORT_GPIO_MODE)
 #define PORT18_LIN0_TXD            (PORT_ALT1_FUNC_MODE)
 #define PORT18_DSPI0_CS4            (PORT_ALT2_FUNC_MODE)
 #define PORT18_SSCM_DEBUG2            (PORT_ALT3_FUNC_MODE)
 #define PORT18_SIUL2_IRQ17            (PORT_INPUT1_MODE)
 #define PORT19_GPIO            (PORT_GPIO_MODE)
 #define PORT19_DSPI0_CS5            (PORT_ALT2_FUNC_MODE)
 #define PORT19_SSCM_DEBUG3            (PORT_ALT3_FUNC_MODE)
 #define PORT19_LIN0_RXD            (PORT_INPUT1_MODE)
 #define PORT20_GPIO            (PORT_GPIO_MODE)
 #define PORT20_TDO_MUX_TDO            (PORT_ALT1_FUNC_MODE)
 #define PORT21_GPIO            (PORT_GPIO_MODE)
 #define PORT21_DSPI0_CS7            (PORT_ALT1_FUNC_MODE)
 #define PORT22_GPIO            (PORT_GPIO_MODE)
 #define PORT22_MC_CGM_CLKOUT            (PORT_ALT1_FUNC_MODE)
 #define PORT22_DSPI2_CS2            (PORT_ALT2_FUNC_MODE)
 #define PORT22_SIUL2_IRQ18            (PORT_INPUT1_MODE)
 #define PORT23_GPI            (PORT_GPIO_MODE)
 #define PORT23_ADC0_AN0            (PORT_ANALOG_INPUT_MODE)
 #define PORT23_LIN0_RXD            (PORT_INPUT1_MODE)
 #define PORT24_GPI            (PORT_GPIO_MODE)
 #define PORT24_ADC0_AN1            (PORT_ANALOG_INPUT_MODE)
 #define PORT24_eTimer0_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT25_GPI            (PORT_GPIO_MODE)
 #define PORT25_ADC0_ADC1_AN11            (PORT_ANALOG_INPUT_MODE)
 #define PORT26_GPI            (PORT_GPIO_MODE)
 #define PORT26_ADC0_ADC1_AN12            (PORT_ANALOG_INPUT_MODE)
 #define PORT27_GPI            (PORT_GPIO_MODE)
 #define PORT27_ADC0_ADC1_AN13            (PORT_ANALOG_INPUT_MODE)
 #define PORT28_GPI            (PORT_GPIO_MODE)
 #define PORT28_ADC0_ADC1_AN14            (PORT_ANALOG_INPUT_MODE)
 #define PORT29_GPI            (PORT_GPIO_MODE)
 #define PORT29_ADC1_AN0            (PORT_ANALOG_INPUT_MODE)
 #define PORT29_LIN1_RXD            (PORT_INPUT1_MODE)
 #define PORT30_GPI            (PORT_GPIO_MODE)
 #define PORT30_ADC1_AN1            (PORT_ANALOG_INPUT_MODE)
 #define PORT30_eTimer0_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT30_SIUL2_IRQ19            (PORT_INPUT2_MODE)
 #define PORT31_GPI            (PORT_GPIO_MODE)
 #define PORT31_ADC1_AN2            (PORT_ANALOG_INPUT_MODE)
 #define PORT31_SIUL2_IRQ20            (PORT_INPUT1_MODE)
 #define PORT32_GPI            (PORT_GPIO_MODE)
 #define PORT32_ADC1_AN3            (PORT_ANALOG_INPUT_MODE)
 #define PORT33_GPI            (PORT_GPIO_MODE)
 #define PORT33_ADC0_AN2            (PORT_ANALOG_INPUT_MODE)
 #define PORT34_GPI            (PORT_GPIO_MODE)
 #define PORT34_ADC0_AN3            (PORT_ANALOG_INPUT_MODE)
 #define PORT36_GPIO            (PORT_GPIO_MODE)
 #define PORT36_DSPI0_CS0            (PORT_ALT1_FUNC_MODE)
 #define PORT36_FlexPWM0_X1            (PORT_ALT2_FUNC_MODE)
 #define PORT36_SSCM_DEBUG4            (PORT_ALT3_FUNC_MODE)
 #define PORT36_SIUL2_IRQ22            (PORT_INPUT1_MODE)
 #define PORT36_FlexPWM0_X1_IN            (PORT_INPUT2_MODE)
 #define PORT37_GPIO            (PORT_GPIO_MODE)
 #define PORT37_DSPI0_SCK            (PORT_ALT1_FUNC_MODE)
 #define PORT37_SSCM_DEBUG5            (PORT_ALT3_FUNC_MODE)
 #define PORT37_FlexPWM0_FAULT3            (PORT_INPUT1_MODE)
 #define PORT37_SIUL2_IRQ23            (PORT_INPUT2_MODE)
 #define PORT38_GPIO            (PORT_GPIO_MODE)
 #define PORT38_DSPI0_SOUT            (PORT_ALT1_FUNC_MODE)
 #define PORT38_FlexPWM0_B1            (PORT_ALT2_FUNC_MODE)
 #define PORT38_SSCM_DEBUG6            (PORT_ALT3_FUNC_MODE)
 #define PORT38_SIUL2_IRQ24            (PORT_INPUT1_MODE)
 #define PORT38_FlexPWM0_B1_IN            (PORT_INPUT2_MODE)
 #define PORT39_GPIO            (PORT_GPIO_MODE)
 #define PORT39_FlexPWM0_A1            (PORT_ALT2_FUNC_MODE)
 #define PORT39_SSCM_DEBUG7            (PORT_ALT3_FUNC_MODE)
 #define PORT39_DSPI0_SIN            (PORT_INPUT1_MODE)
 #define PORT39_FlexPWM0_A1_IN            (PORT_INPUT2_MODE)
 #define PORT42_GPIO            (PORT_GPIO_MODE)
 #define PORT42_DSPI2_CS2            (PORT_ALT1_FUNC_MODE)
 #define PORT42_FlexPWM0_A3            (PORT_ALT3_FUNC_MODE)
 #define PORT42_FlexPWM0_FAULT1            (PORT_INPUT1_MODE)
 #define PORT42_FlexPWM0_A3_IN            (PORT_INPUT2_MODE)
 #define PORT43_GPIO            (PORT_GPIO_MODE)
 #define PORT43_eTimer0_ETC4            (PORT_ALT1_FUNC_MODE)
 #define PORT43_DSPI2_CS2            (PORT_ALT2_FUNC_MODE)
 #define PORT43_ENET0_TX_ER            (PORT_ALT3_FUNC_MODE)
 #define PORT43_eTimer0_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT43_DSPI3_CS0            (PORT_INPUT2_MODE)
 #define PORT44_GPIO            (PORT_GPIO_MODE)
 #define PORT44_eTimer0_ETC5            (PORT_ALT1_FUNC_MODE)
 #define PORT44_DSPI2_CS3            (PORT_ALT2_FUNC_MODE)
 #define PORT44_LFAST_PH0_POS            (PORT_ALT3_FUNC_MODE)
 #define PORT44_DSPI3_CS1            (PORT_ALT4_FUNC_MODE)
 #define PORT44_eTimer0_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT44_SENT1_RX0            (PORT_INPUT2_MODE)
 #define PORT45_GPIO            (PORT_GPIO_MODE)
 #define PORT45_eTimer1_ETC1            (PORT_ALT1_FUNC_MODE)
 #define PORT45_FlexPWM1_A0            (PORT_ALT4_FUNC_MODE)
 #define PORT45_CTU0_EXT_IN            (PORT_INPUT1_MODE)
 #define PORT45_FlexPWM0_SYNC            (PORT_INPUT2_MODE)
 #define PORT45_FlexPWM1_A0_IN            (PORT_INPUT3_MODE)
 #define PORT45_eTimer1_ETC1_IN            (PORT_INPUT4_MODE)
 #define PORT46_GPIO            (PORT_GPIO_MODE)
 #define PORT46_eTimer1_ETC2            (PORT_ALT1_FUNC_MODE)
 #define PORT46_CTU0_EXT_TRIG            (PORT_ALT2_FUNC_MODE)
 #define PORT46_DSPI1_CS7            (PORT_ALT3_FUNC_MODE)
 #define PORT46_FlexPWM1_B0            (PORT_ALT4_FUNC_MODE)
 #define PORT46_FlexPWM1_B0_IN            (PORT_INPUT1_MODE)
 #define PORT46_eTimer1_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT47_GPIO            (PORT_GPIO_MODE)
 #define PORT47_FlexRay_FR_A_TXEN            (PORT_ALT1_FUNC_MODE)
 #define PORT47_eTimer1_ETC0            (PORT_ALT2_FUNC_MODE)
 #define PORT47_FlexPWM0_A1            (PORT_ALT3_FUNC_MODE)
 #define PORT47_CTU0_EXT_IN            (PORT_INPUT1_MODE)
 #define PORT47_FlexPWM0_SYNC            (PORT_INPUT2_MODE)
 #define PORT47_eTimer1_ETC0_IN            (PORT_INPUT3_MODE)
 #define PORT47_FlexPWM0_A1_IN            (PORT_INPUT4_MODE)
 #define PORT48_GPIO            (PORT_GPIO_MODE)
 #define PORT48_FlexRay_FR_A_TX            (PORT_ALT1_FUNC_MODE)
 #define PORT48_eTimer1_ETC1            (PORT_ALT2_FUNC_MODE)
 #define PORT48_FlexPWM0_B1            (PORT_ALT3_FUNC_MODE)
 #define PORT48_eTimer1_ETC1_IN            (PORT_INPUT1_MODE)
 #define PORT48_FlexPWM0_B1_IN            (PORT_INPUT2_MODE)
 #define PORT49_GPIO            (PORT_GPIO_MODE)
 #define PORT49_eTimer1_ETC2            (PORT_ALT2_FUNC_MODE)
 #define PORT49_CTU0_EXT_TRIG            (PORT_ALT3_FUNC_MODE)
 #define PORT49_FlexRay_FR_A_RX            (PORT_INPUT1_MODE)
 #define PORT49_eTimer1_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT50_GPIO            (PORT_GPIO_MODE)
 #define PORT50_eTimer1_ETC3            (PORT_ALT2_FUNC_MODE)
 #define PORT50_FlexPWM0_X3            (PORT_ALT3_FUNC_MODE)
 #define PORT50_FlexRay_FR_B_RX            (PORT_INPUT1_MODE)
 #define PORT50_eTimer1_ETC3_IN            (PORT_INPUT2_MODE)
 #define PORT50_FlexPWM0_X3_IN            (PORT_INPUT3_MODE)
 #define PORT51_GPIO            (PORT_GPIO_MODE)
 #define PORT51_FlexRay_FR_B_TX            (PORT_ALT1_FUNC_MODE)
 #define PORT51_eTimer1_ETC4            (PORT_ALT2_FUNC_MODE)
 #define PORT51_FlexPWM0_A3            (PORT_ALT3_FUNC_MODE)
 #define PORT51_eTimer1_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT51_FlexPWM0_A3_IN            (PORT_INPUT2_MODE)
 #define PORT52_GPIO            (PORT_GPIO_MODE)
 #define PORT52_FlexRay_FR_B_TXEN            (PORT_ALT1_FUNC_MODE)
 #define PORT52_eTimer1_ETC5            (PORT_ALT2_FUNC_MODE)
 #define PORT52_FlexPWM0_B3            (PORT_ALT3_FUNC_MODE)
 #define PORT52_eTimer1_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT52_FlexPWM0_B3_IN            (PORT_INPUT2_MODE)
 #define PORT53_GPIO            (PORT_GPIO_MODE)
 #define PORT53_DSPI0_CS3            (PORT_ALT1_FUNC_MODE)
 #define PORT53_DSPI3_SOUT            (PORT_ALT4_FUNC_MODE)
 #define PORT53_FlexPWM0_FAULT2            (PORT_INPUT1_MODE)
 #define PORT53_SENT0_RX0            (PORT_INPUT2_MODE)
 #define PORT53_ENET0_RX_D1            (PORT_INPUT3_MODE)
 #define PORT54_GPIO            (PORT_GPIO_MODE)
 #define PORT54_DSPI0_CS2            (PORT_ALT1_FUNC_MODE)
 #define PORT54_FlexPWM0_X3            (PORT_ALT3_FUNC_MODE)
 #define PORT54_DSPI3_SCK            (PORT_ALT4_FUNC_MODE)
 #define PORT54_FlexPWM0_FAULT1            (PORT_INPUT1_MODE)
 #define PORT54_FlexPWM0_X3_IN            (PORT_INPUT2_MODE)
 #define PORT54_DSPI3_SCK_IN            (PORT_INPUT3_MODE)
 #define PORT54_ENET0_RX_D0            (PORT_INPUT4_MODE)
 #define PORT55_GPIO            (PORT_GPIO_MODE)
 #define PORT55_DSPI1_CS3            (PORT_ALT1_FUNC_MODE)
 #define PORT55_DSPI0_CS4            (PORT_ALT3_FUNC_MODE)
 #define PORT55_SENT1_RX0            (PORT_INPUT1_MODE)
 #define PORT55_DSPI3_SIN            (PORT_INPUT2_MODE)
 #define PORT55_ENET0_RX_DV            (PORT_INPUT3_MODE)
 #define PORT56_GPIO            (PORT_GPIO_MODE)
 #define PORT56_DSPI1_CS2            (PORT_ALT1_FUNC_MODE)
 #define PORT56_eTimer1_ETC4            (PORT_ALT2_FUNC_MODE)
 #define PORT56_DSPI0_CS5            (PORT_ALT3_FUNC_MODE)
 #define PORT56_FlexPWM0_FAULT3            (PORT_INPUT1_MODE)
 #define PORT56_eTimer1_ETC4_IN            (PORT_INPUT2_MODE)
 #define PORT56_ENET0_RX_CLK            (PORT_INPUT3_MODE)
 #define PORT57_GPIO            (PORT_GPIO_MODE)
 #define PORT57_FlexPWM0_X0            (PORT_ALT1_FUNC_MODE)
 #define PORT57_LIN1_TXD            (PORT_ALT2_FUNC_MODE)
 #define PORT58_GPIO            (PORT_GPIO_MODE)
 #define PORT58_FlexPWM0_A0            (PORT_ALT1_FUNC_MODE)
 #define PORT58_ENET0_TX_D2            (PORT_ALT3_FUNC_MODE)
 #define PORT58_DSPI3_CS0            (PORT_ALT4_FUNC_MODE)
 #define PORT58_eTimer0_ETC0_IN            (PORT_INPUT1_MODE)
 #define PORT58_FlexPWM0_A0_IN            (PORT_INPUT2_MODE)
 #define PORT58_DSPI3_CS0_IN            (PORT_INPUT3_MODE)
 #define PORT59_GPIO            (PORT_GPIO_MODE)
 #define PORT59_FlexPWM0_B0            (PORT_ALT1_FUNC_MODE)
 #define PORT59_DSPI3_CS1            (PORT_ALT3_FUNC_MODE)
 #define PORT59_DSPI3_SCK            (PORT_ALT4_FUNC_MODE)
 #define PORT59_eTimer0_ETC1_IN            (PORT_INPUT1_MODE)
 #define PORT59_FlexPWM0_B0_IN            (PORT_INPUT2_MODE)
 #define PORT59_DSPI3_SCK_IN            (PORT_INPUT3_MODE)
 #define PORT60_GPIO            (PORT_GPIO_MODE)
 #define PORT60_FlexPWM0_X1            (PORT_ALT1_FUNC_MODE)
 #define PORT60_DSPI1_CS6            (PORT_ALT2_FUNC_MODE)
 #define PORT60_DSPI3_CS2            (PORT_ALT3_FUNC_MODE)
 #define PORT60_DSPI3_SOUT            (PORT_ALT4_FUNC_MODE)
 #define PORT60_LIN1_RXD            (PORT_INPUT1_MODE)
 #define PORT60_FlexPWM0_X1_IN            (PORT_INPUT2_MODE)
 #define PORT62_GPIO            (PORT_GPIO_MODE)
 #define PORT62_FlexPWM0_B1            (PORT_ALT1_FUNC_MODE)
 #define PORT62_DSPI3_CS3            (PORT_ALT3_FUNC_MODE)
 #define PORT62_eTimer0_ETC3_IN            (PORT_INPUT1_MODE)
 #define PORT62_FlexPWM0_B1_IN            (PORT_INPUT2_MODE)
 #define PORT62_DSPI3_SIN            (PORT_INPUT3_MODE)
 #define PORT64_GPI            (PORT_GPIO_MODE)
 #define PORT64_ADC1_AN5_ADC3_AN4            (PORT_ANALOG_INPUT_MODE)
 #define PORT66_GPI            (PORT_GPIO_MODE)
 #define PORT66_ADC0_AN5            (PORT_ANALOG_INPUT_MODE)
 #define PORT68_GPI            (PORT_GPIO_MODE)
 #define PORT68_ADC0_AN7            (PORT_ANALOG_INPUT_MODE)
 #define PORT69_GPI            (PORT_GPIO_MODE)
 #define PORT69_ADC0_AN8            (PORT_ANALOG_INPUT_MODE)
 #define PORT70_GPI            (PORT_GPIO_MODE)
 #define PORT70_ADC0_ADC2_AN4            (PORT_ANALOG_INPUT_MODE)
 #define PORT71_GPI            (PORT_GPIO_MODE)
 #define PORT71_ADC0_AN6            (PORT_ANALOG_INPUT_MODE)
 #define PORT73_GPI            (PORT_GPIO_MODE)
 #define PORT73_ADC1_AN7_ADC3_AN6            (PORT_ANALOG_INPUT_MODE)
 #define PORT74_GPI            (PORT_GPIO_MODE)
 #define PORT74_ADC1_AN8_ADC3_AN7            (PORT_ANALOG_INPUT_MODE)
 #define PORT75_GPI            (PORT_GPIO_MODE)
 #define PORT75_ADC1_AN4_ADC3_AN3            (PORT_ANALOG_INPUT_MODE)
 #define PORT76_GPI            (PORT_GPIO_MODE)
 #define PORT76_ADC1_AN6_ADC3_AN5            (PORT_ANALOG_INPUT_MODE)
 #define PORT77_GPIO            (PORT_GPIO_MODE)
 #define PORT77_eTimer0_ETC5            (PORT_ALT1_FUNC_MODE)
 #define PORT77_DSPI2_CS3            (PORT_ALT2_FUNC_MODE)
 #define PORT77_DSPI1_CS4            (PORT_ALT3_FUNC_MODE)
 #define PORT77_DSPI3_SCK            (PORT_ALT4_FUNC_MODE)
 #define PORT77_SIUL2_IRQ25            (PORT_INPUT1_MODE)
 #define PORT77_eTimer0_ETC5_IN            (PORT_INPUT2_MODE)
 #define PORT77_DSPI3_SCK_IN            (PORT_INPUT3_MODE)
 #define PORT78_GPIO            (PORT_GPIO_MODE)
 #define PORT78_eTimer1_ETC5            (PORT_ALT1_FUNC_MODE)
 #define PORT78_DSPI3_SOUT            (PORT_ALT2_FUNC_MODE)
 #define PORT78_DSPI1_CS5            (PORT_ALT3_FUNC_MODE)
 #define PORT78_FlexPWM1_B2            (PORT_ALT4_FUNC_MODE)
 #define PORT78_FlexPWM1_B2_IN            (PORT_INPUT1_MODE)
 #define PORT78_SIUL2_IRQ26            (PORT_INPUT2_MODE)
 #define PORT78_eTimer1_ETC5_IN            (PORT_INPUT3_MODE)
 #define PORT79_GPIO            (PORT_GPIO_MODE)
 #define PORT79_DSPI0_CS1            (PORT_ALT1_FUNC_MODE)
 #define PORT79_ENET0_TIMER1            (PORT_ALT3_FUNC_MODE)
 #define PORT79_SIUL2_IRQ27            (PORT_INPUT1_MODE)
 #define PORT79_DSPI3_SIN            (PORT_INPUT2_MODE)
 #define PORT80_GPIO            (PORT_GPIO_MODE)
 #define PORT80_FlexPWM0_A1            (PORT_ALT1_FUNC_MODE)
 #define PORT80_DSPI3_CS3            (PORT_ALT2_FUNC_MODE)
 #define PORT80_ENET0_MDC            (PORT_ALT3_FUNC_MODE)
 #define PORT80_eTimer0_ETC2_IN            (PORT_INPUT1_MODE)
 #define PORT80_SIUL2_IRQ28            (PORT_INPUT2_MODE)
 #define PORT80_FlexPWM0_A1_IN            (PORT_INPUT3_MODE)
 #define PORT83_GPIO            (PORT_GPIO_MODE)
 #define PORT83_DSPI0_CS6            (PORT_ALT1_FUNC_MODE)
 #define PORT83_DSPI3_CS2            (PORT_ALT3_FUNC_MODE)
 #define PORT83_ENET0_TIMER2            (PORT_ALT4_FUNC_MODE)
 #define PORT84_GPIO            (PORT_GPIO_MODE)
 #define PORT84_Nexus0_MDO3            (PORT_ALT2_FUNC_MODE)
 #define PORT84_DSPI3_CS1            (PORT_ALT3_FUNC_MODE)
 #define PORT85_GPIO            (PORT_GPIO_MODE)
 #define PORT85_Nexus0_MDO2            (PORT_ALT2_FUNC_MODE)
 #define PORT85_DSPI3_CS0            (PORT_ALT3_FUNC_MODE)
 #define PORT85_DSPI3_CS0_IN            (PORT_INPUT1_MODE)
 #define PORT86_GPIO            (PORT_GPIO_MODE)
 #define PORT86_Nexus0_MDO1            (PORT_ALT2_FUNC_MODE)
 #define PORT87_GPIO            (PORT_GPIO_MODE)
 #define PORT87_Nexus0_MCKO            (PORT_ALT2_FUNC_MODE)
 #define PORT88_GPIO            (PORT_GPIO_MODE)
 #define PORT88_Nexus0_MSEO_B1            (PORT_ALT2_FUNC_MODE)
 #define PORT89_GPIO            (PORT_GPIO_MODE)
 #define PORT89_Nexus0_MSEO_B0            (PORT_ALT2_FUNC_MODE)
 #define PORT90_GPIO            (PORT_GPIO_MODE)
 #define PORT90_Nexus0_EVTO_B            (PORT_ALT2_FUNC_MODE)
 #define PORT91_GPIO            (PORT_GPIO_MODE)
 #define PORT91_Nexus0_EVTI_IN            (PORT_ALT2_FUNC_MODE)
 #define PORT92_GPIO            (PORT_GPIO_MODE)
 #define PORT92_eTimer1_ETC3            (PORT_ALT1_FUNC_MODE)
 #define PORT92_FlexPWM1_A1            (PORT_ALT4_FUNC_MODE)
 #define PORT92_FlexPWM1_A1_IN            (PORT_INPUT1_MODE)
 #define PORT92_SIUL2_IRQ30            (PORT_INPUT2_MODE)
 #define PORT92_eTimer1_ETC3_IN            (PORT_INPUT3_MODE)
 #define PORT93_GPIO            (PORT_GPIO_MODE)
 #define PORT93_eTimer1_ETC4            (PORT_ALT1_FUNC_MODE)
 #define PORT93_FlexPWM1_B1            (PORT_ALT4_FUNC_MODE)
 #define PORT93_FlexPWM1_B1_IN            (PORT_INPUT1_MODE)
 #define PORT93_SIUL2_IRQ31            (PORT_INPUT2_MODE)
 #define PORT93_eTimer1_ETC4_IN            (PORT_INPUT3_MODE)
 #define PORT94_GPIO            (PORT_GPIO_MODE)
 #define PORT94_LIN1_TXD            (PORT_ALT1_FUNC_MODE)
 #define PORT94_CAN2_TXD            (PORT_ALT2_FUNC_MODE)
 #define PORT95_GPIO            (PORT_GPIO_MODE)
 #define PORT95_LIN1_RXD            (PORT_INPUT1_MODE)
 #define PORT95_CAN2_RXD            (PORT_INPUT2_MODE)
 #define PORT98_GPIO            (PORT_GPIO_MODE)
 #define PORT98_FlexPWM0_X2            (PORT_ALT1_FUNC_MODE)
 #define PORT98_DSPI1_CS1            (PORT_ALT2_FUNC_MODE)
 #define PORT98_FlexPWM0_X2_IN            (PORT_INPUT1_MODE)
 #define PORT99_GPIO            (PORT_GPIO_MODE)
 #define PORT99_FlexPWM0_A2            (PORT_ALT1_FUNC_MODE)
 #define PORT99_eTimer0_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT99_FlexPWM0_A2_IN            (PORT_INPUT2_MODE)
 #define PORT100_GPIO            (PORT_GPIO_MODE)
 #define PORT100_FlexPWM0_B2            (PORT_ALT1_FUNC_MODE)
 #define PORT100_eTimer0_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT100_FlexPWM0_B2_IN            (PORT_INPUT2_MODE)
 #define PORT101_GPIO            (PORT_GPIO_MODE)
 #define PORT101_FlexPWM0_X3            (PORT_ALT1_FUNC_MODE)
 #define PORT101_DSPI2_CS3            (PORT_ALT2_FUNC_MODE)
 #define PORT101_ENET0_TX_EN            (PORT_ALT3_FUNC_MODE)
 #define PORT101_FlexPWM0_X3_IN            (PORT_INPUT1_MODE)
 #define PORT102_GPIO            (PORT_GPIO_MODE)
 #define PORT102_FlexPWM0_A3            (PORT_ALT1_FUNC_MODE)
 #define PORT102_FlexPWM0_A3_IN            (PORT_INPUT1_MODE)
 #define PORT103_GPIO            (PORT_GPIO_MODE)
 #define PORT103_FlexPWM0_B3            (PORT_ALT1_FUNC_MODE)
 #define PORT103_LFAST_RX_POS            (PORT_ALT3_FUNC_MODE)
 #define PORT103_FlexPWM0_B3_IN            (PORT_INPUT1_MODE)
 #define PORT104_GPIO            (PORT_GPIO_MODE)
 #define PORT104_FlexRay_DBG0            (PORT_ALT1_FUNC_MODE)
 #define PORT104_DSPI0_CS1            (PORT_ALT2_FUNC_MODE)
 #define PORT104_ENET0_RMII_CLK            (PORT_ALT3_FUNC_MODE)
 #define PORT104_FlexPWM0_FAULT0            (PORT_INPUT1_MODE)
 #define PORT104_SIUL2_IRQ21            (PORT_INPUT2_MODE)
 #define PORT104_SENT0_RX0            (PORT_INPUT3_MODE)
 #define PORT104_ENET0_TX_CLK            (PORT_INPUT4_MODE)
 #define PORT105_GPIO            (PORT_GPIO_MODE)
 #define PORT105_FlexRay_DBG1            (PORT_ALT1_FUNC_MODE)
 #define PORT105_DSPI1_CS1            (PORT_ALT2_FUNC_MODE)
 #define PORT105_ENET0_TX_D0            (PORT_ALT3_FUNC_MODE)
 #define PORT105_FlexPWM0_FAULT1            (PORT_INPUT1_MODE)
 #define PORT105_SIUL2_IRQ29            (PORT_INPUT2_MODE)
 #define PORT105_SENT1_RX0            (PORT_INPUT3_MODE)
 #define PORT106_GPIO            (PORT_GPIO_MODE)
 #define PORT106_FlexRay_DBG2            (PORT_ALT1_FUNC_MODE)
 #define PORT106_DSPI2_CS3            (PORT_ALT2_FUNC_MODE)
 #define PORT106_ENET0_TX_D1            (PORT_ALT3_FUNC_MODE)
 #define PORT106_FlexPWM0_FAULT2            (PORT_INPUT1_MODE)
 #define PORT106_SENT0_RX1            (PORT_INPUT2_MODE)
 #define PORT107_GPIO            (PORT_GPIO_MODE)
 #define PORT107_FlexRay_DBG3            (PORT_ALT1_FUNC_MODE)
 #define PORT107_ENET0_TX_D3            (PORT_ALT3_FUNC_MODE)
 #define PORT107_FlexPWM0_FAULT3            (PORT_INPUT1_MODE)
 #define PORT107_SENT1_RX1            (PORT_INPUT2_MODE)
 #define PORT116_GPIO            (PORT_GPIO_MODE)
 #define PORT116_FlexPWM1_X0            (PORT_ALT1_FUNC_MODE)
 #define PORT116_eTimer2_ETC0            (PORT_ALT2_FUNC_MODE)
 #define PORT116_eTimer2_ETC0_IN            (PORT_INPUT1_MODE)
 #define PORT116_ENET0_CRS            (PORT_INPUT2_MODE)
 #define PORT117_GPIO            (PORT_GPIO_MODE)
 #define PORT117_FlexPWM1_A0            (PORT_ALT1_FUNC_MODE)
 #define PORT117_DSPI0_CS4            (PORT_ALT3_FUNC_MODE)
 #define PORT117_FlexPWM1_A0_IN            (PORT_INPUT1_MODE)
 #define PORT117_ENET0_COL            (PORT_INPUT2_MODE)
 #define PORT118_GPIO            (PORT_GPIO_MODE)
 #define PORT118_FlexPWM1_B0            (PORT_ALT1_FUNC_MODE)
 #define PORT118_DSPI0_CS5            (PORT_ALT3_FUNC_MODE)
 #define PORT118_FlexPWM1_B0_IN            (PORT_INPUT1_MODE)
 #define PORT119_GPIO            (PORT_GPIO_MODE)
 #define PORT119_FlexPWM1_X1            (PORT_ALT1_FUNC_MODE)
 #define PORT119_eTimer2_ETC1            (PORT_ALT2_FUNC_MODE)
 #define PORT119_ENET0_MDIO            (PORT_ALT3_FUNC_MODE)
 #define PORT119_eTimer2_ETC1_IN            (PORT_INPUT2_MODE)
 #define PORT120_GPIO            (PORT_GPIO_MODE)
 #define PORT120_FlexPWM1_A1            (PORT_ALT1_FUNC_MODE)
 #define PORT120_DSPI0_CS6            (PORT_ALT3_FUNC_MODE)
 #define PORT120_FlexPWM1_A1_IN            (PORT_INPUT1_MODE)
 #define PORT120_ENET0_RX_D2            (PORT_INPUT2_MODE)
 #define PORT121_GPIO            (PORT_GPIO_MODE)
 #define PORT121_FlexPWM1_B1            (PORT_ALT1_FUNC_MODE)
 #define PORT121_DSPI0_CS7            (PORT_ALT3_FUNC_MODE)
 #define PORT121_FlexPWM1_B1_IN            (PORT_INPUT1_MODE)
 #define PORT122_GPIO            (PORT_GPIO_MODE)
 #define PORT122_FlexPWM1_X2            (PORT_ALT1_FUNC_MODE)
 #define PORT122_eTimer2_ETC2            (PORT_ALT2_FUNC_MODE)
 #define PORT122_eTimer2_ETC2_IN            (PORT_INPUT1_MODE)
 #define PORT123_GPIO            (PORT_GPIO_MODE)
 #define PORT123_FlexPWM1_A2            (PORT_ALT1_FUNC_MODE)
 #define PORT123_FlexPWM1_A2_IN            (PORT_INPUT1_MODE)
 #define PORT124_GPIO            (PORT_GPIO_MODE)
 #define PORT124_FlexPWM1_B2            (PORT_ALT1_FUNC_MODE)
 #define PORT124_FlexPWM1_B2_IN            (PORT_INPUT1_MODE)
 #define PORT125_GPIO            (PORT_GPIO_MODE)
 #define PORT125_FlexPWM1_X3            (PORT_ALT1_FUNC_MODE)
 #define PORT125_eTimer2_ETC3            (PORT_ALT2_FUNC_MODE)
 #define PORT125_eTimer2_ETC3_IN            (PORT_INPUT1_MODE)
 #define PORT126_GPIO            (PORT_GPIO_MODE)
 #define PORT126_FlexPWM1_A3            (PORT_ALT1_FUNC_MODE)
 #define PORT126_eTimer2_ETC4            (PORT_ALT2_FUNC_MODE)
 #define PORT126_eTimer2_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT127_GPIO            (PORT_GPIO_MODE)
 #define PORT127_FlexPWM1_B3            (PORT_ALT1_FUNC_MODE)
 #define PORT127_eTimer2_ETC5            (PORT_ALT2_FUNC_MODE)
 #define PORT127_eTimer2_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT128_GPIO            (PORT_GPIO_MODE)
 #define PORT128_eTimer2_ETC0            (PORT_ALT1_FUNC_MODE)
 #define PORT128_DSPI0_CS4            (PORT_ALT2_FUNC_MODE)
 #define PORT128_FlexPWM1_FAULT0            (PORT_INPUT1_MODE)
 #define PORT128_eTimer2_ETC0_IN            (PORT_INPUT2_MODE)
 #define PORT129_GPIO            (PORT_GPIO_MODE)
 #define PORT129_eTimer2_ETC1            (PORT_ALT1_FUNC_MODE)
 #define PORT129_DSPI0_CS5            (PORT_ALT2_FUNC_MODE)
 #define PORT129_FlexPWM1_FAULT1            (PORT_INPUT1_MODE)
 #define PORT129_eTimer2_ETC1_IN            (PORT_INPUT2_MODE)
 #define PORT129_ENET0_RX_ER            (PORT_INPUT3_MODE)
 #define PORT130_GPIO            (PORT_GPIO_MODE)
 #define PORT130_eTimer2_ETC2            (PORT_ALT1_FUNC_MODE)
 #define PORT130_DSPI0_CS6            (PORT_ALT2_FUNC_MODE)
 #define PORT130_FlexPWM1_FAULT2            (PORT_INPUT1_MODE)
 #define PORT130_eTimer2_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT131_GPIO            (PORT_GPIO_MODE)
 #define PORT131_eTimer2_ETC3            (PORT_ALT1_FUNC_MODE)
 #define PORT131_DSPI0_CS7            (PORT_ALT2_FUNC_MODE)
 #define PORT131_CTU0_EXT_TRIG            (PORT_ALT3_FUNC_MODE)
 #define PORT131_ENET0_TIMER0            (PORT_ALT4_FUNC_MODE)
 #define PORT131_FlexPWM1_FAULT3            (PORT_INPUT1_MODE)
 #define PORT131_eTimer2_ETC3_IN            (PORT_INPUT2_MODE)
 #define PORT132_GPIO            (PORT_GPIO_MODE)
 #define PORT132_Nexus0_NEX_RDY_B            (PORT_ALT2_FUNC_MODE)
 #define PORT133_GPIO            (PORT_GPIO_MODE)
 #define PORT133_CAN2_TXD            (PORT_ALT1_FUNC_MODE)
 #define PORT133_LFAST_PH0_NEG            (PORT_ALT3_FUNC_MODE)
 #define PORT134_GPIO            (PORT_GPIO_MODE)
 #define PORT134_LFAST_RX_NEG            (PORT_ALT3_FUNC_MODE)
 #define PORT134_CAN2_RXD            (PORT_INPUT1_MODE)
 #define PORT135_GPIO            (PORT_GPIO_MODE)
 #define PORT135_LFAST_REF_CLK            (PORT_ALT1_FUNC_MODE)
 #define PORT135_SENT0_RX0            (PORT_INPUT1_MODE)
 #define PORT136_GPIO            (PORT_GPIO_MODE)
 #define PORT136_SENT1_RX0            (PORT_INPUT1_MODE)
 #define PORT137_GPIO            (PORT_GPIO_MODE)
 #define PORT137_eTimer2_ETC4            (PORT_ALT1_FUNC_MODE)
 #define PORT137_eTimer2_ETC4_IN            (PORT_INPUT1_MODE)
 #define PORT138_GPIO            (PORT_GPIO_MODE)
 #define PORT138_eTimer2_ETC5            (PORT_ALT1_FUNC_MODE)
 #define PORT138_eTimer2_ETC5_IN            (PORT_INPUT1_MODE)
 #define PORT139_GPIO            (PORT_GPIO_MODE)
 #define PORT139_SENT0_RX1            (PORT_INPUT1_MODE)
 #define PORT140_GPIO            (PORT_GPIO_MODE)
 #define PORT140_SENT1_RX1            (PORT_INPUT1_MODE)
 #define PORT141_GPIO            (PORT_GPIO_MODE)
 #define PORT141_CTU1_EXT_TRIG            (PORT_ALT1_FUNC_MODE)
 #define PORT142_GPIO            (PORT_GPIO_MODE)
 #define PORT142_DSPI3_CS0            (PORT_ALT1_FUNC_MODE)
 #define PORT142_DSPI3_CS0_IN            (PORT_INPUT1_MODE)
 #define PORT143_GPIO            (PORT_GPIO_MODE)
 #define PORT143_DSPI3_SCK            (PORT_ALT1_FUNC_MODE)
 #define PORT143_DSPI3_SCK_IN            (PORT_INPUT1_MODE)
 #define PORT144_GPIO            (PORT_GPIO_MODE)
 #define PORT144_DSPI3_SOUT            (PORT_ALT1_FUNC_MODE)
 #define PORT145_GPIO            (PORT_GPIO_MODE)
 #define PORT145_DSPI3_SIN            (PORT_INPUT1_MODE)
 #define PORT146_GPIO            (PORT_GPIO_MODE)
 #define PORT146_DSPI3_CS1            (PORT_ALT1_FUNC_MODE)
 #define PORT147_GPIO            (PORT_GPIO_MODE)
 #define PORT147_DSPI3_CS2            (PORT_ALT1_FUNC_MODE)
 #define PORT148_GPIO            (PORT_GPIO_MODE)
 #define PORT148_DSPI3_CS3            (PORT_ALT1_FUNC_MODE)
 #define PORT148_CTU1_EXT_IN            (PORT_INPUT1_MODE)
 #define PORT149_GPI            (PORT_GPIO_MODE)
 #define PORT149_ADC2_ADC3_AN0            (PORT_ANALOG_INPUT_MODE)
 #define PORT149_SENT0_RX1            (PORT_INPUT1_MODE)
 #define PORT150_GPI            (PORT_GPIO_MODE)
 #define PORT150_ADC2_ADC3_AN1            (PORT_ANALOG_INPUT_MODE)
 #define PORT150_SENT1_RX1            (PORT_INPUT1_MODE)
 #define PORT151_GPI            (PORT_GPIO_MODE)
 #define PORT151_ADC2_ADC3_AN2            (PORT_ANALOG_INPUT_MODE)
 #define PORT152_GPIO            (PORT_GPIO_MODE)
 #define PORT152_eTimer2_ETC4            (PORT_ALT1_FUNC_MODE)
 #define PORT152_eTimer2_ETC2            (PORT_ALT2_FUNC_MODE)
 #define PORT152_CAN2_RXD            (PORT_INPUT1_MODE)
 #define PORT152_eTimer2_ETC2_IN            (PORT_INPUT2_MODE)
 #define PORT152_eTimer2_ETC4_IN            (PORT_INPUT3_MODE)
 #define PORT153_GPIO            (PORT_GPIO_MODE)
 #define PORT153_eTimer2_ETC5            (PORT_ALT1_FUNC_MODE)
 #define PORT153_Nexus0_NEX_RDY_B            (PORT_ALT2_FUNC_MODE)
 #define PORT153_CTU1_EXT_IN            (PORT_INPUT1_MODE)
 #define PORT153_eTimer2_ETC5_IN            (PORT_INPUT2_MODE)
 #define PORT153_ENET0_RX_D3            (PORT_INPUT3_MODE)


/**
* @brief Enable/Disable Development Error Detection
*
* @implements   PORT_DEV_ERROR_DETECT_define
*/
#define PORT_DEV_ERROR_DETECT           (STD_OFF)

/**
* @brief Use/remove Port_SetPinDirection function from the compiled driver
*
* @implements   PORT_SET_PIN_DIRECTION_API_define
*/

#define PORT_SET_PIN_DIRECTION_API      (STD_ON)


/**
* @brief Use/remove Port_SetPinMode function from the compiled driver
*
* @implements   PORT_SET_PIN_MODE_API_define
*/

#define PORT_SET_PIN_MODE_API           (STD_ON)


/**
* @brief Use/remove Port_GetVersionInfo function from the compiled driver
*
* @implements   PORT_VERSION_INFO_API_define
*/
#define PORT_VERSION_INFO_API           (STD_OFF)

/**
* @brief Port Pin symbolic names
* @details Get All Symbolic Names from configuration tool
*
*
*/
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SIGeFD2048  0
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_A1  1
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ABS_1  2
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ABS_2  3
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_FAB  4
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nLOGSPICS_A  5
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_LOGSPICLK_B  6
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_LOGDATA1  7
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPI1SIN  8
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETIMER2CH5  9
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nSiGeSPICS  10
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeSPICLK  11
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeSPIDOUT  12
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeSPIDIN  13
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN1TX  14
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN1RX  15
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN0TX  16
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN0RX  17
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nMICROPSUWAKE  18
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SUPPLYHOLDON  19
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_JTAGTDO  20
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_JTAGTDI  21
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CLKOUT  22
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_RX0AAF  23
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B8  24
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B9  25
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B10  26
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B11  27
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B12  28
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_RX1AAF  29
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V6V0PWRGD_A  30
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_B15  31
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_C0  32
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_C1  33
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_VPIMON  34
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nLOGSPICS_B  35
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_LOGSPICLK_C  36
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_LOGDATA0  37
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPI0SIN  38
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeRAMPDIRIN  39
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETIMER0CH4  40
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETIMER0CH5  41
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeFSKSYNC_A  42
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CTU0EXTTRG  43
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAEN  44
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CATX  45
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CARX  46
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CBRX  47
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CBTX  48
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CBEN  49
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXD_1  50
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXD_0  51
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXDV  52
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXCLK  53
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V6V0SYNCMON  54
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXD_2  55
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SYNCFILT  56
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V5VAEN  57
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeFMCWSYNC  58
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V3V3AMON  59
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V5VAMON  60
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V1V2MON  61
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V3V3MON_A  62
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V6V0MON  63
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V5VCANMON  64
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V3V3MON_B  65
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_E10  66
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_E11  67
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V4V1MON  68
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETMR0ETC5  69
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V3V3AEN  70
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_E15  71
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHMDC  72
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICROBOOT  73
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MDO_3  74
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MDO_2  75
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MDO_1  76
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MCKO  77
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nMSEO1  78
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nMSEO0  79
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nEVTO  80
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nEVTI  81
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETMR1ETC3  82
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_YRSELFTEST  83
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_YRDIAG  84
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_RXEN_0  85
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V4V1SYNCMON  86
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPAREPSUSYNC  87
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_G4  88
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXEN  89
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_G6  90
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_G7  91
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXCLK  92
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXD_0  93
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXD_1  94
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHTXD_3  95
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHCRS  96
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHCOL  97
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_H6  98
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHMDIO  99
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXD_2  100
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICRORXEN_1  101
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICRORXEN_2  102
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICRORXEN_3  103
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICROIFEN_0  104
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICROIFEN_1  105
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICROIFEN_2  106
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_MICROIFEN_3  107
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_I0  108
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXERR  109
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETIMER2CH2  110
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_TIMER0  111
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nNEXUSRDY  112
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN2TX  113
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CAN2RX  114
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nCAN0ENMON  115
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nCAN1ENMON  116
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETMR2ETC4  117
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETMR2ETC5  118
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nSiGeRESET  119
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V6V0PWRGD  120
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_CTU1EXTTRIG  121
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_nSPI3CS  122
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPI3SCLK  123
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPI3SOUT  124
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SPI3SIN  125
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_J2  126
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeTXSEL_1  127
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_SiGeFSKSYNC_B  128
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_J5  129
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_RX2AAF  130
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_RX3AAF  131
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_V6V0PWRGD_B  132
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_PortContainer_0_ETHRXD3  133


/**
* @brief Number of INMUX registers
* @details Platform constant
*/
#define PORT_NMBR_INMUX_REGS_U16    ((uint16)234)
/**
* @brief Number of available pad modes options
* @details Platform constant
*/
#define PAD_MODE_OPTIONS_U8         ((uint8)11)
/**
* @brief Number of pad 16 blocks
* @details Platform constant
*/
#define PAD_16BLOCK_NO_U8           ((uint8)10)
/**
 * @brief The last supported pin number
 */
#define PORT_MAX_PIN_PACKAGE_U16    ((uint16)153)



/**
* @brief Port driver Pre-Compile configuration switch
*/
#define PORT_PRECOMPILE_SUPPORT  (STD_ON)

/**
* @brief Declaration of configuration settings for PC configuration
*/
#define PORT_CONFIG_PC
/**
* @brief The maximum number of configured pins
*/
#define PORT_MAX_CONFIGURED_PADS_U16   ((uint16)134)
/**
* @brief The number of configured pins
*/

/**
 * @brief Number of UnUsed pin array
*/
#define PORT_MAX_UNUSED_PADS_U16   (0U)


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief   Structure needed by @p Port_Init().
* @details The structure @p Port_ConfigType is a type for the external data
*          structure containing the initialization data for the PORT Driver.
* @note    The user must use the symbolic names defined in the configuration
*          tool.
*
* @implements Port_ConfigType_struct
*
* @api
*/
typedef struct
{
    VAR(uint16, PORT_VAR) u16NumPins;                                                     /**< @brief Number of used pads (to be configured) */
    VAR(uint16, PORT_VAR) u16NumUnusedPins;                                               /**< @brief Number of unused pads */
    P2CONST(uint16, PORT_VAR, PORT_APPL_CONST) au16UnusedPads;                            /**< @brief Unused pad id's array */
    P2CONST(Port_Siul2_UnUsedPinConfigType, PORT_VAR, PORT_APPL_CONST) pUnusedPadConfig;  /**< @brief Unused pad configuration */
    P2CONST(Port_Siul2_PinConfigType, PORT_VAR, PORT_APPL_CONST) pUsedPadConfig;          /**< @brief Used pads data configuration */
    P2CONST(Port_Siul2_PadSelConfigType, PORT_VAR, PORT_APPL_CONST) pPadSelConfig;        /**< @brief Used pads INMUX configuration */
} Port_ConfigType;

/**
* @brief Settings for a INMUX register
* @details The structure @p Port_InMuxSettingType manages ExtraFunctions PinMode.
* 
* @implements Port_INMUXSettingType_struct
*
* @api
*/
typedef struct
{
    VAR(uint16,PORT_VAR) u16InMuxId;   /**< @brief The id of the INMUX register to be configured */
    VAR(uint8, PORT_VAR) u8InMuxCode;  /**< @brief The value of the INMUX reg for signal allocation */
} Port_InMuxSettingType;

/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"



/**
* @brief External declaration of the Port configuration structure for pre-compiled mode
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_ConfigType, PORT_CONST) Port_ConfigPC;

/**
* @brief Settings for Pins not initialized
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_Siul2_UnUsedPinConfigType, PORT_CONST) Port_UnUsedPin;

#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief External declaration of the Port pin description array
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(uint16, PORT_CONST) Port_au16PinDescription[11][10];
/**
* @brief External declaration of the Port pad inmux functionality settings array
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_InMuxSettingType,PORT_CONST) Port_aPadFunctInMuxSettings[212];

/**
* @brief External declaration of the Port pad inmux functionality settings index array
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(uint16,PORT_CONST) Port_au16PadFunctInMuxIndex[154];
#endif

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#define PORT_START_SEC_CODE
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#define PORT_STOP_SEC_CODE
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* PORT_CFG_H */

/** @} */

/* End of File */
