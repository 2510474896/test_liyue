/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Compiler_Cfg.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:25CST $

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
*   @file    Compiler_Cfg.h
*   @implements     Compiler_Cfg.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - Module specific memory and pointer classes
*   @details The file Compiler_Cfg.h contains the module specific parameters (ptrclass and 
*            memclass) that are passed to the macros defined in Compiler.h
*            This file contains sample code only. It is not part of the production code deliverables
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

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused. The driver needs to use defines starting with letter E.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** 
@{
* @brief ADC memory and pointer classes.
*/
#define ADC_CODE
#define ADC_CONST
#define ADC_APPL_DATA
#define ADC_APPL_CONST
#define ADC_APPL_CODE
#define ADC_CALLOUT_CODE
#define ADC_VAR_NOINIT
#define ADC_VAR_POWER_ON_INIT
#define ADC_VAR_FAST
#define ADC_VAR
/**@}*/

/** 
@{
* @brief CAN memory and pointer classes.
*/
#define CAN_CODE
#define CAN_CONST
#define CAN_APPL_DATA
#define CAN_APPL_CONST
#define CAN_APPL_CODE
#define CAN_CALLOUT_CODE
#define CAN_VAR_NOINIT
#define CAN_VAR_POWER_ON_INIT
#define CAN_VAR_FAST
#define CAN_VAR
/**@}*/

/** 
@{
* @brief CANIF memory and pointer classes.
*/
#define CANIF_CODE
#define CANIF_CONST
#define CANIF_APPL_DATA
#define CANIF_APPL_CONST
#define CANIF_APPL_CODE
#define CANIF_CALLOUT_CODE
#define CANIF_VAR_NOINIT
#define CANIF_VAR_POWER_ON_INIT
#define CANIF_VAR_FAST
#define CANIF_VAR
/**@}*/

/** 
@{
* @brief CRCU memory and pointer classes.
*/
#define CRCU_CODE
#define CRCU_CONST
#define CRCU_APPL_DATA
#define CRCU_APPL_CONST
#define CRCU_APPL_CODE
#define CRCU_CALLOUT_CODE
#define CRCU_VAR_NOINIT
#define CRCU_VAR_POWER_ON_INIT
#define CRCU_VAR_FAST
#define CRCU_VAR
/**@}*/
/** 
@{
* @brief DEM memory and pointer classes.
*/
#define DEM_CODE
#define DEM_CONST
#define DEM_APPL_DATA
#define DEM_APPL_CONST
#define DEM_APPL_CODE
#define DEM_CALLOUT_CODE
#define DEM_VAR_NOINIT
#define DEM_VAR_POWER_ON_INIT
#define DEM_VAR_FAST
#define DEM_VAR
/**@}*/

/** 
@{
* @brief DET memory and pointer classes.
*/
#define DET_CODE
#define DET_CONST
#define DET_APPL_DATA
#define DET_APPL_CONST
#define DET_APPL_CODE
#define DET_CALLOUT_CODE
#define DET_VAR_NOINIT
#define DET_VAR_POWER_ON_INIT
#define DET_VAR_FAST
#define DET_VAR
/**@}*/

/** 
@{
* @brief DIO memory and pointer classes.
*/
#define DIO_CODE
#define DIO_CONST
#define DIO_APPL_DATA
#define DIO_APPL_CONST
#define DIO_APPL_CODE
#define DIO_CALLOUT_CODE
#define DIO_VAR_NOINIT
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_FAST
#define DIO_VAR
/**@}*/

/** 
@{
* @brief ETH memory and pointer classes.
*/

#define ETH_CODE
#define ETH_CONST
#define ETH_APPL_DATA
#define ETH_APPL_CONST
#define ETH_APPL_CODE
#define ETH_CALLOUT_CODE
#define ETH_VAR_NOINIT
#define ETH_VAR_POWER_ON_INIT
#define ETH_VAR_FAST
#define ETH_VAR
/**@}*/



/** 
@{
* @brief FEE memory and pointer classes.
*/
#define FEE_CODE
#define FEE_CONST
#define FEE_APPL_DATA
#define FEE_APPL_CONST
#define FEE_APPL_CODE
#define FEE_CALLOUT_CODE
#define FEE_VAR_NOINIT
#define FEE_VAR_POWER_ON_INIT
#define FEE_VAR_FAST
#define FEE_VAR
/**@}*/

/** 
@{
* @brief FLS memory and pointer classes.
*/
#define FLS_CODE
#define FLS_CONST
#define FLS_APPL_DATA
#define FLS_APPL_CONST
#define FLS_APPL_CODE
#define FLS_CALLOUT_CODE
#define FLS_VAR_NOINIT
#define FLS_VAR_POWER_ON_INIT
#define FLS_VAR_FAST
#define FLS_VAR
/**@}*/

/** 
@{
* @brief FlexRay memory and pointer classes.
*/
#define FR_CODE
#define FR_CONST
#define FR_APPL_DATA
#define FR_APPL_CONST
#define FR_APPL_CODE
#define FR_CALLOUT_CODE
#define FR_VAR_NOINIT
#define FR_VAR_POWER_ON_INIT
#define FR_VAR_FAST
#define FR_VAR
/**@}*/

/** 
@{
* @brief GPT memory and pointer classes.
*/
#define GPT_CODE
#define GPT_CONST
#define GPT_APPL_DATA
#define GPT_APPL_CONST
#define GPT_APPL_CODE
#define GPT_CALLOUT_CODE
#define GPT_VAR_NOINIT
#define GPT_VAR_POWER_ON_INIT
#define GPT_VAR_FAST
#define GPT_VAR
/**@}*/

/** 
@{
* @brief ICU memory and pointer classes.
*/
#define ICU_CODE
#define ICU_CONST
#define ICU_APPL_DATA
#define ICU_APPL_CONST
#define ICU_APPL_CODE
#define ICU_CALLOUT_CODE
#define ICU_VAR_NOINIT
#define ICU_VAR_POWER_ON_INIT
#define ICU_VAR_FAST
#define ICU_VAR
/**@}*/

/** 
@{
* @brief LIN memory and pointer classes.
*/
#define LIN_CODE
#define LIN_CONST
#define LIN_APPL_DATA
#define LIN_APPL_CONST
#define LIN_APPL_CODE
#define LIN_CALLOUT_CODE
#define LIN_VAR_NOINIT
#define LIN_VAR_POWER_ON_INIT
#define LIN_VAR_FAST
#define LIN_VAR
/**@}*/

/** 
@{
* @brief MCEM memory and pointer classes.
*/
#define MCEM_CODE
#define MCEM_CONST
#define MCEM_APPL_DATA
#define MCEM_APPL_CONST
#define MCEM_APPL_CODE
#define MCEM_CALLOUT_CODE
#define MCEM_VAR_NOINIT
#define MCEM_VAR_POWER_ON_INIT
#define MCEM_VAR_FAST
#define MCEM_VAR
/**@}*/

/** 
@{
* @brief MCL memory and pointer classes.
*/
#define MCL_CODE
#define MCL_CONST
#define MCL_APPL_DATA
#define MCL_APPL_CONST
#define MCL_APPL_CODE
#define MCL_CALLOUT_CODE
#define MCL_VAR_NOINIT
#define MCL_VAR_POWER_ON_INIT
#define MCL_VAR_FAST
#define MCL_VAR
/**@}*/

/** 
@{
* @brief MCU memory and pointer classes.
*/
#define MCU_CODE
#define MCU_CONST
#define MCU_APPL_DATA
#define MCU_APPL_CONST
#define MCU_APPL_CODE
#define MCU_CALLOUT_CODE
#define MCU_VAR_NOINIT
#define MCU_VAR_POWER_ON_INIT
#define MCU_VAR_FAST
#define MCU_VAR
/**@}*/

/** 
@{
* @brief PORT memory and pointer classes.
*/
#define PORT_CODE
#define PORT_CONST
#define PORT_APPL_DATA
#define PORT_APPL_CONST
#define PORT_APPL_CODE
#define PORT_CALLOUT_CODE
#define PORT_VAR_NOINIT
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_FAST
#define PORT_VAR
/**@}*/

/** 
@{
* @brief PWM memory and pointer classes.
*/
#define PWM_CODE
#define PWM_CONST
#define PWM_APPL_DATA
#define PWM_APPL_CONST
#define PWM_APPL_CODE
#define PWM_CALLOUT_CODE
#define PWM_VAR_NOINIT
#define PWM_VAR_POWER_ON_INIT
#define PWM_VAR_FAST
#define PWM_VAR
/**@}*/


/** 
@{
* @brief RamTST memory and pointer classes.
*/
#define RAMTST_CODE
#define RAMTST_CONST
#define RAMTST_APPL_DATA
#define RAMTST_APPL_CONST
#define RAMTST_APPL_CODE
#define RAMTST_CALLOUT_CODE
#define RAMTST_VAR_NOINIT
#define RAMTST_VAR_POWER_ON_INIT
#define RAMTST_VAR_FAST
#define RAMTST_VAR
/**@}*/

/** 
@{
* @brief SchM memory and pointer classes.
*/
#define SCHM_CODE
#define SCHM_CONST
#define SCHM_APPL_DATA
#define SCHM_APPL_CONST
#define SCHM_APPL_CODE
#define SCHM_CALLOUT_CODE
#define SCHM_VAR_NOINIT
#define SCHM_VAR_POWER_ON_INIT
#define SCHM_VAR_FAST
#define SCHM_VAR
/**@}*/

/** 
@{
* @brief SPI memory and pointer classes.
*/
#define SPI_CODE
#define SPI_CONST
#define SPI_APPL_DATA
#define SPI_APPL_CONST
#define SPI_APPL_CODE
#define SPI_CALLOUT_CODE
#define SPI_VAR_NOINIT
#define SPI_VAR_POWER_ON_INIT
#define SPI_VAR_FAST
#define SPI_VAR
/**@}*/

/** 
@{
* @brief WDG memory and pointer classes.
*/
#define WDG_CODE
#define WDG_CONST
#define WDG_APPL_DATA
#define WDG_APPL_CONST
#define WDG_APPL_CODE
#define WDG_CALLOUT_CODE
#define WDG_VAR_NOINIT
#define WDG_VAR_POWER_ON_INIT
#define WDG_VAR_FAST
#define WDG_VAR
/**@}*/

/** 
@{
* @brief WDGIF memory and pointer classes.
*/
#define WDGIF_CODE
#define WDGIF_CONST
#define WDGIF_APPL_DATA
#define WDGIF_APPL_CONST
#define WDGIF_APPL_CODE
#define WDGIF_CALLOUT_CODE
#define WDGIF_VAR_NOINIT
#define WDGIF_VAR_POWER_ON_INIT
#define WDGIF_VAR_FAST
#define WDGIF_VAR
/**@}*/

/** 
* @brief Define for ComStack Data.
*/
#define AUTOSAR_COMSTACKDATA

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMPILER_CFG_H */

/** @} */
