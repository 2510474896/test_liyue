/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Dem.c $
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
*   @file    Dem.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Dem - module implementation
*   @details This module implements stubs for the AUTOSAR Dem
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Dem.h"

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/
#define DEM_VENDOR_ID_C         43
#define DEM_AR_RELEASE_MAJOR_VERSION_C  4
#define DEM_AR_RELEASE_MINOR_VERSION_C  0
#define DEM_AR_RELEASE_REVISION_VERSION_C  3
#define DEM_SW_MAJOR_VERSION_C  1
#define DEM_SW_MINOR_VERSION_C  0
#define DEM_SW_PATCH_VERSION_C  0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and DEM header file are of the same vendor */
#if (DEM_VENDOR_ID_C != DEM_VENDOR_ID)
    #error "Dem.c and Dem.h have different vendor ids"
#endif

/* Check if source file and DEM header file are of the same Autosar version */
#if ((DEM_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) || \
     (DEM_AR_RELEASE_REVISION_VERSION_C != DEM_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Dem.c and Dem.h are different"
#endif

/* Check if source file and DEM header file are of the same Software version */
#if ((DEM_SW_MAJOR_VERSION_C != DEM_SW_MAJOR_VERSION) || \
     (DEM_SW_MINOR_VERSION_C != DEM_SW_MINOR_VERSION) || \
     (DEM_SW_PATCH_VERSION_C != DEM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Dem.c and Dem.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if DEM source file and STD_TYPES header file are of the same Software version */
    #if ((DEM_AR_RELEASE_MAJOR_VERSION_C != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
        (DEM_AR_RELEASE_MINOR_VERSION_C != STD_TYPES_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Dem.C and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/* put all DEM variables un-init vars into defined section */
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* Variable Definition */
VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId;                     /**< @brief DEM event ID*/
VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus;                 /**< @brief DEM event status*/
VAR(Dem_EventIdType    , DEM_VAR) Dem_EventId2;                    /**< @brief DEM event ID2*/
VAR(Dem_EventStatusType, DEM_VAR) Dem_EventStatus2;                /**< @brief DEM event status2*/

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* put all DEM variables init vars into defined section */
#define DEM_START_SEC_VAR_INIT_32
#include "MemMap.h"

VAR(uint32, DEM_VAR)              Dem_numEventErrors = (uint32)0;  /**< @brief DEM event number of errors*/

#define DEM_STOP_SEC_VAR_INIT_32
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/* put all DEM code into defined section */
#define DEM_START_SEC_CODE
#include "MemMap.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/** 
* @brief   This function reports the error status. 
* @details This is a function stub only. It loads Dem_EventId = EventId and 
*          Dem_EventStatus = EventStatus and increments Dem_numEventErrors
*     
* @param[in]     EventId      ID of the event
* @param[in]     EventStatus  status of the event
*   
*/
FUNC(void, DEM_CODE) Dem_ReportErrorStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    Dem_EventId = EventId;
    Dem_EventStatus = EventStatus;
    Dem_numEventErrors++;
}

/*================================================================================================*/
/** 
* @brief   This function sets the error status. 
* @details This is a function stub only. It loads Dem_EventId2 = EventId and 
*          Dem_EventStatus2 = EventStatus and returns success.
*     
* @param[in]     EventId        ID of the event
* @param[in]     EventStatus    status of the event 
* @return        Std_ReturnType This function is always successful
*   
*/
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    Dem_EventId2 = EventId;
    Dem_EventStatus2 = EventStatus;
    return(E_OK);
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

