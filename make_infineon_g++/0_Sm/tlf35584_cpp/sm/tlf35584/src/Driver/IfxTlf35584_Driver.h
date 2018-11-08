/**
 * \file IfxTlf35584_Driver.h
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
 * \defgroup IfxLld_Tlf35584_driver 1EDI2010AS Driver
 * \ingroup IfxLld_Tlf35584
 */

#ifndef TLF35584_DRIVER_H
#define TLF35584_DRIVER_H

#include "Ifx_Cfg.h"
#ifndef IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
#define IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE (FALSE)
#endif

#include "SysSe/Bsp/Bsp.h"
#include "If/SpiIf.h"
#include "IfxTlf35584_reg.h"
#include "IfxTlf35584_enum.h"



#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
#include "Ifx_DeviceCache.h"
#endif

typedef enum
{
    IfxTlf35584_status_notInitialized,  /**< \brief device driver is not initialized */
    IfxTlf35584_status_ready            /**< \brief device driver is ready */
}IfxTlf35584_status;
typedef struct
{
    SpiIf_Ch *channel;
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
    struct
    {
        /* Device specific part */
        Ifx_TLF35584    cache;                                                       /**< \brief Cache of the device registers */
        uint32          modificationMask[sizeof(Ifx_g_TLF35584_validAddress) / 4];   /**< \brief register modification mask. If bit with offset x is 1, corresponding register address x has been modified and need to be written to the device */
        uint32          cacheValid[sizeof(Ifx_g_TLF35584_validAddress) / 4];         /**< \brief register cache valid. If bit with offset x is 1, corresponding register cache x has is valid */
        uint32          cacheValidVolatile[sizeof(Ifx_g_TLF35584_validAddress) / 4]; /**< \brief register cache valid (volatile registers). If bit with offset x is 1, corresponding register cache x has is valid */
        Ifx_DeviceCache engine;
        boolean         enabled;                                                     /* Cache status: enabled (TRUE) or disabled (FALSE). Enabled by default */
        uint8           tempCacheLine[1];                                            /** Buffer for the temporary cache line */
    }cache;
#endif

    struct
    {
        IfxPort_Pin wdi;        /**< \brief WDI pin */
    }                  pins;
    IfxTlf35584_status status;
    boolean useWdiPin;		/**< \brief If TRUE, use the WDI pin to service the watchdog, else use the SPI */
    Ifx_TickTime windowWatchdogServiceRequest;		/**< \brief Window watchdog service request timeout */
    Ifx_TickTime windowWatchdogServiceRequestRelease;/**< \brief Window watchdog service request timeout to release the WDI signal */
    Ifx_TickTime windowWatchdogClosedWindowTime;	/**< \brief Window watchdog closed window time  */
    Ifx_TickTime windowWatchdogOpenedWindowTime;	/**< \brief Window watchdog opened window time  */
    Ifx_TickTime windowWatchdogMinDelay;	/**< \brief Minimal delay between WDI signal change  */

    Ifx_TickTime functionalWatchdogServiceRequest;	/**< \brief Window watchdog service request timeout */
    Ifx_TickTime functionalWatchdogPeriod;	/**< \brief Functional watchdog period */

}IfxTlf35584_Driver;

typedef struct
{
    SpiIf_Ch   *channel;
    IfxPort_Pin wdi;        /**< \brief WDI pin */
    IfxTlf35584_WatchdogCycleTime watchdogCycleTime; /**< \brief  Watchdog cycle time */

    /** \brief Window watchdog */
    struct
    {
        boolean enabled; /**< \brief If TRUE, the watchdog is enabled */
    	float32 openWindowTime;  /**< \brief Watchdog open window time in s */
    	float32 closeWindowTime;  /**< \brief Watchdog close window time in s */
        boolean useWdiPin;		/**< \brief If TRUE, use the WDI pin to service the watchdog, else use the SPI */
    }windowWatchdog;
    struct
    {
        boolean enabled; /**< \brief If TRUE, the watchdog is enabled */
    	float32 heartbeatTimerPeriod;  /**< \brief Watchdog heartbeat period in s */
    	float32 servicePeriod;  /**< \brief Watchdog service period in s */
    }functionalWatchdog;
    boolean errEnabled;  /**< \brief If TRUE, the ERR monitoring is enabled */
}IfxTlf35584_Config;


/** \addtogroup IfxLld_Tlf35584_driver
 * \{ */

/** Disable the cache
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_disableCache(IfxTlf35584_Driver *driver);
/** Enable the cache
 * Enabling the cache will automatically invalidate the cache
 */
IFX_EXTERN void IfxTlf35584_Driver_enableCache(IfxTlf35584_Driver *driver);
IFX_EXTERN void IfxTlf35584_Driver_restoreCache(IfxTlf35584_Driver *driver, boolean enabled);

IFX_EXTERN boolean IfxTlf35584_Driver_init(IfxTlf35584_Driver *driver, IfxTlf35584_Config *config);
IFX_EXTERN void    IfxTlf35584_Driver_initConfig(IfxTlf35584_Config *config);
/** Invalidate the cache
 *
 */
IFX_INLINE void IfxTlf35584_Driver_invalidateCache(IfxTlf35584_Driver *driver);

/** read a register value either from cache or the device if the cache is not valid
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_readRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 *data);

/** Synchonize the cache with the device (read)
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_readSync(IfxTlf35584_Driver *driver);

/** Write a register in the cache
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_writeRegister(IfxTlf35584_Driver *driver, IfxTlf35584_Address address, uint8 data);

/** Synchonize the cache with the device (write)
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_writeSync(IfxTlf35584_Driver *driver);

IFX_INLINE void IfxTlf35584_Driver_invalidateCache(IfxTlf35584_Driver *driver)
{
#if IFX_CFG_TLF35584_DRIVER_CACHE_ENABLE
Ifx_DeviceCache_invalidate(&driver->cache.engine);
#else
    (void)driver;
#endif
}


IFX_EXTERN boolean IfxTlf35584_Driver_unlock(IfxTlf35584_Driver *driver);
IFX_EXTERN boolean IfxTlf35584_Driver_lock(IfxTlf35584_Driver *driver);
IFX_EXTERN boolean IfxTlf35584_Driver_goToNormal(IfxTlf35584_Driver *driver, boolean tracker1Enabled, boolean tracker2Enabled, boolean CommunicationLdoEnabled, boolean referenceVoltageEnabled, Ifx_TickTime timeout);

/** Service the window watchdog
 * This function has to be called within the open window
 *
 * IfxTlf35584_Driver_releaseWindowWatchdogPin() must be called every time after the IfxTlf35584_Driver_serviceWindowWatchdogPin().
 * A delay of 3xTsam (3*213us=639) has must be respected between IfxTlf35584_Driver_serviceWindowWatchdogPin() and
 * IfxTlf35584_Driver_releaseWindowWatchdogPin() calls, either ways.
 */
IFX_EXTERN boolean IfxTlf35584_Driver_serviceWindowWatchdog(IfxTlf35584_Driver *driver);

/** Release the window watchdog trigger
 *
 * This function has to be called every time after the IfxTlf35584_Driver_serviceWindowWatchdogPin().
 * A delay of 3xTsam (3*213us=639us) has must be respected between IfxTlf35584_Driver_serviceWindowWatchdogPin() and
 * IfxTlf35584_Driver_releaseWindowWatchdogPin() calls, either ways.
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_releaseWindowWatchdogTrigger(IfxTlf35584_Driver *driver);

/** Service the functional watchdog
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_serviceFunctionalWatchdog(IfxTlf35584_Driver *driver);

/** Enable the window watchdog
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_enableWindowWatchdog(IfxTlf35584_Driver *driver, float32 openWindowTime, float32 closeWindowTime, boolean useWdiPin);
/** Disable the window watchdog
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_disableWindowWatchdog(IfxTlf35584_Driver *driver);
/** Enable the functional watchdog and set the heartbeat period
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_enableFunctionalWatchdog(IfxTlf35584_Driver *driver, float32 heartbeartTimerPeriod, float32 servicePeriod);

/** Return the functinal watchdog service period
 *
 */
IFX_EXTERN float32 IfxTlf35584_Driver_getFunctionalWatchdogPeriod(IfxTlf35584_Driver *driver);
/** Return the window watchdog open window time
 *
 * Note the service is done in the middle of teh opened window time
 *
 */
IFX_EXTERN float32 IfxTlf35584_Driver_getWindowWatchdogOpenedWindow(IfxTlf35584_Driver *driver);
/** Return the window watchdog closed window time
 *
 * Note the service is done in the middle of teh opened window time
 *
 */
IFX_EXTERN float32 IfxTlf35584_Driver_getWindowWatchdogClosedWindow(IfxTlf35584_Driver *driver);

/** Disable the functinal watchdog
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_disableFunctionalWatchdog(IfxTlf35584_Driver *driver);
/** Enable the ERR monitoring
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_enableErr(IfxTlf35584_Driver *driver);
/** Disable the ERR monitoring
 *
 */
IFX_EXTERN boolean IfxTlf35584_Driver_disableErr(IfxTlf35584_Driver *driver);


/** Handles the windows and functional watchdog
 * This function must be called periodically to service the watchdogs
 *
 * FIXME document period of call
 */
IFX_EXTERN boolean IfxTlf35584_Driver_process(IfxTlf35584_Driver *driver);

IFX_EXTERN boolean IfxTlf35584_Driver_setStateRequest(IfxTlf35584_Driver* driver, IfxTlf35584_State state, boolean tracker1Enabled, boolean tracker2Enabled, boolean CommunicationLdoEnabled, boolean referenceVoltageEnabled, Ifx_TLF35584_DEVCTRL *reg);
IFX_EXTERN boolean IfxTlf35584_Driver_setStateRequestN(IfxTlf35584_Driver* driver, Ifx_TLF35584_DEVCTRL devctrl);
/** \} */

#endif /* TLF35584_DRIVER_H */
