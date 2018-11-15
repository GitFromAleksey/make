/**
 * \file IfxCcu6_PwmHl.h
 * \brief CCU6 PWMHL details
 * \ingroup IfxLld_Ccu6
 *
 * \version iLLD_1_0_1_3_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
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
 * \defgroup  IfxLld_Ccu6_PwmHl_Usage How to use the CCU6 PWM Driver
 * \ingroup  IfxLld_Ccu6_PwmHl
 *
 * This driver implements the PWM functionalities as defined by \ref library_srvsw_stdif_pwmhl.
 * The user is free to use either the driver specific APIs below or to used the \ref library_srvsw_stdif_pwmhl "standard interface APIs".
 *
 * \section Specific Specific implementation
 * \todo add documentation
 *
 * For a detailed configuration of the microcontroller, see \ref IfxCcu6_PwmHl_init().
 *
 * \defgroup IfxLld_Ccu6_PwmHl PWM Interface Driver
 * \ingroup IfxLld_Ccu6
 * \defgroup IfxLld_Ccu6_PwmHl_DataStructures Data Structures
 * \ingroup IfxLld_Ccu6_PwmHl
 * \defgroup IfxLld_Ccu6_PwmHl_PwmHl_Functions PwmHl Functions
 * \ingroup IfxLld_Ccu6_PwmHl
 * \defgroup IfxLld_Ccu6_PwmHl_StdIf_Functions StdIf Functions
 * \ingroup IfxLld_Ccu6_PwmHl
 */

#ifndef IFXCCU6_PWMHL_H
#define IFXCCU6_PWMHL_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "StdIf/IfxStdIf_PwmHl.h"
#include "Ccu6/TimerWithTrigger/IfxCcu6_TimerWithTrigger.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Maximal number of channels handled by the driver. One channel has a top and bottom pwm output
 */
#define IFXCCU6_PWMHL_MAX_CHANNELS (3)

/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/

typedef struct IfxCcu6_PwmHl_s IfxCcu6_PwmHl;

typedef void                 (*IfxCcu6_PwmHl_Update)(IfxCcu6_PwmHl *driver, Ifx_TimerValue *tOn);

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Ccu6_PwmHl_DataStructures
 * \{ */
/** \brief Multi-channels PWM object definition (channels only)
 */
typedef struct
{
    Ifx_TimerValue  deadtime;               /**< \brief Dead time between the top and bottom channel in ticks */
    Ifx_TimerValue  minPulse;               /**< \brief minimum pulse that is output, shorter pulse time will be output as 0% duty cycle */
    Ifx_TimerValue  maxPulse;               /**< \brief internal parameter */
    Ifx_Pwm_Mode    mode;                   /**< \brief actual PWM mode */
    sint8           setMode;                /**< \brief A non zero flag indicates that the PWM mode is being modified */
    Ifx_ActiveState ccxActiveState;         /**< \brief Top PWM active state */
    Ifx_ActiveState coutxActiveState;       /**< \brief Bottom PWM active state */
    boolean         inverted;               /**< \brief Flag indicating the center aligned inverted mode (TRUE) */
    uint8           channelCount;           /**< \brief Number of PWM channels, one channel is made of a top and bottom channel */
} IfxCcu6_PwmHl_Base;

/** \} */

/** \addtogroup IfxLld_Ccu6_PwmHl_DataStructures
 * \{ */
/** \brief CCU6: PWM HL configuration
 */
typedef struct
{
    IfxStdIf_PwmHl_Config     base;        /**< \brief PWM HL standard interface configuration */
    IfxCcu6_TimerWithTrigger *timer;       /**< \brief Pointer to the linked timer object */
    IfxCcu6_Cc60_Out         *cc0;         /**< \brief CC0 channel used */
    IfxCcu6_Cc61_Out         *cc1;         /**< \brief CC1 channel used */
    IfxCcu6_Cc62_Out         *cc2;         /**< \brief CC2 channel used */
    IfxCcu6_Cout60_Out       *cout0;       /**< \brief COUT0 channel used */
    IfxCcu6_Cout61_Out       *cout1;       /**< \brief COUT1 channel used */
    IfxCcu6_Cout62_Out       *cout2;       /**< \brief COUT2 channel used */
} IfxCcu6_PwmHl_Config;

/** \brief Structure for PWM configuration
 */
typedef struct
{
    Ifx_Pwm_Mode         mode;           /**< \brief pwm mode */
    boolean              inverted;       /**< \brief Inverted configuration for the selected mode */
    IfxCcu6_PwmHl_Update update;         /**< \brief update call back function for the selected mode */
} IfxCcu6_PwmHl_Mode;

/** \brief CCU6 PWM driver
 */
struct IfxCcu6_PwmHl_s
{
    IfxCcu6_PwmHl_Base        base;         /**< \brief Multi-channels PWM object definition (channels only) */
    IfxCcu6_TimerWithTrigger *timer;        /**< \brief Pointer to the linked timer object */
    IfxCcu6_PwmHl_Update      update;       /**< \brief Update function for actual selected mode */
};

/** \} */

/** \addtogroup IfxLld_Ccu6_PwmHl_PwmHl_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initializes the timer object
 * \note To ensure that the channels counter are reset by the timer and do not overflow, leading to random signal on the output, the timer must be started before the call to this function.
 * Initialise the CCU6 module for PWM generation of high- and low switches usage, e.g.
 * - electric motor drive
 * - half-bridge switches
 *
 * It is assumed that the whole CCU6 module is only used for purposes mentioned at the
 * IfxCcu6_PwmHl API. No part of CCU6 module is used for other purpose.
 *
 * The timer used should configure the T12 as PWM base timer and T13 as trigger.
 * \param driver CCU6 PWM driver
 * \param config CCU6 : PWM HL configuration
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxCcu6_PwmHl_init(IfxCcu6_PwmHl *driver, const IfxCcu6_PwmHl_Config *config);

/** \brief Initialize the configuration structure to default
 * \param config Channel configuration. This parameter is Initialised by the function
 * \return None
 */
IFX_EXTERN void IfxCcu6_PwmHl_initConfig(IfxCcu6_PwmHl_Config *config);

/** \} */

/** \addtogroup IfxLld_Ccu6_PwmHl_StdIf_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the dead time
 * \param driver CCU6 PWM driver
 * \return Dead Time
 *
 * \see IfxStdIf_PwmHl_GetDeadtime
 *
 */
IFX_EXTERN float32 IfxCcu6_PwmHl_getDeadtime(IfxCcu6_PwmHl *driver);

/** \brief Returns the minimum pulse
 * \param driver CCU6 PWM driver
 * \return Min Pulse
 *
 * \see IfxStdIf_PwmHl_GetMinPulse
 *
 */
IFX_EXTERN float32 IfxCcu6_PwmHl_getMinPulse(IfxCcu6_PwmHl *driver);

/** \brief Returns Pwm mode
 * \param driver CCU6 PWM driver
 * \return Pwm mode
 *
 * \see IfxStdIf_PwmHl_GetMode
 *
 */
IFX_EXTERN Ifx_Pwm_Mode IfxCcu6_PwmHl_getMode(IfxCcu6_PwmHl *driver);

/** \brief Sets the dead time
 * \note The changes are not applied until Timer->applyUpdate() is called.
 * \param driver CCU6 PWM driver
 * \param deadtime Dead time value
 * \return TRUE on success else FALSE
 *
 * \see IfxStdIf_PwmHl_SetDeadtime
 *
 */
IFX_EXTERN boolean IfxCcu6_PwmHl_setDeadtime(IfxCcu6_PwmHl *driver, float32 deadtime);

/** \brief Sets the minimum pulse
 * \param driver CCU6 PWM driver
 * \param minPulse Minimum pulse
 * \return TRUE on success else FALSE
 *
 * \see IfxStdIf_PwmHl_SetMinPulse
 *
 */
IFX_EXTERN boolean IfxCcu6_PwmHl_setMinPulse(IfxCcu6_PwmHl *driver, float32 minPulse);

/** \brief Sets the PWM mode, the mode is only applied after setOnTime() + applyUpdate()
 * \param driver CCU6 PWM driver
 * \param mode Pwm mode
 * \return TRUE on success else FALSE
 *
 * \see IfxStdIf_PwmHl_SetMode
 *
 */
IFX_EXTERN boolean IfxCcu6_PwmHl_setMode(IfxCcu6_PwmHl *driver, Ifx_Pwm_Mode mode);

/** \brief Sets the ON time
 * Assign the ON time to the TOP channels.
 * The ON time of the BOTTOM channels are complementary.
 *
 * \note The changes are not applied until Timer->applyUpdate() is called.
 * \param driver CCU6 PWM driver
 * \param tOn ON time
 * \return None
 *
 * \see IfxStdIf_PwmHl_SetOnTime
 *
 */
IFX_EXTERN void IfxCcu6_PwmHl_setOnTime(IfxCcu6_PwmHl *driver, Ifx_TimerValue *tOn);

/** \brief Set channels which are generating PWM or in "stuck-at" state.
 *
 * \note The values for the parameters are arranged as follows:
 * index = 0 --> phase 0 top
 * index = 1 --> phase 0 bottom
 * index = 2 --> phase 1 top
 * index = 3 --> phase 1 bottom
 * index = 4 --> phase 2 top
 * index = 5 --> phase 2 bottom
 * \param driver CCU6 PWM driver
 * \param activeCh Pointer to boolean array containing values for PWM channels.
 * If FALSE, the channel will be in stuck-at state, else the channel will generate PWM.
 * \param stuckSt Pointer to boolean array containing values for active channels.
 * If FALSE, the stuck-at state is passive level, else the stuck-at state is active level.
 * \return None
 *
 * \see IfxStdIf_PwmHl_SetupChannels
 *
 */
IFX_EXTERN void IfxCcu6_PwmHl_setupChannels(IfxCcu6_PwmHl *driver, boolean *activeCh, boolean *stuckSt);

/** \brief Initialises the statndard interface Pwm
 * \param stdif Standard interface object, will be initialized by the function
 * \param driver Interface driver to be used by the standard interface. must be initialised separately
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxCcu6_PwmHl_stdIfPwmHlInit(IfxStdIf_PwmHl *stdif, IfxCcu6_PwmHl *driver);

/** \} */

#endif /* IFXCCU6_PWMHL_H */
