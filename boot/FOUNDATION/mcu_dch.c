/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: mcu_dch.c $
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
    /* DEVIATION: 0303
       DESCRIPTION: Cast between a pointer to volatile object and an integral type.
       JUSTIFICATION: Deviation due to the use of a standard header file.
    */
    /* PRQA S 0303 ++ */


/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#include "types.h"
#include "MPC5744P.h"
#include "mcu_dch.h"

/*************************************************************/
/*      GLOBAL VARIABLES                                     */
/*************************************************************/

#define COUNTER_FOR_TASK_1MS    1U
#define PSU_SYNC_PERIOD (COUNTS_PER_MICROSECOND)    /* PSU sync period (counts) = 1.0us */

U8 ubCntTaskScheduler = 0;
BOOLEAN ubTaskScheduler = FALSE;


/*************************************************************/
/*      CODE                                                 */
/*************************************************************/

/*========================================================================*/
/*                      GLOBAL VARIABLES                                  */
/*========================================================================*/

/*========================================================================*/
/*                      EXTERNAL PROTOTYPES                               */
/*========================================================================*/

/*========================================================================*/
/*                          FUNCTIONS                                     */
/*========================================================================*/

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Init_Ints                                             */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Set up the interrupt system.  Uses software vector mode.  Vector table  */
/*  is in vecter.c                                                          */
/****************************************************************************/
void Mcu_Init_Ints(void)
{
    /* Initialize interrupt controller (INTC) */
    INTC_0.BCR.R = 0;                       /* Software vector mode */
    INTC_0.IACKR[0].R = 0;                  /* Don't use vectors, just int numbers */

    /* Set the interrupt priorities - These default to 0 */
    /* NOTE priority registers do NOT exist for unused vectors */
    INTC_0.PSR[INT_PIT0].R = 0x8001;        /* PIT ch 0 Periodic Interrupt Timer */

    INTC_0.CPR[0].B.PRI = 0;                /* Set the INTC's current priority to 0 */

    /* Setup the periodic interrupt timer */
    Mcu_Init_PIT();
}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Reset_Ints                                            */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Turn off the interrupt system                                           */
/****************************************************************************/
void Mcu_Reset_Ints(void)
{
    /* Set the interrupt priorities back to zero */
    INTC_0.PSR[226].R = 0x0000;             /* PIT ch 0 and 1 Periodic Interrupt Timer */
    INTC_0.CPR[0].B.PRI = 0;                /* Set the INTC's current priority to 0 */

    Mcu_Reset_PIT();
}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Init_PIT                                              */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Set up the periodic interrupt timer (PIT).  Uses channel 0 to           */
/*  generate a 0.5ms interrupt.                                             */
/*  The other channels are set up for development purposes only.            */
/****************************************************************************/
void Mcu_Init_PIT(void)
{
    PIT_0.MCR.B.FRZ = 1;                       /* Freeze in debug mode */

    /* Timer 0 - 0.5ms timer interrupts */
    PIT_0.TIMER[0].TCTRL.B.TEN = 0;                                     /* Disable for setup */
    PIT_0.TIMER[0].LDVAL.R     = (TICKS_PER_MICROSECOND * 500U) - 1U;   /* 0.5ms */
    PIT_0.TIMER[0].TCTRL.B.TIE = 1;                                     /* Ints on */
    PIT_0.TIMER[0].TFLG.B.TIF  = 1;                                     /* Flag cleared */
    PIT_0.TIMER[0].TCTRL.B.TEN = 1;                                     /* Timer enabled */

    /* Timer 1 */
    PIT_0.TIMER[1].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[1].LDVAL.R     = (TICKS_PER_MICROSECOND * 1000U) - 1U;    /* 1ms */
    PIT_0.TIMER[1].TCTRL.B.TIE = 0;              /* No ints */
    PIT_0.TIMER[1].TFLG.B.TIF  = 1;              /* Flag cleared */
    PIT_0.TIMER[1].TCTRL.B.TEN = 1;              /* Timer enabled */

    /* Timer 2 */
    PIT_0.TIMER[2].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[2].LDVAL.R     = (TICKS_PER_MICROSECOND * 500U) - 1U;     /* 0.5ms */
    PIT_0.TIMER[2].TCTRL.B.TIE = 0;              /* No ints */
    PIT_0.TIMER[2].TFLG.B.TIF  = 1;              /* Flag cleared */
    PIT_0.TIMER[2].TCTRL.B.TEN = 1;              /* Timer enabled */

    /* Timer 3 - Used for software timing */
    PIT_0.TIMER[3].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[3].LDVAL.R     = 0xffffffffU;    /* Reset at rollover */
    PIT_0.TIMER[3].TCTRL.B.TIE = 0;              /* No ints */
    PIT_0.TIMER[3].TFLG.B.TIF  = 1;              /* Flag cleared */
    PIT_0.TIMER[3].TCTRL.B.TEN = 1;              /* Timer enabled */
}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Reset_PIT                                             */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Turn off the PIT.                                                       */
/****************************************************************************/
void Mcu_Reset_PIT(void)
{
    PIT_0.MCR.B.FRZ = 1;                       /* Freeze in debug mode */

    /* Timer 0 - 0.5ms timer interrupts */
    PIT_0.TIMER[0].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[0].TCTRL.B.TIE = 0;              /* Ints off */
    PIT_0.TIMER[0].TFLG.B.TIF  = 1;              /* Flag cleared */

    /* Timer 1 */
    PIT_0.TIMER[1].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[1].TCTRL.B.TIE = 0;              /* No ints */

    /* Timer 2 */
    PIT_0.TIMER[2].TCTRL.B.TEN = 0;              /* Disable for setup*/
    PIT_0.TIMER[2].TCTRL.B.TIE = 0;              /* No ints */

    /* Timer 3 - Used for software timing */
    PIT_0.TIMER[3].TCTRL.B.TEN = 0;              /* Disable for setup */
    PIT_0.TIMER[3].TCTRL.B.TIE = 0;              /* No ints */
}


/****************************************************************************/
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*      Handles timer interrupts every 0.5ms                                */
/*                                                                          */
/****************************************************************************/
void InterruptHandler(int signal_val)
{
    if (INT_PIT0 == signal_val)                 /* Timer interrupt (PIT channel 0) */
    {
        PIT_0.TIMER[0].TFLG.B.TIF  = 1;     /* Flag cleared */

        if (COUNTER_FOR_TASK_1MS <= ubCntTaskScheduler)
        {
            ubCntTaskScheduler = 0;
            ubTaskScheduler = TRUE;
        }
        else
        {
            ubCntTaskScheduler++;
        }
    }
    else                                    /* Unexpected interrupt */
    {
        INTC_0.PSR[signal_val].R = 0;           /* Make sure it doesn't happen again - set its priority to zero */
    }
}


/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Init_ADC                                              */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*      Sets up the internal ADCs to measure battery voltage                */
/*                                                                          */
/****************************************************************************/
/* DEVIATION: 0303, 0662 - globally disabled */
void Mcu_Init_ADC(void)
{

    /****************************************************************************/
    /*  Set up the ADC                                                          */
    /****************************************************************************/

    /*  ADC setup with pre-sampling (reduced window for 1.6us sampling):-
        -----------------------------------------------------------------
        ADC input clock is 50 MHz.
        Configure the sample rate at ADC clock = MC_CLK = 50MHz.
        INPSAMP = 10, Sampling time = 10 cycles.
        Pre-Sampling time = Sampling time + 1 = 11 cycles.
        Conversion time (13 bit mode) = 4 x N = 52 + 4 for the CS capacitor = 56.
        Data processing time = 2.
        Trigger processing time = 2.
        Total conversion time = 79 cycles = 1.58us.

        ADC setup with pre-sampling:-
        -----------------------------
        ADC input clock is 50 MHz.
        Configure the sample rate at ADC clock = MC_CLK = 50MHz.
        INPSAMP = 14, Sampling time = 14 cycles.
        Pre-Sampling time = Sampling time + 1 = 15 cycles.
        Conversion time (13 bit mode) = 4 x N = 52 + 4 for the CS capacitor = 56.
        Data processing time = 2.
        Trigger processing time = 2.
        Total conversion time = 87 cycles = 1.74us.

        ADC setup without pre-sampling:-
        --------------------------------
        ADC input clock is 50 MHz.
        Configure the sample rate at ADC clock = MC_CLK = 50MHz.
        INPSAMP = 14, Sampling time = 14 cycles.
        Conversion time (13 bit mode) = 4 x N = 52 + 4 for the CS capacitor = 56.
        Data processing time = 2.
        Trigger processing time = 2 (only on first sample of a chain).
        Total conversion time = 72 cycles = 1.24us.
    */
    
    ADC_0.MCR.B.PWDN      = 1;            /* can only modify the clock in power down */
    ADC_0.MCR.B.ADCLKSEL  = 1;            /* ADC clock = AUX0_CLK */
    ADC_0.MCR.B.OWREN     = 1;            /* Allow overwrites */
    ADC_0.CTR0.B.INPSAMP  = 14;           /* Sampling phase duration */
    ADC_0.CTR1.B.INPSAMP  = 22;           /* Sampling phase duration TSENS 0 */
    ADC_0.JCMR0.R         = 0x0000;       /* Channel select       */
    ADC_0.MCR.B.JEDGE     = 0;            /* External trigger falling edge */
    ADC_0.MCR.B.JTRGEN    = 0;            /* External trigger disable */
    ADC_0.DMAE.B.DCLR     = 0;            /* DMA request cleared by DMA cont */
    ADC_0.DMAE.B.DMAEN    = 0;            /* ADC DMA disabled */
    ADC_0.DMAR0.R         = 0;            /* ADC DMA channel diaabled */
    ADC_0.MCR.B.CTUEN     = 0;            /* CPU mode */
    ADC_0.PSCR.R          = 0x00;         /* Presample to Vss */
    ADC_0.PSR0.R          = 0x0001;       /* Presample the Rx inputs */
    ADC_0.WTIMR.R         = 0;            /* No watchdog interrupts */
    ADC_0.MCR.B.PWDN      = 0;            /* Exit from power down */

}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Read_ADC                                              */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : Status flag (0 = timed out, 1 = OK)                       */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Read the active ADC channels.                                           */
/****************************************************************************/
#define ADC_TIMEOUT     200                 /* Limit to about 50us */
/*  DEVIATION:     2006
    DESCRIPTION:   'Mcu_Read_ADC()' has more than one 'return' path.
    JUSTIFICATION: Function return two values because it is created on "if" conditions.
*/
/* PRQA S 2006 44 */
/*  DEVIATION:     4700
    DESCRIPTION:   Metric value out of threshold range: Mcu_Get_ADC() : STM19 = 3.
    JUSTIFICATION: Message is generated because the number of executable lines of code is less
                   than required.
*/
/* PRQA S 4700 38 */
/* DEVIATION: 0303, 0662 - globally disabled */
#define ADC_VBAT_MON_MASK   (1 << ADC_VBAT_MON) 
#define ADC_TIMEOUT                   200      /* Limit to about 50us */
#define ADC_12BIT_CONVERSION_MASK  0x0FFFU     /* only 12c bits of thr ADC register are valid for reading */
          
U8 Mcu_Read_ADC(void)
{
    U8   return_value = READ_ADC_SUCCESS;
    S32  timeout;
 
    
    timeout = ADC_TIMEOUT;
    while (1 == (ADC_0.MSR.B.NSTART))
    {
        --timeout;
        if (0 == timeout)
        {
            ADC_0.MCR.B.ABORT = 1; /* Try aborting the chain for next time */
            return_value =  READ_ADC_FAILURE;
        }
    }
    
    
    ADC_0.ISR.B.ECH = 1;                    /* Clear the done flags */
    ADC_0.MCR.B.CTUEN = 0;                  /* CPU mode */
    ADC_0.MCR.B.NSTART = 0;                 /* Stop any existing conversion */
    ADC_0.MCR.B.MODE = 0;                   /* Single shot mode     */
    ADC_0.DMAE.B.DMAEN = 0;                 /* ADC DMA disabled     */
    ADC_0.DMAR0.R = 0;                      /* ADC DMA channel disabled */
    ADC_0.WTIMR.R = 0;                      /* No watchdog interrupts */

    /* Configure pre-sampling */
    ADC_0.PSCR.R = 0;                       /* Presample to Vss */
    ADC_0.PSR0.R = 0x0001;                  /* Presample the Rx inputs */

    /* Now start the conversion of the internal channels */
    ADC_0.NCMR0.R = ADC_VBAT_MON_MASK;      /* Channel select       */

    ADC_0.MCR.B.NSTART = 1;                 /* Start conversion     */

    timeout = ADC_TIMEOUT;
    while (1 == (ADC_0.MSR.B.NSTART))
    {
        --timeout;
        if (0 == timeout)
        {
            ADC_0.MCR.B.ABORT = 1; /* Try aborting the chain for next time */
            return_value =  READ_ADC_FAILURE;
        }
    }
    
    ADC_0.ISR.B.ECH = 1;                    /* Clear the done flag  */


    return return_value;
}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Get_ADC                                               */
/*                                                                          */
/*  Parameters  : Channel number (0 to 31).                                 */
/*              : Channels  0 to 15 are converter 0 channels 0 to 15.       */
/*              : Channels 16 to 31 are converter 1 channels 0 to 15.       */
/*                                                                          */
/*  Returns     : Status flag (0 = timed out, 1 = OK)                       */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Return an ADC channel value.                                            */
/****************************************************************************/
/*  DEVIATION:     2006
    DESCRIPTION:   'Mcu_Read_ADC()' has more than one 'return' path.
    JUSTIFICATION: Function return two values because it is created on "if" conditions.
*/
/* PRQA S 2006 20 */
/*  DEVIATION:     4700
    DESCRIPTION:   Metric value out of threshold range: Mcu_Get_ADC() : STM19 = 3.
    JUSTIFICATION: Message is generated because the number of executable lines of code is less
                   than required.
*/
/* PRQA S 4700 14 */
/* DEVIATION: 0303, 0662 - globally disabled */
U16 Mcu_Get_ADC(U8 channel)
{
    U16  raw_value = 0;

    if (channel ==  ADC_VBAT_MON)
    {
        raw_value = (U16)(ADC_0.CDR_MCR[ADC_VBAT_MON].R & ADC_12BIT_CONVERSION_MASK);
    }   
  
    return raw_value;
}

U32 Mcu_Get_Tick_Count(void)
{
    return (~PIT_0.TIMER[3].CVAL.R);
}

/****************************************************************************/
/*                                                                          */
/*  Function    : Mcu_Init_PWM                                              */
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Returns     : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*                                                                          */
/*  Set up the PWM timer.  Uses channel 0 to generate a PSU sync signal.    */
/****************************************************************************/
#define PSU_SYNC_PERIOD (COUNTS_PER_MICROSECOND)    /* PSU sync period (counts) = 1.0us */

void Mcu_Init_PWM(void)
{
    FlexPWM_0.MCTRL.R = 0xf0;               /* Clear all of the LDOK bits during init */

    /* Set up PWM 0 for operation as PSU Sync */
    FlexPWM_0.SUB0_INIT.R = 0;
    FlexPWM_0.SUB0_CTRL1.R = 0x400;         /* Reload at every full cycle, no prescaler, no double switching */
    FlexPWM_0.SUB0_CTRL2.R = 0xa000;        /* Independent PWMs, run in debug, use bus clock */
    FlexPWM_0.SUB0_DISMAP.R = 0;            /* No fault disables */
    FlexPWM_0.SUB0_OCTRL.R = 0x0700;        /* All outputs inverted */

    FlexPWM_0.SUB0_VAL0.R = (PSU_SYNC_PERIOD / 2U) - 1U;    /* PSU Sync 50:50 duty */
    FlexPWM_0.SUB0_VAL1.R = PSU_SYNC_PERIOD - 1U;           /* Set reload period */
    FlexPWM_0.SUB0_VAL4.R = (PSU_SYNC_PERIOD / 2U) - 1U;    /* PSU Sync 50:50 duty */
    FlexPWM_0.SUB0_VAL5.R = PSU_SYNC_PERIOD - 1U;           /* Set reload period */

    FlexPWM_0.OUTEN.R = 0x010;                  /* Enable channel B pin on module 0 as output */
    FlexPWM_0.DTSRCSEL.R = 0;                   /* Use PWM outputs when forced */

    FlexPWM_0.MCTRL.B.LDOK = 0x1;               /* Set the LDOK flag for module 0 */
    FlexPWM_0.MCTRL.B.RUN = 0x1;                /* Set the RUN flag for module 0 */
}


/****************************************************************************/
/*                                                                          */
/*  Parameters  : void                                                      */
/*                                                                          */
/*  Description :                                                           */
/*      Clear all reset flags.                                              */
/*                                                                          */
/****************************************************************************/
void Mcu_Clear_Reset_Flags(void)
{
    MC_RGM.FES.R = MC_RGM.FES.R;
    MC_RGM.DES.R = MC_RGM.DES.R;
}

/* PRQA S 0303 -- */
