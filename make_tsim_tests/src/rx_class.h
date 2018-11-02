/*
 * gaz_eps_protocol_rx_class.h
 *
 *  Created on: 1 окт. 2018 г.
 *      Author: user1
 */

#ifndef GAZ_EPS_PROTOCOL_RX_CLASS_H_
#define GAZ_EPS_PROTOCOL_RX_CLASS_H_

#include "types.h"
#include "array.h"
#include "can_dl.h"
#include "msg.h"

namespace GazEpsProtocolImp
{

	// \brief Класс для обработки входящих сообщений
	class MsgRxClass
	{
	public:

		MsgRxClass(u8 eurAddr, u8 budAddr)
		{
		    msg = Message();
			this->eurAddr = eurAddr;
			this->budAddr = budAddr;

			msgRegCtrl_1.dataRxFlag = false;
			msgRegCtrl_2.dataRxFlag = false;
			msgRegCtrl_3.dataRxFlag = false;
		}
		~MsgRxClass(){}

		CanDL::Data getData(void)
		{
			return this->msg.data.getDataBytes();
		}
		u8 getDlc(void)
		{
			return this->msg.dlc;
		}

		u8 getPf(void)
		{
			return this->msg.id.getPfField();
		}

		u8 getPS(void)
		{
			return this->msg.id.getPsField();
		}

		u8 getSA(void)
		{
		    return this->msg.id.getSaField();
		}

		//! Возвращает PGN из ID CAN сообщения
		u32 getPGN(void)
		{
			return this->msg.id.getPgnAsU32();
		}

		//! Возвращает PGN из сообщения REQUEST
		u32 getRequestPGN(void)
		{
			return request_pgn;
		}

		/*!
		\brief Принимает входящие данные для расшифровки
		\param[id] can ID идентификатор CAN сообщения
		\param[data] can data данные CAN сообщения
		\param[dlc] can dlc длина поля данных CAN сообщения
		*/
		// \todo возможно, нужно переименовать этот метод
		void setPacket(u32 id, const CanDL::Data &data, u8 dlc)
		{
			msg.id = CanIdClass(id);
			msg.dlc = dlc;

			// проверка номера источника сообщения
			if(msg.id.getSaField() != budAddr)
			{
			    msg = Message();
				// выход, если номер источника не совпадает
				return;
			}

			if(msg.dlc > 0)
			{
			    msg.data = ProtocolData(data);
			}
			else
			{
			    msg.data = ProtocolData();
			}

			if(msg.id.getPfField() == PF_REQUEST)
			{
			    DecodeRequestData();
			}
			else if(msg.id.getPfField() == PF_SYNC_CTRL)
			{
			    DecodeSyncControlData();
			}
			else if(msg.id.getPfField() == PF_SYNC_PARAM)
			{
			    DecodeSyncParamData();
			}
			else if( (msg.id.getPfField() & PF_REG_CTRL) == PF_REG_CTRL)
			{
			    DecodeRegControlData();
			}
			else if(msg.id.getPfField() == PF_CONTROL)
			{
			    DecodeControlData();
			}

		}

		// \brief Возвращает структуру полученного сообщения (id,data,dlc,data64)
//		MsgStruct getPacket(void)
//		{
//			return msg;
//		}

		//
		bool getRegCtrl1Data(RegControl_1_DataFormat &RegCtrlData)
		{
			RegCtrlData.setWheelPosition = msgRegCtrl_1.setWheelPosition;
			RegCtrlData.turnSpeed = msgRegCtrl_1.turnSpeed;
			RegCtrlData.dataRxFlag = msgRegCtrl_1.dataRxFlag;
			RegCtrlData.dataError = msgRegCtrl_1.dataError;
			RegCtrlData.doNotApplyData = msgRegCtrl_1.doNotApplyData;

			msgRegCtrl_1.dataRxFlag = false;
			return true;
		}

		bool getRegCtrl2Data(RegControlRegulatorDataFormat &RegCtrlData)
		{
			RegCtrlData.Ki = msgRegCtrl_2.Ki;
			RegCtrlData.Kp = msgRegCtrl_2.Kp;
			RegCtrlData.L = msgRegCtrl_2.L;
			RegCtrlData.Qi = msgRegCtrl_2.Qi;
			RegCtrlData.Qp = msgRegCtrl_2.Qp;

			RegCtrlData.dataRxFlag = msgRegCtrl_2.dataRxFlag;
			RegCtrlData.data64 = msgRegCtrl_2.data64;

			msgRegCtrl_2.dataRxFlag = false;
			return true;
		}
		bool getRegCtrl3Data(RegControlRegulatorDataFormat &RegCtrlData)
		{
			RegCtrlData.Ki = msgRegCtrl_3.Ki;
			RegCtrlData.Kp = msgRegCtrl_3.Kp;
			RegCtrlData.L = msgRegCtrl_3.L;
			RegCtrlData.Qi = msgRegCtrl_3.Qi;
			RegCtrlData.Qp = msgRegCtrl_3.Qp;

			RegCtrlData.dataRxFlag = msgRegCtrl_3.dataRxFlag;
			RegCtrlData.data64 = msgRegCtrl_3.data64;

			msgRegCtrl_3.dataRxFlag = false;
			return true;
		}

		bool isRegCtrlDataError(void)
		{
			return msgRegCtrl_1.dataError;
		}
		u32 getSetWheelPosition(void)
		{
			return msgRegCtrl_1.setWheelPosition;
		}
		u8 getSetTurnSpeed(void)
		{
			return msgRegCtrl_1.turnSpeed;
		}

		void getControlData(ControlDataFormat &ctrlData)
		{
			ctrlData.cmdCode = controlData.cmdCode;
			ctrlData.devAddr = controlData.devAddr;
			ctrlData.comandData = controlData.comandData;
			controlData.dataRxFlag = false;
		}

		u32 getSyncParamDataPGN(void)
		{
			return syncParamsData.PGN;
		}

		u8 getSyncParamDataTelemetrySum(void)
		{
			return syncParamsData.telemetryCountPGN;
		}

	private:
		Message msg;

		u32 request_pgn = 0;
		SyncParamDataFormat syncParamsData;
		ControlDataFormat controlData;
		// задание положения и скорости поворота руля
		RegControl_1_DataFormat msgRegCtrl_1;
		// коэффициенты и ограничения ПИ-регулятора положения
		RegControlRegulatorDataFormat msgRegCtrl_2;
		// коэффициенты и предел ПИ-регулятора скорости
		RegControlRegulatorDataFormat msgRegCtrl_3;

		u8 eurAddr;	// адрес ЭУР (собственный адрес)
		u8 budAddr;	// адрес БУД (адрес источника сообщений)

		// \brief Декодирование данных запроса REQUEST
		void DecodeRequestData(void)
		{
			request_pgn = msg.data.extractDataFromArray<u32>(request_pgn,
			        0, 32);
		}

		// \brief Запись массива байт в число 64 бита
//		void DataConvertArrayToU64(const CanDL::Data &data, const u8 &dlc)
//		{
//			u8 i = 0;
//			msg.data64 = 0;
//			for(i = 0; i < dlc; i++)
//			{
//				msg.data[i] = data[i];
//				msg.data64 |= (u64)msg.data[i]<<(i*8);
//				// msg.data[i] = (msg.data64>>((7-i)*8) ) & 0xFF;
//			}
//		}

		// \brief Декодирование данных запроса SYNC_CTRL
		void DecodeSyncControlData(void)
		{
			//if( msgRegCtrl_1.dataRxFlag == true )
			{
				CheckRegControlData();	// проверка данных на корректность
			}
		}

		// \brief Декодирование данных запроса SYNC_PARAM
		void DecodeSyncParamData(void)
		{
//			SyncParamDataFormat syncParamsData;

			syncParamsData.PGN_lsb = msg.data[0];
			syncParamsData.PGN_mdl = msg.data[1];
			syncParamsData.PGN_msb = msg.data[2];
			syncParamsData.telemetryCountPGN = msg.data[3];

			syncParamsData.PGN = 0;
			syncParamsData.PGN |= ((u32)msg.data[2]<<16);
			syncParamsData.PGN |= ((u32)msg.data[1]<<8);
			syncParamsData.PGN |= ((u32)msg.data[0]);
		}

		// \brief Декодирование данных запроса PEG_CTRL_1
		void DecodeRegControlData(void)
		{
			// если dlc == 0 - данные не были приняты
			if(msg.dlc == 0)
			{
				msgRegCtrl_1.dataRxFlag = false;
				msgRegCtrl_2.dataRxFlag = false;
				msgRegCtrl_3.dataRxFlag = false;
				return;
			}

			// REG_CTRL_1 - положение руля и скорость поворота
			if(msg.id.getPfField() == A_BASE_BUD)
			{
				// id:0x0C208782
				msg.data.extractDataFromArray(msgRegCtrl_1.setWheelPosition,
				        0, 11);
				msg.data.extractDataFromArray(msgRegCtrl_1.turnSpeed,
				        16, 8);
				msgRegCtrl_1.dataRxFlag = true;		// сообщение получено
			}
			// REG_CTRL_2 - настройка ПИ рагулятора
			else if(msg.id.getPfField() == (A_BASE_BUD + 1) )
			{
			    msg.data.extractDataFromArray(msgRegCtrl_2.L, 0, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_2.Kp, 16, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_2.Qp, 32, 8);
			    msg.data.extractDataFromArray(msgRegCtrl_2.Ki, 40, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_2.Qi, 56, 8);

			    // TODO: какой-то костыль
				msgRegCtrl_2.data64 = unpackData(msg.data.getDataBytes());

				msgRegCtrl_2.dataRxFlag = true; // получены данные
			}
			// REG_CTRL_3 - настройка ПИ рагулятора
			else if(msg.id.getPfField() == (A_BASE_BUD + 2) )
			{

			    msg.data.extractDataFromArray(msgRegCtrl_3.L, 0, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_3.Kp, 16, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_3.Qp, 32, 8);
			    msg.data.extractDataFromArray(msgRegCtrl_3.Ki, 40, 16);
			    msg.data.extractDataFromArray(msgRegCtrl_3.Qi, 56, 8);

			    // TODO: какой-то костыль
			    msgRegCtrl_3.data64 = unpackData(msg.data.getDataBytes());

				msgRegCtrl_3.dataRxFlag = true; // получены данные
			}
		}

		// \brief Декодирование данных запроса CONTROL
		void DecodeControlData(void)
		{
		    msg.data.extractDataFromArray(controlData.cmdCode, 0, 8);
		    msg.data.extractDataFromArray(controlData.devAddr, 8, 8);
		    msg.data.extractDataFromArray(controlData.comandData, 16, 8);
			//controlData.rezerv = (msg.data64>>32) & 0xFF;

			controlData.dataRxFlag = true;
		}

		bool CheckRegControlData(void)
		{
			bool data_correct = false;

			if(msgRegCtrl_1.dataRxFlag == true)	// данные были приняты
			{
				// проверка задания положения руля
				if(msgRegCtrl_1.setWheelPosition > 2000)
				{
					msgRegCtrl_1.dataError = true;	// ошибка данных

					if(msgRegCtrl_1.setWheelPosition == 2047)	// 0x7FF
					{
						// не применять данные
						msgRegCtrl_1.doNotApplyData = true;
						// данные верны
						msgRegCtrl_1.dataError = false;
						data_correct = true;
					}
				}
				else
				{
					// применять данные
					msgRegCtrl_1.doNotApplyData = false;
					// данные верны
					msgRegCtrl_1.dataError = false;
					data_correct = true;
				}

				if(msgRegCtrl_1.dataError == true)
					{ return false; }

				// проверка задания скорости поворота
				if(msgRegCtrl_1.turnSpeed > 100)
				{
					msgRegCtrl_1.dataError = true;	// ошибка данных

					if(msgRegCtrl_1.turnSpeed == 255)	// 0xFF
					{
						// не применять данные
						msgRegCtrl_1.doNotApplyData = true;
						// данные верны
						msgRegCtrl_1.dataError = false;
						data_correct = true;
					}
				}
				else
				{
					// применять данные
					msgRegCtrl_1.doNotApplyData = false;
					// данные верны
					msgRegCtrl_1.dataError = false;
					data_correct = true;
				}

				if(msg.dlc == 0)
					data_correct = false;
			}
			return data_correct;
		}

	};

}



#endif /* GAZ_EPS_PROTOCOL_RX_CLASS_H_ */
