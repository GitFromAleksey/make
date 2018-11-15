#include "tlf35584.h"

//#############################################################################

Tlf35584 tlf35584;

//#############################################################################

IFX_INTERRUPT(tlf35584_SpiTxIsr, 0, ISR_PRIO_TX, ISR_PRIO_GROUP_TX)
{
    IfxQspi_SpiMaster_isrTransmit(tlf35584.spi());
}

//#############################################################################

IFX_INTERRUPT(tlf35584_SpiRxIsr, 0, ISR_PRIO_RX, ISR_PRIO_GROUP_RX)
{
    IfxQspi_SpiMaster_isrReceive(tlf35584.spi());
}

//#############################################################################

IFX_INTERRUPT(tlf35584_SpiErrIsr, 0, ISR_PRIO_ERR, ISR_PRIO_GROUP_ERR)
{
    IfxQspi_SpiMaster_isrError(tlf35584.spi());
}

//#############################################################################
