/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Dio_Cfg.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:18CST $

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
*   @file    Dio_Cfg.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Dio configuration header.
*   @details This file is the Autosar DIO driver configuration header. This
*            file is automatically generated, do not modify manually.
*
*   @addtogroup DIO_CFG
*   @{
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

#ifndef DIO_CFG_H
#define DIO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_Cfg_H_REF_1
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external
*          identifiers. The defines are ok. 
* 
* @section Dio_Cfg_H_REF_2
*           Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
*           Precautions shall be taken in order to prevent the contents of a header file 
*           being included twice. This is not a violation since all header files are 
*           protected against multiple inclusions
*
* @section Dio_C_REF_3
*          Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope 
*          if they are only accessed from within a single function. 
*          This violation can not be avoided because it is an AUTOSAR requirement
*
* @section [global]
*           Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not
*           rely on the significance of more than 31 characters. The used compilers use more than
*           31 chars for identifiers.
**/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
/**
* @violates @ref Dio_Cfg_H_REF_2 MISRA 2004 Required Rule 19.15, Repeated include file
*/

#include "Dio_EnvCfg.h"

/**
 *     @file       Dio_Cfg.h
 *     @implements Dio_Cfg.h_Artifact
 * */

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID_CFG                   43
#define DIO_AR_RELEASE_MAJOR_VERSION_CFG    4
#define DIO_AR_RELEASE_MINOR_VERSION_CFG    0
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_REVISION_VERSION_CFG 3
#define DIO_SW_MAJOR_VERSION_CFG            1
#define DIO_SW_MINOR_VERSION_CFG            0
#define DIO_SW_PATCH_VERSION_CFG            0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Dio_EnvCfg.h version check start */
#if ((DIO_AR_RELEASE_MAJOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MAJOR_VERSION) ||   \
     (DIO_AR_RELEASE_MINOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MINOR_VERSION) ||   \
     (DIO_AR_RELEASE_REVISION_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_REVISION_VERSION)\
    )
    #error "AUTOSAR Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_CFG != DIO_ENVCFG_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_CFG != DIO_ENVCFG_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_CFG != DIO_ENVCFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_VENDOR_ID_CFG != DIO_ENVCFG_VENDOR_ID))
    #error "VENDOR ID for Dio_Cfg.h and Dio_EnvCfg.h is different"
#endif
/* Dio_EnvCfg.h version check end */
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/**
* @brief          Enable or Disable Development Error Detection.
*
* @implements     DIO_DEV_ERROR_DETECT_define
* @api
*/
#define DIO_DEV_ERROR_DETECT    (STD_OFF)

/**
* @brief          Function @p Dio_GetVersionInfo() enable switch.
*
* @implements DIO_VERSION_INFO_API_define
* @api
*/
#define DIO_VERSION_INFO_API    (STD_OFF)

/**
* @brief          Function @p Dio_FlipChannel() enable switch.
*
* @api
*/
#define DIO_FLIP_CHANNEL_API    (STD_ON)

/**
* @brief          Function @p Dio_MaskedWritePort() enable switch.
*
* @api
*/
#define DIO_MASKEDWRITEPORT_API (STD_OFF)

/**
* @brief          Reversed port functionality enable switch.
*
* @implements DIO_REVERSEPORTBITS_define
* @api
*/
#define DIO_REVERSEPORTBITS     (STD_OFF)

/**
* @brief          Undefined pins masking enable switch.
*
* @api
*/
#define DIO_READZERO_UNDEFINEDPORTS (STD_ON)


/**
* @brief          Number of implemented ports.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_PORTS_U16   ((uint16)0xa)

/**
* @brief          Number of implemented ports.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_PER_PORT_U16   ((uint16)(sizeof(Dio_PortLevelType) * 0x8U))

/**
* @brief          Number of channels available on the implemented ports.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_U16    ((uint16)(DIO_NUM_PORTS_U16 * DIO_NUM_CHANNELS_PER_PORT_U16))

/**
* @brief          Mask representing no available channels on a port.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NO_AVAILABLE_CHANNELS_U16   ((Dio_PortLevelType)0x0U)

/**
* @brief          Mask representing the maximum valid offset for a channel group.
*
* @note           Used for channel group validation.
*
* @api
*/
#define DIO_MAX_VALID_OFFSET_U8 ((uint8)0xFU)

/**
*   @brief   Enables or disables the access to a hardware register from user mode
*            USER_MODE_SOFT_LOCKING:        All reads to hw registers will be done via REG_PROT, user mode access
*            SUPERVISOR_MODE_SOFT_LOCKING:  Locks the access to the registers only for supervisor mode
*
*   @note    Currently, no register protection mechanism is used for Dio driver.
*/
#define DIO_USER_MODE_SOFT_LOCKING  (STD_OFF)

/**
* @brief          Dio driver Pre-Compile configuration switch.
*
* @api
*/
#define DIO_PRECOMPILE_SUPPORT


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief          Symbolic name for the configuration Dio_ConfigPC.
*
*/
#define Dio_ConfigPC    (DioConfig_0)  

/* ========== DioConfig_0 ========== */

/* ---------- DioPort_A ---------- */

/**
* @brief          Symbolic name for the port DioPort_A.
*
*/
#define DioConf_DioPort_DioPort_A  ((uint8)0x00U)

/**
* @brief          Symbolic name for the channel SIGeFD2048.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SIGeFD2048 ((uint8)0x00U)

/**
* @brief          Symbolic name for the channel A1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_A1 ((uint8)0x01U)

/**
* @brief          Symbolic name for the channel ABS_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ABS_1 ((uint8)0x02U)

/**
* @brief          Symbolic name for the channel ABS_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ABS_2 ((uint8)0x03U)

/**
* @brief          Symbolic name for the channel FAB.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_FAB ((uint8)0x04U)

/**
* @brief          Symbolic name for the channel nLOGSPICS_A.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nLOGSPICS_A ((uint8)0x05U)

/**
* @brief          Symbolic name for the channel LOGSPICLK_B.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LOGSPICLK_B ((uint8)0x06U)

/**
* @brief          Symbolic name for the channel LOGDATA1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LOGDATA1 ((uint8)0x07U)

/**
* @brief          Symbolic name for the channel SPI1SIN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPI1SIN ((uint8)0x08U)

/**
* @brief          Symbolic name for the channel ETIMER2CH5.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETIMER2CH5 ((uint8)0x09U)

/**
* @brief          Symbolic name for the channel nSiGeSPICS.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nSiGeSPICS ((uint8)0x0aU)

/**
* @brief          Symbolic name for the channel SiGeSPICLK.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeSPICLK ((uint8)0x0bU)

/**
* @brief          Symbolic name for the channel SiGeSPIDOUT.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeSPIDOUT ((uint8)0x0cU)

/**
* @brief          Symbolic name for the channel SiGeSPIDIN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeSPIDIN ((uint8)0x0dU)

/**
* @brief          Symbolic name for the channel CAN1TX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN1TX ((uint8)0x0eU)

/**
* @brief          Symbolic name for the channel CAN1RX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN1RX ((uint8)0x0fU)

/* ---------- DioPort_B ---------- */

/**
* @brief          Symbolic name for the port DioPort_B.
*
*/
#define DioConf_DioPort_DioPort_B  ((uint8)0x01U)

/**
* @brief          Symbolic name for the channel CAN0TX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN0TX ((uint8)0x10U)

/**
* @brief          Symbolic name for the channel CAN0RX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN0RX ((uint8)0x11U)

/**
* @brief          Symbolic name for the channel nMICROPSUWAKE.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nMICROPSUWAKE ((uint8)0x12U)

/**
* @brief          Symbolic name for the channel SUPPLYHOLDON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SUPPLYHOLDON ((uint8)0x13U)

/**
* @brief          Symbolic name for the channel JTAGTDO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_JTAGTDO ((uint8)0x14U)

/**
* @brief          Symbolic name for the channel JTAGTDI.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_JTAGTDI ((uint8)0x15U)

/**
* @brief          Symbolic name for the channel CLKOUT.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CLKOUT ((uint8)0x16U)

/**
* @brief          Symbolic name for the channel RX0AAF.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RX0AAF ((uint8)0x17U)

/**
* @brief          Symbolic name for the channel B8.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B8 ((uint8)0x18U)

/**
* @brief          Symbolic name for the channel B9.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B9 ((uint8)0x19U)

/**
* @brief          Symbolic name for the channel B10.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B10 ((uint8)0x1aU)

/**
* @brief          Symbolic name for the channel B11.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B11 ((uint8)0x1bU)

/**
* @brief          Symbolic name for the channel B12.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B12 ((uint8)0x1cU)

/**
* @brief          Symbolic name for the channel RX1AAF.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RX1AAF ((uint8)0x1dU)

/**
* @brief          Symbolic name for the channel V6V0PWRGD_A.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V6V0PWRGD_A ((uint8)0x1eU)

/**
* @brief          Symbolic name for the channel B15.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_B15 ((uint8)0x1fU)

/* ---------- DioPort_C ---------- */

/**
* @brief          Symbolic name for the port DioPort_C.
*
*/
#define DioConf_DioPort_DioPort_C  ((uint8)0x02U)

/**
* @brief          Symbolic name for the channel C0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_C0 ((uint8)0x20U)

/**
* @brief          Symbolic name for the channel C1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_C1 ((uint8)0x21U)

/**
* @brief          Symbolic name for the channel VPIMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_VPIMON ((uint8)0x22U)

/**
* @brief          Symbolic name for the channel nLOGSPICS_B.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nLOGSPICS_B ((uint8)0x24U)

/**
* @brief          Symbolic name for the channel LOGSPICLK_C.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LOGSPICLK_C ((uint8)0x25U)

/**
* @brief          Symbolic name for the channel LOGDATA0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LOGDATA0 ((uint8)0x26U)

/**
* @brief          Symbolic name for the channel SPI0SIN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPI0SIN ((uint8)0x27U)

/**
* @brief          Symbolic name for the channel SiGeRAMPDIRIN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeRAMPDIRIN ((uint8)0x2aU)

/**
* @brief          Symbolic name for the channel ETIMER0CH4.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETIMER0CH4 ((uint8)0x2bU)

/**
* @brief          Symbolic name for the channel ETIMER0CH5.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETIMER0CH5 ((uint8)0x2cU)

/**
* @brief          Symbolic name for the channel SiGeFSKSYNC_A.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeFSKSYNC_A ((uint8)0x2dU)

/**
* @brief          Symbolic name for the channel CTU0EXTTRG.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CTU0EXTTRG ((uint8)0x2eU)

/**
* @brief          Symbolic name for the channel CAEN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAEN ((uint8)0x2fU)

/* ---------- DioPort_D ---------- */

/**
* @brief          Symbolic name for the port DioPort_D.
*
*/
#define DioConf_DioPort_DioPort_D  ((uint8)0x03U)

/**
* @brief          Symbolic name for the channel CATX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CATX ((uint8)0x30U)

/**
* @brief          Symbolic name for the channel CARX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CARX ((uint8)0x31U)

/**
* @brief          Symbolic name for the channel CBRX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CBRX ((uint8)0x32U)

/**
* @brief          Symbolic name for the channel CBTX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CBTX ((uint8)0x33U)

/**
* @brief          Symbolic name for the channel CBEN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CBEN ((uint8)0x34U)

/**
* @brief          Symbolic name for the channel ETHRXD_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXD_1 ((uint8)0x35U)

/**
* @brief          Symbolic name for the channel ETHRXD_0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXD_0 ((uint8)0x36U)

/**
* @brief          Symbolic name for the channel ETHRXDV.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXDV ((uint8)0x37U)

/**
* @brief          Symbolic name for the channel ETHRXCLK.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXCLK ((uint8)0x38U)

/**
* @brief          Symbolic name for the channel V6V0SYNCMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V6V0SYNCMON ((uint8)0x39U)

/**
* @brief          Symbolic name for the channel ETHTXD_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXD_2 ((uint8)0x3aU)

/**
* @brief          Symbolic name for the channel SYNCFILT.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SYNCFILT ((uint8)0x3bU)

/**
* @brief          Symbolic name for the channel V5VAEN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V5VAEN ((uint8)0x3cU)

/**
* @brief          Symbolic name for the channel SiGeFMCWSYNC.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeFMCWSYNC ((uint8)0x3eU)

/* ---------- DioPort_E ---------- */

/**
* @brief          Symbolic name for the port DioPort_E.
*
*/
#define DioConf_DioPort_DioPort_E  ((uint8)0x04U)

/**
* @brief          Symbolic name for the channel V3V3AMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V3V3AMON ((uint8)0x40U)

/**
* @brief          Symbolic name for the channel V5VAMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V5VAMON ((uint8)0x42U)

/**
* @brief          Symbolic name for the channel V1V2MON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V1V2MON ((uint8)0x44U)

/**
* @brief          Symbolic name for the channel V3V3MON_A.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V3V3MON_A ((uint8)0x45U)

/**
* @brief          Symbolic name for the channel V6V0MON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V6V0MON ((uint8)0x46U)

/**
* @brief          Symbolic name for the channel V5VCANMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V5VCANMON ((uint8)0x47U)

/**
* @brief          Symbolic name for the channel V3V3MON_B.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V3V3MON_B ((uint8)0x49U)

/**
* @brief          Symbolic name for the channel E10.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_E10 ((uint8)0x4aU)

/**
* @brief          Symbolic name for the channel E11.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_E11 ((uint8)0x4bU)

/**
* @brief          Symbolic name for the channel V4V1MON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V4V1MON ((uint8)0x4cU)

/**
* @brief          Symbolic name for the channel ETMR0ETC5.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETMR0ETC5 ((uint8)0x4dU)

/**
* @brief          Symbolic name for the channel V3V3AEN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V3V3AEN ((uint8)0x4eU)

/**
* @brief          Symbolic name for the channel E15.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_E15 ((uint8)0x4fU)

/* ---------- DioPort_F ---------- */

/**
* @brief          Symbolic name for the port DioPort_F.
*
*/
#define DioConf_DioPort_DioPort_F  ((uint8)0x05U)

/**
* @brief          Symbolic name for the channel ETHMDC.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHMDC ((uint8)0x50U)

/**
* @brief          Symbolic name for the channel MICROBOOT.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICROBOOT ((uint8)0x53U)

/**
* @brief          Symbolic name for the channel MDO_3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MDO_3 ((uint8)0x54U)

/**
* @brief          Symbolic name for the channel MDO_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MDO_2 ((uint8)0x55U)

/**
* @brief          Symbolic name for the channel MDO_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MDO_1 ((uint8)0x56U)

/**
* @brief          Symbolic name for the channel MCKO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MCKO ((uint8)0x57U)

/**
* @brief          Symbolic name for the channel nMSEO1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nMSEO1 ((uint8)0x58U)

/**
* @brief          Symbolic name for the channel nMSEO0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nMSEO0 ((uint8)0x59U)

/**
* @brief          Symbolic name for the channel nEVTO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nEVTO ((uint8)0x5aU)

/**
* @brief          Symbolic name for the channel nEVTI.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nEVTI ((uint8)0x5bU)

/**
* @brief          Symbolic name for the channel ETMR1ETC3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETMR1ETC3 ((uint8)0x5cU)

/**
* @brief          Symbolic name for the channel YRSELFTEST.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_YRSELFTEST ((uint8)0x5dU)

/**
* @brief          Symbolic name for the channel YRDIAG.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_YRDIAG ((uint8)0x5eU)

/**
* @brief          Symbolic name for the channel RXEN_0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RXEN_0 ((uint8)0x5fU)

/* ---------- DioPort_G ---------- */

/**
* @brief          Symbolic name for the port DioPort_G.
*
*/
#define DioConf_DioPort_DioPort_G  ((uint8)0x06U)

/**
* @brief          Symbolic name for the channel V4V1SYNCMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V4V1SYNCMON ((uint8)0x62U)

/**
* @brief          Symbolic name for the channel SPAREPSUSYNC.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPAREPSUSYNC ((uint8)0x63U)

/**
* @brief          Symbolic name for the channel G4.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_G4 ((uint8)0x64U)

/**
* @brief          Symbolic name for the channel ETHTXEN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXEN ((uint8)0x65U)

/**
* @brief          Symbolic name for the channel G6.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_G6 ((uint8)0x66U)

/**
* @brief          Symbolic name for the channel G7.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_G7 ((uint8)0x67U)

/**
* @brief          Symbolic name for the channel ETHTXCLK.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXCLK ((uint8)0x68U)

/**
* @brief          Symbolic name for the channel ETHTXD_0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXD_0 ((uint8)0x69U)

/**
* @brief          Symbolic name for the channel ETHTXD_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXD_1 ((uint8)0x6aU)

/**
* @brief          Symbolic name for the channel ETHTXD_3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHTXD_3 ((uint8)0x6bU)

/* ---------- DioPort_H ---------- */

/**
* @brief          Symbolic name for the port DioPort_H.
*
*/
#define DioConf_DioPort_DioPort_H  ((uint8)0x07U)

/**
* @brief          Symbolic name for the channel ETHCRS.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHCRS ((uint8)0x74U)

/**
* @brief          Symbolic name for the channel ETHCOL.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHCOL ((uint8)0x75U)

/**
* @brief          Symbolic name for the channel H6.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_H6 ((uint8)0x76U)

/**
* @brief          Symbolic name for the channel ETHMDIO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHMDIO ((uint8)0x77U)

/**
* @brief          Symbolic name for the channel ETHRXD_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXD_2 ((uint8)0x78U)

/**
* @brief          Symbolic name for the channel MICRORXEN_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICRORXEN_1 ((uint8)0x79U)

/**
* @brief          Symbolic name for the channel MICRORXEN_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICRORXEN_2 ((uint8)0x7aU)

/**
* @brief          Symbolic name for the channel MICRORXEN_3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICRORXEN_3 ((uint8)0x7bU)

/**
* @brief          Symbolic name for the channel MICROIFEN_0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICROIFEN_0 ((uint8)0x7cU)

/**
* @brief          Symbolic name for the channel MICROIFEN_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICROIFEN_1 ((uint8)0x7dU)

/**
* @brief          Symbolic name for the channel MICROIFEN_2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICROIFEN_2 ((uint8)0x7eU)

/**
* @brief          Symbolic name for the channel MICROIFEN_3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MICROIFEN_3 ((uint8)0x7fU)

/* ---------- DioPort_I ---------- */

/**
* @brief          Symbolic name for the port DioPort_I.
*
*/
#define DioConf_DioPort_DioPort_I  ((uint8)0x08U)

/**
* @brief          Symbolic name for the channel I0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_I0 ((uint8)0x80U)

/**
* @brief          Symbolic name for the channel ETHRXERR.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXERR ((uint8)0x81U)

/**
* @brief          Symbolic name for the channel ETIMER2CH2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETIMER2CH2 ((uint8)0x82U)

/**
* @brief          Symbolic name for the channel TIMER0.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TIMER0 ((uint8)0x83U)

/**
* @brief          Symbolic name for the channel nNEXUSRDY.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nNEXUSRDY ((uint8)0x84U)

/**
* @brief          Symbolic name for the channel CAN2TX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN2TX ((uint8)0x85U)

/**
* @brief          Symbolic name for the channel CAN2RX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN2RX ((uint8)0x86U)

/**
* @brief          Symbolic name for the channel nCAN0ENMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nCAN0ENMON ((uint8)0x87U)

/**
* @brief          Symbolic name for the channel nCAN1ENMON.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nCAN1ENMON ((uint8)0x88U)

/**
* @brief          Symbolic name for the channel ETMR2ETC4.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETMR2ETC4 ((uint8)0x89U)

/**
* @brief          Symbolic name for the channel ETMR2ETC5.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETMR2ETC5 ((uint8)0x8aU)

/**
* @brief          Symbolic name for the channel nSiGeRESET.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nSiGeRESET ((uint8)0x8bU)

/**
* @brief          Symbolic name for the channel V6V0PWRGD_B.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V6V0PWRGD_B ((uint8)0x8cU)

/**
* @brief          Symbolic name for the channel CTU1EXTTRIG.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CTU1EXTTRIG ((uint8)0x8dU)

/**
* @brief          Symbolic name for the channel nSPI3CS.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_nSPI3CS ((uint8)0x8eU)

/**
* @brief          Symbolic name for the channel SPI3SCLK.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPI3SCLK ((uint8)0x8fU)

/* ---------- DioPort_J ---------- */

/**
* @brief          Symbolic name for the port DioPort_J.
*
*/
#define DioConf_DioPort_DioPort_J  ((uint8)0x09U)

/**
* @brief          Symbolic name for the channel SPI3SOUT.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPI3SOUT ((uint8)0x90U)

/**
* @brief          Symbolic name for the channel SPI3SIN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SPI3SIN ((uint8)0x91U)

/**
* @brief          Symbolic name for the channel J2.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_J2 ((uint8)0x92U)

/**
* @brief          Symbolic name for the channel SiGeTXSEL_1.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeTXSEL_1 ((uint8)0x93U)

/**
* @brief          Symbolic name for the channel SiGeFSKSYNC_B.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SiGeFSKSYNC_B ((uint8)0x94U)

/**
* @brief          Symbolic name for the channel J5.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_J5 ((uint8)0x95U)

/**
* @brief          Symbolic name for the channel RX2AAF.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RX2AAF ((uint8)0x96U)

/**
* @brief          Symbolic name for the channel RX3AAF.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RX3AAF ((uint8)0x97U)

/**
* @brief          Symbolic name for the channel V4V1PWRGD.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_V4V1PWRGD ((uint8)0x98U)

/**
* @brief          Symbolic name for the channel ETHRXD3.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ETHRXD3 ((uint8)0x99U)


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief          Type of a DIO port representation.
*
* @implements     Dio_PortType_typedef
*
* @api
*/
typedef uint8 Dio_PortType;

/**
* @brief          Type of a DIO channel representation.
*
* @implements     Dio_ChannelType_typedef
*
* @api
*/
typedef uint8 Dio_ChannelType;

/**
* @brief          Type of a DIO port levels representation.
*
* @implements     Dio_PortLevelType_typedef
*
* @api
*/
typedef uint16 Dio_PortLevelType;

/**
* @brief          Type of a DIO channel levels representation.
*
* @implements     Dio_LevelType_typedef
*
* @api
*/
typedef uint8 Dio_LevelType;

/**
* @brief          Type of a DIO channel group representation.
*
* @implements     Dio_ChannelGroupType_struct
*
* @api
*/
typedef struct
{
    VAR(Dio_PortType, DIO_VAR)      port;      /**< @brief Port identifier.  */
    VAR(uint8, DIO_VAR)             offset;    /**< @brief Bit offset within the port. */
    VAR(Dio_PortLevelType, DIO_VAR) mask;      /**< @brief Group mask. */
} Dio_ChannelGroupType;

/**
* @brief          Type of a DIO configuration structure.
*
* @note           In this implementation there is no need for a configuration
*                 structure there is only a dummy field, it is recommended
*                 to initialize this field to zero.
*
* @implements     Dio_ConfigType_struct
*
* @api
*/
typedef struct
{                                                                       
    VAR(uint8, DIO_VAR) u8NumChannelGroups; /**< @brief Number of channel groups in configuration */
    P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_APPL_CONST) pChannelGroupList;  /**< @brief 
                                               Pointer to list of channel groups in configuration */
} Dio_ConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

/**
* @brief Array of bitmaps of output pins available per port
*/
/** @violates @ref Dio_C_REF_3 Objects shall be defined at block scope if they are only accessed
    from within a single function. This violation can not be avoided because it is an AUTOSAR
    requirement*/

extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForWrite[DIO_NUM_PORTS_U16];

/**
* @brief Array of bitmaps of input pins available per port
*/
/** @violates @ref Dio_C_REF_3 Objects shall be defined at block scope if they are only accessed
    from within a single function. This violation can not be avoided because it is an AUTOSAR
    requirement*/

extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForRead[DIO_NUM_PORTS_U16];


/**
* @brief          List of channel groups in configuration DioConfig_0.
*/



/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* DIO_CFG_H */

/** @} */
