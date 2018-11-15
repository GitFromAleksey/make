#if !defined(AURIX_GTM_TIM_H)
#   define AURIX_GTM_TIM_H

#   include "types.h"
#   include "IfxGtm_regdef.h"


namespace Aurix
{
    namespace Gtm
    {
        namespace Tim
        {
            enum class Mode: u8
            {
                pwmMeasurement = 0,
                pulseIntegration,
                inputEvent,
                inputPrescaler,
                reserved,
                gatedPeriodicSampling
            };
            enum class InpCtrl: u8 {useThis = 0, usePrev = 1};
            enum class GprxInp: u8
            {
                tbuTs0 = 0, tbuTs1, tbuTs2, cnt,
                __e_sh__ = 4,
                ecnt = 0x10, timInpVal
            };
            enum class CntsInp: u8 {cnt = 0, tbuTs0};
            enum class FiltClk: u8 {cmuClk0 = 0, cmuClk1, cmuClk6, cmuClk7};
            enum class FiltCountMode: u8 {upDown = 0, hold};
            enum class Clk: u8
            {
                cmuClk0 = 0, cmuClk1, cmuClk2, cmuClk3,
                cmuClk4, cmuClk5, cmuClk6, cmuClk7
            };
            enum class EdgeCntOverflowBits: u8 {_8 = 0, full};
            enum class TimeoutCtrl: u8
            {
                off = 0, bothEdges, risingEdge, fallingEdge
            };
            //=================================================================
        }
    }
}
//#############################################################################

#endif  // AURIX_GTM_TIM_H
