/**
 *  \file IfxTlf35584_enum.h 
 *  \brief Enumeration for TLF35584 register bitfields 
 *  
 *  Date: 2015-11-20 07:21:23 GMT
 *
 *  \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved. 
 *  
 *  Specification: <Reference to specification used> 
 *  MAY BE CHANGED BY USER [yes/no]: No 
 *  
 *                                  IMPORTANT NOTICE 
 *  
 *  Infineon Technologies AG (Infineon) is supplying this file for use 
 *  exclusively with Infineon's microcontroller products. This file can be freely 
 *  distributed within development tools that are supporting such microcontroller 
 *  products. 
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED 
 *  OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF 
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. 
 *  INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, 
 *  OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER. 
 *  
 *  \defgroup IfxLld_Tlf35584_Enum Enumeration 
 *  \ingroup IfxLld_Tlf35584
 */

#ifndef IFXTLF35584_ENUM_H
#define IFXTLF35584_ENUM_H 1
/******************************************************************************/
/** \addtogroup IfxLld_Tlf35584_Enum
 * \{  */

typedef enum
{
	IfxTlf35584_WindowWatchdogTrigger_wdi,
	IfxTlf35584_WindowWatchdogTrigger_spi
}IfxTlf35584_WindowWatchdogTrigger;
typedef enum
{
	IfxTlf35584_WindowWatchdogTriggerLevel_low = 0,
	IfxTlf35584_WindowWatchdogTriggerLevel_high = 1
}IfxTlf35584_WindowWatchdogTriggerLevel;
typedef enum
{
    IfxTlf35584_State_noRequest = 0,
    IfxTlf35584_State_init      = 1,
    IfxTlf35584_State_normal    = 2,
    IfxTlf35584_State_sleep     = 3,
    IfxTlf35584_State_standby   = 4,
    IfxTlf35584_State_wake      = 5,
}IfxTlf35584_State;
typedef enum
{
	IfxTlf35584_WatchdogCycleTime_100us = 0,
	IfxTlf35584_WatchdogCycleTime_1ms = 1
}IfxTlf35584_WatchdogCycleTime;

/** \}  */
#endif /* IFXTLF35584_ENUM_H_ */
