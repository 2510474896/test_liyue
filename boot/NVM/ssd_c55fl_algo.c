/* PRQA S 0292 17 */
/*********************************************************************
    MODULE SPECIFICATION:

        $ProjectName: /DAS/060_Projects/<DF_> DF/<X37_Rad> DFPV X37 MY2021 Radar AC1k/040_Product/030_Software/050_Construction/020_SW_Development/MainBoot/NVM/project.pj $
        $RCSfile: ssd_c55fl_algo.c $
        $Revision: 1.1 $
        $Date: 2019/06/25 14:46:32CST $

        TRW Ltd owns the copyright in this document and associated
        documents and all rights are reserved.  These documents must
        not be used for any purpose other than that for which they
        are supplied and must not be copied in whole or in part or
        disclosed to others without prior written consent of TRW
        Ltd. Any copy of this drawing or document made by any method
        must also include a copy of this legend.

    $CopyrightDate: (c) ZF 2019 $

*********************************************************************/


/************************************************************************
 * (c) Copyright Freescale Semiconductor, Inc 2011, All Rights Reserved  *
 *************************************************************************

 *************************************************************************
 *                                                                       *
 *               Standard Software Driver for C55fl                      *
 *                                                                       *
 *               VLE_Instruction set                                     *
 *               Release   v1.0.0                                        *
 *************************************************************************/


/***************************************************************************
*
*   Deviations from QAC - global
*
****************************************************************************/
/* DEVIATION:     1255
   DESCRIPTION:   Unsuffixed integer constant is not of type int.
   JUSTIFICATION: Code originally developed by 3rd party and it is better to not change it.
*/
/* PRQA S 1255 EOF */

/* DEVIATION:     1281
   DESCRIPTION:   Integer literal constant is of an unsigned type but does not include a "U" suffix.
   JUSTIFICATION: Code originally developed by 3rd party and it is better to not change it.
*/
/* PRQA S 1281 EOF */

/* DEVIATION:     3408
   DESCRIPTION:   '%s' has external linkage and is being defined without any previous declaration.
   JUSTIFICATION: Code originally developed by 3rd party and it is better to not change it.
*/
/* PRQA S 3408 EOF */

/***************************************************************************/


const unsigned long __attribute__((section(".fls_driver")))BlankCheck_C[] = 
{
    0x182106D0, 0x00801AC1, 0x0908DD01, 0x013F014E, 0x015D016C, 
    0x017B030A, 0x48097FC6, 0xEB7874C6, 0x07BF2A06, 0xE6034819, 
    0xE8212A0D, 0xE61F77B6, 0xF0BF4DA6, 0x7C163040, 0x7EE6B05E, 
    0x48087C18, 0xB840E00D, 0xC07E1807, 0xACFFE606, 0x4A09D0EC, 
    0xC06ED06B, 0xE80B203E, 0x2008E8F2, 0xD0EA76E7, 0x103B07D7, 
    0xD17AD3CA, 0xD4BA30FF, 0x003C2A07, 0xE6070193, 0x1800D000, 
    0x00001800, 0xD0000193, 0x1AC10808, 0xCD010090, 0x18218030, 
    0x00044D50, 0x43353542, 0x43313030
    
}; /* Total Data Size = 152 bytes */


const unsigned long __attribute__((section(".fls_driver")))FlashCheckStatus_C[] = 
{
    0x182106D0, 0x00801B01, 0x0910DD01, 0x013F014E, 0x015D016C, 
    0x62FB4806, 0xD06D77CB, 0x063F180B, 0xA803E50D, 0xE638180B, 
    0xA800E611, 0x180BA801, 0x7A120192, 0x180BA802, 0xE611E85E, 
    0x180BA804, 0xE643180B, 0xA8057A12, 0x0208E856, 0xC88C30DF, 
    0x00342A06, 0xE654C0AF, 0xE854C88C, 0xC16C2A06, 0x7A1202D6, 
    0x62EB00B8, 0xC15CC26C, 0xC37C511C, 0x0010513C, 0x0014C04C, 
    0x01F302C2, 0x0007D03D, 0xC07D2A07, 0x7A0201B8, 0xC17C2A07, 
    0x7A0202AA, 0x780001AC, 0xC88CC16C, 0x2A067A12, 0x029C62EB, 
    0x00B8C15C, 0xC36CC47C, 0xC04C01F3, 0x02C00007, 0xD03DC07D, 
    0x2A077A02, 0x018CC17C, 0x2A077A02, 0x02787800, 0x0180C88C, 
    0xC16C2A06, 0x7A12026A, 0x62EB00B8, 0xC15CC04C, 0x01F301C7, 
    0x2C060007, 0xD03DC07D, 0x2A077A02, 0x0162C17C, 0x2A077A02, 
    0x02487800, 0x0156630B, 0x7800023E, 0xC0AF203A, 0xC09A67B9, 
    0x7A120232, 0x6759E659, 0x67C9E609, 0x67D9E604, 0x496B7800, 
    0x0220494B, 0x7800021A, 0x6769E630, 0x67F9E626, 0xC07A70C3, 
    0x7FFE4667, 0xD07AC17C, 0x2A07E612, 0x62EB00B8, 0xC16CC27C, 
    0xC05C01F3, 0x480402C0, 0x0007D03D, 0xC07D2A07, 0x7A1201E6, 
    0x62FB7800, 0x01E0C07A, 0x70C37F7F, 0x4667D07A, 0xC07A70C3, 
    0x7FEF4667, 0xD07A7800, 0x01C867D9, 0xE604493B, 0x780001BE, 
    0x491B7800, 0x01B867F9, 0xE6144887, 0xD07DC06A, 0x70E37FFE, 
    0x4676D06A, 0xC06A70E3, 0x7F7F4676, 0xD06AC06A, 0x70E37FEF, 
    0x4676D06A, 0x7800018E, 0x67D9E604, 0x493B7800, 0x0184491B, 
    0x7800017E, 0x62EB7800, 0x017830FF, 0x00342A07, 0xE603C0AF, 
    0xE803C0AF, 0x203AC09A, 0x67D97A12, 0x01606759, 0xE62D67E9, 
    0xE604495B, 0x78000152, 0x6769E60C, 0x67F9E607, 0xC07A70C3, 
    0x7FFE4667, 0xD07AE80F, 0x492B7800, 0x01384907, 0xD07D67F9, 
    0xE607C07A, 0x70C37FFE, 0x4667D07A, 0xE80262FB, 0x2B2B7A12, 
    0x011CC07A, 0x70C37F7F, 0x4667D07A, 0xC07A70C3, 0x7FFB4667, 
    0xD07A7800, 0x010462EB, 0x780000FE, 0x62FB7800, 0x00F862FB, 
    0x780000F2, 0x62FB7800, 0x00EC30FF, 0x00342A07, 0xE204637B, 
    0x780000DE, 0xC07F1B47, 0x8054C09A, 0x67E9E668, 0x67F9E665, 
    0x6799E603, 0x497BE862, 0xC07F50E7, 0x0058C76C, 0xC0660D67, 
    0xE240C07F, 0x50E7005C, 0xC76CC166, 0x0D67E239, 0xC07F50E7, 
    0x0060C76C, 0xC2660D67, 0xE232C07F, 0x50E70064, 0xC76CC366, 
    0x0D67E22B, 0xC07F50E7, 0x0068C76C, 0xC4660D67, 0xE224C07F, 
    0x50E7006C, 0xC76CC566, 0x0D67E21D, 0xC07F50E7, 0x0070C76C, 
    0xC6660D67, 0xE216C07F, 0x50E70074, 0xC76CC766, 0x0D67E20F, 
    0xC07F50E7, 0x0078C76C, 0xC8660D67, 0xE208C07F, 0x50E7007C, 
    0xC76CC966, 0x0D67E604, 0x6357D07D, 0xE8034807, 0xD07D6769, 
    0xE609C07F, 0xC0776727, 0xE6034B0B, 0xE80F4B1B, 0xE80DC07A, 
    0x18E7CCDB, 0xD07AC06A, 0x61E6D06A, 0xC07A6007, 0xD07AE802, 
    0x62EB30FF, 0x003C2A07, 0xE60701B3, 0x1800D000, 0x00001800, 
    0xD00001B3, 0x1B010810, 0xCD010090, 0x18218030, 0x00044D50, 
    0x43353543, 0x53313030
    
}; /* Total Data Size = 868 bytes */


const unsigned long __attribute__((section(".fls_driver")))FlashErase_C[] = 
{
    0x182106C0, 0x00801AA1, 0x09145401, 0x0044013F, 0x014E015D, 
    0x016C017B, 0x030AC08F, 0x028F52D7, 0x00004809, 0x77CB063F, 
    0x180BA800, 0xE60B180B, 0xA801E608, 0x180BA802, 0xE608180B, 
    0xA803E605, 0xE80E52BF, 0x0004E80E, 0x52BF0030, 0x480D480C, 
    0x480B4807, 0xD07A4806, 0xD16AE804, 0x63197800, 0x013476C0, 
    0x06F72A00, 0xE20976C0, 0x077B2A00, 0xE60876C7, 0x07BF2A07, 
    0xE6044849, 0x78000116, 0x77C7063F, 0x2A07E605, 0x77C7063F, 
    0x2A17E24F, 0x2C07C26F, 0xC35F0456, 0xC44F0446, 0x18C6B020, 
    0x406746D7, 0x017D2C07, 0xC56FC65F, 0x0456C74F, 0x044618C6, 
    0xB0204067, 0x46C7017C, 0x2C07C86F, 0xC95F0456, 0xCA4F0446, 
    0x18C6B020, 0x406746B7, 0x017BCB7F, 0x23F7E50C, 0xC07A2C06, 
    0xCB5F18A5, 0xB0204056, 0x4667D07A, 0x4807D17A, 0xE80C2C07, 
    0xD07AC16A, 0x2C07CB5F, 0x25F518A5, 0xB0204057, 0x4676D16A, 
    0x7F67EB78, 0x44C7C06A, 0x4467C15A, 0x44572A07, 0xE63F77A7, 
    0x801F44C7, 0xDE78DFB8, 0xC06A54D8, 0x0040C17A, 0x54F80044, 
    0x50F70000, 0x65D774E7, 0x04DF54F7, 0x000050D7, 0x000067D6, 
    0xE2034829, 0xE82777C7, 0x063F2A17, 0xE60577C7, 0x063F2A37, 
    0xE21550F7, 0x00006587, 0x74E704DF, 0x54F70000, 0x50D70000, 
    0x6786E20A, 0x50F70000, 0x70C37FFB, 0x466754F7, 0x00006369, 
    0xE80B2C07, 0x54F50000, 0x50D70000, 0x65F674C6, 0x04DF54D7, 
    0x000030FF, 0x003C2A07, 0xE6070193, 0x1800D000, 0x00001800, 
    0xD0000193, 0x1AA10814, 0x50010044, 0x00901821, 0x80400004, 
    0x4D504335, 0x35464531, 0x303000
    
}; /* Total Data Size = 452 bytes */


const unsigned long __attribute__((section(".fls_driver")))FlashInit_C[] = 
{
    0x182106E0, 0x00801BA1, 0x0914D901, 0x013F480E, 0x30DF0034, 
    0x2A06E631, 0xC07FC06F, 0xC06618C6, 0xD1E0D067, 0xC07FC2D7, 
    0x77A6077F, 0x6C16D26F, 0x77A7EFBF, 0x6C17D37F, 0x77A6DF7F, 
    0x6C16D46F, 0x77A7C77F, 0x6C17D57F, 0x77A6AFBF, 0x6C16D66F, 
    0x77A79F7F, 0x6C17D77F, 0x77A6877F, 0x6C16D86F, 0x77A76FBF, 
    0x6C17D97F, 0x77A65F7F, 0x6C16DA6F, 0x77A746FF, 0x6C17DB7F, 
    0x30FF003C, 0x2A07E607, 0x01E31800, 0xD0000000, 0x1800D000, 
    0x01E31BA1, 0x0814C901, 0x009021F1, 0x00044D50, 0x43353546, 
    0x49313030
    
}; /* Total Data Size = 164 bytes */


const unsigned long __attribute__((section(".fls_driver")))FlashProgram_C[] = 
{
    0x182106C0, 0x00801A81, 0x09105401, 0x0044013F, 0x014E015D, 
    0x016C017B, 0x030A4809, 0x30DF0034, 0x2A06E208, 0x77C7063F, 
    0x2A07E604, 0x63797800, 0x00E677A7, 0x077F2A07, 0xE2077F67, 
    0xE37874E7, 0x07BF2A07, 0xE6034819, 0xE86630FF, 0x00342A07, 
    0xE60452FF, 0x0000E805, 0x52FF0000, 0x1AF78004, 0x52D70000, 
    0x76C006F7, 0x2A00E605, 0x1AC7C809, 0x2A07E205, 0x76C7077D, 
    0x2A47E203, 0x4849E84B, 0x2A0CE649, 0x50F70000, 0x65B774E7, 
    0x04DF54F7, 0x000050D7, 0x000067B6, 0xE2034829, 0xE83C77C7, 
    0x063F2A07, 0xE61550F7, 0x00006587, 0x74E704DF, 0x54F70000, 
    0x50D70000, 0x6786E20A, 0x50F70000, 0x70C37FEF, 0x466754F7, 
    0x00006369, 0xE824CE7F, 0x0D7C7EA7, 0xE05E76B4, 0xF0BF4808, 
    0x7C18A040, 0xE010C07B, 0xD07D203D, 0x203B243C, 0xCE7F7C1D, 
    0x3B960570, 0x7CE0E850, 0x2A07E603, 0x2008E8EF, 0xD0DAD1CA, 
    0xD2BA50F7, 0x000065F7, 0x74E704DF, 0x54F70000, 0x30FF003C, 
    0x2A07E607, 0x01931800, 0xD0000000, 0x1800D000, 0x01931A81, 
    0x08105001, 0x00440090, 0x18218040, 0x00044D50, 0x43353546, 
    0x50313030
    
}; /* Total Data Size = 324 bytes */

const unsigned long __attribute__((section(".fls_driver")))FlashResume_C[] = 
{
    0x182106D0, 0x00801B21, 0x0914DD01, 0x013F014E, 0x480D30DF, 
    0x00342A06, 0xE603C0CF, 0xE803C0CF, 0x203CC0BC, 0x48F94A07, 
    0x907E480A, 0x67CBE609, 0x4A17907E, 0x488A67EB, 0xE60B4A37, 
    0x907EE808, 0x1B67C812, 0x2A27E216, 0x4A27907E, 0x482AC07C, 
    0x65F774E7, 0x04DFD07C, 0xC06C45A6, 0x74C604DF, 0xD06CC07C, 
    0x6757E606, 0x240918F9, 0x80012A07, 0xE2F930FF, 0x003C2A07, 
    0xE60701D3, 0x1800D000, 0x00001800, 0xD00001D3, 0x1B210814, 
    0xCD010090, 0x18218030, 0x00044D50, 0x43353546, 0x52313030
    
}; /* Total Data Size = 160 bytes */

const unsigned long __attribute__((section(".fls_driver")))FlashSuspend_C[] = 
{
    0x182106E0, 0x00801B41, 0x0908D901, 0x013F014E, 0x480A480D, 
    0x4907907E, 0x30DF0034, 0x2A06E603, 0xC0CFE803, 0xC0CF203C, 
    0xC0BC1B66, 0xC8142A06, 0xE6497767, 0x06F92B07, 0xE6057767, 
    0x077D2A47, 0xE22B67FB, 0xE20D67BB, 0xE6084917, 0x907E67DB, 
    0xE6314937, 0x907EE82E, 0x4927907E, 0xE82B67BB, 0xE60EC07C, 
    0x65C774E7, 0x04DFD07C, 0x480A7747, 0x043F1807, 0xA8A0E010, 
    0x200AE8FA, 0xC07C65E7, 0x74E704DF, 0xD07C480A, 0x7747043F, 
    0x70079940, 0xE003200A, 0xE8FAC0BC, 0x67CBE608, 0x4947907E, 
    0x67EBE608, 0x4967907E, 0xE80567EB, 0xE6034957, 0x907EC07C, 
    0x6757E6FE, 0xC07C70C3, 0x7FFE4667, 0xD07C30FF, 0x003C2A07, 
    0xE60701D3, 0x1800D000, 0x00001800, 0xD00001D3, 0x1B410808, 
    0xC9010090, 0x21F10004, 0x4D504335, 0x35465331, 0x303000
    
}; /* Total Data Size = 240 bytes */

const unsigned long __attribute__((section(".fls_driver")))GetLock_C[] = 
{
    0x182106D0, 0x00801AE1, 0x090CDD01, 0x013F014E, 0x015D480C, 
    0x30DF0034, 0x2A06E607, 0xC07FC487, 0xC06F52E6, 0x0014E806, 
    0xC07FCA87, 0xC06F52E6, 0x002C77CB, 0x063F180B, 0xA803E50C, 
    0xE638180B, 0xA800E60F, 0x180BA801, 0xE61A180B, 0xA802E623, 
    0xE85B180B, 0xA804E63F, 0x180BA805, 0xE651E854, 0x018B4909, 
    0x2C06C27F, 0xC35F0457, 0xC44F0447, 0x18E7B020, 0x407674DA, 
    0x801FE848, 0x018B4809, 0x2C0AC57F, 0xC65F0457, 0xC74F0447, 
    0x18E7B020, 0x407AE83C, 0x03FB4809, 0x2C0AC87F, 0xC95F0457, 
    0xCA4F0447, 0x18E7B020, 0x407AE830, 0x30FF0034, 0x2A07E609, 
    0xC07FC6B7, 0x4809CB7F, 0x23F7E405, 0x2C0AE824, 0x637CE826, 
    0x2C0ACB6F, 0x18C6B020, 0x406AE81C, 0x30FF0034, 0x2A07E60E, 
    0xC07FC7B7, 0x4809CB7F, 0x23F7E10A, 0x2C0ACB6F, 0x25F618C6, 
    0xB020406A, 0xE80B637C, 0xE80D480A, 0xE807018B, 0x49F9620A, 
    0xE803638C, 0xE8057F67, 0xD0384097, 0xD07D30FF, 0x003C2A07, 
    0xE60701C3, 0x1800D000, 0x00001800, 0xD00001C3, 0x1AE1080C, 
    0xCD010090, 0x18218030, 0x00044D50, 0x43353547, 0x4C313030
    
}; /* Total Data Size = 320 bytes */


const unsigned long __attribute__((section(".fls_driver")))ProgramVerify_C[] = 
{
    0x182106C0, 0x00801A81, 0x09105401, 0x0044013F, 0x014E015D, 
    0x016C017B, 0x030A0319, 0x032872E0, 0x00007F86, 0xF37844D6, 
    0x74C607BF, 0x2A06E604, 0x72E00001, 0xE8292A0D, 0xE62777B4, 
    0xF0BF4D06, 0x7C143040, 0x7EA6A05E, 0x72C00000, 0x7C16A840, 
    0xE012C07E, 0xC06C0D67, 0xE60972E0, 0x0040D0EB, 0xC06ED06A, 
    0xC07CD079, 0xE80F203E, 0x203C1AD6, 0x8001E8ED, 0xD0E876A7, 
    0x103B07D7, 0xD178D2C8, 0xD3B8D4A8, 0xD59830FF, 0x003C2A07, 
    0xE60703F3, 0x1800D000, 0x00001800, 0xD00003F3, 0x1A810810, 
    0x50010044, 0x00901821, 0x80400004, 0x4D504335, 0x35505631, 
    0x303000
    
}; /* Total Data Size = 184 bytes */

const unsigned long __attribute__((section(".fls_driver")))SetLock_C[] = 
{
    0x182106D0, 0x00801AE1, 0x090CDD01, 0x013F014E, 0x015D480C, 
    0x30DF0034, 0x2A06E605, 0x490872E0, 0x0014E804, 0x4A8872E0, 
    0x002C77CB, 0x063F180B, 0xA803E50C, 0xE638180B, 0xA800E60F, 
    0x180BA801, 0xE61A180B, 0xA802E623, 0xE859180B, 0xA804E63E, 
    0x180BA805, 0xE64FE852, 0x018B4909, 0x2C06C27F, 0xC35F0457, 
    0xC44F0447, 0x18E7B020, 0x407674DA, 0x801FE846, 0x018B4809, 
    0x2C0AC57F, 0xC65F0457, 0xC74F0447, 0x18E7B020, 0x407AE83A, 
    0x03FB4809, 0x2C0AC87F, 0xC95F0457, 0xCA4F0447, 0x18E7B020, 
    0x407AE82E, 0x30FF0034, 0x2A07E608, 0x498B4809, 0xCB7F23F7, 
    0xE4052C0A, 0xE823637C, 0xE8362C0A, 0xCB6F18C6, 0xB020406A, 
    0xE81B30FF, 0x00342A07, 0xE60D49CB, 0x4809CB7F, 0x23F7E10A, 
    0x2C0ACB6F, 0x25F618C6, 0xB020406A, 0xE80B637C, 0xE81E480A, 
    0xE807018B, 0x49F9620A, 0xE803638C, 0xE816C07F, 0x04B7017B, 
    0xC06B45A6, 0xD06B7FB8, 0xC83046A8, 0xC06B4486, 0xD06B52FB, 
    0x00007EF7, 0xC0387C18, 0xB84062D6, 0x7F9C309E, 0x30FF003C, 
    0x2A07E607, 0x01C31800, 0xD0000000, 0x1800D000, 0x01C31AE1, 
    0x080CCD01, 0x00901821, 0x80300004, 0x4D504335, 0x35534C31, 
    0x303000
    
}; /* Total Data Size = 344 bytes */

const unsigned long __attribute__((section(".fls_driver")))FlashAbort_C[] = 
{
    0x182106E0, 0x00801BC1, 0x0918D901, 0x013F4807, 0xD37130DF, 
    0x00342A06, 0xE604C07F, 0xD271E804, 0xC07F2037, 0xD271C271, 
    0xC0E767EE, 0xE60967CE, 0xE6044837, 0xD371E808, 0x4827D371, 
    0xE80567CE, 0xE6034817, 0xD371C371, 0x67F7E614, 0xC271C077, 
    0x6757E6FD, 0xC271C261, 0xC06665F6, 0x70A37FF7, 0x4656D067, 
    0xC271C261, 0xC06670A3, 0x7FF74656, 0xD067C371, 0x67E7E622, 
    0xC271C261, 0xC06670A3, 0x7FFE4656, 0xD067C271, 0xC0776757, 
    0xE6FDC271, 0xC261C066, 0x70A37FEF, 0x4656D067, 0xC271C261, 
    0xC06665F6, 0x70A37FFD, 0x4656D067, 0xC271C261, 0xC06670A3, 
    0x7FFD4656, 0xD067C271, 0xC261C066, 0x70A37FFE, 0x4656D067, 
    0xC271C077, 0x6757E6FD, 0xC271C261, 0xC06670A3, 0x7FEF4656, 
    0xD067C271, 0xC261C066, 0x70A37FFB, 0x4656D067, 0x30FF003C, 
    0x2A07E606, 0x1800D000, 0x00001800, 0xD0001BC1, 0x0818C901, 
    0x009021F1, 0x00044D50, 0x4335354F, 0x50313030

}; /* Total Data Size = 276 bytes */