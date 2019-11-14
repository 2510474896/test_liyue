/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Dem_Types.h $
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
*   @file    Dem_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Dem -  module header
*   @details This file contains data types of the AUTOSAR Dem
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup DEM_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : 
*   Dependencies         : 
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

#ifndef DEM_TYPES_H
#define DEM_TYPES_H

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
#define DEM_TYPES_VENDOR_ID 43
#define DEM_TYPES_MODULE_ID 54

#define DEM_TYPES_AR_RELEASE_MAJOR_VERSION      4
#define DEM_TYPES_AR_RELEASE_MINOR_VERSION      0
#define DEM_TYPES_AR_RELEASE_REVISION_VERSION   3
#define DEM_TYPES_SW_MAJOR_VERSION              1
#define DEM_TYPES_SW_MINOR_VERSION              0
#define DEM_TYPES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef uint16 Dem_EventIdType;                              /**< @brief dem event ID type */

typedef uint8 Dem_EventStatusType;                           /**< @brief dem event status type */

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define DEM_EVENT_STATUS_PASSED     (Dem_EventStatusType)0x00U  /**< @brief dem event passed */
#define DEM_EVENT_STATUS_FAILED     (Dem_EventStatusType)0x01U  /**< @brief dem event failed */
#define DEM_EVENT_STATUS_PREPASSED  (Dem_EventStatusType)0x02U  /**< @brief dem event pre-passed */
#define DEM_EVENT_STATUS_PREFAILED  (Dem_EventStatusType)0x03U  /**< @brief dem event pre-failed */

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DEM_TYPES_H */
