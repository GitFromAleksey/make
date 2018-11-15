/**
 * \file IfxTlf35584_Driver.c
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

#include "IfxTlf35584_Driver.h"
#include "IfxTlf35584_Hal.h"
#include "string.h"
#include "IfxTlf35584_If.h"
#include "IfxTlf35584.h"
#include "IfxTlf35584_bf.h"


#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
#pragma message  "WARNING: TLF35584 Cache feature is experimental"
#endif


/*--------------------------------------------*/
boolean IfxTlf35584_Driver_disableCache(IfxTlf35584_Driver *driver)
{
    boolean enabled;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
    /* Ensure all cached data are written to the device before disabling the cache */
    IfxTlf35584_Driver_writeSync(driver);

    enabled               = driver->cache.enabled;
    driver->cache.enabled = FALSE;
#else
    (void)driver;
    enabled = FALSE;
#endif
    return enabled;
}


void IfxTlf35584_Driver_enableCache(IfxTlf35584_Driver *driver)
{
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
    driver->cache.enabled = TRUE;
    Ifx_DeviceCache_invalidate(&driver->cache.engine);
#else
    (void)driver;
#endif
}


void IfxTlf35584_Driver_restoreCache(IfxTlf35584_Driver *driver, boolean enabled)
{
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
    if (enabled)
    {
        IfxTlf35584_Driver_enableCache(driver);
    }
#else
    (void)driver;
    (void)enabled;
#endif
}


boolean IfxTlf35584_Driver_init(IfxTlf35584_Driver *driver, IfxTlf35584_Config *config)
{
    boolean result = TRUE;

    driver->status = IfxTlf35584_status_notInitialized;
    IfxTlf35584_Hal_init(config);

    driver->channel        = config->channel;
    driver->pins.wdi       = config->wdi;
    driver->useWdiPin	   = config->windowWatchdog.useWdiPin;

#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
    Ifx_DeviceCache_Config cacheConfig;
    Ifx_DeviceCache_initConfig(&cacheConfig);

    driver->cache.enabled  = TRUE;
    cacheConfig.ItemCount         = sizeof(Ifx_TLF35584) / IFXTLF35584_ADDRESS_UNIT;
    cacheConfig.buffer            = &driver->cache.cache;
    cacheConfig.modificationMask  = &driver->cache.modificationMask[0];
    cacheConfig.validAddress      = (uint32 *)&Ifx_g_TLF35584_validAddress[0];
    cacheConfig.volatileRegisters = (uint32 *)&Ifx_g_TLF35584_volatileRegisters[0];
    cacheConfig.valid             = &driver->cache.cacheValid[0];
    cacheConfig.validVolatile     = &driver->cache.cacheValidVolatile[0];
    cacheConfig.flagArraySize     = sizeof(Ifx_g_TLF35584_validAddress) / 4;
    cacheConfig.read              = (Ifx_DeviceCache_ReadFromDevice)IfxTlf35584_If_readRegister;
    cacheConfig.write             = (Ifx_DeviceCache_WriteToDevice)IfxTlf35584_If_writeRegister;
    cacheConfig.deviceDriver      = driver;
    cacheConfig.registerWidth     = IFXTLF35584_ADDRESS_UNIT;
    cacheConfig.previousCache     = NULL_PTR;
    cacheConfig.tempCacheLine     = driver->cache.tempCacheLine;

    result                       &= Ifx_DeviceCache_init(&driver->cache.engine, &cacheConfig);

    if (result)
#endif
    { /* WARNING: part of the previous if (result) statement */
        driver->status = IfxTlf35584_status_ready;
    }

    // A delay of 3xTsam (3*213us=639) has must be respected between IfxTlf35584_Driver_serviceWindowWatchdogPin() and
    // IfxTlf35584_Driver_releaseWindowWatchdogPin() calls, either ways.

    driver->windowWatchdogMinDelay = TimeConst_1s * 639e-6;

    if (driver->useWdiPin)
    {
    	result &= IfxTlf35584_Driver_releaseWindowWatchdogTrigger(driver);
    	wait (driver->windowWatchdogMinDelay); /* FIXME Feedback: why such long delay ? */
    }
    /* Device configuration */

	result &= IfxTlf35584_Driver_unlock(driver);
    result &= IfxTlf35584_setWatchdogCycleTime(driver, config->watchdogCycleTime);


    if (config->windowWatchdog.enabled)
	{
    	result &= IfxTlf35584_Driver_enableWindowWatchdog(driver, config->windowWatchdog.openWindowTime, config->windowWatchdog.closeWindowTime, config->windowWatchdog.useWdiPin);
	}
	else
	{
		result &= IfxTlf35584_Driver_disableWindowWatchdog(driver);
	}

	if (config->functionalWatchdog.enabled)
	{
		result &= IfxTlf35584_Driver_enableFunctionalWatchdog(driver, config->functionalWatchdog.heartbeatTimerPeriod, config->functionalWatchdog.servicePeriod);
	}
	else
	{
		result &= IfxTlf35584_Driver_disableFunctionalWatchdog(driver);
	}

	if (config->errEnabled)
	{
		result &= IfxTlf35584_Driver_enableErr(driver); /* Note: the ERR is enabled by default */
	}
	else
	{
		result &= IfxTlf35584_Driver_disableErr(driver);
	}

	result &= IfxTlf35584_Driver_writeSync(driver);
	result &= IfxTlf35584_Driver_lock(driver);

    if (config->windowWatchdog.enabled)
	{
    	/* Service the window watchdog */
    	result &= IfxTlf35584_Driver_serviceWindowWatchdog(driver);
		driver->windowWatchdogServiceRequestRelease = TIME_INFINITE;
		driver->windowWatchdogServiceRequest = getDeadLine(driver->windowWatchdogClosedWindowTime + driver->windowWatchdogOpenedWindowTime /2 );
		/* Release of the WDi signal is required for a complete service */
		wait (driver->windowWatchdogMinDelay);
		IfxTlf35584_Driver_releaseWindowWatchdogTrigger(driver);
	}

	if (config->functionalWatchdog.enabled)
	{
    	result &= IfxTlf35584_Driver_serviceFunctionalWatchdog(driver);
		driver->functionalWatchdogServiceRequest = getDeadLine(driver->functionalWatchdogPeriod);
	}


    return result;
}


void IfxTlf35584_Driver_initConfig(IfxTlf35584_Config *config)
{
    config->channel   = NULL_PTR;
    config->wdi       = (IfxPort_Pin) {NULL_PTR, 0};
    config->watchdogCycleTime = IfxTlf35584_WatchdogCycleTime_100us;
    config->windowWatchdog.useWdiPin = FALSE;
    config->windowWatchdog.enabled = TRUE;
    config->windowWatchdog.openWindowTime = 5e-3;
    config->windowWatchdog.closeWindowTime = 5e-3;
    config->functionalWatchdog.enabled = FALSE;
    config->functionalWatchdog.heartbeatTimerPeriod = 0.0;
}


boolean IfxTlf35584_Driver_readRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 *data)
{
    boolean result = TRUE;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE

    if (driver->cache.enabled)
    {
        result = Ifx_DeviceCache_getValue8(&driver->cache.engine, address, data);
    }
    else
#endif
    {
        result = IfxTlf35584_If_readRegister(driver, address, data);
    }

    return result;
}


boolean IfxTlf35584_Driver_readSync(IfxTlf35584_Driver *driver)
{
    boolean result = TRUE;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE

    if (driver->cache.enabled)
    {
        result = Ifx_DeviceCache_synchronize8(&driver->cache.engine);
    }
    else
#else
    (void)driver;
#endif
    {
        /* Nothing to do */
    }

    return result;
}


boolean IfxTlf35584_Driver_writeRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 data)
{
    boolean result = TRUE;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE

    if (driver->cache.enabled)
    {
        Ifx_DeviceCache_setValue8(&driver->cache.engine, address, data);
    }
    else
#endif
    {
        result = IfxTlf35584_If_writeRegister(driver, 1, address, &data);
    }

    return result;
}


boolean IfxTlf35584_Driver_writeSync(IfxTlf35584_Driver *driver)
{
    boolean result = TRUE;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE

    if (driver->cache.enabled)
    {
        result = Ifx_DeviceCache_writeBack8(&driver->cache.engine);
    }
    else
#else
    (void)driver;
#endif
    {
        /* Nothing to do */
    }

    return result;
}


boolean IfxTlf35584_Driver_unlock(IfxTlf35584_Driver *driver)
{
    boolean status;
    boolean enabled;
    boolean locked;
    /* Disable the cache to ensure the sequence */
    enabled = IfxTlf35584_Driver_disableCache(driver);
    status  = IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0xAB);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0xEF);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0x56);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0x12);
    IfxTlf35584_Driver_restoreCache(driver, enabled);
    status &= IfxTlf35584_isProtectedRegisterLocked(driver, &locked);
    status &= locked == 0;
    return status;
}


boolean IfxTlf35584_Driver_lock(IfxTlf35584_Driver *driver)
{
    boolean status;
    boolean enabled;
    boolean locked;
    /* Disable the cache to ensure the sequence */
    enabled = IfxTlf35584_Driver_disableCache(driver);
    status  = IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0xDF);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0x34);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0xBE);
    status &= IfxTlf35584_Driver_writeRegister(driver, (uint8)&MODULE_TLF35584.PROTCFG, 0xCA);
    IfxTlf35584_Driver_restoreCache(driver, enabled);
    status &= IfxTlf35584_isProtectedRegisterLocked(driver, &locked);
    status &= locked == 1;
    return status;
}


boolean IfxTlf35584_waitForStateRequest(IfxTlf35584_Driver *driver, Ifx_TickTime timeout)
{
    boolean           result   = TRUE;
    IfxTlf35584_State state;
    Ifx_TickTime      deadline = getDeadLine(timeout);

    do
    {
        result &= IfxTlf35584_getDeviceStateRequest(driver, &state);
    } while (result && (state != IfxTlf35584_State_noRequest) && (now() < deadline));

    result &= state == IfxTlf35584_State_noRequest;

    return result;
}


boolean IfxTlf35584_Driver_goToNormal(IfxTlf35584_Driver *driver, boolean tracker1Enabled, boolean tracker2Enabled, boolean CommunicationLdoEnabled, boolean referenceVoltageEnabled, Ifx_TickTime timeout)
{
    boolean              result = TRUE;
    boolean              enabled;
    Ifx_TLF35584_DEVCTRL devctrl;

    result &= IfxTlf35584_waitForStateRequest(driver, timeout);

    if (result)
    {
        IfxTlf35584_State state;

        /* Disable the cache to ensure the sequence */
        enabled = IfxTlf35584_Driver_disableCache(driver);
        result &= IfxTlf35584_Driver_setStateRequest(driver, IfxTlf35584_State_normal, tracker1Enabled, tracker2Enabled, CommunicationLdoEnabled, referenceVoltageEnabled, &devctrl);
        result &= IfxTlf35584_Driver_setStateRequestN(driver, devctrl);
        IfxTlf35584_Driver_restoreCache(driver, enabled);

        result &= IfxTlf35584_waitForStateRequest(driver, timeout);

        result &= IfxTlf35584_getDeviceState(driver, &state);
        result &= state == IfxTlf35584_State_normal;
    }

    return result;
}

boolean IfxTlf35584_Driver_serviceWindowWatchdog(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
	if (driver->useWdiPin)
	{
		IfxTlf35584_Hal_setPinLow(&driver->pins.wdi);
	}
	else
	{
	    boolean              enabled;
	    IfxTlf35584_WindowWatchdogTriggerLevel lastTrigger;

	    enabled = IfxTlf35584_Driver_disableCache(driver);
	    result &= IfxTlf35584_getWindowWatchdogLastTriggerLevel(driver, &lastTrigger);
	    lastTrigger = lastTrigger == IfxTlf35584_WindowWatchdogTriggerLevel_low ? IfxTlf35584_WindowWatchdogTriggerLevel_high : IfxTlf35584_WindowWatchdogTriggerLevel_low;
		result &= IfxTlf35584_setWindowWatchdogTriggerLevel(driver, lastTrigger);
	    IfxTlf35584_Driver_restoreCache(driver, enabled);
	}
	return result;
}

boolean IfxTlf35584_Driver_releaseWindowWatchdogTrigger(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
	if (driver->useWdiPin)
	{
		IfxTlf35584_Hal_setPinHigh(&driver->pins.wdi);
	}
	else
	{
	}
	return result;
}

typedef struct
{
	uint8 question;
	uint8 response[4];
}IfxTlf35584_Driver_FunctionalWatchdogResponse;

IfxTlf35584_Driver_FunctionalWatchdogResponse IfxTlf35584_Driver_g_FunctionalWatchdogResponse[16] =
{
	{.question = 0x0, .response = {0xFF, 0x0F, 0xF0, 0x00 }},
	{.question = 0x1, .response = {0xB0, 0x40, 0xBF, 0x4F }},
	{.question = 0x2, .response = {0xE9, 0x19, 0xE6, 0x16 }},
	{.question = 0x3, .response = {0xA6, 0x56, 0xA9, 0x59 }},
	{.question = 0x4, .response = {0x75, 0x85, 0x7A, 0x8A }},
	{.question = 0x5, .response = {0x3A, 0xCA, 0x35, 0xC5 }},
	{.question = 0x6, .response = {0x63, 0x93, 0x6C, 0x9C }},
	{.question = 0x7, .response = {0x2C, 0xDC, 0x23, 0xD3 }},
	{.question = 0x8, .response = {0xD2, 0x22, 0xDD, 0x2D }},
	{.question = 0x9, .response = {0x9D, 0x6D, 0x92, 0x62 }},
	{.question = 0xA, .response = {0xC4, 0x34, 0xCB, 0x3B }},
	{.question = 0xB, .response = {0x8B, 0x7B, 0x84, 0x74 }},
	{.question = 0xC, .response = {0x58, 0xA8, 0x57, 0xA7 }},
	{.question = 0xD, .response = {0x17, 0xE7, 0x18, 0xE8 }},
	{.question = 0xE, .response = {0x4E, 0xBE, 0x41, 0xB1 }},
	{.question = 0xF, .response = {0x01, 0xF1, 0x0E, 0xFE }}
};

boolean IfxTlf35584_Driver_serviceFunctionalWatchdog(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
    boolean              enabled;
    uint8 question;

	result &= IfxTlf35584_getFunctionalWatchdogQuestion(driver, &question);

	/* The response is written without checking the response counter FWDSTAT0.FWDRSPC. It is assumed that the synchronization is correct
	 * Incorrect synchronization shows a bad system  behavior
	 */

    enabled = IfxTlf35584_Driver_disableCache(driver);
    result &= IfxTlf35584_setFunctionalWatchdogResponse(driver, IfxTlf35584_Driver_g_FunctionalWatchdogResponse[question].response[0]);
    result &= IfxTlf35584_setFunctionalWatchdogResponse(driver, IfxTlf35584_Driver_g_FunctionalWatchdogResponse[question].response[1]);
    result &= IfxTlf35584_setFunctionalWatchdogResponse(driver, IfxTlf35584_Driver_g_FunctionalWatchdogResponse[question].response[2]);
    result &= IfxTlf35584_setFunctionalWatchdogResponseSynchronization(driver, IfxTlf35584_Driver_g_FunctionalWatchdogResponse[question].response[3]);
    IfxTlf35584_Driver_restoreCache(driver, enabled);

	return result;
}

boolean IfxTlf35584_Driver_process(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
    if (driver->windowWatchdogClosedWindowTime != 0)
    {
    	if (isDeadLine(driver->windowWatchdogServiceRequestRelease))
    	{
    		result &= IfxTlf35584_Driver_releaseWindowWatchdogTrigger(driver);
    		driver->windowWatchdogServiceRequestRelease = TIME_INFINITE;
    	}
    	else if (isDeadLine(driver->windowWatchdogServiceRequest))
    	{
    		result &= IfxTlf35584_Driver_serviceWindowWatchdog(driver);
    		driver->windowWatchdogServiceRequestRelease = getDeadLine(driver->windowWatchdogMinDelay);
    		driver->windowWatchdogServiceRequest = getDeadLine(driver->windowWatchdogClosedWindowTime + driver->windowWatchdogOpenedWindowTime /2 );
    	}
    }

	if ((driver->functionalWatchdogPeriod != 0) &&   isDeadLine(driver->functionalWatchdogServiceRequest))
	{
		driver->functionalWatchdogServiceRequest = getDeadLine(driver->functionalWatchdogPeriod);
		result &= IfxTlf35584_Driver_serviceFunctionalWatchdog(driver);
	}

	return result;
}

boolean IfxTlf35584_Driver_enableWindowWatchdog(IfxTlf35584_Driver *driver, float32 openWindowTime, float32 closeWindowTime, boolean useWdiPin)
{
    boolean              result = TRUE;
    IfxTlf35584_WatchdogCycleTime cycleTime;
	uint8 valueCw;
	uint8 valueOw;
	float32 divider;

    driver->useWdiPin = useWdiPin;

    result &= IfxTlf35584_getWatchdogCycleTime(driver,&cycleTime);
    if (cycleTime == IfxTlf35584_WatchdogCycleTime_1ms)
    {
    	divider = 1e-3*50;
    }
    else//if (cycleTime == IfxTlf35584_WatchdogCycleTime_100us)
    {
    	divider = 100e-6*50;
    }

    /* FIXME check that the set timing match the required timing, Option is to return the configured timing */
	valueCw = closeWindowTime / divider - 1;
	result &= valueCw <= IFX_TLF35584_WWDCFG0_CW_MSK;

	valueOw = openWindowTime / divider - 1;
	result &= valueOw <= IFX_TLF35584_WWDCFG1_OW_MSK;

	result &= IfxTlf35584_setWindowWatchdogCloseWindow(driver, valueCw);
	result &= IfxTlf35584_setWindowWatchdogOpenWindow(driver, valueOw);

    result &= IfxTlf35584_setWindowWatchdogTrigger(driver,
			useWdiPin ? IfxTlf35584_WindowWatchdogTrigger_wdi : IfxTlf35584_WindowWatchdogTrigger_spi);

	result &= IfxTlf35584_enableWindowWatchdog(driver);/* Note: the Window watchdog is enabled by default */

	if (result)
	{
	    driver->windowWatchdogClosedWindowTime = ((valueCw+1)*divider) * TimeConst_1s; /* FIXME check that new settings won't break the current watchdog timing */
	    driver->windowWatchdogOpenedWindowTime = ((valueOw+1)*divider) * TimeConst_1s; /* FIXME check that new settings won't break the current watchdog timing */
	    result &= driver->windowWatchdogClosedWindowTime >= driver->windowWatchdogMinDelay;
	}

	if (!result)
	{
	    driver->windowWatchdogClosedWindowTime = 0;
	    driver->windowWatchdogOpenedWindowTime = 0;
	}

	return result;

}



boolean IfxTlf35584_Driver_disableWindowWatchdog(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;

    result &= IfxTlf35584_disableWindowWatchdog(driver);
	driver->windowWatchdogClosedWindowTime = 0;

    return result;
}


boolean IfxTlf35584_Driver_enableFunctionalWatchdog(IfxTlf35584_Driver *driver, float32 heartbeartTimerPeriod, float32 servicePeriod)
{
    boolean              result = TRUE;
    IfxTlf35584_WatchdogCycleTime cycleTime;
	uint8 value;
	float32 divider;


    result &= IfxTlf35584_getWatchdogCycleTime(driver,&cycleTime);
    if (cycleTime == IfxTlf35584_WatchdogCycleTime_1ms)
    {
    	divider = 1e-3*50;
    }
    else//if (cycleTime == IfxTlf35584_WatchdogCycleTime_100us)
    {
    	divider = 100e-6*50;
    }

    value = heartbeartTimerPeriod / divider -1;
	result &= value <= IFX_TLF35584_FWDCFG_WDHBTP_MSK;


	result &= IfxTlf35584_setWatchdogHeartbeatPeriod(driver, value);

	result &= IfxTlf35584_enableFunctionalWatchdog(driver);

	if (result)
	{
	    driver->functionalWatchdogPeriod = servicePeriod * TimeConst_1s;
	}
	if (!result)
	{
	    driver->functionalWatchdogPeriod = 0;

	}
	return result;

}

float32 IfxTlf35584_Driver_getFunctionalWatchdogPeriod(IfxTlf35584_Driver *driver)
{
	float32 period;

	if(driver->functionalWatchdogPeriod > 0.0)
	{
		period = (float32)driver->functionalWatchdogPeriod / TimeConst_1s;
	}
	else
	{
		period = 0;
	}
	return period;
}
float32 IfxTlf35584_Driver_getWindowWatchdogOpenedWindow(IfxTlf35584_Driver *driver)
{
	float32 value;

	if(driver->windowWatchdogClosedWindowTime > 0.0)
	{
		value = (float32)driver->windowWatchdogOpenedWindowTime / TimeConst_1s;
	}
	else
	{
		value = 0;
	}
	return value;
}
float32 IfxTlf35584_Driver_getWindowWatchdogClosedWindow(IfxTlf35584_Driver *driver)
{
	float32 value;

	if(driver->windowWatchdogClosedWindowTime > 0.0)
	{
		value = (float32)driver->windowWatchdogClosedWindowTime / TimeConst_1s;
	}
	else
	{
		value = 0;
	}
	return value;
}

boolean IfxTlf35584_Driver_disableFunctionalWatchdog(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
    result &= IfxTlf35584_disableFunctionalWatchdog(driver);
	driver->functionalWatchdogPeriod = 0;
	return result;

}

boolean IfxTlf35584_Driver_enableErr(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
	result &= IfxTlf35584_enableErr(driver); /* Note: the ERR is enabled by default */

	return result;

}
boolean IfxTlf35584_Driver_disableErr(IfxTlf35584_Driver *driver)
{
    boolean              result = TRUE;
	result &= IfxTlf35584_disableErr(driver);
	return result;

}

boolean IfxTlf35584_Driver_setStateRequest(IfxTlf35584_Driver *driver, IfxTlf35584_State state, boolean tracker1Enabled, boolean tracker2Enabled, boolean CommunicationLdoEnabled, boolean referenceVoltageEnabled, Ifx_TLF35584_DEVCTRL *reg)
{
    boolean status;
    status = IfxTlf35584_Driver_readRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.DEVCTRL) >> IFXTLF35584_ADDRESS_SHIFT), &reg->U);
    if (status)
    {
        reg->B.STATEREQ = state;
        reg->B.TRK1EN   = tracker1Enabled ? 1 : 0;
        reg->B.TRK2EN   = tracker2Enabled ? 1 : 0;
        reg->B.COMEN    = CommunicationLdoEnabled ? 1 : 0;
        reg->B.VREFEN   = referenceVoltageEnabled ? 1 : 0;
        status         &= IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.DEVCTRL) >> IFXTLF35584_ADDRESS_SHIFT), reg->U);
    }
    return status;
}


boolean IfxTlf35584_Driver_setStateRequestN(IfxTlf35584_Driver *driver, Ifx_TLF35584_DEVCTRL devctrl)
{
    boolean               status;
    Ifx_TLF35584_DEVCTRLN reg;
    reg.U  = ~devctrl.U;
    status = IfxTlf35584_Driver_writeRegister(driver, (IfxTlf35584_Address) (((uint8)&MODULE_TLF35584.DEVCTRLN) >> IFXTLF35584_ADDRESS_SHIFT), reg.U);
    return status;
}

