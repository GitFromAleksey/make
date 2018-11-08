#if !defined(AURIX_H_)
#   define AURIX_H_

#   include "IfxLldVersion.h"
#   include "IfxCpu_Intrinsics.h"

#   include "aurix_gpio.h"
#   include "aurix_dma.h"
#   include "aurix_gtm_tim.h"
#   include "aurix_gtm_dtm.h"
#   include "aurix_adc.h"
#   include "aurix_dma_util.h"
#   include "aurix_pmu.h"
#   include "aurix_reset.h"

//#############################################################################

namespace Aurix
{
    // If customers receive a productive device with a different value
    // they can discard it.
    S_C_U32 testPassMarker_Valid = 0x80658383;

    union Ucb4_IFX
    {
        u8 byte[1024];
        struct
        {
            u8 uid[16];
            u8 reserved_0[0x80 - 0x10];
            u8 dsAdcTrim[0x100 - 0x80];
            u8 calib[0x200 - 0x100];
            u8 test[0x380 - 0x200];
            u32 testPassMarker;
        };
        struct
        {
            u32 uid32[4];
        };
    };
    extern Ucb4_IFX ucb4_IFX;
    //========================================================================
}

//#############################################################################

#   define ILLD_PACK_VERSION(GEN, MAJ, MAJ_U, MINOR, ...) \
    ((MINOR) + 100UL * ((MAJ_U) + 100UL * ((MAJ) + 100UL * (GEN))))

#   if ILLD_PACK_VERSION(1, 0, 1, 2) >  ILLD_PACK_VERSION \
                                        (\
                                            IFX_LLD_VERSION_GENERATION, \
                                            IFX_LLD_VERSION_MAJOR, \
                                            IFX_LLD_VERSION_MAJOR_UPDATE, \
                                            IFX_LLD_VERSION_MINOR \
                                        )
INLINE u32 __crc32 (u32 crc, u32 data)
{
    u32 res;
#      if defined(__GNUC__)
    asm ("crc32 %0, %1, %2" : "=d" (res) : "d" (crc), "d" (data));
#      else
    res = crc;
#      endif
    return res;
}
#   endif

//#############################################################################

#endif  // AURIX_H_
