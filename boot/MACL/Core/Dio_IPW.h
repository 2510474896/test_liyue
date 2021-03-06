/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Dio_IPW.h $
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
*   @file    Dio_Ipw.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Dio low level header.
*   @details This file is the DIO driver low level header.
*
*   @addtogroup DIO_IPW
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

#ifndef DIO_IPW_H
#define DIO_IPW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_IPW_H_REF_1
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external
*          identifiers. The defines are ok. 
*
* @section Dio_IPW_H_REF_2
*          Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*          Middle layer between AUTOSAR and hardware needs a way to map HLD
*          functions to LLD functions.
*
* @section [global]
*     Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*     on the significance of more than 31 characters. The used compilers use more than 31 chars for
*     identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Dio_Siul2.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID_IPW                   43
#define DIO_AR_RELEASE_MAJOR_VERSION_IPW    4
#define DIO_AR_RELEASE_MINOR_VERSION_IPW    0
/** @violates @ref Dio_IPW_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_REVISION_VERSION_IPW 3
#define DIO_SW_MAJOR_VERSION_IPW            1
#define DIO_SW_MINOR_VERSION_IPW            0
#define DIO_SW_PATCH_VERSION_IPW            0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

#if ((DIO_AR_RELEASE_MAJOR_VERSION_IPW != DIO_SIUL2_AR_RELEASE_MAJOR_VERSION)       || \
     (DIO_AR_RELEASE_MINOR_VERSION_IPW != DIO_SIUL2_AR_RELEASE_MINOR_VERSION)       || \
     (DIO_AR_RELEASE_REVISION_VERSION_IPW != DIO_SIUL2_AR_RELEASE_REVISION_VERSION)    \
    )
     #error "AUTOSAR Version Numbers of Dio_Ipw.h and Dio_Siul2.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_IPW != DIO_SIUL2_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_IPW != DIO_SIUL2_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_IPW != DIO_SIUL2_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Dio_Ipw.h and Dio_Siul2.h are different"
#endif

#if (DIO_VENDOR_ID_IPW != DIO_SIUL2_VENDOR_ID)
    #error "VENDOR ID for Dio_Ipw.h and Dio_Siul2.h is different"
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/** Bit mask for the leftmost channel in a port*/
#define DIO_BIT1_LEFTMOST_MASK_U16                  ((uint16)0x8000U)
#define DIO_PIN_MASK_U16                            ((uint16)0x000FU)
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define DIO_CHECK_CHANNEL_VALIDITY(channelId)       (DIO_BIT1_LEFTMOST_MASK_U16 >> ((channelId) & DIO_PIN_MASK_U16))

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_ReadChannel(ChannelId)              (Dio_Siul2_ReadChannel(ChannelId))


/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_WriteChannel(ChannelId, ChannelLevel) (Dio_Siul2_WriteChannel((ChannelId), (ChannelLevel)))

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_FlipChannel(ChannelId)              (Dio_Siul2_FlipChannel(ChannelId))

#endif /* STD_ON == DIO_FLIP_CHANNEL_API */

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_ReadPort(PortId)                    (Dio_Siul2_ReadPort(PortId))

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_WritePort(PortId, PortLevel)        (Dio_Siul2_WritePort((PortId), (PortLevel)))

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_ReadChannelGroup(pChannelGroupIdPtr) (Dio_Siul2_ReadChannelGroup(pChannelGroupIdPtr))

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_WriteChannelGroup(pChannelGroupIdPtr, Level)    (Dio_Siul2_WriteChannelGroup((pChannelGroupIdPtr), (Level)))

#if (STD_ON == DIO_MASKEDWRITEPORT_API)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
/**
* @violates @ref Dio_IPW_H_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define Dio_Ipw_MaskedWritePort(PortId, PortLevel, Mask)        (Dio_Siul2_MaskedWritePort((PortId), (PortLevel), (Mask)))
    
#endif /* STD_ON == DIO_MASKEDWRITEPORT_API */


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* DIO_IPW_H */

/** @} */
