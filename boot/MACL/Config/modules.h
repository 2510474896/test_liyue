/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: modules.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:20CST $

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
*   @file    modules.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - Project configuration.
*   @details Header file describing all Autosar MCAL modules present in the current project.
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
* @file        modules.h
*/
/** 
* @page misra_violations MISRA-C:2004 violations
*
* @section modules_h_REF_1
*          Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to
*          prevent the contents of a header file being included twice. All header files are
*          protected against multiple inclusions.
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*          on the significance of more than 31 characters. The used compilers use more than 31 chars for
*          identifiers.
*/

#ifndef MODULES_H
#define MODULES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/** 
* @file        modules.h
* @brief Include Standard types & defines
*/
/* @violates @ref modules_h_REF_1 MISRA 2004 Required Rule 19.15, precautions to prevent the 
*   contents of a header file being included twice.*/
#include "Std_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/** 
@{
* @brief Parameters that shall be published within the modules header file.
*       The integration of incompatible files shall be avoided.
*/
#define MODULES_VENDOR_ID                       43
#define MODULES_MODULE_ID                       0
#define MODULES_AR_RELEASE_MAJOR_VERSION_H      4
#define MODULES_AR_RELEASE_MINOR_VERSION_H      0
#define MODULES_AR_RELEASE_REVISION_VERSION_H   3
#define MODULES_SW_MAJOR_VERSION_H              1
#define MODULES_SW_MINOR_VERSION_H              0
#define MODULES_SW_PATCH_VERSION_H              0
/**@}*/
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Std_Types.h header file are of the same Autosar version */
    #if ((MODULES_AR_RELEASE_MAJOR_VERSION_H != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         (MODULES_AR_RELEASE_MINOR_VERSION_H != STD_TYPES_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of modules.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** 
* @brief This constant used for other modules to check if ADC is present in the project.  
*/
#define USE_ADC_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if CAN is present in the project.  
*/
#define USE_CAN_MODULE              (STD_ON)

/** 
* @brief This constant used for other modules to check if CRCU is present in the project.  
*/
#define USE_CRCU_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if DIO is present in the project.  
*/
#define USE_DIO_MODULE              (STD_ON)

/** 
* @brief This constant used for other modules to check if ETH is present in the project.
*/
#define USE_ETH_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if FEE is present in the project.  
*/
#define USE_FEE_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if FLS is present in the project.  
*/
#define USE_FLS_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if Fr is present in the project.  
*/
#define USE_FR_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if GPT is present in the project.  
*/
#define USE_GPT_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if ICU is present in the project.  
*/
#define USE_ICU_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if LIN is present in the project.  
*/
#define USE_LIN_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if MCEM is present in the project.  
*/
#define USE_MCEM_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if MCEM is present in the project.  
*/
#define USE_MCL_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if MCU is present in the project.  
*/
#define USE_MCU_MODULE              (STD_ON)

/** 
* @brief This constant used for other modules to check if PORT is present in the project.  
*/
#define USE_PORT_MODULE             (STD_ON)

/** 
* @brief This constant used for other modules to check if PWM is present in the project.  
*/
#define USE_PWM_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if SPI is present in the project.  
*/
#define USE_SPI_MODULE              (STD_OFF)

/** 
* @brief This constant used for other modules to check if WDG is present in the project.  
*/
#define USE_WDG_MODULE              (STD_OFF)

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

#endif /* MODULES_H */

/** @} */


