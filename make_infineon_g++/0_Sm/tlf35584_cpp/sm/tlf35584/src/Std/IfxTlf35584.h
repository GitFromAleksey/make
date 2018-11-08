/**
 * \file IfxTlf35584.h
 * \brief TLF35584  basic functionality 
 * \ingroup IfxLld_Tlf35584 
 *
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2015-11-20 07:21:15
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
 * \defgroup IfxLld_Tlf35584_Std_Std Std  
 * \ingroup IfxLld_Tlf35584_Std
 */

#ifndef IFXTLF35584_H
#define IFXTLF35584_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxTlf35584_cfg.h"
#include "IfxTlf35584_Driver.h"

/** \addtogroup IfxLld_Tlf35584_Std_Std
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
IFX_EXTERN boolean IfxTlf35584_isWakeTimerEnabled(IfxTlf35584_Driver* driver, boolean* value);
IFX_EXTERN boolean IfxTlf35584_enableWakeTimer(IfxTlf35584_Driver* driver);

IFX_EXTERN boolean IfxTlf35584_setWindowWatchdogTrigger(IfxTlf35584_Driver* driver, IfxTlf35584_WindowWatchdogTrigger value);
IFX_EXTERN boolean IfxTlf35584_setWindowWatchdogTriggerLevel(IfxTlf35584_Driver* driver, IfxTlf35584_WindowWatchdogTriggerLevel value);
IFX_EXTERN boolean IfxTlf35584_getWindowWatchdogLastTriggerLevel(IfxTlf35584_Driver* driver, IfxTlf35584_WindowWatchdogTriggerLevel *value);
IFX_EXTERN boolean IfxTlf35584_setFunctionalWatchdogResponse(IfxTlf35584_Driver* driver, uint8 value);
IFX_EXTERN boolean IfxTlf35584_setFunctionalWatchdogResponseSynchronization(IfxTlf35584_Driver* driver, uint8 value);

IFX_EXTERN boolean IfxTlf35584_enableFunctionalWatchdog(IfxTlf35584_Driver* driver);
IFX_EXTERN boolean IfxTlf35584_disableFunctionalWatchdog(IfxTlf35584_Driver* driver);
IFX_EXTERN boolean IfxTlf35584_enableWindowWatchdog(IfxTlf35584_Driver* driver);
IFX_EXTERN boolean IfxTlf35584_disableWindowWatchdog(IfxTlf35584_Driver* driver);
IFX_EXTERN boolean IfxTlf35584_enableErr(IfxTlf35584_Driver* driver);
IFX_EXTERN boolean IfxTlf35584_disableErr(IfxTlf35584_Driver* driver);

IFX_EXTERN boolean IfxTlf35584_getDeviceStateRequest(IfxTlf35584_Driver* driver, IfxTlf35584_State *value);
IFX_EXTERN boolean IfxTlf35584_getDeviceState(IfxTlf35584_Driver* driver, IfxTlf35584_State *value);
IFX_EXTERN boolean IfxTlf35584_isProtectedRegisterLocked(IfxTlf35584_Driver* driver, boolean *value);
IFX_EXTERN boolean IfxTlf35584_getFunctionalWatchdogQuestion(IfxTlf35584_Driver* driver, uint8 *value);

IFX_EXTERN boolean IfxTlf35584_isWindowWatchdogEnabled(IfxTlf35584_Driver* driver, boolean *value);
IFX_EXTERN boolean IfxTlf35584_isFunctionalWatchdogEnabled(IfxTlf35584_Driver* driver, boolean *value);
IFX_EXTERN boolean IfxTlf35584_getWatchdogHeartbeatPeriod(IfxTlf35584_Driver* driver, uint8 *value);
IFX_EXTERN boolean IfxTlf35584_setWatchdogHeartbeatPeriod(IfxTlf35584_Driver* driver, uint8 value);
IFX_EXTERN boolean IfxTlf35584_getWindowWatchdogCloseWindow(IfxTlf35584_Driver* driver, uint8 *value);
IFX_EXTERN boolean IfxTlf35584_setWindowWatchdogCloseWindow(IfxTlf35584_Driver* driver, uint8 value);
IFX_EXTERN boolean IfxTlf35584_getWindowWatchdogOpenWindow(IfxTlf35584_Driver* driver, uint8 *value);
IFX_EXTERN boolean IfxTlf35584_setWindowWatchdogOpenWindow(IfxTlf35584_Driver* driver, uint8 value);
IFX_EXTERN boolean IfxTlf35584_isErrEnabled(IfxTlf35584_Driver* driver, boolean *value);


IFX_EXTERN boolean IfxTlf35584_getWatchdogCycleTime(IfxTlf35584_Driver* driver, IfxTlf35584_WatchdogCycleTime *value);
IFX_EXTERN boolean IfxTlf35584_setWatchdogCycleTime(IfxTlf35584_Driver* driver, IfxTlf35584_WatchdogCycleTime value);



/** \} */  


#endif /* IFXTLF35584_H */
