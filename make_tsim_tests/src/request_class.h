/*
 * gaz_eps_request_class.h
 *
 *  Created on: 9 окт. 2018 г.
 *      Author: user1
 */

#ifndef GAZ_EPS_REQUEST_CLASS_H_
#define GAZ_EPS_REQUEST_CLASS_H_

#include "types.h"
#include "array.h"
#include "can_dl.h"
#include "const.h"
#include "can_message.h"
#include "gaz_eps_protocol.h"

#include "dev_state_maker.h"
#include "program_info_maker.h"
#include "warnings_maker.h"
#include "errors_maker.h"
#include "ack_nack_maker.h"
#include "parent_handler_class.h"

namespace GazEpsProtocolImp
{

	class RequestHandlerClass : public ParentHandlerClass
	{
	public:
        RequestHandlerClass(){}
	    ~RequestHandlerClass(){}

		void init(DataCanSender *dataCanSenderPtr,
					GazEpsProtocol::User *epsObjPtr)
		{

		    if(dataCanSenderPtr != nullptr && epsObjPtr != nullptr)
			{
			    devStatMaker.init(dataCanSenderPtr, epsObjPtr);
			    pgmInfoMaker.init(dataCanSenderPtr, epsObjPtr);
			    warningMaker.init(dataCanSenderPtr, epsObjPtr);
			    errorMaker.init(dataCanSenderPtr, epsObjPtr);
			    ackNackMaker.init(dataCanSenderPtr, epsObjPtr);
			}
		}

		// TODO: рефакторинг параметров
		bool setData(u32 id, const Data &data, u8 dlc)
		{
		    Message msg = Message();
		    msg.id = CanIdClass(id);
		    msg.data = ProtocolData(data);
		    msg.dlc = dlc;

		    if(msg.id.getPfField() != PF_REQUEST)
		    {
		        return false;
		    }

		    if( msg.dlc != requestDlc )
		    {
		        return false;
		    }

		    msg.data.extractDataFromArray<u32>(pgnData,
		            pgnShift, pgnBitsLength);

			switch(pgnData)
			{
				case PGN_DEVSTATE:
					devStatMaker.sendDevState();
					break;
				case PGN_PROGRAM_INFO:
					pgmInfoMaker.SendProgramInfo();
					break;
				case PGN_WARNINGS:
					warningMaker.SendWarnings();
					break;
				case PGN_ERRORS:
					errorMaker.SendErrors(0);
					break;
				default:
					ackNackMaker.SendNack(pgnData);
					break;
			}
		}

		virtual bool CheckSendingData()
		{

		}

	private:
		const u8 requestDlc = 3;

		const u8 pgnShift = 0;
		const u8 pgnBitsLength = 24;
		u32 pgnData = 0;

		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		DevStateMaker devStatMaker;
		ProgramInfoMaker pgmInfoMaker;
		WarningsMaker warningMaker;
		ErrorsMaker errorMaker;
		AckNackMaker ackNackMaker;

	};
}

#endif /* GAZ_EPS_REQUEST_CLASS_H_ */
