/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: comms.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:49CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/


/******************************************************************************
*
*   INCLUDE FILES
*
******************************************************************************/
#include "Std_Types.h"
#include "types.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "Can_Cfg.h"
#include "comms.h"
#include "can_app_if.h"
#include "bootstrp.h"  /* for T_REPROG_INFO_TYPE */
#include "ccppar.h"
#include "ccp.h"

#include "tp15765.h"  /* To access tp_cyclic_task() */
#include "mcu_dch.h"  /* To access ubTaskScheduler */
#include "uds_prog.h" /* To access UDS_DiagServiceHandler(), UDS_DiagContinueProgramming()*/


/******************************************************************************
*
*   Macro DECLARATIONS
*
******************************************************************************/
#define CAN_DIAG_REQ_LENGTH				   0x08U

/******************************************************************************
*
*   PRIVATE VARIABLE DECLARATIONS
*
******************************************************************************/
static U32 Comms_ms_count  = 0U;
static U8  ubUdsSchedCount = 0U;



/******************************************************************************
*
*   CODE
*
******************************************************************************/

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Comms_Init

DESCRIPTION:
    Performs power on initialization steps in Communication Subsystem.
    This function shall be called from the startup hook before before operatings-system
    periodic scheduler is started.

*******************************************************************************/
void Comms_Init(void)
{
    ubUdsSchedCount = 0;

    UDS_DiagInit();
    tp_init();
}


/****************************************************************************/
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*      Task scheduler call every 0.5ms                                     */
/*                                                                          */
/****************************************************************************/
void basic_scheduler(void)
{
    /* Condition true all 1ms */
    if(TRUE == ubTaskScheduler)
    {
        ubTaskScheduler = FALSE;

        Comms_ms_count++;

        if(ubUdsSchedCount >= 2)
        {
            ubUdsSchedCount = 0;
            tp_cyclic_task();
            UDS_DiagServiceHandler(); /*UDS service handler*/
            UDS_DiagContinueProgramming();
        }
        else
        {
            ubUdsSchedCount++;
        }
    }
}

/**************************   CPP interface    *******************************/



/*****************************************************************************
                              FUNCTION INFO
NAME:
    can_pl_process_ccp_msg

DESCRIPTION:

*******************************************************************************/

void can_pl_process_ccp_msg (Can_PduType const *pdu)
{
    U8 i;

    for (i=0;i<8;i++)
    {
        /* DEVIATION:     0491
           DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
           JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
        */
        /* PRQA S 0491 1*/
        CCP_RxData[i] = pdu->sdu[i];
    }

    ccpCommand(CCP_RxData);
}


/*****************************************************************************
                              FUNCTION INFO
NAME:
    Comms_Send_CAN_message

DESCRIPTION:

*******************************************************************************/
/*  DEVIATION:     0491
    DESCRIPTION:   Array subscripting applied to an object of pointer type.
    JUSTIFICATION: There was used array notation to an object of pointer.
                   It works well and it is clarity to read.
*/
/* PRQA S 0491 30 */
Can_ReturnType Comms_Send_CAN_message( U8 tx_handle, U8* data)
{
    Can_PduType pdu;
    Can_ReturnType result;

    U8 hth ;

    hth = (tx_handle + NO_OF_CAN_RX_MSGS);  /* hth corresponds to the mail box id */


    /* DEVIATION:     0491
       DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
       JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
    */
    /* PRQA S 0491 1*/
    pdu.id           = (Can_IdType)((Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr)[hth].uMessageId);

    pdu.length       = 8;
    pdu.swPduHandle  = tx_handle;
    pdu.sdu          = data;

    result =   Can_Write((Can_HwHandleType)hth,&pdu);

    return(result);
}

/**************************   UDS interface    *******************************/



Can_ReturnType Comms_Tx_UDS1_Message(U8* data_pu8, U8 dlc_u8)
{
    Can_PduType pdu;
    Can_ReturnType comms_tx_retval;
    U8   hth ;

    hth = (UDS_DIAG_TX + NO_OF_CAN_RX_MSGS);  /* hth corresponds to the mail box id */

    /* DEVIATION:     0491
       DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
       JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
    */
    /* PRQA S 0491 1*/
    pdu.id = (Can_IdType)((Can_pCurrentConfig->MBConfigContainer.pMessageBufferConfigsPtr)[hth].uMessageId);

    pdu.length       = dlc_u8;
    pdu.swPduHandle  = UDS_DIAG_TX;
    pdu.sdu          = data_pu8;

    comms_tx_retval =   Can_Write((Can_HwHandleType)hth,&pdu);

    return comms_tx_retval;

}


void Comms_Process_UDS1_Message(Can_PduType const *pdu)
{
    U8      rxBuf_u8[8];
    U8      indexRxbuf_u8;

    /*Extraction of data bytes*/
    for(indexRxbuf_u8=0;indexRxbuf_u8<8;indexRxbuf_u8++)
    {
        /* DEVIATION:     0491
           DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
           JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
        */
        /* PRQA S 0491 1*/
        rxBuf_u8[indexRxbuf_u8] = pdu->sdu[indexRxbuf_u8];
    }
    if(CAN_DIAG_REQ_LENGTH == (pdu->length))
    {
    	tp_rx_dtool_to_ACC_message(rxBuf_u8, pdu->length);
    }
    else
    {
    	;
    }
}


void Comms_Process_UDS2_Message(Can_PduType const *pdu)
{
    U8      rxBuf_u8[8];
    U8      indexRxbuf_u8;

    /*Extraction of data bytes*/
    for(indexRxbuf_u8=0;indexRxbuf_u8<8;indexRxbuf_u8++)
    {
        /* DEVIATION:     0491
           DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
           JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
        */
        /* PRQA S 0491 1*/
        rxBuf_u8[indexRxbuf_u8] = pdu->sdu[indexRxbuf_u8];
    }

    if(CAN_DIAG_REQ_LENGTH == (pdu->length))
    {
    	tp_rx_dtool_to_all_message(rxBuf_u8, pdu->length);
    }
    else
    {
    	;
    }

}


void Comms_Send_UDS1_Message(void)
{
    if (TPTransactionInProgress_bo == FALSE)
    {
        UDS_Send_Msg_Complete();
    }
    return;
}


/*****************************************************************************
                              FUNCTION INFO
NAME:
    COMMS_Get_Millisecond_Count

DESCRIPTION:
    Time since system power on in milliseconds

*******************************************************************************/
U32 COMMS_Get_Millisecond_Count ( void )
{
    return (Comms_ms_count);
}

