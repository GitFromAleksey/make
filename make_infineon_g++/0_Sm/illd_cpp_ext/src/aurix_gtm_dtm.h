#if !defined(AURIX_GTM_DTM_H_)
#   define AURIX_GTM_DTM_H_

#   include <types.h>

//#############################################################################

namespace Aurix
{
    namespace Gtm
    {
        namespace Dtm
        {
            struct Ctrl
            {
                enum class Clk: u8 {sysClk = 0, cmuClk0, fxClk0, fxClk1};
                enum class UpdateMode: u8
                {
                    async = 0, in0_edge = 4, in1_edge, in2_edge, in3_edge
                };
            };
            //================================================================
            struct ChCtrl2
            {
                enum class Polarity: u8 {pos = 0, neg, inverted = neg};
                enum class Output: u8 {func = 0, forced};
            };
        }
    }
}
//#############################################################################

#endif  // AURIX_GTM_DTM_H_
