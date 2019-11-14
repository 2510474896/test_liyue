#/*********************************************************************
#    MODULE SPECIFICATION:
#
#        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/MCAL/project.pj $
#        $RCSfile: Mpc5500_DSI_ISI.asm $
#        $Revision: 1.1 $
#        $Date: 2019/06/25 14:46:16CST $
#
#        TRW Ltd owns the copyright in this document and associated
#        documents and all rights are reserved.  These documents must
#        not be used for any purpose other than that for which they
#        are supplied and must not be copied in whole or in part or
#        disclosed to others without prior written consent of TRW
#        Ltd. Any copy of this drawing or document made by any method
#        must also include a copy of this legend.
#
#    $CopyrightDate: (c) ZF 2019 $
#
#*********************************************************************/
#/**
#    @file        Mpc5500_DSI_ISI.s
#    @version     M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
#
#    @brief       AUTOSAR M4_SRC_MODULE_NAME - IVOR1 MCI handler
#
#    @details     IVOR1 MCI handler
#
#    Project      : M4_SRC_PROJECT_NAME
#    Platform     : M4_SRC_MCU_FAMILY
#    Peripheral   : M4_SRC_USED_PERIPHERAL
#    Dependencies : M4_SRC_AR_MODULE_DEPENDENCY
#
#    Autosar Version       : M4_SRC_AR_SPEC_VERSION_MAJOR.M4_SRC_AR_SPEC_VERSION_MINOR.M4_SRC_AR_SPEC_VERSION_PATCH
#    Autosar Revision      : M4_SRC_AR_RELEASE_REVISION
#    Autosar Conf. Variant :
#    Software Version      : M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
#    Build Version         : M4_SRC_BUILD_ID
#
#    (c) Copyright M4_SRC_YEAR_ID Freescale Semiconductor Inc. & STMicroelectronics
#    All Rights Reserved.
#*/
#/*==================================================================================================
#ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
#Revision History:
#                             Modification     Tracking
#Author (core ID)              Date D/M/Y       Number     Description of Changes
#---------------------------   ----------    ------------  ------------------------------------------
#Petr Pomkla (B12796)          09/03/2010    ENGR00116361  [FLS] ECC errors handling
#Jaromir Jasik (R60817)        03/08/2010    ENGR00125819  [FLS] Flash ECC errors handling
#---------------------------   ----------    ------------  ------------------------------------------
#',)dnl - DO NOT modify this M4 line!
#==================================================================================================*/

# STACK FRAME DESIGN: Depth: 20 words (80 bytes)
#           ************* ______________
#  0x4C     *  GPR12    *    ^
#  0x48     *  GPR11    *    |
#  0x44     *  GPR10    *    |
#  0x40     *  GPR9     *    |
#  0x3C     *  GPR8     *    |
#  0x38     *  GPR7     *  GPRs (32 bit)
#  0x34     *  GPR6     *    |
#  0x30     *  GPR5     *    |
#  0x2C     *  GPR4     *    |
#  0x28     *  GPR3     *    |
#  0x24     *  GPR0     * ___v__________
#  0x20     *  CR       * __CR__________
#  0x1C     *  XER      *    ^
#  0x18     *  CTR      *    |
#  0x14     *  LR       * locals & padding for 16 B alignment
#  0x10     *  SRR1     *    |
#  0x0C     *  padding  *    |
#  0x08     *  padding  * ___v__________
#  0x04     * resvd- LR * Reserved for calling function
#  0x00     *  SP       * Backchain (same as gpr1 in GPRs)
#           *************

# Define the compiler specific constants according to BEART
.set COMPILER_GHS,  0
.set COMPILER_DIAB, 1
.set COMPILER_CW,   2

#   .include "compiler_used.s"
.set COMPILER_USED, COMPILER_DIAB

# Specify output section for the code bellow (compiler specific)
.if COMPILER_USED == COMPILER_GHS
    .vle
    .section ".vletext", "avx"
.else
    .if COMPILER_USED == COMPILER_DIAB
        .section ".text_vle"
    .else
        .if COMPILER_USED == COMPILER_CW
            .text_vle
        .endif
    .endif
.endif

# Name(s) of external symbols
.extern MpcDsi_Handler

# Name(s) of exported symbols
.global MPC5500_IVOR1Handler

    .align 4                            # Align IVOR handlers on a 16 byte boundary for MPC555x



# Implemetation of not nested IVOR1 exception handler
MPC5500_IVOR1Handler:
    e_stwu  r1,-80(r1)              # Create stack frame and store back chain

    e_stw   r0, 0x24(r1)            # Save working register (R0)

    mfspr   r0, 27                  # Save SRR1
    e_stw   r0, 0x10(r1)

    se_mflr r0                      # Save LR
    e_stw   r0, 0x14(r1)

    se_mfctr r0                     # Save CTR
    e_stw   r0, 0x18(r1)

    mfspr   r0, 1                   # Save XER
    e_stw   r0, 0x1C(r1)

    mfcr    r0                      # Save CR
    e_stw   r0, 0x20(r1)

    e_stw   r3, 0x28(r1)            # Save GPRs except R0
    e_stw   r4, 0x2C(r1)
    e_stw   r5, 0x30(r1)
    e_stw   r6, 0x34(r1)
    e_stw   r7, 0x38(r1)
    e_stw   r8, 0x3C(r1)
    e_stw   r9, 0x40(r1)
    e_stw   r10, 0x44(r1)
    e_stw   r11, 0x48(r1)
    e_stw   r12, 0x4C(r1)

    mfspr   r5, 572                 # Get MCSR and pass it to the C function
    mfspr   r4, 573                 # Get MCAR and pass it to the C function
    mfspr   r3, 570                 # Get MCSRR0 and pass it to the C function

    e_lis   r0, MpcDsi_Handler@h    # Load address of the MCI handler function
    e_or2i  r0, MpcDsi_Handler@l

    se_mtlr r0                      # Transfer R0 to LR and jump
    se_blrl

    mtspr   570,    r3                  # Set new value of MCSRR0 (return value of the MpcDsi_Handler function)

    mfspr   r5, 572                 # Get MCSR
    mtspr   572, r5                 # clear MCSR to avoid a redundant machine check exception

    e_lwz   r12, 0x4C(r1)           # Restore GPRs except R0
    e_lwz   r11, 0x48(r1)
    e_lwz   r10, 0x44(r1)
    e_lwz   r9, 0x40(r1)
    e_lwz   r8, 0x3C(r1)
    e_lwz   r7, 0x38(r1)
    e_lwz   r6, 0x34(r1)
    e_lwz   r5, 0x30(r1)
    e_lwz   r4, 0x2C(r1)
    e_lwz   r3, 0x28(r1)

    e_lwz   r0, 0x20(r1)            # Restore CR
    mtcrf   0xff, r0

    e_lwz   r0, 0x1C(r1)            # Restore XER
    mtspr   1, r0

    e_lwz   r0, 0x18(r1)            # Restore CTR
    se_mtctr r0

    e_lwz   r0, 0x14(r1)            # Restore LR
    se_mtlr r0

    e_lwz   r0, 0x10(r1)            # Restore SRR1
    mtspr   27, r0

    e_lwz   r0, 0x24(r1)            # Restore R0

    e_addi  r1, r1, 80              # Clean up stack

.if COMPILER_USED == COMPILER_GHS
    .short 0x000B               ;se_rfmci instruction
                                            # End of Interrupt (load program counter from MCSRR0)
.else
    se_rfmci                        # End of Interrupt (load program counter from MCSRR0)
.endif
