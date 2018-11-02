/*
 * parent_handler_class.h
 *
 *  Created on: 15 окт. 2018 г.
 *      Author: user1
 */

#ifndef PARENT_HANDLER_CLASS_H_
#define PARENT_HANDLER_CLASS_H_

#include "types.h"
#include "utils.h"
#include "data_can_sender.h"
#include "gaz_eps_protocol.h"


namespace GazEpsProtocolImp
{

	class ParentHandlerClass
	{
	public:
		ParentHandlerClass(){}
		virtual ~ParentHandlerClass(){}

		// TODO: сделать булевой, чтобы возвращать результат инициализации
		virtual void init(DataCanSender *dataCanSenderPtr,
				GazEpsProtocol::User *epsObjPtr) = 0;

		virtual bool setData(u32 id, const Data &data, u8 dlc) = 0;

		virtual bool CheckSendingData() = 0;

	protected:
		ProtocolData prData();
	};

}


#endif /* PARENT_HANDLER_CLASS_H_ */
