/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcu_MC_RGM.c $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:32CST $

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
*   @file    Mcu_MC_RGM.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Mcu - Reset Generation Module functions implementation.
*   @details Specific functions for MC_RGM configuration and control.
*            Part of the Magic Carpet hw IP.
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
* @section Mcu_MC_RGM_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_MC_RGM_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_MC_RGM_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers. The defines
* are validated.
*
* @section Mcu_MC_RGM_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between
* a pointer to a function and any type other than an integral type.
* Appears when accessing memory-mapped registers.
*
* @section Mcu_MC_RGM_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
*
* @section Mcu_MC_RGM_c_REF_6
* Violates MISRA 2004 Required Rule 1.2, No reliance shall be placed on undefined or
* unspecified behaviour.
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
#include "Mcu_MC_RGM.h"
/** @violates @ref Mcu_MC_RGM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_MC_ME.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
#include "Mcu_IPW_Irq.h"
#endif

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_MC_RGM_VENDOR_ID_C                      43
/**
* @violates @ref Mcu_MC_RGM_c_REF_3 The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
*/
#define MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C       4
/**
* @violates @ref Mcu_MC_RGM_c_REF_3 The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
*/
#define MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C       0
/**
* @violates @ref Mcu_MC_RGM_c_REF_3 The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
*/
#define MCU_MC_RGM_AR_RELEASE_REVISION_VERSION_C    3
#define MCU_MC_RGM_SW_MAJOR_VERSION_C               1
#define MCU_MC_RGM_SW_MINOR_VERSION_C               0
#define MCU_MC_RGM_SW_PATCH_VERSION_C               0


/*==================================================================================================
                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if current file and Mcu_ME_RGM header file are of the same vendor */
#if (MCU_MC_RGM_VENDOR_ID_C != MCU_MC_RGM_VENDOR_ID)
    #error "Mcu_MC_RGM.c and Mcu_MC_RGM.h have different vendor ids"
#endif
/* Check if current file and Mcu_ME_RGM header file are of the same Autosar version */
#if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_REVISION_VERSION_C != MCU_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM.c and Mcu_MC_RGM.h are different"
#endif
/* Check if current file and Mcu_ME_RGM header file are of the same Software version */
#if ((MCU_MC_RGM_SW_MAJOR_VERSION_C != MCU_MC_RGM_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_SW_MINOR_VERSION_C != MCU_MC_RGM_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_SW_PATCH_VERSION_C != MCU_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_RGM.c and Mcu_MC_RGM.h are different"
#endif

/* Check if current file and Mcu_MC_ME header file are of the same vendor */
#if (MCU_MC_RGM_VENDOR_ID_C != MCU_MC_ME_VENDOR_ID)
    #error "Mcu_MC_RGM.c and Mcu_MC_ME.h have different vendor ids"
#endif
/* Check if current file and Mcu_MC_ME header file are of the same Autosar version */
#if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C    != MCU_MC_ME_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_REVISION_VERSION_C != MCU_MC_ME_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM.c and Mcu_MC_ME.h are different"
#endif
/* Check if current file and Mcu_MC_ME header file are of the same Software version */
#if ((MCU_MC_RGM_SW_MAJOR_VERSION_C != MCU_MC_ME_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_SW_MINOR_VERSION_C != MCU_MC_ME_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_SW_PATCH_VERSION_C != MCU_MC_ME_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_RGM.c and Mcu_MC_ME.h are different"
#endif

#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
/* Check if current file and Mcu_IPW_Irq header file are of the same vendor */
#if (MCU_MC_RGM_VENDOR_ID_C != MCU_IPW_IRQ_VENDOR_ID)
    #error "Mcu_MC_RGM.c and Mcu_IPW_Irq.h have different vendor ids"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Autosar version */
#if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (MCU_MC_RGM_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_MC_RGM.c and Mcu_IPW_Irq.h are different"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Software version */
#if ((MCU_MC_RGM_SW_MAJOR_VERSION_C != MCU_IPW_IRQ_SW_MAJOR_VERSION) || \
     (MCU_MC_RGM_SW_MINOR_VERSION_C != MCU_IPW_IRQ_SW_MINOR_VERSION) || \
     (MCU_MC_RGM_SW_PATCH_VERSION_C != MCU_IPW_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_MC_RGM.c and Mcu_IPW_Irq.h are different"
#endif
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_MC_RGM.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and DEM header file are of the same version */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_MC_RGM.c and Dem.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_MC_RGM_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_MC_RGM_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_MC_RGM.c and SilRegMacros.h are different"
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
* @violates @ref Mcu_MC_RGM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_MC_RGM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


/**
* @brief            This function initializes the Reset parameters.
* @details          This function configures disabling the functional event reset, disabling the
*                   destructive event reset, the functional event alternate request, the
*                   destructive event alternate request, the functional event short sequence, the
*                   standby reset sequence and enabling the functional bidirectional reset.
*                   Called by:
*                       - Mcu_IPW_Init() from IPW.
*
* @param[in]        MC_RGM_pConfigPtr   Pointer to the MC_RGM configuration structure.
*
* @return           void
*
*/
FUNC(void, MCU_CODE) Mcu_MC_RGM_ResetInit(P2CONST( Mcu_MC_RGM_ConfigType, AUTOMATIC, MCU_APPL_DATA) MC_RGM_pConfigPtr)
{
#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_04_01_00) || \
     (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* 'Destructive' Event Reset Disable Register (RGM_DERD) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_DERD_ADDR32, (MC_RGM_pConfigPtr->u32DestResetOpt));
#endif

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* 'Destructive' Event Alternate Request Register (RGM_DEAR) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_DEAR_ADDR32, (MC_RGM_pConfigPtr->u32DestSafeIsrOpt));
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) ||
           (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00)) */

    /* 'Destructive' Bidirectional Reset Enable Register (RGM_DBRE) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_DBRE_ADDR32, (MC_RGM_pConfigPtr->u32DestExtPinReset));

    /* 'Functional' Event Reset Disable Register (RGM_FERD) */
#ifdef ERR_IPV_MC_0044
#if (ERR_IPV_MC_0044 == STD_ON)
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FERD_ADDR32, (MC_RGM_pConfigPtr->u32FuncResetOpt) & (~MC_RGM_FERD_D_ESR0_MASK32));
#else
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FERD_ADDR32, (MC_RGM_pConfigPtr->u32FuncResetOpt));
#endif /* (ERR_IPV_MC_0044 == STD_ON) */
#else
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FERD_ADDR32, (MC_RGM_pConfigPtr->u32FuncResetOpt));
#endif /* ERR_IPV_MC_0044 */

    /* 'Functional' Event Alternate Request Register (RGM_FEAR) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FEAR_ADDR32, (MC_RGM_pConfigPtr->u32FuncSafeIsrOpt));

    /* 'Functional' Bidirectional Reset Enable Register (RGM_FBRE) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FBRE_ADDR32, (MC_RGM_pConfigPtr->u32FuncExtPinReset));

    /* 'Functional' Event Short Sequence Register (RGM_FESS) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK32( MC_RGM_BASEADDR, MC_RGM_FESS_ADDR32, (MC_RGM_pConfigPtr->u32FuncPhase1or3Opt));

    /* 'Functional' Reset Escalation Threshold Register (MC_RGM_FRET) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK8(  MC_RGM_BASEADDR, MC_RGM_FRET_ADDR8,  (MC_RGM_pConfigPtr->u8ThresholdReset));

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) || \
     (IPV_MC == IPV_MC_04_06_01_00) || (IPV_MC == IPV_MC_04_06_05_00) || \
     (IPV_MC == IPV_MC_05_00_00_10) || (IPV_MC == IPV_MC_05_00_00_07) || \
     (IPV_MC == IPV_MC_04_04_01_00) \
    )
    /* 'Destructive' Reset Escalation Threshold Register (MC_RGM_DRET) */
#ifdef ERR_IPV_MC_0042
#if (ERR_IPV_MC_0042  != STD_ON)
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK8(MC_RGM_BASEADDR, MC_RGM_DRET_ADDR8, (MC_RGM_pConfigPtr->u8DesThresholdReset));
#endif /* (ERR_IPV_MC_0042  != STD_ON) */
#else
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE_LOCK8(MC_RGM_BASEADDR, MC_RGM_DRET_ADDR8, (MC_RGM_pConfigPtr->u8DesThresholdReset));
#endif /* ERR_IPV_MC_0042 */
#endif /* IPV_MC == IPV_MC_04_00_15_15 */
}


/**
* @brief            This function returns the Reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_IPW_GetResetReason() from IPW.
*
* @return           Reason of the Reset event.
* @retval           MCU_SOFT_DEST_RESET   Software destructive reset.
* @retval           MCU_POWER_ON_RESET   Power on event.
* @retval           MCU_1_2_LV_RESET   1.2 V low-voltage detected event.
* @retval           MCU_1_2_HV_RESET   1.2 V high-voltage detected event.
* @retval           MCU_2_7_LV_VREG_RESET   2.7 V low-voltage detected event (VREG).
* @return           MCU_2_7_LV_FLASH_RESET   2.7 V low-voltage detected event (FLASH).
* @retval           MCU_2_7_LV_IO_RESET   2.7 V low-voltage detected event (I/O).
* @retval           MCU_JTAG_RESET   JTAG initiated reset event.
* @retval           MCU_CORE_RESET   Core reset event.
* @retval           MCU_SOFT_RESET   Software destrutive event.
* @retval           MCU_CWD_RESET   Core watchdog reset event.
* @return           MCU_PLL0_RESET   PLL0 fail event.
* @retval           MCU_MC_RGM_OLR_RESET   Oscillator frequency lower than reference event.
* @retval           MCU_MC_RGM_FHL_RESET   CMU0 clock frequency higher/lower than reference event.
* @retval           MCU_FCCU_SAFE_RESET   FCCU safe mode event.
* @retval           MCU_SW_RESET   Software reset event.
* @retval           MCU_PLL1_RESET   PLL1 fail event.
* @return           MCU_FL_ECC_RCC_RESET   Flash, ECC or lock-step error event.
* @retval           MCU_MC_RGM12_FHL_RESET   CMU 1/2 clock frequence too high/low event.
* @retval           MCU_ST_DONE_RESET   Self-test completed event.
* @retval           MCU_FCCU_SOFT_RESET   FCCU soft reaction request event.
* @retval           MCU_FCCU_HARD_RESET   FCCU hard reaction request event.
* @retval           MCU_EXR_RESET   External reset event.
* @retval           MCU_RESET_UNDEFINED   Undefined reset source.
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons. The function Mcu_GetResetReason shall
*                   return MCU_RESET_UNDEFINED if this function is called prior to calling of the
*                   function Mcu_Init, and if supported by the hardware.
*/
FUNC( Mcu_ResetType, MCU_CODE) Mcu_MC_RGM_GetResetReason(VAR( void, AUTOMATIC))
{
    /* Code for the Reset event returned by this function. */
    VAR( Mcu_ResetType, AUTOMATIC) eResetReason = MCU_RESET_UNDEFINED;
    /* Time-out value for specific wait operations. */
    VAR( uint32, AUTOMATIC) u32TimeOut;
    /* Temporary variable for DES and FES registers value. */
    VAR( uint32, AUTOMATIC) u32RegValue = 0U;
    /* these registers will indicate witch flag will be erased in this call */
    VAR( uint32, AUTOMATIC) u32DesEraseFlag = 0U;
    VAR( uint32, AUTOMATIC) u32FesEraseFlag = 0U;    
    VAR( uint32, AUTOMATIC) u32Index;
    VAR( uint32, AUTOMATIC) u32DynamicMask;
    VAR( uint32, AUTOMATIC) u32Position = (uint32)0x00U;

    /* Check "Destructive Reset Reason" from DES Status Register. */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32RegValue = (uint32)REG_READ32(MC_RGM_DES_ADDR32) & MC_RGM_DES_RWBITS_MASK32;

    /* If at least one bit is set in RGM_DES register, then it means a some reset events are logged. */
    for (u32Index = 0x00U; u32Index < 0x20U; u32Index++)
    {
        u32DynamicMask = ((uint32)0x01U << u32Index);
        if ((uint32)0x00U != (u32DynamicMask & MC_RGM_DES_RWBITS_MASK32))
        {
            if ((uint32)0x00U != (u32DynamicMask & u32RegValue))
            {
                eResetReason = (Mcu_ResetType)u32Position;
                u32DesEraseFlag = u32DynamicMask;
                break;
            }
            u32Position++;
        }
    }
    
    if (MCU_RESET_UNDEFINED == eResetReason)
    {
        /* Check "Functional Reset Reason" from FES Status Register. */
        /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
        u32RegValue = (uint32)REG_READ32(MC_RGM_FES_ADDR32) & MC_RGM_FES_RWBITS_MASK32;
        
        if (0x00U != u32RegValue)
        {
            /* If at least one bit is set in RGM_DES register, then it means a some reset events are logged. */
            for (u32Index = 0x00U; u32Index < 0x20U; u32Index++)
            {
                u32DynamicMask = ((uint32)0x01U << u32Index);
                if ((uint32)0x00U != (u32DynamicMask & MC_RGM_FES_RWBITS_MASK32))
                {
                    if ((uint32)0x00U != (u32DynamicMask & u32RegValue))
                    {
                        eResetReason = (Mcu_ResetType)u32Position;
                        u32FesEraseFlag = u32DynamicMask;
                        break;
                    }
                    u32Position++;
                }
            }
        }
    }

    /* clear the selected reset flag for MC_RGM_DES_ADDR32 */
    if ( (uint32)0x00U != u32DesEraseFlag )
    {
        u32TimeOut = MCU_TIMEOUT_LOOPS;
        do
        {
            u32TimeOut--;
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            REG_WRITE32(MC_RGM_DES_ADDR32, u32DesEraseFlag);            
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            u32RegValue = REG_BIT_GET32(MC_RGM_DES_ADDR32, u32DesEraseFlag);
        }
        while (((uint32)0x00U != u32RegValue) && ((uint32)0x00U < u32TimeOut));

        if ( (uint32)0x00U == u32TimeOut)
        {
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.state)
            {
                Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.id, DEM_EVENT_STATUS_FAILED);
            }
#endif
        }
    }

    /* clear the selected reset flag for MC_RGM_FES_ADDR32 */
    if ((uint32)0x00U != u32FesEraseFlag)
    {
        u32TimeOut = MCU_TIMEOUT_LOOPS;
        do
        {
            u32TimeOut--;
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            REG_WRITE32(MC_RGM_FES_ADDR32, u32FesEraseFlag);            
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            u32RegValue = REG_BIT_GET32(MC_RGM_FES_ADDR32, u32FesEraseFlag);
        }
        while (((uint32)0x00U != u32RegValue) && ((uint32)0x00U < u32TimeOut));

        if ( (uint32)0x00U == u32TimeOut)
        {
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.state)
            {
                Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.id, DEM_EVENT_STATUS_FAILED);
            }
#endif
        }
    }
    
    return (Mcu_ResetType)eResetReason;
}


/**
* @brief            This function returns the Raw Reset value.
* @details          This routine returns the Raw Reset value that is read from the hardware.
*                   Called by:
*                       - Mcu_IPW_GetResetRawValue() from IPW.
*
* @return           Register value with the Reset status.
* @retval           uint32   Code of the Raw reset value.
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons.
*
*/
FUNC( Mcu_RawResetType, MCU_CODE) Mcu_MC_RGM_GetResetRawValue( VAR( void, AUTOMATIC))
{
    /* Temporary variable for DES and FES registers value. */
    VAR( uint32, AUTOMATIC) u32RawReset = (uint32)0x00U;
    VAR( uint32, AUTOMATIC) u32TimeOut;
    VAR( uint32, AUTOMATIC) u32RegValue;
    VAR( uint32, AUTOMATIC) u32Index;
    VAR( uint32, AUTOMATIC) u32DynamicMask;
    VAR( uint32, AUTOMATIC) u32Position;

    /* compact the 2x32 registers to 1x32 register */
    /* lower 16 bits will be FES, higher 16 bits will be DES */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32RegValue = REG_READ32( MC_RGM_FES_ADDR32) & MC_RGM_FES_RWBITS_MASK32;
        
    if ((uint32)0x00U != u32RegValue)
    {
        u32Position = (uint32)0x00U;
        
        for (u32Index = 0x00U; u32Index < 0x20U; u32Index++)
        {
            u32DynamicMask = ((uint32)0x01U << u32Index);
            if ((uint32)0x00U != (u32DynamicMask & MC_RGM_FES_RWBITS_MASK32))
            {
                if ((uint32)0x00U != (u32DynamicMask & u32RegValue))
                {
                    u32RawReset |= ((uint32)0x01U << u32Position);
                }
                u32Position++;
            }
        }
        
        /* functional events clear */
        u32TimeOut = MCU_TIMEOUT_LOOPS;
        do
        {
            u32TimeOut--;        
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            REG_WRITE32( MC_RGM_FES_ADDR32, u32RegValue);
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            u32RegValue = REG_READ32(MC_RGM_FES_ADDR32) & MC_RGM_FES_RWBITS_MASK32;
        }
        while (((uint32)0x00U != u32RegValue) && ((uint32)0x00U < u32TimeOut));
        
        if ( (uint32)0x0U == u32TimeOut)
        {
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.state)
            {
                Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.id, DEM_EVENT_STATUS_FAILED);
            }
#endif
        }
    }
    
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32RegValue = REG_READ32( MC_RGM_DES_ADDR32) & MC_RGM_DES_RWBITS_MASK32;

    if ((uint32)0x00U != u32RegValue)
    {
#if (IPV_MC == IPV_MC_04_06_05_00)
        u32Position = (uint32)0x08U;
#else
        u32Position = (uint32)0x10U;
#endif

        for (u32Index = 0x00U; u32Index < 0x20U; u32Index++)
        {
            u32DynamicMask = ((uint32)0x01U << u32Index);
            if ((uint32)0x00U != (u32DynamicMask & MC_RGM_DES_RWBITS_MASK32))
            {
                if ((uint32)0x00U != (u32DynamicMask & u32RegValue))
                {
                    u32RawReset |= ((uint32)0x01U << u32Position);
                }
                u32Position++;
            }
        }

        /* destructive events clear */
        u32TimeOut = MCU_TIMEOUT_LOOPS;
        do
        {
            u32TimeOut--;        
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            REG_WRITE32( MC_RGM_DES_ADDR32, u32RegValue);
            /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
            u32RegValue = REG_READ32(MC_RGM_DES_ADDR32) & MC_RGM_DES_RWBITS_MASK32;
        }
        while (((uint32)0x00U != u32RegValue) && ((uint32)0x00U < u32TimeOut));

        if ((uint32)0x0U == u32TimeOut)
        {
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.state)
            {
                Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.id, DEM_EVENT_STATUS_FAILED);
            }
#endif
        }
    }

    return (Mcu_RawResetType)u32RawReset;
}


#if (MCU_PERFORM_RESET_API == STD_ON)

/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   This is a chip-wide virtual mode during which the application is not active.
*                   The system remains in this mode until all resources are available for the
*                   embedded software to take control of the device.
*                   Called by:
*                       - Mcu_IPW_PerformReset() from IPW.
*
* @param[in]        MC_RGM_pConfigPtr  Pointer to the MC_RGM configuration structure.
*
* @return           void
*
*/
FUNC(void, MCU_CODE) Mcu_MC_RGM_PerformReset(P2CONST( Mcu_MC_RGM_ConfigType, AUTOMATIC, MCU_APPL_DATA) MC_RGM_pConfigPtr)
{
    switch (MC_RGM_pConfigPtr->Mcu_MC_RGM_eResetType)
    {
        case (MCU_FUNC_RESET):
        {
            /* Initiate "Functional Reset" Mode. */
            Mcu_MC_ME_ApplyMode( MCU_RESET_MODE);
            break;
        }
        case (MCU_DEST_RESET):
        {
            /* Initiate "Destructive Reset" Mode. */
            Mcu_MC_ME_ApplyMode( MCU_DEST_RESET_MODE);
            break;
        }
        default:
        {
            /* Default case - should never enter here. */
            break;
        }
    }
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */


#if (MCU_RESET_ALTERNATE_ISR_USED == STD_ON)
/**
* @brief            This function handle the 'Functional' Reset Alternate Event Interrupt for
*                   Leopard. This function handle the 'Functional' and 'Destructive' Reset
*                   Alternate Event Interrupt for Panther.
* @details          Assigned to INTC56 for MPC56XXL.
*                   Assigned to INTC255 for MPC57XXP.
*                   Only the following errors support interrupt reaction.
*                       - CMU12_FHL
*                       - PLL1
*                       - CMU0_FHL
*                       - CMU0_OLR
*                       - PLL0
*                       - CWD
*
* @return           void
* @implements Mcu_MC_RGM_ResetAlt_Int_Activity
*/
/** @violates @ref Mcu_MC_RGM_c_REF_5 Global declaration of function */
FUNC(void, MCU_CODE) Mcu_MC_RGM_ResetAlt_Int( VAR( void, AUTOMATIC))
{
#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
    VAR( uint32, AUTOMATIC) u32CmuIrqMask = 0U;
#endif
    /* functional event ISR's */
    VAR( uint32, AUTOMATIC) u32MCRGM_FunctionalEventStatus ;
    VAR( uint32, AUTOMATIC) u32MCRGM_EnabledFunctionalIsr ;
#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* destructive event ISR's on platform that support this feature */
    VAR( uint32, AUTOMATIC) u32MCRGM_DestructiveEventStatus ;
    VAR( uint32, AUTOMATIC) u32MCRGM_EnabledDestructiveIsr ;
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || ... */

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
 #ifdef ERR_IPV_MC_0045
  #if (STD_ON != ERR_IPV_MC_0045)
    VAR( uint8, AUTOMATIC) u8MCRGM_ExtResetOutputStatus;
  #endif /* (STD_ON != ERR_IPV_MC_0045) */
 #else
    VAR( uint8, AUTOMATIC) u8MCRGM_ExtResetOutputStatus;
 #endif /* ERR_IPV_MC_0045 */
#endif /* (IPV_MC == IPV_MC_04_00_15_15) */

    /* get the ISR status and enables isr's */
    /* functional */
    /* get only the bits that can generate a functional reset IRQ */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32MCRGM_FunctionalEventStatus = (uint32)(REG_READ32(MC_RGM_FES_ADDR32) & MC_RGM_FES_IRQ_BITS_MASK32);
    /* clear active IRQ's */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE32( MC_RGM_FES_ADDR32, u32MCRGM_FunctionalEventStatus);

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* destructive */
    /* reset only the bits that can generate an IRQ ( defined in RGM_DEAR ) */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32MCRGM_DestructiveEventStatus = (uint32)(REG_READ32(MC_RGM_DES_ADDR32) & MC_RGM_DES_IRQ_BITS_MASK32);
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE32( MC_RGM_DES_ADDR32, u32MCRGM_DestructiveEventStatus);
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15)) */

#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
    /* destructive */
 #ifdef ERR_IPV_MC_0045
  #if (STD_ON != ERR_IPV_MC_0045)
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u8MCRGM_ExtResetOutputStatus = (uint8)(REG_READ8(MC_RGM_EROEC_ADDR8) & MC_RGM_EROEC_EROEC_MASK32);
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE8( MC_RGM_EROEC_ADDR8, u8MCRGM_ExtResetOutputStatus);
  #endif /* (STD_ON != ERR_IPV_MC_0045) */
 #else
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u8MCRGM_ExtResetOutputStatus = (uint8)(REG_READ8(MC_RGM_EROEC_ADDR8) & MC_RGM_EROEC_EROEC_MASK32);
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    REG_WRITE8( MC_RGM_EROEC_ADDR8, u8MCRGM_ExtResetOutputStatus);
 #endif /* ERR_IPV_MC_0045 */
#endif /* (IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00) */

    /* get enabled ISR's */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32MCRGM_EnabledFunctionalIsr = REG_READ32(MC_RGM_FEAR_ADDR32) & MC_RGM_FEAR_RWBITS_MASK32;

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* destructive */
    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32MCRGM_EnabledDestructiveIsr = REG_READ32(MC_RGM_DEAR_ADDR32) & MC_RGM_DEAR_RWBITS_MASK32;
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15)) */

    /* signal event to upper layers */
    /* functional */
#if ((IPV_MC == IPV_MC_04_00_15_15) || (IPV_MC == IPV_MC_04_01_00_00))
  #ifdef ERR_IPV_MC_0045
    #if (STD_ON == ERR_IPV_MC_0045)
    if ((uint32)0x00U != u32MCRGM_FunctionalEventStatus)
    #else
    if (((uint32)0x00U != u32MCRGM_FunctionalEventStatus) || ((uint8)0x00U != u8MCRGM_ExtResetOutputStatus))
    #endif /* (STD_ON == ERR_IPV_MC_0045) */
  #else
    if (((uint32)0x00U != u32MCRGM_FunctionalEventStatus) || ((uint8)0x00U != u8MCRGM_ExtResetOutputStatus))
  #endif /* ERR_IPV_MC_0045 */
#else
    if ((uint32)0x00U != u32MCRGM_FunctionalEventStatus)
#endif /* (IPV_MC == IPV_MC_04_00_15_15) */
    {
        if ( (uint32)0x00U != u32MCRGM_EnabledFunctionalIsr )
        {
#ifdef MCU_ERROR_ISR_NOTIFICATION
            MCU_ERROR_ISR_NOTIFICATION(MCU_E_ISR_FUNC_RESET_ALT_FAILURE);
#endif
        }
    }

#if ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
     (IPV_MC == IPV_MC_04_01_00_00) || (IPV_MC == IPV_MC_04_06_01_00) || \
     (IPV_MC == IPV_MC_04_06_05_00) \
    )
    /* destructive */
    if ( (uint32)0x00U != u32MCRGM_DestructiveEventStatus )
    {
        if ( (uint32)0x00U != u32MCRGM_EnabledDestructiveIsr )
        {
#ifdef MCU_ERROR_ISR_NOTIFICATION
            MCU_ERROR_ISR_NOTIFICATION(MCU_E_ISR_DEST_RESET_ALT_FAILURE);
#endif
        }
    }
#endif /* ((IPV_MC == IPV_MC_04_03_00_00) || (IPV_MC == IPV_MC_04_00_15_15) || \
          (IPV_MC == IPV_MC_04_01_00_00)) */

    /* clear the CMU interrupt irq */
#if (MCU_CMU_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
#if (IPV_MC == IPV_MC_05_00_00_07)
        u32CmuIrqMask = MC_RGM_FES_F_CMU_OLR_MASK32;
#elif (IPV_MC == IPV_MC_05_00_00_10)
        u32CmuIrqMask = MC_RGM_FES_F_FXOSC_OR_MASK32;
#endif
    if ((uint32)0x00U != (u32MCRGM_FunctionalEventStatus & u32CmuIrqMask))
    {
        Mcu_IPW_CMU_ClearClockFailIrqFlags((uint8)0U, MCU_IPW_CMU_ISR_OLRI_MASK32);
    }
#endif
}
#endif /* ( MCU_RESET_ALTERNATE_ISR_USED == STD_ON ) */


#if (MCU_RGM_CLEAR_CLOCK_IRQ_FLAG == STD_ON)
/**
* @brief            This function clear the Reset Alternate Event Interrupt flags.
* @details          This function clear the Reset Alternate Event Interrupt flags which were
*                   generated by the CMU.
*
*
* @return           void
* @implements Mcu_MC_RGM_ClearClockMonitoringIrqFlags_Activity
*/
FUNC( void, MCU_CODE ) Mcu_MC_RGM_ClearClockMonitoringIrqFlags(VAR( void, AUTOMATIC))
{
    /* Timeout value for specific wait operations. */
    VAR( uint32, AUTOMATIC) u32TimeOut = MCU_TIMEOUT_LOOPS;
    VAR( uint32, AUTOMATIC) u32MaskValue = (uint32)0U;
    VAR( uint32, AUTOMATIC) u32RegValue;

#if (IPV_MC == IPV_MC_05_00_00_07)
    u32MaskValue = MC_RGM_FES_F_CMU_OLR_MASK32;
#elif (IPV_MC == IPV_MC_05_00_00_10)
    u32MaskValue = MC_RGM_FES_F_FXOSC_OR_MASK32;
#endif

    /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
    u32RegValue = REG_READ32(MC_RGM_FES_ADDR32);

    /* check if the F_CMU_OLR bit has been cleared */
    while (((uint32) 0x00 != (u32RegValue & u32MaskValue)) && (u32TimeOut > (uint32)0x0U))
    {
        /* clear it again */
        /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
        REG_WRITE32(MC_RGM_FES_ADDR32, (u32RegValue & u32MaskValue));
        /** @violates @ref Mcu_MC_RGM_c_REF_4 Conversion from int to pointer */
        u32RegValue = REG_READ32( MC_RGM_FES_ADDR32 );
        u32TimeOut--;
    }
}
#endif /* (MCU_RGM_CLEAR_CLOCK_IRQ_FLAG == STD_ON) */

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_MC_RGM_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_MC_RGM_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

