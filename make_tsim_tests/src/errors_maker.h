/*
 * errors_maker.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: user1
 */

#ifndef ERRORS_MAKER_H_
#define ERRORS_MAKER_H_

#include "can_dl.h"
#include "utils.h"
#include "gaz_eps_protocol.h"


namespace GazEpsProtocolImp
{

	class ErrorsMaker
	{
	public:
		ErrorsMaker()
		{
			msg = Message();
			msg.id = CanIdClass(PRIOR_LO, PF_ERRORS, 0x0A, EPAS_ID);
			dataCanSenderPtr = nullptr;
			epsObjPtr = nullptr;
			flagNum = 0;
			errorCode = 0;
			errors = 0;
			storedErrors = 0;
		}
		~ErrorsMaker(){}

		void init(DataCanSender *dataCanSenderPtr,
							GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		void SendErrors(u8 flagNumber)
		{
			errors = (u64)epsObjPtr->getErrorMask();

			if((flagNumber <= 56) && (flagNumber >= 1))
			{
			    errors |= (1 << (flagNumber - 1));
			    flagNum = flagNumber;
			}

			msg.dlc = 8;

			if(msg.data.insertDataInArray<u64>(errors, 8, 56) ||
			        msg.data.insertDataInArray<u64>(flagNum, 0, 8))
			{
				// TODO: ошибка записи в дату, нужно как-то обрабатывать
				return;
			}

			dataCanSenderPtr->SendData(&msg);
		}

		//! \returns true, если появились новые флаги ошибок
		void checkForNewErrors()
		{
		    u64 errors;
		    u64 newErrorsMask = 0;
		    errors = (u64)epsObjPtr->getErrorMask();

		    if(storedErrors != errors)
		    {
		        // Состояние ошибок изменилось
		        newErrorsMask = (storedErrors ^ errors) & errors;
		        if(newErrorsMask)
		        {
		            // перебор всех флагов
		            // TODO: в общем случае избыточно по времени исполнения
		            for(u8 i = 0; i <= 63; i++)
		            {
		                // очередной флаг равен 1
		                if(newErrorsMask & ((u64)1 << i))
		                {
		                    flagNum = i;
		                    SendErrors(0);
		                }
		            }
		        }
		    }
		    storedErrors = errors;
		}

	private:
		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		Message msg;

		u8 errorCode;

		u64 errors;
		u64 storedErrors;

		u8 flagNum;			// Порядковый номер выставленного флага
		// еще 55 битов флагов
	};
}

#endif /* ERRORS_MAKER_H_ */
