/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/DIAG/project.pj $
        $RCSfile: tp15765.h $
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

#ifndef TP_INC
#define TP_INC

#ifdef DIAG_SUBSYSTEM
/*************************************************************/
/*      DEFINITIONS LOCAL TO THIS SUBSYSTEM                  */

#define N_PCI_ID_MASK           0xF0
#define SINGLE_FRAME            0x00
#define FIRST_FRAME             0x10
#define CONSECUTIVE_FRAME       0x20
#define FLOW_CONTROL            0x30
#define N_PCI_DL_MASK           0x0F
#define N_PCI_SN_MASK           0x0F
#define N_PCI_FS_MASK           0x0F
#define CONTINUE_TO_SEND        0x00
#define WAIT                    0x01
#define OVFLW                   0x02
/* Maximum number of wait frame transmissions */
#define WFT_MAX                 0x02

#define INFINITE_BS             0xFFFF

#define UNUSED_PADDING          0xAA

/* Error monitor timeout values [ms] */
#define TP_N_A_SEND_TIMEOUT_CPV     1000
#define TP_N_A_RECEIVE_TIMEOUT_CPV  1000
#define TP_N_B_SEND_TIMEOUT_CPV     1000
#define TP_N_C_RECEIVE_TIMEOUT_CPV  1000

/* Flow control parameters - directive to tester */
#define TP_DIAGNOSTIC_BS_CPV        0
#define TP_DIAGNOSTIC_STMIN_CPV     0 /* ms */

/* Session definition */
#define TP_DEFAULT_SESSION_CPV      STANDARD

/* Non-default session timeout period */
#define TP_S3CAN_SERVER_MAX_CPV     5000U  /* ms */

#define TP_P2STAR_CAN_SERVER_MAX    5000U  /* ms */


U16 tp_get_rx_message_length(void);
BOOLEAN tp_response_message_pending(void);
void tp_init_send_message(U8 *tx_data, U16 message_length);
void tp_rx_dtool_to_ACC_message(const U8 *rx_data, U8 canDlc);
void tp_rx_dtool_to_all_message(const U8 *rx_data, U8 canDlc);
void tp_tx_frame_complete(void);

extern U8 RxMessageType_u8;
extern BOOLEAN TPMessageReceived_bo;
extern U16 TpS3Timer_u16;

typedef enum
{
    NEW_MESSAGE,

	SEGMENTED_MESSAGE

} t_rx_state;

typedef enum
{
    DISARMED,

    N_As,

    N_Ar,

    N_Bs,

    N_Cr

} t_monitor_timer;


#define PHYS   0x01
#define FUNCT  0x02

#endif




/*************************************************************/
/*      DEFINITIONS EXPORTED FROM THIS SUBSYSTEM             */
/*************************************************************/

#define system_check_time(typ,x,y) ((typ)((typ)COMMS_Get_Millisecond_Count() - (typ)(x)) > (typ)(y))

extern U16 AppRxDataLen_u16;
extern U16 TransmitMsgLen_u16;
extern BOOLEAN TPTransactionInProgress_bo;
extern U8 UDS_TDS_Received_u8;

extern void tp_cyclic_task(void);
extern void tp_init(void);
extern void tp_rx_dtool_to_ACC_message(const U8 *rx_data, U8 canDlc);
extern void tp_rx_dtool_to_all_message(const U8 *rx_data, U8 canDlc);
extern BOOLEAN tp_response_message_pending(void);

#endif /* TP_HEADER */
