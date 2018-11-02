/*
 * ack_nack_maker.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: user1
 */

#ifndef ACK_NACK_MAKER_H_
#define ACK_NACK_MAKER_H_

namespace GazEpsProtocolImp
{

	class AckNackMaker
	{
	public:
		AckNackMaker()
		{
		    message = Message();
			message.id = CanIdClass(PRIOR_LO, PF_NACK, MCM_ID, EPAS_ID);
			dataCanSenderPtr = nullptr;
			epsObjPtr = nullptr;
		}
		~AckNackMaker(){}

		void init(DataCanSender *dataCanSenderPtr,
							GazEpsProtocol::User *epsObjPtr)
		{
			this->dataCanSenderPtr = dataCanSenderPtr;
			this->epsObjPtr = epsObjPtr;
		}

		void SendAck(u32 pgn)
		{
			FillAckNackAnswer(pgn, false);
			dataCanSenderPtr->SendData(&message);
		}

		void getAckNack(u32 &id, Data &data, u8 &dlc, u32 pgn, bool nack)
		{
		    FillAckNackAnswer( pgn, true );

		    id = this->message.id.getIdAsU32();
		    data = this->message.data.getDataBytes();
		    dlc = this->message.dlc;
		}

		void SendNack(u32 pgn)
		{
			FillAckNackAnswer(pgn, true);
			dataCanSenderPtr->SendData(&message);
		}

	private:
		DataCanSender *dataCanSenderPtr;
		GazEpsProtocol::User *epsObjPtr;

		Message message;

		void FillAckNackAnswer(u32 pgn, bool nack)
		{
			u8 controlByte = NACK_CONTROLBYTE;

			if(nack)
			{
				if(message.data.insertDataInArray<u8>(controlByte, 0, 8))
				{
					// TODO: ошибка записи в дату, нужно как-то обрабатывать
					return;
				}
			}

			u32 tmp = NACK_FILL;
			message.data.insertDataInArray<u32>(tmp, 8, 32);
			message.data.insertDataInArray<u32>(pgn, 40, 24);
			message.dlc = NACK_DATA_SIZE;
		}
	};
}

#endif /* ACK_NACK_MAKER_H_ */
