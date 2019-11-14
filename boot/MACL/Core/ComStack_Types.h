/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Core/project.pj $
        $RCSfile: ComStack_Types.h $
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
*   @file           ComStack_Types.h
*   @implements     ComStack_Types.h_Artifact
*   @version 1.0.0
*
*   @brief   AUTOSAR Base - Communication stack types header file.
*   @details AUTOSAR communication stack type header file.
*            This file contains sample code only. It is not part of the production code deliverables
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


#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section ComStack_Types_h_REF_1
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers.
*/
/*==================================================================================================
*                                         INCLUDE FILES
==================================================================================================*/

#include "Std_Types.h"
#include "ComStack_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** 
* @brief Parameters that shall be published within the standard types header file and also in the 
*        module's description file
*/
#define COMTYPE_VENDOR_ID                    43
/*
 * @violates @ref ComStack_Types_h_REF_1 This is required as per autosar Requirement, 
 */
#define COMTYPE_AR_RELEASE_MAJOR_VERSION     4
/*
 * @violates @ref ComStack_Types_h_REF_1 This is required as per autosar Requirement, 
 */
#define COMTYPE_AR_RELEASE_MINOR_VERSION     0
/*
 * @violates @ref ComStack_Types_h_REF_1 This is required as per autosar Requirement, 
 */
#define COMTYPE_AR_RELEASE_REVISION_VERSION  3
#define COMTYPE_SW_MAJOR_VERSION             1
#define COMTYPE_SW_MINOR_VERSION             0
#define COMTYPE_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Std_Types.h header file are of the same Autosar version */
    #if ((COMTYPE_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         (COMTYPE_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of ComStack_Types.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief  Action has been successfully finished 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_OK           0x00

/**
* @brief  Message not successfully received or sent out 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_NOT_OK     0x01

/**
* @brief  Timer N_Ar/N_As has passed its time-out value N_Asmax/N_Armax 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_TIMEOUT_A  0x02

/**
* @brief  Timer N_Bs has passed its time-out value N_Bsmax 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_TIMEOUT_BS 0x03

/**
* @brief  Timer N_Cr has passed its time-out value N_Crmax 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_TIMEOUT_CR 0x04

/**
* @brief  Unexpected sequence number (PCI.SN) value received 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_WRONG_SN   0x05

/**
* @brief  Invalid or unknown FlowStatus value has been received 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_INVALID_FS 0x06

/**
* @brief  Unexpected protocol data unit received 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_UNEXP_PDU  0x07

/**
* @brief  Flow control WAIT frame that exceeds the maximum counter N_WFTmax received 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_WFT_OVRN   0x08

/**
* @brief  Flow control (FC) N_PDU with FlowStatus = OVFLW received 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_ABORT  0x09

/**
* @brief  Indicates an abort of a transmission. 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_NO_BUFFER  0x0A

/**
* @brief  Requested cancellation has been executed 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_CANCELATION_OK 0x0B

/**
* @brief  Request cancellation has not been executed
*         Due to an internal error the requested cancelation has not been executed.
*         This will happen e.g. if the to be canceled transmission has been executed already. 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_CANCELATION_NOT_OK 0x0C

/**
* @brief  The parameter change request has been successfully executed
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_PARAMETER_OK  0x0D

/**
* @brief  The request for the change of the parameter did not complete successfully
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_PARAMETER_NOT_OK  0x0E

/**
* @brief  The parameter change request not executed successfully due to an ongoing reception 
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_RX_ON 0x0F

/**
* @brief  The parameter change request not executed successfully due to a wrong value
* @details   General return codes for NotifResultType
*/
#define NTFRSLT_E_VALUE_NOT_OK 0x10

/**
* @brief   There is no bus transceiver error seen or transceiver does not support the detection 
*          of bus errors 
* @details   General return codes for BusTrcvErrorType
*/
#define BUSTRCV_OK           0x00

/**
* @brief  Bus transceiver detected an unclassified error 
* @details   General return codes for BusTrcvErrorType
*/
#define BUSTRCV_E_ERROR      0x01

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/
/** 
* @brief Variables of this type are used to store the result of a buffer request.
* @implements BufReq_ReturnType_enumeration
*/
typedef enum
{
    BUFREQ_OK = 0,         /**< @brief Buffer request accomplished successful */
    BUFREQ_E_NOT_OK = 1,   /**< @brief Buffer request not successful. Buffer cannot be accessed */
    BUFREQ_E_BUSY = 2,     /**< @brief Temporarily no buffer available. It's up the requestor to 
                            *          retry request for a certain time. */
    BUFREQ_E_OVFL = 3      /**< @brief No Buffer of the required length can be provided */
} BufReq_ReturnType;

/** 
* @brief Variables of this type shall be used to store the state of TP buffer.
*/
typedef enum
{
    TP_DATACONF = 0,    /**< @brief Indicates that all data, that have been copied so far, are c
                        *           confirmed and can be removed from the TP buffer. */
    TP_DATARETRY = 1,   /**< @brief Indicates that this API call shall copy already copied data in 
                        *           order to recover from an error */
    TP_CONFPENDING = 2, /**< @brief Indicates that the previously copied data must remain in the TP 
                        */
    TP_NORETRY = 3      /**< @brief Indicate that the copied transmit data can be removed from the 
                        *           buffer after it has been copied */
} TpDataStateType;

/** 
* @brief Specify the parameter to which the value has to be changed (BS or STmin)
* @implements TPParameterType_enumeration
*/
typedef enum
{
    TP_STMIN = 0,    /**< @brief Separation Time */
    TP_BS = 1,       /**< @brief Block Size */
    TP_BC = 2        /**<Band width control parameter used in FlexRay transport protocol module */
} TPParameterType;



/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** 
* @brief Variables of this type are used to store the result status of a notification (confirmation 
*        or indication).
* @implements NotifResultType_enumeration
*/
typedef uint8        NotifResultType;

/** 
* @brief Variables of this type are used to return the bus status evaluated by a transceiver.
* @implements BusTrcvErrorType_enumeration
*/
typedef uint8        BusTrcvErrorType; 

/** 
* @brief   Variables of the type NetworkHandleType are used to store the identifier 
*          of a communication channel.
* @implements NetworkHandleType_type
*/
typedef uint8        NetworkHandleType;  

/** 
* @brief   Variables of the type PNCHandleType used to store the identifier of a partial network
*          cluster.
* @implements PNCHandleType_type
*/
typedef uint8        PNCHandleType;

/** 
* @brief Variables of this type are used to store the basic information about a PDU of any type,
*        namely a pointer variable pointing to it's SDU (payload), and the corresponding length 
*        of the SDU in bytes.
* @implements PduInfoType_structure
*/
typedef struct
{
    P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SduDataPtr;   /**< pointer to the SDU (i.e. 
                                                                *    payload data) of the PDU */
    PduLengthType  SduLength;                                   /**< length of the SDU in bytes */
} PduInfoType;

/** 
* @brief Variables of this type shall be used to store the information about Tp buffer handling.
* @implements RetryInfoType_structure
*/
typedef struct
{
    TpDataStateType TpDataState;   /**< The enum type to be used to store the state of Tp buffer */
    PduLengthType  TxTpDataCnt;    /**< length of the SDU in bytes */
} RetryInfoType;


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* COMSTACK_TYPES_H */

/** @} */
