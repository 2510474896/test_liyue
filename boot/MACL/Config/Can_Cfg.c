/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: Can_Cfg.c $
        $Revision: 1.2 $
        $Date: 2019/08/21 18:16:56CST $

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
*   @file    Can_Cfg.c
*   @version 1.0.0
*
*   @brief   AUTOSAR Can - module interface
*   @details Configuration Structures for PreCompile.
*
*   @addtogroup CAN_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : FLEXCAN
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : MPC57xxP_MCAL_1_0_0_RTM_HF3_ASR_REL_4_0_REV_0003_20151120
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
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Can_Cfg_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Can_Cfg_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Can_Cfg_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Can_Cfg_c_REF_5
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_Cfg_c_REF_4
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can.h"
#include "Can_IPW.h"

/**
* @file           Can_Cfg.c
*/



/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CAN_VENDOR_ID_PCCFG_C                   43
/* @violates @ref Can_Cfg_c_REF_3 Violates MISRA 2004 Rule 1.4, Identifier clash */
#define CAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C     4
/* @violates @ref Can_Cfg_c_REF_3 Violates MISRA 2004 Rule 1.4, Identifier clash */
#define CAN_AR_RELEASE_MINOR_VERSION_PCCFG_C     0
/* @violates @ref Can_Cfg_c_REF_3 Violates MISRA 2004 Rule 1.4, Identifier clash */
#define CAN_AR_RELEASE_REVISION_VERSION_PCCFG_C  3
#define CAN_SW_MAJOR_VERSION_PCCFG_C             1
#define CAN_SW_MINOR_VERSION_PCCFG_C             0
#define CAN_SW_PATCH_VERSION_PCCFG_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (CAN_PRECOMPILE_SUPPORT == STD_ON)


/* Check if current file and Can configuration header file are of the same vendor */
#if (CAN_VENDOR_ID_PCCFG_C != CAN_VENDOR_ID)
#error "Can.h and Can_Cfg.h have different vendor ids"
#endif
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C != CAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_AR_RELEASE_MINOR_VERSION_PCCFG_C != CAN_AR_RELEASE_MINOR_VERSION) || \
     (CAN_AR_RELEASE_REVISION_VERSION_PCCFG_C != CAN_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Can_Cfg.c and Can.h are different"
#endif
/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_PCCFG_C != CAN_SW_MAJOR_VERSION) || \
     (CAN_SW_MINOR_VERSION_PCCFG_C != CAN_SW_MINOR_VERSION) || \
     (CAN_SW_PATCH_VERSION_PCCFG_C != CAN_SW_PATCH_VERSION))
       #error "Software Version Numbers of Can_Cfg.c and Can.h are different"
#endif

/* Check if current file and Can_IPW configuration header file are of the same vendor */
#if (CAN_VENDOR_ID_PCCFG_C  != CAN_IPW_VENDOR_ID_H)
#error "Can.h and Can_Cfg.h have different vendor ids"
#endif
/* Check if current file and CAN_IPW header file are of the same Autosar version */
#if ((CAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C != CAN_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_AR_RELEASE_MINOR_VERSION_PCCFG_C != CAN_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_AR_RELEASE_REVISION_VERSION_PCCFG_C != CAN_IPW_AR_RELEASE_REVISION_VERSION_H))
  #error "AutoSar Version Numbers of Can_Cfg.c and Can.h are different"
#endif
/* Check if current file and CAN_IPW header file are of the same Software version */
#if ((CAN_SW_MAJOR_VERSION_PCCFG_C != CAN_IPW_SW_MAJOR_VERSION_H) || \
     (CAN_SW_MINOR_VERSION_PCCFG_C != CAN_IPW_SW_MINOR_VERSION_H) || \
     (CAN_SW_PATCH_VERSION_PCCFG_C != CAN_IPW_SW_PATCH_VERSION_H))
       #error "Software Version Numbers of Can_Cfg.c and Can.h are different"
#endif


/*==================================================================================================
*                                   GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Can_Cfg_c_REF_2 MISRA 2004 Rule 19.15, Repeated include file MemMap.h  */
#include "MemMap.h"

/**
* @brief    Prototype of User Notifications
*/






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









/*==================================================================================================*/
/**
* @brief          Filter Masks
* @details        Filter Masks
*
*/
static CONST(Can_IdType, CAN_CONST) Can_FilterMasks_PC[CAN_MAXFILTERCOUNT_0] =
    {   
        /* FilterMasks_PC[0], "CanFilterMask_0" */
        (Can_IdType)0x7ffU,
        /* FilterMasks_PC[1], "CanFilterMask_0" */
        (Can_IdType)0x7ffU
    };


/*==================================================================================================*/
/**
* @brief          Information about message buffers
* @details        (CAN100)Several TX hardware objects with unique HTHs may be configured. The CanIf module provides the HTH as parameter of the TX request. See Figure 7-2 for a possible configuration.
*
*/
static CONST(Can_MBConfigObjectType, CAN_CONST) MessageBufferConfigs_PC[CAN_MAXMBCOUNT_0] =
    {
        
        
        /* CCP_REQUEST_Box_Index Message Buffer of Can Controller ID = 0U */
        {
            /* uIdMaskIndex */
            (Can_HwHandleType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)CAN_STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)CAN_RECEIVE,
            /* MessageId */
            (Can_IdType)0x7beU,
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HwHandleType)0x0U,
            /* Read/Write period reference used when polling mode is selected for the controller */
            (uint8)0U/* HOH reference is from CanMainFunctionRWPeriods_0 */
        },
        
        
        /* HS2_REQ_DIAG_ON_CAN_6B6 Message Buffer of Can Controller ID = 0U */
        {
            /* uIdMaskIndex */
            (Can_HwHandleType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)CAN_STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)CAN_RECEIVE,
            /* MessageId */
            (Can_IdType)0x7C3U,								/*Changed to 0x7C3 from 0x6B6 for X37 project*/
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HwHandleType)0x1U,
            /* Read/Write period reference used when polling mode is selected for the controller */
            (uint8)0U/* HOH reference is from CanMainFunctionRWPeriods_0 */
        },
        
        
        /* HS2_REQ_DIAG_ON_CAN_BROADCAST Message Buffer of Can Controller ID = 0U */
        {
            /* uIdMaskIndex */
            (Can_HwHandleType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)CAN_STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)CAN_RECEIVE,
            /* MessageId */
            (Can_IdType)0x7DFU,								/*Changed to 0x7DF from 0x7FF for X37 project*/
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HwHandleType)0x2U,
            /* Read/Write period reference used when polling mode is selected for the controller */
            (uint8)0U/* HOH reference is from CanMainFunctionRWPeriods_0 */
        },
        
        
        /* HS2_REP_DIAG_ON_CAN_696 Message Buffer of Can Controller ID = 0U */
        {
            /* uIdMaskIndex */
            (Can_HwHandleType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)CAN_STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)CAN_TRANSMIT,
            /* MessageId */
            (Can_IdType)0x7CBU,								/*Changed to 0x7CB from 0x696 for X37 project*/
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HwHandleType)0x3U,
            /* Read/Write period reference used when polling mode is selected for the controller */
            (uint8)0U/* HOH reference is from CanMainFunctionRWPeriods_0 */
        },
        
        
        /* CCP_RESPONSE_Box_Index Message Buffer of Can Controller ID = 0U */
        {
            /* uIdMaskIndex */
            (Can_HwHandleType)0U,
            /* ControllerId  - based on the order from CanController list */
            (uint8)0U,
            /* ID type: EXTENDED, STANDARD, MIXED */
            (CanIdType)CAN_STANDARD,
            /* Receive/Transmit MB configuration */
            (Can_ObjType)CAN_TRANSMIT,
            /* MessageId */
            (Can_IdType)0x7bfU,
            /* Local priority bits used for arbitration */
            (uint8)0x0U,
            /* Hardware Object ID */
            (Can_HwHandleType)0x4U,
            /* Read/Write period reference used when polling mode is selected for the controller */
            (uint8)0U/* HOH reference is from CanMainFunctionRWPeriods_0 */
        }
        
    };


/*==================================================================================================*/
/**
* @brief          Configuration of FlexCan controller
* @details        Configuration of FlexCan controller
*
*/

static CONST(Can_ControllerBaudrateConfigType, CAN_CONST) ControllerBaudrateConfigs_PC_0[CAN_CFGSET0_MAX_BAUDRATE_FC_A_0] = {
    
    /*
        =================================================

        Clock Size = 4.0E7 Hz  - Clock from external OSC.
        
        Clock Prescaler = 8 (1..256)
        
        CanBitRate = 500 Kbps (1bps..1Mbps)
        Number CANTimeQuantas per bit = 10 (8..25)
        
        CTRL Register Fields:
            PSEG1 = 0 (0..7)
            PSEG2 = 1 (1..7)
            PROPSEG = 5 (0..7)
            RJW = 1 (0..3)
        =================================================
    */
    
    /* Configuration for CanController ID0 == FlexCAN_A */
    {
      /* ===== Control Register - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)(((uint32)7 << FLEXCAN_CTRL_PRESDIV_SHIFT_U8) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        ((uint32)1 << FLEXCAN_CTRL_RJW_SHIFT_U8) |
        /* CTRL[PSEG1] - Segment 1 */
        ((uint32)0U << FLEXCAN_CTRL_PSEG1_SHIFT_U8) |
        /* CTRL[PSEG2] - Segment 2 */
        ((uint32)1U << FLEXCAN_CTRL_PSEG2_SHIFT_U8) |
        ((uint32)0 << FLEXCAN_CTRL_CLKSRC_SHIFT_U8) |
        /* CTRL[LPB] - Loop-back mode */
        ((uint32)0 << FLEXCAN_CTRL_LPB_SHIFT_U8) |
        /* CTRL[SMP] - Sampling mode */
        ((uint32)0 << FLEXCAN_CTRL_SMP_SHIFT_U8) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        ((uint32)0 << FLEXCAN_CTRL_BOFFREC_SHIFT_U8) |
        /* CTRL[LBUF] - Lowest Buffer Transmitted First */
        ((uint32)0 << FLEXCAN_CTRL_LBUF_SHIFT_U8) |
        /* CTRL[LOM] - Listen only mode */
        ((uint32)0 << FLEXCAN_CTRL_LOM_SHIFT_U8) |
        /* CTRL[PROPSEG] - Propagation segment */
        (uint32)5) ,

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
        0U,
    
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

        (uint16)500   /* 500kbps baud rate */
    }
    
  };

static CONST(Can_ControllerBaudrateConfigType, CAN_CONST) ControllerBaudrateConfigs_PC_1[CAN_CFGSET0_MAX_BAUDRATE_FC_B_1] = {
    
    /*
        =================================================

        Clock Size = 4.0E7 Hz  - Clock from external OSC.
        
        Clock Prescaler = 8 (1..256)
        
        CanBitRate = 500 Kbps (1bps..1Mbps)
        Number CANTimeQuantas per bit = 10 (8..25)
        
        CTRL Register Fields:
            PSEG1 = 0 (0..7)
            PSEG2 = 1 (1..7)
            PROPSEG = 5 (0..7)
            RJW = 1 (0..3)
        =================================================
    */
    
    /* Configuration for CanController ID1 == FlexCAN_B */
    {
      /* ===== Control Register - CTRL ===== */
        /* CTRL[PRESDIV] - Clock Prescaler */
        (uint32)(((uint32)7 << FLEXCAN_CTRL_PRESDIV_SHIFT_U8) |
        /* CTRL[RJW] - Resynchronization Jump Width */
        ((uint32)1 << FLEXCAN_CTRL_RJW_SHIFT_U8) |
        /* CTRL[PSEG1] - Segment 1 */
        ((uint32)0U << FLEXCAN_CTRL_PSEG1_SHIFT_U8) |
        /* CTRL[PSEG2] - Segment 2 */
        ((uint32)1U << FLEXCAN_CTRL_PSEG2_SHIFT_U8) |
        ((uint32)0 << FLEXCAN_CTRL_CLKSRC_SHIFT_U8) |
        /* CTRL[LPB] - Loop-back mode */
        ((uint32)0 << FLEXCAN_CTRL_LPB_SHIFT_U8) |
        /* CTRL[SMP] - Sampling mode */
        ((uint32)0 << FLEXCAN_CTRL_SMP_SHIFT_U8) |
        /* CTRL[BOFF_REC] - Bus off recovery */
        ((uint32)0 << FLEXCAN_CTRL_BOFFREC_SHIFT_U8) |
        /* CTRL[LBUF] - Lowest Buffer Transmitted First */
        ((uint32)0 << FLEXCAN_CTRL_LBUF_SHIFT_U8) |
        /* CTRL[LOM] - Listen only mode */
        ((uint32)0 << FLEXCAN_CTRL_LOM_SHIFT_U8) |
        /* CTRL[PROPSEG] - Propagation segment */
        (uint32)5) ,

#if (CAN_DUAL_CLOCK_MODE == STD_ON)
        0U,
    
#endif /* CAN_DUAL_CLOCK_MODE == STD_ON */

        (uint16)500   /* 500kbps baud rate */
    }
    
  };

/*==================================================================================================*/
/**
* @brief          Description of individual FlexCan controllers on chip
* @details        Description of individual FlexCan controllers on chip
*
*/
static CONST(Can_ControlerDescriptorType, CAN_CONST) ControlerDescriptors_PC[CAN_MAXCONTROLLERCOUNT_0] =
    {
        
        /* ControlerDescriptor of CanController_0 */
        {
            /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. */
            (uint8)FLEXCAN_A_OFFSET,

            /* No. of Message Buffers for current controller. If RxFifo enabled will contains also the space of 8 MBs reserved for this. */
            
            (uint8)5U,
            
            /* No. of BaudRate configured for current controller */
            (uint8)1U,
            
            /* Default BaudRate configured for current controller */
            (uint8)0U,

            /* pControllerBaudrateConfigsPtr */
            ControllerBaudrateConfigs_PC_0,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* WakeUp source ID (ECU State Manager) */
            (uint32)0U, /* EcuM source not used */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /*Rx Fifo Global mask value*/
            (Can_IdType)0U,
            
            /* Number of MBs used by Rx Fifo */
            (uint8)0U,

            /* Pointer to RxFifo Overflow notification function. */         
            NULL_PTR,

            /* Pointer to RxFifo Warning notification function. */            
            NULL_PTR,
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
#if ((CAN_ERROR_NOTIFICATION_ENABLE == STD_ON) && (CPU_BYTE_ORDER==HIGH_BYTE_FIRST))
     /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
            NULL_PTR,             
#elif(CPU_BYTE_ORDER==LOW_BYTE_FIRST) /* (CAN_ERROR_NOTIFICATION_ENABLE == STD_ON) */
         /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
            NULL_PTR,          
#endif

      /* ===== Controller Options ===== */
        (uint32)(
        
         /* RX Fifo Disabled */ 
        /* Local Priority Feature */
        CAN_CONTROLLERCONFIG_LPRIO_EN_U32 | 
        
         /* Error interrupt */ 

        /* RxPoll Enabled */
        CAN_CONTROLLERCONFIG_RXPOL_EN_U32 | 
        /* TxPoll Enabled */
        CAN_CONTROLLERCONFIG_TXPOL_EN_U32 | 
        /* BusOff select by interrupt */
        CAN_CONTROLLERCONFIG_WKPOL_EN_U32 |/* Wakeup Support Disabled */
        
        0U),
#if (CAN_MIX_MB_SUPPORT == STD_ON)
        /* Maximum MBs supported for this controller. */
        
           (uint8)32U
        
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
        },
        
        /* ControlerDescriptor of CanController_1 */
        {
            /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. */
            (uint8)FLEXCAN_B_OFFSET,

            /* No. of Message Buffers for current controller. If RxFifo enabled will contains also the space of 8 MBs reserved for this. */
            
            (uint8)0U,
            
            /* No. of BaudRate configured for current controller */
            (uint8)1U,
            
            /* Default BaudRate configured for current controller */
            (uint8)0U,

            /* pControllerBaudrateConfigsPtr */
            ControllerBaudrateConfigs_PC_1,

#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* WakeUp source ID (ECU State Manager) */
            (uint32)0U, /* EcuM source not used */
#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_RXFIFO_ENABLE == STD_ON)
            /*Rx Fifo Global mask value*/
            (Can_IdType)0U,
            
            /* Number of MBs used by Rx Fifo */
            (uint8)0U,

            /* Pointer to RxFifo Overflow notification function. */         
            NULL_PTR,

            /* Pointer to RxFifo Warning notification function. */            
            NULL_PTR,
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
#if ((CAN_ERROR_NOTIFICATION_ENABLE == STD_ON) && (CPU_BYTE_ORDER==HIGH_BYTE_FIRST))
     /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
            NULL_PTR,             
#elif(CPU_BYTE_ORDER==LOW_BYTE_FIRST) /* (CAN_ERROR_NOTIFICATION_ENABLE == STD_ON) */
         /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
            NULL_PTR,          
#endif

      /* ===== Controller Options ===== */
        (uint32)(
        
         /* RX Fifo Disabled */ 
        /* Local Priority Feature */
        CAN_CONTROLLERCONFIG_LPRIO_EN_U32 | 
        
         /* Error interrupt */ 

        /* RxPoll Enabled */
        CAN_CONTROLLERCONFIG_RXPOL_EN_U32 | 
        /* TxPoll Enabled */
        CAN_CONTROLLERCONFIG_TXPOL_EN_U32 | 
        /* BusOff select by interrupt */
        CAN_CONTROLLERCONFIG_WKPOL_EN_U32 |/* Wakeup Support Disabled */
        
        0U),
#if (CAN_MIX_MB_SUPPORT == STD_ON)
        /* Maximum MBs supported for this controller. */
        
           (uint8)32U
        
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
        }
        

    };



/*==================================================================================================*/
/**
* @brief          Top level structure containing all Can driver configurations
* @details        Top level structure containing all Can driver configurations
*
*/

/* @violates @ref Can_Cfg_c_REF_4 Violates MISRA 2004 Required Rule 8.10*/
CONST(Can_ConfigType, CAN_CONST) Can_ConfigSet_PC =
    {
        /* Number of CAN controllers configured */
        (uint8)2U,

        /* pFilterMasks */
        Can_FilterMasks_PC,

        /* MessageBufferConfigContainer */
        {
            /* pMessageBufferConfigsPtr */
            MessageBufferConfigs_PC,

            /* uMessageBufferConfigCount */
            (Can_HwHandleType)5U,
        },

        /* FlexCAN controller description */
        ControlerDescriptors_PC,

#if (CAN_RXFIFO_ENABLE == STD_ON)
        /* Can_RxFiFoTableIdConfigType */
        NULL_PTR, /* Rx fifo disabled */
#endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */



        /*Maximum Object IDs configured */
        (uint32)5U,

        /*Controller ID mapping*/
        {0U,0U,0U,0U,0U},

        /*Object Type mapping*/
        {(Can_ObjType)CAN_RECEIVE
                ,(Can_ObjType)CAN_RECEIVE
                ,(Can_ObjType)CAN_RECEIVE
                ,(Can_ObjType)CAN_TRANSMIT
                ,(Can_ObjType)CAN_TRANSMIT
                }


    };

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*
@file Can_Cfg.c
@note Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. - See @ref Can_Cfg_c_REF_1
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h - See @ref Can_Cfg_c_REF_2
*/
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Can_Cfg_c_REF_2 MISRA 2004 Rule 19.15, Repeated include file MemMap.h  */
/* @violates @ref Can_Cfg_c_REF_1 MISRA 2004  Rule 19.1, #include preceded by non preproc directives.*/
#include "MemMap.h"

#endif /*CAN_PRECOMPILE_SUPPORT == STD_ON*/

#ifdef __cplusplus
}
#endif

/** @} */
