#if !defined(AURIX_PMU_H_)
#   define AURIX_PMU_H_

#   include "types.h"

//#############################################################################

namespace Aurix
{
    namespace Pmu
    {
        // Reset value: 0x00D4C0XX
        union Id
        {
            u32 v;
            struct
            {
                u32 modRev: 8;
                u32 modType: 8;
                u32 modNum: 16;
            };
        };
        //====================================================================
        struct Unit
        {
            const Id &id() {return _id;}
        private:
            u8 reserved_0[8];
            Id _id;
            u8 reserved_1[245];
        };
        extern Unit n0;
        //====================================================================
    }
}

//#############################################################################

#endif  // AURIX_PMU_H_
