/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: main.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:14CST $

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


  /*  DEVIATION:     0303
      DESCRIPTION:   Cast between a pointer to volatile object and an integral type.
      JUSTIFICATION: Some addresses which are integer are cast to pointers to obtain
                     information which is stored under them.
  */
  /* PRQA S 0303 ++ */

  /*  DEVIATION:     3138
      DESCRIPTION:   Null statement is located close to other code or comments.
      JUSTIFICATION: Here are used some defines which are converted into ASM code.
  */
  /* PRQA S 3138 ++ */


/***************************************************************************/

#define MAIN_

#include "types.h"
#include "Mcu_dch.h"
#include "can.h"
#include "bootstrp.h"  /* for T_REPROG_INFO_TYPE */
#include "ccppar.h"
#include "ccp.h"
#include "can_cfg.h"
#include "flsh_int.h"
/* MCAL Includes */
#include "port.h"
#include "dio.h"
#include "mcu.h"
#include "FCCU.h"
#include "MEMU.h"
#include "StdRegMacros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_FlexCan.h"
#include "comms.h"
#include "uds_prog.h" /* To access UDS_DiagServiceHandler() */


/*==================================================================================================
                            FLEXCAN Register Access Macros
==================================================================================================*/
/*  DEVIATION:      3453
    DESCRIPTION:    A function could probably be used instead of this function-like macro.
    JUSTIFICATION:  These macros were previously (in K0) defined in MCAL\Core\Reg_eSys_FlexCan.h
*/
/* PRQA S 3453 2 */
#define FLEXCAN_MCR_CONFIG( offset, value)  (REG_WRITE32( FLEXCAN_MCR(offset), (uint32)(value)))
#define FLEXCAN_MCR_READ(offset)  (REG_READ32( FLEXCAN_MCR(offset)))



#define FES_FCCU_HARD_MASK  0x00000020
/* #define FES_SWT_MASK        0x0100 */
/* #define FES_FCCU_SAFE_MASK  0x0080 */

/******************************************************************************
* GLOBAL CONSTANTS
******************************************************************************/

/* DEVIATION: 3447
   DESCRIPTION: '?' is being declared with external linkage but this declaration is not in a header file
   JUSTIFICATION: For some reason, FreeScale have not provided these declarations in a header file. When the Mcal C files
                  need to use these variables they declare them directly, just like this
*/
/* PRQA S 3447 11 */
#ifdef MCU_PRECOMPILE_SUPPORT
/** @violates @ref Mcu_c_REF_7 MISRA 2004 Required Rule 8.7, object defined external because of autosar*/
extern CONST(Mcu_ConfigType, MCU_CONST) Mcu_Config_PC;
#endif


/* CAN Controller Message Buffer and Individual Mask Register RAM */
#define NUMBER_OF_USED_CAN_PORTS    2U                /* Only CAN0 and CAN1 is used in Radar project */
#define SIZE_OF_MB_RAM              0x400U            /* MB RAM size is 64*16 bytes */
#define SIZE_OF_IMR_RAM             0x100U            /* IMR RAM size is 64*4 bytes */
#define SIZE_OF_WORD                4U                /* Word-size equals 4 bytes   */
#define NUMBER_OF_STEPS             3U                /* First write 0x55555555 to RAM, Second write 0x55555555 to RAM, Third set all bytes to 0xFF */
#define FIRST_PATTERN               0
#define SECOND_PATTERN              1U
#define THIRD_PATTERN               2U
#define NUMBER_OF_RAM_BLOCKS        2U                /* Number of RAM blocks per CAN. There are two blocks per CAN, MB (1024 bytes) and IMR (256 bytes) */

#define SUPPRESS_MASK               0xFEFFFFFFU       /* Used to suppress bits in read/write test */

/******************************************************************************
* Prototypes
******************************************************************************/

/* DEVIATION: 3408
   DESCRIPTION: %s' has external linkage and is being defined without any previous declaration..
   JUSTIFICATION: Set_ECC_Vector is declared in crts0.asm but no .h file exists for this
*/
/* PRQA S 3408 2 */
void Set_ECC_Vector(void);

static void PROG_Main (void);
static void CAN_RAM_Test(void);


/********************************************************************************/
/*  Main Program                                                                */
/********************************************************************************/
int main(void)
{
    Set_ECC_Vector();

    /* Start the loop task */
    PROG_Main();

    return (0);     /* To satisfy compiler warnings */
}


/*********************************************************************************/
/* Name: PROG_Main                                                               */
/*-------------------------------------------------------------------------------*/
/* Description:                                                                  */
/*********************************************************************************/
/* Input parameters          : None                                              */
/* Output parameters         : None                                              */
/* Return value              : None                                              */
/*-------------------------------------------------------------------------------*/
/* Used public variables     : None                                              */
/* Modified public variables : None                                              */
/*-------------------------------------------------------------------------------*/
/* Used private variables    : None                                              */
/* Modified private variables: None                                              */
/*-------------------------------------------------------------------------------*/
/* Called functions          : None                                              */
/* Called macros             : None                                              */
/* Called callbacks          : None                                              */
/*********************************************************************************/
static void PROG_Main (void)
{
    /* DEVIATION: 3138 - globally disabled */
    DisableAllInterrupts();

    /* Clear the MEMU Error Reporting Tables (used for ECC) */
    MEMU_Clear_Err_Tables();

    /* Check FCCU for latched faults which trigger reset */
    FCCU_Check_Reset_Reason();

    /* Initialise the FCCU Non-Critical Fault behaviour */
    FCCU_Init();

    /* Switch the processor out of SAFE mode, into DRUN mode */
    /* SwitchToDrunMode(); */

    /* Setup the MCU clocks and modes */
    /* MC_MODE_INIT(); */

    Mcu_Init(&Mcu_Config_PC);

    (void)Mcu_InitClock(McuClockSettingConfig);

    /* Wait till PLL lock */
    while(Mcu_GetPllStatus() != MCU_PLL_LOCKED)
    {
    }

    Mcu_DistributePllClock();

    /* Setup ports */
    Port_Init(&Port_ConfigPC);

    /* Perform CAN controller health check */
    CAN_RAM_Test();

    Can_Init(&Can_ConfigSet_PC);            /* setup CAN */

    (void)Can_SetControllerMode(CanConf_CanController_CanController_0,CAN_T_START); /* enable controller 0 */
    (void)Can_SetControllerMode(CanConf_CanController_CanController_1,CAN_T_START); /* enable controller 1 */

    Mcu_Init_PWM();

    /* Initialise the interrupts to start the timers, but don't enable them until after checking other apps */
    Mcu_Init_Ints();

    /* Check the boot pin / CAN and reprogramming status - NOTE this needs the timers running */
    Bstrp_Bootstrap();

    Comms_Init();



    Mcu_Init_ADC();


    /* DEVIATION: 3138 - globally disabled */
    EnableAllInterrupts();

    FlsAppInit();

    (void)ccpHandleReprogRequest(&Reprog_Info);/* Continue the CCP dialogue that was established in the main application...*/


    if(System_Dld_Reason == (U8)SYS_REPROG_REQUEST_UDS)
    {
        UDS_progSessionStart();
    }
    #ifndef POLYSPACE
    while (TRUE)
    {
    #else
    /* Polyspace throws NTL(non termination of loop) error if we use infinite 'while' loop.                                                     */
    /* As we have an infinite 'While' loop  without any initialization and break condition statements in the below mentioned code,              */
    /* to facilitate  polyspace verification the following changes were done. Here below functions are called in 'for' loop for multiple times. */
    int i;
    for(i=0;i<1000;i++)
    {
    #endif
        basic_scheduler();

        Can_MainFunction_Read();

        Can_MainFunction_Write();/* invokes tx confirmation fn and other call back functions in the can interface */

        FlsMonitorDownloadComplete();
    }
}
/* - End PROG_Main                                                               */
/*-------------------------------------------------------------------------------*/

/*********************************************************************************/
/* Name: CAN_RAM_Test                                                            */
/*-------------------------------------------------------------------------------*/
/* Description:This function is used to test condition of CAN driver internal RAM*/
/*********************************************************************************/
/* Input parameters          : None                                              */
/* Output parameters         : None                                              */
/* Return value              : None                                              */
/*-------------------------------------------------------------------------------*/
/* Used public variables     : None                                              */
/* Modified public variables : None                                              */
/*-------------------------------------------------------------------------------*/
/* Used private variables    : None                                              */
/* Modified private variables: None                                              */
/*-------------------------------------------------------------------------------*/
/* Called functions          : Send_hardware_fault()                             */
/* Called macros             : None                                              */
/* Called callbacks          : None                                              */
/*********************************************************************************/
static void CAN_RAM_Test(void)
{
    const uint8_t  canPortNumber_au8 [NUMBER_OF_USED_CAN_PORTS] =
    {
        0,    /* '0' means MCR register for CAN0 */
        1U    /* '1' means MCR register for CAN1 */
    };

    const uint32_t canPortBaseAddr_u32[NUMBER_OF_USED_CAN_PORTS] =
    {
        (uint32_t)FLEXCAN0_BASEADDR,
        (uint32_t)FLEXCAN1_BASEADDR
    };

    uint8_t  canIndex_u8;
    uint8_t  testIndex_u8;
    uint8_t  ramIndex_u8;
    uint16_t wordIndex_u16;
    uint16_t numberOfWords_u16;
    uint16_t numberOfErrors_u16 = 0;
    uint32_t canTimeoutCount_u32;
    uint32_t pattern_u32;
    uint32_t wr_pattern_u32;
    uint32_t saveMcrStateCAN0_u32;
    uint32_t saveMcrStateCAN1_u32;
    uint32_t flexCan_baseaddr;
    uint32_t *baseAddress_pu32;
    volatile uint32_t *targetAddress_pu32;

    /* Remember the last state of MCR register (CAN0 and CAN1) */
    /* Deviation 0303 - globally disabled */
    saveMcrStateCAN0_u32 = (uint32)FLEXCAN_MCR_READ(canPortNumber_au8[0]);
    /* Deviation 0303 - globally disabled */
    saveMcrStateCAN1_u32 = (uint32)FLEXCAN_MCR_READ(canPortNumber_au8[1]);

    /* Enable FlexCAN0 and set it in Freeze mode; Setting AEN supposedly aids readback of BUSY bit... */
    /* Deviation 0303 - globally disabled */
    FLEXCAN_MCR_CONFIG( canPortNumber_au8[0], (uint32)(FLEXCAN_MCR_FRZ_U32 | FLEXCAN_MCR_HALT_U32 | FLEXCAN_MCR_AEN_U32 | FLEXCAN_MCR_BCC_U32));
    canTimeoutCount_u32 = (uint32)CAN_TIMEOUT_DURATION;

    /* Wait until FRZACK bit is set */
    /* Deviation 0303 - globally disabled */
    while ( (FLEXCAN_MCR_FRZACK_U32 != ((uint32)FLEXCAN_MCR_READ(canPortNumber_au8[0]) & FLEXCAN_MCR_FRZACK_U32)) &&
            (canTimeoutCount_u32 > (uint32)0x0) )
    {
        /* MCR[FRZ_ACK] still not set -> controller freeze is in-progress. */
        canTimeoutCount_u32--;
    }

    /* Enable FlexCAN1 and set it in Freeze mode */
    /* Deviation 0303 - globally disabled */
    FLEXCAN_MCR_CONFIG( canPortNumber_au8[1], (uint32)(FLEXCAN_MCR_FRZ_U32 | FLEXCAN_MCR_HALT_U32 | FLEXCAN_MCR_AEN_U32 | FLEXCAN_MCR_BCC_U32));
    canTimeoutCount_u32 = (uint32)CAN_TIMEOUT_DURATION;

    /* Wait until FRZACK bit is set */
    /* Deviation 0303 - globally disabled */
    while ( (FLEXCAN_MCR_FRZACK_U32 != ((uint32)FLEXCAN_MCR_READ(canPortNumber_au8[1]) & FLEXCAN_MCR_FRZACK_U32)) &&
            (canTimeoutCount_u32 > (uint32)0x0) )
    {
        /* MCR[FRZ_ACK] still not set -> controller freeze is in-progress. */
        canTimeoutCount_u32--;
    }

    /* Loop to perform test on used CAN ports */
    for(canIndex_u8 = 0U; canIndex_u8 < NUMBER_OF_USED_CAN_PORTS; canIndex_u8++)
    {
        flexCan_baseaddr = canPortBaseAddr_u32[canIndex_u8];

        for(ramIndex_u8=0; ramIndex_u8 < NUMBER_OF_RAM_BLOCKS;ramIndex_u8++)
        {
            if(0 == ramIndex_u8)
            {
                /*  DEVIATION:     0306
                    DESCRIPTION:   Cast between a pointer to object and an integral type.
                    JUSTIFICATION: Need to obtain actually baseAddress.
                */
                /* PRQA S 0306 1 */
                baseAddress_pu32 = (uint32_t *)(flexCan_baseaddr + (uint32_t)FLEXCAN_MB_OFFSET_U32);
                numberOfWords_u16 = (SIZE_OF_MB_RAM/SIZE_OF_WORD);
            }
            else
            {
                /*  DEVIATION:     0306
                    DESCRIPTION:   Cast between a pointer to object and an integral type.
                    JUSTIFICATION: Need to obtain actually baseAddress.
                */
                /* PRQA S 0306 1 */
                baseAddress_pu32 = (uint32_t *)(flexCan_baseaddr + (uint32_t)FLEXCAN_RXIMR_OFFSET_U32);
                numberOfWords_u16 = (SIZE_OF_IMR_RAM/SIZE_OF_WORD);
            }

            for(testIndex_u8=0; testIndex_u8 < NUMBER_OF_STEPS; testIndex_u8++)
            {
                switch (testIndex_u8)
                {
                    case FIRST_PATTERN:
                    {
                        pattern_u32 = 0x55555555UL;                          /* First pattern to write into CAN RAM */
                        break;
                    }
                    case SECOND_PATTERN:
                    {
                        pattern_u32 = 0xAAAAAAAAUL;                          /* Second pattern to write into CAN RAM */
                        break;
                    }
                    case THIRD_PATTERN:
                    default:
                    {
                        pattern_u32 = 0x00000000UL;                          /* Default pattern to write into CAN after tests */
                        break;
                    }
                }
                targetAddress_pu32 = baseAddress_pu32;

                /* Write the test pattern */
                for(wordIndex_u16=0; wordIndex_u16 < numberOfWords_u16; wordIndex_u16++)
                {
                    /* Don't set Message Buffer 0x0 Bit<7> (CODE 0) to avoid uncertain operation */
                    if ((ramIndex_u8 == 0U) && ((wordIndex_u16 % 4U) == 0U))
                    {
                        wr_pattern_u32 = pattern_u32 & SUPPRESS_MASK;
                    }
                    else
                    {
                        wr_pattern_u32 = pattern_u32;
                    }
                    /*  DEVIATION:     0310
                    DESCRIPTION:   Cast between a pointer to object and an integral type.
                    JUSTIFICATION: There are used two forms (uint32_t and uint32). One
                                   of them is unsigned int and second one is unsigned long.
                                   In this case it doesn't matter.
                    */
                    /* PRQA S 0310 1 */
                    REG_WRITE32(targetAddress_pu32, wr_pattern_u32);
                    /*  DEVIATION:     0489
                    DESCRIPTION:   Increment or decrement operation performed on pointer.
                    JUSTIFICATION: It's the only way to skip through addresses.
                    */
                    /* PRQA S 0489 1 */
                    targetAddress_pu32++;    /*489*/
                }

                /* Readback test, not performed on final step */
                if((NUMBER_OF_STEPS-1U) != testIndex_u8)
                {
                    targetAddress_pu32 = baseAddress_pu32;

                    for(wordIndex_u16=0; wordIndex_u16 < numberOfWords_u16; wordIndex_u16++)
                    {
                        /* Ignore readback of each Message Buffer 0x0 Bit<7> (CODE 0) due to uncertain operation */
                        if ((ramIndex_u8 == 0U) && ((wordIndex_u16 % 4U) == 0U))
                        {
                            /*  DEVIATION:     0310
                                DESCRIPTION:   Cast between a pointer to object and an integral type.
                                JUSTIFICATION: There are used two forms (uint32_t and uint32). One
                                               of them is unsigned int and second one is unsigned long.
                                               In this case it doesn't matter.
                            */
                            /* PRQA S 0310 1 */
                            if((REG_READ32(targetAddress_pu32) & SUPPRESS_MASK) != (pattern_u32 & SUPPRESS_MASK))
                            {
                                numberOfErrors_u16 ++;
                            }
                        }
                        else
                        {
                            /* Standard readback check */
                            /* PRQA S 0310 1 */
                            if(REG_READ32(targetAddress_pu32) != pattern_u32)
                            {
                                numberOfErrors_u16 ++;
                            }

                        }

                        /*  DEVIATION:     0489
                            DESCRIPTION:   Increment or decrement operation performed on pointer.
                            JUSTIFICATION: It's the only way to skip through addresses.
                        */
                        /* PRQA S 0489 1 */
                        targetAddress_pu32++;
                    }
                }
            }
        }
    }
    /* Restore previous (read at start of the function) configuration of MSR register */
    /* Deviation 0303 - globally disabled */
    FLEXCAN_MCR_CONFIG( canPortNumber_au8[0], (uint32)saveMcrStateCAN0_u32);
    /* Deviation 0303 - globally disabled */
    FLEXCAN_MCR_CONFIG( canPortNumber_au8[1], (uint32)saveMcrStateCAN1_u32);

    /* If CAN RAM fault detected, fault shall be reported */
    if(0 != numberOfErrors_u16)
    {
        Send_hardware_fault(4);             /* This never returns */
    }

}
/* - End CAN_RAM_Test                                                               */
/*-------------------------------------------------------------------------------*/

/* PRQA S 3138 -- */
/* PRQA S 0303 -- */
