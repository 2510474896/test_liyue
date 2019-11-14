/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Port_SIUL2_Types.h $
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
*   @file    Port_Siul2_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Port - SIUL low level IP driver exported structures.
*   @details Interface between the high level driver (Autosar dependent) and the low level driver(platform dependent).
*
*   @addtogroup Siul2
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

#ifndef PORT_SIUL2_TYPES_H
#define PORT_SIUL2_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers(internal and external) shall not rely 
* on the significance of more than 31 characters.The used compilers use more than 31 chars
* for identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/


/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
* @brief current file vendor, Autosar and API version numbers
*       The integration of incompatible files shall be avoided.
*/
#define PORT_SIUL2_VENDOR_ID_TYPES_H                     43
#define PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_TYPES_H      4
#define PORT_SIUL2_AR_RELEASE_MINOR_VERSION_TYPES_H      0
#define PORT_SIUL2_AR_RELEASE_REVISION_VERSION_TYPES_H   3
#define PORT_SIUL2_SW_MAJOR_VERSION_TYPES_H              1
#define PORT_SIUL2_SW_MINOR_VERSION_TYPES_H              0
#define PORT_SIUL2_SW_PATCH_VERSION_TYPES_H              0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/**
* @brief Possible output status of a port pin.
*/
#define  PORT_PIN_LEVEL_LOW_U8         ((uint8)0)    /**< @brief Sets port pin in '0' logic. */
#define  PORT_PIN_LEVEL_HIGH_U8        ((uint8)1)    /**< @brief Sets port pin in '1' logic. */
#define  PORT_PIN_LEVEL_NOTCHANGED_U8  ((uint8)2)    /**< @brief No level changes for the port pin. */

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief Data type for the symbolic name of a port pin.
* @details Shall cover all available port pins. The type should be chosen for the specific MCU
*         platform (best performance).
* @implements Port_PinType_typedef
*/
typedef uint32 Port_PinType;

/**
* @brief Possible directions of a port pin.
* @implements Port_PinDirectionType_enumeration 
*/
typedef enum
{
    PORT_PIN_IN = 0,        /**< @brief Sets port pin as input. */
    PORT_PIN_OUT,           /**< @brief Sets port pin as output. */
    PORT_PIN_INOUT          /**< @brief Sets port pin as bidirectional. */
} Port_PinDirectionType;

/**
* @brief Different port pin modes.
* @details A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
*        The type Port_PinModeType shall be used with the function call Port_SetPinMode
* @implements Port_PinModeType_typedef
*/
typedef uint8 Port_PinModeType;

/*
* @brief Data type for the number, mentioned in platform spec, of a port pin.
*        It is the same with the index of the PCR/MSCR register.
* @details Shall cover all available port pins.
* 
*/
typedef uint16 Port_InternalPinIdType;

/**
* @brief   A SIUL2 register value.
* @details A port register shall be written with a 32 bits value (type Port_RegValueType).
*          The type Port_RegValueType shall be used with the function call Port_SetPinMode
* 
*/
typedef uint32 Port_RegValueType;

/**
* @brief   Single pin configuration.
* @details This structure contains all configuration parameters of a single pin
*          identified by @p SIUPin.
* 
* @api
*/
typedef struct
{
    VAR(Port_InternalPinIdType, PORT_VAR) u16SIUPin; /**< @brief Pin Defined on Part SIUx */
    VAR(uint32,                 PORT_VAR) u32MSCR;   /**< @brief Pad Control Register */
    VAR(uint8,                  PORT_VAR) u8PDO;     /**< @brief Pad Data Output */
    VAR(uint8,                  PORT_VAR) u8PDDir;   /**< @brief Pad Data Direction */
    VAR(boolean,                PORT_VAR) bGPIO;     /**< @brief GPIO initial mode*/
    VAR(boolean,                PORT_VAR) bDC;       /**< @brief Direction changebility*/
    VAR(boolean,                PORT_VAR) bMC;       /**< @brief Mode changebility*/
} Port_Siul2_PinConfigType;

/**
* @brief   Default pin configuration.
* @details This structure contains all configuration parameters of a Default pin
*
* @api
*/
typedef struct
{
    VAR(uint32, PORT_VAR)   u32MSCR;   /**< Pad Control Register */
    VAR(uint8,  PORT_VAR)   u8PDO;    /**< Pad Data Output */
} Port_Siul2_UnUsedPinConfigType;

/**
* @brief Data type used for Pad Selection Multiplexed Configuration.
* @details This type should be chosen for the specific MCU platform (best performance).
*
* @api
*/
typedef uint32 Port_Siul2_PadSelConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/


#ifdef __cplusplus
}
#endif
/* PORT_SIUL2_TYPES_H */
#endif
/** @} */
