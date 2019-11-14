/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: ccppar.h $
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

#ifndef CCPPAR_H
#define CCPPAR_H

/*----------------------------------------------------------------------------*/
/* Processor-specific configuration definitions */
#define V_ENABLE_USE_DUMMY_STATEMENT
#define C_CPUTYPE_32BIT
#define C_CPUTYPE_BIGENDIAN

/*----------------------------------------------------------------------------*/
/* General CCP configuration */
#define V21

#define C_ENABLE_CCP

#define CCP_CAN_CHANNEL     0

#define CCP_ROM             V_MEMROM2

#define CCP_BYTE            unsigned char
#define CCP_WORD            unsigned short
#define CCP_DWORD           unsigned long
#define CCP_BYTEPTR         unsigned char*

#define CCP_DISABLE_INTERRUPT
#define CCP_ENABLE_INTERRUPT

#define CCP_STATION_ID      "ACC"

#define CCP_STATION_ADDR    0x3A   /* Motorola Format(Big Endian)  */

/*----------------------------------------------------------------------------*/
/* CCP buffer mappings */
#define CCP_TX_DATA_PTR     CCP_TxData
#define CCP_RX_DATA_PTR     CCP_RxData

/*----------------------------------------------------------------------------*/
/* CCP Data Acuisition Parameters */

#define CCP_DAQ                   /* Enable synchronous data aquisition in ccpDaq() */
#define CCP_MAX_ODT         4     /* Number of ODTs in each DAQ lists */
#define CCP_MAX_DAQ         1     /* Number of DAQ lists */

#define CCP_CHECKSUM
#define CCP_CHECKSUM_TYPE   CCP_WORD

#define CCP_CMD_NOT_IN_INTERRUPT

/* CCP boot system, allow reprogramming */
#define CCP_PROGRAM

#define CCP_GET_SEND_PENDING_STATUS()  (ccp.SendStatus & CCP_SEND_PENDING)

extern void ccpHandleReprogRequest(const T_REPROG_INFO_TYPE *reprog_info);


#endif
