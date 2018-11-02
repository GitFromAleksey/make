/*
 * DevStateMaker.h
 *
 *  Created on: 10 окт. 2018 г.
 *      Author: user1
 */

#ifndef SRC_DEV_STATE_MAKER_H_
#define SRC_DEV_STATE_MAKER_H_

#include "can_dl.h"
#include "utils.h"
#include "gaz_eps_protocol.h"
#include "receive_handlers.h"
#include "data_can_sender.h"

namespace GazEpsProtocolImp
{

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

	class DevStateMaker
	{
	public:
		DevStateMaker()
	    {
		    msg = Message();
		    msg.id = CanIdClass(PRIOR_LO, PF_DEVSTATE, 0, EPAS_ID);
		    dataCanSenderPtr = nullptr;
		    epsObjPtr = nullptr;
		}
		~DevStateMaker(){}

		void init(DataCanSender *dataCanSenderPtr,
							GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		// TODO: возможно лишний метод
		void init(DataCanSender *dataCanSenderPtr,
					GazEpsProtocol::User *epsObjPtr,
					CanIdClass *canIdClassPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		void sendDevState()
		{
			epsObjPtr->getErrorMask();

			switch((u8)epsObjPtr->getMode())
			{
			case epsMode::NORMAL:
				workMode = (u8)mode._READY;
				break;
			case epsMode::REMOTE_CONTROL:
				workMode = (u8)mode._WORKING;
				break;
			case epsMode::FAILURE: default:
				workMode = (u8)mode._NOT_READY;
				break;
			}

			if(epsObjPtr->getWarningMask() == 0)
			{
			    warnFlag = 0;
			}
			else
			{
			    warnFlag = 1;
			}

			if(epsObjPtr->getErrorMask() == 0)
			{
			    errFlag = 0;
			}
			else
			{
			    errFlag = 1;
			}

			if (msg.data.insertDataInArray<u8>(workMode,    0,	wrkModeBits) ||
				msg.data.insertDataInArray<u8>(warnFlag,    8,	warnFlagBits)||
				msg.data.insertDataInArray<u8>(errFlag,     9,	errFlagBits) ||
				msg.data.insertDataInArray<u8>(rezerv,      10,	rezervBits)	 ||
				msg.data.insertDataInArray<u8>(techCond,    12,	techCondBits))
			{
				// TODO: ошибка записи в дату, нужно как-то обрабатывать
				return;
			}

			msg.dlc = DEVSTATE_DATA_SIZE;
			dataCanSenderPtr->SendData(&msg);
		}

	private:
		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		Message msg;

		typedef GazEpsProtocol::User::Mode epsMode;

		EnumWorkModes mode;

		//! Unsigned2 - режим работы
		u8 workMode = 0;
		const u8 wrkModeBits = 8;		//!< Unsigned2
		const u8 wrkModeShift = 0;

		//! код технического состояния (0 - исправно, 1 - работоспособно ...)
		u8 techCond = 0;
		const u8 techCondBits = 4;      //!< Unsigned4
		const u8 techCondShift = 12;

		//! rezerv << 10;
		u8 rezerv = 0;              //! заполняется нулями
		const u8 rezervBits = 2;    //! Void2
		const u8 rezervShift = 10;

		//! флаг ошибок (0 - нет, 1 - есть)
		u8 errFlag = 0;
		const u8 errFlagBits = 1;   //! Unsigned1
		const u8 errFlagShift = 9;

		//! флаг предупреждения (0 - нет, 1 - есть)
		u8 warnFlag = 0;
		const u8 warnFlagBits = 1;  //!< Unsigned1
		const u8 warnFlagShift = 8;
	};
}


#endif /* SRC_DEV_STATE_MAKER_H_ */
