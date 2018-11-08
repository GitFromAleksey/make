/**
 * \file IfxTlf35584_regdef.c
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Date: 2015-11-20 07:21:23 GMT
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
 */
/******************************************************************************/
#include "IfxTlf35584_regdef.h"
/******************************************************************************/
uint32 Ifx_g_TLF35584_validAddress[2] = {
0xffffffff,
0x800fffff,
};
/* Register with bitfield marked are r, rw1c, rwhc, rwhu have a 1 in the Ifx_g_TLF35584_volatileRegisters flag array */
uint32 Ifx_g_TLF35584_volatileRegisters[2] = {
0xFCE3F804,
0x8009DFFF
};

/* Registers that when read trigger an action on the device */
uint32 Ifx_g_TLF35584_actionReadRegisters[2] = {
0x00000000,
0x00000000
};

/* Registers that when written trigger an action on the device (register value is changed: clear set, ... the device starts an operation on write, ...)
 * rw1c, rwhc, rwhu
 *
 * Note: Generally all configuration registers have an action on the device, but only when the feature is enable/runing. those registers are not included in this
 * flag array and if required cache must be commit explicitly
 * */
uint32 Ifx_g_TLF35584_actionWriteRegisters[2] = {
0xFFE00008,
0x0009D03F
};
