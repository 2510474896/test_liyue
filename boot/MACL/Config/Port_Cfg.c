/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Port_Cfg.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:19CST $

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
* @file    Port_Cfg.c
*
* @version 1.0.0
* @brief   AUTOSAR Port - PORT driver configuration.
* @details This file contains the PORT driver precompile configuration.
*
* @addtogroup  Port
* @{
*/
/*=================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : SIUL2
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
=================================================================================================*/
/*=================================================================================================
=================================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_CFG_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section PORT_CFG_REF_2
* Violates MISRA 2004 Required Rule 10.1, Implicit conversion changes signedness.
* Many type conversions are implemented in MACROS. The code was tested successfully with 3 
* different compilers.
*
* @section PORT_CFG_REF_3
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section PORT_CFG_REF_4
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that
* 31 character signifiance and case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section PORT_CFG_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or 
* functions at file scope shall have internal linkage unless external linkage is required.
* State variables may be used by IP layer.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Port.h"

#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief        Parameters that shall be published within the Port driver header file and also in the
*               module's description file
* @details      The integration of incompatible files shall be avoided.
*
*/
#define PORT_VENDOR_ID_CFG_C                       43
/**
* @violates @ref PORT_CFG_REF_4 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_AR_RELEASE_MAJOR_VERSION_CFG_C        4
/**
* @violates @ref PORT_CFG_REF_4 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_AR_RELEASE_MINOR_VERSION_CFG_C        0
/**
* @violates @ref PORT_CFG_REF_4 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_AR_RELEASE_REVISION_VERSION_CFG_C     3
#define PORT_SW_MAJOR_VERSION_CFG_C                1
#define PORT_SW_MINOR_VERSION_CFG_C                0
#define PORT_SW_PATCH_VERSION_CFG_C                0

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/
/* Check if Port_Cfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_CFG_C != PORT_VENDOR_ID)
    #error "Port_Cfg.c and Port.h have different vendor ids"
#endif

/* Check if Port_Cfg.c and Port.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_C != PORT_AR_RELEASE_MAJOR_VERSION)     || \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_C != PORT_AR_RELEASE_MINOR_VERSION)     || \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_C != PORT_AR_RELEASE_REVISION_VERSION)  \
    )
   #error "AutoSar Version Numbers of Port_Cfg.c and Port.h are different"
#endif

/* Check if Port_Cfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_CFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_CFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_Cfg.c and Port.h are different"
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
/*
* @violates @ref PORT_CFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_CFG_REF_3 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"



/**
* @violates @ref PORT_CFG_REF_2 Violates MISRA 2004 Required Rule 10.1, Implicit
* conversion changes signedness.
*/
#if (PORT_MAX_UNUSED_PADS_U16 != 0)
/**
* @brief NoDefaultPadsArray is an array containing Unimplemented pads and User pads
* @violates @ref PORT_CFG_REF_5 Violates MISRA 2004 Required Rule 8.10
*/
CONST(uint16, PORT_CONST) Port_au16NoUnUsedPadsArrayDefault[PORT_MAX_UNUSED_PADS_U16]=
{

};
#endif

/**
* @brief Default Configuration for Pins not initialized
* @violates @ref PORT_CFG_REF_5 Violates MISRA 2004 Required Rule 8.10
*/
CONST(Port_Siul2_UnUsedPinConfigType, PORT_CONST) Port_UnUsedPin =
{
   /**
   * @note: Configuration of Default pin
   */
      (uint32)0x00080000, (uint8)0
   };


/**
* @brief Pin default configuration data
* @violates @ref PORT_CFG_REF_5 Violates MISRA 2004 Required Rule 8.10
*/
CONST(Port_Siul2_PinConfigType, PORT_CONST) Port_aPinConfigDefault[PORT_MAX_CONFIGURED_PADS_U16]=
{
    {(Port_InternalPinIdType)0, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)1, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)2, (uint32)0x000f0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)3, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)4, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)5, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)6, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)7, (uint32)0x10000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)8, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)9, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)10, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)TRUE},
    {(Port_InternalPinIdType)11, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)TRUE},
    {(Port_InternalPinIdType)12, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)TRUE},
    {(Port_InternalPinIdType)13, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)14, (uint32)0x00000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)15, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)16, (uint32)0x00000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)17, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)18, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)19, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)20, (uint32)0x10000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)21, (uint32)0x000f0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)22, (uint32)0x12000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)23, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)24, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)25, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)26, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)27, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)28, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)29, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)30, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)31, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)32, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)33, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)34, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)36, (uint32)0x10000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)37, (uint32)0x10000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)38, (uint32)0x10000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)39, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)42, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)43, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)44, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)45, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)46, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)47, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)48, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)49, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)50, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)51, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)52, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)53, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)54, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)55, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)56, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)57, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)58, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)59, (uint32)0x00000001, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)60, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)62, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)64, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)66, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)68, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)69, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)70, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)71, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)73, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)74, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)75, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)76, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)77, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)78, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)79, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)80, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)83, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)84, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)85, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)86, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)87, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)88, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)89, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)90, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)91, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)92, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)93, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)94, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)95, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)98, (uint32)0x000c0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)99, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)100, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)101, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)102, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)103, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)104, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)105, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)106, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)107, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)116, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)117, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)118, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)119, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)120, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)121, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)122, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)123, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)124, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)125, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)126, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)127, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)128, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)129, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)130, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)131, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)132, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)133, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)134, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)135, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)136, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)137, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)138, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)139, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)140, (uint32)0x000f0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)141, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)142, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)143, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)144, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)145, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)146, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)147, (uint32)0x02000000, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)148, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)149, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)150, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)151, (uint32)0x00400000, (uint8)2, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)152, (uint32)0x000f0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)153, (uint32)0x000d0000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE}

};

/**
* @brief Multiplex Pad selection default configuration
* @violates @ref PORT_CFG_REF_5 Violates MISRA 2004 Required Rule 8.10
*/
CONST(Port_Siul2_PadSelConfigType, PORT_CONST) Port_aPadSelConfigDefault[PORT_NMBR_INMUX_REGS_U16]=
{
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000002,
         (uint32)0x00000001,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000001,
         (uint32)0x00000001,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000001,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0xFFFFFFFFU,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000,
         (uint32)0x00000000
};

/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the pre-compiled mode
*/
CONST(Port_ConfigType, PORT_CONST) Port_ConfigPC =
{
  PORT_MAX_CONFIGURED_PADS_U16,
  PORT_MAX_UNUSED_PADS_U16,
/**
* @violates @ref PORT_CFG_REF_2 Violates MISRA 2004 Required Rule 10.1, Implicit
* conversion changes signedness.
*/  
#if (PORT_MAX_UNUSED_PADS_U16 != 0)
  Port_au16NoUnUsedPadsArrayDefault,
#else
  NULL_PTR,
#endif
  &Port_UnUsedPin,
  Port_aPinConfigDefault,
  Port_aPadSelConfigDefault
};


#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief Port Pin description data
*/
CONST (uint16, PORT_CONST) Port_au16PinDescription[11][10] =
{  

/*  Mode PORT_GPIO_MODE: */
{
/* Pads   0 ...  15 : PORT0_GPIO | 
PORT1_GPIO | 
PORT2_GPIO | 
PORT3_GPIO | 
PORT4_GPIO | 
PORT5_GPIO | 
PORT6_GPIO | 
PORT7_GPIO | 
PORT8_GPIO | 
PORT9_GPIO | 
PORT10_GPIO | 
PORT11_GPIO | 
PORT12_GPIO | 
PORT13_GPIO | 
PORT14_GPIO | 
PORT15_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  16 ...  31 : PORT16_GPIO | 
PORT17_GPIO | 
PORT18_GPIO | 
PORT19_GPIO | 
PORT20_GPIO | 
PORT21_GPIO | 
PORT22_GPIO | 
PORT23_GPI | 
PORT24_GPI | 
PORT25_GPI | 
PORT26_GPI | 
PORT27_GPI | 
PORT28_GPI | 
PORT29_GPI | 
PORT30_GPI | 
PORT31_GPI */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  32 ...  47 : PORT32_GPI | 
PORT33_GPI | 
PORT34_GPI | 
PORT36_GPIO | 
PORT37_GPIO | 
PORT38_GPIO | 
PORT39_GPIO | 
PORT42_GPIO | 
PORT43_GPIO | 
PORT44_GPIO | 
PORT45_GPIO | 
PORT46_GPIO | 
PORT47_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  48 ...  63 : PORT48_GPIO | 
PORT49_GPIO | 
PORT50_GPIO | 
PORT51_GPIO | 
PORT52_GPIO | 
PORT53_GPIO | 
PORT54_GPIO | 
PORT55_GPIO | 
PORT56_GPIO | 
PORT57_GPIO | 
PORT58_GPIO | 
PORT59_GPIO | 
PORT60_GPIO | 
PORT62_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(14)),
/* Pads  64 ...  79 : PORT64_GPI | 
PORT66_GPI | 
PORT68_GPI | 
PORT69_GPI | 
PORT70_GPI | 
PORT71_GPI | 
PORT73_GPI | 
PORT74_GPI | 
PORT75_GPI | 
PORT76_GPI | 
PORT77_GPIO | 
PORT78_GPIO | 
PORT79_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  80 ...  95 : PORT80_GPIO | 
PORT83_GPIO | 
PORT84_GPIO | 
PORT85_GPIO | 
PORT86_GPIO | 
PORT87_GPIO | 
PORT88_GPIO | 
PORT89_GPIO | 
PORT90_GPIO | 
PORT91_GPIO | 
PORT92_GPIO | 
PORT93_GPIO | 
PORT94_GPIO | 
PORT95_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  96 ... 111 : PORT98_GPIO | 
PORT99_GPIO | 
PORT100_GPIO | 
PORT101_GPIO | 
PORT102_GPIO | 
PORT103_GPIO | 
PORT104_GPIO | 
PORT105_GPIO | 
PORT106_GPIO | 
PORT107_GPIO */
 (uint16)( SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11)),
/* Pads 112 ... 127 : PORT116_GPIO | 
PORT117_GPIO | 
PORT118_GPIO | 
PORT119_GPIO | 
PORT120_GPIO | 
PORT121_GPIO | 
PORT122_GPIO | 
PORT123_GPIO | 
PORT124_GPIO | 
PORT125_GPIO | 
PORT126_GPIO | 
PORT127_GPIO */
 (uint16)( SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads 128 ... 143 : PORT128_GPIO | 
PORT129_GPIO | 
PORT130_GPIO | 
PORT131_GPIO | 
PORT132_GPIO | 
PORT133_GPIO | 
PORT134_GPIO | 
PORT135_GPIO | 
PORT136_GPIO | 
PORT137_GPIO | 
PORT138_GPIO | 
PORT139_GPIO | 
PORT140_GPIO | 
PORT141_GPIO | 
PORT142_GPIO | 
PORT143_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9) | 
SHL_PAD_U16(10) | 
SHL_PAD_U16(11) | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads 144 ... 159 : PORT144_GPIO | 
PORT145_GPIO | 
PORT146_GPIO | 
PORT147_GPIO | 
PORT148_GPIO | 
PORT149_GPI | 
PORT150_GPI | 
PORT151_GPI | 
PORT152_GPIO | 
PORT153_GPIO */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2) | 
SHL_PAD_U16(3) | 
SHL_PAD_U16(4) | 
SHL_PAD_U16(5) | 
SHL_PAD_U16(6) | 
SHL_PAD_U16(7) | 
SHL_PAD_U16(8) | 
SHL_PAD_U16(9)) }
,
/*  Mode PORT_ALT1_FUNC_MODE: */
{
/* Pads   0 ...  15 : PORT0_eTimer0_ETC0 | 
PORT1_eTimer0_ETC1 | 
PORT2_eTimer0_ETC2 | 
PORT3_eTimer0_ETC3 | 
PORT4_eTimer1_ETC0 | 
PORT5_DSPI1_CS0 | 
PORT6_DSPI1_SCK | 
PORT7_DSPI1_SOUT | 
PORT9_DSPI2_CS1 | 
PORT10_DSPI2_CS0 | 
PORT11_DSPI2_SCK_OUT | 
PORT12_DSPI2_SOUT | 
PORT14_CAN1_TX */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(1)     | 
SHL_PAD_U16(2)     | 
SHL_PAD_U16(3)     | 
SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)  | 
SHL_PAD_U16(6)  | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(9)  | 
SHL_PAD_U16(10)  | 
SHL_PAD_U16(11)      | 
SHL_PAD_U16(12)   | 
SHL_PAD_U16(14)),
/* Pads  16 ...  31 : PORT16_CAN0_TX | 
PORT18_LIN0_TXD | 
PORT20_TDO_MUX_TDO | 
PORT21_DSPI0_CS7 | 
PORT22_MC_CGM_CLKOUT */
 (uint16)( SHL_PAD_U16(0) | 
SHL_PAD_U16(2)  | 
SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(6)      ),
/* Pads  32 ...  47 : PORT36_DSPI0_CS0 | 
PORT37_DSPI0_SCK | 
PORT38_DSPI0_SOUT | 
PORT42_DSPI2_CS2 | 
PORT43_eTimer0_ETC4 | 
PORT44_eTimer0_ETC5 | 
PORT45_eTimer1_ETC1 | 
PORT46_eTimer1_ETC2 | 
PORT47_FlexRay_FR_A_TXEN */
 (uint16)( SHL_PAD_U16(4)   | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(6)    | 
SHL_PAD_U16(10)  | 
SHL_PAD_U16(11)     | 
SHL_PAD_U16(12)     | 
SHL_PAD_U16(13)     | 
SHL_PAD_U16(14)     | 
SHL_PAD_U16(15)         ),
/* Pads  48 ...  63 : PORT48_FlexRay_FR_A_TX | 
PORT51_FlexRay_FR_B_TX | 
PORT52_FlexRay_FR_B_TXEN | 
PORT53_DSPI0_CS3 | 
PORT54_DSPI0_CS2 | 
PORT55_DSPI1_CS3 | 
PORT56_DSPI1_CS2 | 
PORT57_FlexPWM0_X0 | 
PORT58_FlexPWM0_A0 | 
PORT59_FlexPWM0_B0 | 
PORT60_FlexPWM0_X1 | 
PORT62_FlexPWM0_B1 */
 (uint16)( SHL_PAD_U16(0)         | 
SHL_PAD_U16(3)         | 
SHL_PAD_U16(4)           | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(6)   | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(8)   | 
SHL_PAD_U16(9)     | 
SHL_PAD_U16(10)    | 
SHL_PAD_U16(11)    | 
SHL_PAD_U16(12)    | 
SHL_PAD_U16(14)   ),
/* Pads  64 ...  79 : PORT77_eTimer0_ETC5 | 
PORT78_eTimer1_ETC5 | 
PORT79_DSPI0_CS1 */
 (uint16)( SHL_PAD_U16(13)     | 
SHL_PAD_U16(14)     | 
SHL_PAD_U16(15) ),
/* Pads  80 ...  95 : PORT80_FlexPWM0_A1 | 
PORT83_DSPI0_CS6 | 
PORT92_eTimer1_ETC3 | 
PORT93_eTimer1_ETC4 | 
PORT94_LIN1_TXD */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(3)   | 
SHL_PAD_U16(12)     | 
SHL_PAD_U16(13)     | 
SHL_PAD_U16(14)),
/* Pads  96 ... 111 : PORT98_FlexPWM0_X2 | 
PORT99_FlexPWM0_A2 | 
PORT100_FlexPWM0_B2 | 
PORT101_FlexPWM0_X3 | 
PORT102_FlexPWM0_A3 | 
PORT103_FlexPWM0_B3 | 
PORT104_FlexRay_DBG0 | 
PORT105_FlexRay_DBG1 | 
PORT106_FlexRay_DBG2 | 
PORT107_FlexRay_DBG3 */
 (uint16)( SHL_PAD_U16(2)     | 
SHL_PAD_U16(3)     | 
SHL_PAD_U16(4)      | 
SHL_PAD_U16(5)      | 
SHL_PAD_U16(6)      | 
SHL_PAD_U16(7)      | 
SHL_PAD_U16(8)       | 
SHL_PAD_U16(9)       | 
SHL_PAD_U16(10)      | 
SHL_PAD_U16(11)     ),
/* Pads 112 ... 127 : PORT116_FlexPWM1_X0 | 
PORT117_FlexPWM1_A0 | 
PORT118_FlexPWM1_B0 | 
PORT119_FlexPWM1_X1 | 
PORT120_FlexPWM1_A1 | 
PORT121_FlexPWM1_B1 | 
PORT122_FlexPWM1_X2 | 
PORT123_FlexPWM1_A2 | 
PORT124_FlexPWM1_B2 | 
PORT125_FlexPWM1_X3 | 
PORT126_FlexPWM1_A3 | 
PORT127_FlexPWM1_B3 */
 (uint16)( SHL_PAD_U16(4)      | 
SHL_PAD_U16(5)      | 
SHL_PAD_U16(6)      | 
SHL_PAD_U16(7)      | 
SHL_PAD_U16(8)      | 
SHL_PAD_U16(9)      | 
SHL_PAD_U16(10)     | 
SHL_PAD_U16(11)     | 
SHL_PAD_U16(12)     | 
SHL_PAD_U16(13)     | 
SHL_PAD_U16(14)     | 
SHL_PAD_U16(15)    ),
/* Pads 128 ... 143 : PORT128_eTimer2_ETC0 | 
PORT129_eTimer2_ETC1 | 
PORT130_eTimer2_ETC2 | 
PORT131_eTimer2_ETC3 | 
PORT133_CAN2_TXD | 
PORT135_LFAST_REF_CLK | 
PORT137_eTimer2_ETC4 | 
PORT138_eTimer2_ETC5 | 
PORT141_CTU1_EXT_TRIG | 
PORT142_DSPI3_CS0 | 
PORT143_DSPI3_SCK */
 (uint16)( SHL_PAD_U16(0)       | 
SHL_PAD_U16(1)       | 
SHL_PAD_U16(2)       | 
SHL_PAD_U16(3)       | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(7)        | 
SHL_PAD_U16(9)       | 
SHL_PAD_U16(10)      | 
SHL_PAD_U16(13)       | 
SHL_PAD_U16(14)   | 
SHL_PAD_U16(15)  ),
/* Pads 144 ... 159 : PORT144_DSPI3_SOUT | 
PORT146_DSPI3_CS1 | 
PORT147_DSPI3_CS2 | 
PORT148_DSPI3_CS3 | 
PORT152_eTimer2_ETC4 | 
PORT153_eTimer2_ETC5 */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(2)    | 
SHL_PAD_U16(3)    | 
SHL_PAD_U16(4)    | 
SHL_PAD_U16(8)       | 
SHL_PAD_U16(9)      ) }
,
/*  Mode PORT_ALT2_FUNC_MODE: */
{
/* Pads   0 ...  15 : PORT0_DSPI2_SCK_OUT | 
PORT1_DSPI2_SOUT | 
PORT3_DSPI2_CS0 | 
PORT4_DSPI2_CS1 | 
PORT5_eTimer1_ETC5 | 
PORT6_eTimer2_ETC2 | 
PORT7_eTimer2_ETC3 | 
PORT8_eTimer2_ETC4 | 
PORT9_eTimer2_ETC5 | 
PORT10_FlexPWM0_B0 | 
PORT11_FlexPWM0_A0 | 
PORT12_FlexPWM0_A2 | 
PORT13_FlexPWM0_B2 | 
PORT14_eTimer1_ETC4 | 
PORT15_eTimer1_ETC5 */
 (uint16)( SHL_PAD_U16(0)      | 
SHL_PAD_U16(1)   | 
SHL_PAD_U16(3)  | 
SHL_PAD_U16(4)  | 
SHL_PAD_U16(5)     | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(8)     | 
SHL_PAD_U16(9)     | 
SHL_PAD_U16(10)    | 
SHL_PAD_U16(11)    | 
SHL_PAD_U16(12)    | 
SHL_PAD_U16(13)    | 
SHL_PAD_U16(14)     | 
SHL_PAD_U16(15)    ),
/* Pads  16 ...  31 : PORT16_eTimer1_ETC2 | 
PORT17_eTimer1_ETC3 | 
PORT18_DSPI0_CS4 | 
PORT19_DSPI0_CS5 | 
PORT22_DSPI2_CS2 */
 (uint16)( SHL_PAD_U16(0)      | 
SHL_PAD_U16(1)      | 
SHL_PAD_U16(2)   | 
SHL_PAD_U16(3)   | 
SHL_PAD_U16(6)  ),
/* Pads  32 ...  47 : PORT36_FlexPWM0_X1 | 
PORT38_FlexPWM0_B1 | 
PORT39_FlexPWM0_A1 | 
PORT43_DSPI2_CS2 | 
PORT44_DSPI2_CS3 | 
PORT46_CTU0_EXT_TRIG | 
PORT47_eTimer1_ETC0 */
 (uint16)( SHL_PAD_U16(4)     | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(11)  | 
SHL_PAD_U16(12)  | 
SHL_PAD_U16(14)      | 
SHL_PAD_U16(15)    ),
/* Pads  48 ...  63 : PORT48_eTimer1_ETC1 | 
PORT49_eTimer1_ETC2 | 
PORT50_eTimer1_ETC3 | 
PORT51_eTimer1_ETC4 | 
PORT52_eTimer1_ETC5 | 
PORT56_eTimer1_ETC4 | 
PORT57_LIN1_TXD | 
PORT60_DSPI1_CS6 */
 (uint16)( SHL_PAD_U16(0)      | 
SHL_PAD_U16(1)      | 
SHL_PAD_U16(2)      | 
SHL_PAD_U16(3)      | 
SHL_PAD_U16(4)      | 
SHL_PAD_U16(8)      | 
SHL_PAD_U16(9)  | 
SHL_PAD_U16(12) ),
/* Pads  64 ...  79 : PORT77_DSPI2_CS3 | 
PORT78_DSPI3_SOUT */
 (uint16)( SHL_PAD_U16(13)  | 
SHL_PAD_U16(14)  ),
/* Pads  80 ...  95 : PORT80_DSPI3_CS3 | 
PORT84_Nexus0_MDO3 | 
PORT85_Nexus0_MDO2 | 
PORT86_Nexus0_MDO1 | 
PORT87_Nexus0_MCKO | 
PORT88_Nexus0_MSEO_B1 | 
PORT89_Nexus0_MSEO_B0 | 
PORT90_Nexus0_EVTO_B | 
PORT91_Nexus0_EVTI_IN | 
PORT94_CAN2_TXD */
 (uint16)( SHL_PAD_U16(0)   | 
SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)     | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(8)        | 
SHL_PAD_U16(9)        | 
SHL_PAD_U16(10)      | 
SHL_PAD_U16(11)       | 
SHL_PAD_U16(14)),
/* Pads  96 ... 111 : PORT98_DSPI1_CS1 | 
PORT101_DSPI2_CS3 | 
PORT104_DSPI0_CS1 | 
PORT105_DSPI1_CS1 | 
PORT106_DSPI2_CS3 */
 (uint16)( SHL_PAD_U16(2)   | 
SHL_PAD_U16(5)    | 
SHL_PAD_U16(8)    | 
SHL_PAD_U16(9)    | 
SHL_PAD_U16(10)  ),
/* Pads 112 ... 127 : PORT116_eTimer2_ETC0 | 
PORT119_eTimer2_ETC1 | 
PORT122_eTimer2_ETC2 | 
PORT125_eTimer2_ETC3 | 
PORT126_eTimer2_ETC4 | 
PORT127_eTimer2_ETC5 */
 (uint16)( SHL_PAD_U16(4)       | 
SHL_PAD_U16(7)       | 
SHL_PAD_U16(10)      | 
SHL_PAD_U16(13)      | 
SHL_PAD_U16(14)      | 
SHL_PAD_U16(15)     ),
/* Pads 128 ... 143 : PORT128_DSPI0_CS4 | 
PORT129_DSPI0_CS5 | 
PORT130_DSPI0_CS6 | 
PORT131_DSPI0_CS7 | 
PORT132_Nexus0_NEX_RDY_B */
 (uint16)( SHL_PAD_U16(0)    | 
SHL_PAD_U16(1)    | 
SHL_PAD_U16(2)    | 
SHL_PAD_U16(3)    | 
SHL_PAD_U16(4)          ),
/* Pads 144 ... 159 : PORT152_eTimer2_ETC2 | 
PORT153_Nexus0_NEX_RDY_B */
 (uint16)( SHL_PAD_U16(8)       | 
SHL_PAD_U16(9)          ) }
,
/*  Mode PORT_ALT3_FUNC_MODE: */
{
/* Pads   0 ...  15 : PORT2_FlexPWM0_A3 | 
PORT3_FlexPWM0_B3 | 
PORT4_eTimer0_ETC4 | 
PORT5_DSPI0_CS7 | 
PORT9_FlexPWM0_B3 | 
PORT10_FlexPWM0_X2 | 
PORT11_FlexPWM0_A2 | 
PORT12_FlexPWM0_B2 */
 (uint16)( SHL_PAD_U16(2)    | 
SHL_PAD_U16(3)    | 
SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)  | 
SHL_PAD_U16(9)    | 
SHL_PAD_U16(10)    | 
SHL_PAD_U16(11)    | 
SHL_PAD_U16(12)   ),
/* Pads  16 ...  31 : PORT16_SSCM_DEBUG0 | 
PORT17_SSCM_DEBUG1 | 
PORT18_SSCM_DEBUG2 | 
PORT19_SSCM_DEBUG3 */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(1)     | 
SHL_PAD_U16(2)     | 
SHL_PAD_U16(3)    ),
/* Pads  32 ...  47 : PORT36_SSCM_DEBUG4 | 
PORT37_SSCM_DEBUG5 | 
PORT38_SSCM_DEBUG6 | 
PORT39_SSCM_DEBUG7 | 
PORT42_FlexPWM0_A3 | 
PORT43_ENET0_TX_ER | 
PORT44_LFAST_PH0_POS | 
PORT46_DSPI1_CS7 | 
PORT47_FlexPWM0_A1 */
 (uint16)( SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)     | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(10)    | 
SHL_PAD_U16(11)    | 
SHL_PAD_U16(12)      | 
SHL_PAD_U16(14)  | 
SHL_PAD_U16(15)   ),
/* Pads  48 ...  63 : PORT48_FlexPWM0_B1 | 
PORT49_CTU0_EXT_TRIG | 
PORT50_FlexPWM0_X3 | 
PORT51_FlexPWM0_A3 | 
PORT52_FlexPWM0_B3 | 
PORT54_FlexPWM0_X3 | 
PORT55_DSPI0_CS4 | 
PORT56_DSPI0_CS5 | 
PORT58_ENET0_TX_D2 | 
PORT59_DSPI3_CS1 | 
PORT60_DSPI3_CS2 | 
PORT62_DSPI3_CS3 */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(1)       | 
SHL_PAD_U16(2)     | 
SHL_PAD_U16(3)     | 
SHL_PAD_U16(4)     | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(8)   | 
SHL_PAD_U16(10)    | 
SHL_PAD_U16(11)  | 
SHL_PAD_U16(12)  | 
SHL_PAD_U16(14) ),
/* Pads  64 ...  79 : PORT77_DSPI1_CS4 | 
PORT78_DSPI1_CS5 | 
PORT79_ENET0_TIMER1 */
 (uint16)( SHL_PAD_U16(13)  | 
SHL_PAD_U16(14)  | 
SHL_PAD_U16(15)    ),
/* Pads  80 ...  95 : PORT80_ENET0_MDC | 
PORT83_DSPI3_CS2 | 
PORT84_DSPI3_CS1 | 
PORT85_DSPI3_CS0 */
 (uint16)( SHL_PAD_U16(0)   | 
SHL_PAD_U16(3)   | 
SHL_PAD_U16(4)   | 
SHL_PAD_U16(5)  ),
/* Pads  96 ... 111 : PORT101_ENET0_TX_EN | 
PORT103_LFAST_RX_POS | 
PORT104_ENET0_RMII_CLK | 
PORT105_ENET0_TX_D0 | 
PORT106_ENET0_TX_D1 | 
PORT107_ENET0_TX_D3 */
 (uint16)( SHL_PAD_U16(5)      | 
SHL_PAD_U16(7)       | 
SHL_PAD_U16(8)         | 
SHL_PAD_U16(9)      | 
SHL_PAD_U16(10)     | 
SHL_PAD_U16(11)    ),
/* Pads 112 ... 127 : PORT117_DSPI0_CS4 | 
PORT118_DSPI0_CS5 | 
PORT119_ENET0_MDIO | 
PORT120_DSPI0_CS6 | 
PORT121_DSPI0_CS7 */
 (uint16)( SHL_PAD_U16(5)    | 
SHL_PAD_U16(6)    | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(8)    | 
SHL_PAD_U16(9)   ),
/* Pads 128 ... 143 : PORT131_CTU0_EXT_TRIG | 
PORT133_LFAST_PH0_NEG | 
PORT134_LFAST_RX_NEG */
 (uint16)( SHL_PAD_U16(3)        | 
SHL_PAD_U16(5)        | 
SHL_PAD_U16(6)      ),
/* Pads 144 ... 159 */
 (uint16)0x0000 }
,
/*  Mode PORT_ALT4_FUNC_MODE: */
{
/* Pads   0 ...  15 : PORT4_FlexPWM1_A2 */
 (uint16)( SHL_PAD_U16(4)   ),
/* Pads 16 ... 31 */
 (uint16)0x0000,
/* Pads  32 ...  47 : PORT44_DSPI3_CS1 | 
PORT45_FlexPWM1_A0 | 
PORT46_FlexPWM1_B0 */
 (uint16)( SHL_PAD_U16(12)  | 
SHL_PAD_U16(13)    | 
SHL_PAD_U16(14)   ),
/* Pads  48 ...  63 : PORT53_DSPI3_SOUT | 
PORT54_DSPI3_SCK | 
PORT58_DSPI3_CS0 | 
PORT59_DSPI3_SCK | 
PORT60_DSPI3_SOUT */
 (uint16)( SHL_PAD_U16(5)    | 
SHL_PAD_U16(6)   | 
SHL_PAD_U16(10)  | 
SHL_PAD_U16(11)  | 
SHL_PAD_U16(12)  ),
/* Pads  64 ...  79 : PORT77_DSPI3_SCK | 
PORT78_FlexPWM1_B2 */
 (uint16)( SHL_PAD_U16(13)  | 
SHL_PAD_U16(14)   ),
/* Pads  80 ...  95 : PORT83_ENET0_TIMER2 | 
PORT92_FlexPWM1_A1 | 
PORT93_FlexPWM1_B1 */
 (uint16)( SHL_PAD_U16(3)      | 
SHL_PAD_U16(12)    | 
SHL_PAD_U16(13)   ),
/* Pads 96 ... 111 */
 (uint16)0x0000,
/* Pads 112 ... 127 */
 (uint16)0x0000,
/* Pads 128 ... 143 : PORT131_ENET0_TIMER0 */
 (uint16)( SHL_PAD_U16(3)      ),
/* Pads 144 ... 159 */
 (uint16)0x0000 }
,
/*  Mode PORT_ANALOG_INPUT_MODE: */
{
/* Pads 0 ... 15 */
 (uint16)0x0000,
/* Pads  16 ...  31 : PORT23_ADC0_AN0 | 
PORT24_ADC0_AN1 | 
PORT25_ADC0_ADC1_AN11 | 
PORT26_ADC0_ADC1_AN12 | 
PORT27_ADC0_ADC1_AN13 | 
PORT28_ADC0_ADC1_AN14 | 
PORT29_ADC1_AN0 | 
PORT30_ADC1_AN1 | 
PORT31_ADC1_AN2 */
 (uint16)( SHL_PAD_U16(7)  | 
SHL_PAD_U16(8)  | 
SHL_PAD_U16(9)        | 
SHL_PAD_U16(10)       | 
SHL_PAD_U16(11)       | 
SHL_PAD_U16(12)       | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14) | 
SHL_PAD_U16(15)),
/* Pads  32 ...  47 : PORT32_ADC1_AN3 | 
PORT33_ADC0_AN2 | 
PORT34_ADC0_AN3 */
 (uint16)( SHL_PAD_U16(0)  | 
SHL_PAD_U16(1)  | 
SHL_PAD_U16(2) ),
/* Pads 48 ... 63 */
 (uint16)0x0000,
/* Pads  64 ...  79 : PORT64_ADC1_AN5_ADC3_AN4 | 
PORT66_ADC0_AN5 | 
PORT68_ADC0_AN7 | 
PORT69_ADC0_AN8 | 
PORT70_ADC0_ADC2_AN4 | 
PORT71_ADC0_AN6 | 
PORT73_ADC1_AN7_ADC3_AN6 | 
PORT74_ADC1_AN8_ADC3_AN7 | 
PORT75_ADC1_AN4_ADC3_AN3 | 
PORT76_ADC1_AN6_ADC3_AN5 */
 (uint16)( SHL_PAD_U16(0)           | 
SHL_PAD_U16(2)  | 
SHL_PAD_U16(4)  | 
SHL_PAD_U16(5)  | 
SHL_PAD_U16(6)       | 
SHL_PAD_U16(7)  | 
SHL_PAD_U16(9)           | 
SHL_PAD_U16(10)          | 
SHL_PAD_U16(11)          | 
SHL_PAD_U16(12)         ),
/* Pads 80 ... 95 */
 (uint16)0x0000,
/* Pads 96 ... 111 */
 (uint16)0x0000,
/* Pads 112 ... 127 */
 (uint16)0x0000,
/* Pads 128 ... 143 */
 (uint16)0x0000,
/* Pads 144 ... 159 : PORT149_ADC2_ADC3_AN0 | 
PORT150_ADC2_ADC3_AN1 | 
PORT151_ADC2_ADC3_AN2 */
 (uint16)( SHL_PAD_U16(5)        | 
SHL_PAD_U16(6)        | 
SHL_PAD_U16(7)       ) }
,
/*  Mode PORT_INPUT1_MODE: */
{
/* Pads   0 ...  15 : PORT0_eTimer0_ETC0_IN | 
PORT1_eTimer0_ETC1_IN | 
PORT2_MC_RGM_ABS0 | 
PORT3_MC_RGM_ABS2 | 
PORT4_FlexPWM1_A2_IN | 
PORT5_SIUL2_IRQ5 | 
PORT6_SIUL2_IRQ6 | 
PORT7_SIUL2_IRQ7 | 
PORT8_DSPI1_SIN | 
PORT9_FlexPWM0_FAULT0 | 
PORT10_DSPI2_CS0_IN | 
PORT11_DSPI2_SCK_IN | 
PORT12_SIUL2_IRQ11 | 
PORT13_FlexPWM0_FAULT0 | 
PORT14_SIUL2_IRQ13 | 
PORT15_CAN0_RX */
 (uint16)( SHL_PAD_U16(0)        | 
SHL_PAD_U16(1)        | 
SHL_PAD_U16(2)    | 
SHL_PAD_U16(3)    | 
SHL_PAD_U16(4)       | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(6)   | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(8)  | 
SHL_PAD_U16(9)        | 
SHL_PAD_U16(10)     | 
SHL_PAD_U16(11)     | 
SHL_PAD_U16(12)    | 
SHL_PAD_U16(13)        | 
SHL_PAD_U16(14)    | 
SHL_PAD_U16(15)),
/* Pads  16 ...  31 : PORT16_SIUL2_IRQ15 | 
PORT17_CAN0_RX | 
PORT18_SIUL2_IRQ17 | 
PORT19_LIN0_RXD | 
PORT22_SIUL2_IRQ18 | 
PORT23_LIN0_RXD | 
PORT24_eTimer0_ETC5_IN | 
PORT29_LIN1_RXD | 
PORT30_eTimer0_ETC4_IN | 
PORT31_SIUL2_IRQ20 */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(2)     | 
SHL_PAD_U16(3)  | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)  | 
SHL_PAD_U16(8)         | 
SHL_PAD_U16(13) | 
SHL_PAD_U16(14)        | 
SHL_PAD_U16(15)   ),
/* Pads  32 ...  47 : PORT36_SIUL2_IRQ22 | 
PORT37_FlexPWM0_FAULT3 | 
PORT38_SIUL2_IRQ24 | 
PORT39_DSPI0_SIN | 
PORT42_FlexPWM0_FAULT1 | 
PORT43_eTimer0_ETC4_IN | 
PORT44_eTimer0_ETC5_IN | 
PORT45_CTU0_EXT_IN | 
PORT46_FlexPWM1_B0_IN | 
PORT47_CTU0_EXT_IN */
 (uint16)( SHL_PAD_U16(4)     | 
SHL_PAD_U16(5)         | 
SHL_PAD_U16(6)     | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(10)        | 
SHL_PAD_U16(11)        | 
SHL_PAD_U16(12)        | 
SHL_PAD_U16(13)    | 
SHL_PAD_U16(14)       | 
SHL_PAD_U16(15)   ),
/* Pads  48 ...  63 : PORT48_eTimer1_ETC1_IN | 
PORT49_FlexRay_FR_A_RX | 
PORT50_FlexRay_FR_B_RX | 
PORT51_eTimer1_ETC4_IN | 
PORT52_eTimer1_ETC5_IN | 
PORT53_FlexPWM0_FAULT2 | 
PORT54_FlexPWM0_FAULT1 | 
PORT55_SENT1_RX0 | 
PORT56_FlexPWM0_FAULT3 | 
PORT58_eTimer0_ETC0_IN | 
PORT59_eTimer0_ETC1_IN | 
PORT60_LIN1_RXD | 
PORT62_eTimer0_ETC3_IN */
 (uint16)( SHL_PAD_U16(0)         | 
SHL_PAD_U16(1)         | 
SHL_PAD_U16(2)         | 
SHL_PAD_U16(3)         | 
SHL_PAD_U16(4)         | 
SHL_PAD_U16(5)         | 
SHL_PAD_U16(6)         | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(8)         | 
SHL_PAD_U16(10)        | 
SHL_PAD_U16(11)        | 
SHL_PAD_U16(12) | 
SHL_PAD_U16(14)       ),
/* Pads  64 ...  79 : PORT77_SIUL2_IRQ25 | 
PORT78_FlexPWM1_B2_IN | 
PORT79_SIUL2_IRQ27 */
 (uint16)( SHL_PAD_U16(13)    | 
SHL_PAD_U16(14)       | 
SHL_PAD_U16(15)   ),
/* Pads  80 ...  95 : PORT80_eTimer0_ETC2_IN | 
PORT85_DSPI3_CS0_IN | 
PORT92_FlexPWM1_A1_IN | 
PORT93_FlexPWM1_B1_IN | 
PORT95_LIN1_RXD */
 (uint16)( SHL_PAD_U16(0)         | 
SHL_PAD_U16(5)      | 
SHL_PAD_U16(12)       | 
SHL_PAD_U16(13)       | 
SHL_PAD_U16(15)),
/* Pads  96 ... 111 : PORT98_FlexPWM0_X2_IN | 
PORT99_eTimer0_ETC4_IN | 
PORT100_eTimer0_ETC5_IN | 
PORT101_FlexPWM0_X3_IN | 
PORT102_FlexPWM0_A3_IN | 
PORT103_FlexPWM0_B3_IN | 
PORT104_FlexPWM0_FAULT0 | 
PORT105_FlexPWM0_FAULT1 | 
PORT106_FlexPWM0_FAULT2 | 
PORT107_FlexPWM0_FAULT3 */
 (uint16)( SHL_PAD_U16(2)        | 
SHL_PAD_U16(3)         | 
SHL_PAD_U16(4)          | 
SHL_PAD_U16(5)         | 
SHL_PAD_U16(6)         | 
SHL_PAD_U16(7)         | 
SHL_PAD_U16(8)          | 
SHL_PAD_U16(9)          | 
SHL_PAD_U16(10)         | 
SHL_PAD_U16(11)        ),
/* Pads 112 ... 127 : PORT116_eTimer2_ETC0_IN | 
PORT117_FlexPWM1_A0_IN | 
PORT118_FlexPWM1_B0_IN | 
PORT120_FlexPWM1_A1_IN | 
PORT121_FlexPWM1_B1_IN | 
PORT122_eTimer2_ETC2_IN | 
PORT123_FlexPWM1_A2_IN | 
PORT124_FlexPWM1_B2_IN | 
PORT125_eTimer2_ETC3_IN | 
PORT126_eTimer2_ETC4_IN | 
PORT127_eTimer2_ETC5_IN */
 (uint16)( SHL_PAD_U16(4)          | 
SHL_PAD_U16(5)         | 
SHL_PAD_U16(6)         | 
SHL_PAD_U16(8)         | 
SHL_PAD_U16(9)         | 
SHL_PAD_U16(10)         | 
SHL_PAD_U16(11)        | 
SHL_PAD_U16(12)        | 
SHL_PAD_U16(13)         | 
SHL_PAD_U16(14)         | 
SHL_PAD_U16(15)        ),
/* Pads 128 ... 143 : PORT128_FlexPWM1_FAULT0 | 
PORT129_FlexPWM1_FAULT1 | 
PORT130_FlexPWM1_FAULT2 | 
PORT131_FlexPWM1_FAULT3 | 
PORT134_CAN2_RXD | 
PORT135_SENT0_RX0 | 
PORT136_SENT1_RX0 | 
PORT137_eTimer2_ETC4_IN | 
PORT138_eTimer2_ETC5_IN | 
PORT139_SENT0_RX1 | 
PORT140_SENT1_RX1 | 
PORT142_DSPI3_CS0_IN | 
PORT143_DSPI3_SCK_IN */
 (uint16)( SHL_PAD_U16(0)          | 
SHL_PAD_U16(1)          | 
SHL_PAD_U16(2)          | 
SHL_PAD_U16(3)          | 
SHL_PAD_U16(6)   | 
SHL_PAD_U16(7)    | 
SHL_PAD_U16(8)    | 
SHL_PAD_U16(9)          | 
SHL_PAD_U16(10)         | 
SHL_PAD_U16(11)   | 
SHL_PAD_U16(12)   | 
SHL_PAD_U16(14)      | 
SHL_PAD_U16(15)     ),
/* Pads 144 ... 159 : PORT145_DSPI3_SIN | 
PORT148_CTU1_EXT_IN | 
PORT149_SENT0_RX1 | 
PORT150_SENT1_RX1 | 
PORT152_CAN2_RXD | 
PORT153_CTU1_EXT_IN */
 (uint16)( SHL_PAD_U16(1)    | 
SHL_PAD_U16(4)      | 
SHL_PAD_U16(5)    | 
SHL_PAD_U16(6)    | 
SHL_PAD_U16(8)   | 
SHL_PAD_U16(9)     ) }
,
/*  Mode PORT_INPUT2_MODE: */
{
/* Pads   0 ...  15 : PORT0_DSPI2_SCK_IN | 
PORT1_SIUL2_IRQ1 | 
PORT2_DSPI2_SIN | 
PORT3_eTimer0_ETC3_IN | 
PORT4_SIUL2_IRQ4 | 
PORT5_eTimer1_ETC5_IN | 
PORT6_eTimer2_ETC2_IN | 
PORT7_eTimer2_ETC3_IN | 
PORT8_SIUL2_IRQ8 | 
PORT9_eTimer2_ETC5_IN | 
PORT10_SIUL2_IRQ9 | 
PORT11_SIUL2_IRQ10 | 
PORT12_FlexPWM0_A2_IN | 
PORT13_DSPI2_SIN | 
PORT14_eTimer1_ETC4_IN | 
PORT15_CAN1_RX */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(1)   | 
SHL_PAD_U16(2)  | 
SHL_PAD_U16(3)        | 
SHL_PAD_U16(4)   | 
SHL_PAD_U16(5)        | 
SHL_PAD_U16(6)        | 
SHL_PAD_U16(7)        | 
SHL_PAD_U16(8)   | 
SHL_PAD_U16(9)        | 
SHL_PAD_U16(10)   | 
SHL_PAD_U16(11)    | 
SHL_PAD_U16(12)       | 
SHL_PAD_U16(13)  | 
SHL_PAD_U16(14)        | 
SHL_PAD_U16(15)),
/* Pads  16 ...  31 : PORT16_eTimer1_ETC2_IN | 
PORT17_CAN1_RX | 
PORT30_SIUL2_IRQ19 */
 (uint16)( SHL_PAD_U16(0)         | 
SHL_PAD_U16(1) | 
SHL_PAD_U16(14)   ),
/* Pads  32 ...  47 : PORT36_FlexPWM0_X1_IN | 
PORT37_SIUL2_IRQ23 | 
PORT38_FlexPWM0_B1_IN | 
PORT39_FlexPWM0_A1_IN | 
PORT42_FlexPWM0_A3_IN | 
PORT43_DSPI3_CS0 | 
PORT44_SENT1_RX0 | 
PORT45_FlexPWM0_SYNC | 
PORT46_eTimer1_ETC2_IN | 
PORT47_FlexPWM0_SYNC */
 (uint16)( SHL_PAD_U16(4)        | 
SHL_PAD_U16(5)     | 
SHL_PAD_U16(6)        | 
SHL_PAD_U16(7)        | 
SHL_PAD_U16(10)       | 
SHL_PAD_U16(11)  | 
SHL_PAD_U16(12)  | 
SHL_PAD_U16(13)      | 
SHL_PAD_U16(14)        | 
SHL_PAD_U16(15)     ),
/* Pads  48 ...  63 : PORT48_FlexPWM0_B1_IN | 
PORT49_eTimer1_ETC2_IN | 
PORT50_eTimer1_ETC3_IN | 
PORT51_FlexPWM0_A3_IN | 
PORT52_FlexPWM0_B3_IN | 
PORT53_SENT0_RX0 | 
PORT54_FlexPWM0_X3_IN | 
PORT55_DSPI3_SIN | 
PORT56_eTimer1_ETC4_IN | 
PORT58_FlexPWM0_A0_IN | 
PORT59_FlexPWM0_B0_IN | 
PORT60_FlexPWM0_X1_IN | 
PORT62_FlexPWM0_B1_IN */
 (uint16)( SHL_PAD_U16(0)        | 
SHL_PAD_U16(1)         | 
SHL_PAD_U16(2)         | 
SHL_PAD_U16(3)        | 
SHL_PAD_U16(4)        | 
SHL_PAD_U16(5)   | 
SHL_PAD_U16(6)        | 
SHL_PAD_U16(7)   | 
SHL_PAD_U16(8)         | 
SHL_PAD_U16(10)       | 
SHL_PAD_U16(11)       | 
SHL_PAD_U16(12)       | 
SHL_PAD_U16(14)      ),
/* Pads  64 ...  79 : PORT77_eTimer0_ETC5_IN | 
PORT78_SIUL2_IRQ26 | 
PORT79_DSPI3_SIN */
 (uint16)( SHL_PAD_U16(13)        | 
SHL_PAD_U16(14)    | 
SHL_PAD_U16(15) ),
/* Pads  80 ...  95 : PORT80_SIUL2_IRQ28 | 
PORT92_SIUL2_IRQ30 | 
PORT93_SIUL2_IRQ31 | 
PORT95_CAN2_RXD */
 (uint16)( SHL_PAD_U16(0)     | 
SHL_PAD_U16(12)    | 
SHL_PAD_U16(13)    | 
SHL_PAD_U16(15)),
/* Pads  96 ... 111 : PORT99_FlexPWM0_A2_IN | 
PORT100_FlexPWM0_B2_IN | 
PORT104_SIUL2_IRQ21 | 
PORT105_SIUL2_IRQ29 | 
PORT106_SENT0_RX1 | 
PORT107_SENT1_RX1 */
 (uint16)( SHL_PAD_U16(3)        | 
SHL_PAD_U16(4)         | 
SHL_PAD_U16(8)      | 
SHL_PAD_U16(9)      | 
SHL_PAD_U16(10)   | 
SHL_PAD_U16(11)  ),
/* Pads 112 ... 127 : PORT116_ENET0_CRS | 
PORT117_ENET0_COL | 
PORT119_eTimer2_ETC1_IN | 
PORT120_ENET0_RX_D2 */
 (uint16)( SHL_PAD_U16(4)    | 
SHL_PAD_U16(5)    | 
SHL_PAD_U16(7)          | 
SHL_PAD_U16(8)     ),
/* Pads 128 ... 143 : PORT128_eTimer2_ETC0_IN | 
PORT129_eTimer2_ETC1_IN | 
PORT130_eTimer2_ETC2_IN | 
PORT131_eTimer2_ETC3_IN */
 (uint16)( SHL_PAD_U16(0)          | 
SHL_PAD_U16(1)          | 
SHL_PAD_U16(2)          | 
SHL_PAD_U16(3)         ),
/* Pads 144 ... 159 : PORT152_eTimer2_ETC2_IN | 
PORT153_eTimer2_ETC5_IN */
 (uint16)( SHL_PAD_U16(8)          | 
SHL_PAD_U16(9)         ) }
,
/*  Mode PORT_INPUT3_MODE: */
{
/* Pads   0 ...  15 : PORT0_SIUL2_IRQ0 | 
PORT2_eTimer0_ETC2_IN | 
PORT3_DSPI2_CS0_IN | 
PORT4_MC_RGM_FAB | 
PORT8_eTimer2_ETC4_IN | 
PORT9_FlexPWM0_B3_IN | 
PORT10_FlexPWM0_B0_IN | 
PORT11_FlexPWM0_A0_IN | 
PORT12_FlexPWM0_B2_IN | 
PORT13_SIUL2_IRQ12 | 
PORT15_SIUL2_IRQ14 */
 (uint16)( SHL_PAD_U16(0)   | 
SHL_PAD_U16(2)        | 
SHL_PAD_U16(3)     | 
SHL_PAD_U16(4)   | 
SHL_PAD_U16(8)        | 
SHL_PAD_U16(9)       | 
SHL_PAD_U16(10)       | 
SHL_PAD_U16(11)       | 
SHL_PAD_U16(12)       | 
SHL_PAD_U16(13)    | 
SHL_PAD_U16(15)   ),
/* Pads  16 ...  31 : PORT17_SIUL2_IRQ16 */
 (uint16)( SHL_PAD_U16(1)    ),
/* Pads  32 ...  47 : PORT45_FlexPWM1_A0_IN | 
PORT47_eTimer1_ETC0_IN */
 (uint16)( SHL_PAD_U16(13)       | 
SHL_PAD_U16(15)       ),
/* Pads  48 ...  63 : PORT50_FlexPWM0_X3_IN | 
PORT53_ENET0_RX_D1 | 
PORT54_DSPI3_SCK_IN | 
PORT55_ENET0_RX_DV | 
PORT56_ENET0_RX_CLK | 
PORT58_DSPI3_CS0_IN | 
PORT59_DSPI3_SCK_IN | 
PORT62_DSPI3_SIN */
 (uint16)( SHL_PAD_U16(2)        | 
SHL_PAD_U16(5)     | 
SHL_PAD_U16(6)      | 
SHL_PAD_U16(7)     | 
SHL_PAD_U16(8)      | 
SHL_PAD_U16(10)     | 
SHL_PAD_U16(11)     | 
SHL_PAD_U16(14) ),
/* Pads  64 ...  79 : PORT77_DSPI3_SCK_IN | 
PORT78_eTimer1_ETC5_IN */
 (uint16)( SHL_PAD_U16(13)     | 
SHL_PAD_U16(14)       ),
/* Pads  80 ...  95 : PORT80_FlexPWM0_A1_IN | 
PORT92_eTimer1_ETC3_IN | 
PORT93_eTimer1_ETC4_IN */
 (uint16)( SHL_PAD_U16(0)        | 
SHL_PAD_U16(12)        | 
SHL_PAD_U16(13)       ),
/* Pads  96 ... 111 : PORT104_SENT0_RX0 | 
PORT105_SENT1_RX0 */
 (uint16)( SHL_PAD_U16(8)    | 
SHL_PAD_U16(9)   ),
/* Pads 112 ... 127 */
 (uint16)0x0000,
/* Pads 128 ... 143 : PORT129_ENET0_RX_ER */
 (uint16)( SHL_PAD_U16(1)     ),
/* Pads 144 ... 159 : PORT152_eTimer2_ETC4_IN | 
PORT153_ENET0_RX_D3 */
 (uint16)( SHL_PAD_U16(8)          | 
SHL_PAD_U16(9)     ) }
,
/*  Mode PORT_INPUT4_MODE: */
{
/* Pads   0 ...  15 : PORT2_SIUL2_IRQ2 | 
PORT3_SIUL2_IRQ3 | 
PORT4_eTimer0_ETC4_IN | 
PORT9_SENT0_RX1 | 
PORT10_FlexPWM0_X2_IN | 
PORT11_FlexPWM0_A2_IN | 
PORT13_FlexPWM0_B2_IN | 
PORT15_eTimer1_ETC5_IN */
 (uint16)( SHL_PAD_U16(2)   | 
SHL_PAD_U16(3)   | 
SHL_PAD_U16(4)        | 
SHL_PAD_U16(9)  | 
SHL_PAD_U16(10)       | 
SHL_PAD_U16(11)       | 
SHL_PAD_U16(13)       | 
SHL_PAD_U16(15)       ),
/* Pads  16 ...  31 : PORT17_eTimer1_ETC3_IN */
 (uint16)( SHL_PAD_U16(1)        ),
/* Pads  32 ...  47 : PORT45_eTimer1_ETC1_IN | 
PORT47_FlexPWM0_A1_IN */
 (uint16)( SHL_PAD_U16(13)        | 
SHL_PAD_U16(15)      ),
/* Pads  48 ...  63 : PORT54_ENET0_RX_D0 */
 (uint16)( SHL_PAD_U16(6)    ),
/* Pads 64 ... 79 */
 (uint16)0x0000,
/* Pads 80 ... 95 */
 (uint16)0x0000,
/* Pads  96 ... 111 : PORT104_ENET0_TX_CLK */
 (uint16)( SHL_PAD_U16(8)      ),
/* Pads 112 ... 127 */
 (uint16)0x0000,
/* Pads 128 ... 143 */
 (uint16)0x0000,
/* Pads 144 ... 159 */
 (uint16)0x0000 }
,
/*  Mode PORT_INPUT5_MODE: */
{
/* Pads   0 ...  15 : PORT2_FlexPWM0_A3_IN | 
PORT3_FlexPWM0_B3_IN | 
PORT4_eTimer1_ETC0_IN | 
PORT10_SENT1_RX1 */
 (uint16)( SHL_PAD_U16(2)       | 
SHL_PAD_U16(3)       | 
SHL_PAD_U16(4)        | 
SHL_PAD_U16(10) ),
/* Pads 16 ... 31 */
 (uint16)0x0000,
/* Pads 32 ... 47 */
 (uint16)0x0000,
/* Pads 48 ... 63 */
 (uint16)0x0000,
/* Pads 64 ... 79 */
 (uint16)0x0000,
/* Pads 80 ... 95 */
 (uint16)0x0000,
/* Pads 96 ... 111 */
 (uint16)0x0000,
/* Pads 112 ... 127 */
 (uint16)0x0000,
/* Pads 128 ... 143 */
 (uint16)0x0000,
/* Pads 144 ... 159 */
 (uint16)0x0000 }

};

/**
* @brief Port INPUT INMUX settings data
*/
CONST(Port_InMuxSettingType,PORT_CONST) Port_aPadFunctInMuxSettings[212]=
{  
  /* INMUX settings for pad not available:  */
  { NO_INPUTMUX_U16, 0U},
  /* INMUX settings for pad PORT0:      {INMUX reg, PADSEL val} */
  /* eTimer0_ETC0_IN input func */
  {59U, 2U}, 
  /* DSPI2_SCK_IN input func */
  {48U, 1U}, 
  /* SIUL2_IRQ0 input func */
  {173U, 1U}, 
  /* INMUX settings for pad PORT1:      {INMUX reg, PADSEL val} */
  /* eTimer0_ETC1_IN input func */
  {60U, 2U}, 
  /* SIUL2_IRQ1 input func */
  {174U, 1U}, 
  /* INMUX settings for pad PORT2:      {INMUX reg, PADSEL val} */
  /* MC_RGM_ABS0 input func */
  {169U, 0U}, 
  /* DSPI2_SIN input func */
  {47U, 2U}, 
  /* eTimer0_ETC2_IN input func */
  {61U, 2U}, 
  /* SIUL2_IRQ2 input func */
  {175U, 1U}, 
  /* FlexPWM0_A3_IN input func */
  {97U, 1U}, 
  /* INMUX settings for pad PORT3:      {INMUX reg, PADSEL val} */
  /* MC_RGM_ABS2 input func */
  {171U, 0U}, 
  /* eTimer0_ETC3_IN input func */
  {62U, 2U}, 
  /* DSPI2_CS0_IN input func */
  {49U, 1U}, 
  /* SIUL2_IRQ3 input func */
  {176U, 1U}, 
  /* FlexPWM0_B3_IN input func */
  {98U, 1U}, 
  /* INMUX settings for pad PORT4:      {INMUX reg, PADSEL val} */
  /* FlexPWM1_A2_IN input func */
  {112U, 1U}, 
  /* SIUL2_IRQ4 input func */
  {177U, 1U}, 
  /* MC_RGM_FAB input func */
  {172U, 0U}, 
  /* eTimer0_ETC4_IN input func */
  {63U, 3U}, 
  /* eTimer1_ETC0_IN input func */
  {65U, 1U}, 
  /* INMUX settings for pad PORT5:      {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ5 input func */
  {178U, 1U}, 
  /* eTimer1_ETC5_IN input func */
  {70U, 1U}, 
  /* INMUX settings for pad PORT6:      {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ6 input func */
  {179U, 1U}, 
  /* eTimer2_ETC2_IN input func */
  {73U, 1U}, 
  /* INMUX settings for pad PORT7:      {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ7 input func */
  {180U, 1U}, 
  /* eTimer2_ETC3_IN input func */
  {74U, 1U}, 
  /* INMUX settings for pad PORT8:      {INMUX reg, PADSEL val} */
  /* DSPI1_SIN input func */
  {44U, 1U}, 
  /* SIUL2_IRQ8 input func */
  {181U, 1U}, 
  /* eTimer2_ETC4_IN input func */
  {75U, 1U}, 
  /* INMUX settings for pad PORT9:      {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT0 input func */
  {83U, 1U}, 
  /* eTimer2_ETC5_IN input func */
  {76U, 1U}, 
  /* FlexPWM0_B3_IN input func */
  {98U, 2U}, 
  /* SENT0_RX1 input func */
  {206U, 3U}, 
  /* INMUX settings for pad PORT10:     {INMUX reg, PADSEL val} */
  /* DSPI2_CS0_IN input func */
  {49U, 2U}, 
  /* SIUL2_IRQ9 input func */
  {182U, 1U}, 
  /* FlexPWM0_B0_IN input func */
  {89U, 1U}, 
  /* FlexPWM0_X2_IN input func */
  {96U, 1U}, 
  /* SENT1_RX1 input func */
  {214U, 3U}, 
  /* INMUX settings for pad PORT11:     {INMUX reg, PADSEL val} */
  /* DSPI2_SCK_IN input func */
  {48U, 2U}, 
  /* SIUL2_IRQ10 input func */
  {183U, 1U}, 
  /* FlexPWM0_A0_IN input func */
  {88U, 1U}, 
  /* FlexPWM0_A2_IN input func */
  {94U, 1U}, 
  /* INMUX settings for pad PORT12:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ11 input func */
  {184U, 1U}, 
  /* FlexPWM0_A2_IN input func */
  {94U, 2U}, 
  /* FlexPWM0_B2_IN input func */
  {95U, 1U}, 
  /* INMUX settings for pad PORT13:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT0 input func */
  {83U, 2U}, 
  /* DSPI2_SIN input func */
  {47U, 1U}, 
  /* SIUL2_IRQ12 input func */
  {185U, 1U}, 
  /* FlexPWM0_B2_IN input func */
  {95U, 2U}, 
  /* INMUX settings for pad PORT14:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ13 input func */
  {186U, 1U}, 
  /* eTimer1_ETC4_IN input func */
  {69U, 1U}, 
  /* INMUX settings for pad PORT15:     {INMUX reg, PADSEL val} */
  /* CAN0_RX input func */
  {32U, 1U}, 
  /* CAN1_RX input func */
  {33U, 1U}, 
  /* SIUL2_IRQ14 input func */
  {187U, 1U}, 
  /* eTimer1_ETC5_IN input func */
  {70U, 2U}, 
  /* INMUX settings for pad PORT16:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ15 input func */
  {188U, 1U}, 
  /* eTimer1_ETC2_IN input func */
  {67U, 1U}, 
  /* INMUX settings for pad PORT17:     {INMUX reg, PADSEL val} */
  /* CAN0_RX input func */
  {32U, 2U}, 
  /* CAN1_RX input func */
  {33U, 2U}, 
  /* SIUL2_IRQ16 input func */
  {189U, 1U}, 
  /* eTimer1_ETC3_IN input func */
  {68U, 1U}, 
  /* INMUX settings for pad PORT18:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ17 input func */
  {190U, 1U}, 
  /* INMUX settings for pad PORT19:     {INMUX reg, PADSEL val} */
  /* LIN0_RXD input func */
  {165U, 1U}, 
  /* INMUX settings for pad PORT22:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ18 input func */
  {191U, 1U}, 
  /* INMUX settings for pad PORT23:     {INMUX reg, PADSEL val} */
  /* LIN0_RXD input func */
  {165U, 2U}, 
  /* INMUX settings for pad PORT24:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC5_IN input func */
  {64U, 1U}, 
  /* INMUX settings for pad PORT29:     {INMUX reg, PADSEL val} */
  /* LIN1_RXD input func */
  {166U, 1U}, 
  /* INMUX settings for pad PORT30:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC4_IN input func */
  {63U, 1U}, 
  /* SIUL2_IRQ19 input func */
  {192U, 1U}, 
  /* INMUX settings for pad PORT31:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ20 input func */
  {193U, 1U}, 
  /* INMUX settings for pad PORT36:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ22 input func */
  {195U, 1U}, 
  /* FlexPWM0_X1_IN input func */
  {93U, 1U}, 
  /* INMUX settings for pad PORT37:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT3 input func */
  {86U, 1U}, 
  /* SIUL2_IRQ23 input func */
  {196U, 1U}, 
  /* INMUX settings for pad PORT38:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ24 input func */
  {197U, 1U}, 
  /* FlexPWM0_B1_IN input func */
  {92U, 1U}, 
  /* INMUX settings for pad PORT39:     {INMUX reg, PADSEL val} */
  /* DSPI0_SIN input func */
  {41U, 1U}, 
  /* FlexPWM0_A1_IN input func */
  {91U, 1U}, 
  /* INMUX settings for pad PORT42:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT1 input func */
  {84U, 1U}, 
  /* FlexPWM0_A3_IN input func */
  {97U, 2U}, 
  /* INMUX settings for pad PORT43:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC4_IN input func */
  {63U, 4U}, 
  /* DSPI3_CS0 input func */
  {52U, 1U}, 
  /* INMUX settings for pad PORT44:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC5_IN input func */
  {64U, 3U}, 
  /* SENT1_RX0 input func */
  {213U, 4U}, 
  /* INMUX settings for pad PORT45:     {INMUX reg, PADSEL val} */
  /* CTU0_EXT_IN input func */
  {38U, 1U}, 
  /* FlexPWM0_SYNC input func */
  {87U, 1U}, 
  /* FlexPWM1_A0_IN input func */
  {105U, 1U}, 
  /* eTimer1_ETC1_IN input func */
  {66U, 1U}, 
  /* INMUX settings for pad PORT46:     {INMUX reg, PADSEL val} */
  /* FlexPWM1_B0_IN input func */
  {106U, 1U}, 
  /* eTimer1_ETC2_IN input func */
  {67U, 2U}, 
  /* INMUX settings for pad PORT47:     {INMUX reg, PADSEL val} */
  /* CTU0_EXT_IN input func */
  {38U, 2U}, 
  /* FlexPWM0_SYNC input func */
  {87U, 2U}, 
  /* eTimer1_ETC0_IN input func */
  {65U, 2U}, 
  /* FlexPWM0_A1_IN input func */
  {91U, 2U}, 
  /* INMUX settings for pad PORT48:     {INMUX reg, PADSEL val} */
  /* eTimer1_ETC1_IN input func */
  {66U, 2U}, 
  /* FlexPWM0_B1_IN input func */
  {92U, 2U}, 
  /* INMUX settings for pad PORT49:     {INMUX reg, PADSEL val} */
  /* FlexRay_FR_A_RX input func */
  {136U, 1U}, 
  /* eTimer1_ETC2_IN input func */
  {67U, 3U}, 
  /* INMUX settings for pad PORT50:     {INMUX reg, PADSEL val} */
  /* FlexRay_FR_B_RX input func */
  {137U, 1U}, 
  /* eTimer1_ETC3_IN input func */
  {68U, 2U}, 
  /* FlexPWM0_X3_IN input func */
  {99U, 1U}, 
  /* INMUX settings for pad PORT51:     {INMUX reg, PADSEL val} */
  /* eTimer1_ETC4_IN input func */
  {69U, 2U}, 
  /* FlexPWM0_A3_IN input func */
  {97U, 3U}, 
  /* INMUX settings for pad PORT52:     {INMUX reg, PADSEL val} */
  /* eTimer1_ETC5_IN input func */
  {70U, 3U}, 
  /* FlexPWM0_B3_IN input func */
  {98U, 3U}, 
  /* INMUX settings for pad PORT53:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT2 input func */
  {85U, 1U}, 
  /* SENT0_RX0 input func */
  {205U, 1U}, 
  /* ENET0_RX_D1 input func */
  {227U, 1U}, 
  /* INMUX settings for pad PORT54:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT1 input func */
  {84U, 2U}, 
  /* FlexPWM0_X3_IN input func */
  {99U, 2U}, 
  /* DSPI3_SCK_IN input func */
  {51U, 1U}, 
  /* ENET0_RX_D0 input func */
  {226U, 1U}, 
  /* INMUX settings for pad PORT55:     {INMUX reg, PADSEL val} */
  /* SENT1_RX0 input func */
  {213U, 1U}, 
  /* DSPI3_SIN input func */
  {50U, 2U}, 
  /* ENET0_RX_DV input func */
  {225U, 1U}, 
  /* INMUX settings for pad PORT56:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT3 input func */
  {86U, 2U}, 
  /* eTimer1_ETC4_IN input func */
  {69U, 3U}, 
  /* ENET0_RX_CLK input func */
  {224U, 1U}, 
  /* INMUX settings for pad PORT58:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC0_IN input func */
  {59U, 1U}, 
  /* FlexPWM0_A0_IN input func */
  {88U, 2U}, 
  /* DSPI3_CS0_IN input func */
  {52U, 2U}, 
  /* INMUX settings for pad PORT59:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC1_IN input func */
  {60U, 1U}, 
  /* FlexPWM0_B0_IN input func */
  {89U, 2U}, 
  /* DSPI3_SCK_IN input func */
  {51U, 2U}, 
  /* INMUX settings for pad PORT60:     {INMUX reg, PADSEL val} */
  /* LIN1_RXD input func */
  {166U, 2U}, 
  /* FlexPWM0_X1_IN input func */
  {93U, 2U}, 
  /* INMUX settings for pad PORT62:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC3_IN input func */
  {62U, 1U}, 
  /* FlexPWM0_B1_IN input func */
  {92U, 3U}, 
  /* DSPI3_SIN input func */
  {50U, 3U}, 
  /* INMUX settings for pad PORT77:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ25 input func */
  {198U, 1U}, 
  /* eTimer0_ETC5_IN input func */
  {64U, 4U}, 
  /* DSPI3_SCK_IN input func */
  {51U, 3U}, 
  /* INMUX settings for pad PORT78:     {INMUX reg, PADSEL val} */
  /* FlexPWM1_B2_IN input func */
  {113U, 1U}, 
  /* SIUL2_IRQ26 input func */
  {199U, 1U}, 
  /* eTimer1_ETC5_IN input func */
  {70U, 4U}, 
  /* INMUX settings for pad PORT79:     {INMUX reg, PADSEL val} */
  /* SIUL2_IRQ27 input func */
  {200U, 1U}, 
  /* DSPI3_SIN input func */
  {50U, 4U}, 
  /* INMUX settings for pad PORT80:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC2_IN input func */
  {61U, 1U}, 
  /* SIUL2_IRQ28 input func */
  {201U, 1U}, 
  /* FlexPWM0_A1_IN input func */
  {91U, 3U}, 
  /* INMUX settings for pad PORT85:     {INMUX reg, PADSEL val} */
  /* DSPI3_CS0_IN input func */
  {52U, 3U}, 
  /* INMUX settings for pad PORT92:     {INMUX reg, PADSEL val} */
  /* FlexPWM1_A1_IN input func */
  {109U, 1U}, 
  /* SIUL2_IRQ30 input func */
  {203U, 1U}, 
  /* eTimer1_ETC3_IN input func */
  {68U, 3U}, 
  /* INMUX settings for pad PORT93:     {INMUX reg, PADSEL val} */
  /* FlexPWM1_B1_IN input func */
  {110U, 1U}, 
  /* SIUL2_IRQ31 input func */
  {204U, 1U}, 
  /* eTimer1_ETC4_IN input func */
  {69U, 4U}, 
  /* INMUX settings for pad PORT95:     {INMUX reg, PADSEL val} */
  /* LIN1_RXD input func */
  {166U, 3U}, 
  /* CAN2_RXD input func */
  {34U, 1U}, 
  /* INMUX settings for pad PORT98:     {INMUX reg, PADSEL val} */
  /* FlexPWM0_X2_IN input func */
  {96U, 2U}, 
  /* INMUX settings for pad PORT99:     {INMUX reg, PADSEL val} */
  /* eTimer0_ETC4_IN input func */
  {63U, 2U}, 
  /* FlexPWM0_A2_IN input func */
  {94U, 3U}, 
  /* INMUX settings for pad PORT100:    {INMUX reg, PADSEL val} */
  /* eTimer0_ETC5_IN input func */
  {64U, 2U}, 
  /* FlexPWM0_B2_IN input func */
  {95U, 3U}, 
  /* INMUX settings for pad PORT101:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_X3_IN input func */
  {99U, 3U}, 
  /* INMUX settings for pad PORT102:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_A3_IN input func */
  {97U, 4U}, 
  /* INMUX settings for pad PORT103:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_B3_IN input func */
  {98U, 4U}, 
  /* INMUX settings for pad PORT104:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT0 input func */
  {83U, 3U}, 
  /* SIUL2_IRQ21 input func */
  {194U, 1U}, 
  /* SENT0_RX0 input func */
  {205U, 3U}, 
  /* ENET0_TX_CLK input func */
  {233U, 1U}, 
  /* INMUX settings for pad PORT105:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT1 input func */
  {84U, 3U}, 
  /* SIUL2_IRQ29 input func */
  {202U, 1U}, 
  /* SENT1_RX0 input func */
  {213U, 3U}, 
  /* INMUX settings for pad PORT106:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT2 input func */
  {85U, 2U}, 
  /* SENT0_RX1 input func */
  {206U, 4U}, 
  /* INMUX settings for pad PORT107:    {INMUX reg, PADSEL val} */
  /* FlexPWM0_FAULT3 input func */
  {86U, 3U}, 
  /* SENT1_RX1 input func */
  {214U, 4U}, 
  /* INMUX settings for pad PORT116:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC0_IN input func */
  {71U, 1U}, 
  /* ENET0_CRS input func */
  {231U, 1U}, 
  /* INMUX settings for pad PORT117:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_A0_IN input func */
  {105U, 2U}, 
  /* ENET0_COL input func */
  {230U, 1U}, 
  /* INMUX settings for pad PORT118:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_B0_IN input func */
  {106U, 2U}, 
  /* INMUX settings for pad PORT119:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC1_IN input func */
  {72U, 1U}, 
  /* INMUX settings for pad PORT120:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_A1_IN input func */
  {109U, 2U}, 
  /* ENET0_RX_D2 input func */
  {228U, 1U}, 
  /* INMUX settings for pad PORT121:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_B1_IN input func */
  {110U, 2U}, 
  /* INMUX settings for pad PORT122:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC2_IN input func */
  {73U, 2U}, 
  /* INMUX settings for pad PORT123:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_A2_IN input func */
  {112U, 2U}, 
  /* INMUX settings for pad PORT124:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_B2_IN input func */
  {113U, 2U}, 
  /* INMUX settings for pad PORT125:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC3_IN input func */
  {74U, 2U}, 
  /* INMUX settings for pad PORT126:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC4_IN input func */
  {75U, 2U}, 
  /* INMUX settings for pad PORT127:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC5_IN input func */
  {76U, 2U}, 
  /* INMUX settings for pad PORT128:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_FAULT0 input func */
  {100U, 1U}, 
  /* eTimer2_ETC0_IN input func */
  {71U, 2U}, 
  /* INMUX settings for pad PORT129:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_FAULT1 input func */
  {101U, 1U}, 
  /* eTimer2_ETC1_IN input func */
  {72U, 2U}, 
  /* ENET0_RX_ER input func */
  {232U, 1U}, 
  /* INMUX settings for pad PORT130:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_FAULT2 input func */
  {102U, 1U}, 
  /* eTimer2_ETC2_IN input func */
  {73U, 3U}, 
  /* INMUX settings for pad PORT131:    {INMUX reg, PADSEL val} */
  /* FlexPWM1_FAULT3 input func */
  {103U, 1U}, 
  /* eTimer2_ETC3_IN input func */
  {74U, 3U}, 
  /* INMUX settings for pad PORT134:    {INMUX reg, PADSEL val} */
  /* CAN2_RXD input func */
  {34U, 2U}, 
  /* INMUX settings for pad PORT135:    {INMUX reg, PADSEL val} */
  /* SENT0_RX0 input func */
  {205U, 2U}, 
  /* INMUX settings for pad PORT136:    {INMUX reg, PADSEL val} */
  /* SENT1_RX0 input func */
  {213U, 2U}, 
  /* INMUX settings for pad PORT137:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC4_IN input func */
  {75U, 3U}, 
  /* INMUX settings for pad PORT138:    {INMUX reg, PADSEL val} */
  /* eTimer2_ETC5_IN input func */
  {76U, 3U}, 
  /* INMUX settings for pad PORT139:    {INMUX reg, PADSEL val} */
  /* SENT0_RX1 input func */
  {206U, 1U}, 
  /* INMUX settings for pad PORT140:    {INMUX reg, PADSEL val} */
  /* SENT1_RX1 input func */
  {214U, 1U}, 
  /* INMUX settings for pad PORT142:    {INMUX reg, PADSEL val} */
  /* DSPI3_CS0_IN input func */
  {52U, 4U}, 
  /* INMUX settings for pad PORT143:    {INMUX reg, PADSEL val} */
  /* DSPI3_SCK_IN input func */
  {51U, 4U}, 
  /* INMUX settings for pad PORT145:    {INMUX reg, PADSEL val} */
  /* DSPI3_SIN input func */
  {50U, 1U}, 
  /* INMUX settings for pad PORT148:    {INMUX reg, PADSEL val} */
  /* CTU1_EXT_IN input func */
  {39U, 1U}, 
  /* INMUX settings for pad PORT149:    {INMUX reg, PADSEL val} */
  /* SENT0_RX1 input func */
  {206U, 2U}, 
  /* INMUX settings for pad PORT150:    {INMUX reg, PADSEL val} */
  /* SENT1_RX1 input func */
  {214U, 2U}, 
  /* INMUX settings for pad PORT152:    {INMUX reg, PADSEL val} */
  /* CAN2_RXD input func */
  {34U, 3U}, 
  /* eTimer2_ETC2_IN input func */
  {73U, 4U}, 
  /* eTimer2_ETC4_IN input func */
  {75U, 4U}, 
  /* INMUX settings for pad PORT153:    {INMUX reg, PADSEL val} */
  /* CTU1_EXT_IN input func */
  {39U, 2U}, 
  /* eTimer2_ETC5_IN input func */
  {76U, 4U}, 
  /* ENET0_RX_D3 input func */
  {229U, 1U}
};
/**
* @brief Port index to address the INPUT INDEX data
*/
CONST(uint16,PORT_CONST) Port_au16PadFunctInMuxIndex[154]=
{  
  /* Index to address the input settings for pad 0*/
  (uint16)1, 
  /* Index to address the input settings for pad 1*/
  (uint16)4, 
  /* Index to address the input settings for pad 2*/
  (uint16)6, 
  /* Index to address the input settings for pad 3*/
  (uint16)11, 
  /* Index to address the input settings for pad 4*/
  (uint16)16, 
  /* Index to address the input settings for pad 5*/
  (uint16)21, 
  /* Index to address the input settings for pad 6*/
  (uint16)23, 
  /* Index to address the input settings for pad 7*/
  (uint16)25, 
  /* Index to address the input settings for pad 8*/
  (uint16)27, 
  /* Index to address the input settings for pad 9*/
  (uint16)30, 
  /* Index to address the input settings for pad 10*/
  (uint16)34, 
  /* Index to address the input settings for pad 11*/
  (uint16)39, 
  /* Index to address the input settings for pad 12*/
  (uint16)43, 
  /* Index to address the input settings for pad 13*/
  (uint16)46, 
  /* Index to address the input settings for pad 14*/
  (uint16)50, 
  /* Index to address the input settings for pad 15*/
  (uint16)52, 
  /* Index to address the input settings for pad 16*/
  (uint16)56, 
  /* Index to address the input settings for pad 17*/
  (uint16)58, 
  /* Index to address the input settings for pad 18*/
  (uint16)62, 
  /* Index to address the input settings for pad 19*/
  (uint16)63, 
  /* Index to address the input settings for pad 20*/
  (uint16)0, 
  /* Index to address the input settings for pad 21*/
  (uint16)0, 
  /* Index to address the input settings for pad 22*/
  (uint16)64, 
  /* Index to address the input settings for pad 23*/
  (uint16)65, 
  /* Index to address the input settings for pad 24*/
  (uint16)66, 
  /* Index to address the input settings for pad 25*/
  (uint16)0, 
  /* Index to address the input settings for pad 26*/
  (uint16)0, 
  /* Index to address the input settings for pad 27*/
  (uint16)0, 
  /* Index to address the input settings for pad 28*/
  (uint16)0, 
  /* Index to address the input settings for pad 29*/
  (uint16)67, 
  /* Index to address the input settings for pad 30*/
  (uint16)68, 
  /* Index to address the input settings for pad 31*/
  (uint16)70, 
  /* Index to address the input settings for pad 32*/
  (uint16)0, 
  /* Index to address the input settings for pad 33*/
  (uint16)0, 
  /* Index to address the input settings for pad 34*/
  (uint16)0, 
  /* Index to address the input settings for pad 35*/
  (uint16)0, 
  /* Index to address the input settings for pad 36*/
  (uint16)71, 
  /* Index to address the input settings for pad 37*/
  (uint16)73, 
  /* Index to address the input settings for pad 38*/
  (uint16)75, 
  /* Index to address the input settings for pad 39*/
  (uint16)77, 
  /* Index to address the input settings for pad 40*/
  (uint16)0, 
  /* Index to address the input settings for pad 41*/
  (uint16)0, 
  /* Index to address the input settings for pad 42*/
  (uint16)79, 
  /* Index to address the input settings for pad 43*/
  (uint16)81, 
  /* Index to address the input settings for pad 44*/
  (uint16)83, 
  /* Index to address the input settings for pad 45*/
  (uint16)85, 
  /* Index to address the input settings for pad 46*/
  (uint16)89, 
  /* Index to address the input settings for pad 47*/
  (uint16)91, 
  /* Index to address the input settings for pad 48*/
  (uint16)95, 
  /* Index to address the input settings for pad 49*/
  (uint16)97, 
  /* Index to address the input settings for pad 50*/
  (uint16)99, 
  /* Index to address the input settings for pad 51*/
  (uint16)102, 
  /* Index to address the input settings for pad 52*/
  (uint16)104, 
  /* Index to address the input settings for pad 53*/
  (uint16)106, 
  /* Index to address the input settings for pad 54*/
  (uint16)109, 
  /* Index to address the input settings for pad 55*/
  (uint16)113, 
  /* Index to address the input settings for pad 56*/
  (uint16)116, 
  /* Index to address the input settings for pad 57*/
  (uint16)0, 
  /* Index to address the input settings for pad 58*/
  (uint16)119, 
  /* Index to address the input settings for pad 59*/
  (uint16)122, 
  /* Index to address the input settings for pad 60*/
  (uint16)125, 
  /* Index to address the input settings for pad 61*/
  (uint16)0, 
  /* Index to address the input settings for pad 62*/
  (uint16)127, 
  /* Index to address the input settings for pad 63*/
  (uint16)0, 
  /* Index to address the input settings for pad 64*/
  (uint16)0, 
  /* Index to address the input settings for pad 65*/
  (uint16)0, 
  /* Index to address the input settings for pad 66*/
  (uint16)0, 
  /* Index to address the input settings for pad 67*/
  (uint16)0, 
  /* Index to address the input settings for pad 68*/
  (uint16)0, 
  /* Index to address the input settings for pad 69*/
  (uint16)0, 
  /* Index to address the input settings for pad 70*/
  (uint16)0, 
  /* Index to address the input settings for pad 71*/
  (uint16)0, 
  /* Index to address the input settings for pad 72*/
  (uint16)0, 
  /* Index to address the input settings for pad 73*/
  (uint16)0, 
  /* Index to address the input settings for pad 74*/
  (uint16)0, 
  /* Index to address the input settings for pad 75*/
  (uint16)0, 
  /* Index to address the input settings for pad 76*/
  (uint16)0, 
  /* Index to address the input settings for pad 77*/
  (uint16)130, 
  /* Index to address the input settings for pad 78*/
  (uint16)133, 
  /* Index to address the input settings for pad 79*/
  (uint16)136, 
  /* Index to address the input settings for pad 80*/
  (uint16)138, 
  /* Index to address the input settings for pad 81*/
  (uint16)0, 
  /* Index to address the input settings for pad 82*/
  (uint16)0, 
  /* Index to address the input settings for pad 83*/
  (uint16)0, 
  /* Index to address the input settings for pad 84*/
  (uint16)0, 
  /* Index to address the input settings for pad 85*/
  (uint16)141, 
  /* Index to address the input settings for pad 86*/
  (uint16)0, 
  /* Index to address the input settings for pad 87*/
  (uint16)0, 
  /* Index to address the input settings for pad 88*/
  (uint16)0, 
  /* Index to address the input settings for pad 89*/
  (uint16)0, 
  /* Index to address the input settings for pad 90*/
  (uint16)0, 
  /* Index to address the input settings for pad 91*/
  (uint16)0, 
  /* Index to address the input settings for pad 92*/
  (uint16)142, 
  /* Index to address the input settings for pad 93*/
  (uint16)145, 
  /* Index to address the input settings for pad 94*/
  (uint16)0, 
  /* Index to address the input settings for pad 95*/
  (uint16)148, 
  /* Index to address the input settings for pad 96*/
  (uint16)0, 
  /* Index to address the input settings for pad 97*/
  (uint16)0, 
  /* Index to address the input settings for pad 98*/
  (uint16)150, 
  /* Index to address the input settings for pad 99*/
  (uint16)151, 
  /* Index to address the input settings for pad 100*/
  (uint16)153, 
  /* Index to address the input settings for pad 101*/
  (uint16)155, 
  /* Index to address the input settings for pad 102*/
  (uint16)156, 
  /* Index to address the input settings for pad 103*/
  (uint16)157, 
  /* Index to address the input settings for pad 104*/
  (uint16)158, 
  /* Index to address the input settings for pad 105*/
  (uint16)162, 
  /* Index to address the input settings for pad 106*/
  (uint16)165, 
  /* Index to address the input settings for pad 107*/
  (uint16)167, 
  /* Index to address the input settings for pad 108*/
  (uint16)0, 
  /* Index to address the input settings for pad 109*/
  (uint16)0, 
  /* Index to address the input settings for pad 110*/
  (uint16)0, 
  /* Index to address the input settings for pad 111*/
  (uint16)0, 
  /* Index to address the input settings for pad 112*/
  (uint16)0, 
  /* Index to address the input settings for pad 113*/
  (uint16)0, 
  /* Index to address the input settings for pad 114*/
  (uint16)0, 
  /* Index to address the input settings for pad 115*/
  (uint16)0, 
  /* Index to address the input settings for pad 116*/
  (uint16)169, 
  /* Index to address the input settings for pad 117*/
  (uint16)171, 
  /* Index to address the input settings for pad 118*/
  (uint16)173, 
  /* Index to address the input settings for pad 119*/
  (uint16)174, 
  /* Index to address the input settings for pad 120*/
  (uint16)175, 
  /* Index to address the input settings for pad 121*/
  (uint16)177, 
  /* Index to address the input settings for pad 122*/
  (uint16)178, 
  /* Index to address the input settings for pad 123*/
  (uint16)179, 
  /* Index to address the input settings for pad 124*/
  (uint16)180, 
  /* Index to address the input settings for pad 125*/
  (uint16)181, 
  /* Index to address the input settings for pad 126*/
  (uint16)182, 
  /* Index to address the input settings for pad 127*/
  (uint16)183, 
  /* Index to address the input settings for pad 128*/
  (uint16)184, 
  /* Index to address the input settings for pad 129*/
  (uint16)186, 
  /* Index to address the input settings for pad 130*/
  (uint16)189, 
  /* Index to address the input settings for pad 131*/
  (uint16)191, 
  /* Index to address the input settings for pad 132*/
  (uint16)0, 
  /* Index to address the input settings for pad 133*/
  (uint16)0, 
  /* Index to address the input settings for pad 134*/
  (uint16)193, 
  /* Index to address the input settings for pad 135*/
  (uint16)194, 
  /* Index to address the input settings for pad 136*/
  (uint16)195, 
  /* Index to address the input settings for pad 137*/
  (uint16)196, 
  /* Index to address the input settings for pad 138*/
  (uint16)197, 
  /* Index to address the input settings for pad 139*/
  (uint16)198, 
  /* Index to address the input settings for pad 140*/
  (uint16)199, 
  /* Index to address the input settings for pad 141*/
  (uint16)0, 
  /* Index to address the input settings for pad 142*/
  (uint16)200, 
  /* Index to address the input settings for pad 143*/
  (uint16)201, 
  /* Index to address the input settings for pad 144*/
  (uint16)0, 
  /* Index to address the input settings for pad 145*/
  (uint16)202, 
  /* Index to address the input settings for pad 146*/
  (uint16)0, 
  /* Index to address the input settings for pad 147*/
  (uint16)0, 
  /* Index to address the input settings for pad 148*/
  (uint16)203, 
  /* Index to address the input settings for pad 149*/
  (uint16)204, 
  /* Index to address the input settings for pad 150*/
  (uint16)205, 
  /* Index to address the input settings for pad 151*/
  (uint16)0, 
  /* Index to address the input settings for pad 152*/
  (uint16)206, 
  /* Index to address the input settings for pad 153*/
  (uint16)209
};
#endif

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_CFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_CFG_REF_3 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"
/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/
#define PORT_START_SEC_CODE
/**
* @violates @ref PORT_CFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_CFG_REF_3 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/
#define PORT_STOP_SEC_CODE
/**
* @violates @ref PORT_CFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_CFG_REF_3 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#endif    /* PORT_PRECOMPILE_SUPPORT*/

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
