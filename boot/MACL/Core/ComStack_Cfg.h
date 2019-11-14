/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: ComStack_Cfg.h $
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
*   @file           ComStack_Cfg.h
*   @implements     ComStack_Cfg.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - type definition of the PduIdType and PduLengthType.
*   @details AUTOSAR type definition of the PduIdType and PduLengthType. shall be generated by 
*            the generator of EcuC Virtual Layer
*            This file contains sample code only. It is not part of the production code deliverables
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
#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
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

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** 
* @brief   This type serve as a unique identifier of a PDU within a software module.
*          Allowed ranges: uint8 .. uint16
* @implements PduIdType_type
*/
typedef uint32       PduIdType;

/** 
* @brief   This type serve as length information of a PDU in bytes.
*          Allowed ranges: uint8 .. uint32 
* @implements PduLengthType_Type
*/
typedef uint32       PduLengthType; 

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* COMSTACK_CFG_H */

/** @} */
