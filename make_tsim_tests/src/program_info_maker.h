/*
 * program_info_maker.h
 *
 *  Created on: 10 окт. 2018 г.
 *      Author: user1
 */

#ifndef PROGRAM_INFO_MAKER_H_
#define PROGRAM_INFO_MAKER_H_

#include "can_dl.h"
#include "utils.h"
#include "gaz_eps_protocol.h"
#include "receive_handlers.h"
#include "can_message.h"

namespace GazEpsProtocolImp
{

	class ProgramInfoMaker
	{
	public:
		ProgramInfoMaker()
		{
		    msg = Message();
			msg.id = CanIdClass(PRIOR_LO, PF_PROGRAM_INFO, 0x01, EPAS_ID);
			dataCanSenderPtr = nullptr;
			epsObjPtr = nullptr;
		}
		~ProgramInfoMaker(){}

		void init(DataCanSender *dataCanSenderPtr,
							GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		void SendProgramInfo()
		{
			epsObjPtr->getVersion(x, y, z, hashSum);

			if(	msg.data.insertDataInArray<u32>(hashSum, 0, 32) ||
			        msg.data.insertDataInArray<u8>(x, 32, 8)    ||
			        msg.data.insertDataInArray<u8>(y, 40, 8)    ||
			        msg.data.insertDataInArray<u16>(z, 48, 16) )
			{
				// TODO: ошибка записи в дату, нужно как-то обрабатывать
				return;
			}

			msg.data.insertDataInArray<u16>(z, 48, 16);

			msg.dlc = 8;
			dataCanSenderPtr->SendData(&msg);
		}

	private:
		CanIdClass canIdClass;

		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		Message msg;

		u32 hashSum = 0;    // Значения контрольной характеристики программы
		                    // устройства
		u8 x = 0;			// глобальные изменения в ПО
		u8 y = 0;			// обавлении новых функций и исправлении ошибок
		u16 z = 0;			// при исправлении незначительных ошибок и внесении
		                    // незначительных исправлений
	};

}

#endif /* SRC_PROGRAM_INFO_MAKER_H_ */
