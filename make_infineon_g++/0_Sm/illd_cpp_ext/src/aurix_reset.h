#if !defined(AURIX_RESET_H_)
#   define AURIX_RESET_H_

#   include "types.h"
#   include "IfxCpu.h"
#   include "IfxScuWdt.h"

namespace Aurix
{
    namespace ResetCtrl
    {
        INLINE void doReset(u16 info = 0, bool system = false)
        {
            u16 pw = IfxScuWdt_getSafetyWatchdogPassword();
            IfxScuWdt_clearSafetyEndinit(pw);

            if (system)
            {
                MODULE_SCU.RSTCON.B.SW = 1;
            }
            MODULE_SCU.RSTCON2.B.USRINFO = info;
            MODULE_SCU.SWRSTCON.B.SWRSTREQ = 1;
            // Wait till reset
            while (1) {}
            IfxScuWdt_setSafetyEndinit(pw);
        }
        INLINE bool isSwReset()
        {
            return MODULE_SCU.RSTSTAT.B.SW != 0;
        }
        INLINE u16 getInfo()
        {
            return MODULE_SCU.RSTCON2.B.USRINFO;
        }
    }
}

// USRINFO


#endif  // AURIX_RESET_H_
