/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: comms.h $
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

#ifndef COMMS_H
#define COMMS_H


/******************************************************************************
*
*   FUNCTION DECLARATIONS
*
******************************************************************************/

extern U8 CCP_TxData[8];
extern U8 CCP_RxData[8];


Can_ReturnType Comms_Send_CAN_message( U8 tx_handle, U8* data);
void can_pl_process_ccp_msg (Can_PduType const *pdu);
void Comms_Process_UDS1_Message (Can_PduType const *pdu);
void Comms_Process_UDS2_Message (Can_PduType const *pdu);
void Comms_Send_UDS1_Message (void);
Can_ReturnType Comms_Tx_UDS1_Message(U8* data_pu8, U8 dlc_u8);

extern void basic_scheduler(void);
extern void Comms_Init(void);

/******************************************************************************
*
*   VARIABLE DECLARATIONS
*
******************************************************************************/

extern U32 COMMS_Get_Millisecond_Count(void);
#endif /* COMMS_H */

