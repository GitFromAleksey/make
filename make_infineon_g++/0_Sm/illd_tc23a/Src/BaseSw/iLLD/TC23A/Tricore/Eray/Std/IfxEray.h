/**
 * \file IfxEray.h
 * \brief ERAY  basic functionality
 * \ingroup IfxLld_Eray
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
 * \defgroup IfxLld_Eray_Std_Enumerations Enumerations
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Interrupt Interrupt Functions
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_IO IO Pin Configuration Functions
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Module Module Functions
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Status Status Functions
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Configuration Configuration Functions
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Structures Data Structures
 * \ingroup IfxLld_Eray_Std
 * \defgroup IfxLld_Eray_Std_Operative Operative Functions
 * \ingroup IfxLld_Eray_Std
 */

#ifndef IFXERAY_H
#define IFXERAY_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxEray_cfg.h"
#include "_PinMap/IfxEray_PinMap.h"
#include "Src/Std/IfxSrc.h"
#include "IfxEray_reg.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Eray_Std_Enumerations
 * \{ */
/** \brief Baudrate on the flexray bus, defined in MODULE_ERAY0.PRTC1.B.BRP.
 */
typedef enum
{
    IfxEray_Baudrate_10  = 0, /**< \brief baudrate is 10MBits/Sec */
    IfxEray_Baudrate_5   = 1, /**< \brief baudrate is 5MBits/Sec */
    IfxEray_Baudrate_2_5 = 2  /**< \brief baudrate is 2.5MBits/Sec */
} IfxEray_Baudrate;

/** \brief wheather transmit buffer or receive buffer, defined in MODULE_ERAY0.WRHS1.B.CFG.
 */
typedef enum
{
    IfxEray_BufferDirection_receive  = 0, /**< \brief buffer is configured as receive buffer */
    IfxEray_BufferDirection_transmit = 1  /**< \brief buffer is configured as transmit buffer */
} IfxEray_BufferDirection;

/** \brief Channel Id
 */
typedef enum
{
    IfxEray_Channel_a = 0,  /**< \brief channel A */
    IfxEray_Channel_b = 1   /**< \brief channel B */
} IfxEray_Channel;

/** \brief Selection of error flag to clear defined in MODULE_ERAY.EIR.U
 */
typedef enum
{
    IfxEray_ClearErrorFlag_pemc = 1,         /**< \brief POC error mode change bit. */
    IfxEray_ClearErrorFlag_cna  = 2,         /**< \brief command not accepted event bit. */
    IfxEray_ClearErrorFlag_sfbm = 4,         /**< \brief sync frame below minimum bit. */
    IfxEray_ClearErrorFlag_sfo  = 8,         /**< \brief sync frame overflow event bit */
    IfxEray_ClearErrorFlag_ccf  = 16,        /**< \brief clock correction failure event. */
    IfxEray_ClearErrorFlag_ccl  = 32,        /**< \brief CHI command locked event. */
    IfxEray_ClearErrorFlag_eerr = 64,        /**< \brief ECC error event bit. */
    IfxEray_ClearErrorFlag_rfo  = 128,       /**< \brief RxFIFO overrun event bit. */
    IfxEray_ClearErrorFlag_efa  = 256,       /**< \brief empty FIFO access event bit. */
    IfxEray_ClearErrorFlag_iiba = 512,       /**< \brief illegal input buffer access event. */
    IfxEray_ClearErrorFlag_ioba = 1024,      /**< \brief illegal output buffer access event. */
    IfxEray_ClearErrorFlag_mhf  = 2048,      /**< \brief message handler constraint flag. */
    IfxEray_ClearErrorFlag_eda  = 65536,     /**< \brief error event on channel A. */
    IfxEray_ClearErrorFlag_ltva = 131072,    /**< \brief latest transmit violation flag on channel A . */
    IfxEray_ClearErrorFlag_taba = 262144,    /**< \brief transmission across channel A boundary flag. */
    IfxEray_ClearErrorFlag_edb  = 16777216,  /**< \brief error event on channel B. */
    IfxEray_ClearErrorFlag_ltvb = 33554432,  /**< \brief latest transmit violation flag on channel B . */
    IfxEray_ClearErrorFlag_tabb = 67108864   /**< \brief transmission across channel B boundary flag. */
} IfxEray_ClearErrorFlag;

/** \brief Selection of status flag to clear defined in MODULE_ERAY.SIR.U
 */
typedef enum
{
    IfxEray_ClearStatusFlag_wst  = 1,         /**< \brief wakeup status bit. */
    IfxEray_ClearStatusFlag_cas  = 2,         /**< \brief collision avoidance bit. */
    IfxEray_ClearStatusFlag_cycs = 4,         /**< \brief cycle start service bit. */
    IfxEray_ClearStatusFlag_txi  = 8,         /**< \brief transmit service request bit. */
    IfxEray_ClearStatusFlag_rxi  = 16,        /**< \brief receive service request bit. */
    IfxEray_ClearStatusFlag_rfne = 32,        /**< \brief receive fifo not empty bit. */
    IfxEray_ClearStatusFlag_rfcl = 64,        /**< \brief RxFIFO critical level reached bit. */
    IfxEray_ClearStatusFlag_nmvc = 128,       /**< \brief network management vector bit. */
    IfxEray_ClearStatusFlag_ti0  = 256,       /**< \brief timer0 service request bit. */
    IfxEray_ClearStatusFlag_ti1  = 512,       /**< \brief timer1 service request bit. */
    IfxEray_ClearStatusFlag_tibc = 1024,      /**< \brief transfer input buffer completion request bit. */
    IfxEray_ClearStatusFlag_tobc = 2048,      /**< \brief transfer output buffer completion request bit. */
    IfxEray_ClearStatusFlag_swe  = 4096,      /**< \brief stop watch event bit. */
    IfxEray_ClearStatusFlag_sucs = 8192,      /**< \brief startup success event bit. */
    IfxEray_ClearStatusFlag_mbsi = 16384,     /**< \brief message buffer service status bit. */
    IfxEray_ClearStatusFlag_sds  = 32768,     /**< \brief dynamic segment start bit. */
    IfxEray_ClearStatusFlag_wupa = 65536,     /**< \brief wakeup pattern channel A bit. */
    IfxEray_ClearStatusFlag_mtsa = 131072,    /**< \brief MTS receive channel A bit. */
    IfxEray_ClearStatusFlag_wupb = 16777216,  /**< \brief wakeup pattern channel B bit. */
    IfxEray_ClearStatusFlag_mtsb = 33554432   /**< \brief MTS receive channel B bit. */
} IfxEray_ClearStatusFlag;

/** \brief Clock divider in RUN mode, defined in MODULE_ERAY0.B.RMC.
 */
typedef enum
{
    IfxEray_ClockDivider_none = 0,  /**< \brief no clock signal */
    IfxEray_ClockDivider_1    = 1,  /**< \brief run mode clock divider 1  */
    IfxEray_ClockDivider_2,         /**< \brief run mode clock divider 2  */
    IfxEray_ClockDivider_3,         /**< \brief run mode clock divider 3  */
    IfxEray_ClockDivider_4,         /**< \brief run mode clock divider 4  */
    IfxEray_ClockDivider_5,         /**< \brief run mode clock divider 5  */
    IfxEray_ClockDivider_6,         /**< \brief run mode clock divider 6  */
    IfxEray_ClockDivider_7          /**< \brief run mode clock divider 7  */
} IfxEray_ClockDivider;

/** \brief External offset correction control defined in MODULE_ERAY0.GTU11.B.EOCC.
 */
typedef enum
{
    IfxEray_ExternalOffset_noCorrection         = 1,  /**< \brief No external correction control. */
    IfxEray_ExternalOffset_correctionSubtracted = 2,  /**< \brief External offset correction subtracted from calculated correction. */
    IfxEray_ExternalOffset_correctionAdded      = 3   /**< \brief External offset correction added to calculated correction. */
} IfxEray_ExternalOffset;

/** \brief External clock offset correction value defined in MODULE_ERAY0.GTU11.B.EOC.
 */
typedef enum
{
    IfxEray_ExternalOffsetCorrection_0 = 0,      /**< \brief external clock offset correction value 0  */
    IfxEray_ExternalOffsetCorrection_1,          /**< \brief external clock offset correction value 1  */
    IfxEray_ExternalOffsetCorrection_2,          /**< \brief external clock offset correction value 2  */
    IfxEray_ExternalOffsetCorrection_3,          /**< \brief external clock offset correction value 3  */
    IfxEray_ExternalOffsetCorrection_4,          /**< \brief external clock offset correction value 4  */
    IfxEray_ExternalOffsetCorrection_5,          /**< \brief external clock offset correction value 5  */
    IfxEray_ExternalOffsetCorrection_6,          /**< \brief external clock offset correction value 6  */
    IfxEray_ExternalOffsetCorrection_7           /**< \brief external clock offset correction value 7  */
} IfxEray_ExternalOffsetCorrection;

/** \brief External rate correction control MODULE_ERAY0.GTU11.B.ERCC.
 */
typedef enum
{
    IfxEray_ExternalRate_noCorrection         = 1,  /**< \brief No external correction control. */
    IfxEray_ExternalRate_correctionSubtracted = 2,  /**< \brief External rate correction subtracted from calculated correction. */
    IfxEray_ExternalRate_correctionAdded      = 3   /**< \brief External rate correction added to calculated correction. */
} IfxEray_ExternalRate;

/** \brief External clock rate correction value defined in MODULE_ERAY0.GTU11.B.ERC.
 */
typedef enum
{
    IfxEray_ExternalRateCorrection_0 = 0,      /**< \brief external clock rate correction value 0  */
    IfxEray_ExternalRateCorrection_1,          /**< \brief external clock rate correction value 1  */
    IfxEray_ExternalRateCorrection_2,          /**< \brief external clock rate correction value 2  */
    IfxEray_ExternalRateCorrection_3,          /**< \brief external clock rate correction value 3  */
    IfxEray_ExternalRateCorrection_4,          /**< \brief external clock rate correction value 4  */
    IfxEray_ExternalRateCorrection_5,          /**< \brief external clock rate correction value 5  */
    IfxEray_ExternalRateCorrection_6,          /**< \brief external clock rate correction value 6  */
    IfxEray_ExternalRateCorrection_7           /**< \brief external clock rate correction value 7  */
} IfxEray_ExternalRateCorrection;

/** \brief Duration of dynamic slot idle phase, defined in MODULE_ERAY0.B.DSI.
 */
typedef enum
{
    IfxEray_IdleDynamicSlots_0 = 0,      /**< \brief duration of dynamic slot idle phase is 0  */
    IfxEray_IdleDynamicSlots_1,          /**< \brief duration of dynamic slot idle phase is 1  */
    IfxEray_IdleDynamicSlots_2           /**< \brief duration of dynamic slot idle phase is 2  */
} IfxEray_IdleDynamicSlots;

/** \brief Wakeup or Startup listen timeout in presence of noise, defined in MODULE_ERAY0.SUCC2.B.LTN.
 */
typedef enum
{
    IfxEray_ListenTimeOutNoise_2 = 1,      /**< \brief listen Time-out noise 2  */
    IfxEray_ListenTimeOutNoise_3,          /**< \brief listen Time-out noise 3  */
    IfxEray_ListenTimeOutNoise_4,          /**< \brief listen Time-out noise 4  */
    IfxEray_ListenTimeOutNoise_5,          /**< \brief listen Time-out noise 5  */
    IfxEray_ListenTimeOutNoise_6,          /**< \brief listen Time-out noise 6  */
    IfxEray_ListenTimeOutNoise_7,          /**< \brief listen Time-out noise 7  */
    IfxEray_ListenTimeOutNoise_8,          /**< \brief listen Time-out noise 8  */
    IfxEray_ListenTimeOutNoise_9,          /**< \brief listen Time-out noise 9  */
    IfxEray_ListenTimeOutNoise_10,         /**< \brief listen Time-out noise 10  */
    IfxEray_ListenTimeOutNoise_11,         /**< \brief listen Time-out noise 11  */
    IfxEray_ListenTimeOutNoise_12,         /**< \brief listen Time-out noise 12  */
    IfxEray_ListenTimeOutNoise_13,         /**< \brief listen Time-out noise 13  */
    IfxEray_ListenTimeOutNoise_14,         /**< \brief listen Time-out noise 14  */
    IfxEray_ListenTimeOutNoise_15,         /**< \brief listen Time-out noise 15  */
    IfxEray_ListenTimeOutNoise_16          /**< \brief listen Time-out noise 16  */
} IfxEray_ListenTimeOutNoise;

/** \brief Maximum number of sync frames in a cluster defined in MODULE_ERAY0.GTU02.B.SNM.
 */
typedef enum
{
    IfxEray_MaxSynchFrames_2 = 2,      /**< \brief Maximum number of sync frames in a cluster are 2  */
    IfxEray_MaxSynchFrames_3,          /**< \brief Maximum number of sync frames in a cluster are 3  */
    IfxEray_MaxSynchFrames_4,          /**< \brief Maximum number of sync frames in a cluster are 4  */
    IfxEray_MaxSynchFrames_5,          /**< \brief Maximum number of sync frames in a cluster are 5  */
    IfxEray_MaxSynchFrames_6,          /**< \brief Maximum number of sync frames in a cluster are 6  */
    IfxEray_MaxSynchFrames_7,          /**< \brief Maximum number of sync frames in a cluster are 7  */
    IfxEray_MaxSynchFrames_8,          /**< \brief Maximum number of sync frames in a cluster are 8  */
    IfxEray_MaxSynchFrames_9,          /**< \brief Maximum number of sync frames in a cluster are 9  */
    IfxEray_MaxSynchFrames_10,         /**< \brief Maximum number of sync frames in a cluster are 10  */
    IfxEray_MaxSynchFrames_11,         /**< \brief Maximum number of sync frames in a cluster are 11  */
    IfxEray_MaxSynchFrames_12,         /**< \brief Maximum number of sync frames in a cluster are 12  */
    IfxEray_MaxSynchFrames_13,         /**< \brief Maximum number of sync frames in a cluster are 13  */
    IfxEray_MaxSynchFrames_14,         /**< \brief Maximum number of sync frames in a cluster are 14  */
    IfxEray_MaxSynchFrames_15          /**< \brief Maximum number of sync frames in a cluster are 15  */
} IfxEray_MaxSynchFrames;

/** \brief Commmand to control the Communication, defined in MODULE_ERAY0.SUCC1.B.CMD.
 */
typedef enum
{
    IfxEray_PocCommand_notAccepted = 0,  /**< \brief command not accepted. */
    IfxEray_PocCommand_config      = 1,  /**< \brief command to controller to enter CONFIG */
    IfxEray_PocCommand_ready       = 2,  /**< \brief command to controller to enter READY. */
    IfxEray_PocCommand_wakeup      = 3,  /**< \brief command to controller to enter WAKEUP */
    IfxEray_PocCommand_run         = 4,  /**< \brief command to controller to enter RUN */
    IfxEray_PocCommand_allSlots    = 5,  /**< \brief command to controller to enter ALL_SLOTS */
    IfxEray_PocCommand_halt        = 6,  /**< \brief command to controller to enter HALT */
    IfxEray_PocCommand_freeze      = 7,  /**< \brief command to controller to enter FREEZE */
    IfxEray_PocCommand_sendMts     = 8,  /**< \brief command to controller to enter SEND_MTS */
    IfxEray_PocCommand_coldStart   = 9,  /**< \brief command to controller to enter COLD_START */
    IfxEray_PocCommand_reset       = 10, /**< \brief command to controller to enter RESET */
    IfxEray_PocCommand_monitor     = 11, /**< \brief command to controller to enter MONITOR */
    IfxEray_PocCommand_clearRam    = 12  /**< \brief command to controller to enter CLEAR_RAM */
} IfxEray_PocCommand;

/** \brief State of Communication Controller Protocol operation control, defined in MODULE_ERAY0.CCSV.B.POCS.
 */
typedef enum
{
    IfxEray_PocState_defaultConfig               = 0,   /**< \brief controller entered default config state */
    IfxEray_PocState_ready                       = 1,   /**< \brief controller entered ready state */
    IfxEray_PocState_normalActive                = 2,   /**< \brief controller entered normal-active state */
    IfxEray_PocState_normalPassive               = 3,   /**< \brief controller entered normal-passive state */
    IfxEray_PocState_halt                        = 4,   /**< \brief controller entered halt state */
    IfxEray_PocState_monitor                     = 5,   /**< \brief controller entered monitor state */
    IfxEray_PocState_config                      = 15,  /**< \brief controller entered config state */
    IfxEray_PocState_wakeupStandby               = 16,  /**< \brief controller entered wakeup standby state */
    IfxEray_PocState_wakeupListen                = 17,  /**< \brief controller entered wakeup-listen state */
    IfxEray_PocState_wakeupSend                  = 18,  /**< \brief controller entered wakeup-send state */
    IfxEray_PocState_wakeupDetect                = 19,  /**< \brief controller entered wakeup-detection state */
    IfxEray_PocState_startup                     = 32,  /**< \brief controller entered startup state */
    IfxEray_PocState_coldStartListen             = 33,  /**< \brief controller entered clod-start listen state */
    IfxEray_PocState_collisionResolution         = 34,  /**< \brief controller entered collission-resolution state. */
    IfxEray_PocState_consistencyCheck            = 35,  /**< \brief controller entered consistency-check. */
    IfxEray_PocState_gap                         = 36,  /**< \brief controller entered gap state. */
    IfxEray_PocState_join                        = 37,  /**< \brief controller entered join state. */
    IfxEray_PocState_integrationCheck            = 38,  /**< \brief controller entered integration-check. */
    IfxEray_PocState_integrationListen           = 39,  /**< \brief controller entered integration-listen state. */
    IfxEray_PocState_integrationConsistencyCheck = 40,  /**< \brief controller entered integration consistency check state */
    IfxEray_PocState_initializeSchedule          = 41,  /**< \brief controller entered initialise schedule state */
    IfxEray_PocState_staruAborted                = 42,  /**< \brief controller entered startup-abort state */
    IfxEray_PocState_startupSucced               = 43   /**< \brief controller entered startup succeed state. */
} IfxEray_PocState;

/** \brief Receiving channel, defined in MODULE_ERAY0.FRF.B.CH.
 */
typedef enum
{
    IfxEray_ReceiveChannel_both = 0,  /**< \brief both channels for reception */
    IfxEray_ReceiveChannel_b    = 1,  /**< \brief channel A for reception */
    IfxEray_ReceiveChannel_a    = 2,  /**< \brief channel B for reception */
    IfxEray_ReceiveChannel_none = 3   /**< \brief none channels for reception */
} IfxEray_ReceiveChannel;

/** \brief Enable/disable the sensitivity of the module to sleep signal\n
 * Definition in Ifx_ERAY.CLC.B.EDIS
 */
typedef enum
{
    IfxEray_SleepMode_enable  = 0, /**< \brief enables sleep mode */
    IfxEray_SleepMode_disable = 1  /**< \brief disables sleep mode */
} IfxEray_SleepMode;

/** \brief Sample count value for strobing, defined in MODULE_ERAY0.PRTC1.B.SPP.
 */
typedef enum
{
    IfxEray_StrobePosition_5 = 0,  /**< \brief Sample count 5 for strobing */
    IfxEray_StrobePosition_4 = 1,  /**< \brief Sample count 4 for strobing */
    IfxEray_StrobePosition_6 = 2   /**< \brief Sample count 6 for strobing */
} IfxEray_StrobePosition;

/** \brief OCDS Suspend Control (OCDS.SUS)
 */
typedef enum
{
    IfxEray_SuspendMode_none = 0,  /**< \brief No suspend */
    IfxEray_SuspendMode_hard = 1,  /**< \brief Hard Suspend */
    IfxEray_SuspendMode_soft = 2   /**< \brief Soft Suspend */
} IfxEray_SuspendMode;

/** \brief Transmission mode of Header, defined in MODULE_ERAY0.WRHS1.B.TXM.
 */
typedef enum
{
    IfxEray_TransmissionMode_continuous = 0,  /**< \brief continuos transmission mode */
    IfxEray_TransmissionMode_singleShot = 1   /**< \brief single transmission mode */
} IfxEray_TransmissionMode;

/** \brief Initial transmission mode, defined in MODULE_ERAY0.SUCC1.B.TSM.
 */
typedef enum
{
    IfxEray_TransmissionSlotMode_all    = 0, /**< \brief transmission in all slots. */
    IfxEray_TransmissionSlotMode_single = 1  /**< \brief transmission in key slot. */
} IfxEray_TransmissionSlotMode;

/** \brief Wakeup pattern carry channel, defined in MODULE_ERAY0.SUCC1.B.WUCS.
 */
typedef enum
{
    IfxEray_WakeupChannel_a = 0,  /**< \brief send wakeup channel pattern on channel A */
    IfxEray_WakeupChannel_b = 1   /**< \brief send wakeup channel pattern on channel B */
} IfxEray_WakeupChannel;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Eray_Std_Structures
 * \{ */
/** \brief Header section in  a frame.
 */
typedef struct
{
    uint16                   frameId;                         /**< \brief slot ID of the selected Message Buffer. */
    uint8                    cycleCode;                       /**< \brief the cycle set used for cycle counter filtering. */
    boolean                  channelAFiltered;                /**< \brief channel A serves as a control for transmit and filter for receive buffers. */
    boolean                  channelBFiltered;                /**< \brief channel B serves as a control for transmit and filter for receive buffers. */
    IfxEray_BufferDirection  bufferDirection;                 /**< \brief selects buffer as a transmit buffer or as a receive buffer. */
    boolean                  transmitPayloadIndicatior;       /**< \brief weather payload indicator is set or not. */
    IfxEray_TransmissionMode transmissionMode;                /**< \brief transmission mode of Header. */
    boolean                  bufferServiceEnabled;            /**< \brief wether buffer service request is enabled or not. */
    uint8                    payloadLength;                   /**< \brief length of data section. */
    uint16                   dataPointer;                     /**< \brief pointer to the data section of message buffer in RAM. */
    boolean                  startupFrameIndicator;           /**< \brief whether startup frame is indicated or not. */
    boolean                  syncFrameIndicator;              /**< \brief whether sync frame is indicated or not. */
} IfxEray_Header;

/** \brief Received header in a frame.
 */
typedef struct
{
    uint16 frameId : 11;                     /**< \brief received frame id. */
    uint8  payloadLength : 7;                /**< \brief received payload length. */
    uint16 headerCrc : 11;                   /**< \brief received header crc. */
    uint8  reservedBit : 1;                  /**< \brief state of the received reserved bit. */
    uint8  nullFrameIndicator : 1;           /**< \brief 0 : no data frame received; 1: atleast one data frame received. */
    uint8  syncFrame : 1;                    /**< \brief 0 : received frame is not a synch frame ; 1 : receive frame is a synch frame. */
    uint8  startupFrame : 1;                 /**< \brief 0 : received frame is not a startup frame ; 1 : receive frame is a startup frame. */
    uint8  cycleNumber : 7;                  /**< \brief cycle number in which frame is received. */
    uint8  payloadPreambleIndicator : 1;     /**< \brief 1 : received payload segment has network management and message id or not; 0 : It hasn't. */
} IfxEray_ReceivedHeader;

/** \brief Transmit control structure.
 */
typedef struct
{
    boolean headerTransfered;        /**< \brief whether header is transfered from input buffers to Message RAM or not. */
    boolean dataTransfered;          /**< \brief whether data is transfered from input buffers to Message RAM or not. */
    boolean transferRequested;       /**< \brief transmit buffer released for transmission or not. */
    uint8   bufferIndex;             /**< \brief buffer index in the Message RAM. */
} IfxEray_SlotConfig;

/** \} */

/** \addtogroup IfxLld_Eray_Std_Interrupt
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clears the error flag requested.
 * \param eray pointer to ERAY module registers.
 * \param errorFlag error flag to be cleared.
 * \return None
 */
IFX_INLINE void IfxEray_clearErrorFlag(Ifx_ERAY *eray, IfxEray_ClearErrorFlag errorFlag);

/** \brief Clears the status flag requested.
 * \param eray pointer to ERAY module registers.
 * \param statusFlag status flag to be cleared.
 * \return None
 */
IFX_INLINE void IfxEray_clearStatusFlag(Ifx_ERAY *eray, IfxEray_ClearStatusFlag statusFlag);

/** \brief Gets the error interrupt flags.
 * \param eray pointer to ERAY module registers.
 * \return error interrupt flags.
 */
IFX_INLINE Ifx_ERAY_EIR IfxEray_getErrorInterrupts(Ifx_ERAY *eray);

/** \brief Gets the IBUSY service request.
 * \param eray pointer to ERAY module registers.
 * \return address of IBUSY service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInputBufferBusySrcPtr(Ifx_ERAY *eray);

/** \brief Gets the INT0 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of INT0 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInterruptLine0SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the INT1 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of INT1 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInterruptLine1SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the message buffers interrupt status.
 * \param eray pointer to ERAY module registers.
 * \param messageBuffer message buffer to which interrupt status be checked.
 * \return message buffer interrupt status.
 */
IFX_INLINE boolean IfxEray_getMessageBufferInterruptStatus(Ifx_ERAY *eray, uint8 messageBuffer);

/** \brief Gets the MBSC0 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of MBSC0 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getMessageBufferStatus0SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the MBSC1 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of MBSC1 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getMessageBufferStatus1SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the NDAT0 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of NDAT0 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getNewDataInterrupt0SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the NDAT1 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of NDAT1 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getNewDataInterrupt1SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the new data interrupt buffers status.
 * \param eray pointer to ERAY module registers.
 * \param ndat message buffer number configured to which ndat occurs.
 * \return ndat interrupt buffer.
 */
IFX_INLINE boolean IfxEray_getNewDataInterruptStatus(Ifx_ERAY *eray, uint8 ndat);

/** \brief Gets the OBUSY service request.
 * \param eray pointer to ERAY module registers.
 * \return address of OBUSY service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getOutputBufferBusySrcPtr(Ifx_ERAY *eray);

/** \brief Gets the status interrupt flags.
 * \param eray pointer to ERAY module registers.
 * \return status interrupt flags.
 */
IFX_INLINE Ifx_ERAY_SIR IfxEray_getStatusInterrupts(Ifx_ERAY *eray);

/** \brief Gets the TINT0 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of TINT0 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getTimerInterrupt0SrcPtr(Ifx_ERAY *eray);

/** \brief Gets the TINT1 service request.
 * \param eray pointer to ERAY module registers.
 * \return address of TINT1 service request value.
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getTimerInterrupt1SrcPtr(Ifx_ERAY *eray);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clears all the error flags.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_EXTERN void IfxEray_clearAllFlags(Ifx_ERAY *eray);

/** \brief Enables all the Interrupt lines.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_EXTERN void IfxEray_enableInterruptLines(Ifx_ERAY *eray);

/** \brief Selects between MBSC0 and MBSC1 interrupt destination
 * \param eray pointer to ERAY module registers.
 * \param messageBuffer message buffer interrupt which should be configured
 * \param messageBufferDestination selects MBSC0 or MBSC1 interrupt output
 * \return None
 */
IFX_EXTERN void IfxEray_setMessageBufferInterruptDestination(Ifx_ERAY *eray, uint8 messageBuffer, uint8 messageBufferDestination);

/** \brief Selects between NDAT0 and NDAT1 interrupt destination
 * \param eray pointer to ERAY module registers.
 * \param ndat NDAT interrupt which should be configured
 * \param ndatDestination selects NDAT0 or NDAT1 interrupt output
 * \return None
 */
IFX_EXTERN void IfxEray_setNewDataInterruptDestination(Ifx_ERAY *eray, uint8 ndat, uint8 ndatDestination);

/** \} */

/** \addtogroup IfxLld_Eray_Std_IO
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initialises a RX pin.
 * \param rx the RX Pin which should be configured.
 * \param rxMode the pin input mode which should be configured.
 * \return None
 */
IFX_INLINE void IfxEray_initRxPin(const IfxEray_Rxd_In *rx, IfxPort_InputMode rxMode);

/** \brief Initializes a TX Enable output.
 * \param txEn the TX Enable Pin which should be configured.
 * \param txEnMode the pin output mode which should be configured.
 * \param padDriver the pad driver mode which should be configured.
 * \return None
 */
IFX_INLINE void IfxEray_initTxEnPin(const IfxEray_Txen_Out *txEn, IfxPort_OutputMode txEnMode, IfxPort_PadDriver padDriver);

/** \brief Initializes a TX output.
 * \param tx the TX Pin which should be configured.
 * \param txMode the pin output mode which should be configured.
 * \param padDriver the pad driver mode which should be configured.
 * \return None
 */
IFX_INLINE void IfxEray_initTxPin(const IfxEray_Txd_Out *tx, IfxPort_OutputMode txMode, IfxPort_PadDriver padDriver);

/** \} */

/** \addtogroup IfxLld_Eray_Std_Module
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Disables the ERAY module.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_INLINE void IfxEray_disableModule(Ifx_ERAY *eray);

/** \brief Enables the ERAY module.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_INLINE void IfxEray_enableModule(Ifx_ERAY *eray);

/** \brief Returns the module's suspend state.
 * TRUE :if module is suspended.
 * FALSE:if module is not yet suspended.
 * \param eray Pointer to ERAY module registers
 * \return Suspend status (TRUE / FALSE)
 */
IFX_INLINE boolean IfxEray_isModuleSuspended(Ifx_ERAY *eray);

/** \brief Sets the sensitivity of the module to sleep signal
 * \param eray pointer to ERAY registers
 * \param mode mode selection (enable/disable)
 * \return None
 */
IFX_INLINE void IfxEray_setSleepMode(Ifx_ERAY *eray, IfxEray_SleepMode mode);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/**
 * \param eray Resource index of the ERAY
 * \return ERAY module register address
 */
IFX_EXTERN Ifx_ERAY *IfxEray_getAddress(IfxEray_Index eray);

/** \brief API to get the resource index of the ERAY specified.
 * \param eray Pointer to the ERAY HW module (register memory map)
 * \return Resource index of the ERAY
 */
IFX_EXTERN IfxEray_Index IfxEray_getIndex(Ifx_ERAY *eray);

/** \brief Resets the ERAY kernel.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_EXTERN void IfxEray_resetModule(Ifx_ERAY *eray);

/** \} */

/** \addtogroup IfxLld_Eray_Std_Status
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Gets the FIFO status.
 * \param eray pointer to ERAY module registers.
 * \return FIFO status.
 */
IFX_INLINE Ifx_ERAY_FSR IfxEray_getFifoStatus(Ifx_ERAY *eray);

/** \brief Gets the Input Buffer Host Busy status.
 * \param eray pointer to ERAY module registers.
 * \return TRUE if Host is Busy otherwise FALSE.
 */
IFX_INLINE boolean IfxEray_getInputBufferBusyHostStatus(Ifx_ERAY *eray);

/** \brief Gets the Input Buffer Shadow status.
 * \param eray pointer to ERAY module registers.
 * \return TRUE if busy otherwise FALSE
 */
IFX_INLINE uint8 IfxEray_getInputBufferBusyShadowStatus(Ifx_ERAY *eray);

/** \brief Gets the output buffer index.
 * \param eray pointer to ERAY module registers.
 * \return output buffer index.
 */
IFX_INLINE uint8 IfxEray_getOutputBuffer(Ifx_ERAY *eray);

/** \brief Gets the Output Buffer Shadow status.
 * \param eray pointer to ERAY module registers.
 * \return TRUE if busy otherwise FALSE
 */
IFX_INLINE boolean IfxEray_getOutputBufferBusyShadowStatus(Ifx_ERAY *eray);

/** \brief Gets the current POC state.
 * \param eray pointer to ERAY module registers.
 * \return current POC state.
 */
IFX_INLINE IfxEray_PocState IfxEray_getPocState(Ifx_ERAY *eray);

/** \brief Gets the received wakeup pattern channel.
 * \param eray pointer to ERAY module registers.
 * \return received wakeup pattern channel.
 */
IFX_INLINE IfxEray_WakeupChannel IfxEray_getWakeupPatternReceivedChannel(Ifx_ERAY *eray);

/** \brief Waits until the controller enters required POC state.
 * \param eray pointer to ERAY module registers.
 * \param pocState POC state upto which controller waits.
 * \return None
 */
IFX_INLINE void IfxEray_waitForPocState(Ifx_ERAY *eray, IfxEray_PocState pocState);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Changes the Commmunication Controller state.
 * \param eray pointer to ERAY module registers.
 * \param pocCommand POC command which triggers the Controller state.
 * \return TRUE if command accepted otherwise FALSE.
 */
IFX_EXTERN boolean IfxEray_changePocState(Ifx_ERAY *eray, IfxEray_PocCommand pocCommand);

/** \brief Sets the POC state to Ready state.
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_EXTERN void IfxEray_setPocReady(Ifx_ERAY *eray);

/** \} */

/** \addtogroup IfxLld_Eray_Std_Configuration
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief request to receive header section from message buffer.
 * \param eray pointer to ERAY module registers.
 * \param headerReceived whether header is received or not.
 * \return None
 */
IFX_INLINE void IfxEray_receiveHeader(Ifx_ERAY *eray, boolean headerReceived);

/** \brief sets the bit to send header in  frame.
 * \param eray pointer to ERAY module registers.
 * \param headerTransfered whether header transfered or not.
 * \return None
 */
IFX_INLINE void IfxEray_sendHeader(Ifx_ERAY *eray, boolean headerTransfered);

/** \brief Sets number of cycle pairs for Active state.
 * \param eray pointer to ERAY module registers.
 * \param numberOfCyclePairsForActive number of cycle pairs for Active state.
 * \return None
 */
IFX_INLINE void IfxEray_setActiveCyclePairs(Ifx_ERAY *eray, uint8 numberOfCyclePairsForActive);

/** \brief Sets auto delays between input, output buffers and message RAM
 * \param eray pointer to ERAY module registers.
 * \return None
 */
IFX_INLINE void IfxEray_setAutoDelayBuffers(Ifx_ERAY *eray);

/** \brief Sets baudrate on Flexray bus.
 * \param eray pointer to ERAY module registers.
 * \param baudrate baudrate on flexray bus.
 * \return None
 */
IFX_INLINE void IfxEray_setBaudrate(Ifx_ERAY *eray, IfxEray_Baudrate baudrate);

/** \brief Sets secured buffers in message RAM.
 * \param eray pointer to ERAY module registers.
 * \param secureValue secure value.
 * \return None
 */
IFX_INLINE void IfxEray_setBufferReconfigSecure(Ifx_ERAY *eray, uint8 secureValue);

/** \brief Sets channel A initial offstes.
 * \param eray pointer to ERAY module registers.
 * \param channelAMicrotickInitialOffset difference between reference points on channel A in microticks.
 * \param channelAMacrotickInitialOffset difference between reference points on channel A in macroticks.
 * \return None
 */
IFX_INLINE void IfxEray_setChannelAInitialOffsets(Ifx_ERAY *eray, uint8 channelAMicrotickInitialOffset, uint8 channelAMacrotickInitialOffset);

/** \brief Sets channel B initial offstes.
 * \param eray pointer to ERAY module registers.
 * \param channelBMicrotickInitialOffset difference between reference points on channel B in microticks.
 * \param channelBMacrotickInitialOffset difference between reference points on channel B in macroticks.
 * \return None
 */
IFX_INLINE void IfxEray_setChannelBInitialOffsets(Ifx_ERAY *eray, uint8 channelBMicrotickInitialOffset, uint8 channelBMacrotickInitialOffset);

/** \brief Sets receive delays on channels.
 * \param eray pointer to ERAY module registers.
 * \param channelAReceptionDelay reception delay on channel A.
 * \param channelBReceptionDelay reception delay on channel B.
 * \return None
 */
IFX_INLINE void IfxEray_setChannelsReceiveDelay(Ifx_ERAY *eray, uint8 channelAReceptionDelay, uint8 channelBReceptionDelay);

/** \brief Sets clock correction cycles for Passive and Halt.
 * \param eray pointer to ERAY module registers.
 * \param clockCorrectionCyclesPassive maximum number of cycles missing clock correction leading for passive state.
 * \param clockCorrectionCyclesHalt maximum number of cycles missing clock correction leading for halt state.
 * \return None
 */
IFX_INLINE void IfxEray_setClockCorrectionCycles(Ifx_ERAY *eray, uint8 clockCorrectionCyclesPassive, uint8 clockCorrectionCyclesHalt);

/** \brief lead to halt state in clock synch error.
 * \param eray pointer to ERAY module registers.
 * \param clockSyncErrorHalt whether to enter halt in clock synch error or not.
 * \return None
 */
IFX_INLINE void IfxEray_setClockSynchErrorHalt(Ifx_ERAY *eray, boolean clockSyncErrorHalt);

/** \brief Sets cluster drift values.
 * \param eray pointer to ERAY module registers.
 * \param clusterDrift cluster drift damping value used in clock synchronization.
 * \param maxDriftOffset maximum drift offset between two nodes.
 * \return None
 */
IFX_INLINE void IfxEray_setClusterDriftValues(Ifx_ERAY *eray, uint8 clusterDrift, uint16 maxDriftOffset);

/** \brief Sets cluster startup deviation.
 * \param eray pointer to ERAY module registers.
 * \param acceptedStartupDeviation deviation for startup Frames during integration.
 * \return None
 */
IFX_INLINE void IfxEray_setClusterStartupDeviation(Ifx_ERAY *eray, uint16 acceptedStartupDeviation);

/** \brief Sets CAS symbol window duration.
 * \param eray pointer to ERAY module registers.
 * \param collisionAvoidanceDuration accepted duration of CAS symbol.
 * \return None
 */
IFX_INLINE void IfxEray_setCollisionAvoidanceDuration(Ifx_ERAY *eray, uint8 collisionAvoidanceDuration);

/** \brief sets duration of the communication cycle in Macroticks.
 * \param eray pointer to ERAY module registers.
 * \param macroticks duration of the communication cycle in Macroticks.
 * \return None
 */
IFX_INLINE void IfxEray_setCycleDurationMacroticks(Ifx_ERAY *eray, uint16 macroticks);

/** \brief sets duration of the communication cycle in Microticks.
 * \param eray pointer to ERAY module registers.
 * \param microticks duration of the communication cycle in Microticks.
 * \return None
 */
IFX_INLINE void IfxEray_setCycleDurationMicroticks(Ifx_ERAY *eray, uint32 microticks);

/** \brief Sets decoding correction value.
 * \param eray pointer to ERAY module registers.
 * \param decodingCorrection decoding correction value.
 * \return None
 */
IFX_INLINE void IfxEray_setDecodingCorrectionValue(Ifx_ERAY *eray, uint8 decodingCorrection);

/** \brief Sets dynamic slots count and length.
 * \param eray pointer to ERAY module registers.
 * \param dynamicSlotLength duration of dynamic slot in macroticks.
 * \param dynamicSlotCount number of dynamic slots in a communication cycle.
 * \param idleDynamicSlots duration of dynamic slot idle phase.
 * \return None
 */
IFX_INLINE void IfxEray_setDynamicSlots(Ifx_ERAY *eray, uint8 dynamicSlotLength, uint16 dynamicSlotCount, IfxEray_IdleDynamicSlots idleDynamicSlots);

/** \brief Sets external correction controls.
 * \param eray pointer to ERAY module registers.
 * \param externalOffset External offset correction control.
 * \param externalRate External rate correction control.
 * \return None
 */
IFX_INLINE void IfxEray_setExternalCorrectionControl(Ifx_ERAY *eray, IfxEray_ExternalOffset externalOffset, IfxEray_ExternalRate externalRate);

/** \brief Sets external correction values.
 * \param eray pointer to ERAY module registers.
 * \param externalOffsetCorrection external clock offset correction value.
 * \param externalRateCorrection external clock rate correction value.
 * \return None
 */
IFX_INLINE void IfxEray_setExternalCorrectionValues(Ifx_ERAY *eray, IfxEray_ExternalOffsetCorrection externalOffsetCorrection, IfxEray_ExternalRateCorrection externalRateCorrection);

/** \brief Sets FIFO buffer start idex.
 * \param eray pointer to ERAY module registers.
 * \param fifoBufferStartIndex FIFO buffer start idex.
 * \return None
 */
IFX_INLINE void IfxEray_setFifoBufferStartIndex(Ifx_ERAY *eray, uint8 fifoBufferStartIndex);

/** \brief Sets FIFO filter configurations.
 * \param eray pointer to ERAY module registers.
 * \param rejectedFrameId rejected frameId by FIFO.
 * \param filteredCycleNumber filtered cycle number.
 * \param fifoNullFramesRejected null frames rejection selection.
 * \param frameIdFilter filtered frameid by FIFO.
 * \return None
 */
IFX_INLINE void IfxEray_setFifoFilterConfigurations(Ifx_ERAY *eray, uint16 rejectedFrameId, uint8 filteredCycleNumber, boolean fifoNullFramesRejected, uint16 frameIdFilter);

/** \brief Sets FIFO configurations.
 * \param eray pointer to ERAY module registers.
 * \param receiveChannel FIFO receive channel.
 * \param staticFifoDisabled static FIFO selection.
 * \param fifoDepth FIFO depth.
 * \return None
 */
IFX_INLINE void IfxEray_setFifoMessageBufferConfigurations(Ifx_ERAY *eray, IfxEray_ReceiveChannel receiveChannel, boolean staticFifoDisabled, uint8 fifoDepth);

/** \brief Sets first dynamic buffer.
 * \param eray pointer to ERAY module registers.
 * \param firstDynamicBuffer first dynamic buffer.
 * \return None
 */
IFX_INLINE void IfxEray_setFirstDynamicBuffer(Ifx_ERAY *eray, uint8 firstDynamicBuffer);

/** \brief Sets startup or wakeup listen timeouts.
 * \param eray pointer to ERAY module registers.
 * \param listenTimeOut wakeup or startup listen timeout in microticks.
 * \param listenTimeOutNoise upper limit for startup or wakeup listen timeout in presence of noise.
 * \return None
 */
IFX_INLINE void IfxEray_setListenTimeOuts(Ifx_ERAY *eray, uint32 listenTimeOut, IfxEray_ListenTimeOutNoise listenTimeOutNoise);

/** \brief Sets the maximum cold start attempts for active state.
 * \param eray pointer to ERAY module registers.
 * \param maxColdStartAttempts maximum number of attempts that a cold start node allows.
 * \return None
 */
IFX_INLINE void IfxEray_setMaxColdStartAttempts(Ifx_ERAY *eray, uint8 maxColdStartAttempts);

/** \brief Sets max limit correction values.
 * \param eray pointer to ERAY module registers.
 * \param maxOffsetCorrection maximum offset correction.
 * \param maxRateCorrection maximum rate correction.
 * \return None
 */
IFX_INLINE void IfxEray_setMaxCorrectionValues(Ifx_ERAY *eray, uint16 maxOffsetCorrection, uint16 maxRateCorrection);

/** \brief Sets maximum synch frames in a cluster.
 * \param eray pointer to ERAY module registers.
 * \param maxSyncFrames maximum synch frames in a cluster.
 * \return None
 */
IFX_INLINE void IfxEray_setMaxSynchFrames(Ifx_ERAY *eray, IfxEray_MaxSynchFrames maxSyncFrames);

/** \brief Sets number of message buffers.
 * \param eray pointer to ERAY module registers.
 * \param numberOfMessageBuffers number of message buffers.
 * \return None
 */
IFX_INLINE void IfxEray_setMessageBufferCount(Ifx_ERAY *eray, uint8 numberOfMessageBuffers);

/** \brief Sets Message Handler configurations.
 * \param eray pointer to ERAY module registers.
 * \param staticFramepayload payload length of static frames in double bytes.
 * \param latestTransmissionStart dynamic slots befor transmission of inhibit frame in dynamic segment.
 * \return None
 */
IFX_INLINE void IfxEray_setMessageHandlerConfigurations(Ifx_ERAY *eray, uint8 staticFramepayload, uint8 latestTransmissionStart);

/** \brief Sets network start Idle time.
 * \param eray pointer to ERAY module registers.
 * \param networkStartIdleTime starting point of Network Idle Time Phase.
 * \return None
 */
IFX_INLINE void IfxEray_setNetworkStartIdleTime(Ifx_ERAY *eray, uint16 networkStartIdleTime);

/** \brief Sets network management vector length.
 * \param eray pointer to ERAY module registers.
 * \param networkVectorLength length of network management vector.
 * \return None
 */
IFX_INLINE void IfxEray_setNetworkVectorLength(Ifx_ERAY *eray, uint32 networkVectorLength);

/** \brief Sets channels connected to node.
 * \param eray pointer to ERAY module registers.
 * \param channelAConnectedNode whether node connected to channel A or not.
 * \param channelBConnectedNode whether node connected to channel B or not.
 * \return None
 */
IFX_INLINE void IfxEray_setNodeChannels(Ifx_ERAY *eray, boolean channelAConnectedNode, boolean channelBConnectedNode);

/** \brief Sets offset correction starting point.
 * \param eray pointer to ERAY module registers.
 * \param correctionOffset offset correction start point.
 * \return None
 */
IFX_INLINE void IfxEray_setOffsetCorrection(Ifx_ERAY *eray, uint16 correctionOffset);

/** \brief requests to receive the frame.
 * \param eray pointer to ERAY module registers.
 * \param receiveRequested whether frame to be received or not.
 * \return None
 */
IFX_INLINE void IfxEray_setReceiveRequest(Ifx_ERAY *eray, boolean receiveRequested);

/** \brief Sets receive wakeup times.
 * \param eray pointer to ERAY module registers.
 * \param receiveWakeupTestDuration duration of receive wakeup pattern.
 * \param receiveWakeupIdleTime duration of receive wakeup idle time.
 * \param receiveWakeupLowTime duration of receive wakeup low time.
 * \return None
 */
IFX_INLINE void IfxEray_setReceiveWakeupTimes(Ifx_ERAY *eray, uint8 receiveWakeupTestDuration, uint8 receiveWakeupIdleTime, uint8 receiveWakeupLowTime);

/** \brief sets buffer number in which frame is received.
 * \param eray pointer to ERAY module registers.
 * \param bufferIndex buffer number in which frame is received.
 * \return None
 */
IFX_INLINE void IfxEray_setRxBufferNumber(Ifx_ERAY *eray, uint8 bufferIndex);

/** \brief Sets slots action points.
 * \param eray pointer to ERAY module registers.
 * \param staticActionPoint static slots and symbol window action point.
 * \param dynamicActionPoint dynamic slots action point.
 * \return None
 */
IFX_INLINE void IfxEray_setSlotActionPoints(Ifx_ERAY *eray, uint8 staticActionPoint, uint8 dynamicActionPoint);

/** \brief Sets static slots count and length.
 * \param eray pointer to ERAY module registers.
 * \param staticSlotLength duration of static slot in macroticks.
 * \param staticSlotsCount number of static slots in a communication cycle.
 * \return None
 */
IFX_INLINE void IfxEray_setStaticSlots(Ifx_ERAY *eray, uint16 staticSlotLength, uint16 staticSlotsCount);

/** \brief Sets sample point for strobing.
 * \param eray pointer to ERAY module registers.
 * \param strobePosition strobing sample count.
 * \return None
 */
IFX_INLINE void IfxEray_setStrobePosition(Ifx_ERAY *eray, IfxEray_StrobePosition strobePosition);

/** \brief Sets channels which transmits symbols.
 * \param eray pointer to ERAY module registers.
 * \param channelASymbolTransmitted whether symbol is transmitted in Channel A or not.
 * \param channelBSymbolTransmitted whether symbol is transmitted in Channel B or not.
 * \return None
 */
IFX_INLINE void IfxEray_setSymbolChannels(Ifx_ERAY *eray, boolean channelASymbolTransmitted, boolean channelBSymbolTransmitted);

/** \brief Sets the transmit slot mode.
 * \param eray pointer to ERAY module registers.
 * \param transmissionSlotMode transmission slot mode.
 * \return None
 */
IFX_INLINE void IfxEray_setTransmissionSlotMode(Ifx_ERAY *eray, IfxEray_TransmissionSlotMode transmissionSlotMode);

/** \brief Sets transmission start time duration.
 * \param eray pointer to ERAY module registers.
 * \param transmissionStartTime transmission start time.
 * \return None
 */
IFX_INLINE void IfxEray_setTransmissionStartTime(Ifx_ERAY *eray, uint16 transmissionStartTime);

/** \brief Sets transfer request to send frame.
 * \param eray pointer to ERAY module registers.
 * \param transferRequested whether transfer requested or not.
 * \return None
 */
IFX_INLINE void IfxEray_setTransmitRequest(Ifx_ERAY *eray, boolean transferRequested);

/** \brief Sets transmit wakeup times.
 * \param eray pointer to ERAY module registers.
 * \param transmitWakeupRepetitions transmission wakeup repetitions.
 * \param transmitWakeupIdleTime duration of transmit wakeup idle time.
 * \param transmitWakeupLowTime duration of transmit wakeup low time.
 * \return None
 */
IFX_INLINE void IfxEray_setTransmitWakeupTimes(Ifx_ERAY *eray, uint8 transmitWakeupRepetitions, uint8 transmitWakeupIdleTime, uint8 transmitWakeupLowTime);

/** \brief Configures transmitted frames for startup and synchronization.
 * \param eray pointer to ERAY module registers.
 * \param startupFrameTransmitted whether startup Frame transmitted or not.
 * \param synchFrameTransmitted whether synch Frame transmitted or not.
 * \return None
 */
IFX_INLINE void IfxEray_setTransmittedFrames(Ifx_ERAY *eray, boolean startupFrameTransmitted, boolean synchFrameTransmitted);

/** \brief Sets the transmit buffer number.
 * \param eray pointer to ERAY module registers.
 * \param bufferIndex buffer number in which frame is sent.
 * \return None
 */
IFX_INLINE void IfxEray_setTxBufferNumber(Ifx_ERAY *eray, uint8 bufferIndex);

/** \brief Swaps the shadow and Host output registers.
 * \param eray pointer to ERAY module registers.
 * \param swapRequested whether swap is requested or not.
 * \return None
 */
IFX_INLINE void IfxEray_setViewData(Ifx_ERAY *eray, boolean swapRequested);

/** \brief Sets the cluster wakeup channel.
 * \param eray pointer to ERAY module registers.
 * \param wakeupPatternChannel cluster wakeup pattern channel.
 * \return None
 */
IFX_INLINE void IfxEray_setWakeupPatternChannel(Ifx_ERAY *eray, IfxEray_WakeupChannel wakeupPatternChannel);

/** \} */

/** \addtogroup IfxLld_Eray_Std_Operative
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief requests to receive data from message buffer.
 * \param eray pointer to ERAY module registers.
 * \param dataReceived whether data to be received or not.
 * \return None
 */
IFX_INLINE void IfxEray_receiveData(Ifx_ERAY *eray, boolean dataReceived);

/** \brief sets the bit to send data in  frame.
 * \param eray pointer to ERAY module registers.
 * \param dataTransfered whether data transfered or not.
 * \return None
 */
IFX_INLINE void IfxEray_sendData(Ifx_ERAY *eray, boolean dataTransfered);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Calculate and returns the CRC for frame.
 * \param payloadLength payload length configured for frame.
 * \param frameId slot id
 * \param startupFrameIndicator whether startup frame is indicated or not.
 * \param syncFrameIndicator whether sync frame is indicated or not.
 * \return calculated CRC value.
 */
IFX_EXTERN uint16 IfxEray_calcHeaderCrc(uint8 payloadLength, uint16 frameId, boolean startupFrameIndicator, boolean syncFrameIndicator);

/** \brief Reads the received data from output registers.
 * \param eray pointer to ERAY module registers.
 * \param data pointer to received data buffer.
 * \param payloadLength payload length received in a frame.
 * \return None
 */
IFX_EXTERN void IfxEray_readData(Ifx_ERAY *eray, uint32 *data, uint8 payloadLength);

/** \brief Reads header and data from output buffers.
 * \param eray pointer to ERAY module registers.
 * \param header header received in a frame.
 * \param data data received in a frame.
 * \param maxPayloadLength maximum payload length received in a frame.
 * \return None
 */
IFX_EXTERN void IfxEray_readFrame(Ifx_ERAY *eray, IfxEray_ReceivedHeader *header, uint32 *data, Ifx_SizeT maxPayloadLength);

/** \brief Writes header and data to Input buffers and set the slots.
 * \param eray pointer to ERAY module registers.
 * \param header Header section of message buffer.
 * \param data data section of message buffer.
 * \param slotConfig pointer slot allocation configuration structure.
 * \return None
 */
IFX_EXTERN void IfxEray_setSlot(Ifx_ERAY *eray, const IfxEray_Header *header, const uint32 *data, const IfxEray_SlotConfig *slotConfig);

/** \brief Writes data section of a frame to input data registers.
 * \param eray pointer to ERAY module registers.
 * \param data data segment in a frame.
 * \param payloadLength payload length configured for slot buffer.
 * \return None
 */
IFX_EXTERN void IfxEray_writeData(Ifx_ERAY *eray, const uint32 *data, uint8 payloadLength);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Gets the FIFO index.
 * \param eray pointer to ERAY module registers.
 * \return FIFO buffer index.
 */
IFX_INLINE uint8 IfxEray_getFifoIndex(Ifx_ERAY *eray);

/** \brief Configure the Module to Hard/Soft suspend mode.
 * Note: The api works only when the OCDS is enabled and in Supervisor Mode. When OCDS is disabled the OCS suspend control is ineffective.
 * \param eray Pointer to ERAY module registers
 * \param mode Module suspend mode
 * \return None
 */
IFX_INLINE void IfxEray_setSuspendMode(Ifx_ERAY *eray, IfxEray_SuspendMode mode);

/** \brief Provides functionality for both setting of pin direction as input and configuring pad driver.
 * \param rx the RX Pin which should be configured.
 * \param rxMode the pin input mode which should be configured.
 * \param padDriver Pad Driver Configuration
 * \return None
 */
IFX_INLINE void IfxEray_initRxPinWithPadLevel(const IfxEray_Rxd_In *rx, IfxPort_InputMode rxMode, IfxPort_PadDriver padDriver);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxEray_clearErrorFlag(Ifx_ERAY *eray, IfxEray_ClearErrorFlag errorFlag)
{
    eray->EIR.U = errorFlag;
}


IFX_INLINE void IfxEray_clearStatusFlag(Ifx_ERAY *eray, IfxEray_ClearStatusFlag statusFlag)
{
    eray->SIR.U = statusFlag;
}


IFX_INLINE void IfxEray_disableModule(Ifx_ERAY *eray)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    //disable the module
    eray->CLC.B.DISR = 1;
    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE void IfxEray_enableModule(Ifx_ERAY *eray)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    // Run Mode Clock divider to 1
    //enable the module
    eray->CLC.U = 0x00000100;

    // ensure that write access finished before leaving this function
    if (eray->CLC.U)
    {}

    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE Ifx_ERAY_EIR IfxEray_getErrorInterrupts(Ifx_ERAY *eray)
{
    Ifx_ERAY_EIR interruptFlags;
    interruptFlags.U = eray->EIR.U;
    return interruptFlags;
}


IFX_INLINE uint8 IfxEray_getFifoIndex(Ifx_ERAY *eray)
{
    return eray->MRC.B.FFB;
}


IFX_INLINE Ifx_ERAY_FSR IfxEray_getFifoStatus(Ifx_ERAY *eray)
{
    Ifx_ERAY_FSR fifoStatus;
    fifoStatus.U = eray->FSR.U;
    return fifoStatus;
}


IFX_INLINE boolean IfxEray_getInputBufferBusyHostStatus(Ifx_ERAY *eray)
{
    return (eray->IBCR.B.IBSYH == 1) ? TRUE : FALSE;
}


IFX_INLINE uint8 IfxEray_getInputBufferBusyShadowStatus(Ifx_ERAY *eray)
{
    return (eray->IBCR.B.IBSYS == 1) ? TRUE : FALSE;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInputBufferBusySrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].IBUSY;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInterruptLine0SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].INT[0];
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getInterruptLine1SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].INT[1];
}


IFX_INLINE boolean IfxEray_getMessageBufferInterruptStatus(Ifx_ERAY *eray, uint8 messageBuffer)
{
    uint8           ix                     = messageBuffer / 32;
    uint32          mask                   = 1 << (messageBuffer % 32);
    Ifx_ERAY_MBSC1 *mbscSFR                = (Ifx_ERAY_MBSC1 *)((uint32)&eray->MBSC1 + 4 * ix);
    boolean         messageBufferInterrupt = (mbscSFR->U & mask) ? TRUE : FALSE;

    return messageBufferInterrupt;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getMessageBufferStatus0SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].MBSC[0];
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getMessageBufferStatus1SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].MBSC[1];
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getNewDataInterrupt0SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].NDAT[0];
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getNewDataInterrupt1SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].NDAT[1];
}


IFX_INLINE boolean IfxEray_getNewDataInterruptStatus(Ifx_ERAY *eray, uint8 ndat)
{
    uint8           ix            = ndat / 32;
    uint32          mask          = 1 << (ndat % 32);
    Ifx_ERAY_NDAT1 *ndatSFR       = (Ifx_ERAY_NDAT1 *)((uint32)&eray->NDAT1 + 4 * ix);
    boolean         ndatInterrupt = (ndatSFR->U & mask) ? TRUE : FALSE;

    return ndatInterrupt;
}


IFX_INLINE uint8 IfxEray_getOutputBuffer(Ifx_ERAY *eray)
{
    return eray->OBCR.B.OBRH;
}


IFX_INLINE boolean IfxEray_getOutputBufferBusyShadowStatus(Ifx_ERAY *eray)
{
    return (eray->OBCR.B.OBSYS == 1) ? TRUE : FALSE;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getOutputBufferBusySrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].OBUSY;
}


IFX_INLINE IfxEray_PocState IfxEray_getPocState(Ifx_ERAY *eray)
{
    return (IfxEray_PocState)eray->CCSV.B.POCS;
}


IFX_INLINE Ifx_ERAY_SIR IfxEray_getStatusInterrupts(Ifx_ERAY *eray)
{
    Ifx_ERAY_SIR interruptFlags;
    interruptFlags.U = eray->SIR.U;
    return interruptFlags;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getTimerInterrupt0SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].TINT[0];
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxEray_getTimerInterrupt1SrcPtr(Ifx_ERAY *eray)
{
    return &MODULE_SRC.ERAY.ERAY[0].TINT[1];
}


IFX_INLINE IfxEray_WakeupChannel IfxEray_getWakeupPatternReceivedChannel(Ifx_ERAY *eray)
{
    IfxEray_WakeupChannel wakeupChannel = IfxEray_WakeupChannel_a;

    if (eray->SIR.B.WUPA == 1)
    {
        wakeupChannel = IfxEray_WakeupChannel_a;
    }
    else if (eray->SIR.B.WUPB == 1)
    {
        wakeupChannel = IfxEray_WakeupChannel_b;
    }

    return wakeupChannel;
}


IFX_INLINE void IfxEray_initRxPin(const IfxEray_Rxd_In *rx, IfxPort_InputMode rxMode)
{
    IfxPort_setPinModeInput(rx->pin.port, rx->pin.pinIndex, rxMode);

    if (rx->nodeId == IfxEray_NodeId_a)
    {
        rx->module->CUST1.B.RISA = rx->select;
    }
    else
    {
        rx->module->CUST1.B.RISB = rx->select;
    }
}


IFX_INLINE void IfxEray_initTxEnPin(const IfxEray_Txen_Out *txEn, IfxPort_OutputMode txEnMode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeOutput(txEn->pin.port, txEn->pin.pinIndex, txEnMode, txEn->select);
    IfxPort_setPinPadDriver(txEn->pin.port, txEn->pin.pinIndex, padDriver);
}


IFX_INLINE void IfxEray_initTxPin(const IfxEray_Txd_Out *tx, IfxPort_OutputMode txMode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeOutput(tx->pin.port, tx->pin.pinIndex, txMode, tx->select);
    IfxPort_setPinPadDriver(tx->pin.port, tx->pin.pinIndex, padDriver);
}


IFX_INLINE boolean IfxEray_isModuleSuspended(Ifx_ERAY *eray)
{
    Ifx_ERAY_OCS ocs;

    // read the status
    ocs.U = eray->OCS.U;

    // return the status
    return ocs.B.SUSSTA;
}


IFX_INLINE void IfxEray_receiveData(Ifx_ERAY *eray, boolean dataReceived)
{
    eray->OBCM.B.RDSS = dataReceived;
}


IFX_INLINE void IfxEray_receiveHeader(Ifx_ERAY *eray, boolean headerReceived)
{
    eray->OBCM.B.RHSS = headerReceived;
}


IFX_INLINE void IfxEray_sendData(Ifx_ERAY *eray, boolean dataTransfered)
{
    eray->IBCM.B.LDSH = dataTransfered;
}


IFX_INLINE void IfxEray_sendHeader(Ifx_ERAY *eray, boolean headerTransfered)
{
    eray->IBCM.B.LHSH = headerTransfered;
}


IFX_INLINE void IfxEray_setActiveCyclePairs(Ifx_ERAY *eray, uint8 numberOfCyclePairsForActive)
{
    eray->SUCC1.B.PTA = numberOfCyclePairsForActive;
}


IFX_INLINE void IfxEray_setAutoDelayBuffers(Ifx_ERAY *eray)
{
    eray->CUST1.B.IEN = 1;
    eray->CUST1.B.OEN = 1;
    eray->CUST3.U     = 0xFFFFFFFF;
}


IFX_INLINE void IfxEray_setBaudrate(Ifx_ERAY *eray, IfxEray_Baudrate baudrate)
{
    eray->PRTC1.B.BRP = baudrate;
}


IFX_INLINE void IfxEray_setBufferReconfigSecure(Ifx_ERAY *eray, uint8 secureValue)
{
    eray->MRC.B.SEC = secureValue;
}


IFX_INLINE void IfxEray_setChannelAInitialOffsets(Ifx_ERAY *eray, uint8 channelAMicrotickInitialOffset, uint8 channelAMacrotickInitialOffset)
{
    eray->GTUC03.B.UIOA = channelAMicrotickInitialOffset;
    eray->GTUC03.B.MIOA = channelAMacrotickInitialOffset;
}


IFX_INLINE void IfxEray_setChannelBInitialOffsets(Ifx_ERAY *eray, uint8 channelBMicrotickInitialOffset, uint8 channelBMacrotickInitialOffset)
{
    eray->GTUC03.B.UIOB = channelBMicrotickInitialOffset;
    eray->GTUC03.B.MIOB = channelBMacrotickInitialOffset;
}


IFX_INLINE void IfxEray_setChannelsReceiveDelay(Ifx_ERAY *eray, uint8 channelAReceptionDelay, uint8 channelBReceptionDelay)
{
    eray->GTUC05.B.DCA = channelAReceptionDelay;
    eray->GTUC05.B.DCB = channelBReceptionDelay;
}


IFX_INLINE void IfxEray_setClockCorrectionCycles(Ifx_ERAY *eray, uint8 clockCorrectionCyclesPassive, uint8 clockCorrectionCyclesHalt)
{
    Ifx_ERAY_SUCC3 succ3;
    succ3.U       = 0;
    succ3.B.WCP   = clockCorrectionCyclesPassive;
    succ3.B.WCF   = clockCorrectionCyclesHalt;
    eray->SUCC3.U = succ3.U;
}


IFX_INLINE void IfxEray_setClockSynchErrorHalt(Ifx_ERAY *eray, boolean clockSyncErrorHalt)
{
    eray->SUCC1.B.HCSE = clockSyncErrorHalt;
}


IFX_INLINE void IfxEray_setClusterDriftValues(Ifx_ERAY *eray, uint8 clusterDrift, uint16 maxDriftOffset)
{
    eray->GTUC05.B.CDD = clusterDrift;
    eray->GTUC06.B.MOD = maxDriftOffset;
}


IFX_INLINE void IfxEray_setClusterStartupDeviation(Ifx_ERAY *eray, uint16 acceptedStartupDeviation)
{
    eray->GTUC06.B.ASR = acceptedStartupDeviation;
}


IFX_INLINE void IfxEray_setCollisionAvoidanceDuration(Ifx_ERAY *eray, uint8 collisionAvoidanceDuration)
{
    eray->PRTC1.B.CASM = collisionAvoidanceDuration;
}


IFX_INLINE void IfxEray_setCycleDurationMacroticks(Ifx_ERAY *eray, uint16 macroticks)
{
    eray->GTUC02.B.MPC = macroticks;
}


IFX_INLINE void IfxEray_setCycleDurationMicroticks(Ifx_ERAY *eray, uint32 microticks)
{
    eray->GTUC01.U = microticks;
}


IFX_INLINE void IfxEray_setDecodingCorrectionValue(Ifx_ERAY *eray, uint8 decodingCorrection)
{
    eray->GTUC05.B.DEC = decodingCorrection;
}


IFX_INLINE void IfxEray_setDynamicSlots(Ifx_ERAY *eray, uint8 dynamicSlotLength, uint16 dynamicSlotCount, IfxEray_IdleDynamicSlots idleDynamicSlots)
{
    eray->GTUC08.B.MSL = dynamicSlotLength;
    eray->GTUC08.B.NMS = dynamicSlotCount;
    eray->GTUC09.B.DSI = idleDynamicSlots;
}


IFX_INLINE void IfxEray_setExternalCorrectionControl(Ifx_ERAY *eray, IfxEray_ExternalOffset externalOffset, IfxEray_ExternalRate externalRate)
{
    eray->GTUC11.B.EOCC = externalOffset;
    eray->GTUC11.B.ERCC = externalRate;
}


IFX_INLINE void IfxEray_setExternalCorrectionValues(Ifx_ERAY *eray, IfxEray_ExternalOffsetCorrection externalOffsetCorrection, IfxEray_ExternalRateCorrection externalRateCorrection)
{
    eray->GTUC11.B.EOC = externalOffsetCorrection;
    eray->GTUC11.B.ERC = externalRateCorrection;
}


IFX_INLINE void IfxEray_setFifoBufferStartIndex(Ifx_ERAY *eray, uint8 fifoBufferStartIndex)
{
    // Buffers from MRC.B.FFB to MRC.B.LCB are assigned FIFO
    eray->MRC.B.FFB = fifoBufferStartIndex;
}


IFX_INLINE void IfxEray_setFifoFilterConfigurations(Ifx_ERAY *eray, uint16 rejectedFrameId, uint8 filteredCycleNumber, boolean fifoNullFramesRejected, uint16 frameIdFilter)
{
    eray->FRF.B.FID   = rejectedFrameId;
    eray->FRF.B.CYF   = filteredCycleNumber;
    eray->FRF.B.RNF   = fifoNullFramesRejected;
    eray->FRFM.B.MFID = frameIdFilter;
}


IFX_INLINE void IfxEray_setFifoMessageBufferConfigurations(Ifx_ERAY *eray, IfxEray_ReceiveChannel receiveChannel, boolean staticFifoDisabled, uint8 fifoDepth)
{
    eray->FRF.B.CH  = receiveChannel;
    eray->FRF.B.RSS = staticFifoDisabled;
    eray->FCL.U     = fifoDepth;
}


IFX_INLINE void IfxEray_setFirstDynamicBuffer(Ifx_ERAY *eray, uint8 firstDynamicBuffer)
{
    // 0: No static bufers, 0x01...0x7F: 0 to (MRC.B.FDB - 1) are static buffers, 0x80...0xFF:No dynamic buffers
    eray->MRC.B.FDB = firstDynamicBuffer;
}


IFX_INLINE void IfxEray_setListenTimeOuts(Ifx_ERAY *eray, uint32 listenTimeOut, IfxEray_ListenTimeOutNoise listenTimeOutNoise)
{
    Ifx_ERAY_SUCC2 succ2;
    succ2.U       = 0;
    succ2.B.LT    = listenTimeOut;
    succ2.B.LTN   = listenTimeOutNoise;
    eray->SUCC2.U = succ2.U;
}


IFX_INLINE void IfxEray_setMaxColdStartAttempts(Ifx_ERAY *eray, uint8 maxColdStartAttempts)
{
    eray->SUCC1.B.CSA = maxColdStartAttempts;
}


IFX_INLINE void IfxEray_setMaxCorrectionValues(Ifx_ERAY *eray, uint16 maxOffsetCorrection, uint16 maxRateCorrection)
{
    eray->GTUC10.B.MOC = maxOffsetCorrection;
    eray->GTUC10.B.MRC = maxRateCorrection;
}


IFX_INLINE void IfxEray_setMaxSynchFrames(Ifx_ERAY *eray, IfxEray_MaxSynchFrames maxSyncFrames)
{
    eray->GTUC02.B.SNM = maxSyncFrames;
}


IFX_INLINE void IfxEray_setMessageBufferCount(Ifx_ERAY *eray, uint8 numberOfMessageBuffers)
{
    eray->MRC.B.LCB = numberOfMessageBuffers - 1;
}


IFX_INLINE void IfxEray_setMessageHandlerConfigurations(Ifx_ERAY *eray, uint8 staticFramepayload, uint8 latestTransmissionStart)
{
    Ifx_ERAY_MHDC mhdc;
    mhdc.U       = 0;
    mhdc.B.SFDL  = staticFramepayload;
    mhdc.B.SLT   = latestTransmissionStart;
    eray->MHDC.U = mhdc.U;
}


IFX_INLINE void IfxEray_setNetworkStartIdleTime(Ifx_ERAY *eray, uint16 networkStartIdleTime)
{
    eray->GTUC04.B.NIT = networkStartIdleTime;
}


IFX_INLINE void IfxEray_setNetworkVectorLength(Ifx_ERAY *eray, uint32 networkVectorLength)
{
    eray->NEMC.U = networkVectorLength;
}


IFX_INLINE void IfxEray_setNodeChannels(Ifx_ERAY *eray, boolean channelAConnectedNode, boolean channelBConnectedNode)
{
    eray->SUCC1.B.CCHA = channelAConnectedNode;
    eray->SUCC1.B.CCHB = channelBConnectedNode;
}


IFX_INLINE void IfxEray_setOffsetCorrection(Ifx_ERAY *eray, uint16 correctionOffset)
{
    eray->GTUC04.B.OCS = correctionOffset;
}


IFX_INLINE void IfxEray_setReceiveRequest(Ifx_ERAY *eray, boolean receiveRequested)
{
    eray->OBCR.B.REQ = receiveRequested;
}


IFX_INLINE void IfxEray_setReceiveWakeupTimes(Ifx_ERAY *eray, uint8 receiveWakeupTestDuration, uint8 receiveWakeupIdleTime, uint8 receiveWakeupLowTime)
{
    eray->PRTC1.B.RXW = receiveWakeupTestDuration;
    eray->PRTC2.B.RXI = receiveWakeupIdleTime;
    eray->PRTC2.B.RXL = receiveWakeupLowTime;
}


IFX_INLINE void IfxEray_setRxBufferNumber(Ifx_ERAY *eray, uint8 bufferIndex)
{
    eray->OBCR.B.OBRS = bufferIndex;
}


IFX_INLINE void IfxEray_setSleepMode(Ifx_ERAY *eray, IfxEray_SleepMode mode)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    eray->CLC.B.EDIS = mode;
    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE void IfxEray_setSlotActionPoints(Ifx_ERAY *eray, uint8 staticActionPoint, uint8 dynamicActionPoint)
{
    eray->GTUC09.B.MAPO = dynamicActionPoint;
    eray->GTUC09.B.APO  = staticActionPoint;
}


IFX_INLINE void IfxEray_setStaticSlots(Ifx_ERAY *eray, uint16 staticSlotLength, uint16 staticSlotsCount)
{
    eray->GTUC07.B.SSL = staticSlotLength;
    eray->GTUC07.B.NSS = staticSlotsCount;
}


IFX_INLINE void IfxEray_setStrobePosition(Ifx_ERAY *eray, IfxEray_StrobePosition strobePosition)
{
    eray->PRTC1.B.SPP = strobePosition;
}


IFX_INLINE void IfxEray_setSuspendMode(Ifx_ERAY *eray, IfxEray_SuspendMode mode)
{
    Ifx_ERAY_OCS ocs;

    // remove protection and configure the suspend mode.
    ocs.B.SUS_P = 1;
    ocs.B.SUS   = mode;
    eray->OCS.U = ocs.U;
}


IFX_INLINE void IfxEray_setSymbolChannels(Ifx_ERAY *eray, boolean channelASymbolTransmitted, boolean channelBSymbolTransmitted)
{
    eray->SUCC1.B.MTSA = channelASymbolTransmitted;
    eray->SUCC1.B.MTSB = channelBSymbolTransmitted;
}


IFX_INLINE void IfxEray_setTransmissionSlotMode(Ifx_ERAY *eray, IfxEray_TransmissionSlotMode transmissionSlotMode)
{
    eray->SUCC1.B.TSM = transmissionSlotMode;
}


IFX_INLINE void IfxEray_setTransmissionStartTime(Ifx_ERAY *eray, uint16 transmissionStartTime)
{
    eray->PRTC1.B.TSST = transmissionStartTime;
}


IFX_INLINE void IfxEray_setTransmitRequest(Ifx_ERAY *eray, boolean transferRequested)
{
    eray->IBCM.B.STXRH = transferRequested;
}


IFX_INLINE void IfxEray_setTransmitWakeupTimes(Ifx_ERAY *eray, uint8 transmitWakeupRepetitions, uint8 transmitWakeupIdleTime, uint8 transmitWakeupLowTime)
{
    eray->PRTC1.B.RWP = transmitWakeupRepetitions;
    eray->PRTC2.B.TXI = transmitWakeupIdleTime;
    eray->PRTC2.B.TXL = transmitWakeupLowTime;
}


IFX_INLINE void IfxEray_setTransmittedFrames(Ifx_ERAY *eray, boolean startupFrameTransmitted, boolean synchFrameTransmitted)
{
    eray->SUCC1.B.TXST = startupFrameTransmitted;
    eray->SUCC1.B.TXSY = synchFrameTransmitted;
}


IFX_INLINE void IfxEray_setTxBufferNumber(Ifx_ERAY *eray, uint8 bufferIndex)
{
    eray->IBCR.B.IBRH = bufferIndex;
}


IFX_INLINE void IfxEray_setViewData(Ifx_ERAY *eray, boolean swapRequested)
{
    eray->OBCR.B.VIEW = swapRequested;
}


IFX_INLINE void IfxEray_setWakeupPatternChannel(Ifx_ERAY *eray, IfxEray_WakeupChannel wakeupPatternChannel)
{
    eray->SUCC1.B.WUCS = wakeupPatternChannel;
}


IFX_INLINE void IfxEray_waitForPocState(Ifx_ERAY *eray, IfxEray_PocState pocState)
{
    while (eray->CCSV.B.POCS != (uint8)pocState)
    {}
}


IFX_INLINE void IfxEray_initRxPinWithPadLevel(const IfxEray_Rxd_In *rx, IfxPort_InputMode rxMode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeInput(rx->pin.port, rx->pin.pinIndex, rxMode);
    IfxPort_setPinPadDriver(rx->pin.port, rx->pin.pinIndex, padDriver);

    if (rx->nodeId == IfxEray_NodeId_a)
    {
        rx->module->CUST1.B.RISA = rx->select;
    }
    else
    {
        rx->module->CUST1.B.RISB = rx->select;
    }
}


#endif /* IFXERAY_H */
