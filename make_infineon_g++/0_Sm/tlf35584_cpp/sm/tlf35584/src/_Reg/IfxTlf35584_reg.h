/**
 * \file IfxTlf35584_reg.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
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
 * \defgroup IfxLld_Tlf35584_Cfg Tlf35584 address
 * \ingroup IfxLld_Tlf35584
 * 
 * \defgroup IfxLld_Tlf35584_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Tlf35584_Cfg
 *
 * \defgroup IfxLld_Tlf35584_Cfg_Tlf35584 2-TLF35584
 * \ingroup IfxLld_Tlf35584_Cfg
 *
 *
 */
#ifndef IFXTLF35584_REG_H
#define IFXTLF35584_REG_H 1
/******************************************************************************/
#include "IfxTlf35584_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Tlf35584_Cfg_BaseAddress
 * \{  */

/** \brief TLF35584 object */
#define MODULE_TLF35584 /*lint --e(923)*/ ((*(Ifx_TLF35584*)0x0u))
/** \}  */

/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Tlf35584_Cfg_Tlf35584
 * \{  */
/** \brief 0, Device configuration 0  *R2) */
#define TLF35584_DEVCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVCFG0*)0x0u)

/** \brief 1, Device configuration 1 *R0) */
#define TLF35584_DEVCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVCFG1*)0x1u)

/** \brief 2, Device configuration 2 *R2) */
#define TLF35584_DEVCFG2 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVCFG2*)0x2u)

/** \brief 3, Protection register  *R2) */
#define TLF35584_PROTCFG /*lint --e(923)*/ (*(volatile Ifx_TLF35584_PROTCFG*)0x3u)

/** \brief 4, Protected System configuration request 0 *R1) */
#define TLF35584_SYSPCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_SYSPCFG0*)0x4u)

/** \brief 5, Protected System configuration request 1 *R2) */
#define TLF35584_SYSPCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_SYSPCFG1*)0x5u)

/** \brief 6, Protected  Watchdog configuration request 0 *R2) */
#define TLF35584_WDCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WDCFG0*)0x6u)

/** \brief 7, Protected Watchdog configuration request 1 *R2) */
#define TLF35584_WDCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WDCFG1*)0x7u)

/** \brief 8, Protected Functional watchdog configuration request *R2) */
#define TLF35584_FWDCFG /*lint --e(923)*/ (*(volatile Ifx_TLF35584_FWDCFG*)0x8u)

/** \brief 9, Protected Window watchdog configuration request 0 *R2) */
#define TLF35584_WWDCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WWDCFG0*)0x9u)

/** \brief A, Protected Window watchdog configuration request 1 *R2) */
#define TLF35584_WWDCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WWDCFG1*)0xAu)

/** \brief B, System  configuration 0 status *R0) */
#define TLF35584_RSYSPCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RSYSPCFG0*)0xBu)

/** \brief C, System configuration 1 status  *R3) */
#define TLF35584_RSYSPCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RSYSPCFG1*)0xCu)

/** \brief D, Watchdog configuration 0 status *R3) */
#define TLF35584_RWDCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RWDCFG0*)0xDu)

/** \brief E, Watchdog configuration 1 status *R3) */
#define TLF35584_RWDCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RWDCFG1*)0xEu)

/** \brief F, Functional watchdog configuration status *R3) */
#define TLF35584_RFWDCFG /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RFWDCFG*)0xFu)

/** \brief 10, Window watchdog configuration 0 status *R3) */
#define TLF35584_RWWDCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RWWDCFG0*)0x10u)

/** \brief 11, Window watchdog configuration 1 status *R3) */
#define TLF35584_RWWDCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_RWWDCFG1*)0x11u)

/** \brief 12, Wake timer configuration 0 *R2) */
#define TLF35584_WKTIMCFG0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WKTIMCFG0*)0x12u)

/** \brief 13, Wake timer configuration 1 *R2) */
#define TLF35584_WKTIMCFG1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WKTIMCFG1*)0x13u)

/** \brief 14, Wake timer configuration 2 *R2) */
#define TLF35584_WKTIMCFG2 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WKTIMCFG2*)0x14u)

/** \brief 15, Device control request *R2) */
#define TLF35584_DEVCTRL /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVCTRL*)0x15u)

/** \brief 16, Device control inverted request *R2) */
#define TLF35584_DEVCTRLN /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVCTRLN*)0x16u)

/** \brief 17, Window watchdog service command  *R2) */
#define TLF35584_WWDSCMD /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WWDSCMD*)0x17u)

/** \brief 18, Functional watchdog response command  *R2) */
#define TLF35584_FWDRSP /*lint --e(923)*/ (*(volatile Ifx_TLF35584_FWDRSP*)0x18u)

/** \brief 19, Functional watchdog response command with synchronization\\n*R2) */
#define TLF35584_FWDRSPSYNC /*lint --e(923)*/ (*(volatile Ifx_TLF35584_FWDRSPSYNC*)0x19u)

/** \brief 1A, Failure status flags *R1) */
#define TLF35584_SYSFAIL /*lint --e(923)*/ (*(volatile Ifx_TLF35584_SYSFAIL*)0x1Au)

/** \brief 1B, Init error status flags *R2) */
#define TLF35584_INITERR /*lint --e(923)*/ (*(volatile Ifx_TLF35584_INITERR*)0x1Bu)

/** \brief 1C, Interrupt flags  *R2) */
#define TLF35584_IF /*lint --e(923)*/ (*(volatile Ifx_TLF35584_IF*)0x1Cu)

/** \brief 1D, System status flags *R2) */
#define TLF35584_SYSSF /*lint --e(923)*/ (*(volatile Ifx_TLF35584_SYSSF*)0x1Du)

/** \brief 1E, Wakeup status flags *R2) */
#define TLF35584_WKSF /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WKSF*)0x1Eu)

/** \brief 1F, SPI status flags *R2) */
#define TLF35584_SPISF /*lint --e(923)*/ (*(volatile Ifx_TLF35584_SPISF*)0x1Fu)

/** \brief 20, Monitor status flags 0 *R1) */
#define TLF35584_MONSF0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_MONSF0*)0x20u)

/** \brief 21, Monitor status flags 1 *R1) */
#define TLF35584_MONSF1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_MONSF1*)0x21u)

/** \brief 22, Monitor status flags 2 *R2) */
#define TLF35584_MONSF2 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_MONSF2*)0x22u)

/** \brief 23, Monitor status flags 3 *R1) */
#define TLF35584_MONSF3 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_MONSF3*)0x23u)

/** \brief 24, Over temperature failure status flags *R1) */
#define TLF35584_OTFAIL /*lint --e(923)*/ (*(volatile Ifx_TLF35584_OTFAIL*)0x24u)

/** \brief 25, Over temperature warning status flags  *R2) */
#define TLF35584_OTWRNSF /*lint --e(923)*/ (*(volatile Ifx_TLF35584_OTWRNSF*)0x25u)

/** \brief 26, Voltage monitor status  *R2) */
#define TLF35584_VMONSTAT /*lint --e(923)*/ (*(volatile Ifx_TLF35584_VMONSTAT*)0x26u)

/** \brief 27, Device status  *R2) */
#define TLF35584_DEVSTAT /*lint --e(923)*/ (*(volatile Ifx_TLF35584_DEVSTAT*)0x27u)

/** \brief 28, Protection status  *R1) */
#define TLF35584_PROTSTAT /*lint --e(923)*/ (*(volatile Ifx_TLF35584_PROTSTAT*)0x28u)

/** \brief 29, Window watchdog status  *R3) */
#define TLF35584_WWDSTAT /*lint --e(923)*/ (*(volatile Ifx_TLF35584_WWDSTAT*)0x29u)

/** \brief 2A, Functional watchdog status 0 *R3) */
#define TLF35584_FWDSTAT0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_FWDSTAT0*)0x2Au)

/** \brief 2B, Functional watchdog status 1 *R3) */
#define TLF35584_FWDSTAT1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_FWDSTAT1*)0x2Bu)

/** \brief 2C, ABIST control0 *R2) */
#define TLF35584_ABIST_CTRL0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_ABIST_CTRL0*)0x2Cu)

/** \brief 2D, ABIST control1 *R2) */
#define TLF35584_ABIST_CTRL1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_ABIST_CTRL1*)0x2Du)

/** \brief 2E, ABIST select 0 *R2) */
#define TLF35584_ABIST_SELECT0 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_ABIST_SELECT0*)0x2Eu)

/** \brief 2F, ABIST select 1 *R2) */
#define TLF35584_ABIST_SELECT1 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_ABIST_SELECT1*)0x2Fu)

/** \brief 30, ABIST select 2 *R2) */
#define TLF35584_ABIST_SELECT2 /*lint --e(923)*/ (*(volatile Ifx_TLF35584_ABIST_SELECT2*)0x30u)

/** \brief 31, Buck switching frequency change *R2) */
#define TLF35584_BCK_FREQ_CHANGE /*lint --e(923)*/ (*(volatile Ifx_TLF35584_BCK_FREQ_CHANGE*)0x31u)

/** \brief 32, Buck Frequency spread *R2) */
#define TLF35584_BCK_FRE_SPREAD /*lint --e(923)*/ (*(volatile Ifx_TLF35584_BCK_FRE_SPREAD*)0x32u)

/** \brief 33, Buck main control *R2) */
#define TLF35584_BCK_MAIN_CTRL /*lint --e(923)*/ (*(volatile Ifx_TLF35584_BCK_MAIN_CTRL*)0x33u)

/** \brief 3F, Global testmode *R2) */
#define TLF35584_GTM /*lint --e(923)*/ (*(volatile Ifx_TLF35584_GTM*)0x3Fu)

/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXTLF35584_REG_H */
