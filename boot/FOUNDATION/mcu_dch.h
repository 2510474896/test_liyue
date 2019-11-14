/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: mcu_dch.h $
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

#ifndef MCU_DCH_H_
#define MCU_DCH_H_

/******************************************************************************
* Include
******************************************************************************/

/******************************************************************************
* Defines
******************************************************************************/
#define PIT_TIF 0x00000001  /* PIT Time interrupt flag */

/* Interrupt vector numbers */
#define INT_PIT0    226      /* Periodic Interrupt Timer - channel 0 */

/* Battery MIN and MAX voltage */
#define MIN_VBAT_COUNT 690U   /* One count is 12.6 mv: Min voltage~ 8.6V(Actual voltage 0.8V more ~9.5V)*/
#define MAX_VBAT_COUNT 1270U  /* One count is 12.6 mv: Max voltage~ 16V(Actual voltage 0.8V more ~16.8V)*/
/* ADC SET measure, RESET measure */
#define READ_ADC_SUCCESS    1U
#define READ_ADC_FAILURE    0U

/* ADC, battery status during transfer data */
#define BATTERY_STATUS_NOT_OK      1U
#define BATTERY_STATUS_OK          0U

#define ADC_VBAT_MON         3      /* ADC 0  Battery monitor channel number 3   */


/******************************************************************************
* Function Prototypes
******************************************************************************/

void Send_hardware_fault(int d);            /* This is the BT error handler in crts0.asm which waggles the boot pin */

/* Initialize MCU interrupts */
void Mcu_Init_Ints(void);
void Mcu_Reset_Ints(void);

/* Initialise PIT */
void Mcu_Init_PIT(void);
void Mcu_Reset_PIT(void);
U32  Mcu_Get_Tick_Count(void);

/* Initialise PWM (PSU sync) */
void Mcu_Init_PWM(void);

/* Timer interrupt handler */
void InterruptHandler(int signal_val);

/* Initialise ADC */
void Mcu_Init_ADC(void);
U8   Mcu_Read_ADC(void);
U16  Mcu_Get_ADC(U8 channel);



/* Clear reset flags */
void Mcu_Clear_Reset_Flags(void);
extern BOOLEAN ubTaskScheduler;
extern U8 ubCntTaskScheduler;

#endif /* MCU_H_ */

