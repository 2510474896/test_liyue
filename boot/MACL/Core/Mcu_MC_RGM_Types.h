/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_MC_RGM_Types.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:33CST $

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
*   @file    Mcu_MC_RGM_Types.h
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from MC_RGM.
*   @details Public data types exported outside of the Mcu driver.
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


#ifndef MCU_MC_RGM_TYPES_H
#define MCU_MC_RGM_TYPES_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_MC_RGM_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
*
* @section Mcu_MC_RGM_Types_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. This violation is due to
* function like macros defined for register operations. Function like macros are used to reduce
* code complexity.
*
* @section Mcu_MC_RGM_Types_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_1 Repeated include files.*/
#include "Mcu_Cfg.h"

/** @violates @ref Mcu_MC_RGM_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Reg_eSys_MC_RGM.h"

/** @violates @ref Mcu_MC_RGM_Types_h_REF_1 Repeated include files.*/
#include "Soc_Ips.h"

/** @violates @ref Mcu_MC_RGM_Types_h_REF_1 Repeated include files.*/
#include "Mcu_MC_IPVersion.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_MC_RGM_TYPES_VENDOR_ID                    43
#define MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION     0
#define MCU_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION  3
#define MCU_MC_RGM_TYPES_SW_MAJOR_VERSION             1
#define MCU_MC_RGM_TYPES_SW_MINOR_VERSION             0
#define MCU_MC_RGM_TYPES_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_Cfg header file are from the same vendor */
#if (MCU_MC_RGM_TYPES_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_MC_RGM_Types.h and Mcu_Cfg.h have different vendor ids"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Autosar version */
#if ((MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM_Types.h and Mcu_Cfg.h are different"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Software version */
#if ((MCU_MC_RGM_TYPES_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_RGM_Types.h and Mcu_Cfg.h are different"
#endif

/* Check if source file and Reg_eSys_MC_RGM header file are from the same vendor */
#if (MCU_MC_RGM_TYPES_VENDOR_ID != REG_ESYS_MC_RGM_VENDOR_ID)
    #error "Mcu_MC_RGM_Types.h and Reg_eSys_MC_RGM.h have different vendor ids"
#endif
/* Check if source file and Reg_eSys_MC_RGM header file are of the same Autosar version */
#if ((MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION != REG_ESYS_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION != REG_ESYS_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION != REG_ESYS_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM_Types.h and Reg_eSys_MC_RGM.h are different"
#endif
/* Check if source file and Reg_eSys_MC_RGM header file are of the same Software version */
#if ((MCU_MC_RGM_TYPES_SW_MAJOR_VERSION != REG_ESYS_MC_RGM_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_MINOR_VERSION != REG_ESYS_MC_RGM_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_PATCH_VERSION != REG_ESYS_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_RGM_Types.h and Reg_eSys_MC_RGM.h are different"
#endif

/* Check if current file and Soc_Ips header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_MC_RGM_Types.h and Soc_Ips.h are different"
    #endif
#endif

/* Check if source file and Mcu_MC_IPVersion header file are from the same vendor */
#if (MCU_MC_RGM_TYPES_VENDOR_ID != MCU_MC_IPVERSION_VENDOR_ID)
    #error "Mcu_MC_RGM_Types.h and Mcu_MC_IPVersion.h have different vendor ids"
#endif
/* Check if source file and Mcu_MC_IPVersion header file are of the same Autosar version */
#if ((MCU_MC_RGM_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_MC_IPVERSION_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_MINOR_VERSION != MCU_MC_IPVERSION_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_AR_RELEASE_REVISION_VERSION != MCU_MC_IPVERSION_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM_Types.h and Mcu_MC_IPVersion.h are different"
#endif
/* Check if source file and Mcu_MC_IPVersion header file are of the same Software version */
#if ((MCU_MC_RGM_TYPES_SW_MAJOR_VERSION != MCU_MC_IPVERSION_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_MINOR_VERSION != MCU_MC_IPVERSION_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_TYPES_SW_PATCH_VERSION != MCU_MC_IPVERSION_SW_PATCH_VERSION))
    #error "Software Version Numbers of Mcu_MC_RGM_Types.h and Mcu_MC_IPVersion.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/********** RGM_DERD Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_DEST_U32(value)                          ( ((value) & MC_RGM_DERD_RWBITS_MASK32 ) | MC_RGM_DERD_RESBITS_MASK32 )

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00))
#define MC_RGM_TSR_DEST_RESET_U32                       ((uint32)0x00000000U)
#define MC_RGM_TSR_DEST_SAFE_INT_U32                    (MC_RGM_DERD_D_TSR_DEST_MASK32)
#endif

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00))
#define MC_RGM_PORST_RESET_U32                          ((uint32)0x00000000U)
#define MC_RGM_PORST_SAFE_INT_U32                       (MC_RGM_DERD_D_PORST_MASK32)
#endif

/********** RGM_DEAR Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define MC_RGM_DEAR_U32(value)                      ( ((value) & MC_RGM_DEAR_RWBITS_MASK32 ) | MC_RGM_DEAR_RESBITS_MASK32 )
#endif

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* RGM_DEAR[AR_TSR_DEST] field value. */
    #define MC_RGM_TSR_DEST_ALT_EVENT_SAFE_U32          ((uint32)0x00000000U)
    #define MC_RGM_TSR_DEST_ALT_EVENT_ISR_U32           (MC_RGM_DEAR_AR_TSR_DEST_MASK32)
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_06_01_00) ||
           (IPV_MC == IPV_MC_04_06_05_00)) */

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00))
    /* RGM_DEAR[AR_TSR_DEST] field value. */
    #define MC_RGM_PORST_ALT_EVENT_SAFE_U32             ((uint32)0x00000000U)
    #define MC_RGM_PORST_ALT_EVENT_ISR_U32              (MC_RGM_DEAR_AR_PORST_MASK32)
#endif

/********** RGM_DBRE Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_DBRE_U32(value)                          ( ((value) & MC_RGM_DBRE_RWBITS_MASK32 ) | MC_RGM_DBRE_RESBITS_MASK32 )

#if (IPV_MC == IPV_MC_04_06_01_00)
    /* RGM_DBRE[BE_PMC_STF] field value. */
    #define MC_RGM_PMC_STF_RESET_B_EN_U32                 ((uint32)0x00000000U)
    #define MC_RGM_PMC_STF_RESET_B_DIS_U32                (MC_RGM_DBRE_BE_PMC_STF_MASK32)

    /* RGM_DBRE[BE_JTAG_DEST] field value. */
    #define MC_RGM_JTAG_DEST_RESET_B_EN_U32                 ((uint32)0x00000000U)
    #define MC_RGM_JTAG_DEST_RESET_B_DIS_U32                (MC_RGM_DBRE_BE_JTAG_DEST_MASK32)
#endif /* (IPV_MC == IPV_MC_04_06_01_00) */


/********** RGM_FERD Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_FERD_U32(value)                          ( ((value) & MC_RGM_FERD_RWBITS_MASK32 ) | MC_RGM_FERD_RESBITS_MASK32 )

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) ||\
     (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) ||\
     (IPV_MC == IPV_MC_04_06_01_00) \
    )
    /* RGM_FERD[D_VOR_FUNC] - A voltage out of range functional reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_VOR_FUNC_EVENT_SAFE_INT_U32              (MC_RGM_FERD_D_VOR_FUNC_MASK32)
    #define MC_RGM_VOR_FUNC_EVENT_RESET_U32                 ((uint32)0x00000000U)
#endif

/* RGM_FERD[D_TSR_FUNC] - A temperature sensor functional reset event triggers an interrupt/Safe mode request. */
#define MC_RGM_TSR_FUNC_EVENT_SAFE_INT_U32              (MC_RGM_FERD_D_TSR_FUNC_MASK32)
#define MC_RGM_TSR_FUNC_EVENT_RESET_U32                 ((uint32)0x00000000U)

#if (IPV_MC == IPV_MC_04_01_00_00)
    /* RGM_FERD[D_ESR1] - A voltage out of range functional reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_ESR1_EVENT_SAFE_INT_U32                (MC_RGM_FERD_D_ESR1_MASK32)
    #define MC_RGM_ESR1_EVENT_RESET_U32                   ((uint32)0x00000000U)
    /* RGM_FERD[D_ESR0] - A temperature sensor functional reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_ESR0_EVENT_SAFE_INT_U32                (MC_RGM_FERD_D_ESR0_MASK32)
    #define MC_RGM_ESR0_EVENT_RESET_U32                   ((uint32)0x00000000U)
#endif
#if (IPV_MC == IPV_MC_04_00_15_15)
    /* RGM_FERD[D_ESR1] - A voltage out of range functional reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_ESR1_EVENT_SAFE_INT_U32                (MC_RGM_FERD_D_ESR1_MASK32)
    #define MC_RGM_ESR1_EVENT_RESET_U32                   ((uint32)0x00000000U)
#endif
#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) || (IPV_MC == IPV_MC_05_00_00_07) \
    )
    /* RGM_FERD[D_JTAG] - A JTAG initiated reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_JTAG_FUNC_EVENT_SAFE_INT_U32           (MC_RGM_FERD_D_JTAG_FUNC_MASK32)
    #define MC_RGM_JTAG_FUNC_EVENT_RESET_U32              ((uint32)0x00000000U)
#endif

#if (IPV_MC == IPV_MC_04_04_01_00)
    /* RGM_FERD[D_FCCU_SOFT] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_FCCU_SOFT_EVENT_SAFE_INT_U32           (MC_RGM_FERD_D_FCCU_SOFT_MASK32)
    #define MC_RGM_FCCU_SOFT_EVENT_RESET_U32              ((uint32)0x00000000U)
    /* RGM_FERD[D_FCCU_HARD] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_FCCU_HARD_EVENT_SAFE_INT_U32           (MC_RGM_FERD_D_FCCU_HARD_MASK32)
    #define MC_RGM_FCCU_HARD_EVENT_RESET_U32              ((uint32)0x00000000U)
    /* RGM_FERD[D_SOFT_FUNC] - A software functional reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_SOFT_FUNC_EVENT_SAFE_INT_U32           (MC_RGM_FERD_D_SOFT_FUNC_MASK32)
    #define MC_RGM_SOFT_FUNC_EVENT_RESET_U32              ((uint32)0x00000000U)
    /* RGM_FERD[D_ST_DONE] - A self-test completed event triggers an interrupt/Safe mode request. */
    #define MC_RGM_ST_DONE_EVENT_SAFE_INT_U32             (MC_RGM_FERD_D_ST_DONE_MASK32)
    #define MC_RGM_ST_DONE_EVENT_RESET_U32                ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_04_04_01_00) */


#if (IPV_MC == IPV_MC_05_00_00_07)
    /* RGM_FERD[D_LVD_LV_PD2_COLD] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_LVD_LV_PD2_COLD_EVENT_SAFE_INT_U32    (MC_RGM_FERD_D_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVD_LV_PD2_COLD_EVENT_RESET_U32       ((uint32)0x00000000U)
    /* RGM_FERD[D_HVD_LV_COLD] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_HVD_LV_COLD_EVENT_SAFE_INT_U32       (MC_RGM_FERD_D_HVD_LV_COLD_MASK32)
    #define MC_RGM_HVD_LV_COLD_EVENT_RESET_U32          ((uint32)0x00000000U)
    /* RGM_FERD[D_LVD_IO_A_HI] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_LVD_IO_A_HI_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_Z2_DBG] - A Z2 Debug Reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_Z2_DBG_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_Z2_DBG_MASK32)
    #define MC_RGM_Z2_DBG_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_Z4B_DBG] - A Z4B Debug Reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_Z4B_DBG_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_Z4B_DBG_MASK32)
    #define MC_RGM_Z4B_DBG_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_Z4A_DBG] - A Z4A Debug Reset event triggers an interrupt/Safe mode request. */
    #define MC_RGM_Z4A_DBG_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_Z4A_DBG_MASK32)
    #define MC_RGM_Z4A_DBG_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_CMU_OLR] - OSC Frequency less than RC event triggers an interrupt/Safe mode request. */
    #define MC_RGM_CMU_OLR_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_CMU_OLR_MASK32)
    #define MC_RGM_CMU_OLR_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_NMI_WKPU] - A Non Maskable Interrupt from Wakeup Unit event triggers an interrupt/Safe mode request. */
    #define MC_RGM_NMI_WKPU_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_NMI_WKPU_MASK32)
    #define MC_RGM_NMI_WKPU_EVENT_RESET_U32           ((uint32)0x00000000U)
#endif

#if (IPV_MC == IPV_MC_05_00_00_10)
    /* RGM_FERD[D_LVD_LV_PD2_COLD] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_LVD_LV_PD2_COLD_EVENT_SAFE_INT_U32    (MC_RGM_FERD_D_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVD_LV_PD2_COLD_EVENT_RESET_U32       ((uint32)0x00000000U)
    /* RGM_FERD[D_HVD_VDD_LV_PD2] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_HVD_VDD_LV_PD2_EVENT_SAFE_INT_U32     (MC_RGM_FERD_D_HVD_VDD_LV_PD2_MASK32)
    #define MC_RGM_HVD_VDD_LV_PD2_EVENT_RESET_U32        ((uint32)0x00000000U)
    /* RGM_FERD[D_LVD_IO_A_HI] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_LVD_IO_A_HI_EVENT_SAFE_INT_U32        (MC_RGM_FERD_D_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_EVENT_RESET_U32           ((uint32)0x00000000U)
    /* RGM_FERD[D_FXOSC_OR] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_FXOSC_OR_EVENT_SAFE_INT_U32           (MC_RGM_FERD_D_FXOSC_OR_MASK32)
    #define MC_RGM_FXOSC_OR_EVENT_RESET_U32              ((uint32)0x00000000U)
    /* RGM_FERD[D_JTAG_FUNC] - A FCCU hard reaction request event triggers an interrupt/Safe mode request. */
    #define MC_RGM_JTAG_FUNC_EVENT_SAFE_INT_U32         (MC_RGM_FERD_D_JTAG_FUNC_MASK32)
    #define MC_RGM_JTAG_FUNC_EVENT_RESET_U32            ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_05_00_00_10) */

/********** RGM_FEAR Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_FEAR_U32(value)                            ( ((value) & MC_RGM_FEAR_RWBITS_MASK32 ) | MC_RGM_FEAR_RWBITS_MASK32 )

/* RGM_FEAR[AR_VOR_FUNC] - Generate an interrupt request if the reset is disabled. */
#define MC_RGM_VOR_FUNC_EVENT_ISR_U32                   (MC_RGM_FEAR_AR_VOR_FUNC_MASK32)
#define MC_RGM_VOR_FUNC_EVENT_SAFE_U32                  ((uint32)0x00000000U)
/* RGM_FEAR[AR_TSR_FUNC] - Generate an interrupt request if the reset is disabled. */
#define MC_RGM_TSR_FUNC_EVENT_ISR_U32                   (MC_RGM_FEAR_AR_TSR_FUNC_MASK32)
#define MC_RGM_TSR_FUNC_EVENT_SAFE_U32                  ((uint32)0x00000000U)

#if ((IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_00_15_15))
    /* RGM_FEAR[AR_ESR1] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_ESR1_EVENT_ISR_U32                   (MC_RGM_FEAR_AR_ESR1_MASK32)
    #define MC_RGM_ESR1_EVENT_SAFE_U32                  ((uint32)0x00000000U)
#endif

/* RGM_FEAR[AR_JTAG_FUNC] - Generate an interrupt request if the reset is disabled. */
#define MC_RGM_JTAG_FUNC_EVENT_ISR_U32              (MC_RGM_FEAR_AR_JTAG_FUNC_MASK32)
#define MC_RGM_JTAG_FUNC_EVENT_SAFE_U32             ((uint32)0x00000000U)

#if (IPV_MC == IPV_MC_05_00_00_07)
    /* RGM_FEAR[AR_LVD_LV_PD2_COLD] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_LVW_PD2_COLD_EVENT_ISR_U32          (MC_RGM_FEAR_AR_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVW_PD2_COLD_EVENT_SAFE_U32         ((uint32)0x00000000U)
    /* RGM_FEAR[AR_HVD_LV_COLD] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_HVD_LV_COLD_EVENT_ISR_U32          (MC_RGM_FEAR_AR_HVD_LV_COLD_MASK32)
    #define MC_RGM_HVD_LV_COLD_EVENT_SAFE_U32         ((uint32)0x00000000U)
    /* RGM_FEAR[AR_LVD_IO_A_HI] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_LVD_IO_A_HI_EVENT_ISR_U32           (MC_RGM_FEAR_AR_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_EVENT_SAFE_U32          ((uint32)0x00000000U)
    /* RGM_FEAR[AR_Z2_DBG] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_Z2_DBG_EVENT_ISR_U32              (MC_RGM_FEAR_AR_Z2_DBG_MASK32)
    #define MC_RGM_Z2_DBG_EVENT_SAFE_U32             ((uint32)0x00000000U)
    /* RGM_FEAR[AR_Z4B_DBG] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_Z4B_DBG_EVENT_ISR_U32              (MC_RGM_FEAR_AR_Z4B_DBG_MASK32)
    #define MC_RGM_Z4B_DBG_EVENT_SAFE_U32             ((uint32)0x00000000U)
    /* RGM_FEAR[AR_Z4A_DBG] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_Z4A_DBG_EVENT_ISR_U32              (MC_RGM_FEAR_AR_Z4A_DBG_MASK32)
    #define MC_RGM_Z4A_DBG_EVENT_SAFE_U32             ((uint32)0x00000000U)
    /* RGM_FEAR[AR_CMU_OLR] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_CMU_OLR_EVENT_ISR_U32              (MC_RGM_FEAR_AR_CMU_OLR_MASK32)
    #define MC_RGM_CMU_OLR_EVENT_SAFE_U32             ((uint32)0x00000000U)
    /* RGM_FEAR[AR_NMI_WKPU] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_NMI_WKPU_EVENT_ISR_U32              (MC_RGM_FEAR_AR_CMU_OLR_MASK32)
    #define MC_RGM_NMI_WKPU_EVENT_SAFE_U32             ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_05_00_00_10) */


#if (IPV_MC == IPV_MC_05_00_00_10)
    /* RGM_FEAR[AR_LVD_LV_PD2_COLD] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_LVW_PD2_COLD_EVENT_ISR_U32          (MC_RGM_FEAR_AR_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVW_PD2_COLD_EVENT_SAFE_U32         ((uint32)0x00000000U)
    /* RGM_FEAR[AR_HVD_VDD_LV_PD2] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_HVD_VDD_LV_PD2_EVENT_ISR_U32        (MC_RGM_FEAR_AR_HVD_VDD_LV_PD2_MASK32)
    /** @violates @ref Mcu_MC_RGM_Types_h_REF_3 MISRA 2004 Required Rule 1.4, 31 characters limit.*/
    #define MC_RGM_HVD_VDD_LV_PD2_EVENT_SAFE_U32       ((uint32)0x00000000U)
    /* RGM_FEAR[AR_LVD_IO_A_HI] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_LVD_IO_A_HI_EVENT_ISR_U32           (MC_RGM_FEAR_AR_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_EVENT_SAFE_U32          ((uint32)0x00000000U)
    /* RGM_FEAR[AR_FXOSC_OR] - Generate an interrupt request if the reset is disabled. */
    #define MC_RGM_FXOSC_OR_EVENT_ISR_U32              (MC_RGM_FEAR_AR_FXOSC_OR_MASK32)
    #define MC_RGM_FXOSC_OR_EVENT_SAFE_U32             ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_05_00_00_10) */

/********** RGM_FBRE Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_FBRE_U32(value)                          ( ((value) & MC_RGM_FBRE_RWBITS_MASK32 ) | MC_RGM_FBRE_RESBITS_MASK32 )
/* RGM_FBRE[BE_VOR_FUNC] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_VOR_FUNC_EXT_RESET_B_DIS_U32             (MG_RGM_FBRE_BE_VOR_FUNC_MASK32)
#define MC_RGM_VOR_FUNC_EXT_RESET_B_EN_U32              ((uint32)0x00000000U)
/* RGM_FBRE[BE_TSR_FUNC] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_TSR_FUNC_EXT_RESET_B_DIS_U32             (MG_RGM_FBRE_BE_TSR_FUNC_MASK32)
#define MC_RGM_TSR_FUNC_EXT_RESET_B_EN_U32              ((uint32)0x00000000U)

#if (IPV_MC == IPV_MC_05_00_00_07)
    /* RGM_FBRE[BE_LVD_LV_PD2_cold] - RESET_B is not asserted if the reset is enabled. */
    /** @violates @ref Mcu_MC_RGM_Types_h_REF_3 MISRA 2004 Required Rule 1.4, 31 characters limit.*/
    #define MC_RGM_LVD_LV_PD2_COLD_ASSERT_ESR0_DIS_U32          (MG_RGM_FBRE_BE_LVD_LV_PD2_COLD_MASK32)
    /** @violates @ref Mcu_MC_RGM_Types_h_REF_3 MISRA 2004 Required Rule 1.4, 31 characters limit.*/
    #define MC_RGM_LVD_LV_PD2_COLD_ASSERT_ESR0_EN_U32           ((uint32)0x00000000U)

    /* RGM_FBRE[BE_Z2_DBG] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_Z2_DBG_ASSERT_ESR0_DIS_U32                   (MG_RGM_FBRE_BE_Z2_DBG_MASK32)
    #define MC_RGM_Z2_DBG_ASSERT_ESR0_EN_U32                    ((uint32)0x00000000U)

    /* RGM_FBRE[BE_Z4B_DBG] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_Z4B_DBG_ASSERT_ESR0_DIS_U32                  (MG_RGM_FBRE_BE_Z4B_DBG_MASK32)
    #define MC_RGM_Z4B_DBG_ASSERT_ESR0_EN_U32                   ((uint32)0x00000000U)

    /* RGM_FBRE[BE_Z4A_DBG] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_Z4A_DBG_ASSERT_ESR0_DIS_U32                  (MG_RGM_FBRE_BE_Z4A_DBG_MASK32)
    #define MC_RGM_Z4A_DBG_ASSERT_ESR0_EN_U32                   ((uint32)0x00000000U)

    /* RGM_FBRE[BE_FCCU_SHORT] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_FCCU_SHORT_ASSERT_ESR0_DIS_U32               (MG_RGM_FBRE_BE_FCCU_SHORT_MASK32)
    #define MC_RGM_FCCU_SHORT_ASSERT_ESR0_EN_U32                ((uint32)0x00000000U)

    /* RGM_FBRE[BE_FCCU_LONG] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_FCCU_LONG_ASSERT_ESR0_DIS_U32                (MG_RGM_FBRE_BE_FCCU_LONG_MASK32)
    #define MC_RGM_FCCU_LONG_ASSERT_ESR0_EN_U32                 ((uint32)0x00000000U)

    /* RGM_FBRE[BE_CMU_OLR] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_CMU_OLR_ASSERT_ESR0_DIS_U32                  (MG_RGM_FBRE_BE_CMU_OLR_MASK32)
    #define MC_RGM_CMU_OLR_ASSERT_ESR0_EN_U32                   ((uint32)0x00000000U)

    /* RGM_FBRE[BE_JTAG_FUNC] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_JTAG_FUNC_ASSERT_ESR0_DIS_U32                (MG_RGM_FBRE_BE_JTAG_FUNC_MASK32)
    #define MC_RGM_JTAG_FUNC_ASSERT_ESR0_EN_U32                 ((uint32)0x00000000U)

    /* RGM_FBRE[BE_NMI_WKPU] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_NMI_WKPU_ASSERT_ESR0_DIS_U32                 (MG_RGM_FBRE_BE_NMI_WKPU_MASK32)
    #define MC_RGM_NMI_WKPU_ASSERT_ESR0_EN_U32                  ((uint32)0x00000000U)

    /* RGM_FBRE[BE_SOFT_FUNC] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_SOFT_FUNC_ASSERT_ESR0_DIS_U32                (MG_RGM_FBRE_BE_SOFT_FUNC_MASK32)
    #define MC_RGM_SOFT_FUNC_ASSERT_ESR0_EN_U32                 ((uint32)0x00000000U)

#endif


#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_05_00_00_07))
    /* RGM_FBRE[BE_HSM_FUNC] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_HSM_FUNC_ASSERT_ESR0_DIS_U32             (MG_RGM_FBRE_BE_HSM_FUNC_MASK32)
    #define MC_RGM_HSM_FUNC_ASSERT_ESR0_EN_U32              ((uint32)0x00000000U)
#endif

#if (IPV_MC == IPV_MC_04_01_00_00)
    /* RGM_FBRE[BE_HSM_FUNC] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_HSM_FUNC_EXT_RESET_B_DIS_U32             (MG_RGM_FBRE_BE_HSM_FUNC_MASK32)
    #define MC_RGM_HSM_FUNC_EXT_RESET_B_EN_U32              ((uint32)0x00000000U)
#endif

/* RGM_FBRE[BE_JTAG] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_JTAG_EXT_RESET_B_DIS_U32                 (MG_RGM_FBRE_BE_JTAG_FUNC_MASK32)
#define MC_RGM_JTAG_EXT_RESET_B_EN_U32                  ((uint32)0x00000000U)
/* RGM_FBRE[BE_FCCU_SOFT] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_FCCU_SOFT_EXT_RESET_B_DIS_U32            (MG_RGM_FBRE_BE_FCCU_SOFT_MASK32)
#define MC_RGM_FCCU_SOFT_EXT_RESET_B_EN_U32             ((uint32)0x00000000U)
/* RGM_FBRE[BE_FCCU_HARD] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_FCCU_HARD_EXT_RESET_B_DIS_U32            (MG_RGM_FBRE_BE_FCCU_HARD_MASK32)
#define MC_RGM_FCCU_HARD_EXT_RESET_B_EN_U32             ((uint32)0x00000000U)
/* RGM_FBRE[BE_SOFT_FUNC] - RESET_B is not asserted if the reset is enabled. */
#define MC_RGM_SOFT_FUNC_EXT_RESET_B_DIS_U32            (MG_RGM_FBRE_BE_SOFT_FUNC_MASK32)
#define MC_RGM_SOFT_FUNC_EXT_RESET_B_EN_U32             ((uint32)0x00000000U)

#if (IPV_MC == IPV_MC_04_00_15_15)
    /* RGM_FBRE[BE_ESR1] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_ESR1_ASSERT_ESR0_DIS_U32             (MG_RGM_FBRE_BE_ESR1_MASK32)
    #define MC_RGM_ESR1_ASSERT_ESR0_EN_U32              ((uint32)0x00000000U)
#endif

#if (IPV_MC == IPV_MC_04_01_00_00)
    /* RGM_FBRE[BE_ESR1] - RESET_B is not asserted if the reset is enabled. */
    #define MC_RGM_ESR1_EXT_RESET_B_DIS_U32             (MG_RGM_FBRE_BE_ESR1_MASK32)
    #define MC_RGM_ESR1_EXT_RESET_B_EN_U32              ((uint32)0x00000000U)
#endif

#if (IPV_MC == IPV_MC_04_06_01_00)
    /* Bidirectional Reset Enable for Self Test Completed 'Functional' Reset */
    #define MC_RGM_ST_DONE_EXT_RESET_B_DIS_U32          (MG_RGM_FBRE_BE_ST_DONE_MASK32)
    #define MC_RGM_ST_DONE_EXT_RESET_B_EN_U32           ((uint32)0x00000000U)
    /* Bidirectional Reset Enable for ESR0 External Reset */
    #define MC_RGM_ESR0_EXT_RESET_B_DIS_U32             (MG_RGM_FBRE_BE_ESR0_MASK32)
    #define MC_RGM_ESR0_EXT_RESET_B_EN_U32              ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_04_06_01_00) */

/********** RGM_FESS Register bits values **********/
/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_FESS_U32(value)                          ( ((value) & MC_RGM_FESS_RWBITS_MASK32 ) | MC_RGM_FESS_RESBITS_MASK32 )

#if (IPV_MC == IPV_MC_05_00_00_07)
    /* RGM_FESS[SS_LVD_LV_PD2_Cold] - The reset sequence triggered by a LVD_LV_PD2_COLD software reset event. */
    #define MC_RGM_LVD_LV_PD2_COLD_PHASE3_U32  (MC_RGM_FESS_SS_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVD_LV_PD2_COLD_PHASE1_U32  ((uint32)0x00000000U)
    /* RGM_FESS[SS_HVD_LV_cold] - The reset sequence triggered by a HVD_LV_cold software reset event. */
    #define MC_RGM_HVD_LV_COLD_PHASE3_U32      (MC_RGM_FESS_SS_HVD_LV_COLD_MASK32)
    #define MC_RGM_HVD_LV_COLD_PHASE1_U32      ((uint32)0x00000000U)
    /* RGM_FESS[SS_LVD_IO_A_HI] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_LVD_IO_A_HI_PHASE3_U32      (MC_RGM_FESS_SS_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_PHASE1_U32      ((uint32)0x00000000U)
    /* RGM_FESS[SS_Z2_DBG] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_Z2_DBG_PHASE3_U32           (MG_RGM_FESS_SS_Z2_DBG_MASK32)
    #define MC_RGM_Z2_DBG_PHASE1_U32           ((uint32)0x00000000U)
    /* RGM_FESS[SS_Z4B_DBG] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_Z4B_DBG_PHASE3_U32          (MG_RGM_FESS_SS_Z4B_DBG_MASK32)
    #define MC_RGM_Z4B_DBG_PHASE1_U32          ((uint32)0x00000000U)
    /* RGM_FESS[SS_Z4A_DBG] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_Z4A_DBG_PHASE3_U32          (MG_RGM_FESS_SS_Z4A_DBG_MASK32)
    #define MC_RGM_Z4A_DBG_PHASE1_U32          ((uint32)0x00000000U)
    /* RGM_FESS[SS_CMU_OLR] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_CMU_OLR_PHASE3_U32          (MG_RGM_FESS_SS_CMU_OLR_MASK32)
    #define MC_RGM_CMU_OLR_PHASE1_U32          ((uint32)0x00000000U)
    /* RGM_FESS[SS_NMI_WKPU] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_NMI_WKPU_PHASE3_U32          (MG_RGM_FESS_SS_NMI_WKPU_MASK32)
    #define MC_RGM_NMI_WKPU_PHASE1_U32          ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_05_00_00_07) */

#if (IPV_MC == IPV_MC_05_00_00_10)
    /* RGM_FESS[SS_SWT2_RST_REQ] - The reset sequence triggered by a SWT timeout reset event. */
    #define MC_RGM_SWT2_RST_REQ_PHASE3_U32          (MC_RGM_FESS_SS_SWT2_RST_REQ_MASK32)
    #define MC_RGM_SWT2_RST_REQ_PHASE1_U32          ((uint32)0x00000000U)
    /* RGM_FESS[SS_CM0_RST_REQ] - The reset sequence triggered by a CM0 software reset event. */
    #define MC_RGM_CM0_RST_REQ_PHASE3_U32           (MC_RGM_FESS_SS_CM0_RST_REQ_MASK32)
    #define MC_RGM_CM0_RST_REQ_PHASE1_U32           ((uint32)0x00000000U)
    /* RGM_FESS[SS_LVD_LV_PD2_COLD] - The reset sequence triggered by a LVD_LV_PD2_COLD software reset event. */
    #define MC_RGM_LVD_LV_PD2_COLD_PHASE3_U32       (MC_RGM_FESS_SS_LVD_LV_PD2_COLD_MASK32)
    #define MC_RGM_LVD_LV_PD2_COLD_PHASE1_U32       ((uint32)0x00000000U)
    /* RGM_FESS[SS_HVD_VDD_LV_PD2] - The reset sequence triggered by a SS_HVD_VDD_LV_PD2 software reset event. */
    #define MC_RGM_HVD_VDD_LV_PD2_PHASE3_U32         (MC_RGM_FESS_SS_HVD_VDD_LV_PD2_MASK32)
    #define MC_RGM_HVD_VDD_LV_PD2_PHASE1_U32        ((uint32)0x00000000U)
    /* RGM_FESS[SS_LVD_IO_A_HI] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_LVD_IO_A_HI_PHASE3_U32           (MC_RGM_FESS_SS_LVD_IO_A_HI_MASK32)
    #define MC_RGM_LVD_IO_A_HI_PHASE1_U32           ((uint32)0x00000000U)
    /* RGM_FESS[SS_FXOSC_OR] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_SS_FXOSC_OR_PHASE3_U32           (MC_RGM_FESS_SS_FXOSC_OR_MASK32)
    #define MC_RGM_SS_FXOSC_OR_PHASE1_U32           ((uint32)0x00000000U)
#endif /* (IPV_MC == IPV_MC_05_00_00_10) */

/* RGM_FESS[SS_VOR_FUNC] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
#define MC_RGM_VOR_FUNC_RESET_PHASE3_U32              (MC_RGM_FESS_SS_VOR_FUNC_MASK32)
#define MC_RGM_VOR_FUNC_RESET_PHASE1_U32              ((uint32)0x00000000U)
/* RGM_FESS[SS_TSR_FUNC] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
#define MC_RGM_TSR_FUNC_RESET_PHASE3_U32              (MC_RGM_FESS_SS_TSR_FUNC_MASK32)
#define MC_RGM_TSR_FUNC_RESET_PHASE1_U32              ((uint32)0x00000000U)
/* RGM_FESS[SS_JTAG] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
#define MC_RGM_JTAG_FUNC_RESET_PHASE3_U32             (MC_RGM_FESS_SS_JTAG_FUNC_MASK32)
#define MC_RGM_JTAG_FUNC_RESET_PHASE1_U32             ((uint32)0x00000000U)
/* RGM_FESS[SS_SOFT_FUNC] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
#define MC_RGM_SOFT_FUNC_RESET_PHASE3_U32             (MC_RGM_FESS_SS_SOFT_FUNC_MASK32)
#define MC_RGM_SOFT_FUNC_RESET_PHASE1_U32             ((uint32)0x00000000U)

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
    /* RGM_FESS[SS_SOFT_FUNC] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_ESR1_RESET_PHASE3_U32              (MC_RGM_FESS_SS_ESR1_MASK32)
    #define MC_RGM_ESR1_RESET_PHASE1_U32              ((uint32)0x00000000U)
    /* RGM_FESS[SS_SOFT_FUNC] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_ESR0_RESET_PHASE3_U32              (MC_RGM_FESS_SS_ESR0_MASK32)
    #define MC_RGM_ESR0_RESET_PHASE1_U32              ((uint32)0x00000000U)
#else
    /* RGM_FESS[SS_EXR] - The reset sequence will start from PHASE3, skipping PHASE1 and PHASE2. */
    #define MC_RGM_EXR_RESET_PHASE3_U32               (MC_RGM_FESS_SS_EXR_MASK32)
    #define MC_RGM_EXR_RESET_PHASE1_U32               ((uint32)0x00000000U)
#endif

/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_FRET_U8(val)                          ((uint8)(((val) & MC_RGM_FRET_RWBITS_MASK8) | MC_RGM_FRET_RESBITS_MASK8))

/** @violates @ref Mcu_MC_RGM_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define MC_RGM_DRET_U8(val)                          ((uint8)(((val) & MC_RGM_DRET_RWBITS_MASK8) | MC_RGM_DRET_RESBITS_MASK8))

/* Mcu_MC_RGM_GetResetRawValue defines */
#if ((IPV_MC == IPV_MC_04_04_01_00) || (IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_06_01_00))
    #define MC_RGM_RAWRESET_FES_F_EXR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SOFT_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_HARD_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_SOFT_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_JTAG_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_TSR_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_VOR_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32) 0U))
#elif ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
    #define MC_RGM_RAWRESET_FES_F_ESR0_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_ESR1_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SOFT_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_HARD_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_SOFT_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_JTAG_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_HSM_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_TSR_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_VOR_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32) 0U))
#elif (IPV_MC == IPV_MC_04_06_05_00)
    #define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SOFT_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_HARD_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_SOFT_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_JTAG_FUNC_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_TSR_FUNC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
#elif (IPV_MC == IPV_MC_05_00_00_10)
    #define MC_RGM_RAWRESET_FES_F_EXR_MASK32                ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SOFT_FUNC_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_JTAG_FUNC_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FXOSC_OR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_HARD_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_SOFT_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_LVD_IO_A_HI_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_HVD_VDD_LV_PD2_MASK32     ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_LVD_LV_PD2_COLD_MASK32    ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_LVW_PD2_MASK32            ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_CM0_RST_REQ_MASK32        ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SWT2_RST_REQ_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xCU) << (uint32) 0U))
#elif (IPV_MC == IPV_MC_05_00_00_07)
    #define MC_RGM_RAWRESET_FES_F_EXR_MASK32                ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_HSM_FUNC_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_SOFT_FUNC_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_NMI_WKPU_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_JTAG_FUNC_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_CMU_OLR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_LONG_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_FCCU_SHORT_MASK32         ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_Z4A_MASK32                ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_Z4B_MASK32                ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_Z2_MASK32                 ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_LVD_IO_A_HI_MASK32        ((uint32)(((uint32)0x01 << (uint32)0xCU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_HVD_LV_COLD_MASK32        ((uint32)(((uint32)0x01 << (uint32)0xDU) << (uint32) 0U))
    #define MC_RGM_RAWRESET_FES_F_LVD_LV_PD2_COLD_MASK32    ((uint32)(((uint32)0x01 << (uint32)0xEU) << (uint32) 0U))
#endif

#if (IPV_MC == IPV_MC_04_04_01_00)
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FFRR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_EDR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FIF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_TSR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_VOR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32)16U))
#elif (IPV_MC == IPV_MC_04_03_00_00)
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FFRR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_EDR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_TSR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_VOR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
#elif ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_PORST_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FFRR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_EDR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FIF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_JTAG_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SSCM_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_HSM_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_TSR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_VOR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32)16U))
#elif (IPV_MC == IPV_MC_04_06_01_00)
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_PORST_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FFRR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SSR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_EDR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FIF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_JTAG_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_TSR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_VOR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_PMC_MASK32            ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32)16U))
#elif (IPV_MC == IPV_MC_04_06_05_00)
    /* i've run out of bits - use the free bits from the lower section */
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_FFRR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_EDR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0xCU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_LVD_CORE_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xDU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_HVD_CORE_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xEU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_LVD_ADC_MASK32        ((uint32)(((uint32)0x01 << (uint32)0xFU) << (uint32)0U))
    #define MC_RGM_RAWRESET_DES_F_HVD_ADC_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_LVD_FLASH_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_LVD_PLL_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_LVD_IO_MASK32         ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_LVD_PMC_MASK32        ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD0_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD1_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD2_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD3_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD4_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x9U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD5_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xAU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_TSR_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xBU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD7_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xCU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD8_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xDU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD6_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xEU) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_AFE_LVD9_MASK32       ((uint32)(((uint32)0x01 << (uint32)0xFU) << (uint32)16U))
#elif (IPV_MC == IPV_MC_05_00_00_10)
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SSSR_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_EFR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FIF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_JTAG_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
#elif (IPV_MC == IPV_MC_05_00_00_07)
    #define MC_RGM_RAWRESET_DES_F_POR_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_HSM_DEST_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SOFT_DEST_MASK32      ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SSCM_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_FUNC_ESC_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SUF_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SWT0_RES_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SWT1_RES_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32)16U))
    #define MC_RGM_RAWRESET_DES_F_SWT2_RES_MASK32       ((uint32)(((uint32)0x01 << (uint32)0x8U) << (uint32)16U))
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            Reset type to be performed through the Mcu_PerformReset() API.
* @details          Destructive Reset:
*                       - Flash is always reset, so an updated value of the option bits is reloaded
*                         in volatile registers outside of the Flash array.
*                       - Trimming is lost.
*                       - STCU is reset and configured BISTs are executed
*                   Functional Reset:
*                       - Starts the reset sequence from PHASE1 or from PHASE3.
*                       - The volatile registers are not reset; in case of a reset event, the
*                         trimming is maintained.
*                       - No BISTs shall be executed after functional resets.
*/
typedef enum
{
    MCU_FUNC_RESET = 0x5AU,     /**< @brief Functional Reset type. */
    MCU_DEST_RESET = 0x3CU      /**< @brief Destructive Reset type. */
    
} Mcu_MC_RGM_ResetType;

#endif /* (MCU_PERFORM_RESET_API == STD_ON) */


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            Configuration of MC_RGM hw IP.
* @details          This data configuration is set at module initialization phase.
*/
typedef struct
{
#if (MCU_PERFORM_RESET_API == STD_ON)
    /**< @brief RESET type: Functional vs Destructive. Used by McuPerformReset() API. */
    VAR( Mcu_MC_RGM_ResetType, MCU_VAR) Mcu_MC_RGM_eResetType;
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

    /* destructive reset control */
    /**< @brief Enable/Disable destructive reset sources (RGM_DERD register). */
    VAR( uint32, MCU_VAR) u32DestResetOpt;
    /**
    * < @brief Alternate request can be either a SAFE mode request to MC_ME or an interrupt request
    * to the system (RGM_DEAR register).
    */
    VAR( uint32, MCU_VAR) u32DestSafeIsrOpt;
    /**
    * < @brief Enable the generation of an external reset when a destructive reset is triggered
    * (RGM_DBRE register).
    */
    VAR( uint32, MCU_VAR) u32DestExtPinReset;
    /* functional reset control */
    /**< @brief Enable/Disable functional reset sources (RGM_FERD register). */
    VAR( uint32, MCU_VAR) u32FuncResetOpt;
    /**
    * < @brief Alternate request can be either a SAFE mode request to MC_ME or an interrupt
    * request to the system (RGM_FEAR register).
    */
    VAR( uint32, MCU_VAR) u32FuncSafeIsrOpt;
    /**
    * < @brief Enable the generation of an external reset when a functional reset is triggered
    * (RGM_FBRE register).
    */
    VAR( uint32, MCU_VAR) u32FuncExtPinReset;
    /**
    * < @brief The functional reset sequence can either start from PHASE1 or from PHASE3
    * (RGM_FESS register).
    */
    VAR( uint32, MCU_VAR) u32FuncPhase1or3Opt;
    /* 'Functional' Reset Escalation Threshold Register */
    /**< @brief Reset Escalation Threshold. MC_RGM_FRET */
    VAR( uint8, MCU_VAR) u8ThresholdReset;
    /* 'Destructive' Reset Escalation Threshold Register */
#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00) || \
     (IPV_MC == IPV_MC_05_00_00_10) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_05_00_00_07) \
    )
    /**< @brief Reset Escalation Threshold. MC_RGM_DRET */
    VAR( uint8, MCU_VAR) u8DesThresholdReset;
#endif /* (IPV_MC == IPV_MC_04_00_15_15) */

} Mcu_MC_RGM_ConfigType;



/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_MC_RGM_TYPES_H */

/** @} */

