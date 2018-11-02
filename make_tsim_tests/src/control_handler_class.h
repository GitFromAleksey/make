/*
 * control_handler_class.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: user1
 */

#ifndef CONTROL_HANDLER_CLASS_H_
#define CONTROL_HANDLER_CLASS_H_

#include "types.h"
#include "array.h"
#include "can_dl.h"
#include "const.h"
#include "can_message.h"
#include "parent_handler_class.h"
#include "gaz_eps_protocol.h"


namespace GazEpsProtocolImp
{

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

	//! значение кодов команд сообщения CONTROL
	struct ControlCommands
	{
		typedef enum
		{
			ctrlCmdSwitchEUMode = 1,	// перевести устройство в режим ЭУ
			ctrlCmdSwitchDUMode = 2,	// перевести устройство в режим ДУ
			ctrlCmdClearError = 32,		// сброс флагов предупреждений
			ctrlCmdClearWarning = 33	// сброс флагов ошибок
		} Commands;
	};

	class ControlHandlerClass : public ParentHandlerClass
	{
	public:
        ControlHandlerClass()
        {
            waitSendData = false;
        }
        ControlHandlerClass(ParentHandlerClass *prevObjPtr)
        {
            waitSendData = false;
        }
		~ControlHandlerClass(){}

		void init(DataCanSender *dataCanSenderPtr,
					GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		bool setData(u32 id, const Data &data, u8 dlc)
		{
		    CanIdClass canIdObj = CanIdClass(id);
			if(canIdObj.getPfField() != PF_CONTROL)return false;

			ProtocolData prData(data);

			prData.extractDataFromArray<u8>(cmdCode, 0, 8);
			prData.extractDataFromArray<u8>(devAddr, 8, 8);
			prData.extractDataFromArray<u8>(commandData, 16, 8);

			switch(cmdCode)
			{
				case ControlCommands::ctrlCmdClearError:
				    if(commandData > maxErrorFlagNumber)
					{
						SendData(
						cmdCode,	// ControlCommands::ctrlCmdClearError,
						RetControlDataFormat::CommandCanNotExec );
					}
					else
					{
						waitSendData = true;

						SendData(
						cmdCode,	// ControlCommands::ctrlCmdClearError,
						RetControlDataFormat::CommandAccepted );
					}
				break;
				case ControlCommands::ctrlCmdClearWarning:
					if(commandData > maxWarningFlagNumber)
					{
						SendData(
						cmdCode,	// ControlCommands::ctrlCmdClearError,
						RetControlDataFormat::CommandCanNotExec );
					}
					else
					{
						waitSendData = true;

						SendData(
						cmdCode,	// ControlCommands::ctrlCmdClearError,
						RetControlDataFormat::CommandAccepted );
					}
				break;
				case ControlCommands::ctrlCmdSwitchDUMode:
					waitSendData = true;
					SendData(
							cmdCode,	//ControlCommands::ctrlCmdClearError,
						RetControlDataFormat::CommandAccepted );
				break;
				case ControlCommands::ctrlCmdSwitchEUMode:
					waitSendData = true;
					SendData(
						cmdCode,
						RetControlDataFormat::CommandAccepted );
				break;
				default:
					// команда не поддерживается
					SendData(
						cmdCode,
						RetControlDataFormat::CommandNotSupported );
				break;
			}
		}

		// TODO: добавить в timeUpdate для сброса по таймауту
		void ResetDataApply()
		{
			waitSendData = false;
		}

		bool CheckSendingData()
		{
			if( waitSendData == true )
			{
				waitSendData = false;

				// применение действия
				switch(cmdCode)
				{
					case ControlCommands::ctrlCmdClearError:
					    if(commandData == 0)
							epsObjPtr->clearAllErrors();
						else
							epsObjPtr->clearError(commandData);
						break;
					case ControlCommands::ctrlCmdClearWarning:
						if(commandData == 0)
							epsObjPtr->clearAllWarnings();
						else
							epsObjPtr->clearWarning(commandData);
						break;
					case ControlCommands::ctrlCmdSwitchDUMode:
						epsObjPtr->goToRemoteControlMode();
						break;
					case ControlCommands::ctrlCmdSwitchEUMode:
					    epsObjPtr->goToNormalMode();
					    break;
					default:
						break;
				}
			}

			return waitSendData;
		}

	private:

		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		u8 cmdCode;
		u8 devAddr;
		u8 commandData;

		bool waitSendData;

		const u8 maxErrorFlagNumber = 55;
		const u8 maxWarningFlagNumber = 55;

		const u8 cmdCodeShift = 0;
		const u8 devAddrShift = 8;
		const u8 commandDataShift = 16;

		bool SendData(u8 cmdCode, u8 result)
		{
			bool res = false;

			Message msg = Message();
			msg.id = CanIdClass(PRIOR_HI, PF_RETCONTROL, MCM_ID, EPAS_ID);

			msg.data.insertDataInArray<u8>(cmdCode,	0,	8);
			msg.data.insertDataInArray<u8>(result,	16,	8);

			msg.dlc = RETCONTROL_DATA_SIZE;

			res = dataCanSenderPtr->SendData(&msg);

			return res;
		}
	};

}

#endif /* CONTROL_HANDLER_CLASS_H_ */
