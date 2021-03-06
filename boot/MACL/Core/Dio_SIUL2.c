/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Dio_SIUL2.c $
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
*   @file    Dio_Siul2.c
*   @implements        DIO_SIUL2_unit
*   @version 1.0.0
*
*   @brief   AUTOSAR Dio SIUL2 source file support for DIO driver.
*   @details This file is the SIUL2 DIO low level driver code.
*
*   @addtogroup DIO_SIUL2
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
===================================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
* @file    Dio_Siul2.c
* */

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Dio_Siul2_C_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file,
* Precautions shall be taken in order to prevent the contents of a header file
* being included twice This is not a violation since all header files are
* protected against multiple inclusions
*
* @section Dio_Siul2_C_REF_2
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This violation can not be avoided because it appears when addressing
* memory mapped registers or other hardware specific features.
*
* @section Dio_Siul2_C_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Dio_Siul2_C_REF_4
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Dio_Siul2_C_REF_5
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include'. This is an Autosar requirement about the memory management.
*
* @section Dio_Siul2_C_REF_7
* Violates MISRA 2004 Required Rule 8.1, Functions shall have prototype
* declarations and the prototype shall be visible at both the function
* definition and call. Function is static
*
*  @section Dio_Siul2_C_REF_8
*  Violates MISRA 2004 Required Rule 10.1, Implicit conversion changes signedness, and 10.3,
*  Cast of complex integer expression to larger type.
*  All the type conversions are implemented in MACROS. The code was tested successfully.
*
* @section Dio_Siul2_C_REF_10
* Violates MISRA 2004 Required Rule 10.3 , The value of a complex expression of integer type may only be cast
* to a type that is narrower and of the same signedness as the underlying type of the expression
* This violation is due to the value of a complex expression of integer type was cast to a type that is
* not narrower.
*
* @section Dio_Siul2_C_REF_11
* Violates MISRA 2004 Required Rule 10.5 , If the bitwise operators ~ and << are applied to an operand
* of underlying type unsigned char or unsigned shot, the result shall be immediately cast to the underlying type
* of the operand
* This violation is due to the operator << was used.
*/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Dio_Cfg.h"
#include "Dio_Ipw.h"
/* @violates @ref Dio_Siul2_C_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Dio_Siul2.h"
#define USER_MODE_REG_PROT_ENABLED (DIO_USER_MODE_SOFT_LOCKING)
#include "SilRegMacros.h"
#include "Dio_Reg_eSys_Siul2.h"
#include "SchM_Dio.h"

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_SIUL2_VENDOR_ID_C                    43
/* @violates @ref Dio_Siul2_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C     4
/* @violates @ref Dio_Siul2_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C     0
/* @violates @ref Dio_Siul2_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIUL2_AR_RELEASE_REVISION_VERSION_C  3
#define DIO_SIUL2_SW_MAJOR_VERSION_C             1
#define DIO_SIUL2_SW_MINOR_VERSION_C             0
#define DIO_SIUL2_SW_PATCH_VERSION_C             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Dio_Ipw.h version check start */
#if ((DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C != DIO_AR_RELEASE_MAJOR_VERSION_IPW) || \
     (DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C != DIO_AR_RELEASE_MINOR_VERSION_IPW) || \
     (DIO_SIUL2_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION_IPW) \
    )
    #error "AUTOSAR Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if ((DIO_SIUL2_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_IPW) || \
     (DIO_SIUL2_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_IPW) || \
     (DIO_SIUL2_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_IPW) \
    )
    #error "Software Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if (DIO_SIUL2_VENDOR_ID_C != DIO_VENDOR_ID_IPW)
    #error "VENDOR ID for Dio.c and Dio_Ipw.h is different"
#endif
/* Dio_Ipw.h version check end */

/* Dio_Siul2.h version check start */
#if ((DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C != DIO_SIUL2_AR_RELEASE_MAJOR_VERSION) || \
     (DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C != DIO_SIUL2_AR_RELEASE_MINOR_VERSION) || \
     (DIO_SIUL2_AR_RELEASE_REVISION_VERSION_C != DIO_SIUL2_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siul2.c and Dio_Siul2.h are different"
#endif

#if ((DIO_SIUL2_SW_MAJOR_VERSION_C != DIO_SIUL2_SW_MAJOR_VERSION) || \
     (DIO_SIUL2_SW_MINOR_VERSION_C != DIO_SIUL2_SW_MINOR_VERSION) || \
     (DIO_SIUL2_SW_PATCH_VERSION_C != DIO_SIUL2_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Dio_Siul2.c and Dio_Siul2.h are different"
#endif

#if (DIO_SIUL2_VENDOR_ID_C != DIO_SIUL2_VENDOR_ID)
    #error "VENDOR ID for Dio_Siul2.c and Dio_Siul2.h is different"
#endif
/* Dio_Siul2.h version check end */

/* SilRegMacros.h version check start */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if ((DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
       (DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AUTOSAR Version Numbers of Dio_Siul2.c and SilRegMacros.h are different"
  #endif
#endif
/* SilRegMacros.h version check end */

/* Dio_Reg_eSys_Siul2.h version check start */
#if ((DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C != DIO_REGESYS_SIUL2_AR_RELEASE_MAJOR_VERSION_REG) || \
     (DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C != DIO_REGESYS_SIUL2_AR_RELEASE_MINOR_VERSION_REG) || \
     (DIO_SIUL2_AR_RELEASE_REVISION_VERSION_C != DIO_REGESYS_SIUL2_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siul2.c and Dio_Reg_eSys_Siul2.h are different"
#endif

#if ((DIO_SIUL2_SW_MAJOR_VERSION_C != DIO_REGESYS_SIUL2_SW_MAJOR_VERSION_REG) || \
     (DIO_SIUL2_SW_MINOR_VERSION_C != DIO_REGESYS_SIUL2_SW_MINOR_VERSION_REG) ||\
     (DIO_SIUL2_SW_PATCH_VERSION_C != DIO_REGESYS_SIUL2_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Dio_Siul2.c and Dio_Reg_eSys_Siul2.h are different"
#endif

#if (DIO_SIUL2_VENDOR_ID_C != DIO_REGESYS_SIUL2_VENDOR_ID_REG)
    #error "VENDOR ID for Dio_Siul2.c and Dio_Reg_eSys_Siul2.h is different"
#endif
/* Dio_Reg_eSys_Siul2.h version check end */

/* Dio_Cfg.h version check start */
#if ((DIO_SIUL2_AR_RELEASE_MAJOR_VERSION_C != DIO_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (DIO_SIUL2_AR_RELEASE_MINOR_VERSION_C != DIO_AR_RELEASE_MINOR_VERSION_CFG) || \
     (DIO_SIUL2_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siul2.c and Dio_Cfg.h are different"
#endif

#if ((DIO_SIUL2_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_CFG) || \
     (DIO_SIUL2_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_CFG) ||\
     (DIO_SIUL2_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Dio_Siul2.c and Dio_Cfg.h are different"
#endif

#if (DIO_SIUL2_VENDOR_ID_C != DIO_VENDOR_ID_CFG)
    #error "VENDOR ID for Dio_Siul2.c and Dio_Cfg.h is different"
#endif
/* Dio_Cfg.h version check end */

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/

/* @violates @ref Dio_Siul2_C_REF_4 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
#define SIUL2_MPGPDO_MULTIPLIER_U32(port)   ((uint32)((port) << 0x2U))
#define SIUL2_MPGPDO_MASK_SHIFT_U8          ((uint8)16)
#define SIUL2_MPGPDO_MPPDO_MASK_U32         ((uint32)0x0000FFFFU)

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

#define DIO_START_SEC_CODE
/* @violates @ref Dio_Siul2_C_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#if ((STD_ON == DIO_REVERSEPORTBITS) || (LOW_BYTE_FIRST == CPU_BYTE_ORDER))
STATIC FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siul2_ReverseBits16
(
    VAR(Dio_PortLevelType, AUTOMATIC) Level
);
#endif /* ((STD_ON == DIO_REVERSEPORTBITS) || (LOW_BYTE_FIRST == CPU_BYTE_ORDER)) */

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

/*================================================================================================*/

#if ((STD_ON == DIO_REVERSEPORTBITS) || (LOW_BYTE_FIRST == CPU_BYTE_ORDER))
/*================================================================================================*/
/**
* @brief          Reverses bits in a 16 bits word.
*
* @param[in]      Level       Bits to be reversed.
*
* @return         The reversed 16 bits word.
*
* @pre            This function can be used only if @p DIO_REVERSEPORTBITS is
*                 enabled.
*/
STATIC FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siul2_ReverseBits16
(
    VAR(Dio_PortLevelType, AUTOMATIC) Level
)
/* @violates @ref Dio_Siul2_C_REF_7 Functions shall have prototype declarations */
{
    /* RevLevel will be reversed bits of Level */
    VAR(Dio_PortLevelType, AUTOMATIC) RevLevel = Level;
    VAR(uint16, AUTOMATIC) u16NumShifts = 15U; /* number of shifts needed due to trailing 0s */

    Level= (uint16)(Level>>1);

    for (; Level!=0U; Level = (Dio_PortLevelType)(Level >> 1U))
    {
        RevLevel = (uint16)(RevLevel<<1);
        RevLevel = (uint16)(RevLevel |((uint16)(Level & (uint16)1)));
        u16NumShifts--;
    }
    RevLevel = (uint16)(((uint32)RevLevel)<<u16NumShifts); /* Remaining shifts when Level's highest bits are zero */
    
    return RevLevel;
}
#endif /* ((STD_ON == DIO_REVERSEPORTBITS) || (LOW_BYTE_FIRST == CPU_BYTE_ORDER)) */

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

/*===============================================================================================*/
/**
* @brief          Returns the value of the specified DIO channel.
* @details        This function returns the value of the specified DIO channel.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*/
FUNC (Dio_LevelType, DIO_CODE) Dio_Siul2_ReadChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
)
{
    VAR(Dio_LevelType, AUTOMATIC) ChannelLevel = (Dio_LevelType) STD_LOW;

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    ChannelLevel = (Dio_LevelType)(REG_READ8(SIUL2_GPDI_ADDR32(ChannelId)));

    return ChannelLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall set the specified level on the
*                 specified channel. If the specified channel is configured
*                 as an input channel, this function shall have no influence
*                 on the physical output and on the result of the next read
*                 service.
*
* @param[in]      ChannelId   Specifies the required channel id.
* @param[in]      Level       Specifies the channel desired level.
*/
FUNC (void, DIO_CODE) Dio_Siul2_WriteChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId,
    CONST(Dio_LevelType,   AUTOMATIC) Level
)
{
    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    REG_WRITE8(SIUL2_GPDO_ADDR32(ChannelId), Level);
 }

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/*===============================================================================================*/
/**
* @brief          Inverts the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall invert the level of the specified
*                 channel. If the specified channel is configured as an
*                 input channel, this function shall have no influence
*                 on the physical output and on the result of the next
*                 read service.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*
* @pre            This function can be used only if @p DIO_FLIP_CHANNEL_API
*                 has been enabled.

*/
FUNC(Dio_LevelType, DIO_CODE) Dio_Siul2_FlipChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
)
{
    VAR(Dio_LevelType, AUTOMATIC) ChannelLevel = (Dio_LevelType)STD_LOW;

    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_00();

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    if ((Dio_LevelType)0 == (Dio_LevelType)(REG_READ8(SIUL2_GPDO_ADDR32(ChannelId))))
    {
        ChannelLevel = (Dio_LevelType)1;
    }
    else
    {
        ChannelLevel = (Dio_LevelType)0;
    }

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    REG_WRITE8(SIUL2_GPDO_ADDR32(ChannelId), ChannelLevel);

    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_00();

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    ChannelLevel = (Dio_LevelType)(REG_READ8(SIUL2_GPDI_ADDR32(ChannelId)));

   return ChannelLevel;
}
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

/*===============================================================================================*/
/**
* @brief          Returns the level of all channels of specified port.
* @details        This function will return the level of all channels
*                 belonging to the specified port.
*
* @param[in]      PortId      Specifies the required port id.
*
* @return                     Levels of all channels of specified port.
*/
FUNC (Dio_PortLevelType, DIO_CODE) Dio_Siul2_ReadPort
(
    CONST(Dio_PortType, AUTOMATIC) PortId
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) PortLevel = (Dio_PortLevelType)STD_LOW;

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    /* @violates @ref Dio_Siul2_C_REF_11 The operator << was used. */
    PortLevel = (Dio_PortLevelType)(REG_READ16(SIUL2_PGPDI_ADDR32(PortId)));

#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    PortLevel = (Dio_PortLevelType)(Dio_Siul2_ReverseBits16(PortLevel));
#if (STD_ON == DIO_READZERO_UNDEFINEDPORTS)
    PortLevel = (Dio_PortLevelType)(PortLevel & Dio_Siul2_ReverseBits16(Dio_aAvailablePinsForRead[PortId]));
#endif
#else
#if (STD_ON == DIO_READZERO_UNDEFINEDPORTS)
    PortLevel = (Dio_PortLevelType)(PortLevel & Dio_aAvailablePinsForRead[PortId]);
#endif
#endif

#if (STD_ON == DIO_REVERSEPORTBITS)
    PortLevel = (Dio_PortLevelType)(Dio_Siul2_ReverseBits16(PortLevel));
#endif

     return PortLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets the value of a port.
* @details        This function will set the specified value on the specified
*                 port.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
*/
FUNC (void, DIO_CODE) Dio_Siul2_WritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) CrtLevel = Level;

#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    CrtLevel = (Dio_PortLevelType)(Dio_Siul2_ReverseBits16(CrtLevel));
#endif

#if (STD_ON == DIO_REVERSEPORTBITS)
    CrtLevel = (Dio_PortLevelType)(Dio_Siul2_ReverseBits16(CrtLevel));
#endif

    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    /* @violates @ref Dio_Siul2_C_REF_10 The value of a complex expression was cast to a type that is not narrower */
    /* @violates @ref Dio_Siul2_C_REF_11 The operator << was used. */
    REG_WRITE16(SIUL2_PGPDO_ADDR32(PortId), CrtLevel);
 }

/*===============================================================================================*/
/**
* @brief          This service reads a subset of the adjoining bits of a port.
* @details        This function will read a subset of adjoining bits of a
*                 port (channel group).
*
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @return                     The channel group levels.
*/
FUNC (Dio_PortLevelType, DIO_CODE) Dio_Siul2_ReadChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) PortLevel = (Dio_PortLevelType)STD_LOW;

#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    PortLevel = REG_READ16(SIUL2_PGPDI_ADDR32((uint32)(pChannelGroupIdPtr->port)));
    PortLevel = (Dio_PortLevelType)(Dio_Siul2_ReverseBits16(PortLevel));
    PortLevel = (Dio_PortLevelType)((PortLevel & (pChannelGroupIdPtr->mask)) >> (pChannelGroupIdPtr->offset));
#else
    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    PortLevel = (Dio_PortLevelType) \
                ((REG_READ16(SIUL2_PGPDI_ADDR32((uint32)(pChannelGroupIdPtr->port))) & \
                 (pChannelGroupIdPtr->mask)) >> (pChannelGroupIdPtr->offset)           \
                );
#endif

    return PortLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets a subset of the adjoining bits of a port to the
*                 specified levels.
* @details        This function will set a subset of adjoining bits of a port
*                 (channel group) to the specified levels without changing
*                 the remaining channels of the port and channels that
*                 are configured as input.
*                 This function will do the masking of the channels and will
*                 do the shifting so that the values written by the function
*                 are aligned to the LSB.
*
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @param[in]      Level       Desired levels for the channel group.
*/
FUNC (void, DIO_CODE) Dio_Siul2_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr,
    CONST  (Dio_PortLevelType,    AUTOMATIC)                 Level
)
{
    VAR(uint32, AUTOMATIC) u32Value;
#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    VAR(uint16, AUTOMATIC) u16MpgpdoMppdo;
    VAR(uint16, AUTOMATIC) u16MpgpdoMask;
#endif

#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    /* @violates @ref Dio_Siul2_C_REF_8 Implicit conversion changes signedness */
    /* @violates @ref Dio_Siul2_C_REF_11 The operator << was used. */
    u16MpgpdoMppdo = Dio_Siul2_ReverseBits16((uint16)(Level << pChannelGroupIdPtr->offset));
    u16MpgpdoMask  = Dio_Siul2_ReverseBits16(pChannelGroupIdPtr->mask);
    u32Value = ((((uint32)(u16MpgpdoMppdo)) & SIUL2_MPGPDO_MPPDO_MASK_U32) | \
                (((uint32)(u16MpgpdoMask)) << SIUL2_MPGPDO_MASK_SHIFT_U8)    \
               );
#else
    u32Value = ((((uint32)(Level) << (pChannelGroupIdPtr->offset)) & \
                  (SIUL2_MPGPDO_MPPDO_MASK_U32)) | (((uint32)(pChannelGroupIdPtr->mask) << \
                  (SIUL2_MPGPDO_MASK_SHIFT_U8)))                                           \
               );
#endif

    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    REG_WRITE32(SIUL2_MPGPDO_ADDR32(SIUL2_MPGPDO_MULTIPLIER_U32((uint32)pChannelGroupIdPtr->port)), u32Value);
}

#if ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__))
/*===============================================================================================*/
/**
* @brief          DIO Mask write port using mask.
* @details        Writes a DIO port with masked value.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
* @param[in]      Mask        Specifies the Mask value of the port.
*
* @pre            This function can be used only if @p DIO_MASKEDWRITEPORT_API
*                 has been enabled.
*/

FUNC (void, DIO_CODE) Dio_Siul2_MaskedWritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level,
    CONST(Dio_PortLevelType, AUTOMATIC) Mask
)
{
    VAR(uint32, AUTOMATIC) u32Value;
#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    VAR(uint16, AUTOMATIC) u16MpgpdoMppdo;
    VAR(uint16, AUTOMATIC) u16MpgpdoMask;
#endif

#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
    u16MpgpdoMppdo = Dio_Siul2_ReverseBits16((uint16)(Level));
    u16MpgpdoMask  = Dio_Siul2_ReverseBits16((uint16)(Mask));
    u32Value = (((uint32)u16MpgpdoMask << (SIUL2_MPGPDO_MASK_SHIFT_U8)) | (uint32)u16MpgpdoMppdo);
#else
    u32Value = (((uint32) Mask << (SIUL2_MPGPDO_MASK_SHIFT_U8)) | (uint32)Level);
#endif

    /* @violates @ref Dio_Siul2_C_REF_2 Cast from unsigned long to pointer.*/
    REG_WRITE32(SIUL2_MPGPDO_ADDR32(SIUL2_MPGPDO_MULTIPLIER_U32((uint32)PortId)), u32Value);
}
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__) */

#define DIO_STOP_SEC_CODE
/* @violates @ref Dio_Siul2_C_REF_5 Only preprocessor statements and comments before '#include' */
/* @violates @ref Dio_Siul2_C_REF_1 Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
