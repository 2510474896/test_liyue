/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/COMMS/project.pj $
        $RCSfile: can_ccp.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:45:48CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/

/* Global QAC warning suppression */

/*  DEVIATION:     0492
    DESCRIPTION:   Array subscripting applied to a function parameter declared as a pointer.
    JUSTIFICATION: This file contains well used legacy code. The QAC help text (below) associated 
    with this warning also implies that it is a question of company coding standards rather than 
    outright 'bad' code:-

    "This is perfectly legitimate in the C language providing the pointer addresses
    an array element; but some coding standards recommend that if a parameter refers to an
    array, it should be declared as an array."  */
    /* PRQA S 0492 EOF*/

/*  DEVIATION:     2215
    DESCRIPTION:   This indentation is not consistent with configured depth.
    JUSTIFICATION: To improve readability, we break this rule by indenting after a conditional compilation flag.
                    e.g we believe that 
                    #ifdef CCP_TESTMODE
                        static void ccpPrintDaqList( CCP_BYTE daq );
                    #endif
                    reads better than
                    #ifdef CCP_TESTMODE
                    static void ccpPrintDaqList( CCP_BYTE daq );
                    #endif  */
    /* PRQA S 2215 EOF*/

/*************************************************************/
/*      FILE DEFINITIONS                                     */
/*************************************************************/

#define CCP_CAN_INTERNAL

/*************************************************************/
/*      INCLUDE FILES                                        */
/*************************************************************/

#include "types.h"
#include "can.h"
#include "bootstrp.h"  /* for T_REPROG_INFO_TYPE */
#include "ccppar.h"
#include "ccp.h"
#include "comms.h"
#include "can_app_if.h"
#include "sw_utils.h"

/*************************************************************/
/*      CODE                                                 */
/*************************************************************/

#if defined ( C_ENABLE_CCP )

    #define CCP_CAN_ADAPTER_VERSION  0x0103
    #define CCP_CAN_ADAPTER_BUGFIX_VERSION 0x03


    /*----------------------------------------------------------------------------*/

    /* CCP_CAN_CHANNEL defines in ccppar.h (CANgen) the used CAN channel for CCP */

    #if (defined ( C_SINGLE_RECEIVE_BUFFER ) || defined ( C_MULTIPLE_RECEIVE_BUFFER ))
        #if defined ( CCP_CAN_CHANNEL )

            #if ( CCP_CAN_CHANNEL == 0 )
                #define CanTransmit CanTransmit_0
                #if defined ( C_ENABLE_TRANSMIT_QUEUE_0 )
                    #define C_ENABLE_TRANSMIT_QUEUE
                #endif
            #endif

            #if ( CCP_CAN_CHANNEL == 1 )
                #define CanTransmit CanTransmit_1
                #if defined ( C_ENABLE_TRANSMIT_QUEUE_1 )
                    #define C_ENABLE_TRANSMIT_QUEUE
                #endif
            #endif

            #if ( CCP_CAN_CHANNEL == 2 )
                #define CanTransmit CanTransmit_2
                #if defined ( C_ENABLE_TRANSMIT_QUEUE_2 )
                    #define C_ENABLE_TRANSMIT_QUEUE
                #endif
            #endif

            #if ( CCP_CAN_CHANNEL == 3 )
                #define CanTransmit CanTransmit_3
                #if defined ( C_ENABLE_TRANSMIT_QUEUE_3 )
                    #define C_ENABLE_TRANSMIT_QUEUE
                #endif
            #endif

            #if ( CCP_CAN_CHANNEL == 4 )
                #define CanTransmit CanTransmit_4
                #if defined ( C_ENABLE_TRANSMIT_QUEUE_4 )
                    #define C_ENABLE_TRANSMIT_QUEUE
                #endif
            #endif
        #else
            #if (kCanNumberOfChannels > 1)
                #error "! CCP only available in one instance - use CCP_CAN_CHANNEL !"
            #endif
        #endif /*CCP_CAN_CHANNEL*/

    #endif /*C_SINGLE_RECEIVE_BUFFER || C_MULTIPLE_RECEIVE_BUFFER*/

    /*----------------------------------------------------------------------------*/

    #if defined ( CCP_CALPAGE )
        static CCP_BYTE ccpCalPage = 0;
    #endif

    #if defined ( CCP_WRITE_EEPROM )
        void ccpCheckPendingEEPROM( void );
    #endif

    /******************************************************************************/
    /* The following functions are the interface between CCP and the CAN driver   */
    /******************************************************************************/

    /* Transmit the CCP message */
    void ccpSend(const CCP_BYTEPTR msg)
    {
        Can_ReturnType result;

        CCP_TX_DATA_PTR[0] = msg[0];
        CCP_TX_DATA_PTR[1] = msg[1];
        CCP_TX_DATA_PTR[2] = msg[2];
        CCP_TX_DATA_PTR[3] = msg[3];
        CCP_TX_DATA_PTR[4] = msg[4];
        CCP_TX_DATA_PTR[5] = msg[5];
        CCP_TX_DATA_PTR[6] = msg[6];
        CCP_TX_DATA_PTR[7] = msg[7];

        result = Comms_Send_CAN_message(CCP_TX,CCP_TX_DATA_PTR);

        #if defined ( C_ENABLE_TRANSMIT_QUEUE )
        if(result != CAN_OK)
        {
            /* Fatal Error, should never fail */
            ccpInit();
        }
        #else
        if(result != CAN_OK)
        {
            /* Set transmission request flag */
            ccp.SendStatus |= (CCP_BYTE)CCP_TX_PENDING;
        }
        #endif
    }
    /*----------------------------------------------------------------------------*/
    /* Perform CCP queue management */
    void CCP_tx_confirm_isr (void)
    {
        (void)ccpSendCallBack();/* Message transmitted */
    }


    /******************************************************************************/
    /* The following functions must be individually implemented if required       */
    /* There are samples available for C16x, HC12, SH7055                         */
    /******************************************************************************/

    /*
    ccpGetPointer

    Convert a memory address from CCP 8/32bit into a C pointer
    used for memory transfers like DNLOAD, UPLOAD (MTA)
    */

    #if defined ( ccpGetPointer )
    #else
        #ifdef C_COMP_ANSI_CANOE
            /* Datasegment-Pointer */
            #ifdef __BORLANDC__
                #define isDllAddr 0x58
                extern CCP_BYTE __isDLL;
                static CCP_DWORD dataSeg = (CCP_DWORD)(&__isDLL-isDllAddr);
            #else
                extern CCP_BYTE __xc_a;
                static CCP_DWORD dataSeg = (CCP_DWORD)&__xc_a;

                #ifndef CCP_OLD_ADRESS_CALC
                    #include <stdio.h>
                    #include <Windows.h>
                    #include <malloc.h>

                    typedef struct _MODULEINFO
                    {
                        LPVOID lpBaseOfDll;
                        DWORD SizeOfImage;
                        LPVOID EntryPoint;
                    } MODULEINFO, *LPMODULEINFO;

                    #define MAX_MODULE_NAME32 255

                    typedef struct tagMODULEENTRY32
                    {
                        DWORD   dwSize;
                        DWORD   th32ModuleID;
                        DWORD   th32ProcessID;
                        DWORD   GlblcntUsage;
                        DWORD   ProccntUsage;
                        BYTE  * modBaseAddr;
                        DWORD   modBaseSize;
                        HMODULE hModule;
                        TCHAR   szModule[MAX_MODULE_NAME32 + 1];
                        TCHAR   szExePath[MAX_PATH];
                    } MODULEENTRY32;

                    typedef enum
                    {
                        WINUnknown = 0,
                        WIN95,
                        WIN98,
                        WINME,
                        WINNT351,
                        WINNT40,
                        WIN2000,
                        WINXP
                    } winversion;


                    winversion GetWindowsVersion(void)
                    {
                        OSVERSIONINFO osvi;

                        memset(&osvi,0,sizeof(OSVERSIONINFO));
                        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

                        GetVersionEx(&osvi);

                        switch(osvi.dwPlatformId)
                        {
                            case VER_PLATFORM_WIN32_NT:
                            {
                                if(osvi.dwMajorVersion==3 && osvi.dwMinorVersion==51)
                                {
                                    return WINNT351;
                                }
                                if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion==0)
                                {
                                    return WINNT40;
                                }
                                if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion==0)
                                {
                                    return WIN2000;
                                }
                                if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion==1)
                                {
                                    return WINXP;
                                }
                                break;
                            }

                            case VER_PLATFORM_WIN32_WINDOWS:
                            {
                                if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion==0)
                                {
                                    return WIN95;
                                }
                                if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion==10)
                                {
                                    return WIN98;
                                }
                                if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion== 90 )
                                {
                                    return WIN98;
                                }
                                break;
                            }
                        }
                        return WINUnknown;
                    }



                    /*----------------------------------------------------------------------------*/
                    /* GetStartAddressNT(HMODULE hModule, char *ModuleName, DWORD *ErrorCode)     */
                    /*----------------------------------------------------------------------------*/
                    /* determine programm start adress                                            */
                    /* HMODULE hModule: Modulehandle in case of a DLL - in case of an EXE this    */
                    /*                  parameter should be NULL                                  */
                    /* char *ModuleName:Module Name. Only used in case of determine the start     */
                    /*                  address of other Modules in all other case dir Parameter  */
                    /*                  should be NULL                                            */
                    /* DWORD *ErrorCode:Error code                                                */
                    /*----------------------------------------------------------------------------*/
                    CCP_DWORD GetStartAddressNT(HMODULE hModule, char *ModuleName, DWORD *ErrorCode)
                    {
                        typedef BOOL  (WINAPI *ENUMPROCESSMODULES)(HANDLE hProcess, HMODULE * lphModule, DWORD cb, LPDWORD lpcbNeeded);
                        typedef DWORD (WINAPI *GETMODULEINFO)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD nSize);
                        typedef DWORD (WINAPI *GETMODULEBASENAME)(HANDLE hProcess, HMODULE hModule, LPTSTR  BaseName, DWORD nSize);

                        HINSTANCE             hPsapi;
                        CCP_DWORD StartAddress = 0;
                        ENUMPROCESSMODULES    EnumProcessModules;
                        GETMODULEINFO         GetModuleInfo;
                        GETMODULEBASENAME     GetModuleBaseName;
                        MODULEINFO            str;
                        HANDLE                hProcess;
                        DWORD                 dwModules;

                        hPsapi = LoadLibrary("PSAPI.DLL");
                        if (!hPsapi)
                        {
                            if (ErrorCode)
                            {
                                *ErrorCode = GetLastError();
                            }
                            return 0;
                        }

                        EnumProcessModules= (ENUMPROCESSMODULES)GetProcAddress(hPsapi, "EnumProcessModules");
                        GetModuleInfo     = (GETMODULEINFO)GetProcAddress(hPsapi, "GetModuleInformation");
                        GetModuleBaseName = (GETMODULEBASENAME)GetProcAddress(hPsapi, "GetModuleBaseNameA");

                        if(EnumProcessModules==0 || GetModuleInfo==0 || GetModuleBaseName==0)
                        {
                            FreeLibrary(hPsapi);
                            if (ErrorCode)
                            {
                                *ErrorCode = GetLastError();
                            }
                            return 0;
                        }

                        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

                        if(hProcess)
                        {
                            /* If the handle of the DLL is known */
                            if(hModule)
                            {
                                GetModuleInfo(hProcess, hModule,&str,sizeof(MODULEINFO));
                            }

                            /* If the handle is unkown, but the name of the DLL is known */
                            if(!hModule && ModuleName)
                            {
                                HMODULE *hModules;

                                EnumProcessModules(hProcess, NULL, 0, &dwModules);

                                if((hModules = (HMODULE *) malloc(dwModules)) == NULL)
                                {
                                    CloseHandle(hProcess);
                                    FreeLibrary(hPsapi);
                                    return 0;
                                }
                                else
                                {
                                    UINT i;

                                    EnumProcessModules(hProcess, hModules, dwModules, &dwModules);

                                    for(i=0; i<dwModules/sizeof(HMODULE); i++)
                                    {
                                        char MBuffer[MAX_PATH];
                                        GetModuleBaseName(hProcess,hModules[i],MBuffer,sizeof(MBuffer));
                                        if(stricmp(ModuleName,MBuffer)==0)
                                        {
                                            GetModuleInfo(hProcess, hModules[i],&str,sizeof(MODULEINFO));
                                            break;
                                        }
                                    }
                                    free(hModules);
                                }
                            }

                            if(!hModule && !ModuleName)
                            {
                                /* In case of an EXE-Application use always the first handle in hModules */
                                HMODULE hModules[1];

                                EnumProcessModules(hProcess, &hModules[0], sizeof(hModules), &dwModules);
                                GetModuleInfo(hProcess, hModules[0],&str, sizeof(MODULEINFO));
                            }

                            CloseHandle(hProcess);
                            StartAddress=(CCP_DWORD)str.lpBaseOfDll;
                        }
                        FreeLibrary(hPsapi);
                        return StartAddress;
                    }


                    /*----------------------------------------------------------------------------*/
                    /* GetStartAdressDefault(HMODULE hModule, char *ModuleName, DWORD *ErrorCode) */
                    /*----------------------------------------------------------------------------*/
                    /* determine programm start adress                                            */
                    /* HMODULE hModule: Modulehandle in case of a DLL - in case of an EXE this    */
                    /*                  parameter should be NULL                                  */
                    /* char *ModuleName:Module Name. Only used in case of determine the start     */
                    /*                  address of other Modules in all other case dir Parameter  */
                    /*                  should be NULL                                            */
                    /* DWORD *ErrorCode:Error code                                                */
                    /*----------------------------------------------------------------------------*/
                    CCP_DWORD GetStartAddressDefault(HMODULE hModule, char *ModuleName, DWORD *ErrorCode)
                    {
                        typedef HANDLE  (WINAPI *CREATETOOLHELP32SNAPSHOT)(DWORD Flags, DWORD ProcessID);
                        typedef HANDLE  (WINAPI *MODULE32FIRST)(HANDLE hSnapshot,MODULEENTRY32 *me);
                        typedef HANDLE  (WINAPI *MODULE32NEXT)(HANDLE hSnapshot,MODULEENTRY32 *me);

                        MODULEENTRY32 Modul = {0};
                        HANDLE hModuleSnap;
                        CCP_DWORD StartAddress = 0;
                        char Buffer[255];
                        char *pBuf = Buffer;
                        int len;

                        HINSTANCE                hKernel;
                        CREATETOOLHELP32SNAPSHOT CreateToolhelp32Snapshot;
                        MODULE32FIRST            Module32First;
                        MODULE32NEXT             Module32Next;

                        hKernel = LoadLibrary("KERNEL32.DLL");
                        if(!hKernel)
                        {
                            if (ErrorCode)
                            {
                                *ErrorCode = GetLastError();
                            }
                            return 0;
                        }

                        CreateToolhelp32Snapshot = (CREATETOOLHELP32SNAPSHOT) GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
                        Module32First= (MODULE32FIRST) GetProcAddress(hKernel, "Module32First");
                        Module32Next = (MODULE32NEXT) GetProcAddress(hKernel, "Module32Next");

                        if(Module32Next==0 || Module32First==0 || CreateToolhelp32Snapshot==0)
                        {
                            FreeLibrary(hKernel);
                            if (ErrorCode)
                            {
                                *ErrorCode = GetLastError();
                            }
                            return 0;
                        }

                        if (!ModuleName)
                        {
                            GetModuleFileName(hModule, Buffer, sizeof(Buffer));
                            len = strlen(Buffer);
                            while((Buffer[len--]!='\\') && (len>=0));
                                pBuf += len+2;
                        }
                        else
                        {
                            pBuf = ModuleName;
                        }

                        Modul.dwSize=sizeof(MODULEENTRY32);

                        hModuleSnap = CreateToolhelp32Snapshot(0x00000008, GetCurrentProcessId());
                        if (hModuleSnap == INVALID_HANDLE_VALUE)
                        {
                            if (ErrorCode)
                            {
                                *ErrorCode = -1;
                            }
                            return 0;
                        }

                        if (Module32First(hModuleSnap,&Modul))
                        {
                            do
                            {
                                if (stricmp((pBuf),(Modul.szModule))==0)
                                {
                                    StartAddress = (CCP_DWORD)Modul.modBaseAddr;
                                    break;
                                }
                            }
                            while (Module32Next(hModuleSnap, &Modul));
                        }
                        CloseHandle(hModuleSnap);
                        FreeLibrary(hKernel);
                        return StartAddress;
                    }


                    /*----------------------------------------------------------------------------*/
                    /* GetStartAdress(HMODULE hModule, char *ModuleName, DWORD *ErrorCode)        */
                    /*----------------------------------------------------------------------------*/
                    /* determine programm start adress                                            */
                    /* HMODULE hModule: Modulehandle in case of a DLL - in case of an EXE this    */
                    /*                  parameter should be NULL                                  */
                    /* char *ModuleName:Module Name. Only used in case of determine the start     */
                    /*                  address of other Modules in all other case dir Parameter  */
                    /*                  should be NULL                                            */
                    /* DWORD *ErrorCode:Error code                                                */
                    /*----------------------------------------------------------------------------*/
                    CCP_DWORD GetStartAddress(HMODULE hModule, char* ModuleName, DWORD *ErrorCode)
                    {
                        winversion WinVers = GetWindowsVersion();
                        if(WinVers==WINNT40 || WinVers==WINNT351)
                        {
                            return GetStartAddressNT(hModule, ModuleName, ErrorCode);
                        }
                        else
                        {
                            return GetStartAddressDefault(hModule, ModuleName, ErrorCode);
                        }

                        return 0;
                    }
                #endif
            #endif /* MSVC compiler */

            CCP_BYTEPTR ccpGetPointer( CCP_BYTE addr_ext, CCP_DWORD addr )
            {
                CCP_BYTEPTR a;
                #ifndef CCP_OLD_ADRESS_CALC
                    static CCP_BYTE flag=0;
                    DWORD ErrorCode = 0;

                    if (flag==0)
                    {
                        char nodeName[255];

                        sprintf(nodeName,"%s.dll",CANoeAPI_GetNodeName());
                        dataSeg = GetStartAddress(NULL,nodeName,&ErrorCode);

                        if (ErrorCode)
                        {
                            uint8 acString[256];

                            sprintf(acString,"CCP Driver Error <%d>: Error during address calculation", ErrorCode);
                            CANoeAPI_WriteString(acString);
                        }
                        flag=1;
                    }
                #endif

                a = (CCP_BYTEPTR)(addr+dataSeg);
                if (addr<2)
                {
                    return (CCP_BYTEPTR)addr;
                }

                #if defined(CCP_CALPAGE)
                    if (a>=(CCP_BYTE*)&CALRAM_START && a<=(CCP_BYTE*)&CALRAM_LAST)
                    {
                        /* Address within Calibration RAM */
                        if (ccpCalPage==0)
                        {
                            /* RAM */
                            return (CCP_BYTEPTR)a;
                        }
                        else
                        {
                            /* FLASH */
                            return (CCP_BYTEPTR)(ccpFlash+(a-(CCP_BYTE*)&CALRAM_START));
                        }
                    }
                    else
                #endif
                {
                    return (CCP_BYTEPTR)a;
                }
            }
        #else
            CCP_MTABYTEPTR ccpGetPointer(CCP_BYTE addr_ext, CCP_DWORD addr)
            {

                #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
                    /* avoid compiler warning due to unused parameters */
                    addr_ext = addr_ext;
                #endif

                /*  DEVIATION:     0306
                    DESCRIPTION:   Cast between a pointer to object and an integral type
                    JUSTIFICATION: The memory adress required for the operation like upload or download is 
                     received as a 32bit integer in the CCP message request. This has to be converted to a C 
                     pointer to that memory locatin. Hence the typecase cannot be avoided. This has been tested*/
                /* PRQA S 0306 1*/
                return (CCP_MTABYTEPTR)addr;
            }
        #endif
    #endif


    /*
    ccpGetDaqPointer

    Convert a memory address from CCP 8/32bit into a address
    stored in the ODT entries for DAQ.

    This is for reducing memory space used for DAQ lists.
    For example on a 32 bit microcontroller, a DAQ pointer may be stored as 16 bit
    value. DAQ will add the base address CCP_DAQ_BASE_ADDR before dereferencing the
    pointer. This will limit data acquisition to a single 64K memory range, but it
    will save 50% memory used for DAQ lists.

    Note: It must be possible to calculate the final address for DAQ like
     value = * (CCP_DAQ_BASE_ADDR + addr);
    */

    #if defined ( CCP_DAQ_BASE_ADDR )
        CCP_DAQBYTEPTR ccpGetDaqPointer(CCP_BYTE addr_ext, CCP_DWORD addr)
        {
            return (CCP_DAQBYTEPTR)(ccpGetPointer(addr_ext, addr) - CCP_DAQ_BASE_ADDR);
        }
    #endif



    /*----------------------------------------------------------------------------*/
    /* Check addresses for valid write access */
    /* Used only if Write Protection is required */
    /* Returns false if access denied */
    #if defined ( CCP_WRITE_PROTECTION )
        CCP_BYTE ccpCheckWriteAccess(CCP_MTABYTEPTR a, CCP_BYTE s)
        {
            /* Protect CCP */
            if(a+s>=(CCP_MTABYTEPTR)&ccp && a<(CCP_MTABYTEPTR)&ccp+sizeof(ccp))
            {
                return 0;
            }

            return 1;
        }
    #endif


    /*----------------------------------------------------------------------------*/
    /* Flash Kernel Download */
    /* Used only of Download of the Flash Kernel is required */
    #if defined ( CCP_BOOTLOADER_DOWNLOAD )
        CCP_BYTE ccpDisableNormalOperation(CCP_MTABYTEPTR a, CCP_WORD s)
        {
            #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
                /* avoid compiler warning due to unused parameters */
                a = a;
                s = s;
            #endif

            /* CANape attempts to download the flash kernel to CCP_RAM */
            /* Address is a */
            /* Size is s bytes */

            /* ... */

            /* return 0; */ /* Refused */
            return 1; /* Ok */
        }
    #endif

    /*----------------------------------------------------------------------------*/
    /* Example: Calibration CCP_RAM/CCP_ROM Selection */
    /* Used if Flash Programming is required */

    #if defined ( CCP_CALPAGE ) || defined ( CCP_PROGRAM )
        CCP_DWORD ccpGetCalPage(void)
        {
            return (CCP_DWORD)ccpCalPage;
        }

        void ccpSetCalPage(CCP_DWORD a)
        {
            ccpCalPage = (CCP_BYTE)a;

            #if defined ( CANBOX ) || defined ( PHYTEC_MM167 )
                if (ccpCalPage==1)
                {/* CCP_RAM */
                    #pragma asm
                    mov DPP1,#11h
                    #pragma endasm
                }
                else
                {/* CCP_ROM */
                    #pragma asm
                    mov DPP1,#05h
                    #pragma endasm
                }
            #endif
        }

        void ccpInitCalPage(void)
        {
            #if defined ( CANBOX ) || defined ( PHYTEC_MM167 )

                #define CALROM_ADDR 0x14000
                #define CALRAM_ADDR 0x44000
                huge CCP_BYTE *p1 = (huge CCP_BYTE *)CALROM_ADDR;
                huge CCP_BYTE *p2 = (huge CCP_BYTE *)CALRAM_ADDR;
                unsigned int i;

                for(i = 0; i < 0x4000; i++)
                {
                    *p2++ = *p1++;
                }
            #endif
        }
    #endif

    /*----------------------------------------------------------------------------*/
    /* Example: Seed&Key*/
    /* Used only if Seed&Key is required */

    #if defined ( CCP_SEED_KEY )

        CCP_BYTE ccpResourceMask = 0;
        CCP_DWORD ccpLastSeed = 0;

        CCP_DWORD ccpGetSeed(CCP_BYTE resourceMask)
        {
            ccpResourceMask = resourceMask;

            /* Generate a seed */

            /* Example: */
            /* Optimum would be a number which never appears twice */
            #if defined ( CCP_TIMESTAMPING )
                ccpLastSeed = ccpGetTimestamp() * ccpGetTimestamp();
                return ccpLastSeed;
            #endif

            return 0;
        }

        CCP_BYTE ccpUnlock(CCP_BYTE *key)
        {
            /* Check the key */

            /* Example: */
            ccpLastSeed = (ccpLastSeed>>5) | (ccpLastSeed<<23);
            ccpLastSeed *= 7;
            ccpLastSeed ^= 0x26031961;

            if(*(CCP_DWORD*)key != ccpLastSeed)
            {
                return 0;
            }

            /* Reset resource protection bit */
            return ccpResourceMask;
        }
    #endif /* defined ( CCP_SEED_KEY ) */


    /*----------------------------------------------------------------------------*/
    /* Example: EEPROM write access */
    /* Used only if required */

    #if defined ( CCP_WRITE_EEPROM )

        /* Pending EEPROM write cycle */
        CCP_BYTE ccpEEPROMState = 0;

        /* EEPROM write */
        /* Return values for ccpCheckWriteEEPROM:
           CCP_WRITE_OK      - EEPROM written
           CCP_WRITE_DENIED  - This address is not in EEPROM
           CCP_WRITE_PENDING - EEPROM write in progress, call ccpSendCrm() when done
           CCP_WRITE_ERROR   - EEPROM write failed
        */
        CCP_BYTE ccpCheckWriteEEPROM(CCP_MTABYTEPTR addr, CCP_BYTE size, CCP_BYTEPTR data)
        {
            /* Check address for EEPROM */
            if(addr<EEPROM_START || addr>EEPROM_END)
            {
                /* Not EEPROM */
                /* Let the CCP driver perform a standard CCP_RAM write access */
                return CCP_WRITE_DENIED;
            }

            /* Alternative 1: */
            /* Initiate EEPROM write */
            /* When finished, call ccpSendCrm() */
            #if defined ( C_CLIENT_BMWAG )

                #if ( EEBUFFER < 5 )
                    #error "! CCP will need at least 5 Entries in EEBUFFER !"
                #endif

                if(EECheckBuffer() > (EEBUFFER_MAX - size))
                {
                    return CCP_WRITE_ERROR;
                }

                while(size--)
                {
                    if(E_OK != EEAddByte((unsigned int) addr++,*data++))
                    {
                        return CCP_WRITE_ERROR;
                    }
                }

                ccpEEPROMState = CCP_WRITE_PENDING;

                return CCP_WRITE_PENDING;

                /* Alternative 2: */
                /* Write to EEPROM here and wait until finished */
            #else

                eeWrite(addr,data,size);
                return CCP_WRITE_OK;

            #endif
        }

        /* Check for EEPROM write finished */
        void ccpCheckPendingEEPROM( void )
        {
            #if defined ( C_CLIENT_BMWAG )
                if(ccpEEPROMState == CCP_WRITE_PENDING)
                {
                    if(EECheckBuffer() == 0)
                    {
                        ccpSendCrm();
                        ccpEEPROMState = 0;
                    }
                }
            #endif
        }

    #endif   /* defined ( CCP_WRITE_EEPROM ) */


    #if defined ( CCP_READ_EEPROM )
        /* EEPROM read */
        /* Return values for ccpCheckReadEEPROM:
           0 (FALSE)    - This address is not in EEPROM
           1 (TRUE)     - EEPROM read
        */
        CCP_BYTE ccpCheckReadEEPROM( CCP_MTABYTEPTR addr, CCP_BYTE size, CCP_BYTEPTR data )
        {

            /* Read EEPROM */
            #if defined ( C_CLIENT_BMWAG )
                /* Check address for EEPROM */
                if((addr < EEPROM_START) || (addr > EEPROM_END))
                {
                    /* Not EEPROM */
                    /* Let the CCP driver perform a standard CCP_RAM read access */
                    return 0;
                }

                while(size-- > 0)
                {
                    *data++ = EEReadByte(addr++);
                }

                return 1;
            #else
                return 0;
            #endif
        }

    #endif /* defined ( CCP_READ_EEPROM ) */


    void ccpHandleReprogRequest(const T_REPROG_INFO_TYPE *reprog_info)
    {
        if(System_Dld_Reason == (U8)SYS_REPROG_REQUEST_CCP)
        {
            /* We are conitnuing the communication that was established
               in the main application ...
            */

            /* Connect: */
            ccp.SessionStatus |= SS_CONNECTED;
            ccp.SessionStatus &= INVERT_BITS_IN_BYTE(SS_TMP_DISCONNECTED);

            /* Set MTA: */
            ccp.MTA[0] = ccpGetPointer(0,reprog_info->ccp_erase_address);

            /* Clear memory:  */
            CCP_RX_DATA_PTR[0] = CC_CLEAR_MEMORY;
            CCP_RX_DATA_PTR[1] = reprog_info->ccp_ctr;

            CCP_RX_DATA_PTR[2] = (U8)(((reprog_info->ccp_erase_size) & 0xFF000000U) >> 24);
            CCP_RX_DATA_PTR[3] = (U8)(((reprog_info->ccp_erase_size) & 0xFF0000U)   >> 16);
            CCP_RX_DATA_PTR[4] = (U8)(((reprog_info->ccp_erase_size) & 0xFF00U)     >> 8 );
            CCP_RX_DATA_PTR[5] = (U8)(((reprog_info->ccp_erase_size) & 0xFFU)            );

            CCP_RX_DATA_PTR[6] = 0;
            CCP_RX_DATA_PTR[7] = 0;


            ccpCommand(CCP_RX_DATA_PTR);
        }
    }

#endif /* C_ENABLE_CCP */

