/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
        $RCSfile: pack_id.h $
        $Revision: 1.2 $
        $Date: 2019/08/21 18:35:02CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/
#ifndef PACK_ID_H
#define PACK_ID_H

#define NUM_CHARS_IN_LONG_BUILD_NAME        24U
extern const  U8 Boot_ID[];                         /* e.g. "PSAX8AC1KRRBoo_K2_Rel01a" */
extern        U8 Boot_ID_short_name[];              /* e.g. "EBRel01A" */
extern const  U8 Boot_date[];                       /* format is dd/mm/yyyy */
extern const  U8 Boot_time[];                       /* format is "hh:mm" */


#define GET_ID_CLEF_APPLI()                 0xEFCAU


#endif /* PACK_ID_H */
