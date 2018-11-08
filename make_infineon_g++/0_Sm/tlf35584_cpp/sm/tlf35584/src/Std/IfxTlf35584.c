/**
 * \file IfxTlf35584.c
 * \brief TLF35584  basic functionality 
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2015-11-20 07:21:16
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
 * List of protected register and corresponding status register:
 * - SYSPCFG0 => RSYSPCFG0
 * - SYSPCFG1 => RSYSPCFG1
 * - WDCFG0   => RWDCFG0
 * - WDCFG1   => RWDCFG1
 * - FWDCFG   => RFWDCFG
 * - WWDCFG0  => RWWDCFG0
 * - WWDCFG1  => RWWDCFG1
 *
 * ==> requirement to Gcg :
 * - linked bitfield (read at x but write at y)
 *
 * \note Protected registers data is send inverted on read
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxTlf35584.h"

 
/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

boolean IfxTlf35584_isWakeTimerEnabled(IfxTlf35584_Driver* driver, boolean* value)
{
    boolean status;
    Ifx_TLF35584_DEVCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.DEVCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.WKTIMEN == 1 ? TRUE : FALSE;
    }
    return status;
}


boolean IfxTlf35584_enableWakeTimer(IfxTlf35584_Driver* driver)
{
    boolean status;
    Ifx_TLF35584_DEVCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.DEVCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WKTIMEN = 1;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.DEVCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

/*FIXME TO BE REMOVED: DIFF MARKER SYSPCFG1:ERREN */
boolean IfxTlf35584_enableErr(IfxTlf35584_Driver *driver)
{
    boolean               status;
    Ifx_TLF35584_SYSPCFG1 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.SYSPCFG1) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.ERREN = 1;
        status     &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.SYSPCFG1) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}


boolean IfxTlf35584_disableErr(IfxTlf35584_Driver *driver)
{
    boolean               status;
    Ifx_TLF35584_SYSPCFG1 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.SYSPCFG1) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.ERREN = 0;
        status     &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.SYSPCFG1) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}
/*FIXME TO BE REMOVED: DIFF MARKER SYSPCFG1:ERREN END*/
boolean IfxTlf35584_getWatchdogCycleTime(IfxTlf35584_Driver *driver, IfxTlf35584_WatchdogCycleTime *value)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.WDCYC;
    }
    return status;
}

boolean IfxTlf35584_setWatchdogCycleTime(IfxTlf35584_Driver *driver, IfxTlf35584_WatchdogCycleTime value)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WDCYC = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}



boolean IfxTlf35584_setWindowWatchdogTrigger(IfxTlf35584_Driver *driver, IfxTlf35584_WindowWatchdogTrigger value)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WWDTSEL = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}



boolean IfxTlf35584_enableFunctionalWatchdog(IfxTlf35584_Driver* driver)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.FWDEN = 1;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_disableFunctionalWatchdog(IfxTlf35584_Driver* driver)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.FWDEN = 0;
        status     &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_enableWindowWatchdog(IfxTlf35584_Driver* driver)
{   /* FIXME why two register WDCFG0 and RWDCFG0 ? => one for read, one for write.  Why redundant information? does values differs? */
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WWDEN = 1;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_disableWindowWatchdog(IfxTlf35584_Driver* driver)
{
    boolean status;
    Ifx_TLF35584_WDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WWDEN = 0;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_getWatchdogHeartbeatPeriod(IfxTlf35584_Driver *driver, uint8 *value)
{
    boolean status;
    Ifx_TLF35584_FWDCFG reg; /* FIXME should read be done from WWDCFG0 or from RWDCFG0? in which use case?  */
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.FWDCFG) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.WDHBTP;
    }
    return status;
}


boolean IfxTlf35584_setWatchdogHeartbeatPeriod(IfxTlf35584_Driver *driver, uint8 value)
{
    boolean status;
    Ifx_TLF35584_FWDCFG reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDCFG) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.WDHBTP = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDCFG) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}


boolean IfxTlf35584_getWindowWatchdogCloseWindow(IfxTlf35584_Driver *driver, uint8 *value)
{
    boolean              status;
    Ifx_TLF35584_WWDCFG0 reg; /* FIXME should read be done from WWDCFG0 or from RWDCFG0? in which use case?  */
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.WWDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.CW;
    }
    return status;
}

boolean IfxTlf35584_setWindowWatchdogCloseWindow(IfxTlf35584_Driver *driver, uint8 value)
{
    boolean status;
    Ifx_TLF35584_WWDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.CW = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_getWindowWatchdogOpenWindow(IfxTlf35584_Driver *driver, uint8 *value)
{
    boolean status;
    Ifx_TLF35584_WWDCFG1 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDCFG1) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.OW;
    }
    return status;
}

boolean IfxTlf35584_setWindowWatchdogOpenWindow(IfxTlf35584_Driver *driver, uint8 value)
{
    boolean status;
    Ifx_TLF35584_WWDCFG1 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDCFG1) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.OW = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDCFG1) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}



/*FIXME TO BE REMOVED: DIFF MARKER RSYSPCFG1:ERREN */
boolean IfxTlf35584_isErrEnabled(IfxTlf35584_Driver *driver, boolean *value)
{
    boolean status;
    Ifx_TLF35584_RSYSPCFG1 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.RSYSPCFG1) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
    	*value = reg.B.ERREN ? TRUE : FALSE;
    }
    return status;
}






boolean IfxTlf35584_isFunctionalWatchdogEnabled(IfxTlf35584_Driver *driver, boolean *value)
{
    boolean status;
    Ifx_TLF35584_RWDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.RWDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
    	*value = reg.B.FWDEN ? TRUE : FALSE;
    }
    return status;
}

boolean IfxTlf35584_isWindowWatchdogEnabled(IfxTlf35584_Driver *driver, boolean *value)
{
    boolean status;
    Ifx_TLF35584_RWDCFG0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.RWDCFG0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
    	*value = reg.B.WWDEN ? TRUE : FALSE;
    }
    return status;
}

/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL:STATEREQ */
boolean IfxTlf35584_getDeviceStateRequest(IfxTlf35584_Driver *driver, IfxTlf35584_State *value)
{
    boolean              status;
    Ifx_TLF35584_DEVCTRL reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.DEVCTRL) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.STATEREQ;
    }
    return status;
}
/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL:STATEREQ END*/

/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL WWDSCMD:TRIG */
boolean IfxTlf35584_setWindowWatchdogTriggerLevel(IfxTlf35584_Driver *driver, IfxTlf35584_WindowWatchdogTriggerLevel value)
{
    boolean status;
    Ifx_TLF35584_WWDSCMD reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDSCMD) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.TRIG = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.WWDSCMD) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_getWindowWatchdogLastTriggerLevel(IfxTlf35584_Driver *driver, IfxTlf35584_WindowWatchdogTriggerLevel *value)
{
    boolean status;
    Ifx_TLF35584_WWDSCMD reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.WWDSCMD) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.TRIG_STATUS;
		/* Write to one bitfield read from an other. feature currently not supported by GcG */
        	// ==> proposal is to have the TRIG rwh, write new value, but read last value?
    }
    return status;
}


boolean IfxTlf35584_setFunctionalWatchdogResponse(IfxTlf35584_Driver *driver, uint8 value)
{
    boolean status;
    Ifx_TLF35584_FWDRSP reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDRSP) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.FWDRSP = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDRSP) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}

boolean IfxTlf35584_setFunctionalWatchdogResponseSynchronization(IfxTlf35584_Driver *driver, uint8 value)
{
    boolean status;
    Ifx_TLF35584_FWDRSPSYNC reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDRSPSYNC) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        reg.B.FWDRSPS = value;
        status &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDRSPSYNC) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    }
    return status;
}



/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL DEVSTAT:STATE */
boolean IfxTlf35584_getDeviceState(IfxTlf35584_Driver *driver, IfxTlf35584_State *value)
{
    boolean status;
    Ifx_TLF35584_DEVSTAT reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.DEVSTAT) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.STATE;
    }
    return status;
}
/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL DEVSTAT:STATE END*/

/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL PROTSTAT:LOCK */
boolean IfxTlf35584_isProtectedRegisterLocked(IfxTlf35584_Driver* driver, boolean* value)
{
    boolean status;
    Ifx_TLF35584_PROTSTAT reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.PROTSTAT) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.LOCK == 1 ? TRUE : FALSE;
    }
    return status;
}
/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL PROTSTAT:LOCK END*/

/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL FWDSTAT0:FWDQUEST */
boolean IfxTlf35584_getFunctionalWatchdogQuestion(IfxTlf35584_Driver* driver, uint8* value)
{
    boolean status;
    Ifx_TLF35584_FWDSTAT0 reg;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address)(((uint8)&MODULE_TLF35584.FWDSTAT0) >> IFXTLF35584_ADDRESS_SHIFT), &reg.U);
    if (status)
    {
        *value = reg.B.FWDQUEST;
    }
    return status;
}
/*FIXME TO BE REMOVED: DIFF MARKER DEVCTRL FWDSTAT0:FWDQUEST END*/



