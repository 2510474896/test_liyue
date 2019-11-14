/**
*   @file    Adc_Ctu2.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - CTU2 driver source file.
*   @details This is the CTU2 source file, mainly implemented for the CTU2 hardware IP.
*
*   @addtogroup ADC
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : ADCDIG
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
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Ctu2_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section Adc_Ctu2_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file
* There are different kinds of execution code sections.
* 
* @section Adc_Ctu2_c_REF_3
* Violates MISRA 2004 Advisory Rule 11.3, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware offset of the controller.
* The address calculated as an unsigned int is passed to a macro for initializing the
* pointer with that address (ex: see REG_WRITE32 macro).
*
* @section Adc_Ctu2_c_REF_4
* Violates MISRA 2004 Required Rule 14.7, Return statement before end of function.
* The return statement are used to simplify the code structure and easier readability.
*
* @section Adc_Ctu2_c_REF_5
* Violates MISRA 2004 Required Rule 10.1,
* Cast from integer type to different type or a wider integer type
* This is used for the Speed optimization of the memory access. 
*
* @section Adc_Ctu2_c_REF_6
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to a amcro for initializing the pointer with that address.
*
* @section Adc_Ctu2_c_REF_7
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
* arithmetic but used due to the code complexity
*
* @section Adc_Ctu2_c_REF_8
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Ctu2_c_REF_9
* Violates MISRA 2004 Required Rule 1.2, place reliance on undefined or unspecified behaviour
* This is used for the code complexity.
*
* @section Adc_Ctu2_c_REF_10
* Violates MISRA 2004 Required Rule 12.4, contain side effects of right-hand operand of a logical && or ||
* This is used because of the code complexity.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. All compilers used support more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "Adc_Cfg.h"
#include "Adc_Ctu2.h"
#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
#include "CDD_Mcl.h"

#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
  /** @violates @ref Adc_Ctu2_c_REF_2 Repeated include file */
  #include "Dem.h"
#endif

#include "Adc_Reg_eSys_Ctu2.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_CTU2_VENDOR_ID_C                    43
/** @violates @ref Adc_Ctu2_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C     4
/** @violates @ref Adc_Ctu2_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_CTU2_AR_RELEASE_MINOR_VERSION_C     0
/** @violates @ref Adc_Ctu2_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_CTU2_AR_RELEASE_REVISION_VERSION_C  3
#define ADC_CTU2_SW_MAJOR_VERSION_C             1
#define ADC_CTU2_SW_MINOR_VERSION_C             0
#define ADC_CTU2_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and CTUV2 header file are from the same vendor */
#if (ADC_CTU2_VENDOR_ID_C != ADC_CTU2_VENDOR_ID)
    #error "Adc_Ctu2.c and Adc_Ctu2.h have different vendor ids"
#endif

/* Check if source file and CTUV2 header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != ADC_CTU2_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != ADC_CTU2_AR_RELEASE_MINOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_C != ADC_CTU2_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Ctu2.c and Adc_Ctu2.h are different"
#endif

/* Check if source file and CTUV2 header file are of the same Software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_C != ADC_CTU2_SW_MAJOR_VERSION) || \
     (ADC_CTU2_SW_MINOR_VERSION_C != ADC_CTU2_SW_MINOR_VERSION) || \
     (ADC_CTU2_SW_PATCH_VERSION_C != ADC_CTU2_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Adc_Ctu2.c and Adc_Ctu2.h are different"
#endif

/* Check if source file and ADC configuration header file are of the same vendor */
#if (ADC_CTU2_VENDOR_ID_C != ADC_VENDOR_ID_CFG)
#error "Adc_Ctu2.c and Adc_Cfg.h have different vendor ids"
#endif

/* Check if source file and ADC configuration header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != ADC_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != ADC_AR_RELEASE_MINOR_VERSION_CFG) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_C != ADC_AR_RELEASE_REVISION_VERSION_CFG) \
    )
#error "AutoSar Version Numbers of Adc_Ctu2.c and Adc_Cfg.h are different"
#endif

/* Check if source file and ADC configuration header file are of the same software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_C != ADC_SW_MAJOR_VERSION_CFG) || \
     (ADC_CTU2_SW_MINOR_VERSION_C != ADC_SW_MINOR_VERSION_CFG) || \
     (ADC_CTU2_SW_PATCH_VERSION_C != ADC_SW_PATCH_VERSION_CFG) \
    )
#error "Software Version Numbers of Adc_Ctu2.c and Adc_Cfg.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same vendor */
#if (ADC_CTU2_VENDOR_ID_C != ADC_CTU2_VENDOR_ID_REG)
    #error "Adc_Ctu2.c and Adc_Reg_eSys_Ctu2.h have different vendor ids"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != ADC_CTU2_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != ADC_CTU2_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_C != ADC_CTU2_AR_RELEASE_REVISION_VERSION_REG))
    #error "AutoSar Version Numbers of Adc_Ctu2.c and Adc_Reg_eSys_Ctu2.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_C != ADC_CTU2_SW_MAJOR_VERSION_REG) || \
     (ADC_CTU2_SW_MINOR_VERSION_C != ADC_CTU2_SW_MINOR_VERSION_REG) || \
     (ADC_CTU2_SW_PATCH_VERSION_C != ADC_CTU2_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of Adc_Ctu2.c and Adc_Reg_eSys_Ctu2.h are different"
#endif

/** @violates @ref Adc_Ctu2_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Ctu2.c and Mcal.h are different"
 #endif 
   /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Ctu2.c and SilRegMacros.h are different"
 #endif  
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
 /* Check if source file and Dem header file are of the same version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
     )
    #error "AutoSar Version Numbers of Adc_Ctu2.c and Dem.h are different"
 #endif
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
 /* Check if source file and DMA header file are of the same Autosar version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_C != MCL_AR_RELEASE_MINOR_VERSION)  \
    )
    #error "AutoSar Version Numbers of Adc_Ctu2.c and CDD_Mcl.h are different"
 #endif 
#endif


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
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
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Ctu2_c_REF_1 only preprocessor statements and comments before "#include"*/
/** @violates @ref Adc_Ctu2_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/** @violates @ref Adc_Ctu2_c_REF_5 cast from integer type to a other type or a wider integer type */
/**
* @brief          Global CTUv2 configuration structure pointer.
*
*/
P2CONST(Adc_Ctu2ConfigType, ADC_VAR, ADC_APPL_CONST) Adc_Ctu2_pCfgPtr = NULL_PTR;

#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Ctu2_c_REF_1 only preprocessor statements and comments before "#include"*/
/** @violates @ref Adc_Ctu2_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
* @violates @ref Adc_Ctu2_c_REF_1 only preprocessor statements and comments before "#include"
* @violates @ref Adc_Ctu2_c_REF_2 Repeated include file MemMap.h
*/
#include "MemMap.h"

#if (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2_CheckGre
(
    VAR(uint32, AUTOMATIC) u32CtuAddr
)
{
    VAR(volatile uint32, AUTOMATIC) u32Timeout = 5U;
    VAR(Std_ReturnType, AUTOMATIC) RetResult = (Std_ReturnType)E_OK;
      
    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */            
    REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_CGRE_U16);
    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */ 
    /** @violates @ref Adc_Ctu2_c_REF_10 the right-hand operand of a logical "&&" or "||" operator
      * shall not contain side effects.*/
    while((CTU2_CR_GRE_U16 == ((REG_READ16(CTU2_CR_ADDR16(u32CtuAddr)))&CTU2_CR_GRE_U16)) && (u32Timeout > 0UL))
    {
        u32Timeout--;
    }
    
    if (0UL == u32Timeout)
    {
        RetResult = (Std_ReturnType)E_NOT_OK;
    }
    return RetResult;    
} 
#endif
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief          This function initializes the CTUV2 hardware module.
* @details        Initializes all the CTUv2 registers and structures.
*
* @param[in]      pConfigPtr   CTUv2 configuration pointer structure.
*
* @return         void
*
* @api
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Init
(
    P2CONST(Adc_Ctu2ConfigType, AUTOMATIC, ADC_APPL_CONST) pConfigPtr
)
{
    VAR(uint8, AUTOMATIC)  u8Index = 0U;
    VAR(uint16, AUTOMATIC) u16DmaVal = 0U;
    VAR(uint16, AUTOMATIC) u16TriggerInterrupts = 0U;
    VAR(uint32, AUTOMATIC) u32ThreeZeroThcr = 0UL;
    VAR(uint32, AUTOMATIC) u32SevenFourThcr = 0UL;
    VAR(uint32, AUTOMATIC) u32Trigger03AdcDisplacement = 0UL;
    VAR(uint32, AUTOMATIC) u32Trigger47AdcDisplacement = 0UL;
    VAR(uint32, AUTOMATIC) u32FifoCtrRegVal = 0UL;
    VAR(uint32, AUTOMATIC) u32FifoTresholRegVal = 0UL;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    P2CONST(Adc_Ctu2TriggerConfigType, AUTOMATIC, ADC_APPL_CONST) pTriggerCfg;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;
    Adc_Ctu2_pCfgPtr = pConfigPtr;

    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            pTriggerCfg = &(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].TriggerCfg);
            /* Clear the CTUEFR_IFR flag */
            /* Clear the error flag */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_EFR_ADDR16(u32CtuAddr), REG_READ16(CTU2_EFR_ADDR16(u32CtuAddr)));
            /* Clear the interrupt flag */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_IFR_ADDR16(u32CtuAddr), REG_READ16(CTU2_IFR_ADDR16(u32CtuAddr)));

            /* TGS Counter reload value */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCRR_ADDR32(u32CtuAddr), pTriggerCfg->u16TgsCounterReloadValue);
            /* Stop TGS counter at this value */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCCR_ADDR16(u32CtuAddr), pTriggerCfg->u16TgsCounterCompareValue);

            /* Update the Trigger Compare Registers for each trigger in CTUV2
            * Calculate the u16TriggerInterrupts status, in order to update the CTUV2_CTUIR register.
            */
            u16TriggerInterrupts = 0U;
            for (u8Index = 0U; u8Index < (uint8)ADC_CTU2_MAX_TRIGGERS_U8; u8Index++ )
            {
                /* Trigger u8Index occurs when TGS counter reaches TriggerCompareValues[u8Index] */
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                REG_WRITE16(CTU2_TxCR_ADDR16(u32CtuAddr, (uint32)u8Index), pTriggerCfg->TriggerCompareValues[u8Index]);

                /* Update the u16TriggerInterrupts value */
                u16TriggerInterrupts |= (uint16)((uint32)(pTriggerCfg->ActiveTriggers[u8Index]) << u8Index);
            }
            /* Move the active triggers part to the upper part of the word. */
            u16TriggerInterrupts = (uint16)((uint16)u16TriggerInterrupts << 8U);
            /* Activate implicitly the MRS_DMAE, MRS_IE and IEE interrupts */
            u16TriggerInterrupts |= (uint16)0x0007;

            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            /* Interrupt mask: T0_enable, interrupt error enable */
            REG_WRITE16(CTU2_IR_ADDR16(u32CtuAddr), u16TriggerInterrupts);

            /* no pulse mode on external trigger */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCR_ADDR16(u32CtuAddr), (uint16)0x00C0);

            /* Only ADC command outputs of the triggers are active. */
            u32ThreeZeroThcr = (uint32)CTU2_ADC_COMMAND_OUTPUTS_ACTIVE_U32;
            u32SevenFourThcr = (uint32)CTU2_ADC_COMMAND_OUTPUTS_ACTIVE_U32;

            /* Process each active triggers, constructing the values to be written in the THCRx registers */
            u32ThreeZeroThcr |= (uint32)( \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[0]) << 6U)  | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[1]) << 14U) | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[2]) << 22U) | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[3]) << 30U) \
                                        );
            u32SevenFourThcr |= (uint32)( \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[4]) << 6U)  | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[5]) << 14U) | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[6]) << 22U) | \
                                            (uint32)((uint32)(pTriggerCfg->ActiveTriggers[7]) << 30U) \
                                        );

            /* Enable associated ETIMER channels where needed */
            u32ThreeZeroThcr |= (uint32)( \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[0]) << 0U)  | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[1]) << 8U)  | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[2]) << 16U) | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[3]) << 24U) \
                                        );
            u32SevenFourThcr |= (uint32)( \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[4]) << 0U)  | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[5]) << 8U)  | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[6]) << 16U) | \
                                            (uint32)((uint32)(pTriggerCfg->AssociatedEtimerCh[7]) << 24U) \
                                        );

            /* Write the 0-3 triggers values */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_THCR1_ADDR32(u32CtuAddr), u32ThreeZeroThcr);
            /* Write the 4-7 triggers values */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_THCR2_ADDR32(u32CtuAddr), u32SevenFourThcr);

            /* Get the values of the ADC command displacements for the Triggers */
            u32Trigger03AdcDisplacement = (uint32)( \
                                                    (uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[0] ) | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[1]) << 8U)  | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[2]) << 16U) | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[3]) << 24U) \
                                                  );
            u32Trigger47AdcDisplacement = (uint32)( \
                                                    (uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[4] ) | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[5]) << 8U)  | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[6]) << 16U) | \
                                                    (uint32)((uint32)(pTriggerCfg->TriggerAdcCommandDisplacement[7]) << 24U) \
                                                  );
            /* Program the registers */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_CLCR1_ADDR32(u32CtuAddr), u32Trigger03AdcDisplacement);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_CLCR2_ADDR32(u32CtuAddr), u32Trigger47AdcDisplacement);

            /* Control ON time - guard time for external trigger */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_COTR_ADDR16(u32CtuAddr), pTriggerCfg->u16ControlOnTime);

            /* calculate which dma channel is active, and the final value to write into the register */
            u16DmaVal = 0U;
            u32FifoTresholRegVal = 0UL;
            for (u8Index = 0U; u8Index < (uint8)ADC_CTU2_MAX_DMA_U8; u8Index++ )
            {
                /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
                u16DmaVal = (uint16)(u16DmaVal | (uint16)(((uint32)(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].FifoCfg.ActiveDmaChannels[u8Index])) << u8Index ));

                /* considering only FIFO FULL interrupts/exceptions enablements. */
                /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
                u32FifoCtrRegVal |= (uint32)((uint32)(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].FifoCfg.ActiveFifo[u8Index]) << (4U * u8Index));

                /* calculate the word to be written into the Fifo Threshold Register */
                /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
                u32FifoTresholRegVal |= (uint32)((uint32)(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].FifoCfg.FifoThreshold[u8Index]) << (8U * u8Index));
            }

            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u8OverflowTrigger)
            {
                u32FifoCtrRegVal = (u32FifoCtrRegVal << 2UL);
            }

            /* activate all active dma channels */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_FDCR_ADDR32(u32CtuAddr), u16DmaVal);
            /* activate fifo full exception on all active fifo's */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_FCR_ADDR32(u32CtuAddr), u32FifoCtrRegVal);
            /* Specify which fifo has what threshold */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_FTH_ADDR32(u32CtuAddr), u32FifoTresholRegVal);

            /* Program all the CTUV2_ADC command registers, with the provided commands. */
            for (u8Index = 0U; u8Index < (uint8)ADC_CTU2_MAX_ADC_COMMANDS_U8; u8Index++ )
            {
                /**
                 * @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer
                 * @violates @ref Adc_Ctu2_c_REF_7 Array indexing
                 */
                REG_WRITE16(CTU2_CLRx_ADDR16(u32CtuAddr, (uint32)u8Index), Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].AdcCommands[u8Index]);
            }

            /* Update the double buffered registers */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_GRE_U16);
            u8ArrayIdx++;
        }
    }
}
  
/**
* @brief          This function de-initializes the CTUV2 hardware.
* @details        De-initializes all the CTUv2 registers and structures.
*
* @param[in]      void
*
* @return         void
*
* @api
*/
FUNC(void, ADC_CODE) Adc_Ctu2_DeInit(void)
{
    VAR(uint8, AUTOMATIC) u8Index = 0U;
    VAR(uint8, AUTOMATIC) u8Idx = 0U;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;
    P2CONST(Adc_Ctu2FifoConfigurationType, AUTOMATIC, ADC_APPL_CONST) fifoConfig = NULL_PTR;
    VAR(uint32, AUTOMATIC) u32FifoAddress = 0U;
    Adc_Ctu2_StopCtu();

    /** @violates @ref Adc_Ctu2_c_REF_5 cast from integer type to a other type or a wider integer type */
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCRR_ADDR32(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCCR_ADDR16(u32CtuAddr), (uint16)0x0000U);

            for (u8Index = (uint8)0; u8Index < (uint8)ADC_CTU2_MAX_TRIGGERS_U8; u8Index++ )
            {
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                REG_WRITE16(CTU2_TxCR_ADDR16(u32CtuAddr, (uint32)u8Index), (uint16)0x0000U);
            }

            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_IR_ADDR16(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_TGSCR_ADDR16(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_THCR1_ADDR32(u32CtuAddr), (uint32)0x00000000UL);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_THCR2_ADDR32(u32CtuAddr), (uint32)0x00000000UL);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_COTR_ADDR16(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_FDCR_ADDR32(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_FDCR_ADDR32(u32CtuAddr), (uint16)0x0000U);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_FCR_ADDR32(u32CtuAddr), (uint32)0x00000000UL);
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_FTH_ADDR32(u32CtuAddr), (uint32)0x00000000UL);

            /* clear fifos */
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            fifoConfig = &(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].FifoCfg);
            for(u8Index = 0U; u8Index < (uint8)ADC_CTU2_MAX_FIFOS_U8; u8Index++)
            {
                if (1U == fifoConfig->ActiveFifo[u8Index]) /* the u8Index'th fifo is active */
                {
                    /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
                    u32FifoAddress = CTU2_FIFO_ADDR32(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress, (uint32)u8Index);
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                    while (0U == (REG_READ32(CTU2_FST_ADDR32(u32CtuAddr)) & (CTU2_FST_EMP_X_U32((uint32)u8Index))))
                    {
                        /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                        (void)REG_READ32(u32FifoAddress);
                    }
                }
            }
            
            /* Update the double buffered registers */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_CGRE_U16);
            u8ArrayIdx ++;
        }
    }
    Adc_Ctu2_pCfgPtr = NULL_PTR;
}

/**
* @brief          This function initializes the DMA hardware module, to read
*                 from the active fifo(s) to the user specified destination
*                 addresses.
* @details        Configures the DMA to use the user specified channel, to
*                 read from the user specified CTUv2 fifo, to the user
*                 specified buffer, when the configured channel will be active.
*
* @param[in]      void
*
* @return         void
*
* @api
*/
FUNC(void, ADC_CODE) Adc_Ctu2_SetupDma (void)
{
    VAR(Mcl_DmaTcdAttributesType, AUTOMATIC) DmaTcdConfig;
    P2VAR(Mcl_DmaTcdType, AUTOMATIC, ADC_APPL_DATA) pTcdAddress;
    VAR(uint8, AUTOMATIC) u8Index = 0U;
    VAR(uint32, AUTOMATIC) u32FifoAddress = 0U;
    VAR(uint16, AUTOMATIC) u16FifoThreshold = 0U;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel = 0U;
    P2VAR(uint32, AUTOMATIC, ADC_APPL_DATA) pUserBuffer = NULL_PTR;
    VAR(uint8, AUTOMATIC) u8Idx = 0U;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;

    /** @violates @ref Adc_Ctu2_c_REF_5 cast from integer type to a other type or a wider integer type */
    P2CONST(Adc_Ctu2FifoConfigurationType, AUTOMATIC, ADC_APPL_CONST) fifoConfig = NULL_PTR;
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            fifoConfig = &(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].FifoCfg);
            for(u8Index = 0U; u8Index < (uint8)ADC_CTU2_MAX_FIFOS_U8; u8Index++)
            {
                if (1U == fifoConfig->ActiveFifo[u8Index]) /* the u8Index'th fifo is active */
                {
                    /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
                    u32FifoAddress = CTU2_FIFO_ADDR32(Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress, (uint32)u8Index);
                    u16FifoThreshold = fifoConfig->FifoThreshold[u8Index];
                    pUserBuffer = fifoConfig->pUserBuffers[u8Index];
                    if (1U == fifoConfig->ActiveDmaChannels[u8Index]) /* if the DMA channel is active */
                    {
                        DmaChannel = fifoConfig->RealDmaChannel[u8Index]; /* get the real DMA ch number */

                        DmaTcdConfig.saddr = (uint32 )(u32FifoAddress);
                        DmaTcdConfig.ssize = (uint32)DMA_SIZE_4BYTES;  
                        DmaTcdConfig.dsize = (uint32)DMA_SIZE_4BYTES; 
                        DmaTcdConfig.soff = (uint32)0; 
                        DmaTcdConfig.num_bytes = (uint32) ((uint32)CTU2_DMA_TRANSFER_WORD_SIZE_U32*(uint32)((uint32)u16FifoThreshold + 1U)); 
                        /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                        /** Compiler_Warning: It is intended for the address of the element to be stored
                        in another non pointer element*/
                        DmaTcdConfig.daddr = (uint32)pUserBuffer; 
                        DmaTcdConfig.iter = (uint32)1; 
                        DmaTcdConfig.doff = (uint32)(CTU2_DMA_TRANSFER_WORD_SIZE_U32); 
                        DmaTcdConfig.smod = (uint32)0; 
                        DmaTcdConfig.dmod = (uint32)0; 

                        /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                        pTcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress((Mcl_ChannelType)DmaChannel);
                        /** @violates @ref Adc_Ctu2_c_REF_9 undefined behavior */
                        Mcl_DmaConfigScatterGatherTcd(pTcdAddress, &DmaTcdConfig, 
                        /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                        (Mcl_DmaTcdType*)((uint32)(~((uint32)CTU2_DMA_TRANSFER_WORD_SIZE_U32*(((uint32)u16FifoThreshold) + 1U)))+1U));
                        Mcl_DmaTcdSetFlags(pTcdAddress, (uint8)(DMA_TCD_DISABLE_REQ | DMA_TCD_INT_HALF));
                    }
                }
            }
            u8ArrayIdx++;
        }
    }
}

/**
* @brief          This function starts the CTUV2 hardware module configured.
* @details        Starts the input signals of the module.
*
* @param[in]      void
*
* @return         void
*
* @api
*/
FUNC(void, ADC_CODE) Adc_Ctu2_StartCtu(void)
{
    VAR(uint32, AUTOMATIC) u32Timeout;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;

    /** @violates @ref Adc_Ctu2_c_REF_5 cast from integer type to a other type or a wider integer type */   
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            /* Load the timeout counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;

            /* Program the accepted inputs of the CTUV2 module */
            /**
             * @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer
             * @violates @ref Adc_Ctu2_c_REF_7 Array indexing
             */
            REG_WRITE32(CTU2_TGSISR_ADDR32(u32CtuAddr), Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].TriggerCfg.u32InputSelectorValue);
            /* Generating synchronization signal to copy double buffered input selection register */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_TGSISR_RE_U16);

            /* Wait until the double buffered registers are updated */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            while((0U != (REG_READ16(CTU2_CR_ADDR16(u32CtuAddr))&CTU2_CR_TGSISR_RE_U16)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /** If the ADC hardware is not entered in power down state, report the production error */
            if (0UL == u32Timeout)
            {
            #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
                if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
                {
                    /* Report production error and return from function. */
                    Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
                }
            #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
                /** @violates @ref Adc_Ctu2_c_REF_4 Return statement before end of function. */
                return;
            }
            u8ArrayIdx ++;
        }
    }
}

/**
* @brief          This function stops the CTUV2 hardware module configured.
* @details        Stops the input signals of the module.
*
* @param[in]      void
*
* @return         void
*
* @api
*/
FUNC(void, ADC_CODE) Adc_Ctu2_StopCtu(void)
{
    VAR(uint32, AUTOMATIC) u32Timeout;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;

    /** @violates @ref Adc_Ctu2_c_REF_5 cast from integer type to a other type or a wider integer type */  
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            /* Load the timeout counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;

            /* Select no input signal on no edges. */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE32(CTU2_TGSISR_ADDR32(u32CtuAddr), 0x0UL);
            /* Generating synchronization signal to copy double buffered input selection register */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_TGSISR_RE_U16);

            /* wait until the double buffered registers are updated */
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
            while ((0U != (REG_READ16(CTU2_CR_ADDR16(u32CtuAddr))&CTU2_CR_TGSISR_RE_U16)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /** If the ADC hardware is not entered in power down state, report the production error */
            if (0UL == u32Timeout)
            {
            #if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
                if((uint32)STD_ON == Adc_E_TimeoutCfg.state)
                {
                    /* Report production error and return from function. */
                    Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
                }
            #endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
                /** @violates @ref Adc_Ctu2_c_REF_4 Return statement before end of function. */
                return;
            }
            u8ArrayIdx ++;
        }
    }
}

#if (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON)
/**
* @brief            Function to set the trigger handler control registers of the CTUV2 IP.
*
* @details          Full configurability of CTU THCR1 & THCR2 registers of the CTUv2 IP.
*                   This function has in input the CTU trigger (0...7) and the mask (8 bit)
*                   to enable the External Trigger and Timer output for that Trigger, without considering
*                   the ADC command output enable.
*                   See from the RM the THCR1 and THCR2 registers for the right Thcr_value to use.
*
* @param[in]        u8Trigger      Index of the trigger: 0...7.
* @param[in]        u8Thcr_value   THCRx mask value (only with bits for Ext. Trigger and Timer) for the selected input trigger.
*
* @return           Std_ReturnType  E_OK or E_NOT_OK.
*
* @api
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2_ConfigureTrigger
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(uint8, AUTOMATIC) u8ThcrValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) RetResult = (Std_ReturnType)E_OK;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;

    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            u8ThcrValue = u8ThcrValue&CTU2_TRIGGER_EXT_TIMER_OUTPUT_MASK_U32;

            if ((Std_ReturnType)E_NOT_OK == Adc_Ctu2_CheckGre(u32CtuAddr))
            {
                RetResult = (Std_ReturnType)E_NOT_OK;
                break;
            }
            else
            {
                if (u8Trigger <  ADC_CTU2_MAX_TRIGGERS_DIV2_U8)
                {
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */ 
                    REG_RMW32(CTU2_THCR1_ADDR32(u32CtuAddr), \
                              CTU2_THCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_EXT_TIMER_OUTPUT_MASK_U32), \
                              CTU2_THCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)u8ThcrValue) \
                             );
                }
                else
                {
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */   
                    REG_RMW32(CTU2_THCR2_ADDR32(u32CtuAddr), \
                              CTU2_THCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_EXT_TIMER_OUTPUT_MASK_U32), \
                              CTU2_THCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)u8ThcrValue) \
                             );
                }
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */   
                REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_GRE_U16);
                RetResult = (Std_ReturnType)E_OK;
            }
            u8ArrayIdx ++;
        }
    }
    return RetResult;
}

/**
* @brief        Function to set/clear the bit Tx_E of the trigger handler control registers of the CTUV2 IP.
*
* @details      Full configurability of CTU THCR1 & THCR2 registers of the CTUv2 IP.
*               This function has in input the CTU trigger (0...7) and a Boolean to set/clear the right trigger bit.
*               See from the RM the THCR1 and THCR2 registers for the right API use.
*
* @param[in]    u8Trigger      Index of the trigger: 0...7.
* @param[in]    bEnable   if True, the bit Tx_E shall be set to 1, 0 otherwise
*
* @return       Std_ReturnType  E_OK or E_NOT_OK.
*
* @api
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2_EnableTrigger
(
  VAR(uint8, AUTOMATIC) u8Trigger,
  VAR(boolean, AUTOMATIC) bEnable
)
{
    VAR(Std_ReturnType, AUTOMATIC) RetResult = (Std_ReturnType)E_OK;
    VAR(uint32, AUTOMATIC) u32MaskValue = 0UL;
    VAR(uint16, AUTOMATIC) u16InterruptMask = 0U;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;

    if((boolean)FALSE != bEnable)
    {
        bEnable = (boolean)TRUE;
    }
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            if ((Std_ReturnType)E_NOT_OK == Adc_Ctu2_CheckGre(u32CtuAddr))
            {
                RetResult = (Std_ReturnType)E_NOT_OK;
                break;
            }
            else
            {
                if((boolean)TRUE == bEnable)
                {
                    if (u8Trigger < ADC_CTU2_MAX_TRIGGERS_DIV2_U8)
                    {
                        u32MaskValue=(uint32)(CTU2_THCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_ENABLE_OUTPUT_MASK_U32));
                    }
                    else
                    {
                        u32MaskValue=(uint32)(CTU2_THCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_ENABLE_OUTPUT_MASK_U32));
                    }
                    u16InterruptMask= (uint16) (CTU2_IR_T0_IE_U16<< u8Trigger);
                }
                if (u8Trigger <  ADC_CTU2_MAX_TRIGGERS_DIV2_U8)
                {
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                    REG_RMW32(CTU2_THCR1_ADDR32(u32CtuAddr),\
                              CTU2_THCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_ENABLE_OUTPUT_MASK_U32),\
                              u32MaskValue \
                             );
                }
                else
                {
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                    REG_RMW32(CTU2_THCR2_ADDR32(u32CtuAddr), \
                              CTU2_THCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_ENABLE_OUTPUT_MASK_U32),\
                              u32MaskValue \
                             );
                }
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                REG_RMW16(CTU2_IR_ADDR16(u32CtuAddr), \
                          ((uint32)CTU2_IR_T0_IE_U16 << ((uint8)u8Trigger)), u16InterruptMask \
                         );
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */            
                REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_GRE_U16);
                RetResult = (Std_ReturnType)E_OK;
            }
            u8ArrayIdx ++;
        }
    }
    return RetResult;
}


/**
* @brief          This function sets the cmd list handler control registers of the CTUV2 IP.
* @details        Full configurability of CTU CLCR1 & CLCR2 registers of the CTUv2 IP.
*                 This function has in input the CTU trigger (0...7) and the position of the first
*                 command in the command list.
*                 See from the RM the CLCR1 and CLCR2 registers for the right API use.
*
* @param[in]      u8Trigger      Index of the trigger: 0...7.
* @param[in]      u8ClcrValue   Position of the first command
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
*
* @api
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2_SetCmdListIndex
(
  VAR(uint8, AUTOMATIC) u8Trigger,
  VAR(uint8, AUTOMATIC) u8ClcrValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) RetResult = (Std_ReturnType)E_OK;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;
    
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */ 
            if ((Std_ReturnType)E_NOT_OK == Adc_Ctu2_CheckGre(u32CtuAddr))
            {
                RetResult = (Std_ReturnType)E_NOT_OK;
                break;
            }
            else
            {
                if (u8Trigger < ((uint8) ADC_CTU2_MAX_TRIGGERS_DIV2_U8))
                {  /* write the CLCR1 register */
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */ 
                    REG_RMW32(CTU2_CLCR1_ADDR32(u32CtuAddr),\
                              CTU2_CLCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_CMD_LIST_OUTPUT_MASK_U32),\
                              CTU2_CLCR1_TRIGGER_U32((uint32)u8Trigger, (uint32)u8ClcrValue) \
                             );
                }
                else
                {  /* write the CLCR2 register */
                    /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */  
                    REG_RMW32(CTU2_CLCR2_ADDR32(u32CtuAddr),\
                              CTU2_CLCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)CTU2_TRIGGER_CMD_LIST_OUTPUT_MASK_U32),\
                              CTU2_CLCR2_TRIGGER_U32((uint32)u8Trigger, (uint32)u8ClcrValue) \
                             );
                }
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */                
                REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_GRE_U16);
            }
            u8ArrayIdx ++;
        }
    }
    return RetResult;
}

/**
* @brief          This function sets the trigger compare registers of the CTUV2 IP.
* @details        Full configurability of CTU TxCR registers of the CTUv2 IP.
*                 This function has in input the CTU trigger (0...7) and the comparator value
*                 See from the RM the TxCR trigger compare registers for the right u16CompareValue to use.
*
* @param[in]  u8Trigger      Index of the trigger: 0...7.
* @param[in]  u16CompareValue  value to set in the register TxCR.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Ctu2_SetTriggerCompareValue
(
    VAR(uint8, AUTOMATIC) u8Trigger,
    VAR(uint16, AUTOMATIC) u16CompareValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) RetResult = (Std_ReturnType)E_OK;
    VAR(uint8, AUTOMATIC) u8Idx;
    VAR(uint32, AUTOMATIC) u32CtuAddr;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;
    
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            /** @violates @ref Adc_Ctu2_c_REF_7 Array indexing */
            u32CtuAddr = Adc_Ctu2_pCfgPtr->pUnitConfig[u8ArrayIdx].u32BaseAddress;
            if ((Std_ReturnType)E_NOT_OK == Adc_Ctu2_CheckGre(u32CtuAddr))
            {
                RetResult = (Std_ReturnType)E_NOT_OK;
                break;
            }
            else
            {
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */
                REG_WRITE16(CTU2_TxCR_ADDR16(u32CtuAddr, (uint32)u8Trigger), u16CompareValue);
                /** @violates @ref Adc_Ctu2_c_REF_6 cast from unsigned int to pointer */ 
                REG_WRITE16(CTU2_CR_ADDR16(u32CtuAddr), CTU2_CR_GRE_U16);
            }
            u8ArrayIdx ++;
        }
    }
    return RetResult;
}
#endif/* (ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS == STD_ON) */

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Ctu2_c_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Ctu2_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#endif /* ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON */

#ifdef __cplusplus
}
#endif

/** @} */
