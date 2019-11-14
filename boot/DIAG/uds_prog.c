/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/DIAG/project.pj $
        $RCSfile: uds_prog.c $
        $Revision: 1.7 $
        $Date: 2019/09/09 14:14:51CST $

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

/* DEVIATION:     4700
   DESCRIPTION:   Metric value out of threshold range.
   JUSTIFICATION: The number of executable lines of code is necessary.
*/
/* PRQA S 4700 ++ */

/* DEVIATION:     0491
   DESCRIPTION:   Array subscripting applied to an object of pointer type.
   JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
*/
/* PRQA S 0491 ++ */

/* DEVIATION:     0492
   DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
   JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
*/
/* PRQA S 0492 ++ */

/* DEVIATION:     0310
   DESCRIPTION:   Casting to different object pointer type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0310 ++ */

/* DEVIATION:     0303
   DESCRIPTION:   Cast between a pointer to volatile object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0303 ++ */

/* DEVIATION:     0306
   DESCRIPTION:   Cast between a pointer to object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0306 ++ */

/* DEVIATION:     0308
   DESCRIPTION:   Non-portable cast involving pointer to an incomplete type.
   JUSTIFICATION: Warning occurs as "%s" is defined as extern in the header file and not defined anywhere in the code
                  as it gets defined by the linker. Hence this is an incomplete type and it is cast to target type.
                  This cannot be avoided as addresses get defined only in the linker stage.
*/
/* PRQA S 0308 ++ */

/* DEVIATION:     0662
   DESCRIPTION:   Accessing a member of a nested structure in this way is a language extension.
   JUSTIFICATION: A nested structure member is being accessed in a non-standard way but it works fine.
*/
/* PRQA S 0662 ++ */

/* DEVIATION:     0488
   DESCRIPTION:   Performing pointer arithmetic.
   JUSTIFICATION: Pointer arithmetic is necessary for accessing data.
*/
/* PRQA S 0488 ++ */

/* DEVIATION:     0715
   DESCRIPTION:   Nesting of control structures (statements) exceeds 15 - program is non-conforming.
   JUSTIFICATION: It provides proper functionality.
*/
/* PRQA S 0715 ++ */

/***************************************************************************/


/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

/* defines this file */
#define UDS_PROG
/* defines the subsystem that this file resides in */
#define DIAG_SUBSYSTEM

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#include "Std_Types.h"
#include "types.h"
#include "flsh_int.h"
#include "bootstrp.h"
#include "Can.h"
/* To access COMMS_Get_Millisecond_Count() */
#include "comms.h"
#include "tp15765.h"
#include "MPC5744P.h"
#include "uds_prog.h"
#include "mcu_dch.h"
#include "pack_id.h"






/*
 * History is built with 21 location with 48bytes each. This table is representation of history locations.
 * First location is filled with supplier data
 * Rest of location are empty (all bytes are equal to 0xFF)
 */
static const U8 __attribute__((section(".eb_historic_field_1")))historyRecording_1_au8[NUMBER_OF_HISTORY_ZONES_MAX_1][ZI_DATA_LENGTH] =
{
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	},
	{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF}
};

/*
* History is built with 21 location with 48bytes each. This table is representation of history locations.
* First location is filled with supplier data
* Rest of location are empty (all bytes are equal to 0xFF)
*/
static const U8 __attribute__((section(".eb_historic_field_2")))historyRecording_2_au8[NUMBER_OF_HISTORY_ZONES_MAX_2][ZI_DATA_LENGTH] =
{
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{
   	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff},{0xff,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xff},
   	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,
   	0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
   	}
};




#define BSTRAP_READ_LOAD_STATUS()           	(*__LOAD_STATUS)


volatile static const U16 __attribute__((section(".eb_appli_key")))appliKey_u16 = GET_ID_CLEF_APPLI();

/*  DEVIATION:     3218
    DESCRIPTION:   File scope static, '...', only accessed in one function.Apr04@2019
    JUSTIFICATION: This section has to be placed here for better code readability.
*/


/* Global variables */
U8 CurrentDiagnosticSession_u8 = TP_DEFAULT_SESSION_CPV;

/* Static variables */
/* Sequence counter of download */
static UDS_ProgState_t UDSFlashSequence_e;
/* Current seed for security access service */
static U32 CurrSeed_u32;
/* Timer to manage Security access delay time initialized with a value enabling
 * to start security access sequence from the start of the bootloader
 */

/* DEVIATION:     3101, 3102
   DESCRIPTION:   Unary '-' applied to an operand of type unsigned int or unsigned long gives an unsigned result (3101).
                  Unary '-' applied to an operand whose underlying type is unsigned (3102).
   JUSTIFICATION: This is used in security to block access for 10 seconds after sending wrong key.
*/
/* PRQA S 3101 1 */ /* PRQA S 3102 1 */
static U32 SecurityAccessProhibitTimer_u32 = 0;	/* Changed to 0 from (U32)SECURITY_ACCESS_PROHIBIT_TIMER_INIT_VALUE, to get 10sec delay to unlock security access*/
/* Transfer Data sequence counter */
static U8 TransferSequenceCounter_u8;
/* Block count for erase routine */
static U8 StartBlock_u8;
/* Block count for erase routine */
static U8 EndBlock_u8;
/* Flash blocks numbers occupied by calibration and application */
static U8 Blocks_table[] =
{
    8U, 9U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U
};
/* Pointer to Input buffer for Diagnostic request */
static U8 *DiagBuffer_pu8;
/* Load status erase status */
static U8 Load_status_erase = FALSE;



/* Its initial value is TRUE.
 * This flag is set when data was transfered properly, or clear when data was transfered improperly.
 */
static BOOLEAN writeOk_bo = TRUE;

/* DEVIATION:     4643
   DESCRIPTION:   The identifier 'toolSignature_u16' could conflict in the future with the name of a function in '<ctype.h>'.
   JUSTIFICATION: This is irrelevant here.
*/

/* Flag for calibration memory erased status */
static BOOLEAN tunBlank_bo;
/* Flag for calibration + application memory erased status */
static BOOLEAN globalBlank_bo;
#if 0
/* After program checking is passed this flag is set. It allows to write ZI section */
static BOOLEAN authoriseLog_bo;
#endif
/* Memory type identifier (calibration/application/ZI/KEY_APPLI) */
static MemBlkIxPSA_t MemBlkIxPSA;


/* DEVIATION:     3684, 3447
   DESCRIPTION:   Array declared with unknown size (3684).
                  __SHARED_FLASH_AREA' has external linkage but this declaration is not in a header file (3447).
   JUSTIFICATION: This is defined in the linker file.
*/
/* PRQA S 3684 3 */ /* PRQA S 3447 1 */
extern U32 __SHARED_FLASH_AREA[];

/* Data buffers */
/* DEVIATION:     3406
   DESCRIPTION:   Object/function 'UDS_data_in', with external linkage, has been defined in a header file.
   JUSTIFICATION: There is only declaration for other modules.
*/
/* PRQA S 3406 2 */
/* Input buffer for Diagnostic request */
UDS_data_in_type UDS_data_in;
/* Output buffer for Diagnostic request */
UDS_data_out_type UDS_data_out;

/* DEVIATION: 3408
   DESCRIPTION: 'diagState' has external linkage but is being defined without any previous declaration.
   JUSTIFICATION: 'diagState' is used only within uds_prog.c.
*/
/* PRQA S 3408 1 */
tDiagState diagState;

/* Erase status of the sector */
static U8 Fls_secEraseSt[20]; /*Erase status of the sector*/
/* Initial value of this flag is set to TRUE to allow download application using
 * CANape (CCP) without UDS communication before flash
 */

BOOLEAN UDS_Send_Msg_Complete_bo = TRUE;

static U8 Seed_Bit_shift_u8 = 0x00;

static uint32_t memLogicalAddr;

static uint32_t ReceMemSize;

static U8 UDS_TD_Initiated = FALSE;

static U8 PreviousDiagnosticSession_u8 = DEFAULT_SESSION;
static U8 UDS_Perform_Mcu_Reset_Flag = FALSE;
static U8 UDS_Transfer_Data_Success_u8 = FALSE;
static U8 Erased_App_Cal_Brp_u8 = FALSE;
static U8 Erase_Routine_Inprog_u8 =FALSE;		/*to know the status of erase memory routine is in progress or not?*/

static U8 Invalid_Key_Attempts = 0;

static U8 SecurityAccessProhibitTimerActive_u32 = FALSE;

static BOOLEAN g_ApplStatus_bo = FALSE;


MemBlkIx_t memBlkIx; /* Common for download services and service 0x31. */


/* Enums and variables are used in service 0x22 (RDBI), DID 0x2101 */
typedef enum
{
    FA_MOTEUR_TYPE_ESSENCE     = 0,
    FA_MOTEUR_TYPE_DIESEL      = 1,
    FA_MOTEUR_TYPE_HYBRIDE     = 2,
    FA_MOTEUR_TYPE_ELECTRIQUE  = 3,
    FA_MOTEUR_TYPE_INVALIDE    = 4
} fa_moteur_type_t;

/* DEVIATION:     4641
   DESCRIPTION:   The identifier 'ECR_ABSENT...' could conflict in the future with the name of a macro in '<errno.h>'.
   JUSTIFICATION: These identifiers will not cause conflict in the future with macro in '<errno.h>'.
*/
/* PRQA S 4641 7 */
typedef enum
{
    ECR_ABSENT   = 0,
    ECR_GAUCHE   = 1,
    ECR_DROIT    = 2,
    ECR_INVALIDE = 3
} arc_option_hapt_ecr_t;

/* Macros for security access */
#define ResetSecurityAccess()          (diagState.securityFlags=0)
#define SetSecurityAccess()            (diagState.securityFlags|=1)
#define CheckSecurityAccess()          ((diagState.securityFlags==1) ? TRUE:FALSE)
#define ResetDevCtrlSecurityAccess()   (diagState.DevCtrlsecurityFlags=0)
#define SetDevCtrlSecurityAccess()     (diagState.DevCtrlsecurityFlags|=1)
#define CheckDevCtrlSecurityAccess()   ((diagState.DevCtrlsecurityFlags==1) ? TRUE:FALSE)

#define UDS_READ_LOAD_STATUS()         (*__LOAD_STATUS)


/******************************************************************************
 * Name         :  UDS_DiagInit
 * Called by    :  Boot Loader
 * Preconditions:  None
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Initialization function for UDS, calling once at power up
 ******************************************************************************/
void UDS_DiagInit(void)
{
    /* Initialize variables */
    CurrentDiagnosticSession_u8 = DEFAULT_SESSION;
    UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;

    /* Start delay timer if anti-tampering was active when ECU in last driving cycle */
    /*  DEVIATION:     0306        DESCRIPTION:   Cast between a pointer to object and an integral type.
        JUSTIFICATION: Warning is due to the definition of m_eInfractAtt.
                       The value of security access violation is saved at a fixed address in the
                       NVM. Hence pointing to the fixed memory location becomes necessary and hence
                       this warning cannot be removed */

    /* commented by Rami for X37 project*/
    /*if (m_eInfractAtt != PROG_NO_INFRACT_ATT)
    {
        SecurityAccessProhibitTimer_u32 = COMMS_Get_Millisecond_Count();
    }*/
}

/******************************************************************************
 * Name         :  UDS_DiagDataIndication
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  Process called to check if any new data is received
 * Parameters   :  None
 * Return code  :  none zero if data received
 * Description  :  Sets a pointer to the UDS receive data buffer
 ******************************************************************************/
static U8 UDS_DiagDataIndication(void)
{
    U8 newMessage_u8 = FALSE;

    if (TRUE == TPMessageReceived_bo)
    {
        TPMessageReceived_bo = FALSE;

        /* Point to received data */
        DiagBuffer_pu8 = &(UDS_data_in.UDS_data.UDS_request_body[0]);

        /* Get length of received message */
        UDS_data_in.UDS_data_length = tp_get_rx_message_length();

        newMessage_u8 = TRUE;
    }

    return (newMessage_u8);
}

/****************************************************************************/
/*                                                                          */
/*  Function    : send_negative_response                                    */
/*                                                                          */
/*  Parameters  : U8 responseCode_u8                                        */
/*                The negative response code to use.                        */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function formats a negative response message from the service id   */
/*  and Response code passed in.                                            */
/*                                                                          */
/****************************************************************************/
static void send_negative_response(U8 responseCode_u8)
{
    U8 serviceId_u8;

    if ((RxMessageType_u8 == FUNCT)
     && ((responseCode_u8 == SERVICE_NOT_SUPPORTED)
      || (responseCode_u8 == SUBFUNCTION_NOT_SUPPORTED)
      || (responseCode_u8 == REQUEST_OUT_OF_RANGE)))
    {
        /* For Functional addressing mode */
        /* No response */
        UDS_data_out.UDS_data_length = 0;
        TPTransactionInProgress_bo = FALSE;
    }
    else
    {
        serviceId_u8 = UDS_data_in.UDS_data.UDS_request_body[0];

        UDS_data_out.UDS_data.UDS_NegativeResponse.UDS_response_ID = NEG_RESPONSE_BYTE;
        UDS_data_out.UDS_data.UDS_NegativeResponse.DSE_UDS_request_ID = serviceId_u8;
        UDS_data_out.UDS_data.UDS_NegativeResponse.UDS_NegativeResponseCode = responseCode_u8;

        UDS_data_out.UDS_data_length = 3;
    }
} /* end of send_negative_response */

/****************************************************************************/
/*                                                                          */
/*  Function    : reset_session_parameters                                  */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function is called when a diagnostics session is stopped to reset  */
/*  anything that has changed during the session back to default session    */
/*  settings                                                                */
/****************************************************************************/
static void reset_session_parameters(void)
{
    /* reset security */
    ResetSecurityAccess();

    /*Rest device control security access*/
    ResetDevCtrlSecurityAccess();

    /*clear the invalid key attempts whenever session changes*/
    Invalid_Key_Attempts = 0;


    SecurityAccessProhibitTimerActive_u32 = FALSE;

    /* Set Flash sequence status to Sequence not active */
    UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;
}

/******************************************************************************
 * Name         :  UDS_DiagServiceHandler
 * Called by    :  Boot Schedular
 * Preconditions:  None
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Cyclic called every 3ms
 UDS diagnostic service dispatcher
 ******************************************************************************/
void UDS_DiagServiceHandler(void)
{
	U8 Actual_Resp_Lenngth = 0;

    /* If new Diagnostic data has been received from TP layer */
    if (TRUE == UDS_DiagDataIndication())
    {
        /* Service S3 timer */
        TpS3Timer_u16 = (U16)COMMS_Get_Millisecond_Count();

        /* Assume positive response */
        UDS_data_out.UDS_data.UDS_response_body[0] = (DiagBuffer_pu8[0] | 0x40);
        UDS_data_out.UDS_data_length = 0x01;

        if (DEFAULT_SESSION == CurrentDiagnosticSession_u8)
        {
            /* Current session is Default mode */
            switch (DiagBuffer_pu8[0])
            {
                case DIAGNOSTIC_SESSION_CONTROL_ID:
                {
                    process_diagnostic_session_control();
                    break;
                }
                case TESTER_PRESENT_ID:
                {
                    process_tester_present();
                    break;
                }
                /*case READ_DTC_INFORMATION_ID:
                {
                    UDS_read_dtc_information();
                    break;
                }*/
                /*case READ_DATA_BY_IDENT_ID:
                {
                    read_data_by_identifier();
                    break;
                }*/
                case CLEAR_DIAGNOSTIC_INFO_ID:
                {
                	clear_diagnostic_info();
                	break;
                }
                case WRITE_DATA_BY_IDENT_ID:
                case ROUTINE_CONTROL_ID:
                case REQUEST_DOWNLOAD_ID:
                case TRANSFER_DATA_ID:
                case REQUEST_TRANSFER_EXIT_ID:
                case RESET_ECU_ID:
                case SECURITY_ACCESS_ID:
                case COMMUNICATION_CONTROL_ID:
                case CONTROL_DTC_SETTING_ID:
                {
                    send_negative_response(SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
                    break;
                }
                case READ_DATA_BY_IDENT_ID:
                case READ_DTC_INFORMATION_ID:
                default:
                {
                    send_negative_response(SERVICE_NOT_SUPPORTED);
                    break;
                }
            }
        }
        else if (PROGRAM_SESSION == CurrentDiagnosticSession_u8)
        {
            /* Current session is Program mode */
            switch (DiagBuffer_pu8[0])
            {
                case DIAGNOSTIC_SESSION_CONTROL_ID:
                {
                    process_diagnostic_session_control();
                    break;
                }

                case SECURITY_ACCESS_ID:
                {
                    process_SecurityAccess();
                    break;
                }

                case REQUEST_DOWNLOAD_ID:
                {
                    UDS_RequestDownload();
                    break;
                }

                case ROUTINE_CONTROL_ID:
                {
                    routine_control();
                    break;
                }
                case REQUEST_TRANSFER_EXIT_ID:
                {
                    UDS_TransferExit();
                    break;
                }
                case TRANSFER_DATA_ID:
                {
                    UDS_TransferData();
                    break;
                }

                case TESTER_PRESENT_ID:
                {
                    process_tester_present();
                    break;
                }

                /*case READ_DATA_BY_IDENT_ID:
                {
                    read_data_by_identifier();
                    break;
                }

                case READ_DTC_INFORMATION_ID:
                {
                    UDS_read_dtc_information();
                    break;
                }*/

                case WRITE_DATA_BY_IDENT_ID:
                {
                	write_data_by_identifier();
                    break;
                }
                case RESET_ECU_ID:
                {
                	reset_ecu_id();
                	break;
                }
                case CLEAR_DIAGNOSTIC_INFO_ID:
                case COMMUNICATION_CONTROL_ID:
                case CONTROL_DTC_SETTING_ID:
                {
                	send_negative_response(SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
                	break;
                }
                case READ_DATA_BY_IDENT_ID:
                case READ_DTC_INFORMATION_ID:
                default:
                {
                    send_negative_response(SERVICE_NOT_SUPPORTED);
                    break;
                }
            }
        }
        else if(EXTENDED_SESSION == CurrentDiagnosticSession_u8)
        {
            /* Current session is Extended mode */
            switch (DiagBuffer_pu8[0])
            {
                case DIAGNOSTIC_SESSION_CONTROL_ID:
                {
                    process_diagnostic_session_control();
                    break;
                }
                case SECURITY_ACCESS_ID:
                {
                     process_SecurityAccess();
                     break;
                }
                case TESTER_PRESENT_ID:
                {
                    process_tester_present();
                    break;
                }
                /*case READ_DTC_INFORMATION_ID:
                {
                    UDS_read_dtc_information();
                    break;
                }*/
                case RESET_ECU_ID:
                {
                	reset_ecu_id();
                	break;
                }
                case COMMUNICATION_CONTROL_ID:
                {
                	communication_control_msg();
                	break;
                }
                case CONTROL_DTC_SETTING_ID:
                {
                	control_dtc_setting();
                	break;
                }
                case ROUTINE_CONTROL_ID:
                {
                    routine_control();
                    break;
                }
                case REQUEST_DOWNLOAD_ID:
                case TRANSFER_DATA_ID:
                case REQUEST_TRANSFER_EXIT_ID:
                case WRITE_DATA_BY_IDENT_ID:
                case CLEAR_DIAGNOSTIC_INFO_ID:
                {
                    send_negative_response(SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
                    break;
                }
                case READ_DATA_BY_IDENT_ID:
                case READ_DTC_INFORMATION_ID:
                default:
                {
                    send_negative_response(SERVICE_NOT_SUPPORTED);
                    break;
                }
            }

        }
        else
        {
            /* do nothing */
        }
    }

    if (UDS_data_out.UDS_data_length > 0)
    {
        /*  DEVIATION:     0310
            DESCRIPTION:   Casting to different object pointer type
            JUSTIFICATION: This casting is required here as tp_init_send_message
                           requires U8 pointer as input parameter */
        /* PRQA S 0310 1*/

    	Actual_Resp_Lenngth = (U8)UDS_data_out.UDS_data_length;

    	for(;Actual_Resp_Lenngth < CAN_DIAG_RESP_LENGTH;Actual_Resp_Lenngth++)
    	{
    		 UDS_data_out.UDS_data.UDS_response_body[Actual_Resp_Lenngth] = DIAG_RESP_PADDING_BYTE;
    	}

        tp_init_send_message((U8 *)&UDS_data_out.UDS_data.UDS_response_body, UDS_data_out.UDS_data_length);

        UDS_data_out.UDS_data_length = 0U;
        /* Clear the flag which signals sent or not message on CAN */
        UDS_Send_Msg_Complete_bo = FALSE;
    }
    else
    {
        /* No response, so transaction is complete */
        TPTransactionInProgress_bo = FALSE;

        /* More speedily reset in event that received message needs no reply */
        TPMessageReceived_bo = FALSE;
    }

    if((TRUE == UDS_Perform_Mcu_Reset_Flag)&&(FALSE == TPTransactionInProgress_bo))
    {
        	UDS_Perform_Mcu_Reset_Flag = FALSE;
        	CurrentDiagnosticSession_u8 = DEFAULT_SESSION;
        	PreviousDiagnosticSession_u8 = DEFAULT_SESSION;
        	reset_session_parameters();
        	if(TRUE == Erased_App_Cal_Brp_u8)
        	{
        		Erased_App_Cal_Brp_u8 = FALSE;
        		/* Valid test code checksum and signature. Program LS and reset the unit */
        		(void)FlsProgramLoadStatus(SYS_LOAD_STATUS_BRP_VALID);
        	}
        	else
        	{
        		;
        	}
        	(void)finish_programming_sequence();
    }
    /* Non-default diagnostic session monitor */
    else if ((DEFAULT_SESSION != CurrentDiagnosticSession_u8)||(PROGRAM_SESSION == PreviousDiagnosticSession_u8))
    {
    	/* If tester has not talked for 5 sec, reset to default session */
        if (system_check_time(U16, TpS3Timer_u16, TP_S3CAN_SERVER_MAX_CPV))
        {
         	CurrentDiagnosticSession_u8 = DEFAULT_SESSION;
            PreviousDiagnosticSession_u8 = DEFAULT_SESSION;
            reset_session_parameters();
            (void) finish_programming_sequence();
        }
    }
    else
    {
    	;
    }
}


/****************************************************************************/
/*                                                                          */
/*  Function    : process_diagnostic_session_control                        */
/*  Called by   : UDS_DiagServiceHandler                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*  This function is invoked when Diagnostic session control service is     */
/*  requested. The request for the session requested is processed, and a    */
/*  positive or negative response is sent accordingly.                      */
/****************************************************************************/
static void process_diagnostic_session_control(void)
{
    U8 diagSessCtlSubFunc_u8;
    U8 diagnosticMode_u8;
    U8 suppressPos_u8;
    U8 dscStatus_u8 = 0U;
    U16 batVoltage_u16;


    /* Check request message type. This service is supported in physical and functional addressing */
    if ((FUNCT == RxMessageType_u8) || (PHYS == RxMessageType_u8))
    {
        diagSessCtlSubFunc_u8 = UDS_data_in.UDS_data.UDS_StartDiagnosticSession_msg.diagnosticSession;
        diagnosticMode_u8 = (diagSessCtlSubFunc_u8 & SUBFUNCTION_MASK);
        suppressPos_u8 = (diagSessCtlSubFunc_u8 & SUPPRESS_POS_RESPONSE);

        /* Minimum length check */
        if (DIAG_SESS_CONTROL_LENGTH == MESSAGE_DATA_LENGTH)
        {
            switch (diagnosticMode_u8)
            {
                case DEFAULT_SESSION:
                {
                        /* close this session and start a new one */
                        reset_session_parameters();

                        if (PROGRAM_SESSION == CurrentDiagnosticSession_u8)
                        {
                            (void) finish_programming_sequence();
                        }
                        /* Store the diagnostic mode which has been requested */
                        CurrentDiagnosticSession_u8 = diagnosticMode_u8;

                        /* Diagnosis mode is correct, create a positive response */
                        UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_DiagnosticMode =
                                     diagnosticMode_u8;

                        /* Check whether response required */
                        if (0U == suppressPos_u8)
                        {
#if 1
                            /* Transport layer timing ... */
                            /********************************************************/
                            UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_msb =
                                         UDS_P2CAN_SERVER_MAX_MSB;
                            UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_lsb =
                                         UDS_P2CAN_SERVER_MAX_LSB;
                            UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_msb =
                                         UDS_P2STARCAN_SERVER_MAX_MSB;
                            UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_lsb =
                                         UDS_P2STARCAN_SERVER_MAX_LSB;

                            UDS_data_out.UDS_data_length = 6;
#else
                            UDS_data_out.UDS_data_length = 2;
#endif
                        }
                        else
                        {
                            /* no response! */
                            /*UDS_data_out.UDS_data_length = 0;*/
                        	dscStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        }
                        break;
                	}

                	case PROGRAM_SESSION:
                	{
                        /* After change session from programming session to programming
                         * session, ECU should response with NRC_22 - condition not correct.
                         * In other, ECU returns positive response.
                         */
                            if (Mcu_Read_ADC() == READ_ADC_SUCCESS)
                            {
                                batVoltage_u16 = Mcu_Get_ADC(ADC_VBAT_MON);
                            }
                            else
                            {
                                /* If read battery voltage was not successful,
                                 * assign a valid value to battery voltage
                                 */
                                batVoltage_u16 = MIN_VBAT_COUNT;
                            }

                            if (batVoltage_u16 < MIN_VBAT_COUNT)
                            {
                                dscStatus_u8 = VOLTAGE_TOO_LOW;
                            }
                            /* When battery voltage is too high */
                            else if (batVoltage_u16 > MAX_VBAT_COUNT)
                            {
                                dscStatus_u8 = VOLTAGE_TOO_HIGH;
                            }
                            else
                            {
                                /* close this session and start a new one */
                                reset_session_parameters();

                                /* Store the diagnostic mode which has been requested */
                                CurrentDiagnosticSession_u8 = diagnosticMode_u8;

                                /* Diagnosis mode is correct, create a positive response */
                                UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_DiagnosticMode =
                                             diagnosticMode_u8;

                                /* Check whether response required */
                                if (0U == suppressPos_u8)
                                {

#if 1
                                    /* Transport layer timing ... */
                                    /********************************************************/
                                    UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_msb =
                                                 UDS_P2CAN_SERVER_MAX_MSB;
                                    UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_lsb =
                                                 UDS_P2CAN_SERVER_MAX_LSB;
                                    UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_msb =
                                                 UDS_P2STARCAN_SERVER_MAX_MSB;
                                    UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_lsb =
                                                 UDS_P2STARCAN_SERVER_MAX_LSB;

                                    UDS_data_out.UDS_data_length = 6;
#else
                                    UDS_data_out.UDS_data_length = 2;
#endif
                                }
                                else
                                {
                                    /* no response! */
                                    /*UDS_data_out.UDS_data_length = 0;*/
                                	dscStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                                }
                                PreviousDiagnosticSession_u8 = CurrentDiagnosticSession_u8;
                            }
                       break;
                	}

                	case EXTENDED_SESSION:
                	{
                        if (PROGRAM_SESSION != CurrentDiagnosticSession_u8)
                        {
                            /* close this session and start a new one */
                            reset_session_parameters();

                            /* Store the diagnostic mode which has been requested */
                            CurrentDiagnosticSession_u8 = diagnosticMode_u8;

                            /* Diagnosis mode is correct, create a positive response */
                            UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_DiagnosticMode =
                                         diagnosticMode_u8;

                            /* Check whether response required */
                            if (0U == suppressPos_u8)
                            {

#if 1
                                /* Transport layer timing ... */
                                /********************************************************/
                                UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_msb =
                                             UDS_P2CAN_SERVER_MAX_MSB;
                                UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2CAN_server_max_lsb =
                                             UDS_P2CAN_SERVER_MAX_LSB;
                                UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_msb =
                                             UDS_P2STARCAN_SERVER_MAX_MSB;
                                UDS_data_out.UDS_data.UDS_DiagnosticSessionControl_resp.UDS_P2STARCAN_server_max_lsb =
                                             UDS_P2STARCAN_SERVER_MAX_LSB;

                                UDS_data_out.UDS_data_length = 6;
#else
                                UDS_data_out.UDS_data_length = 2;
#endif
                            }
                            else
                            {
                                /* no response! */
                                UDS_data_out.UDS_data_length = 0;
                            }
                        }
                        else
                        {
                            dscStatus_u8 = CONDITIONS_NOT_CORRECT;
                        }
                        break;
                	}
                	default:
                	{
                		dscStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                		break;
                	}
            	}
        	}
        	else
        	{
        		/* Minimum length check */
        		dscStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
        	}
    	}
    	else
    	{
    		/* No response */
    		UDS_data_out.UDS_data_length = 0U;
    	}
    	if (dscStatus_u8 != 0U)
    	{
    		send_negative_response(dscStatus_u8);
    	}
}

/******************************************************************************
 * Name         :  process_SecurityAccess
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  May be called after service request was received
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Performs the security access procedure.
 ******************************************************************************/
static void process_SecurityAccess(void)
{
    U8 diagSecAccSubFunc_u8;
    U8 saSubFunct_u8;
    U8 suppressPos_u8;
    U8 saStatus_u8 = FALSE;
    U8 index_u8;

    /* Seed sent by ECU */
    static U8 CurrentSeed_au8[4U];
    /* Key_u32 calculated by ECU */
    static U8 DecryptedKey_au8[4U];
    /* Current key received from tester */
    static U8 ReturnedSAKey_au8[4U];

    /* Seed sent by ECU */
    static U8 DevCtrlCurrentSeed_au8[4U];
    /* Key_u32 calculated by ECU */
    static U8 DevCtrlDecryptedKey_au8[4U];
    /* Current key received from tester */
    static U8 DevCtrlReturnedSAKey_au8[4U];

    /* Check request message type. This service is supported in physical addressing */
    /* In other case there is no response */
    if (PHYS == RxMessageType_u8)
    {
        if (MESSAGE_DATA_LENGTH >= SECURITY_ACCESS_MINIMUM_LENGTH)
        {
            diagSecAccSubFunc_u8 = (U8)UDS_data_in.UDS_data.UDS_SecurityAccess_msg.securityAccessMode;
            saSubFunct_u8 = (diagSecAccSubFunc_u8 & SUBFUNCTION_MASK);
            suppressPos_u8 = (diagSecAccSubFunc_u8 & SUPPRESS_POS_RESPONSE);

            switch (saSubFunct_u8)
            {
                case REQUEST_SEED_PRG:
                {
                    if (REQUEST_SEED_LENGTH != MESSAGE_DATA_LENGTH)
                    {
                        saStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                    }
                    else if(PROGRAM_SESSION != CurrentDiagnosticSession_u8)
                    {
                    	saStatus_u8 = SUBFUNCT_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                    }
                    /* Check if SEED have been already sent */
                    else if (SECURITY_UNLOCKING == UDSFlashSequence_e)
                    {
                        saStatus_u8 = REQUEST_SEQUENCE_ERROR;
                    }
                    /* Check if SA prohibit timer delay active */
                    else if (!system_check_time(U32, SecurityAccessProhibitTimer_u32, SA_PROHIBIT_DELAY))
                    {
                        saStatus_u8 = REQUIRED_TIME_DELAY_NOT_EXPIRED;
                    }
                    else if (TRUE == CheckSecurityAccess())
                    {
                        /* If security is disabled or security is already unlocked, return a SEED of 4x 00h */
                        for (index_u8 = 0; index_u8 < 4U; index_u8++)
                        {
                            CurrentSeed_au8[index_u8] = 0U;
                            UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessSeed[index_u8] = 0U;
                        }
                    }
                    else
                    {
                        /* Generate a seed value */
                        CurrSeed_u32 = securitySeedGeneration((U16)COMMS_Get_Millisecond_Count());

                        CurrentSeed_au8[0] = (U8)(CurrSeed_u32 >> 24U);
                        CurrentSeed_au8[1] = (U8)(CurrSeed_u32 >> 16U);
                        CurrentSeed_au8[2] = (U8)(CurrSeed_u32 >> 8U);
                        CurrentSeed_au8[3] = (U8)(CurrSeed_u32);

                        copy_data((const U8 *)&CurrentSeed_au8[0U],
                                  (U8 *)&UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessSeed[0U],
								  4U);

                        evaluate_key(&DecryptedKey_au8[0U]);

                        /* Signal that unlock procedure is in progress */
                        UDSFlashSequence_e = SECURITY_UNLOCKING;
                    }

                    if (FALSE == saStatus_u8)
                    {
                        /* Check whether response required */
                        if (0U == suppressPos_u8)
                        {
                            /* Complete the positive response message */
                            UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessMode = REQUEST_SEED_PRG;
                            UDS_data_out.UDS_data_length = 6U;
                        }
                        else
                        {
                            /* no response! */
                            UDS_data_out.UDS_data_length = 0U;
                        }
                    }
                    else
                    {
                        send_negative_response(saStatus_u8);
                    }
                    break;
                }
                case SEND_KEY_PRG:
                {
                    if (SEND_KEY_LENGTH != MESSAGE_DATA_LENGTH)
                    {
                        saStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                    }
                    else if(PROGRAM_SESSION != CurrentDiagnosticSession_u8)
                    {
                    	saStatus_u8 = SUBFUNCT_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                    }
                    /* Check sequence order */
                    else if ((UDSFlashSequence_e != SECURITY_UNLOCKING) && ( FALSE == CheckSecurityAccess()))
                    {
                        saStatus_u8 = REQUEST_SEQUENCE_ERROR;
                    }
                    else if (FALSE == CheckSecurityAccess())
                    {
                        copy_data((const U8 *)&UDS_data_in.UDS_data.UDS_SecurityAccessSendKey_msg.key[0],
                                  (U8 *)&ReturnedSAKey_au8[0],
								  4U);

                        /* Check the key bytes */
                        if ((ReturnedSAKey_au8[0U] == DecryptedKey_au8[0U])
                         && (ReturnedSAKey_au8[1U] == DecryptedKey_au8[1U])
                         && (ReturnedSAKey_au8[2U] == DecryptedKey_au8[2U])
                         && (ReturnedSAKey_au8[3U] == DecryptedKey_au8[3U]))
                        {
                        	Invalid_Key_Attempts = 0;	/*Reset the counter value*/

                        	if(TRUE == SecurityAccessProhibitTimerActive_u32)
                        	{
                        		SecurityAccessProhibitTimerActive_u32 =  FALSE;
                        	}
                        	else
                        	{
                        		;
                        	}
                            /* unlock security access level 1*/
                            SetSecurityAccess();
                        }
                        else
                        {
                            /* Security Access SendKey Request Parameter is incorrect, create a negative response */
                            saStatus_u8 = INVALID_KEY;

                            ++Invalid_Key_Attempts;	/*Increment the counter when received key is not equal to calculated key*/

                            if((TRUE == SecurityAccessProhibitTimerActive_u32) && (INVALID_KEY == saStatus_u8))
                            {
                            	SecurityAccessProhibitTimer_u32 = COMMS_Get_Millisecond_Count();
                            }
                            else if(INVALID_KEY_ATTEMPTS == Invalid_Key_Attempts)
                            {
                            	/* Security Access SendKey Request Parameter is incorrect for 3 times, create a negative response */
                            	saStatus_u8 = EXCEEDED_NUMBER_OF_ATTEMPTS;
                            	/* Restart SA-inhibit timer */
                            	SecurityAccessProhibitTimer_u32 = COMMS_Get_Millisecond_Count();

                            	SecurityAccessProhibitTimerActive_u32 =  TRUE;
                            }
                            else
                            {
                            	;
                            }
                            /* Restart SA-inhibit timer */
                            /*  DEVIATION:     0306
                                DESCRIPTION:   Cast between a pointer to object and an integral type.
                                JUSTIFICATION: Warning is due to the definition of m_eInfractAtt.
                                               The value of security access violation is saved at a
                                               fixed address in the NVM. Hence pointing to the fixed
                                               memory location becomes necessary and therefore
                                               this warning cannot be removed */
                           /* FLASH_WriteWord(PROG_INFRACT_ATT_ADDRESS, PROG_INFRACT_ATT);*/
                        }
                    }
                    else
                    {
                        /* This is the arbitrary situation required where client has ignored       */
                        /* the response to 27 03 that unit is already unlocked and has             */
                        /* (redundantly) sent the key.                                             */
                        /* Generate a positive response : (this is done by retaining saStatus_u8 = FALSE*/
                        ; /* Do nothing */

                        saStatus_u8 = CONDITIONS_NOT_CORRECT;
                    }

                    if (saStatus_u8 != FALSE)
                    {
                        send_negative_response(saStatus_u8);
                        UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;
                    }
                    else
                    {
                        /* Check whether response required */
                        if (0U == suppressPos_u8)
                        {
                            /* Generate a positive response ... */
                            UDS_data_out.UDS_data.UDS_SecurityAccessSendKey_resp.securityAccessMode = SEND_KEY_PRG;
                            UDS_data_out.UDS_data_length = 2U;
                        }
                        else
                        {
                            /* no response! */
                            UDS_data_out.UDS_data_length = 0U;
                        }
                        UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
                        /*Initialize erase status of all Flash sectors to FALSE*/
                        for (index_u8 = 0; index_u8 < 20U; index_u8++)
                        {
                            Fls_secEraseSt[index_u8] = FALSE;
                        }
                    }
                    break;
                }
                case REQUEST_SEED_DEVICECTRL:
                {
                    if (REQUEST_SEED_LENGTH != MESSAGE_DATA_LENGTH)
                    {
                        saStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                    }
                    else if(EXTENDED_SESSION != CurrentDiagnosticSession_u8)
                    {
                    	saStatus_u8 = SUBFUNCT_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                    }
                    /* Check if SEED have been already sent */
                    else if (DEVCTRL_SECURITY_UNLOCKING == UDSFlashSequence_e)
                    {
                        saStatus_u8 = REQUEST_SEQUENCE_ERROR;
                    }
                    /* Check if SA prohibit timer delay active */
                    else if (!system_check_time(U32, SecurityAccessProhibitTimer_u32, SA_PROHIBIT_DELAY))
                    {
                        saStatus_u8 = REQUIRED_TIME_DELAY_NOT_EXPIRED;
                    }
                    else if (TRUE == CheckDevCtrlSecurityAccess())
                    {
                        /* If security is disabled or security is already unlocked, return a SEED of 4x 00h */
                        for (index_u8 = 0; index_u8 < 4U; index_u8++)
                        {
                            DevCtrlCurrentSeed_au8[index_u8] = 0U;
                            UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessSeed[index_u8] = 0U;
                        }
                    }
                    else
                    {
                        /* Generate a seed value */
                        CurrSeed_u32 = securitySeedGeneration((U16)COMMS_Get_Millisecond_Count());

                        DevCtrlCurrentSeed_au8[0] = (U8)(CurrSeed_u32 >> 24U);
                        DevCtrlCurrentSeed_au8[1] = (U8)(CurrSeed_u32 >> 16U);
                        DevCtrlCurrentSeed_au8[2] = (U8)(CurrSeed_u32 >> 8U);
                        DevCtrlCurrentSeed_au8[3] = (U8)(CurrSeed_u32);

                        copy_data((const U8 *)&DevCtrlCurrentSeed_au8[0U],
                                  (U8 *)&UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessSeed[0U],
                				  4U);

                        evaluate_key(&DevCtrlDecryptedKey_au8[0U]);

                        /* Signal that unlock procedure is in progress */
                        UDSFlashSequence_e = DEVCTRL_SECURITY_UNLOCKING;
                    }

                    if (FALSE == saStatus_u8)
                    {
                        /* Check whether response required */
                        if (0U == suppressPos_u8)
                        {
                            /* Complete the positive response message */
                            UDS_data_out.UDS_data.UDS_SecurityAccess_resp.securityAccessMode = REQUEST_SEED_DEVICECTRL;
                            UDS_data_out.UDS_data_length = 6U;
                        }
                        else
                        {
                            /* no response! */
                            UDS_data_out.UDS_data_length = 0U;
                        }
                    }
                    else
                    {
                        send_negative_response(saStatus_u8);
                    }
                    break;
                }
                case SEND_KEY_DEVICECTRL:
                {
                    if (SEND_KEY_LENGTH != MESSAGE_DATA_LENGTH)
                    {
                        saStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                    }
                    else if(EXTENDED_SESSION != CurrentDiagnosticSession_u8)
                    {
                       	saStatus_u8 = SUBFUNCT_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                    }
                    /* Check sequence order */
                    else if ((UDSFlashSequence_e != DEVCTRL_SECURITY_UNLOCKING) && ( FALSE == CheckDevCtrlSecurityAccess()))
                    {
                        saStatus_u8 = REQUEST_SEQUENCE_ERROR;
                    }
                    else if (FALSE == CheckDevCtrlSecurityAccess())
                    {
                        copy_data((const U8 *)&UDS_data_in.UDS_data.UDS_SecurityAccessSendKey_msg.key[0],
                                  (U8 *)&DevCtrlReturnedSAKey_au8[0],
                				  4U);

                        /* Check the key bytes */
                        if ((DevCtrlReturnedSAKey_au8[0U] == DevCtrlDecryptedKey_au8[0U])
                         && (DevCtrlReturnedSAKey_au8[1U] == DevCtrlDecryptedKey_au8[1U])
                         && (DevCtrlReturnedSAKey_au8[2U] == DevCtrlDecryptedKey_au8[2U])
                         && (DevCtrlReturnedSAKey_au8[3U] == DevCtrlDecryptedKey_au8[3U]))
                        {

                        	Invalid_Key_Attempts = 0;	/*Reset the counter value*/

                        	if(TRUE == SecurityAccessProhibitTimerActive_u32)
                        	{
                        		SecurityAccessProhibitTimerActive_u32 =  FALSE;
                        	}
                        	else
                        	{
                        		;
                        	}


                            /* unlock */
                            SetDevCtrlSecurityAccess();

                        }
                        else
                        {
                            /* Security Access SendKey Request Parameter is incorrect, create a negative response */
                            saStatus_u8 = INVALID_KEY;

                            ++Invalid_Key_Attempts;	/*Increment the counter when received key is not equal to calculated key*/
                            if((TRUE == SecurityAccessProhibitTimerActive_u32) && (INVALID_KEY == saStatus_u8))
                            {
                                SecurityAccessProhibitTimer_u32 = COMMS_Get_Millisecond_Count();
                            }
                            else if(INVALID_KEY_ATTEMPTS == Invalid_Key_Attempts)
                            {
                            	Invalid_Key_Attempts = 0;	/*Reset the counter value*/

                            	/* Security Access SendKey Request Parameter is incorrect for 3 times, create a negative response */
                            	saStatus_u8 = EXCEEDED_NUMBER_OF_ATTEMPTS;
                            	/* Restart SA-inhibit timer */
                            	SecurityAccessProhibitTimer_u32 = COMMS_Get_Millisecond_Count();

                            	SecurityAccessProhibitTimerActive_u32 = TRUE;
                            }
                            else
                            {
                            	;
                            }
                            /* Restart SA-inhibit timer */
                            /*  DEVIATION:     0306
                                DESCRIPTION:   Cast between a pointer to object and an integral type.
                                JUSTIFICATION: Warning is due to the definition of m_eInfractAtt.
                                               The value of security access violation is saved at a
                                               fixed address in the NVM. Hence pointing to the fixed
                                               memory location becomes necessary and therefore
                                               this warning cannot be removed */
                            /*FLASH_WriteWord(PROG_INFRACT_ATT_ADDRESS, PROG_INFRACT_ATT);*/
                        }
                    }
                    else
                    {
                        /* This is the arbitrary situation required where client has ignored       */
                        /* the response to 27 03 that unit is already unlocked and has             */
                        /* (redundantly) sent the key.                                             */
                        /* Generate a positive response : (this is done by retaining saStatus_u8 = FALSE*/
                        ; /* Do nothing */

                        saStatus_u8 = CONDITIONS_NOT_CORRECT;
                    }

                    if (saStatus_u8 != FALSE)
                    {
                        send_negative_response(saStatus_u8);
                        UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;
                    }
                    else
                    {
                        /* Check whether response required */
                        if (0U == suppressPos_u8)
                        {
                            /* Generate a positive response ... */
                            UDS_data_out.UDS_data.UDS_SecurityAccessSendKey_resp.securityAccessMode = SEND_KEY_DEVICECTRL;
                            UDS_data_out.UDS_data_length = 2U;
                        }
                        else
                        {
                            /* no response! */
                            UDS_data_out.UDS_data_length = 0U;
                        }
                        UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
                        /*Initialize erase status of all Flash sectors to FALSE*/
                        for (index_u8 = 0; index_u8 < 20U; index_u8++)
                        {
                            Fls_secEraseSt[index_u8] = FALSE;
                        }
                    }
                    break;
                }
                default:
                {
                	send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
                    break;
                }
            }
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}

/******************************************************************************
 * Name         :  routine_control
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  Called after routine service request was received
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Routines: Erase memory and Check programming dependencies
 ******************************************************************************/
static void routine_control(void)
{
    /*                           |   0|   1|   2|   3|   4|   5|   6|
     * Check programming:        |0x31|0x01|0xFF|0x04|
     * Check programming status: |0x31|0x03|0xFF|0x04|
     *                           |   0|   1|   2|   3|   4|   5|   6|
     * Erase memory:             |0x31|0x01|0xFF|0x00|0x81|0xF0|0x5A|
     *                                               |0x8x|
     * Erase memory status:      |0x31|0x03|0xFF|0x00|
     */
    U16 routineId_u16;
    U8 rcSubFunction_u8;
    U8 diagRoutConSubFunc_u8;
    U8 suppressPos_u8;
    U8 logicalMarker_u8;
    U8 rcStatus_u8 = FALSE;
    U8 flshStatus_u8 = FLS_OK;
    U8 idx_u8;
    U32 ReadCRC;
    U32 CalculatedCRC;
    static BOOLEAN progInit_bo = FALSE;
    static BOOLEAN checkingInProgress_bo = FALSE;
    static SelfCheckStat_t selfcheckFlag; /* Memory status checked in 0x31 */
    static U8 l_Prog_Depend_Checked = TRUE;
    static U8 l_Prog_PreCond_Checked = TRUE;
    static U8 g_App_Cal_Fls_u8 = FALSE;		/* This flag is being used to update the load status with Valid application while flashing the App+Cal software together*/

    static U8 g_Erase_Fls_Sector = FALSE;	/*This flag is used while updating the download counter*/

    /* Check request message type. This service is supported in physical addressing */
    /* In other case there is no response */
    if (PHYS == RxMessageType_u8)
    {
        if (MESSAGE_DATA_LENGTH < RC_MIN_REQ_LENGTH)
        {
            rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
        }
        else
        {

            /* Subfunction identifier */
            diagRoutConSubFunc_u8 = (U8)UDS_data_in.UDS_data.UDS_RoutineControl_msg.subFunc;
            rcSubFunction_u8 = (diagRoutConSubFunc_u8 & SUBFUNCTION_MASK);
            suppressPos_u8 = (diagRoutConSubFunc_u8 & SUPPRESS_POS_RESPONSE);

            /* Erase/Check memory routine id */
            routineId_u16 = (U16)(((U16)UDS_data_in.UDS_data.UDS_RoutineControl_msg.RCIdent_msb << 8U)
                                | ((U16)UDS_data_in.UDS_data.UDS_RoutineControl_msg.RCIdent_lsb));

            /*extract the memory logical address to flash the application or calibration area*/

            memLogicalAddr = GetNBytes(&(UDS_data_in.UDS_data.UDS_RoutineControl_msg.RC_Control_Bytes[0]), sizeof(memLogicalAddr));

            memLogicalAddr = (memLogicalAddr & LOGICAL_ADDR_FLS_BLK_IX_MASK);


            if(memLogicalAddr == APP_AREA_BEG)
            {
            	logicalMarker_u8 = MEMBLK_GLOBAL_IX_PSA;
            	g_App_Cal_Fls_u8 = TRUE;
            }
            else if((memLogicalAddr == CALIB_AREA_BEG) || (memLogicalAddr == MIRROR_CALIB_AREA_BEG))		/*could able to flash with logical and physical addressing*/
            {
            	logicalMarker_u8 = MEMBLK_CALIBRATION_IX_PSA;

            	if(TRUE == g_App_Cal_Fls_u8)
            	{
            		g_App_Cal_Fls_u8 = SUCCESS;
            	}
            	else
            	{
            		;
            	}
            }
            else if(memLogicalAddr == BRP_AREA_BEG)
            {
            	logicalMarker_u8 = MEMBLK_BRP_IX_PSA;
            }
            else
            {
            	logicalMarker_u8 = N_INVALID_MEMBLK;
            }
            switch (routineId_u16)
            {
                case ERASE_MEMORY:
                {
                    	/* Initialize positive response */
                        UDS_data_out.UDS_data.UDS_RoutineControl_resp.subFunc = rcSubFunction_u8;
                        UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_msb = (U8)(ERASE_MEMORY >> 8U);
                        UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_lsb = (U8)(ERASE_MEMORY);
                        UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;

                        switch (rcSubFunction_u8)
                        {
                            case START_ROUTINE:
                            {
                            	UDS_data_out.UDS_data_length = 5U;

                                if (MESSAGE_DATA_LENGTH != RC_ERASE_START_LEN)
                                {
                                    rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                                }
                        		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                                {
                        			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                                }
                                /* Security access required */
                                else if (CheckSecurityAccess() != TRUE)
                                {
                                    rcStatus_u8 = SECURITY_ACCESS_DENIED;
                                }
                                else if ((logicalMarker_u8 != MEMBLK_CALIBRATION_IX_PSA)
                                      && (logicalMarker_u8 != MEMBLK_GLOBAL_IX_PSA)
									  && (logicalMarker_u8 != MEMBLK_BRP_IX_PSA))
                                {
                                    rcStatus_u8 = REQUEST_OUT_OF_RANGE;
                                }
                                else if (EXEC_ROUTINE_ERASE_FLASH == UDSFlashSequence_e)
                                {
                                    /*UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_IN_PROGRESS;*/
                                	rcStatus_u8 = RESPONSE_PENDING;
                                }
                                else if (FIN_ROUTINE_ERASE_FLASH == UDSFlashSequence_e)
                                {
                                    /* To check if entire App area has been successfully erased */
                                    globalBlank_bo = TRUE;
                                    tunBlank_bo = TRUE;

                                    /* To check if BRP area successfully erased */
                                    if(MEMBLK_BRP_IX_PSA == MemBlkIxPSA)
                                    {
                                    	globalBlank_bo &= Fls_secEraseSt[Blocks_table[CAL_AREA_END]];
                                    }
                                    else if(MEMBLK_GLOBAL_IX_PSA == MemBlkIxPSA)
                                    {
                                    	if(Erased_App_Cal_Brp_u8 == TRUE)
                                    	{
                                    		 /* To check if Application and calibration area successfully erased */
                                    		 globalBlank_bo &= Fls_secEraseSt[Blocks_table[CAL_AREA]];

                                    		 for (idx_u8 = APP_START_AREA; idx_u8 <= APP_END_AREA; idx_u8++)
                                    		 {
                                    			 globalBlank_bo &= Fls_secEraseSt[Blocks_table[idx_u8]];
                                    		 }
                                    	}
                                    	else
                                    	{
                                    		 /* To check if BRP, Application and calibration area successfully erased */
                                    		for (idx_u8 = CAL_AREA; idx_u8 <= APP_END_AREA; idx_u8++)
                                    		{
                                    		    globalBlank_bo &= Fls_secEraseSt[Blocks_table[idx_u8]];
                                    		}
                                    	}
                                    }
                                    else if(MEMBLK_CALIBRATION_IX_PSA == MemBlkIxPSA)
                                    {
                                    	/* To check if BRP and calibration area successfully erased */
                                    	tunBlank_bo &= Fls_secEraseSt[Blocks_table[CAL_AREA]];
                                    	tunBlank_bo &= Fls_secEraseSt[Blocks_table[CAL_AREA + 1]];
                                    }
                                    else
                                    {
                                    	;
                                    }

                                    if (((TRUE == globalBlank_bo) && ((MEMBLK_GLOBAL_IX_PSA == MemBlkIxPSA) || (MEMBLK_BRP_IX_PSA == MemBlkIxPSA)))
                                     || ((TRUE == tunBlank_bo) && (MEMBLK_CALIBRATION_IX_PSA == MemBlkIxPSA)))
                                    {
                                        UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;
                                        UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;

                                        g_Erase_Fls_Sector = TRUE;

                                        if((MemBlkIxPSA == MEMBLK_GLOBAL_IX_PSA) &&	(TRUE != Erased_App_Cal_Brp_u8))		/*Added by Rami*/
                                        {
                                        	flshStatus_u8 = FlsProgramLoadStatus(SYS_LOAD_STATUS_CALIB_CLEAN);
                                                                            	/* Deviation 0715 - globally disabled */
                                        	if (flshStatus_u8 != FLS_OK)
                                        	{
                                        		rcStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                                        	}
                                        	else
                                        	{
                                        		rcStatus_u8 = FALSE;

                                        	}
                                        }
                                        else
                                        {
                                        	;
                                        }
                                    }
                                    else
                                    {
                                        /* when erasing failed */
                                    	UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_NOK_X37;
                                        UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
                                    }
                                }
                                else if ((UDSFlashSequence_e != EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI)
                                      && (UDSFlashSequence_e != FIN_ROUTINE_ERASE_FLASH))
                                {
                                    rcStatus_u8 = REQUEST_SEQUENCE_ERROR;
                                }
                                else
                                {
                                	Erase_Routine_Inprog_u8 = TRUE;
                                    /* Logical marker defines which blocks to erase global/calibration*/
                                    MemBlkIxPSA = (MemBlkIxPSA_t) logicalMarker_u8;
                                    /* Variables initialization */
                                    checkingInProgress_bo = FALSE;
                                    tunBlank_bo = FALSE;
                                    globalBlank_bo = FALSE;
                                    writeOk_bo = TRUE;
                                    progInit_bo = TRUE;
                                    StartBlock_u8 = CAL_AREA;
                                    EndBlock_u8 = CAL_AREA_END;

                                    /* Deviation 0715 - globally disabled */
                                    if (MemBlkIxPSA == MEMBLK_BRP_IX_PSA)
                                    {
                                    	StartBlock_u8 = CAL_AREA_END;
                                        EndBlock_u8 = CAL_AREA_END;
                                        Erased_App_Cal_Brp_u8 = TRUE;
                                    }
                                    else if (MemBlkIxPSA == MEMBLK_GLOBAL_IX_PSA)
                                    {
                                    	StartBlock_u8 = CAL_AREA;
                                   		EndBlock_u8 = APP_END_AREA;
                                    }
                                    else
                                    {
                                    	;
                                    }

                                    /*rcStatus_u8 = FALSE;*/
                                    rcStatus_u8 = RESPONSE_PENDING;

                                    UDSFlashSequence_e = EXEC_ROUTINE_ERASE_FLASH;
                                }
                                break;
                            }/* end of START_ROUTINE */

                            case STATUS_ROUTINE:
                            {
                            	UDS_data_out.UDS_data_length = 5U;

                                if (MESSAGE_DATA_LENGTH != RC_ERASE_STATUS_LEN)
                                {
                                    rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                                }
                        		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                                {
                        			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                                }
                                else if (CheckSecurityAccess() != TRUE)
                                {
                                    rcStatus_u8 = SECURITY_ACCESS_DENIED;
                                }
                                else if (((logicalMarker_u8 != MEMBLK_CALIBRATION_IX_PSA)
                                		&& (logicalMarker_u8 != MEMBLK_GLOBAL_IX_PSA)
										&& (logicalMarker_u8 != MEMBLK_BRP_IX_PSA)) && (TRUE == Erase_Routine_Inprog_u8))
                                {
                                	rcStatus_u8 = REQUEST_OUT_OF_RANGE;
                                }
                                else
                                {
                                	if(TRUE == Erase_Routine_Inprog_u8)
                                	{
                                		if (((TRUE == globalBlank_bo) && ((MEMBLK_GLOBAL_IX_PSA == MemBlkIxPSA) || (MEMBLK_BRP_IX_PSA == MemBlkIxPSA)))
                                			|| ((TRUE == tunBlank_bo) && (MEMBLK_CALIBRATION_IX_PSA == MemBlkIxPSA)))
                                		{
                                			UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;
                                		}
                                		else
                                		{
                                			UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_NOK_X37;
                                		}
                                	}
                                	else
                                	{
                                		rcStatus_u8 = REQUEST_SEQUENCE_ERROR;
                                	}
                                }
                                Erase_Routine_Inprog_u8 = FALSE;	/* end of erase routine*/
                                break;
                            } /* end of STATUS_ROUTINE */
                            default:
                            {
                            	rcStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                                break;
                            }
                        }
                    break;
                }/* end of ERASE_MEMORY */

                case CHECK_MEMORY:
                {
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.subFunc = rcSubFunction_u8;
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_msb = (U8)(CHECK_MEMORY >> 8U);
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_lsb = (U8)(CHECK_MEMORY);

                    switch (rcSubFunction_u8)
                    {
                        case START_ROUTINE:
                        {
                            if (MESSAGE_DATA_LENGTH != RC_CHECK_START_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else if ((logicalMarker_u8 != MEMBLK_CALIBRATION_IX_PSA)
                            		&& (logicalMarker_u8 != MEMBLK_GLOBAL_IX_PSA)
									&& (logicalMarker_u8 != MEMBLK_BRP_IX_PSA))
                            {
                            	rcStatus_u8 = REQUEST_OUT_OF_RANGE;
                            }
                            else
                            {
                                if (writeOk_bo != TRUE)
                                {
                                    /* Positive response signalising writing error */
                                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_NOK;
                                    /*UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[1U] = WRITING_ERROR;*/
                                    UDS_data_out.UDS_data_length = 5U;
                                }
                                else
                                {
                                	UDS_data_out.UDS_data_length = 5U;

                                    /* State enabling variables, used during the routine, proper initialization */
                                	tunBlank_bo = FALSE;
                                	globalBlank_bo = FALSE;
                                    selfcheckFlag = SUCCESS;
                                    checkingInProgress_bo = TRUE;

                                    /* Deviation 0310 - globally disabled */
                                   /* CalculatedCRC = Calculate_CRC16CCIT_HW((const U8 *) (&__APV_FLASH_DATA_START_ADDR),
                                            *(((U16*)&__APV_FLASH_CONTENT_SIZE_ADDR)), CRC_CCITT_VALUE);*/

                                    /* Deviation 0308 - globally disabled */
                                    /* Deviation 0310 - globally disabled */
                                   /* CalculatedCRC = Calculate_CRC16CCIT_HW((const U8 *) (&__APV_FLASH_SECTOR_STATUS_ADDR),
                                           (((U32) (&__APV_FLASH_SECTOR_CRC_ADDR)) - ((U32) (&__APV_FLASH_SECTOR_STATUS_ADDR))), CalculatedCRC);*/

                                    CalculatedCRC = Calculate_CRC32CCIT_HW((const U8 *)(&__APV_FLASH_DATA_START_ADDR),
                                                                               ((U32)&__APV_FLASH_SECTOR_CRC_ADDR - (U32)&__APV_FLASH_DATA_START_ADDR), CRC_32_INIT_VALUE);


                                    ReadCRC = (*((U32*)&__APV_FLASH_SECTOR_CRC_ADDR));

                                    if (CalculatedCRC != ReadCRC)
                                    {
                                        selfcheckFlag |= CALIBRATION_FAILED;
                                    }

                                    /* Deviation 0310 - globally disabled */
                                    CalculatedCRC = Calculate_CRC32CCIT_HW((const U8 *) __START_APP_CODE,
                                            ((U32) __APP_CRC - (U32) __START_APP_CODE), CRC_32_INIT_VALUE);

                                    /* Deviation 0310 - globally disabled */
                                    ReadCRC = (*((U32 *) (__APP_CRC)));

                                    if((CalculatedCRC != ReadCRC))
                                    {
                                        selfcheckFlag |= APPLICATION_FAILED;
                                        diagState.invalid_App = TRUE;
                                    }

                                    if((logicalMarker_u8 == MEMBLK_BRP_IX_PSA)||(TRUE == Erased_App_Cal_Brp_u8))
                                    {
                                    	UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;

                                    	if(((Bstrp_CalcChecksum(PROG_BRP_CODE) == 0U) && ((*(__BRP_CODE_SIGN_ADDR)) == (UINT32)0x7E57C0DE)))
                                    	{
                                    		UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_OK;
                                    	}
                                    	else
                                    	{
                                    		UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_NOK;

                                    		/*BRP checksum is wrong, then ECU should stay in boot mode only*/
                                    		Erased_App_Cal_Brp_u8 = FALSE;
                                    	}
                                    }
                                    else
                                    {
                                        UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;

                                        /* Global failed */
                                        if ((APPLICATION_FAILED == (selfcheckFlag & APPLICATION_FAILED)) &&(MEMBLK_GLOBAL_IX_PSA == logicalMarker_u8))
                                        {
                                            UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_NOK;
                                        }
                                        /* Calibration failed */
                                        else if ((CALIBRATION_FAILED == (selfcheckFlag & CALIBRATION_FAILED))&&(MEMBLK_CALIBRATION_IX_PSA == logicalMarker_u8))
                                        {
                                            UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_NOK;

                                        }
                                        else
                                        {
        #if (1 == ZI_READ)
                                            if (progInit_bo == TRUE)
                                            {
                                                authoriseLog_bo = TRUE;
                                            }

                                            /* Positive response */
                                            UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK;
                                            UDS_data_out.UDS_data_length = 5U;
        #else

                                            if((SUCCESS == g_App_Cal_Fls_u8)&&(SUCCESS == selfcheckFlag)&&(TRUE == g_Erase_Fls_Sector))
                                            {
                                            	g_App_Cal_Fls_u8 = FALSE;

                                            	g_ApplStatus_bo = TRUE;

                                            }
                                            else if((MEMBLK_CALIBRATION_IX_PSA == logicalMarker_u8)&&(SUCCESS == selfcheckFlag)&&(TRUE == g_Erase_Fls_Sector))
                                            {
                                            	g_ApplStatus_bo = TRUE;
                                            }
                                            else
                                            {
                                            	g_ApplStatus_bo = FALSE;

                                            	if(TRUE == g_Erase_Fls_Sector)
                                            	{
                                            		flshStatus_u8 = FlsProgramLoadStatus(SYS_LOAD_STATUS_CALIB_CLEAN);
                                            	}
                                            	else
                                            	{
                                            		;
                                            	}
                                            }
        #endif
                                        }
                                    }

                                }
                            }
                            break;
                        } /* end of START_ROUTINE */

                        case STATUS_ROUTINE:
                        {

                        	UDS_data_out.UDS_data_length = 5U;

                            if (MESSAGE_DATA_LENGTH != RC_CHECK_STATUS_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else if (TRUE != checkingInProgress_bo)				/* As per IS0-14229-1 spec given NRC 24 as highest priority instead of NRC 31 */
                            {
                                rcStatus_u8 = REQUEST_SEQUENCE_ERROR;
                            }
                            else if ((logicalMarker_u8 != MEMBLK_CALIBRATION_IX_PSA)
                            		&& (logicalMarker_u8 != MEMBLK_GLOBAL_IX_PSA)
									&& (logicalMarker_u8 != MEMBLK_BRP_IX_PSA))
                            {
                            	rcStatus_u8 = REQUEST_OUT_OF_RANGE;
                            }
                            else
                            {
                            	if(SUCCESS == selfcheckFlag)
                            	{
                            		/* Positive response */
                            		UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_OK;
                            	}
                            	else
                            	{
                            		/* Failed response */
                            		UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = CHK_MEMORY_ROUTINE_NOK;
                            	}
                            }

                            break;
                        } /* end of STATUS_ROUTINE */
                        default:
                        {
                       		rcStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                            break;
                        }
                    }
                    break;
                } /* end of CHECK_MEMORY */
                case CHECK_PROGRAM_DEPENDENCIES:
                {
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.subFunc = rcSubFunction_u8;
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_msb = (U8)(CHECK_PROGRAM_DEPENDENCIES >> 8U);
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_lsb = (U8)(CHECK_PROGRAM_DEPENDENCIES);

                    switch (rcSubFunction_u8)
                    {
                        case START_ROUTINE:
                        {
                            if (MESSAGE_DATA_LENGTH != RC_START_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else
                            {
                            	UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;
                                UDS_data_out.UDS_data_length = 5U;
                				l_Prog_Depend_Checked = FALSE;
                            }
                            break;
                        } /* end of START_ROUTINE */

                        case STATUS_ROUTINE:
                        {
                            if (MESSAGE_DATA_LENGTH != RC_STATUS_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else if (FALSE != l_Prog_Depend_Checked)
                            {
                                rcStatus_u8 = REQUEST_SEQUENCE_ERROR;

                            }
                            else
                            {
                            	UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;
                                UDS_data_out.UDS_data_length = 5U;
                				/*l_Prog_Depend_Checked = SUCCESS;*/
                                l_Prog_Depend_Checked = TRUE;
                            }
                            break;
                        } /* end of STATUS_ROUTINE */
                        default:
                        {
                        	rcStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                            break;
                        }
                    }
                    break;
                } /* end of CHECK_PROGRAMMING_DEPENDENCIES ROUTINE */
                case CHECK_VEH_ENG_SPEED:
                {
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.subFunc = rcSubFunction_u8;
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_msb = (U8)(CHECK_VEH_ENG_SPEED >> 8U);
                    UDS_data_out.UDS_data.UDS_RoutineControl_resp.RCIdent_lsb = (U8)(CHECK_VEH_ENG_SPEED);

                    switch (rcSubFunction_u8)
                    {
                        case START_ROUTINE:
                        {
                            if (MESSAGE_DATA_LENGTH != RC_START_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != EXTENDED_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckDevCtrlSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else
                            {
                            	UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;
                                UDS_data_out.UDS_data_length = 5U;
                                l_Prog_PreCond_Checked =  FALSE;
                            }
                            break;
                        } /* end of START_ROUTINE */

                        case STATUS_ROUTINE:
                        {
                            if (MESSAGE_DATA_LENGTH != RC_STATUS_LEN)
                            {
                                rcStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                            }
                    		else if(CurrentDiagnosticSession_u8 != EXTENDED_SESSION)
                            {
                    			rcStatus_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            else if (CheckDevCtrlSecurityAccess() != TRUE)
                            {
                                rcStatus_u8 = SECURITY_ACCESS_DENIED;
                            }
                            else if (FALSE != l_Prog_PreCond_Checked)
                            {
                               rcStatus_u8 = REQUEST_SEQUENCE_ERROR;
                            }
                            else
                            {
                            	UDS_data_out.UDS_data.UDS_RoutineControl_resp.RC_Result_bytes[0U] = ROUTINE_OK_X37;

                                UDS_data_out.UDS_data_length = 5U;

                                l_Prog_PreCond_Checked =  TRUE;
                            }
                            break;
                        } /* end of STATUS_ROUTINE */
                        default:
                        {
                        	rcStatus_u8 = SUBFUNCTION_NOT_SUPPORTED;
                            break;
                        }
                    }
                    break;
                } /* end of CHECK_VEH_ENG_SPEED ROUTINE */
                default:
                {
                    /* When incorrect routine id received */
                    rcStatus_u8 = REQUEST_OUT_OF_RANGE;
                    break;
                }
            }

            if ((0U != UDS_data_out.UDS_data_length) && (0U != suppressPos_u8))
            {
                /* no response! */
                UDS_data_out.UDS_data_length = 0U;
            }
        }

        if (rcStatus_u8 != FALSE)
        {
            send_negative_response(rcStatus_u8);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}

#if 0
/******************************************************************************/
/*                                                                            */
/*  Function    : read_data_by_identifier                                     */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*  This function validates the ID, message format and reads the required data*/
/*  from the unit and constructs the response data positive response message. */
/*                                                                            */
/******************************************************************************/
static void read_data_by_identifier(void)
{
    U8 *p;
    U16 dataIdent;
    U8 i;
    U8 status_u8 = 0U;
    U8 notValidDIDCount = 0U;

    /* Check request message type. This service is supported in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
        /* Check that the request length is greater than or equal to the minimum request length and */
        /* Request length is odd(as request = SID + n*2_byte_DID, where n=no of DIDs to be read)    */
        if ((RDBI_REQ_LENGTH <= MESSAGE_DATA_LENGTH) && (1U == (MESSAGE_DATA_LENGTH % 2U)))
        {
            if ((MESSAGE_DATA_LENGTH - 1U) <= (2U * MAX_NUM_DID_READ))
            {
                p = &UDS_data_out.UDS_data.UDS_ReadDataByIdent_resp.Read_data_buf[0];

                for (i = 0U; i < (MESSAGE_DATA_LENGTH - 1U); i = (i + 2U))
                {
                    dataIdent = ((U16)UDS_data_in.UDS_data.UDS_ReadDataByIdent_msg.RDBI_DID[i] << 8U)
                              + ((U16)UDS_data_in.UDS_data.UDS_ReadDataByIdent_msg.RDBI_DID[i + 1U]);

                    /* Assume a positive response - write DID to response buffer */
                    *p = UDS_data_in.UDS_data.UDS_ReadDataByIdent_msg.RDBI_DID[i];
                    /*  DEVIATION:     0489
                        DESCRIPTION:   Increment or decrement operation performed on pointer.
                        JUSTIFICATION: This is done for accessing different elements of the array,
                                       it is analyzed and causes no issues */
                    /* PRQA S 0489 1040 */
                    p++;
                    *p = UDS_data_in.UDS_data.UDS_ReadDataByIdent_msg.RDBI_DID[i + 1U];
                    p++;
                    UDS_data_out.UDS_data_length += 2U;

                    switch (dataIdent)
                    {
                    	case DID_BOOTLOADER_VER:
                    	{
                    		if(MESSAGE_DATA_LENGTH != DID_BOOTLOADER_VER_REQ_SIZE)
                    		{
                    			status_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                    		}
                    		else
                    		{
                    			*p =  Boot_ID_short_name[6];		/*boot loader version getting from short name*/
                    			p++;
                    			*p = Boot_ID_short_name[7];
                    			UDS_data_out.UDS_data_length += DID_BOOTLOADER_VER_RSP_SIZE;
                    			p++;
                    		}
                    		break;
                    	}

#if 0
                        case DID_ACTIVE_DIAG_SESSION:
                        {
                            copy_data((const U8 *)&CurrentDiagnosticSession_u8, p, DID_ACTIVE_DIAG_SESSION_SIZE);
                            UDS_data_out.UDS_data_length += DID_ACTIVE_DIAG_SESSION_SIZE;
                            p += DID_ACTIVE_DIAG_SESSION_SIZE;
                            break;
                        }
                        case DID_PROGRAM_DATE:
                        {
                        	status_u8 = RDBI_ECU_Programming_Date(p);
                        	/* Negative response will be sent */
                        	if (0U != status_u8)
                        	{
                        	    UDS_data_out.UDS_data_length -= 2U;
                        	    /* need to decrement the pointer to ignore the DID values */
                        	    p -= 2U;
                        	}
                        	 /* Manufacturing date will be sent */
                        	else
                        	{
                        	     /* 3 bytes of manufacturing date */
                        	    UDS_data_out.UDS_data_length += DID_PROGRAM_DATE_RESP_SIZE;
                        	     /* Increment pointer of output buffer */
                        	    p += DID_PROGRAM_DATE_RESP_SIZE;
                        	 }
                        	 break;
                        }
                        case DID_PROGRAM_COUNTER:
                        {
							status_u8 = RDBI_ECU_Programming_Counter(p);
							/* Negative response will be sent */
							if (0U != status_u8)
							{
								UDS_data_out.UDS_data_length -= 2U;
								/* need to decrement the pointer to ignore the DID values */
								p -= 2U;
							}
							 /* Manufacturing date will be sent */
							 else
							 {
								 /* 3 bytes of manufacturing date */
								 UDS_data_out.UDS_data_length += DID_PROGRAM_COUNTER_RESP_SIZE;
								 /* Increment pointer of output buffer */
								 p += DID_PROGRAM_COUNTER_RESP_SIZE;
							 }
							 break;
                        }
                        case DID_AUTHEN_ZONE:
                        {
                            status_u8 = RDBI_identSys(p);
                            if (0U != status_u8)
                            {
                                UDS_data_out.UDS_data_length -= 2U;
                                /* need to decrement the pointer to ignore the DID values */
                                p -= 2U;
                            }
                            else
                            {
                                UDS_data_out.UDS_data_length += DID_AUTHEN_ZONE_SIZE;
                                /* Deviation 0488 - globally disabled */
                                p += DID_AUTHEN_ZONE_SIZE;
                            }
                            break;
                        }
#if (1 == ZI_ENABLE)
                        case DID_ZI_READ:
                        {
                            status_u8 = RDBI_readZI(p);
                            if (0U != status_u8)
                            {
                                UDS_data_out.UDS_data_length -= 2U;
                                /* need to decrement the pointer to ignore the DID values */
                                p -= 2U;
                            }
                            else
                            {
                                UDS_data_out.UDS_data_length += ZI_DATA_LENGTH / 2U;
                                /* Deviation 0488 - globally disabled */
                                p += ZI_DATA_LENGTH / 2U;
                            }
                            break;
                        }
#endif
                        case DID_SERIAL_NUM_DATA_IDENT_LEN:
                        {
                            /* This DID is supported only in physical addressing */
                            if (PHYS == RxMessageType_u8)
                            {
                                status_u8 = RDBI_ECU_Serial_Number_Length(p);
                                /* Negative response will be sent */
                                if (0U != status_u8)
                                {
                                    UDS_data_out.UDS_data_length -= 2U;
                                    /* need to decrement the pointer to ignore the DID values */
                                    p -= 2U;
                                }
                                /* Data will be sent */
                                else
                                {
                                    /* 1 byte of data */
                                    UDS_data_out.UDS_data_length += 1U;
                                    /* Increment pointer of output buffer */
                                    p += 1U;
                                }
                            }
                            else
                            {
                                notValidDIDCount += 2U;
                                /*  DEVIATION:     0488
                                    DESCRIPTION:   Performing pointer arithmetic.
                                    JUSTIFICATION: This is done for incrementing the output buffer
                                                   pointer by the size of the DID data, it is required*/
                                /* PRQA S 0488 2*/
                                p -= 2U;
                                UDS_data_out.UDS_data_length -= 2U;
                            }
                            break;
                        }
                        case DID_SERIAL_NUM_DATA_IDENT:
                        {
                            status_u8 = RDBI_ECU_Serial_Number(p);

                            /* Negative response will be sent */
                            if (0U != status_u8)
                            {
                                UDS_data_out.UDS_data_length -= 2U;
                                /* need to decrement the pointer to ignore the DID values */
                                p -= 2U;
                            }
                            /* Serial number will be sent */
                            else
                            {
                                /* 9 bytes of number */
                                UDS_data_out.UDS_data_length += ECU_SERIAL_NUMBER_LENGTH;
                                /* Increment pointer of output buffer */
                                p += ECU_SERIAL_NUMBER_LENGTH;
                            }
                            break;
                        }

                        case DID_ECU_MANUFACTURING_DATE:
                        {
                            status_u8 = RDBI_ECU_Manufacturing_Date(p);
                            /* Negative response will be sent */
                            if (0U != status_u8)
                            {
                                UDS_data_out.UDS_data_length -= 2U;
                                /* need to decrement the pointer to ignore the DID values */
                                p -= 2U;
                            }
                            /* Manufacturing date will be sent */
                            else
                            {
                                /* 3 bytes of manufacturing date */
                                UDS_data_out.UDS_data_length += ECU_MANUFACTURING_DATE_LENGTH;
                                /* Increment pointer of output buffer */
                                p += ECU_MANUFACTURING_DATE_LENGTH;
                            }
                            break;
                        }
                        case DID_ECU_PART_NUMBER:
                        {

                        	if (PHYS == RxMessageType_u8)
                        	{
                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        		}
                        		else
                        		{
									for (i=0;i<DID_ECU_PART_NUMBER_SIZE;i++)
									{
										*p = (i + '0');
										 p++;	/* Increment pointer of output buffer */
									}
	                        		/* 3 bytes of manufacturing date */
	                        		UDS_data_out.UDS_data_length += DID_ECU_PART_NUMBER_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        	break;
                     	}
                        case DID_ECU_SUPPLIER_NUMBER:
                        {

                        	if (PHYS == RxMessageType_u8)
                        	{
                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        		}
                        		else
                        		{
									for (i=0;i<DID_ECU_SUPPLIER_NUMBER_SIZE;i++)
									{
										*p = (i + '0');
										p++;
									}
									/* 3 bytes of manufacturing date */
									UDS_data_out.UDS_data_length += DID_ECU_SUPPLIER_NUMBER_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        	break;
                        }
                        case DID_ECU_RADAR_TYPE:
                        {

                        	if (PHYS == RxMessageType_u8)
                        	{

                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        		}
                        		else
                        		{

									*p = 0x01;
									 p++;
									 /* 3 bytes of manufacturing date */
									 UDS_data_out.UDS_data_length += DID_ECU_RADAR_TYPE_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        		/* Increment pointer of output buffer */
                        	break;
                        }
                        case DID_ECU_HARDWARE_VERSION:
                        {

                        	if (PHYS == RxMessageType_u8)
                        	{
                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        		}
                        		else
                        		{

									*p = (U8)ConvertHexToBCD(0x25);
									 p++;
									*p = (U8)ConvertHexToBCD(0x36);
									 p++;
									 /* 3 bytes of manufacturing date */
									 UDS_data_out.UDS_data_length += DID_ECU_HARDWARE_VERSION_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        		/* Increment pointer of output buffer */
                        	break;
                        }
                        case DID_ECU_SOFTWARE_VERSION:
                        {
                        	if (PHYS == RxMessageType_u8)
                        	{
                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        			break;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        			break;
                        		}
                        		else
                        		{
									*p = (U8)ConvertHexToBCD(0x36);
									 p++;
									*p = (U8)ConvertHexToBCD(0x25);
									 p++;
									 /* 3 bytes of manufacturing date */
									 UDS_data_out.UDS_data_length += DID_ECU_SOFTWARE_VERSION_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        		/* Increment pointer of output buffer */
                        	break;
                        }
                        case DID_ECU_CALIBRATION_SOFTWARE_VERSION:
                        {
                        	if (PHYS == RxMessageType_u8)
                        	{
                        		if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
                        		{
                        			status_u8 = SUBFUNCTION_NOT_SUPPORTED;
                        		}
                        		else if (CheckSecurityAccess() != TRUE)
                        		{
                        			status_u8 = SECURITY_ACCESS_DENIED;
                        		}
                        		else
                        		{
									*p = (U8)ConvertHexToBCD(0x25);
									 p++;
									*p = (U8)ConvertHexToBCD(0x15);
									 p++;
									 /* 3 bytes of manufacturing date */
									 UDS_data_out.UDS_data_length += DID_ECU_CALIBRATION_SOFTWARE_VERSION_SIZE;
                        		}
                        	}
                        	else
                        	{
                        		 notValidDIDCount += 2U;
                        		 /*  DEVIATION:     0488
                        		     DESCRIPTION:   Performing pointer arithmetic.
                        		     JUSTIFICATION: This is done for incrementing the output buffer
                        		                    pointer by the size of the DID data, it is required*/
                        		 /* PRQA S 0488 2*/
                        		 p -= 2U;
                        		 UDS_data_out.UDS_data_length -= 2U;
                        	}
                        	break;
                        }
#endif
                        default:
                        {
                            notValidDIDCount += 2U;
                            /*  DEVIATION:     0488
                                DESCRIPTION:   Performing pointer arithmetic.
                                JUSTIFICATION: This is done for incrementing the output buffer
                                               pointer by the size of the DID data, it is required*/
                            /* PRQA S 0488 2*/
                            p -= 2U;
                            UDS_data_out.UDS_data_length -= 2U;
                            break;
                        }
                        /*  DEVIATION:     3352
                            DESCRIPTION:   This 'switch' statement contains only two paths.
                            JUSTIFICATION: When more DIDs will be added this warning will be removed */
                        /* PRQA S 3352 1*/
                    }
                }

                if (notValidDIDCount == (MESSAGE_DATA_LENGTH - 1U))
                {
                    send_negative_response(REQUEST_OUT_OF_RANGE);
                }
                else if (0U != status_u8)
                {
                    send_negative_response(status_u8);
                }
                else
                {
                    ;
                }
            }
            else
            {
                send_negative_response(REQUEST_OUT_OF_RANGE);
            }

        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}
#endif

/******************************************************************************/
/*                                                                            */
/*  Function    : write_data_by_identifier                                     */
/*                                                                            */
/*  Parameters  : void                                                        */
/*                                                                            */
/*  Returns     : void                                                        */
/*                                                                            */
/*  Description :                                                             */
/*  This function validates the ID, message format and writes the required data*/
/*  into NVM and constructs the response data positive response message. */
/*                                                                            */
/******************************************************************************/
static void write_data_by_identifier(void)
{

    U16 dataIdent;
    U8 	status_u8 = 0u;
    U8 emptyHistoryLocation_u8 = 0;
    U8 Program_Counter_u8 = 0;


	dataIdent = (((U16)(UDS_data_in.UDS_data.UDS_WriteDataByIdentifier_msg.dataIdent_msb) << 8U)

		| ((U16)UDS_data_in.UDS_data.UDS_WriteDataByIdentifier_msg.dataIdent_lsb));


    /* Check request message type. This service is supported in physical and functional addressing */
    /*if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))*/
    /*As per the system requirement,WDBI 2E service supported only with Physical addressing*/
    if(PHYS == RxMessageType_u8)
    {
    		if(MESSAGE_DATA_LENGTH < WDBI_REQ_LENGTH)
    		{
    			status_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
    		}
    		else if(CurrentDiagnosticSession_u8 != PROGRAM_SESSION)
            {
            	status_u8 = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
            }
			else
			{
				switch (dataIdent)
				{
					case DID_PROGRAMM_DATE:
					{
						if(MESSAGE_DATA_LENGTH == DID_PROGRAM_DATE_SIZE)
						{
				            if (CheckSecurityAccess() != TRUE)
				            {
				            	status_u8 = SECURITY_ACCESS_DENIED;
				            }
				            else
				            {
								 if (TRUE == GetEmptyHistoryZoneIdx_ProgrammingDate(&emptyHistoryLocation_u8))
				            	 {
				            		 if(emptyHistoryLocation_u8 == 0x00)
				            		 {
				            			 Program_Counter_u8 = 1;
				            		 }
				            		 else
				            		 {
				            			 emptyHistoryLocation_u8--;

				            			 Program_Counter_u8 = ((uint8_t)((historyRecording_2_au8[emptyHistoryLocation_u8][4u])) + 1u);

				            			 if(Program_Counter_u8 >= 0xFF)
				            			 {
				            				 Program_Counter_u8 = 0xFF;
				            			 }
				            			 ++emptyHistoryLocation_u8;
				            		 }
				            		 UDS_data_in.UDS_data.UDS_WriteDataByIdentifier_msg.Write_Data_Bytes[4u] = Program_Counter_u8;

				            		 status_u8 = UDS_FlashWrite((U32) historyRecording_2_au8[emptyHistoryLocation_u8],
				            		                                        (U8 *) &UDS_data_in.UDS_data.UDS_WriteDataByIdentifier_msg.Write_Data_Bytes[0u],
				            		                                        ZI_DATA_LENGTH);
				            		 if(status_u8 != FLASH_OK)
				            		 {
				            		 	writeOk_bo = FALSE;
				            		 	status_u8 = GENERAL_PROGRAMMING_FAILURE;
				            		 }
				            		 else
				            		 {
				            		 	status_u8 = FALSE;
				            		 }
				            	 }
				            	 else
				            	 {
				            		 status_u8 = FALSE;
				            	 }
				            }
 						}
						else
						{
							status_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
						}
						break;
					}
					case DID_FINGERPRINT_DATA:
					{
						if(MESSAGE_DATA_LENGTH == DID_FINGERPRINT_DATA_SIZE)
						{
					        if (CheckSecurityAccess() != TRUE)
					        {
					        	status_u8 = SECURITY_ACCESS_DENIED;
					        }
					        else
					        {
								 if (TRUE == GetEmptyHistoryZoneIdx_FingerPrint(&emptyHistoryLocation_u8))
					        	 {

					        		 status_u8 = UDS_FlashWrite((U32) historyRecording_1_au8[emptyHistoryLocation_u8],
					        		                                        (U8 *) &UDS_data_in.UDS_data.UDS_WriteDataByIdentifier_msg.Write_Data_Bytes[0u],
					        		                                        ZI_DATA_LENGTH);
					        		 if(status_u8 != FLASH_OK)
					        		 {
					        		 	writeOk_bo = FALSE;
					        		 	status_u8 = GENERAL_PROGRAMMING_FAILURE;
					        		 }
					        		 else
					        		 {
					        		 	status_u8 = FALSE;
					        		 }
					        	 }
					        	 else
					        	 {
					        		 status_u8 = FALSE;
					        	 }
					        }
						}
						else
						{
							status_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
						}
						break;
					}
					default:
					{
						status_u8 = REQUEST_OUT_OF_RANGE;
						break;
					}
				}
			}
			if(status_u8 != FALSE)
			{
				 send_negative_response(status_u8);
			}
			else
			{
				 UDS_data_out.UDS_data.UDS_WriteDataByCommon_resp.dataIdent_msb = (U8)((dataIdent>>8) & 0xFF);
				 UDS_data_out.UDS_data.UDS_WriteDataByCommon_resp.dataIdent_lsb = (U8)(dataIdent & 0xFF);
				 UDS_data_out.UDS_data_length = WD_RESPONSE_LENGTH;
			}
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}

/******************************************************************************
 * Name         :  UDS_RequestDownload
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  May be called after service request was received
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Init of download
 ******************************************************************************/
static void UDS_RequestDownload(void)
{
    U8 rdStatus_u8 = FALSE;
    U32 memSize;

    memSize = GetNBytes(&(UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_size[0]), sizeof(memSize));

    memLogicalAddr = GetNBytes(&(UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_Add[0]), sizeof(memLogicalAddr));

    memLogicalAddr = (memLogicalAddr & LOGICAL_ADDR_FLS_BLK_IX_MASK);

    ReceMemSize = memSize;

	if(memLogicalAddr == BRP_AREA_BEG)
	{
		MemBlkIxPSA = MEMBLK_BRP_IX_PSA;
	}
	else if((memLogicalAddr >= APP_AREA_BEG) && (memLogicalAddr < APP_AREA_END))
	{
		MemBlkIxPSA = MEMBLK_GLOBAL_IX_PSA;
	}
	else if(((memLogicalAddr >= CALIB_AREA_BEG) && (memLogicalAddr < CALIB_AREA_END)) || ((memLogicalAddr >= MIRROR_CALIB_AREA_BEG) && (memLogicalAddr < MIRROR_CALIB_AREA_END)))
	{
		MemBlkIxPSA = MEMBLK_CALIBRATION_IX_PSA;
	}
	else
	{
		MemBlkIxPSA = N_INVALID_MEMBLK;
	}

    /* Check request message type. This service is supported in physical addressing */
    /* In other case there is no response */
    if (PHYS == RxMessageType_u8)
    {
    		if (REQ_DOWNLOAD_FORMAT_LEN != UDS_data_in.UDS_data_length)
    		{
    			rdStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
    		}

            /*  REQUEST FORMAT
             * | 00 | 01 | 02 | 03 | 04 |
             * |0x34|0x81|0x11| 00 | 00 | Calibration
             * |0x34|0x82|0x11| 00 | 00 | Global*/

            /* Check parameters */
            /* DEVIATION:     3355, 3356
               DESCRIPTION:   The result of this logical operation is always 'true' (3355).
                              The result of this logical operation is always 'false' (3356).
               JUSTIFICATION: It is done deliberately to show possible options.
             */
            /* PRQA S 3355 19 *//* PRQA S 3356 19 */
#if (1 == KEY_APPLI_CHANGE_ENABLED)
    		else if (((UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_CALIBRATION_IX_PSA)
                   && (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_GLOBAL_IX_PSA)
                   && (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_ZI_IX_PSA)
                   && (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_KEY_APPLI_IX_PSA))
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.addLenFmtId != NUMBER_OF_PARAMETERS)
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_Add != PARAMETER_MA)
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_size != PARAMETER_MS))
#else
#if (1 == ZI_READ)
            else if (((UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_CALIBRATION_IX_PSA)
                   && (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_GLOBAL_IX_PSA)
                   && (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != MEMBLK_ZI_IX_PSA))
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.addLenFmtId != NUMBER_OF_PARAMETERS)
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_Add != PARAMETER_MA)
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.mem_size != PARAMETER_MS))
#else
            else if (((MemBlkIxPSA != MEMBLK_CALIBRATION_IX_PSA)
           	       && (MemBlkIxPSA != MEMBLK_GLOBAL_IX_PSA)
				   && (MemBlkIxPSA != MEMBLK_BRP_IX_PSA))
                  || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.addLenFmtId != PARAMETER_AALFI)
           	      || (UDS_data_in.UDS_data.UDS_ReqDwnLd_msg.dataFmtId != PARAMETER_DFI)
                  || (memSize == PARAMETER_MS))
#endif
#endif
            {
                rdStatus_u8 = REQUEST_OUT_OF_RANGE;
            }
            else if (CheckSecurityAccess() != TRUE)
            {
                  rdStatus_u8 = SECURITY_ACCESS_DENIED;
            }
            else if(TRANSFER_DATA == UDSFlashSequence_e)
            {
            	rdStatus_u8 = CONDITIONS_NOT_CORRECT;
            }
            else
            {
                switch (MemBlkIxPSA)
                {
                    case MEMBLK_CALIBRATION_IX_PSA:
                    {
                    	if (tunBlank_bo != TRUE)
                        {
                            rdStatus_u8 = UPLOAD_DOWNLOAD_NOT_ACCEPTED;
                        }
                        else
                        {
                            UDSFlashSequence_e = TRANSFER_DATA;
                        }
                        break;
                    }

                    case MEMBLK_GLOBAL_IX_PSA:
                    {
                    	if (globalBlank_bo != TRUE)
                        {
                            rdStatus_u8 = UPLOAD_DOWNLOAD_NOT_ACCEPTED;
                        }
                        else
                        {
                            UDSFlashSequence_e = TRANSFER_DATA;
                        }
                        break;
                    }
                    case MEMBLK_BRP_IX_PSA:
                    {
                    	if (globalBlank_bo != TRUE)
                        {
                            rdStatus_u8 = UPLOAD_DOWNLOAD_NOT_ACCEPTED;
                        }
                        else
                        {
                            UDSFlashSequence_e = TRANSFER_DATA;
                        }
                        break;
                    }

#if 0
                    case MEMBLK_ZI_IX_PSA:
                    {
                        if (TRUE != authoriseLog_bo)
                        {
                            rdStatus_u8 = UPLOAD_DOWNLOAD_NOT_ACCEPTED;
                        }
                        else
                        {
                            UDSFlashSequence_e = TRANSFER_ZI;
                        }
                        break;
                    }
#endif
#if (1 == KEY_APPLI_CHANGE_ENABLED)
                    case MEMBLK_KEY_APPLI_IX_PSA:
                    {
                        UDSFlashSequence_e = TRANSFER_KEY_APPLI;
                        break;
                    }
#endif
                     /* DEVIATION:     2018
                        DESCRIPTION:   This switch default label is unreachable.
                        JUSTIFICATION: The default case will be retained for unexpected values
                     */
                     /* PRQA S 2018 1 */
                    default:
                    {
                        rdStatus_u8 = REQUEST_OUT_OF_RANGE;
                        break;
                    }
                }
            }

        if (rdStatus_u8 == FALSE)
        {
        	/* reset the transfer data initiated block flag*/

        	UDS_TD_Initiated = FALSE;
            /* Reset sequence counter to next expected value */
            TransferSequenceCounter_u8 = 1;
            /* Generate a positive response ... */
            UDS_data_out.UDS_data.UDS_ReqDwnLd_resp.lenFmtId = LENGTH_FMT_ID;
            UDS_data_out.UDS_data.UDS_ReqDwnLd_resp.maxNumOfBlockLen[0] = FALSE;
            UDS_data_out.UDS_data.UDS_ReqDwnLd_resp.maxNumOfBlockLen[1] = FALSE;
            UDS_data_out.UDS_data.UDS_ReqDwnLd_resp.maxNumOfBlockLen[2] = ((MAX_NUMBER_OF_BLOCK_LENGTH >> (U8)0x08U) & (U8)0xFF);
            UDS_data_out.UDS_data.UDS_ReqDwnLd_resp.maxNumOfBlockLen[3] = (MAX_NUMBER_OF_BLOCK_LENGTH & (U8)0xFF);
            UDS_data_out.UDS_data_length = RD_RESPONSE_LENGTH;
        }
        else
        {
            send_negative_response(rdStatus_u8);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0;
    }
}

/******************************************************************************
 * Name         :  UDS_TransferData
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  May be called after service request was received
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Receive the data to be downloaded
 ******************************************************************************/
static void UDS_TransferData(void)
{
    U8 tdStatus_u8 = FALSE;
    U8 flshStatus_u8 = FLASH_OK;
    /* Destination start address of data block to be flashed */
    volatile static U32 address_u32 = CALIB_AREA_BEG;
    U8 rxBlockCounter_u8;
    U16 curBlkSize_u8;
    U16 tdSize_u8 = MAX_NUMBER_OF_BLOCK_LENGTH;
#if (1 == ZI_READ)
    BOOLEAN ziStatus_bo = TRUE;
    U16 emptyHistoryLocation_u16;
#endif
    U16 batVoltage_u16;
    U8 batteryStatus_u8 = 0U;
    U8 index_u8;

    /* Check request message type. This service is supported in physical addressing */
    /* In other case there is no response */
    if (PHYS == RxMessageType_u8)
    {
        /* Get battery voltage */
        if (Mcu_Read_ADC() == READ_ADC_SUCCESS)
        {
            batVoltage_u16 = Mcu_Get_ADC(ADC_VBAT_MON);

            /* When battery voltage is too low */
            if (batVoltage_u16 < MIN_VBAT_COUNT)
            {
                batteryStatus_u8 = VOLTAGE_TOO_LOW;
            }
            /* When battery voltage is too high */
            else if (batVoltage_u16 > MAX_VBAT_COUNT)
            {
                batteryStatus_u8 = VOLTAGE_TOO_HIGH;
            }
            /* When battery voltage is between MIN and MAX, then it is assumed that is ok */
            else
            {
                batteryStatus_u8 = 0U;
            }
        }
        else
        {
            batteryStatus_u8 = 0U;
        }

        rxBlockCounter_u8 = UDS_data_in.UDS_data.UDS_TransData_msg.Data.blockSeqCounter;

        curBlkSize_u8 = (UDS_data_in.UDS_data_length - MIN_TRANSFER_DATA_LENGTH);

        /* Minimum length check */
        if (UDS_data_in.UDS_data_length < TRANSFER_DATA_DWNLD_MIN_LEN)
        {
            tdStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
        }
#if (1 == KEY_APPLI_CHANGE_ENABLED)
        else if ((UDSFlashSequence_e != TRANSFER_DATA)
              && (UDSFlashSequence_e != TRANSFER_ZI)
              && (UDSFlashSequence_e != TRANSFER_KEY_APPLI))
#else
#if (1 == ZI_READ)
        else if ((UDSFlashSequence_e != TRANSFER_DATA)
              && (UDSFlashSequence_e != TRANSFER_ZI))
#else
        else if (UDSFlashSequence_e != TRANSFER_DATA)
#endif
#endif
        {
            tdStatus_u8 = REQUEST_SEQUENCE_ERROR;
        }
        else if (curBlkSize_u8 > (tdSize_u8 - MIN_TRANSFER_DATA_LENGTH))
        {
            tdStatus_u8 = TRANSFER_DATA_SUSPENDED;
        }
        else if (rxBlockCounter_u8 == TransferSequenceCounter_u8)
        {
                switch (MemBlkIxPSA)
                {
                    case MEMBLK_CALIBRATION_IX_PSA:
                    case MEMBLK_GLOBAL_IX_PSA:
                    case MEMBLK_BRP_IX_PSA:
                    {
                    	rxBlockCounter_u8 = UDS_data_in.UDS_data.UDS_TransData_msg.Data.blockSeqCounter;

                        if((MemBlkIxPSA == MEMBLK_CALIBRATION_IX_PSA)&&(UDS_TD_Initiated == FALSE))
                        {
                        	address_u32 = (memLogicalAddr & 0x00FFFFFF);;
                        	UDS_TD_Initiated = TRUE;
                        }
                        else if((MemBlkIxPSA == MEMBLK_GLOBAL_IX_PSA)&&(UDS_TD_Initiated == FALSE))
                        {
                        	address_u32 = (memLogicalAddr & LOGICAL_ADDR_FLS_BLK_IX_MASK);
                        	UDS_TD_Initiated = TRUE;
                        }
                        else if((MemBlkIxPSA == MEMBLK_BRP_IX_PSA)&&(UDS_TD_Initiated == FALSE))
                        {
                        	address_u32 = BRP_AREA_BEG;
                        	UDS_TD_Initiated = TRUE;
                        }
                        else
                        {
                        	;
                        }
                        /* Check if the client is not sending more data than requested. */


                        /* DEVIATION:     3355
                        DESCRIPTION:   The result of this logical operation is always 'true'.
                        JUSTIFICATION: It is done deliberately to show possible options.
                        */
                        /* PRQA S 3355 5 */
#if 0
                        if ((((address_u32 + tdSize_u8) > CALIB_AREA_END) || (address_u32 < CALIB_AREA_BEG))
                              && ((MemBlkIxPSA == MEMBLK_CALIBRATION_IX_PSA)
                               || ((MemBlkIxPSA == MEMBLK_GLOBAL_IX_PSA)
                                && (((address_u32 + tdSize_u8) > APP_AREA_END) || (address_u32 < APP_AREA_BEG)))))
#else
                        /*else if (((MEMBLK_CALIBRATION_IX_PSA == MemBlkIxPSA)
                               && (((address_u32 + (tdSize_u8 - MIN_TRANSFER_DATA_LENGTH)) > CALIB_AREA_END) || (address_u32 < CALIB_AREA_BEG)))
                              || ((MEMBLK_GLOBAL_IX_PSA == MemBlkIxPSA)
                               && (((address_u32 + (tdSize_u8 - MIN_TRANSFER_DATA_LENGTH)) > APP_AREA_END) || (address_u32 < CALIB_AREA_BEG))))*/
                        if((TRUE == UDS_Transfer_Data_Success_u8))
#endif
                        {
                            tdStatus_u8 = REQUEST_OUT_OF_RANGE;
                        }
                        else if (writeOk_bo != TRUE)
                        {
                            tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                        }
                        /* Check if the battery voltage is ok */
                        /* If ok, tdStatus_u8 is further FALSE, else it equals VOLTAGE_TOO_LOW or VOLTAGE_TOO_HIGH */
                        else if (batteryStatus_u8 != BATTERY_STATUS_OK)
                        {
                            tdStatus_u8 = batteryStatus_u8;
                        }
                        else
                        {

                            flshStatus_u8 = UDS_FlashWrite(address_u32,
                                                           (U8 *)&UDS_data_in.UDS_data.UDS_TransData_msg.Data.tranfData[0],
                                                           (U32)(curBlkSize_u8));
                            if (flshStatus_u8 != FLASH_OK)
                            {
                                writeOk_bo = FALSE;
                                tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                            }
                            else
                            {

                                /* Deviation 0715 - globally disabled */
                                if (MEMBLK_CALIBRATION_IX_PSA == MemBlkIxPSA)
                                {
                                    Fls_secEraseSt[Blocks_table[CAL_AREA]] = FALSE;
                                    Fls_secEraseSt[Blocks_table[CAL_AREA+1]] = FALSE;

                                    if((address_u32 + curBlkSize_u8) >= CALIB_AREA_END_Loc)
                                    {
                                         UDS_Transfer_Data_Success_u8 = TRUE;
                                    }
                                    else
                                    {
                                         ;
                                    }
                                }
                                else if (MEMBLK_GLOBAL_IX_PSA == MemBlkIxPSA)
                                {
                                    for (index_u8 = CAL_AREA_END; index_u8 <= APP_END_AREA; index_u8++)
                                    {
                                        Fls_secEraseSt[Blocks_table[index_u8]] = FALSE;
                                    }

                                    if(TRUE == Erased_App_Cal_Brp_u8)
                                    {
                                    	if((address_u32 + curBlkSize_u8) >= APP_AREA_END_BRP)		/*new boot image size :APP_AREA_END_BRP*/
                                    	{
                                    		UDS_Transfer_Data_Success_u8 = TRUE;
                                    	}
                                    	else
                                    	{
                                    		;
                                    	}
                                    }
                                    else
                                    {
                                    	if((address_u32 + curBlkSize_u8) >= APP_AREA_END)
                                    	{
                                    		UDS_Transfer_Data_Success_u8 = TRUE;
                                    	}
                                    	else
                                    	{
                                    		;
                                    	}
                                    }
                                }
                                else if((MEMBLK_BRP_IX_PSA == MemBlkIxPSA))
                                {
                                	for (index_u8 = CAL_AREA; index_u8 <= APP_END_AREA; index_u8++)
                                	{
                                	    Fls_secEraseSt[Blocks_table[index_u8]] = FALSE;
                                	}

                                	if((address_u32 + curBlkSize_u8) >= BRP_AREA_END)
                                	{
                                		if((address_u32 - ReceMemSize) == BRP_AREA_BEG)
                                		{
                                			UDS_Transfer_Data_Success_u8 = TRUE;
                                		}
                                		else
                                		{
                                			;
                                		}
                                	}
                                	else if((address_u32 + curBlkSize_u8) >= PCB_TEST_CODE_AREA_END)
									{
                                		if((address_u32 - ReceMemSize) == BRP_AREA_BEG)
                                		{
                                			UDS_Transfer_Data_Success_u8 = TRUE;
                                		}
                                		else
                                		{
                                			;
                                		}
									}
                                	else
                                	{
                                		;
                                	}

                                }
                                else
                                {
                                	;
                                }
                                writeOk_bo = TRUE;
                                tdStatus_u8 = FALSE;
                            }
                        }
                        break;
                    }
#if (1 == ZI_READ)
                    case MEMBLK_ZI_IX_PSA:
                    {
                        curBlkSize_u8 = UDS_data_in.UDS_data_length - MIN_ZI_LENGTH;
                        /* Check if the client is not sending more data than requested. */
                        if (curBlkSize_u8 != ZI_DATA_LENGTH)
                        {
                            tdStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                        }
                        else
                        {
                            if (TRUE == GetEmptyHistoryZoneIdx(&emptyHistoryLocation_u16))
                            {
                                /* Set marker (45 byte of history) as 0x5C */
                                UDS_data_in.UDS_data.UDS_TransData_msg.ZI.ZI_tranfData[ZI_MARKER_PLACE] =
                                        RECORD_HIST_CORRECT;
                                flshStatus_u8 = UDS_FlashWrite((U32)historyRecording_au8[emptyHistoryLocation_u16],
                                                               (U8 *)&UDS_data_in.UDS_data.UDS_TransData_msg.ZI.ZI_tranfData[0],
                                                               ZI_DATA_LENGTH);
                                if (flshStatus_u8 != FLASH_OK)
                                {
                                    tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                                }
                                else
                                {
                                    /*
                                     * Set load status to APP VALID what means ECU_STATUS to ECU_STATUS_OPERATIONAL
                                     * as confirmation that ZI was written correctly and there is valid application.
                                     */
                                    flshStatus_u8 = FlsProgramLoadStatus(SYS_LOAD_STATUS_MAIN_APP_VALID);
                                    /* Deviation 0715 - globally disabled */
                                    if (flshStatus_u8 != FLS_OK)
                                    {
                                        tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                                    }
                                    else
                                    {
                                        tdStatus_u8 = FALSE;
                                    }
                                    authoriseLog_bo = FALSE;
                                    toolSignature_u16 = 0;
                                    tdStatus_u8 = FALSE;
                                }
                            }
                            else
                            {
                                /*
                                 * Set load status to APP VALID what means ECU_STATUS to ECU_STATUS_OPERATIONAL
                                 * as confirmation that ZI was written correctly and there is valid application.
                                 */
                                flshStatus_u8 = FlsProgramLoadStatus(SYS_LOAD_STATUS_MAIN_APP_VALID);
                                if (flshStatus_u8 != FLS_OK)
                                {
                                    tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                                }
                                else
                                {
                                    tdStatus_u8 = FALSE;
                                }
                                authoriseLog_bo = FALSE;
                                toolSignature_u16 = 0;
                                ziStatus_bo = FALSE;
                                UDS_data_out.UDS_data.UDS_TransData_resp.blockSeqNumber = TransferSequenceCounter_u8;
                                UDS_data_out.UDS_data.UDS_TransData_resp.transStatus = ZI_NO_MORE_SPACE;
                                UDS_data_out.UDS_data_length = TD_RESPONSE_LENGTH;
                            }
                        }
                        break;
                    }
#endif

#if (1 == KEY_APPLI_CHANGE_ENABLED)
                    case MEMBLK_KEY_APPLI_IX_PSA:
                    {
                        curBlkSize_u8 = UDS_data_in.UDS_data_length;
                        /* Check if the client is not sending more data than requested. */
                        if (curBlkSize_u8 != KEY_APPLI_LENGTH)
                        {
                            tdStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
                        }
                        else
                        {
                            /* Deviation 0303 - globally disabled */
                            flshStatus_u8 = UDS_FlashWrite((U32) &appliKey_u16,
                                    (U8 *) &UDS_data_in.UDS_data.UDS_TransData_msg.KEY_APPLI.KEY_APPLI_tranfData[0],
                                    (U32) KEY_APPLI_DATA_LENGTH);
                            if (flshStatus_u8 != FLASH_OK)
                            {
                                tdStatus_u8 = GENERAL_PROGRAMMING_FAILURE;
                            }
                            else
                            {
                                tdStatus_u8 = FALSE;
                            }
                        }
                        break;
                    }
#endif
                    /* DEVIATION:     2018
                       DESCRIPTION:   This switch default label is unreachable.
                       JUSTIFICATION: The default case will be retained for unexpected values
                    */
                    /* PRQA S 2018 1 */
                    default:
                    {
                        tdStatus_u8 = REQUEST_OUT_OF_RANGE;
                        break;
                    }
                }
#if (1 == ZI_READ)
                if ((tdStatus_u8 == FALSE) && (ziStatus_bo == TRUE))
#else
                if (FALSE == tdStatus_u8)
#endif
                {
                    /* Transfer was good */
                    UDS_data_out.UDS_data.UDS_TransData_resp.blockSeqNumber = TransferSequenceCounter_u8;
                    UDS_data_out.UDS_data_length = TD_RESPONSE_LENGTH;
                    TransferSequenceCounter_u8++;
                    address_u32 += curBlkSize_u8;	/*Increment the address to next transfer data request*/
                    UDS_TDS_Received_u8 = FALSE;
                }
        }
        else if (rxBlockCounter_u8 == (TransferSequenceCounter_u8 - 1))
        {
            writeOk_bo = TRUE;
            /* Send a positive response as this block has already been programmed */
            UDS_data_out.UDS_data.UDS_TransData_resp.blockSeqNumber = rxBlockCounter_u8;
            UDS_data_out.UDS_data_length = TD_RESPONSE_LENGTH;
        }
        else
        {
            tdStatus_u8 = WRONG_SEQUENCE_COUNTER;
        }
        if (tdStatus_u8 != FALSE)
        {
        	UDS_TDS_Received_u8 = FALSE;	/*Reset to False */
        	UDS_TD_Initiated = FALSE;
            UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
            send_negative_response(tdStatus_u8);
        }
        else
        {
        	;
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0;
    }
}

/******************************************************************************
 * Name         :  UDS_TransferExit
 * Called by    :  UDS_DiagServiceHandler
 * Preconditions:  May be called after service request was received
 * Parameters   :  None
 * Return code  :  None
 * Description  :
 ******************************************************************************/
static void UDS_TransferExit(void)
{
    U8 teStatus_u8 = FALSE;

    /* Check request message type. This service is supported only in physical addressing */
    /* In other case there is no response */
    if (PHYS == RxMessageType_u8)
    {
        if(UDSFlashSequence_e != TRANSFER_DATA)
        {
            teStatus_u8 = REQUEST_SEQUENCE_ERROR;
        }
        else if((UDS_Transfer_Data_Success_u8 == FALSE) && (UDS_TDS_Received_u8 == TRUE))
        {
        	teStatus_u8 = CONDITIONS_NOT_CORRECT;
        	UDS_TDS_Received_u8 = FALSE;
        }
        else
        {
        	if(TRANSFER_EXIT_LENGTH != MESSAGE_DATA_LENGTH)
        	{
        		teStatus_u8 = INCORRECT_MSG_LENGTH_OR_FORMAT;
        	}
#if (1 == KEY_APPLI_CHANGE_ENABLED)
            else if (UDSFlashSequence_e == TRANSFER_KEY_APPLI)
            {
                UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
                UDS_data_out.UDS_data_length = 1;
            }
#endif
#if (1 == ZI_READ)
            else if (UDSFlashSequence_e == TRANSFER_ZI)
            {
                UDSFlashSequence_e = EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI;
                UDS_data_out.UDS_data_length = 1;
            }
#endif
            else
            {
            	UDS_data_out.UDS_data_length = 1;
            	UDS_TD_Initiated = FALSE;
            	UDS_Transfer_Data_Success_u8 = FALSE;
            }
        }
        if (teStatus_u8 != FALSE)
        {
        	UDS_TD_Initiated = FALSE;
        	UDS_Transfer_Data_Success_u8 = FALSE;
            send_negative_response(teStatus_u8);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0;
    }
}

/****************************************************************************/
/*                                                                          */
/*  Function    : process_tester_present                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a tester present message                        */
/*                                                                          */
/****************************************************************************/
static void process_tester_present(void)
{
    U8 testerPresentsubFunc_u8;
    U8 tpSubFunct_u8;
    U8 suppressPos_u8;

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
        testerPresentsubFunc_u8 = UDS_data_in.UDS_data.UDS_TesterPresent_msg.subFunction;
        tpSubFunct_u8 = (U8)testerPresentsubFunc_u8;
        suppressPos_u8 = (testerPresentsubFunc_u8 & SUPPRESS_POS_RESPONSE);

        if (TESTER_PRESENT_REQ_LENGTH == MESSAGE_DATA_LENGTH)
        {
            if (tpSubFunct_u8 == 0U)
            {
                UDS_data_out.UDS_data.UDS_response_body[1] = tpSubFunct_u8;
                UDS_data_out.UDS_data_length = 2;
            }
            else if((suppressPos_u8 == SUPPRESS_POS_RESPONSE)&&(tpSubFunct_u8 == 0x80))
            {
            	/* suppress the positive response */
            	UDS_data_out.UDS_data_length = 0;
            }
            else
            {
                send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
            }
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}
/****************************************************************************/
/*                                                                          */
/*  Function    : control_dtc_Setting                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a control dtc setting message                   */
/*                                                                          */
/****************************************************************************/
static void control_dtc_setting(void)
{
    U8 controlDtcsubFunc_u8;
    U8 cdSubFunct_u8;
    U8 suppressPos_u8;

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
    	controlDtcsubFunc_u8 = UDS_data_in.UDS_data.UDS_ControlDtc_msg.subFunction;
    	cdSubFunct_u8 = (U8)controlDtcsubFunc_u8;
        suppressPos_u8 = (controlDtcsubFunc_u8 & SUPPRESS_POS_RESPONSE);

        if (TESTER_PRESENT_REQ_LENGTH == MESSAGE_DATA_LENGTH)
        {
            if ((CONTROLDTCOFF == cdSubFunct_u8) || (CONTROLDTCON == cdSubFunct_u8))
            {
                UDS_data_out.UDS_data.UDS_response_body[1] = cdSubFunct_u8;
                UDS_data_out.UDS_data_length = 2;
            }
            else if((suppressPos_u8 == SUPPRESS_POS_RESPONSE) && ((SUPP_CONTROLDTCOFF == cdSubFunct_u8) || (SUPP_CONTROLDTCON == cdSubFunct_u8 )))
            {

            	/* suppress the positive response */
            	UDS_data_out.UDS_data_length = 0;
            }
            else
            {
                send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
            }
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}
/****************************************************************************/
/*                                                                          */
/*  Function    : communication_control_msg                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a communication control message for tx and rx   */
/*  Enable or Disable                                                       */
/****************************************************************************/
static void communication_control_msg(void)
{
    U8 commControlsubFunc_u8;
    U8 ccSubFunct_u8;
    U8 suppressPos_u8;
    U8 commType_u8;

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
    	commControlsubFunc_u8 = UDS_data_in.UDS_data.UDS_CommControl_msg.subFunction;
    	ccSubFunct_u8 = (U8)commControlsubFunc_u8;
        suppressPos_u8 = (commControlsubFunc_u8 & SUPPRESS_POS_RESPONSE);
        commType_u8 = UDS_data_in.UDS_data.UDS_CommControl_msg.commType;

        if (COMM_CTRL_REQ_LENGTH == MESSAGE_DATA_LENGTH)
        {
            if ((DISABLE_RX_TX_COMM == ccSubFunct_u8) || (ENABLE_RX_TX_COMM == ccSubFunct_u8))
            {
            	if(COMM_TYPE == commType_u8)
            	{
            		UDS_data_out.UDS_data.UDS_response_body[1] = ccSubFunct_u8;
            		UDS_data_out.UDS_data_length = 2;
            	}
            	else
            	{
            		send_negative_response(REQUEST_OUT_OF_RANGE);
            	}
            }
            else if((suppressPos_u8 == SUPPRESS_POS_RESPONSE) && ((ccSubFunct_u8 == SUPP_DISABLE_RX_TX_COMM) || (ccSubFunct_u8 == SUPP_ENABLE_RX_TX_COMM)))
            {
            	if(COMM_TYPE == commType_u8)
            	{
            		/* suppress the positive response */
            		UDS_data_out.UDS_data_length = 0;
            	}
            	else
            	{
            		send_negative_response(REQUEST_OUT_OF_RANGE);
            	}
            }
            else
            {
                send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
            }
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}
/****************************************************************************/
/*                                                                          */
/*  Function    : reset_ecu_id                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a tester present message                        */
/*                                                                          */
/****************************************************************************/
static void reset_ecu_id(void)
{
    U8 resetecusubFunc_u8;
    U8 reSubFunct_u8;
    U8 flshStatus_u8;

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
    	resetecusubFunc_u8 = UDS_data_in.UDS_data.UDS_ResetEcu_msg.subFunction;
    	reSubFunct_u8 = (U8)resetecusubFunc_u8;

        if (TESTER_PRESENT_REQ_LENGTH == MESSAGE_DATA_LENGTH)
        {
			if (reSubFunct_u8 == 0x01U)
			{
				UDS_data_out.UDS_data.UDS_response_body[1] = reSubFunct_u8;
				UDS_data_out.UDS_data_length = 2;

				/*If application is valid, then update the load status with valid application sw*/

				if(TRUE == g_ApplStatus_bo)
				{
					g_ApplStatus_bo = FALSE;

					flshStatus_u8 = FlsProgramLoadStatus(SYS_LOAD_STATUS_MAIN_APP_VALID);

					if (flshStatus_u8 != FLS_OK)
					{
						writeOk_bo = FALSE;

						send_negative_response(GENERAL_PROGRAMMING_FAILURE);
						/*rcStatus_u8 = GENERAL_PROGRAMMING_FAILURE;*/
					}
					else
					{
						;
					}
				}
				else
				{
					;
				}

				UDS_Perform_Mcu_Reset_Flag = TRUE;
			}
			else
			{
				send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
			}
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}

/****************************************************************************/
/*                                                                          */
/*  Function    : clear_diagnostic_info                                    */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a Clear diagnostic DTC message                  */
/*                                                                          */
/****************************************************************************/
static void clear_diagnostic_info(void)
{

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
        if (CLEAR_DTC_REQ_LENGTH == MESSAGE_DATA_LENGTH)
        {
			if ((UDS_data_in.UDS_data.UDS_ClearDTC_msg.subFunction[0] == 0xFFU) && (UDS_data_in.UDS_data.UDS_ClearDTC_msg.subFunction[1] == 0xFFU) &&
					(UDS_data_in.UDS_data.UDS_ClearDTC_msg.subFunction[2] == 0xFFU))
			{
				UDS_data_out.UDS_data_length = 1;
			}
			else
			{
				send_negative_response(REQUEST_OUT_OF_RANGE);
			}
        }
        else
        {
            send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
        }
    }
    else
    {
        /* No response */
        UDS_data_out.UDS_data_length = 0U;
    }
}

#if 0
/****************************************************************************/
/*                                                                          */
/*  Function    : UDS_read_dtc_information                                  */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function processes a read DTC information request                  */
/*                                                                          */
/****************************************************************************/
static void UDS_read_dtc_information(void)
{
    U8 subFuncIdent_u8;
    U8 statusMaskIdent_u8;
    volatile U64 load_status_u64;

    /* Check request message type. This service is supported only in physical and functional addressing */
    if ((PHYS == RxMessageType_u8) || (FUNCT == RxMessageType_u8))
    {
        subFuncIdent_u8 = UDS_data_in.UDS_data.UDS_ReadDTCByStatusMask_msg.subFunction_u8;
        statusMaskIdent_u8 = UDS_data_in.UDS_data.UDS_ReadDTCByStatusMask_msg.statusMask_u8;

        /* Check subfunction */
        if (DTC_RDTCBSM == subFuncIdent_u8)
        {
            /* Check request length */
            if (READ_DTC_BY_STATUS_MASK_LENGTH == MESSAGE_DATA_LENGTH)
            {
                UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.subFunc_u8 = subFuncIdent_u8;
                UDS_data_out.UDS_data_length++;
                UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.statusMask_u8 = DTC_STATUSAVAMASK;
                UDS_data_out.UDS_data_length++;

                if ((statusMaskIdent_u8 & DTC_STATUSAVAMASK) != 0U)
                {
                    load_status_u64 = UDS_READ_LOAD_STATUS();

                    if (load_status_u64 != SYS_LOAD_STATUS_MAIN_APP_VALID)
                    {
                        UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.DTC_u8[0]      = (U8) ((DTC_DOWNLOAD_FAILURE >> 16U) & 0xFFU);
                        UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.DTC_u8[1]      = (U8) ((DTC_DOWNLOAD_FAILURE >> 8U ) & 0xFFU);
                        UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.DTC_u8[2]      = (U8) ((DTC_DOWNLOAD_FAILURE       ) & 0xFFU);
                        UDS_data_out.UDS_data.UDS_ReadDTCByStatusMask_resp.statusOfDTC_u8 = DTC_STATUSMASK;	/*DTC_STATUSMASK*/

                        UDS_data_out.UDS_data_length += 4U;
                    }
                }
            }
            else
            {
                /* Incorrect Message Length */
                send_negative_response(INCORRECT_MSG_LENGTH_OR_FORMAT);
            }
        }
        else
        {
            /* Subfunction not supported */
            send_negative_response(SUBFUNCTION_NOT_SUPPORTED);
        }
    }
    else
    {
        /* no response! */
        UDS_data_out.UDS_data_length = 0;
    }
}
#endif

/****************************************************************************/
/*                                                                          */
/*  Function    : copy_data                                                 */
/*                                                                          */
/*  Parameters  : U8 *Source - Pointer to source area                       */
/*                U8 *Dest   - Pointer to destination area                  */
/*                U8 Length  - Number of items to copy                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  This function copys data from one area to another.                      */
/*                                                                          */
/****************************************************************************/
static void copy_data(const U8 *Source, U8 *Dest, U8 Length)
{
    U8 index_u8;

    for (index_u8 = 0; index_u8 < Length; index_u8++)
    {
        *Dest = *Source;
        /*  DEVIATION:     0489
            DESCRIPTION:   Increment or decrement operation performed on pointer.
            JUSTIFICATION: This is done for accessing different elements of the array,
                           it is analyzed and causes no issues */
        /* PRQA S 0489 2*/
        Dest++;
        Source++;

    }
}

/******************************************************************************
 * Name         :  UDS_ReadByte
 * Called by    :  Appl_CalculateCRC32, other UDS modules
 * Preconditions:  None
 * Parameters   :  Memory address to read out
 * Return code  :  Byte at memory location 'address'
 * Description  :  This function can be used to read one byte from the given
 *                 address.
 ******************************************************************************/
/* DEVIATION:     3219
   DESCRIPTION:   Static function 'UDS_ReadByte()' is not used within this translation unit.
   JUSTIFICATION:  This function is not currently used but it may be used in the future.
 */
/* PRQA S 3219 1 */
/*static U8 UDS_ReadByte(U32 address)
{*/
    /*  DEVIATION:     0306
        DESCRIPTION:   Cast between a pointer to object and an integral type.
        JUSTIFICATION: The byte at a fixed address given by the U32 input needs to be read.Hence
                       casting becomes necessary and cannot be avoided. */
/*    return (*((U8 *) address));*/ /* Store byte */
/*}*/

/******************************************************************************
 * Name         :  securitySeedGeneration
 * Called by    :  process_SecurityAccess
 * Preconditions:
 * Parameters   :
 * Return code  :
 * Description  :
 ******************************************************************************/
static U32 securitySeedGeneration(U16 timebase_u16)
{
    uint32_t randomValue_u32 = 0x0000AAAAUL;

    S16 swK;
    S16 swR;
    S16 swNI;

    swK = (S16) (randomValue_u32 / 178U);

#ifndef POLYSPACE
    /* DEVIATION:     0273
       DESCRIPTION:   Value of integer expression is definitely not representable in the signed result type
       JUSTIFICATION: Algorithm is explicit given by customer.
     */
    /* PRQA S 0273 1 */
    swR = (S16)(randomValue_u32 - (swK * (U8)178));
#else
    /* The randomValue_u32 is declared as uint32_t randomValue_u32 = 0x0000AAAAUL;                                    */
    /* The decimal value of randomValue_u32 is 43690                                                                  */
    /* uint32_t  value is directly type casted to S16 which causes overflow and polyspace thrown OVFL error(Red error)*/
    /* to facilitate polyspace verification below changes were made.                                                  */
    swR = ((randomValue_u32 & 0xFFFF) - swK * 178);
#endif

    swNI = (-63 * swK) + (swR * (U8)170);

    /* DEVIATION:     0290
       DESCRIPTION:   An integer expression with a value that is definitely negative is being converted to an unsigned type.
       JUSTIFICATION: Algorithm is explicit given by customer.
     */
    /* PRQA S 0290 3 */
    randomValue_u32 = (uint32_t)(((uint32_t)((U16)swNI + (U16)((timebase_u16 + 2) * 67521))) << 16)
                    + (uint32_t)((U16)swNI + (U16)((timebase_u16 + 2) * 542));

    return randomValue_u32;
}

/****************************************************************************/
/*                                                                          */
/*  Function    : evaluate_key                                              */
/*                                                                          */
/*  Parameters  :                                                           */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description : Function to evaluate the key for service 0x27             */
/*                                                                          */
/****************************************************************************/
static void evaluate_key(U8 *hash)
{
    /* Deviation 0310 - globally disabled */
 	*((U32*)hash) = securityCalcKeyAlgo(CurrSeed_u32);
}

#if 0
/****************************************************************************/
/*                                                                          */
/*  Function    : securityCalculateEncryptionKey                            */
/*                                                                          */
/*  Parameters  :                                                           */
/*                                                                          */
/*  Returns     : static S16                                            */
/*                                                                          */
/*  Description : Function to evaluate the key for service 0x27             */
/*                                                                          */
/****************************************************************************/
static S16 securityCalculateEncryptionKey(S16 swE1, S16 swE2)
{
    S16 swKey;
    S16 swK, swR, swNI;

    /* F1(E1), F2(E2), E1 and E2 are 16bits signed type.

     F1 description:
     K := E1 div 178
     R := E1 - K * 178
     NI := - 63 * K + R * 170
     If NI < 0 then NI := NI + 30323

     Example with E1 = 1234Hex (4660dec)
     K := integer part of 4660 / 178 = 26
     R := 4660 - 26 * 178 = 32
     NI := -63 * 26 + 32 * 170 = 3802 (EDAhex)
     NI stay the same because >= 0
     F1(1234hex) = EDAhex
     */
    /* DEVIATION:     3103
       DESCRIPTION:   Result of signed division or remainder operation may be implementation defined.
       JUSTIFICATION: Algorithm is explicit given by customer.
    */
    /* PRQA S 3103 1 */
    swK = (swE1 / 178);
    swR = (swE1 - (swK * 178));
    swNI = ((-63 * swK) + (swR * 170));

    if (swNI < 0)
    {
        swNI = swNI + 30323;
    }

    swKey = swNI;

    /* F2 description:
     K := E2 div 177
     R := E2 - K * 177
     NY := - K - K + R * 171
     If NY < 0 then NY := NY + 30269

     Example with E2 = C221Hex (- 15839dec)
     K := integer part of - 15839 / 177 = - 89
     R := - 15839 - (- 89) * 177 = - 86
     NY := - (- 89) - (- 89) + (- 86) * 170 = - 14528
     NY is < 0 then NY := - 14528 + 30269 = 15741dec (3D7DHex)
     F2(C221hex) = 3D7Dhex
     */
    /* DEVIATION:     3103
       DESCRIPTION:   Result of signed division or remainder operation may be implementation defined.
       JUSTIFICATION: Algorithm is explicit given by customer.
    */
    /* PRQA S 3103 1 */
    swK = (swE2 / 177);
    swR = (swE2 - (swK * 177));
    swNI = ((-swK - swK) + (swR * 171));

    if (swNI < 0)
    {
        swNI = (swNI + 30269);
    }

    swKey = (S16)((U16)swKey | (U16)swNI);

    return swKey;
}
#endif

#if 0

/****************************************************************************/
/*                                                                          */
/*  Function    : securityCalcKey                                           */
/*                                                                          */
/*  Parameters  :                                                           */
/*                                                                          */
/*  Returns     : U32                                                       */
/*                                                                          */
/*  Description : Function to evaluate the key for service 0x27             */
/*                                                                          */
/****************************************************************************/
static U32 securityCalcKey(U32 seed, U16 appliKey)
{
    uint8_t ubSeedValue[4];
    uint32_t ulKey;
    S16 swKey12;
    S16 swKey34;

    ubSeedValue[0] = (U8)(seed >> 24);
    ubSeedValue[1] = (U8)(seed >> 16);
    ubSeedValue[2] = (U8)(seed >> 8);
    ubSeedValue[3] = (U8)seed;

    swKey12 = securityCalculateEncryptionKey((S16)appliKey,
                                             (S16)((((U16)(ubSeedValue[0])) << 8) + (ubSeedValue[3])));

    swKey34 = securityCalculateEncryptionKey((S16)((((U16)(ubSeedValue[1])) << 8) + (ubSeedValue[2])),
                                             swKey12);

    ulKey = (uint32_t)(((uint32_t)swKey12 << 16) + (uint32_t)swKey34);

    return (ulKey);
}
#endif /*PSA security algorithm*/
#if 0
/****************************************************************************/
/*                                                                          */
/*  Function    : Reverse                                           */
/*                                                                          */
/*  Parameters  :                                                           */
/*                                                                          */
/*  Returns     : U8                                                       */
/*                                                                          */
/*  Description : Function to reverse the bit positions in the byte         */
/*                                                                          */
/****************************************************************************/

static U8 Reverse(U8 Seed)
{
	U8 reversed =  0x00;
	U8 i  = 0;

	for(i = 0; i<8;i++)
	{
		reversed |=(U8)(((Seed>>i)& 0x01)<<(0x07 - i));
	}

	return(reversed);
}

#endif	/* Reverse function is not being used*/

/****************************************************************************/
/*                                                                          */
/*  Function    : RIGHT_ROTATE_8_BITS_fn                                           */
/*                                                                          */
/*  Parameters  :   seed and position                                                        */
/*                                                                          */
/*  Returns     : U8                                                       */
/*                                                                          */
/*  Description : Function to rotate the bit positions to right           */
/*                                                                          */
/****************************************************************************/

static U8 RIGHT_ROTATE_8_BITS_fn(U8 seed,U8 position )
{
	static U8 Seed1_u8 = 0x00;
	static U8 Seed2_u8 = 0x00;
	static U8 Seed3_u8 = 0x00;
	static U8 Seed4_u8 = 0x00;

	static U8 Bit_Pos = 0x00;

	Seed_Bit_shift_u8 = 0x00;

	Seed3_u8 = seed;
	Seed4_u8 = seed;

	Bit_Pos = position;

	Seed1_u8 = (U8)((((U8)(Seed3_u8))<<((U8)SIZE_BITS_8 - (U8)Bit_Pos)) & (U8)0xFFu);
	Seed2_u8 = (U8)((((U8)(Seed4_u8))>>((U8)Bit_Pos)) & (U8)0xFFu);

	Seed1_u8 = (U8)(Seed1_u8 | Seed2_u8);

	Seed_Bit_shift_u8 = (U8)Seed1_u8;

	return(Seed_Bit_shift_u8);
}
/****************************************************************************/
/*                                                                          */
/*  Function    : SWAP_ADJACENT_BITS_8_BITS_fn                                           */
/*                                                                          */
/*  Parameters  :   seed                                                       */
/*                                                                          */
/*  Returns     : U8                                                       */
/*                                                                          */
/*  Description : Function to interchange the positions of adjacent bits           */
/*                                                                          */
/****************************************************************************/
static U8 SWAP_ADJACENT_BITS_8_BITS_fn(U8 seed)
{

	static U8 Seed1_u8 = 0x00;
	static U8 Seed2_u8 = 0x00;
	static U8 Seed3_u8 = 0x00;
	static U8 Seed4_u8 = 0x00;

	Seed_Bit_shift_u8 = 0x00;

	Seed3_u8 = seed;
	Seed4_u8 = seed;

	/*(((d & 0x55u) << 1u)|((d & 0xAAu) >> 1u))*/

	Seed3_u8 = (U8)((((U8)(Seed3_u8))&(HIGH_NIBBLE_MASK)) & 0xFFu);
	Seed1_u8 = (U8)((((U8)(Seed3_u8))<<(0x01u)) & 0xFFu);
	Seed4_u8 = (U8)((((U8)(Seed4_u8))&(LOW_NIBBLE_MASK)) & 0xFFu);
	Seed2_u8 = (U8)((((U8)(Seed4_u8))>>(0x01u)) & 0xFFu);

	Seed1_u8 = (U8)(Seed1_u8 | Seed2_u8);

	Seed_Bit_shift_u8 = (U8)Seed1_u8;

	return(Seed_Bit_shift_u8);
}
/****************************************************************************/
/*                                                                          */
/*  Function    : LEFT_ROTATE_16_BITS_fn                                           */
/*                                                                          */
/*  Parameters  :   seed and position                                                        */
/*                                                                          */
/*  Returns     : U16                                                       */
/*                                                                          */
/*  Description : Function to rotate the bit positions to left           */
/*                                                                          */
/****************************************************************************/
static U16 LEFT_ROTATE_16_BITS_fn(U16 seed,U8 position )
{

	static U16 Seed1_u16 = 0x00;
	static U16 Seed2_u16 = 0x00;
	static U16 Seed3_u16 = 0x00;
	static U16 Seed4_u16 = 0x00;

	static U8 Bit_Pos = 0x00;
	static U16 Seed_Bit_shift_u16 = 0x00;

	Seed_Bit_shift_u16 = 0x00;

	Seed3_u16 = seed;
	Seed4_u16 = seed;

	Bit_Pos = position;

	Seed1_u16 = (U16)((((U16)((Seed3_u16)))<<((U8)Bit_Pos)) & (U16)0xFFFF);

	Seed2_u16 = (U16)((((U16)(Seed4_u16))>>((U16)SIZE_BITS_16 - (U8)Bit_Pos)) & (U16)0xFFFF);

	Seed1_u16 = (U16)(Seed1_u16 | Seed2_u16);

	Seed_Bit_shift_u16 = (U16)Seed1_u16;

	return(Seed_Bit_shift_u16);
}

/****************************************************************************/
/*                                                                          */
/*  Function    : securityCalcKey                                           */
/*                                                                          */
/*  Parameters  :     seed                                                      */
/*                                                                          */
/*  Returns     : U32                                                       */
/*                                                                          */
/*  Description : Function to evaluate the key for security seed service 0x27 01 */
/*                                                                          */
/****************************************************************************/
static U32 securityCalcKeyAlgo(U32 seed)
{

		uint8_t coef_1 = COEFICIENT_1;
		uint8_t coef_2 = COEFICIENT_2;
		uint8_t coef_3 = COEFICIENT_3;
		uint8_t coef_4 = COEFICIENT_4;

		uint32_t ulKey;

	    static uint8_t seedHighByte_u8 = 0x00;
	    static uint8_t seedSecByte_u8 = 0x00;
	    static uint8_t seedHighByte_1_u8 = 0x00;
	    static uint8_t seedSecByte_1_u8 = 0x00;
	    static uint8_t seedThirdByte_u8 = 0x00;
	    static uint8_t seedLowByte_u8 = 0x00;
	    static uint8_t seedHighByte_2_u8 = 0x00;
	    static uint8_t seedHighByte_3_u8 = 0x00;
	    static uint16_t High_Sec_u16 = 0x00;
	    static uint16_t Third_Low_u16 = 0x00;
	    static uint16_t seedHighBytes_u16 = 0x00;
	    static uint16_t seedLowBytes_u16 = 0x00;

	    /* Get individual bytes of the seed */
	    seedHighByte_u8  = (U8)GET_BYTE(seed, HIGH_BYTE);
	    seedSecByte_u8   = (U8)GET_BYTE(seed, THIRD_BYTE);
	    seedThirdByte_u8 = (U8)GET_BYTE(seed, SECOND_BYTE);
	    seedLowByte_u8   = (U8)GET_BYTE(seed, LOW_BYTE);

	    /* 3 bit positions Right rotate in the byte */
	    seedHighByte_u8  = (U8)RIGHT_ROTATE_8_BITS_fn(seedHighByte_u8, ROTATE_BY_3_BITS);
	    seedSecByte_u8   = (U8)RIGHT_ROTATE_8_BITS_fn(seedSecByte_u8, ROTATE_BY_3_BITS);
	    seedThirdByte_u8 = (U8)RIGHT_ROTATE_8_BITS_fn(seedThirdByte_u8, ROTATE_BY_3_BITS);
	    seedLowByte_u8   = (U8)RIGHT_ROTATE_8_BITS_fn(seedLowByte_u8, ROTATE_BY_3_BITS);

	    /* Swap adjacent bits */
	    seedHighByte_u8  = (U8)SWAP_ADJACENT_BITS_8_BITS_fn(seedHighByte_u8);
	    seedSecByte_u8   = (U8)SWAP_ADJACENT_BITS_8_BITS_fn(seedSecByte_u8);
	    seedThirdByte_u8 = (U8)SWAP_ADJACENT_BITS_8_BITS_fn(seedThirdByte_u8);
	    seedLowByte_u8   = (U8)SWAP_ADJACENT_BITS_8_BITS_fn(seedLowByte_u8);

	    /* Creating two 16 bit units of two 8 bit units for the next operation */

	    seedHighBytes_u16 = seedHighByte_u8;

	    seedHighBytes_u16 = (U16)(((((U16)(seedHighBytes_u16)) << SIZE_BITS_8) & 0xFFFF) | seedSecByte_u8);

	    seedLowBytes_u16  = seedThirdByte_u8;

	    seedLowBytes_u16  = (U16)(((((U16)(seedLowBytes_u16)) << SIZE_BITS_8) & 0xFFFF) | seedLowByte_u8);

	    /* Left rotate the 16 bit units by 3 bits */
	    seedHighBytes_u16 = (U16)LEFT_ROTATE_16_BITS_fn(seedHighBytes_u16, ROTATE_BY_3_BITS);
	    seedLowBytes_u16  = (U16)LEFT_ROTATE_16_BITS_fn(seedLowBytes_u16, ROTATE_BY_3_BITS);

	    /* Get individual byte for the next step */

	    seedSecByte_u8 = 0x00;
	    seedHighByte_u8 = 0x00;
	    seedLowByte_u8 = 0x00;
	    seedThirdByte_u8 = 0x00;


	    High_Sec_u16 = seedLowBytes_u16;
	    Third_Low_u16 = seedLowBytes_u16;

	    seedLowByte_u8   =  (U8)(High_Sec_u16 & 0x00FFu);
	    seedThirdByte_u8 =  (U8)((Third_Low_u16>>0x08u) & 0x00FFu);

	    High_Sec_u16 = seedHighBytes_u16;
	    Third_Low_u16 = seedHighBytes_u16;

	    seedSecByte_1_u8   =  (U8)(High_Sec_u16 & 0xFFu);
	   	seedHighByte_1_u8 =   (U8)((Third_Low_u16>>0x08u) & 0xFFu);

	    /*Apply the coefficient factor to the individual bytes*/
	   	seedHighByte_2_u8  = (seedHighByte_1_u8 ^ coef_1);
	    seedSecByte_u8   = (seedSecByte_1_u8 ^ coef_2);
	    seedThirdByte_u8 = (seedThirdByte_u8 ^ coef_3);
	    seedLowByte_u8   = (seedLowByte_u8 ^ coef_4);

	    /*Reverse the bit value in the byte*/

	    seedHighByte_3_u8 	= (U8)((seedHighByte_2_u8 ^ 0xFFU) & 0xFFU);
	    seedSecByte_u8 		= (U8)((seedSecByte_u8 ^ 0xFFU) & 0xFFU);
	    seedThirdByte_u8 	= (U8)((seedThirdByte_u8 ^ 0xFFU) & 0xFFU);
	    seedLowByte_u8 		= (U8)((seedLowByte_u8 ^ 0xFFU) & 0xFFU);


	    /* Creating two 16 bit units of two 8 bit units for the next operation */
	    seedHighBytes_u16 = (U16)((((U16)(seedHighByte_3_u8)) << SIZE_BITS_8) | seedSecByte_u8);

		seedLowBytes_u16 = (U16)((((U16)(seedThirdByte_u8)) << SIZE_BITS_8) | seedLowByte_u8);

		/* Creating 32 bit units from two 16 bit units for the final key generation */
		ulKey = (uint32_t)(((uint32_t)seedHighBytes_u16 << SIZE_BITS_16) + (uint32_t)seedLowBytes_u16);

		return (ulKey);
}


/******************************************************************************
 * Name         :  finish_programming_sequence
 * Called by    :
 * Preconditions:
 * Parameters   :  None
 * Return code  :  None
 * Description  :  Determines action after reprogramming activity
 ******************************************************************************/
static U8 finish_programming_sequence(void)
{
    U8 retval_u8 = FALSE;
    U8 checksum_res = FALSE;

    /*  DEVIATION:     0310
        DESCRIPTION:   Casting to different object pointer type
        JUSTIFICATION: The checksum is a 32 bit value, saved at a fixed address. The address is
                       __APP_CRC - 2 where __APP_CRC is a U8 location. Hence casting becomes
                       necessary. But this is a part of the legacy code and it works fine.  */
    /*  DEVIATION:     0488
        DESCRIPTION:   Performing pointer arithmetic.
        JUSTIFICATION: Since the checksum is in &__APP_CRC - 2 location, pointer arithmetic
                       becomes necessary. This is a part of legacy code and works fine*/
    /* Deviation 0310, 0488 - globally disabled */
    if (Bstrp_CalcChecksum(PROG_APPLICATION) == ~(*((volatile U32 *)((U8 *)__APP_CRC))))
    {
        checksum_res = TRUE;
    }
    else
    {
        checksum_res = FALSE;
    }

    if (TRUE == checksum_res)
    {
        if (diagState.invalid_App == FALSE)
        {
            /* Load status erase status reset */
            Load_status_erase = FALSE;
            /* Now, RESET the processor */
            UDSFlashSequence_e = SUCCESSFUL_REPROG_RESET;
            retval_u8 = TRUE;
        }
    }
    else
    {
        /* Reset should occur in spite wrong checksum */
        UDSFlashSequence_e = SUCCESSFUL_REPROG_RESET;
    }

    return retval_u8;
}

/******************************************************************************
 * Name         :  UDS_DiagContinueProgramming
 * Called by    :
 * Preconditions:
 * Parameters   :  None
 * Return code  :  None
 * Description  :  To continue flash erase and check program dependencies
 *                 services, essentially to ensure that the desired response
 *                 pending has been sent before postponing the normal scheduler.
 ******************************************************************************/
void UDS_DiagContinueProgramming(void)
{
    U8 status_u8 = FLS_OK;
    U8 erase_blk;

    switch (UDSFlashSequence_e)
    {
        case EXEC_ROUTINE_ERASE_FLASH:
        {

            /* Erase Flash. */
            if (Fls_secEraseSt[Blocks_table[StartBlock_u8]] == FALSE)
            {

                if (StartBlock_u8 <= EndBlock_u8)
                {
                    /* 1 needs to be subtracted from APV_BLOCK_INDEX as StartBlock_u8 count */
                    /* starts with 0 where as APV_BLOCK_INDEX starts with 1 */
                    erase_blk = Blocks_table[StartBlock_u8];
                    /* DEVIATION:     3138
                       DESCRIPTION:   Null statement is located close to other code or comments.
                       JUSTIFICATION: The functions represent assembly code which generates warning. This is how it is made in core bootloader.
                     */
                    /* PRQA S 3138 5 */
                    DisableAllInterrupts();

                    status_u8 = Fls_C55EraseBlk(erase_blk);
                    /* PRQA S 3138 5 */
                    EnableAllInterrupts();
                }
                else
                {
                    /* StartBlock_u8 > EndBlock_u8: All requested blocks erased */
                    status_u8 = REQ_BLKS_ERASED;
                }

                /* Manage state return by the flash erasing request */
                switch (status_u8)
                {
                    case FLS_C55_PENDING:
                    {
                        status_u8 = FLS_OK;
                        break;
                    }

                    case REQ_BLKS_ERASED:
                    {
                        status_u8 = FLS_OK;
                        UDSFlashSequence_e = FIN_ROUTINE_ERASE_FLASH;
                        break;
                    }

                    case FLS_C55_DONE:
                    {
                        /* If the block erased was load */
                        if (FALSE == Load_status_erase)
                        {
                            /* status block */
                            Load_status_erase = TRUE;
                            status_u8 = FLS_OK;
                        }
                        else
                        {
                            /* Erase complete, increment block number */
                            /* Update array for block erase status as Erased (TRUE) */
                            Fls_secEraseSt[Blocks_table[StartBlock_u8]] = TRUE;
                            StartBlock_u8++;

                            /*Skip the erasing BRP section while flashing new boot image if already BRP section is erased and programmed)*/
                            if((Erased_App_Cal_Brp_u8 == TRUE) && (StartBlock_u8 == CAL_AREA_END))
                            {
                            	StartBlock_u8 = APP_START_AREA;
                            }
                            else
                            {
                            	;
                            }
                            status_u8 = FLS_OK;
                        }
                        break;
                    }

                    case FLS_C55_FAIL:
                    default:
                    {
                        status_u8 = GENERAL_PROGRAMMING_FAILURE;
                        UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;
                        break;
                    }
                }
            }
            else
            {
                /* Block already erased, hence increment to next block */
                StartBlock_u8++;
            }

            if (status_u8 != FLS_OK)
            {
                send_negative_response(status_u8);
            }
            break;
        }

        case SUCCESSFUL_REPROG_RESET:
        {
            UDSFlashSequence_e = SEQUENCE_NOT_ACTIVE;
            Fls_Programming_Complete = TRUE;
            break;
        }

        default:
            break;
    }
}

/******************************************************************************
 * Name         :  UDS_FlashWrite
 * Called by    :  TransferData-service
 * Preconditions:  Data is expected in DiagBuffer_pu8
 * Parameters   :
 * Return code  :  Status of Flash programming (0 == SUCCESS)
 * Description  :  Program flash
 ******************************************************************************/
static U8 UDS_FlashWrite(U32 writeAddress, U8* writeBuffer, U32 writeLength)
{
    U8 *data_pu8;
    U8 errorCode_u8 = FLASH_OK;
    U8 tempErrorCode_u8;
    U32 index_u8;

    /* Do not call the flash driver with zero length */
    data_pu8 = (U8 *)&writeBuffer[0];
    while ((FLASH_OK == errorCode_u8) && (writeLength > 0U))
    {
        if (writeLength < UDS_PRG_SIZE)
        {
            for (index_u8 = writeLength; index_u8 < UDS_PRG_SIZE; index_u8++)
            {
                data_pu8[index_u8] = 0xFF;
            }
            writeLength = UDS_PRG_SIZE;
        }
        else
        {
            ; /* Do nothing */
        }

        /* Call flash write function in RAM */
        /*  DEVIATION:     0306
            DESCRIPTION:   Cast between a pointer to object and an integral type.
            JUSTIFICATION: The programming needs to be done to the address dervied from the tester and
                           hence the U32 integer value needs to be converted to a pointer and used as
                           the programming address.Also, this is a part of legacy code and works fine */
        tempErrorCode_u8 = FlsProgramFlash(data_pu8, (U8*) writeAddress, (U32) UDS_PRG_SIZE);
        if (tempErrorCode_u8 != FLS_OK)
        {
            errorCode_u8 = FLASH_FAILED;
        }

        writeLength -= (U32)UDS_PRG_SIZE;
        writeAddress += (U32)UDS_PRG_SIZE;
        /* Move source pointer on */
        /*  DEVIATION:     0488
            DESCRIPTION:   Performing pointer arithmetic.
            JUSTIFICATION: As data is being handled as elements of an array, pointer arithmetic is
                           used to point to different elements of the array for efficient coding. */
        data_pu8 += UDS_PRG_SIZE;
    }

    return errorCode_u8;
}

/**************************************************************************************************
 * Name         :  UDS_progSessionStart
 * Called by    :  PROG_Main
 * Parameters   :
 * Return code  :
 * Description  : This function is called when a switch from Main application to Boot takes place.
 As, response to Programming Session seed request (10 02/82) requested from application s/w needs to be sent out,this function fills up the UDS diagnostic
 input buffer with DSC - Programming session request bytes, and sets TP request
 received to TRUE.
 **************************************************************************************************/
void UDS_progSessionStart(void)
{
    /* Add Request data for Programming session in the input buffer */
    UDS_data_in.UDS_data.UDS_StartDiagnosticSession_msg.request_ID = DIAGNOSTIC_SESSION_CONTROL_ID;

    /* If application request "SuppressPosRspMsgIndicationBit" the ECU don't send a positive response message */
    if (0U != Suppres_Ctr_Bit)
    {
        UDS_data_in.UDS_data.UDS_StartDiagnosticSession_msg.diagnosticSession = (PROGRAM_SESSION | SUPPRESS_POS_RESPONSE);
    }
    /* unless the ECU send a positive response message */
    else
    {
        UDS_data_in.UDS_data.UDS_StartDiagnosticSession_msg.diagnosticSession = PROGRAM_SESSION;
    }

    AppRxDataLen_u16 = 0x02;
    TPTransactionInProgress_bo = TRUE;
    RxMessageType_u8 = PHYS;
    /* Signal that a message has been received */
    TPMessageReceived_bo = TRUE;

    /* Set default session and allow UDS layer finish switching to programming session */
    CurrentDiagnosticSession_u8 = DEFAULT_SESSION;
}

/**************************************************************************************************
 * Name         :  FLASH_WriteWord
 * Called by    :  PROG_Main
 * Parameters  : uAddr : Address to access
 *               bData : Word to write
 * Return code  :
 * Description  : This function writes 4bytes data in the Flash at the given address uAddr
 **************************************************************************************************/
static void FLASH_WriteWord(U32 uAddr, U32 bData)
{
    /* This table definition satisfies MISRA standard */
    U8 aubTmpData[UDS_PRG_SIZE] =
    {
        0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
    };

    aubTmpData[0] = (U8)((bData >> 24) & 0xFFU);
    aubTmpData[1] = (U8)((bData >> 16) & 0xFFU);
    aubTmpData[2] = (U8)((bData >> 8) & 0xFFU);
    aubTmpData[3] = (U8)(bData & 0xFFU);

    /*  DEVIATION:     0306
        DESCRIPTION:   Cast between a pointer to object and an integral type.
        JUSTIFICATION: The programming needs to be done to the given input address and
                       hence the U32 integer value needs to be converted to a pointer and used as
                       the programming address.Also, this is a part of legacy code and works fine */
    (void)FlsProgramFlash(aubTmpData, (U8*)uAddr, UDS_PRG_SIZE);

}
#if 0
/**************************************************************************************************
 * Name         :  Calculate_CRC16CCIT_HW
 * Called by    :
 * Parameters   :  *data - pointer to data
 *              :  len - length of data from which CRC will be count
 *              :  CRC16InitValue - init value of module cstat buffer
 * Return code  :  calculated CRC value
 * Description  :  Function calculates CRC value according to PSA specification.
 **************************************************************************************************/
static U16 Calculate_CRC16CCIT_HW(const U8 *data, U32 len, U16 CRC16InitValue)
{

    /* ************************************************************************

       This function, a copy from the K0 fusion project, is optimized to ensure
       that the T-Diag time, as specified in the DIAG1 specification, is not
       exceeded.
       Changes to this functionm should be considered carefully before being made

     **************************************************************************/

    uint8_t * inp_p;


    /*  DEVIATION:     0312
        DESCRIPTION:   Dangerous pointer cast results in loss of volatile qualification.
        JUSTIFICATION: There is no issue with losing of volatile qualification in this case.
     */
    /* PRQA S 0312 1 */
    inp_p = (uint8_t *)(&(CRC_0.INP1.R));

    /* CRC init value needs bits reversing */
    CRC16InitValue = (((CRC16InitValue >> 1U) & 0x5555U) | ((CRC16InitValue & 0x5555U) << 1U));
    CRC16InitValue = (((CRC16InitValue >> 2U) & 0x3333U) | ((CRC16InitValue & 0x3333U) << 2U));
    CRC16InitValue = (((CRC16InitValue >> 4U) & 0x0f0fU) | ((CRC16InitValue & 0x0f0fU) << 4U));
    CRC16InitValue = (((CRC16InitValue >> 8U) & 0x00ffU) | ((CRC16InitValue & 0x00ffU) << 8U));


    /* Deviation 0303 - globally disabled (4 lines below) */
    CRC_0.CFG1.B.POLYG = 0;
    CRC_0.CFG1.B.INV = 1U;
    CRC_0.CFG1.B.SWAP = 1U;
    CRC_0.CSTAT1.B.CSTAT = CRC16InitValue;

    while (len > 0UL)
    {
        /* Deviation 0303 - globally disabled */
        *inp_p = *data;
        /* DEVIATION:     0489
           DESCRIPTION:   Increment or decrement operation performed on pointer.
           JUSTIFICATION: Pointer Increment operation is necessary here.
         */
        /* PRQA S 0489 1 */
        ++data;
        --len;
    }
    /* Deviation 0303 - globally disabled */
    return (U16)(CRC_0 .OUTP1.B.OUTP ^ 0xFFFFU);
}
#endif
/**************************************************************************************************
 * Name         :  Calculate_CRC32CCIT_HW
 * Called by    :
 * Parameters   :  *data - pointer to data
 *              :  len - length of data from which CRC will be count
 *              :  CRC32InitValue - init value of module cstat buffer
 * Return code  :  calculated CRC value
 * Description  :  Function calculates CRC value according to PSA specification.
 **************************************************************************************************/
static U32 Calculate_CRC32CCIT_HW(const U8 *data, U32 len, U32 CRC32InitValue)
{

    /* ************************************************************************

       This function, a copy from the K0 fusion project, is optimized to ensure
       that the T-Diag time, as specified in the DIAG1 specification, is not
       exceeded.
       Changes to this functionm should be considered carefully before being made

     **************************************************************************/

    uint8_t * inp_p;


    /*  DEVIATION:     0312
        DESCRIPTION:   Dangerous pointer cast results in loss of volatile qualification.
        JUSTIFICATION: There is no issue with losing of volatile qualification in this case.
     */
    /* PRQA S 0312 1 */
    inp_p = (uint8_t *)(&(CRC_0.INP1.R));

    /* CRC init value needs bits reversing */
    /*CRC16InitValue = (((CRC16InitValue >> 1U) & 0x5555U) | ((CRC16InitValue & 0x5555U) << 1U));
    CRC16InitValue = (((CRC16InitValue >> 2U) & 0x3333U) | ((CRC16InitValue & 0x3333U) << 2U));
    CRC16InitValue = (((CRC16InitValue >> 4U) & 0x0f0fU) | ((CRC16InitValue & 0x0f0fU) << 4U));
    CRC16InitValue = (((CRC16InitValue >> 8U) & 0x00ffU) | ((CRC16InitValue & 0x00ffU) << 8U));*/

    CRC32InitValue = (((CRC32InitValue >> 1) & 0x55555555) | ((CRC32InitValue << 1) & 0xaaaaaaaa));
    CRC32InitValue = (((CRC32InitValue >> 2) & 0x33333333) | ((CRC32InitValue << 2) & 0xcccccccc));
    CRC32InitValue = (((CRC32InitValue >> 4) & 0x0f0f0f0f) | ((CRC32InitValue << 4) & 0xf0f0f0f0));
    CRC32InitValue = (((CRC32InitValue >> 8) & 0x00ff00ff) | ((CRC32InitValue << 8) & 0xff00ff00));
    CRC32InitValue = (((CRC32InitValue >> 16) & 0x0000ffff)|((CRC32InitValue << 16) & 0xffff0000));


    /* Deviation 0303 - globally disabled (4 lines below) */
    CRC_0.CFG1.B.POLYG = 1;
    CRC_0.CFG1.B.INV = 1U;
    CRC_0.CFG1.B.SWAP = 1U;
    CRC_0.CSTAT1.B.CSTAT = CRC32InitValue;

    while (len > 0UL)
    {
        /* Deviation 0303 - globally disabled */
        *inp_p = *data;
        /* DEVIATION:     0489
           DESCRIPTION:   Increment or decrement operation performed on pointer.
           JUSTIFICATION: Pointer Increment operation is necessary here.
         */
        /* PRQA S 0489 1 */
        ++data;
        --len;
    }
    /* Deviation 0303 - globally disabled */
    return (U32)(CRC_0 .OUTP1.B.OUTP ^ 0xFFFFFFFFU);
}


/**************************************************************************************************
 * Name         :  GetEmptyHistoryZoneIdx_u16
 * Called by    :
 * Parameters   :  *EmptyHistoryzoneIdx_u16 - pointer to last empty history zone
 * Return code  :  status if there is empty history zone
 * Description  :  Function checks if there is any empty location for history.
 **************************************************************************************************/
static BOOLEAN GetEmptyHistoryZoneIdx_ProgrammingDate(U8 *emptyHistoryZoneIdx_pu8)
{
    BOOLEAN status_bo = TRUE;
    U8 zoneIdx_u8 = 0;
    U8 byteIdx_u8 = 0;
    BOOLEAN historyZoneEmpty_bo = FALSE;

    if (emptyHistoryZoneIdx_pu8 != NULL)
    {
        /* Check if the marker (byte 45) is equal to 0x5C. If it is increase location index */
        while ((zoneIdx_u8 < NUMBER_OF_HISTORY_ZONES_MAX_2)
                && (historyRecording_2_au8[zoneIdx_u8][0u] != 0xFFu))
        {
        	zoneIdx_u8++;
        }

        /* Check if all bytes of current location are equal to 0xFF (RECORD_HIST_FREE). If no increase location index*/
        while ((historyZoneEmpty_bo == FALSE) && (zoneIdx_u8 < NUMBER_OF_HISTORY_ZONES_MAX_2))
        {
            historyZoneEmpty_bo = TRUE;
            while ((byteIdx_u8 < ZI_DATA_LENGTH) && (historyZoneEmpty_bo == TRUE))
            {
                if (historyRecording_2_au8[zoneIdx_u8][byteIdx_u8] != 0xFFu)
                {
                    historyZoneEmpty_bo = FALSE;
                    byteIdx_u8 = 0;
                    zoneIdx_u8++;
                }
                else
                {
                	byteIdx_u8++;
                }
            }
        }
        /* If there is no empty location, return false.*/
        if (zoneIdx_u8 == NUMBER_OF_HISTORY_ZONES_MAX_2)
        {
            status_bo = FALSE;
        }
        *emptyHistoryZoneIdx_pu8 = zoneIdx_u8;
    }
    else
    {
        status_bo = FALSE;
    }
    return status_bo;
}
/**************************************************************************************************
 * Name         :  GetEmptyHistoryZoneIdx_u16
 * Called by    :
 * Parameters   :  *EmptyHistoryzoneIdx_u16 - pointer to last empty history zone
 * Return code  :  status if there is empty history zone
 * Description  :  Function checks if there is any empty location for history.
 **************************************************************************************************/
static BOOLEAN GetEmptyHistoryZoneIdx_FingerPrint(U8 *emptyHistoryZoneIdx_pu8)
{
    BOOLEAN status_bo = TRUE;
    U8 zoneIdx_u8 = 0;
    U8 byteIdx_u8 = 0;
    BOOLEAN historyZoneEmpty_bo = FALSE;

    if (emptyHistoryZoneIdx_pu8 != NULL)
    {
        /* Check if the marker (byte 45) is equal to 0x5C. If it is increase location index */
        while ((zoneIdx_u8 < NUMBER_OF_HISTORY_ZONES_MAX_1)
                && (historyRecording_1_au8[zoneIdx_u8][0u] != 0xFFu))
        {
        	zoneIdx_u8++;
        }

        /* Check if all bytes of current location are equal to 0xFF (RECORD_HIST_FREE). If no increase location index*/
        while ((historyZoneEmpty_bo == FALSE) && (zoneIdx_u8 < NUMBER_OF_HISTORY_ZONES_MAX_1))
        {
            historyZoneEmpty_bo = TRUE;
            while ((byteIdx_u8 < ZI_DATA_LENGTH) && (historyZoneEmpty_bo == TRUE))
            {
                if (historyRecording_1_au8[zoneIdx_u8][byteIdx_u8] != 0xFFu)
                {
                    historyZoneEmpty_bo = FALSE;
                    byteIdx_u8 = 0;
                    zoneIdx_u8++;
                }
                else
                {
                	byteIdx_u8++;
                }
            }
        }
        /* If there is no empty location, return false.*/
        if (zoneIdx_u8 == NUMBER_OF_HISTORY_ZONES_MAX_1)
        {
            status_bo = FALSE;
        }
        *emptyHistoryZoneIdx_pu8 = zoneIdx_u8;
    }
    else
    {
        status_bo = FALSE;
    }
    return status_bo;
}
#if 0
/**************************************************************************************************
 * Name         :  RDBI_readZI
 * Called by    :
 * Parameters   :  *outputData - pointer to data output buffer
 * Return status:  status_u8: FALSE if data is read or UDS_NRC_22 if there is wrong CRC
 * Description  :  Function fills the message register with data required by RDBI.
 **************************************************************************************************/
static U8 RDBI_readZI(U8 *outputData_pu8)
{
    U8 status_u8 = FALSE;
    U16 lastZoneHistoryIdx_u16;
    U16 idx_u16;
    U8 ProdDay_u8 = 0U;
    U8 ProdMonth_u8 = 0U;
    U8 ProdYear_u8 = 0U;
    U8 *buffTvds_pu;
    volatile U64 load_status_u64;

    if (outputData_pu8 != NULL)
    {
        /* Recover the index of the first empty history zone */
        (void) GetEmptyHistoryZoneIdx(&lastZoneHistoryIdx_u16);

        /* Recover last history recording */
        if (lastZoneHistoryIdx_u16 != 0)
        {
            lastZoneHistoryIdx_u16--;
        }

        /* If CRC of the history sector is incorrect send NRC 22*/
        if ((Calculate_CRC16CCIT_HW((const U8*) (historyRecording_au8[lastZoneHistoryIdx_u16]),
             ZI_DATA_LENGTH, CRC_CCITT_INIT_TRANSFER) == CRC_CCITT_VALUE))
        {
            for (idx_u16 = 0; idx_u16 < (ZI_DATA_LENGTH / 2); idx_u16++)
            {
                /* Deviation 0492 - globally disabled */
                outputData_pu8[idx_u16] = historyRecording_au8[lastZoneHistoryIdx_u16][idx_u16];
            }

            /* Now try to get the Tvds information from NVM */
            if (FlsGet_From_Nvm(BN_NVM_TRV_AC, TVDS_DATA_OFFSET, &buffTvds_pu) == NVM_READ_PASS)
            {
                /*Check for meaningful values else use the value from the history record*/
                /* History record .mot file will have to be attached boot which means that this
                 leaves an option to get the manufacturing date from history record if Tvds is
                 invalid */
                /* Giving negative response here for invalid value here is not an option
                 as this could have other information which could still be used to trace the
                 product */
                /* Deviation 0491 - globally disabled (7 lines below)*/
                ProdDay_u8 = buffTvds_pu[DAY_idx];
                ProdMonth_u8 = buffTvds_pu[MONTH_idx];
                ProdYear_u8 = buffTvds_pu[YEAR_idx];

                if (((buffTvds_pu[DAY_idx] >= FIRST_DAY_OF_MONTH) && (buffTvds_pu[DAY_idx] <= LAST_DAY_OF_MONTH))
                 && ((buffTvds_pu[MONTH_idx] >= JANUARY) && (buffTvds_pu[MONTH_idx] <= DECEMBER)))
                {
                    /* Deviation 0492 - globally disabled (3 lines below) */
                    outputData_pu8[6] = ConvertHexToBCD(ProdDay_u8);
                    outputData_pu8[7] = ConvertHexToBCD(ProdMonth_u8);
                    outputData_pu8[8] = ConvertHexToBCD(ProdYear_u8);
                }
            }

            load_status_u64 = UDS_READ_LOAD_STATUS();

            /* If the application is not valid Or If the calibration is not valid then respond with
               Software Version = 0x00, Software Edition = 0x00/0x00 & Downloading Date = 0x00/0x00/0x00 */
            if((load_status_u64 != SYS_LOAD_STATUS_MAIN_APP_VALID) || (CALIBRATION_INVALID == historyRecording_au8[lastZoneHistoryIdx_u16][10]))
            {
                outputData_pu8[10] = 0x00; /* Software Version - 1 byte   */
                outputData_pu8[11] = 0x00; /* Software Edition - 1st byte */
                outputData_pu8[12] = 0x00; /* Software Edition - 2nd byte */
                outputData_pu8[13] = 0x00; /* Downloading Date - day      */
                outputData_pu8[14] = 0x00; /* Downloading Date - month    */
                outputData_pu8[15] = 0x00; /* Downloading Date - year     */
            }
        }
        else
        {
            status_u8 = CONDITIONS_NOT_CORRECT;
        }
    }
    return status_u8;
}


/**************************************************************************************************
 * Name         :  RDBI_IdentSys
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return code  :  status_u8 - Good or UDS_NRC_22
 * Description  :  Function fills the data output buffer.
 **************************************************************************************************/
static U8 RDBI_identSys(U8 *outputData_pu8)
{
    U8 status_u8 = FALSE;
    U16 lastZoneHistoryIdx_u16;
    U8 *tmpRefSup1_pu8;
    U8 *tmpRefSup2_pu8;
    U8 *tmpRefPsa1_pu8;
    U8 *tmpRefPsa2_pu8;
    U8 *tmpPSASoftEdition_pu8;
    U32 appli_u32 = *((U32 *) &__SHARED_FLASH_AREA[0]);
    U32 versdiag_u32 = *((U32 *) &__SHARED_FLASH_AREA[1U]);
    volatile U64 load_status_u64;

    /* REFPSA  to be obtained from NVM */
    if (NULL != outputData_pu8)
    {
        /* DEVIATION:     3415
           DESCRIPTION:   The right hand operand of '&&' or '||' has side effects.
           JUSTIFICATION: The statement works fine.
         */
        /* PRQA S 3415 2 */
        if ((NVM_READ_PASS == (FlsGet_From_Nvm(BN_NVM_TRV_AC, REFPSA1_DATA_OFFSET, &tmpRefPsa1_pu8)))
         && (NVM_READ_PASS == (FlsGet_From_Nvm(BN_NVM_TRV_AC, REFPSA2_DATA_OFFSET, &tmpRefPsa2_pu8))))
        {
            /* Deviation 0491, 0492 - globally disabled (5 lines below)*/
            outputData_pu8[0] = (U8)(tmpRefPsa1_pu8[0]);
            outputData_pu8[1U] = (U8)(tmpRefPsa1_pu8[1U]);
            outputData_pu8[2U] = (U8)(tmpRefPsa1_pu8[2U]);
            outputData_pu8[3U] = (U8)(tmpRefPsa1_pu8[3U]);
            outputData_pu8[4U] = (U8)(tmpRefPsa2_pu8[0]);
        }
        else
        {
            /* Deviation 0492 - globally disabled (5 lines below) */
            outputData_pu8[0] = 0x00;
            outputData_pu8[1U] = 0x00;
            outputData_pu8[2U] = 0x00;
            outputData_pu8[3U] = 0x00;
            outputData_pu8[4U] = 0x00;
        }

        /* CODE_FNR_2 */
        /* Deviation 0492 - globally disabled (2 lines below)*/
        outputData_pu8[5U] = TRW_CODE_FNR_1;
        outputData_pu8[6U] = TRW_CODE_FNR_2;

        /* REFSUP to be obtained from NVM */
        /* DEVIATION:     3415
           DESCRIPTION:   The right hand operand of '&&' or '||' has side effects.
           JUSTIFICATION: Statement is correct.
         */
        /* PRQA S 3415 2 */
        if ((NVM_READ_PASS == (FlsGet_From_Nvm(BN_NVM_TRV_AC, REFSUP1_DATA_OFFSET, &tmpRefSup1_pu8)))
         && (NVM_READ_PASS == (FlsGet_From_Nvm(BN_NVM_TRV_AC, REFSUP2_DATA_OFFSET, &tmpRefSup2_pu8))))
        {
            /* Deviation 0491, 0492 - globally disabled (5 lines below)*/
            outputData_pu8[7U] = (U8)(tmpRefSup1_pu8[0]);
            outputData_pu8[8U] = (U8)(tmpRefSup1_pu8[1U]);
            outputData_pu8[9U] = (U8)(tmpRefSup1_pu8[2U]);
            outputData_pu8[10U] = (U8)(tmpRefSup1_pu8[3U]);
            outputData_pu8[11U] = (U8)(tmpRefSup2_pu8[0]);
        }
        else
        {
            /* Deviation 0492 - globally disabled (5 lines below) */
            outputData_pu8[7U] = 0x00;
            outputData_pu8[8U] = 0x00;
            outputData_pu8[9U] = 0x00;
            outputData_pu8[10U] = 0x00;
            outputData_pu8[11U] = 0x00;
        }

        /* Bootloader SOFTVERSION hardcoded in flash */
        outputData_pu8[12U] = boot_SoftVersion_u8;

        /* SOFTEDITION Obtained from history just initialize before history is read */
        outputData_pu8[13U] = 0x00;

        /* CALIBVERSION always set to 0xFF */
        /* Deviation 0492 - globally disabled */
        outputData_pu8[14U] = 0xFFU;

        /* CALIBEDITION always set to 0xFF */
        /* Deviation 0492 - globally disabled */
        outputData_pu8[15U] = 0xFFU;

        load_status_u64 = UDS_READ_LOAD_STATUS();
#if 0
        /* When application is NOT VALID */
        if (load_status_u64 != SYS_LOAD_STATUS_MAIN_APP_VALID)
        {
            /* Overwrite the SOFTEDITION value from the history record. *
             * Recover the index of the first empty history zone.       */
            (void) GetEmptyHistoryZoneIdx(&lastZoneHistoryIdx_u16);

            if (lastZoneHistoryIdx_u16 != 0)
            {
                lastZoneHistoryIdx_u16--;
            }
            if (CRC_CCITT_VALUE == Calculate_CRC16CCIT_HW((const U8*)(historyRecording_au8[lastZoneHistoryIdx_u16]),
                                                          ZI_DATA_LENGTH,
														  CRC_CCITT_INIT_TRANSFER))
            {
                /* Deviation 0492 - globally disabled */
                outputData_pu8[13U] = historyRecording_au8[lastZoneHistoryIdx_u16][11U];
            }

            /* VERSDIAG set to zero if there is no application*/
            /* Deviation 0492 - globally disabled */
            outputData_pu8[16U] = 0x00;

            /* NBPARAMFLT set to zero if there is no application*/
            /* Deviation 0492 - globally disabled */
            outputData_pu8[17U] = 0x00;

            /* APPLI set to 0xFFFFFFFF when there is no application */
            /* Deviation 0492 - globally disabled (4 lines below) */
            outputData_pu8[18U] = 0xFFU;
            outputData_pu8[19U] = 0xFFU;
            outputData_pu8[20U] = 0xFFU;
            outputData_pu8[21U] = 0xFFU;
        }
        /* When application is VALID */
        else
#endif
        {
            if ((NVM_READ_PASS == FlsGet_From_Nvm(BN_NVM_TRV_AC, PSASOFTEDITION_DATA_OFFSET, &tmpPSASoftEdition_pu8)))
            {
                /* Deviation 0491, 0492 - globally disabled (1 line below)*/
                outputData_pu8[13U] = (U8)(tmpPSASoftEdition_pu8[0]);
            }

            /* VERSDIAG is shared by the application in shared flash */
            /* Deviation 0492 - globally disabled */
            outputData_pu8[16U] = (U8)versdiag_u32;

            /* NBPARAMFLT */
            /* Deviation 0492 - globally disabled */
            outputData_pu8[17U] = (U8)PSA_NBPARAMFLT;

            /* APPLI is shared by the application in the shared flash */
            /* Deviation 0492 - globally disabled (4 lines below) */
            outputData_pu8[18U] = (U8)(appli_u32 >> 24U);
            outputData_pu8[19U] = (U8)(appli_u32 >> 16U);
            outputData_pu8[20U] = (U8)(appli_u32 >> 8U);
            outputData_pu8[21U] = (U8)appli_u32;
        }
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return status_u8;
}
#endif

/**************************************************************************************************
 * Name         :  UDS_Send_CAN_Msg_Complete
 *-------------------------------------------------------------------------------------------------
 * Parameters   :   -
 * Return value :   -
 * Description  :  Callback from TP, that UDS message has been sent
 **************************************************************************************************/
void UDS_Send_Msg_Complete(void)
{
    UDS_Send_Msg_Complete_bo = TRUE;

    return;
}
#if 0
/**************************************************************************************************
 * Name         :  RDBI_ECU_Serial_Number_Length
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return value :  status_u8 - 0 (data read) or negative response number
 * Description  :  Function fills the output buffer with ECU serial number length.
 **************************************************************************************************/
static U8 RDBI_ECU_Serial_Number_Length(U8 *outputData_pu8)
{
    U8 status_u8 = 0U;

    /*
       Response frame:
       Byte 1 - SID, Bytes 2,3 - DID, Byte 4 - Ecu serial number length
       outputData_pu8 points here directly into 4-th byte of response frame
    */
    if (NULL != outputData_pu8)
    {
        *outputData_pu8 = ECU_SERIAL_NUMBER_LENGTH;
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return (status_u8);
}
/**************************************************************************************************
 * Name         :  RDBI_ECU_Programming_Counter
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return value :  status_u8 - 0 (data read) or negative response number
 * Description  :  Function fills the output buffer with ECU Flash programming counter value
 **************************************************************************************************/
static U8 RDBI_ECU_Programming_Counter(U8 *outputData_pu8)
{
    U8 status_u8 = 0U;
    U32 l_Fls_Program_Cntr = 0x00;

    /*
       Response frame:
       Byte 1 - SID, Bytes 2,3 - DID, Byte 4 - Ecu serial number length
       outputData_pu8 points here directly into 4-th byte of response frame
    */
    if (NULL != outputData_pu8)
    {
    	l_Fls_Program_Cntr = ((U32)*(__ECU_PROG_COUNTER));

    	UDS_Fls_Cntr_Stat =  ((U8)((l_Fls_Program_Cntr >> (U8)0x08U) & (U8)0xFF));

    	if(0xFFu == UDS_Fls_Cntr_Stat)
    	{
    		*outputData_pu8 = 0x00u;			/*if not programmed value should be 0*/
    	}
    	else
    	{
    		*outputData_pu8 = (U8)((U32)l_Fls_Program_Cntr & (U8)0xFF);
    	}
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return (status_u8);
}

/**************************************************************************************************
 * Name         :  RDBI__ECU_Serial_Number
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return value :  status_u8 - 0 (data read) or negative response number
 * Description  :  Function fills the output buffer with ECU serial number.
 **************************************************************************************************/
static U8 RDBI_ECU_Serial_Number(U8 *outputData_pu8)
{
    U8 status_u8 = 0U;
    U8 *tmpAcsn_pu8;
    U32 *tmpAcsn_pu32;

    /*
       Response frame:
       Byte 1 - SID, Bytes 2,3 - DID
       outputData_pu8 points here directly into 4-th byte of response frame (serial number)
    */

    if (NULL != outputData_pu8)
    {
        if (NVM_READ_PASS == FlsGet_From_Nvm(BN_NVM_TRV_AC, ACSN_DATA_OFFSET, &tmpAcsn_pu8))
        {
            /* Deviation 0310 - globally disabled */
            tmpAcsn_pu32 = (U32 *)tmpAcsn_pu8;
            /* Bytes 4-12 : Parameter TRA_NUM_CHR - Serial number in ASCII format */
            ConvertNumToAscii(*tmpAcsn_pu32, outputData_pu8, ECU_SERIAL_NUMBER_LENGTH);
        }
        else
        {
            status_u8 = CONDITIONS_NOT_CORRECT;
        }
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return(status_u8);
}

/**************************************************************************************************
 * Name         :  RDBI_ECU_Manufacturing_Date
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return value :  status_u8 - 0 (data read) or negative response number
 * Description  :  Function fills the output buffer with ECU serial number length.
 **************************************************************************************************/
static U8 RDBI_ECU_Manufacturing_Date(U8 *outputData_pu8)
{
    U8 status_u8 = 0;
    U8 ProdDay_u8 = 0;
    U8 ProdMonth_u8 = 0;
    U8 ProdYear_u8 = 0;
    U8 *buffTvds_pu8;

    /*
       Response frame:
       Byte 1 - SID, Bytes 2,3 - DID, Bytes 4 - 6 Ecu manufacturing date
       outputData_pu8 points here directly into 4-th byte of response frame
     */
    if (NULL != outputData_pu8)
    {
        /* Now try to get the Tvds information from NVM */
        if (NVM_READ_PASS == FlsGet_From_Nvm(BN_NVM_TRV_AC, TVDS_DATA_OFFSET, &buffTvds_pu8))
        {
            /* Deviation 0491 - globally disabled (9 lines below)*/
            ProdDay_u8 = buffTvds_pu8[DAY_idx];
            ProdMonth_u8 = buffTvds_pu8[MONTH_idx];
            ProdYear_u8 = buffTvds_pu8[YEAR_idx];

            /* Bytes 4-6 : Parameters JOURPROD, MOISPROD, ANNEEPROD, */
            /* ie ECU Production date in Day, Month, Year order */
            if (((buffTvds_pu8[DAY_idx] >= FIRST_DAY_OF_MONTH) && (buffTvds_pu8[DAY_idx] <= LAST_DAY_OF_MONTH))
             && ((buffTvds_pu8[MONTH_idx] >= JANUARY) && (buffTvds_pu8[MONTH_idx] <= DECEMBER)))
            {
                /* Deviation 0492 - globally disabled (3 lines below) */
                outputData_pu8[0] = ConvertHexToBCD(ProdDay_u8);
                outputData_pu8[1U] = ConvertHexToBCD(ProdMonth_u8);
                outputData_pu8[2U] = ConvertHexToBCD(ProdYear_u8);
            }
            else
            {
                status_u8 = CONDITIONS_NOT_CORRECT;
            }
        }
        else
        {
            status_u8 = CONDITIONS_NOT_CORRECT;
        }
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return(status_u8);
}
/**************************************************************************************************
 * Name         :  RDBI_ECU_Programming_Date
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  *outputData - pointer to data output buffer
 * Return value :  status_u8 - 0 (data read) or negative response number
 * Description  :  Function fills the output buffer with ECU serial number length.
 **************************************************************************************************/
static U8 RDBI_ECU_Programming_Date(U8 *outputData_pu8)
{
    U8 status_u8 = 0;
    U8 ProdDay_u8 = 0;
    U8 ProdMonth_u8 = 0;
    U8 ProdYear_MSB_u8 = 0;
    U8 ProdYear_LSB_u8 = 0;

    volatile U32 Program_Date = 0x00;

    /*
       Response frame:
       Byte 1 - SID, Bytes 2,3 - DID, Bytes 4 - 6 Ecu manufacturing date
       outputData_pu8 points here directly into 4-th byte of response frame
     */
    if (NULL != outputData_pu8)
    {

    	  UDS_Fls_Prog_Cntr = FLASH_READ_PROGRAM_COUNTER();
    	  UDS_Fls_Cntr_Stat =  ((U8)((UDS_Fls_Prog_Cntr >> (U8)0x08U) & (U8)0xFF));

    	  if(0xFFu == UDS_Fls_Cntr_Stat)			/* ECU not flashed atleast once with serial loader tool*/
    	  {
    		  	  outputData_pu8[0U] =  0x00u;
    		  	  outputData_pu8[1U] = 0x00u;
    		      outputData_pu8[2U] = 0x00u;
    		      outputData_pu8[3U] = 0x00u;
    	  }
    	  else
    	  {

    		  	  Program_Date = FLASH_READ_PROGRAM_DATE();

    		  	  /* Deviation 0491 - globally disabled (9 lines below)*/
    		  	  ProdDay_u8 =  (U8)(Program_Date & (U8)0xFF);
    		  	  ProdMonth_u8 = (U8)((Program_Date >> (U8)8U) & (U8)0xFF);
    		  	  ProdYear_LSB_u8 = (U8)((Program_Date >> (U8)16U) & (U8)0xFF);
    		  	  ProdYear_MSB_u8 = (U8)((Program_Date >> (U8)24U) & (U8)0xFF);

    		  	  /* Bytes 4-6 : Parameters JOURPROD, MOISPROD, ANNEEPROD, */
    		  	  /* ie ECU Production date in Day, Month, Year order */
    		  	  if (((ProdDay_u8 >= FIRST_DAY_OF_MONTH) && (ProdDay_u8 <= LAST_DAY_OF_MONTH))
    		  			  && ((ProdMonth_u8 >= JANUARY) && (ProdMonth_u8 <= DECEMBER)))
    		  	  {
    		  		  /* Deviation 0492 - globally disabled (3 lines below) */
    		  		  /*  outputData_pu8[0] = ConvertHexToBCD(ProdDay_u8);
    		  		    outputData_pu8[1U] = ConvertHexToBCD(ProdMonth_u8);
    		  		    outputData_pu8[2U] = ConvertHexToBCD(ProdYear_u8);*/
    		  		  	  outputData_pu8[0U] =  ProdYear_MSB_u8;
    		  		  	  outputData_pu8[1U] = ProdYear_LSB_u8;
    		  		  	  outputData_pu8[2U] = ProdMonth_u8;
    		  		  	  outputData_pu8[3U] = ProdDay_u8;
    		  	  }
    		  	  else
    		  	  {
    		  		  	  status_u8 = CONDITIONS_NOT_CORRECT;
    		  	  }
    	  }
    }
    else
    {
        status_u8 = CONDITIONS_NOT_CORRECT;
    }

    return(status_u8);
}

/****************************************************************************/
/*                                                                          */
/*  Function    : ConvertNumToAscii                                         */
/*                                                                          */
/*  Parameters  : U32 source variable that needs to be converted            */
/*                U8 pointer to destination array                           */
/*                No of digits to be converted                              */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description : Function to convert a U32 number to ASCII                 */
/*                                                                          */
/****************************************************************************/
static void ConvertNumToAscii(U32 sourceVar_u32, U8 *dstArray_pu8, U8 noOfDigits_u8)
{
    U32 modMul_u32 = 1UL;
    U32 tmpResult_u32;
    U8  index_u8;

    for (index_u8 = noOfDigits_u8; index_u8 > 0; index_u8--)
    {
        /* Extract digit at (no_of_digits - index_u8) position */
        tmpResult_u32 = ((sourceVar_u32 / modMul_u32) % 10UL);
        modMul_u32 = modMul_u32 *10UL;
        /* Add '0' to convert to ASCII ('0' equals 0x30 in ASCII)*/
        /* Deviation 0492 - globally disabled */
        dstArray_pu8[index_u8 - 1] = (U8)(tmpResult_u32 + '0');
    }
}
#endif
#if 0
/************************************************************************************/
/*                                                                                  */
/*  Function    : ConvertHexToBCD                                                   */
/*                                                                                  */
/*  Parameters  : U8 source variable in hex format that needs to be converted to BCD*/
/*                                                                                  */
/*  Returns     : U8 - BCD value                                                    */
/*                                                                                  */
/*  Description : Function to convert a U8 hex number to BCD                        */
/*                                                                                  */
/************************************************************************************/
static U8 ConvertHexToBCD (U8 source_hex_var)
{
    U8  return_bcd_value_u8;

    if (source_hex_var > 99U)
    {
        /* Invalid value since valid decimal value range is (0-99) */
        return_bcd_value_u8 = 0xFFU;
    }
    else
    {
        /* Convert the hex number to its decimal equivalent by extracting the decimal digits at */
        /* 'Units' and 'Tens' positions and then bitwise ORing them together */
        return_bcd_value_u8 = (U8)(((source_hex_var / 10UL) << 4U) | (source_hex_var % 10UL));
        /* Example:
        Hex number '0x19' is converted to '0x25' where '25' is it the decimal equivalent of '0x19' */
    }

    return (return_bcd_value_u8);
}
#endif
/************************************************************************************/
/*                                                                                  */
/*  Function    : GetNBytes                                                   */
/*                                                                                  */
/*  Parameters  : memory logical address and size of the address*/
/*                                                                                  */
/*  Returns     : uint32_t - memory logical index                                   */
/*                                                                                  */
/*  Description : Function to convert a U8 hex number to BCD                        */
/*                                                                                  */
/************************************************************************************/
static uint32_t GetNBytes(uint8_t const* start, uint8_t n)
{
	uint8_t i;
    uint32_t result = 0;

    /* CAUTION! Correct only if the diagnostic buffer is in network order, big endian. */
    for (i=0; i<n; ++i) {
        result = (result << 8) | (uint32_t)start[i];
    }

    return result;
}

/* PRQA S 4700 -- */
/* PRQA S 0491 -- */
/* PRQA S 0492 -- */
/* PRQA S 0310 -- */
/* PRQA S 0303 -- */
/* PRQA S 0306 -- */
/* PRQA S 0308 -- */
/* PRQA S 0662 -- */
/* PRQA S 0488 -- */
/* PRQA S 0715 -- */
