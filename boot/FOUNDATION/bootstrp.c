/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: bootstrp.c $
        $Revision: 1.2 $
        $Date: 2019/08/21 18:17:20CST $

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

/* DEVIATION:     0310
   DESCRIPTION:   Casting to different object pointer type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0310 ++ */

/* DEVIATION:     0306
   DESCRIPTION:   Cast between a pointer to object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0306 ++ */

/*  DEVIATION:     3440
    DESCRIPTION:   Result of ++ or -- operator used in expression.
    JUSTIFICATION: These operators are use to change indicated place in memory.

*/
/* PRQA S 3440 ++ */

/*  DEVIATION:     0489
    DESCRIPTION:   Increment or decrement operation performed on pointer.
    JUSTIFICATION: To change indicated address we use pointer arithmetic.
*/
/* PRQA S 0489 ++ */

/***************************************************************************/

#include "MPC5744P.h"
#include "types.h"
#include "bootstrp.h"
#include "Mcu.h"
#include "Mcu_dch.h"


/*****************************************************************************
*
*   PRIVATE VARIABLE DECLARATIONS
*
******************************************************************************/


#define BSTRAP_READ_LOAD_STATUS()           (*__LOAD_STATUS)
#define SYS_BOOT_RUNNING                    1U

U8  System_Dld_Reason  = (U8)SYS_DOWNLOAD_REASON_UNKNOWN;
U8  Suppres_Ctr_Bit = 0;

/*****************************************************************************
*   Local Prorotypes
******************************************************************************/
static U8  Bstrp_GetBootPin(void);
static void Bstrp_LoadProgram(U8 programme);
static void Bstrp_HandleBootPinAndLoadStatus(void);

/*****************************************************************************
*
*   CODE
*
******************************************************************************/

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_InitReprogInfo

DESCRIPTION:
     Initialises the 'Reprog_Info' structure to a known state

*******************************************************************************/

void Bstrp_InitReprogInfo(void)
{
    Reprog_Info.ccp_ctr           = 0;
    Reprog_Info.ccp_erase_address = 0;
    Reprog_Info.ccp_erase_size    = 0;

    Reprog_Info.reprog_req_status = REPROG_REQUEST_INIT_VALUE;
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_GetBootPin

DESCRIPTION:
     Returns 1 if the Application should be run or 0 to stay in boot mode.
     (For B2.1 hardware this is the opposite of the boot pin value).

*******************************************************************************/
static U8  Bstrp_GetBootPin(void)
{
    U32 bp_time;
    U8 bp_ret;

    /* If the boot pin / pad is high stay in boot mode */
    if (IO_READ_BOOT_PIN() != IO_LOW)
    {
        bp_ret = 0U;
    }
    else
    {   /* Some radars do not have a boot pin.  Look for a CAN dominant on both CAN buses for 10ms. */
        /* If both CAN inputs are continuously dominant for at least 10ms stay in boot mode */
        bp_ret = 0U;
        bp_time = Mcu_Get_Tick_Count();
        while (((Mcu_Get_Tick_Count() - bp_time) < (TICKS_PER_MICROSECOND * 10000U)) && (bp_ret == 0U))
        {
            if (IO_READ_CAN_0_RX() != IO_LOW)
            {
                bp_ret = 1U;
            }
            if (IO_READ_CAN_1_RX() != IO_LOW)
            {
                bp_ret = 1U;
            }
        }
    }
    return (bp_ret);
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_LoadProgram

ARGUMENTS:
    PROG_BRP_CODE to call the BRP code or PROG_APPLICATION
    to call the application checksum.

DESCRIPTION:
    Routine to invoke either the main application or a BRP code
    The argument specifies which to run, an unrecognised argument is
    ignored and the function returns.

*******************************************************************************/

static void Bstrp_LoadProgram(U8 programme)
{
    if (PROG_BRP_CODE == programme)
    {
        /*  DEVIATION:     3138
            DESCRIPTION:   Null statement is located close to other code or comments.
            JUSTIFICATION: DisableAllInterrupts is a macro which contains assembler code. QAC has been setup to not see assembler so it is wrongly seeing this macro as empty.
        */
        /* PRQA S 3138 7 */
        DisableAllInterrupts();
        Mcu_Reset_Ints();
        __BRP_STARTUP_ADDR();
    }
    else if(PROG_APPLICATION == programme)
    {
        DisableAllInterrupts();
        Mcu_Reset_Ints();

        /* check the checksum and run it. */
        /*  DEVIATION:     0488
            DESCRIPTION:   Performing pointer arithmetic.
            JUSTIFICATION: To change indicated address we use pointer arithmetic.
        */
        /* PRQA S 0488 1 */
        if(  Bstrp_CalcChecksum(PROG_APPLICATION) == ~(*((volatile U32 *) ((U8 *) __APP_CRC))))
        {
            /* Read through the APV sector and Load_status. This will check for ECC errors in these areas */
            Bstrp_ECC_APV_LS_AreaCheck();

            /* Run main application */
            __APPS_STARTUP_ADDR();
        }
    }
    else
    {
        ;
    }
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_HandleBootPinAndLoadStatus

DESCRIPTION:
    This routine decides if the control needs to stay in the boot or
    to load the main application or a BRP code. Boot pin state and
    the load status value are used as inputs.

*******************************************************************************/

static void Bstrp_HandleBootPinAndLoadStatus(void)
{
    volatile U64 load_status;

    if(Bstrp_GetBootPin() != 0U)
    {
        /* boot pin not active */
        load_status = BSTRAP_READ_LOAD_STATUS();

        if (load_status == SYS_LOAD_STATUS_MAIN_APP_VALID)
        {
            Bstrp_LoadProgram(PROG_APPLICATION);  /* no return */
        }
        else
        {
            if ((load_status == SYS_LOAD_STATUS_BRP_VALID) &&
                (*__BRP_CODE_SIGN_ADDR == (U32)0x7E57C0DE))
            {
                /* valid BRP code checksum and signature. */
                Bstrp_LoadProgram(PROG_BRP_CODE);  /* no return */
            }
            else
            {
                /* Do not know what the load status is set to. Stay in the boot*/
                System_Dld_Reason = (U8)SYS_NO_VALID_APP;
            }
        }
    }
    else
    {
        /* Boot pin is active. Stay in the boot */
        System_Dld_Reason = (U8)SYS_BOOT_PIN_ACTIVE;
    }
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_Bootstrap

DESCRIPTION:
    This is the main bootstrap routine.
    This program reads the reason that caused the reset and decides if it is a
    valid re-programming request.
    If it is not a software interrupt, then the shared information RAM area
    had to be initialised here as it would not have been initialised before.

*******************************************************************************/

void Bstrp_Bootstrap(void)
{
    Mcu_ResetType reset_reason;

    reset_reason = Mcu_GetResetReason();

    /*  DCH - 29-8-14 - MCAL 0.9.1 does not clear all of the reset flags when Mcu_GetResetReason() is called.
        This means that other reset flags may still be set in the event of a software reset.  I.e. a
        re-programming request from an application.  Therefore Mcu_GetResetReason() may not return MCU_SOFT_FUNC_RESET
        and the boot will do a full reset rather than clearing a sector as required.
        To prevent this all of the reset flags are cleared here.
    */
    Mcu_Clear_Reset_Flags();

    if (MCU_SOFT_FUNC_RESET == reset_reason)
    {
        /* Software reset! */

        /* We can read the shared info area as it should have been initialized
           either in the main application or in the previous call to the boot! and so
           it should not generate any ECC errors!! */

        /* 1. Could be a reprogramming request from CCP or  => Need to stay in the boot!!
           2. reset after the re-prog has been completed or
           3. a reset to restore default apvs
           4. reset from some other program like boot replacer
         */

        if (REPROG_REQUEST_CCP == Reprog_Info.reprog_req_status)
        {
            System_Dld_Reason = (U8)SYS_REPROG_REQUEST_CCP;
        }
        else if (REPROG_REQUEST_UDS == Reprog_Info.reprog_req_status)
        {
            System_Dld_Reason = (U8)SYS_REPROG_REQUEST_UDS;
            Suppres_Ctr_Bit = Reprog_Info.ccp_ctr;
        }
        else
        {
            /* Do not know the reason for the sw reset */

            /* Handle boot pin and load status */
            Bstrp_HandleBootPinAndLoadStatus();
        }
        /* stay in the boot for reprogramming */
    }
    else
    {
        /* Not a software reset. Could be a power on reset or external reset on the ICE */
        /* initialize the shared info area to avoid ECC errors */
        Bstrp_InitReprogInfo();

        /* Handle boot pin and load status */
        Bstrp_HandleBootPinAndLoadStatus();
    }
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_CalcChecksum

ARGUMENTS:
    PROG_BRP_CODE to calculate the BRP code checksum or PROG_APPLICATION
    to calculate the application checksum.

DESCRIPTION:
    Calculate the Checksum value for App code or BRP Code.
    The argument specifies which to calculate, an unrecognised argument is
    ignored and the function returns a non-zero value.

*******************************************************************************/

U32 Bstrp_CalcChecksum(U8 programme)
{
    U32     checksum = 0, *start, *end;
    U32     calculated_checksum;
    BOOLEAN invalid_programme = FALSE;

    switch (programme)
    {
    case PROG_BRP_CODE:

        start = __START_BRP_CODE;
        end   = __END_BRP_CODE;
        break;

    case PROG_APPLICATION:

        start = __START_APP_CODE;
        end   = __END_APP_CODE;
        break;

    default:
        invalid_programme = TRUE;
        break;
    }

    if (invalid_programme == TRUE)
    {
        calculated_checksum = 1;
    }
    else
    {
        /*  DEVIATION:     3347
            DESCRIPTION:   The variable 'start' (and 'end') is apparently unset at this point.
            JUSTIFICATION: From the logic above it can be seen that this condition is not possible.
        */
        /* PRQA S 3347 1 */
        while (start <= end)
        {
            checksum += *start;
            start++;
        }
        calculated_checksum = ~checksum;
    }

    return calculated_checksum;
}

/*****************************************************************************
                              FUNCTION INFO
NAME:
    Bstrp_ECC_APV_LS_AreaCheck

ARGUMENTS:

DESCRIPTION:
    We need to read every byte in three areas of flash

    1. The APV data content
    2. The APV_FLASH_CONTROL_DATA
    3. Load_status

    If an ECC error is encountered then an interrupt is generated and will be handled elsewhere.

*******************************************************************************/

void Bstrp_ECC_APV_LS_AreaCheck(void)
{
    U32  *start;
    U32  *end;
    volatile U32 currentRead;

    /* Read the APV data content (don't bother if the APV flash sector is invalid) */
    /*  DEVIATION:     0308
        DESCRIPTION:   Non-portable cast involving pointer to an incomplete type.
        JUSTIFICATION: Warning occurs as __APV_FLASH_SECTOR_STATUS_ADDR is defined as extern in the header
         file and not defined anywhere in the code as it gets defined by the linker. Hence
         this is an incomplete type and it is cast as a U8 pointer. But this cannot be avoided
         as addresses get defined only in the linker stage*/
    /* PRQA S 0308 20*/
    /* Deviation 0310 - globally disabled */
    /* Deviation 0306 - globally disabled */
    if ( *((U32 *)&__APV_FLASH_SECTOR_STATUS_ADDR) != 0xFFFFFFFFUL)
    {
        /* Read from start to the end of the APV data area */
        start = (U32 *)(__APV_FLASH_DATA_START_ADDR);
        end   = (U32 *)((U32)start + (U32)(*((U16*)&__APV_FLASH_CONTENT_SIZE_ADDR)));

        while (start < end)
        {
            /* DEVIATION: 3440, 0489 - globally disabled */
            currentRead = *start++;
        }
    }

    /* Read the APV_FLASH_CONTROL_DATA area */
    /* Deviation 0310 - globally disabled */
    start = (U32 *)(&__APV_FLASH_SECTOR_STATUS_ADDR);
    /* Deviation 0306 - globally disabled */
    end   = (U32 *)((U32)start + APV_FLASH_CONTROL_DATA_SIZE);

    while (start < end)
    {
        /* DEVIATION: 3440, 0489 - globally disabled */
        currentRead = *start++;
    }

    /* Read the Load_status location */
    /* Read the APV data content (don't bother if the APV flash sector is invalid) */
    /*  DEVIATION:     0308
        DESCRIPTION:   Non-portable cast involving pointer to an incomplete type.
        JUSTIFICATION: Warning occurs as __LOAD_STATUS is defined as extern in the header
         file and not defined anywhere in the code as it gets defined by the linker. Hence
         this is an incomplete type and it is cast as a U8 pointer. But this cannot be avoided
         as addresses get defined only in the linker stage*/
    /* PRQA S 0308 20*/
    /* Deviation 0310 - globally disabled */
    start = (U32 *)(&__LOAD_STATUS);
    end   = (U32 *)((U32)start + 8UL);

    while (start < end)
    {
        /* DEVIATION: 3440, 0489 - globally disabled */
        currentRead = *start++;
    }

}

/* PRQA S 0310 -- */
/* PRQA S 0306 -- */
/* PRQA S 3440 -- */
/* PRQA S 0489 -- */
