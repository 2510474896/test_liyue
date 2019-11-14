/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: can_app_if.c $
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


/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#include "types.h"
#include "Can.h"
#include "comms.h"
#include "can_app_if.h"
#include "bootstrp.h"  /* for T_REPROG_INFO_TYPE */
#include "ccppar.h"
#include "ccp.h"



/******************************************************************************
* GLOBAL VARIABLES
******************************************************************************/

__attribute__ (( aligned(4) ))  U8 CCP_RxData[8];
                                U8 CCP_TxData[8];


/*************************************************************/
/* Rx List */
/* indexed by the rx handle */

const ApplIndicationFct  CanRxApplIndicationPtr[NO_OF_CAN_RX_MSGS] =
{
    &can_pl_process_ccp_msg,        /* CanRxCCP_Request */
    &Comms_Process_UDS1_Message,    /* HS2_REQ_DIAG_ON_CAN_6B6 */
    &Comms_Process_UDS2_Message     /* HS2_REQ_DIAG_ON_CAN_BROADCAST */
};

/*************************************************************/
/* Transmit callbacks */
const ApplConfirmationFct CanTxApplConfirmationPtr[NO_OF_CAN_TX_MSGS] =
{
    &Comms_Send_UDS1_Message,       /* HS2_REP_DIAG_ON_CAN_696 */
    &CCP_tx_confirm_isr             /* CCP_TX */
};

