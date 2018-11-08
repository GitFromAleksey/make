/**
 * \file IfxTlf35584_If.c
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
#include "IfxTlf35584_If.h"

#include "IfxTlf35584_Hal.h"
#include "Ifx_Console.h"

/** Message command keys*/
typedef enum
{
    IfxTlf35584_If_Cmd_read  = 0x0,
    IfxTlf35584_If_Cmd_write = 0x1,
}IfxTlf35584_If_Cmd;

/**
 * Read frame definition (MRST)
 */
typedef union
{
    struct
    {
        uint16 p : 1;
        uint16 data : 8;
        uint16 status : 6;
        uint16 cmd : 1;
    }      fields;
    uint16 data;
}IfxTlf35584_If_MrstRead;

/**
 * Write frame definition (MRST)
 */
typedef union
{
    struct
    {
        uint16 p : 1;
        uint16 data : 8;
        uint16 status : 6;
        uint16 cmd : 1;
    }      fields;
    uint16 data;
}IfxTlf35584_If_MrstWrite;

/**
 * Cmd frame definition (MTSR)
 */
typedef union
{
    struct
    {
        uint16 p : 1;
        uint16 data : 8;
        uint16 address : 6;
        uint16 cmd : 1;
    }      fields;
    uint16 data;
}IfxTlf35584_If_Mtsr;

uint8 IfxTlf35584_If_calcualteParity(uint16 data)
{
    uint8 p = 0;
    uint8 i = 15;

    while (i)
    {
        data = data >> 1;
        p    = p ^ (data & 1);
        i--;
    }

    return p;
}


/** Checks the parity
 */
boolean IfxTlf35584_If_checkReadResponse(IfxTlf35584_If_MrstRead *frame)
{
    boolean status = TRUE;

    if ((frame->fields.p == IfxTlf35584_If_calcualteParity(frame->data)) && (frame->fields.cmd == 1))
    {
        status = TRUE;
    }
    else
    {
        status = FALSE;
    }

    return status;
}


/** Checks the parity
 */
boolean IfxTlf35584_If_checkWriteResponse(IfxTlf35584_If_MrstWrite *frame)
{
    boolean status = TRUE;

    if ((frame->fields.p == IfxTlf35584_If_calcualteParity(frame->data)) && (frame->fields.cmd == 1))
    {
        status = TRUE;
    }
    else
    {
        status = FALSE;
    }

    return status;
}


/** Initialize the MTSR frame (Message: READ)
 * \param frame frame to be initialized
 * \param address Regsiter address
 */
void IfxTlf35584_If_initMtsrRead(IfxTlf35584_If_Mtsr *frame, uint8 address)
{
    frame->fields.cmd     = IfxTlf35584_If_Cmd_read;
    frame->fields.address = address;
    frame->fields.data    = 0;
    frame->fields.p       = IfxTlf35584_If_calcualteParity(frame->data);
}


/** Initialize the MTSR frame (Message: WRITE)
 * \param frame frame to be initialized
 * \param address Regsiter address
 */
void IfxTlf35584_If_initMtsrWrite(IfxTlf35584_If_Mtsr *frame, uint8 address, uint8 data)
{
    frame->fields.cmd     = IfxTlf35584_If_Cmd_write;
    frame->fields.address = address;
    frame->fields.data    = data;
    frame->fields.p       = IfxTlf35584_If_calcualteParity(frame->data);
}


boolean IfxTlf35584_If_readRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 *data)
{
    boolean                  status = TRUE;
    IfxTlf35584_If_Mtsr     request;
    IfxTlf35584_If_MrstRead frame;

    IfxTlf35584_If_initMtsrRead(&request, address);

#if TLF35584_DEBUG
	Ifx_Console_print(ENDL);
#endif

    status = IfxTlf35584_Hal_exchangeSpi(driver->channel, &request, &frame, 1);

    if (status)
    {
        status = IfxTlf35584_If_checkReadResponse(&frame);

        if (status)
        {
        	if ((address >= (IfxTlf35584_Address) & MODULE_TLF35584.SYSPCFG0) && (address <= (IfxTlf35584_Address) & MODULE_TLF35584.WWDCFG1))
        	{ /* Protected registers have inverted data */
                *data = ~frame.fields.data;
        	}
        	else
        	{
                *data = frame.fields.data;
        	}
#if TLF35584_DEBUG
    {
        uint8 d = *data;
        Ifx_Console_print(" TLF35584 read 0x%02X @ 0x%02X"ENDL, d, address);
    }
#endif
        }
    }

    return status;
}


boolean IfxTlf35584_If_writeRegister(IfxTlf35584_Driver *driver, uint32 mask, IfxTlf35584_Address address, uint8 *data)
{
    boolean                   status = TRUE;
    IfxTlf35584_If_Mtsr      request;
    IfxTlf35584_If_MrstWrite frame;

    (void)mask;
#if TLF35584_DEBUG
    {
        uint8 d = *data;
        Ifx_Console_print(ENDL "TLF35584 write 0x%02X @ 0x%02X", d, address);
    }
#endif

    IfxTlf35584_If_initMtsrWrite(&request, address, *data);

    status = IfxTlf35584_Hal_exchangeSpi(driver->channel, &request, &frame, 1);
#if TLF35584_DEBUG
	Ifx_Console_print(ENDL);
#endif

    if (status)
    {
        status = IfxTlf35584_If_checkWriteResponse(&frame);
        /* FIXME is it enough / required to check the parity bit only ? */
    }

    return status;
}
