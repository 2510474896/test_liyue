/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/BRP/project.pj $
        $RCSfile: brp_main.h $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:47CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/


#ifndef BRP_MAIN_H_
#define BRP_MAIN_H_


/************************************************************************
*   Abstraction of SSD functions
************************************************************************/
extern const unsigned int FlashInit_C[];
extern const unsigned int FlashErase_C[];
extern const unsigned int BlankCheck_C[];
extern const unsigned int FlashProgram_C[];
extern const unsigned int ProgramVerify_C[];
extern const unsigned int FlashCheckStatus_C[];
extern const unsigned int GetLock_C[];
extern const unsigned int SetLock_C[];
extern const unsigned int FlashSuspend_C[];
extern const unsigned int FlashResume_C[];
extern const unsigned int FlashAbort_C[];


/************************************************************************
*   Extern variables defined in the linker file
************************************************************************/
extern UINT32 __FLASH_API_RAM_BASE[];
extern UINT32 __FLS_DRV_ST[];
extern UINT32 __FLS_DRV_SIZE;
extern UINT32 __SLF_ERASE_FN_RAM_BASE;
extern UINT32 __SLF_ERASE_CODE_ST;
extern UINT32 __SLF_ERASE_CODE_SIZE;
extern UINT32 __BOOT_CODE_START_ADDR[];
extern UINT32 __BRP_BOOT_IMG_START_ADDR;
extern UINT32 __BRP_START_ADDR;


#endif /* BRP_MAIN_H_ */
