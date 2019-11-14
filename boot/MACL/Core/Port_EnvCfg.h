/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Port_EnvCfg.h $
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
*   @file Port_EnvCfg.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Port - contains the configuration data of the PORT driver
*   @details Contains the configuration data of the PORT driver
*
*   @addtogroup PORT_MODULE
*   @{
*/
/*==================================================================================================
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
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef PORT_ENVCFG_H
#define PORT_ENVCFG_H

#ifdef __cplusplus
extern "C"{
#endif 

/**
* @page misra_violations MISRA-C:2004 violations
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

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define PORT_ENVCFG_VENDOR_ID                        43

#define PORT_ENVCFG_AR_RELEASE_MAJOR_VERSION         4
#define PORT_ENVCFG_AR_RELEASE_MINOR_VERSION         0
#define PORT_ENVCFG_AR_RELEASE_REVISION_VERSION      3

#define PORT_ENVCFG_SW_MAJOR_VERSION                 1
#define PORT_ENVCFG_SW_MINOR_VERSION                 0
#define PORT_ENVCFG_SW_PATCH_VERSION                 0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define PORT_QM   (STD_OFF)
#define PORT_FTE  (STD_ON)
#define PORT_GTE  (STD_OFF)
#define PORT_NTE  (STD_OFF)

#if (STD_ON == PORT_QM)
  #define PORT_PERIODIC_CHECK_API        (STD_OFF)
  #define PORT_USER_MODE_SOFT_LOCKING    (STD_OFF)
  #define PORT_SERR_NOTIFY_ERROR_ENABLE  (STD_OFF)
#endif

#if (STD_ON == PORT_FTE)
  #define PORT_PERIODIC_CHECK_API        (STD_ON)
  #define PORT_USER_MODE_SOFT_LOCKING    (STD_OFF)
  #define PORT_SERR_NOTIFY_ERROR_ENABLE  (STD_OFF)
#endif

#if (STD_ON == PORT_GTE)
  #define PORT_PERIODIC_CHECK_API        (STD_ON)
  #define PORT_SERR_NOTIFY_ERROR_ENABLE  (STD_ON)
  #define PORT_USER_MODE_SOFT_LOCKING    (STD_ON)
#endif

#if (STD_ON == PORT_NTE)
  #define PORT_PERIODIC_CHECK_API        (STD_ON)
  #define PORT_SERR_NOTIFY_ERROR_ENABLE  (STD_ON)
  #define PORT_USER_MODE_SOFT_LOCKING    (STD_ON)
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* PORT_ENVCFG_H */
