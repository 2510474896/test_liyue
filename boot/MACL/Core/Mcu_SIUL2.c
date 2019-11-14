/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_SIUL2.c $
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
*   @file    Mcu_SIUL2.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Power Control Unit module functions implementation.
*   @details Specific functions for AFE configuration and control.
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
* @section Mcu_SIUL2_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_SIUL2_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_SIUL2_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers. The defines
* are validated.
*
* @section Mcu_SIUL2_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer to a
* function and any type other than an integral type. Appears when accessing memory-mapped registers.
*
* @section Mcu_SIUL2_c_REF_5
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
#include "Mcu_SIUL2.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define MCU_SIUL2_VENDOR_ID_C                      43
/** @violates @ref Mcu_SIUL2_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIUL2_AR_RELEASE_MAJOR_VERSION_C       4
/** @violates @ref Mcu_SIUL2_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIUL2_AR_RELEASE_MINOR_VERSION_C       0
/** @violates @ref Mcu_SIUL2_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIUL2_AR_RELEASE_REVISION_VERSION_C    3
#define MCU_SIUL2_SW_MAJOR_VERSION_C               1
#define MCU_SIUL2_SW_MINOR_VERSION_C               0
#define MCU_SIUL2_SW_PATCH_VERSION_C               0


/*==================================================================================================
                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_SIUL2 header file are of the same vendor. */
#if (MCU_SIUL2_VENDOR_ID_C != MCU_SIUL2_VENDOR_ID)
    #error "Mcu_SIUL2.c and Mcu_SIUL2.h have different Vendor IDs."
#endif
#ifdef CHECK_AUTOSAR_VERSION
  /* Check if source file and Mcu_SIUL2 header file are of the same Autosar version. */
  #if ( (MCU_SIUL2_AR_RELEASE_MAJOR_VERSION_C != MCU_SIUL2_AR_RELEASE_MAJOR_VERSION) || \
        (MCU_SIUL2_AR_RELEASE_MINOR_VERSION_C != MCU_SIUL2_AR_RELEASE_MINOR_VERSION) || \
        (MCU_SIUL2_AR_RELEASE_REVISION_VERSION_C != MCU_SIUL2_AR_RELEASE_REVISION_VERSION) \
      )
        #error "AutoSar Version Numbers of Mcu_SIUL2.c and Mcu_SIUL2.h are different."
  #endif
#endif
/* Check if source file and Mcu_SIUL2 header file are of the same Software version. */
#if ( (MCU_SIUL2_SW_MAJOR_VERSION_C != MCU_SIUL2_SW_MAJOR_VERSION) || \
      (MCU_SIUL2_SW_MINOR_VERSION_C != MCU_SIUL2_SW_MINOR_VERSION) || \
      (MCU_SIUL2_SW_PATCH_VERSION_C != MCU_SIUL2_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIUL2.c and Mcu_SIUL2.h are different."
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIUL2_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIUL2_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIUL2.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIUL2_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIUL2_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIUL2.c and SilRegMacros.h are different"
    #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
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
* @violates @ref Mcu_SIUL2_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SIUL2_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
* comments before '#include'
*/
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (MCU_GET_MIDR_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_SIUL2_GetMidrStructure(P2VAR(Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr)
{
    /** @violates @ref Mcu_SIUL2_c_REF_4 Conversion from pointer to integer */
    pMidr->u32Midr1 = REG_READ32( SIUL2_MIDR1_ADDR32 );
    /** @violates @ref Mcu_SIUL2_c_REF_4 Conversion from pointer to integer */
    pMidr->u32Midr2 = REG_READ32( SIUL2_MIDR2_ADDR32 );
}
#endif /* (MCU_GET_MIDR_API == STD_ON) */

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_SIUL2_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SIUL2_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
* comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif
/** @} */
