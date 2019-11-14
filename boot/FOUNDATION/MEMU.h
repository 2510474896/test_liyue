/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: MEMU.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:09CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

#define MEMU_

#include "types.h"

/*
** Defines for number of entries in MEMU Reporting Tables
*/
#define MEMU_SYS_RAM_CERR_ENTRIES    10
#define MEMU_PERIPH_RAM_CERR_ENTRIES  2
#define MEMU_FLASH_CERR_ENTRIES      20

/*
** Externs
*/
void MEMU_Read_SYS_RAM_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8);
void MEMU_Read_PERIPH_RAM_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8);
void MEMU_Read_FLASH_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8);

/* MPW if there is a valid bit set in the MEMU, then read the status and the address of the UCF. */
void MEMU_Read_SYS_RAM_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32);

/* MPW if there is a valid bit set in the MEMU, then read the status and the address of the UCF. */
void MEMU_Read_PERIPH_RAM_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32);

/* MPW if there is a valid bit set in the MEMU, then read the status and the address of the UCF. */
void MEMU_Read_FLASH_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32);

void MEMU_Clear_SYS_RAM_Correctable_Err_Table(void);
void MEMU_Clear_PERIPH_RAM_Correctable_Err_Table(void);
void MEMU_Clear_FLASH_Correctable_Err_Table(void);

void MEMU_Clear_SYS_RAM_Uncorrectable_Err_Table(void);
void MEMU_Clear_PERIPH_RAM_Uncorrectable_Err_Table(void);
void MEMU_Clear_FLASH_Uncorrectable_Err_Table(void);

void MEMU_Clear_Err_Tables(void);
