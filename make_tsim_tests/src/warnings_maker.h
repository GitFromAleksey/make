/*
 * warnings_maker.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: user1
 */

#ifndef WARNINGS_MAKER_H_
#define WARNINGS_MAKER_H_

#include "can_dl.h"
#include "utils.h"
#include "gaz_eps_protocol.h"

namespace GazEpsProtocolImp
{

class WarningsMaker
{
	public:
		WarningsMaker()
		{
		    msg = Message();
		    msg.id = CanIdClass(PRIOR_LO, PF_WARNINGS, 0x0B, EPAS_ID);
		    dataCanSenderPtr = nullptr;
		    epsObjPtr = nullptr;
		}
		~WarningsMaker(){}

		void init(DataCanSender *dataCanSenderPtr,
							GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		void SendWarnings()
		{
			u64 warnMask;

			flagNum = 5;
			watchdogReset = 1;

			warnMask = epsObjPtr->getWarningMask();

			if(msg.data.insertDataInArray<u64>(warnMask, 8, 56))
			{
				// TODO: ошибка записи в дату, нужно как-то обрабатывать
				return;
			}

			msg.dlc = WARNINGS_DATA_SIZE;
			dataCanSenderPtr->SendData(&msg);
		}

	private:
		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		CanIdClass canIdClass;

		Message msg;

		u8 flagNum = 0;			// Порядковый номер выставленного флага

		u8 watchdogReset = 0;	// Устройство переза­пущено по
							    // срабатыванию watchdog таймера
	};
}

#endif /* WARNINGS_MAKER_H_ */
