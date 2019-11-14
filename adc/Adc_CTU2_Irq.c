/**
*   @file    Adc_Ctu2_Irq.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Adc - CTU2 Interrupt source file.
*   @details CTU2 Interrupt source file.
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
* @section Adc_Ctu2_Irq_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section Adc_Ctu2_Irq_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file
* There are different kinds of execution code sections.
* 
* @section Adc_Ctu2_Irq_c_REF_3
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Ctu2_Irq_c_REF_4
* Violates MISRA 2004 Required Rule 10.1,
* Cast from integer type to different type or a wider integer type
* This is used for the Speed optimization of the memory access.
*
* @section Adc_Ctu2_Irq_c_REF_5
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to a macro for initializing the pointer with that address.
*
* @section Adc_Ctu2_Irq_c_REF_6
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared 
* in one and only one file.
* This violation cannot be removed due to the interaction with MCL module.
*
* @section Adc_Ctu2_Irq_c_REF_7
* Violates MISRA 2004 Required Rule 8.10, all declarations and definitions of objects or functions 
* at file scope shall have internal linkage unless external linkage is required.
* This violation cannot be removed due to the interaction with MCL module.
*
* @section Adc_Ctu2_Irq_c_REF_8
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
* arithmetic but used due to the code complexity
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
#include "Adc_Ipw.h"
#include "Adc_Ctu2.h"

#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"

#if (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON)
#include "CDD_Mcl.h"
#include "Adc_Reg_eSys_Ctu2.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_CTU2_AR_VENDOR_ID_IRQ_C                 43
/**
* @violates @ref Adc_Ctu2_Irq_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers
*/
#define ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C     4
/**
* @violates @ref Adc_Ctu2_Irq_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C     0
/**
* @violates @ref Adc_Ctu2_Irq_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_CTU2_AR_RELEASE_REVISION_VERSION_IRQ_C  3
#define ADC_CTU2_SW_MAJOR_VERSION_IRQ_C             1
#define ADC_CTU2_SW_MINOR_VERSION_IRQ_C             0
#define ADC_CTU2_SW_PATCH_VERSION_IRQ_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and CTUv2 header file are from the same vendor */
#if (ADC_CTU2_AR_VENDOR_ID_IRQ_C != ADC_CTU2_VENDOR_ID)
    #error "Adc_Ctu2_Irq.c and Adc_Ctu2.h have different vendor ids"
#endif

/* Check if source file and CTUv2 header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_MINOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and Adc_Ctu2.h are different"
#endif

/* Check if source file and CTUv2 header file are of the same Software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_IRQ_C != ADC_CTU2_SW_MAJOR_VERSION) || \
     (ADC_CTU2_SW_MINOR_VERSION_IRQ_C != ADC_CTU2_SW_MINOR_VERSION) || \
     (ADC_CTU2_SW_PATCH_VERSION_IRQ_C != ADC_CTU2_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Adc_Ctu2_Irq.c and Adc_Ctu2.h are different"
#endif

/* Check if source file and Adc_Ipw header file are from the same vendor */
#if (ADC_CTU2_AR_VENDOR_ID_IRQ_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Ctu2_Irq.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and Adc_Ipw header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_IRQ_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and Adc_Ipw.h are different"
#endif

/* Check if source file and Adc_Ipw header file are of the same Software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_IRQ_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_CTU2_SW_MINOR_VERSION_IRQ_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_CTU2_SW_PATCH_VERSION_IRQ_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Ctu2_Irq.c and Adc_Ipw.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same vendor */
#if (ADC_CTU2_AR_VENDOR_ID_IRQ_C != ADC_CTU2_VENDOR_ID_REG)
    #error "Adc_Ctu2_Irq.c and Adc_Reg_eSys_Ctu2.h have different vendor ids"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_CTU2_AR_RELEASE_REVISION_VERSION_IRQ_C != ADC_CTU2_AR_RELEASE_REVISION_VERSION_REG))
    #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and Adc_Reg_eSys_Ctu2.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Ctu2 header file are of the same software version */
#if ((ADC_CTU2_SW_MAJOR_VERSION_IRQ_C != ADC_CTU2_SW_MAJOR_VERSION_REG) || \
     (ADC_CTU2_SW_MINOR_VERSION_IRQ_C != ADC_CTU2_SW_MINOR_VERSION_REG) || \
     (ADC_CTU2_SW_PATCH_VERSION_IRQ_C != ADC_CTU2_SW_PATCH_VERSION_REG))
#error "Software Version Numbers of Adc_Ctu2_Irq.c and Adc_Reg_eSys_Ctu2.h are different"
#endif

/** @violates @ref Adc_Ctu2_Irq_c_REF_3 Identifier clash */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and DMA header file are of the same Autosar version */
#if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != MCL_AR_RELEASE_MINOR_VERSION)  \
    )
    #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and CDD_Mcl.h are different"
#endif
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and Mcal.h are different"
 #endif 
    /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_CTU2_AR_RELEASE_MAJOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_CTU2_AR_RELEASE_MINOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Ctu2_Irq.c and SilRegMacros.h are different"
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
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Ctu2_Irq_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Ctu2_Irq_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Ctu2_Irq_c_REF_1 only preprocessor statements and comments before "#include"*/
#include "MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Ctu2_Irq_c_REF_2 Repeated include file MemMap.h */
/** @violates @ref Adc_Ctu2_Irq_c_REF_1 only preprocessor statements and comments before "#include"*/
#include "MemMap.h"

STATIC uint8 Adc_Ctu2_GetIndexCtu2Active(VAR(uint8,AUTOMATIC) u8Unit);

ISR(CTU_0_MRS_I_InterruptHandler);
ISR(CTU_1_MRS_I_InterruptHandler);
ISR(CTU_0_T0_I_InterruptHandler);
ISR(CTU_1_T0_I_InterruptHandler);
ISR(CTU_0_T1_I_InterruptHandler);
ISR(CTU_1_T1_I_InterruptHandler);
ISR(CTU_0_T2_I_InterruptHandler);
ISR(CTU_1_T2_I_InterruptHandler);
ISR(CTU_0_T3_I_InterruptHandler);
ISR(CTU_1_T3_I_InterruptHandler);
ISR(CTU_0_T4_I_InterruptHandler);
ISR(CTU_1_T4_I_InterruptHandler);
ISR(CTU_0_T5_I_InterruptHandler);
ISR(CTU_1_T5_I_InterruptHandler);
ISR(CTU_0_T6_I_InterruptHandler);
ISR(CTU_1_T6_I_InterruptHandler);
ISR(CTU_0_T7_I_InterruptHandler);
ISR(CTU_1_T7_I_InterruptHandler);
ISR(CTU_0_FIFO0_I_InterruptHandler);
ISR(CTU_1_FIFO0_I_InterruptHandler);
ISR(CTU_0_FIFO1_I_InterruptHandler);
ISR(CTU_1_FIFO1_I_InterruptHandler);
ISR(CTU_0_FIFO2_I_InterruptHandler);
ISR(CTU_1_FIFO2_I_InterruptHandler);
ISR(CTU_0_FIFO3_I_InterruptHandler);
ISR(CTU_1_FIFO3_I_InterruptHandler);
ISR(CTU_0_ADC_I_InterruptHandler);
ISR(CTU_1_ADC_I_InterruptHandler);
ISR(CTU_0_ERR_I_InterruptHandler);
ISR(CTU_1_ERR_I_InterruptHandler);

/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo1Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo2Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo3Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo4Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo1Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo2Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo3Complete(void);
/** @violates @ref Adc_Ctu2_Irq_c_REF_6 Function declaration */
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo4Complete(void);


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          Get index of the CTUv2 IP active.
*
* @param[in]      u8Unit        CTUv2 unit.
*
* @return         uint8       index of the CTUv2 active.
*
*/
STATIC uint8 Adc_Ctu2_GetIndexCtu2Active(VAR(uint8,AUTOMATIC) u8Unit)
{
    VAR(uint8, AUTOMATIC) u8Idx = 0U;
    VAR(uint8, AUTOMATIC) u8ArrayIdx = 0U;
    for (u8Idx = 0U; u8Idx < (uint8)CTU_MAX_HW_UNITS; u8Idx++)
    {
        if ((uint8)STD_ON == Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Active)
        {
            if ((Adc_Ctu2_pCfgPtr->aCtu2UnitActive[u8Idx].u8Ctu2Unit == (uint8)u8Unit))
            {
                break;
            }
            else
            {
                u8ArrayIdx ++;
            }
        }  
    }
    return u8ArrayIdx;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the MRS_I_InterruptHandler for CTU_0.
* @details        The function implements the MRS_I_InterruptHandler for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_MRS_I_InterruptHandler)
{
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    if (REG_READ16(CTU2_CR_ADDR16(CTU0_BASEADDR))&CTU2_CR_FGRE_U16)
    {
        /* activate GRE in order to refresh the double buffered registers. */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        REG_WRITE16(CTU2_CR_ADDR16(CTU0_BASEADDR), CTU2_CR_GRE_U16);
        /* ack MRS_RE interrupt */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        REG_WRITE16(CTU2_EFR_ADDR16(CTU0_BASEADDR), CTU2_EFR_MRS_RE_U16);
    }
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_MRS_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the MRS_I_InterruptHandler for CTU_1.
* @details        The function implements the MRS_I_InterruptHandler for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_MRS_I_InterruptHandler)
{
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    if (REG_READ16(CTU2_CR_ADDR16(CTU1_BASEADDR))&CTU2_CR_FGRE_U16)
    {
        /* activate GRE in order to refresh the double buffered registers. */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        REG_WRITE16(CTU2_CR_ADDR16(CTU1_BASEADDR), CTU2_CR_GRE_U16);

        /* ack MRS_RE interrupt */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        REG_WRITE16(CTU2_EFR_ADDR16(CTU1_BASEADDR), CTU2_EFR_MRS_RE_U16);
    }
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_MRS_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T0_I_InterruptHandler for CTU_0.
* @details        The function implements the T0_I_InterruptHandler (trigger 0) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T0_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T0_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T0_I_InterruptHandler for CTU_1.
* @details        The function implements the T0_I_InterruptHandler (trigger 0) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T0_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T0_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T1_I_InterruptHandler for CTU_0.
* @details        The function implements the T1_I_InterruptHandler (trigger 1) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T1_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T1_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T1_I_InterruptHandler for CTU_1.
* @details        The function implements the T1_I_InterruptHandler (trigger 1) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T1_I_InterruptHandler)
{
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T1_I_U16); /* ack the interrupt */

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T2_I_InterruptHandler for CTU_0.
* @details        The function implements the T2_I_InterruptHandler (trigger 2) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T2_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T2_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}
/**
* @brief          This function implements the T2_I_InterruptHandler for CTU_1.
* @details        The function implements the T2_I_InterruptHandler (trigger 2) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T2_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T2_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T3_I_InterruptHandler for CTU_0.
* @details        The function implements the T3_I_InterruptHandler (trigger 3) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T3_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T3_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T3_I_InterruptHandler for CTU_1.
* @details        The function implements the T3_I_InterruptHandler (trigger 3) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T3_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T3_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T4_I_InterruptHandler for CTU_0.
* @details        The function implements the T4_I_InterruptHandler (trigger 4) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T4_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T4_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T4_I_InterruptHandler for CTU_1.
* @details        The function implements the T4_I_InterruptHandler (trigger 4) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T4_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T4_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T5_I_InterruptHandler for CTU_0.
* @details        The function implements the T5_I_InterruptHandler (trigger 5) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T5_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T5_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T5_I_InterruptHandler for CTU_1.
* @details        The function implements the T5_I_InterruptHandler (trigger 5) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T5_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T5_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T6_I_InterruptHandler for CTU_0.
* @details        The function implements the T6_I_InterruptHandler (trigger 6) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T6_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T6_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T6_I_InterruptHandler for CTU_1.
* @details        The function implements the T6_I_InterruptHandler (trigger 6) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T6_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T6_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the T7_I_InterruptHandler for CTU_0.
* @details        The function implements the T7_I_InterruptHandler (trigger 7) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_T7_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_T7_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the T7_I_InterruptHandler for CTU_1.
* @details        The function implements the T7_I_InterruptHandler (trigger 7) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_T7_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_T7_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the FIFO0_I_InterruptHandler for CTU_0.
* @details        The function implements the FIFO0_I_InterruptHandler
*                (fifo 0 - threshold occurred) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_FIFO0_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32((CTU0_BASEADDR)))&ADC_CTU0_FIFO0_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_0_FIFO0_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU0_BASEADDR), CTU2_FST_OR0_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the FIFO0_I_InterruptHandler for CTU_1.
* @details        The function implements the FIFO0_I_InterruptHandler
*                (fifo 0 - threshold occurred) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_FIFO0_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32((CTU1_BASEADDR)))&ADC_CTU1_FIFO0_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_1_FIFO0_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU1_BASEADDR), CTU2_FST_OR0_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the FIFO1_I_InterruptHandler for CTU_0.
* @details        The function implements the FIFO1_I_InterruptHandler
*                 (fifo 1 - threshold occurred) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_FIFO1_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU0_BASEADDR))&ADC_CTU0_FIFO1_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_0_FIFO1_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU0_BASEADDR), CTU2_FST_OR1_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the FIFO1_I_InterruptHandler for CTU_1.
* @details        The function implements the FIFO1_I_InterruptHandler
*                 (fifo 1 - threshold occurred) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_FIFO1_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU1_BASEADDR))&ADC_CTU1_FIFO1_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_1_FIFO1_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU1_BASEADDR), CTU2_FST_OR1_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the FIFO2_I_InterruptHandler for CTU_0.
* @details        The function implements the FIFO2_I_InterruptHandler
*                 (fifo 2 - threshold occurred) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_FIFO2_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU0_BASEADDR))&ADC_CTU0_FIFO2_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_0_FIFO2_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU0_BASEADDR), CTU2_FST_OR2_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the FIFO2_I_InterruptHandler for CTU_1.
* @details        The function implements the FIFO2_I_InterruptHandler
*                 (fifo 2 - threshold occurred) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_FIFO2_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU1_BASEADDR))&ADC_CTU1_FIFO2_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_1_FIFO2_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU1_BASEADDR), CTU2_FST_OR2_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the FIFO3_I_InterruptHandler for CTU_0.
* @details        The function implements the FIFO3_I_InterruptHandler
*                 (fifo 3 - threshold occurred) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_FIFO3_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU0_BASEADDR))&ADC_CTU0_FIFO3_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_0_FIFO3_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU0_BASEADDR), CTU2_FST_OR3_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the FIFO3_I_InterruptHandler for CTU_1.
* @details        The function implements the FIFO3_I_InterruptHandler
*                 (fifo 3 - threshold occurred) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_FIFO3_I_InterruptHandler)
{
    if(NULL_PTR != Adc_Ctu2_pCfgPtr)
    {
        /* Handle the FIFO FULL condition */
        /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
        if (REG_READ32(CTU2_FST_ADDR32(CTU1_BASEADDR))&ADC_CTU1_FIFO3_FLAG_U32)
        {
            /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
            Mcl_DmaEnableHwRequest((Mcl_ChannelType)CTU2_1_FIFO3_DMA_CHANNEL_U8);
        }
    }
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE32(CTU2_FST_ADDR32(CTU1_BASEADDR), CTU2_FST_OR3_U32);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the ADC_I_InterruptHandler for CTU_0.
* @details        The function implements the ADC_I_InterruptHandler for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_ADC_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU0_BASEADDR), CTU2_IFR_ADC_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the ADC_I_InterruptHandler for CTU_1.
* @details        The function implements the ADC_I_InterruptHandler for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_ADC_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_IFR_ADDR16(CTU1_BASEADDR), CTU2_IFR_ADC_I_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/** @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from integer type to a other type or a wider integer type */
/**
* @brief          This function implements the ERR_I_InterruptHandler for CTU_0.
* @details        The function implements the ERR_I_InterruptHandler (error interrupt) for CTU_0.
*
* @isr
*
*/
ISR(CTU_0_ERR_I_InterruptHandler)
{
    /* ack the interrupt */
    /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
    REG_WRITE16(CTU2_EFR_ADDR16(CTU0_BASEADDR), \
                CTU2_EFR_ET_OE_U16|CTU2_EFR_ERR_CMP_U16|CTU2_EFR_T3_OE_U16|CTU2_EFR_T2_OE_U16| \
                CTU2_EFR_T1_OE_U16|CTU2_EFR_ADC_OE_U16|CTU2_EFR_TGS_OSM_U16|CTU2_EFR_MRS_O_U16| \
                CTU2_EFR_ICE_U16|CTU2_EFR_SM_TO_U16|CTU2_EFR_MRS_RE_U16);

    /**
    * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
    * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
    */
    EXIT_INTERRUPT();
}

/**
* @brief          This function implements the ERR_I_InterruptHandler for CTU_1.
* @details        The function implements the ERR_I_InterruptHandler (error interrupt) for CTU_1.
*
* @isr
*
*/
ISR(CTU_1_ERR_I_InterruptHandler)
{
  /* ack the interrupt */
  /** @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer */
  REG_WRITE16(CTU2_EFR_ADDR16(CTU1_BASEADDR), \
              CTU2_EFR_ET_OE_U16|CTU2_EFR_ERR_CMP_U16|CTU2_EFR_T3_OE_U16|CTU2_EFR_T2_OE_U16| \
              CTU2_EFR_T1_OE_U16|CTU2_EFR_ADC_OE_U16|CTU2_EFR_TGS_OSM_U16|CTU2_EFR_MRS_O_U16| \
              CTU2_EFR_ICE_U16|CTU2_EFR_SM_TO_U16|CTU2_EFR_MRS_RE_U16);

  /**
  * @violates @ref Adc_Ctu2_Irq_c_REF_4 cast from int to a different type or a wider integer type
  * @violates @ref Adc_Ctu2_Irq_c_REF_5 cast from unsigned int to pointer.
  */
  EXIT_INTERRUPT();
}


/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 0, FIFO1.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo1Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(0U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[0]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 1, FIFO1.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo1Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(1U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[0]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 0, FIFO2.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo2Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(0U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[1]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 1, FIFO2.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo2Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(1U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[1]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 0, FIFO3.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo3Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(0U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[2]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 1, FIFO3.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo3Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(1U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[2]();
}


/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 0, FIFO4.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit0Fifo4Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(0U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[3]();
}

/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer 
*                 is completed for the CTU unit 1, FIFO4.
*
* @return         void
* @violates @ref Adc_Ctu2_Irq_c_REF_7 internal linkage
*/
FUNC(void, ADC_CODE) Adc_Ctu2_Unit1Fifo4Complete(void)
{
    VAR(uint8, AUTOMATIC) u8Index = Adc_Ctu2_GetIndexCtu2Active(1U);
    /** @violates @ref Adc_Ctu2_Irq_c_REF_8 Array indexing */
    Adc_Ctu2_pCfgPtr->pUnitConfig[u8Index].FifoCfg.pfNotifications[3]();
}

#define ADC_STOP_SEC_CODE
/**
* @violates @ref Adc_Ctu2_Irq_c_REF_1 only preprocessor statements and comments before "#include"
* @violates @ref Adc_Ctu2_Irq_c_REF_2 Repeated include file MemMap.h
*/
#include "MemMap.h"

#endif /* (ADC_ENABLE_CTU_CONTROL_MODE_API == STD_ON) */

#ifdef __cplusplus
}
#endif

/** @} */
