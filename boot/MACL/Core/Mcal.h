/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Mcal.h $
        $Revision: 1.1 $
        $Date: 2019/06/26 13:29:29CST $

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
*   @file           Mcal.h
*   @implements     Mcal.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - SWS Compiler abstraction specific for MCAL.
*   @details The file Mcal.h provides MCAL specific macros used for compiler abstraction.
*
*
*   @addtogroup BASE_COMPONENT
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MPC574XP
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
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcal_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, A function should be used in preference to a function-like
* macro. Compiler abstraction need to implement function-like macros to hide compiler specifics from
* the implementation.
*
* @section Mcal_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Mcal_h_REF_3
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers
* 
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused. The driver needs to use defines starting with letter E.
*
* @section Mcal_h_REF_5
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to a braced initialiser, a constant, a
* parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct
* This is used to abstract compiler specific encapsulation of definitions and declarations
*
* @section Mcal_h_REF_6
* Violates MISRA 2004 Required Rule 19.10, In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses unless it is used as * the operand of # or ##.
* This is used to abstract compiler specific encapsulation of definitions and declarations
* 
*/

#ifndef MCAL_H
#define MCAL_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*
* @file        Mcal.h
* @brief Include compiler abstraction
*/
/*
* @violates @ref Mcal_h_REF_2 MISRA 2004 Precautions shall be taken in order to
* prevent the contents of a header being included twice.
*/
#include "Compiler.h"
/*
* @file        Mcal.h
* @brief Include standard types
*/
/*
* @violates @ref Mcal_h_REF_2 MISRA 2004 Precautions shall be taken in order to
* prevent the contents of a header being included twice.
*/
#include "Std_Types.h"
/*
* @file        Mcal.h
* @brief Include Safety error report and react mechanism
*/
#include "Cer.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCAL_VENDOR_ID                    43
#define MCAL_MODULE_ID                    0
/*
 * @violates @ref Mcal_h_REF_3 This is required as per autosar Requirement, 
 */
#define MCAL_AR_RELEASE_MAJOR_VERSION     4
/*
 * @violates @ref Mcal_h_REF_3 This is required as per autosar Requirement, 
 */
#define MCAL_AR_RELEASE_MINOR_VERSION     0
/*
 * @violates @ref Mcal_h_REF_3 This is required as per autosar Requirement, 
 */
#define MCAL_AR_RELEASE_REVISION_VERSION  3
#define MCAL_SW_MAJOR_VERSION             1
#define MCAL_SW_MINOR_VERSION             0
#define MCAL_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Compiler.h header file are of the same Autosar version */
    #if ((MCAL_AR_RELEASE_MAJOR_VERSION != COMPILER_AR_RELEASE_MAJOR_VERSION) || \
         (MCAL_AR_RELEASE_MINOR_VERSION != COMPILER_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcal.h and Compiler.h are different"
    #endif
#endif


#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Std_Types.h header file are of the same Autosar version */
    #if ((MCAL_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         (MCAL_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Mcal.h and Std_Types.h are different"
    #endif
#endif

/* Check if source file and Cer.h header file have same versions */
#if (MCAL_VENDOR_ID != CER_VENDOR_ID)
#error "Mcal.h and Cer.h have different vendor IDs"
#endif
#if ((MCAL_AR_RELEASE_MAJOR_VERSION != CER_AR_RELEASE_MAJOR_VERSION) || \
     (MCAL_AR_RELEASE_MINOR_VERSION != CER_AR_RELEASE_MINOR_VERSION) || \
     (MCAL_AR_RELEASE_REVISION_VERSION != CER_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Mcal.h and Cer.h are different"
#endif
#if ((MCAL_SW_MAJOR_VERSION != CER_SW_MAJOR_VERSION) || \
     (MCAL_SW_MINOR_VERSION != CER_SW_MINOR_VERSION) || \
     (MCAL_SW_PATCH_VERSION != CER_SW_PATCH_VERSION))
#error "Software Version Numbers of Mcal.h and Cer.h are different"
#endif


/*==================================================================================================
*                                         CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define ASM_KEYWORD  __asm
#ifdef MCAL_PLATFORM_ARM
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wfi")
#else    
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wait")
#endif    
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
    * parameter shall be enclosed in parentheses
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
    
   /**
    * @brief Compiler abstraction for the packed qualifier
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #ifdef MCAL_PLATFORM_ARM
        #define PACKED __packed 
    #else    
        #define PACKED 
    #endif
#endif /* #ifdef _GREENHILLS_C_MPC574XP_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    */
    #define ASM_KEYWORD  asm volatile

    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  .word 0x7C00007C")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
    
    /**
     * @brief Compiler abstraction for the packed qualifier
     */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #ifdef MCAL_PLATFORM_ARM
        #define PACKED __packed__ 
    #else    
        #define PACKED 
    #endif    

#endif /* #ifdef _DIABDATA_C_MPC574XP_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    */
    #define ASM_KEYWORD  asm

    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD (" opword 0x7C00007C")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define VAR_ALIGN(v, size) v __attribute__(( aligned(size) ));
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
    
    /**
    * @brief Compiler abstraction for the packed qualifier
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #ifdef MCAL_PLATFORM_ARM
        #define PACKED __packed 
    #else    
        #define PACKED 
    #endif    

#endif /* #ifdef _CODEWARRIOR_C_MPC574XP_ */

/*************************************** Cosmic ***************************************************/
#ifdef _COSMIC_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    */
    #define ASM_KEYWORD  _asm
    /**
    * @brief Compiler abstraction for the asm keyword.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ASM_PUBLIC_LABEL(label)  _asm("\txdef\t" #label "\n" #label ":")

    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD (" dc.l 0x7C00007C")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    #define ALIGNED_VARS_START(sec_name, align) \#pragma section [sec_name ## align]
    /**
    * @brief Compiler abstraction for the data alignment
    */
    #define VAR_ALIGN(v, size) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    #define ALIGNED_VARS_STOP() \#pragma section []
#endif /* #ifdef _COSMIC_C_MPC574XP_ */

/*************************************** HighTec **********************************************/
#ifdef _HITECH_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    */
    #define ASM_KEYWORD  __asm

    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wait")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
#endif /* #ifdef _HITECH_C_MPC574XP_ */
/**************************************** Linaro *********************************************/
#ifdef _LINARO_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define ASM_KEYWORD  __asm
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wfi")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
    * parameter shall be enclosed in parentheses
    */
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
    
    /**
     * @brief Compiler abstraction for the packed qualifier
     */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #ifdef MCAL_PLATFORM_ARM
        #define PACKED __packed__
    #else    
        #define PACKED 
    #endif    
#endif /* #ifdef _LINARO_C_MPC574XP_ */

/**************************************** DS5 *********************************************/
#ifdef _ARM_DS5_C_MPC574XP_
    /**
    * @brief Compiler abstraction for the asm keyword.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define ASM_KEYWORD  __asm
    /**
    * @brief Compiler abstraction for the intrinsic wait instruction.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define EXECUTE_WAIT()      ASM_KEYWORD("  wfi")
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_START(sec_name, align)
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
    * parameter shall be enclosed in parentheses
    */
    #define VAR_ALIGN(v, size) __align(size) v;
    /**
    * @brief Compiler abstraction for the data alignment
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define ALIGNED_VARS_STOP()
    /**
     * @brief Compiler abstraction for the packed qualifier
     */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #ifdef MCAL_PLATFORM_ARM
        #define PACKED __packed 
    #else    
        #define PACKED 
    #endif
#endif /* #ifdef _GREENHILLS_C_MPC574XP_ */

/* check that the compiler used is supported (otherwise some defines might not exist) */
#ifndef _GREENHILLS_C_MPC574XP_
    #ifndef _DIABDATA_C_MPC574XP_
        #ifndef _CODEWARRIOR_C_MPC574XP_
            #ifndef _COSMIC_C_MPC574XP_
                #ifndef _HITECH_C_MPC574XP_
                    #ifndef _LINARO_C_MPC574XP_
                        #ifndef _ARM_DS5_C_MPC574XP_
                            #error "Unsupported compiler. Compiler abstraction needs to be updated to use this compiler."
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #endif
#endif

#if defined(AUTOSAR_OS_NOT_USED)
    #if defined (USE_SW_VECTOR_MODE)
        /**
        * @brief Compiler abstraction for creating an interrupt handler if no OS is present.
        */
        /*
        * @violates @ref Mcal_h_REF_1 A function should be used in
        * preference to a function-like macro.
        * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
        * a constant, a parenthesised expression
        * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
        * parameter shall be enclosed in parentheses
        */
        #define ISR(IsrName)       void IsrName(void)

        /**
        * @brief Compiler abstraction for returning from an ISR if no OS is present.
        */
        /*
        * @violates @ref Mcal_h_REF_1 A function should be used in
        * preference to a function-like macro.
        */
        #define EXIT_INTERRUPT()
    #else
        /**
        * @brief Compiler abstraction for creating an interrupt handler if no OS is present.
        */
        /*
        * @violates @ref Mcal_h_REF_1 A function should be used in
        * preference to a function-like macro.
        * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
        * a constant, a parenthesised expression
        * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
        * parameter shall be enclosed in parentheses
        */
        #define ISR(IsrName)       INTERRUPT_FUNC void IsrName(void)

        /**
        * @brief Compiler abstraction for returning from an ISR if no OS is present.
        */
        /* @errata  ERR_IPV_INTC_0001 */
        #ifdef ERR_IPV_INTC_0001
          #if (ERR_IPV_INTC_0001 == STD_ON)
            /*
            * @violates @ref Mcal_h_REF_1 A function should be used in
            * preference to a function-like macro.
            * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
            * a constant, a parenthesised expression
            * @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
            * parameter shall be enclosed in parentheses
            */
            #define EXIT_INTERRUPT() \
                do { \
                    SuspendAllInterrupts(); \
                    ASM_KEYWORD(" e_lis   r4, 0xFC040030@ha "); \
                    ASM_KEYWORD(" e_or2i  r4, 0xFC040030@l "); \
                    ASM_KEYWORD("mfspr    r5, PIR"); \
                    ASM_KEYWORD("e_mulli  r5,r5, 4"); \
                    ASM_KEYWORD(" or.   r4, r4, r5"); \
                    ASM_KEYWORD(" e_li r5, 0" ); \
                    ASM_KEYWORD(" e_stw   r5, 0(r4) "); \
                    ASM_KEYWORD(" e_stw   r5, 0(r4) "); \
                } while(0) 
          #else
            /*
            * @violates @ref Mcal_h_REF_1 A function should be used in
            * preference to a function-like macro.
            * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
            * a constant, a parenthesised expression
            */
                #define EXIT_INTERRUPT() \
                  do { \
                    SuspendAllInterrupts(); \
                    ASM_KEYWORD(" e_lis   r4, 0xFC040030@ha "); \
                    ASM_KEYWORD(" e_or2i  r4, 0xFC040030@l "); \
                    ASM_KEYWORD("mfspr    r5, PIR"); \
                    ASM_KEYWORD("e_mulli  r5,r5, 4"); \
                    ASM_KEYWORD(" or.   r4, r4, r5"); \
                    ASM_KEYWORD(" e_li r5, 0" ); \
                    ASM_KEYWORD(" e_stw   r5, 0(r4) "); \
                  } while(0) 
                
          #endif
        #else
            #ifdef MCAL_PLATFORM_ARM
                /*
                * @violates @ref Mcal_h_REF_1 A function should be used in
                * preference to a function-like macro.
                * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
                * a constant, a parenthesised expression
                */
                #define EXIT_INTERRUPT()  
            #else
                #ifdef ERR_IPV_INTC_0002
                  #if (ERR_IPV_INTC_0002 == STD_ON)
                    /*
                    * @violates @ref Mcal_h_REF_1 A function should be used in
                    * preference to a function-like macro.
                    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
                    * a constant, a parenthesised expression
                    */
                  
                    #define EXIT_INTERRUPT() \
                        do { \
                            SuspendAllInterrupts(); \
                            ASM_KEYWORD(" e_lis   r4, 0xFC040030@ha "); \
                            ASM_KEYWORD(" e_or2i  r4, 0xFC040030@l "); \
                            ASM_KEYWORD("mfspr    r5, PIR"); \
                            ASM_KEYWORD("e_mulli  r5,r5, 4"); \
                            ASM_KEYWORD(" or.   r4, r4, r5"); \
                            ASM_KEYWORD(" e_li r6, 0" ); \
                            ASM_KEYWORD(" e_stw   r6, 0(r4) "); \
                            ASM_KEYWORD(" e_lis   r4, 0xFC040010@ha "); \
                            ASM_KEYWORD(" e_or2i  r4, 0xFC040010@l "); \
                            ASM_KEYWORD(" or.   r4, r4, r5"); \
                            ASM_KEYWORD(" e_stw   r6, 0(r4) "); \
                        } while(0)                     
                    
                  #else
                    /*
                    * @violates @ref Mcal_h_REF_1 A function should be used in
                    * preference to a function-like macro.
                    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
                    * a constant, a parenthesised expression
                    */
                    #define EXIT_INTERRUPT() \
                        do { \
                            SuspendAllInterrupts(); \
                            ASM_KEYWORD(" e_lis   r4, 0xFC040030@ha "); \
                            ASM_KEYWORD(" e_or2i  r4, 0xFC040030@l "); \
                            ASM_KEYWORD("mfspr    r5, PIR"); \
                            ASM_KEYWORD("e_mulli  r5,r5, 4"); \
                            ASM_KEYWORD(" or.   r4, r4, r5"); \
                            ASM_KEYWORD(" e_li r5, 0" ); \
                            ASM_KEYWORD(" e_stw   r5, 0(r4) "); \
                        } while(0) 
                  #endif
                #else
                  /*
                  * @violates @ref Mcal_h_REF_1 A function should be used in
                  * preference to a function-like macro.
                  * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
                  * a constant, a parenthesised expression
                  */
                    #define EXIT_INTERRUPT() \
                        do { \
                            SuspendAllInterrupts(); \
                            ASM_KEYWORD(" e_lis   r4, 0xFC040030@ha "); \
                            ASM_KEYWORD(" e_or2i  r4, 0xFC040030@l "); \
                            ASM_KEYWORD("mfspr    r5, PIR"); \
                            ASM_KEYWORD("e_mulli  r5,r5, 4"); \
                            ASM_KEYWORD(" or.   r4, r4, r5"); \
                            ASM_KEYWORD(" e_li r5, 0 "); \
                            ASM_KEYWORD(" e_stw   r5, 0(r4) "); \
                        } while(0) 
                #endif
            #endif
        #endif    
    #endif /*USE_SW_VECTOR_MODE*/
#ifdef MCAL_PLATFORM_ARM
    /**
    * @brief Compiler abstraction for disabling all interrupts if no OS is present.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define SuspendAllInterrupts() ASM_KEYWORD(" cpsid i")

    /**
    * @brief Compiler abstraction for re-enabling all interrupts if no OS is present.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define ResumeAllInterrupts() ASM_KEYWORD(" cpsie i")
#else
    /**
    * @brief Compiler abstraction for disabling all interrupts if no OS is present.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define SuspendAllInterrupts() ASM_KEYWORD(" wrteei 0")

    /**
    * @brief Compiler abstraction for re-enabling all interrupts if no OS is present.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    * @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
    * a constant, a parenthesised expression
    */
    #define ResumeAllInterrupts() ASM_KEYWORD(" wrteei 1")
#endif    
#else
    #include "Os.h"
    /**
    * @brief Compiler abstraction for returning from an ISR if OS is present must be empty.
    */
    /*
    * @violates @ref Mcal_h_REF_1 A function should be used in
    * preference to a function-like macro.
    */
    #define EXIT_INTERRUPT()
#endif

/**
* @brief The compiler abstraction for pointer to pointer to variable.
*/
/*
* @violates @ref Mcal_h_REF_1 A function should be used in
* preference to a function-like macro.
* @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
* a constant, a parenthesised expression
* @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses
*/
#define P2P2VAR(ptrtype, memclass, ptrclass) ptrtype **

/**
* @brief The compiler abstraction for pointer to pointer to constant.
*/
/*
* @violates @ref Mcal_h_REF_1 A function should be used in
* preference to a function-like macro.
* @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
* a constant, a parenthesised expression
* @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses
*/
#define P2P2CONST(ptrtype, memclass, ptrclass) const ptrtype **

/**
* @brief The compiler abstraction for const pointer to function.
*/
/*
* @violates @ref Mcal_h_REF_1 A function should be used in
* preference to a function-like macro.
* @violates @ref Mcal_h_REF_5 C macros shall only expand to a braced initialiser, 
* a constant, a parenthesised expression
* @violates @ref Mcal_h_REF_6 In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses
*/
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

/**
* @brief The compiler abstraction shall provide the STATIC define for abstraction of compiler
*        keyword static. Keep here for backward compatibility. It has been removed from ASR4.0
*/
#define STATIC static

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief Typedef for DEM error management implemented by MCAL drivers
*/
typedef struct
{
    uint32 state;   /**< enabling/disabling the DEM error: Active=STD_ON/ Inactive=STD_OFF */
    uint32 id ;     /**< ID of DEM error (0 if STD_OFF)*/
}Mcal_DemErrorType; 
/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCAL_H */

/** @} */
