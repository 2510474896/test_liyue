/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/DIAG/project.pj $
        $RCSfile: tp15765.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:51CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/


/***************************************************************************
*
*   Deviations from QAC - global
*
****************************************************************************/

/* DEVIATION:     0492
   DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
   JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
*/
/* PRQA S 0492 ++ */

/***************************************************************************/


/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

#define TP                 /* defines this file    */
#define DIAG_SUBSYSTEM     /* defines the subsystem that this file resides in  */


/**********************************************************************/
/*  Include Files                                                     */
/**********************************************************************/

#include "Std_Types.h"
#include "types.h"
#include "Can.h"
/* To access COMMS_Get_Millisecond_Count() */
#include "comms.h"

#include "uds_prog.h"
#include "tp15765.h"


/**********************************************************************/
/*  Declare Local/Global Data                                         */
/**********************************************************************/
U16 AppRxDataLen_u16 = 0;
U16 TransmitMsgLen_u16 = 0;
U16 TpS3Timer_u16 = 0;
/* valid is FUNCT or PHYS */
U8 RxMessageType_u8 = 0;
BOOLEAN TPMessageReceived_bo = FALSE;
BOOLEAN TPTransactionInProgress_bo = FALSE;

/* TPSegmentedTxInProgress_bo set up after successful sending of FF
   and cleared right after successful sending last CF */
static BOOLEAN TPSegmentedTxInProgress_bo;
static U16 ReceiveDataLength_u16;
static U16 ReceiveBS_u16;
static U16 TpNCSendTimer_u16;
static U16 TpErrorTimer_u16;
static U16 TransmitBS_u16;
static U8 ReceiveSN_u8;
static U8 TransmitSTMin_u8;
static U8 TransmitSN_u8;
static U8 TxFlowControlStatus_u8;
static U8 TpWftMax_u8;
static U8 *AppRxBuffer_pu8;
static U8 *TransmitMsgPtr_pu8;
static U8 TpNCsTimerActive_u8;
static U8 FirstFrameOfTx_u8;
static U8 ReqTxFlowCtrlFr_u8;
static U8 ReqTxConsecutiveFr_u8;
static t_monitor_timer Tp_error_timer_active;
static t_rx_state Tp_receive_state;

U8 UDS_TDS_Received_u8 = FALSE;

/* Function prototypes */
static U8 tp_rx_single_frame (const U8 *rx_frame, U8 canDlc);
static U8 tp_rx_first_frame (const U8 *rx_frame, U8 canDlc);
static U8 tp_rx_consecutive_frame (const U8 *rx_frame, U8 canDlc);
static U8 tp_rx_flow_control_frame (const U8 *rx_frame, U8 canDlc);
static void tp_tx_flow_control_frame (U8 block_size, U8 separation_time);
static void tp_tx_next_data_frame (void);


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_init                                                     */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description:                                                              */
/*      Called at power up from scheduler.                                    */
/*      Initialises the module variables.                                     */
/******************************************************************************/
void tp_init(void)
{
    Tp_receive_state = NEW_MESSAGE;
    Tp_error_timer_active = DISARMED;
    TpNCsTimerActive_u8 = FALSE;
    TPTransactionInProgress_bo = FALSE;
    TPMessageReceived_bo = FALSE;
    TransmitMsgLen_u16 = 0;
    AppRxDataLen_u16 = 0;
    TPSegmentedTxInProgress_bo = FALSE;
}

/******************************************************************************/
/*                                                                            */
/*  Function    : tp_init_send_message                                        */
/*                                                                            */
/*  Parameters  : U8* tx_data - pointer to message buffer to transmit         */
/*                U16 message length - no of data bytes to transmit           */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*       Initiates the transmission of a response message.                    */
/*       Called from the UDS application, initialises variables which control  */
/*       message transmission and requests transmission of the first frame.   */
/*                                                                            */
/******************************************************************************/
void tp_init_send_message(U8 *tx_data, U16 message_length)
{
    TransmitMsgPtr_pu8 = tx_data;
    TransmitMsgLen_u16 = message_length;
    TransmitBS_u16 = 1;
    TransmitSN_u8 = 0;

    /* Request transmission of first frame */
    TPSegmentedTxInProgress_bo = FALSE;
    FirstFrameOfTx_u8 = TRUE;
    ReqTxConsecutiveFr_u8 = TRUE;
}

/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_single_frame                                          */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : 0 == Invalid frame;  1 == Valid frame                       */
/*                                                                            */
/*  Description :                                                             */
/*       Extracts the data from a Single Frame, if frame valid.               */
/*                                                                            */
/******************************************************************************/
static U8 tp_rx_single_frame(const U8 *rx_frame, U8 canDlc)
{
    U8 index_u8;
    U8 sf_dl;
    U8 *dst;

    U8 valid_frame = FALSE;

    /* Deviation 0492 - globally disabled */
    sf_dl = (U8)(rx_frame[0] & N_PCI_DL_MASK);
    if ((sf_dl > 0) && (sf_dl < 8) && (canDlc > sf_dl))
    {
        /*  DEVIATION:     0310
            DESCRIPTION:   Casting to different object pointer type 
            JUSTIFICATION: This casting is required here and cannot be avoided
                           it is analyzed and causes no issues */
        /* PRQA S 0310 1*/
        dst = (U8*)&UDS_data_in.UDS_data.UDS_request_body;        

        for (index_u8 = 1; index_u8 <= sf_dl; index_u8++)
        {
            /* Deviation 0492 - globally disabled */
            *dst = rx_frame[index_u8];
            /*  DEVIATION:     0489
                DESCRIPTION:   Increment or decrement operation performed on pointer.
                JUSTIFICATION: This is done for accessing different elements of the array, 
                               it is anyalyzed and causes no issues*/   
            /* PRQA S 0489 1*/
            dst++;
        }

        AppRxDataLen_u16 = (U16)sf_dl;
        valid_frame = TRUE;
    }

    return valid_frame;
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_first_frame                                           */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : 0 == Invalid frame;  1 == Valid frame                       */
/*                                                                            */
/*  Description :                                                             */
/*       Extracts the data from a First Frame, if frame valid.                */
/*                                                                            */
/******************************************************************************/
static U8 tp_rx_first_frame(const U8 *rx_frame, U8 canDlc)
{
    U8 index_u8;
    U16 ff_dl;
    U8 *dst;
    U8 valid_frame = FALSE;
    static U16 UDSAppRxBufferSize_u16;

    /* Deviation 0492 - globally disabled */
    ff_dl = (((U16)(rx_frame[0] & N_PCI_DL_MASK) * 256) + (U16)rx_frame[1]);

    UDSAppRxBufferSize_u16 = sizeof(UDS_data_in.UDS_data);

    /* For FF legal CAN frame length is 8 bytes */
    if (8 == canDlc)
    {
        /* Input length less than the maximum size of input buffer */
        if (ff_dl <= UDSAppRxBufferSize_u16)
        {
            /* Legal data length? */
            if (ff_dl > 7)
            {
                /*  DEVIATION:     0310
                    DESCRIPTION:   Casting to different object pointer type
                    JUSTIFICATION: This casting is required here and cannot be avoided,
                                   it is analyzed and causes no issues */
                /* PRQA S 0310 1*/
                dst = (U8*)&UDS_data_in.UDS_data.UDS_request_body;

                for (index_u8 = 2; index_u8 < 8; index_u8++)
                {
                    /* Deviation 0492 - globally disabled */
                    *dst = rx_frame[index_u8];
                    /*  DEVIATION:     0489
                        DESCRIPTION:   Increment or decrement operation performed on pointer.
                        JUSTIFICATION: This is done for accessing different elements of the array,
                                       it is analyzed and causes no issues */
                    /* PRQA S 0489 1*/
                    dst++;
                }

                if(rx_frame[2] == TRANSFER_DATA_ID)
                {
                	UDS_TDS_Received_u8 = TRUE;
                }
                else
                {
                	;
                }

                AppRxBuffer_pu8 = dst;
                AppRxDataLen_u16 = 6;
                /* remaining bytes in message */
                ReceiveDataLength_u16 = (ff_dl - 6);

                /* Reset sequence number and request flow control be sent */
                ReceiveSN_u8 = 0;
                ReqTxFlowCtrlFr_u8 = TRUE;
                TxFlowControlStatus_u8 = CONTINUE_TO_SEND;
                valid_frame = TRUE;
            }
        }
        else
        {
            /* Receive buffer overflow indication to the sender */
            ReqTxFlowCtrlFr_u8 = TRUE;
            TxFlowControlStatus_u8 = OVFLW;
        }
    }

    return valid_frame;
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_consecutive_frame                                     */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : 0 == Invalid frame;  1 == Valid frame                       */
/*                                                                            */
/*  Description :                                                             */
/*       Extracts the data from a Consecutive Frame, if frame valid.          */
/*                                                                            */
/******************************************************************************/
static U8 tp_rx_consecutive_frame(const U8 *rx_frame, U8 canDlc)
{
    U8 sn;
    U8 index_u8;
    U8 *dst;
    U8 valid_frame = FALSE;

    /* For last CF DLC should be greater than number of remaining bytes to receipt
       otherwise DLC should be equal to 8 */
    if (((ReceiveDataLength_u16 > 7) && (canDlc == 8)) ||
        ((ReceiveDataLength_u16 < 8) && (canDlc > ReceiveDataLength_u16)))
    {
        /* Deviation 0492 - globally disabled */
        sn = (U8)(rx_frame[0] & N_PCI_SN_MASK);
        /* Next frame in the sequence? */
        if (sn == ((ReceiveSN_u8 + 1) & N_PCI_SN_MASK))
        {
            index_u8 = 1;
            dst = AppRxBuffer_pu8;

            /* Transfer data to the message buffer. */
            do
            {
                /* Receive buffer not overflowed? */
                /* Deviation 0492 - globally disabled */
                *dst = rx_frame[index_u8];
                /*  DEVIATION:     0489
                    DESCRIPTION:   Increment or decrement operation performed on pointer.
                    JUSTIFICATION: This is done for accessing different elements of the array,
                                   it is analyzed and causes no issues */
                /* PRQA S 0489 1*/
                dst++;
                AppRxDataLen_u16++;
                ReceiveDataLength_u16--;
                index_u8++;
            } while ((index_u8 < 8) && (ReceiveDataLength_u16 > 0));

            AppRxBuffer_pu8 = dst;
            ReceiveSN_u8 = sn;

            /* Message not complete? */
            if (ReceiveDataLength_u16 > 0)
            {
                ReceiveBS_u16--;
                /* Not the last block? */
                if (ReceiveBS_u16 > 0)
                {
                    TpErrorTimer_u16 =  (U16)COMMS_Get_Millisecond_Count();
                    Tp_error_timer_active = N_Cr;
                }
                else
                {
                    /* Request another flow control be sent */
                    ReqTxFlowCtrlFr_u8 = TRUE;
                    TxFlowControlStatus_u8 = CONTINUE_TO_SEND;
                }
            }

            valid_frame = TRUE;
        }
    }

    return valid_frame;
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_flow_control_frame                                    */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : 0 == Invalid frame;  1 == Valid frame                       */
/*                                                                            */
/*  Description :                                                             */
/*       Processes the receipt of a Flow Control frame if still required.     */
/*                                                                            */
/******************************************************************************/
static U8 tp_rx_flow_control_frame(const U8 *rx_frame, U8 canDlc)
{
    U8 flow_control;
    U8 valid_frame = FALSE;

    /* Check if we still have data to transmit, otherwise ignore because flow control may have timed out */
    /* For FC CAN frame legal data length is greater or equal than 3 */
    if ((TransmitMsgLen_u16 > 0) && (canDlc >= 3))
    {
        /* Deviation 0492 - globally disabled */
        flow_control = (U8)(rx_frame[0] & N_PCI_FS_MASK);

        switch (flow_control)
        {
            case CONTINUE_TO_SEND:
            {
                /* Deviation 0492 - globally disabled */
                /* No further flow control frames? */
                if (0 == rx_frame[1])
                {
                    TransmitBS_u16 = INFINITE_BS;
                }
                else
                {
                    /* Deviation 0492 - globally disabled */
                    TransmitBS_u16 = rx_frame[1];
                }
                /* Deviation 0492 - globally disabled */
                TransmitSTMin_u8 = rx_frame[2];

                /* STMin error handling as per ISO 15765-2, section 6.5.5.6 */
                /* DEVIATION:     3355
                   DESCRIPTION:   The result of this logical operation is always 'true'.
                   JUSTIFICATION: It is done deliberately to show possible options.
                */
                /* PRQA S 3355 7 */
                if (((TransmitSTMin_u8 > 0x7FU) && (TransmitSTMin_u8 <= 0xF0U)) ||
                    ((TransmitSTMin_u8 > 0xF9U) && (TransmitSTMin_u8 <= 0xFFU)))
                {
                    TransmitSTMin_u8 = 0x7F;
                }

                if ((TransmitSTMin_u8 > 0xF0U) && (TransmitSTMin_u8 <= 0xF9U))
                {
                    TransmitSTMin_u8 = 0U;
                }

                /* Disarm N_Bs monitor timer */
                Tp_error_timer_active = DISARMED;

                /* Request next consecutive frame be sent */
                ReqTxConsecutiveFr_u8 = TRUE;

                valid_frame = TRUE;
                break;
            }

            case WAIT:
            {
                /* Wait state as per ISO1576-2,6.5.5.2 -> Wait for a new valid Flow control frame */
                /* Increment counter for max number of wait flow control frames possible */
                TpWftMax_u8++;
                /* If wait flow control frame count less than maximum possible value, process request */
                if (TpWftMax_u8 <= WFT_MAX)
                {
                    /* Restart N_Bs timer */
                    TpErrorTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
                    Tp_error_timer_active = N_Bs;
                    valid_frame = TRUE;
                }
                else
                {
                    /* Max value for wait flow control frame reached, reset TP receive state to NEW MESSAGE */
                    Tp_receive_state = NEW_MESSAGE;
                    /* Disarm N_Bs monitor timer */
                    Tp_error_timer_active = DISARMED;
                }
                break;
            }

            case OVFLW:
            default:
            {
                valid_frame = FALSE;
                break;
            }
        }
    }

    return valid_frame;
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_tx_flow_control_frame                                    */
/*                                                                            */
/*  Parameters  : U8 block size- no of message segments per Flow Control frame*/
/*                U8 separation time - time in ms between Consecutive Frames  */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*       Generates and transmits a Flow Control frame.                        */
/*                                                                            */
/******************************************************************************/
static void tp_tx_flow_control_frame(U8 block_size, U8 separation_time)
{
    U8 tx_data[8];
    Can_ReturnType retVal;

    tx_data[0] = (FLOW_CONTROL | TxFlowControlStatus_u8);
    tx_data[1] = block_size;
    tx_data[2] = separation_time;
    tx_data[3] = DIAG_RESP_PADDING_BYTE;
    tx_data[4] = DIAG_RESP_PADDING_BYTE;
    tx_data[5] = DIAG_RESP_PADDING_BYTE;
    tx_data[6] = DIAG_RESP_PADDING_BYTE;
    tx_data[7] = DIAG_RESP_PADDING_BYTE;

    retVal = (Can_ReturnType)Comms_Tx_UDS1_Message(tx_data, 8U);
    
    if (CAN_OK == retVal)
    {
        /* No flow control? */
        if (0 == block_size)
        {
            ReceiveBS_u16 = INFINITE_BS;
        }
        else
        {
            ReceiveBS_u16 = block_size;
        }
    }

    /* Start the monitor timer */
    TpErrorTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
    Tp_error_timer_active = N_Ar;

    if (CAN_OK == retVal)
    {
        tp_tx_frame_complete();
    }
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_tx_next_data_frame                                       */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*      Initiates the transmission of the next data frame, albeit SF, FF or   */
/*      CF frame type.                                                        */
/******************************************************************************/
static void tp_tx_next_data_frame(void)
{
    U8 tx_buf[8];
    U16 index_u8;
    U8 dlc_u8;
    U8 *p;
    Can_ReturnType retVal;

    p = tx_buf;
    /* SF or FF */
    if (TRUE == FirstFrameOfTx_u8)
    {
        /* Single frame? */
        if (TransmitMsgLen_u16 < 8)
        {

            *p = (U8)(SINGLE_FRAME | (TransmitMsgLen_u16 ));
           /* index_u8 = TransmitMsgLen_u16;
           dlc_u8 = (U8)(TransmitMsgLen_u16 + 1U);	*/	/*Commented by Rami to implement padding bytes*/
            index_u8 = CAN_DIAG_RESP_LENGTH;
            dlc_u8   = (CAN_DIAG_RESP_LENGTH + 1U);
            TransmitMsgLen_u16 = CAN_DIAG_RESP_LENGTH;

            /*  DEVIATION:     0489
                DESCRIPTION:   Increment or decrement operation performed on pointer.
                JUSTIFICATION: This is done for accessing different elements of the array, 
                               it is analyzed and causes no issues */
            /* PRQA S 0489 40*/
            p++;
        }
        /* First frame of multi segment */
        else
        {
            index_u8 = 6;
            dlc_u8 = 8;
            *p = (U8)(FIRST_FRAME | ((TransmitMsgLen_u16 / 256) & N_PCI_DL_MASK));
            *(p + 1) = (U8)(TransmitMsgLen_u16 & 0x00FF);
            /*  DEVIATION:     0488
                DESCRIPTION:   Performing pointer arithmetic.
                JUSTIFICATION: This is done for accessing different elements of the array, 
                               it is analyzed and causes no issues */
            /* PRQA S 0488 1*/
            p += 2;
        }
        FirstFrameOfTx_u8 = FALSE;
    }
    else
    {
        /* Consecutive Frame */
        index_u8 = (TransmitMsgLen_u16 > 7) ? 7 : TransmitMsgLen_u16;
        dlc_u8 = (U8)(index_u8 + 1U);
        *p = (U8)(CONSECUTIVE_FRAME | TransmitSN_u8);
        p++;
    }

    /* TransmitMsgLen_u16 equal to 0 indicates interruption of segmented transmission
       (e.g. reception of unexpected FC) so don't send anything */
    if (TransmitMsgLen_u16 > 0)
    {

        TransmitMsgLen_u16 -= index_u8;

        /* Copy data to transmit buffer */
        for (; index_u8 > 0; index_u8--)
        {
            *p = *TransmitMsgPtr_pu8;
            p++;
            TransmitMsgPtr_pu8++;
        }

        /* Inc. sequence no. and dec. block size for next frame */
        TransmitSN_u8 = (U8)((TransmitSN_u8 + 1) & N_PCI_SN_MASK);
        TransmitBS_u16--;

        retVal = (Can_ReturnType)Comms_Tx_UDS1_Message(tx_buf, dlc_u8);

        /* Re-initialize timer for this transmission confirmation */
        TpErrorTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
        Tp_error_timer_active = N_As;

        if (CAN_OK == retVal)
        {
            if (TransmitMsgLen_u16 > 0)
            {
                TPSegmentedTxInProgress_bo = TRUE;
            }
            else
            {
                TPSegmentedTxInProgress_bo = FALSE;
            }
            tp_tx_frame_complete();
        }
    }
}



/******************************************************************************/
/*                                                                            */
/*  Function    : tp_tx_frame_complete                                        */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*      This function is invoked when a message segment has been transmitted. */
/*      Performs diagnostic timer management and time-event scheduling of     */
/*      next consecutive data frame, as required.                             */
/******************************************************************************/
void tp_tx_frame_complete(void)
{
    /* A data frame (transmission on sender side) just occurred ? */
    if (Tp_error_timer_active == N_As)
    {
        /* Expecting a Flow Control frame ? */
        if ((TransmitBS_u16 == 0) && (TransmitMsgLen_u16 > 0))
        {
            /* Yes - start N_Bs timer, to monitor receipt of Flow Control */
            TpErrorTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
            Tp_error_timer_active = N_Bs;
        }
        else
        {
            /* No - disable timer until required next */
            Tp_error_timer_active = DISARMED;
        }
    }
    else
    {
        /* A flow control frame (transmission on receiver side) just occurred? */
        if (Tp_error_timer_active == N_Ar)
        {
            /* Yes - start N_Cr timer, to monitor receipt of next consecutive frame */
            TpErrorTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
            Tp_error_timer_active = N_Cr;
        }
    }

    /* A further Consecutive Frame transmission to schedule? */
    if ((TransmitMsgLen_u16 > 0) && (TransmitBS_u16 > 0))
    {
        /* Schedule transmission of next consecutive frame */
        TpNCSendTimer_u16 = (U16)COMMS_Get_Millisecond_Count();
        TpNCsTimerActive_u8 = TRUE;
    }
    else
    {
        if (0 == TransmitMsgLen_u16)
        {
            /* Signal end of CMD-Response  transaction */
            TPTransactionInProgress_bo = FALSE; 

            /* These items must be done here to allow UDS to be immediately ready to */
            /* receive rather than after next call to cyclic task up to 10ms later  */
            TPMessageReceived_bo = FALSE;
        }
    }
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_cyclic_task                                              */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description:                                                              */
/*      Called periodically from scheduler.                                   */
/*      Performs diagnostic error monitoring and scheduling of next data or   */
/*      flow control frame.                                                   */
/******************************************************************************/
void tp_cyclic_task(void)
{
    U16 timeout_period;

    /* Monitor network layer timing */
    if (Tp_error_timer_active != DISARMED)
    {
        switch (Tp_error_timer_active)
        {
            case N_As:
                /* Monitor N_As - transmission time of a CAN frame by transmit node */
                timeout_period = TP_N_A_SEND_TIMEOUT_CPV;
                break;

            case N_Ar:
                /* Monitor N_Ar - transmission time of a Flow Control frame by receive node */
                timeout_period = TP_N_A_RECEIVE_TIMEOUT_CPV;
                break;

            case N_Bs:
                /* Monitor N_Bs - reception time of a Flow Control frame from receive node */
                timeout_period = TP_N_B_SEND_TIMEOUT_CPV;
                break;

            case N_Cr:
                /* Monitor N_Cr - transmission time of a Consecutive Frame from transmit node */
                timeout_period = TP_N_C_RECEIVE_TIMEOUT_CPV;
                break;

            /*  DEVIATION:     2018
                DESCRIPTION:   This switch default label is unreachable.
                JUSTIFICATION: The default case will be retained for unexpected values */
            /* PRQA S 2018 1*/
            default:
                break;
        }

        if (system_check_time(U16, TpErrorTimer_u16, timeout_period))
        {
            /* Abort transmission. */
            TransmitMsgLen_u16 = 0;
            TPTransactionInProgress_bo = FALSE;
            TPMessageReceived_bo = FALSE;
            Tp_receive_state = NEW_MESSAGE;
            Tp_error_timer_active = DISARMED;
            TPSegmentedTxInProgress_bo = FALSE;
        }
    }

    /* end of Monitor network layer timing */


    /* Determine if there is a frame to transmit, Consecutive or Flow Control */
    /* Note that Consecutive Frame transmission and Flow Control transmission */
    /* are effectively mutually exclusive.                                    */
    if (TRUE == ReqTxConsecutiveFr_u8)
    {
        tp_tx_next_data_frame();
        ReqTxConsecutiveFr_u8 = FALSE;
    }
    else
    {
        if (TRUE == TpNCsTimerActive_u8)
        {
            if (system_check_time(U16, TpNCSendTimer_u16, TransmitSTMin_u8))
            {
                TpNCsTimerActive_u8 = FALSE;
                tp_tx_next_data_frame();
            }
        }
        else
        {
            /* Consider transmission of Flow Control when receiving */
            if (TRUE == ReqTxFlowCtrlFr_u8)
            {
                tp_tx_flow_control_frame(TP_DIAGNOSTIC_BS_CPV, TP_DIAGNOSTIC_STMIN_CPV);

                ReqTxFlowCtrlFr_u8 = FALSE;
            }
        }
    }
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_dtool_to_ACC_message                                  */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*       Process receipt of a physically addressed tester message.            */
/******************************************************************************/
/* DEVIATION:     4700
   DESCRIPTION:   Metric value out of threshold range: tp_rx_dtool_to_ACC_message() : STCYC = 19.
   JUSTIFICATION: This is not functional issue.
*/
/* PRQA S 4700 150 */
void tp_rx_dtool_to_ACC_message(const U8 *rx_data, U8 canDlc)
{
    U8 n_PCI_id;
    U8 frame_valid = FALSE;

    /* Deviation 0492 - globally disabled */
    n_PCI_id = (U8)(rx_data[0] & N_PCI_ID_MASK);

    if (Tp_receive_state == NEW_MESSAGE)
    {
        /* No receipt in progress */
        switch (n_PCI_id)
        {
            case SINGLE_FRAME:
            {
                /* Ignore SF if segmented transmission in progress && buffer free? - it is released by the application */
                if ((FALSE == TPSegmentedTxInProgress_bo) && (FALSE == TPMessageReceived_bo))
                {
                    frame_valid = tp_rx_single_frame(rx_data, canDlc);

                    if (TRUE == frame_valid)
                    {
                        TPTransactionInProgress_bo = TRUE;

                        /* Signal that a message has been received */
                        RxMessageType_u8 = PHYS;
                        TPMessageReceived_bo = TRUE;
                        /* Initialize wait Flow control counter to zero */
                        TpWftMax_u8 = 0x00;
                    }
                }
                break;
            }

            case FIRST_FRAME:
            {
                /* Ignore FF if segmented transmission in progress && buffer free? */
                if ((FALSE == TPSegmentedTxInProgress_bo) && (FALSE == TPMessageReceived_bo))
                {
                    frame_valid = tp_rx_first_frame(rx_data, canDlc);

                    if (TRUE == frame_valid)
                    {
                        TPTransactionInProgress_bo = TRUE;
                        Tp_receive_state = SEGMENTED_MESSAGE;
                    }
                }
                break;
            }

            case CONSECUTIVE_FRAME:
            {
                /* Unexpected frame - do nothing */
                break;
            }

            case FLOW_CONTROL:
            {
                /* In respect of a transmission */
                /* Frame expected? */
                if (0 == TransmitBS_u16)
                {
                    frame_valid = tp_rx_flow_control_frame(rx_data, canDlc);
                }
                break;
            }

            default:
            {
                break;
            }
        }
    }
    else
    {
        /* Segmented message currently in receipt */
        switch (n_PCI_id)
        {
            case SINGLE_FRAME:
            {
                /* Previous receive sequence aborted by valid single frame */
                frame_valid = tp_rx_single_frame(rx_data, canDlc);

                if (TRUE == frame_valid)
                {
                    /* Could be a flow control pending since this is an abort/restart */
                    ReqTxFlowCtrlFr_u8 = FALSE;

                    Tp_receive_state = NEW_MESSAGE;

                    /* Signal that a message has been received */
                    RxMessageType_u8 = PHYS;
                    TPMessageReceived_bo = TRUE;
                }
                break;
            }

            case FIRST_FRAME:
            {
                /* Previous receive sequence aborted by valid first frame */
                frame_valid = tp_rx_first_frame(rx_data, canDlc);
                break;
            }

            case CONSECUTIVE_FRAME:
            {
                frame_valid = tp_rx_consecutive_frame(rx_data, canDlc);

                if (TRUE == frame_valid)
                {
                    /* Message complete? */
                    if (0 == ReceiveDataLength_u16)
                    {
                        Tp_receive_state = NEW_MESSAGE;

                        /* Signal that a message has been received */
                        RxMessageType_u8 = PHYS;
                        TPMessageReceived_bo = TRUE;
                    }
                }
                /* Abort message reception. */
                else
                {
                    Tp_receive_state = NEW_MESSAGE;
                }
                break;
            }

            case FLOW_CONTROL:
            {
                /* Unexpected frame - do nothing */
                break;
            }

            default:
            {
                break;
            }
        }
    }
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_rx_dtool_to_all_message                                  */
/*                                                                            */
/*  Parameters  : U8*  - pointer to message packet                            */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*       Process receipt of a functionally addressed tester message.          */
/*       Only Single Frame messages are valid, others ignored !!!             */
/******************************************************************************/
void tp_rx_dtool_to_all_message(const U8 *rx_data, U8 canDlc)
{
    U8 frame_valid;
    U8 n_PCI_id;
    U8 sf_dl;

    /* Deviation 0492 - globally disabled */
    n_PCI_id = (U8)(rx_data[0] & N_PCI_ID_MASK);
    /* Deviation 0492 - globally disabled */
    sf_dl = (U8)(rx_data[0] & N_PCI_DL_MASK);

    if (SINGLE_FRAME == n_PCI_id)
    {
        /* Tester Present is a special case, an exception to the general
           protocol rules for application layer services and may be used as an
           unconfirmed service. */

        /* Explicitly handle tester present with noResponse required */
        if ((TESTER_PRESENT_ID == rx_data[1]) &&
            (SUPPRESS_POS_RESPONSE == rx_data[2]) &&
            (TESTER_PRESENT_REQ_LENGTH == sf_dl))
        {
            if (CurrentDiagnosticSession_u8 != TP_DEFAULT_SESSION_CPV) 
            {
                TpS3Timer_u16 = (U16)COMMS_Get_Millisecond_Count();
            }
        }
        else
        {
            /* Functionally addressed, single frame command */
            /* buffer free? */
            if (FALSE == TPMessageReceived_bo)
            {
                /* Unload frame to application input puffer */
                frame_valid = tp_rx_single_frame(rx_data, canDlc);

                if (TRUE == frame_valid)
                {
                    Tp_receive_state = NEW_MESSAGE;
                    TPTransactionInProgress_bo = TRUE;

                    /* Signal to the cyclic task that a command has been received */
                    RxMessageType_u8 = FUNCT;
                    TPMessageReceived_bo = TRUE;
                }
            }
        }
    }
}


/******************************************************************************/
/*                                                                            */
/*  Function    : tp_get_rx_message_length                                    */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : U16 - length of received message                            */
/*                                                                            */
/*  Description:                                                              */
/*      Accessor for length of received message.                              */
/******************************************************************************/
U16  tp_get_rx_message_length(void)
{
    return (AppRxDataLen_u16);
}

/******************************************************************************/
/*                                                                            */
/*  Function    : tp_response_message_pending                                 */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : BOOLEAN - (TRUE == message pending)                         */
/*                                                                            */
/*  Description:                                                              */
/*      Function to test if there is a transmit message pending.              */
/******************************************************************************/
BOOLEAN tp_response_message_pending(void)
{
    return ((BOOLEAN)(TransmitMsgLen_u16 > 0));
}

/* PRQA S 0492 -- */
