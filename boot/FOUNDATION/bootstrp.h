/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: bootstrp.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:12CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

#ifndef BOOTSTRP_H_
#define BOOTSTRP_H_

#include "types.h"
#include "ssd_types.h"
#include "dio.h"


#define SYS_LOAD_STATUS_BRP_VALID           0xFFFFFFFFFFFF0000ULL
#define SYS_LOAD_STATUS_MAIN_APP_VALID      0xFFFFFFFF00000000ULL   /* PSA ETAT_UCE equal 0xF0 */
#define SYS_LOAD_STATUS_CALIB_CLEAN         0xFFFFFFFFFFFFFFFFULL   /* PSA ETAT_UCE equal 0x00 */	//Rami changed from 0x0000000000000000ULL to 0xFFFFFFFFFFFFFFFFULL, then able to write the valid app flag into __load_status


#define IO_READ_BOOT_PIN()  Dio_ReadChannel((Dio_ChannelType)DioConf_DioChannel_MICROBOOT)
#define IO_READ_CAN_0_RX()  Dio_ReadChannel((Dio_ChannelType)DioConf_DioChannel_CAN0RX)
#define IO_READ_CAN_1_RX()  Dio_ReadChannel((Dio_ChannelType)DioConf_DioChannel_CAN1RX)

#define IO_LOW              0
#define IO_HIGH             1

#define V1V2_MIN            1525
#define V1V2_MAX            1920
#define V3V3_MIN            3270
#define V3V3_MAX            3700
#define VBAT_BOOT           540

#define Reprog_Info         __SHARED_INFO_START

/* Programme value arguments for Bstrp_LoadProgram() and Bstrp_CalcChecksum () */
#define PROG_BRP_CODE       1
#define PROG_APPLICATION    2

typedef enum
{
    SYS_DOWNLOAD_REASON_UNKNOWN,
    SYS_REPROG_REQUEST_CCP ,
    SYS_REPROG_REQUEST_UDS,
    SYS_BOOT_PIN_ACTIVE,
    SYS_NO_VALID_APP,
    SYS_APP_CHECKSUM_FAILURE
} SYS_DLD_REASON_TYPE;


typedef enum
{
    REPROG_REQUEST_INIT_VALUE = 0x5A,
    REPROG_REQUEST_CCP = 0xAA,
    REPROG_REQUEST_UDS = 0x55

} REPROG_REQUEST_STATUS_TYPE;

typedef struct
{
    U32 ccp_erase_address;
    U32 ccp_erase_size;
    U8  ccp_ctr;
    U8  reprog_req_status;

}  __attribute__ ((packed)) T_REPROG_INFO_TYPE;


void    Bstrp_Bootstrap(void) ;
void    Bstrp_InitReprogInfo(void) ;
U32     Bstrp_CalcChecksum(U8 programme);
void    Bstrp_ECC_APV_LS_AreaCheck(void);

extern U8  System_Dld_Reason;
extern U8  Suppres_Ctr_Bit;
extern T_REPROG_INFO_TYPE  __SHARED_INFO_START;


/* Extern variables defined in the linker file*/
void   __APPS_STARTUP_ADDR(void);
void   __BRP_STARTUP_ADDR(void);

extern U64 __LOAD_STATUS[];

extern U32 __START_BRP_CODE[];
extern U32 __END_BRP_CODE[];
extern U32 __BRP_CODE_SIGN_ADDR[];
extern U32 __START_APP_CODE[];
extern U32 __END_APP_CODE[];
extern U32 __ECU_PROG_DATE[];
extern U32 __ECU_PROG_COUNTER[];
extern U32 __TENTAVIOL[];

#ifndef POLYSPACE
extern U32 __APP_CRC[];
#else
/* Polyspace thrown IDP error at line "if(  Bstrp_CalcChecksum(PROG_APPLICATION) == ~(*((volatile U32 *) ((U8 *) __APP_CRC - 2))))" */
/* in the files  ‘bootstrap.c and uds_prog.c’                                                                                       */
/* As polyspace will not read the linker file and also the linker variable is not defined in the Source code  and to facilitate     */
/* polyspace verification below changes were done.                                                                                  */
#define __APP_CRC (*((unsigned int *) 0x011FFFFE))
#endif
extern U32 __APV_FLASH_SECTOR_CRC_ADDR;

extern U32 __APV_FLASH_DATA_START_ADDR[];
extern U32 __APV_FLASH_SECTOR_STATUS_ADDR[];
extern U32 __APV_FLASH_CONTENT_SIZE_ADDR;

extern U32 __APV_FLASH_CONTROL_DATA_SIZE;
#define APV_FLASH_CONTROL_DATA_SIZE ((U32)&__APV_FLASH_CONTROL_DATA_SIZE)

#endif
