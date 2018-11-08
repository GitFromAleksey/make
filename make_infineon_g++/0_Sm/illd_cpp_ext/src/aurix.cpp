#include "aurix.h"
#include "IfxGtm_regdef.h"

//#############################################################################

namespace Aurix
{
#   pragma section ".aurix.ucb4"
    Ucb4_IFX ucb4_IFX;
#   pragma section
#   pragma section ".aurix.gtm"
    Ifx_GTM gtm;
#   pragma section
#   pragma section ".aurix.pmu0"
    Pmu::Unit Pmu::n0;
#   pragma section
}

//#############################################################################
