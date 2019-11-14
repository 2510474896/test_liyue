/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Reg_eSys_CMU.h $
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
*   @file    Reg_eSys_CMU.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Macros for memory access.
*   @details Macros/Defines used for registry and memory read/write.
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


#ifndef REG_ESYS_CMU_H
#define REG_ESYS_CMU_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section REG_ESYS_CMU_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section REG_ESYS_CMU_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section REG_ESYS_CMU_h_REF_3
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and
* functions shall not be reused
*
* @section REG_ESYS_CMU_h_REF_4
* Violates MISRA 2004 Required Rule 8.12, When an array is declared with external linkage, its size
* shall be stated explicitly or defined implicitly by initialisation.
*
* @section REG_ESYS_CMU_h_REF_5
* Violates MISRA 2004 Required Rule 8.7,
* Objects shall be defined at block scope if they are only accessed from within a single function.
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
/** @violates @ref REG_ESYS_CMU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Std_Types.h"
#include "Reg_eSys.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REG_ESYS_CMU_VENDOR_ID                       43
#define REG_ESYS_CMU_AR_RELEASE_MAJOR_VERSION        4
#define REG_ESYS_CMU_AR_RELEASE_MINOR_VERSION        0
#define REG_ESYS_CMU_AR_RELEASE_REVISION_VERSION     3
#define REG_ESYS_CMU_SW_MAJOR_VERSION                1
#define REG_ESYS_CMU_SW_MINOR_VERSION                0
#define REG_ESYS_CMU_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Std_Types header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((REG_ESYS_CMU_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         (REG_ESYS_CMU_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Reg_eSys_CMU.h and Std_Types.h are different"
    #endif
#endif

/* Check if current file and Reg_eSys header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((REG_ESYS_CMU_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (REG_ESYS_CMU_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Reg_eSys_CMU.h and Reg_eSys.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
/**
 * @brief CMU base address array declaration
 */
/**
 * @violates @ref REG_ESYS_CMU_h_REF_3 This is not a standard library macro.
 * @violates @ref REG_ESYS_CMU_h_REF_4 Violates MISRA 2004 Required Rule 8.12, array size shall
 * be stated explicitly.
 * @violates @ref REG_ESYS_CMU_h_REF_5 the define cannot be moved inside the block scope because
 * it must be visible from other layers.
 */
extern CONST(uint32, MCU_CONST) MCU_CMU_BASE_ADDR[];

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/* CMU Control Status Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_CSR_X_ADDR32(chNumber)       ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                          (uint32)0x00000000U) \
                                         )
/* CMU Frequency Display Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_FDR_X_ADDR32(chNumber)       ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                          (uint32)0x00000004U) \
                                         )
/* CMU High Frequency Reference Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_HFREFR_X_ADDR32(chNumber)    ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                          (uint32)0x00000008U) \
                                         )
/* CMU Low Frequency Reference Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_LFREFR_X_ADDR32(chNumber)    ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                                   (uint32)0x0000000CU \
                                                  ) \
                                         )
/* CMU Interrupt Status Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_ISR_X_ADDR32(chNumber)       ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                          (uint32)0x00000010U) \
                                         )
/* CMU Measurement Duration Register */
/** @violates @ref REG_ESYS_CMU_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define CMU_MDR_X_ADDR32(chNumber)       ((uint32)(MCU_CMU_BASE_ADDR[(chNumber)] + \
                                          (uint32)0x00000018U) \
                                         )

/* defines for various fields */
/* for CMU_CSR_ADDR32 */
#define CMU_CSR_RWBITS_MASK32            ((uint32)0x00800307U)
#define CMU_CSR_RESBITS_MASK32           ((uint32)0x00000000U)
#define CMU_CSR_MASK32                   (CMU_CSR_RWBITS_MASK32)
#define CMU_CSR_SFM_MASK32               ((uint32)0x00800000U)
#define CMU_CSR_CHKSEL_MASK32            ((uint32)0x00000300U)
#define CMU_CSR_RCDIV_MASK32             ((uint32)0x00000006U)
#define CMU_CSR_CME_MASK32               ((uint32)0x00000001U)

/* for CMU_FDR_ADDR32 */
#define CMU_FDR_MASK32                   ((uint32)0x000FFFFFU)

/* for CMU_HFREFR_ADDR32 */
#define CMU_HFREFR_RWBITS_MASK32         ((uint32)0x00000FFFU)
#define CMU_HFREFR_RESBITS_MASK32        ((uint32)0x00000000U)

/* for CMU_LFREFR_ADDR32 */
#define CMU_LFREFR_RWBITS_MASK32         ((uint32)0x00000FFFU)
#define CMU_LFREFR_RESBITS_MASK32        ((uint32)0x00000000U)

/* for CMU_ISR_ADDR32 */
#define CMU_ISR_RWBITS_MASK32            ((uint32)0x00000007U)
#define CMU_ISR_MASK32                   (CMU_ISR_RWBITS_MASK32)
#define CMU_ISR_FHHI_MASK32              ((uint32)0x00000004U)
#define CMU_ISR_FLLI_MASK32              ((uint32)0x00000002U)
#define CMU_ISR_OLRI_MASK32              ((uint32)0x00000001U)

/* for CMU_MDR_ADDR32 */
#define CMU_MDR_RWBITS_MASK32            ((uint32)0x000FFFFFU)
#define CMU_MDR_RESBITS_MASK32           ((uint32)0x00000000U)

/********** reset values */
#define MCU_CMU_CSR_RESET_VALUE_U32      ((uint32)0x00000006U)
#define MCU_CMU_HFREFR_RESET_VALUE_U32   ((uint32)0x00000FFFU)
#define MCU_CMU_LREF_RESET_VALUE_U32     ((uint32)0x00000000U)
#define MCU_CMU_MDR_MD_RESET_VALUE_U32   ((uint32)0x00000000U)
#define MCU_CMU_ISR_RESET_VALUE_U32      ((uint32)0x00000007U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif /* REG_ESYS_CMU_H */

/** @} */
