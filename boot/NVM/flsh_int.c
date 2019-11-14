/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/NVM/project.pj $
        $RCSfile: flsh_int.c $
        $Revision: 1.2 $
        $Date: 2019/08/21 18:34:59CST $

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
/* DEVIATION:     0303
   DESCRIPTION:   Cast between a pointer to volatile object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0303 EOF */

/*  DEVIATION:     0305
    DESCRIPTION:   Cast between a pointer to function and an integral type.
    JUSTIFICATION: MISRA doesn't allow to cast from function to pointer (volatile) and
                   vice versa. It is convenient to use pointers to functions.
*/
/* PRQA S 0305 EOF */

/* DEVIATION:     0306
   DESCRIPTION:   Cast between a pointer to object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0306 EOF */

/*
    DEVIATION:     0277
    DESCRIPTION:   An integer constant expression with negative value is being converted to an unsigned type.
    JUSTIFICATION: Some defines are sometimes negated in order to reverse bits.
 */
/* PRQA S 0277 EOF */

/*  DEVIATION:     0488
    DESCRIPTION:   Performing pointer arithmetic.
    JUSTIFICATION: This method is used in all code of bootloader to change place indicated by pointer.
*/
/* PRQA S 0488 EOF */

/*  DEVIATION:     2213
    DESCRIPTION:   Matching braces appear on the same line - proper indentation would be preferred.
    JUSTIFICATION: The braces are not indented correctly, but if every brace were to be on a new
    line the data would not be very readable
*/
/* PRQA S 2213 EOF */

/*  DEVIATION:     3138
    DESCRIPTION:   Null statement is located close to other code or comments.
    JUSTIFICATION: In this file there are located some defines which are
                   replaced by ASM commands.
*/
/* PRQA S 3138 EOF */

/*  DEVIATION:     4130
    DESCRIPTION:   Bitwise operations on signed data will give implementation defined results.
    JUSTIFICATION: It can not be avoided as it is used to access memory mapped registers.
*/
/* PRQA S 4130 EOF */

/*  DEVIATION:     3673
    DESCRIPTION:   The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'.
    JUSTIFICATION: Making this argument a const caused further instances of warning 0311 "Dangerous pointer cast results in loss of const qualification."
    Since this is legacy code we have decided to suppress this warning.*/
/* PRQA S 3673 EOF */

/*  DEVIATION:     3415
    DESCRIPTION:   The right hand operand of '&&' or '||' has side effects.
    JUSTIFICATION: It works well and meets assumption. It is proven before side effect.
*/
/* PRQA S 3415 EOF */

/*  DEVIATION:     0750
    DESCRIPTION:   A union type specifier has been defined.
    JUSTIFICATION: QAC doesn't allow to create union. Some standards advocate that unions be avoided.
*/
/* PRQA S 0750 EOF */

/*  DEVIATION:     0759
    DESCRIPTION:   A union type specifier has been defined.
    JUSTIFICATION: QAC doesn't allow to create union. Some standards advocate that unions be avoided.
*/
/* PRQA S 0759 EOF */

/*  DEVIATION:     2006
    DESCRIPTION:   Function has more than one 'return' path.
    JUSTIFICATION: In some functions we need to return a result, depending on the condition.
                   It is one of the way to reach functionality.
*/
/* PRQA S 2006 EOF */

/* DEVIATION:     0491
   DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
   JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
*/
/* PRQA S 0491 EOF */

/* DEVIATION:     0492
   DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
   JUSTIFICATION: This is the way to access memory avoiding pointer arithmetic.
*/
/* PRQA S 0492 EOF */
/***************************************************************************/


/*****************************************************************************

                                   FILE INFO
Purpose:
    This file provides the interface functions to the flash
    low level drivers.These interface functions can be used
    by the CCP Application layer.



Function List:

    FlsAppInit
    FlsEraseFlash
    FlsProgramFlash

    FlsErrorTrap
    FlsCopyRoutines
    FlsFillBuffer
    FlsLockBlock
    FlsGetFlashBlock
    FlsIsBlockErasable
    FlsIsBlockProgrammable
    FlsSetLocks
    FlsSetBlkProtection
    FlsProgramLoadStatus
    FlsProgramBuffer
    FlsEraseLoadStatusSector
    FlsEraseSector
    FlsIsLocationProgrammable



Design Document:
    41516035_016_1_Leopard_Boot_Program_Structure.doc

Notes:

CANape seems to conduct a programming session by buffering the .mot file in RAM and
then proceeding to erase and programme the required sectors in order.  If an error
occurs and retry is pressed CANape erases the affected sector and starts programming
it again from the start.  CANape uses a combination of CCP PROG6 and PROG commands
to completely programme each sector.  Before erasing or programming the sector CANape
uses a set MTA command to move the data pointer.

In practice this means that whenever a sector is erased there will be no outstanding
unprogrammed locations since each sector contains an exact number of flash lines and
CANape always programmes exactly one sector.

It is possible when programming large blocks of 0xff locations to skip by setting the
MTA pointer.  If this is done in the middle of a flash line it may leave unprogrammed
locations which must be programmed before moving to the new address.

Programming strategy:

1)  Always erase the load status before erasing any other sector to prevent a valid
    load status with erased sectors.  Load status will only be erased if it is not
    already erased.

2)  The load status can only ever be programmed by the CAN downloader at the end of
    the session if the image is valid.  If CANape tries to programme the load status
    area with anything other than 0xffffffffffffffff it causes a CCP error.

3)  Record the MTA of any buffered data.  If the next programming request is at a
    different address, programme the previous data before moving to the new address.

4)  Since CANape will always programme to the end of a flash line before erasing
    the next sector the erase routine can be used to clear the programme buffer.
    Any unprogrammed bytes should be programmed before clearing the buffer.
    This should make the buffering more robust.

5)  Since CANape erases and programmes the sectors in order, but only those that are
    used, it is possible for programmed sectors above the last application sector
    to remain unerased.  This would lead to an incorrect application checksum.  To
    avoid this all of the application sectors are erased whenever the first application
    sector is erased.  Other application sectors are treated normally.  Thus whenever
    an application is loaded the whole application space is clear and so the
    checksum is computed correctly.  Since a blank-check is performed before erasing
    any sector, no extra erase operations are actually performed.
    No application can ever be loaded without using the first sector as the boot
    must jump to a vector in this sector to start the application.

******************************************************************************/
/*****************************************************************************
*
*   INCLUDE FILES
*
******************************************************************************/

#include "types.h"
#include "Mcu_Reg_eSys_FLASHC.h"
#include "flsh_int.h"
#include "ssd_c55fl.h"
#include "MPC5744P.h"

#include "Mcu.h"
#include "Mcu_dch.h"
#include "bootstrp.h"

#include  <string.h>
#include "can.h"
#include "ccppar.h"
#include "ccp.h"
#include "dio.h"
#include "fccu.h"
#include "memu.h"
#include "uds_prog.h"


#define FLSH_LOAD_STATUS_LINE_START_ADDR    ((  (((UINT64)&__LOAD_STATUS)+3U) /  FLASH_LINE_SIZE) * FLASH_LINE_SIZE)
#define FLSH_LOAD_PROGRAM_DATE_START_ADDR      ((  (((UINT64)&__ECU_PROG_DATE)+3U) /  FLASH_LINE_SIZE) * FLASH_LINE_SIZE)
#define FLSH_LOAD_ANTISCANNING_DELAY_START_ADDR      ((  (((UINT64)&__TENTAVIOL)+3U) /  FLASH_LINE_SIZE) * FLASH_LINE_SIZE)
#define FLSH_LOAD_PROGRAM_COUNTER_START_ADDR      ((  (((UINT64)&__ECU_PROG_COUNTER)+3U) /  FLASH_LINE_SIZE) * FLASH_LINE_SIZE)
#define FLASH_LINE_BLANK 0xFFFFFFFFFFFFFFFFULL
#define LOAD_STATUS_LSB_MASK 0x00000000FFFFFFFFULL

/* Address of the INFRACT_ATT variable in calibration/application memory area */
#define PROG_INFRACT_ATT_ADDRESS             0x00FDFFF0UL
/* Reserve space in memory for the INFRACT_ATT information */
#define m_eInfractAtt (U32)(*((U32*)(PROG_INFRACT_ATT_ADDRESS)))

#define ERASED_FLASH_VALUE (U32)0xFFFFFFFFU
#define ERASED_FLASH_XOR_LSB_BYTE(value) (U32)(ERASED_FLASH_VALUE ^ (U8)~(value))

#define PROG_INFRACT_ATT                ERASED_FLASH_XOR_LSB_BYTE(0x00U)

/*****************************************************************************
*
*   PRIVATE FUNCTION DECLARATIONS
*
******************************************************************************/
static void     FlsErrorTrap(UINT32 return_code);
static void     FlsCopyRoutines(void);
static void     FlsFillBuffer(UINT8 *src , UINT32 size_bytes, UINT8 fill_value);
static void     DisablePrefetchingPiplining(void);
static void     EnablePrefetchingPiplining(void);
static UINT32   FlsLockBlock(UINT8 blk_lock_indicator, UINT32 inp_blk_lock_mask);
static BOOL     FlsGetFlashBlock(UINT32 addr, UINT8 *index);
static BOOL     FlsIsBlockErasable(UINT32 addr, UINT32 len, UINT8 *index);
static BOOL     FlsIsBlockProgrammable(UINT32 addr, UINT8 *index) ;
static UINT32   FlsSetLocks(UINT32 low_addr_space_blk_state, UINT32 mid_addr_space_blk_state, UINT32 high_addr_space_blk_state, UINT32 n256k_1st_addr_space_blk_state, UINT32 n256k_2nd_addr_space_blk_state);
static UINT32   FlsSetBlkProtection(UINT8 block_id, UINT32 *low_addr_space_enable, UINT32 *mid_addr_space_enable, UINT32 *high_addr_space_enable, N256K_BLOCK_SEL *n256KBlockSelect_p);
static UINT8    FlsProgramBuffer(void);
UINT8    FlsEraseLoadStatusSector(void);
static UINT8    FlsEraseSector(UINT8 block);
static BOOL     FlsIsLocationProgrammable(UINT32 addr);
/* static BOOL     FlsGetAddrSpaceAndBitMask(U32 addr, U8* addr_space, U32* bit_mask); */ /* not currently used */

/*  DEVIATION:     3218
    DESCRIPTION:   File scope static, 'Fls_Failed_Reason', is only accessed in one function
    JUSTIFICATION: To fix this warning we could move these declarations to be declared within the functions in which they are used.
                   We don't want to do that because we think that this file has better readability (and easier CCP access) if they are declared here.
*/
/* PRQA S 3218 1*/
static VUINT32  Fls_Failed_Reason;


/*****************************************************************************
*
*   PRIVATE VARIABLE DECLARATIONS
*
******************************************************************************/
BOOLEAN Fls_Programming_Complete = FALSE;
static BOOLEAN ReadingBlocks = FALSE;
static BOOLEAN ReadingCluster = FALSE;
static BOOLEAN ECC_ClustIdRead = FALSE; /* ECC when cluster id read*/
static UINT32 * BlockHeaderAddress_pu32;

/************************ Private Type definitions ***************************/

typedef enum  FLS_ADDRESS_SPACE_TYPE_TAG
{
    FLS_LOW_ADDRESS_SPACE,
    FLS_MID_ADDRESS_SPACE,
    FLS_HIGH_ADDRESS_SPACE,
    FLS_256K_1ST_ADDRESS_SPACE,
    FLS_256K_2ND_ADDRESS_SPACE,
    FLS_NUM_ADDRESS_SPACES

}FLS_ADDRESS_SPACE_TYPE;

typedef struct FLS_INFO_TYPE_TAG
{
    UINT32                  Start_Address;
    UINT32                  Length;
    FLS_ADDRESS_SPACE_TYPE  Address_Space;
    UINT32                  Bit_Mapped_Block_Id;
    BOOL                    CCP_Programmable;
    BOOL                    UDS_Programmable;

}FLS_INFO_TYPE;


typedef union FLS_PROG_DATA_TYPE_TAG
{
    UINT8   byte[ FLS_PROG_BUFF_SIZE ];
    UINT32  word[ FLS_PROG_BUFF_SIZE/sizeof(UINT32) ];

}FLS_PROG_DATA_TYPE ;



/************************ Variable definitions ***************************/

/* Source buffer for program and verify */
static FLS_PROG_DATA_TYPE   Fls_Data_Buffer;
static FLS_PROG_DATA_TYPE   Fls_Load_Status_Sec_Buff;   /* consider keeping this to 8 bytes long */

static UINT32               Flsh_bytes_received;        /* Number of currently buffered bytes for programming */
static UINT32               Prog_buffer_address;        /* Intended programming address for currently buffered bytes, 0xffffffff = invalid */


/* Assign function pointers */
static PFLASHINIT             pFlashInit;
static PFLASHERASE            pFlashErase;
static PBLANKCHECK            pBlankCheck;
static PFLASHPROGRAM          pFlashProgram;
static PPROGRAMVERIFY         pProgramVerify;
static PGETLOCK               pGetLock;
static PSETLOCK               pSetLock;
static PFLASHSUSPEND          pFlashSuspend;
static PFLASHRESUME           pFlashResume;
static PFLSC55ERASESECTOR     pFlsC55EraseSector;
static PFLASHERASESTOP        pFlashEraseStop;
static PFLASHCHECKSTATUS      pFlashCheckStatus;
static PFLASHABORT            pFlashAbort;
static PFLASHPROGRAMANDCHECK  pFlashProgramAndCheck;
static PFLASHERASEANDCHECK    pFlashEraseAndCheck;

static SSD_CONFIG ssdConfig =
{
    C55_REG_BASE,         /* C55 control register base */
    MAIN_ARRAY_BASE,      /* base of main array */
    { 0, 0, 0 },          /* blocks info of low address space */
    { 0, 0, 0 },          /* blocks info of mid address space */
    { 0, 0, 0 },          /* blocks info of high address space */
    0,                    /* number of blocks in 256K address space */
    UTEST_ARRAY_BASE,     /* base of UTEST array */
    TRUE,                 /* interface flag indicate main or alternate interface */
    C55_PROGRAMMABLE_SIZE,/* programmable size */
    FALSE                 /* debug mode selection */
};

#ifndef STATIC_TEST
void static write_r3(register UINT32 value);
#endif /* STATIC_TEST */

static UINT8  __attribute__((section(".fls_driver"))) FlsC55EraseSector(UINT8 block);
static UINT32 __attribute__((section(".fls_driver"))) FlashEraseStop (PSSD_CONFIG pSSDConfig);
static UINT32 __attribute__((section(".fls_driver"))) FlashProgramAndCheck(PSSD_CONFIG pSSDConfig, BOOL factoryPgmFlag, UINT32 dest, UINT32 size, UINT32 source, PCONTEXT_DATA pCtxData);
static UINT32 __attribute__((section(".fls_driver"))) FlashEraseAndCheck(PSSD_CONFIG pSSDConfig, UINT8 eraseOption, UINT32 lowBlockSelect, UINT32 midBlockSelect, UINT32 highBlockSelect, N256K_BLOCK_SEL n256KBlockSelect, PCONTEXT_DATA pCtxData);

/*  DEVIATION:     3218
    DESCRIPTION:   File scope static, 'dummyCtxData', is only accessed in one function
    JUSTIFICATION: To fix this warning we could move these declarations to be declared within the functions in which they are used.
                   We don't want to do that because we think that this file has better readability (and easier CCP access) if they are declared here.
*/
/* PRQA S 3218 1*/
static CONTEXT_DATA dummyCtxData;
static CONTEXT_DATA pgmCtxData;
static CONTEXT_DATA bcCtxData;
static CONTEXT_DATA pvCtxData;

/* Flash Information Table */

static const FLS_INFO_TYPE Fls_Info[] =
{

     /*----------------------------------------------------------------------------------------------------------------------*/
     /* Start_Address   |   Length     |   Address_Space        |   Bit_Mapped_Block_Id  |  CCP           |  UDS             */
     /*                 |              |                        |                        |  Programmable  |  Programmable    */
     /*----------------------------------------------------------------------------------------------------------------------*/
    {   0x00800000,         0x00004000,    FLS_LOW_ADDRESS_SPACE,      0x00000001,          TRUE,            FALSE   },  /* Emulated EEPROM1 - Page 1 */
    {   0x00804000,         0x00004000,    FLS_LOW_ADDRESS_SPACE,      0x00000002,          TRUE,            FALSE   },  /* Emulated EEPROM1 - Page 2 */
    {   0x00F98000,         0x00004000,    FLS_LOW_ADDRESS_SPACE,      0x00000004,          TRUE,            FALSE   },  /* Unused */
    {   0x00F9C000,         0x00004000,    FLS_LOW_ADDRESS_SPACE,      0x00000008,          TRUE,            FALSE   },  /* Unused */

    {   0x00808000,         0x00008000,    FLS_MID_ADDRESS_SPACE,      0x00000001,          TRUE,            FALSE   },  /* Emulated EEPROM2 - Page 1 */
    {   0x00810000,         0x00008000,    FLS_MID_ADDRESS_SPACE,      0x00000002,          TRUE,            FALSE   },  /* Emulated EEPROM2 - Page 2 */

    {   0x00FA0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000001,          FALSE,           FALSE   },  /* BOOT 1 */
    {   0x00FB0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000002,          FALSE,           FALSE   },  /* BOOT 2 */
    {   0x00FC0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000004,          TRUE,            TRUE    },  /* APVs */
    {   0x00FD0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000008,          TRUE,            TRUE    },  /* BRP and Load status */
    {   0x00FE0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000010,          TRUE,            FALSE   },  /* Emulated EEPROM3 - Page 1 */
    {   0x00FF0000,         0x00010000,    FLS_HIGH_ADDRESS_SPACE,     0x00000020,          TRUE,            FALSE   },  /* Emulated EEPROM3 - Page 2 */

    {   0x01000000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000001,          TRUE,            TRUE    },  /* Application sectors */
    {   0x01040000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000002,          TRUE,            TRUE    },
    {   0x01080000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000004,          TRUE,            TRUE    },
    {   0x010C0000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000008,          TRUE,            TRUE    },
    {   0x01100000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000010,          TRUE,            TRUE    },
    {   0x01140000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000020,          TRUE,            TRUE    },
    {   0x01180000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000040,          TRUE,            TRUE    },
    {   0x011C0000,         0x00040000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000080,          TRUE,            TRUE    },
};

#define FLASH_CAL_SECTOR_START          8
#define FLASH_LOAD_STATUS_SECTOR_START  9
#define APP_START                       12
#define SECTORS                         (sizeof(Fls_Info) / sizeof(FLS_INFO_TYPE))


/*****************************************************************************
*
*   CODE
*
******************************************************************************/

/*****************************************************************************/
/* Name:        FlsAppInit                                                   */
/* Description:                                                              */
/*        Initialises the fash data buffer,flash module and locks the        */
/*        shadow row against program/erase operations                        */
/*                                                                           */
/* Input:       - void                                                       */
/* Output:      -                                                            */
/* Return:      -  void                                                      */
/*****************************************************************************/
void FlsAppInit(void)
{
    UINT32 return_code;           /* Return code from each SSD function. */
    UINT32 mcr_value;
    UINT32 blkLockState;
    UINT32 MCRAddress;            /* address of C55MCR register */


    /* Initialize source buffer */
    FlsFillBuffer(Fls_Data_Buffer.byte, FLS_PROG_BUFF_SIZE, 0xFF);
    FlsFillBuffer(Fls_Load_Status_Sec_Buff.byte, FLS_PROG_BUFF_SIZE, 0xFF);

    Flsh_bytes_received = 0;                           /* No bytes waiting for programming */
    Prog_buffer_address = 0xffffffffU;                 /* Address invalid */

    Fls_Programming_Complete = FALSE;

    MCRAddress = C55_REG_BASE + C55_MCR;

    mcr_value = C55_REG_READ(MCRAddress);

    if( (mcr_value & (UINT32)C55_MCR_EER) == (UINT32)C55_MCR_EER) /* is flash ecc error bit set? */
    {
        C55_REG_BIT_SET(MCRAddress, (UINT32)C55_MCR_EER);   /* clear the bit */
    }

    if( (mcr_value & (UINT32)C55_MCR_RWE) == (UINT32)C55_MCR_RWE) /* is flash RWE error bit set? */
    {
        C55_REG_BIT_SET(MCRAddress, (UINT32)C55_MCR_RWE);   /* clear the bit */
    }

    FlsCopyRoutines();    /* Copy the flash drivers into RAM */

    /*========================= Initialize Part =========================*/

    /* set up function pointers in context data */
    pgmCtxData.pReqCompletionFn = pFlashProgram;
    bcCtxData.pReqCompletionFn  = pBlankCheck;
    pvCtxData.pReqCompletionFn  = pProgramVerify;

    return_code = pFlashInit( &ssdConfig );

    if (C55_OK != return_code)
    {
        FlsErrorTrap(return_code);
    }

    /*================ Lock to Protect UTest Address Space ====================*/

    return_code = pGetLock(&ssdConfig, C55_BLOCK_UTEST, &blkLockState);

    if (C55_OK != return_code)
    {
        FlsErrorTrap(return_code);
    }

    if (0U == (blkLockState & 0x00000001UL))
    {
        return_code = pSetLock(&ssdConfig, C55_BLOCK_UTEST, LOCK_ALL_BLOCKS);

        if (C55_OK != return_code)
        {
            FlsErrorTrap(return_code);
        }
    }

    /*===== Lock the blocks containing the boot code (block 0 and 1 in High address space) ======*/

    return_code = FlsLockBlock(C55_BLOCK_HIGH, FLS_BOOT_BLOCK_MASK);

    if(C55_OK != return_code)
    {
        FlsErrorTrap(return_code);
    }
}


/*****************************************************************************/
/* Name:        FlsEraseFlash                                                */
/* Description: Check if target address is valid sector, and can be erased   */
/*              then unlocks the sector and erases it. Also ensures          */
/*              App Status erased 1st time round                             */
/* Input:       - UINT32 sector address, 32 bit length                       */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_INVALID, FLS_FAIL                             */
/*****************************************************************************/
UINT8 FlsEraseFlash(UINT32 target, UINT32 length)
{
    UINT8   i;
    UINT8   stat = FLS_OK;

    target = (target & 0x01FFFFFF);

    /* Erase request. See if there is any data left in the prog buffer */
    if(Flsh_bytes_received > 0U)
    {
        (void)FlsProgramBuffer();                 /* Don't worry about the return status - just carry on */
        Flsh_bytes_received = 0;
    }

    /* Check if address in flash block table, length within sector, and erasable and get index to sector/core table */
    if (FlsIsBlockErasable(target, length, &i) == TRUE)
    {
        /* Address is programmable so allow erase of this sector */

        /* Erase the Load Status Sector if it has not been erased already */
        /* Leave it here, don't include the function in the if statement because the return value has got to bubble up to the caller!! */
        stat = FlsEraseLoadStatusSector();

        if(stat == FLS_OK)
        {
            stat = FlsEraseSector(i);

            /* If this is the first application sector then erase the whole application space */
            if (APP_START == i)
            {
                for (i = APP_START + 1; (i < SECTORS) && (stat == FLS_OK); i++)
                {
                    stat = FlsEraseSector(i);
                }
                /* Erase the APV sector(s) too */
                for (i = FLASH_CAL_SECTOR_START; (i < FLASH_LOAD_STATUS_SECTOR_START) && (stat == FLS_OK); i++)
                {
                    stat = FlsEraseSector(i);
                }
            }
        }
    }
    else
    {
        /*Block not mapped in the physical memory of the CPU*/
        stat = FLS_INVALID;
    }
    return (stat);
}  /* End flash_erase_flash */

/*****************************************************************************/
/* Name:        FlsProgramFlash                                              */
/* Description:                                                              */
/*                                                                           */
/*        Programmes the data in chumks of FLASH_LINE_SIZE bytes and verifies*/
/*        the programmed data.                                               */
/*                                                                           */
/*                                                                           */
/* Input:       -source addr ptr, dest address and length                    */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_INVALID, FLS_FAIL                             */
/*****************************************************************************/

/* 'program_data' and 'target' are constant pointers => pointers themselves can't be modified but what
   they are pointing can be modified  */

UINT8 FlsProgramFlash(UINT8 *program_data, UINT8 *target, UINT32 length )
{
    UINT8  i;
    UINT8  return_status = FLS_OK;
    UINT8 *fls_buffer;
    UINT32 mta;



    mta = (UINT32)target;

    mta = (mta & 0x01FFFFFF);

    if(length == 0U)
    {
        /* End of flash programming. See if there is any data left in the prog buffer */
        if(Flsh_bytes_received > 0U)
        {
            return_status = FlsProgramBuffer();
            Flsh_bytes_received = 0;
        }

        /* End of Programming including the data left in the buffer. */
        /* Check the checksums and decide if there is any valid software to run. */

        /* Check Checksums */
        if(   ( (*(__BRP_CODE_SIGN_ADDR)) == (UINT32)0x7E57C0DE  )
           && (Bstrp_CalcChecksum(PROG_BRP_CODE) == 0U)
          )
        {
            /* Valid test code checksum and signature. Program LS and reset the unit */
            (void)FlsProgramLoadStatus(SYS_LOAD_STATUS_BRP_VALID);
        }
        /*
           DEVIATION:     0310
           DESCRIPTION:   Casting to different object pointer type and Performing pointer arithmetic.
           JUSTIFICATION: In order to get checksum from flash the best option available is pointer arithmetic.
        */
        /* PRQA S 0310 1 */
        else if(Bstrp_CalcChecksum(PROG_APPLICATION) == ~(*((volatile U32 *) ((U8 *) __APP_CRC))))
        {
            /* Valid App Checksum. Program LS and reset the unit */
            (void)FlsProgramLoadStatus(SYS_LOAD_STATUS_MAIN_APP_VALID);

        }
        else
        {
        }

        /* Perform a soft reset anyway */
        Fls_Programming_Complete = TRUE;
    }
    else
    {
        if ((0U != Flsh_bytes_received) && ((mta / FLASH_LINE_SIZE) != (Prog_buffer_address / FLASH_LINE_SIZE)))
        {
            /* Still some unprogrammed bytes in the buffer at the old address */
            return_status = FlsProgramBuffer();

            if (FLS_OK != return_status)
            {
                return (return_status);
            }
        }

        Flsh_bytes_received = mta % FLASH_LINE_SIZE;

        /* This loads the latest CCP data into the buffer */
        fls_buffer = Fls_Data_Buffer.byte;

        for( i=0; i<length; i++ )
        {
            Flsh_bytes_received++;

            if ( Flsh_bytes_received > FLASH_LINE_SIZE )
            {
                fls_buffer[(mta % FLASH_LINE_SIZE) + FLASH_LINE_SIZE] = program_data[i];
            }
            else
            {
                fls_buffer[mta % FLASH_LINE_SIZE] = program_data[i];
                Prog_buffer_address = mta - (mta % FLASH_LINE_SIZE);
            }

            mta++;
        }

        if ( Flsh_bytes_received >= FLASH_LINE_SIZE )
        {
            return_status = FlsProgramBuffer();

            for( i=0; i<(Flsh_bytes_received-FLASH_LINE_SIZE); i++ )
            {
                Fls_Data_Buffer.byte[i] = Fls_Data_Buffer.byte[FLASH_LINE_SIZE + i];
            }

            Flsh_bytes_received -= FLASH_LINE_SIZE;
            Prog_buffer_address = mta - (mta % FLASH_LINE_SIZE);
        }
    }

    return(return_status);
}

static void FlsFillBuffer(UINT8 *src , UINT32 size_bytes, UINT8 fill_value)
{
    UINT32 i;

    for (i = 0; i < size_bytes ; i++)

    {
        /* Set source buffer to all FFs */
        src[i] = fill_value;
    }
}

static UINT32 FlsLockBlock(UINT8 blk_lock_indicator, UINT32 inp_blk_lock_mask)
{
    UINT32  blkLockState;         /* block lock status to be retrieved */
    UINT32  return_code;          /* Return code from each SSD function. */


    return_code = pGetLock(&ssdConfig, blk_lock_indicator, &blkLockState);


    /* if the block to be locked is not already locked and if there are no errors...*/
    if ( ((blkLockState & inp_blk_lock_mask) != inp_blk_lock_mask ) && (C55_OK == return_code))
    {
        return_code = pSetLock(&ssdConfig, blk_lock_indicator, (blkLockState | inp_blk_lock_mask));

    }

    return return_code;
}


/* Error trap function */
static void FlsErrorTrap(UINT32 return_code)
{
    Fls_Failed_Reason = return_code;

    Send_hardware_fault(5);                 /* This never returns */
}

/*****************************************************************************/
/* Name:        flash_copy_routines                                          */
/* Description: Copies the flash routines from ROM into RAM for running      */
/* Input:       -                                                            */
/* Output:      -                                                            */
/* Return:      -                                                            */
/*****************************************************************************/
static void FlsCopyRoutines(void)
{
    /* Copy flash api code from ram to rom. Use labels created in link process. */
    (void)memcpy ((void *)&__FLASH_API_RAM_BASE, (void *)&__FLS_DRV_ST, (UINT32)&__FLS_DRV_SIZE);

    /* Set up function pointers for flash api functions which are now in RAM */
    #ifndef POLYSPACE
    /*
        DEVIATION:     0428
        DESCRIPTION:   Function identifier should probably be followed by ().
        JUSTIFICATION: It shouldn't be followed by ().
    */
    /* PRQA S 0428 15 */
    pFlashInit            =  (PFLASHINIT)            ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashInit_C           - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashErase           =  (PFLASHERASE)           ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashErase_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pBlankCheck           =  (PBLANKCHECK)           ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&BlankCheck_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashProgram         =  (PFLASHPROGRAM)         ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashProgram_C        - (UINT32)&__FLS_DRV_ST) ) ;
    pProgramVerify        =  (PPROGRAMVERIFY)        ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&ProgramVerify_C       - (UINT32)&__FLS_DRV_ST) ) ;
    pGetLock              =  (PGETLOCK)              ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&GetLock_C             - (UINT32)&__FLS_DRV_ST) ) ;
    pSetLock              =  (PSETLOCK)              ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&SetLock_C             - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashSuspend         =  (PFLASHSUSPEND)         ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashSuspend_C        - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashResume          =  (PFLASHRESUME)          ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashResume_C         - (UINT32)&__FLS_DRV_ST) ) ;
    pFlsC55EraseSector    =  (PFLSC55ERASESECTOR)    ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlsC55EraseSector     - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashEraseStop       =  (PFLASHERASESTOP)       ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashEraseStop        - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashCheckStatus     =  (PFLASHCHECKSTATUS)     ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashCheckStatus_C    - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashAbort           =  (PFLASHABORT)           ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashAbort_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashProgramAndCheck =  (PFLASHPROGRAMANDCHECK) ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashProgramAndCheck  - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashEraseAndCheck   =  (PFLASHERASEANDCHECK)   ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashEraseAndCheck    - (UINT32)&__FLS_DRV_ST) ) ;
    #else
    /*The above function pointers are updated through the flash drivers which is not a 'C' code. As polyspace does not recognize the Hexa code,  */
    /* to facilitate polyspace verification used by ssd_c55fl_algo.c file which contains the below functions definitions in C code           */

    pFlashInit            =  &FlashInit;
    pFlashErase           =  &FlashErase;
    pBlankCheck           =  &BlankCheck;
    pFlashProgram         =  &FlashProgram;
    pProgramVerify        =  &ProgramVerify;
    pGetLock              =  &GetLock;
    pSetLock              =  &SetLock;
    pFlashSuspend         =  &FlashSuspend;
    pFlashResume          =  &FlashResume;
    pFlsC55EraseSector    =  &FlsC55EraseSector;
    pFlashEraseStop       =  &FlashEraseStop;
    pFlashCheckStatus     =  &FlashCheckStatus;
    pFlashAbort           =  &FlashAbort;
    pFlashProgramAndCheck =  &FlashProgramAndCheck;
    pFlashEraseAndCheck   =  &FlashEraseAndCheck;

    #endif
}

/*****************************************************************************/
/* Name:        FlsGetFlashBlock                                             */
/* Description: Get index to Flash Desc table from flash address             */
/* Input:       - flash address                                              */
/* Output:      - index to table                                             */
/* Return:      - address found TRUE/FALSE                                   */
/*****************************************************************************/
static BOOL FlsGetFlashBlock(UINT32 addr, UINT8 *index)
{
    UINT8 i;
    BOOL programmable = FALSE;
    BOOL found        = FALSE;

    for (i = 0; (i < FLS_MAX_SECTORS)&&(found == FALSE); i++)
    {
        if (addr < ((UINT32)Fls_Info[i].Start_Address + Fls_Info[i].Length))
        {
            /* Found matching block for address */
            *index = i;
            programmable = TRUE;  /* Don't need this variable ? */
            found = TRUE;
        }
    }
    return programmable;
}

/*****************************************************************************/
/* Name:        FlsIsBlockErasable                                           */
/* Description: Get index to Flash Desc table from flash address if erasable */
/* Input:       - flash address                                              */
/* Output:      - index to table                                             */
/* Return:      - address found and sector erasable                          */
/*****************************************************************************/
static BOOL FlsIsBlockErasable(UINT32 addr, UINT32 len, UINT8 *index)
{
    BOOL ret = FALSE;

    /* Check if address in flash block table and get index to sector/core table */
    if (FlsGetFlashBlock(addr, index) == TRUE)
    {
        /* Check if block programmable and length keeps address range within sector size */
        if ((Fls_Info[*index].CCP_Programmable == TRUE) &&
            (((addr + len) - 1U) < ((UINT32)Fls_Info[*index].Start_Address + (UINT32)Fls_Info[*index].Length)))
        {
            ret = TRUE;
        }
    }

    return(ret);
}

/*****************************************************************************/
/* Name:        FlsIsBlockProgrammable                                       */
/* Description: Get index to Flash Desc table from flash address if          */
/*              programmable. Check if allowed, and erased in this powercycle*/
/* Input:       - flash address                                              */
/* Output:      - index to table                                             */
/* Return:      - address found and sector programmable                      */
/*****************************************************************************/
static BOOL FlsIsBlockProgrammable(UINT32 addr, UINT8 *index)
{
    BOOL ret = FALSE;

    /* Check if address in programmable range and get index to sector/core table */
    if (FlsGetFlashBlock(addr, index) == TRUE)
    {
        ret = TRUE;
    }

    return(ret);
}

/*****************************************************************************/
/* Name:        FlsSetLocks                                                  */
/* Description:                                                              */
/*        Sets locks for the blocks as specified in the bit mapped           */
/*        inputs low_addr_space_blk_state,mid_addr_space_blk_state,          */
/*        high_addr_space_blk_state and _256k_first_addr_space_blk_state     */
/*                                                                           */
/* Input:                                                                    */
/*      low_addr_space_blk_state - bit mapped block state;                   */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      mid_addr_space_blk_state - bit mapped block state;                   */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      high_addr_space_blk_state - bit mapped block state;                  */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      n256k_1st_addr_space_blk_state - bit mapped block state;             */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      n256k_2nd_addr_space_blk_state - bit mapped block state;             */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*                                                                           */
/* Output:      - lock status                                                */
/*****************************************************************************/
static UINT32 FlsSetLocks(UINT32 low_addr_space_blk_state,
                          UINT32 mid_addr_space_blk_state,
                          UINT32 high_addr_space_blk_state,
                          UINT32 n256k_1st_addr_space_blk_state,
                          UINT32 n256k_2nd_addr_space_blk_state)
{
    UINT32 return_code;

    /* Unlock flash blocks */

    /* Set lock bit for the low address space */
    return_code = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_LOW, (UINT32)~low_addr_space_blk_state);

    /* Set lock bit for the middle address space */
    if(C55_OK == return_code)
    {
        return_code = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_MID, (UINT32)~mid_addr_space_blk_state);
    }

    /* Set lock bit for the high address space */
    if(C55_OK == return_code)
    {
        return_code = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_HIGH, (UINT32)~high_addr_space_blk_state);
    }

    /* Set lock bit for the 256k first address space (from block 0 to block 31) */
    if(C55_OK == return_code)
    {
        return_code = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_256K_FIRST, (UINT32)~n256k_1st_addr_space_blk_state);
    }

    /* Set lock bit for the 256k second address space (from block 32 to upper block numbering) */
    if(C55_OK == return_code)
    {
        return_code = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_256K_SECOND, (UINT32)~n256k_2nd_addr_space_blk_state);
    }

    return(return_code);
}

/*****************************************************************************/
/* FUNCTION: FlsSetBlkProtection                                             */
/*                                                                           */
/* PARAMETERS: block id (a number between 0 and FLS_MAX_SECTORS)             */
/*                                                                           */
/* DESCRIPTION:                                                              */
/*         Obtains the bit pattern required to unlock only the               */
/*         required block and to lock all other blocks.                      */
/*                                                                           */
/* RETURNS:                                                                  */
/*    Returns the bit pattern for the low, mid, high and 256k address spaces */
/*    and the status.                                                        */
/*                                                                           */
/*****************************************************************************/
static UINT32 FlsSetBlkProtection(UINT8 block_id,
                                  UINT32 *low_addr_space_enable,
                                  UINT32 *mid_addr_space_enable,
                                  UINT32 *high_addr_space_enable,
                                  N256K_BLOCK_SEL *n256KBlockSelect_p)
{
    UINT8  req_space;
    UINT32 fls_blk_id_mask ;
    UINT32 enable_blocks[ FLS_NUM_ADDRESS_SPACES ];

    UINT32 return_code = 0xFF;

    if(block_id < FLS_MAX_SECTORS )
    {
        /* get the required addres space low, mid, high or 256k */
        req_space       = (UINT8)Fls_Info[ block_id ].Address_Space;
        fls_blk_id_mask =        Fls_Info[ block_id ].Bit_Mapped_Block_Id;

        enable_blocks[ FLS_LOW_ADDRESS_SPACE ]      = 0;
        enable_blocks[ FLS_MID_ADDRESS_SPACE ]      = 0;
        enable_blocks[ FLS_HIGH_ADDRESS_SPACE ]     = 0;
        enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ] = 0;
        enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ] = 0;

        if(req_space < FLS_NUM_ADDRESS_SPACES)
        {
            enable_blocks[ req_space ] = fls_blk_id_mask;
        }

        return_code = FlsSetLocks(enable_blocks[ FLS_LOW_ADDRESS_SPACE ],
                                  enable_blocks[ FLS_MID_ADDRESS_SPACE ],
                                  enable_blocks[ FLS_HIGH_ADDRESS_SPACE ],
                                  enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ],
                                  enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ]);

        *low_addr_space_enable    = enable_blocks[ FLS_LOW_ADDRESS_SPACE ];
        *mid_addr_space_enable    = enable_blocks[ FLS_MID_ADDRESS_SPACE ];
        *high_addr_space_enable   = enable_blocks[ FLS_HIGH_ADDRESS_SPACE ];

        n256KBlockSelect_p->first256KBlockSelect  = enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ];
        n256KBlockSelect_p->second256KBlockSelect = enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ];
    }

    return(return_code);
}

static void DisablePrefetchingPiplining(void)
{
/*   FLASH.BIUCR.APC = 0x7;  */ /* No Address Pipelining */
/*   FLASH.BIUCR.DPFEN = 0;  */ /* Disable data prefetching */
/*   FLASH.BIUCR.IPFEN = 0;  */ /* Disable instruction prefetching */
/*   FLASH.BIUCR.PFLIM = 0;  */
/*   FLASH.BIUCR.BFEN = 0;   */
/*   FLASH.BIUCR.R = 0xFB00; */
}

static void EnablePrefetchingPiplining(void)
{
/*   FLASH.BIUCR.APC = 2;        */ /* Access requests require two hold cycles */
/*   FLASH.BIUCR.DPFEN = 0;      */ /* Disable data prefetching */
/*   FLASH.BIUCR.IPFEN = 3;      */ /* Prefetching may be triggered by any instruction read access */
/*   FLASH.BIUCR.R = 0x00005b3b; */ /* FLash waitstate for 130 MHz */
}

/* DEVIATION:     3219
   DESCRIPTION:   Static function 'FlsGetAddrSpaceAndBitMask()' is not used within this translation unit.
  JUSTIFICATION:  This function is not currently used but it may be used in the future.
*/
/* PRQA S 3219 1 */
/*static BOOL FlsGetAddrSpaceAndBitMask(U32 addr, U8* addr_space, U32* bit_mask)
{
    BOOL ret = FALSE;
    U8   index;

    if((FlsGetFlashBlock(addr, &index)) == TRUE)
    {*/
        /* Get the required address space low, mid, high or 256k */
/*      *addr_space = (UINT8)Fls_Info[ index ].Address_Space;
        *bit_mask   = Fls_Info[ index ].Bit_Mapped_Block_Id;

        if(*addr_space < FLS_NUM_ADDRESS_SPACES)
        {
            ret = TRUE;
        }
    }

    return ret;
}*/


void FlsMonitorDownloadComplete(void)
{
    if(Fls_Programming_Complete == TRUE)
    {
        /* If the ccp message has been sent and the UDS message too */
        if ((FALSE == CCP_GET_SEND_PENDING_STATUS()) && (TRUE == UDS_Send_Msg_Complete_bo))
        {
            /* clear the shared info area as we have completed the flash programming  */
            Bstrp_InitReprogInfo();

            /* Disable interrupts: */

            DisableAllInterrupts();   /* disable ALL interrupts */
            Mcu_Reset_Ints();

            Mcu_PerformReset();
        }
    }
}

/*****************************************************************************/
/* Name:        FlsProgramLoadStatus                                         */
/* Description: Programmes the load status area.                             */
/* Input:       Data to programme                                            */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_FAIL                                          */
/*****************************************************************************/
UINT8 FlsProgramLoadStatus(UINT64 Load_Status)
{
    UINT8  i;
    UINT8  return_status = FLS_OK;

    UINT32 prog_address;

    UINT32 failAddress;          /* save the failed address in flash */

    UINT32 return_code;
    UINT32 opResult;
    UINT32 low_address_space_enable = 0;
    UINT32 mid_address_space_enable = 0;
    UINT32 high_address_space_enable = 0;
    N256K_BLOCK_SEL n256KBlockSelect;

    UINT32 failData;             /* save the failed data in flash */
    UINT32 failSource;           /* save the failed data in source buffer */

    /* Program the load status */

    /*
        DEVIATION:     0501
        DESCRIPTION:   Right operand of shift operator is too large - this is undefined.
        JUSTIFICATION: In bootloader there is need of using 64bit variables. MISRA accepts variables which have max 32bits.
     */
    /* PRQA S 0501 1 */
    Fls_Load_Status_Sec_Buff.word[0] =(UINT32)(Load_Status >> 32);
    Fls_Load_Status_Sec_Buff.word[1] =(UINT32)(Load_Status & (LOAD_STATUS_LSB_MASK));

    prog_address = FLSH_LOAD_STATUS_LINE_START_ADDR;

    if (FlsIsBlockProgrammable(prog_address, &i) == TRUE)
    {
        return_code = FlsSetBlkProtection(i, &low_address_space_enable,
                                             &mid_address_space_enable,
                                             &high_address_space_enable,
                                             &n256KBlockSelect);

        if(C55_OK == return_code)
        {
            DisableAllInterrupts();
            DisablePrefetchingPiplining();

            opResult = pFlashProgramAndCheck(&ssdConfig,
                                             FALSE,
                                             prog_address,
                                             FLASH_LINE_SIZE,
                                             (UINT32)Fls_Load_Status_Sec_Buff.word,
                                             &pgmCtxData);

            if(C55_OK == opResult)
            {
                /* Verify */
                return_code = pProgramVerify(&ssdConfig,
                                             prog_address,                           /* dest   */
                                             FLASH_LINE_SIZE,                        /* size   */
                                             (UINT32)Fls_Load_Status_Sec_Buff.word,  /* source */
                                             &failAddress,
                                             &failData,
                                             &failSource,
                                             &pvCtxData);

                if (C55_OK == return_code)
                {
                    /* Call FlashCheckStatus() to check status of the progress */
                    while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                               C55_MODE_OP_PROGRAM_VERIFY,
                                                               &opResult,
                                                               &pvCtxData))
                    {
                        /* Add your code here */
                    }
                }

                if((C55_OK != return_code) || (C55_OK != opResult))
                {
                    return_status = FLS_FAIL;  /* verify failed */
                }
                else
                {
                    return_status = FLS_OK;
                }
            }
            else
            {
                return_status = FLS_FAIL;  /* program failed */
            }

            EnablePrefetchingPiplining();
            EnableAllInterrupts();
        }
        else
        {
            return_status = FLS_FAIL;  /* block locking/unlocking failed */
        }
    }

    return(return_status);
}

/*****************************************************************************/
/* Name:        FlsUpdate anti scanning time delay status                    */
/* Description: Update the anti scanning time delay status into flash memory.*/
/* Input:       Data to programme                                            */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_FAIL                                          */
/*****************************************************************************/
UINT8 FlsUpdateASDStat(U32 antiscandelaystat)
{
    UINT8  i;
    UINT8  return_status = FLS_OK;

    UINT32 prog_address;

    UINT32 failAddress;          /* save the failed address in flash */

    UINT32 return_code;
    UINT32 opResult;
    UINT32 low_address_space_enable = 0;
    UINT32 mid_address_space_enable = 0;
    UINT32 high_address_space_enable = 0;
    N256K_BLOCK_SEL n256KBlockSelect;

    UINT32 failData;             /* save the failed data in flash */
    UINT32 failSource;           /* save the failed data in source buffer */

    /* Program the load status */

    /*
        DEVIATION:     0501
        DESCRIPTION:   Right operand of shift operator is too large - this is undefined.
        JUSTIFICATION: In bootloader there is need of using 64bit variables. MISRA accepts variables which have max 32bits.
     */
    /* PRQA S 0501 1 */
    Fls_Load_Status_Sec_Buff.word[0] =(UINT32)(antiscandelaystat);
    Fls_Load_Status_Sec_Buff.word[1] =(UINT32)(0xFFFFFFFFUL);

    prog_address = FLSH_LOAD_ANTISCANNING_DELAY_START_ADDR;

    if (FlsIsBlockProgrammable(prog_address, &i) == TRUE)
    {
        return_code = FlsSetBlkProtection(i, &low_address_space_enable,
                                             &mid_address_space_enable,
                                             &high_address_space_enable,
                                             &n256KBlockSelect);

        if(C55_OK == return_code)
        {
            DisableAllInterrupts();
            DisablePrefetchingPiplining();

            opResult = pFlashProgramAndCheck(&ssdConfig,
                                             FALSE,
                                             prog_address,
                                             FLASH_LINE_SIZE,
                                             (UINT32)Fls_Load_Status_Sec_Buff.word,
                                             &pgmCtxData);

            if(C55_OK == opResult)
            {
                /* Verify */
                return_code = pProgramVerify(&ssdConfig,
                                             prog_address,                           /* dest   */
                                             FLASH_LINE_SIZE,                        /* size   */
                                             (UINT32)Fls_Load_Status_Sec_Buff.word,  /* source */
                                             &failAddress,
                                             &failData,
                                             &failSource,
                                             &pvCtxData);

                if (C55_OK == return_code)
                {
                    /* Call FlashCheckStatus() to check status of the progress */
                    while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                               C55_MODE_OP_PROGRAM_VERIFY,
                                                               &opResult,
                                                               &pvCtxData))
                    {
                        /* Add your code here */
                    }
                }

                if((C55_OK != return_code) || (C55_OK != opResult))
                {
                    return_status = FLS_FAIL;  /* verify failed */
                }
                else
                {
                    return_status = FLS_OK;
                }
            }
            else

            {
                return_status = FLS_FAIL;  /* program failed */
            }

            EnablePrefetchingPiplining();
            EnableAllInterrupts();
        }
        else
        {
            return_status = FLS_FAIL;  /* block locking/unlocking failed */
        }
    }

    return(return_status);
}


/*****************************************************************************/
/* Name:         FlsProgramBuffer                                            */
/* Description:                                                              */
/*                                                                           */
/*        Programmes FLASH_LINE_SIZE bytes from the buffer and verifies      */
/*        the programmed data.                                               */
/*                                                                           */
/*                                                                           */
/* Input:       -                                                            */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_INVALID, FLS_FAIL                             */
/*****************************************************************************/

static UINT8 FlsProgramBuffer(void)
{
    UINT8  i;
    UINT8  return_status = FLS_OK;

    UINT32 prog_address;

    UINT32 failAddress;          /* save the failed address in flash */
    UINT32 return_code;
    UINT32 opResult;
    UINT32 low_address_space_enable = 0;
    UINT32 mid_address_space_enable = 0;
    UINT32 high_address_space_enable = 0;
    N256K_BLOCK_SEL n256KBlockSelect;

    UINT32 failData;             /* save the failed data in flash */
    UINT32 failSource;           /* save the failed data in source buffer */



    /* Work out the the 8 byte boundary address to start programming */
    /* The program start address must be double word aligned !! */
    prog_address = Prog_buffer_address;

    if ((prog_address >= (UINT32)FLSH_LOAD_STATUS_LINE_START_ADDR) &&
        (prog_address < ((UINT32)FLSH_LOAD_STATUS_LINE_START_ADDR + FLASH_LINE_SIZE))
       )
    {
         /* Someone is trying to program the LoadStatus Value!! check if the value to program equals 0xFFFFFFFFFFFFFFFF */
         /* if not send an error message through the CCP */
        if( (*((UINT64 *)Fls_Data_Buffer.word)) != FLASH_LINE_BLANK)
        {
            return_status = FLS_FAIL;
        }
    }
    else
    {
        if ( (FlsIsBlockProgrammable(prog_address, &i)  == TRUE) &&
             (FlsIsLocationProgrammable(prog_address)   == TRUE)
           ) /* Ensure that the block is programmable and that the address is blank */
        {
            /* see if the program address + length crosses the sector boundary */
            if ((prog_address + FLASH_LINE_SIZE) > ((UINT32)Fls_Info[i].Start_Address + Fls_Info[i].Length))
            {
                return_status = FLS_FAIL;
            }
            else
            {
                return_code = FlsSetBlkProtection(i, &low_address_space_enable,
                                                     &mid_address_space_enable,
                                                     &high_address_space_enable,
                                                     &n256KBlockSelect);

                if(C55_OK == return_code)
                {
                    DisableAllInterrupts();
                    DisablePrefetchingPiplining();

                    opResult = pFlashProgramAndCheck(&ssdConfig,
                                                     FALSE,
                                                     prog_address,
                                                     FLASH_LINE_SIZE,
                                                     (UINT32)Fls_Data_Buffer.word,
                                                     &pgmCtxData);

                    if(C55_OK == opResult)
                    {
                        /* Verify */
                        return_code = pProgramVerify(&ssdConfig,
                                                     prog_address,                  /* dest   */
                                                     FLASH_LINE_SIZE,               /* size   */
                                                     (UINT32)Fls_Data_Buffer.word,  /* source */
                                                     &failAddress,
                                                     &failData,
                                                     &failSource,
                                                     &pvCtxData);

                        if (C55_OK == return_code)
                        {

                            /* Call FlashCheckStatus() to check status of the progress */
                            while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                                       C55_MODE_OP_PROGRAM_VERIFY,
                                                                       &opResult,
                                                                       &pvCtxData))
                            {
                                /* Add your code here */
                            }
                        }

                        if((C55_OK != return_code) || (C55_OK != opResult))
                        {
                            return_status = FLS_FAIL;  /* Flash program verify failed */
                        }
                    }
                    else
                    {
                        return_status = FLS_FAIL;   /* Flash program failed */
                    }

                    EnablePrefetchingPiplining();
                    EnableAllInterrupts();
                }
                else
                {
                    return_status = FLS_FAIL;    /* block locking/unlocking failed */
                }
            }
        }
        else
        {
            return_status = FLS_INVALID;  /* Block not programmable */
        }
    }

    /* No longer need this buffered data */
    FlsFillBuffer(Fls_Data_Buffer.byte, FLASH_LINE_SIZE, 0xFF);

    return(return_status);
}

/*****************************************************************************/
/* Name:        FlsEraseLoadStatusSector                                     */
/* Description: Erases the load status area if it is not already erased.     */
/* Input:       -                                                            */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_INVALID, FLS_FAIL                             */
/*****************************************************************************/
UINT8 FlsEraseLoadStatusSector(void)					/* Rami changed to global instead of file static*/
{
    UINT8   app_block = 0;
    UINT8   stat      = FLS_OK;

    if(m_eInfractAtt != PROG_INFRACT_ATT)
    {
    	/* Erase the Load Status if it is not already erased */
    	if (TRUE == FlsIsLocationProgrammable((UINT32)(__LOAD_STATUS)))
    	{
    		return (FLS_OK); /* Already erased */
    	}
    }

    if(FlsGetFlashBlock( ( (UINT32)(__LOAD_STATUS) ), &app_block) == TRUE)
    {
        stat = FlsEraseSector(app_block);
    }
    else
    {
        stat = FLS_INVALID;
    }

    return stat;
}

/*****************************************************************************/
/* Name:        FlsIsLocationProgrammable                                    */
/* Description: Checks if the given flash line is blank.                     */
/* Input:       Address to check.                                            */
/* Output:      -                                                            */
/* Return:      TRUE if blank else FALSE.                                    */
/*****************************************************************************/
static BOOL FlsIsLocationProgrammable(UINT32 addr)
{
    BOOL ret = FALSE;

    if( (*((UINT64 *)addr)) == FLASH_LINE_BLANK )
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }

    return  ret;
}

/*****************************************************************************/
/* Name:        FlsEraseCalibSector                                          */
/* Description: Unconditionally erases the calibration sector      .         */
/* Input:       Sector number to erase.                                      */
/* Output:      -                                                            */
/* Return:      -  FLS_OK, FLS_FAIL                                          */
/*****************************************************************************/
static UINT8 FlsEraseSector(UINT8 block)
{
    UINT8   stat                        = FLS_OK;
    UINT32  failAddress;                /* save the failed address in flash */
    UINT32  result;
    UINT32  opResult = C55_OK;
    UINT32  low_address_space_enable    = 0;
    UINT32  mid_address_space_enable    = 0;
    UINT32  high_address_space_enable   = 0;
    N256K_BLOCK_SEL n256KBlockSelect;
    UINT32  failData;                   /* save the failed data in flash */

    result = FlsSetBlkProtection(block, &low_address_space_enable,
                                        &mid_address_space_enable,
                                        &high_address_space_enable,
                                        &n256KBlockSelect);

    if(C55_OK == result)  /* if the unlocking has not failed ...*/
    {
        /* Erase the sector */
        DisablePrefetchingPiplining();

        /* Beginning EB modifications */
        /* Interrupts disable to keep a manage schedule by interruption watchdog */
        DisableAllInterrupts();
        /* End EB modifications */

        opResult = pFlashEraseAndCheck(&ssdConfig,
                                       C55_ERASE_MAIN,
                                       low_address_space_enable,
                                       mid_address_space_enable,
                                       high_address_space_enable,
                                       n256KBlockSelect,
                                       &dummyCtxData);

        if(C55_OK == opResult)
        {
            result = pBlankCheck(&ssdConfig,
                                 Fls_Info[ block ].Start_Address,
                                 Fls_Info[ block ].Length,
                                 &failAddress,
                                 &failData,
                                 &bcCtxData);

            /* Call FlashCheckStatus() to check status of the progress */
            while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                       C55_MODE_OP_BLANK_CHECK,
                                                       &opResult,
                                                       &bcCtxData))
            {
                /* Add your code here */
            }

            if(C55_OK == opResult)
            {
                stat = FLS_OK;
            }
            else
            {
                stat = FLS_FAIL;
            }
        }
        else
        {
            stat = FLS_FAIL;
        }
        /* Beginning EB modifications */
        EnableAllInterrupts();
        /* End EB modifications */

        EnablePrefetchingPiplining();
    }
    else
    {
        /* Unlocking has failed */
        stat = FLS_FAIL;
    }

    return stat;
}

/*****************************************************************************/
/* Name:        Fls_C55EraseBlk                                              */
/* Description: Erases the given block and load status if it is not already  */
/*              erased                                                       */
/* Input:       Block/Sector number to erase.                                */
/* Return:      -  FLS_C55_DONE => Erase complete                            */
/*                 FLS_C55_PENDING => Erase in progress, not yet complete    */
/*                 FLS_C55_FAIL => Erase failed due to some error            */
/*****************************************************************************/

UINT8 Fls_C55EraseBlk(UINT8 block)
{
    UINT8 status;

    if(pFlsC55EraseSector != NULL_PTR)
    {
        status = pFlsC55EraseSector(block);
    }
    else
    {
        status = FLS_C55_FAIL;
    }
    return status;
}


/*****************************************************************************/
/* Name:        FlsC55EraseSector                                            */
/* Description: Erases the given sector if it is not already erased.         */
/* Input:       Sector number to erase.                                      */
/* Return:      -  FLS_C55_DONE => Erase complete                            */
/*                 FLS_C55_PENDING => Erase in progress, not yet complete    */
/*                 FLS_C55_FAIL => Erase failed due to some error            */
/*****************************************************************************/
/*
    DEVIATION:     4700
    DESCRIPTION:   Metric value out of threshold range: FlsEraseLoadStatusSector() : STM19 = 2.
    JUSTIFICATION: Message is generated automatically when a metric value exceeds of
                   fall below a specified limit.
 */
/* PRQA S 4700 325 */


static UINT8 __attribute__((section(".fls_driver"))) FlsC55EraseSector(UINT8 block)
{
    BOOL   shadowFlag                      = FALSE;
    UINT8  stat                            = FLS_C55_DONE; /*return status*/
    UINT32 failAddress;                    /* save the failed address in flash */
    UINT32 result;                         /* result for intermediate function calls*/
    UINT32 low_address_space_enable        = 0U;
    UINT32 mid_address_space_enable        = 0U;
    UINT32 low_mid_address_space_enable    = 0U;/* low and mid address blockas are mapped on the same 32 bit register. */
    UINT32 high_address_space_enable       = 0U;
    UINT32 n256k_1st_address_space_enable       = 0U;
    UINT32 failData;                       /* save the failed data in flash */
    UINT8  resume_state = C55_RES_NOTHING; /* Erase resume status variable */
    UINT32 MCRValue;                       /* content of C55MCR register */
    UINT32 MCRAddress;                     /* address of C55MCR register */
    UINT32 c55flRegBase_u32;               /* base address of C55 registers */
    UINT32 interlockWriteAddress;          /* interlock write address */
    PSSD_CONFIG pSSDConfig;                /* ssd configuration structure*/
    UINT32  opResult = 0;

    static  UINT8 suspend_state = C55_SUS_NOTHING;  /*Status of suspend function*/
    static  UINT8 erase_status = START_ERASE;    /*State of FlsC55EraseSector() function*/



    /*Initialization of variables*/
    pSSDConfig = &ssdConfig;
    c55flRegBase_u32 = pSSDConfig->c55RegBase;
    MCRAddress = c55flRegBase_u32 + (UINT32)C55_MCR;

    switch(erase_status)
    {
        case START_ERASE:
        {
            UINT8  req_space;
            UINT32 fls_blk_id_mask ;
            UINT32 enable_blocks[ FLS_NUM_ADDRESS_SPACES ];
            UINT32 blockSelectRegister_Lo_Mi;
            UINT32 blockSelectRegister_Hi;
            UINT32 blockSelectRegister_n256_1st;

            blockSelectRegister_Lo_Mi    = c55flRegBase_u32 + (UINT32)C55_SEL0;
            blockSelectRegister_Hi       = c55flRegBase_u32 + (UINT32)C55_SEL1;
            blockSelectRegister_n256_1st = c55flRegBase_u32 + (UINT32)C55_SEL2;


            /* Check if the sector is already erased, if not erase it */
            /* Always erase the short (NVM) sectors without reading them first */
            result = pBlankCheck(&ssdConfig,
                                 Fls_Info[ block ].Start_Address,
                                 Fls_Info[ block ].Length,
                                 &failAddress,
                                 &failData,
                                 &bcCtxData);

            if (C55_OK == result)
            {
                /* Call FlashCheckStatus() to check status of the progress */
                while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                           C55_MODE_OP_BLANK_CHECK,
                                                           &opResult,
                                                           &bcCtxData))
                {
                    /* Add your code here */
                }
            }


            if ((0U != Fls_Info[ block ].Length)||(C55_OK != result) || (C55_OK != opResult))
            {
                result = 0xFFFFFFFFUL;
                /* get the required address space low, mid, high or n256k */
                req_space       = (UINT8)Fls_Info[ block ].Address_Space;
                fls_blk_id_mask =        Fls_Info[ block ].Bit_Mapped_Block_Id;

                enable_blocks[ FLS_LOW_ADDRESS_SPACE ]      = 0;
                enable_blocks[ FLS_MID_ADDRESS_SPACE ]      = 0;
                enable_blocks[ FLS_HIGH_ADDRESS_SPACE ]     = 0;
                enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ] = 0;
                enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ] = 0;


                if(req_space < FLS_NUM_ADDRESS_SPACES)
                {
                    enable_blocks[ req_space ] = fls_blk_id_mask;
                }

                /*
                 Unlock flash block as specified by req_space[ fls_blk_id_mask]
                 */


                /* Set lock bit for the low address space */
                result = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_LOW, (UINT32)~enable_blocks[ FLS_LOW_ADDRESS_SPACE ]);

                /* Set lock bit for the middle address space */
                if(C55_OK == result)
                {
                    result = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_MID, (UINT32)~enable_blocks[ FLS_MID_ADDRESS_SPACE ]);
                }

                /* Set lock bit for the high address space */
                if(C55_OK == result)
                {
                    result = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_HIGH, (UINT32)~enable_blocks[ FLS_HIGH_ADDRESS_SPACE ]);
                }

                /* Set lock bit for the 256k first address space (from block 0 to block 31) */
                if(C55_OK == result)
                {
                    result = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_256K_FIRST, (UINT32)~enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ]);
                }

                /* Set lock bit for the 256k second address space (from block 32 to upper block numbering) */
                if(C55_OK == result)
                {
                    result = pSetLock(&ssdConfig, (UINT8)C55_BLOCK_256K_SECOND, (UINT32)~enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ]);
                }

                low_address_space_enable       = enable_blocks[ FLS_LOW_ADDRESS_SPACE ];
                mid_address_space_enable       = enable_blocks[ FLS_MID_ADDRESS_SPACE ];
                high_address_space_enable      = enable_blocks[ FLS_HIGH_ADDRESS_SPACE ];
                n256k_1st_address_space_enable = enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ];


                if(C55_OK == result)  /* if the unlocking has not failed ...*/
                {
                    /* Initiate erase operation for the sector */
                    result = 0xFFFFFFFFUL;
                    shadowFlag = FALSE;
                    MCRValue = C55_REG_READ(MCRAddress);


                    /* program and/or erase operation in progress */
                    if (0U != (MCRValue & (C55_MCR_PGM | C55_MCR_ERS)))
                    {
                        result = C55_ERROR_BUSY;
                    }
                    else
                    {
                       /*
                           DEVIATION:     3355 3356
                           DESCRIPTION:   The result of this logical operation is always 'true'.
                                          The value of this 'if' control expression is always 'true'.
                           JUSTIFICATION: This flag is changed in more files. Not only here
                       */
                       /* PRQA S 3355 2 *//* PRQA S 3358 2 */
                        if (FALSE == shadowFlag)
                        {
                            /* erase the main array blocks */
                            interlockWriteAddress = pSSDConfig->mainArrayBase;

                            /* mask off reserved bits for low address space. Note: Low and Mid are in same register */
                            low_mid_address_space_enable = (low_address_space_enable)&(0xFFFFFFFFUL >> (32U - pSSDConfig->lowBlockInfo.n16KBlockNum));

                            /* mask off reserved bits for mid address space. Note: Low and Mid are in same register*/
                            low_mid_address_space_enable |= (mid_address_space_enable & (0xFFFFFFFFUL >> (32U - pSSDConfig->midBlockInfo.n32KBlockNum))) << 16;

                            /* mask off reserved bits for high address space */
                            high_address_space_enable &= 0xFFFFFFFFUL >> (32U - pSSDConfig->highBlockInfo.n64KBlockNum);

                            /* mask off reserved bits for n246k_1st address space */
                            n256k_1st_address_space_enable &= 0xFFFFFFFFUL >> (32U - pSSDConfig->n256KBlockNum);


                            if (0U == (low_mid_address_space_enable | high_address_space_enable | n256k_1st_address_space_enable) )
                            {
                                /* no blocks to be erased */
                                result = C55_OK;
                            }
                            else
                            {
                                /* set the block selection registers - mpw it may be that we have to makesure all other blocks are not enabled otherwise they will bwe erased. */
                                C55_REG_WRITE (blockSelectRegister_Lo_Mi,    low_mid_address_space_enable);
                                C55_REG_WRITE (blockSelectRegister_Hi,       high_address_space_enable);
                                C55_REG_WRITE (blockSelectRegister_n256_1st, n256k_1st_address_space_enable);


                                /* set ERS bit in MCR to start erase operation */
                                C55_MCR_BIT_SET (MCRAddress, (UINT32)C55_MCR_ERS);

                                /* interlock write */
                                *( (UINT32 *)interlockWriteAddress ) = 0xFFFFFFFFUL;
                                /* Set EHV to high */
                                C55_MCR_BIT_SET (MCRAddress, (UINT32)C55_MCR_EHV);

                                /* Successful process */
                                result = C55_OK;
                            }
                        }
                    }

                    if(C55_OK == result)
                    {
                        VUINT32 cnt_index;
                        result =  0xFFFFFFFFUL;
                        /*Wait for a while , then suspend the erase*/
                        for(cnt_index=0; cnt_index < ERASE_DELAY; cnt_index++)
                        {
                            ;  /* mpw this is a poor delay, could use timer read instead */
                        }

                        result = pFlashSuspend (&ssdConfig, &suspend_state);

                        if( ((result == C55_OK) && (suspend_state == C55_SUS_NOTHING)) ||
                            ((result == C55_OK) && (suspend_state == C55_ERS_SUS))        )
                        {
                            /*If erase suspend state is no operation(blank check will be done in
                              next cycle) or erase suspend, set return status to Erase pending */
                            stat = FLS_C55_PENDING;
                        }
                        else
                        {
                            stat = FLS_C55_FAIL;   /*Suspend operation failed*/
                        }
                    }
                    else
                    {
                        stat = FLS_C55_FAIL;  /*Start erase failed*/
                    }
                }
                else
                {   /* Unlocking has failed */
                    stat = FLS_C55_FAIL;
                }
            }
            else
            {
                /* Blank check successful , the block is blank */
                stat = FLS_C55_DONE;
            }
            break;
        }

        case ERASE_CONTINUE:
        {
            if(suspend_state == C55_SUS_NOTHING)
            {
                result = 0xFFFFFFFFUL;
                /*Check if sector is blank */
                result = pBlankCheck(&ssdConfig,
                                     Fls_Info[ block ].Start_Address,
                                     Fls_Info[ block ].Length,
                                     &failAddress,
                                     &failData,
                                     &bcCtxData);
                if(C55_OK == result)
                {
                    /*Erase of sector complete, stop erase (set erase ERS and EHV bit to low)*/
                    pFlashEraseStop(&ssdConfig);

                    stat = FLS_C55_DONE;
                }
                else
                {
                    stat = FLS_C55_FAIL; /*Blank check failed*/
                }
            }
            else if(suspend_state == C55_ERS_SUS)
            {
                VUINT32 cnt_index;
                result =  0xFFFFFFFFUL;

                result = pFlashResume(&ssdConfig, &resume_state);

                if( ((result == C55_OK) && (resume_state == C55_RES_ERS))      ||
                    ((result == C55_OK) && (resume_state == C55_RES_NOTHING))  )
                {
                    /* Generate a delay of over 1 us*/
                    /* The FlashResume function transitions EHV from 0-1*/
                    /* This causes the DONE bit to go low for a time */
                    /* Tdone + Tres as per datasheet. Which is 105ns so decided to have */
                    /* a higher delay of little more than 1us to be sure */
                    for (cnt_index = 20U; cnt_index > 0U; cnt_index--)
                    {
                        ; /* mpw poor delay mechanism, should use timer. mpw */
                    }
                    if(0U != (C55_REG_BIT_TEST (MCRAddress, (UINT32)C55_MCR_DONE)))
                    {
                        result = 0xFFFFFFFFUL;
                        result = pFlashEraseStop(&ssdConfig);

                        /* This check makes sure that the PEG bit is set to One to indicate */
                        /* the completion of erase operation                                */
                        if (C55_OK == result)
                        {
                            stat = FLS_C55_DONE;
                        }
                        else
                        {
                            /* The erasing restart after the suspend action */
                            stat = FLS_C55_PENDING;
                        }
                    }
                    else
                    {
                        VINT32 cnt_delay;
                        result = 0xFFFFFFFFUL;
                        /* The erasing should restart in the next cycle after suspend action */
                        for(cnt_delay = 0; cnt_delay <(INT32)ERASE_DELAY; cnt_delay++)
                        {
                            ;
                        }

                        result = pFlashSuspend (&ssdConfig, &suspend_state);

                        if(C55_OK == result)
                        {
                            stat = FLS_C55_PENDING; /*Erase suspended, return status erase in progress*/
                        }
                        else
                        {
                            stat = FLS_C55_FAIL;  /*Erase suspend failed*/
                        }
                    }
                }
                else
                {
                    stat = FLS_C55_FAIL;  /* Erase resume operation failed */
                }
            }
            else
            {
                stat = FLS_C55_FAIL; /*Erase suspend state not correct*/
            }
            break;
        }
        default:
        {
            break;
        }
    }
    if (stat == FLS_C55_DONE)
    {
        /* Erase successful , the block is blank */
        erase_status = START_ERASE;
        suspend_state = C55_SUS_NOTHING;
    }
    else if(stat == FLS_C55_PENDING)
    {
        /*Erase in progress, continue erase in next cycle*/
        erase_status = ERASE_CONTINUE;
    }
    else
    {
        /*Erase failed, stop erase function(reset ERS and EHV bits) and set function status to Start erase*/
        erase_status = START_ERASE;
        suspend_state = C55_SUS_NOTHING;
        pFlashEraseStop(&ssdConfig);
    }
    return stat;
}


#ifndef STATIC_TEST
asm void static write_r3(register UINT32 value)
{
% reg value
  mr r3,value
}
#endif /* STATIC_TEST */


/*****************************************************************************/
/* Name:        FlashEraseStop                                               */
/* Description: Stops the erase operation                                    */
/* Input:       pointer to SSD configuration structure                       */
/* Return:      -  C90FL_OK => Erase stopped                                 */
/*                 C90FL_ERROR_EGOOD => Error in erase stop operation        */
/*****************************************************************************/

static UINT32 __attribute__((section(".fls_driver"))) FlashEraseStop (PSSD_CONFIG pSSDConfig)
{
    register UINT32 returnCode;     /* return code */
    UINT32 MCRAddress;              /* address of C90FLMCR register */

    returnCode = C55_OK;

    MCRAddress = pSSDConfig->c55RegBase + (UINT32)C55_MCR;



    /* Set MCR-EHV to 0 */
    C55_MCR_BIT_CLEAR(MCRAddress, C55_MCR_EHV);

    /* confirm MCR-PEG = 1 */
    if (0U == (C55_REG_READ (MCRAddress) & (UINT32)C55_MCR_PEG) )
    {
        returnCode = C55_ERROR_EGOOD;
    }
    /* clear MCR-ERS bit */
    C55_MCR_BIT_CLEAR (MCRAddress, C55_MCR_ERS);

    if (0 != (pSSDConfig->BDMEnable))
    {
        /* save the return code to R3 */
        /* For CodeWarrior */
        #if (CODE_WARRIOR == COMPILER_SELECT)
        asm ( "mr   r3,returnCode" );
        #else
        /* For Diab */
        #ifndef STATIC_TEST
        (void)write_r3(returnCode);
        #endif /* STATIC_TEST */
        #endif

        #ifdef VLE_ASM
        asm ( "nop" );
        asm ( "se_sc " );                  /* generate system call interrupt */
        asm ( "nop" );
        #else
        asm ( "nop" );
        asm ( "sc " );
        asm ( "nop" );
        #endif
    }

    return returnCode;
}

/*********************************************************************************/
/* Name: MpcDsi_Handler: Note that there is a function with the same name in     */
/* the MCAL application code.                                                    */
/*-------------------------------------------------------------------------------*/
/* Description: Handles the ECC interrupt call when an ECC error occurs.         */
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* Implements:                                                                   */
/*********************************************************************************/
U32 MpcDsi_Handler(U32 val_mcsrr0, U32 val_mcar, U32 val_mcsr)
{
    U32 FlashUnCorrectableAddr_0;
    U32 FlashUnCorrectableSts_0;

    U32 SysRamUnCorrectableAddr_0;
    U32 SysRamUnCorrectableSts_0;

    U32 PeriphRamUnCorrectableAddr_0;
    U32 PeriphRamUnCorrectableSts_0;

    U8 * instr = (U8 *)val_mcsrr0;
    U8 opcode = (U8)( (* instr) & 0x90u);

    /* Read MEMU and check where is ECC Error */
    MEMU_Read_SYS_RAM_Uncorrectable_Err(&SysRamUnCorrectableAddr_0,&SysRamUnCorrectableSts_0);

    /* Read MEMU and check where is ECC Error */
    MEMU_Read_PERIPH_RAM_Uncorrectable_Err(&PeriphRamUnCorrectableAddr_0,&PeriphRamUnCorrectableSts_0);

    /* Read MEMU and check where is ECC Error */
    MEMU_Read_FLASH_Uncorrectable_Err(&FlashUnCorrectableAddr_0, &FlashUnCorrectableSts_0);

    if((val_mcsr & 0x000C0000UL) == 0x00080000UL) /* test the MAV bit and is a phsical address */
    {
        if(FlashUnCorrectableSts_0 != 0U)  /* In FLASH */
        {
            if((val_mcar >= (U32)&__CALIB_FLASH_START) && (val_mcar <= (U32)&__CALIB_FLASH_END))
            {
                /* Erase Calibration and Load status sectors */
                FlsAppInit();
                (void)FlsEraseSector(FLASH_LOAD_STATUS_SECTOR_START);
                (void)FlsEraseSector(FLASH_CAL_SECTOR_START);
                MEMU_Clear_Err_Tables();
                /* RESET to remove any ECC Errors that might be in SYS RAM or PERIPFERAL RAM */
                Mcu_PerformReset();
            }
            else   /* Code */
            {
                if (opcode == 0x10)
                {
                    /* most significant 4 Bits have a value of 1,3,5,7 */
                    instr += 4;    /* instruction was 32 bit */
                }
                else
                {
                    /* most significant 4 Bits have a value of 0,2,4,6,8,9,A,B,C,D,E (and F, which is reserved) */
                    instr += 2;    /* instruction was 16 bit */
                }


                if (ReadingBlocks == TRUE)
                {
                    BlockHeaderAddress_pu32 = BlockHeaderAddress_pu32 + 8;

                }
                else if (ReadingCluster == TRUE)
                {
                    /* In this case there is no point trying to get Tvds. Overkill trying to
                    to figure out which of the clusters failed etc. This itself might be
                    an overkill as boot gets called from application and application
                    would have corrected the ECC errors */

                    ECC_ClustIdRead = TRUE;

                }
                else if (((val_mcar >= (U32)&__SOFT_FLASH_START) && (val_mcar <= (U32)&__SOFT_FLASH_END))
#if 0
                      || ((val_mcar >= (U32)&__HISTORIC_FIELD) && (val_mcar <= (U32)&__HISTORIC_FIELD_END))
#endif
						)
                {
                    /* ECC error in application do nothing */
                    /* ECC error in history area do nothing */
                }
                else
                {
                    /* The fault lies outside of app, cal or history area so we cannot handle the situation */
                    /* Note that this function never returns */
                    Send_hardware_fault(3);
                }
            }
        }
        else if(SysRamUnCorrectableSts_0 != 0U)
        {
            /* RESET the Software */
            MEMU_Clear_Err_Tables();
            Mcu_PerformReset();
        }
        else if(PeriphRamUnCorrectableSts_0 != 0U)
        {
            /* RESET the Software */
            MEMU_Clear_Err_Tables();
            Mcu_PerformReset();
        }
        else
        {
        }
    }
    else
    {    /* why are we here? Well if it is bus error or ilegal instruction or something else, we can just increment the program counter. */

        if (opcode == 0x10)
        {
            /* most significant 4 Bits have a value of 1,3,5,7 */
            instr += 4;    /* instruction was 32 bit */
        }
        else
        {
            /* most significant 4 Bits have a value of 0,2,4,6,8,9,A,B,C,D,E (and F, which is reserved) */
            instr += 2;    /* instruction was 16 bit */
        }
    }
    return ((U32)instr);
}

/**************************************************************************************************
 * Name         :  FlsGet_From_Nvm
 *-------------------------------------------------------------------------------------------------
 * Parameters   :  block_number_u16 - number of block to read data from NVM,
 *              :  offset_u8 - offset in NVM block to read data
 *              :  nvm_read_buf - pointer to pointer where data can be read
 * Return value :  nvm_ret_u8 - NVM_READ_FAIL (data not obtained) or NVM_READ_PASS (data read)
 * Description  :  Function fills the data output buffer
 **************************************************************************************************/
UINT8 FlsGet_From_Nvm(UINT16 block_number_u16, UINT8 offset_u8, UINT8 **nvm_read_buf)
{

    UINT32 ClustID1_u32;
    UINT32 ClustID2_u32;
    UINT32 * EmulEepromAdr_pu32;
    UINT32 * DataBlockAddress_pu32;
    UINT16 BlockNumber_u16;
    UINT32 BlockCount_u32 = 0;
    UINT32 ClusterStartAddress = 0;
    UINT32 LogicalPhysicalOffset = 0;
    UINT8 BlockValidity_u8;
    UINT8 nvm_ret_u8 = NVM_READ_FAIL;

    ReadingCluster = TRUE;

    ClustID1_u32 = *((UINT32 *) &__EEPROM3_SECTOR1_ADDR);
    ClustID2_u32 = *((UINT32 *) &__EEPROM3_SECTOR2_ADDR);

    ReadingCluster = FALSE;

    /* reading cluster went wrong no point continuing*/
    if (ECC_ClustIdRead == FALSE)
    {
        /* Do we need to check the validity of a cluster as well? */

        /* The below conditions figures out the correct cluster id*/
        if ((ClustID1_u32 == 0xFFFFFFFFUL) && (ClustID2_u32 == 0xFFFFFFFFUL))
        {
            /* Invalid clusters*/
            /* return default value of Tvds*/
        }
        else
        {
            if (ClustID2_u32 == 0xFFFFFFFFUL)
            {
                EmulEepromAdr_pu32 = &__EEPROM3_SECTOR1_ADDR;
            }
            else if (ClustID1_u32 == 0xFFFFFFFFUL)
            {
                EmulEepromAdr_pu32 = &__EEPROM3_SECTOR2_ADDR;
            }
            else if (ClustID1_u32 > ClustID2_u32)
            {
                EmulEepromAdr_pu32 = &__EEPROM3_SECTOR1_ADDR;
            }
            else
            {
                EmulEepromAdr_pu32 = &__EEPROM3_SECTOR2_ADDR;
            }

            /* Now that we have figured out which cluster to use read through the
            blocks to find the right block then check if it is valid, then
            get the right value from it */
            /*  DEVIATION:     0489/0306
            DESCRIPTION:   Performing pointer arithmetic/Incrementing pointer/Cast between a pointer to object and an integral type
            JUSTIFICATION: In order to browse through the NVM structure the best option available is pointer arithmetic.
                           Avoid this warning for next 44 lines*/
            /* PRQA S 0489 1 */ /* PRQA S 0306 2 */
            ClusterStartAddress = *(EmulEepromAdr_pu32 + 1);    /* The cluster address is 4 bytes away or 1 words away*/
            LogicalPhysicalOffset = ((UINT32)EmulEepromAdr_pu32 - ClusterStartAddress); /* This is the difference between the logical address (used by the FEE)
                                                                                           to the physical address (as it appears in the .mot file) */

            BlockHeaderAddress_pu32 = EmulEepromAdr_pu32 + 8;   /* The block address is 32 bytes away or 8 words away*/
            ReadingBlocks = TRUE;

            /* Now loop through till the end to get the Tvds information */

            /* Just keep the range to the size of EMUL eeprom*/
            /* Block count is just for protection, the assumption is that without any data
           just by filling up with block headers alone the count can go up to 65536 */
            while ((*BlockHeaderAddress_pu32 != 0xFFFFFFFFUL) && (BlockCount_u32 < 65536U))
            {
                /* These lines should be here so that the conditions after a read should not
               pass in case there is an ECC error on read */
                BlockNumber_u16 = 0;
                BlockValidity_u8 = 0;

                BlockNumber_u16 = *((UINT16 *) ((void *) BlockHeaderAddress_pu32));
                if (BlockNumber_u16 == block_number_u16) /* The first 2 bytes of the block gives the block number*/
                {
                    /* We have found the right block now check if it is valid  */

                    BlockValidity_u8 = *((UINT8 *) ((void *) (BlockHeaderAddress_pu32 + 4U)));/* The block validity is 16 bytes or 4 words away*/
                    if (BlockValidity_u8 == 0x81U)
                    {
                        /* Now that the block is valid get the Tvds from data
                     for that get the data block address */
                        /*  DEVIATION:     0489/0306
                        DESCRIPTION:   Incrementing pointer/Converting value to pointer
                        JUSTIFICATION: In order to browse through the NVM structure the best option available is pointer arithmetic. */
                        /* PRQA S 0306 1 */ /* PRQA S 0489 1 */
                        DataBlockAddress_pu32 = (UINT32 *) (*(BlockHeaderAddress_pu32 + 1U)); /* Data block address is one word(4 bytes) away from the block header base address*/
                        /* There is an offset of 20 to get data */
                        *nvm_read_buf = (UINT8 *) (((UINT8 *) (void *) DataBlockAddress_pu32) + offset_u8 + LogicalPhysicalOffset);
                        /* Return read passed*/
                        nvm_ret_u8 = NVM_READ_PASS;
                    }
                }
                BlockHeaderAddress_pu32 = BlockHeaderAddress_pu32 + 8U; /* Run to the next block which is 8 words away*/
                BlockCount_u32++; /* Just for protection in case something drastically goes wrong with NVM blocks*/
            }
        }
    }
    ReadingBlocks = FALSE;
    ECC_ClustIdRead = FALSE;
    return nvm_ret_u8;
}

/*****************************************************************************
 * Name:        FlashProgramAndCheck
 * Description: Calls the pFlashProgram() function to Programme the specified
 *      source data into the specified destination FLASH area and then waits,
 *      checking the Flash status,  while the programming is carried out.
 *      Should the attempt to Programme the Flash return a failure then this
 *      programming of Flash is aborted and the function returns the error code.
 *
 * Note 1: flash programming, pFlashProgram(), is a non blocking function and
 *      so the function, pFlashCheckStatus(), is polled waiting for the completion
 *      of the programming action. The execution of this function is carried out in
 *      RAM while the FLASH is being updated.
 *
 * Note 2: it is intended that this function be copied to RAM and executed from
 *       RAM, especially if it is to update any part of its FLASH partition.
 *
 * Note 3: the functions [ pFlashProgram(), pFlashCheckStatus(), and pFlashAbort() ]
 *       called from this function are RAM functions and must be copied there before
 *       calling this function.
 *
 * Input:  pSSDConfig - Pointer to the SSD Configuration Structure.
 *         factoryPgmFlag - A flag indicate to do whether factory program or not.
 *         dest - Destination address to be programmed in flash memory.
 *         size - Size, in bytes, of the flash region to be programmed.
 *         source - Source program buffer address.
 *         pCtxData - Address of context data structure.
 *
 * Output: pCtxData - Address of context data structure.
 * Return: opResult - Successful completion or error value.
 *****************************************************************************/
static UINT32 __attribute__((section(".fls_driver"))) FlashProgramAndCheck(PSSD_CONFIG pSSDConfig,
                                                                           BOOL factoryPgmFlag,
                                                                           UINT32 dest,
                                                                           UINT32 size,
                                                                           UINT32 source,
                                                                           PCONTEXT_DATA pCtxData)
{

    UINT32 opResult;
    UINT32 return_code;

    return_code = pFlashProgram(pSSDConfig,
                                factoryPgmFlag, /* factoryPgmFlag */
                                dest,           /* dest */
                                size,           /* size */
                                source,         /* source */
                                pCtxData);

    if (C55_OK == return_code)
    {
        /* Call FlashCheckStatus() to check status of the progress */
        while (C55_INPROGRESS == pFlashCheckStatus(pSSDConfig,
                                                   C55_MODE_OP_PROGRAM,
                                                   &opResult,
                                                   pCtxData))
        {
            /* Add your code here */
        }
    }
    else
    {
        pFlashAbort(pSSDConfig);
        opResult = return_code;   /* Flash program failed */
    }

    return opResult;
}

/*****************************************************************************
 * Name:        FlashEraseAndCheck
 * Description: Calls the pFlashErase() function to erase the specified blocks
 *      from the various Partitions and then waits, checking the Flash status,
 *      while the erasing is carried out. Should the erasing function return
 *      a failure then the erasing of Flash is aborted and this function
 *      returns the error code.
 *
 * Note 1: flash erase, pFlashErase(), is a non blocking function and so the
 *      function, pFlashCheckStatus(), is polled waiting for the completion of
 *      the erasing action. The execution of this function is carried out in
 *      RAM while the FLASH is being erased.
 *
 * Note 2: it is intended that this function be copied to RAM and executed from
 *      RAM, especially if it is to update any part of its FLASH partition.
 *
 * Note 3: the functions [ pFlashErase(), pFlashCheckStatus(), and pFlashAbort() ]
 *      called from this function are RAM functions and must be copied there
 *      before calling this function.
 *
 * Input: pSSDConfig - Pointer to the SSD Configuration Structure.
 *        eraseOption - The option is to select users expected erase operation.
 *        lowBlockSelect - To select the array blocks in low address space for erasing.
 *        midBlockSelect - To select the array blocks in mid address space for erasing.
 *        highBlockSelect - To select the array blocks in high address space for erasing.
 *        n256KBlockSelect - To select the array blocks in 256K address space for erasing.
 *                         It includes two elements to decode the first half of 256K block
 *                         select and the second half of 256K block select.
 *        pCtxData - Address of context data structure.
 *
 * Output: pCtxData - Address of context data structure.
 * Return: opResult - Successful completion or error value.
 *****************************************************************************/
static UINT32 __attribute__((section(".fls_driver"))) FlashEraseAndCheck(PSSD_CONFIG pSSDConfig,
                                                                         UINT8 eraseOption,
                                                                         UINT32 lowBlockSelect,
                                                                         UINT32 midBlockSelect,
                                                                         UINT32 highBlockSelect,
                                                                         N256K_BLOCK_SEL n256KBlockSelect,
                                                                         PCONTEXT_DATA pCtxData)
{

    UINT32 opResult;
    UINT32 return_code;

    return_code = pFlashErase(pSSDConfig,
                              eraseOption,
                              lowBlockSelect,
                              midBlockSelect,
                              highBlockSelect,
                              n256KBlockSelect);

    if (C55_OK == return_code)
    {
        /* Call FlashCheckStatus() to check status of the progress */
        while (C55_INPROGRESS == pFlashCheckStatus(pSSDConfig,
                                                   C55_MODE_OP_ERASE,
                                                   &opResult,
                                                   pCtxData))
        {
            /* Add your code here */
        }
    }
    else
    {
        pFlashAbort(pSSDConfig);
        opResult = return_code;
    }

    return opResult;
}
