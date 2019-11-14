/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_SSCM.c $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:35CST $

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
*   @file    Mcu_SSCM.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - SSCM functions implementation.
*   @details Specific functions for SSCM configuration and control.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MC
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_HF2_ASR_REL_4_0_REV_0003_20150723
*
*   (c) Copyright 2006-2015 Freescale Inc
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifdef __cplusplus
extern "C"
{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_SSCM_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_SSCM_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_SSCM_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_SSCM_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between
* a pointer to a function and any type other than an integral type.
* Appears when accessing memory-mapped registers.
*
* @section Mcu_SSCM_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_SSCM.h"
/** @violates @ref Mcu_SSCM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_SSCM_VENDOR_ID_C                        43
/** @violates @ref Mcu_SSCM_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_SSCM_AR_RELEASE_MAJOR_VERSION_C         4
/** @violates @ref Mcu_SSCM_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_SSCM_AR_RELEASE_MINOR_VERSION_C         0
/** @violates @ref Mcu_SSCM_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_SSCM_AR_RELEASE_REVISION_VERSION_C      3
#define MCU_SSCM_SW_MAJOR_VERSION_C                 1
#define MCU_SSCM_SW_MINOR_VERSION_C                 0
#define MCU_SSCM_SW_PATCH_VERSION_C                 0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcu_SSCM header file are of the same vendor */
#if (MCU_SSCM_VENDOR_ID_C != MCU_SSCM_VENDOR_ID)
    #error "Mcu_SSCM.c and Mcu_SSCM.h have different vendor ids"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Autosar version */
#if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_MINOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_REVISION_VERSION_C != MCU_SSCM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SSCM.c and Mcu_SSCM.h are different"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Software version */
#if ((MCU_SSCM_SW_MAJOR_VERSION_C != MCU_SSCM_SW_MAJOR_VERSION) || \
     (MCU_SSCM_SW_MINOR_VERSION_C != MCU_SSCM_SW_MINOR_VERSION) || \
     (MCU_SSCM_SW_PATCH_VERSION_C != MCU_SSCM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SSCM.c and Mcu_SSCM.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SSCM_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SSCM.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and DEM header file are of the same version */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SSCM_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SSCM.c and Dem.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SSCM_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SSCM.c and SilRegMacros.h are different"
    #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_SSCM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SSCM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
* comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief            Initialize SSCM registers
* @details
*
* @param[in]        SSCM_pConfigPtr - Pointer to SSCM configuration structure.
*
* @return           void
*
*/
/** @violates @ref Mcu_SSCM_c_REF_5 Global declaration of function */
FUNC( void, MCU_CODE) Mcu_SSCM_Init(P2CONST( Mcu_SSCM_ConfigType, AUTOMATIC, MCU_APPL_DATA) SSCM_pConfigPtr)
{
    VAR( uint16, AUTOMATIC) u16State = (uint16)0U;

    /* check SSCM errors */
    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    u16State = REG_READ16(SSCM_STATUS_ADDR16) ;
    /* clear only the CER flag if set - W1 to clear */
    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    REG_WRITE16(SSCM_STATUS_ADDR16, ((u16State & SSCM_STATUS_CER_MASK16 ) | SSCM_STATUS_RESBITS_MASK16));

    /* check if error and report it */
    if ( SSCM_STATUS_CER_MASK16 == (SSCM_STATUS_CER_MASK16 & u16State) )
    {
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_SscmCerFailureCfg.state)
        {
            Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_SscmCerFailureCfg.id, DEM_EVENT_STATUS_FAILED);
        }
#endif
    }
#if ((IPV_SSCM==IPV_SSCM_05_04_00_00) || (IPV_SSCM==IPV_SSCM_05_03_00_00) ||\
     (IPV_SSCM==IPV_SSCM_06_00_00_01) \
    )
    /* write PAE and RAE bits */
    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    REG_WRITE16(SSCM_ERROR_ADDR16, SSCM_pConfigPtr->u16SscmError );
#else
    MCU_PARAM_UNUSED(SSCM_pConfigPtr);
#endif
}

#if (MCU_GET_SYSTEM_STATE_API == STD_ON)
/**
* @brief            Get the System Status and Configuration Module information.
* @details          Return information about execution mode, security, vle, jtag id, etc.
*                       - Mcu_IPW_GetSystem_State() from IPW.
*
* @return           Status read from SSCM module - STATUS and MEMCONFIG registers.
* @retval           uint32   Platform register specific.
*
*/
FUNC( uint32, MCU_CODE) Mcu_SSCM_GetSystemState ( VAR( void, AUTOMATIC) )
{

    /* Temporary variable. */
    VAR( uint32, AUTOMATIC) u32State = (uint32)0U;

    /* Get the STATUS content register. */
    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    u32State = (uint32)REG_READ16(SSCM_STATUS_ADDR16);
    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    u32State |= (uint32)((uint32)REG_READ16(SSCM_MEMCONFIG_ADDR16) << (uint32)0x16U);

    return (uint32)u32State;
}
#endif /* (MCU_GET_SYSTEM_STATE_API == STD_ON) */

#if (MCU_GET_MEM_CONFIG_API == STD_ON)

/**
* @brief            This function returns the value of the SSCM_MEMCONFIG register.
* @details          Returns the System Memory and ID register which reflects the memory
*                   configuration of the system and the JTAG ID.
*
* @return           The value of the SSCM_MEMCONFIG register.
*
* @api
*
* @requirements
*
* @note
*
*/
FUNC( Mcu_SSCM_MemConfigType, MCU_CODE) Mcu_SSCM_GetMemConfig( VAR( void, AUTOMATIC) )
{
    /* Temporary variable. */
    VAR( Mcu_SSCM_MemConfigType, AUTOMATIC) State = (Mcu_SSCM_MemConfigType)0U;

    /** @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    State = (Mcu_SSCM_MemConfigType)REG_READ16(SSCM_MEMCONFIG_ADDR16);

    return (Mcu_SSCM_MemConfigType)(State);
}

#endif /* (MCU_GET_MEM_CONFIG_API == STD_ON) */

#if (MCU_SSCM_GET_STATUS_API == STD_ON)
/**
* @brief            This function returns the value of the SSCM_STATUS register.
* @details          Return information about execution mode, security, vle.
*                       - Mcu_IPW_GetStatus() from IPW.
*
* @return           The value of the SSCM_STATUS register.
*
* @api
*
* @requirements
*
* @note
*
*/
FUNC (Mcu_SSCM_StatusType, MCU_CODE) Mcu_SSCM_GetStatus(VAR( void, AUTOMATIC))
{
    VAR(Mcu_SSCM_StatusType, AUTOMATIC) Status = (Mcu_SSCM_StatusType)0U;

    /* @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    Status = (Mcu_SSCM_StatusType)REG_READ16(SSCM_STATUS_ADDR16);
    return Status;
}
#endif /* MCU_SSCM_GET_STATUS_API == STD_ON */

#ifdef MCU_SSCM_GET_UOPS_API
#if (MCU_SSCM_GET_UOPS_API == STD_ON)
/**
* @brief            This function returns the value of the SSCM_UOPS register.
* @details          Return information about User Option Bits, HSM Boot Configuration.
*                       - Mcu_IPW_SscmGetUops() from IPW.
*
* @return           The value of the SSCM_UOPS register.
*
* @api
*
* @requirements
*
* @note
*
*/
FUNC (Mcu_SSCM_UopsType, MCU_CODE) Mcu_SSCM_GetUops(VAR( void, AUTOMATIC))
{
    VAR(Mcu_SSCM_UopsType, AUTOMATIC) State = (Mcu_SSCM_UopsType)0U;

    /* @violates @ref Mcu_SSCM_c_REF_4 Conversion form pointer to integer*/
    State = (Mcu_SSCM_UopsType)REG_READ32(SSCM_UOPS_ADDR32);
    return State;
}
#endif /* MCU_SSCM_GET_UOPS_API == STD_ON */
#endif /* MCU_SSCM_GET_UOPS_API */

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_SSCM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SSCM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
