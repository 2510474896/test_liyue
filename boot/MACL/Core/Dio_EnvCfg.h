/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Dio_EnvCfg.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:27CST $

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
*   @file    Dio_EnvCfg.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Dio - Dio driver header file.
*   @details DIO driver header file, containing variables, functions prototypes, data types and/or
*            defines and macros that:
*            - are Autosar specific and are not exported by the DIO driver.
*            - are not related to the DIO driver related IPs.
*
*   @addtogroup DIO_MODULE
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

#ifndef DIO_ENVCFG_H
#define DIO_ENVCFG_H

#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_EnvCfg_H_REF_1
*           Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
*           Precautions shall be taken in order to prevent the contents of a header file 
*           being included twice. This is not a violation since all header files are 
*           protected against multiple inclusions
* @section [global]
*     Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*     on the significance of more than 31 characters. The used compilers use more than 31 chars for
*     identifiers.
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @violates @ref Dio_EnvCfg_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include  "Std_Types.h"


/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Dio_EnvCfg.h
* @{
*/
#define DIO_ENVCFG_VENDOR_ID                      43
#define DIO_ENVCFG_AR_RELEASE_MAJOR_VERSION       4
#define DIO_ENVCFG_AR_RELEASE_MINOR_VERSION       0
#define DIO_ENVCFG_AR_RELEASE_REVISION_VERSION    3
#define DIO_ENVCFG_SW_MAJOR_VERSION               1
#define DIO_ENVCFG_SW_MINOR_VERSION               0
#define DIO_ENVCFG_SW_PATCH_VERSION               0
/** @} */


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((DIO_ENVCFG_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         (DIO_ENVCFG_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Dio_EnvCfg.h and Std_Types.h are different"
    #endif
#endif


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

#define DIO_QM  (STD_OFF)
#define DIO_FTE (STD_ON)
#define DIO_GTE (STD_OFF)
#define DIO_NTE (STD_OFF)  


#if (DIO_FTE == STD_ON)
    #define DIO_VALIDATE_PARAMS  (DIO_DEV_ERROR_DETECT)
#endif 

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

#ifdef __cplusplus
}
#endif

#endif /*DIO_ENVCFG_H*/

/** @} */





