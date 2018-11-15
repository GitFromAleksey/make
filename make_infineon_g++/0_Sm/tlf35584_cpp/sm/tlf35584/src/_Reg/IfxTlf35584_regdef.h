/**
 * \file IfxTlf35584_regdef.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Date: 2015-11-20 07:21:22 GMT
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
 * \defgroup IfxLld_Tlf35584_Bitfields Bitfields
 * \ingroup IfxLld_Tlf35584
 * 
 * \defgroup IfxLld_Tlf35584_union Register unions
 * \ingroup IfxLld_Tlf35584
 * 
 * \defgroup IfxLld_Tlf35584_struct Memory map
 * \ingroup IfxLld_Tlf35584
 */
#ifndef IFXTLF35584_REGDEF_H
#define IFXTLF35584_REGDEF_H 1
/******************************************************************************/
#include "Platform_Types.h"
#include "Compilers.h"

#define IFXTLF35584_ADDRESS_UNIT  (1)   /*Register width in byte */
#define IFXTLF35584_ADDRESS_SHIFT (0)   /* Shift required to convert byte to address unit */
typedef uint8 IfxTlf35584_Address;

/* FIXME add support for register that trigger an action on write (action write) => always write register even if value match the cache */

/******************************************************************************/
/** \addtogroup IfxLld_Tlf35584_Bitfields
 * \{  */
/** \brief ABIST control0 *R2) */
typedef struct _Ifx_TLF35584_ABIST_CTRL0_Bits
{
    uint8 START:1;                    /**< \brief [0:0] Start ABIST operation, the operation itself will\nbe started. This bit is cleared after ABIST operation has been performed (rwh) */
    uint8 PATH:1;                     /**< \brief [1:1] Select the path which should be covered by ABIST\noperation (rw) */
    uint8 SINGLE:1;                   /**< \brief [2:2] Select wether a single comparator shall be tested\nor all comparators in predefined sequence (rw) */
    uint8 INT:1;                      /**< \brief [3:3] Select wether safe state related comparator shall\nbe tested or interrupt related (rw) */
    uint8 STATUS:4;                   /**< \brief [7:4] ABIST global status information after requested\noperation has been performed, information shall only be considered\nvalid, once START bit is cleared (Bits have different reset class\nthan whole register. The Bits are reset according to *R1) ) (rh) */
} Ifx_TLF35584_ABIST_CTRL0_Bits;

/** \brief ABIST control1 *R2) */
typedef struct _Ifx_TLF35584_ABIST_CTRL1_Bits
{
    uint8 OV_TRIG:1;                  /**< \brief [0:0] Enable overvoltage trigger for secondary internal\nmonitor (rw) */
    uint8 ABIST_CLK_EN:1;             /**< \brief [1:1] Select ABIST clock to check its functionality (rw) */
    uint8 NU:6;                       /**< \brief [7:2]  (None) */
} Ifx_TLF35584_ABIST_CTRL1_Bits;

/** \brief ABIST select 0 *R2) */
typedef struct _Ifx_TLF35584_ABIST_SELECT0_Bits
{
    uint8 PREGOV:1;                   /**< \brief [0:0] Select Pre-regulator OV comparator for ABIST operation (rwh) */
    uint8 UCOV:1;                     /**< \brief [1:1] Select uC LDO OV comparator for ABIST operation (rwh) */
    uint8 STBYOV:1;                   /**< \brief [2:2] Select Standby LDO OV comparator for ABIST operation (rwh) */
    uint8 VCOREOV:1;                  /**< \brief [3:3] Select Core voltage OV comparator for ABIST operation (rwh) */
    uint8 COMOV:1;                    /**< \brief [4:4] Select COM OV comparator for ABIST operation (rwh) */
    uint8 VREFOV:1;                   /**< \brief [5:5] Select VREF OV comparator for ABIST operation (rwh) */
    uint8 TRK1OV:1;                   /**< \brief [6:6] Select TRK1 OV comparator for ABIST operation (rwh) */
    uint8 TRK2OV:1;                   /**< \brief [7:7] Select TRK2 OV comparator for ABIST operation (rwh) */
} Ifx_TLF35584_ABIST_SELECT0_Bits;

/** \brief ABIST select 1 *R2) */
typedef struct _Ifx_TLF35584_ABIST_SELECT1_Bits
{
    uint8 PREGUV:1;                   /**< \brief [0:0] Select pre regulator UV comparator for ABIST operation (rwh) */
    uint8 UCUV:1;                     /**< \brief [1:1] Select uC UV comparator for ABIST operation (rwh) */
    uint8 STBYUV:1;                   /**< \brief [2:2] Select STBY UV comparator for ABIST operation (rwh) */
    uint8 VCOREUV:1;                  /**< \brief [3:3] Select VCORE UV comparator for ABIST operation (rwh) */
    uint8 COMUV:1;                    /**< \brief [4:4] Select COM UV comparator for ABIST operation (rwh) */
    uint8 VREFUV:1;                   /**< \brief [5:5] Select VREF UV comparator for ABIST operation (rwh) */
    uint8 TRK1UV:1;                   /**< \brief [6:6] Select TRK1 UV comparator for ABIST operation (rwh) */
    uint8 TRK2UV:1;                   /**< \brief [7:7] Select TRK2 UV comparator for ABIST operation (rwh) */
} Ifx_TLF35584_ABIST_SELECT1_Bits;

/** \brief ABIST select 2 *R2) */
typedef struct _Ifx_TLF35584_ABIST_SELECT2_Bits
{
    uint8 VBATOV:1;                   /**< \brief [0:0] Supply voltage VS1/2 is too high (rwh) */
    uint8 NU:2;                       /**< \brief [2:1]  (None) */
    uint8 INTOV:1;                    /**< \brief [3:3] Internal supply OV condition (rwh) */
    uint8 BG12UV:1;                   /**< \brief [4:4] Bandgap comparator UV condition (VBG1 - 4% \xe2\x89\xa4 VBG2) (rwh) */
    uint8 BG12OV:1;                   /**< \brief [5:5] Bandgap comparator OV condition (VBG1 + 4% \xe2\x89\xa5 VBG2) (rwh) */
    uint8 BIASLOW:1;                  /**< \brief [6:6] Bias current too low (rwh) */
    uint8 BIASHI:1;                   /**< \brief [7:7] Bias current too high (rwh) */
} Ifx_TLF35584_ABIST_SELECT2_Bits;

/** \brief Buck switching frequency change *R2) */
typedef struct _Ifx_TLF35584_BCK_FREQ_CHANGE_Bits
{
    uint8 BCK_FREQ_SEL:3;             /**< \brief [2:0] BUCK switching frequency change, for hi and low\nswitching mode. New value needs to be validated via data_valid procedure (rw) */
    uint8 NU:5;                       /**< \brief [7:3]  (None) */
} Ifx_TLF35584_BCK_FREQ_CHANGE_Bits;

/** \brief Buck Frequency spread *R2) */
typedef struct _Ifx_TLF35584_BCK_FRE_SPREAD_Bits
{
    uint8 FRE_SP_THR:8;               /**< \brief [7:0] Select the percentage of frequency down-spread (rw) */
} Ifx_TLF35584_BCK_FRE_SPREAD_Bits;

/** \brief Buck main control *R2) */
typedef struct _Ifx_TLF35584_BCK_MAIN_CTRL_Bits
{
    uint8 NU:6;                       /**< \brief [5:0]  (None) */
    uint8 DATA_VALID:1;               /**< \brief [6:6] Update Command to load new parameter for stepdown\nregulator (after configuration write 1 to update and write 0 after\nBUSY flag is cleared to proceed operation) (rw) */
    uint8 BUSY:1;                     /**< \brief [7:7] DATA_VALID parameter update (rh) */
} Ifx_TLF35584_BCK_MAIN_CTRL_Bits;

/** \brief Device configuration 0  *R2) */
typedef struct _Ifx_TLF35584_DEVCFG0_Bits
{
    uint8 TRDEL:4;                    /**< \brief [3:0] Transition delay into low power states (STANDBY, SLEEP). Defined as a step\nof 100 us (rw) */
    uint8 reserved_4 : 2;             /**< \brief \internal Reserved */
    uint8 WKTIMCYC:1;                 /**< \brief [6:6] Wake timer cycle period (rw) */
    uint8 WKTIMEN:1;                  /**< \brief [7:7] Wake timer enable (rw) */
} Ifx_TLF35584_DEVCFG0_Bits;

/** \brief Device configuration 1 *R0) */
typedef struct _Ifx_TLF35584_DEVCFG1_Bits
{
    uint8 RESDEL:3;                   /**< \brief [2:0] Reset release delay time (rw) */
    uint8 NU:5;                       /**< \brief [7:3]  (None) */
} Ifx_TLF35584_DEVCFG1_Bits;

/** \brief Device configuration 2 *R2) */
typedef struct _Ifx_TLF35584_DEVCFG2_Bits
{
    uint8 ESYNEN:1;                   /**< \brief [0:0] Enable synchronization output for external switchmode\nregulator (rw) */
    uint8 ESYNPHA:1;                  /**< \brief [1:1] External synchronization output phase (rw) */
    uint8 CTHR:2;                     /**< \brief [3:2] LDO_\xc2\xb5C current monitoring threshold value (rw) */
    uint8 CMONEN:1;                   /**< \brief [4:4] LDO_\xc2\xb5C current monitor enabled when transition to\na low power state (The setting is overwritten\nin SLEEP as current monitoring is always enabled. (rw) */
    uint8 FRE:1;                      /**< \brief [5:5] Step-down converter high frequency selection (rh) */
    uint8 STU:1;                      /**< \brief [6:6] Step-up converter enable (rh) */
    uint8 EVCEN:1;                    /**< \brief [7:7] Enable of external core supply voltage (rh) */
} Ifx_TLF35584_DEVCFG2_Bits;

/** \brief Device control request *R2) */
typedef struct _Ifx_TLF35584_DEVCTRL_Bits
{
    uint8 STATEREQ:3;                 /**< \brief [2:0] "Request for device state transition. Cleared to\n000 by the HW after the request is processed. After writing a new\nstate value a user should not change the value before it's cleared\nby HW." (rwh) */
    uint8 VREFEN:1;                   /**< \brief [3:3] Enable request for reference voltage. (rw) */
    uint8 reserved_4 : 1;
    uint8 COMEN:1;                    /**< \brief [5:5] Enable request for communication LDO. (rw) */
    uint8 TRK1EN:1;                   /**< \brief [6:6] Enable request for tracker1 sensor voltage. (rw) */
    uint8 TRK2EN:1;                   /**< \brief [7:7] Enable request for tracker2 sensor voltage (rw) */
} Ifx_TLF35584_DEVCTRL_Bits;

/** \brief Device control inverted request *R2) */
typedef struct _Ifx_TLF35584_DEVCTRLN_Bits
{
    uint8 STATEREQ:3;                 /**< \brief [2:0] "Request for device state transition. Cleared to\n000 by the HW after the request is processed. After writing a new\nstate value a user should not change the value before it's cleared\nby HW." (rwh) */
    uint8 VREFEN:1;                   /**< \brief [3:3] Enable request for reference voltage. (rw) */
    uint8 reserved_4 : 1;
    uint8 COMEN:1;                    /**< \brief [5:5] Enable request for communication LDO. (rw) */
    uint8 TRK1EN:1;                   /**< \brief [6:6] Enable request for tracker1 sensor voltage. (rw) */
    uint8 TRK2EN:1;                   /**< \brief [7:7] Enable request for tracker2 sensor voltage (rw) */
} Ifx_TLF35584_DEVCTRLN_Bits;

/** \brief Device status  *R2) */
typedef struct _Ifx_TLF35584_DEVSTAT_Bits
{
    uint8 STATE:3;                    /**< \brief [2:0] Current device state (rh) */
    uint8 VREFEN:1;                   /**< \brief [3:3] Current state reference voltage enable (rh) */
    uint8 STBYEN:1;                   /**< \brief [4:4] Current state of standby LDO enable (rh) */
    uint8 COMEN:1;                    /**< \brief [5:5] Current state of Communication LDO enable (rh) */
    uint8 TRK1EN:1;                   /**< \brief [6:6] Current status of Tracker1 voltage enable (rh) */
    uint8 TRK2EN:1;                   /**< \brief [7:7] Current status of Tracker2 voltage enable (rh) */
} Ifx_TLF35584_DEVSTAT_Bits;

/** \brief Protected Functional watchdog configuration request *R2) */
typedef struct _Ifx_TLF35584_FWDCFG_Bits
{
    uint8 WDHBTP:5;                   /**< \brief [4:0] Watchdog heartbeat timer period defined as a multiple\nof  50 watchdog cycles (rwh) */
    uint8 NU:3;                       /**< \brief [7:5] not used bits shall be written as 0 and will always\nreturn 1 upon read (None) */
} Ifx_TLF35584_FWDCFG_Bits;

/** \brief Functional watchdog response command  *R2) */
typedef struct _Ifx_TLF35584_FWDRSP_Bits
{
    uint8 FWDRSP:8;                   /**< \brief [7:0] Functional watchdog response byte write command (rw) */
} Ifx_TLF35584_FWDRSP_Bits;

/** \brief Functional watchdog response command with synchronization\n*R2) */
typedef struct _Ifx_TLF35584_FWDRSPSYNC_Bits
{
    uint8 FWDRSPS:8;                  /**< \brief [7:0] Functional watchdog response byte write and heartbeat synchronization\ncommand (rw) */
} Ifx_TLF35584_FWDRSPSYNC_Bits;

/** \brief Functional watchdog status 0 *R3) */
typedef struct _Ifx_TLF35584_FWDSTAT0_Bits
{
    uint8 FWDQUEST:4;                 /**< \brief [3:0] Functional watchdog question (rh) */
    uint8 FWDRSPC:2;                  /**< \brief [5:4] Functional watchdog response counter value (rh) */
    uint8 FWDRSPOK:1;                 /**< \brief [6:6] Functional watchdog response check status (rh) */
    uint8 NU:1;                       /**< \brief [7:7]  (None) */
} Ifx_TLF35584_FWDSTAT0_Bits;

/** \brief Functional watchdog status 1 *R3) */
typedef struct _Ifx_TLF35584_FWDSTAT1_Bits
{
    uint8 FWDECNT:4;                  /**< \brief [3:0] Functional watchdog error counter value (rh) */
    uint8 NU:4;                       /**< \brief [7:4]  (None) */
} Ifx_TLF35584_FWDSTAT1_Bits;

/** \brief Global testmode *R2) */
typedef struct _Ifx_TLF35584_GTM_Bits
{
    uint8 TM:1;                       /**< \brief [0:0] Test mode status (rh) */
    uint8 NTM:1;                      /**< \brief [1:1] Test mode status inverted (rh) */
    uint8 NU:6;                       /**< \brief [7:2]  (None) */
} Ifx_TLF35584_GTM_Bits;

/** \brief Interrupt flags  *R2) */
typedef struct _Ifx_TLF35584_IF_Bits
{
    uint8 SYS:1;                      /**< \brief [0:0] System interrupt flag (rwh) */
    uint8 WK:1;                       /**< \brief [1:1]  (rwh) */
    uint8 SPI:1;                      /**< \brief [2:2] SPI interrupt flag (rwh) */
    uint8 MON:1;                      /**< \brief [3:3] Monitor interrupt flag (rwh) */
    uint8 OTW:1;                      /**< \brief [4:4] Over temperature warning interrupt flag (rwh) */
    uint8 OTF:1;                      /**< \brief [5:5] Over temperature failure interrupt flag (rwh) */
    uint8 ABIST:1;                    /**< \brief [6:6] Requested ABIST operation performed (rwh) */
    uint8 INTMISS:1;                  /**< \brief [7:7] Interrupt has not been serviced within tINT,TO time (rh) */
} Ifx_TLF35584_IF_Bits;

/** \brief Init error status flags *R2) */
typedef struct _Ifx_TLF35584_INITERR_Bits
{
    uint8 NU:2;                       /**< \brief [1:0]  (rwh) */
    uint8 VMONF:1;                    /**< \brief [2:2] Voltage monitor failure which lead to INIT (rwh) */
    uint8 WWDF:1;                     /**< \brief [3:3] Window watchdog error counter reached the error\nthreshold (rwh) */
    uint8 FWDF:1;                     /**< \brief [4:4] Functional watchdog error counter reached the error\nthreshold (rwh) */
    uint8 ERRF:1;                     /**< \brief [5:5] MCU error monitor failure (rwh) */
    uint8 SOFTRES:1;                  /**< \brief [6:6] Soft reset has been generated due to the first INIT\nfailure. i.e. The device restarts INIT phase for the 2nd time. (rwh) */
    uint8 HARDRES:1;                  /**< \brief [7:7] Hard reset has been generated due to the second\nINIT failure in row. i.e. The device restarts INIT phase for the\n3rd time. (rwh) */
} Ifx_TLF35584_INITERR_Bits;

/** \brief Monitor status flags 0 *R1) */
typedef struct _Ifx_TLF35584_MONSF0_Bits
{
    uint8 PREGSG:1;                   /**< \brief [0:0] Pre-regulator voltage short to ground status flag (rwh) */
    uint8 UCSG:1;                     /**< \brief [1:1] uC LDO short to ground status flag (rwh) */
    uint8 STBYSG:1;                   /**< \brief [2:2] Standby LDO short to ground status flag (rwh) */
    uint8 VCORESG:1;                  /**< \brief [3:3] Core voltage short to ground status flag (rwh) */
    uint8 COMSG:1;                    /**< \brief [4:4] Communication LDO short to ground status flag (rwh) */
    uint8 VREFSG:1;                   /**< \brief [5:5] Voltage reference short to ground status flag (rwh) */
    uint8 TRK1SG:1;                   /**< \brief [6:6] Tracker1 short to ground status flag (rwh) */
    uint8 TRK2SG:1;                   /**< \brief [7:7] Tracker2 short to ground status flag (rwh) */
} Ifx_TLF35584_MONSF0_Bits;

/** \brief Monitor status flags 1 *R1) */
typedef struct _Ifx_TLF35584_MONSF1_Bits
{
    uint8 PREGOV:1;                   /**< \brief [0:0] Pre-regulator voltage over voltage status flag (rwh) */
    uint8 UCOV:1;                     /**< \brief [1:1] uC LDO over voltage status flag (rwh) */
    uint8 STBYOV:1;                   /**< \brief [2:2] Standby LDO over voltage status flag (rwh) */
    uint8 VCOREOV:1;                  /**< \brief [3:3] Core voltage over voltage status flag (rwh) */
    uint8 COMOV:1;                    /**< \brief [4:4] Communication LDO over voltage status flag (rwh) */
    uint8 VREFOV:1;                   /**< \brief [5:5] Voltage reference over voltage status flag (rwh) */
    uint8 TRK1OV:1;                   /**< \brief [6:6] Tracker1 over voltage status flag (rwh) */
    uint8 TRK2OV:1;                   /**< \brief [7:7] Tracker2 over voltage status flag (rwh) */
} Ifx_TLF35584_MONSF1_Bits;

/** \brief Monitor status flags 2 *R2) */
typedef struct _Ifx_TLF35584_MONSF2_Bits
{
    uint8 PREGUV:1;                   /**< \brief [0:0] Pre-regulator voltage under voltage status flag (rwh) */
    uint8 UCUV:1;                     /**< \brief [1:1] uC LDO under voltage status flag (rwh) */
    uint8 STBYUV:1;                   /**< \brief [2:2] Standby LDO under voltage status flag (rwh) */
    uint8 VCOREUV:1;                  /**< \brief [3:3] Core voltage under voltage status flag (rwh) */
    uint8 COMUV:1;                    /**< \brief [4:4] Communication LDO under voltage status flag (rwh) */
    uint8 VREFUV:1;                   /**< \brief [5:5] Voltage reference under voltage status flag (rwh) */
    uint8 TRK1UV:1;                   /**< \brief [6:6] Tracker1 under voltage status flag (rwh) */
    uint8 TRK2UV:1;                   /**< \brief [7:7] Tracker2 under voltage status flag (rwh) */
} Ifx_TLF35584_MONSF2_Bits;

/** \brief Monitor status flags 3 *R1) */
typedef struct _Ifx_TLF35584_MONSF3_Bits
{
    uint8 VBATOV:1;                   /**< \brief [0:0] Supply voltage VS1/2 is too high (rwh) */
    uint8 NU:3;                       /**< \brief [3:1]  (None) */
    uint8 BG12UV:1;                   /**< \brief [4:4] Bandgap comparator UV condition (VBG1 - 4% \xe2\x89\xa4 VBG2) (rwh) */
    uint8 BG12OV:1;                   /**< \brief [5:5] Bandgap comparator OV condition (VBG1 + 4% \xe2\x89\xa5 VBG2) (rwh) */
    uint8 BIASLOW:1;                  /**< \brief [6:6] Bias current too low (rwh) */
    uint8 BIASHI:1;                   /**< \brief [7:7] Bias current too high (rwh) */
} Ifx_TLF35584_MONSF3_Bits;

/** \brief Over temperature failure status flags *R1) */
typedef struct _Ifx_TLF35584_OTFAIL_Bits
{
    uint8 PREG:1;                     /**< \brief [0:0] Pre-regulator over temperature (rwh) */
    uint8 UC:1;                       /**< \brief [1:1] uC LDO over temperature (rwh) */
    uint8 NU:2;                       /**< \brief [3:2]  (None) */
    uint8 COM:1;                      /**< \brief [4:4] Communication LDO over temperature (rwh) */
    uint8 reserved_5:2;               /**< \brief [6:5] \internal Reserved */
    uint8 MON:1;                      /**< \brief [7:7] Monitoring over temperature (rwh) */
} Ifx_TLF35584_OTFAIL_Bits;

/** \brief Over temperature warning status flags  *R2) */
typedef struct _Ifx_TLF35584_OTWRNSF_Bits
{
    uint8 PREG:1;                     /**< \brief [0:0] Pre-regulator over temperature warning (rwh) */
    uint8 UC:1;                       /**< \brief [1:1] uC LCO over temperature warning (rwh) */
    uint8 STDBY:1;                    /**< \brief [2:2] Standby LDO over load (over current for more than\n1ms) (rwh) */
    uint8 NU:1;                       /**< \brief [3:3]  (None) */
    uint8 COM:1;                      /**< \brief [4:4] Communication LDO over temperature warning (rwh) */
    uint8 VREF:1;                     /**< \brief [5:5] Voltage reference over load (over current for more\nthan 1ms) (rwh) */
    uint8 reserved_5:2;               /**< \brief [7:6] \internal Reserved */
} Ifx_TLF35584_OTWRNSF_Bits;

/** \brief Protection register  *R2) */
typedef struct _Ifx_TLF35584_PROTCFG_Bits
{
    uint8 KEY:8;                      /**< \brief [7:0] Protection register to control write access to protected\nregisters. (rw) */
} Ifx_TLF35584_PROTCFG_Bits;

/** \brief Protection status  *R1) */
typedef struct _Ifx_TLF35584_PROTSTAT_Bits
{
    uint8 LOCK:1;                     /**< \brief [0:0] Protected register lock status (rh) */
    uint8 reserved_1 : 3;
    uint8 KEY1OK:1;                   /**< \brief [4:4] Information about validity of the 1st received protection\nkey byte (rh) */
    uint8 KEY2OK:1;                   /**< \brief [5:5] Information about validity of the 2nd received protection\nkey byte (rh) */
    uint8 KEY3OK:1;                   /**< \brief [6:6] Information about validity of the 3rd received protection\nkey byte (rh) */
    uint8 KEY4OK:1;                   /**< \brief [7:7] Information about validity of the 4th received protection\nkey byte (rh) */
} Ifx_TLF35584_PROTSTAT_Bits;

/** \brief Functional watchdog configuration status *R3) */
typedef struct _Ifx_TLF35584_RFWDCFG_Bits
{
    uint8 WDHBTP:5;                   /**< \brief [4:0] Current configuration of watchdog heartbeat timer\nperiod defined as a multiple of  50 watchdog cycles (rh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_RFWDCFG_Bits;

/** \brief System  configuration 0 status *R0) */
typedef struct _Ifx_TLF35584_RSYSPCFG0_Bits
{
    uint8 STBYEN:1;                   /**< \brief [0:0] Current configuration for standby LDO. Valid for\nall device states except FAILSAFE (rh) */
    uint8 NU:7;                       /**< \brief [7:1]  (None) */
} Ifx_TLF35584_RSYSPCFG0_Bits;

/** \brief System configuration 1 status  *R3) */
typedef struct _Ifx_TLF35584_RSYSPCFG1_Bits
{
    uint8 ERRREC:2;                   /**< \brief [1:0] ERR pin monitor recovery time (rh) */
    uint8 ERRRECEN:1;                 /**< \brief [2:2] ERR pin monitor recovery enable (rh) */
    uint8 ERREN:1;                    /**< \brief [3:3] Enable ERR pin monitor (rh) */
    uint8 ERRSLPEN:1;                 /**< \brief [4:4]  (rh) */
    uint8 SS2DEL:3;                   /**< \brief [7:5] Safe state 2 delay (Bits have different reset class\nthan whole register. The Bits are reset according to *R1) ) (rh) */
} Ifx_TLF35584_RSYSPCFG1_Bits;

/** \brief Watchdog configuration 0 status *R3) */
typedef struct _Ifx_TLF35584_RWDCFG0_Bits
{
    uint8 WDCYC:1;                    /**< \brief [0:0] Current configuration of watchdog cycle time (rh) */
    uint8 WWDTSEL:1;                  /**< \brief [1:1] Current configuration of window watchdog trigger\nselection. This is ignored when window watchdog is disabled. (rh) */
    uint8 FWDEN:1;                    /**< \brief [2:2] Current configuration of functional watchdog (rh) */
    uint8 WWDEN:1;                    /**< \brief [3:3] Current configuration of window watchdog (rh) */
    uint8 WWDETHR:4;                  /**< \brief [7:4] Current configuration of window watchdog error threshold.\nNumber of WWD errors to generate CPU reset and enter into INIT state (rh) */
} Ifx_TLF35584_RWDCFG0_Bits;

/** \brief Watchdog configuration 1 status *R3) */
typedef struct _Ifx_TLF35584_RWDCFG1_Bits
{
    uint8 FWDETHR:4;                  /**< \brief [3:0] Current configuration of functional watchdog error\nthreshold. Number of FWD errors to enter into FAILSAFE condition. (rh) */
    uint8 WDSLPEN:1;                  /**< \brief [4:4]  (rh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_RWDCFG1_Bits;

/** \brief Window watchdog configuration 0 status *R3) */
typedef struct _Ifx_TLF35584_RWWDCFG0_Bits
{
    uint8 CW:5;                       /**< \brief [4:0] Current configuration of WWD close window defined\nas a multiple of 50 watchdog cycles (rh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_RWWDCFG0_Bits;

/** \brief Window watchdog configuration 1 status *R3) */
typedef struct _Ifx_TLF35584_RWWDCFG1_Bits
{
    uint8 OW:5;                       /**< \brief [4:0] Current configuration of WWD open window time defined\nas a multiple 50 wd cycles (rh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_RWWDCFG1_Bits;

/** \brief SPI status flags *R2) */
typedef struct _Ifx_TLF35584_SPISF_Bits
{
    uint8 PARE:1;                     /**< \brief [0:0] Parity error in SPI frame (rwh) */
    uint8 LENE:1;                     /**< \brief [1:1] Invalid frame length, number of detected SPI clock\ncycles different than 16 (rwh) */
    uint8 ADDRE:1;                    /**< \brief [2:2] Invalid address in SPI frame (rwh) */
    uint8 DURE:1;                     /**< \brief [3:3] Error in duration of SPI transaction, SCS low for\nmore than 2 ms (rwh) */
    uint8 LOCK:1;                     /**< \brief [4:4] Error during LOCK/UNLOCK procedure (rwh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_SPISF_Bits;

/** \brief Failure status flags *R1) */
typedef struct _Ifx_TLF35584_SYSFAIL_Bits
{
    uint8 VOLTSELERR:1;               /**< \brief [0:0] Double Bit error on voltage selection, device entered\nFAILSAFE state (rwh) */
    uint8 OTF:1;                      /**< \brief [1:1] Over temperature failure (rwh) */
    uint8 VMONF:1;                    /**< \brief [2:2] Voltage monitor failure (rwh) */
    uint8 NU:3;                       /**< \brief [5:3]  (None) */
    uint8 ABISTERR:1;                 /**< \brief [6:6] ABIST operation interrupted by any fault/event which\nis not part of ABIST. (rwh) */
    uint8 INITF:1;                    /**< \brief [7:7] INIT failure due to the third INIT failure in row.\ni.e. The device restarts INIT phase from FAILSAFE. (rwh) */
} Ifx_TLF35584_SYSFAIL_Bits;

/** \brief Protected System configuration request 0 *R1) */
typedef struct _Ifx_TLF35584_SYSPCFG0_Bits
{
    uint8 STBYEN:1;                   /**< \brief [0:0] Enable request for standby LDO. Valid for all device\nstates except FAILSAFE (rwh) */
    uint8 NU:7;                       /**< \brief [7:1] not used bits shall be written as 0 and will always\nreturn 1 upon read (None) */
} Ifx_TLF35584_SYSPCFG0_Bits;

/** \brief Protected System configuration request 1 *R2) */
typedef struct _Ifx_TLF35584_SYSPCFG1_Bits
{
    uint8 ERRREC:2;                   /**< \brief [1:0] ERR pin monitor recovery time (rwh) */
    uint8 ERRRECEN:1;                 /**< \brief [2:2] ERR pin monitor recovery enable (rwh) */
    uint8 ERREN:1;                    /**< \brief [3:3] Enable ERR pin monitor (rwh) */
    uint8 ERRSLPEN:1;                 /**< \brief [4:4]  (rwh) */
    uint8 SS2DEL:3;                   /**< \brief [7:5] Safe state 2 delay (rwh) */
} Ifx_TLF35584_SYSPCFG1_Bits;

/** \brief System status flags *R2) */
typedef struct _Ifx_TLF35584_SYSSF_Bits
{
    uint8 CFGE:1;                     /**< \brief [0:0] Double bit error occurred on protected configuration\nregister, Status registers shall be read in order to determine which configuration\nhas changed (rwh) */
    uint8 WWDE:1;                     /**< \brief [1:1] Window watchdog error interrupt flag (rwh) */
    uint8 FWDE:1;                     /**< \brief [2:2] Functional watchdog error interrupt flag (rwh) */
    uint8 ERRMISS:1;                  /**< \brief [3:3] "MCU error miss status flag. Set only when SYSPCFG1.ERRRECEN='1'" (rwh) */
    uint8 TRFAIL:1;                   /**< \brief [4:4] Transition to low power failed either due to the\nLDO_\xc2\xb5C current monitor or WAK event or a rising edge on ENA during\nTRDEL time (rwh) */
    uint8 NO_OP:1;                    /**< \brief [5:5] Requested state transition via DEVCTRL, DEVCTRLN\ncould not be performed because of wrong protocol (rwh) */
    uint8 NU:2;                       /**< \brief [7:6]  (None) */
} Ifx_TLF35584_SYSSF_Bits;

/** \brief Voltage monitor status  *R2) */
typedef struct _Ifx_TLF35584_VMONSTAT_Bits
{
    uint8 NU:2;                       /**< \brief [1:0]  (None) */
    uint8 STBYST:1;                   /**< \brief [2:2] Standby LDO voltage status (rh) */
    uint8 VCOREST:1;                  /**< \brief [3:3] Core voltage status (rh) */
    uint8 COMST:1;                    /**< \brief [4:4] Communication voltage status (rh) */
    uint8 VREFST:1;                   /**< \brief [5:5] Reference voltage status (rh) */
    uint8 TRK1ST:1;                   /**< \brief [6:6] Tracker1 sensor LDO voltage status (rh) */
    uint8 TRK2ST:1;                   /**< \brief [7:7] Tracker2 sensor LDO  voltage status (rh) */
} Ifx_TLF35584_VMONSTAT_Bits;

/** \brief Protected  Watchdog configuration request 0 *R2) */
typedef struct _Ifx_TLF35584_WDCFG0_Bits
{
    uint8 WDCYC:1;                    /**< \brief [0:0] Watchdog cycle time (rwh) */
    uint8 WWDTSEL:1;                  /**< \brief [1:1] Window watchdog trigger selection. This is ignored\nwhen window watchdog is disabled. (rwh) */
    uint8 FWDEN:1;                    /**< \brief [2:2] Functional watchdog enable (rwh) */
    uint8 WWDEN:1;                    /**< \brief [3:3] Window watchdog enable (rwh) */
    uint8 WWDETHR:4;                  /**< \brief [7:4] Window watchdog error threshold. Number of WWD errors\nto generate CPU reset and enter into INIT state (rwh) */
} Ifx_TLF35584_WDCFG0_Bits;

/** \brief Protected Watchdog configuration request 1 *R2) */
typedef struct _Ifx_TLF35584_WDCFG1_Bits
{
    uint8 FWDETHR:4;                  /**< \brief [3:0] Functional watchdog error threshold. Number of FWD\nerrors to generate CPU reset and enter into INIT state (rwh) */
    uint8 WDSLPEN:1;                  /**< \brief [4:4]  (rwh) */
    uint8 NU:3;                       /**< \brief [7:5] not used bits shall be written as 0 and will always\nreturn 1 upon read (None) */
} Ifx_TLF35584_WDCFG1_Bits;

/** \brief Wakeup status flags *R2) */
typedef struct _Ifx_TLF35584_WKSF_Bits
{
    uint8 WAK:1;                      /**< \brief [0:0] Wakeup by WAK signal, bit will also be set if FAILSAFE\nor STBY state left because of WAK (rwh) */
    uint8 ENA:1;                      /**< \brief [1:1] Wake by ENA signal, bit will also be set if FAILSAFE\nor STBY state left because of ENA (rwh) */
    uint8 CMON:1;                     /**< \brief [2:2] Wakup by LDO_\xc2\xb5C current monitor threshold (rwh) */
    uint8 WKTIM:1;                    /**< \brief [3:3] Wakeup by wake timer, bit will also be set if device\nleaves STBY state because of wakeup timer expired (rwh) */
    uint8 WKSPI:1;                    /**< \brief [4:4]  (rwh) */
    uint8 NU:3;                       /**< \brief [7:5]  (None) */
} Ifx_TLF35584_WKSF_Bits;

/** \brief Wake timer configuration 0 *R2) */
typedef struct _Ifx_TLF35584_WKTIMCFG0_Bits
{
    uint8 TIMVALL:8;                  /**< \brief [7:0] Wake timer value (7:0) (rw) */
} Ifx_TLF35584_WKTIMCFG0_Bits;

/** \brief Wake timer configuration 1 *R2) */
typedef struct _Ifx_TLF35584_WKTIMCFG1_Bits
{
    uint8 TIMVALM:8;                  /**< \brief [7:0] Wake timer value (15:8) (rw) */
} Ifx_TLF35584_WKTIMCFG1_Bits;

/** \brief Wake timer configuration 2 *R2) */
typedef struct _Ifx_TLF35584_WKTIMCFG2_Bits
{
    uint8 TIMVALH:8;                  /**< \brief [7:0] Wake timer value (23:16) (rw) */
} Ifx_TLF35584_WKTIMCFG2_Bits;

/** \brief Protected Window watchdog configuration request 0 *R2) */
typedef struct _Ifx_TLF35584_WWDCFG0_Bits
{
    uint8 CW:5;                       /**< \brief [4:0] WWD close window defined as a multiple of 50 watchdog\ncycles (rwh) */
    uint8 NU:3;                       /**< \brief [7:5] not used bits shall be written as 0 and will always\nreturn 1 upon read (None) */
} Ifx_TLF35584_WWDCFG0_Bits;

/** \brief Protected Window watchdog configuration request 1 *R2) */
typedef struct _Ifx_TLF35584_WWDCFG1_Bits
{
    uint8 OW:5;                       /**< \brief [4:0] WWD open window time defined as a multiple 50 wd\ncycles (rwh) */
    uint8 NU:3;                       /**< \brief [7:5] not used bits shall be written as 0 and will always\nreturn 1 upon read (None) */
} Ifx_TLF35584_WWDCFG1_Bits;

/** \brief Window watchdog service command  *R2) */
typedef struct _Ifx_TLF35584_WWDSCMD_Bits
{
    uint8 TRIG:1;                     /**< \brief [0:0] WWD trigger command to trigger WWD, read TRIG_STATUS\nbit first and write inverted value to TRIG bit (rw) */
    uint8 NU:6;                       /**< \brief [6:1]  (None) */
    uint8 TRIG_STATUS:1;              /**< \brief [7:7] Last internal trigger value received via SPI (rh) */
} Ifx_TLF35584_WWDSCMD_Bits;

/** \brief Window watchdog status  *R3) */
typedef struct _Ifx_TLF35584_WWDSTAT_Bits
{
    uint8 WWDECNT:4;                  /**< \brief [3:0] Window watchdog error counter status (rh) */
    uint8 NU:4;                       /**< \brief [7:4]  (None) */
} Ifx_TLF35584_WWDSTAT_Bits;

/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_tlf35584_union
 * \{   */
/** \brief ABIST control0 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_ABIST_CTRL0_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_ABIST_CTRL0;

/** \brief ABIST control1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_ABIST_CTRL1_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_ABIST_CTRL1;

/** \brief ABIST select 0 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_ABIST_SELECT0_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_ABIST_SELECT0;

/** \brief ABIST select 1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_ABIST_SELECT1_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_ABIST_SELECT1;

/** \brief ABIST select 2 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_ABIST_SELECT2_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_ABIST_SELECT2;

/** \brief Buck switching frequency change *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_BCK_FREQ_CHANGE_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_BCK_FREQ_CHANGE;

/** \brief Buck Frequency spread *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_BCK_FRE_SPREAD_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_BCK_FRE_SPREAD;

/** \brief Buck main control *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_BCK_MAIN_CTRL_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_BCK_MAIN_CTRL;

/** \brief Device configuration 0  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVCFG0_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_DEVCFG0;

/** \brief Device configuration 1 *R0)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVCFG1_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_DEVCFG1;

/** \brief Device configuration 2 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVCFG2_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_DEVCFG2;

/** \brief Device control request *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVCTRL_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_DEVCTRL;

/** \brief Device control inverted request *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVCTRLN_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_DEVCTRLN;

/** \brief Device status  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_DEVSTAT_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_DEVSTAT;

/** \brief Protected Functional watchdog configuration request *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_FWDCFG_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_FWDCFG;

/** \brief Functional watchdog response command  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_FWDRSP_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_FWDRSP;

/** \brief Functional watchdog response command with synchronization\n*R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_FWDRSPSYNC_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_FWDRSPSYNC;

/** \brief Functional watchdog status 0 *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_FWDSTAT0_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_FWDSTAT0;

/** \brief Functional watchdog status 1 *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_FWDSTAT1_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_FWDSTAT1;

/** \brief Global testmode *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_GTM_Bits B;          /**< \brief Bitfield access */
} Ifx_TLF35584_GTM;

/** \brief Interrupt flags  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_IF_Bits B;           /**< \brief Bitfield access */
} Ifx_TLF35584_IF;

/** \brief Init error status flags *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_INITERR_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_INITERR;

/** \brief Monitor status flags 0 *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_MONSF0_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_MONSF0;

/** \brief Monitor status flags 1 *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_MONSF1_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_MONSF1;

/** \brief Monitor status flags 2 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_MONSF2_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_MONSF2;

/** \brief Monitor status flags 3 *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_MONSF3_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_MONSF3;

/** \brief Over temperature failure status flags *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_OTFAIL_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_OTFAIL;

/** \brief Over temperature warning status flags  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_OTWRNSF_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_OTWRNSF;

/** \brief Protection register  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_PROTCFG_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_PROTCFG;

/** \brief Protection status  *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_PROTSTAT_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_PROTSTAT;

/** \brief Functional watchdog configuration status *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RFWDCFG_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_RFWDCFG;

/** \brief System  configuration 0 status *R0)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RSYSPCFG0_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_RSYSPCFG0;

/** \brief System configuration 1 status  *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RSYSPCFG1_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_RSYSPCFG1;

/** \brief Watchdog configuration 0 status *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RWDCFG0_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_RWDCFG0;

/** \brief Watchdog configuration 1 status *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RWDCFG1_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_RWDCFG1;

/** \brief Window watchdog configuration 0 status *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RWWDCFG0_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_RWWDCFG0;

/** \brief Window watchdog configuration 1 status *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_RWWDCFG1_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_RWWDCFG1;

/** \brief SPI status flags *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_SPISF_Bits B;        /**< \brief Bitfield access */
} Ifx_TLF35584_SPISF;

/** \brief Failure status flags *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_SYSFAIL_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_SYSFAIL;

/** \brief Protected System configuration request 0 *R1)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_SYSPCFG0_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_SYSPCFG0;

/** \brief Protected System configuration request 1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_SYSPCFG1_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_SYSPCFG1;

/** \brief System status flags *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_SYSSF_Bits B;        /**< \brief Bitfield access */
} Ifx_TLF35584_SYSSF;

/** \brief Voltage monitor status  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_VMONSTAT_Bits B;     /**< \brief Bitfield access */
} Ifx_TLF35584_VMONSTAT;

/** \brief Protected  Watchdog configuration request 0 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WDCFG0_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_WDCFG0;

/** \brief Protected Watchdog configuration request 1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WDCFG1_Bits B;       /**< \brief Bitfield access */
} Ifx_TLF35584_WDCFG1;

/** \brief Wakeup status flags *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WKSF_Bits B;         /**< \brief Bitfield access */
} Ifx_TLF35584_WKSF;

/** \brief Wake timer configuration 0 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WKTIMCFG0_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_WKTIMCFG0;

/** \brief Wake timer configuration 1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WKTIMCFG1_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_WKTIMCFG1;

/** \brief Wake timer configuration 2 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WKTIMCFG2_Bits B;    /**< \brief Bitfield access */
} Ifx_TLF35584_WKTIMCFG2;

/** \brief Protected Window watchdog configuration request 0 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WWDCFG0_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_WWDCFG0;

/** \brief Protected Window watchdog configuration request 1 *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WWDCFG1_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_WWDCFG1;

/** \brief Window watchdog service command  *R2)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WWDSCMD_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_WWDSCMD;

/** \brief Window watchdog status  *R3)   */
typedef union
{
    uint8 U;                          /**< \brief Unsigned access */
    sint8 I;                          /**< \brief Signed access */
    Ifx_TLF35584_WWDSTAT_Bits B;      /**< \brief Bitfield access */
} Ifx_TLF35584_WWDSTAT;

/** \}  */


/******************************************************************************/
/** \addtogroup IfxLld_Tlf35584_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief TLF35584 object */
typedef volatile struct _Ifx_TLF35584
{
       Ifx_TLF35584_DEVCFG0                DEVCFG0;                /**< \brief 0, Device configuration 0  *R2)*/
       Ifx_TLF35584_DEVCFG1                DEVCFG1;                /**< \brief 1, Device configuration 1 *R0)*/
       Ifx_TLF35584_DEVCFG2                DEVCFG2;                /**< \brief 2, Device configuration 2 *R2)*/
       Ifx_TLF35584_PROTCFG                PROTCFG;                /**< \brief 3, Protection register  *R2)*/
       Ifx_TLF35584_SYSPCFG0               SYSPCFG0;               /**< \brief 4, Protected System configuration request 0 *R1)*/
       Ifx_TLF35584_SYSPCFG1               SYSPCFG1;               /**< \brief 5, Protected System configuration request 1 *R2)*/
       Ifx_TLF35584_WDCFG0                 WDCFG0;                 /**< \brief 6, Protected  Watchdog configuration request 0 *R2)*/
       Ifx_TLF35584_WDCFG1                 WDCFG1;                 /**< \brief 7, Protected Watchdog configuration request 1 *R2)*/
       Ifx_TLF35584_FWDCFG                 FWDCFG;                 /**< \brief 8, Protected Functional watchdog configuration request *R2)*/
       Ifx_TLF35584_WWDCFG0                WWDCFG0;                /**< \brief 9, Protected Window watchdog configuration request 0 *R2)*/
       Ifx_TLF35584_WWDCFG1                WWDCFG1;                /**< \brief A, Protected Window watchdog configuration request 1 *R2)*/
       Ifx_TLF35584_RSYSPCFG0              RSYSPCFG0;              /**< \brief B, System  configuration 0 status *R0)*/
       Ifx_TLF35584_RSYSPCFG1              RSYSPCFG1;              /**< \brief C, System configuration 1 status  *R3)*/
       Ifx_TLF35584_RWDCFG0                RWDCFG0;                /**< \brief D, Watchdog configuration 0 status *R3)*/
       Ifx_TLF35584_RWDCFG1                RWDCFG1;                /**< \brief E, Watchdog configuration 1 status *R3)*/
       Ifx_TLF35584_RFWDCFG                RFWDCFG;                /**< \brief F, Functional watchdog configuration status *R3)*/
       Ifx_TLF35584_RWWDCFG0               RWWDCFG0;               /**< \brief 10, Window watchdog configuration 0 status *R3)*/
       Ifx_TLF35584_RWWDCFG1               RWWDCFG1;               /**< \brief 11, Window watchdog configuration 1 status *R3)*/
       Ifx_TLF35584_WKTIMCFG0              WKTIMCFG0;              /**< \brief 12, Wake timer configuration 0 *R2)*/
       Ifx_TLF35584_WKTIMCFG1              WKTIMCFG1;              /**< \brief 13, Wake timer configuration 1 *R2)*/
       Ifx_TLF35584_WKTIMCFG2              WKTIMCFG2;              /**< \brief 14, Wake timer configuration 2 *R2)*/
       Ifx_TLF35584_DEVCTRL                DEVCTRL;                /**< \brief 15, Device control request *R2)*/
       Ifx_TLF35584_DEVCTRLN               DEVCTRLN;               /**< \brief 16, Device control inverted request *R2)*/
       Ifx_TLF35584_WWDSCMD                WWDSCMD;                /**< \brief 17, Window watchdog service command  *R2)*/
       Ifx_TLF35584_FWDRSP                 FWDRSP;                 /**< \brief 18, Functional watchdog response command  *R2)*/
       Ifx_TLF35584_FWDRSPSYNC             FWDRSPSYNC;             /**< \brief 19, Functional watchdog response command with synchronization\n*R2)*/
       Ifx_TLF35584_SYSFAIL                SYSFAIL;                /**< \brief 1A, Failure status flags *R1)*/
       Ifx_TLF35584_INITERR                INITERR;                /**< \brief 1B, Init error status flags *R2)*/
       Ifx_TLF35584_IF                     IF;                     /**< \brief 1C, Interrupt flags  *R2)*/
       Ifx_TLF35584_SYSSF                  SYSSF;                  /**< \brief 1D, System status flags *R2)*/
       Ifx_TLF35584_WKSF                   WKSF;                   /**< \brief 1E, Wakeup status flags *R2)*/
       Ifx_TLF35584_SPISF                  SPISF;                  /**< \brief 1F, SPI status flags *R2)*/
       Ifx_TLF35584_MONSF0                 MONSF0;                 /**< \brief 20, Monitor status flags 0 *R1)*/
       Ifx_TLF35584_MONSF1                 MONSF1;                 /**< \brief 21, Monitor status flags 1 *R1)*/
       Ifx_TLF35584_MONSF2                 MONSF2;                 /**< \brief 22, Monitor status flags 2 *R2)*/
       Ifx_TLF35584_MONSF3                 MONSF3;                 /**< \brief 23, Monitor status flags 3 *R1)*/
       Ifx_TLF35584_OTFAIL                 OTFAIL;                 /**< \brief 24, Over temperature failure status flags *R1)*/
       Ifx_TLF35584_OTWRNSF                OTWRNSF;                /**< \brief 25, Over temperature warning status flags  *R2)*/
       Ifx_TLF35584_VMONSTAT               VMONSTAT;               /**< \brief 26, Voltage monitor status  *R2)*/
       Ifx_TLF35584_DEVSTAT                DEVSTAT;                /**< \brief 27, Device status  *R2)*/
       Ifx_TLF35584_PROTSTAT               PROTSTAT;               /**< \brief 28, Protection status  *R1)*/
       Ifx_TLF35584_WWDSTAT                WWDSTAT;                /**< \brief 29, Window watchdog status  *R3)*/
       Ifx_TLF35584_FWDSTAT0               FWDSTAT0;               /**< \brief 2A, Functional watchdog status 0 *R3)*/
       Ifx_TLF35584_FWDSTAT1               FWDSTAT1;               /**< \brief 2B, Functional watchdog status 1 *R3)*/
       Ifx_TLF35584_ABIST_CTRL0            ABIST_CTRL0;            /**< \brief 2C, ABIST control0 *R2)*/
       Ifx_TLF35584_ABIST_CTRL1            ABIST_CTRL1;            /**< \brief 2D, ABIST control1 *R2)*/
       Ifx_TLF35584_ABIST_SELECT0          ABIST_SELECT0;          /**< \brief 2E, ABIST select 0 *R2)*/
       Ifx_TLF35584_ABIST_SELECT1          ABIST_SELECT1;          /**< \brief 2F, ABIST select 1 *R2)*/
       Ifx_TLF35584_ABIST_SELECT2          ABIST_SELECT2;          /**< \brief 30, ABIST select 2 *R2)*/
       Ifx_TLF35584_BCK_FREQ_CHANGE        BCK_FREQ_CHANGE;        /**< \brief 31, Buck switching frequency change *R2)*/
       Ifx_TLF35584_BCK_FRE_SPREAD         BCK_FRE_SPREAD;         /**< \brief 32, Buck Frequency spread *R2)*/
       Ifx_TLF35584_BCK_MAIN_CTRL          BCK_MAIN_CTRL;          /**< \brief 33, Buck main control *R2)*/
       uint8                               reserved_34[11];        /**< \brief 34, \internal Reserved */
       Ifx_TLF35584_GTM                    GTM;                    /**< \brief 3F, Global testmode *R2)*/
} Ifx_TLF35584;

/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
IFX_EXTERN uint32 Ifx_g_TLF35584_validAddress[2];

IFX_EXTERN uint32 Ifx_g_TLF35584_volatileRegisters[2];


#endif /* IFXTLF35584_REGDEF_H */
