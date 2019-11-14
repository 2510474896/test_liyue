/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: can_app_if.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:48CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

#ifndef CAN_APP_IF_H
    #define CAN_APP_IF_H

    #define CanGetRxDataLen(i)           CanRxDataLen[i]
    #define CanGetApplIndicationPtr(i)   CanRxApplIndicationPtr[i]
    #define CanGetApplConfirmationPtr(i) CanTxApplConfirmationPtr[i]

    typedef void (*ApplIndicationFct)   (Can_PduType const *pdu);
    typedef void (*ApplConfirmationFct) (void);


    extern const ApplIndicationFct      CanRxApplIndicationPtr[];
    extern const ApplConfirmationFct    CanTxApplConfirmationPtr[];

    extern const U8                     CanRxDataLen[];

    /* Receive handles */
    typedef enum
    {
        Index_0_in_Can_Rx_Msg_Info,     /* CCP_Request_Index */
        Index_1_in_Can_Rx_Msg_Info,     /* HS2_REQ_DIAG_ON_CAN_6B6 */
        Index_2_in_Can_Rx_Msg_Info,     /* HS2_REQ_DIAG_ON_CAN_BROADCAST */
        NO_OF_CAN_RX_MSGS
    } CanRx_MsgHandles;

    /* Transmit handles */
    typedef enum
    {
        Index_0_in_Can_Tx_Msg_Info,    /* LAS_REP_DIAG_ON_CAN_696_Index */
        Index_1_in_Can_Tx_Msg_Info,    /* CCP_Response_Index */
        NO_OF_CAN_TX_MSGS
    } CanTx_MsgHandles;

#define UDS_DIAG_TX          Index_0_in_Can_Tx_Msg_Info
#define CCP_TX               Index_1_in_Can_Tx_Msg_Info

#define CAN_FIRST_TX_HANDLE  (NO_OF_CAN_RX_MSGS)     /* should be the last entry in the RX list */

#endif
