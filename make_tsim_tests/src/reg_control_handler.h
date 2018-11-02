/*
 * reg_control_handler.h
 *
 *  Created on: 12 окт. 2018 г.
 *      Author: user1
 */

#ifndef REG_CONTROL_HANDLER_H_
#define REG_CONTROL_HANDLER_H_

#include "types.h"
#include "utils.h"
#include "can_message.h"
#include "array.h"
#include "can_dl.h"
#include "gaz_eps_protocol.h"
#include "receive_handlers.h"

namespace GazEpsProtocolImp
{

	class AbstractHandler
	{
	public:
		virtual ~AbstractHandler(){}

		virtual void Init(DataCanSender *dataCanSenderPtr,
				GazEpsProtocol::User *epsObjPtr) = 0;

		virtual bool SetData(u32 id, const Data &data, u8 dlc) = 0;

		virtual void ResetDataApply() = 0;

		virtual bool CheckSendingData() = 0;

	};

	class RegControlHandler: public AbstractHandler
	{
	public:
		RegControlHandler(){}
		~RegControlHandler(){}

		void init(DataCanSender *dataCanSenderPtr,
					GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		bool SetData(u32 id, const Data &data, u8 dlc)
		{
			bool res = false;

			return res;
		}

		void ResetDataApply()
		{

		}

		bool CheckSendingData()
		{
			bool res = false;

			return res;
		}

	private:
		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

	};

}

#endif /* REG_CONTROL_HANDLER_H_ */
