/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: FCCU.h $
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
#ifndef FCCU_H
#define FCCU_H



typedef struct
{
    U32          rgm_fes;            /* Reset Generation Module - Functional Event Status Register */
    U32          Critical_Faults;    /* Contents of the Critical fault status register (CFS0) */
    U16          EventID;            /* Fault event to be raised in case of a critical error */
    U8           SnapshotData;       /* snapshot data associated with the critical fault */
}  __attribute__ ((packed)) T_RESET_INFO_TYPE;

extern T_RESET_INFO_TYPE   __RESET_INFO_START;
#define Reset_Info         __RESET_INFO_START

/*
** Definitions of faults written to Reset_Info.Critical_Faults
** - Mask to check for SWT timeout
** - Mask to check for uncorrectable RAM ECC Error
** - Mask to check for safety core exception fault
** - Mask to check for lockstep fault
*/

#define SWT_CRITICAL_FAULT_MASK         0x00000001UL
#define RAMECC_CRITICAL_FAULT_MASK      0x00000002UL
#define SAFETY_CORE_CRITICAL_FAULT_MASK 0x00000004UL
#define LOCKSTEP_CRITICAL_FAULT_MASK    0x00000008UL


/*
** Externs
*/

/**
 * @description     Sets up the FCCU for ECC errors and SWT
 *                  NCF[14] - Software Watchdog
 *                  NCF[15] - System RAM correctable ECC
 *                  NCF[16] - System RAM uncorrectable ECC
 *                  NCF[17] - System RAM overflow
 *                  NCF[18] - Peripheral RAM correctable ECC
 *                  NCF[19] - Peripheral RAM uncorrectable ECC
 *                  NCF[20] - Peripheral RAM overflow
 *                  NCF[21] - Flash correctable ECC
 *                  NCF[22] - Flash uncorrectable ECC
 *                  NCF[23] - Flash RAM overflow
 *                  NCF[44] - Safety Core Exception
 *                  NCF[45] - Lockstep Error
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
void FCCU_Init(void);


/**
 * @description     Check the FCCU for NCFs that trigger a reset.
 *                  Copy to shared structure in RAM for APP to log them to NVM
 * @param[in]       parameters
 * @param[in]       None
 * @param[out]      parameters
 * @param[out]      valuevalue - None
 */
void FCCU_Check_Reset_Reason(void);

#endif /* FCCU_H */
