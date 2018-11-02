#ifndef SRC_CONST_H_
#define SRC_CONST_H_

// Electric Power Assisted Steering (ЭУР) ID
#define EPAS_ID		0x87
// Electric Power Assisted Steering base
#define EPAS_A_BASE	0x88
// Movement Control Module (БУД) ID
#define MCM_ID		0x82
// Movement Control Module A base
#define MCM_A_BASE	0x20

// ------------EPAS states------------
#define STATE_READY			0x00
#define STATE_WORKING		0x01
#define STATE_TECHMODE		0x02
#define STATE_SELFCONTROL	0x04
#define STATE_NOTREADY		0x80
// -----------------------------------

// ------incoming messages------------

#define	SYNCPARAM_ID	0x0C098782
#define	REQUEST_ID		0x0CEA8782
#define	SYNC_CTRL_ID	0x0C088782
#define	REG_CTRL_1_ID	0x0C208782
#define	CONTROL_ID		0x0C0A8782

#define	SYNCPARAM_DATA				0x0000000000000000
#define	REQUEST_DEVSTATE_DATA		0x000000000000F800
#define	REQUEST_PROGRAMINFO_DATA	0x000000000000F801
#define	REQUEST_WARNINGS_DATA		0x000000000000F80B
#define	REQUEST_ERRORS_DATA			0x000000000000F80A
#define	SYNC_CTRL_DATA				0x0000000000000000
#define	REG_CTRL_1_DATA				0x0000000000000000 + 1100 + (0 << 16)
#define	CONTROL_DATA				0x00000000 + 2 + (0 << 16)

// -----------------------------------


// --------------REQUEST--------------
// CAN ID parameters
#define REQUEST_PF			0xEA
#define REQUEST_PRIORITY	3

// CAN data parameters
#define REQUEST_DATA_SIZE	3
// -----------------------------------

// ---------------NACK----------------
// CAN ID parameters
#define NACK_PF			0xE8
#define NACK_PS			MCM_ID
#define NACK_PRIORITY	6

// CAN data parameters
#define NACK_DATA_SIZE		8

#define ACK_CONTROLBYTE		0x00
#define NACK_CONTROLBYTE	0x01
#define NACK_FILL			0xFFFFFFFF
// -----------------------------------

// -------------DEVSTATE--------------
// CAN ID parameters
#define DEVSTATE_PF			0xF8
#define DEVSTATE_PS			0x00
#define DEVSTATE_PRIORITY	6

// CAN data parameters
#define DEVSTATE_DATA_SIZE			2

#define DEVSTATE_SELFDIAG_ALL_OK	0
#define DEVSTATE_SELFDIAG_OPERABLE	1
// -----------------------------------

// -----------PROGRAM_INFO------------
// CAN ID parameters
#define PROGRAMINFO_PF			0xF8
#define PROGRAMINFO_PS			0x01
#define PROGRAMINFO_PRIORITY	6

// CAN data parameters
#define PROGRAMINFO_DATA_SIZE	8
// -----------------------------------

// --------------ERRORS---------------
// CAN ID parameters
#define ERRORS_PF			0xF8
#define ERRORS_PS			0x0A
#define ERRORS_PRIORITY		6

// CAN data parameters
#define ERRORS_DATA_SIZE	8
// -----------------------------------

// -------------WARNINGS--------------
// CAN ID parameters
#define WARNINGS_PF			0xF8
#define WARNINGS_PS			0x0B
#define WARNINGS_PRIORITY	6

// CAN data parameters
#define WARNINGS_DATA_SIZE	8
// -----------------------------------

// -------------CONTROL---------------
// CAN ID parameters
#define CONTROL_PF			0x0A
#define CONTROL_PS			0xDA
#define CONTROL_PRIORITY	3

// CAN data parameters
#define CONTROL_DATA_SIZE	4

#define COMMAND_CODE_STATE_READY	1
#define COMMAND_CODE_STATE_WORKING	2
#define COMMAND_CODE_CLEAR_ERROR	32
#define COMMAND_CODE_CLEAR_WARNING	33
// -----------------------------------

// -----------RETCONTROL--------------
// CAN ID parameters
#define RETCONTROL_PF			0x0B
#define RETCONTROL_PS			MCM_ID
#define RETCONTROL_PRIORITY		3

// CAN data parameters
#define RETCONTROL_DATA_SIZE	5

#define RETCONTROL_RESULT_ACCEPTED					0
#define RETCONTROL_RESULT_UNABLE_TO_EXECUTE			1
#define RETCONTROL_RESULT_EXECUTION_ERROR			2
#define RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED		255
// -----------------------------------

// -----------SYNC_CTRL---------------
// CAN ID parameters
#define SYNCCTRL_PF			0x08
#define SYNCCTRL_PS			EPAS_ID
#define SYNCCTRL_PRIORITY	3

// CAN data parameters
#define SYNCCTRL_DATA_SIZE	0
// -----------------------------------

// -----------REG_CTRL_1--------------
// CAN ID parameters
#define REGCTRL1_PF			MCM_A_BASE
#define REGCTRL1_PS			EPAS_ID
#define REGCTRL1_PRIORITY	3

// CAN data parameters
#define REGCTRL1_DATA_SIZE	8
// -----------------------------------

// -----------REG_CTRL_2--------------
// CAN ID parameters
#define REGCTRL2_PF			MCM_A_BASE + 1
#define REGCTRL2_PS			EPAS_ID
#define REGCTRL2_PRIORITY	3

// CAN data parameters
#define REGCTRL2_DATA_SIZE	8
// -----------------------------------

// -----------REG_CTRL_3--------------
// CAN ID parameters
#define REGCTRL3_PF			MCM_A_BASE + 2
#define REGCTRL3_PS			EPAS_ID
#define REGCTRL3_PRIORITY	3

// CAN data parameters
#define REGCTRL3_DATA_SIZE	8
// -----------------------------------

// -----------SYNC_PARAM--------------
// CAN ID parameters
#define SYNCPARAM_PF		0x09
#define SYNCPARAM_PS		EPAS_ID
#define SYNCPARAM_PRIORITY	3

// CAN data parameters
#define SYNCPARAM_DATA_SIZE	4
// -----------------------------------

// ----------REG_PARAM_1--------------
// CAN ID parameters
#define REGPARAM1_PF			0xF8
#define REGPARAM1_PS			EPAS_A_BASE
#define REGPARAM1_PRIORITY		6

// CAN data parameters
#define REGPARAM1_DATA_SIZE		8
// -----------------------------------

// ----------REG_PARAM_2--------------
// CAN ID parameters
#define REGPARAM2_PF			0xF8
#define REGPARAM2_PS			EPAS_A_BASE + 1
#define REGPARAM2_PRIORITY		6

// CAN data parameters
#define REGPARAM2_DATA_SIZE		8
// -----------------------------------

// ----------REG_PARAM_3--------------
// CAN ID parameters
#define REGPARAM3_PF			0xF8
#define REGPARAM3_PS			EPAS_A_BASE + 2
#define REGPARAM3_PRIORITY		6

// CAN data parameters
#define REGPARAM3_DATA_SIZE		8
// -----------------------------------

// приоритеты сообщения
#define PRIOR_HI			0x3
#define PRIOR_LO			0x6

#define PGN_REQUEST			0x00EA00	// БУД->ЭУР - Запрос
#define PGN_NACK			0x00E800	// ЭУР->БУД - Отрицательное подтверждение
#define PGN_SYNC_CTRL		0x000800	// БУД->ЭУР - Синхронизация по управлению
#define PGN_SYNC_PARAM		0x000900	// БУД->ЭУР - Синхронизация по телеметрии
#define PGN_REG_CTRL_1		0x002000	// БУД->ЭУР - Регистр управления
#define PGN_REG_PARAM_1		0x00F888	// ЭУР->БУД - Регистр телеметрии 1
#define PGN_REG_PARAM_2		0x00F889	// ЭУР->БУД - Регистр телеметрии 2
#define PGN_REG_PARAM_3		0x00F88A	// ЭУР->БУД - Регистр телеметрии 3
#define PGN_WARNINGS		0x00F80B	// ЭУР->БУД - Флаги возникновения предупреждений
#define PGN_ERRORS			0x00F80A	// ЭУР->БУД - Флаги возникновения ошибок
#define PGN_CONTROL			0x000A00	// БУД->ЭУР - Управление режимом работы
#define PGN_RETCONTROL		0x000B00	// ЭУР->БУД - Ответ на команду CONTROL
#define PGN_DEVSTATE		0x00F800	// ЭУР->БУД - Режим работы и состояние БУД
#define PGN_PROGRAM_INFO	0x00F801	// ЭУР->БУД - Информация о программе

#define PF_REQUEST			0xEA	// БУД->ЭУР - Запрос
#define PF_NACK				0xE8	// ЭУР->БУД - Отрицательное подтверждение
#define PF_SYNC_CTRL		0x08	// БУД->ЭУР - Синхронизация по управлению
#define PF_SYNC_PARAM		0x09	// БУД->ЭУР - Синхронизация по телеметрии
#define PF_REG_CTRL			0x20	// БУД->ЭУР - Регистр управления
#define PF_REG_PARAM		0xF8	// ЭУР->БУД - Регистр телеметрии 1
#define PF_WARNINGS			0xF8	// ЭУР->БУД - Флаги возникновения предупреждений
#define PF_ERRORS			0xF8	// ЭУР->БУД - Флаги возникновения ошибок
#define PF_CONTROL			0x0A	// БУД->ЭУР - Управление режимом работы
#define PF_RETCONTROL		0x0B	// ЭУР->БУД - Ответ на команду CONTROL
#define PF_DEVSTATE			0xF8	// ЭУР->БУД - Режим работы и состояние БУД
#define PF_PROGRAM_INFO		0xF8	// ЭУР->БУД - Информация о программе

#endif /* SRC_CONST_H_ */

