/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: FCCU.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:08CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

/**********************************/
/* GLOBAL QAC WARNING SUPPRESSION */
/**********************************/

    /*  DEVIATION:     0303
        DESCRIPTION:   Cast between a pointer to volatile object and an integral type
        JUSTIFICATION: We are accessing memory mapped variables in the Mcal layer. QAC reports this as a portability issue.
                       In this case, that is not a problem because the Mcal is specific to the hardware and will never be ported to a different hardware.*/
    /* PRQA S 0303 EOF */

/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

#define FCCU_                    /*  defines this file */
#define FOUNDATION_SUBSYSTEM     /*  defines the subsystem that this file resides in */

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#include "../FOUNDATION/types.h"
#include "../FOUNDATION/mpc5744p.h"
#include "../FOUNDATION/fccu.h"

/*************************************************************/
/*      GLOBAL VARIABLES                                     */
/*************************************************************/

/* ##########################################################*/

/*
** FCCU State definitions (FCCU_STAT Register)
*/
#define FCCU_STATE_NORMAL       0x00U
#define FCCU_STATE_CONFIG       0x01U
#define FCCU_STATE_ALARM        0x02U
#define FCCU_STATE_FAULT        0x03U

/*
** FCCU Operation status (OPS) definitions (FCCU_CTRL Register)
*/
#define FCCU_OPS_IN_IDLE        0x00
#define FCCU_OPS_IN_PROGRESS    0x01
#define FCCU_OPS_ABORTED        0x02
#define FCCU_OPS_SUCCESSFUL     0x03U

/*
** FCCU Operation run (OPR) definitions (FCCU_CTRL Register)
*/
#define FCCU_OPR_SET_CONFIG         0x01U
#define FCCU_OPR_SET_NORMAL         0x02U
#define FCCU_OPR_READ_FCCU_STATE    0x03U
#define FCCU_OPR_READ_N2AF_STATUS   0x04U
#define FCCU_OPR_READ_A2FF_STATUS   0x05U
#define FCCU_OPR_READ_N2FF_STATUS   0x06U
#define FCCU_OPR_READ_F2AF_STATUS   0x07U
#define FCCU_OPR_READ_NCF_STATUS    0x0AU

#define FCCU_CTRL_OPR0      0x00000000U   /* 00000: No operation [OP0]    */
#define FCCU_CTRL_OPR1      0x00000001U   /* 00001: Set the FCCU into the CONFIG state [OP1] */
#define FCCU_CTRL_OPR2      0x00000002U   /* 00010: Set the FCCU into the NORMAL state [OP2] */
#define FCCU_CTRL_OPR3      0x00000003U   /* 00011: Read the FCCU state (refer to the FCCU_STAT register) [OP3] */
#define FCCU_CTRL_OPR4      0x00000004U   /* 00100: Read the FCCU frozen status flags (refer to the FCCU_NAFS register) [OP4] */
#define FCCU_CTRL_OPR5      0x00000005U   /* 00101: Read the FCCU frozen status flags (refer to the FCCU_AFFS register) [OP5] */
#define FCCU_CTRL_OPR6      0x00000006U   /* 00110: Read the FCCU frozen status flags (refer to the FCCU_NFFS register) [OP6] */
#define FCCU_CTRL_OPR7      0x00000007U   /* 00111: Read the FCCU frozen status flags (refer to the FCCU_FAFS register) [OP7] */
#define FCCU_CTRL_OPR8      0x00000008U   /* 01000: Read the FCCU frozen status flags (refer to the FCCU_SCFS register) [OP8] */
#define FCCU_CTRL_OPR9      0x00000009U   /* 01001: Read the CF status register (refer to the FCCU_CFS register) [OP9] */
#define FCCU_CTRL_OPR10     0x0000000AU   /* 01010: Read the NCF status register (refer to the FCCU_NCFS register) [OP10] */
#define FCCU_CTRL_OPR11     0x0000000BU   /* 01011: CF status clear operation in progress (refer to the FCCU_CFS register) [OP11] */
#define FCCU_CTRL_OPR12     0x0000000CU   /* 01100: NCF status clear operation in progress (refer to the FCCU_NCFS register) [OP12] */
#define FCCU_CTRL_OPR13     0x0000000DU   /* 01101: Clear the freeze status registers (refer to the freeze registers) [OP13] */
#define FCCU_CTRL_OPR14     0x0000000EU   /* 01110: CONFIG to NORMAL FCCU state (configuration timeout) in progress [OP14] */
#define FCCU_CTRL_OPR15     0x0000000FU   /* 01111: Clear the operation status (OPS=Idle, NVML=0) [OP15] */
#define FCCU_CTRL_OPR16     0x00000010U   /* 10000: Lock the FCCU configuration [OP16] */
#define FCCU_CTRL_OPR17     0x00000011U   /* 10001: Read the ALARM timer (refer to the FCCU_XTMR register) [OP17] */
#define FCCU_CTRL_OPR18     0x00000012U   /* 10010: Read the SMRT timer (refer to the FCCU_XTMR register) [OP18] */
#define FCCU_CTRL_OPR19     0x00000013U   /* 10011: Read the CFG timer (refer to the FCCU_XTMR register) [OP19] */
                                            /* 10100 - 11111: RESERVED [OP20-OP30] */
#define FCCU_CTRL_OPR31     0x0000001FU   /* 11111: Run the NVM loading operation (only for test purposes) [OP31] */

/*
** Keys for Operations (FCCU_CTRLK Register)
*/
#define FCCU_CTRLK_OP1      0x913756AFUL    /* = 913756AFh: Key for the operation OP1 */
#define FCCU_CTRLK_OP2      0x825A132BUL    /* = 825A132Bh: Key for the operation OP2 */
#define FCCU_CTRLK_OP16     0x7ACB32F0UL    /* = 7ACB32F0h: Key for the operation OP16 */
#define FCCU_CTRLK_OP31     0x29AF8752UL    /* = 29AF8752h: Key for the operation OP31 */

/*
** Key access to clear the NCF (Non-Critical Fault) status flags (FCCU_NCFK Register)
*/
#define FCCU_NCFK_KEY       0xAB3498FEUL

/*
** Defines for NCF Status Registers
*/

#define FCCU_NCF_S0         0U   /* NCFS[31:0]   */
#define FCCU_NCF_S1         1U   /* NCFS[63:32]  */
#define FCCU_NCF_S2         2U   /* NCFS[95:64]  */
#define FCCU_NCF_MAX_REG    3U

#define FCCU_NCF_CLEAR_ALL  0xFFFFFFFFU

/*
** Definitions of NCFs that are configured to trigger a reset
*/
#define FCCU_NCF0_MASK_SWT      0x00004000U /* NCF 14 */
#define FCCU_NCF0_MASK_RAMECC   0x00010000U /* NCF 16 */

#define FCCU_NCF1_MASK_SAFETY   0x00001000U /* NCF 44 */
#define FCCU_NCF1_MASK_LOCKSTEP 0x00002000U /* NCF 45 */


/**
 * @description     Read the current FCCU State
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - Content of the FCCU_STAT Register
 */
static U32 FCCU_Read_FCCU_State(void);

/**
 * @description     Read the FCCU frozen status flags
 * @param[in]       parameters
 * @param[in]       None
 * @param[in]       N2AF_status_pu32 - Content of the N2AF_STATUS Register
 *                  A2FF_status_pu32 - Content of the A2FF_STATUS Register
 *                  N2FF_status_pu32 - Content of the N2FF_STATUS Register
 *                  F2AF_status_pu32 - Content of the F2AF_STATUS Register
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static void FCCU_Read_Frozen_Status_Flags(U32 *N2AF_status_pu32, U32 *A2FF_status_pu32, U32 *N2FF_status_pu32, U32 *F2AF_status_pu32);

/**
 * @description     Read the Non-Critical Fault (NCF) Status Register
 * @param[in]       parameters
 * @param[in]       NCFx_Reg_u8 - NCF Status Register : Range 0-2
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - Content of the NCF_S[x] Register
 */
static U32 FCCU_Read_NCFx_Status(U8 NCFx_Reg_u8);

/**
 * @description     Read the Non-Critical Fault (NCF) Status Registers [0 to 2]
 * @param[in]       parameters
 * @param[in]       None
 * @param[in]       NCF0_status_pu32 - Content of the NCF_S[0] Register
 *                  NCF1_status_pu32 - Content of the NCF_S[1] Register
 *                  NCF2_status_pu32 - Content of the NCF_S[2] Register
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static void FCCU_Read_NCFx_Status_Flags(U32 *NCF0_status_pu32, U32 *NCF1_status_pu32, U32 *NCF2_status_pu32);

/**
 * @description     Clear the Fault in the NCF_S[x] Register
 * @param[in]       parameters
 * @param[in]       NCFx_Reg_u8   - NCF Status Register : Range 0-2
 *                  NCFx_Mask_u32 - NCF Mask for Fault Clearing
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static void FCCU_Clear_NCFx_Status(U8 NCFx_Reg_u8, U32 NCFx_Mask_u32);

/**
 * @description     Clear the Fault in the NCF_S[x] Registers [0 to 2]
 * @param[in]       parameters
 * @param[in]       NCF0_status_u32 - Current value of NCF_S[0] Register
 *                  NCF1_status_u32 - Current value of NCF_S[1] Register
 *                  NCF2_status_u32 - Current value of NCF_S[2] Register
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */

static void FCCU_Clear_NCFx_Status_Flags(U32 NCF0_status_u32, U32 NCF1_status_u32, U32 NCF2_status_u32);

/**
 * @description     Transition the FCCU into the CONFIG state
 *                  NOTE: Can only access CONFIG mode from NORMAL mode
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static U32 FCCU_Enter_CONFIG_State(void);

/**
 * @description     Transition the FCCU into the NORMAL state
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static void FCCU_Enter_NORMAL_State(void);

/**
 * @description     Configure the FCCU for how it should handle NCFs
 *                  - SWT configured to trigger reset : NCF[14]
 *                  - Uncorrectable ECC Errors in SYS and PERIPH RAM are configured
 *                  to trigger reset : NCF[16] and NCF[19]
 *                  - Uncorrectable ECC Errors in FLASH are configured to
 *                  trigger NMI (IVOR1) : NCF[22]
 *                  - All correctable ECC Errors are configured to trigger IRQ 448
 *                  into the INTC : NCF[15], NCF[18] and NCF[21]
 *                  - All MEMU ECC Overflow Error Conditions are configured to
 *                  perform no action : NCF[17], NCF[20] and NCF[23]
 *                  - Safety Core Exception configured to trigger reset : NCF[44]
 *                  - Lockstep error configured to trigger reset : NCF[45]
 *                  After configuration FCCU is locked from changes until reset
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
static void FCCU_Configure(void);

/* ##########################################################*/


/*************************************************************/
/*      CODE                                                 */
/*************************************************************/

/*********************************************************************************/
/* Name: FCCU_Init                                                               */
/*-------------------------------------------------------------------------------*/
/* Description:  Sets up the FCCU for ECC errors and SWT                         */
/*               NCF[14] - Software Watchdog                                     */
/*               NCF[15] - System RAM correctable ECC                            */
/*               NCF[16] - System RAM uncorrectable ECC                          */
/*               NCF[17] - System RAM overflow                                   */
/*               NCF[18] - Peripheral RAM correctable ECC                        */
/*               NCF[19] - Peripheral RAM uncorrectable ECC                      */
/*               NCF[20] - Peripheral RAM overflow                               */
/*               NCF[21] - Flash correctable ECC                                 */
/*               NCF[22] - Flash uncorrectable ECC                               */
/*               NCF[23] - Flash RAM overflow                                    */
/*               NCF[44] - Safety Core Exception                                 */
/*               NCF[45] - Lockstep Error                                        */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void FCCU_Init(void)
{
    U32 fccu_status_u32;
    U32 NCF0_status_u32;
    U32 NCF1_status_u32;
    U32 NCF2_status_u32;
    U32 N2AF_status_u32;
    U32 A2FF_status_u32;
    U32 N2FF_status_u32;
    U32 F2AF_status_u32;
    U32 op_status_u32;

    /*
    ** DCH - Turn off reset escalation
    */
    MC_RGM.FRET.R = 0;                      /*???? Turn this off for debug to keep the radar from entering permanent reset. */
    MC_RGM.DRET.R = 0;                      /*???? Turn this off for debug to keep the radar from entering permanent reset. */
    MC_RGM.FESS.R = 0x0180046d;             /* Set short functional resets to turn off the BIST to get round the BIST XOSC / PLL bug. */

    PMC.CTL_TD.R = 0x303;                   /* Enable Temperature sensor outputs */

    /*
    ** Read the current FCCU state
    */
    fccu_status_u32 = FCCU_Read_FCCU_State();
    /*
    ** If FCCU is in ALARM or FAULT state we need to
    ** clear the NCF/s to transition back to NORMAL state
    */
    if ((FCCU_STATE_FAULT == fccu_status_u32) ||
        (FCCU_STATE_ALARM == fccu_status_u32))
    {
        /*
        ** Read the FCCU frozen status flag registers
        */
        FCCU_Read_Frozen_Status_Flags(&N2AF_status_u32, &A2FF_status_u32,
                                      &N2FF_status_u32, &F2AF_status_u32);

        /*
        ** Read the NCFx Status Registers
        */
        FCCU_Read_NCFx_Status_Flags(&NCF0_status_u32, &NCF1_status_u32, &NCF2_status_u32);

        /*
        ** NOTE:  Cut 1:  We get a NCF[9] BIST fault on startup
        **        Need to clear all faults to allow entry to CONFIG mode.
        */
        FCCU_Clear_NCFx_Status_Flags(FCCU_NCF_CLEAR_ALL, FCCU_NCF_CLEAR_ALL, FCCU_NCF_CLEAR_ALL);

        /*
        ** Read the NCFx Status Registers
        */
        FCCU_Read_NCFx_Status_Flags(&NCF0_status_u32, &NCF1_status_u32, &NCF2_status_u32);
    }

    /*
    ** Read the current FCCU state to ensure that we are in NORMAL mode
    */
    fccu_status_u32 = FCCU_Read_FCCU_State();

    /*
    ** Transition the FCCU into the CONFIG state in
    ** order to make configuration changes
    */
    op_status_u32 = FCCU_Enter_CONFIG_State();

    if (FCCU_OPS_SUCCESSFUL == op_status_u32)
    {
        /*
        ** Read the current FCCU state to ensure that we are in CONFIG mode
        */
        fccu_status_u32 = FCCU_Read_FCCU_State();

        if (FCCU_STATE_CONFIG == fccu_status_u32)
        {
            /*
            ** Now make FCCU configuration changes
            */
            FCCU_Configure();

            /*
            ** Transition the FCCU back into the NORMAL state
            */
            FCCU_Enter_NORMAL_State();

            /*
            ** Read the current FCCU state to ensure that we are in NORMAL mode
            */
            fccu_status_u32 = FCCU_Read_FCCU_State();
        }
    }
}


/*********************************************************************************/
/* Name: FCCU_Read_FCCU_State                                                    */
/*-------------------------------------------------------------------------------*/
/* Description:  Read the current FCCU State                                     */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : Content of the FCCU_STAT Register                        */
/*********************************************************************************/

static U32 FCCU_Read_FCCU_State(void)
{
    U32 fccu_state_u32;

    /* Write the operation to allow read of the current FCCU state */
    FCCU.CTRL.B.OPR = FCCU_OPR_READ_FCCU_STATE;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    /* Read the current FCCU state */
    fccu_state_u32 = FCCU.STAT.B.STATUS;

    return fccu_state_u32;
}


/*********************************************************************************/
/* Name: FCCU_Read_Frozen_Status_Flags                                           */
/*-------------------------------------------------------------------------------*/
/* Description:  Read the FCCU frozen status flags                               */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : N2AF_status_pu32 - Content of the N2AF_STATUS Register   */
/*                      A2FF_status_pu32 - Content of the A2FF_STATUS Register   */
/*                      N2FF_status_pu32 - Content of the N2FF_STATUS Register   */
/*                      F2AF_status_pu32 - Content of the F2AF_STATUS Register   */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Read_Frozen_Status_Flags(U32 *N2AF_status_pu32, U32 *A2FF_status_pu32,
                                   U32 *N2FF_status_pu32, U32 *F2AF_status_pu32)
{
    /* OP Read the FCCU frozen status flag N2AF_STATUS */
    FCCU.CTRL.B.OPR = FCCU_OPR_READ_N2AF_STATUS;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    /* Read NORMAL to ALARM freeze status */
    if (NULL != N2AF_status_pu32)
    {
        *N2AF_status_pu32 = FCCU.N2AF_STATUS.R;
    }


    /* OP Read the FCCU frozen status flag A2FF_STATUS */
    FCCU.CTRL.B.OPR = FCCU_OPR_READ_A2FF_STATUS;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    /* Read ALARM to FAULT freeze status */
    if (NULL != A2FF_status_pu32)
    {
        *A2FF_status_pu32 = FCCU.A2FF_STATUS.R;
    }


    /* OP Read the FCCU frozen status flag N2FF_STATUS */
    FCCU.CTRL.B.OPR = FCCU_OPR_READ_N2FF_STATUS;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    /* Read NORMAL to FAULT freeze status */
    if (NULL != N2FF_status_pu32)
    {
        *N2FF_status_pu32 = FCCU.N2FF_STATUS.R;
    }

    /* OP Read the FCCU frozen status flag F2AF_STATUS */
    FCCU.CTRL.B.OPR = FCCU_OPR_READ_F2AF_STATUS;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    /* Read FAULT to ALARM freeze status */
    if (NULL != F2AF_status_pu32)
    {
        *F2AF_status_pu32 = FCCU.N2FF_STATUS.R;
    }
}


/*********************************************************************************/
/* Name: FCCU_Read_NCFx_Status                                                   */
/*-------------------------------------------------------------------------------*/
/* Description:  Read the Non-Critical Fault (NCF) Status Register               */
/*********************************************************************************/
/* Input parameters   : NCFx_Reg_u8 - NCF Status Register : Range 0-2            */
/* Output parameters  : None                                                     */
/* Return value       : Content of the NCF_S[x] Register                         */
/*********************************************************************************/

static U32 FCCU_Read_NCFx_Status(U8 NCFx_Reg_u8)
{
    U32 NCF_status_u8 = 0;

    if (NCFx_Reg_u8 < FCCU_NCF_MAX_REG)
    {
        /* OP Read NCF status */
        FCCU.CTRL.B.OPR = FCCU_OPR_READ_NCF_STATUS;

        /* Wait for operation to complete */
        while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
        {
        }

        /* Read NCFx status */
        NCF_status_u8 = FCCU.NCF_S[NCFx_Reg_u8].R;
    }

    return (NCF_status_u8);
}


/*********************************************************************************/
/* Name: FCCU_Read_NCFx_Status_Flags                                             */
/*-------------------------------------------------------------------------------*/
/* Description:  Read the Non-Critical Fault (NCF) Status Registers [0 to 3]     */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : NCF0_status_pu32 - Content of the NCF_S[0] Register      */
/*                      NCF1_status_pu32 - Content of the NCF_S[1] Register      */
/*                      NCF2_status_pu32 - Content of the NCF_S[2] Register      */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Read_NCFx_Status_Flags(U32 *NCF0_status_pu32, U32 *NCF1_status_pu32, U32 *NCF2_status_pu32)
{
    if (NULL != NCF0_status_pu32)
    {
        *NCF0_status_pu32 = FCCU_Read_NCFx_Status(FCCU_NCF_S0);
    }

    if (NULL != NCF1_status_pu32)
    {
        *NCF1_status_pu32 = FCCU_Read_NCFx_Status(FCCU_NCF_S1);
    }

    if (NULL != NCF2_status_pu32)
    {
        *NCF2_status_pu32 = FCCU_Read_NCFx_Status(FCCU_NCF_S2);
    }

}


/*********************************************************************************/
/* Name: FCCU_Clear_NCFx_Status                                                  */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the Fault in the NCF_S[x] Register                        */
/*********************************************************************************/
/* Input parameters   : NCFx_Reg_u8   - NCF Status Register : Range 0-3          */
/*                      NCFx_Mask_u32 - NCF Mask for Fault Clearing              */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Clear_NCFx_Status(U8 NCFx_Reg_u8, U32 NCFx_Mask_u32)
{
    if (NCFx_Reg_u8 < FCCU_NCF_MAX_REG)
    {
        /*
        ** If there are any NCFs present in the mask then clear them
        */
        if (0U != NCFx_Mask_u32)
        {
            /* Write key into the FCCU_NCFK register */
            FCCU.NCFK.R = FCCU_NCFK_KEY;

            /* Clear Fault in the NCFx Status Register */
            FCCU.NCF_S[NCFx_Reg_u8].R = NCFx_Mask_u32;

            /* Wait for operation to complete */
            while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
            {
            }
        }
    }
}


/*********************************************************************************/
/* Name: FCCU_Clear_NCFx_Status_Flags                                            */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the Fault in the NCF_S[x] Registers [0 to 3]              */
/*********************************************************************************/
/* Input parameters   : NCF0_status_u32 - Current value of NCF_S[0] Register     */
/*                      NCF1_status_u32 - Current value of NCF_S[1] Register     */
/*                      NCF2_status_u32 - Current value of NCF_S[2] Register     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Clear_NCFx_Status_Flags(U32 NCF0_status_u32, U32 NCF1_status_u32, U32 NCF2_status_u32)
{
    FCCU_Clear_NCFx_Status(FCCU_NCF_S0, NCF0_status_u32);
    FCCU_Clear_NCFx_Status(FCCU_NCF_S1, NCF1_status_u32);
    FCCU_Clear_NCFx_Status(FCCU_NCF_S2, NCF2_status_u32);
}


/*********************************************************************************/
/* Name: FCCU_Enter_CONFIG_State                                                 */
/*-------------------------------------------------------------------------------*/
/* Description:  Transition the FCCU into the CONFIG state                       */
/*               NOTE: Can only access CONFIG mode from NORMAL mode              */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

static U32 FCCU_Enter_CONFIG_State(void)
{
    U32 op_status_u32;

    /* Remove Transient Lock, needed to enter CONFIG state */
    FCCU.TRANS_LOCK.R = 0xBC;

    /* Extend CONFIG watchdog timeout to maximum */
    FCCU.CFG_TO.R = 0x7;

    /* Key to allow access to CONFIG state */
    FCCU.CTRLK.R = FCCU_CTRLK_OP1;

    /* OP to set the FCCU into the CONFIG state (OP1) */
    FCCU.CTRL.R = FCCU_CTRL_OPR1;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }

    op_status_u32 = FCCU.CTRL.B.OPS;

    return (op_status_u32);
}


/*********************************************************************************/
/* Name: FCCU_Enter_NORMAL_State                                                 */
/*-------------------------------------------------------------------------------*/
/* Description:  Transition the FCCU into the NORMAL state                       */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Enter_NORMAL_State(void)
{
    /* Key to allow access to NORMAL state */
    FCCU.CTRLK.R = FCCU_CTRLK_OP2;

    /* OP to set the FCCU into the NORMAL state (OP2) */
    FCCU.CTRL.R = FCCU_CTRL_OPR2;

    /* Wait for operation to complete */
    while(FCCU.CTRL.B.OPS == FCCU_OPS_IN_PROGRESS)
    {
    }
}


/*********************************************************************************/
/* Name: FCCU_Configure                                                          */
/*-------------------------------------------------------------------------------*/
/* Description:  Configure the FCCU for how it should handle NCFs                */
/*               - SWT configured to trigger reset : NCF[14]                     */
/*               - Uncorrectable ECC Errors in SYS and PERIPH RAM are configured */
/*                 to trigger reset : NCF[16] and NCF[19]                        */
/*               - Uncorrectable ECC Errors in FLASH are configured to           */
/*                 trigger NMI (IVOR1) : NCF[22]                                 */
/*               - All correctable ECC Errors are configured to trigger IRQ 448  */
/*                 into the INTC : NCF[15], NCF[18] and NCF[21]                  */
/*               - All MEMU ECC Overflow Error Conditions are configured to      */
/*                 perform no action : NCF[17], NCF[20] and NCF[23]              */
/*               - Safety Core Exception configured to trigger reset : NCF[44]   */
/*               - Lockstep error configured to trigger reset : NCF[45]          */
/*               After configuration FCCU is locked from changes until reset     */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

static void FCCU_Configure(void)
{
    /* Clear FCCU.NCF_Es Register for the new Config */
    FCCU.NCF_E[0].R = 0x00000000;
    FCCU.NCF_E[1].R = 0x00000000;
    FCCU.NCF_E[2].R = 0x00000000;


    FCCU.NCF_E[0].R |= 0x00004000U;   /* Enable NCF 14*/
    FCCU.NCF_E[1].R |= 0x00002000U;   /* Enable NCF 45 */

    /*
    ** Configure NCF 14 (SWT) to trigger short functional reset
    ** Configure NCF 45 (Lockstep) to trigger short functional reset
    */
    FCCU.NCFS_CFG[0].B.NCFSC14 = 1; /* NCF 14 */
    FCCU.NCFS_CFG[2].B.NCFSC13 = 1; /* NCF 45 */


    /* Clear FCCU.NMI_ENs Register for the new Config */
    FCCU.NMI_EN[0].R = 0x00000000;
    FCCU.NMI_EN[1].R = 0x00000000;
    FCCU.NMI_EN[2].R = 0x00000000;

    /*
    ** Lock the FCCU from further configuration until reset
    */
    FCCU.PERMNT_LOCK.B.PERMNTKEY = 0xFF;   /* Lock FCCU Configuration until reset */
}

/*********************************************************************************/
/* Name: FCCU_Check_Reset_Reason                                                 */
/*-------------------------------------------------------------------------------*/
/* Description:  Check the FCCU for NCFs that trigger a reset.                   */
/*               Copy to shared structure in RAM for APP to log them to NVM      */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void FCCU_Check_Reset_Reason(void)
{
    U32 NCF0_status_u32;
    U32 NCF1_status_u32;

    Reset_Info.rgm_fes         = MC_RGM.FES.R;
    Reset_Info.Critical_Faults = 0;

    /*
    ** Copy the latched faults to the shared structure
    ** so the APP can examine them.
    */
    NCF0_status_u32 = FCCU_Read_NCFx_Status(FCCU_NCF_S0);

    if ((NCF0_status_u32 & FCCU_NCF0_MASK_SWT) != 0UL)
    {
        Reset_Info.Critical_Faults |= SWT_CRITICAL_FAULT_MASK;
    }

    if ((NCF0_status_u32 & FCCU_NCF0_MASK_RAMECC) != 0UL)
    {
        Reset_Info.Critical_Faults |= RAMECC_CRITICAL_FAULT_MASK;
    }

    NCF1_status_u32 = FCCU_Read_NCFx_Status(FCCU_NCF_S1);

    if ((NCF1_status_u32 & FCCU_NCF1_MASK_SAFETY) != 0UL)
    {
        Reset_Info.Critical_Faults |= SAFETY_CORE_CRITICAL_FAULT_MASK;
    }

    if ((NCF1_status_u32 & FCCU_NCF1_MASK_LOCKSTEP) != 0UL)
    {
        Reset_Info.Critical_Faults |= LOCKSTEP_CRITICAL_FAULT_MASK;
    }
}

