/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Det.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:26CST $

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
*   @file    Det.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Det - module interface.
*   @details This file contains the functions prototypes and data types of the AUTOSAR Det.
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup DET_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : 
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
#ifndef DET_H
#define DET_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Det.h
* @requirements   DET001_PI
*/

#define DET_VENDOR_ID 43
#define DET_MODULE_ID 15

#define DET_AR_RELEASE_MAJOR_VERSION        4
#define DET_AR_RELEASE_MINOR_VERSION        0
#define DET_AR_RELEASE_REVISION_VERSION     3
#define DET_SW_MAJOR_VERSION                1
#define DET_SW_MINOR_VERSION                0
#define DET_SW_PATCH_VERSION                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define DET_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"

extern VAR(uint8 , DET_VAR) Det_InstanceId;     /**< @brief DET instance ID*/
extern VAR(uint8 , DET_VAR) Det_ApiId;          /**< @brief DET API ID*/
extern VAR(uint8 , DET_VAR) Det_ErrorId;        /**< @brief DET Error ID*/

#define DET_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"


#define DET_START_SEC_VAR_NO_INIT_16
#include "MemMap.h"

extern VAR(uint16, DET_VAR) Det_ModuleId;       /**< @brief DET module ID*/

#define DET_STOP_SEC_VAR_NO_INIT_16
#include "MemMap.h"

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
FUNC(void, DET_CODE) Det_Init(void);
FUNC(void, DET_CODE) Det_ReportError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId);
FUNC(void, DET_CODE) Det_Start(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DET_H */

/** @} */
