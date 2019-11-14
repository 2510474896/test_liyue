/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: types.h $
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

#include "typedefs.h"

#ifndef TYPES_H_
    #define TYPES_H_

    /* Variable types and associated #defines */
    #ifndef TRUE
        #define TRUE        1U
    #endif

    #ifndef FALSE
        #define FALSE       0U
    #endif

    #ifndef NULL
        #define NULL        0U
    #endif

    typedef     uint8_t         BOOLEAN;

    typedef     uint8_t         U8;
    typedef     int8_t          S8;
    typedef     uint16_t        U16;
    typedef     int16_t         S16;
    typedef     uint32_t        U32;
    typedef     int32_t         S32;
    typedef     float           F32;
    typedef     uint64_t        U64;

    __attribute__((aligned(8))) typedef struct
    {
        F32     real;
        F32     imag;
    } COMPLEX;

    #define TICKS_PER_MICROSECOND       50U
    #define COUNTS_PER_MICROSECOND      100U
    #define EnableAllInterrupts()       asm("wrteei 1")
    #define DisableAllInterrupts()      asm("wrteei 0")
    #define Get_Tick_Count()            (~PIT.CH[3].CVAL.R)


#endif  /* TYPES_H_ */

