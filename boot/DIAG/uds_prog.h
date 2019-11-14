/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/DIAG/project.pj $
        $RCSfile: uds_prog.h $
        $Revision: 1.2 $
        $Date: 2019/08/21 18:18:21CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/


#ifndef UDS_PROG_INC
#define UDS_PROG_INC

#ifdef DIAG_SUBSYSTEM

#define KEY_APPLI_CHANGE_ENABLED   0   /* 0 - change Key_Appli disabled, 1- change Key_Appli enabled */
#define ZI_ENABLE 0  /* 0 - disable ZI, 1 - enable ZI */
#define ZI_READ 0

/*************************************************************/
/*      DEFINITIONS LOCAL TO THIS SUBSYSTEM                  */
/*************************************************************/

/* The -0x00400000 offset is applied in the .mot file to support 24bit addressing in flash loading process */
/* and now it has to be applied during UDS transfer data. */
#define ADDRESS_OFFSET 0x00400000UL

/* Minimum lengths of services */
#define SECURITY_ACCESS_MINIMUM_LENGTH     2U
#define MIN_TRANSFER_DATA_LENGTH           2U			//Rami changed from 8u to 2u as per the requirement
#if (1 == ZI_ENABLE)
#define MIN_ZI_LENGTH                      4U
#endif
#if (1 == KEY_APPLI_CHANGE_ENABLED)
#define KEY_APPLI_LENGTH                   6U
#endif
#define RC_ERASE_START_LEN                 0x0CU		//Rami changed from 7U to 8U
#define RC_ERASE_STATUS_LEN                0x0CU		//Rami changed from 4U to 8U
#define RC_CHECK_START_LEN                 0x0CU		//Rami changed from 4U to 8U
#define RC_CHECK_STATUS_LEN                0x0CU		//Rami changed from 4U to 8U
#define RC_START_LEN           			   4U
#define RC_STATUS_LEN           		   4U
#define RC_MIN_REQ_LENGTH                  4U		/* changed to 4 from 8 because for check veh speed and check programming dependencies the request length is 4 bytes only*/

/* Lengths of services */
#define REQUEST_SEED_LENGTH                2U
#define SEND_KEY_LENGTH                    6U
#define ECU_RESET_LENGTH                   2U
#define DIAG_SESS_CONTROL_LENGTH           2U
#define RC_ERASE_44FORMAT_LEN              13U
#define RC_CHECKPROG_44FORMAT_LEN          17U
#define REQ_DOWNLOAD_FORMAT_LEN            11U
#if 0
#define TRANSFER_DATA_DWNLD_MIN_LEN        4U
#else
#define TRANSFER_DATA_DWNLD_MIN_LEN        3U
#endif
#define TRANSFER_EXIT_LENGTH               1U
#define TESTER_PRESENT_REQ_LENGTH          2U
#define READ_DTC_BY_STATUS_MASK_LENGTH     3U
#define CLEAR_DTC_REQ_LENGTH			   4U
#define COMM_CTRL_REQ_LENGTH       		   3U

/* ECU Reset Service */
#define ECU_HARD_RESET                     1U
#define ECU_KEY_OFF_ON_RESET               2U
#define ECU_SOFT_RESET                     3U

#if (1 == ZI_READ)
/* History zone */
#define NUMBER_OF_HISTORY_ZONES_MAX        21U
#define RECORD_HIST_FREE                   0xFFU
#define RECORD_HIST_CORRECT                0x5CU
#define ZI_MARKER_PLACE                    45U
#endif

#define NUMBER_OF_HISTORY_ZONES_MAX_1        50U
#define NUMBER_OF_HISTORY_ZONES_MAX_2        77U
#define ZI_DATA_LENGTH                 8u


/* Transport layer timing ... */
#define UDS_P2CAN_SERVER_MAX_MSB           0x00UL
/* 200ms = 0xC8 * 1ms */
#define UDS_P2CAN_SERVER_MAX_LSB           0x32UL	/* changed to 50ms from 200ms in X37 project*/
#define UDS_P2STARCAN_SERVER_MAX_MSB       0x00UL
/* 200ms = 0x14 * 10ms */
#define UDS_P2STARCAN_SERVER_MAX_LSB       0xC3UL

/* Local Identifiers */
#define NEG_RESPONSE_BYTE                   0x7FU

/* Negative response codes */
#define SERVICE_NOT_SUPPORTED                     0x11U
#define SUBFUNCTION_NOT_SUPPORTED                 0x12U
#define INCORRECT_MSG_LENGTH_OR_FORMAT            0x13U
#define CONDITIONS_NOT_CORRECT                    0x22U
#define REQUEST_SEQUENCE_ERROR                    0x24U
#define REQUEST_OUT_OF_RANGE                      0x31U
#define SECURITY_ACCESS_DENIED                    0x33U
#define INVALID_KEY                               0x35U
#define EXCEEDED_NUMBER_OF_ATTEMPTS               0x36U
#define REQUIRED_TIME_DELAY_NOT_EXPIRED           0x37U
#define UPLOAD_DOWNLOAD_NOT_ACCEPTED              0x70U
#define TRANSFER_DATA_SUSPENDED                   0x71U
#define GENERAL_PROGRAMMING_FAILURE               0x72U
#define WRONG_SEQUENCE_COUNTER                    0x73U
#define RESPONSE_PENDING                          0x78U
#define SUBFUNCT_NOT_SUPPORTED_IN_ACTIVE_SESSION  0x7EU
#define SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION   0x7FU
#define VOLTAGE_TOO_HIGH                          0x92U
#define VOLTAGE_TOO_LOW                           0x93U

/* Diagnostic sessions */
#define DEFAULT_SESSION       0x01U
#define PROGRAM_SESSION       0x02U
#define EXTENDED_SESSION      0x03U

/* To allow compilation of other files without change ... */
#define STANDARD          DEFAULT_SESSION

/* Supported message id's (Service ids) */

#define SUPPRESS_POS_RESPONSE             0x80U
#define SUBFUNCTION_MASK                  0x7FU

#define DIAGNOSTIC_SESSION_CONTROL_ID     0x10U
#define RESET_ECU_ID                      0x11U
#define CLEAR_DIAGNOSTIC_INFO_ID          0x14U
#define READ_DTC_INFORMATION_ID           0x19U
#define READ_DATA_BY_IDENT_ID             0x22U
#define SECURITY_ACCESS_ID                0x27U
#define COMMUNICATION_CONTROL_ID          0x28U
#define WRITE_DATA_BY_IDENT_ID            0x2EU
#define TESTER_PRESENT_ID                 0x3EU
#define CONTROL_DTC_SETTING_ID            0x85U
#define IOCONTROL_BY_IDENT_ID             0x2FU
#define ROUTINE_CONTROL_ID                0x31U
#define REQUEST_DOWNLOAD_ID               0x34U
#define TRANSFER_DATA_ID                  0x36U
#define REQUEST_TRANSFER_EXIT_ID          0x37U

#define CONTROLDTCOFF					  0x02u
#define CONTROLDTCON					  0x01u
#define SUPP_CONTROLDTCOFF				  0x82u
#define SUPP_CONTROLDTCON				  0x81u

#define DISABLE_RX_TX_COMM				  0x03u
#define ENABLE_RX_TX_COMM				  0x00u
#define SUPP_DISABLE_RX_TX_COMM			  0x83u
#define SUPP_ENABLE_RX_TX_COMM			  0x80u
#define COMM_TYPE						  0x01u				/*Normal Communication Message*/

/* Defines onto request buffer */
#define MESSAGE_DATA_LENGTH             UDS_data_in.UDS_data_length
#define MAX_ID_DATA_BYTES               300U
#define MAX_NUM_DID_READ                10U

/* Define max size of the variable uint8_t */
#define MAX_UINT8                     255U

/* Security access */
#define REQUEST_SEED_PRG                             1U
#define SEND_KEY_PRG                                 2U
#define REQUEST_SEED_DEVICECTRL                      3U
#define SEND_KEY_DEVICECTRL                          4U

/* 10000msec @ 1ms resolution */
#define SA_PROHIBIT_DELAY                            10000UL
/* 0 - 10000 to bypass 10s delay at the start of the bootloader */
#define SECURITY_ACCESS_PROHIBIT_TIMER_INIT_VALUE    (-SA_PROHIBIT_DELAY)		/*Removed the -  by Rami*/
/* defined value of KEY_APPLI by PSA to bypass security sequence */
/*#define KEY_APPLI_BYPASS                             0xFFFFU*/
/* Address of the INFRACT_ATT variable in calibration/application memory area */
#define PROG_INFRACT_ATT_ADDRESS             0x00FDFFF0UL
/* Reserve space in memory for the INFRACT_ATT information */
#define m_eInfractAtt (U32)(*((U32*)(PROG_INFRACT_ATT_ADDRESS)))

#define ERASED_FLASH_VALUE (U32)0xFFFFFFFFU
#define ERASED_FLASH_XOR_LSB_BYTE(value) (U32)(ERASED_FLASH_VALUE ^ (U8)~(value))

/* Status of the violation attempt */
#define PROG_NO_INFRACT_ATT             ERASED_FLASH_VALUE
#define PROG_INFRACT_ATT                ERASED_FLASH_XOR_LSB_BYTE(0x00U)

/* Final Main application erase block index */
#define ERASE_FUNC_DELAY                175U

/* Routine control defines */
#define TOOL_SIGNATURE                  0xF05Au
#define START_ROUTINE                   1U
#define STATUS_ROUTINE                  3U
#define CAL_AREA                        0U
#define CAL_AREA_END                    1U
#define APP_START_AREA                  2U
#define APP_END_AREA                    9U
#define ROUTINE_IN_PROGRESS             0x01u
#define ROUTINE_OK                      0x02u
#define ROUTINE_NOK                     0x03u
#define ROUTINE_OK_X37                  0x00u
#define ROUTINE_NOK_X37                 0x01u
#define CHK_MEMORY_ROUTINE_OK			0X00U
#define CHK_MEMORY_ROUTINE_NOK			0X01U
#define CAL_NOK                         0x04u
#define APP_NOK                         0x08u
#define WRITING_ERROR                   0x10u
#define ERASE_MEMORY                    0xFF00u
#define CHECK_MEMORY                    0x0202u		/* to 0x0202u from F000u*/
#define CHECK_PROGRAM_DEPENDENCIES		0xFF01u
#define CHECK_VEH_ENG_SPEED				0x0203u
#define MAX_BYTES_RC_GETRES             0x10U
#define MAX_RC_CTRL_BYTES               0x4U	//Changed by Rami from 3U to 4U
#define MAX_CD_CTRL_BYTES				0x03u

/* Due to direct and indirect implementation of the algorithm possible we need to use 0x1D0F or 0xFFFF
* to much up result produced by algorithm in the SRecord and in data transfer. */
#define CALIB_AREA_BEG                 0x00FC0000UL
#define CALIB_AREA_END                 0x00FE0000UL
#define APP_AREA_BEG                   0x01000000UL
#define APP_AREA_END                   0x01200000UL
#define BRP_AREA_BEG                   0x00FD0000UL
#define BRP_AREA_END				   0x00FD6C40UL
#define PCB_TEST_CODE_AREA_END		   0x00FD425FUL
#define CALIB_AREA_END_Loc             0x00FC7BE0UL	/*added by Rami*/
#define APP_AREA_END_BRP			   0x01010040UL
#define MIRROR_CALIB_AREA_BEG          0x08FC0000UL
#define MIRROR_CALIB_AREA_END          0x08FE0000UL



/* 0x34 Parameter format */
#define NUMBER_OF_PARAMETERS            0x11u
#define PARAMETER_DFI                   0x00u				//data format identifier
#define PARAMETER_AALFI                 0x44u				//Address and length format identifier
#define PARAMETER_MS					0x00u
#define MAX_NUMBER_OF_BLOCK_LENGTH      0x0C02u				//Rami changed from 0x00 to 0x22 as per the requirement
#define RD_RESPONSE_LENGTH              6					//Rami changed from 3 to 6 as per the requirement
#define WD_RESPONSE_LENGTH 				3
#define WDBI_REQ_LENGTH 				4
#define LENGTH_FMT_ID                   0x40			//Rami changed from 0x10 to 0x40 as per the requirement

/* Service 0x22 parameters */
/* Block number of NVM_TRV_AC is 16 */
#define BN_NVM_TRV_AC                        16U
/* 12 bytes offset */
#define TVDS_DATA_OFFSET                     12U
/* 20 bytes offset */
#define REFSUP1_DATA_OFFSET                  20U
/* 24 bytes offset */
#define REFSUP2_DATA_OFFSET                  24U
/* 30 bytes offset */
#define PSASOFTEDITION_DATA_OFFSET           30U
/* 16 bytes offset */
#define ACSN_DATA_OFFSET                     16U
/* 25 bytes offset */
#define REFPSA1_DATA_OFFSET                  25U
/* 29 bytes offset */
#define REFPSA2_DATA_OFFSET                  29U
/* Length of serial number */
#define ECU_SERIAL_NUMBER_LENGTH             9U
/* Calibration is not valid */
#define CALIBRATION_INVALID                  0U

/* Read DTC defines */
#define DTC_DOWNLOAD_FAILURE            0x560051UL		/*PSA: 0x900051*/
#define DTC_RDTCBSM                     2U
#define DTC_STATUSMASK                  0x0FU
#define DTC_STATUSAVAMASK 				0X4FU

/*Security access*/
#define INVALID_KEY_ATTEMPTS 			0x03U

/*macros defined to use while calculating the security algorithm*/

#define SIZE_BITS_8 	8u
#define SIZE_BITS_16    16u
#define HIGH_BYTE       3u
#define THIRD_BYTE      2u
#define SECOND_BYTE     1u
#define LOW_BYTE       	0u
#define HIGH_NIBBLE_MASK 0x55u
#define LOW_NIBBLE_MASK 0xAAu

#define ROTATE_BY_3_BITS 3u

#define GET_BYTE(x,n) (((x >> (8u*n))) & 0xFFu)

/*#define LEFT_ROTATE_8_BITS(d,n)			((((U16)d) << n) | (((U16)d) >> (SIZE_BITS_8 - n)))
#define LEFT_ROTATE_16_BITS(d,n)		((d << n) | (d >> (SIZE_BITS_16 - n)))
#define RIGHT_ROTATE_8_BITS(d,n)		((d >> n) | (d << (SIZE_BITS_8 - n)))
#define RIGHT_ROTATE_16_BITS(d,n)		((d >> n) | (d << (SIZE_BITS_16 - n)))

#define SWAP_ADJACENT_BITS_8_BITS(d)	(((d & 0x55u) << 1u)|((d & 0xAAu) >> 1u))*/

/* Changed the coefficient values as per X37 security algorithm*/

#define COEFICIENT_1 0x28u
#define COEFICIENT_2 0x4Du
#define COEFICIENT_3 0x62u
#define COEFICIENT_4 0x81u



/* Typedef for DID
 * Common for 0x31, 0x34, 0x37*/
typedef enum
{
	/* BRP Only */
	MEMBLK_BRP_IX_PSA = 0x80u,
    /* CALIB Only */
    MEMBLK_CALIBRATION_IX_PSA = 0x81u,

    /* APL0 + CALIB */
    MEMBLK_GLOBAL_IX_PSA = 0x82u,

	N_INVALID_MEMBLK = 6,

#if (1 == ZI_READ)
    /* History record */
    MEMBLK_ZI_IX_PSA = 0x83u,
#endif

#if (1 == KEY_APPLI_CHANGE_ENABLED)
    /* KEY_APLLI */
    MEMBLK_KEY_APPLI_IX_PSA = 0x88u
#endif

} MemBlkIxPSA_t;

/* Transfer data related defines */
#define UDS_PRG_SIZE                   8U
/* Maximum data length is 256 bytes. */
#define TRANSFER_BLOCK_SIZE            3072U	//Rami changed from 256 to 3072 bytes
#if (1 == ZI_READ)
#define ZI_DATA_LENGTH                 48u
#define ZI_BLK_COUNTER                 1u
#endif
#if (1 == KEY_APPLI_CHANGE_ENABLED)
#define KEY_APPLI_DATA_LENGTH          2u
#endif
#define TOOL_SIGNATURE                 0xF05Au
#define CRC_ERROR_RESP                 0x0Au
#define WRITING_OK_RESPONSE            0x02u
#define TD_RESPONSE_LENGTH             2u		//Rami changed from 3 to 2 as per the requirement
#if (1 == ZI_READ)
#define ZI_NO_MORE_SPACE               8u
#endif

/* Defines related with CRC calculation */
/* Initialize value required during data transfer sequence */
#define CRC_CCITT_INIT_TRANSFER        0xFFFFUL
#define CRC_CCITT_VALUE                0xF0B8u
#define CRC_32_INIT_VALUE              0xFFFFFFFFUL

/* Define return code of several functions */
/* Function call successful */
#define FLASH_OK                       0x00
/* Function call failed */
#define FLASH_FAILED                   0x01
/* Invalid address */
#define FLASH_INVALID_ADDRESS          0x02
/* Length not aligned */
#define FLASH_INVALID_SIZE             0x03
/* Requested blocks already erased */
#define REQ_BLKS_ERASED                0xAA

/* ReadDataByIdentifier defines */
#define RDBI_REQ_LENGTH                    3U

/* ReadDataByIdentifier define */
#define DID_PROCESSOR_TYPE                         0xF1FAU
#define PROCESSOR_TYPE_SIZE                        1U
#define DID_ACTIVE_DIAG_SESSION                    0xF186U
#define DID_ACTIVE_DIAG_SESSION_SIZE               1U
#define DID_AUTHEN_ZONE                            0xF080U
#define DID_AUTHEN_ZONE_SIZE                       22U
#define DID_ECU_PART_NUMBER_SIZE				   14U
#define DID_ECU_SUPPLIER_NUMBER_SIZE			   6U
#define DID_ECU_RADAR_TYPE_SIZE			   		   1U
#define DID_ECU_HARDWARE_VERSION_SIZE			   2U
#define DID_ECU_SOFTWARE_VERSION_SIZE			   2U
#define DID_ECU_CALIBRATION_SOFTWARE_VERSION_SIZE  2U
#define DID_PROGRAM_DATE_SIZE 					   7U
#define DID_PROGRAM_DATE_RESP_SIZE 				   4U
#define DID_FINGERPRINT_DATA_SIZE 				   11U
#define DID_FINGERPRINT_RESP_SIZE 			   	   4U
#define DID_BOOTLOADER_VER						   0xF180
#define DID_PROGRAMM_DATE						   0xFD63
#define DID_FINGERPRINT_DATA					   0xF184
#define DID_BOOTLOADER_VER_REQ_SIZE 				3U
#define DID_BOOTLOADER_VER_RSP_SIZE 				2U

#if (1 == ZI_READ)
#define DID_ZI_READ                                0xF0FEU
#endif
#define DID_SERIAL_NUM_DATA_IDENT_LEN              0x0D01U
#define DID_SERIAL_NUM_DATA_IDENT                  0xF18CU
#define DID_ECU_MANUFACTURING_DATE                 0xF18BU
#define DID_ECU_PART_NUMBER						   0xF187U
#define DID_ECU_SUPPLIER_NUMBER					   0xF18AU
#define DID_ECU_RADAR_TYPE					   	   0xFD61U
#define DID_ECU_HARDWARE_VERSION				   0xF179U
#define DID_ECU_SOFTWARE_VERSION				   0xF189U
#define DID_ECU_CALIBRATION_SOFTWARE_VERSION	   0xF19CU


#define FIRST_DAY_OF_MONTH                         1U
#define LAST_DAY_OF_MONTH                          0x31U		//changed rami from 31U to 0x31U
#define JANUARY                                    1U
#define DECEMBER                                   12U
#define DAY_idx                                    3U
#define MONTH_idx                                  2U
#define YEAR_idx                                   1U
//#define FIRST_DAY_OF_MONTH                         1U
//#define LAST_DAY_OF_MONTH                          31U
/* Length of serial number */
#define ECU_SERIAL_NUMBER_LENGTH                   9U
/* Length of manufacturing date */
#define ECU_MANUFACTURING_DATE_LENGTH              3U

#if 0 /* not used */
/* DID0x2101 defines */
/* Allow for Xtal tolerance */
#define MOD_FR_24150        24.153F
#define MOD_FR_24075        24.078F
/* Frequently read tolerance of +- 1MHz */
#define MOD_FR_TOL          0.001F
#endif

/* Values for required data for RDBI. Here are components of response for Authorization Zone request */
#define TRW_CODE_FNR_1                     0x00U
#define TRW_CODE_FNR_2                     0x0FU
/* to be specified, copy from EB EQA10A01 */
#define PSA_NBPARAMFLT                     0x01U
#define CAN_DIAG_RESP_LENGTH			   7U
#define DIAG_RESP_PADDING_BYTE			   0x00U



/* Defines *******************************************************************/
#define UDS_Conv3BytesToU32(addbyte1, addbyte2, addbyte3)  \
        (((U32)addbyte1 << 16) | ((U32)addbyte2 << 8) | ((U32)addbyte3))

#define UDS_CRC32Get(a,b)    (((U32)a[b] << 24) + ((U32)a[b + 1] << 16) + ((U32)a[b + 2] << 8) + ((U32)a[b + 3]))

#define LOGICAL_ADDR_BLK_IX_MASK 0x01FFFFFFUL	
#define LOGICAL_ADDR_FLS_BLK_IX_MASK 0xFFFFFFFFUL
#define LOGICAL_ADDR_OFFSET_SIZE 24


typedef enum {

	BRP_MEM_BLK_IX		 = 2,
    APL0_MEM_BLK_IX      = 3,
    NVM0_MEM_BLK_IX      = 4,
	N_INVALID_MEM_BLK	 = 6
} MemBlkIx_t;

/* Service 0x31 response required flag - status of self checking */
typedef enum
{

	CALIBRATION_FAILED = 1,

    APPLICATION_FAILED = 2,

	SUCCESS = 4,			/* Self check successful, all blocks OK */

	CALIBRATION_ONLY_FAILED = 5,	/*To avoid QAC warnings in enumeration*/

	APPLICATION_ONLY_FAILED = 6,	/*To avoid QAC warnings in enumeration*/

	APPLICATION_CALIBRATION_FAILED = 7	/*To avoid QAC warnings in enumeration*/

} SelfCheckStat_t;

/* UDS programming states */
typedef enum
{
    SEQUENCE_NOT_ACTIVE = 0,

    SECURITY_UNLOCKING,

    EXPECT_ROUTINE_ERASE_FLASH_OR_WDBI,

    EXEC_ROUTINE_ERASE_FLASH,

    FIN_ROUTINE_ERASE_FLASH,

    REQUEST_DOWNLOAD,

    TRANSFER_DATA,

#if (1 == KEY_APPLI_CHANGE_ENABLED)
    TRANSFER_KEY_APPLI,
#endif

#if (1 == ZI_READ)
    TRANSFER_ZI,
#endif

    SUCCESSFUL_REPROG_RESET,

	DEVCTRL_SECURITY_UNLOCKING

} UDS_ProgState_t;

/* Structures required for services */
typedef U8 UDS_request_body_type[80];

typedef struct
{
    U8 request_ID;

    U8 subFunc;

    U8 RCIdent_msb;

    U8 RCIdent_lsb;

    U8 RC_Control_Bytes[MAX_RC_CTRL_BYTES];

} UDS_RoutineControl_msg_type;

typedef struct
{
    U8 request_ID;

    U8 subFunction;

} UDS_ResetEcu_msg_type;

typedef struct
{
    U8 request_ID;

    U8 subFunction[MAX_CD_CTRL_BYTES];

} UDS_ClearDTC_msg_type;

typedef struct
{
    U8 request_ID;

    U8 securityAccessMode;

} UDS_SecurityAccess_msg_type;

typedef struct
{
    U8 request_ID;

    U8 securityAccessMode;

    U8 key[4];

} UDS_SecurityAccessSendKey_msg_type;

typedef struct
{
    U8 request_ID_u8;

    U8 subFunction_u8;

    U8 statusMask_u8;

} UDS_ReadDTCByStatusMask_msg_type;

typedef struct
{
    U8 request_ID;

    U8 diagnosticSession;

} UDS_StartDiagnosticSession_msg_type;

typedef struct
{
    U8 request_ID;

    U8 subFunction;

} UDS_TesterPresent_msg_type;

typedef struct
{
    U8 request_ID;

    U8 subFunction;

} UDS_ControlDtc_msg_type;

typedef struct
{
    U8 request_ID;

    U8 subFunction;

    U8 commType;

} UDS_CommControl_msg_type;

typedef struct
{
    U8 request_ID;

    U8 dataFmtId;

    U8 addLenFmtId;

    U8 mem_Add[4];

    U8 mem_size[4];

} UDS_ReqDwnLd_msg_type;

typedef union
{
    struct
	{
        U8 request_ID;

        U8 blockSeqCounter;

      //  U8 mem_Add[3];

      //  U8 mem_size;

        /* 2 bytes added for buffer */
        U8 tranfData[TRANSFER_BLOCK_SIZE + 2];

    } Data;

#if (1 == ZI_READ)
    struct
	{
        U8 ZI_request_ID;

        U8 ZI_blockSeqCounter;

        /* 2 bytes added for buffer */
        U8 ZI_tranfData[ZI_DATA_LENGTH + 2];

    } ZI;
#endif

#if (1 == KEY_APPLI_CHANGE_ENABLED)
    struct
	{
        U8 KEY_APPLI_request_ID;

        U8 KEY_APPLI_blockSeqCounter;

        /* 2 bytes added for buffer */
        U8 KEY_APPLI_tranfData[KEY_APPLI_DATA_LENGTH + 2];

    } KEY_APPLI;
#endif

} UDS_TransData_msg_type;

typedef struct
{
	U8 request_ID;
}UDS_TransExit_msg_type;
typedef struct
{
    U8 request_ID;

    U8 dataIdent_msb;

    U8 dataIdent_lsb;

    U8 Write_Data_Bytes[MAX_ID_DATA_BYTES];

} UDS_WriteDataByIdentifier_msg_type;

typedef struct
{
    U8 request_ID;

    U8 RDBI_DID[2 * MAX_NUM_DID_READ];

} UDS_ReadDataByIdentifier_msg_type;

typedef U8 UDS_response_body_type[30];

typedef struct
{
    U8 UDS_response_ID;

    U8 UDS_DiagnosticMode;

    U8 UDS_P2CAN_server_max_msb;

    U8 UDS_P2CAN_server_max_lsb;

    U8 UDS_P2STARCAN_server_max_msb;

    U8 UDS_P2STARCAN_server_max_lsb;

} UDS_DiagnosticSessionControl_resp_type;

typedef struct
{
    U8 UDS_response_ID;

    U8 DSE_UDS_request_ID;

    U8 UDS_NegativeResponseCode;

} UDS_negative_resp_type;

typedef struct
{
    U8 response_ID;

    U8 resetType;

} UDS_ResetEcu_resp_type;

typedef struct
{
    U8 response_ID;

} UDS_ClearDTC_resp_type;

typedef struct
{
    U8 response_ID;

    U8 securityAccessMode;

    U8 securityAccessSeed[4];

} UDS_SecurityAccess_resp_type;

typedef struct
{
    U8 response_ID;

    U8 securityAccessMode;

} UDS_SecurityAccessSendKey_resp_type;

typedef struct
{
    U8 response_ID;

    U8 subFunc;

    U8 RCIdent_msb;

    U8 RCIdent_lsb;

    U8 RC_Result_bytes[MAX_BYTES_RC_GETRES];

} UDS_RoutineControl_resp_type;

/* For re-programming services */
typedef struct
{
    U8 response_ID;

    U8 lenFmtId;

    U8 maxNumOfBlockLen[4];

} UDS_ReqDwnLd_resp_type;

typedef struct
{
    U8 response_ID;

    U8 blockSeqNumber;

  //  U8 transStatus;	//Commented by Rami as per the requirement

} UDS_TransData_resp_type;

typedef struct
{
    U8 response_ID;

    U8 dataIdent_msb;

    U8 dataIdent_lsb;

} UDS_WriteDataByCommon_resp_type;

typedef struct
{
    U8 response_ID;

    U8 Read_data_buf[MAX_ID_DATA_BYTES];

} UDS_ReadDataByIdentifier_resp_type;

typedef struct
{
    U8 response_ID_u8;

    U8 subFunc_u8;

    U8 statusMask_u8;

    U8 DTC_u8[3];

    U8 statusOfDTC_u8;

} UDS_ReadDTCByStatusMask_resp_type;

/* Global variables */

typedef struct
{
    U16 UDS_data_length;

    union
	{
        UDS_request_body_type                  UDS_request_body;
        UDS_ResetEcu_msg_type                  UDS_ResetEcu_msg;
        UDS_SecurityAccess_msg_type            UDS_SecurityAccess_msg ;
        UDS_SecurityAccessSendKey_msg_type     UDS_SecurityAccessSendKey_msg ;
        UDS_StartDiagnosticSession_msg_type    UDS_StartDiagnosticSession_msg;
        UDS_TesterPresent_msg_type             UDS_TesterPresent_msg;
        UDS_RoutineControl_msg_type            UDS_RoutineControl_msg;
        UDS_WriteDataByIdentifier_msg_type     UDS_WriteDataByIdentifier_msg;
        UDS_ReadDataByIdentifier_msg_type      UDS_ReadDataByIdent_msg;
        UDS_ReqDwnLd_msg_type                  UDS_ReqDwnLd_msg;
        UDS_TransData_msg_type                 UDS_TransData_msg;
        UDS_TransExit_msg_type                 UDS_TransExit_msg;
        UDS_ReadDTCByStatusMask_msg_type       UDS_ReadDTCByStatusMask_msg;
        UDS_ClearDTC_msg_type                  UDS_ClearDTC_msg;
        UDS_ControlDtc_msg_type                UDS_ControlDtc_msg;
        UDS_CommControl_msg_type			   UDS_CommControl_msg;
    } UDS_data;

} UDS_data_in_type;

typedef struct
{
    U16 UDS_data_length;

    union
	{
        UDS_response_body_type                       UDS_response_body;
        UDS_negative_resp_type                       UDS_NegativeResponse;
        UDS_ResetEcu_resp_type                       UDS_ResetEcu_resp;
        UDS_SecurityAccess_resp_type                 UDS_SecurityAccess_resp;
        UDS_SecurityAccessSendKey_resp_type          UDS_SecurityAccessSendKey_resp;
        UDS_DiagnosticSessionControl_resp_type       UDS_DiagnosticSessionControl_resp;
        UDS_RoutineControl_resp_type                 UDS_RoutineControl_resp;
        UDS_ReqDwnLd_resp_type                       UDS_ReqDwnLd_resp;
        UDS_TransData_resp_type                      UDS_TransData_resp;
        UDS_WriteDataByCommon_resp_type              UDS_WriteDataByCommon_resp;
        UDS_ReadDataByIdentifier_resp_type           UDS_ReadDataByIdent_resp;
        UDS_ReadDTCByStatusMask_resp_type            UDS_ReadDTCByStatusMask_resp;
        UDS_ClearDTC_resp_type                  	 UDS_ClearDTC_resp;
    } UDS_data;

} UDS_data_out_type;

typedef struct
{
    /* State of SecurityAccess - Service */
    U8 securityFlags :2;

    /* Valid flag of application */
    U8 invalid_App   :1;

    U8 DevCtrlsecurityFlags     :2;

    U8 dummy         :3;

} tDiagState;

/*************************************************************/
/*      DEFINITIONS LOCAL TO THIS SUBSYSTEM                  */
/*************************************************************/
/* Function prototypes */
void UDS_DiagInit(void);
static U8 UDS_DiagDataIndication(void);
void UDS_DiagServiceHandler(void);
void UDS_DiagContinueProgramming(void);
static U16 Calculate_CRC16CCIT_HW(const U8 *data, U32 len, U16 CRC16InitValue);
static U32 Calculate_CRC32CCIT_HW(const U8 *data, U32 len, U32 CRC32InitValue);
void UDS_Send_Msg_Complete(void);
static void ConvertNumToAscii(U32 sourceVar_u32, U8 *dstArray_pu8, U8 noOfDigits_u8);
/*        static U8 UDS_ReadByte(U32 address); */

static void send_negative_response(U8 responseCode_u8);
static void reset_session_parameters(void);
static void copy_data(const U8 *Source, U8 *Dest, U8 Length);
static S16 securityCalculateEncryptionKey(S16 swE1, S16 swE2);
static U32 securityCalcKey(U32 seed, U16 appliKey);
static U32 securitySeedGeneration(U16 timebase_u16);
static void evaluate_key(U8 *hash);
static U8 finish_programming_sequence(void);
static U8 UDS_FlashWrite(U32 writeAddress, U8* writeBuffer, U32 writeLength);
static void FLASH_WriteWord(U32 uAddr, U32 bData);
#if (1 == ZI_READ)
static BOOLEAN GetEmptyHistoryZoneIdx(U16 *emptyHistoryZoneIdx_pu16);
#endif
static U8 RDBI_identSys(U8 *outputData_pu8);
#if (1 == ZI_READ)
static U8 RDBI_readZI(U8 *outputData_pu8);
#endif
static U8 RDBI_ECU_Serial_Number_Length(U8 *outputData_pu8);
static U8 RDBI_ECU_Serial_Number(U8 *outputData_pu8);
static U8 RDBI_ECU_Manufacturing_Date(U8 *outputData_pu8);
static void reset_ecu_id(void);
static U32 securityCalcKeyAlgo(U32 CurrSeed_u32);
static U8 Reverse(U8 Seed);
static U16 LEFT_ROTATE_16_BITS_fn(U16 seed,U8 position );
static uint32_t GetNBytes(uint8_t const* start, uint8_t n);
static U8 SWAP_ADJACENT_BITS_8_BITS_fn(U8 seed);
static U8 RIGHT_ROTATE_8_BITS_fn(U8 seed,U8 position );
static void FlsUpdate_Previous_Program_Counter(void);
static BOOLEAN GetEmptyHistoryZoneIdx_FingerPrint(U8 *emptyHistoryZoneIdx_pu8);
static BOOLEAN GetEmptyHistoryZoneIdx_ProgrammingDate(U8 *emptyHistoryZoneIdx_pu8);
static U8 ConvertHexToBCD(U8 source_hex_var);


/* Prototypes of the service handlers */
static void process_SecurityAccess(void);
static void process_diagnostic_session_control(void);
static void process_tester_present(void);
static void routine_control(void);
static void read_data_by_identifier(void);
static void write_data_by_identifier(void);
static void UDS_RequestDownload(void);
static void UDS_TransferData(void);
static void UDS_TransferExit(void);
static void UDS_read_dtc_information(void);
static void control_dtc_setting(void);
static void communication_control_msg(void);
static void clear_diagnostic_info(void);

/* Global Variables */
extern UDS_data_in_type UDS_data_in;
extern UDS_data_out_type UDS_data_out;
extern U8 CurrentDiagnosticSession_u8;
extern MemBlkIx_t memBlkIx;
#endif

/*************************************************************/
/*      DEFINITIONS EXPORTED FROM THIS SUBSYSTEM             */
/*************************************************************/

extern BOOLEAN UDS_Send_Msg_Complete_bo;


/* Functions */
extern void UDS_DiagServiceHandler(void);
extern void UDS_progSessionStart(void);
extern void UDS_DiagInit(void);
extern void UDS_DiagContinueProgramming(void);
extern void UDS_Send_Msg_Complete(void);

#endif

