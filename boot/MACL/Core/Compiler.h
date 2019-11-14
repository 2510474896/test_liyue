/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: Compiler.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:25CST $

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
*   @file           Compiler.h
*   @implements     Compiler.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - SWS Compiler abstraction
*   @details The file Compiler.h provides macros for the encapsulation of definitions and
*            declarations.
*            This file contains sample code only. It is not part of the production code deliverables
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
* @section Compiler_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, A function should be used in preference to a function-like
* macro. This is the compiler abstraction specified in AutoSar Specification of Compiler Abstraction.
*
* @section Compiler_h_REF_2
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and
* functions shall not be reused. Symbol required to be defined when one compiler is used.
* Requested by AutoSAR (Req. COMPILER010).
*
* @section Compiler_h_REF_3
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to a braced initialiser, a constant, a
* parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct.
* This is used to abstract compiler specific encapsulation of definitions and declarations
*
* @section Compiler_h_REF_4
* Violates MISRA 2004 Required Rule 19.10, In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses unless it is used as the operand of # or ##.
* This is used to abstract compiler specific encapsulation of definitions and declarations
*
* @section Compiler_h_REF_5
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers.
*/

/**
* @file         Compiler.h
* @requirements COMPILER047
*/
#ifndef COMPILER_H
#define COMPILER_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Compiler_Cfg.h"
#include "Soc_Ips.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief  Parameters that shall be published within the compiler abstraction header file and also in
          the module's description file.
@{
*/
#define COMPILER_VENDOR_ID                      43
/*
 * @violates @ref Compiler_h_REF_5 This is required as per autosar Requirement, 
 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION       4
/*
 * @violates @ref Compiler_h_REF_5 This is required as per autosar Requirement, 
 */
#define COMPILER_AR_RELEASE_MINOR_VERSION       0
/*
 * @violates @ref Compiler_h_REF_5 This is required as per autosar Requirement, 
 */
#define COMPILER_AR_RELEASE_REVISION_VERSION    3
#define COMPILER_SW_MAJOR_VERSION               1
#define COMPILER_SW_MINOR_VERSION               0
#define COMPILER_SW_PATCH_VERSION               0
/**@}*/
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#ifdef __ghs__
    /**
    * @brief Symbol required to be defined when GreenHills compiler is used.
    */
  /*
    * @violates @ref Compiler_h_REF_2 The names of standard library
    * macros, objects and functions shall not be reused.
    */
    #define _GREENHILLS_C_MPC574XP_
#endif
#ifdef __DCC__
    /**
    * @brief Symbol required to be defined when Diab compiler is used.
    */
  /*
    * @violates @ref Compiler_h_REF_2 The names of standard library
    * macros, objects and functions shall not be reused.
    */
    #define _DIABDATA_C_MPC574XP_
#endif
#ifdef __MWERKS__
    /**
    * @brief Symbol required to be defined when Codewarrior compiler is used.
    */
  /*
    * @violates @ref Compiler_h_REF_2 The names of standard library
    * macros, objects and functions shall not be reused.
    */
    #define _CODEWARRIOR_C_MPC574XP_
#endif
#ifdef __CSMC__
    /**
    * @brief Symbol required to be defined when Cosmic compiler is used.
    */
  /*
    * @violates @ref Compiler_h_REF_2 The names of standard library
    * macros, objects and functions shall not be reused.
    */
  #define _COSMIC_C_MPC574XP_
#endif
#ifdef __GNUC__
    #ifndef MCAL_PLATFORM_ARM
        /**
        * @brief Symbol required to be defined when HiTech compiler is used.
        */
        /*
        * @violates @ref Compiler_h_REF_2 The names of standard library
        * macros, objects and functions shall not be reused.
        */
        #define _HITECH_C_MPC574XP_
    #else 
        /**
        * @brief Symbol required to be defined when Linaro ARM compiler is used.
        */
        /*
        * @violates @ref Compiler_h_REF_2 The names of standard library
        * macros, objects and functions shall not be reused.
        */
        #define _LINARO_C_MPC574XP_
    #endif
#endif      
#ifdef __CC_ARM 
        /**
        * @brief Symbol required to be defined when DS5 ARM compiler is used.
        */
        /*
        * @violates @ref Compiler_h_REF_2 The names of standard library
        * macros, objects and functions shall not be reused.
        */
        #define _ARM_DS5_C_MPC574XP_     
#endif

/**
* @brief The memory class AUTOMATIC shall be provided as empty definition, used for the declaration
*        of local pointers.
*/
#define AUTOMATIC

/**
* @brief The memory class TYPEDEF shall be provided as empty definition. This memory class shall be
*        used within type definitions, where no memory qualifier can be specified. This can be
*        necessary for defining pointer types, with e.g. P2VAR, where the macros require two
*        parameters. First parameter can be specified in the type definition (distance to the memory
*        location referenced by the pointer), but the second one (memory allocation of the pointer
*        itself) cannot be defined at this time. Hence memory class TYPEDEF shall be applied.
*/
#define TYPEDEF

/**
* @brief The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero
*        definition.
*/
#define NULL_PTR ((void *)0)

/**************************************** Green Hills *********************************************/
#ifdef _GREENHILLS_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __interrupt
#endif /* #ifdef _GREENHILLS_C_MPC574XP_ */

/**************************************** Wind River Diab *****************************************/
#ifdef _DIABDATA_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE              __inline__

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline__

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __interrupt__
#endif /* #ifdef _DIABDATA_C_MPC574XP_ */

/*************************************** CodeWarrior **********************************************/
#ifdef _CODEWARRIOR_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE              inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC      __declspec(interrupt nowarn)
#endif /* #ifdef _CODEWARRIOR_C_MPC574XP_ */

/*************************************** Cosmic ***************************************************/
#ifdef _COSMIC_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INLINE @inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static @inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC @interrupt
#endif /* #ifdef _COSMIC_C_MPC574XP_ */
/*************************************** HighTec **********************************************/
#ifdef _HITECH_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

/**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
*/
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INTERRUPT_FUNC      __attribute__((interrupt));
#endif /* #ifdef _HITECH_C_MPC574XP_ */

/**************************************** Linaro *********************************************/
#ifdef _LINARO_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE                  inline __attribute__((always_inline))

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static inline __attribute__((always_inline))

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
    /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC     
#endif /* #ifdef _LINARO_C_MPC574XP_ */
/**************************************** DS5 *************************************************/
#ifdef _ARM_DS5_C_MPC574XP_
    /* Prototypes for intrinsic functions */
    /**
    * @brief The compiler abstraction shall provide the INLINE define for abstraction of the keyword
    *        inline.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */    
    #define INLINE              __inline

    /**
    * @brief The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the
    *       keyword inline in functions with "static" scope
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define LOCAL_INLINE            static __inline

    /**
    * @brief Compiler abstraction for specifying an interrupt handler.
    */
  /*
    * @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
    *    a constant, a parenthesised expression
    */        
    #define INTERRUPT_FUNC
#endif /* #ifdef _ARM_DS5_C_MPC574XP_ */

/**
* @brief The compiler abstraction shall define the FUNC macro for the declaration and definition of
*        functions, that ensures correct syntax of function declarations as required by a specific
*        compiler.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define FUNC(rettype, memclass) rettype

/**
* @brief The compiler abstraction shall define the P2VAR macro for the declaration and definition of
*        pointers in RAM, pointing to variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/**
* @brief The compiler abstraction shall define the P2CONST macro for the declaration and definition
*        of pointers in RAM pointing to constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/**
* @brief The compiler abstraction shall define the CONSTP2VAR macro for the declaration and
*        definition of constant pointers accessing variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/**
* @brief The compiler abstraction shall define the CONSTP2CONST macro for the declaration and
*        definition of constant pointers accessing constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/**
* @brief The compiler abstraction shall define the P2FUNC macro for the type definition of pointers
*        to functions.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

/**
* @brief The compiler abstraction shall define the CONST macro for the declaration and definition of
*        constants.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define CONST(consttype, memclass) const consttype

/**
* @brief The compiler abstraction shall define the VAR macro for the declaration and definition of
*        variables.
*/
/*
* @violates @ref Compiler_h_REF_1 A function should be used in
* preference to a function-like macro.
*/
/*
* @violates @ref Compiler_h_REF_3 C macros shall only expand to a braced initialiser, 
*    a constant, a parenthesised expression
*/
/*
* @violates @ref Compiler_h_REF_4 In the definition of a function-like macro each instance of a
*  parameter shall be enclosed in parentheses
*/
#define VAR(vartype, memclass) vartype

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMPILER_H */

/** @} */
