#if !defined(AURIX_DFLASH_TOOLS_H)
#   define AURIX_DFLASH_TOOLS_H

//#############################################################################

#   include "IfxFlash.h"

//#############################################################################

namespace Aurix
{
    // [UM]-11.5.6.2:
    // DFlash ECC
    // The DFlash ECC value is calculated over 64 data bits.
    // Features:
    //  * Correction of 1-bit, 2-bit and 3-bit errors.
    //  * Detection of 4-bit errors.
    //  * All-0 (data and ECC) is a correct code vector - erased state.
    //  * All-1 (data and ECC) is a valid code vector - used for marking "bad"
    //    in EEPROM emulations.
    //  * Address errors are not detected.
    // Error reporting and ECC disabling:
    //  * Single-bit, double-bit, triple-bit errors:
    //   – Are noted in FSR.DFSBER, FSR.DFDBER, FSR.DFTBER respectively.
    //   – Data and ECC value are corrected if this is not disabled with
    //     ECCRD.ECCORDIS1.
    //  * Quad-bit error:
    //   – Is noted in FSR.DFMBER.
    //   – Causes a bus error if not disabled by MARD.TRAPDIS.
    class DFlashTools
    {
    public:
        u32 size() const {return IFXFLASH_DFLASH_SIZE;}
        u32 startAddr() const {return IFXFLASH_DFLASH_START;}
        u32 endAddr() const {return startAddr() + size();}
        u32 bytesInPage() const {return IFXFLASH_DFLASH_PAGE_LENGTH;}
        u32 bytesInBurst() const {return IFXFLASH_DFLASH_BURST_LENGTH;}
        u32 pagesInBurst() const {return bytesInBurst() / bytesInPage();}
        u32 sectorsNum() const {return IFXFLASH_DFLASH_NUM_LOG_SECTORS;}
        u32 sectorSize() const {return size() / sectorsNum();}
        //------------------------------------------------>
        u32 erasedValue() const {return 0UL;}
        //------------------------------------------------>
        void disableUncorrectableBitErrorTrap()
        {
            u16 password = IfxScuWdt_getCpuWatchdogPassword();
            u32 coreId = (u32)IfxCpu_getCoreIndex();
            Ifx_SCU_WDTCPU *wdt = &MODULE_SCU.WDTCPU[coreId];
            IfxScuWdt_clearCpuEndinitInline(wdt, password);
            MODULE_FLASH0.MARD.B.TRAPDIS = true;
            IfxScuWdt_setCpuEndinitInline(wdt, password);
        }
        //------------------------------------------------>
        bool eraseLogicalSectorRangeByIndex(u32 i_sector0, u8 num)
        {
            bool res = false;
            s32 dn = sectorsNum() - i_sector0;
            if (dn > 0)
            {
                if (num <= dn)
                {
                    u16 pw = IfxScuWdt_getSafetyWatchdogPassword();
                    IfxScuWdt_clearSafetyEndinit(pw);
                    IfxFlash_eraseMultipleSectors
                    (
                        startAddr() + sectorSize() * i_sector0,
                        num
                    );
                    IfxScuWdt_setSafetyEndinit(pw);
                    wait();

                    res = true;
                }
            }
            return res;
        }
        //------------------------------------------------>
        bool eraseAll()
        {
            return eraseLogicalSectorRangeByIndex(0, sectorsNum());
        }
        //------------------------------------------------>
        bool eraseLogicalSectorByIndex(u32 i_sector)
        {
            return eraseLogicalSectorRangeByIndex(i_sector, 1);
        }
        //------------------------------------------------>
        bool eraseLogicalSectorByAddr(u32 addr)
        {
            bool res = false;
            if (addr >= startAddr())
            {
                u32 i = (addr - startAddr()) / sectorSize();
                res = eraseLogicalSectorByIndex(i);
            }
            return res;
        }
        //------------------------------------------------>
        bool program(u32 addr, u8 *data, u32 size)
        {
            bool res = true;
            u32 head = addr;
            u32 end = head + size;
            while (head < end)
            {
                if (!programPage(head, data))
                {
                    res = false;
                }
                head += bytesInPage();
                data += bytesInPage();
            }
            return res;
        }
        //------------------------------------------------>
        bool programFast(u32 addr, u8 *data, u32 size)
        {
            bool res = true;
            u32 head = addr;
            u32 end = head + size;
            while (head < end)
            {
                bool burst;
                u32 bytes;
                if (head % bytesInBurst() || end - head < bytesInBurst())
                {
                    burst = false;
                    bytes = bytesInPage();
                }
                else
                {
                    burst = true;
                    bytes = bytesInBurst();
                }
                if (!programPage(head, data, burst))
                {
                    res = false;
                }
                head += bytes;
                data += bytes;
            }
            return res;
        }
        //------------------------------------------------>
    DEBUG_PUBLIC(private):
        // pageAddr - must be aligned to page or burst size
        bool programPage(u32 pageAddr, u8 *data, bool burst = false)
        {
            u32 err;
            u32 bufSize = burst ? bytesInBurst() : bytesInPage();
            if (pageAddr % bufSize)
            {
                err = 1;
            }
            else
            {
                err = IfxFlash_enterPageMode(pageAddr);
                err += wait();

                if (!err)
                {
                    u32 *dp = (u32 *)data;
                    u32 n = burst ? pagesInBurst() : 1;
                    for (u32 i = 0; i < n; i++)
                    {
                        u32 w0 = *dp++;
                        u32 w1 = *dp++;
                        IfxFlash_loadPage2X32(pageAddr, w0, w1);
                    }

                    u16 pw = IfxScuWdt_getSafetyWatchdogPassword();
                    IfxScuWdt_clearSafetyEndinit(pw);
                    writePage(pageAddr, burst);
                    IfxScuWdt_setSafetyEndinit(pw);
                    err += wait();
                }
            }
            return !err;
        }
        //------------------------------------------------>
        void writePage(u32 pageAddr, bool burst = false)
        {
            u8 *base = (u8 *)(IFXFLASH_CMD_BASE_ADDRESS);
            *(vu32 *)(base + 0xAA50) = pageAddr;
            *(vu32 *)(base + 0xAA58) = 0x00;
            *(vu32 *)(base + 0xAAA8) = 0xA0;
            *(vu32 *)(base + 0xAAA8) = burst ? 0x7A : 0xAA;
            __dsync();
        }
        //------------------------------------------------>
        u8 wait() {return IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);}
    };
}

//#############################################################################

#endif  // AURIX_DFLASH_TOOLS_H
