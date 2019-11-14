/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: sw_utils.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:15CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

#ifndef SW_UTILS_H_
#define SW_UTILS_H_

#include "types.h"

extern U32 __START_UTEST_FLASH[];
extern U32 __END_UTEST_FLASH[];
extern U32 __START_DATA_FLASH[];
extern U32 __END_DATA_FLASH[];
extern U32 __START_CODE_FLASH[];
extern U32 __END_CODE_FLASH[];
extern U32 __START_INTERNAL_RAM[];
extern U32 __END_INTERNAL_RAM[];
extern U32 __START_LOCAL_RAM[];
extern U32 __END_LOCAL_RAM[];


/************************************************************************************/
/* Function:    FOUNDATION_Memory_Access_Valid                                      */
/* Description: This function reports whether the requested memory access is        */
/*              permitted for the specified address.                                */
/************************************************************************************/

typedef enum {
    READ_ACCESS,
    WRITE_ACCESS
} memory_access_type;

extern BOOLEAN FOUNDATION_Memory_Access_Valid(U32 addr, memory_access_type access_type);

/************************************************************************************/
/* Function:    INVERT_BITS_IN_BYTE                                                 */
/* Description: This macro inverts bits in a byte                                   */
/************************************************************************************/

#define INVERT_BITS_IN_BYTE(byte_value)  ( (U8)(0xFFU ^ (byte_value)) )

#endif
