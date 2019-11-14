/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/Config/project.pj $
        $RCSfile: CanIf_Cbk.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:17CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

/************************************************************************

THIS FILE IS NOT GENERATED FROM TRESOS NOR IS PART OF THE MCAL DELIVERY

It is a file that we have to write to satisfy the MCAL callback functions that
are defined in CanIf_Cbk.h

 ************************************************************************/

/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

#define CANIF_CBK           /* defines this file */

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/
#include "types.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "can_app_if.h"

#define CANIF_NOFUNCTIONCALL        0x00U       /* Tx is polled and not interrupt driven */
#define CANIF_TXCONFIRMATION        0x01U       /* Rx is polled and not interrupt driven */
#define CANIF_CANCELTXCONFIRMATION  0x02U       /* Bus-Off is polled and not interrupt driven */
#define CANIF_RXINDICATION          0x03U       /* Enable Tx cancelation */
#define CANIF_CONTROLLERBUSOFF      0x04U       /* Enable Tx multiplex */
#define CANIF_CONTROLLERMODEIND     0x05U       /* Controller Mode Indication*/


/*Used to check which callback function is called to update Can_test_Result */
static volatile uint8   Func_called;

/******************************************************************************
* Function Name    : CanIf_TxConfirmation
* Description      : CAN016: Indicates a successful transmission. Is either called
*                    by the TX-interrupt service routine of the corresponding HW
*                    resource or inside the Can_MainFunction_Write in case of
*                    polling mode.
* Parameters (in)  : CanTxPduId - PDU ID
* Return Value     : None
******************************************************************************/
void CanIf_TxConfirmation(PduIdType CanTxPduId)
{

    if (CanGetApplConfirmationPtr(CanTxPduId) != 0)
    {
        CanGetApplConfirmationPtr(CanTxPduId)();
    }

    /*update Func_called with callback function called*/
    Func_called = CANIF_TXCONFIRMATION;
}


/******************************************************************************
* Function Name    : CanIf_CancelTxConfirmation
* Description      : CAN098: Indicates a cancelled transmission. Is called at
*                    the end of Can_Write if a pending L-PDU has been cancelled.
*                    The implementation of that function is inside the CAN interface.
*                    The transmit buffer is released for the next transmission
*                    after return of CanIf_CancelTxConfirmation.
* Parameters (in)  : PduInfoPtr - Pointer to PDU data.
* Return Value     : None
******************************************************************************/
void CanIf_CancelTxConfirmation(PduIdType CanTxPduId, const PduInfoType * PduInfoPtr)
{
    /*update Func_called with callback function called*/
    Func_called = CANIF_CANCELTXCONFIRMATION;
}


/******************************************************************************
* Function Name    : CanIf_RxIndication
* Description      : CAN013: Indicates that a new L-PDU arrived.
*                    Is either called by the RX-interrupt service routine of the
*                    corresponding HW resource or inside Can_MainFunction_Read
*                    in case of polling mode.
* Parameters (in)  : Hrh - Hardware Receive Handle (HRH)
*                    CanId - Message ID
*                    CanDlc - Message Data length
*                    CanSduPtr - CAN Receive Data
* Return Value     : None
******************************************************************************/
void CanIf_RxIndication(Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, const uint8* CanSduPtr)
{
    Can_PduType   pdu;

    if (CanGetApplIndicationPtr(Hrh) != 0)
    {
        pdu.id = CanId;
        pdu.length = CanDlc;
        pdu.swPduHandle = Hrh;
        /*  DEVIATION:     0311
            DESCRIPTION:   Dangerous pointer cast results in loss of const qualification.
            JUSTIFICATION: pdu.sdu cannot be cast to a constant pointer because it is declared in the bought in Mcal layer code. 
            This warning has been evaluated and is considered not an issue 
         */
        /* PRQA S 0311 1 */
        pdu.sdu = (uint8 *)CanSduPtr;

        CanGetApplIndicationPtr(Hrh)(&pdu);
    }

    /*update Func_called with callback function called*/
    Func_called = CANIF_RXINDICATION;
}


/******************************************************************************
* Function Name    : CanIf_ControllerBusOff
* Description      : CAN019: Indicates that the controller went in bus-off mode.
*                    Is called by the bus-off interrupt service routine of the
*                    corresponding controller or by Can_MainFunction_BusOff,
*                    if the bus-off event is polled.
* Parameters (in)  : Controller
* Return Value     : None
******************************************************************************/
void CanIf_ControllerBusOff(uint8 Controller)
{
    /*update Func_called with callback function called*/
    Func_called = CANIF_CONTROLLERBUSOFF;
}


/******************************************************************************
* Function Name    : CanIf_ControllerModeIndication
******************************************************************************/
void CanIf_ControllerModeIndication( uint8 Controller, CanIf_ControllerModeType ControllerMode )
{
    Func_called = CANIF_CONTROLLERMODEIND;
}

