/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Port_SIUL2.c $
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
*   @file    Port_Siul2.c
*
*   @version 1.0.0
*
*   @brief   AUTOSAR Port - SIUL2 Low level driver implementation.
*   @details Implementation of the SIUL2 low level driver.
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
#ifdef __cplusplus
extern "C" {
#endif

/**
*  @page misra_violations MISRA-C:2004 violations
*
*  @section Port_Siul2_C_REF_1
*  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
*  '#include'. This is an Autosar requirement about the memory management.
*
*  @section Port_Siul2_C_REF_2
*  Violates MISRA 2004 Required Rule 10.1, Implicit conversion changes signedness, and 10.3,
*  Cast of complex integer expression to larger type.
*  All the type conversions are implemented in MACROS. The code was tested successfully.
*
*  @section Port_Siul2_C_REF_3
*  Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*  There are different kinds of execution code sections.
*
*  @section Port_Siul2_C_REF_4
*  Violates MISRA 2004 Required Rule 1.4, Identifier clash. Define name is required by the AUTOSAR
*  specifications although it exceeds the max length of 31 characters
*
*  @section Port_Siul2_C_REF_5
*  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
*  This macro compute the address of any register by using the hardware offset of the controller.
*  The address calculated as an unsigned int is passed to  a macro for initializing the pointer
*  with that address. (ex: see REG_WRITE32 macro).
*
*  @section Port_Siul2_C_REF_6
*  Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator:
*  '||'; the -strong(B,...) option can help provide Boolean-by-enforcement.
*  Booleans operands are not used for logical operators '&&', '||' and '!'
*
*  @section Port_Siul2_C_REF_7
*  Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used.
*  This violation is due to the use of pointer arithmetic, to access the channel parameters,
*  the indexing of the pointer is taken care and hence the unintended memory location will not
*  be accessed.
*
*  @section Port_Siul2_C_REF_8
*  Violates MISRA 2004 Required Rule 10.3, The value of a complex expression of integer type
*  may only be cast to a type that is narrower and of the same signedness as the underlying
*  type of the expression.pointer arithmetic other than array indexing used.
*  All the type conversions are implemented in MACROS. The code was tested successfully.
*
*  @section [global]
*  Violates MISRA 2004 Required Rule 5.1, Identifiers(internal and external) shall not rely 
*  on the significance of more than 31 characters.The used compilers use more than 31 chars
*  for identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "modules.h"
#include "Port.h"
#include "Reg_eSys_Siul2.h"
#include "Port_Siul2.h"
#include "SchM_Port.h"

#define USER_MODE_REG_PROT_ENABLED (PORT_USER_MODE_SOFT_LOCKING)
#include "SilRegMacros.h"

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define PORT_SIUL2_VENDOR_ID_C                     43
/* @violates @ref Port_Siul2_C_REF_4 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C      4
/* @violates @ref Port_Siul2_C_REF_4 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C      0
/* @violates @ref Port_Siul2_C_REF_4 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_SIUL2_AR_RELEASE_REVISION_VERSION_C   3
#define PORT_SIUL2_SW_MAJOR_VERSION_C              1
#define PORT_SIUL2_SW_MINOR_VERSION_C              0
#define PORT_SIUL2_SW_PATCH_VERSION_C              0

/*=================================================================================================
*                                      FILE VERSION CHECKS
=================================================================================================*/

/* Check if Port_Siul2.c and Port.h are of the same vendor */
#if (PORT_SIUL2_VENDOR_ID_C != PORT_VENDOR_ID)
    #error "Port_Siul2.c and Port.h have different vendor ids"
#endif
/* Check if Port_Siul2.c and Port.h are of the same Autosar version */
#if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_SIUL2_AR_RELEASE_REVISION_VERSION_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
   #error "AutoSar Version Numbers of Port_Siul2.c and Port.h are different"
#endif
/* Check if Port_Siul2.c and Port.h are of the same software version */
#if ((PORT_SIUL2_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SIUL2_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SIUL2_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION)    \
    )
  #error "Software Version Numbers of Port_Siul2.c and Port.h are different"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same vendor */
#if (PORT_SIUL2_VENDOR_ID_C != PORT_SIUL2_VENDOR_ID_H)
    #error "Port_Siul2.c and Port_Siul2.h have different vendor ids"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same Autosar version */
#if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C    != PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_H) || \
     (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C    != PORT_SIUL2_AR_RELEASE_MINOR_VERSION_H) || \
     (PORT_SIUL2_AR_RELEASE_REVISION_VERSION_C != PORT_SIUL2_AR_RELEASE_REVISION_VERSION_H) \
    )
  #error "AutoSar Version Numbers of Port_Siul2.c and Port_Siul2.h are different"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same software version */
#if ((PORT_SIUL2_SW_MAJOR_VERSION_C != PORT_SIUL2_SW_MAJOR_VERSION_H) || \
     (PORT_SIUL2_SW_MINOR_VERSION_C != PORT_SIUL2_SW_MINOR_VERSION_H) || \
     (PORT_SIUL2_SW_PATCH_VERSION_C != PORT_SIUL2_SW_PATCH_VERSION_H)    \
    )
  #error "Software Version Numbers of Port_Siul2.c and Port_Siul2.h are different"
#endif

/* Check if Port_Siul2.c and Reg_eSys_Siul2.h are of the same vendor */
#if (PORT_SIUL2_VENDOR_ID_C != REGESYS_SIUL2_VENDOR_ID)
    #error "Port_Siul2.c and Reg_eSys_Siul2.h have different vendor ids"
#endif
/* Check if Port_Siul2.c and Reg_eSys_Siul2.h are of the same Autosar version */
#if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C    != REGESYS_SIUL2_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C    != REGESYS_SIUL2_AR_RELEASE_MINOR_VERSION) || \
     (PORT_SIUL2_AR_RELEASE_REVISION_VERSION_C != REGESYS_SIUL2_AR_RELEASE_REVISION_VERSION) \
    )
   #error "AutoSar Version Numbers of Port_Siul2.c and Reg_eSys_Siul2.h are different"
#endif
/* Check if Port_Siul2.c and Reg_eSys_Siul2.h are of the same software version */
#if ((PORT_SIUL2_SW_MAJOR_VERSION_C != REGESYS_SIUL2_SW_MAJOR_VERSION) || \
     (PORT_SIUL2_SW_MINOR_VERSION_C != REGESYS_SIUL2_SW_MINOR_VERSION) || \
     (PORT_SIUL2_SW_PATCH_VERSION_C != REGESYS_SIUL2_SW_PATCH_VERSION)    \
    )
  #error "Software Version Numbers of Port_Siul2.c and Reg_eSys_Siul2.h are different"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same vendor */
#if (PORT_SIUL2_VENDOR_ID_C != PORT_SIUL2_VENDOR_ID_H)
    #error "Port_Siul2.c and Port_Siul2.h have different vendor ids"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same Autosar version */
#if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C    != PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_H) || \
     (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C    != PORT_SIUL2_AR_RELEASE_MINOR_VERSION_H) || \
     (PORT_SIUL2_AR_RELEASE_REVISION_VERSION_C != PORT_SIUL2_AR_RELEASE_REVISION_VERSION_H) \
    )
   #error "AutoSar Version Numbers of Port_Siul2.c and Port_Siul2.h are different"
#endif
/* Check if Port_Siul2.c and Port_Siul2.h are of the same software version */
#if ((PORT_SIUL2_SW_MAJOR_VERSION_C != PORT_SIUL2_SW_MAJOR_VERSION_H) || \
     (PORT_SIUL2_SW_MINOR_VERSION_C != PORT_SIUL2_SW_MINOR_VERSION_H) || \
     (PORT_SIUL2_SW_PATCH_VERSION_C != PORT_SIUL2_SW_PATCH_VERSION_H)    \
    )
  #error "Software Version Numbers of Port_Siul2.c and Port_Siul2.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Port_Siul2.c and SilRegMacros.h are of the same version */
    #if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Port_Siul2.c and SilRegMacros.h are different"
    #endif
    /* Check if the files Port_Siul2.c and modules.h are of the same version */
   #if ((PORT_SIUL2_AR_RELEASE_MAJOR_VERSION_C != MODULES_AR_RELEASE_MAJOR_VERSION_H) || \
        (PORT_SIUL2_AR_RELEASE_MINOR_VERSION_C != MODULES_AR_RELEASE_MINOR_VERSION_H)    \
       )
       #error "AutoSar Version Numbers of Port_Siul2.c and modules.h are different"
   #endif
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/

#define PORT_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
*  @violates @ref Port_Siul2_C_REF_3 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

#if (STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief    Segment descriptor for data arranged in array
* @detail   Port_Siul2_aGPIODirChangeability variable is only used by PORT_Siul_SetPinDirection
*           and PORT_Siul_SetPinMode functions
*/
STATIC VAR(uint16, PORT_VAR) Port_Siul2_aGPIODirChangeability[PAD_16BLOCK_NO_U8];
#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) */

#define PORT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/**
* @violates @ref Port_Siul2_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1
* @violates @ref Port_Siul2_C_REF_3 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/
#define PORT_START_SEC_CODE
/**
* @violates @ref Port_Siul2_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1
* @violates @ref Port_Siul2_C_REF_3 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/

/**
* @brief        Initializes the SIUL2 IP Driver
* @details      The function Port_Siul2_Init will initialize ALL ports and port pins with the
*               configuration set pointed to by the parameter pConfigPtr.
*
* @param[in]    pConfigPtr  A pointer to the structure which contains initialization parameters
*
* @return none
*
* @pre    none
* @post   No function of the driver is executed without the initialisation of the module.
*
*
*/
FUNC(void, PORT_CODE) Port_Siul2_Init
(
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) pConfigPtr
)
{
    /* Initialize all variables */
    VAR(uint16, AUTOMATIC) u16PinIndex;
    VAR(uint16, AUTOMATIC) u16MuxIndex;

    VAR(uint16, AUTOMATIC) u16NumUnusedPins = (uint16)(pConfigPtr->u16NumUnusedPins);
    VAR(uint16, AUTOMATIC) u16NumPins       = (uint16)(pConfigPtr->u16NumPins);
    VAR(uint16, AUTOMATIC) u16NumMuxRegs    = PORT_NMBR_INMUX_REGS_U16;

    /**
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    */
    VAR(uint32, AUTOMATIC) u32LocalMSCR = pConfigPtr->pUnusedPadConfig->u32MSCR;
    /**
    * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
    * Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to
    * larger type
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    */
    VAR(uint8,  AUTOMATIC) u8LocalPDO = pConfigPtr->pUnusedPadConfig->u8PDO;
    VAR(uint32, AUTOMATIC) u32LocalVar;
    VAR(uint16, AUTOMATIC) u16PcrPin;
    VAR(Port_InternalPinIdType, AUTOMATIC) PinPad;
    
    /* Initialize All UnUsed Port Pins */
    for (u16PinIndex = (uint16)0U; u16PinIndex < u16NumUnusedPins; u16PinIndex++)
    {
        /**
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        u16PcrPin = pConfigPtr->au16UnusedPads[u16PinIndex];

        /**
        * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
        * Implicit conversion changes signedness
        * @violates @ref Port_Siul2_C_REF_8 Violates MISRA 2004 Required Rules 10.3,
        * Cast of complex integer expression to larger type
        * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        REG_WRITE8(SIUL2_GPDO_ADDR8(u16PcrPin), u8LocalPDO);
        /* Write MSCR configuration from Configuration tool */
        /**
        * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)u16PcrPin), u32LocalMSCR);
    }

    /* Initialize All Configured Port Pins */
    for (u16PinIndex = (uint16)0U; u16PinIndex < u16NumPins; u16PinIndex++)
    {
        /**
        * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        PinPad = (uint16)(pConfigPtr->pUsedPadConfig[u16PinIndex].u16SIUPin);

        /**
        * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1,
        * Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to
        * larger type
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        u8LocalPDO = pConfigPtr->pUsedPadConfig[u16PinIndex].u8PDO;

        /**
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        if (pConfigPtr->pUsedPadConfig[u16PinIndex].bGPIO)
        {
            /* Set pin to High value */
            if (PORT_PIN_LEVEL_HIGH_U8 == u8LocalPDO)
            {
                /**
                * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
                * Implicit conversion changes signedness
                * @violates @ref Port_Siul2_C_REF_8 Violates MISRA 2004 Required Rules 10.3,
                * Cast of complex integer expression to larger type
                * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
                * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
                */
                REG_WRITE8( SIUL2_GPDO_ADDR8(PinPad), (uint8)STD_HIGH );
            }
            /* Set pin to Low value */
            else if (PORT_PIN_LEVEL_LOW_U8 == u8LocalPDO)
            {
                /**
                * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
                * Implicit conversion changes signedness
                * @violates @ref Port_Siul2_C_REF_8 Violates MISRA 2004 Required Rules 10.3,
                * Cast of complex integer expression to larger type
                * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
                * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
                */
                REG_WRITE8( SIUL2_GPDO_ADDR8(PinPad), (uint8)STD_LOW );
            }
            else
            {
                /* No action to be done */
            }
        }
        else
        {
            /* No action to be done */
        }
       /**
       * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
       * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type
       * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
       * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 
       */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinPad), (uint32)(pConfigPtr->pUsedPadConfig[u16PinIndex].u32MSCR));
    }

    /* Write Multiplexed Pad configuration registers from Configuration tool */
    for (u16MuxIndex= (uint16)0U; u16MuxIndex < u16NumMuxRegs; u16MuxIndex++)
    {
        /* Write MSCR configuration from Configuration tool */

        /**
        * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1,
        * Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to larger type.
        * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        u32LocalVar = ((uint32)(pConfigPtr->pPadSelConfig[u16MuxIndex]));

        if (SIUL2_INMUX_UNUSED_PATTERN_U32 != u32LocalVar)
        {
            /**
            * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1,
            * Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to
            * larger type.
            * @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer
            * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
            */
            u32LocalVar = ((uint32)(pConfigPtr->pPadSelConfig[u16MuxIndex])<<SIUL2_IMCR_SSS_OFFSET_U32);
            /* Set all reserved bits of the IMCR register to their reset value */
            u32LocalVar|= SIUL2_IMCR_RESET_MASK_U32;
            /** @violates @ref Port_Siul2_C_REF_5 Cast from unsigned long to pointer */
            REG_WRITE32( SIUL2_IMCR_ADDR32((uint32)u16MuxIndex),u32LocalVar ); 
        }
    }

#if (STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API)
    /* Port_Siul2_aGPIODirChangeability is only used by PORT_Siul_SetPinDirection and PORT_Siul_SetPinMode functions */
    /* Initialize the Array with Change Direction Flags for GPIO */
    for (u16PinIndex=(uint16)0U; u16PinIndex < PAD_16BLOCK_NO_U8; u16PinIndex++)
    {
        Port_Siul2_aGPIODirChangeability[u16PinIndex] = (uint16)0UL;
    }
#endif
}


#if (STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief   Sets the port pin direction
* @details Sets the pin direction at runtime, changing it only if the pin is configurated as
*          changeable.
*
* @param[in]     PinIndex      Pin ID number
* @param[in]     eDirection      Port Pin direction
* @param[in]     pConfigPtr      A pointer to the structure which contains initialization parameters
*
* @return Error code after execution
* @retval 0   No error occured
* @retval 1   Pin direction cannot be changed
*
* @pre Port_Init must have been called
* @post none
*
*
*/
FUNC (Std_ReturnType, PORT_CODE) Port_Siul2_SetPinDirection
(
    VAR    (Port_PinType,          AUTOMATIC                 ) PinIndex,
    VAR    (Port_PinDirectionType, AUTOMATIC                 ) eDirection,
    P2CONST(Port_ConfigType,       AUTOMATIC, PORT_APPL_CONST) pConfigPtr
)
{
    /* Point to the Port Pin MSCR register address */
    /**
    * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    */
    VAR(uint16, AUTOMATIC) u16PinPad = (uint16)pConfigPtr->pUsedPadConfig[PinIndex].u16SIUPin;

    /* Return value */
    VAR(Std_ReturnType, AUTOMATIC) PinDirError = (Std_ReturnType)E_OK;

    /* Bit Offset and Table value for change direction flag word*/
    VAR(uint8,  AUTOMATIC) u8PinDescBitOffset = (uint8)((uint8)u16PinPad & SIUL2_BIT_OFFSET_MASK_U8);
    VAR(uint16, AUTOMATIC) u16PinChangeDirFlagWord = Port_Siul2_aGPIODirChangeability[(uint8)(u16PinPad>>4)];

    /* Check the Direction changeability option */
    /**
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    * @violates @ref Port_Siul2_C_REF_6 Violates MISRA 2004 Required Rule 12.6
    * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
    * Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to larger type
    */
    if (((boolean)TRUE == pConfigPtr->pUsedPadConfig[PinIndex].bDC) || \
        ((uint16)0 != (u16PinChangeDirFlagWord & (uint16)(1UL<<u8PinDescBitOffset))))
    {
        /* Configures Port Pin as Output */
        if (PORT_PIN_OUT == eDirection)
        {
            /**
            * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
            * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type.
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_IBE_ON_U32);
            
#if defined(IPV_SIUL2_ODC_SUPPORT_U8)
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_ODC_PUSH_PULL_U32 );
#else
            /**
            * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
            * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type.
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_OBE_ON_U32 );
#endif
        }
        /* Configures Port Pin as Input */
        else if (PORT_PIN_IN == eDirection)
        {
#if defined(IPV_SIUL2_ODC_SUPPORT_U8)       
            /**
            * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
            * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type.
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_ODC_PUSH_PULL_U32);
#else
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_OBE_ON_U32);
#endif
            
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_IBE_ON_U32);
        }
        else
        {
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_IBE_ON_U32);

#if defined(IPV_SIUL2_ODC_SUPPORT_U8)
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_ODC_PUSH_PULL_U32);
#else
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
            */
            REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_OBE_ON_U32);
#endif
        }
    }
    /* Direction changeability is NOT supported */
    else
    {
        PinDirError = (Std_ReturnType)E_NOT_OK;
    }

    return PinDirError;
}
#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_SET_PIN_MODE_API) */


#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief   Sets the port pin mode.
* @details The function will set the port pin mode of the referenced pin during runtime
*
* @param[in]     PinCfgRegIndex         Index of Register MSCR
* @param[in]     PinCfgRegValue         Value of Register MSCR
* @param[in]     u16InMuxRegIndex       Index of Register IMCR
* @param[in]     InMuxRegValue          Value of Register IMCR
*
* @return Error code after execution
* @retval 0   No error occured
* @retval PORT_E_MODE_UNCHANGEABLE   Pin mode cannot be changed
* @retval PORT_E_PARAM_INVALID_MODE  Invalid mode
*
* @pre Port_Init must have been called
* @post none
*
*
*/
FUNC (void, PORT_CODE) Port_Siul2_SetPinMode
(
    VAR(Port_InternalPinIdType, AUTOMATIC) PinCfgRegIndex,
    VAR(Port_RegValueType,  AUTOMATIC) PinCfgRegValue,
    VAR(uint16,             AUTOMATIC) u16InMuxRegIndex,
    VAR(Port_RegValueType,  AUTOMATIC) InMuxRegValue
)
{
    /* Variable used to clear and updated MSCR register*/
    VAR(uint32, AUTOMATIC) u32LocalVar = (uint32)0U;

    if (SIUL2_INPUT_ACTIVE_U32 == PinCfgRegValue)
    {
        /* Set the INPUT mode in MSCR */
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), SIUL2_MSCR_IBE_U32);
    }
    else if (SIUL2_OUTPUT_ACTIVE_U32 == PinCfgRegValue)
    {
        /* Set the OUTPUT mode in MSCR */
#if defined(IPV_SIUL2_ODC_SUPPORT_U8)
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), SIUL2_MSCR_ODC_PUSH_PULL_U32);
#else
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), SIUL2_MSCR_OBE_U32);
#endif    
    }
    else
    {
        if (PORT_ANALOG_INPUT_MODE == PinCfgRegValue)
        {
            /* Set the ANALOGICAL mode in PCR */
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), SIUL2_MSCR_APC_U32);
        }
        else
        {
            /* Clear the previous mode */
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            u32LocalVar = REG_READ32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex));
            u32LocalVar &= ~(SIUL2_MSCR_SSS_U32 | SIUL2_MSCR_APC_U32);

            /* Set the proper mode in MSCR */
            u32LocalVar |= ((uint32)PinCfgRegValue<<SIUL2_MSCR_SSS_OFFSET_U32);
            /**
            * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
            */
            REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), u32LocalVar);
        }
    }

    if (NO_INPUTMUX_U16 != u16InMuxRegIndex)
    {
        /* Set the proper values in IMCR */
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        REG_WRITE32(SIUL2_IMCR_ADDR32((uint32)u16InMuxRegIndex), InMuxRegValue | SIUL2_IMCR_RESET_MASK_U32);

        /* Set the MSCR/IBE bit */
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        u32LocalVar = REG_READ32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex));
        u32LocalVar |= ((uint32)SIUL2_MSCR_IBE_U32);
        /**
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        */
        REG_WRITE32(SIUL2_MSCR_ADDR32((uint32)PinCfgRegIndex), u32LocalVar);
    }
}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */


#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief    Sets or resets the direction changeability for pads in GPIO mode.
* @details  The function will update the direction changeabilty for the pads whose mode is changed
*
* @param[in] PadID          Pin ID number.
* @param[in] bStatus        The new value true or falsr for directuion changeability.
*
* @return    None
*
* @pre  none
* @post none
*
*
*/
FUNC (void, PORT_CODE) Port_Siul2_SetGpioDirChangeability
(
    VAR(Port_InternalPinIdType, AUTOMATIC) PadID,
    VAR(boolean,            AUTOMATIC) bStatus
)
{
    /* Pin description variables */
    VAR(uint16, AUTOMATIC) u16PinDirFlagWord;
    VAR(uint8, AUTOMATIC) u8PinBitOffset;

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02();
    /* Bit offset of Pin index inside the pin description matrix */
    u8PinBitOffset    = (uint8)((uint8)PadID & SIUL2_BIT_OFFSET_MASK_U8);
    u16PinDirFlagWord = Port_Siul2_aGPIODirChangeability[(uint8)((uint8)PadID>>4)];

    if ((boolean)TRUE == bStatus)
    {
        /* Set the change direction flag */
        u16PinDirFlagWord |= (uint16)(1UL<<u8PinBitOffset);
    }
    else
    {   /* Reset the change direction flag */
        u16PinDirFlagWord &= (uint16)(~((uint16)(1UL<<u8PinBitOffset)));
    }
    Port_Siul2_aGPIODirChangeability[(uint8)((uint8)PadID>>4)] = u16PinDirFlagWord;
    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02();
}

/**
* @brief    Sets the output status of the pads in GPIO mode.
* @details  The function will update the output for the pads whose mode is changed
*
* @param[in] PinIndex     Pin ID number.
* @param[in] pConfigPtr     A pointer to the structure which contains initialization parameters
*
*
* @return    None
*
* @pre  none
* @post none
*
*
*/
FUNC (void, PORT_CODE) Port_Siul2_SetGpioPadOutput
(
    VAR    (Port_PinType,    AUTOMATIC                 ) PinIndex,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) pConfigPtr
)
{
    /**
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    */
    VAR(uint16, AUTOMATIC) u16PinPad = (uint16)(pConfigPtr->pUsedPadConfig[PinIndex].u16SIUPin);
    /**
    * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
    */
    VAR(uint8, AUTOMATIC) u8LocalPDO = pConfigPtr->pUsedPadConfig[PinIndex].u8PDO;

    /* Set pin to High value */
    if (PORT_PIN_LEVEL_HIGH_U8 == u8LocalPDO)
    {
        /**
        * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
        * Implicit conversion changes signedness
        * @violates @ref Port_Siul2_C_REF_8 Violates MISRA 2004 Required Rules 10.3,
        * Cast of complex integer expression to larger type
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        REG_WRITE8( SIUL2_GPDO_ADDR8(u16PinPad), (uint8)STD_HIGH );
    }
    /* Set pin to Low value */
    else if (PORT_PIN_LEVEL_LOW_U8 == u8LocalPDO)
    {
        /**
        * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1
        * Implicit conversion changes signedness
        * @violates @ref Port_Siul2_C_REF_8 Violates MISRA 2004 Required Rules 10.3,
        * Cast of complex integer expression to larger type
        * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
        * @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4
        */
        REG_WRITE8( SIUL2_GPDO_ADDR8(u16PinPad), (uint8)STD_LOW );
    }
    else
    {
        /* No action to be done */
    }
}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */


/**
* @brief   Refreshes port direction.
* @details This service shall refresh the direction of all configured ports to the configured
*          direction. The PORT driver shall exclude from refreshing those port pins that are
*          configured as pin direction changeable during runtime.
*
* @param[in]     numPins    Number of pins to be refreshed
* @return none
*
* @pre Port_Init must have been called
* @post none
*
*/
FUNC (void, PORT_CODE) Port_Siul2_RefreshPortDirection
(
    P2CONST(Port_ConfigType, AUTOMATIC,PORT_APPL_CONST) pConfigPtr
)
{
    VAR(uint16, AUTOMATIC) u16NumPins = pConfigPtr->u16NumPins;
    /* Index of the port table */
    VAR(uint16, AUTOMATIC) u16PinIndex;
    VAR(uint16, AUTOMATIC) u16PinPad;
    
    /* Initialize All Configured Port Pins that aren't direction changable */
    for (u16PinIndex = (uint16)0U; u16PinIndex < u16NumPins; u16PinIndex++)
    {
        /* @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 */
        /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        if ((boolean)FALSE == pConfigPtr->pUsedPadConfig[u16PinIndex].bDC)
        {
            /* Point to the Port Pin MSCR register address*/
            /* @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 */
            /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            u16PinPad = (uint16)pConfigPtr->pUsedPadConfig[u16PinIndex].u16SIUPin;

            /* Enter critical region KK*/
            SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01();
        
            /* Configures Port Pin as Output */
#if defined(IPV_SIUL2_ODC_SUPPORT_U8)
           /* @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 */
           /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            if (pConfigPtr->pUsedPadConfig[u16PinIndex].u32MSCR & SIUL2_MSCR_ODC_PUSH_PULL_U32)
            {
                /**
                * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
                */
                REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_ODC_PUSH_PULL_U32 );
            }
#else
           /* @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 */
           /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            if (pConfigPtr->pUsedPadConfig[u16PinIndex].u32MSCR & SIUL2_MSCR_OBE_U32)
            {
                /**
                * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
                * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type.
                * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
                */
                REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_OBE_ON_U32 );
            }
#endif
            else
            {
#if defined(IPV_SIUL2_ODC_SUPPORT_U8)       
                /**
                * @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1, Implicit
                * conversion changes signedness, and 10.3, Cast of complex integer expression to larger type.
                * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
                */
                REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_ODC_PUSH_PULL_U32);
#else
                /**
                * @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer
                */
                REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_OBE_ON_U32);
#endif            
            }
            /* Configures Port Pin as Input */
            /* @violates @ref Port_Siul2_C_REF_7 Violates MISRA 2004 Required Rule 17.4 */
            /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            if (pConfigPtr->pUsedPadConfig[u16PinIndex].u32MSCR & SIUL2_MSCR_IBE_U32)
            {
                /* @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1,
                   Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to larger type.*/
                /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_SET32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_IBE_U32);
            }
            else
            {
                /* @violates @ref Port_Siul2_C_REF_2 Violates MISRA 2004 Required Rules 10.1,
                   Implicit conversion changes signedness,and 10.3,Cast of complex integer expression to larger type.*/
                /* @violates @ref Port_Siul2_C_REF_5 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                REG_BIT_CLEAR32(SIUL2_MSCR_ADDR32((uint32)u16PinPad), SIUL2_MSCR_IBE_U32);
           }
           /* Exit critical region */
           SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01();
        }
    }
}


#define PORT_STOP_SEC_CODE
/**
* @violates @ref Port_Siul2_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
* @violates @ref Port_Siul2_C_REF_3 Violates MISRA 2004 Advisory Rule 19.15, Repeated include
* file MemMap.h
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
