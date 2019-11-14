/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: sw_utils.c $
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
/* DEVIATION:     0306
   DESCRIPTION:   Cast between a pointer to object and an integral type.
   JUSTIFICATION: Casting is required and can not be avoided.
*/
/* PRQA S 0306 EOF */

/***************************************************************************/


/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/



#include "MPC5744P.h"    /* register and bit field descriptions */

#include "sw_utils.h"   /* software utilities */

/*************************************************************/
/*      GLOBAL VARIABLES                                     */
/*************************************************************/

/*************************************************************/
/*      PRIVATE FUNCTION DECLARATIONS                        */
/*************************************************************/

/*************************************************************/
/*      CODE                                                 */
/*************************************************************/



/****************************************************************************/
/*                                                                          */
/*  Function    : FOUNDATION_Memory_Access_Valid                            */
/*                                                                          */
/*  Parameters  : addr        - Address to which access is required         */
/*                access_type - Type of access required                     */
/*                                                                          */
/*  Returns     : TRUE  if access is valid                                  */
/*                FALSE otherwise                                           */
/*                                                                          */
/* Description: This function reports whether the requested memory access   */
/*              is permitted for the specified address.                     */
/*                                                                          */
/****************************************************************************/
BOOLEAN FOUNDATION_Memory_Access_Valid(U32 addr, memory_access_type access_type)
{
    BOOLEAN access_valid = FALSE;

    if (((addr >= (U32)__START_INTERNAL_RAM) && (addr <= (U32)__END_INTERNAL_RAM)) ||
        ((addr >= (U32)__START_LOCAL_RAM) && (addr <= (U32)__END_LOCAL_RAM)))
    {
        access_valid = TRUE;
    }
    else if (access_type == READ_ACCESS)
    {
        if (((addr >= (U32)__START_UTEST_FLASH)  && (addr <= (U32)__END_UTEST_FLASH)) ||
            ((addr >= (U32)__START_DATA_FLASH)  && (addr <= (U32)__END_DATA_FLASH)) ||
            ((addr >= (U32)__START_CODE_FLASH) && (addr <= (U32)__END_CODE_FLASH)))
        {
            access_valid = TRUE;
        }
    }
    else
    {
    }

    return (access_valid);
}
