/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/BRP/project.pj $
        $RCSfile: brp_main.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:47CST $

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

/* DEVIATION:     0305
   DESCRIPTION:   Cast between a pointer to function and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0305 EOF */

/* DEVIATION:     0306
   DESCRIPTION:   Cast between a pointer to object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0306 EOF */

/* DEVIATION:     0428
   DESCRIPTION:   Function identifier should probably be followed by ().
   JUSTIFICATION: This is pointer to function.
*/
/* PRQA S 0428 EOF */

/*  DEVIATION:     2213
    DESCRIPTION:   Matching braces appear on the same line - proper indentation would be preferred.
    JUSTIFICATION: The braces are not indented correctly, but if every brace were to be on a new
    line the data would not be very readable
*/
/* PRQA S 2213 EOF */

/***************************************************************************/


/*****************************************************************************
*
*   INCLUDE FILES
*
******************************************************************************/
#include "types.h"
#include "MPC5744P.h"
#include "boot_img.h"
#include "ssd_c55fl.h"
#include "Mcu_Reg_eSys_FLASHC.h"

/* MCAL Includes */
#include "port.h"
#include "dio.h"
#include "mcu.h"
#include "brp_main.h"

#include <string.h>


/* Macros and Defines */
/******************************************************************************
*
*   DEFINITIONS
*
******************************************************************************/
#define C55_REG_BASE                        0xFFFE0000UL
#define FLASH_BASEADDR                      C55_REG_BASE
#define MAIN_ARRAY_BASE                     0x00800000UL
#define UTEST_ARRAY_BASE                    0x00400000UL
#define UTEST_ARRAY_SIZE                    0x00004000UL

#define C55_PROGRAMMABLE_SIZE               0x80U

/* Lock State */
#define LOCK_ALL_BLOCKS                     0xFFFFFFFFUL
#define UNLOCK_ALL_BLOCKS                   0x00000000UL

#define BOOT_IMAGE_VALID                    1
#define BOOT_IMAGE_NOT_VALID                0

/* Mask for boot blocks in the high address space */
#define FLS_BOOT_BLOCK_MASK                 0x00000003UL
#define FLS_MAX_SECTORS                     (sizeof(Fls_Info) / sizeof(FLS_INFO_TYPE))

/* Status values */
#define FLS_FAIL                            0U
#define FLS_OK                              1U
#define FLS_INVALID                         2U

/* Reset generation module */
/*
#define RGM_BASE_ADDR 0xC3FE4000
#define RGM_FES ( *(volatile unsigned short*)(RGM_BASE_ADDR) ) *//* Functional Event Status */


/*****************************************************************************
*
*   PRIVATE FUNCTION DECLARATIONS
*
******************************************************************************/
/* Function prototypes */
static void   __attribute__((section (".slf_erase_fn"))) Brp_SelfErase(UINT32 low_addr_space_enable, UINT32 mid_address_space_enable, UINT32 high_address_space_enable, N256K_BLOCK_SEL n256KBlockSelect );
static UINT32 __attribute__((section(".fls_driver")))    FlashProgramAndCheck(PSSD_CONFIG pSSDConfig, BOOL factoryPgmFlag, UINT32 dest, UINT32 size, UINT32 source, PCONTEXT_DATA pCtxData);
static UINT32 __attribute__((section(".fls_driver")))    FlashEraseAndCheck(PSSD_CONFIG pSSDConfig, UINT8 eraseOption, UINT32 lowBlockSelect, UINT32 midBlockSelect, UINT32 highBlockSelect, N256K_BLOCK_SEL n256KBlockSelect, PCONTEXT_DATA pCtxData);

static void   Brp_FlsCopyRoutines(void) ;
static void   Brp_FlsAppInit(void)      ;
static UINT8  Brp_EraseFlash(UINT32 sector_addr) ;
static UINT8  Brp_ProgramFlash(UINT32 program_data, UINT32 target, UINT32 length);
static UINT8  Brp_ValidateBootImage(void) ;
static BOOL   Brp_FlsGetFlashBlock(UINT32 addr, UINT8 *index) ;
static BOOL   Brp_FlsGetAddrSpaceAndBitMask(UINT32 addr, UINT8* addr_space, UINT32* bit_mask ) ;
static UINT32 Brp_FlsSetLocks(UINT32 low_addr_space_blk_state, UINT32 mid_addr_space_blk_state, UINT32 high_addr_space_blk_state, UINT32 n256k_1st_addr_space_blk_state, UINT32 n256k_2nd_addr_space_blk_state) ;
static UINT32 Brp_FlsSetBlkProtection(UINT8 block_id, UINT32 *low_addr_space_enable, UINT32 *mid_addr_space_enable, UINT32 *high_addr_space_enable, N256K_BLOCK_SEL *n256KBlockSelect_p);
static void   Brp_FlsErrorTrap(UINT32 return_code) ;

/*****************************************************************************
*
*   PRIVATE VARIABLE DECLARATIONS
*
******************************************************************************/


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
    BOOL                    Programmable;

}FLS_INFO_TYPE;

typedef void (*pBrp_SelfErase_Type) (
                UINT32 low_addr_space_enable,
                UINT32 mid_address_space_enable,
                UINT32 high_address_space_enable,
                N256K_BLOCK_SEL n256KBlockSelect
               );

/************************ Variable definitions ***************************/

static pBrp_SelfErase_Type pBrp_SelfErase; /* function pointer to the function 'Brp_SelfErase'*/


/* Assign function pointers to the flash API */
static PFLASHINIT            pFlashInit;
static PFLASHERASE           pFlashErase;
static PBLANKCHECK           pBlankCheck;
static PFLASHPROGRAM         pFlashProgram;
static PPROGRAMVERIFY        pProgramVerify;
static PSETLOCK              pSetLock;
static PGETLOCK              pGetLock;
static PFLASHCHECKSTATUS     pFlashCheckStatus;
static PFLASHABORT           pFlashAbort;
static PFLASHPROGRAMANDCHECK pFlashProgramAndCheck;
static PFLASHERASEANDCHECK   pFlashEraseAndCheck;

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

static  CONTEXT_DATA dummyCtxData;
static  CONTEXT_DATA pgmCtxData;
static  CONTEXT_DATA bcCtxData;
static  CONTEXT_DATA pvCtxData;

/* Flash Information Table */

static const FLS_INFO_TYPE Fls_Info[] =
{
     /* Start_Address       Length      Address_Space               Bit_Mapped_Block_Id     Programmable */

    {   0x00800000,         0x04000,    FLS_LOW_ADDRESS_SPACE,      0x00000001,             TRUE    },  /* Emulated EEPROM1 - Page 1 */
    {   0x00804000,         0x04000,    FLS_LOW_ADDRESS_SPACE,      0x00000002,             TRUE    },  /* Emulated EEPROM1 - Page 2 */
    {   0x00F98000,         0x04000,    FLS_LOW_ADDRESS_SPACE,      0x00000004,             TRUE    },  /* Unused */
    {   0x00F9C000,         0x04000,    FLS_LOW_ADDRESS_SPACE,      0x00000008,             TRUE    },  /* Unused */

    {   0x00808000,         0x08000,    FLS_MID_ADDRESS_SPACE,      0x00000001,             TRUE    },  /* Emulated EEPROM2 - Page 1 */
    {   0x00810000,         0x08000,    FLS_MID_ADDRESS_SPACE,      0x00000002,             TRUE    },  /* Emulated EEPROM2 - Page 2 */

    {   0x00FA0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000001,             TRUE    },  /* BOOT 1 */
    {   0x00FB0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000002,             TRUE    },  /* BOOT 2 */
    {   0x00FC0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000004,             TRUE    },  /* APVs */
    {   0x00FD0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000008,             TRUE    },  /* BRP and Load status */
    {   0x00FE0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000010,             TRUE    },  /* Emulated EEPROM3 - Page 1 */
    {   0x00FF0000,         0x10000,    FLS_HIGH_ADDRESS_SPACE,     0x00000020,             TRUE    },  /* Emulated EEPROM3 - Page 2 */

    {   0x01000000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000001,             TRUE    },  /* Application sectors */
    {   0x01040000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000002,             TRUE    },
    {   0x01080000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000004,             TRUE    },
    {   0x010C0000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000008,             TRUE    },
    {   0x01100000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000010,             TRUE    },
    {   0x01140000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000020,             TRUE    },
    {   0x01180000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000040,             TRUE    },
    {   0x011C0000,         0x40000,    FLS_256K_1ST_ADDRESS_SPACE, 0x00000080,             TRUE    },
};

/*****************************************************************************/
/* Name:        flash_copy_routines                                          */
/* Description: Copies the flash routines from ROM into RAM for running      */
/* Input:       -                                                            */
/* Output:      -                                                            */
/* Return:      -                                                            */
/*****************************************************************************/

static void Brp_FlsCopyRoutines(void)
{
    /* Copy flash api code from ram to rom. Use labels created in link process. */
    (void)memcpy ((void *)&__FLASH_API_RAM_BASE, (void *)&__FLS_DRV_ST, (UINT32)&__FLS_DRV_SIZE);
    #ifndef POLYSPACE
    /* Set up function pointers for flash api functions which are now in RAM */

    pFlashInit            =  (PFLASHINIT)           ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashInit_C           - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashErase           =  (PFLASHERASE)          ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashErase_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pBlankCheck           =  (PBLANKCHECK)          ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&BlankCheck_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashProgram         =  (PFLASHPROGRAM)        ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashProgram_C        - (UINT32)&__FLS_DRV_ST) ) ;
    pProgramVerify        =  (PPROGRAMVERIFY)       ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&ProgramVerify_C       - (UINT32)&__FLS_DRV_ST) ) ;
    pSetLock              =  (PSETLOCK)             ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&SetLock_C             - (UINT32)&__FLS_DRV_ST) ) ;
    pGetLock              =  (PGETLOCK)             ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&GetLock_C             - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashCheckStatus     =  (PFLASHCHECKSTATUS)    ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashCheckStatus_C    - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashAbort           =  (PFLASHABORT)          ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashAbort_C          - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashProgramAndCheck =  (PFLASHPROGRAMANDCHECK)((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashProgramAndCheck  - (UINT32)&__FLS_DRV_ST) ) ;
    pFlashEraseAndCheck   =  (PFLASHERASEANDCHECK)  ((UINT32)&__FLASH_API_RAM_BASE + ( (UINT32)&FlashEraseAndCheck    - (UINT32)&__FLS_DRV_ST) ) ;

    #else
    /*The above function pointers are updated through the flash drivers which is not a 'C' code. As polyspace does not recognize the Hexa code,  */
    /* to facilitate polyspace verification used “stub_ssd_c55fl_algo.c” file which contains the below functions definitions in C code           */
    pFlashInit            =  &FlashInit;
    pFlashErase           =  &FlashErase;
    pBlankCheck           =  &BlankCheck;
    pFlashProgram         =  &FlashProgram;
    pProgramVerify        =  &ProgramVerify;
    pSetLock              =  &SetLock;
    pGetLock              =  &GetLock;
    pFlashCheckStatus     =  &FlashCheckStatus;
    pFlashAbort           =  &FlashAbort;
    pFlashProgramAndCheck =  &FlashProgramAndCheck;
    pFlashEraseAndCheck   =  &FlashEraseAndCheck;
    #endif
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Brp_FlsAppInit

DESCRIPTION:
    - Copy routines to RAM
    - perform flash driver initialisations

*******************************************************************************/


static void Brp_FlsAppInit(void)
{
    UINT32 return_code;           /* Return code from each SSD function. */
    UINT32 mcr_value;
    UINT32 blkLockState;
    UINT32 MCRAddress;            /* address of C55MCR register */

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

    Brp_FlsCopyRoutines();    /* Copy the flash drivers into RAM */

    /* copy the self erase function to RAM */
    (void)memcpy((void*)&__SLF_ERASE_FN_RAM_BASE, (void*)&__SLF_ERASE_CODE_ST, (UINT32)&__SLF_ERASE_CODE_SIZE);

    /* setup function pointer to the ram function */
    pBrp_SelfErase = (pBrp_SelfErase_Type) ((UINT32)&__SLF_ERASE_FN_RAM_BASE + ( (UINT32)&Brp_SelfErase     - (UINT32)&__SLF_ERASE_CODE_ST) ) ;

    /*========================= Initialize Part =========================*/

    /* set up function pointers in context data */
    pgmCtxData.pReqCompletionFn = pFlashProgram;
    bcCtxData.pReqCompletionFn  = pBlankCheck;
    pvCtxData.pReqCompletionFn  = pProgramVerify;

    return_code = pFlashInit( &ssdConfig );

    if (C55_OK != return_code)
    {
        Brp_FlsErrorTrap(return_code);
    }

    /*============== Lock to Protect UTest Address Space ===============*/

    return_code = pGetLock(&ssdConfig, C55_BLOCK_UTEST, &blkLockState);

    if (C55_OK != return_code)
    {
        Brp_FlsErrorTrap(return_code);
    }

    if (0U == (blkLockState & 0x00000001UL))
    {
        return_code = pSetLock(&ssdConfig, C55_BLOCK_UTEST, LOCK_ALL_BLOCKS);

        if (C55_OK != return_code)
        {
            Brp_FlsErrorTrap(return_code);
        }
    }
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Brp_EraseFlash

DESCRIPTION:
    - Ensures that the sector to be erased is unlocked
    - erase and verify the data

*******************************************************************************/

static UINT8 Brp_EraseFlash(UINT32 sector_addr)
{
    UINT8   erase_blk;
    UINT32  low_addr_space_enable     = 0;
    UINT32  mid_address_space_enable  = 0;
    UINT32  high_address_space_enable = 0;
    N256K_BLOCK_SEL n256KBlockSelect;
    UINT32  result;
    UINT32  opResult;

    UINT8   stat = FLS_FAIL;

    UINT32  failAddress;          /* save the failed address in flash */
    UINT32  failData;             /* save the failed data in flash */

    if(Brp_FlsGetFlashBlock(sector_addr, &erase_blk) == TRUE)
    {
        result = Brp_FlsSetBlkProtection(erase_blk, &low_addr_space_enable,
                                                    &mid_address_space_enable,
                                                    &high_address_space_enable,
                                                    &n256KBlockSelect);

        if(C55_OK == result)  /* if the unlocking has not failed ...*/
        {

            opResult = pFlashEraseAndCheck(&ssdConfig,
                                           C55_ERASE_MAIN,
                                           low_addr_space_enable,
                                           mid_address_space_enable,
                                           high_address_space_enable,
                                           n256KBlockSelect,
                                           &dummyCtxData);

            if(C55_OK == opResult)
            {
                result = pBlankCheck(&ssdConfig,
                                     Fls_Info[ erase_blk ].Start_Address,
                                     Fls_Info[ erase_blk ].Length,
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


                if ((C55_OK == result) && (C55_OK == opResult))
                {
                    stat = FLS_OK;
                }
            }
        }
    }

    return (stat);
}
/*****************************************************************************
                              FUNCTION INFO
NAME:
    Brp_ProgramFlash

DESCRIPTION:
    - Ensures that the sector to be programmed is unlocked
    - program and verify the data

*******************************************************************************/

static UINT8 Brp_ProgramFlash(UINT32 program_data, UINT32 target, UINT32 length)
{
    UINT8  return_status = FLS_FAIL;
    UINT8  prog_blk ;
    UINT32 return_code;
    UINT32 opResult;
    UINT32 low_addr_space_enable = 0;
    UINT32 mid_address_space_enable = 0;
    UINT32 high_address_space_enable = 0;
    N256K_BLOCK_SEL n256KBlockSelect;

    UINT32 failAddress;          /* save the failed address in flash */
    UINT32 failData;             /* save the failed data in flash */
    UINT32 failSource;           /* save the failed data in source buffer */

    if (Brp_FlsGetFlashBlock((UINT32)target, &prog_blk) == TRUE)
    {
        return_code = Brp_FlsSetBlkProtection(prog_blk, &low_addr_space_enable,
                                                        &mid_address_space_enable,
                                                        &high_address_space_enable,
                                                        &n256KBlockSelect);

        if(C55_OK == return_code)
        {

            opResult = pFlashProgramAndCheck(&ssdConfig,
                                             FALSE,
                                             (UINT32)target,
                                             length,
                                             (UINT32)program_data,
                                             &pgmCtxData);


            if(C55_OK == opResult)
            {
                /* Verify */
                return_code = pProgramVerify(&ssdConfig,
                                             (UINT32)target,        /* dest   */
                                             length,                /* size   */
                                             (UINT32)program_data,  /* source */
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

                if((C55_OK == return_code) && (C55_OK == opResult))
                {
                    return_status = FLS_OK;  /* Everything OK */
                }
            }
        }
    }

    return(return_status);
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Brp_ValidateBootImage

DESCRIPTION:
    Sums all the words(32bit) including the checksum word and checks
    if the result is 0xffffffff.

*******************************************************************************/

static UINT8 Brp_ValidateBootImage(void)
{

    BOOL status = BOOT_IMAGE_NOT_VALID;

    /*  DEVIATION:     0310, 0311
        DESCRIPTION:   Casting to different object pointer type (0310).
                       Dangerous pointer cast results in loss of const qualification (0311).
        JUSTIFICATION: This casting is required here and cannot be avoided.
                       It is analyzed and causes no issues. */
    /* PRQA S 0310 1*//* PRQA S 0311 1*/
    UINT32 *begin = (UINT32 *)Boot_Image;
    UINT32 len = Boot_Image_length/sizeof(UINT32);

    UINT32 *end;
    UINT32 sum = 0;

    /* DEVIATION:     0488
       DESCRIPTION:   Performing pointer arithmetic.
       JUSTIFICATION: Pointer arithmetic becomes necessary here. */
    /* PRQA S 0488 1 */
    end = (UINT32 *)(begin + len);


    while (begin < end)
    {
        /*  DEVIATION:     0489, 3440
            DESCRIPTION:   Null statement is located close to other code or comments (0523).
                           Increment or decrement operation performed on pointer (3440).
            JUSTIFICATION: Deviation necessary to allow generation of fast optimised code. */
        /* PRQA S 0489 01*//* PRQA S 3440 01*/
        sum += *begin++;
    }


    if (sum == 0xffffffffUL)
    {
        status = BOOT_IMAGE_VALID;
    }

    return(status);
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Brp_SelfErase

DESCRIPTION:
    This routine is the last one called by the boot replacer.
    This routine should be run from RAM as it tries to erase the
    boot replacer program from flash.
    Note that the block protection bits (to unlock the sector) should be appropriately set
    before calling this routine.
    This routine should be self contained and must not call any other
    routines  from flash.
    After erasing the boot replacer program( this also erases the load status),
    it performs a software reset.


*******************************************************************************/

/* should be Run fron RAM */
static void __attribute__((section (".slf_erase_fn"))) Brp_SelfErase(UINT32 low_addr_space_enable,
                                                                     UINT32 mid_address_space_enable,
                                                                     UINT32 high_address_space_enable,
                                                                     N256K_BLOCK_SEL n256KBlockSelect )
{
    UINT32 result;
    UINT32 opResult = C55_OK;

    /* This routine should be run from RAM.
    ** And there should not be any calls to functions  run from flash */
    /* Ensure that block protection is set appropriately before we enter this program */

    result = pFlashErase(&ssdConfig,
                         C55_ERASE_MAIN,
                         low_addr_space_enable,
                         mid_address_space_enable,
                         high_address_space_enable,
                         n256KBlockSelect);

    if (C55_OK == result)
    {
        /* Call FlashCheckStatus() to check status of the progress */
        while (C55_INPROGRESS == pFlashCheckStatus(&ssdConfig,
                                                   C55_MODE_OP_ERASE,
                                                   &opResult,
                                                   &dummyCtxData))
        {
            /* Add your code here */
        }
    }
    else
    {
        pFlashAbort(&ssdConfig);
    }

    if ((C55_OK == result) && (C55_OK == opResult))
    {
        /* Enter the RESET mode */
        MC_ME.MCTL.R = 0x00005AF0;                  /* Mode and Key */
        MC_ME.MCTL.R = 0x0000A50F;                  /* Mode and Key inverted */
    }

    while (1)
    {
        #ifdef POLYSPACE
        /* Polyspace throws NTL(non termination of loop) error if we use infinite 'while' loop.            */
        /* As this is an infinite 'while' loop  without any initialization and break condition statements  */
        /* to facilitate polyspace verification below code changes were done                               */
        volatile unsigned int exit_loop ;
        if(exit_loop == 0)
        {
            break ;
        }
        #endif
        ;                                           /* All we can do now is wait quietly */
    }
}

/*****************************************************************************
  Name:        FlashProgramAndCheck
  Description: Calls the pFlashProgram() function to Programme the specified
       source data into the specified destination FLASH area and then waits,
       checking the Flash status,  while the programming is carried out.
       Should the attempt to Programme the Flash return a failure then this
       programming of Flash is aborted and the function returns the error code.

  Note 1: flash programming, pFlashProgram(), is a non blocking function and
       so the function, pFlashCheckStatus(), is polled waiting for the completion
       of the programming action. The execution of this function is carried out in
       RAM while the FLASH is being updated.

  Note 2: it is intended that this function be copied to RAM and executed from
        RAM, especially if it is to update any part of its FLASH partition.

  Note 3: the functions [ pFlashProgram(), pFlashCheckStatus(), and pFlashAbort() ]
        called from this function are RAM functions and must be copied there before
        calling this function.

  Input:  pSSDConfig - Pointer to the SSD Configuration Structure.
          factoryPgmFlag - A flag indicate to do whether factory program or not.
          dest - Destination address to be programmed in flash memory.
          size - Size, in bytes, of the flash region to be programmed.
          source - Source program buffer address.
          pCtxData - Address of context data structure.

  Output: pCtxData - Address of context data structure.
  Return: opResult - Successful completion or error value.
******************************************************************************/

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
  Name:        FlashEraseAndCheck
  Description: Calls the pFlashErase() function to erase the specified blocks
       from the various Partitions and then waits, checking the Flash status,
       while the erasing is carried out. Should the erasing function return
       a failure then the erasing of Flash is aborted and this function
       returns the error code.

  Note 1: flash erase, pFlashErase(), is a non blocking function and so the
       function, pFlashCheckStatus(), is polled waiting for the completion of
       the erasing action. The execution of this function is carried out in
       RAM while the FLASH is being erased.

  Note 2: it is intended that this function be copied to RAM and executed from
       RAM, especially if it is to update any part of its FLASH partition.

  Note 3: the functions [ pFlashErase(), pFlashCheckStatus(), and pFlashAbort() ]
       called from this function are RAM functions and must be copied there
       before calling this function.

  Input: pSSDConfig - Pointer to the SSD Configuration Structure.
         eraseOption - The option is to select users expected erase operation.
         lowBlockSelect - To select the array blocks in low address space for erasing.
         midBlockSelect - To select the array blocks in mid address space for erasing.
         highBlockSelect - To select the array blocks in high address space for erasing.
         n256KBlockSelect - To select the array blocks in 256K address space for erasing.
                          It includes two elements to decode the first half of 256K block
                          select and the second half of 256K block select.
         pCtxData - Address of context data structure.

  Output: pCtxData - Address of context data structure.
  Return: opResult - Successful completion or error value.
******************************************************************************/

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

/*****************************************************************************
                              FUNCTION INFO
NAME:
    main

DESCRIPTION:
      This is the main routine used by the boot replacer.


*******************************************************************************/
int main(void)
{
    UINT8 status;

    UINT8 i;

    UINT32 enable_blocks[ FLS_NUM_ADDRESS_SPACES ];

    UINT8  addr_space1;
    UINT32 bit_mask1;
    UINT32 src;
    UINT32 loc_dest;
    UINT32 length;

    /* Since the boot replacer is only ever used with a boot present we can assume
       that the boot has already called the MCAL initialization and set the clock
       speed correctly. Therefore these do not need to be done again.
    */

    status = Brp_ValidateBootImage();

    /* Init Flash routines, copy routines to RAM */
    Brp_FlsAppInit();

    if(status == BOOT_IMAGE_VALID)
    {
        /* Erase the existing boot */
        status = Brp_EraseFlash((UINT32)__BOOT_CODE_START_ADDR);

        if(status == FLS_OK)
        {
            src    = (UINT32) &Boot_Image[8];
            loc_dest   = ((UINT32)&__BOOT_CODE_START_ADDR[2]);
            length = Boot_Image_length - 8U;

            status = Brp_FlsGetFlashBlock(loc_dest, &i);

            if( (status == TRUE)    &&
                ((length % 8U) == 0U) &&     /* length should be multiple of 8 */
                ((loc_dest % 8U) == 0U)  &&     /* destination addresses should be Dword aligned */
                ((src % 4U ) == 0U)  &&     /* source should be word aligned */
                ((loc_dest + length) <= (Fls_Info[i].Start_Address + Fls_Info[i].Length))  /* dest+length should be within the sector */
              )
            {
                (void)Brp_ProgramFlash(src, loc_dest, length);
            }

            src = (UINT32) &Boot_Image[0];
            loc_dest = ((UINT32)&__BOOT_CODE_START_ADDR[0]);
            length = 8;

            status = Brp_FlsGetFlashBlock(loc_dest, &i);

            if( (status == TRUE)    &&
                /* DEVIATION:     3355
                   DESCRIPTION:   The result of this logical operation is always 'true'.
                   JUSTIFICATION: Defensive coding. */
                /* PRQA S 3355 1 */
                ((length % 8U) == 0U) &&        /* length should be multiple of 8 */
                ((loc_dest % 8U) == 0U)  &&     /* destination addresses should be Dword aligned */
                ((src % 4U ) == 0U)  &&         /* source should be word aligned */
                ((loc_dest + length) <= (Fls_Info[i].Start_Address + Fls_Info[i].Length))  /* loc_dest+length should be within the sector */
              )
            {
                (void)Brp_ProgramFlash(src, loc_dest, length);
            }
        }
    }

    /* Erase the boot replacer program and reset */

    /* Stage1 : Erase the boot image */
    (void)Brp_EraseFlash((UINT32)&__BRP_BOOT_IMG_START_ADDR);

    /*  Stage2 : Erase the boot replacer code */
    /* set suitable locks for self erase */
    enable_blocks[ FLS_LOW_ADDRESS_SPACE ]      = 0;
    enable_blocks[ FLS_MID_ADDRESS_SPACE ]      = 0;
    enable_blocks[ FLS_HIGH_ADDRESS_SPACE ]     = 0;
    enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ] = 0;
    enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ] = 0;

    /* TODO: Need to put 2 sectors for Panther */
    status = Brp_FlsGetAddrSpaceAndBitMask((UINT32)&__BRP_START_ADDR, &addr_space1, &bit_mask1);

    if(status == TRUE)
    {
        N256K_BLOCK_SEL n256KBlockSelect;

        enable_blocks[ addr_space1 ] = (bit_mask1 );  /* Enable sector at 0x10000  */

        (void)Brp_FlsSetLocks(enable_blocks[ FLS_LOW_ADDRESS_SPACE ],
                        enable_blocks[ FLS_MID_ADDRESS_SPACE ],
                        enable_blocks[ FLS_HIGH_ADDRESS_SPACE ],
                        enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ],
                        enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ]);

        n256KBlockSelect.first256KBlockSelect  = enable_blocks[ FLS_256K_1ST_ADDRESS_SPACE ];
        n256KBlockSelect.second256KBlockSelect = enable_blocks[ FLS_256K_2ND_ADDRESS_SPACE ];

        /* call the function in RAM - It never returns because we no longer exist! */
        pBrp_SelfErase(enable_blocks[ FLS_LOW_ADDRESS_SPACE ],
                       enable_blocks[ FLS_MID_ADDRESS_SPACE ],
                       enable_blocks[ FLS_HIGH_ADDRESS_SPACE],
                       n256KBlockSelect );
    }

    return (0);                             /* To satisfy compiler warnings */
}


/*****************************************************************************/
/* Name:        Brp_FlsGetFlashBlock                                         */
/* Description: Get index to Flash Desc table from flash address             */
/* Input:       - flash address                                              */
/* Output:      - index to table                                             */
/* Return:      - address found TRUE/FALSE                                   */
/*****************************************************************************/
static BOOL Brp_FlsGetFlashBlock(UINT32 addr, UINT8 *index)
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
            programmable = TRUE;
            found = TRUE;
        }
    }
    return programmable;
}



static BOOL Brp_FlsGetAddrSpaceAndBitMask(UINT32 addr, UINT8* addr_space, UINT32* bit_mask )
{
    BOOL ret = FALSE;
    UINT8   index;

    if((Brp_FlsGetFlashBlock(addr, &index)) == TRUE)
    {
        /* get the required address space low, mid, high or 256k */
        *addr_space = (UINT8)Fls_Info[ index ].Address_Space;
        *bit_mask   = Fls_Info[ index ].Bit_Mapped_Block_Id;

        if(*addr_space < FLS_NUM_ADDRESS_SPACES)
        {
            ret = TRUE;
        }
    }

    return ret;
}


/*****************************************************************************/
/* Name:        Brp_FlsSetLocks                                              */
/* Description:                                                              */
/*        Sets locks for the blocks as specified in the bit mapped           */
/*        inputs low_addr_space_blk_state,mid_addr_space_blk_state and       */
/*        high_addr_space_blk_state                                          */
/*                                                                           */
/* Input:                                                                    */
/*      low_addr_space_blk_state - bit mapped block state;                   */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      mid_addr_space_blk_state - bit mapped block state;                   */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*      high_addr_space_blk_state - bit mapped block state;                  */
/*                            1=unlock; 0= lock; bit0=block0,bit1=block1 etc */
/*                                                                           */
/* Output:      - lock status                                                */
/*****************************************************************************/

static UINT32 Brp_FlsSetLocks(UINT32 low_addr_space_blk_state,
                              UINT32 mid_addr_space_blk_state,
                              UINT32 high_addr_space_blk_state,
                              UINT32 n256k_1st_addr_space_blk_state,
                              UINT32 n256k_2nd_addr_space_blk_state)
{
    UINT32 return_code ;

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
/* FUNCTION: Brp_FlsSetBlkProtection                                         */
/*                                                                           */
/* PARAMETERS: block id (a number between 0 and  FLS_MAX_SECTORS)            */
/*                                                                           */
/* DESCRIPTION:                                                              */
/*         Obtains the bit pattern required to unlock only the               */
/*         required block and to lock all other blocks.                      */
/*                                                                           */
/* RETURNS:                                                                  */
/*    Returns the bit patern for the low,mid and high address spaces         */
/*    and the status.                                                        */
/*                                                                           */
/*****************************************************************************/


static UINT32 Brp_FlsSetBlkProtection(UINT8 block_id,
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

        return_code = Brp_FlsSetLocks(enable_blocks[ FLS_LOW_ADDRESS_SPACE ],
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



static void Brp_FlsErrorTrap(UINT32 return_code)
{
    while(1)
    {
        #ifdef POLYSPACE
        /* Polyspace throws NTL(non termination of loop) error if we use infinite 'while' loop            */
        /* As this is an infinite 'while' loop  without any initialization and break condition statements */
        /* to facilitate polyspace verification below code changes were done                              */
        volatile unsigned int exit_loop ;
        if(exit_loop == 0)
        {
            break ;
        }
        #endif
    }
}
