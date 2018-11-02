/*
 * data_can_sender.h
 *
 *  Created on: 15 окт. 2018 г.
 *      Author: user1
 */

#ifndef DATA_CAN_SENDER_H_
#define DATA_CAN_SENDER_H_

namespace GazEpsProtocolImp
{
	class DataCanSender
	{
	public:

		DataCanSender(){}
		~DataCanSender(){}

		void init( CanDL::Layer *canPtr )
		{
			this->canPtr = canPtr;
		}

	    bool SendData(Message *message)
	    {
            // TODO: убрать после исправления moc объекта canPtr
            dataIsSend = true;

            // TODO: moc объект не отвечает true при отправке
	        canPtr->dlRequest(message->id.getIdAsU32(),
	                message->data.getDataBytes(), message->dlc);

	        return dataIsSend;
	    }

		bool dataIsSent()
		{
			return dataIsSend;
		}

		void dlConfirmReset()
		{
		    dataIsSend = false;
		}

	private:
		bool dataIsSend = false;
		CanDL::Layer *canPtr = NULL;
	};
}

#endif /* DATA_CAN_SENDER_H_ */
