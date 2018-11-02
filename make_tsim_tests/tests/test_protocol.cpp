#include "tests_management.h"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "can_mock_imp.h"
#include "../src/gaz_eps_protocol_imp.h"
#include "eps_mock.h"
#include "utils.h"
#include "../src/const.h"
#include "os.h"
#include "array.h"

#include "../src/can_message.h"
#include "../src/dev_state_maker.h"

#include <iostream>
using namespace std;

#define FILL_DATA_AND_SEND_MESSAGE(pf, ps)	{			\
		data64 = (((u16)(pf)) << 8) + (ps);				\
		protocolObj.dlIndication(REQUEST_ID,			\
				packData(data64, REQUEST_DATA_SIZE),	\
				REQUEST_DATA_SIZE);			    		\
}

u32 Os::Time::MockTime1::time = 0;

#if CONTROL_TESTS

// Тест установки режима сообщением CONTROL
// Условия - только что созданный и инициализированный mock-объект ЭУР
TEST_CASE( "Setting EPS mode by CONTROL message", "[control]" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);
	protocolObj.init(&mockCanObj, &mockEpsObj);

	u64 data64 = 0;

	Data data;

	// создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParams;
	// заполнение объекта RETCONTROL ID для сравнения с ответом
	expectedIdParams.pgn.pf = RETCONTROL_PF;
	expectedIdParams.pgn.ps = RETCONTROL_PS;
	expectedIdParams.priority = (MessagePriority)RETCONTROL_PRIORITY;
	expectedIdParams.sa = mockEpsObj.getId();
	u32 expectedId = composeCanId(&expectedIdParams);

	J1939idParams controlIdParams;
	controlIdParams.pgn.pf = CONTROL_PF;
	controlIdParams.pgn.ps = CONTROL_PS;
	controlIdParams.priority = (MessagePriority)CONTROL_PRIORITY;
	controlIdParams.sa = MCM_ID;
	u32 controlId = composeCanId(&controlIdParams);

	// данные, которые ожидаются в ответе NACK
	u64 answerData;

	// Изменить режим работы командой CONTROL
	// принять ответное сообщение RETCONTROL с подтверждением переключения
	// также проверить, переключился ли режим на самом деле.
	SECTION( "Change mode to WORKING and back to READY" ) {

		// перевести устройство в режим ДУ
		// (он же REMOTE_CONTROL)
		// (он же WORKING)
		data64 = COMMAND_CODE_STATE_WORKING;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_STATE_WORKING +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Установить последние принятые из протокола данные равными 0
		mockCanObj.setTxId(0);
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);

		// перевести устройство в режим ЭУ
		// (он же READY)
		// (он же NORMAL)
		data64 = COMMAND_CODE_STATE_READY;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// В ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_STATE_READY +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::NORMAL );
	}

	// Попытка передать данные, не описанные в протоколе
	// несуществующий режим работы
	SECTION( "Trying to set incorrect mode" ) {

		// отправка 0 в качестве команды
		// это может быть истолковано как команда перейти в
		// несуществующий режим, или как несуществующая команда
		// Регламентированы команды 1, 2, 32 и 33
		data64 = 0;

		// Выставляется режим работы WORKING
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL);

		// Выставляются все возможные флаги ошибок и предупреждений
		for( u8 i = 0; i <= 55; i++)
		{
			mockEpsObj.setError(i);
			mockEpsObj.setWarning(i);
		}

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 255(0xFF), "команда не поддерживается"
		answerData = data64 +
				((u32)RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Ожидается неизмененный режим ДУ
		// (он же WORKING)
		// (он же REMOTE_CONTROL)
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//------
		// отправка 3 в качестве команды
		data64 = 3;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 255(0xFF), "команда не поддерживается"
		answerData = data64 +
				((u32)RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Ожидается неизмененный режим ДУ
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//------
		// отправка 31 в качестве команды
		data64 = 31;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 255(0xFF), "команда не поддерживается"
		answerData = data64 +
				((u32)RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Ожидается неизмененный режим ДУ
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//------
		// отправка 34 в качестве команды
		data64 = 34;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 255(0xFF), "команда не поддерживается"
		answerData = data64 +
				((u32)RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Ожидается неизмененный режим ДУ
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//------
		// отправка максимального числа в качестве команды
		data64 = -1;

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 255(0xFF), "команда не поддерживается"
		answerData = (u8)data64 +
				((u32)RETCONTROL_RESULT_COMMAND_NOT_SUPPORTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Ожидается неизмененный режим ДУ
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
	}

	// Снятие флагов warnings
	SECTION( "Clear warnings" ) {

		// выставляем определенные флаги предупреждений
		// Во вновь инициализированном устройстве не ожидается ни одного флага
		u8 warn1Code = 0;
		u8 warn2Code = 1;
		u8 warn3Code = 55;
		mockEpsObj.setWarning(warn1Code);
		mockEpsObj.setWarning(warn2Code);
		mockEpsObj.setWarning(warn3Code);

		// снимаем флаг 3 предупреждения
		data64 = COMMAND_CODE_CLEAR_WARNING + ((u32)warn3Code << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_CLEAR_WARNING +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// ожидаем флаги предупреждений 1 и 2, но не снятый 3 (см. выше)
		REQUIRE( (u64)mockEpsObj.getWarningMask() == (((u64)1 << warn1Code) |
				((u64)1 << warn2Code)) );

		// снимаем все флаги (0)
		data64 = COMMAND_CODE_CLEAR_WARNING;

		// Установить последние принятые из протокола данные равными 0
		mockCanObj.setTxId(0);
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_CLEAR_WARNING +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// ожидаем все снятые флаги предупреждений
		REQUIRE( mockEpsObj.getWarningMask() == 0 );
	}

	// Снятие флагов errors
	SECTION( "Clear errors" ) {

		// выставляем определенные флаги ошибок
		// Во вновь инициализированном устройстве не ожидается ни одного флага
		u8 err1Code = 0;
		u8 err2Code = 1;
		u8 err3Code = 55;
		mockEpsObj.setError(err1Code);
		mockEpsObj.setError(err2Code);
		mockEpsObj.setError(err3Code);

		// снимаем флаг 3 предупреждения
		data64 = COMMAND_CODE_CLEAR_ERROR + ((u32)err3Code << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_CLEAR_ERROR +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// ожидаем флаги предупреждений 1 и 2, но не снятый 3 (см. выше)
		REQUIRE( mockEpsObj.getErrorMask() == (((u64)1 << err1Code)
				| ((u64)1 << err2Code)) );

		// снимаем все флаги (0)
		data64 = COMMAND_CODE_CLEAR_ERROR;

		// Установить последние принятые из протокола данные равными 0
		mockCanObj.setTxId(0);
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 0, "команда принята"
		answerData = COMMAND_CODE_CLEAR_ERROR +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// ожидаем все снятые флаги ошибок
		REQUIRE( mockEpsObj.getErrorMask() == 0 );
	}

	// Попытка снять несуществующий флаг предупреждения
	SECTION( "Clear incorrect warning flag" ) {

		// Выставляются все возможные флаги ошибок и предупреждений
		for( u8 i = 0; i <= 55; i++)
		{
			mockEpsObj.setError(i);
			mockEpsObj.setWarning(i);
		}

		// пытаемся снять флаг 56 предупреждения
		data64 = COMMAND_CODE_CLEAR_WARNING + ((u32)56 << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 1, "невозможно выполнить"
		answerData = COMMAND_CODE_CLEAR_WARNING +
				((u32)RETCONTROL_RESULT_UNABLE_TO_EXECUTE << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//-------
		// пытаемся снять максимально большой флаг предупреждения
		u32 impossibleWarnNum = -1;
		data64 = COMMAND_CODE_CLEAR_WARNING + (impossibleWarnNum << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 1, "невозможно выполнить"
		answerData = COMMAND_CODE_CLEAR_WARNING +
				((u32)RETCONTROL_RESULT_UNABLE_TO_EXECUTE << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
	}

	// Попытка снять несуществующий флаг ошибки
	SECTION( "Clear incorrect error flag" ) {

		// Выставляются все возможные флаги ошибок и предупреждений
		for( u8 i = 0; i <= 55; i++)
		{
			mockEpsObj.setError(i);
			mockEpsObj.setWarning(i);
		}

		// пытаемся снять флаг 56 предупреждения
		data64 = COMMAND_CODE_CLEAR_ERROR + ((u32)56 << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 1, "невозможно выполнить"
		answerData = COMMAND_CODE_CLEAR_ERROR +
				((u32)RETCONTROL_RESULT_UNABLE_TO_EXECUTE << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
		//-------
		// пытаемся снять максимально большой флаг ошибки
		u32 impossibleErrNum = -1;
		data64 = COMMAND_CODE_CLEAR_ERROR + (impossibleErrNum << 16);

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// в ответе содержится код команды и результат исполнения
		// результат - 1, "невозможно выполнить"
		answerData = COMMAND_CODE_CLEAR_ERROR +
				((u32)RETCONTROL_RESULT_UNABLE_TO_EXECUTE << 16);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Флаги ошибок и предупреждений должны быть неизменно выставлены все
		REQUIRE( mockEpsObj.getErrorMask() ==
				0xFFFFFFFFFFFFFF );
		REQUIRE( mockEpsObj.getWarningMask() ==
				0xFFFFFFFFFFFFFF );
	}
}
#endif

#if ERRORS_TESTS

TEST_CASE( "Multiple errors case" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);

	// Установить время равным нулю
	Os::Time::MockTime1::setTime(0);

	protocolObj.init(&mockCanObj, &mockEpsObj);

	u64 data64 = 0;

	Data data;

	// создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParams;
	// заполнение объекта ID для сравнения с ответом
	expectedIdParams.pgn.pf = ERRORS_PF;
	expectedIdParams.pgn.ps = ERRORS_PS;
	expectedIdParams.priority = (MessagePriority)ERRORS_PRIORITY;
	expectedIdParams.sa = mockEpsObj.getId();
	u32 expectedId = composeCanId(&expectedIdParams);

	// данные, которые ожидаются в ответе NACK
	u64 answerData;

	SECTION( "One error" ) {

		// Сообщений не ожидается
		REQUIRE( mockCanObj.getTxId() == 0 );
		REQUIRE( mockCanObj.getTxData() == 0 );
		REQUIRE( mockCanObj.getTxDlc() == 0 );

		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 0 );

		// Выставляем флаг ошибки
		u8 err1Code = 18;
		mockEpsObj.setError(err1Code);

		// Обновление времени
		protocolObj.timeUpdate();

		// В ответе содержится номер появившейся ошибки и битовая маска
		answerData = (err1Code) +
				((u64)1 << (err1Code + 8));

		// Сравнение
		CHECK( mockCanObj.getTxId() == expectedId );
		CHECK( mockCanObj.getTxData() == answerData );
		CHECK( mockCanObj.getTxDlc() == ERRORS_DATA_SIZE );
		// Ожидается одно сообщение
		CHECK( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	SECTION( "Some errors" ) {

		// Сообщений не ожидается
		REQUIRE( mockCanObj.getTxId() == 0 );
		REQUIRE( mockCanObj.getTxData() == 0 );
		REQUIRE( mockCanObj.getTxDlc() == 0 );

		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 0 );

		// Выставляем флаги ошибок
		u8 err1Code = 3;
		u8 err2Code = 7;
		u8 err3Code = 0xA;
		mockEpsObj.setError(err1Code);
		mockEpsObj.setError(err2Code);
		mockEpsObj.setError(err3Code);

		// Обновление времени
		protocolObj.timeUpdate();

		// В ответе содержится номер появившейся ошибки и битовая маска
		answerData = (err3Code) +
				((u64)1 << (err1Code + 8)) +
				((u64)1 << (err2Code + 8)) +
				((u64)1 << (err3Code + 8));

		// Сравнение
		CHECK( mockCanObj.getTxId() == expectedId );
		CHECK( mockCanObj.getTxData() == answerData );
		CHECK( mockCanObj.getTxDlc() == ERRORS_DATA_SIZE );
		// Ожидается три сообщения
		CHECK( mockCanObj.getDlRequestCallsCnt() == 3 );
	}
}
#endif

#if REGPARAMS_TESTS

// Тест запроса нескольких регистров телеметрии
TEST_CASE( "Requesting all REG_PARAMs" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);
	protocolObj.init(&mockCanObj, &mockEpsObj);

	u64 data64 = 0;

	Data data;

	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedId1Params;
	// Заполнение объекта REG_PARAM_1 ID для сравнения с ответом
	expectedId1Params.pgn.pf = REGPARAM1_PF;
	expectedId1Params.pgn.ps = REGPARAM1_PS;
	expectedId1Params.priority = (MessagePriority)REGPARAM1_PRIORITY;
	expectedId1Params.sa = mockEpsObj.getId();
	u32 expectedId1 = composeCanId(&expectedId1Params);

	J1939idParams expectedId2Params;
	// Заполнение объекта REG_PARAM_2 ID для сравнения с ответом
	expectedId2Params.pgn.pf = REGPARAM2_PF;
	expectedId2Params.pgn.ps = REGPARAM2_PS;
	expectedId2Params.priority = (MessagePriority)REGPARAM2_PRIORITY;
	expectedId2Params.sa = mockEpsObj.getId();
	u32 expectedId2 = composeCanId(&expectedId2Params);

	J1939idParams expectedId3Params;
	// Заполнение объекта REG_PARAM_3 ID для сравнения с ответом
	expectedId3Params.pgn.pf = REGPARAM3_PF;
	expectedId3Params.pgn.ps = REGPARAM3_PS;
	expectedId3Params.priority = (MessagePriority)REGPARAM3_PRIORITY;
	expectedId3Params.sa = mockEpsObj.getId();
	u32 expectedId3 = composeCanId(&expectedId3Params);

	J1939idParams syncParamIdParams;
	syncParamIdParams.pgn.pf = SYNCPARAM_PF;
	syncParamIdParams.pgn.ps = SYNCPARAM_PS;
	syncParamIdParams.priority = (MessagePriority)SYNCPARAM_PRIORITY;
	syncParamIdParams.sa = MCM_ID;
	u32 syncParamId = composeCanId(&syncParamIdParams);

	J1939PGN requestingPgn;

	// Данные, которые ожидаются в ответе
	u64 answerData;

	// Нормальный запрос регистра телеметрии
	SECTION( "Requesting all REG_PARAMs in a normal way" ) {

		mockCanObj.setDlRequestCallsCnt(0);

		u8 newSpeedValue = 74;
		u16 newWheelValue = 1864;

		mockEpsObj.setSteeringSpeed(newSpeedValue);
		mockEpsObj.setSteeringWheelPosition(newWheelValue);
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL);

		u64 testPidPos = 0xA561ABAFD4156658;
		u64 testPidSpeed = 0xA4BEA8794A987BAD;

		mockEpsObj.setPidTermsPosition(testPidPos);
		mockEpsObj.setPidTermsSpeed(testPidSpeed);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				0);

		answerData = newWheelValue +
				((u32)GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL << 11) +
				((u32)newSpeedValue << 16);

		// Ожидается 3 пакета
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 3 );

		// Сравнение
		REQUIRE( mockCanObj.getRegParamId(1) == expectedId1 );
		REQUIRE( mockCanObj.getRegParamData(1) == answerData );
		REQUIRE( mockCanObj.getRegParamDlc(1) == REGPARAM1_DATA_SIZE );

		answerData = testPidPos;
		REQUIRE( mockCanObj.getRegParamId(2) == expectedId2 );
		REQUIRE( mockCanObj.getRegParamData(2) == answerData );
		REQUIRE( mockCanObj.getRegParamDlc(2) == REGPARAM2_DATA_SIZE );

		answerData = testPidSpeed;
		REQUIRE( mockCanObj.getRegParamId(3) == expectedId3 );
		REQUIRE( mockCanObj.getRegParamData(3) == answerData );
		REQUIRE( mockCanObj.getRegParamDlc(3) == REGPARAM3_DATA_SIZE );
	}
}

#endif

#if REQUEST_TESTS

// Тест обработки пришедшего сообщения REQUEST
// Условия - только что созданный и инициализированный mock-объект ЭУР
TEST_CASE( "Answers for REQUEST messages", "[request]" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);
	protocolObj.init( &mockCanObj, &mockEpsObj);

	u64 data64 = 0;

	Data data;

	// Создание объекта PGN для запроса
	J1939PGN requestedPgn;

	// Данные, которые ожидаются в ответе
	u64 answerData;

	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParams;
	expectedIdParams.sa = mockEpsObj.getId();

	// На запрос не описанного в протоколе PGN должен приходить NACK
	SECTION( "NACK answer to REQUEST with unsupported PGN in data" ) {

		// Формируется запрос не описанного PGN
		// Запросим SYNC_CTRL PGN - на него заведомо не должно быть ответа
		requestedPgn.pf = SYNCCTRL_PF;
		requestedPgn.ps = SYNCCTRL_PS;

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Заполнение объекта NACK ID для сравнения с ответом
		expectedIdParams.pgn.pf = NACK_PF;
		expectedIdParams.pgn.ps = NACK_PS;
		expectedIdParams.priority = (MessagePriority)NACK_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		// Данные, которые ожидаются в ответе NACK
		answerData =	((u64)NACK_FILL << 8) |
				((u64)requestedPgn.ps << 40) |
				((u64)requestedPgn.pf << 48) |
				((u64)NACK_CONTROLBYTE << 0);

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );
	}

	// Запрос флагов WARNINGS
	SECTION( "Requesting WARNINGS message" ) {

		// Формируется запрос PGN флагов предупреждений
		requestedPgn.pf = WARNINGS_PF;
		requestedPgn.ps = WARNINGS_PS;

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Заполнение объекта WARNINGS ID для сравнения с ответом
		expectedIdParams.pgn.pf = requestedPgn.pf;
		expectedIdParams.pgn.ps = requestedPgn.ps;
		expectedIdParams.priority = (MessagePriority)WARNINGS_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		answerData = 0;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == WARNINGS_DATA_SIZE );

		// Проверка установки флагов предупреждений
		// warnNum3 превышает максимально возможное количество флагов
		u8 warnNum1 = 54;
		u8 warnNum2 = 55;
		u8 warnNum3 = 56;

		mockEpsObj.setWarning(warnNum1);
		mockEpsObj.setWarning(warnNum2);
		mockEpsObj.setWarning(warnNum3);

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Проверка, что в ответе содержатся флаги 1 и 2, но не 3
		answerData = ((u64)1 << (warnNum1 + 8)) |
		((u64)1 << (warnNum2 + 8));

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == WARNINGS_DATA_SIZE );

	}

	// Запрос флагов ERRORS
	SECTION( "Requesting ERRORS message" ) {

		// Формируется запрос PGN флагов предупреждений
		requestedPgn.pf = ERRORS_PF;
		requestedPgn.ps = ERRORS_PS;

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Заполнение объекта WARNINGS ID для сравнения с ответом
		expectedIdParams.pgn.pf = requestedPgn.pf;
		expectedIdParams.pgn.ps = requestedPgn.ps;
		expectedIdParams.priority = (MessagePriority)ERRORS_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		answerData = 0;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == ERRORS_DATA_SIZE );

		// Проверка установки флагов ошибок
		u8 errNum1 = 54;
		u8 errNum2 = 55;
		u8 errNum3 = 56;

		mockEpsObj.setError(errNum1);
		mockEpsObj.setError(errNum2);
		mockEpsObj.setError(errNum3);

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Проверка, что в ответе содержатся флаги 1 и 2, но не 3
		answerData = ((u64)1 << (errNum1 + 8)) |
		((u64)1 << (errNum2 + 8));

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == ERRORS_DATA_SIZE );
	}

	// Запрос сообщения PROGRAM_INFO
	SECTION( "Requesting PROGRAM_INFO message" ) {

		// Формируется запрос PGN флагов предупреждений
		requestedPgn.pf = PROGRAMINFO_PF;
		requestedPgn.ps = PROGRAMINFO_PS;

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Заполнение объекта PROGRAM_INFO ID для сравнения с ответом
		expectedIdParams.pgn.pf = requestedPgn.pf;
		expectedIdParams.pgn.ps = requestedPgn.ps;
		expectedIdParams.priority = (MessagePriority)PROGRAMINFO_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		answerData = 0;

		EPASVersion requiredVersion;
		u32 requiredHashsum;
		mockEpsObj.getVersion(requiredVersion.major,
				requiredVersion.minor, requiredVersion.revision,
				requiredHashsum);

		answerData = (u64)requiredHashsum << 0;

		answerData |= ((u64)requiredVersion.major << 32);
		answerData |= ((u64)requiredVersion.minor << 40);
		answerData |= ((u64)requiredVersion.revision << 48);

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == PROGRAMINFO_DATA_SIZE );
	}

	// Запрос сообщения DEVSTATE
	SECTION( "Requesting DEVSTATE message" ) {

		// Формируется запрос PGN флагов предупреждений
		requestedPgn.pf = DEVSTATE_PF;
		requestedPgn.ps = DEVSTATE_PS;

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		// Заполнение объекта PROGRAM_INFO ID для сравнения с ответом
		expectedIdParams.pgn.pf = requestedPgn.pf;
		expectedIdParams.pgn.ps = requestedPgn.ps;
		expectedIdParams.priority = (MessagePriority)DEVSTATE_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		GazEpsProtocol::User::Mode::Enum mode = mockEpsObj.getMode();
		u64 stateCode;

		switch(mode)
		{
		case GazEpsProtocol::User::Mode::Enum::NORMAL:
			stateCode = (u64)STATE_READY;
			break;
		case GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL:
			stateCode = (u64)STATE_WORKING;
			break;
		case GazEpsProtocol::User::Mode::Enum::FAILURE:
			stateCode = (u64)STATE_NOTREADY;
			break;
		default:
			break;
		}

		// Режим работы устройства
		// после инициализации должен быть READY
		answerData = stateCode;

		// Код технического состояния устройства, полученный
		// в результате последнего проведения процедуры самодиагностики
		answerData |= (u64)DEVSTATE_SELFDIAG_ALL_OK << 12;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == DEVSTATE_DATA_SIZE );

		// Установить принудительно режим FAILURE (NOT_READY)
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::FAILURE);

		// Установить последние принятые из протокола данные равными 0
		mockCanObj.setTxId(0);
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);

		FILL_DATA_AND_SEND_MESSAGE(requestedPgn.pf, requestedPgn.ps)

		mode = mockEpsObj.getMode();

		switch(mode)
		{
		case GazEpsProtocol::User::Mode::Enum::NORMAL:
			stateCode = (u64)STATE_READY;
			break;
		case GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL:
			stateCode = (u64)STATE_WORKING;
			break;
		case GazEpsProtocol::User::Mode::Enum::FAILURE:
			stateCode = (u64)STATE_NOTREADY;
			break;
		default:
			break;
		}

		// Режим работы устройства
		// должен быть FAILURE (NOT_READY)
		answerData = stateCode;

		// Код технического состояния устройства, полученный
		// в результате последнего проведения процедуры самодиагностики
		answerData |= (u64)DEVSTATE_SELFDIAG_ALL_OK << 12;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		CHECK( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == DEVSTATE_DATA_SIZE );

		// Ожидаем именно состояние неготовности
		u64 failureMode;
		failureMode = STATE_NOTREADY;
		failureMode |= (u64)DEVSTATE_SELFDIAG_ALL_OK << 12;
		REQUIRE( mockCanObj.getTxData() ==  failureMode);
	}
}
#endif

#if TIME_TESTS

// Проверка ситуаций, связанных с потерей управления
TEST_CASE( "Connection timeouts" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);

	// Установить время равным нулю
	Os::Time::MockTime1::setTime(0);

	protocolObj.init( &mockCanObj, &mockEpsObj);

	J1939idParams syncCtrlIdParams;
	syncCtrlIdParams.pgn.pf = SYNCCTRL_PF;
	syncCtrlIdParams.pgn.ps = SYNCCTRL_PS;
	syncCtrlIdParams.priority = (MessagePriority)SYNCCTRL_PRIORITY;
	syncCtrlIdParams.sa = MCM_ID;
	u32 syncCtrlId = composeCanId(&syncCtrlIdParams);

	J1939idParams regCtrl1IdParams;
	regCtrl1IdParams.pgn.pf = REGCTRL1_PF;
	regCtrl1IdParams.pgn.ps = REGCTRL1_PS;
	regCtrl1IdParams.priority = (MessagePriority)REGCTRL1_PRIORITY;
	regCtrl1IdParams.sa = MCM_ID;
	u32 regCtrl1Id = composeCanId(&regCtrl1IdParams);

	// создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParamsRetControl;
	// заполнение объекта RETCONTROL ID для сравнения с ответом
	expectedIdParamsRetControl.pgn.pf = RETCONTROL_PF;
	expectedIdParamsRetControl.pgn.ps = RETCONTROL_PS;
	expectedIdParamsRetControl.priority = (MessagePriority)RETCONTROL_PRIORITY;
	expectedIdParamsRetControl.sa = mockEpsObj.getId();
	u32 expectedId = composeCanId(&expectedIdParamsRetControl);

	J1939idParams controlIdParams;
	controlIdParams.pgn.pf = CONTROL_PF;
	controlIdParams.pgn.ps = CONTROL_PS;
	controlIdParams.priority = (MessagePriority)CONTROL_PRIORITY;
	controlIdParams.sa = MCM_ID;
	u32 controlId = composeCanId(&controlIdParams);

	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParams;
	expectedIdParams.sa = mockEpsObj.getId();

	Data data;

	SECTION( "Lost of SYNC_CTRL" ) {

		// переключить объект ЭУР в режим дист. управления
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL);

		// установить положение руля 0%
		u64 data64 = 1000;

		// установить cкорость поворота руля 0%
		data64 |= 0 << 16;

		// вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// Отправлен SYNC_CTRL
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// Отсчитать менее, чем таймаут потери связи
		Os::Time::MockTime1::setTime(1000);
		// вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// Не ожидается ни одной посылки
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 0 );

		REQUIRE( mockCanObj.getTxId() == 0 );
		REQUIRE( mockCanObj.getTxData() == 0 );
		REQUIRE( mockCanObj.getTxDlc() == 0 );

		// Установить время
		Os::Time::MockTime1::setTime(1001);
		// Вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// Отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// отправлен SYNC_CTRL
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();
		// отсчитать чуть больше
		Os::Time::MockTime1::setTime(2002);
		// вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// Ожидается номер последней ошибки 1 (нумерация с единицы)
		// И первый бит флагов
		u64 answerData = 1 + (1 << 8);

		expectedIdParams.pgn.pf = ERRORS_PF;
		expectedIdParams.pgn.ps = ERRORS_PS;
		expectedIdParams.priority = (MessagePriority)ERRORS_PRIORITY;
		u32 expectedId = composeCanId(&expectedIdParams);

		// Сравнение с пакетом ERRORS
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == ERRORS_DATA_SIZE );

		// Ожидается режим READY
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::NORMAL );

		// Ожидается одна посылка
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	SECTION( "CAN TX malfunctioning" ) {

		// Переключить объект ЭУР в режим дист. управления
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL);

		// Команда "очистить флаги предупреждений
		u64 data64 = COMMAND_CODE_CLEAR_WARNING;

		// Отключить отправку dlConfirm()
		mockCanObj.setTestMode(true);

		// Вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// В ответе содержится код команды и результат исполнения
		// Результат - 0, "команда принята"
		u64 answerData = COMMAND_CODE_CLEAR_WARNING +
				((u32)RETCONTROL_RESULT_ACCEPTED << 16);

		// Сравнение
		// Пришел ответ - команда принята
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == RETCONTROL_DATA_SIZE );

		// Установить время, вплотную приближенное к таймауту
		Os::Time::MockTime1::setTime(9);
		// Вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// Режим - всё ещё WORKING
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL );

		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);
		mockCanObj.setTxId(0);

		// Установить время большее, чем таймаут потери подтверждения
		Os::Time::MockTime1::setTime(10);
		// Вызвать обновление таймера в протоколе
		protocolObj.timeUpdate();

		// Режим cменился на READY
		REQUIRE( mockEpsObj.getMode() ==
				GazEpsProtocol::User::Mode::Enum::NORMAL );

		// CONTROL отправлен
		protocolObj.dlIndication(controlId,
				packData(data64, CONTROL_DATA_SIZE),
				CONTROL_DATA_SIZE);

		// Сравнение
		// Ответ так и не пришёл
		REQUIRE( mockCanObj.getTxId() == 0 );
		REQUIRE( mockCanObj.getTxData() == 0 );
		REQUIRE( mockCanObj.getTxDlc() == 0 );
		//--------------------------------------------------------------------
	}
}
#endif

#if SYNCCTRL_TESTS

// Тест установки технологических параметров сообщением REG_CTRL_1
// Условия - только что созданный и инициализированный mock-объект ЭУР
TEST_CASE( "Setting params by SYNC_CTRL and REG_CTRL_1", "[sync_ctrl]" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);
	protocolObj.init(&mockCanObj, &mockEpsObj);

	Data data;

	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedIdParams;
	// Заполнение объекта NACK ID для сравнения с ответом
	expectedIdParams.pgn.pf = NACK_PF;
	expectedIdParams.pgn.ps = NACK_PS;
	expectedIdParams.priority = (MessagePriority)NACK_PRIORITY;
	expectedIdParams.sa = mockEpsObj.getId();
	u32 expectedId = composeCanId(&expectedIdParams);

	J1939idParams syncCtrlIdParams;
	syncCtrlIdParams.pgn.pf = SYNCCTRL_PF;
	syncCtrlIdParams.pgn.ps = SYNCCTRL_PS;
	syncCtrlIdParams.priority = (MessagePriority)SYNCCTRL_PRIORITY;
	syncCtrlIdParams.sa = MCM_ID;
	u32 syncCtrlId = composeCanId(&syncCtrlIdParams);

	J1939idParams regCtrl1IdParams;
	regCtrl1IdParams.pgn.pf = REGCTRL1_PF;
	regCtrl1IdParams.pgn.ps = REGCTRL1_PS;
	regCtrl1IdParams.priority = (MessagePriority)REGCTRL1_PRIORITY;
	regCtrl1IdParams.sa = MCM_ID;
	u32 regCtrl1Id = composeCanId(&regCtrl1IdParams);

	J1939idParams regCtrl2IdParams;
	regCtrl2IdParams.pgn.pf = REGCTRL2_PF;
	regCtrl2IdParams.pgn.ps = REGCTRL2_PS;
	regCtrl2IdParams.priority = (MessagePriority)REGCTRL2_PRIORITY;
	regCtrl2IdParams.sa = MCM_ID;
	u32 regCtrl2Id = composeCanId(&regCtrl2IdParams);

	J1939idParams regCtrl3IdParams;
	regCtrl3IdParams.pgn.pf = REGCTRL3_PF;
	regCtrl3IdParams.pgn.ps = REGCTRL3_PS;
	regCtrl3IdParams.priority = (MessagePriority)REGCTRL3_PRIORITY;
	regCtrl3IdParams.sa = MCM_ID;
	u32 regCtrl3Id = composeCanId(&regCtrl3IdParams);

	// данные, которые ожидаются в ответе NACK
	u64 answerData;
	answerData =	((u64)NACK_FILL << 8) |
			((u64)syncCtrlIdParams.pgn.ps << 40) |
			((u64)syncCtrlIdParams.pgn.pf << 48) |
			((u64)NACK_CONTROLBYTE << 0);

	// переключим mock-ЭУР в режим WORKING (aka REMOTE_CONTROL)
	mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::REMOTE_CONTROL);

	// В ответ на SYNC_CTRL ожидается NACK,
	// если с момента предыдущего приёма сообщения SYNC_CTRL
	// не было получено сообщение REG_CTRL_1
	SECTION( "There was no REG_CTRL_1 since last SYNC_CTRL" ) {

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );
	}

	// отправка регистра управления, затем SYNC_CTRL
	// затем проверка, установлены ли значения
	SECTION( "Setting values in a normal way" ) {

		// в ЭУР после инициализации ожидаются параметры, равные нулю
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == 0.0f);
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.0f);

		// установить положение руля +10%
		u64 data64 = 1100;

		// установить cкорость поворота руля 55%
		data64 |= 55 << 16;

		// отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == 0.1f );
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.55f );

		// установить положение руля -12.3%
		data64 = 877;

		// установить cкорость поворота руля 99%
		data64 |= 99 << 16;

		// отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == -0.123f );
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.99f );
	}

	// Тест на некорректную длину DLC
	SECTION( "Setting values with wrong DLC" ) {

		// в ЭУР после инициализации ожидаются параметры, равные нулю
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == 0.0f);
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.0f);

		// установить положение руля +10%
		u64 data64 = 1100;

		// установить cкорость поворота руля 55%
		data64 |= 55 << 16;

		// отправлен REG_CTRL_1 с нулем в dlc
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				0);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		// Изменений быть не должно
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == 0.0f );
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.0f );
	}

	// отправка регистра управления с коэффициентами, затем SYNC_CTRL
	// затем проверка, установлены ли значения
	SECTION( "Setting PID values in a normal way" ) {

		// в ЭУР после инициализации ожидаются параметры, равные нулю
		REQUIRE( mockEpsObj.getPidTermsPosition() == 0);
		REQUIRE( mockEpsObj.getPidTermsSpeed() == 0);

		// Установка коэффициентов ПИ-регулятора положения
		// Установить коэффициенты
		u64 data64 = 0x1337 +
				((u64)0xBABA07 << 16) +
				((u64)0xFACE69 << 40);

		// отправлен REG_CTRL_2
		protocolObj.dlIndication(regCtrl2Id,
				packData(data64, REGCTRL2_DATA_SIZE),
				REGCTRL2_DATA_SIZE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		REQUIRE( mockEpsObj.getPidPositionSpeedLimit() == 0x1337 );
		REQUIRE( mockEpsObj.getPidPositionProportionalTerm() == 0xBABA07 );
		REQUIRE( mockEpsObj.getPidPositionIntegralTerm() == 0xFACE69 );

		// Установка коэффициентов ПИ-регулятора скорости
		data64 = 0x0102 +
				((u64)0x030405 << 16) +
				((u64)0x060708 << 40);

		// отправлен REG_CTRL_3
		protocolObj.dlIndication(regCtrl3Id,
				packData(data64, REGCTRL3_DATA_SIZE),
				REGCTRL3_DATA_SIZE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение
		REQUIRE( mockEpsObj.getPidSpeedMomentumLimit() == 0x0102 );
		REQUIRE( mockEpsObj.getPidSpeedProportionalTerm()  == 0x030405 );
		REQUIRE( mockEpsObj.getPidSpeedIntegralTerm() == 0x060708 );
	}

	// попытка установить некорректные значения
	SECTION( "Trying to set incorrect values, waiting NACK" ) {

		// установить положение руля +101%
		u64 data64 = 2010;

		// отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// в ответ ожидается NACK
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );

		// и значение не должно быть изменено
		REQUIRE( mockEpsObj.getSteeringWheelPosition() == 0.0f);

		// установить скорость изменения положения руля 115%
		data64 = 1000 + (115 << 16);

		// отправлен REG_CTRL_1
		protocolObj.dlIndication(regCtrl1Id,
				packData(data64, REGCTRL1_DATA_SIZE),
				REGCTRL1_DATA_SIZE);

		fillDataByZeros(data);

		// Установить последние принятые из протокола данные равными 0
		mockCanObj.setTxId(0);
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// в ответ ожидается NACK
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );

		// и значение не должно быть изменено
		REQUIRE( mockEpsObj.getSteeringWheelSpeed() == 0.0f);
	}

	// если режим не WORKING, то на SYNC_CTRL должен приходить ответ NACK
	SECTION( "Try to send SYNC_CTRL when not in 'working' mode" ) {

		// переключим режим в FAILURE
		mockEpsObj.setState(GazEpsProtocol::User::Mode::Enum::FAILURE);

		fillDataByZeros(data);

		// SYNC_CTRL отправлен
		protocolObj.dlIndication(syncCtrlId, data, SYNCCTRL_DATA_SIZE);

		// сравнение с NACK
		REQUIRE( mockCanObj.getTxId() == expectedId );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );
	}
}
#endif

#if SYNCPARAM_TESTS

// Тест запроса регистров телеметрии
TEST_CASE( "Requesting REG_PARAMs", "[sync_param]" )
{
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;
	GazEpsProtocolImp::ProtocolLayer<Os::Time> protocolObj;

	mockCanObj.init(&protocolObj);
	protocolObj.init(&mockCanObj, &mockEpsObj);

	u64 data64 = 0;

	Data data;

	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedId1Params;
	// Заполнение объекта REG_PARAM_1 ID для сравнения с ответом
	expectedId1Params.pgn.pf = REGPARAM1_PF;
	expectedId1Params.pgn.ps = REGPARAM1_PS;
	expectedId1Params.priority = (MessagePriority)REGPARAM1_PRIORITY;
	expectedId1Params.sa = mockEpsObj.getId();
	u32 expectedId1 = composeCanId(&expectedId1Params);

	J1939idParams expectedId2Params;
	// Заполнение объекта REG_PARAM_2 ID для сравнения с ответом
	expectedId2Params.pgn.pf = REGPARAM2_PF;
	expectedId2Params.pgn.ps = REGPARAM2_PS;
	expectedId2Params.priority = (MessagePriority)REGPARAM2_PRIORITY;
	expectedId2Params.sa = mockEpsObj.getId();
	u32 expectedId2 = composeCanId(&expectedId2Params);

	J1939idParams expectedId3Params;
	// Заполнение объекта REG_PARAM_3 ID для сравнения с ответом
	expectedId3Params.pgn.pf = REGPARAM3_PF;
	expectedId3Params.pgn.ps = REGPARAM3_PS;
	expectedId3Params.priority = (MessagePriority)REGPARAM3_PRIORITY;
	expectedId3Params.sa = mockEpsObj.getId();
	u32 expectedId3 = composeCanId(&expectedId3Params);

	J1939idParams syncParamIdParams;
	syncParamIdParams.pgn.pf = SYNCPARAM_PF;
	syncParamIdParams.pgn.ps = SYNCPARAM_PS;
	syncParamIdParams.priority = (MessagePriority)SYNCPARAM_PRIORITY;
	syncParamIdParams.sa = MCM_ID;
	u32 syncParamId = composeCanId(&syncParamIdParams);

	J1939PGN requestingPgn;

	// Данные, которые ожидаются в ответе
	u64 answerData;

	// Нормальный запрос регистра телеметрии
	// В данных запроса - PGN регистра REG_PARAM_1
	SECTION( "Requesting REG_PARAM_1 in a normal way, with PGN in data" ) {

		requestingPgn.pf = REGPARAM1_PF;
		requestingPgn.ps = REGPARAM1_PS;
		u8 requestedLen = 1;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		// Ожидаемые данные ответа во вновь созданном mock-экземпляре ЭУР:
		// Положение руля - 1000 (с нулевого бита)
		// Текущий режим работы - 0 (ЭУ/READY) (с 11 бита)
		// Текущая скорость поворота руля - 0 (с 16 бита)
		answerData = 1000;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId1 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM1_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	// Нормальный запрос регистра телеметрии
	// В данных запроса - PGN регистра REG_PARAM_2
	SECTION( "Requesting REG_PARAM_2 in a normal way, with PGN in data" ) {

		requestingPgn.pf = REGPARAM2_PF;
		requestingPgn.ps = REGPARAM2_PS;
		u8 requestedLen = 1;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		// Ожидаемые данные ответа во вновь созданном mock-экземпляре ЭУР
		answerData = 0;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId2 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM2_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );

		// Очистить счетчик принятых пакетов
		mockCanObj.setDlRequestCallsCnt(0);
		// Очистить принятые данные
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);
		mockCanObj.setTxId(0);

		u16 testDataLimit =		0x5145;
		u32 testDataProp =		0x5ab4a5;
		u32 testDataIntegr =	0x6dfa14;

		mockEpsObj.setPidPositionSpeedLimit(testDataLimit);
		mockEpsObj.setPidPositionProportionalTerm(testDataProp);
		mockEpsObj.setPidPositionIntegralTerm(testDataIntegr);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		answerData = testDataLimit +
				((u64)testDataProp << 16) +
				((u64)testDataIntegr << 40);

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId2 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM2_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	// Нормальный запрос регистра телеметрии
	// В данных запроса - PGN регистра REG_PARAM_3
	SECTION( "Requesting REG_PARAM_3 in a normal way, with PGN in data" ) {

		requestingPgn.pf = REGPARAM3_PF;
		requestingPgn.ps = REGPARAM3_PS;
		u8 requestedLen = 1;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		// Ожидаемые данные ответа во вновь созданном mock-экземпляре ЭУР
		answerData = 0;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId3 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM3_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );

		// Очистить счетчик принятых пакетов
		mockCanObj.setDlRequestCallsCnt(0);
		// Очистить принятые данные
		mockCanObj.setTxData(0);
		mockCanObj.setTxDlc(0);
		mockCanObj.setTxId(0);

		u16 testDataLimit =		0x8942;
		u32 testDataProp =		0x651203;
		u32 testDataIntegr =	0x361531;

		mockEpsObj.setPidSpeedMomentumLimit(testDataLimit);
		mockEpsObj.setPidSpeedProportionalTerm(testDataProp);
		mockEpsObj.setPidSpeedIntegralTerm(testDataIntegr);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		answerData = testDataLimit +
				((u64)testDataProp << 16) +
				((u64)testDataIntegr << 40);

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId3 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM3_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	// Нормальный запрос регистра телеметрии
	// В данных запроса - PGN регистра REG_PARAM_1
	// Количество PGN неверное
	// TODO: согласно протоколу, необходимо возвращать не один регистр, а все
	SECTION( "Requesting REG_PARAM_1, with PGN in data and incorrect length" ) {

		requestingPgn.pf = REGPARAM1_PF;
		requestingPgn.ps = REGPARAM1_PS;
		u8 requestedLen = 0xFF;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		// Ожидаемые данные ответа во вновь созданном mock-экземпляре ЭУР:
		// Положение руля - 1000 (с нулевого бита)
		// Текущий режим работы - 0 (ЭУ/READY) (с 11 бита)
		// Текущая скорость поворота руля - 0 (с 16 бита)
		answerData = 1000;

		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 3 );

		// Сравнение
		REQUIRE( mockCanObj.getRegParamId(1) == expectedId1 );
		REQUIRE( mockCanObj.getRegParamData(1) == answerData );
		REQUIRE( mockCanObj.getRegParamDlc(1) == REGPARAM1_DATA_SIZE );

        answerData = 0;
        REQUIRE( mockCanObj.getRegParamId(2) == expectedId2 );
        REQUIRE( mockCanObj.getRegParamData(2) == answerData );
        REQUIRE( mockCanObj.getRegParamDlc(2) == REGPARAM2_DATA_SIZE );

        REQUIRE( mockCanObj.getRegParamId(3) == expectedId3 );
        REQUIRE( mockCanObj.getRegParamData(3) == answerData );
        REQUIRE( mockCanObj.getRegParamDlc(3) == REGPARAM3_DATA_SIZE );

		mockCanObj.setDlRequestCallsCnt(0);

		// Количество запрашиваемых регистров - ноль,
		// но при этом есть запрашиваемый PGN
		requestedLen = 0;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		answerData = 1000;

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId1 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == REGPARAM1_DATA_SIZE );

		// Ожидается только один принятый регистр
		REQUIRE( mockCanObj.getDlRequestCallsCnt() == 1 );
	}

	// Запрос регистра телеметрии
	// В данных запроса - неверный PGN
	SECTION( "Requesting wrong PGN" ) {

		requestingPgn.pf = NACK_PF;
		requestingPgn.ps = NACK_PS;
		u8 requestedLen = 1;

		data64 = ((u16)requestingPgn.pf << 8) +
				requestingPgn.ps +
				((u32)requestedLen << 24);

		mockCanObj.setDlRequestCallsCnt(0);

		// SYNC_PARAM отправлен
		protocolObj.dlIndication(syncParamId,
				packData(data64, SYNCPARAM_DATA_SIZE),
				SYNCPARAM_DATA_SIZE);

		// На запрос несуществующего регистра ожидается ответ NACK
		expectedId1Params.pgn.pf = NACK_PF;
		expectedId1Params.pgn.ps = NACK_PS;
		expectedId1Params.priority = (MessagePriority)NACK_PRIORITY;
		expectedId1 = composeCanId(&expectedId1Params);

		// Данные, которые ожидаются в ответе NACK
		answerData =	((u64)NACK_FILL << 8) |
				((u64)syncParamIdParams.pgn.ps << 40) |
				((u64)syncParamIdParams.pgn.pf << 48) |
				((u64)NACK_CONTROLBYTE << 0);

		// Сравнение
		REQUIRE( mockCanObj.getTxId() == expectedId1 );
		REQUIRE( mockCanObj.getTxData() == answerData );
		REQUIRE( mockCanObj.getTxDlc() == NACK_DATA_SIZE );
	}
}

#endif

#if AB_TEST

TEST_CASE( "ProtocolLayer.init()", "[request]" )
{
	GazEpsProtocolImp::CanIdClass idObj(PRIOR_LO, PF_DEVSTATE, 0, 0x87);
	u32 id;


	SECTION( "Test CanIdClass" )
	{
		//idObj.ValidateId(0x0CEA8782, 0X87);
		id = 0x0CEA8782;
		// TODO: понять, 0x82 или всё же 0x87?
		CHECK( idObj.ValidateId(0x87) == true );
		CHECK( idObj.ValidateId(0x80) == false );
		id = 0;
		CHECK( idObj.ValidateId(0x82) == false );

		id = idObj.getIdAsU32();
		CHECK( id == 0x18F80087 );

	}

	GazEpsProtocolImp::DevStateMaker devStateMaker;
	GazEpsProtocolMock::MockEps mockEpsObj;
	GazEpsCanImp::MockCanLayer mockCanObj;

	SECTION( "Test DevStateMaker" )
	{
		//devStateMaker.init(dataCanSenderPtr, epsObjPtr, canIdClassPtr);
	}
}

#endif

#if PROTOCOLDATA_TESTS

/// Юнит-тест объекта ProtocolData
TEST_CASE( "ProtocolData object test" )
{

	SECTION( "Non-argument constructor test" ) {

		GazEpsProtocolImp::ProtocolData dataObject;
		Data receivedBytes = dataObject.getDataBytes();

		for(u8 i = 0; i < dataSize; i++)
		{
			REQUIRE( receivedBytes[i] == 0 );
		}
	}

	SECTION( "Constructor with an array of Data type" ) {
		Data randomBytes;
		randomBytes[0] = 0xC6; randomBytes[1] = 0x6F;
		randomBytes[2] = 0x3B; randomBytes[3] = 0xFE;
		randomBytes[4] = 0xDB; randomBytes[5] = 0x26;
		randomBytes[6] = 0xE8; randomBytes[7] = 0x7F;

		GazEpsProtocolImp::ProtocolData dataObject(randomBytes);
		Data receivedBytes = dataObject.getDataBytes();

		for(u8 i = 0; i < dataSize; i++)
		{
			REQUIRE( receivedBytes[i] == randomBytes[i] );
		}
	}

	SECTION( "Constructor with a 64 bit word" ) {
		u64 randomWord = 0x325EE90DC056FA95;

		GazEpsProtocolImp::ProtocolData dataObject(randomWord);
		Data receivedBytes = dataObject.getDataBytes();

		for(u8 i = 0; i < dataSize; i++)
		{
			REQUIRE( receivedBytes[i] == ((randomWord >> (i * 8)) & 0xFF) );
		}
	}

	SECTION( "Data setter and getter test" ) {
		Data randomBytes;
		randomBytes[0] = 0xC6; randomBytes[1] = 0x6F;
		randomBytes[2] = 0x3B; randomBytes[3] = 0xFE;
		randomBytes[4] = 0xDB; randomBytes[5] = 0x26;
		randomBytes[6] = 0xE8; randomBytes[7] = 0x7F;

		GazEpsProtocolImp::ProtocolData dataObject;
		Data receivedBytes = dataObject.getDataBytes();

		for(u8 i = 0; i < dataSize; i++)
		{
			REQUIRE( receivedBytes[i] == 0 );
		}

		dataObject.setDataBytes(randomBytes);
		receivedBytes = dataObject.getDataBytes();

		for(u8 i = 0; i < dataSize; i++)
		{
			REQUIRE( receivedBytes[i] == randomBytes[i] );
		}
	}

	SECTION( "Data insertion test" ) {

		GazEpsProtocolImp::ProtocolData dataObject;
		Data receivedBytes = dataObject.getDataBytes();

		// Установка трехбитового числа со сдвигом 0
		u8 dataToInsert = 5;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)0, (u8)3);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 5 );

		// Проверка, что маска работает
		fillDataByZeros(receivedBytes);
		dataObject.setDataBytes(receivedBytes);

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)0, (u8)1);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 1 );

		// Проверка сдвига
		fillDataByZeros(receivedBytes);
		dataObject.setDataBytes(receivedBytes);

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)49, (u8)3);
		receivedBytes = dataObject.getDataBytes();

		// 5 << 49 == A 00 00 00 00 00 00
		REQUIRE( receivedBytes[6] == 0xA );

		// Проверка записи битов вплотную к существующим
		fillDataByZeros(receivedBytes);
		dataObject.setDataBytes(receivedBytes);

		dataToInsert = 0x5D;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)0x19, (u8)7);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 0 );
		REQUIRE( receivedBytes[1] == 0 );
		REQUIRE( receivedBytes[2] == 0 );
		REQUIRE( receivedBytes[3] == 0xBA );
		REQUIRE( receivedBytes[4] == 0 );
		REQUIRE( receivedBytes[5] == 0 );
		REQUIRE( receivedBytes[6] == 0 );
		REQUIRE( receivedBytes[7] == 0 );

		dataToInsert = 5;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)22, (u8)3);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 0 );
		REQUIRE( receivedBytes[1] == 0 );
		REQUIRE( receivedBytes[2] == 0x40 );
		REQUIRE( receivedBytes[3] == 0xBB );
		REQUIRE( receivedBytes[4] == 0 );
		REQUIRE( receivedBytes[5] == 0 );
		REQUIRE( receivedBytes[6] == 0 );
		REQUIRE( receivedBytes[7] == 0 );

		// Проверяется, что маска маскирует все лишнее
		fillDataByZeros(receivedBytes);
		dataObject.setDataBytes(receivedBytes);

		dataToInsert = 0x5D;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)0x19, (u8)7);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 0 );
		REQUIRE( receivedBytes[1] == 0 );
		REQUIRE( receivedBytes[2] == 0 );
		REQUIRE( receivedBytes[3] == 0xBA );
		REQUIRE( receivedBytes[4] == 0 );
		REQUIRE( receivedBytes[5] == 0 );
		REQUIRE( receivedBytes[6] == 0 );
		REQUIRE( receivedBytes[7] == 0 );

		dataToInsert = 0xBD;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)22, (u8)3);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 0 );
		REQUIRE( receivedBytes[1] == 0 );
		REQUIRE( receivedBytes[2] == 0x40 );
		REQUIRE( receivedBytes[3] == 0xBB );
		REQUIRE( receivedBytes[4] == 0 );
		REQUIRE( receivedBytes[5] == 0 );
		REQUIRE( receivedBytes[6] == 0 );
		REQUIRE( receivedBytes[7] == 0 );

		// Проверяется задвиг в самые старшие байты
		dataToInsert = 0x92;

		dataObject.insertDataInArray<u8>(dataToInsert, (u8)50, (u8)8);
		receivedBytes = dataObject.getDataBytes();

		REQUIRE( receivedBytes[0] == 0 );
		REQUIRE( receivedBytes[1] == 0 );
		REQUIRE( receivedBytes[2] == 0x40 );
		REQUIRE( receivedBytes[3] == 0xBB );
		REQUIRE( receivedBytes[4] == 0 );
		REQUIRE( receivedBytes[5] == 0 );
		REQUIRE( receivedBytes[6] == 0x48 );
		REQUIRE( receivedBytes[7] == 0x02 );
	}

	SECTION( "Data extraction test" ) {

		Data randomBytes;
		randomBytes[0] = 0xC6; randomBytes[1] = 0x6F;
		randomBytes[2] = 0x3B; randomBytes[3] = 0xFE;
		randomBytes[4] = 0xDB; randomBytes[5] = 0x26;
		randomBytes[6] = 0xE8; randomBytes[7] = 0x7F;

		GazEpsProtocolImp::ProtocolData dataObject(randomBytes);

		// Проверка извлечения 8 бит с нулевым сдвигом
		u8 extractedByte = 0;
		dataObject.extractDataFromArray<u8>(extractedByte, 0, 8);

		CHECK( extractedByte == randomBytes[0] );

		// Проверка извлечения 4 бит с использованием маски, с нулевым сдвигом
		extractedByte = 0;
		dataObject.extractDataFromArray<u8>(extractedByte, 0, 4);

		CHECK( extractedByte == (randomBytes[0] & 0xF) );

		// Проверка извлечения 8 бит со сдвигом
		extractedByte = 0;
		dataObject.extractDataFromArray<u8>(extractedByte, 36, 8);

		CHECK( extractedByte == (((randomBytes[5] & 0xF) << 4) +
								((randomBytes[4] & 0xF0) >> 4)) );

		// Проверка извлечения 5 бит с использованием маски, со сдвигом
		extractedByte = 0;
		dataObject.extractDataFromArray<u8>(extractedByte, 19, 5);

		CHECK( extractedByte == (randomBytes[2] >> 3) );

		// Проверка извлечения 32 бит со сдвигом
		u32 extractedBytes32 = 0;
		dataObject.extractDataFromArray<u32>(extractedBytes32, 16, 32);

		CHECK( extractedBytes32 ==	((u32)randomBytes[2] +
									((u32)randomBytes[3] << 8) +
									((u32)randomBytes[4] << 16) +
									((u32)randomBytes[5] << 24)	) );

		// Проверка извлечения 64 бит со сдвигом
		u64 extractedBytes64 = 0;
		dataObject.extractDataFromArray<u64>(extractedBytes64, 21, 64);

		CHECK( extractedBytes64 ==	((randomBytes[2] >> 5) +
				((u64)randomBytes[3] << 3) +
				((u64)randomBytes[4] << 11) +
				((u64)randomBytes[5] << 19)	+
				((u64)randomBytes[6] << 27)	+
				((u64)randomBytes[7] << 35)) );
	}
}

#endif
