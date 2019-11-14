/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: MEMU.C $
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


#define MEMU_

#include "types.h"
#include "MPC5744P.h"
#include "MEMU.h"

/*********************************************************************************/
/* Name: MEMU_Read_SYS_RAM_Correctable_Err                                       */
/*-------------------------------------------------------------------------------*/
/* Description:  Read System RAM Correctable Error from the table.               */
/*               The SYS RAM CERR table has 10 Entries.                          */
/*               NOTE: This only reads the latest error.                         */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/*                      bad_bit_pu8                                              */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_SYS_RAM_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8)
{
    U8 i;

    /* SYS RAM CERR has 10 Entries */
    for (i = 0; i < MEMU_SYS_RAM_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL0[i].SYS_RAM_CERR_STS.B.VLD)
        {
            *bad_bit_pu8   = MEMU.CHANNEL0[i].SYS_RAM_CERR_STS.B.BAD_BIT;
            *err_addr_pu32 = MEMU.CHANNEL0[i].SYS_RAM_CERR_ADDR.B.ERR_ADD;

            /* Clear the entry in the error table */
            MEMU.CHANNEL0[i].SYS_RAM_CERR_STS.B.VLD = 1;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Read_SYS_RAM_Uncorrectable_Err                                     */
/*-------------------------------------------------------------------------------*/
/* Description:  Read System RAM Uncorrectable Error from the table.             */
/*               The SYS RAM UNCERR table has 1 Entry.                           */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_SYS_RAM_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32)
{
    if (1 == MEMU.SYS_RAM_UNCERR_STS.B.VLD)
    {
        *err_addr_pu32 = MEMU.SYS_RAM_UNCERR_ADDR.B.ERR_ADD;
        *err_sts_pu32 = MEMU.SYS_RAM_UNCERR_STS.R;
    }
}

/*********************************************************************************/
/* Name: MEMU_Read_PERIPH_RAM_Correctable_Err                                    */
/*-------------------------------------------------------------------------------*/
/* Description:  Read Peripheral RAM Correctable Error from the table.           */
/*               The PERIPH RAM CERR table has 2 Entries.                        */
/*               NOTE: This only reads the latest error.                         */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/*                      bad_bit_pu8                                              */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_PERIPH_RAM_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8)
{
    U8 i;

    /* PERIPH RAM CERR has 2 Entries */
    for (i = 0; i < MEMU_PERIPH_RAM_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL1[i].PERIPH_RAM_CERR_STS.B.VLD)
        {
            *bad_bit_pu8   = MEMU.CHANNEL1[i].PERIPH_RAM_CERR_STS.B.BAD_BIT;
            *err_addr_pu32 = MEMU.CHANNEL1[i].PERIPH_RAM_CERR_ADDR.B.ERR_ADD;

            /* Clear the entry in the error table */
            MEMU.CHANNEL1[i].PERIPH_RAM_CERR_STS.B.VLD = 1;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Read_PERIPH_RAM_Uncorrectable_Err                                  */
/*-------------------------------------------------------------------------------*/
/* Description:  Read Peripheral RAM Uncorrectable Error from the table.         */
/*               The PERIPH RAM UNCERR table has 1 Entry.                        */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_PERIPH_RAM_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32)
{
    if (1 == MEMU.PERIPH_RAM_UNCERR_STS.B.VLD)
    {
        *err_addr_pu32 = MEMU.PERIPH_RAM_UNCERR_ADDR.B.ERR_ADD;
        *err_sts_pu32 = MEMU.PERIPH_RAM_UNCERR_STS.R;

    }
}

/*********************************************************************************/
/* Name: MEMU_Read_FLASH_Correctable_Err                                         */
/*-------------------------------------------------------------------------------*/
/* Description:  Read FLASH Correctable Error from the table.                    */
/*               The FLASH CERR table has 20 Entries.                            */
/*               NOTE: This only reads the latest error.                         */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/*                      bad_bit_pu8                                              */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_FLASH_Correctable_Err(U32 *err_addr_pu32, U8 *bad_bit_pu8)
{
    U8 i;

    /* FLASH CERR has 20 Entries */
    for (i = 0; i < MEMU_FLASH_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL2[i].FLASH_CERR_STS.B.VLD)
        {
            *bad_bit_pu8   = MEMU.CHANNEL2[i].FLASH_CERR_STS.B.BAD_BIT;
            *err_addr_pu32 = MEMU.CHANNEL2[i].FLASH_CERR_ADDR.B.ERR_ADD;

            /* Clear the entry in the error table */
            MEMU.CHANNEL2[i].FLASH_CERR_STS.B.VLD = 1;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Read_FLASH_Uncorrectable_Err                                       */
/*-------------------------------------------------------------------------------*/
/* Description:  Read FLASH Uncorrectable Error from the table.                  */
/*               The FLASH UNCERR table has 1 Entry.                             */
/*********************************************************************************/
/* Input parameters   : err_addr_pu32                                            */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Read_FLASH_Uncorrectable_Err(U32 *err_addr_pu32, U32 *err_sts_pu32)
{
    if (1 == MEMU.FLASH_UNCERR_STS.B.VLD)
    {
        *err_sts_pu32 = MEMU.FLASH_UNCERR_STS.R;
        *err_addr_pu32 = MEMU.FLASH_UNCERR_ADDR.B.ERR_ADD;
    }
}


/*********************************************************************************/
/* Name: MEMU_Clear_SYS_RAM_Correctable_Err_Table                                */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear System RAM Correctable Error table.                       */
/*               The SYS RAM CERR table has 10 Entries.                          */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_SYS_RAM_Correctable_Err_Table(void)
{
    U8 i;

    /* SYS RAM CERR has 10 Entries */
    for (i = 0; i < MEMU_SYS_RAM_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL0[i].SYS_RAM_CERR_STS.B.VLD)
        {
            /* Clear the entry in the error table */
            MEMU.CHANNEL0[i].SYS_RAM_CERR_STS.B.VLD = 0;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Clear_SYS_RAM_Uncorrectable_Err_Table                              */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the System RAM Uncorrectable Error Table.                 */
/*               The SYS RAM UNCERR table has 1 Entry.                           */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_SYS_RAM_Uncorrectable_Err_Table(void)
{
    if (1 == MEMU.SYS_RAM_UNCERR_STS.B.VLD)
    {
        /* Clear the entry in the error table */
        MEMU.SYS_RAM_UNCERR_STS.B.VLD = 0;
    }
}

/*********************************************************************************/
/* Name: MEMU_Clear_PERIPH_RAM_Correctable_Err_Table                             */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the Peripheral RAM Correctable Error Table.               */
/*               The PERIPH RAM CERR table has 2 Entries.                        */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_PERIPH_RAM_Correctable_Err_Table(void)
{
    U8 i;

    /* PERIPH RAM CERR has 2 Entries */
    for (i = 0; i < MEMU_PERIPH_RAM_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL1[i].PERIPH_RAM_CERR_STS.B.VLD)
        {
            /* Clear the entry in the error table */
            MEMU.CHANNEL1[i].PERIPH_RAM_CERR_STS.B.VLD = 0;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Clear_PERIPH_RAM_Uncorrectable_Err_Table                           */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the Peripheral RAM Uncorrectable Error Table.             */
/*               The PERIPH RAM UNCERR table has 1 Entry.                        */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_PERIPH_RAM_Uncorrectable_Err_Table(void)
{
    if (1 == MEMU.PERIPH_RAM_UNCERR_STS.B.VLD)
    {
        /* Clear the entry in the error table */
        MEMU.PERIPH_RAM_UNCERR_STS.B.VLD = 0;
    }
}

/*********************************************************************************/
/* Name: MEMU_Clear_FLASH_Correctable_Err_Table                                  */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the FLASH Correctable Error Table.                        */
/*               The FLASH CERR table has 20 Entries.                            */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_FLASH_Correctable_Err_Table(void)
{
    U8 i;

    /* FLASH CERR has 20 Entries */
    for (i = 0; i < MEMU_FLASH_CERR_ENTRIES; i++)
    {
        if (1 == MEMU.CHANNEL2[i].FLASH_CERR_STS.B.VLD)
        {
            /* Clear the entry in the error table */
            MEMU.CHANNEL2[i].FLASH_CERR_STS.B.VLD = 0;
        }
    }
}

/*********************************************************************************/
/* Name: MEMU_Clear_FLASH_Uncorrectable_Err_Table                                */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear the FLASH Uncorrectable Error Table.                      */
/*               The FLASH UNCERR table has 1 Entry.                             */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_FLASH_Uncorrectable_Err_Table(void)
{
    if (1 == MEMU.FLASH_UNCERR_STS.B.VLD)
    {
        /* Clear the entry in the error table */
        MEMU.FLASH_UNCERR_STS.B.VLD = 0;
    }
}


/*********************************************************************************/
/* Name: MEMU_Clear_Err_Tables                                                   */
/*-------------------------------------------------------------------------------*/
/* Description:  Clear all the MEMU Error Reporting Tables.                      */
/*********************************************************************************/
/* Input parameters   : None                                                     */
/* Output parameters  : None                                                     */
/* Return value       : None                                                     */
/*********************************************************************************/

void MEMU_Clear_Err_Tables(void)
{
    MEMU.ERR_FLAG.R = 0xFFFFFFFFUL;
    /* Clear the SYS RAM Error Reporting Tables */
    MEMU_Clear_SYS_RAM_Correctable_Err_Table();
    MEMU_Clear_SYS_RAM_Uncorrectable_Err_Table();

    /* Clear the PERIPH RAM Error Reporting Tables */
    MEMU_Clear_PERIPH_RAM_Correctable_Err_Table();
    MEMU_Clear_PERIPH_RAM_Uncorrectable_Err_Table();

    /* Clear the FLASH Error Reporting Tables */
    MEMU_Clear_FLASH_Correctable_Err_Table();
    MEMU_Clear_FLASH_Uncorrectable_Err_Table();
}