/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: ccp.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:49CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

/************************************************************/
/* GLOBAL QAC WARNING SUPPRESSION                           */
/************************************************************/

/*  DEVIATION:      0492
    DESCRIPTION:    Array subscripting applied to a function parameter declared as a pointer.
    JUSTIFICATION:  This file contains well used legacy code. The QAC help text (below) associated
    with this warning also implies that it is a question of company coding standards rather than
    outright 'bad' code:-

    "This is perfectly legitimate in the C language providing the pointer addresses
    an array element; but some coding standards recommend that if a parameter refers to an
    array, it should be declared as an array."  */
/* PRQA S 0492 EOF*/

/*  DEVIATION:      0841
    DESCRIPTION:    Use of #undef is not recommended in some programming standards.
    JUSTIFICATION:  Deviation due to the use of legacy code. */
/* PRQA S 0841 EOF */

/*  DEVIATION:      0842
    DESCRIPTION:    Macro #define'd or #undef'd within a block.
    JUSTIFICATION:  Deviation due to the use of legacy code. */
/* PRQA S 0842 EOF */

/*  DEVIATION:      2215
    DESCRIPTION:    This indentation is not consistent with configured depth.
    JUSTIFICATION:  To improve readability, we break this rule by indenting after a conditional compilation flag.
                    e.g we believe that
                    #ifdef CCP_TESTMODE
                        static void ccpPrintDaqList( CCP_BYTE daq );
                    #endif
                    reads better than
                    #ifdef CCP_TESTMODE
                    static void ccpPrintDaqList( CCP_BYTE daq );
                    #endif  */
/* PRQA S 2215 EOF */

/*  DEVIATION:      2006
    DESCRIPTION:    <various> have more that has more than one 'return' path.
    JUSTIFICATION:  Deviation due to the use of legacy code. */
/* PRQA S 2006 EOF */

/*  DEVIATION:      4700
    DESCRIPTION:    Metric value out of threshold range 
    JUSTIFICATION:  Deviation due to the use of legacy code. */
/* PRQA S 4700 EOF */

/*  DEVIATION:      3440
    DESCRIPTION:    Result of ++ or -- operator used in expression.
    JUSTIFICATION:  Deviation necessary to allow generation of fast optimised
                    code in a time critical section.
                    Changing the code would require the generated assembler code to be
                    re-optimised. */
/* PRQA S 3440 EOF */

/*  DEVIATION:      0770
    DESCRIPTION:    A continue statement has been used.
    JUSTIFICATION:  Deviation due to the use of legacy code.
*/
/* PRQA S 0770 EOF */

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#ifdef CCP_TESTMODE
    #include <stdio.h>
#endif
#include "can.h"
#include "bootstrp.h"  /* for T_REPROG_INFO_TYPE */
#include "ccppar.h"
#include "ccp.h"
#include "flsh_int.h"
#include "sw_utils.h"
#include "comms.h"
#include "pack_id.h"


#ifndef C_DISABLE_CCP

    /*************************************************************/
    /*      GLOBAL VARIABLES                                     */
    /*************************************************************/

    /* CCP Definitions and Parameters */

    /******************************************************************************/
    /* Version check                                                              */
    /******************************************************************************/
    #if( CCP_DRIVER_VERSION != 142)
        #error "Source and Header file of CCP-Module inconsistent!"
    #endif
    #if( CCP_DRIVER_BUGFIX_VERSION != 0)
        #error "Source and Header file of CCP-Module inconsistent!"
    #endif

    #if( CCP_DRIVER_VERSION > 255)
        #error "Version decreased in CCP-Module"
    #endif

    /*--------------------------------------------------------------------------*/
    /* Performance measurements */

    #ifndef CCP_PROFILE
        #define SET_PORT_BIT(i)
        #define RST_PORT_BIT(i)
    #else
        /*
        t[0] - ccpCommand
        t[1] - ccpCallBack
        t[2] - ccpBackground
        t[3] - ccpDaq
        */
        unsigned int t0[4],t[4];
        #define SET_PORT_BIT(i) t0[i-1]=ccpGetTimestamp();
        #define RST_PORT_BIT(i) t[i-1]=T3-t0[i-1];
    #endif

    /*--------------------------------------------------------------------------*/
    /* ROM */
    /*--------------------------------------------------------------------------*/

    #define ccpStationId Boot_ID

    /*--------------------------------------------------------------------------*/
    /* RAM */
    /*--------------------------------------------------------------------------*/

    /*
       The following structure containes all RAM locations needed by the CCP driver
       It has to be word aligned on a C167 !!!
    */

    /* ##Hp - rename struct ccp */
    CCP_RAM struct ccp ccp;

    /*************************************************************/
    /*      PRIVATE FUNCTION DECLARATIONS                        */
    /*************************************************************/
    #ifdef CCP_SEND_QUEUE
        static void ccpQueueInit(void);
        static CCP_BYTE ccpQueueWrite(const ccpMsg_t *msg);
    #endif
    static CCP_BYTE ccpWriteMTA( CCP_BYTE n, CCP_BYTE size, const CCP_BYTEPTR d );
    static CCP_BYTE ccpReadMTA( CCP_BYTE n, CCP_BYTE size, CCP_BYTEPTR d );
    #ifdef CCP_DAQ
        static CCP_BYTE ccpClearDaqList( CCP_BYTE daq );
        static CCP_BYTE ccpPrepareDaq(  CCP_BYTE daq, CCP_BYTE last, CCP_BYTE eventChannel, CCP_WORD prescaler );
        static CCP_BYTE ccpStartDaq( CCP_BYTE daq );
        static void ccpStartAllPreparedDaq(void);
        static void ccpStopDaq ( CCP_BYTE daq );
        static void ccpStopAllDaq( void );
        #ifndef CCP_SEND_QUEUE
            static void ccpSendDtm( void );
        #endif

        #ifdef CCP_SEND_SINGLE
            static void ccpSampleAndSendNextDtm( void );
        #else
            static int ccpSampleAndTransmitDtm( CCP_BYTE pid, CCP_BYTE daq, CCP_BYTE odt );
        #endif
    #endif /* CCP_DAQ */

    #ifdef CCP_TESTMODE
        #ifdef CCP_DAQ
            static void ccpPrintDaqList( CCP_BYTE daq );
        #endif
    #endif


    /*************************************************************/
    /*      CODE                                                 */
    /*************************************************************/

    /*--------------------------------------------------------------------------*/
    /* Transmit */
    /*--------------------------------------------------------------------------*/

    /* Send a CRM, if no other message is pending */

    void ccpSendCrm( void )
    {
        /*  DEVIATION:     3138
            DESCRIPTION:   Null statement is located close to other code or comments.
            JUSTIFICATION: This warning can be ignored as the macro CCP_DISABLE_INTERRUPT is empty at
            the moment but could be populated in the future.*/
        /* PRQA S 3138 01*/
        CCP_DISABLE_INTERRUPT;

        if ((ccp.SendStatus&CCP_SEND_PENDING) != 0)
        {
            ccp.SendStatus |= CCP_CRM_REQUEST;
        }
        else
        {
            ccp.SendStatus |= CCP_CRM_PENDING;
            ccpSend(ccp.Crm);
        }
        /*  DEVIATION:     3138
            DESCRIPTION:   Null statement is located close to other code or comments.
            JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
            the moment but could be populated in the future.*/
        /* PRQA S 3138 01*/
        CCP_ENABLE_INTERRUPT;
    }


    /* Send a DTM, if no other message is pending */
    #ifdef CCP_DAQ
        #ifndef CCP_SEND_QUEUE
            static void ccpSendDtm( void )
            {
                /*  DEVIATION:     3138
                    DESCRIPTION:   Null statement is located close to other code or comments.
                    JUSTIFICATION: This warning can be ignored as the macro CCP_DISABLE_INTERRUPT is empty at
                    the moment but could be populated in the future.*/
                /* PRQA S 3138 01*/
                CCP_DISABLE_INTERRUPT;

                if ((ccp.SendStatus&CCP_SEND_PENDING) != 0)
                {
                    ccp.SendStatus |= CCP_DTM_REQUEST;
                }
                else
                {
                    ccp.SendStatus |= CCP_DTM_PENDING;
                    ccpSend(ccp.Dtm);
                }
                    /*  DEVIATION:     3138
                        DESCRIPTION:   Null statement is located close to other code or comments.
                        JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
                        the moment but could be populated in the future.*/
                    /* PRQA S 3138 01*/
                    CCP_ENABLE_INTERRUPT;
            }
        #endif
    #endif


    /*--------------------------------------------------------------------------*/
    /* Transmit Queue */
    /*--------------------------------------------------------------------------*/
    #ifdef CCP_SEND_QUEUE

        static void ccpQueueInit(void)
        {
            ccp.Queue.len = 0;
            ccp.Queue.rp = 0;
        }

        static CCP_BYTE ccpQueueWrite(const ccpMsg_t *msg)
        {

            if (ccp.Queue.len>=CCP_SEND_QUEUE_SIZE)
            {
                return 0;
            }
            ccp.Queue.msg[(ccp.Queue.rp+ccp.Queue.len)%CCP_SEND_QUEUE_SIZE] = *msg;
            ccp.Queue.len++;
            return 1;
        }

    #endif


/*--------------------------------------------------------------------------*/
/* Handle MTAs (Memory-Transfer-Address) */
/*--------------------------------------------------------------------------*/

/* Assign a pointer to a MTA */
/* DEVIATION:      3453
   DESCRIPTION:    A function could probably be used instead of this function-like macro.
   JUSTIFICATION:  Macro is more efficant for mapping / decode
 */
/* PRQA S 3453 1 */
#define ccpSetMTA(n, p) (ccp.MTA[(n)] = (p))

    /* Write n bytes */
    static CCP_BYTE ccpWriteMTA( CCP_BYTE n, CCP_BYTE size, const CCP_BYTEPTR d )
    {
        BOOLEAN validStartAddr_bo;
        BOOLEAN validEndAddr_bo;

        /* Check memory access valid before proceding */
        /*  DEVIATION:     0306
            DESCRIPTION:   Cast between a pointer to object and an integral type
            JUSTIFICATION: Deviation due to the use of legacy code.
        */
        /* PRQA S 0306 2 */
        validStartAddr_bo = FOUNDATION_Memory_Access_Valid((U32)ccp.MTA[n], WRITE_ACCESS);
        validEndAddr_bo = FOUNDATION_Memory_Access_Valid((((U32)ccp.MTA[n] + size) - 1U), WRITE_ACCESS);

        if ((validStartAddr_bo == FALSE) ||    /* Start address */
            (validEndAddr_bo == FALSE))        /* End   address */
        {
            return CCP_WRITE_DENIED;
        }

        /* EEPROM write access */
        #ifdef CCP_WRITE_EEPROM
            CCP_BYTE r = ccpCheckWriteEEPROM(ccp.MTA[n],size,d);
            if (r) { /* EEPROM write access */
                ccp.MTA[n] += size;
                return r;
            }
        #endif

        /* Checked ram memory write access */
        #ifdef CCP_WRITE_PROTECTION
            if (!ccpCheckWriteAccess(ccp.MTA[n],size)) {
                ccp.MTA[n] += size;
                return CCP_WRITE_DENIED;
            }
        #endif

        /* double conversion */
        #ifdef CCP_DOUBLE_FLOAT
            if (size==8)
            {
                *(double*)ccp.MTA[n] = *(float*)d;
                #ifdef CCP_TESTMODE
                    if (gDebugLevel>=2) CCPPRINT("[ccpWriteMTA] conversion -> double %g\n",*(double*)ccp.MTA[n]);
                #endif
                ccp.MTA[n] += 8;
                return CCP_WRITE_OK;
            }
        #endif

        while (size-->0)
        {
            /* COSMIC Compiler Bug: *(ccp.MTA[n]++) = *(d++);  */
            *(ccp.MTA[n]) = *d;
             /*  DEVIATION:     0489
                DESCRIPTION:   Increment or decrement operation performed on pointer.
                JUSTIFICATION: Pointer arithemetic is used for efficient coding as large data
                buffers have to be modified in this section of code.*/
            /* PRQA S 0489 02*/
            ccp.MTA[n]++;
            d++;
        }
        return CCP_WRITE_OK;
    }

    /* Read n bytes */
    static CCP_BYTE ccpReadMTA( CCP_BYTE n, CCP_BYTE size, CCP_BYTEPTR d )
    {
        BOOLEAN validStartAddr_bo;
        BOOLEAN validEndAddr_bo;

        /* Check memory access valid before proceding */
        /*  DEVIATION:     0306
            DESCRIPTION:   Cast between a pointer to object and an integral type
            JUSTIFICATION: Deviation due to the use of legacy code.
        */
        /* PRQA S 0306 2 */
        validStartAddr_bo = FOUNDATION_Memory_Access_Valid((U32)ccp.MTA[n], READ_ACCESS);
        validEndAddr_bo = FOUNDATION_Memory_Access_Valid((((U32)ccp.MTA[n] + size) - 1U), READ_ACCESS);

        if ((validStartAddr_bo == FALSE) ||    /* Start address */
            (validEndAddr_bo == FALSE))        /* End   address */
        {
            return CCP_READ_DENIED;
        }

        /* EEPROM read access */
        #ifdef CCP_READ_EEPROM
            if (ccpCheckReadEEPROM(ccp.MTA[n],size,d))
            {
                ccp.MTA[n] += size;
                return CCP_READ_OK;
            }
        #endif

        /* double conversion */
        #ifdef CCP_DOUBLE_FLOAT
            if (size==8)
            {
                *(float*)d = (float)(*(double*)(ccp.MTA[n]));
                #ifdef CCP_TESTMODE
                    if (gDebugLevel>=2) CCPPRINT("[ccpReadMTA] conversion -> float %g\n",(double)(*(float*)d));
                #endif
                return CCP_READ_OK;
            }
        #endif

        while (size-->0)
        {
            *d = *(ccp.MTA[n]);
            /*  DEVIATION:     0489
                DESCRIPTION:   Increment or decrement operation performed on pointer.
                JUSTIFICATION: Pointer arithemetic is used for efficient coding as large data
                buffers have to be modified in this section of code.*/
            /* PRQA S 0489 02*/
            d++;
            ccp.MTA[n]++;
        }
        return CCP_READ_OK;
    }


    /*--------------------------------------------------------------------------*/
    /* Data Aquisition Setup */
    /*--------------------------------------------------------------------------*/

    #ifdef CCP_DAQ

        /* Clear DAQ list */
        static CCP_BYTE ccpClearDaqList( CCP_BYTE daq )
        {

            CCP_BYTEPTR p;
            CCP_BYTEPTR pl;

            if (daq>=CCP_MAX_DAQ)
            {
                return 0;
            }

            /* Clear this daq list to zero */
            /*  DEVIATION:     0310
                DESCRIPTION:   Casting to different object pointer type.
                JUSTIFICATION: Here a structure is accessed by a byte pointer , so that the structure
                elements can be cleared byte by byte irrespective of the structure elements */
            /* PRQA S 0310 1 */
            p = (CCP_BYTEPTR)&ccp.DaqList[daq];
            /*  DEVIATION:     0488
                DESCRIPTION:   Performing pointer arithmetic.
                JUSTIFICATION: Required to store the end pointer upto which the structure should be cleared*/
            /* PRQA S 0488 1 */
            pl = p+sizeof(ccpDaqList_t);
            while (p<pl)
            {
                /*  DEVIATION:     0489
                    DESCRIPTION:   Increment or decrement operation performed on pointer.
                    JUSTIFICATION: Needs to be done to access the next structure byte*/
                /* PRQA S 0489 1 */
                *p++ = 0;
            }

            /* @@@@ Not DAQ list specific */
            ccp.SessionStatus |= SS_DAQ;
            #ifdef CCP_SEND_SINGLE
                ccp.CurrentDaq = 0;
                ccp.CurrentOdt = 0;
            #endif
            #ifdef CCP_SEND_QUEUE
                ccpQueueInit();
            #endif

            return CCP_MAX_ODT;
        }

        /* Prepare DAQ */
        static CCP_BYTE ccpPrepareDaq(  CCP_BYTE daq, CCP_BYTE last, CCP_BYTE eventChannel, CCP_WORD prescaler )
        {

            if (daq>=CCP_MAX_DAQ)
            {
                return 0;
            }

            ccp.DaqList[daq].eventChannel = eventChannel;
            if (prescaler==0)
            {
                prescaler = 1;
            }
            ccp.DaqList[daq].prescaler = prescaler;
            ccp.DaqList[daq].cycle = 1;
            ccp.DaqList[daq].last = last;
            ccp.DaqList[daq].flags = DAQ_FLAG_PREPARED;
            return 1;
        }

        /* Start DAQ */
        static CCP_BYTE ccpStartDaq( CCP_BYTE daq )
        {

            if (daq>=CCP_MAX_DAQ)
            {
                return 0;
            }

            ccp.DaqList[daq].flags = DAQ_FLAG_START;
            ccp.SessionStatus |= ((CCP_BYTE)SS_RUN);

            #ifdef CCP_TIMESTAMPING
                ccpClearTimestamp();
            #endif

            return 1;
        }

        /* Start all prepared DAQs */
        static void ccpStartAllPreparedDaq(void)
        {

            CCP_BYTE q;

            for (q=0;q<CCP_MAX_DAQ;q++)
            {
                if (ccp.DaqList[q].flags==DAQ_FLAG_PREPARED)
                {
                    ccp.DaqList[q].flags = DAQ_FLAG_START;
                }
            }
            ccp.SessionStatus |= ((CCP_BYTE)SS_RUN);

            #ifdef CCP_TIMESTAMPING
                ccpClearTimestamp();
            #endif
        }

        /* Stop DAQ */
        static void ccpStopDaq ( CCP_BYTE daq )
        {

            CCP_BYTE i;

            if (daq>=CCP_MAX_DAQ)
            {
                return;
            }
            ccp.DaqList[daq].flags = 0;

            /* check if all DAQ lists are stopped */
            for (i=0;i<CCP_MAX_DAQ;i++)
            {
                if ((ccp.DaqList[i].flags&DAQ_FLAG_START) != 0)
                {
                    return;
                }
            }

            ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_RUN);
        }

        /* Stop all DAQs */
        static void ccpStopAllDaq( void )
        {

            CCP_BYTE q;

            for (q=0;q<CCP_MAX_DAQ;q++)
            {
                ccp.DaqList[q].flags = 0;
            }
            ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_RUN);
        }


        /*--------------------------------------------------------------------------*/
        /* Data Aquisition Processor */
        /*--------------------------------------------------------------------------*/

        #ifndef CCP_SEND_SINGLE

            /* Sample and transmit a DTM */
            static int ccpSampleAndTransmitDtm( CCP_BYTE pid, CCP_BYTE daq, CCP_BYTE odt )
            {
                #ifdef CCP_SEND_QUEUE
                    CCP_BYTE dtm[8];
                #else
                    #define dtm ccp.Dtm
                #endif
                #ifdef CCP_DAQ_BASE_ADDR
                    CCP_BYTEPTR p;
                #else
                    CCP_DAQBYTEPTR p;
                #endif
                #ifdef CCP_ODT_ENTRY_SIZE
                    CCP_BYTE s;
                    CCP_BYTE *d,*dl;
                    ccpOdtEntry_t *e,*el;
                #else
                    CCP_BYTE i;
                    ccpOdtEntry_t *e;
                #endif
                CCP_BYTE dtm_available = FALSE;

                /* PID */
                dtm[0] = pid;

                /* Assure data consistency */
                /*  DEVIATION:     3138
                    DESCRIPTION:   Null statement is located close to other code or comments.
                    JUSTIFICATION: This warning can be ignored as the macro CCP_DISABLE_INTERRUPT is empty at
                    the moment but could be populated in the future.*/
                /* PRQA S 3138 01*/
                CCP_DISABLE_INTERRUPT;

                /* Sample */
                #ifdef CCP_ODT_ENTRY_SIZE

                    e = &ccp.DaqList[daq].odt[odt][0];
                    /*  DEVIATION:     0488
                        DESCRIPTION:   Performing pointer arithmetic.
                        JUSTIFICATION: Pointer arithemetic used to store the end pointer for the pointer operation
                        below. Pointers have been used here for efficient coding and this code has been tested.*/
                    /* PRQA S 0488 01*/
                    el = e+8;
                    d = &dtm[1];
                    /*  DEVIATION:     0488
                        DESCRIPTION:   Performing pointer arithmetic.
                        JUSTIFICATION: Pointer arithemetic used to store the end pointer for the pointer operation
                        below. Pointers have been used here for efficient coding and this code has been tested.*/
                    /* PRQA S 0488 01*/
                    dl = d+7;
                    while ((d<dl) && (e<el) && ((e->ptr !=0)))
                    {
                        dtm_available = TRUE;
                        #ifdef CCP_DAQ_BASE_ADDR
                            p = (CCP_BYTEPTR)( e->ptr ) + CCP_DAQ_BASE_ADDR;
                        #else
                            p = e->ptr;
                        #endif
                        s = e->siz;
                        #ifdef CCP_DOUBLE_FLOAT
                            if (s==8) {
                                *(float*)d = (float)(*(double*)p);
                                s = 4;
                                #ifdef CCP_TESTMODE
                                    if (gDebugLevel>=2) CCPPRINT("[ccpSampleAndTransmitDtm] conversion -> float %g\n",*(float*)d);
                                #endif
                            } else
                        #endif
                        if (s==4)
                        {
                            /*  DEVIATION:     0310
                                DESCRIPTION:   Casting to different object pointer type.
                                JUSTIFICATION: Casting is done from byte to double word to copy 4 bytes at a time.
                                This is done for efficient coding and this code has been tested.*/
                            /* PRQA S 0310 01*/
                            *(CCP_DWORD*)d = *(CCP_DWORD*)p;
                        }
                        else if (s==2)
                        {
                            /*  DEVIATION:     0310
                                DESCRIPTION:   Casting to different object pointer type.
                                JUSTIFICATION: Casting is done from byte to  word to copy 2 bytes at a time.
                                This is done for efficient coding and this code has been tested.*/
                            /* PRQA S 0310 01*/
                            *(CCP_WORD*)d = *(CCP_WORD*)p;
                        }
                        else
                        {
                            *d = *p;
                        }
                        /*  DEVIATION:     0488
                            DESCRIPTION:   Performing pointer arithmetic.
                            JUSTIFICATION: Pointer arithmetic done to point to the next data location. Pointers
                            have been used here for efficient coding and this code has been tested.*/
                        /* PRQA S 0488 01*/
                        d += s;
                        /*  DEVIATION:     0489
                            DESCRIPTION:   Increment or decrement operation performed on pointer.
                            JUSTIFICATION: Increment done to point to the next data location.Pointers
                            have been used here for efficient coding and this code has been tested.*/
                        /* PRQA S 0489 01*/
                        e++;
                    }

                #else

                    e =  &ccp.DaqList[daq].odt[odt][0];
                    for (i=1;i<8;i++)
                    {
                        #ifdef CCP_DAQ_BASE_ADDR
                            p = (CCP_BYTEPTR)( (e++)->ptr ) + CCP_DAQ_BASE_ADDR;
                        #else
                            /*  DEVIATION:     0489
                                DESCRIPTION:   Increment or decrement operation performed on pointer.
                                JUSTIFICATION: Increment done to point to the next data location.Pointers
                                have been used here for efficient coding and this code has been tested.*/
                            /* PRQA S 0489 01*/
                            p = (e++)->ptr;
                        #endif
                        if (p != 0)
                        {
                            dtm_available = TRUE;
                            dtm[i] = *p;
                        }
                    }

                #endif

                if (dtm_available == TRUE)
                {
                    /* Optional for CANape: Put a timestamp in the first ODT (Byte6+7) of each DAQ */
                    #ifdef CCP_TIMESTAMPING
                        if (odt==0) {
                            *(CCP_WORD*)&dtm[6] = ccpGetTimestamp();
                        }
                    #endif

                    /* Queue or transmit the DTM */
                    #ifdef CCP_SEND_QUEUE

                        if ((ccp.SendStatus&CCP_SEND_PENDING) != 0)
                        {
                            /*  DEVIATION:     0310
                                DESCRIPTION:   Casting to different object pointer type.
                                JUSTIFICATION: This warning occurs as dtm is a U8 array and it is being cast to a
                                structur ccpMsg_t as function ccpQueueWrite() demands it.But ccpMsg_t has just one
                                element which is also an U8 array. So functionally this code works fine and warning
                                can be ignored.*/
                            /* PRQA S 0310 1*/
                            if (ccpQueueWrite((ccpMsg_t*)dtm) == 0)
                            {
                                /* Overun */
                                /*  DEVIATION:     3138
                                    DESCRIPTION:   Null statement is located close to other code or comments.
                                    JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
                                    the moment but could be populated in the future.*/
                                /* PRQA S 3138 01*/
                                CCP_ENABLE_INTERRUPT;
                                return 0;
                            }
                        }
                        else
                        {
                            ccp.SendStatus |= CCP_DTM_PENDING;
                            ccpSend(dtm);
                        }

                    #else

                        if ((ccp.SendStatus&CCP_DTM_REQUEST) != 0)
                        {
                            /* Overun */
                            /*  DEVIATION:     3138
                                DESCRIPTION:   Null statement is located close to other code or comments.
                                JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
                                the moment but could be populated in the future.*/
                            /* PRQA S 3138 01*/
                            CCP_ENABLE_INTERRUPT;
                            return 0;
                        }
                        if ((ccp.SendStatus&CCP_SEND_PENDING) != 0)
                        {
                            ccp.SendStatus |= CCP_DTM_REQUEST;
                        }
                        else
                        {
                            ccp.SendStatus |= CCP_DTM_PENDING;
                            ccpSend(dtm);
                        }

                    #endif
                }

                /*  DEVIATION:     3138
                    DESCRIPTION:   Null statement is located close to other code or comments.
                    JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
                    the moment but could be populated in the future.*/
                /* PRQA S 3138 01*/
                CCP_ENABLE_INTERRUPT;
                return 1;
            }

        #else

            /* Sample and transmit the next DTM in SEND_SINGLE mode */
            static void ccpSampleAndSendNextDtm( void )
            {

                CCP_BYTE i,j;
                CCP_DAQBYTEPTR p;
                ccpOdtEntry_t *e;
                CCP_BYTE dtm_available = FALSE;

                /* Request for DTM transmission pending */
                if (ccp.SendStatus&CCP_DTM_REQUEST) return;

                /* Find a DAQ list marked for transmission */
                for (i=0;i<CCP_MAX_DAQ;i++)
                {
                    if (ccp.DaqList[ccp.CurrentDaq].flags&DAQ_FLAG_SEND)
                    {
                        /* PID */
                        ccp.Dtm[0] = ccp.CurrentDaq*CCP_MAX_ODT+ccp.CurrentOdt;

                        /* Sample */
                        e =  &ccp.DaqList[ccp.CurrentDaq].odt[ccp.CurrentOdt][0];
                        for (j=1;j<8;j++) {
                            p = (e++)->ptr;
                            if (p) {
                                dtm_available = TRUE;
                                ccp.Dtm[j] = *p;
                            }
                        }

                        if (dtm_available == TRUE) {
                            /* Send */
                            ccpSendDtm();
                        }

                        /* Increment ODT */
                        if (++ccp.CurrentOdt>ccp.DaqList[ccp.CurrentDaq].last) {

                            /* DAQ list done */
                            ccp.CurrentOdt = 0;
                            ccp.DaqList[ccp.CurrentDaq].flags &= ~DAQ_FLAG_SEND;

                            /* Increment DAQ */
                            if (++ccp.CurrentDaq>=CCP_MAX_DAQ)
                            {
                                ccp.CurrentDaq = 0;
                            }
                        }
                        break;
                    }
                    else
                    {
                        /* Increment DAQ */
                        if (++ccp.CurrentDaq>=CCP_MAX_DAQ)
                        {
                            ccp.CurrentDaq = 0;
                        }
                    }
                }
            }
        #endif

        /* Data aquisition */
        void ccpDaq( CCP_BYTE eventChannel )
        {
            CCP_BYTE q,o;
            #ifndef CCP_SEND_SINGLE
                CCP_BYTE j;
            #endif

            if ((ccp.SessionStatus&SS_RUN) == 0)
            {
                return;
            }

            /*  DEVIATION:     3138
                DESCRIPTION:   Null statement is located close to other code or comments.
                JUSTIFICATION: This warning can be ignored as the macro SET_PORT_BIT is empty at
                the moment but could be populated in the future.*/
            /* PRQA S 3138 01*/
            SET_PORT_BIT(4); /* Timingtest */

            /*  DEVIATION:     3418
                DESCRIPTION:   The comma operator has been used in a for-loop header.
                JUSTIFICATION: Deviation due to the use of legacy code.
            */
            /* PRQA S 3418 01*/
            for (o=0,q=0; q<CCP_MAX_DAQ; o+=CCP_MAX_ODT,q++)
            {
                if ((ccp.DaqList[q].flags&DAQ_FLAG_START) == 0)
                {
                    continue;
                }

                if (ccp.DaqList[q].eventChannel!=eventChannel)
                {
                    continue;
                }
                if (--ccp.DaqList[q].cycle!=0)
                {
                    continue;
                }
                ccp.DaqList[q].cycle = ccp.DaqList[q].prescaler;

                #ifdef CCP_SEND_SINGLE

                    /* Just mark DAQ for transmission */
                    ccp.DaqList[q].flags |= DAQ_FLAG_SEND;

                #else

                    /* Check that the current queue space fits a complete cycle */
                    #if defined(CCP_SEND_QUEUE) && defined(CCP_SEND_QUEUE_OVERRUN_INDICATION)
                        if ((CCP_SEND_QUEUE_SIZE-ccp.Queue.len)<= (ccp.DaqList[q].last))
                        {
                            ccp.DaqList[q].flags |= (CCP_BYTE)DAQ_FLAG_OVERRUN;
                            continue; /* Skip this DAQ list on overrun */
                        }
                    #endif

                    /* Use BIT7 of PID to indicate overruns (CANape special feature) */
                    #ifdef CCP_SEND_QUEUE_OVERRUN_INDICATION

                        for (j=0;j<=ccp.DaqList[q].last;j++)
                        {
                            if (ccpSampleAndTransmitDtm((CCP_BYTE)((o+j)|(ccp.DaqList[q].flags&DAQ_FLAG_OVERRUN)),q,j) == 0)
                            {
                                ccp.DaqList[q].flags |= (CCP_BYTE)DAQ_FLAG_OVERRUN;
                            }
                            else
                            {
                                ccp.DaqList[q].flags &= INVERT_BITS_IN_BYTE(DAQ_FLAG_OVERRUN);
                            }
                        } /* j */
                    #else

                        for (j=0;j<=ccp.DaqList[q].last;j++)
                        {
                            (void)ccpSampleAndTransmitDtm(o+j,q,j);
                        } /* j */

                    #endif

                #endif

            } /* q */

            /* Check for the next ODT to send */
            #ifdef CCP_SEND_SINGLE
                ccpSampleAndSendNextDtm();
            #endif

            /*  DEVIATION:     3138
                DESCRIPTION:   Null statement is located close to other code or comments.
                JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                the moment but could be populated in the future.*/
            /* PRQA S 3138 01*/
            RST_PORT_BIT(4); /* Timingtest */

        }

    #endif /* CCP_DAQ */


    /*--------------------------------------------------------------------------*/
    /* Background Processing */
    /* Used for Checksum Calculation */
    /*--------------------------------------------------------------------------*/

    /* Table for CCITT checksum calculation */
    #ifdef CCP_CHECKSUM_CCITT
        CCP_MEMROM0 CCP_ROM CCP_WORD CRC16CCITTtab[256] = {

            0x0000,0x1189,0x2312,0x329B,0x4624,0x57AD,0x6536,0x74BF,
            0x8C48,0x9DC1,0xAF5A,0xBED3,0xCA6C,0xDBE5,0xE97E,0xF8F7,
            0x1081,0x0108,0x3393,0x221A,0x56A5,0x472C,0x75B7,0x643E,
            0x9CC9,0x8D40,0xBFDB,0xAE52,0xDAED,0xCB64,0xF9FF,0xE876,
            0x2102,0x308B,0x0210,0x1399,0x6726,0x76AF,0x4434,0x55BD,
            0xAD4A,0xBCC3,0x8E58,0x9FD1,0xEB6E,0xFAE7,0xC87C,0xD9F5,
            0x3183,0x200A,0x1291,0x0318,0x77A7,0x662E,0x54B5,0x453C,
            0xBDCB,0xAC42,0x9ED9,0x8F50,0xFBEF,0xEA66,0xD8FD,0xC974,
            0x4204,0x538D,0x6116,0x709F,0x0420,0x15A9,0x2732,0x36BB,
            0xCE4C,0xDFC5,0xED5E,0xFCD7,0x8868,0x99E1,0xAB7A,0xBAF3,
            0x5285,0x430C,0x7197,0x601E,0x14A1,0x0528,0x37B3,0x263A,
            0xDECD,0xCF44,0xFDDF,0xEC56,0x98E9,0x8960,0xBBFB,0xAA72,
            0x6306,0x728F,0x4014,0x519D,0x2522,0x34AB,0x0630,0x17B9,
            0xEF4E,0xFEC7,0xCC5C,0xDDD5,0xA96A,0xB8E3,0x8A78,0x9BF1,
            0x7387,0x620E,0x5095,0x411C,0x35A3,0x242A,0x16B1,0x0738,
            0xFFCF,0xEE46,0xDCDD,0xCD54,0xB9EB,0xA862,0x9AF9,0x8B70,
            0x8408,0x9581,0xA71A,0xB693,0xC22C,0xD3A5,0xE13E,0xF0B7,
            0x0840,0x19C9,0x2B52,0x3ADB,0x4E64,0x5FED,0x6D76,0x7CFF,
            0x9489,0x8500,0xB79B,0xA612,0xD2AD,0xC324,0xF1BF,0xE036,
            0x18C1,0x0948,0x3BD3,0x2A5A,0x5EE5,0x4F6C,0x7DF7,0x6C7E,
            0xA50A,0xB483,0x8618,0x9791,0xE32E,0xF2A7,0xC03C,0xD1B5,
            0x2942,0x38CB,0x0A50,0x1BD9,0x6F66,0x7EEF,0x4C74,0x5DFD,
            0xB58B,0xA402,0x9699,0x8710,0xF3AF,0xE226,0xD0BD,0xC134,
            0x39C3,0x284A,0x1AD1,0x0B58,0x7FE7,0x6E6E,0x5CF5,0x4D7C,
            0xC60C,0xD785,0xE51E,0xF497,0x8028,0x91A1,0xA33A,0xB2B3,
            0x4A44,0x5BCD,0x6956,0x78DF,0x0C60,0x1DE9,0x2F72,0x3EFB,
            0xD68D,0xC704,0xF59F,0xE416,0x90A9,0x8120,0xB3BB,0xA232,
            0x5AC5,0x4B4C,0x79D7,0x685E,0x1CE1,0x0D68,0x3FF3,0x2E7A,
            0xE70E,0xF687,0xC41C,0xD595,0xA12A,0xB0A3,0x8238,0x93B1,
            0x6B46,0x7ACF,0x4854,0x59DD,0x2D62,0x3CEB,0x0E70,0x1FF9,
            0xF78F,0xE606,0xD49D,0xC514,0xB1AB,0xA022,0x92B9,0x8330,
            0x7BC7,0x6A4E,0x58D5,0x495C,0x3DE3,0x2C6A,0x1EF1,0x0F78
        };
    #endif

    #ifndef CCP_CHECKSUM_BLOCKSIZE
        #define CCP_CHECKSUM_BLOCKSIZE 256
    #endif


/*--------------------------------------------------------------------------*/
/* Command Processor */
/*--------------------------------------------------------------------------*/

/*  DEVIATION:     3673
    DESCRIPTION:   The object addressed by the pointer parameter 'com' is not modified and so the pointer could be of type 'pointer to const'.
    JUSTIFICATION: Making this argument a const caused further instances of warning 0311 "Dangerous pointer cast results in loss of const qualification."
                   Since this is legacy code we have decided to suppress this warning.*/
/* PRQA S 3673 01*/
void ccpCommand(CCP_BYTEPTR com)
{
    CCP_WORD stationAddr;
    BOOLEAN validStartAddr_bo;
    BOOLEAN validEndAddr_bo;

    /*  DEVIATION:     3138
        DESCRIPTION:   Null statement is located close to other code or comments.
        JUSTIFICATION: This warning can be ignored as the macro SET_PORT_BIT is empty at
                       the moment but could be populated in the future.*/
    /* PRQA S 3138 01 */
    SET_PORT_BIT(1); /* Timingtest */

#define cmd com[0]
#define ctr com[1]

    /* Handle CONNECT or TEST command */
    if ((cmd == CC_CONNECT) || (cmd == CC_TEST))
    {
        /* Station Address is always Intel Format (Little Endian) in the received
         * message, regardless of target architecture
         */
        stationAddr = ((CCP_WORD)com[3] << 8) + (CCP_WORD)com[2];

#ifdef CCP_TESTMODE
        if (gDebugLevel) CCPPRINT("\n%u: %s addr=%u\n",ctr,cmd==CC_CONNECT?"CONNECT":"TEST",stationAddr);
#endif

        /* This station */
        if ((stationAddr == CCP_STATION_ADDR) || (stationAddr == CCP_BROADCAST_STATION_ADDR))
        {
            if (cmd == CC_CONNECT)
            {
#ifdef CCP_DAQ
                if ((ccp.SessionStatus & SS_TMP_DISCONNECTED) == 0x00U)
                {
                    ccpStopAllDaq();
                    /* Clear all transmission flags */
                    ccp.SendStatus = 0;
                }
#endif
                ccp.SessionStatus |= SS_CONNECTED;
                ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_TMP_DISCONNECTED);

#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("*** connected ***\n");
#endif
            }

            /* Response */
            /* Station addresses in Intel Format */
            ccp.Crm[0] = 0xFF;
            ccp.Crm[1] = CRC_OK;
            ccp.Crm[2] = ctr;
            ccp.Crm[3] = 0xFE;
            ccp.Crm[4] = (CCP_STATION_ADDR & 0xFF);
            ccp.Crm[5] = ((CCP_STATION_ADDR >> 8) & 0xFF);
            ccp.Crm[6] = (CCP_BROADCAST_STATION_ADDR & 0xFF);
            ccp.Crm[7] = ((CCP_BROADCAST_STATION_ADDR >> 8) & 0xFF);

            /* response */
            /* |||| */
        }

        /* Another station */
        else
        {
            /* If connected, temporary disconnect */
            if ((ccp.SessionStatus&SS_CONNECTED) != 0U)
            {
                ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_CONNECTED);
                ccp.SessionStatus |= SS_TMP_DISCONNECTED;

#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("*** temporary disconnect ***\n");
#endif
            }

            /*  DEVIATION:     3138
                DESCRIPTION:   Null statement is located close to other code or comments.
                JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                               the moment but could be populated in the future. */
            /* PRQA S 3138 01*/
            RST_PORT_BIT(1); /* Timingtest */

            /* no response */
            return;
        }
    }
    /* Handle other commands only if connected */
    else if ((ccp.SessionStatus & SS_CONNECTED) != 0x00U)
    {
        /* prepare the response */
        ccp.Crm[0] = 0xFF;
        ccp.Crm[1] = CRC_OK;
        ccp.Crm[2] = ctr;

        switch (cmd)
        {
            case CC_DISCONNECT:
                {
                    #define disconnectCmd com[2]

                    ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_CONNECTED);
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel) CCPPRINT("%u: DISCONNECT cmd=%u\n",ctr,disconnectCmd);
                    #endif

                    if (disconnectCmd==0x00)
                    { /* Temporary */
                        ccp.SessionStatus |= SS_TMP_DISCONNECTED;
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("*** temporary disconnect ***\n");
                        #endif
                    }
                    else
                    {           /* End of session */
                        #ifdef CCP_DAQ
                            ccpStopAllDaq();
                        #endif
                        #ifdef CCP_SEED_KEY
                            ccp.ProtectionStatus = 0; /* Clear Protection Status */
                        #endif
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("*** end of session ***\n");
                        #endif
                    }
                }
                break;

            /* Exchange Station Identifications */
            case CC_EXCHANGE_ID:
            {
                CCP_BYTE i;
#define masterId com[2]
                for (i = 0; ccpStationId[i] != 0; i++)
                {
                    ;
                }
                /* Length of slave device identifier */
                ccp.Crm[3] = i;
                ccp.Crm[4] = 0;
                /* Build the Resource Availability and Protection Mask */
                /* Default: Calibration available */
                ccp.Crm[5] = PL_CAL;
                /* Default: No Protection */
                ccp.Crm[6] = 0;
#ifdef CCP_SEED_KEY
                /* Protected Calibration */
                ccp.Crm[6] |= PL_CAL;
#endif
#ifdef CCP_DAQ
                /* Data Acquisition */
                ccp.Crm[5] |= PL_DAQ;
#ifdef CCP_SEED_KEY
                /* Protected Data Acquisition */
                ccp.Crm[6] |= PL_DAQ;
#endif
#endif
#if defined(CCP_PROGRAM) || defined(CCP_BOOTLOADER_DOWNLOAD)
                /* Flash Programming */
                ccp.Crm[5] |= PL_PGM;
#ifdef CCP_SEED_KEY
                /* Protected Flash Programming */
                ccp.Crm[6] |= PL_PGM;
#endif
#endif
                /* Driver version number */
                ccp.Crm[7] = CCP_DRIVER_VERSION;
                /* DEVIATION:     850
                   DESCRIPTION:   Macro argument is empty
                   JUSTIFICATION: Deviation due to the use of legacy code.
                 */
                /* PRQA S 0850 7 */
                /* DEVIATION:     311
                   DESCRIPTION:   Dangerous pointer cast results in loss of const qualification.
                   JUSTIFICATION: ccpStationId is a const value and it being passed to a macro
                                  which does not receive it as a const. But the value is not being modified in
                                  the macro and is used as read only. Hence this warning can be ignored. */
                /* PRQA S 0311 1 */
                ccpSetMTA(0, (CCP_MTABYTEPTR)ccpStationId);
#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("%u: EXCANGE_ID master_id=%u\n",ctr,masterId);
#endif
                break;
            }

                #ifdef CCP_SEED_KEY

                    case CC_GET_SEED: /* Get Seed for Key */
                    {
                        #define privilegeLevel com[2]
                        ccp.Crm[3] = 0; /* Protection Status: No key required */
                        *(CCP_DWORD*)&ccp.Crm[4] = 0;
                        #ifdef CCP_SEED_KEY
                            /* Keys required for CAL or PGM */
                            switch (privilegeLevel)
                            {
                                case PL_CAL:
                                    ccp.Crm[3] = (0==(ccp.ProtectionStatus&PL_CAL)); /* Protection Status */
                                    *(CCP_DWORD*)&ccp.Crm[4] = ccpGetSeed(PL_CAL);
                                break;
                                case PL_PGM:
                                    ccp.Crm[3] = (0==(ccp.ProtectionStatus&PL_PGM)); /* Protection Status */
                                    *(CCP_DWORD*)&ccp.Crm[4] = ccpGetSeed(PL_PGM);
                                break;
                                case PL_DAQ:
                                    ccp.Crm[3] = (0==(ccp.ProtectionStatus&PL_DAQ)); /* Protection Status */
                                    *(CCP_DWORD*)&ccp.Crm[4] = ccpGetSeed(PL_DAQ);
                                break;
                                default:
                                    ccp.Crm[1] = CRC_CMD_SYNTAX;
                                /* Error */
                            }
                        #endif
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: GET_SEED resource=%02X, protection_status=%u\n",ctr,privilegeLevel,ccp.Crm[3]);
                        #endif
                    }
                    break;

                    case CC_UNLOCK: /* Unlock Protection */
                    {
                        #define key com[2] /* Key may be up to 6 Bytes */
                        /* Check key */
                        ccp.ProtectionStatus |= ccpUnlock(&com[2]); /* Reset the appropriate resource protection mask bit */
                        ccp.Crm[3] = ccp.ProtectionStatus; /* Current Protection Status */
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: UNLOCK protection_status=%02X\n",ctr,ccp.ProtectionStatus);
                        #endif
                    }
                    break;

                #endif /* CCP_SEED_KEY */

            /* Set transfer address */
            case CC_SET_MTA:
            {
#define mta     com[2]
#define addrExt com[3]
                /* DEVIATION:     0310
                   DESCRIPTION:   Casting to different object pointer type.
                   JUSTIFICATION: This is done to copy all the 4 address bytes at once.
                                  Casting is done for efficient coding. The code has been tested. */
                /* PRQA S 0310 04 */
#define addr    (*(CCP_DWORD*)&com[4])
                if (mta < (CCP_MAX_MTA - 1))
                {
                    ccpSetMTA(mta, ccpGetPointer(addrExt, addr));
                }
                else
                {
                    ccp.Crm[1] = CRC_OUT_OF_RANGE;
                }
#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("%u: SET_MTA %u to %08lX,%u\n",ctr,mta,addr,addrExt);
#endif

#undef mta
#undef addrExt
#undef addr
                break;
            }

                case CC_DNLOAD: /* Download */
                {
                    CCP_BYTE r;
                    #define size com[2]
                    #ifdef CCP_SEED_KEY
                        if (!(ccp.ProtectionStatus&PL_CAL))
                        {
                            ccp.Crm[1] = CRC_ACCESS_DENIED;
                            r = 0;
                        }
                        else
                    #endif
                    r = ccpWriteMTA(0,size,&com[3]);
                    #ifdef CCP_STANDARD
                        ccpGetMTA0((CCP_BYTE*)&ccp.Crm[3],(CCP_DWORD*)&ccp.Crm[4]);
                    #endif
                    if (r==CCP_WRITE_PENDING)
                    {
                        return; /* EEPROM write pending */
                    }
                    if ((r==CCP_WRITE_DENIED) || (r==CCP_WRITE_ERROR))
                    {
                        ccp.Crm[1] = CRC_ACCESS_DENIED; /* No write access */
                    }
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel)
                        {
                            int i;
                            CCPPRINT("%u: DNLOAD n=%u, ",ctr,size);
                            for (i=3;i<3+size&&i<8;i++) CCPPRINT("%02X ",com[i]);
                            CCPPRINT("\n");
                        }
                    #endif

                    #undef size      /* avoid compiler re-definition warning */
                }
                break;

                case CC_DNLOAD6: /* Download */
                {
                    CCP_BYTE r;
                    #ifdef CCP_SEED_KEY
                        if (!(ccp.ProtectionStatus&PL_CAL))
                        {
                            ccp.Crm[1] = CRC_ACCESS_DENIED;
                            r = 0;
                        }
                        else
                    #endif
                    r = ccpWriteMTA(0,6,&com[2]);
                    #ifdef CCP_STANDARD
                        ccpGetMTA0((CCP_BYTE*)&ccp.Crm[3],(CCP_DWORD*)&ccp.Crm[4]);
                    #endif
                    if (r==CCP_WRITE_PENDING)
                    {
                        return; /* EEPROM write pending */
                    }
                    if ((r==CCP_WRITE_DENIED)||(r==CCP_WRITE_ERROR))
                    {
                        ccp.Crm[1] = CRC_ACCESS_DENIED; /* No write access */
                    }
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel)
                        {
                            int i;
                            CCPPRINT("%u: DNLOAD6 ",ctr);
                            for (i=2;i<8;i++) CCPPRINT("%02X ",com[i]);
                            CCPPRINT("\n");
                        }
                    #endif
                }
                break;

                case CC_UPLOAD: /* Upload */
                {
                    CCP_BYTE r;
                    #define size com[2]
                    r = ccpReadMTA(0,size,&ccp.Crm[3]);
                    if (r==CCP_READ_DENIED)
                    {
                        ccp.Crm[1] = CRC_ACCESS_DENIED; /* No read access */
                    }
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel)
                        {
                            int i;
                            CCPPRINT("%u: UPLOAD n=%u, ",ctr,size);
                            for (i=3;i<3+size;i++) CCPPRINT("%02X ",ccp.Crm[i]);
                            CCPPRINT("\n");
                        }
                    #endif

                    #undef size      /* avoid compiler re-definition warning */
                }
                break;

                case CC_SHORT_UPLOAD: /* Upload with Address */
                {
                    CCP_BYTE r;
                    #define size    com[2]
                    #define addrExt com[3]
                    /*  DEVIATION:     0310
                        DESCRIPTION:   Casting to different object pointer type.
                        JUSTIFICATION: This is done to copy all the 4 address bytes at once.
                        Casting is done for efficient coding. The code has been tested .*/
                    /* PRQA S 0310 03*/
                    #define addr    (*(CCP_DWORD*)&com[4])
                    ccpSetMTA(CCP_INTERNAL_MTA,ccpGetPointer(addrExt,addr));
                    r = ccpReadMTA(CCP_INTERNAL_MTA,size,&ccp.Crm[3]);
                    if (r==CCP_READ_DENIED)
                    {
                        ccp.Crm[1] = CRC_ACCESS_DENIED; /* No read access */
                    }
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel) {
                            int i;
                            CCPPRINT("%u: SHORT_UPLOAD p=%08lX,%u,n=%u, ",ctr,addr,addrExt,size);
                            for (i=3;i<3+size&&i<8;i++) CCPPRINT("%02X ",ccp.Crm[i]);
                            CCPPRINT("\n");
                        }
                    #endif

                    #undef size
                    #undef addrExt
                    #undef addr
                }
                break;

                case CC_GET_DAQ_SIZE: /* Return the size of a DAQ list and clear */
                {
                    #define daqList com[2]
                    #define daqId   (*(CCP_DWORD*)&com[4])
                    #ifdef CCP_DAQ
                        ccpStopDaq(daqList); /* Stop this daq list */

                        ccp.Crm[3] = ccpClearDaqList(daqList); /* Number of  ODTs */
                        ccp.Crm[4] = daqList*CCP_MAX_ODT; /* PID of the first ODT */
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: GET_DAQ_SIZE daq=%u,id=%lu,size=%u,pid=%u\n",ctr,daqList,daqId,ccp.Crm[3],daqList*CCP_MAX_ODT);
                        #endif
                    #else
                        ccp.Crm[3] = 0;
                        ccp.Crm[4] = 0;
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: GET_DAQ_SIZE daq=%u,size=0\n",ctr,daqList,daqId);
                        #endif
                    #endif
                    #undef daqList
                    #undef daqId
                }
                break;

                #ifdef CCP_DAQ

                    case CC_SET_DAQ_PTR: /* Set DAQ pointer */
                    {
                        #define comDaq  com[2]
                        #define comOdt  com[3]
                        #define comIdx  com[4]
                        if ((comDaq>=CCP_MAX_DAQ)||(comOdt>=CCP_MAX_ODT)||(comIdx>7))
                        {
                            ccp.Crm[1] = CRC_CMD_SYNTAX;
                            ccp.DaqListPtr = 0;
                        }
                        else
                        {
                            ccp.DaqListPtr = &ccp.DaqList[comDaq].odt[comOdt][comIdx];
                        }
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: SET_DAQ_PTR daq=%u,odt=%u,idx=%u\n",ctr,comDaq,comOdt,comIdx);
                        #endif

                        #undef comDaq
                        #undef comOdt
                        #undef comIdx
                    }
                    break;

                    case CC_WRITE_DAQ: /* Write DAQ entry */
                    {
                        #define writeDaqSize    com[2]
                        #define writeDaqAddrExt com[3]
                        /*  DEVIATION:     0310
                            DESCRIPTION:   Casting to different object pointer type.
                            JUSTIFICATION: This is done to copy all the 4 address bytes at once.
                            Casting is done for efficient coding. The code has been tested.*/
                        /* PRQA S 0310 45*/
                        #define writeDaqAddr    (*(CCP_DWORD*)&com[4])

                        /* Check memory access valid before proceding */
                        /*  DEVIATION:     0306
                              DESCRIPTION:   Cast between a pointer to object and an integral type
                              JUSTIFICATION: Deviation due to the use of legacy code.
                        */
                        /* PRQA S 0306 2 */
                        validStartAddr_bo = FOUNDATION_Memory_Access_Valid(writeDaqAddr, READ_ACCESS);
                        validEndAddr_bo = FOUNDATION_Memory_Access_Valid(((writeDaqAddr + writeDaqSize) - 1U), READ_ACCESS);
                        if ((validStartAddr_bo == FALSE) ||    /* Start address */
                            (validEndAddr_bo == FALSE))        /* End   address */
                        {
                            ccp.Crm[1] = CRC_ACCESS_DENIED; /* No read access */
                        }
                        else
                        {
                            if (
                                #ifdef CCP_ODT_ENTRY_SIZE
                                    #ifdef CCP_DOUBLE_FLOAT
                                    (writeDaqSize!=8) &&
                                    #endif
                                    ((writeDaqSize!=1)&&(writeDaqSize!=2)&&(writeDaqSize!=4))
                                #else
                                    (writeDaqSize!=1)
                                #endif
                                || (ccp.DaqListPtr==0))
                            {
                                ccp.Crm[1] = CRC_CMD_SYNTAX;
                            }
                            else
                            {
                                #ifdef CCP_DAQ_BASE_ADDR
                                    ccp.DaqListPtr->ptr = ccpGetDaqPointer(writeDaqAddrExt,writeDaqAddr);
                                #else
                                    ccp.DaqListPtr->ptr = (CCP_DAQBYTEPTR)ccpGetPointer(writeDaqAddrExt,writeDaqAddr);
                                #endif
                                #ifdef CCP_ODT_ENTRY_SIZE
                                    ccp.DaqListPtr->siz = writeDaqSize;
                                #endif
                            }
                            #ifdef CCP_TESTMODE
                                if (gDebugLevel) CCPPRINT("%u: WRITE_DAQ size=%u,ext=%u,addr=%lu\n",ctr,writeDaqSize,writeDaqAddrExt,writeDaqAddr);
                            #endif
                        }

                        #undef writeDaqSize
                        #undef writeDaqAddrExt
                        #undef writeDaqAddr
                    }
                    break;

                    case CC_START_STOP: /* Cyclic aquisition start/stop */
                    {
                        #define ssCmd                 com[2]  /* Start or Stop */
                        #define ssDaq                 com[3]  /* DAQ list */
                        #define ssLast                com[4]  /* Last ODT to send */
                        #define ssEventChannel        com[5]  /* Event Channel Number */
                        /*  DEVIATION:     0310
                            DESCRIPTION:   Casting to different object pointer type.
                            JUSTIFICATION: This is done to copy all the 2  bytes at once.
                            Casting is done for efficient coding. The code has been tested .*/
                        /* PRQA S 0310 45*/
                        #define ssPrescaler (*(CCP_WORD*)&com[6]) /* Prescaler */

                        #ifdef CCP_SEED_KEY
                        if ((ccp.ProtectionStatus&PL_DAQ) == 0x00)
                            ccp.Crm[1] = CRC_ACCESS_DENIED;
                        else
                        #endif
                        if ((ccp.SessionStatus&SS_DAQ) == 0x00)
                        { /* Not initialized */
                            ccp.Crm[1] = CRC_DAQ_INIT_REQUEST;
                        }
                        else
                        {
                            switch (ssCmd)
                            {
                                case 0: /* stop */
                                {
                                    ccpStopDaq(ssDaq);
                                }
                                break;
                                case 1: /* start */
                                {
                                    (void)ccpPrepareDaq(ssDaq,ssLast,ssEventChannel,(CCP_WORD)ssPrescaler);
                                    (void)ccpStartDaq(ssDaq);
                                    #ifdef CCP_TESTMODE
                                        if (gDebugLevel) ccpPrintDaqList(ssDaq);
                                    #endif
                                }
                                break;
                                case 2: /* prepare */
                                {
                                    (void)ccpPrepareDaq(ssDaq,ssLast,ssEventChannel,(CCP_WORD)ssPrescaler);
                                    #ifdef CCP_TESTMODE
                                        if (gDebugLevel) ccpPrintDaqList(ssDaq);
                                    #endif
                                }
                                break;
                                default:
                                {
                                    ccp.Crm[1] = CRC_CMD_SYNTAX;
                                }
                                break;
                            }
                        }

                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: START_STOP cmd=%u,daq=%u,last=%u,eventChannel=%u,prescaler=%u\n",ctr,ssCmd,ssDaq,ssLast,ssEventChannel,ssPrescaler);
                        #endif

                        #undef ssCmd
                        #undef ssDaq
                        #undef ssLast
                        #undef ssEventChannel
                        #undef ssPrescaler
                    }
                    break;

                    case CC_START_STOP_ALL: /* Cyclic aquisition start/stop */
                    {
                        #define ssCmd                 com[2]  /* Start or Stop */

                        #ifdef CCP_SEED_KEY
                            if ((ccp.ProtectionStatus&PL_DAQ) == 0x00)
                              ccp.Crm[1] = CRC_ACCESS_DENIED;
                            else
                        #endif
                        if ((ccp.SessionStatus&SS_DAQ)== 0x00)
                        { /* Not initialized */
                            ccp.Crm[1] = CRC_DAQ_INIT_REQUEST;
                        }
                        else
                        {
                            switch (ssCmd)
                            {
                                case 0: /* Stop */
                                {
                                    ccpStopAllDaq();
                                }
                                break;
                                case 1: /* Start */
                                {
                                    ccpStartAllPreparedDaq();
                                }
                                break;
                                default:
                                {
                                    ccp.Crm[1] = CRC_CMD_SYNTAX;
                                }
                                break;
                            }
                        }
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: START_STOP_ALL cmd=%u\n",ctr,ssCmd);
                        #endif

                        #undef ssCmd
                    }
                    break;

                #endif /* CCP_DAQ */

                #ifdef CCP_CHECKSUM

                case CC_BUILD_CHKSUM: /* Build Checksum */
                {
                    CCP_DWORD s;

                    /* Initialize Response */
                    ccp.Crm[3] = sizeof(CCP_CHECKSUM_TYPE); /* Checksum Size */
                    /*  DEVIATION:     0310
                        DESCRIPTION:   Casting to different object pointer type.
                        JUSTIFICATION: This is done to set 4 buffer bytes at once.
                        Casting is done for efficient coding. The code has been tested .*/
                    /* PRQA S 0310 04*/
                    #ifdef CCP_CHECKSUM_CCITT               /* Checksum */
                        *(CCP_DWORD*)&ccp.Crm[4] = 0xFFFFFFFF;
                    #else
                        *(CCP_DWORD*)&ccp.Crm[4] = 0;
                    #endif
                    ccp.MTA[CCP_INTERNAL_MTA] = ccp.MTA[0];        /* MTA[0] is not affected */
                    /*  DEVIATION:     0310
                        DESCRIPTION:   Casting to different object pointer type.
                        JUSTIFICATION: Casting is done to access more than one byte of the buffer
                        at a time as per the design logic. This code has been tested.*/
                    /* PRQA S 0310 04*/
                    #ifdef CCP_MOTOROLA
                        s = (*(CCP_WORD*)&com[4]) | (((CCP_DWORD)(*(CCP_WORD*)&com[2]))<<16);
                    #else
                        s = (*(CCP_WORD*)&com[2]) | (((CCP_DWORD)(*(CCP_WORD*)&com[4]))<<16);
                    #endif
                    #ifdef CCP_TESTMODE
                        if (gDebugLevel) CCPPRINT("%u: BUILD_CHKSUM size=%u\n",ctr,s);
                    #endif
                    #ifndef CCP_CPUTYPE_32BIT
                        if ((s&0xffff0000U) != 0U)
                        {
                            ccp.Crm[1] = CRC_OUT_OF_RANGE; /* Range, max. 64K-1 on <32Bit CPUs */
                        }
                        ccp.CheckSumSize = (CCP_WORD)s;
                    #else
                        ccp.CheckSumSize = s;
                    #endif
                    if (ccp.Crm[1]==0)
                    {
                        /*  DEVIATION:     3138
                            DESCRIPTION:   Null statement is located close to other code or comments.
                            JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                            the moment but could be populated in the future.*/
                        /* PRQA S 3138 01*/
                        RST_PORT_BIT(1); /* Timingtest */
                        return; /* Checksum calculation will be performed by ccpBackground() */
                    }

                }
                break;

                #endif /* CCP_CHECKSUM */

                /* Flash Programming Kernel Download */
                #ifdef CCP_BOOTLOADER_DOWNLOAD

                    case CC_PROGRAM_PREPARE: /* Prepare flash kernel download */
                    {
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: PROGRAM_PREPARE\n",ctr);
                        #endif
                        if (!ccpDisableNormalOperation(ccp.MTA[0],*(CCP_WORD*)&com[2])) {
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        }
                    }
                    break;

                    case CC_PROGRAM_START:   /* Start flash kernel */
                    {
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: PROGRAM_START\n",ctr);
                        #endif
                        #ifdef CCP_SEED_KEY
                            if (!(ccp.ProtectionStatus&PL_PGM))
                                ccp.Crm[1] = CRC_ACCESS_DENIED;
                            else
                        #endif
                            ((ccpBootLoader_t)ccp.MTA[0])(&ccp,com);
                    }
                    break;

                #endif /* CCP_BOOTLOADER_DOWNLOAD */

            /* Clear Memory */
            case CC_CLEAR_MEMORY:
            {
                CCP_DWORD s;
#ifdef CCP_PROGRAM
                CCP_BYTE r;
#endif

#ifdef CCP_SEED_KEY
                if (!(ccp.ProtectionStatus&PL_PGM))
                    ccp.Crm[1] = CRC_ACCESS_DENIED;
                else
#endif

#ifdef CCP_BOOTLOADER
                /* Transfer control to the CCP bootloader */
                /* Never returns */
                ccpBootLoaderStartup(&ccp,com);
#else
                /* Clear flash sector */
                /* DEVIATION:     0310
                   DESCRIPTION:   Casting to different object pointer type.
                   JUSTIFICATION: Casting is done to access more than one byte of the buffer
                                  at a time as per the design logic. This code has been tested.*/
                /* PRQA S 0310 04*/
#ifdef CCP_MOTOROLA
                s = (*(CCP_WORD*)&com[4]) | (((CCP_DWORD)(*(CCP_WORD*)&com[2])) << 16);
#else
                s = (*(CCP_WORD*)&com[2]) | (((CCP_DWORD)(*(CCP_WORD*)&com[4])) << 16);
#endif
#ifdef CCP_PROGRAM
                /* DEVIATION:     0306
                   DESCRIPTION:   Cast between a pointer to object and an integral type
                   JUSTIFICATION: Deviation due to the use of legacy code.
                 */
                /* PRQA S 0306 1 */
                r = FlsEraseFlash((CCP_DWORD)ccp.MTA[0], s);
                switch (r)
                {
                    case FLS_OK:
                        ccp.Crm[1] = CRC_OK;
                        break;
                    case FLS_INVALID:
                        ccp.Crm[1] = CRC_OUT_OF_RANGE;
                        break;
                    case FLS_FAIL:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                    /* added here to avoid QAC warning. There is no special handling for the default switch condition so we've repeated the previous case */
                    default:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                }
#else
                /* PPC application to handle a re-programming attempt */
                /* DEVIATION:     0306
                   DESCRIPTION:   Cast between a pointer to object and an integral type
                   JUSTIFICATION: Deviation due to the use of legacy code.
                 */
                /* PRQA S 0306 1 */
                ccpHandleReprogRequest((CCP_DWORD)ccp.MTA[0],s,ctr);
#endif
#endif

#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("%u: CLEAR_MEMORY size=%u\n",ctr,s);
#endif
                break;
            }

#ifdef CCP_PROGRAM
            /* Flash Programming */
#ifndef CCP_BOOTLOADER
            /* Program */
            case CC_PROGRAM:
            {
                CCP_BYTE r;
#define size com[2]
#ifdef CCP_SEED_KEY
                if (!(ccp.ProtectionStatus & PL_PGM))
                {
                    r = FLSH_FAIL;
                }
                else
#endif
                r = FlsProgramFlash(&com[3], ccp.MTA[0], size);
                /* DEVIATION:     0488
                   DESCRIPTION:   Performing pointer arithmetic.
                   JUSTIFICATION: Pointer arithmetic used for efficient coding and this code has been tested. */
                /* PRQA S 0488 01*/
                ccp.MTA[0] += size;

                switch (r)
                {
                    case FLS_OK:
                        /* DEVIATION:     0306
                           DESCRIPTION:   Cast between a pointer to object and an integral type
                           JUSTIFICATION: Deviation due to the use of legacy code.
                         */
                        /* PRQA S 0306 5 */
                        ccp.Crm[1] = CRC_OK;
                        ccp.Crm[4] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 24);
                        ccp.Crm[5] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 16);
                        ccp.Crm[6] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 8);
                        ccp.Crm[7] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0]);
                        break;
                    case FLS_INVALID:
                        ccp.Crm[1] = CRC_OUT_OF_RANGE;
                        break;
                    case FLS_FAIL:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                    /* added here to avoid QAC warning. There is no special
                     * handling for the default switch condition so we've
                     * repeated the previous case
                     */
                    default:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                }

#ifdef CCP_TESTMODE
                if (gDebugLevel)
                {
                    CCPPRINT("%u: PROGRAM ",ctr);
                    if (size == 0)
                    {
                        CCPPRINT("EOS\n");
                    }
                    else
                    {
                        int i;
                        for (i=0;i<size;i++) CCPPRINT("%02X ",com[3+i]);
                        CCPPRINT("\n");
                    }
                }
#endif

#undef size
                break;
            }

            /* Program */
            case CC_PROGRAM6:
            {
                CCP_BYTE r;
#ifdef CCP_SEED_KEY
                if (!(ccp.ProtectionStatus & PL_PGM))
                {
                    ccp.Crm[1] = CRC_ACCESS_DENIED;
                    r = 0;
                }
                else
#endif
                r = FlsProgramFlash(&com[2], ccp.MTA[0], 6);
                /* DEVIATION:     0488
                   DESCRIPTION:   Performing pointer arithmetic.
                   JUSTIFICATION: Pointer arithmetic used for efficient coding and this code has been tested. */
                /* PRQA S 0488 01 */
                ccp.MTA[0] += 6;

                switch (r)
                {
                    case FLS_OK:
                        /* DEVIATION:     0306
                           DESCRIPTION:   Cast between a pointer to object and an integral type
                           JUSTIFICATION: Deviation due to the use of legacy code.
                         */
                        /* PRQA S 0306 5 */
                        ccp.Crm[1] = CRC_OK;
                        ccp.Crm[4] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 24);
                        ccp.Crm[5] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 16);
                        ccp.Crm[6] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0] >> 8);
                        ccp.Crm[7] = (CCP_BYTE)((CCP_DWORD)ccp.MTA[0]);
                        break;
                    case FLS_INVALID:
                        ccp.Crm[1] = CRC_OUT_OF_RANGE;
                        break;
                    case FLS_FAIL:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                    /* added here to avoid QAC warning. There is no special handling
                     * the default switch condition so we've repeated the previous
                     * case
                     */
                    default:
                        ccp.Crm[1] = CRC_ACCESS_DENIED;
                        break;
                }

#ifdef CCP_TESTMODE
                if (gDebugLevel)
                {
                    int i;
                    CCPPRINT("%u: PROGRAM6: ",ctr);
                    for (i=0;i<6;i++) CCPPRINT("%02X ",com[2+i]);
                    CCPPRINT("\n");
                }
#endif
                break;
            }
#endif /* !CCP_BOOTLOADER */
#endif /* CCP_PROGRAM */

                #ifdef CCP_CALPAGE

                    case CC_SET_CAL_PAGE: /* Select Calibration Page */
                    {
                        /*  DEVIATION:     0306
                            DESCRIPTION:   Cast between a pointer to object and an integral type
                            JUSTIFICATION: Deviation due to the use of legacy code.
                        */
                        /* PRQA S 0306 1 */
                        ccpSetCalPage((CCP_DWORD)ccp.MTA[0]);
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: SEL_CAL_PAGE id=%08Xh\n",ctr,(CCP_DWORD)ccp.MTA[0]);
                        #endif
                    }
                    break;

                    case CC_GET_CAL_PAGE: /* Get Active Calibration Page */
                    {
                        ccp.Crm[3] = 0; /* Address Extension */
                        /*  DEVIATION:     0310
                            DESCRIPTION:   Casting to different object pointer type.
                            JUSTIFICATION: This is done to set 4 buffer bytes at once.
                            Casting is done for efficient coding. The code has been tested .*/
                        /* PRQA S 0310 01*/
                        *(CCP_DWORD*)&ccp.Crm[4] = ccpGetCalPage(); /* Address */
                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: GET_CAL_PAGE -> id=%08Xh\n",ctr,*(CCP_DWORD*)&ccp.Crm[4]);
                        #endif
                    }
                    break;

                #endif /* CCP_CALPAGE */

                #ifdef CCP_SET_SESSION_STATUS

                    case CC_SET_S_STATUS: /* Set Session Status */
                    {
                        /* Set Resume and Store mode in SessionStatus */
                        ccp.SessionStatus &= ~(SS_STORE|SS_RESUME);
                        ccp.SessionStatus |= (com[2]&(SS_STORE|SS_RESUME));

                        /* Save as UserSessionStatus */
                        ccp.UserSessionStatus = com[2];

                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: SET_S_STATUS status=%02X\n",ctr,ccp.UserSessionStatus);
                        #endif
                    }
                    break;

                    case CC_GET_S_STATUS: /* Get Session Status */
                    {
                        ccp.Crm[3] = ccp.UserSessionStatus;
                        ccp.Crm[4] = 0; /* No additional status */

                        #ifdef CCP_TESTMODE
                            if (gDebugLevel) CCPPRINT("%u: GET_S_STATUS -> status=%02X\n",ctr,ccp.Crm[3]);
                        #endif
                    }
                    break;

                #endif /* CCP_SET_SESSION_STATUS */

            case CC_GET_CCP_VERSION: /* Get Version */
            {
                ccp.Crm[3] = CCP_VERSION_MAJOR;
                ccp.Crm[4] = CCP_VERSION_MINOR;
#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("%u: GET_VERSION -> major=%02X minor=%02X\n",ctr,ccp.Crm[3],ccp.Crm[4]);
#endif
                break;
            }

            default: /* unknown */
            {
                ccp.Crm[1] = CRC_CMD_UNKNOWN;
#ifdef CCP_TESTMODE
                if (gDebugLevel) CCPPRINT("*** UNKNOWN COMMAND ***\n");
#endif
                break;
            }
        } /* switch */
    /* Response */
    /* |||| */
    }
    /* Not connected */
    else
    {
        /* DEVIATION:     3138
           DESCRIPTION:   Null statement is located close to other code or comments.
           JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                          the moment but could be populated in the future. */
        /* PRQA S 3138 01 */
        RST_PORT_BIT(1); /* Timingtest */

        /* No response */
        return;
    }

    ccpSendCrm();

    /* DEVIATION:     3138
       DESCRIPTION:   Null statement is located close to other code or comments.
       JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                      the moment but could be populated in the future. */
    /* PRQA S 3138 01 */
    RST_PORT_BIT(1); /* Timingtest */
}


    /*--------------------------------------------------------------------------*/
    /* Send notification callback */
    /* ccpSend must not fail, when called from this function */
    /*--------------------------------------------------------------------------*/
    CCP_BYTE ccpSendCallBack( void )
    {

        /*  DEVIATION:     3138
            DESCRIPTION:   Null statement is located close to other code or comments.
            JUSTIFICATION: This warning can be ignored as the macro SET_PORT_BIT is empty at
            the moment but could be populated in the future.*/
        /* PRQA S 3138 01*/
        SET_PORT_BIT(2); /* Timingtest */

        /* Clear all pending flags, except for CCP_CMD_PENDING */
        ccp.SendStatus &= INVERT_BITS_IN_BYTE(CCP_SEND_PENDING);

        /* Send a CRM message */
        if ((ccp.SendStatus&CCP_CRM_REQUEST) != 0)
        {
            ccp.SendStatus &= INVERT_BITS_IN_BYTE(CCP_CRM_REQUEST);
            ccpSendCrm();
            /*  DEVIATION:     3138
                DESCRIPTION:   Null statement is located close to other code or comments.
                JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                the moment but could be populated in the future.*/
            /* PRQA S 3138 01*/
            RST_PORT_BIT(2); /* Timingtest */
            return 1;
        }

        /* Send a DAQ message */
        #ifdef CCP_DAQ
            if ((ccp.SessionStatus&SS_RUN) != 0)
            {
                /* Send a  DAQ message (DTM) from the queue */
                #ifdef CCP_SEND_QUEUE

                    /*  DEVIATION:     3138
                        DESCRIPTION:   Null statement is located close to other code or comments.
                        JUSTIFICATION: This warning can be ignored as the macro CCP_DISABLE_INTERRUPT is empty at
                        the moment but could be populated in the future.*/
                    /* PRQA S 3138 01*/
                    CCP_DISABLE_INTERRUPT;
                    if ((ccp.Queue.len) != 0)
                    {
                        ccp.SendStatus |= CCP_DTM_PENDING;
                        /*  DEVIATION:     0310
                            DESCRIPTION:   Casting to different object pointer type.
                            JUSTIFICATION: msg which is a structure that has only on element - a char array is
                            cast as a byte pointer as the function ccpSend() demands it. But functionally it
                            works the same way. This code has been tested , hence this warning can be ignored.*/
                        /* PRQA S 0310 01*/
                        ccpSend((CCP_BYTEPTR)&ccp.Queue.msg[ccp.Queue.rp]);
                        ccp.Queue.rp++;
                        if (ccp.Queue.rp>=CCP_SEND_QUEUE_SIZE)
                        {
                            ccp.Queue.rp = 0;
                        }
                        ccp.Queue.len--;
                        /*  DEVIATION:     3138
                            DESCRIPTION:   Null statement is located close to other code or comments.
                            JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT and
                            RST_PORT_BIT are empty at the moment but could be populated in the future.*/
                        /* PRQA S 3138 02*/
                        CCP_ENABLE_INTERRUPT;
                        RST_PORT_BIT(2); /* Timingtest */
                        return 1;
                    }
                    /*  DEVIATION:     3138
                        DESCRIPTION:   Null statement is located close to other code or comments.
                        JUSTIFICATION: This warning can be ignored as the macro CCP_ENABLE_INTERRUPT is empty at
                        the moment but could be populated in the future.*/
                    /* PRQA S 3138 01*/
                    CCP_ENABLE_INTERRUPT;

                /* Send a pending DAQ message (DTM) */
                #else

                    if ((ccp.SendStatus&CCP_DTM_REQUEST) != 0)
                    {
                        ccp.SendStatus &= INVERT_BITS_IN_BYTE(CCP_DTM_REQUEST);
                        ccpSendDtm();
                        /*  DEVIATION:     3138
                              DESCRIPTION:   Null statement is located close to other code or comments.
                              JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
                              the moment but could be populated in the future.*/
                        /* PRQA S 3138 01*/
                        RST_PORT_BIT(2); /* Timingtest */
                        return 1;
                    }

                #endif
            }
        #endif

        /*  DEVIATION:     3138
            DESCRIPTION:   Null statement is located close to other code or comments.
            JUSTIFICATION: This warning can be ignored as the macro RST_PORT_BIT is empty at
            the moment but could be populated in the future.*/
        /* PRQA S 3138 01*/
        RST_PORT_BIT(2); /* Timingtest */
        return 0;
    }



    void ccpInit( void )
    {
        /* Initialize all CCP variables to zero */
        CCP_BYTEPTR p;
        CCP_BYTEPTR pl;
        /*  DEVIATION:     0310
            DESCRIPTION:   Casting to different object pointer type.
            JUSTIFICATION: This casting is done to initialize all the elements of structure ccp to zero
            byte by byte irrespective of the data type of each element for efficient coding.Hence this
            warning can be ignored.*/
        /* PRQA S 0310 01*/
        p = (CCP_BYTEPTR)&ccp;
        /*  DEVIATION:     0488
            DESCRIPTION:   Performing pointer arithmetic.
            JUSTIFICATION: Pointer arithemetic used to store the end pointer for the pointer operation
            below. Pointers have been used here for efficient coding and this code has been tested.*/
        /* PRQA S 0488 01*/
        pl = p+sizeof(ccp);
        while (p<pl)
        {
            /*  DEVIATION:     0489
                DESCRIPTION:   Increment or decrement operation performed on pointer.
                JUSTIFICATION: Pointer arithemetic is used for efficient coding as large data
                buffers have to be modified in this section of code.*/
            /* PRQA S 0489 01*/
            *p++ = 0;
        }
    }


    /*--------------------------------------------------------------------------*/
    /* Test */
    /* Screen output for test and diagnostics */
    /*--------------------------------------------------------------------------*/

    #ifdef CCP_TESTMODE
        #ifdef CCP_DAQ
            /* Print all DAQ lists to screen */
            static void ccpPrintDaqList( CCP_BYTE daq )
            {

                CCP_BYTE i,j,f;

                if (daq>=CCP_MAX_DAQ) return;
                CCPPRINT("DAQ-List %u:\n",daq);
                CCPPRINT(" event channel=%u,",ccp.DaqList[daq].eventChannel);
                CCPPRINT(" prescaler=%u,",ccp.DaqList[daq].prescaler);
                CCPPRINT(" last=%u,",ccp.DaqList[daq].last);
                CCPPRINT(" flags=%u\n",ccp.DaqList[daq].flags);
                for (j=0;j<CCP_MAX_ODT;j++) {
                    for (i=0,f=1;i<=6;i++) {
                        if (ccp.DaqList[daq].odt[j][i].ptr) {
                            if (f) { CCPPRINT(" PID %u: ",daq*CCP_MAX_ODT+j); f = 0; }
                            #ifdef CCP_ODT_ENTRY_SIZE
                                CCPPRINT("[%p,%u],",ccp.DaqList[daq].odt[j][i].ptr,ccp.DaqList[daq].odt[j][i].siz);
                            #else
                                CCPPRINT("[%p],",ccp.DaqList[daq].odt[j][i].ptr);
                            #endif
                        }
                    }
                    if (!f) CCPPRINT("\n");
                } /* j */
            }
        #endif
    #endif
#endif /* C_DISABLE_CCP */

