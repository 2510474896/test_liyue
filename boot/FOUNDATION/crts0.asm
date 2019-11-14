#/*********************************************************************
#    MODULE SPECIFICATION:
#
#        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/FOUNDATION/project.pj $
#        $RCSfile: crts0.asm $
#        $Revision: 1.1 $
#        $Date: 2019/06/25 14:46:13CST $
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
#
#   Crts0.asm - start-up code for the Panther processor and assembler utilities.
#
#   Start-up code for the Panther processor.
#
#   assemble with option -DBOOT_CODE to generate a boot code RCW.
#   assemble with option -DBRP_CODE to generate a BRP code RCW, jump instruction and signature. (also used by PCBtest code)
#   assemble with option -DAPPS_CODE to generate an application RCW and jump instruction.
#
#   assemble with option -DINT_VECT to generate a vectored interrupt handler.
#   assemble with option -DINT_HANDLER to generate a single interrupt handler.
#
#   assemble with option -DRAM_CODE to generate a RAM loadable copy.
#

.ifdef  INT_VECT
    .set    INT_HANDLER, 1          # If we want vectors we need the handler too
.endif


    .file   "crts0.asm"

    .ifdef  APPS_CODE
        .extern __START_INTERNAL_RAM            # Defined in the linker file as ADDR(.internal_ram)
        .extern __START_D_MEM_RAM               # Defined in the linker file as ADDR(.local_ram)
        .extern __SIZE_INTERNAL_RAM             # Defined in the linker file
        .extern __SIZE_D_MEM_RAM                # Defined in the linker file
    .else
        .extern __START_INTERNAL_RAM            # Defined in the linker file as ADDR(.internal_ram)
        .extern __START_LOCAL_RAM               # Defined in the linker file as ADDR(.local_ram)
        .extern __SIZE_INTERNAL_RAM             # Defined in the linker file
        .extern __SIZE_LOCAL_RAM                # Defined in the linker file
    .endif

    .equ WORD_SIZE_BYTES,           4
    .equ SRAM_WORD2_SHIFT,          3       # Shift for BYTES to WORDS / 2
    .equ BLOCK_SIZE_BYTES,          64      # RAM initialisation to be done in 64-byte blocks
    .equ SRAM_BLOCK_SHIFT,          6       # Shift for BYTES to BLOCKS

# Defines for the different options of the RESET-Configuration Halfword (used by the SSCM)
    .equ VLE,          0x01000000   # defines VLE-Code
    .equ MPC5700_ID,   0x005A0000   # RCHW boot ID for MPC5700 devices

    .equ RCHW_VAL, (VLE | MPC5700_ID)


#*************** Flash initialization constants ****************
#
# Definitions for FLASH_MCR (Module Configuration Register)
#
    .equ FLASH_MCR_RESET_VAL,   0x00000000
    .equ FLASH_MCR_ADDR,        0xFFFE0000

#*************************************************************

# Reset Status Register (Mode Entry Moule - MC_RGM)
    .equ MC_RGM_FES_ADDR,   0xFFFA8300  # Functional reset flags
    .equ F_SOFT,            28          # Software reset flag number.

# Self Test Status Register (Self Test Control Unit - SCCU)
    .equ STCU_MBSL_ADDR,    0xFFF44044  # MBIST Status flags
    .equ STCU_MBEL_ADDR,    0xFFF44050  # MBIST End flags
    .equ STCU_MBEL_VAL,     0x07FFFFFF  # Expected value - all RAM blocks are OK

# Flag pins for diagnostic purposes
#                                       # MSCR[x] = 0xFFFC0240 + n * 4
#                                       # GDPO[x] = 0xFFFC1300 + n
    .equ TPxx1_MSCR_ADDR,   0xFFFC0264  # (SIU_MSCR_OFFSET(SIU_BASE) + 4 * SIU_PIN_GPIO09) (A9 on dev board)
    .equ TPxx1_OUT_ADDR,    0xFFFC1309  # (SIU_GPDO_OFFSET(SIU_BASE) + SIU_PIN_GPIO09)
    .equ FLAG_OP_CONFIG,    0x02800000  # Configure as an o/p with 10pF push-pull drive and min slewrate, drive in SAFE mode

# Boot Pin (used here to signal an exception)
    .equ BOOT_PIN_PCR_ADDR, 0xC3F900E6  # (SIU_PCR_OFFSET(SIU_BASE) + 2 * SIU_PIN_GPIO83) (F[3])
    .equ BOOT_PIN_OUT_ADDR, 0xC3F90653  # (SIU_GPDO_OFFSET(SIU_BASE) + SIU_PIN_GPIO83)

# Software Watchdog Timer (SWT) registers
    .equ SWT_CR_ADDR,       0xFC050000  # SWT control register
    .equ SWT_SR_ADDR,       0xFC050010  # SWT service register
    .equ SWT_KEY_ONE,       0xC520      # SWT unlock keys
    .equ SWT_KEY_TWO,       0xD928
    .equ SWT_CONFIG,        0x8000010A  # SWT Config - WD off (CPU0 access enabled, reset on invalid access, use osc clock, freeze on debug)

# Mode Entry Moule (MC_ME) registers
    .equ ME_SAFE_MC_ADDR,   0xFFFB8028  # Safe mode control register
    .equ PDO,               8           # I/O Power Down Control bit number

# INTC register
    .equ INTC_IACKR_ADDR,   0xFC040020  # Interrupt vector register
    .equ INTC_EOIR_ADDR,    0xFC040030  # End of interrupt register

# Constants for Cache configuration
    .equ L1CSR0,  1010
    .equ L1CSR1,  1011
    .equ ICE,     1
    .equ ICINV,   (1<<(31-30))      # invalidate
    .equ ICABT,   (1<<(31-29))      # operation aborted
    .equ ICECE,   (1<<(31-15))      # enable error checking
    .equ IC_SETUP,  (ICECE | ICINV) # invalidate
    .equ IC_CONFIG, (ICECE | ICE)   # Enable
    .equ DCE,     1
    .equ DCINV,   (1<<(31-30))      # invalidate
    .equ DCABT,   (1<<(31-29))      # operation aborted
    .equ DCECE,   (1<<(31-15))      # enable error checking
    .equ DC_SETUP,  (DCECE | DCINV) # invalidate
    .equ DC_CONFIG, (DCECE)         # Disable by default

# Branch Target Buffer
    .equ BUCSR,  1013
    .equ BTB_CONFIG, 0x201      # Invalidate and enable Branch Target Buffer


###############################################################################
# Reset Configuration Half-word and start vector.
###############################################################################
#
# Reset Configuration Half-word.
# This is always generated in the boot_rcw area so brp code and applications can be run
# stand alone if there is no boot.  If there is, then brp code and applications will be
# entered from the boot, bypassing their start-up code.

    .section .boot_rcw              # this section defines the RESET configuration halfword for the SSCM

    .long   RCHW_VAL                # this is the "magic word" which allows the SSCM to find the boot-block
    .long   _start                  # pointer to startup-code
    e_b     _start                  # Jump instruction at offset 0x00000008 for boot prog.
    .long   0xffffffff              # Space for the sector checksum

    .ifndef  BOOT_CODE
        .ifndef  BRP_CODE
            .ifndef  APPS_CODE

                .error "No RCW header block specified. Assemble with -DBOOT_CODE or -DBRP_CODE or -DAPPS_CODE"

            .endif                  # End of .ifdef APPS_CODE
        .endif                      # End of .ifdef BRP_CODE
    .endif                          # End of .ifdef BOOT_CODE

###############################################################################
# START OF CODE
###############################################################################

    .ifndef  BOOT_CODE
        .section .boot_startup      # Application startup code in boot sector (for stand-alone debugger testing only)
    .else
        .text                       # Normal start-up code
    .endif


###############################################################################
# Reset Entry Point.
###############################################################################
#
#   If starting from reset the MMU will be set with TLB0 having a 4k page size
#   The first step is therefore to set up the CPU related registers such as registers,
#   IVORs, BTB and Cache.
#   NOTE we have no stack, RAM or even peripheral registers at this stage.
#

###############################################################################
# START OF CODE
###############################################################################

    .globl      _start
    .align      2

_start:

###############################################################################
# CPU_init - CPU Initialisation.
###############################################################################
# Exit:         IVPR, BTB and Cache initialised.
# Regs:         R3, R4, R5, R6 destroyed.
#
# This function sets up the cache and Branch Target Buffer (BTB).
# On exit the cache will be enabled, the BTB will be enabled and the
#
# On entry R0 must point to the first of three exception routines for the CPU.
# The three entry points must be 16 bytes apart and all in the same 64k page.
# The first entry point must also be a multiple of 16.
# The three entry points are for Hardware errors, Software errors and ECC errors.
#

# The E200Z4 core needs its registers initialising before they are used
# otherwise in Lock Step mode the two cores will contain different random data.
# If this is stored to memory (e.g. stacked) it will cause a Lock Step error.

    se_sub  r0,  r0
    se_mr   r1,  r0
    se_mr   r2,  r0
    se_mr   r7,  r0     # r3 to r6 used below
    se_mtar r8,  r0
    se_mtar r9,  r0
    se_mtar r10, r0
    se_mtar r11, r0
    se_mtar r12, r0
    se_mtar r13, r0
    se_mtar r14, r0
    se_mtar r15, r0
    se_mtar r16, r0
    se_mtar r17, r0
    se_mtar r18, r0
    se_mtar r19, r0
    se_mtar r20, r0
    se_mtar r21, r0
    se_mtar r22, r0
    se_mtar r23, r0
    se_mr   r24, r0
    se_mr   r25, r0
    se_mr   r26, r0
    se_mr   r27, r0
    se_mr   r28, r0
    se_mr   r29, r0
    se_mr   r30, r0
    se_mr   r31, r0

# Init any other CPU register which might be stacked (before being used).

    mtcrf   0xFF,  r0       # Condition code register
    se_mtctr  r0
    se_mtlr   r0
    mtspr   SPRG0, r0
    mtspr   SPRG1, r0
    mtspr   SPRG2, r0
    mtspr   SPRG3, r0
    mtspr   SRR0,  r0
    mtspr   SRR1,  r0
    mtspr   CSRR0, r0
    mtspr   CSRR1, r0
    mtspr   MCSRR0, r0
    mtspr   MCSRR1, r0
    mtspr   MCSR,  r0
    mtspr   MCAR,  r0
    mtspr   DEAR,  r0
    mtspr   IVPR,  r0
    mtspr   USPRG0, r0
    mtspr   XER,   r0
    mtspr   ESR,   r0

#   Unlock and invalidate the caches - (destroys R0).
    e_bl    InvalidateInstructionCache

#   Set up the Branch Target Buffer
    e_li    r3, BTB_CONFIG@l
    mtspr   BUCSR, r3

# define the IVPR to point to one of three entry points into a generic error routine
    e_lis   r3, Error_0@h       # Point R3 at the error handler
    e_or2i  r3, Error_0@l
    mtspr   IVPR,  r3           # Put the higher 24 bits into the IVPR register (lower 8 bits are ignored)

# Check and disable the data cache - (destroys R0).
    se_sub  r3, r3              # Cache disabled on exit
    e_bl    InvalidateDataCache

# Turn the I/O on in SAFE mode so we can still see the boot pin if there is an error.
    e_lis   r5, ME_SAFE_MC_ADDR@h
    e_or2i  r5, ME_SAFE_MC_ADDR@l
    se_li   r7, 0
    se_stw  r7,0(r5)

# Set TPxx1 to 'output' to allow it to be used for program tracing/timing
# NOTE - the line is tri-state until enabled
    e_lis   r5, TPxx1_MSCR_ADDR@h
    e_or2i  r5, TPxx1_MSCR_ADDR@l
    e_lis   r6, FLAG_OP_CONFIG@h
    e_or2i  r6, FLAG_OP_CONFIG@l
    se_stw  r6, 0(r5)           # Configure TPxx1 as an output (must write 32 bits)

# Set TPxx1 low to indicate program start
    e_lis   r5, TPxx1_OUT_ADDR@h
    e_or2i  r5, TPxx1_OUT_ADDR@l
    se_li   r6, 0
    se_stb  r6, 0(r5)           # Set TPxx1 low

#***********************************************************************
# Disable the watchdog
#***********************************************************************
    e_lis   r5, SWT_CR_ADDR@h
    e_or2i  r5, SWT_CR_ADDR@l

    # Disable the soft lock
    e_li    r6, SWT_KEY_ONE
    se_stw  r6, 16(r5)          # Write first key
    e_li    r6, SWT_KEY_TWO
    se_stw  r6, 16(r5)          # Write second key

    # Turn it off
    e_lis   r6, SWT_CONFIG@h
    e_or2i  r6, SWT_CONFIG@l
    se_stw  r6, 0(r5)

#*************************************************************************
#* It has been found on the Leopard that sometimes when using the LAUTERBACH
#* that PGM and EHV are set to 1 and are not cleared with a reset.
#* This stops the flash from being written to.
#* If you then set the values to 0 using the Lauterbach every thing works correctly.
#* So force the MCR to it's reset value.
#*
#* We seem to have similar problems on the Panther too so try clearing these bits.
#*************************************************************************
    e_lis   r5, FLASH_MCR_ADDR@h
    e_or2i  r5, FLASH_MCR_ADDR@l
    e_lis   r6, FLASH_MCR_RESET_VAL@h
    e_or2i  r6, FLASH_MCR_RESET_VAL@l
    se_stw  r6, 0(r5)

#**************************************************
# Decide whether the reset was a Software reset or not. Only test the RAM if it was not.
# NOTE - the software reset bit is not cleared by this code - the user must do it later if required.

    e_lis    r5, MC_RGM_FES_ADDR@h
    e_or2i   r5, MC_RGM_FES_ADDR@l
    se_lwz   r6, 0(r5)          # Read Reset Status Register
    se_btsti r6, F_SOFT         # Test for Software Reset
    se_bne   skipRAMtest

.ifdef  RAM_CODE                # Skip the RAM test for RAM based test programmes
    se_b    skipRAMtest
.endif

.ifdef  BOOT_CODE               # For Boot code check for MBIST errors before initialising RAM

# Check for BIST RAM errors
    e_lis   r0, STCU_MBEL_ADDR@h
    e_or2i  r0, STCU_MBEL_ADDR@l
    se_lwz  r0, 0(r0)           # Read MBIST End Register
    e_lis   r1, STCU_MBEL_VAL@h
    e_or2i  r1, STCU_MBEL_VAL@l
    se_and  r0, r1
    se_cmp  r0, r1
    e_bne   RAM_err             # Assume a fault if they haven't all finished
    e_lis   r0, STCU_MBSL_ADDR@h
    e_or2i  r0, STCU_MBSL_ADDR@l
    se_lwz  r0, 0(r0)           # Read MBIST End Register
    se_and  r0, r1
    se_cmp  r0, r1
    e_bne   RAM_err             # Assume a fault if they haven't all passed
.endif

# Test the main RAM
    e_lis   r0, __START_INTERNAL_RAM@h
    e_or2i  r0, __START_INTERNAL_RAM@l
    e_lis   r1, __SIZE_INTERNAL_RAM@h
    e_or2i  r1, __SIZE_INTERNAL_RAM@l
    e_bl    RAM_init

 skipRAMtest:

# Test the CPU RAM
    .ifdef  APPS_CODE
        e_lis   r0, __START_D_MEM_RAM@h
        e_or2i  r0, __START_D_MEM_RAM@l
        e_lis   r1, __SIZE_D_MEM_RAM@h
        e_or2i  r1, __SIZE_D_MEM_RAM@l
    .else
        e_lis   r0, __START_LOCAL_RAM@h
        e_or2i  r0, __START_LOCAL_RAM@l
        e_lis   r1, __SIZE_LOCAL_RAM@h
        e_or2i  r1, __SIZE_LOCAL_RAM@l
    .endif
    e_bl    RAM_init

###############################################################################
# Start of Application setup code - when called from boot.
###############################################################################

    .ifndef  BOOT_CODE

        e_b     _start_app          # Jump to the app / Brp as the boot would

        .ifdef  APPS_CODE

            .section .apps_rcw      # Spoof this for the Application section so other tools can see it

            .long   0xaaaaaaaa      # Dummy boot signature to allow tools to check the app integrity
            .long   _start_app      # pointer to "startup-code"
            e_b     _start_app      # Jump instruction at offset 0x00000008 for boot prog.
            .long   0xffffffff      # Space for the sector checksum

        .endif

        .ifdef  BRP_CODE

            .section .brp_rcw      # Spoof this for the Brp code section so other tools can see it

            .long   0x77777777      # Dummy boot signature to allow tools to check the app integrity
            .long   _start_app      # pointer to "startup-code"
            e_b     _start_app      # Jump instruction at offset 0x00000008 for boot prog.
            .long   0xffffffff      # Space for the sector checksum
            .long   0x7e57c0de      # Brp code signature

        .endif

        .text                       # Now move to the normal code segment for the rest

_start_app:

    # define the IVPR to point to our error routine until the MCAL kicks in.
        e_lis   r3, Error_0@h       # Point R0 at the error handler
        e_or2i  r3, Error_0@l
        mtspr   IVPR,  r3           # Put the higher 24 bits into the IVPR register (lower 8 bits are ignored)

    # Clear the instruction cache in case any RAM code has changed - (destroys R0).
        e_bl    InvalidateInstructionCache

    # Clear and disable the data cache now the RAM map has changed - (destroys R0).
    # (The cache is left disabled above for the boot).
        se_sub  r3, r3              # Cache disabled on exit
        e_bl    InvalidateDataCache

    .endif                          # End of .ifndef BOOT_CODE

# Set TPxx1 high to indicate the end of the RAM initialisation / test
    e_lis   r5, TPxx1_OUT_ADDR@h
    e_or2i  r5, TPxx1_OUT_ADDR@l
    se_li   r7, 1
    se_stb  r7, 0(r5)               # Set TPxx1 high

#**************************************************
# Init Stack Pointer, etc.

    .ifdef  APPS_CODE
        .extern OS_iSpInitial_PA

        e_lis       r3, OS_iSpInitial_PA@ha
        lwz         r1, OS_iSpInitial_PA@l(r3)  # Initialize stack pointer r1
    .else
        e_lis       r1, __SP_INIT@h - 8 # Initialize stack pointer r1 to value in linker
        e_or2i      r1, __SP_INIT@l - 8 # command file and allow a dummy stack frame.
    .endif
    
    e_lis       r13, _SDA_BASE_@h   # Initialize r13 to sdata base
    e_or2i      r13, _SDA_BASE_@l   # (provided by linker).

    e_lis       r2, _SDA2_BASE_@h   # Initialize r2 to sdata2 base
    e_or2i      r2, _SDA2_BASE_@l   # (provided by linker).

    e_bl        __init_main         # Initialization of statics, then call main().
    e_b         exit                # Never returns.


#*************************************************************************
# Instruction Cache Initialisation:
# Invalide the instruction cache and wait for completion.
# If the operation is aborted then invalidate it again.
# The function waits until the operation is complete.
# The instruction cache is left enabled.
# Register R0 is destroyed.
#
InvalidateInstructionCache:
    se_isync
    msync                                   # Flush the store buffer
    e_lis   r0, IC_SETUP@h
    e_or2i  r0, IC_SETUP@l
    mtspr   L1CSR1, r0                      # Start the process

 inst_cache_loop:
    mfspr   r0, L1CSR1
    e_andi. r0, r0, ICABT                   # Check for abort
    e_bne   InvalidateInstructionCache      # Go and clear the cache again if so
    mfspr   r0, L1CSR1
    e_andi. r0, r0, ICINV                   # Invalidate still pending ?
    e_bne   inst_cache_loop
    e_lis   r0, IC_CONFIG@h                 # Enable the data cache
    e_or2i  r0, IC_CONFIG@l
    se_isync
    msync
    mtspr   L1CSR1, r0

    se_blr

#*************************************************************************
# Data Cache Initialisation:
# Invalide the data cache and wait for completion.
# If the operation is aborted then invalidate it again.
# The function waits until the operation is complete.
# The data cache is left either enabled if R3 is non-zero or disabled if R3 = 0.
# Register R0 is destroyed.
#
# C prototype       void InvalidateDataCache(unsigned int d);
#
    .globl  InvalidateDataCache
                                            # External entry point to data cache initialisation
InvalidateDataCache:                        # void InvalidateDataCache(void);
    se_isync
    msync                                   # Flush the store buffer
    e_lis   r0, DC_SETUP@h
    e_or2i  r0, DC_SETUP@l
    mtspr   L1CSR0, r0                      # Start the process

 data_cache_loop:
    mfspr   r0, L1CSR0
    e_andi. r0, r0, ICABT                   # Check for abort
    e_bne   InvalidateDataCache             # Go and clear the data cache again if so
    mfspr   r0, L1CSR0
    e_andi. r0, r0, ICINV                   # Invalidate still pending ?
    e_bne   data_cache_loop
    e_lis   r0, DC_CONFIG@h                 # Enable the data cache
    e_or2i  r0, DC_CONFIG@l
    se_and. r3, r3
    e_beq   data_cache_set
    e_ori   r0, r0, DCE
 data_cache_set:
    se_isync
    msync
    mtspr   L1CSR0, r0

    se_blr

#*************************************************************************
# Error handling:
# Implemented as an endless loop that toggles the Boot pin according to the error source
# The Boot pin is driven low for 1ms then high for n ms where n is the fault code
# The timing is set up for 16MHz operation with the cache enabled
#
# C prototype       void Send_hardware_fault(int c);
#
    .globl  Send_hardware_fault
                                            # External entry point to failure handler
Send_hardware_fault:                        # void Send_hardware_fault(int c);
    se_mr   r5, r3                          # C argument 1
    e_b     error_indicator

    .align  8                               # Needs to start on a 256 byte boundary
Error_0:
HW_err:                                     # Vector 0 - Critical input.
    e_li    r5, 1
    e_b     error_indicator
    .align  4
SW_err:                                     # Vector 1 - Machine Check or NMI.
    e_li    r5, 2
    e_b     error_indicator
    .align  4
IVOR2_err:                                  # Vector 2 - Access control.
    e_li    r5, 3
    e_b     error_indicator
    .align  4
    e_li    r5, 4                           # Vector 3 - Access control.
    e_b     error_indicator
    .align  4
.ifndef INT_HANDLER
IVOR4_Handler:
.endif
    e_b     IVOR4_Handler                   # Vector 4 - Interrupt.
    .align  4
    e_li    r5, 5                           # Vector 5 - Alignment.
    e_b     error_indicator
    .align  4
    e_li    r5, 6                           # Vector 6 - Illegal, privelaged, trap.
    e_b     error_indicator
    .align  4
    e_li    r5, 7                           # Vector 7 - Performance monitor.
    e_b     error_indicator
    .align  4
    e_li    r5, 8                           # Vector 8 - System Call.
    e_b     error_indicator
    .align  4
    e_li    r5, 9                           # Vector 9 - Debug.
    e_b     error_indicator
    .align  4
    e_li    r5, 10                          # Vector 10 - Floating point exception.
    e_b     error_indicator
    .align  4
    e_li    r5, 11                          # Vector 11 - Floating point rounding.
    e_b     error_indicator
    .align  4
    e_li    r5, 12                          # Vector 12 - Reserved.
    e_b     error_indicator
    .align  4
    e_li    r5, 13                          # Vector 13 - Reserved.
    e_b     error_indicator
    .align  4
    e_li    r5, 14                          # Vector 14 - Reserved..
    e_b     error_indicator
    .align  4
    e_li    r5, 15                          # Vector 15 - Reserved..
    e_b     error_indicator

.ifndef  BRP_CODE

    .extern MPC5500_IVOR1Handler
    .align  8                               # Needs to start on a 256 byte boundary
Error_1:                                    # (should follow on from the vectors above)
    e_li    r5, 1                           # Vector 0 - Critical input.
    e_b     error_indicator
    .align  4
    e_b     MPC5500_IVOR1Handler            # ECC handler for use from C
    .align  4
    e_li    r5, 3                           # Vector 2 - Access control.
    e_b     error_indicator
    .align  4
    e_li    r5, 4                           # Vector 3 - Access control.
    e_b     error_indicator
    .align  4
    e_b     IVOR4_Handler                   # Vector 4 - Interrupt.
    .align  4
    e_li    r5, 5                           # Vector 5 - Alignment.
    e_b     error_indicator
    .align  4
    e_li    r5, 6                           # Vector 6 - Illegal, privelaged, trap.
    e_b     error_indicator
    .align  4
    e_li    r5, 7                           # Vector 7 - Performance monitor.
    e_b     error_indicator
    .align  4
    e_li    r5, 8                           # Vector 8 - System Call.
    e_b     error_indicator
    .align  4
    e_li    r5, 9                           # Vector 9 - Debug.
    e_b     error_indicator
    .align  4
    e_li    r5, 10                          # Vector 10 - Floating point exception.
    e_b     error_indicator
    .align  4
    e_li    r5, 11                          # Vector 11 - Floating point rounding.
    e_b     error_indicator
    .align  4
    e_li    r5, 12                          # Vector 12 - Reserved.
    e_b     error_indicator
    .align  4
    e_li    r5, 13                          # Vector 13 - Reserved.
    e_b     error_indicator
    .align  4
    e_li    r5, 14                          # Vector 14 - Reserved..
    e_b     error_indicator
    .align  4
    e_li    r5, 15                          # Vector 15 - Reserved..
    e_b     error_indicator

#*************************************************************************
# ECC Error handling:
# At startup the ECC errors vector through Error_0 to toggle the boot pin.
# In main() the C function void Set_ECC_Vector(void) should be called to redirect
# ECC errors to the MCAL provided handler.
#
# C prototype       void Set_ECC_Vector(void);
#
    .globl  Set_ECC_Vector
    .ifdef  APPS_CODE
        .extern VTABLE
    .endif
    
Set_ECC_Vector:
    .ifdef  APPS_CODE
        e_lis   r3, VTABLE@h
        e_or2i  r3, VTABLE@l
    .else
        e_lis   r3, Error_1@h
        e_or2i  r3, Error_1@l
    .endif
    mtspr   IVPR,  r3                       # define IVOR1 routine (ECC errors use this)
    se_blr

.endif                                      # End of .ifndef BRP_CODE

RAM_err:
    e_li    r5, 4
 error_indicator:
    wrteei  0                               # Don't want any interrupts here.
    e_li    r6, 0x0A20  # 1 ms low (at 16MHz)
    mullw.  r4, r6, r5  # n ms high

    # Set the Boot pin to 'output' to allow it to be used for signalling
#    e_lis   r3, BOOT_PIN_PCR_ADDR@h
#    e_or2i  r3, BOOT_PIN_PCR_ADDR@l
#    e_li    r7, FLAG_OP_CONFIG
#    se_sth  r7, 0(r3)   # Configure the Boot pin as an output
#
#    e_lis   r3, BOOT_PIN_OUT_ADDR@h
#    e_or2i  r3, BOOT_PIN_OUT_ADDR@l
#    se_li   r7, 0
#    se_stb  r7, 0(r3)   # Set the Boot pin low
 err_loop0:
#    se_lbz  r7, 0(r3)   # Invert the boot pin
#    se_not  r7
#    se_stb  r7, 0(r3)
    se_mtctr r4
    se_btsti r7, 31
    se_bne  err_loop1
    se_mtctr r6
 err_loop1:             # Use the same wait loop for low and high periods to ensure...
    se_isync            # the same access timing for both.
    e_bdnz  err_loop1
    e_b     err_loop0


#*************************************************************************
# Interrupt handling:
#
# This interrupt handler works with the INTC Interrupt Controller in software
# vector mode.  It can work in two ways depening on the option INT_VECT.
#
# If INT_VECT is not defined all interrupts are sent to the C function
#
#   void InterruptHandler(int signal);
#
# The interrupt vector number from the INTC module is passed as an argument.
# The C function can then process the interrupt as required and can even use
# a vector table.  This is suitable for applications with few interrupts which
# do not require fast servicing.
#
# If the option INT_VECT is defined then the handler will vector using the value
# in the INTC module which must be set beforehand.  The vector table is defined
# in a C file and the INTC module is set up in C.  This allows a separate
# interrupt handler function for each interrupt.
#
# This routine is called by the CPU IVOR4 vector.  It saves the current context
# then fetches the interrupt routine vector from the INTC module and calls the
# interrupt handler as a normal C function.
#
.ifdef  INT_HANDLER

    .globl   IVOR4_Handler

    .align  4

IVOR4_Handler:
 IVOR4_prolog:                      # PROLOGUE
    e_stwu  r1, -0x50(r1)           # Create stack frame and store back chain
    se_stw  r0, 0x24(r1)            # Save working register r0
    mfSRR1  r0                      # Store SRR1 (must be done before enabling EE)
    se_stw  r0, 0x10(r1)
    mfSRR0  r0                      # Store SRR0 (must be done before enabling EE)
    se_stw  r0, 0x0C(r1)
    se_mfLR r0                      # Store LR (Store now since LR will be used for ISR Vector)
    se_stw  r0, 0x14(r1)

    se_stw  r3, 0x28(r1)            # Store a working register
    e_lis   r3, INTC_IACKR_ADDR@h   # Store address of IACKR in r3
    e_or2i  r3, INTC_IACKR_ADDR@l
    se_lwz  r3, 0(r3)               # Store contents of IACKR in r3 (this is the vector table address)

.ifdef  INT_VECT
    se_lwz  r0, 0(r3)               # Read ISR address from ISR Vector Table address
    se_mtLR r0                      # Store ISR address to LR to use for branching later
.else
    se_isync                        # Wait a couple clocks after reading IACKR
.endif

    wrteei  1                       # Set MSR[EE]=1 (must wait a couple clocks after reading IACKR)

    e_stw   r12, 0x4C(r1)           # Store rest of gprs
    e_stw   r11, 0x48(r1)
    e_stw   r10, 0x44(r1)
    e_stw   r9,  0x40(r1)
    e_stw   r8,  0x3C(r1)
    se_stw  r7,  0x38(r1)
    se_stw  r6,  0x34(r1)
    se_stw  r5,  0x30(r1)
    se_stw  r4,  0x2c(r1)

    mfCR    r0                      # Store CR
    se_stw  r0,  0x20 (r1)
    mfXER   r0                      # Store XER
    se_stw  r0,  0x1C (r1)
    se_mfCTR  r0                    # Store CTR
    se_stw  r0,  0x18 (r1)

    e_rlwinm r3, r3, 30, 23, 31     # Get the vector number in r3

.ifdef  INT_VECT
    se_blrl                         # Branch to ISR, but return here
.else
    .globl  InterruptHandler
    bl      InterruptHandler
.endif

 IVOR4_epilog:                      # EPILOGUE
#                                   # RESTORE CONTEXT
    mbar    0                       # Ensure interrupt flag has finished clearing
#                                   # before writing to INTC_EIOR
    se_lwz  r0, 0x14(r1)            # Restore LR
    se_mtLR r0
    se_lwz  r0, 0x18(r1)            # Restore CTR
    se_mtCTR r0
    se_lwz  r0, 0x1C(r1)            # Restore XER
    mtXER   r0
    se_lwz  r0, 0x20(r1)            # Restore CR
    mtcrf   0xff, r0
    se_lwz  r3,  0x28(r1)
    se_lwz  r5,  0x30(r1)
    se_lwz  r6,  0x34(r1)
    se_lwz  r7,  0x38(r1)
    e_lwz   r8,  0x3C(r1)
    e_lwz   r9,  0x40(r1)
    e_lwz   r10, 0x44(r1)
    e_lwz   r11, 0x48(r1)
    e_lwz   r12, 0x4C(r1)

    wrteei  0                       # Disable interrupts

    se_li   r0,0
    e_lis   r4, INTC_EOIR_ADDR@h    # Load upper half of EIOR address to r4
    e_or2i  r4, INTC_EOIR_ADDR@l    # Load lower half of EIOR address to r4
    se_stw  r0, 0(r4)               # Write 0 to INTC_EOIR
    se_lwz  r4,  0x2C (r1)          # Restore r4
    se_lwz  r0,  0x0C (r1)          # Restore SRR0
    mtSRR0  r0
    se_lwz  r0,  0x10 (r1)          # Restore SRR1
    mtSRR1  r0
    se_lwz  r0,  0x24 (r1)          # Restore working register
    e_addi  r1,  r1, 0x50           # Restore space on stack

    se_rfi                          # End of Interrupt - re-enables interrupts.

.endif      # INT_HANDLER

#**************************************************
# RAM Init
# Init is done in blocks of 64 Bytes
#
#   Registers:
#   On entry R0 contains the RAM start address and R1 the RAM length in bytes.
#
#   R0      RAM start address
#   R1      RAM size (bytes)
#   R2      -
#   R3      -
#   R4      -
#   R5      RAM pointer
#   R6      -
#   R7      Used to load the counter
#   R16-R31 Used to init the RAM
#   CTR     Used to count RAM blocks.
#
RAM_init:
    se_li   r31, 0

 final_init:
    se_mr   r30, r31
    se_mr   r29, r31
    se_mr   r28, r31
    se_mr   r27, r31
    se_mr   r26, r31
    se_mr   r25, r31
    se_mr   r24, r31
    se_mtar r23, r31
    se_mtar r22, r31
    se_mtar r21, r31
    se_mtar r20, r31
    se_mtar r19, r31
    se_mtar r18, r31
    se_mtar r17, r31
    se_mtar r16, r31

    se_mr    r5, r0                     # base address of the internal SRAM
    se_mr    r7, r1                     # calculate the number of RAM blocks
    se_srawi r7, SRAM_BLOCK_SHIFT
    se_mtctr r7                         # configure count register for writing to SRAM

 sram_loop1:
    e_stmw  r16, 0(r5)                  # write 16 registers to SRAM (64 byte write)
    e_addi  r5, r5, BLOCK_SIZE_BYTES    # increment the ram ptr by the block size
    e_bdnz  sram_loop1                  # loop for all SRAM

    se_blr
