/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: mcu_init.c $
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
/* DEVIATION:     0303
   DESCRIPTION:   Cast between a pointer to volatile object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0303 EOF */

/***************************************************************************/


/*****************************************************************************/
/* FILE NAME: mcu_init.c                       COPYRIGHT (c) Freescale 2012  */
/*                                                      All Rights Reserved  */
/* DESCRIPTION: Provides functions to Initilise MPC5744P MCU                 */
/*                                                                           */
/*****************************************************************************/

#include "MPC5744P.h"

static void PLL_sys(void);
static void PLL_PD_Pulse(void);
static void PLL1_PD_Pulse(void);


/******************** Configure the Mode and Clock Tree **********************/
/* DEVIATION: 3408
   DESCRIPTION: 'MC_MODE_INIT' has external linkage but is being defined without any previous declaration.
   JUSTIFICATION: Currently 'MC_MODE_INIT' is not used.
*/
/* PRQA S 3408 1 */
void MC_MODE_INIT(void)
{
    /*
    ** 21 - STOP0 mode enabled
    ** 23 - HALT0 mode enabled
    ** 24 - RUN3 mode enabled
    ** 25 - RUN2 mode enabled
    ** 26 - RUN1 mode enabled
    ** 27 - RUN0 mode enabled
    ** 28 - DRUN mode enabled
    ** 29 - SAFE mode enabled
    ** 30 - TEST mode enabled
    ** 31 - 'functional' RESET mode enabled
    */
    MC_ME.ME.R = 0x000005FF;

    /* Setting RUN Configuration Register ME_RUN_PC[0] */
    MC_ME.RUN_PC[0].R = 0x000000FE; /* Peripheral ON in every mode */

    XOSC.CTL.B.OSCM = 1;    /* loop controlled pierce oscillator mode */
    XOSC.CTL.B.EOCV = 0x80; /* stabilization counter */ /* End of Count Value -> EOCVx512 */

    /* target mode RUN0 */
    MC_ME.MCTL.R = 0x40005AF0;     /* Mode & Key */
    MC_ME.MCTL.R = 0x4000A50F;     /* Mode & Key inverted */

    MC_ME.RUN_MC[0].B.XOSCON = 1;   /* Enable the 40 MHz crystal oscillator in RUN0 mode */
    MC_ME.DRUN_MC.B.XOSCON   = 1;   /* Enable the 40 MHz crystal oscillator in DRUN mode */

    /* RE enter the drun mode, to update the configuration */
    /* target mode DRUN */
    MC_ME.MCTL.R = 0x30005AF0;      /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;      /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }
    while(MC_ME.GS.B.S_XOSC == 0)                /* Wait for clock to stabilise */
    {
    }

    /* Configure CLK_OUT */
    SIUL2.MSCR[22].R = 0x22800001;  /* Set port pin B[6] as CLK_OUT */

    MC_CGM.AC6_SC.B.SELCTL = 1;     /* Select 40MHz XOSC as source for Aux clock select 6 */
    MC_CGM.AC6_DC0.R = 0x80030000U;  /* Enable Divider & div by 4 */

    /* Check CLK_OUT 10MHz here */
    MC_CGM.AC0_SC.B.SELCTL = 2;     /* source AC0 is PLL0 PHI */
    MC_CGM.AC0_DC0.R = 0x80000000U;  /* Aux clock select 0 divider 0 --> div by 1 (MOTC_CLK) */
    MC_CGM.AC0_DC1.R = 0x80070000U;  /* Aux clock select 0 divider 1 --> div by 8 (SWG_CLK) */
    MC_CGM.AC0_DC2.R = 0x80010000U;  /* Aux clock select 0 divider 2 --> div by 2 (ADC_CLK) */

    MC_CGM.AC1_DC0.R = 0x80010000U;  /* Aux clock select 1 divider 0 --> div by 2 (FRAY_PLL_CLK) */
    MC_CGM.AC1_DC1.R = 0x80030000U;  /* Aux clock select 1 divider 1 --> div by 4 (SENT_CLK) */

    MC_CGM.AC2_DC0.R = 0x80070000U;  /* Aux clock select 2 divider 0 --> div by 8 (CAN_PLL_CLK) */

    MC_CGM.PCS_SDUR.R = 0xFF;       /* Configure Switch Duration */

    MC_ME.DRUN_MC.B.SYSCLK = 1;     /* Select system clock as 40MHz XOSC */

    /* target mode DRUN */
    MC_ME.MCTL.R = 0x30005AF0;      /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;      /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }
    while(MC_ME.GS.B.S_SYSCLK != 1)          /* fail is stuck here */
    {
    }

    PLL_sys();
}


static void PLL_sys(void)
{
    MC_CGM.PCS_SDUR.R = 0xFF;       /* Configure Switch Duration */

    MC_ME.DRUN_MC.B.SYSCLK = 1;      /* Select system clock as 40MHz XOSC */

    /* target mode DRUN */
    MC_ME.MCTL.R = 0x30005AF0;       /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;       /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }
    while(MC_ME.GS.B.S_SYSCLK != 1)          /* fail is stuck here   */
    {
    }

    MC_CGM.AC3_SC.B.SELCTL = 1;     /* Select XOSC as PLL0 ref */
    MC_CGM.AC4_SC.B.SELCTL = 1;     /* Select XOSC as PLL1 ref */

    MC_CGM.AC6_SC.R  = 0x02000000;  /* Select PLL0 PHI as source for Aux clock select 6 - CLK_OUT */
    MC_CGM.AC6_DC0.R = 0x80000000U;  /* Enable Divider & div by 1 */

    /*
    ** fPLL0_PHI = fPLL0_ref x PLL0DV[MFD] / (PLL0DV[PREDIV] x PLL0DV[RFDPHI]
    **           = 40MHz x 32 / (4 x 2)
    **           = 160MHz
    */
    PLLDIG.PLL0DV.B.RFDPHI1 = 15;
    PLLDIG.PLL0DV.B.RFDPHI  = 2;
    PLLDIG.PLL0DV.B.PREDIV  = 4;
    PLLDIG.PLL0DV.B.MFD     = 32;  /* The multiplication factor applied to ref frequency */

    /* PLL power cycle pulse and wait for PLL lock */
    PLL_PD_Pulse();

    /* Check CLK_OUT 160MHz here */
    MC_ME.DRUN_MC.B.SYSCLK = 2;      /* Select system clock as PLL0 PHI */

    /* target mode DRUN */
    MC_ME.MCTL.R = 0x30005AF0;       /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;       /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }
    while(MC_ME.GS.B.S_SYSCLK != 2)          /* fail is stuck here   */
    {
    }


    MC_CGM.SC_DC0.R = 0x80030000U;   /* Sys clock select divider 0 --> div by 4 (PBRIDGEx_CLK) */

    MC_CGM.AC6_SC.R  = 0x04000000;  /* Select PLL1 PHI as source for Aux clock select 6 - CLK_OUT */
    MC_CGM.AC6_DC0.R = 0x80000000U;  /* Enable Divider & div by 1 */


    /*
    ** fpll1_phi = fpll1_ref * PLL1DV[MFD] / PLL1DV[RFDPHI]
    ** fpll1_phi = 40MHz * 36 / (8)  = 180MHz
    */

    PLLDIG.PLL1DV.B.RFDPHI = 4; /* div by 8 */
    PLLDIG.PLL1DV.B.MFD    = 36;

    PLL1_PD_Pulse();

    /* Check CLK_OUT 180MHz here */

    MC_ME.DRUN_MC.B.SYSCLK = 4;      /* Select system clock as PLL1 PHI */

    /* target mode DRUN */
    MC_ME.MCTL.R = 0x30005AF0;       /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;       /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }
    while(MC_ME.GS.B.S_SYSCLK != 4)          /* fail is stuck here   */
    {
    }
}

static void PLL_PD_Pulse(void)
{
    MC_ME.DRUN_MC.B.PLL0ON = 0;  /* Disable the PLL0 */

    /* RE enter the drun mode, to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;               /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;               /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }

    MC_ME.DRUN_MC.B.PLL0ON = 1;  /* Enable the PLL0 */

    /* RE enter the drun mode, to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;                /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)           /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)   /* Check DRUN mode has been entered */
    {
    }

    /* waiting for PLL0 to lock */
    while(PLLDIG.PLL0SR.B.LOCK == 0)
    {
    }
}

static void PLL1_PD_Pulse(void)
{
    MC_ME.DRUN_MC.B.PLL1ON = 0;     /* Disable the PLL1 */

    /* RE enter the drun mode, to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;                /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)           /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)   /* Check DRUN mode has been entered */
    {
    }

    MC_ME.DRUN_MC.B.PLL1ON = 1;     /* Enable the PLL1 */

    /* RE enter the drun mode, to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;               /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;               /* Mode & Key inverted */

    while(MC_ME.GS.B.S_MTRANS == 1)          /* Wait for mode entry to complete */
    {
    }
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3)  /* Check DRUN mode has been entered */
    {
    }

    /* waiting for PLL1 to lock */
    while(PLLDIG.PLL1SR.B.LOCK == 0)
    {
    }
}

