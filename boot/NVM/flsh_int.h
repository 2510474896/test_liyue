/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/NVM/project.pj $
        $RCSfile: flsh_int.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:31CST $

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
                                    FILE INFO
Purpose:
    Global interfaces from DIAG Subsystem.

Design Document:


Notes:


******************************************************************************/
#ifndef FLS_INT_H_
#define FLS_INT_H_
/******************************************************************************
*
*   INCLUDE FILES
*
******************************************************************************/
#include    "ssd_types.h"

/************************************************************************
*   MPC-dependent configuration
************************************************************************/
#define C55_REG_BASE                    0xFFFE0000UL
#define FLASH_BASEADDR                  C55_REG_BASE
#define MAIN_ARRAY_BASE                 0x00800000UL
#define UTEST_ARRAY_BASE                0x00400000UL
#define UTEST_ARRAY_SIZE                0x00004000UL

#define C55_PROGRAMMABLE_SIZE           0x80U

#define BUFFER_SIZE_BYTE                0x1000U

/* Lock State */
#define LOCK_ALL_BLOCKS                 0xFFFFFFFFUL
#define UNLOCK_ALL_BLOCKS               0x00000000UL

#define NUM_LOW_BLOCK                          3
#define NUM_MID_BLOCK                          2
#define NUM_HIGH_BLOCK                         6
#define NUM_256K_BLOCK                         8



/* START - CHECK THESE */


#define FLASH_LINE_SIZE                     8U    /* Number of bytes that must be programmed in flash together (multiple of 8) */
#define PROG_TOOL_CHUNK_SIZE                6U   /* The max number of bytes received from the programming tool at a time */
#define FLS_PROG_BUFF_SIZE                  (((FLASH_LINE_SIZE) + (PROG_TOOL_CHUNK_SIZE)) - (FLASH_LINE_SIZE % PROG_TOOL_CHUNK_SIZE))


/* Mask for boot blocks in the high address space */
#define FLS_BOOT_BLOCK_MASK                 0x00000003UL
#define FLS_MAX_SECTORS                     20U


/* Status values */
#define FLS_FAIL                            0U
#define FLS_OK                              1U
#define FLS_INVALID                         2U

/*Parameters for flash erase function*/
#define FLS_C55_FAIL        0
#define FLS_C55_PENDING     1
#define FLS_C55_DONE        2
#define START_ERASE         0
#define ERASE_CONTINUE      1
/* ERASE_DELAY is a time between erase suspend resume and the next erase suspend request. *
 * Minimum is 10ms, as it is written in the documentation. 150k means 15 ms.              */
#define ERASE_DELAY         150000UL


/* END - CHECK THESE */



/* NVM access status values */
#define NVM_READ_PASS                        1U    /* Properly read block of NVM          */
#define NVM_READ_FAIL                        0U    /* Not properly read block of NVM      */


/************************************************************************
*   Abstraction of SSD functions
************************************************************************/

extern const unsigned int FlashInit_C[];
extern const unsigned int FlashErase_C[];
extern const unsigned int FlashEraseAlternate_C[];
extern const unsigned int BlankCheck_C[];
extern const unsigned int FlashProgram_C[];
extern const unsigned int ProgramVerify_C[];
extern const unsigned int FlashCheckStatus_C[];
extern const unsigned int GetLock_C[];
extern const unsigned int SetLock_C[];
extern const unsigned int CheckSum_C[];
extern const unsigned int FlashSuspend_C[];
extern const unsigned int FlashResume_C[];
extern const unsigned int UserMarginReadCheck_C[];
extern const unsigned int FlashArrayIntegrityCheck_C[];
extern const unsigned int FlashArrayIntegrityResume_C[];
extern const unsigned int FlashArrayIntegritySuspend_C[];
extern const unsigned int OverPgmProtGetStatus_C[];
extern const unsigned int FlashAbort_C[];


/******************************************************************************
*
*   FUNCTION DECLARATIONS
*
******************************************************************************/
void Send_hardware_fault(int c);            /* Fault routine in start-up code */

/* Function prototypes */
void          FlsAppInit      (void) ;
UINT8         FlsEraseFlash   (UINT32 target, UINT32 length);
extern UINT8  FlsGet_From_Nvm    (UINT16 block_number_u16, UINT8 offset_u8, UINT8 **nvm_read_buf);
UINT8         FlsProgramFlash(UINT8 *  program_data, UINT8*  target, UINT32 length );

extern UINT8  Fls_C55EraseBlk(UINT8 block);
void          FlsMonitorDownloadComplete(void);
extern UINT8  FlsProgramLoadStatus(UINT64 Load_Status);
extern UINT8 FlsUpdateASDStat(U32 antiscandelaystat);
extern UINT8 FlsEraseLoadStatusSector(void);
U32           MpcDsi_Handler(U32 val_mcsrr0, U32 val_mcar, U32 val_mcsr);

/******************************************************************************
*
*   VARIABLE DECLARATIONS
*
******************************************************************************/

extern BOOLEAN             Fls_Programming_Complete;

/* Extern variables defined in the linker file*/
extern UINT32 __FLASH_API_RAM_BASE[];
extern UINT32 __FLS_DRV_ST[];
extern UINT32 __FLS_DRV_SIZE;
extern U32 __CALIB_FLASH_START;
extern U32 __CALIB_FLASH_END;
extern UINT32 __SOFT_FLASH_START;
extern UINT32 __SOFT_FLASH_END;
#if 0
extern UINT32 __HISTORIC_FIELD;
extern UINT32 __HISTORIC_FIELD_END;
#endif
#ifndef POLYSPACE
extern UINT32 __EEPROM3_SECTOR1_ADDR;
extern UINT32 __EEPROM3_SECTOR2_ADDR;
#else
/* Polyspace has thrown IDP error at line "ClusterStartAddress = *(EmulEepromAdr_pu32 + 1);" in the fill*/
/* where EmulEepromAdr_pu32 is pointing to __EEPROM3_SECTOR1_ADDR or __EEPROM3_SECTOR2_ADDR                          */
/* As polyspace will not read the linker file and also the linker variable is not defined in the Source code  and    */
/* to facilitate polyspace verification below changes were done.                                                     */
#define __EEPROM3_SECTOR1_ADDR (*(unsigned long *) 0x00FE0000)
#define __EEPROM3_SECTOR2_ADDR (*(unsigned long *) 0x00FF0000)
#endif

/******************************************************************************
*
*   INLINE CODE AND/OR FUNCTION-LIKE MACROS
*
******************************************************************************/
/*****************************************************************************
                              FUNCTION INFO
NAME:


DESCRIPTION:


*******************************************************************************/

#endif /* FLS_INT_H_ */
