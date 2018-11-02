/*
 * gaz_eps_protocol_msg.h
 *
 *  Created on: 24 сент. 2018 г.
 *      Author: user1
 */

#ifndef GAZ_EPS_PROTOCOL_MSG_H_
#define GAZ_EPS_PROTOCOL_MSG_H_

#include "types.h"
#include "array.h"
#include "can_dl.h"

namespace GazEpsProtocolImp
{

	const u8 eurAddr = 0x87;
	const u8 budAddr = 0x82;

	// приоритеты сообщения
	#define PRIOR_HI			0x3
	#define PRIOR_LO			0x6

	// Идентификатор ЭУР в сети CAN R2 Abase
	const u8 A_BASE_EUR = 0x88;
	// Идентификатор БУД в сети CAN R2 Abase
	const u8 A_BASE_BUD = 0x20;

	// Parameter Group Number
	// БУД->ЭУР
	#define PGN_REQUEST			0x00EA00    // Запрос
	// ЭУР->БУД
	#define PGN_NACK			0x00E800    // Отрицательное подтверждение
	// БУД->ЭУР
	#define PGN_SYNC_CTRL		0x000800    // Синхронизация по управлению
	// БУД->ЭУР
	#define PGN_SYNC_PARAM		0x000900    // Синхронизация по телеметрии
	// БУД->ЭУР
	#define PGN_REG_CTRL_1		0x002000    // Регистр управления
	// ЭУР->БУД
	#define PGN_REG_PARAM_1		0x00F888    // Регистр телеметрии 1
	// ЭУР->БУД
	#define PGN_REG_PARAM_2		0x00F889    // Регистр телеметрии 2
	// ЭУР->БУД
	#define PGN_REG_PARAM_3		0x00F88A    // Регистр телеметрии 3
	// ЭУР->БУД
	#define PGN_WARNINGS		0x00F80B    // Флаги предупреждений
	// ЭУР->БУД
	#define PGN_ERRORS			0x00F80A    // Флаги возникновения ошибок
	// БУД->ЭУР
	#define PGN_CONTROL			0x000A00    // Управление режимом работы
	// ЭУР->БУД
	#define PGN_RETCONTROL		0x000B00    // Ответ на команду CONTROL
	// ЭУР->БУД
	#define PGN_DEVSTATE		0x00F800    // Режим работы и состояние БУД
	// ЭУР->БУД
	#define PGN_PROGRAM_INFO	0x00F801    // Информация о программе

	// БУД->ЭУР
	#define PF_REQUEST			0xEA    // Запрос
	// ЭУР->БУД
	#define PF_NACK				0xE8    // Отрицательное подтверждение
	// БУД->ЭУР
	#define PF_SYNC_CTRL		0x08    // Синхронизация по управлению
	// БУД->ЭУР
	#define PF_SYNC_PARAM		0x09    // Синхронизация по телеметрии
	// БУД->ЭУР
	#define PF_REG_CTRL			0x20    // Регистр управления
	// ЭУР->БУД
	#define PF_REG_PARAM		0xF8    // Регистр телеметрии 1
	// ЭУР->БУД
	#define PF_WARNINGS			0xF8    // Флаги возникновения предупреждений
	// ЭУР->БУД
	#define PF_ERRORS			0xF8    // Флаги возникновения ошибок
	// БУД->ЭУР
	#define PF_CONTROL			0x0A    // Управление режимом работы
	// ЭУР->БУД
	#define PF_RETCONTROL		0x0B    // Ответ на команду CONTROL
	// ЭУР->БУД
	#define PF_DEVSTATE			0xF8    // Режим работы и состояние БУД
	// ЭУР->БУД
	#define PF_PROGRAM_INFO		0xF8    // Информация о программе

	struct EnumWorkModes
	{
		typedef enum
		{
			_READY = 0,			// Экипажное управление
			_WORKING = 0x01,	// режим дистанционного управления
			_TECHMODE = 0x02,
			_SELFCONTROL = 0x04,
			_NOT_READY = 0x80
		} WorkModes;
	};

	//! структура сообщения ACK/NACK
	// TODO: похоже, это нафиг не нужно
	typedef struct
	{
		u8 controlByte;			//!< 0 - ACK, 1 - NACK
		unsigned pgn	: 24;	//!< Запрашиваемый PGN
	} AckNackMSG;

	//! структура сообщения DEVSTATE
	// TODO: похоже, это нафиг не нужно
	struct DevstateMSG
	{
		u8 wrkMode;						//!< Unsigned2 - режим работы
		unsigned int warnFlag	: 1;	//!< Unsigned1 - флаг предупреждения
										//!< (0 - нет, 1 - есть)
		unsigned int errFlag	: 1;	//!< Unsigned1 - флаг ошибок (1 - есть)
		unsigned int rezerv		: 2;	//!< Void2     - заполняется нулями
		unsigned int techCond	: 4;	//!< Unsigned4 - код технического
										//!< состояния (0 - исправно,
										//!< 1 - работоспособно ...)
	};

	//! структура сообщения  PARAM_INFO
	// TODO: похоже, это нафиг не нужно
	typedef struct
	{
		u32 hashSumm;	//!< Значения контрольной характеристики программы
						//!< устройства
		u8 X;			//!< глобальные изменения в ПО
		u8 Y;			//!< обавлении новых функций и исправлении ошибок
		u16 Z;			//!< при исправлении незначительных ошибок и внесении
						//!< незначительных исправлений
	} ProgramInfoMSG;

	//! структура сообщения WARNINGS
	typedef struct
	{
		u8 flagNum;							// Порядковый номер выставленного флага
		unsigned int watchdogReset	: 1;	// Устройство переза­пущено по
											// срабатыванию watchdog таймера
		// еще 55 битов флагов
	} WarningsMSG;

	// \brief структура сообщения ERRORS
	// TODO: требуется доработка структуры
	typedef struct
	{
		u8 flagNum;						// Порядковый номер выставленного флага
		unsigned int lossCtrlCmds	: 1;	// Потеря команд управления
		// еще 55 битов флагов
	} ErrorsMsg;

	// структура сообщения REG_CTRL_1
	typedef struct
	{
		u16 setWheelPosition;		// 0.0-1.2 управление поворотом руля
									// 1.3-1.7 - Резерв Void5 Заполняется нулями
		u8 turnSpeed;				// 2.0-2.7 - Unsigned8 - скорость поворота руля 0..100
									// 3.0-7.7 - Резерв Void40 Заполняется нулями
		// флаги
		bool dataRxFlag;			// true - данные приняты, false - данные не приняты
		bool dataError;				// true - приняты некорректные данные
		bool doNotApplyData;		// true - не применять данные
	} RegControl_1_DataFormat;

	//
	typedef struct
	{
		// предельная уставка скорости в формате 2^16
		u16 L;	// byte0
				// byte1
		// коэффициент пропорционального звена в формате 2^Qp
		u16 Kp;	// byte2
				// byte3
		//
		u8 Qp;	// byte4
		// коэффициент интегрирующего звена в формате 2^Qi
		u16 Ki;	// byte5
				// byte6
		u8 Qi;	// byte7

		u64 data64;	// полеченные сырые данные как есть

		bool dataRxFlag;	//
	} RegControlRegulatorDataFormat;

	// SYNC_PARAM
	typedef struct
	{
		u8 PGN_lsb;				// младший байт PGN
		u8 PGN_mdl;				// средний байт PGN
		u8 PGN_msb;				// старший байт PGN
		u8 telemetryCountPGN;	// количество PGN телеметрии

		u32 PGN;
	} SyncParamDataFormat;

//	typedef enum
//	{
//		switchEUMode = 1,	// перевести устройство в режим ЭУ
//		switchDUMode = 2,	// перевести устройство в режим ДУ
//		clearError = 32,	// сброс флагов предупреждений
//		clearWarning = 33	// сброс флагов ошибок
//	} ControlCommands;

	// структура сообщения CONTROL
	typedef struct
	{
		u8 cmdCode;			// код команды
		u8 devAddr;			// адрес устройства, для которого команда
		u8 comandData;		// данные команды
		u8 rezerv;
		bool dataRxFlag;	// true - данные приняты, false - данные не приняты
	} ControlDataFormat;

	// значение кодов команд сообщения CONTROL
	struct ControlCommands
	{
		typedef enum
		{
			ctrlCmdSwitchEUMode = 1,	// перевести устройство в режим ЭУ
			ctrlCmdSwitchDUMode = 2,	// перевести устройство в режим ДУ
			ctrlCmdClearError = 32,	// сброс флагов предупреждений
			ctrlCmdClearWarning = 33	// сброс флагов ошибок
		} Commands;
	};

	// структура сообщения RETCONTROL
	struct RetControlDataFormat
	{
		u8 commandCode;
		u8 selfAddr;
		u8 result;		// результат (0 - команда принята, 1 - ком. не может
						// быть выполнена, 2 - ошибка при выполнении, 255 - ком.
						// не поддерживается)
		u16 leadTime;	// время выполнения в милисекундах (не используется)

		typedef enum
		{
			CommandAccepted = 0,
			CommandCanNotExec = 1,
			CommandError = 2,
			CommandNotSupported = 255
		} Result;
	};

	// структура сообщения REG_PARAM_1
	typedef struct
	{
		u16 currentWheelPosition;	// 0.0-1.2 - положение руля 0..2000
		u8 currentWrkMd_EU_DU;		// 1.3 - Текущий режим работы (0 – режим ЭУ, 1 – режим ДУ)
									// 1.4-1.7 - Резерв Void4 Заполняется нулями
		u8 currentTurnSpeed;		// 2.0-2.7 - Текущая скорость поворота руля
									// 3.0-7.7 - Резерв Void40 Заполняется нулями
	} RegParam_1_DataFormat;

	//
	typedef struct
	{
		// предельная уставка скорости в формате 2^16
		u8 L_1;		// byte0
		u8 L_0;		// byte1
		// коэффициент пропорционального звена в формате 2^Qp
		u8 Kp_1;	// byte2
		u8 Kp_0;	// byte3
		//
		u8 Qp;		// byte4
		// коэффициент интегрирующего звена в формате 2^Qi
		u8 Ki_1;	// byte5
		u8 Ki_0;	// byte6
		u8 Qi;		// byte7
	} RegParam_2_positionRegulator;

	//
	typedef struct
	{
		// предельная уставка скорости в формате 2^16
		u8 L_1;		// byte0
		u8 L_0;		// byte1
		// коэффициент пропорционального звена в формате 2^Qp
		u8 Kp_1;	// byte2
		u8 Kp_0;	// byte3
		//
		u8 Qp;		// byte4
		// коэффициент интегрирующего звена в формате 2^Qi
		u8 Ki_1;	// byte5
		u8 Ki_0;	// byte6
		u8 Qi;		// byte7
	} RegParam_2_speedRegulator;

}


#endif /* GAZ_EPS_PROTOCOL_MSG_H_ */
