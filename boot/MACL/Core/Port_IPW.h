/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Port_IPW.h $
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
* @file    Port_Ipw.h
*
* @version 1.0.0
* @brief   AUTOSAR Port - PORT driver low level driver interface.
* @details Interface between the high level driver (Autosar dependent) and the low level driver(IP dependent).
*          It is platform specific.
*
* @addtogroup  Port
* @{
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

#ifndef PORT_IPW_H
#define PORT_IPW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_IPW_H_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linkershall be checked to ensure 
* that 31 character significance and case sensitivity are supported for external 
* identifiers. The defines are ok.
*
* @section PORT_IPW_H_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Port_Siul2.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file.
*
*/
#define PORT_VENDOR_ID_IPW_H                    43
#define PORT_AR_RELEASE_MAJOR_VERSION_IPW_H     4
#define PORT_AR_RELEASE_MINOR_VERSION_IPW_H     0
/**
* @violates @ref PORT_IPW_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
* ensure that 31 character significance and case sensitivity are supported for external
* identifiers.
*/
#define PORT_AR_RELEASE_REVISION_VERSION_IPW_H  3

#define PORT_SW_MAJOR_VERSION_IPW_H             1
#define PORT_SW_MINOR_VERSION_IPW_H             0
#define PORT_SW_PATCH_VERSION_IPW_H             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Check if Port_Ipw.h and Port_Siul.h file are of the same vendor */
#if (PORT_VENDOR_ID_IPW_H != PORT_SIUL2_VENDOR_ID_H)
    #error "Port_Ipw.h and Port_Siul2.h have different vendor ids"
#endif

/* Check if Port_Ipw.h and Port_Siul.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_H    != PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_H) || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_H    != PORT_SIUL2_AR_RELEASE_MINOR_VERSION_H) || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_H != PORT_SIUL2_AR_RELEASE_REVISION_VERSION_H) \
    )
   #error "AutoSar Version Numbers of Port_Ipw.h and Port_Siul2.h are different"
#endif

/* Check if Port_Ipw.h and Port_Siul.h file are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_H != PORT_SIUL2_SW_MAJOR_VERSION_H) || \
     (PORT_SW_MINOR_VERSION_IPW_H != PORT_SIUL2_SW_MINOR_VERSION_H) || \
     (PORT_SW_PATCH_VERSION_IPW_H != PORT_SIUL2_SW_PATCH_VERSION_H)    \
    )
   #error "Software Version Numbers of Port_Ipw.h and Port_Siul2.h are different"
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief  Mapping the platform RefMan IMCR id's to the normal addressing index.
*/
#define IMCR_INDEX_OFFSET_U32          ((uint32)32UL)

#define ONLY_INPUT_INDEX_OFFSET_U8     ((uint8)6U)

#define SIUL2_MODE_BIT_OFFSET_MASK_U8  ((uint8)0x0F)

/**
* @brief  Mapping between low level layer and high level layer for Port_Ipw_Init function.
*/
#define Port_Ipw_Init                  (Port_Siul2_Init)

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
/**
* @brief  Mapping between low level layer and high level layer for Port_Ipw_SetPinDirection.
*/
#define Port_Ipw_SetPinDirection       (Port_Siul2_SetPinDirection)

#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) */

/**
* @brief  Mapping between low level layer and high level layer for Port_Ipw_RefreshPortDirection function.
*/
#define Port_Ipw_RefreshPortDirection  (Port_Siul2_RefreshPortDirection)

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
*                                     FUNCTION PROTOTYPES
=================================================================================================*/

/* Allocate defined section for PORT code */
#define PORT_START_SEC_CODE
/**
* @violates @ref PORT_IPW_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* Sets the port pin mode.
*/
FUNC(Std_ReturnType, PORT_CODE) Port_Ipw_SetPinMode
( 
    VAR     (Port_PinType,      AUTOMATIC                 ) PinIndex,
    VAR     (Port_PinModeType,  AUTOMATIC                 ) PinMode,
    P2CONST (Port_ConfigType,   AUTOMATIC, PORT_APPL_CONST) pConfigPtr
);
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */

#define PORT_STOP_SEC_CODE
/**
* @violates @ref PORT_IPW_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /*PORT_IPW_H*/
/** @} */
