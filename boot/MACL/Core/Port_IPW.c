/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Port_IPW.c $
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
*   @file    Port_Ipw.c
*
*   @version 1.0.0
*   @brief   AUTOSAR Port - PORT driver midle level driver.
*   @details Implementation of the AutoSar midle level PORT driver.
*
*   @addtogroup Port
*   @{
*/
/*=================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.0.
*                          3
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
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_IPW_C_REF_1
*          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
*          '#include'. This is an Autosar memory management requirement.
*
* @section PORT_IPW_C_REF_2
*          Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*          There are different kinds of execution code sections.
*
* @section PORT_IPW_C_REF_3
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external
*          identifiers. The defines are ok.
*
* @section PORT_IPW_C_REF_4
*          Violates MISRA 2004 Required Rule 10.5, Shift left of signed quantity(int)
*          The violation is FALSE: the quantity is unsigned.
*
* @section PORT_IPW_C_REF_5
*          Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form
*          of pointer. The violation is FALSE: the quantity is unsigned.
*
* @section PORT_IPW_C_REF_6
*          Violates MISRA 2004 Required Rule 16.10, If a function returns error information, then
*          that error information shall be tested.
*          The function is called with the fault condition previousely disabled.
*
* @section PORT_IPW_C_REF_7
*          Violates MISRA 2004 Advisory Rule 12.1, Limited dependence should be placed on C's
*          operator precedence rules in expressions.
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not
*          rely on the significance of more than 31 characters. The used compilers use more than
*          31 chars for identifiers.
*
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Port_Ipw.h"
#include "Port.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*
*/
#define PORT_VENDOR_ID_IPW_C                    43

/**
* @violates @ref PORT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*   ensure that 31 character significance and case sensitivity are supported for external
*   identifiers.
*/
#define PORT_AR_RELEASE_MAJOR_VERSION_IPW_C     4

/**
* @violates @ref PORT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*   ensure that 31 character significance and case sensitivity are supported for external
*   identifiers.
*/
#define PORT_AR_RELEASE_MINOR_VERSION_IPW_C     0

/**
* @violates @ref PORT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*   ensure that 31 character significance and case sensitivity are supported for external
*   identifiers.
*/
#define PORT_AR_RELEASE_REVISION_VERSION_IPW_C  3

#define PORT_SW_MAJOR_VERSION_IPW_C             1
#define PORT_SW_MINOR_VERSION_IPW_C             0
#define PORT_SW_PATCH_VERSION_IPW_C             0


/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if source file and Port_Ipw.h file are of the same vendor */
#if (PORT_VENDOR_ID_IPW_C != PORT_VENDOR_ID_IPW_H)
    #error "Port_Ipw.c and Port_Ipw.h have different vendor ids"
#endif

/* Check if the source file and Port_Ipw.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_C    != PORT_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_C    != PORT_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_C != PORT_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
   #error "AutoSar Version Numbers of Port_Ipw.c and Port_Ipw.h are different"
#endif

/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_C != PORT_SW_MAJOR_VERSION_IPW_H) || \
     (PORT_SW_MINOR_VERSION_IPW_C != PORT_SW_MINOR_VERSION_IPW_H) || \
     (PORT_SW_PATCH_VERSION_IPW_C != PORT_SW_PATCH_VERSION_IPW_H)    \
    )
  #error "Software Version Numbers of Port_Ipw.c and Port_Ipw.h are different"
#endif

/* Check if source file and Port header file are of the same vendor */
#if (PORT_VENDOR_ID_IPW_C != PORT_VENDOR_ID)
    #error "Port_Ipw.c and Port.h have different vendor ids"
#endif

/* Check if source file and Port header file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
   #error "AutoSar Version Numbers of Port_Ipw.c and Port.h are different"
#endif

/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_IPW_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_IPW_C != PORT_SW_PATCH_VERSION)    \
    )
  #error "Software Version Numbers of Port_Ipw.c and Port.h are different"
#endif

/*=================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
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
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL FUNCTIONS
=================================================================================================*/

#define PORT_START_SEC_CODE
/**
* @violates @ref PORT_IPW_C_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                      GLOBAL FUNCTIONS
=================================================================================================*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief   Sets the port pin mode.
* @details The function @p Port_Ipw_SetPinMode will set the port pin mode of the
*          referenced pin during runtime.
* @pre     @p Port_Init() must have been called first.

* @param[in] PinIndex       Pin ID number.
* @param[in] PinMode        New Port Pin mode to be set on port pin.
* @param[in] pConfigPtr     Pointer to the initialization data structure
*
* @implements PORT_IPW_SetPinMode_Activity
* @api
*/
FUNC(Std_ReturnType, PORT_CODE) Port_Ipw_SetPinMode
(
    VAR    (Port_PinType,     AUTOMATIC                 ) PinIndex,
    VAR    (Port_PinModeType, AUTOMATIC                 ) PinMode,
    P2CONST(Port_ConfigType,  AUTOMATIC, PORT_APPL_CONST) pConfigPtr
)
{
    VAR(Std_ReturnType,     AUTOMATIC) PinModeError = (Std_ReturnType)0UL;
    /** @violates @ref PORT_IPW_C_REF_5 MISRA 2004 Required Rule 17.4 */
    VAR(Port_InternalPinIdType, AUTOMATIC) PinPad = pConfigPtr->pUsedPadConfig[PinIndex].u16SIUPin;

    VAR(uint16,               AUTOMATIC) u16PinDescWord;
    VAR(uint8,                AUTOMATIC) u8PinDescBitOffset;
    VAR(uint8,                AUTOMATIC) u8PinModeIndex;
    VAR(Port_InMuxSettingType,AUTOMATIC) PadInMuxData;

    VAR(Port_InternalPinIdType, AUTOMATIC) PinCfgRegIndex   = (Port_InternalPinIdType)PinPad;
    VAR(Port_RegValueType,      AUTOMATIC) PinCfgRegValue   = (Port_RegValueType)PinMode;
    VAR(uint16,                 AUTOMATIC) u16InMuxRegIndex = NO_INPUTMUX_U16;
    VAR(Port_RegValueType,      AUTOMATIC) InMuxRegValue    = (Port_RegValueType)0UL;
    VAR(uint16,                 AUTOMATIC) u16Index;

    VAR(Port_PinDirectionType, AUTOMATIC) ePadDirection;

    if (PAD_MODE_OPTIONS_U8 <= PinMode)
    {
        PinModeError = PORT_E_PARAM_INVALID_MODE;
    }
    else
    {
        ePadDirection = (Port_PinDirectionType)0UL;

        /* Bit offset of Pin index inside the pin description matrix */
        u8PinDescBitOffset = (uint8)(PinPad & SIUL2_MODE_BIT_OFFSET_MASK_U8);
        /* Selected word inside the pin description matrix */
        u16PinDescWord = (uint16)Port_au16PinDescription[(uint8)PinMode][(uint8)((uint8)PinPad>>4)];

        /* Check if desired mode is valid for selected pin */
        if (u16PinDescWord & (uint16)(1UL<<u8PinDescBitOffset))
        {
            switch(PinMode)
            {
                case PORT_INPUT1_MODE:
                case PORT_INPUT2_MODE:
                case PORT_INPUT3_MODE:
                case PORT_INPUT4_MODE:
                case PORT_INPUT5_MODE:
                    /* All the INPUT modes */
                    u16Index         = Port_au16PadFunctInMuxIndex[PinPad];
                    /** @violates @ref PORT_IPW_C_REF_7 MISRA 2004 Advisory Rule 12.1 */
                    PadInMuxData     = Port_aPadFunctInMuxSettings[u16Index + PinMode - PORT_INPUT1_MODE];
                    u16InMuxRegIndex = (uint16)PadInMuxData.u16InMuxId;
                    InMuxRegValue    = PadInMuxData.u8InMuxCode;
                    PinCfgRegValue   = SIUL2_INPUT_ACTIVE_U32;
                    Port_Siul2_SetGpioDirChangeability(PinPad,(boolean)FALSE);
                    break;

                case PORT_GPIO_MODE:
                    Port_Siul2_SetGpioDirChangeability(PinPad,(boolean)TRUE);
                    /** @violates @ref PORT_IPW_C_REF_5 MISRA 2004 Required Rule 17.4 */
                    ePadDirection = (Port_PinDirectionType)(pConfigPtr->pUsedPadConfig[PinIndex].u8PDDir);
                    if(PORT_PIN_IN != ePadDirection)
                    {
                        Port_Siul2_SetGpioPadOutput(PinIndex, pConfigPtr);
                    }
                    /** @violates @ref PORT_IPW_C_REF_6 MISRA 2004 Required Rule 16.10 */
                    Port_Siul2_SetPinDirection(PinIndex, ePadDirection, pConfigPtr);
                    break;

                default:
                    Port_Siul2_SetGpioDirChangeability(PinPad,(boolean)FALSE);
                    break;
            }
            /* Sets the port pin mode */
            Port_Siul2_SetPinMode(PinCfgRegIndex, PinCfgRegValue, u16InMuxRegIndex, InMuxRegValue);
        }
        else
        {
            /* Check if a possible alternative mode for this pin exists */
            for (u8PinModeIndex = (uint8)1U; u8PinModeIndex < PAD_MODE_OPTIONS_U8; u8PinModeIndex++)
            {
                u16PinDescWord = (uint16)Port_au16PinDescription[u8PinModeIndex][(uint8)(PinPad>>(uint8)4U)];
                /* A possible mode has been found */
                /** @violates @ref PORT_IPW_C_REF_4 Violates MISRA 2004 Required Rules 10.5 */
                if (u16PinDescWord & (uint16)((uint16)1U<<u8PinDescBitOffset))
                {
                   break;
                }
            }
            /* No possible modes for this pin. The mode is unchangeable */
            if (PAD_MODE_OPTIONS_U8 == u8PinModeIndex)
            {
                PinModeError = PORT_E_MODE_UNCHANGEABLE;
            }
            /* Desired mode is NOT valid for this pin. The mode is invalid */
            else
            {
                PinModeError = PORT_E_PARAM_INVALID_MODE;
            }
        }
    }
    return (PinModeError);
}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */

#define PORT_STOP_SEC_CODE
/**
* @violates @ref PORT_IPW_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor
*                 statements and comments before '#include'
* @violates @ref PORT_IPW_C_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include
*                 file MemMap.h
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
