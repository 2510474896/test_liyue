/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_IPW.c $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:31CST $

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
*   @file    Mcu_IPW.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Middle layer implementation.
*   @details Layer that implements the wrapper for routing data from/to external interface
*            to IP layer.
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
* @section Mcu_IPW_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation
* since all header files are protected against multiple inclusions
*
* @section Mcu_IPW_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory
* section
*
* @section Mcu_IPW_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_IPW_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, Conversion from object to pointer.
* A cast should not be performed between a pointer to
* object type and a different pointer to object type
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/* Header file with prototype functions defines in this layer. */
#include "Mcu_IPW.h"
#include "Mcu_IPW_Irq.h"

/* Header files that are called from IPW layer. */
#include "Mcu_MC_CGM.h"
#include "Mcu_MC_ME.h"
#include "Mcu_MC_RGM.h"
#include "Mcu_MC_PCU.h"
#include "Mcu_STCU.h"
#include "Mcu_SSCM.h"
#if (MCU_ECSM_SUPPORT == STD_ON)
  #include "Mcu_ECSM.h"
#endif /* (MCU_ECSM_SUPPORT == STD_ON) */
#if (MCU_SRAMC_SUPPORT == STD_ON)
  #include "Mcu_PRAM.h"
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
#include "Mcu_FLASH.h"
#include "SchM_Mcu.h"
#include "Mcu_PLLDIG.h"
#include "Mcu_XOSC.h"
#include "Mcu_SIUL2.h"
#include "Mcu_CMU.h"

/**
* @brief    Detected development errors shall be reported to the Det_ReportError service of the
*           Development Error Tracer (DET) if the pre-processor switch McuDevErrorDetect is set
*           The detection of development errors is configurable (ON / OFF) at precompile time.
*           The switch McuDevErrorDetect (see chapter 10) shall activate or deactivate the detection
*           of all development errors.
*           Det_ReportError - Service to report development errors.
*
*/
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_VENDOR_ID_C                     43
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_MAJOR_VERSION_C      4
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_MINOR_VERSION_C      0
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_IPW_SW_MAJOR_VERSION_C              1
#define MCU_IPW_SW_MINOR_VERSION_C              0
#define MCU_IPW_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcu_IPW header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_IPW.h have different vendor ids"
#endif
/* Check if current file and Mcu_IPW header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_IPW_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_IPW.h are different"
#endif
/* Check if current file and Mcu_IPW header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_IPW.h are different"
#endif

/* Check if current file and Mcu_IPW_Irq header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_IRQ_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_IPW_Irq.h have different vendor ids"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_IPW_Irq.h are different"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_IRQ_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_IRQ_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_IPW_Irq.h are different"
#endif

/* Check if current file and Mcu_MC_CGM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_MC_CGM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_MC_CGM.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_CGM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_CGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_CGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_MC_CGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_MC_CGM.h are different"
#endif
/* Check if current file and Mcu_MC_CGM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_MC_CGM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_MC_CGM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_MC_CGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_MC_CGM.h are different"
#endif

/* Check if current file and Mcu_MC_ME header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_MC_ME_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_MC_ME.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_ME header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_MC_ME.h are different"
#endif
/* Check if current file and Mcu_MC_ME header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_MC_ME_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_MC_ME_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_MC_ME.h are different"
#endif

/* Check if current file and Mcu_MC_RGM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_MC_RGM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_MC_RGM.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_RGM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_MC_RGM.h are different"
#endif
/* Check if current file and Mcu_MC_RGM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_MC_RGM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_MC_RGM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_MC_RGM.h are different"
#endif

/* Check if current file and Mcu_MC_PCU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_MC_PCU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_MC_PCU.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_PCU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_PCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_PCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_MC_PCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_MC_PCU.h are different"
#endif
/* Check if current file and Mcu_MC_PCU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_MC_PCU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_MC_PCU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_MC_PCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_MC_PCU.h are different"
#endif

/* Check if current file and Mcu_STCU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_STCU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_STCU.h have different vendor ids"
#endif
/* Check if current file and Mcu_STCU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_STCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_STCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_STCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_STCU.h are different"
#endif
/* Check if current file and Mcu_STCU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_STCU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_STCU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_STCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_STCU.h are different"
#endif

/* Check if current file and Mcu_SSCM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_SSCM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_SSCM.h have different vendor ids"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_SSCM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_SSCM.h are different"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_SSCM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_SSCM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_SSCM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_SSCM.h are different"
#endif

#if (MCU_ECSM_SUPPORT == STD_ON)
/* Check if current file and Mcu_ECSM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_ECSM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_ECSM.h have different vendor ids"
#endif
/* Check if current file and Mcu_ECSM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_ECSM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_ECSM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_ECSM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_ECSM.h are different"
#endif
/* Check if current file and Mcu_ECSM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_ECSM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_ECSM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_ECSM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_ECSM.h are different"
#endif
#endif

#if (MCU_SRAMC_SUPPORT == STD_ON)
/* Check if current file and Mcu_PRAM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_PRAM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_PRAM.h have different vendor ids"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_PRAM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_PRAM.h are different"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_PRAM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_PRAM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_PRAM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_PRAM.h are different"
#endif
#endif

/* Check if current file and Mcu_FLASH header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_FLASH_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_FLASH.h have different vendor ids"
#endif
/* Check if current file and Mcu_FLASH header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_FLASH_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_FLASH_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_FLASH_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_FLASH.h are different"
#endif
/* Check if current file and Mcu_FLASH header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_FLASH_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_FLASH_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_FLASH_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_FLASH.h are different"
#endif

/* Check if current file and Mcu_PLLDIG header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_PLLDIG_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_PLLDIG.h have different vendor ids"
#endif
/* Check if current file and Mcu_PLLDIG header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_PLLDIG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_PLLDIG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_PLLDIG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_PLLDIG.h are different"
#endif
/* Check if current file and Mcu_PLLDIG header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_PLLDIG_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_PLLDIG_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_PLLDIG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_PLLDIG.h are different"
#endif

/* Check if current file and Mcu_XOSC header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_XOSC_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_XOSC.h have different vendor ids"
#endif
/* Check if current file and Mcu_XOSC header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_XOSC_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_XOSC_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_XOSC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_XOSC.h are different"
#endif
/* Check if current file and Mcu_XOSC header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_XOSC_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_XOSC_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_XOSC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_XOSC.h are different"
#endif

/* Check if current file and Mcu_SIUL2 header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_SIUL2_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_SIUL2.h have different vendor ids"
#endif
/* Check if current file and Mcu_SIUL2 header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_SIUL2_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_SIUL2_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_SIUL2_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_SIUL2.h are different"
#endif
/* Check if current file and Mcu_SIUL2 header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_SIUL2_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_SIUL2_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_SIUL2_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_SIUL2.h are different"
#endif

/* Check if current file and Mcu_CMU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_CMU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_CMU.h have different vendor ids"
#endif
/* Check if current file and Mcu_CMU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_CMU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_CMU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_CMU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_CMU.h are different"
#endif
/* Check if current file and Mcu_CMU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_CMU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_CMU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_CMU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_CMU.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_IPW.c and Det.h are different"
    #endif
#endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
/* Mcu clock configuration structure used at a moment by the MCU driver.
   When the Mcu_InitClock() API is called this pointer will be different from NULL_PTR - used as a
    check trigger by Mcu_DistributePllClock() API.
*/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"

STATIC P2CONST( Mcu_ClockConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_pClockConfig = NULL_PTR;

#define MCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"
#endif /* (MCU_INIT_CLOCK == STD_ON) */


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
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


/**
* @brief            This function initializes the MCU module.
* @details          The function initializes the CGM, ME, RGM, PCU modules, specific parameters for
*                   DMAMUX and DMAv2 modules and global parameters from FLASH module.
*                   Called by:
*                       - Mcu_Init() from HLD.
*
* @param[in]        Mcu_pHwIPsConfigPtr   Pointer to IPW configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_IPW_Init(P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pHwIPsConfigPtr)
{
    /* init the SSCM module */
    Mcu_SSCM_Init(Mcu_pHwIPsConfigPtr->SSCM_pConfig);

    /* Init MC_ME registers: MC_ME_RUN_PCx, MC_ME_LP_PCx, MC_ME_IM, clear ME_IS int flags.\
       Initialize the configurations during RUN and NON-RUN modes for each peripheral.
       Configuration of MC_ME_PCTLx registers. */
    Mcu_MC_ME_Modes_Periph_Init( Mcu_pHwIPsConfigPtr->MC_ME_pConfig);

    /* Init MCU MC_RGM part of the registers: MC_RGM_FERD, MC_RGM_FEAR, MC_RGM_FESS, MC_RGM_FBRE,
    clear FES & DES status registers. */
    Mcu_MC_RGM_ResetInit( Mcu_pHwIPsConfigPtr->MC_RGM_pConfig );

    /* Configure the Power Management Unit. */
    Mcu_MC_PCU_PowerInit( Mcu_pHwIPsConfigPtr->MC_PCU_pConfig);

    /* Enter critical region*/
    SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_00();

    /* Flash initialization. */
    Mcu_FLASH_Init( Mcu_pHwIPsConfigPtr->FLASH_pConfig);

    /* Exit critical region. */
    SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_00();
}


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            This function initializes the clock structure.
* @details          This function intializes the clock structure by configuring the CGM module.
*                   The progressive clock switching output (PHI_PCS) of the FMPLL_0 is used as input
*                   for the System Clock Selector only.
*                   The non progressive clock switching output (PHI) of the FMPLL_0 is used as input
*                   for the Output Clock Selector and the Auxiliary Clock Selectors.
*                   Frequency of "PHI" output = Frequency of FVCO / ODF.
*                   Two clock outputs (PHI and FVCO/6) of the FMPLL_1 are used as inputs for the
*                   Auxiliary Clock Selectors.
*                   FMPLL_1 can not be used as a clock source for the System Clock Selector.
*                   Frequency of "FVCO/6" output = Frequency of FVCO / 6
*                   Called by:
*                       - Mcu_InitClock() from HLD.
*
* @param[in]        Mcu_pClockConfigPtr   Pointer to clock configuration structure
*                   (member of 'Mcu_ConfigType' struct).
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_IPW_InitClock(P2CONST( Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pClockConfigPtr)
{
    VAR (uint32, AUTOMATIC) u32ClockConfig;
    VAR (uint8, AUTOMATIC) u8ClockSourceControl;
    VAR (uint32, AUTOMATIC) u32TempClockConfig;

    /* Clear all the settings for CMU0/1/2. */
    /* In case one clock configuration has the CMU disabled, then need to make the transition to
    reset state of CMU modules. */
    if (NULL_PTR != Mcu_pClockConfig)
    {
        if (MCU_CLK_NOTIF_EN == Mcu_pClockConfig->Mcu_ClkNotification)
        {
            Mcu_CMU_DeInit();
        }
    }
    Mcu_pClockConfig = Mcu_pClockConfigPtr;

     /* get the current system clock settings and enabled clocks */
    u32ClockConfig = Mcu_MC_ME_GetCurrentModeClockSettings();

    /* now check witch clock source is under MCU control and must be reconfigured */
    /* if it is under MCU control then i need to shut it down, configure then re-enable it */
    /* small speed optimization - store Mcu_u8ClockSourceControlAndPLLsUnderMcuControl in this
    function */
    u8ClockSourceControl = Mcu_pClockConfigPtr->u8ClockSourcesControl;

    /* no need to check for FIRC - it can't be disabled */
    /* check for IRC */
    if (MCU_IPW_IRC_UNDER_MCU_CONTROL == (u8ClockSourceControl & MCU_IPW_IRC_UNDER_MCU_CONTROL))
    {
        /* mark IRC as disabled */
        u32ClockConfig &= (uint32)(~MC_ME_GS_S_IRCOSC_MASK32);
    }

    /* check for XOSC */
    if (MCU_IPW_XOSC_UNDER_MCU_CONTROL == (u8ClockSourceControl & MCU_IPW_XOSC_UNDER_MCU_CONTROL))
    {
        /* mark XOSC as disabled */
        u32ClockConfig &= (uint32)(~MC_ME_GS_S_XOSC_MASK32);
    }

    /* check for PLL0 */
    if (MCU_IPW_PLL0_UNDER_MCU_CONTROL == (u8ClockSourceControl & MCU_IPW_PLL0_UNDER_MCU_CONTROL))
    {
        /* mark PLL0 as disabled */
        u32ClockConfig &= (uint32)(~MC_ME_GS_S_PLL0_MASK32);
    }

    /* check for PLL1 */
    if (MCU_IPW_PLL1_UNDER_MCU_CONTROL == (u8ClockSourceControl & MCU_IPW_PLL1_UNDER_MCU_CONTROL))
    {
        /* mark PLL1 as disabled */
        u32ClockConfig &= (uint32)(~MC_ME_GS_S_PLL1_MASK32);
    }

    /* so I know what i need to reconfigure and what i need to leave untouched */
    /* now it's time to determine if i need to switch the system clock to something that will remain
    enabled */
    /* the conditions are: system clock and XOSC / PLL0 / PLL1 are under mcu control */
    /* I will not check if the new configuration is the same as the old one -
    it takes too much time */
    u8ClockSourceControl &= (MCU_IPW_XOSC_UNDER_MCU_CONTROL | MCU_IPW_PLL0_UNDER_MCU_CONTROL | MCU_IPW_PLL1_UNDER_MCU_CONTROL);

    if((NULL_PTR != Mcu_pClockConfigPtr->MC_CGM_pClockConfig->apSystemClockConfig) && ((uint8)0x00U != u8ClockSourceControl))
    {
        /* drop to IRCOSC */
        /* we need to do this if the system is running from XOSC / PLLDIG */
        Mcu_MC_ME_SystemClkUpdate(MC_ME_SYSCLK_IRCOSC_U32);
    }

    /* here I apply the determined clock settings */
    Mcu_MC_ME_EnabledClkUpdate(u32ClockConfig);

    /* set up the clock distribution tree */
    Mcu_MC_CGM_ProgClockSwitchConfig( Mcu_pClockConfigPtr->MC_CGM_pClockConfig ) ;

    /* system clock tree */
    if(NULL_PTR != Mcu_pClockConfigPtr->MC_CGM_pClockConfig->apSystemClockConfig)
    {
        Mcu_MC_CGM_SystemClockConfig( Mcu_pClockConfigPtr->MC_CGM_pClockConfig );
    }

    /* aux clock tree */
    if( NULL_PTR != Mcu_pClockConfigPtr->MC_CGM_pClockConfig->apAuxClockConfig )
    {
        Mcu_MC_CGM_AuxClockConfig( Mcu_pClockConfigPtr->MC_CGM_pClockConfig );
    }

    /* configure XOSC */
#if (MCU_XOSC_UNDER_MCU_CONTROL == STD_ON)
    if ( NULL_PTR != Mcu_pClockConfigPtr->MC_XOSC_pClockConfig)
    {
        Mcu_XOSC_Config( Mcu_pClockConfigPtr->MC_XOSC_pClockConfig);
    }
#endif

    /* configure PLLDIG clock generators */
    Mcu_PLLDIG_PllConfig( Mcu_pClockConfigPtr->MC_PLLDIG_pClockConfig );

    /* Every Clock configuration need to adjust the wait-states for RAM and Flash. */
    /* Set the wait-states for Flash. */
    Mcu_FLASH_SetWS( Mcu_pClockConfigPtr->FLASH_pClockConfig);
#if (MCU_ECSM_SUPPORT == STD_ON)
    /* Set the wait-states for Ram (MUDCR egister of ECSM). */
    Mcu_ECSM_SetRamWS( Mcu_pClockConfigPtr->ECSM_pClockConfig);
#endif /* (MCU_ECSM_SUPPORT == STD_ON) */
#if (MCU_SRAMC_SUPPORT == STD_ON)
    /* Set the wait-states for Ram (PRCR1 register of RAM controller). */
    Mcu_PRAM_SetRamWS( Mcu_pClockConfigPtr->SRAMC_pClockConfig);
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */

    /* the configuration is finished */
    /* now it's time to restart all clock sources that the user chose to enable and control */
    /* i already have the list of enabled clock sources - FIRC + the status of the ones that are
    not under mcu controll */
    /* OR with the config requested by the user -> i get the list of the untouched ones + what the
    used wants enabled */
    u32TempClockConfig = u32ClockConfig ;
    u32ClockConfig |= Mcu_pClockConfigPtr->MC_CGM_pClockConfig->u32EnabledClkSources;

    /* filter only PLL's */
    /* get the ones that remain enabled */
    u32TempClockConfig &= ( MC_ME_GS_S_PLL0_MASK32 | MC_ME_GS_S_PLL1_MASK32 ) ;
    /* and compare them with the ones that are requested by the user */
    if(u32TempClockConfig != ((Mcu_pClockConfigPtr->MC_CGM_pClockConfig->u32EnabledClkSources) & (MC_ME_GS_S_PLL0_MASK32 | MC_ME_GS_S_PLL1_MASK32)))
    {
        /* I start some PLL's - I don't need to wait for them to start */
        /* because the user will have to call GetPllStatus */
        Mcu_MC_ME_BlindEnabledClockUpdate( u32ClockConfig );
    }
    else
    {
        /* no need for PLL's */
        Mcu_MC_ME_EnabledClkUpdate( u32ClockConfig );
    }

    /* Current clock configuration is available and valid only after System Clock is updated. */
    /* note: mask the sistem clock switch - keep the old clock source */
    /* check if the clk source will be PLL0 or PLL1 */
    if ((MC_ME_SYSCLK_IRCOSC_U32 == (Mcu_pClockConfigPtr->Mcu_u32SystemClkSource & MC_ME_SYSCLK_DISABLED_U32)) || \
        (MC_ME_SYSCLK_XOSC_U32  == (Mcu_pClockConfigPtr->Mcu_u32SystemClkSource & MC_ME_SYSCLK_DISABLED_U32)) \
       )
    {
        /* no pll used in this config */
        /* switch to that mode and enable CMU */
        /* if system clock is under MCU control switch to that mode */
        if (NULL_PTR != Mcu_pClockConfigPtr->MC_CGM_pClockConfig->apSystemClockConfig)
        {
            Mcu_MC_ME_SystemClkUpdate( Mcu_pClockConfigPtr->Mcu_u32SystemClkSource );
        }
        /* Set the Clock Monitoring Units ( CMU0 .. n ). */
        if ( MCU_CLK_NOTIF_EN == Mcu_pClockConfigPtr->Mcu_ClkNotification)
        {
            Mcu_CMU_Init( Mcu_pClockConfigPtr->Mcu_CMU_pConfig);
        }
    }
    else
    {
        /* the systen clock is derived from PLL */
        /* the user must wait until the PLL's are locked by pooling Mcu_GetPllStatus */
        /* and then call Mcu_DistributePllClock */
    }
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_NO_PLL == STD_OFF)
/**
* @brief              This function activates the main PLL as the system clock source.
* @details            This function sets the PLL as the system clock and also enables monitoring.
*                     Called by:
*                       - Mcu_DistributePllClock() from HLD.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_IPW_DistributePllClock( VAR( void, AUTOMATIC) )
{
    /* 'Mcu_pClockConfig' is set by Mcu_InitClock().
        It doesn't have sense to call PLL distribution without clock initalization. */
    if ( NULL_PTR != Mcu_pClockConfig)
    {

        /* if system clock is under MCU control switch  the sysclk to PLL */
        if (NULL_PTR != Mcu_pClockConfig->MC_CGM_pClockConfig->apSystemClockConfig)
        {
            Mcu_MC_ME_SystemClkUpdate( Mcu_pClockConfig->Mcu_u32SystemClkSource );
        }

        /* enable CMU if used */
        if ( MCU_CLK_NOTIF_EN == Mcu_pClockConfig->Mcu_ClkNotification)
        {
            Mcu_CMU_Init( Mcu_pClockConfig->Mcu_CMU_pConfig);
        }
    }
}
#endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
/**
* @brief            This function returns the lock status of the PLL.
* @details          The user takes care that the PLL is locked by executing Mcu_GetPllStatus.
*                   If the MCU_NO_PLL is TRUE the MCU_GetPllStatus has to return
*                   MCU_PLL_STATUS_UNDEFINED.
*                   Called by:
*                       - Mcu_GetPllStatus() from HLD.
*
* @return           Provides the lock status of the PLL.
* @retval           MCU_PLL_STATUS_UNDEFINED   PLL Status is unknown.
* @retval           MCU_PLL_LOCKED   PLL is locked.
* @retval           MCU_PLL_UNLOCKED    PLL is unlocked.
*
*/
FUNC( Mcu_PllStatusType, MCU_CODE) Mcu_IPW_GetPllStatus( VAR( void, AUTOMATIC))
{
    /* Pll status variable. */
    VAR( Mcu_PllStatusType, AUTOMATIC)   ePllStatus = MCU_PLL_STATUS_UNDEFINED;
    VAR( Mcu_PLLDIG_PllStatusType, AUTOMATIC) ePllDigStatus ;

    /* get the status from each peripheral */
    ePllDigStatus = Mcu_PLLDIG_GetPLLStatus();

    /* if a pll is unlocked return MCU_PLL_UNLOCKED */
    if ( MCU_PLLDIG_PLL_LOCKED == ePllDigStatus )
    {
        ePllStatus = MCU_PLL_LOCKED ;
    }
    else
    {
        ePllStatus = MCU_PLL_UNLOCKED ;
    }

    /* Return the PLL status. */
    return (Mcu_PllStatusType)ePllStatus;
}
#endif /* (MCU_NO_PLL == STD_OFF) */

/**
* @brief            This function initializes the mode structure.
* @details          This function intializes the mode structure by configuring the MC_ME module.
*                   Called by:
*                       - Mcu_SetMode() from HLD.
*
* @param[in]        Mcu_pModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_IPW_SetMode(P2CONST( Mcu_MC_ME_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pModeConfigPtr)
{
    /* Request new mode transition to MC_ME. */
    Mcu_MC_ME_ModeConfig( Mcu_pModeConfigPtr);
}


#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_PerformReset() from HLD.
*
* @param[in]        Mcu_pHwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_IPW_PerformReset(P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_pHwIPsConfigPtr)
{
    /* Performs a microcontroller reset.
       A RESET mode requested via the ME_MCTL register is passed to the MC_RGM, which generates a
       global system reset and initiates the reset sequence. */
    Mcu_MC_RGM_PerformReset( Mcu_pHwIPsConfigPtr->MC_RGM_pConfig );
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */



/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
FUNC( Mcu_ResetType, MCU_CODE) Mcu_IPW_GetResetReason( VAR( void, AUTOMATIC))
{
    VAR( Mcu_ResetType, AUTOMATIC)   eResetReason = MCU_RESET_UNDEFINED;

    eResetReason = Mcu_MC_RGM_GetResetReason();
    return (Mcu_ResetType) eResetReason;
}


/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
FUNC( Mcu_RawResetType, MCU_CODE) Mcu_IPW_GetResetRawValue( VAR( void, AUTOMATIC))
{
    VAR( Mcu_RawResetType, AUTOMATIC) ResetReason;

    ResetReason = Mcu_MC_RGM_GetResetRawValue();
    return (Mcu_RawResetType) ResetReason;
}


#if (MCU_GET_RAM_STATE_API == STD_ON)
FUNC (Mcu_RamStateType, MCU_CODE) Mcu_IPW_GetRamState( VAR( void, AUTOMATIC))
{
    VAR( Mcu_RamStateType, AUTOMATIC) eRamState;

    eRamState = Mcu_STCU_GetRamState();
    return (Mcu_RamStateType) eRamState;
}
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */


#if (MCU_GET_PERIPH_STATE_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) \
Mcu_IPW_GetPeripheralState(VAR( Mcu_PeripheralId, AUTOMATIC) Mcu_PeriphId)
{
    VAR( Std_ReturnType, AUTOMATIC) State;

    State = Mcu_MC_ME_GetPeripheralState( Mcu_PeriphId );
    return (Std_ReturnType) State;
}
#endif /* (MCU_GET_PERIPH_STATE_API == STD_ON) */


#if (MCU_GET_SYSTEM_STATE_API == STD_ON)
FUNC( uint32, MCU_CODE) Mcu_IPW_GetSystemState ( VAR( void, AUTOMATIC))
{
    VAR( uint32, AUTOMATIC)   u32State ;

    u32State = Mcu_SSCM_GetSystemState();
    return (uint32) u32State;
}
#endif /* (MCU_GET_SYSTEM_STATE_API == STD_ON) */


#if (MCU_POWERMODE_STATE_API == STD_ON)
FUNC( Mcu_PowerModeStateType, MCU_CODE) Mcu_IPW_GetPowerModeState( VAR( void, AUTOMATIC))
{
    VAR( Mcu_PowerModeStateType, AUTOMATIC)   State ;

    State = Mcu_MC_ME_GetPowerModeState();
    return (Mcu_PowerModeStateType) State;
}
#endif /*(MCU_POWERMODE_STATE_API == STD_ON)*/


#if (MCU_GET_POWER_DOMAIN_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_IPW_GetPowerDomainState( VAR( void, AUTOMATIC))
{
    VAR( Std_ReturnType, AUTOMATIC)   State ;

    State = Mcu_MC_PCU_Get_PcuState();
    return (Std_ReturnType) State;
}
#endif /*(MCU_GET_POWER_DOMAIN_API == STD_ON)*/


#if (MCU_GET_MEM_CONFIG_API == STD_ON)
FUNC( Mcu_SSCM_MemConfigType, MCU_CODE ) Mcu_IPW_SscmGetMemConfig( VAR( void, AUTOMATIC) )
{
    VAR( Mcu_SSCM_MemConfigType, AUTOMATIC)   MemConfig ;

    MemConfig = Mcu_SSCM_GetMemConfig();
    return (Mcu_SSCM_MemConfigType) MemConfig;
}
#endif /* (MCU_GET_MEM_CONFIG_API == STD_ON) */

#if (MCU_SSCM_GET_STATUS_API == STD_ON)
FUNC( Mcu_SSCM_StatusType, MCU_CODE ) Mcu_IPW_SscmGetStatus( VAR( void, AUTOMATIC) )
{
    VAR( Mcu_SSCM_StatusType, AUTOMATIC)   Status ;

    Status = Mcu_SSCM_GetStatus();
    return (Mcu_SSCM_StatusType) Status;
}
#endif /* (MCU_SSCM_GET_STATUS_API == STD_ON) */


#ifdef MCU_SSCM_GET_UOPS_API
#if (MCU_SSCM_GET_UOPS_API == STD_ON)
FUNC( Mcu_SSCM_UopsType, MCU_CODE ) Mcu_IPW_SscmGetUops( VAR( void, AUTOMATIC) )
{
    VAR( Mcu_SSCM_UopsType, AUTOMATIC)   Status ;

    Status = Mcu_SSCM_GetUops();
    return (Mcu_SSCM_UopsType) Status;
}
#endif /* (MCU_SSCM_GET_UOPS_API == STD_ON) */
#endif /* MCU_SSCM_GET_UOPS_API */


#if (MCU_GET_MIDR_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_IPW_GetMidrStructure(P2VAR( Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr)
{
    /* just call low level API */
    Mcu_SIUL2_GetMidrStructure( pMidr );
}
#endif /*(MCU_GET_MIDR_API == STD_ON)*/


#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
FUNC( void, MCU_CODE ) Mcu_IPW_Disable_CMU(VAR (uint8, AUTOMATIC) u8IndexCmu)
{
    Mcu_CMU_Disable_CMU(u8IndexCmu);
}
#endif
#endif


#if (MCU_RGM_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
FUNC(void, MCU_CODE) Mcu_IPW_RGM_ClearClockFailIrqFlags(VAR( void, AUTOMATIC))
{
    Mcu_MC_RGM_ClearClockMonitoringIrqFlags();
}
#endif


#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
FUNC(void, MCU_CODE) Mcu_IPW_CMU_ClearClockFailIrqFlags(VAR(uint8,AUTOMATIC) u8CmuIdx, VAR(uint32,AUTOMATIC) u32IsrMask)
{
    VAR( Std_ReturnType, AUTOMATIC) CmuStatus = (Std_ReturnType)E_OK;

    CmuStatus = Mcu_CMU_ClearClockFailIrqFlags(u8CmuIdx, u32IsrMask);
    MCU_PARAM_UNUSED(CmuStatus);
}
#endif

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

