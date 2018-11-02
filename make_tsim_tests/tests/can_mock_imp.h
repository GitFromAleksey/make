#ifndef TESTS_CAN_MOCK_IMP_H_
#define TESTS_CAN_MOCK_IMP_H_

#include "../src/const.h"
#include "can_dl.h"
#include "array.h"
#include "utils.h"

namespace GazEpsCanImp
{

class MockCanLayer : public CanDL :: Layer
{
public:
	// Создание объекта ID для сравнения с ответом
	J1939idParams expectedId1Params;
	u32 expectedId1;

	J1939idParams expectedId2Params;
	u32 expectedId2;

	J1939idParams expectedId3Params;
	u32 expectedId3;

	typedef cmn::array< Data, 3 > DataArray;
	typedef cmn::array< u32, 3 > IdArray;
	typedef cmn::array< u8, 3 > DlcArray;

	u32 id;
	Data data;
	u8 dataLenght;

	MockCanLayer() {
		// Заполнение объекта REG_PARAM_1 ID для сравнения с ответом
		expectedId1Params.pgn.pf = REGPARAM1_PF;
		expectedId1Params.pgn.ps = REGPARAM1_PS;
		expectedId1Params.priority = (MessagePriority)REGPARAM1_PRIORITY;
		expectedId1Params.sa = EPAS_ID;
		expectedId1 = composeCanId(&expectedId1Params);

		// Заполнение объекта REG_PARAM_2 ID для сравнения с ответом
		expectedId2Params.pgn.pf = REGPARAM2_PF;
		expectedId2Params.pgn.ps = REGPARAM2_PS;
		expectedId2Params.priority = (MessagePriority)REGPARAM2_PRIORITY;
		expectedId2Params.sa = EPAS_ID;
		expectedId2 = composeCanId(&expectedId2Params);

		// Заполнение объекта REG_PARAM_3 ID для сравнения с ответом
		expectedId3Params.pgn.pf = REGPARAM3_PF;
		expectedId3Params.pgn.ps = REGPARAM3_PS;
		expectedId3Params.priority = (MessagePriority)REGPARAM3_PRIORITY;
		expectedId3Params.sa = EPAS_ID;
		expectedId3 = composeCanId(&expectedId3Params);

		for( u8 i = 0; i <= 2; i++)
		{
			Data temp;

			temp = storedData[i];

			for( u8 j = 0; j <= 7; j++)
			{
				temp[j] = 0;
			}

			// Инициализация нулевыми значениями
			storedData[i] = temp;
			storedId[i] = 0;
			storedDlc[i] = 0;
		}
	}
	~MockCanLayer() { }

	// инициализация CAN
	void init( CanDL::User *protPtr )
	{
		setDlRequestCallsCnt(0);
		protocolObjPtr = protPtr;
		txId = 0;
		txData = 0;
		txDlc = 0;
		setTestMode(false);
	}

	// имплементация виртуальных вункций
	// вызывается объектом Protocol для отправки данных в CAN
	virtual bool dlRequest(u32 id, const Data &data, u8 dlc)
	{
		bool b = false;

		// подсчет количества вызовов
		u32 tempCounter = getDlRequestCallsCnt();
		tempCounter++;
		setDlRequestCallsCnt(tempCounter);

		// сохранить данные, отправленные объектом протокола в CAN
		setTxId(id);

		u64 newTxData = unpackData(data);

		setTxData(newTxData);
		setTxDlc(dlc);

		if ( id == expectedId1)
		{
			storedData[0] = data;
			storedId[0] = id;
			storedDlc[0] = dlc;
		}
		if ( id == expectedId2)
		{
			storedData[1] = data;
			storedId[1] = id;
			storedDlc[1] = dlc;
		}
		if ( id == expectedId3)
		{
			storedData[2] = data;
			storedId[2] = id;
			storedDlc[2] = dlc;
		}

		// Если НЕ режим тестирования - отправить подтверждение
		if( isTestMode() == false )
		{
			protocolObjPtr->dlConfirm();
		}
		return b;
	}

	// вызывается объектом Protocol для отмены отправки данных в CAN
	virtual void dlBreakRequest()
	{

	}

	u32 getDlRequestCallsCnt()
	{
		return dlRequestCallsCnt;
	}

	void setDlRequestCallsCnt(u32 newCntValue)
	{
		this->dlRequestCallsCnt = newCntValue;
	}



	bool Rx(u32 id, const Data &data, u8 dlc)
	{
		protocolObjPtr->dlIndication(id, data, dlc);
		return true;
	}

	u64 getRegParamData(u8 numberOfRegParam)
	{
		u64 retData = 0;
		Data tempArray;

		switch(numberOfRegParam)
		{
		case 1:
			tempArray = storedData[0]; break;
		case 2:
			tempArray = storedData[1]; break;
		case 3:
			tempArray = storedData[2]; break;
		default: return 0; break;
		}

		for(u8 i = 0; i < 8; i++)
		{
			retData |= ((u64)tempArray[i] << (i * 8));
		}

		return retData;
	}

	u32 getRegParamId(u8 numberOfRegParam)
	{
		switch(numberOfRegParam)
		{
		case 1:
			return storedId[0]; break;
		case 2:
			return storedId[1]; break;
		case 3:
			return storedId[2]; break;
		default: break;
		}
		return 0;
	}

	u32 getRegParamDlc(u8 numberOfRegParam)
	{
		switch(numberOfRegParam)
		{
		case 1:
			return storedDlc[0]; break;
		case 2:
			return storedDlc[1]; break;
		case 3:
			return storedDlc[2]; break;
		default: break;
		}
		return 0;
	}

	u64 getTxData() {
		return txData;
	}

	void setTxData(u64 txData) {
		this->txData = txData;
	}

	u8 getTxDlc() {
		return txDlc;
	}

	void setTxDlc(u8 txDlc) {
		this->txDlc = txDlc;
	}

	u32 getTxId() {
		return txId;
	}

	void setTxId(u32 txId) {
		this->txId = txId;
	}

	bool isTestMode() {
		return testMode;
	}

	void setTestMode(bool testMode) {
		this->testMode = testMode;
	}

private:
	u32 dlRequestCallsCnt = 0;

	CanDL::User *protocolObjPtr;

	u32 txId;
	u64 txData;
	u8 txDlc;

	bool testMode;

	DataArray storedData;
	IdArray storedId;
	DlcArray storedDlc;

	u8 counter;

};
}

#endif /* TESTS_CAN_MOCK_IMP_H_ */
