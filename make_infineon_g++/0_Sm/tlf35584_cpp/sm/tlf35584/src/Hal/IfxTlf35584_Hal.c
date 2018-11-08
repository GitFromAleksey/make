/**
 * \file IfxTlf35584_Hal.c
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
 */
#include "IfxTlf35584_Hal.h"
#include "If/SpiIf.h"
#include "Ifx_Console.h"

boolean IfxTlf35584_Hal_exchangeSpi(void *spiChannel, const void *src, const void *dest, uint8 length)
{
#if TLF35584_DEBUG
    {
        uint16 d = *(uint16 *)src;
        Ifx_Console_print(" (0x%04X)", d);
    }
#endif

    SpiIf_Ch *spi = (SpiIf_Ch *)spiChannel;
    SpiIf_exchange(spi, src, dest, length);
    SpiIf_wait(spi); /*FIXME endless timout might be safety critical */
#if TLF35584_DEBUG
    {
        uint16 d = *(uint16 *)dest;
        Ifx_Console_print("->(0x%04X)", d);
    }
#endif
    return TRUE;     /* FIXME handle intermediate status? */
}


void IfxTlf35584_Hal_initPinOut(IfxPort_Pin *pin, IfxPort_Mode mode, IfxPort_PadDriver driver, IfxPort_State state)
{
    Pin_setMode(pin, mode);
    Pin_setDriver(pin, driver);
    Pin_setState(pin, state);
}


void IfxTlf35584_Hal_initPinInp(IfxPort_Pin *pin, IfxPort_Mode mode)
{
    Pin_setMode(pin, mode);
}


boolean IfxTlf35584_Hal_init(IfxTlf35584_Config *config)
{
    boolean result = TRUE;

    IfxTlf35584_Hal_initPinOut(&config->wdi, IfxPort_Mode_outputPushPullGeneral, IfxPort_PadDriver_cmosAutomotiveSpeed1, IfxPort_State_low);

    return result;
}
