/**
 * \file IfxTlf35584_If.h
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
 * \defgroup IfxLld_Tlf35584_Spi SPI interface
 * \ingroup IfxLld_Tlf35584
 */
#ifndef IFXTLF35584_IF_H_
#define IFXTLF35584_IF_H_

#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxTlf35584_Driver.h"

/** Read the register value out of the device
 *
 * Two frames are required to get the value
 * \return TRUE in case of successful communication
 */
boolean IfxTlf35584_If_readRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 *data);
/** Write the register value to the device and check that communication was successful
 *
 * Two frames are required to write the value
 * \return TRUE in case of successful communication
 */
boolean IfxTlf35584_If_writeRegister(IfxTlf35584_Driver *driver, uint32 mask, IfxTlf35584_Address address, uint8 *data);

#endif /* IFXTLF35584_IF_H_ */
