/**
 * \file IfxTlf35584_Hal.h
 * \brief
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \defgroup IfxLld_Tlf35584_Hal Hardware abstraction layer
 * \ingroup IfxLld_Tlf35584
 */

#ifndef IFXTLF35584_HAL_H_
#define IFXTLF35584_HAL_H_

#include "IfxTlf35584_Driver.h"

#define TLF35584_DEBUG (0)
/* Pure virtual function. to be implemented outside of the driver */

/** Perform the SPI exchange operation.
 * \param src Pointer to the start of data buffer for data to transmit
 * \param dest Pointer to the start of data buffer for received data
 * \return TRUE in case of success else FALSE
 * \note the src and dest may be the same data location.
 * \note This function is not implemented in the driver (pure virtual). it must be implemented outside of this module
 */
boolean IfxTlf35584_Hal_exchangeSpi(void *spiChannel, const void *src, const void *dest, uint8 length);

boolean IfxTlf35584_Hal_init(IfxTlf35584_Config *config);

IFX_INLINE void IfxTlf35584_Hal_setPinHigh(IfxPort_Pin *pin)
{
    IfxPort_setPinState(pin->port, pin->pinIndex, IfxPort_State_high);
}


IFX_INLINE void IfxTlf35584_Hal_setPinLow(IfxPort_Pin *pin)
{
    IfxPort_setPinState(pin->port, pin->pinIndex, IfxPort_State_low);
}


IFX_INLINE void IfxTlf35584_Hal_setPinState(IfxPort_Pin *pin, IfxPort_State action)
{
    IfxPort_setPinState(pin->port, pin->pinIndex, action);
}


IFX_INLINE boolean IfxTlf35584_Hal_getPinState(IfxPort_Pin *pin)
{
    return IfxPort_getPinState(pin->port, pin->pinIndex);
}


#endif /* IFXTLF35584_HAL_H_ */
