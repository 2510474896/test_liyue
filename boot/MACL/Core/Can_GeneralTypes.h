/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Can_GeneralTypes.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:24CST $

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
*   @file    Can_GeneralTypes.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - General Types.
*   @details API header for all types and constants that are shared among the AUTOSAR CAN
*            modules Can, CanIf and CanTrcv.
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


#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Can_GeneralTypes_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*/
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/**
* @brief          CAN State Modes of operation.
* @details        State transitions that are used by the function CAN_SetControllerMode().
* @implements     Can_StateTransitionType_enumeration
*/
typedef enum
    {
        CAN_T_STOP = 0U,   /**< @brief CANIF_CS_STARTED -> CANIF_CS_STOPPED */
        CAN_T_START,       /**< @brief CANIF_CS_STOPPED -> CANIF_CS_STARTED */
        CAN_T_SLEEP,       /**< @brief CANIF_CS_STOPPED -> CANIF_CS_SLEEP */
        CAN_T_WAKEUP       /**< @brief CANIF_CS_SLEEP -> CANIF_CS_STOPPED */
    } Can_StateTransitionType;


/**
* @brief          Can_ReturnType
* @details        CAN Return Types from Functions.
* @implements     Can_ReturnType_enumeration
*/
typedef enum
    {
        CAN_OK = 0U,    /**< @brief Operation was ok executed */
        CAN_NOT_OK,     /**< @brief Operation was not ok executed */
        CAN_BUSY        /**< @brief Operation was rejected because of busy state */
    } Can_ReturnType;


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#ifdef CAN_EXTENDEDID
    #if (CAN_EXTENDEDID == STD_ON)
/**
* @{
* @brief          Can_IdType
* @details        Type for storing the Identifier Length Type: Normal or Extended.
*                   - used by "Can_MessageBufferConfigObjectType" structure.
*                 The driver does not distinguish between Extended and Mixed transmission modes.
*                 Extended transmission mode of operation behaves the same as Mixed mode.
* @implements     Can_IdType_type
*/
    typedef  uint32 Can_IdType;
    #else /* (CAN_EXTENDEDID == STD_OFF) */
    typedef  uint16 Can_IdType;
    #endif /* (CAN_EXTENDEDID == STD_ON/STD_OFF) */
#else
    typedef  uint16 Can_IdType;
#endif
/**@}*/

/**
* @brief          Can_PduType
* @details        Type used to provide ID, DLC, SDU from CAN interface to CAN driver.
*                 HTH or HRH = ID+DLC+SDU.
* @implements     Can_PduType_structure
*/
typedef struct
    {
        VAR(Can_IdType, CAN_VAR) id; /**< @brief CAN L-PDU = Data Link Layer Protocol Data Unit.
                                                 Consists of Identifier, DLC and Data(SDU)  It is
                                                 uint32 for CAN_EXTENDEDID=STD_ON, else is uint16.
                                                 */
        VAR(PduIdType, CAN_VAR) swPduHandle; /**< @brief The L-PDU Handle = defined and placed
                                                         inside the CanIf module layer. Each handle
                                                         represents an L-PDU, which is a constant
                                                         structure with information for Tx/Rx
                                                         processing. */
        VAR(uint8, CAN_VAR) length; /**< @brief DLC = Data Length Code (part of L-PDU that describes
                                                the SDU length). */
        P2VAR(uint8, CAN_VAR, CAN_APPL_DATA) sdu; /**< @brief CAN L-SDU = Link Layer Service Data
                                                              Unit. Data that is transported inside
                                                              the L-PDU. */
    } Can_PduType;

#ifdef CAN_MBCOUNTEXTENSION
    #if (CAN_MBCOUNTEXTENSION == STD_ON)
/**
* @{
* @brief          Can_HwHandleType
* @details        Represents the hardware object handles of a CAN hardware unit.
                  For CAN hardware units with more than 255 HW objects use extended range.
*                   - used by "Can_Write" function.
*                 The driver does not distinguish between Extended and Mixed transmission modes.
*                 Extended transmission mode of operation behaves the same as Mixed mode.
* @implements     Can_HwHandleType_type
*/
    typedef uint32 Can_HwHandleType;
    #else /* (CAN_MBCOUNTEXTENSION==STD_OFF) */
    typedef uint16 Can_HwHandleType;
    #endif /* (CAN_MBCOUNTEXTENSION==STD_ON/STD_OFF) */
#else
    typedef uint16 Can_HwHandleType;
#endif
/**@}*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*CAN_GENERAL_TYPES_H*/

/** @} */
