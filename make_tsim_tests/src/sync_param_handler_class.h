/*
 * reg_control_handler_class.h
 *
 *  Created on: 16 окт. 2018 г.
 *      Author: user1
 */

#ifndef REG_CONTROL_HANDLER_CLASS_H_
#define REG_CONTROL_HANDLER_CLASS_H_



#include "array.h"
#include "can_message.h"
#include "parent_handler_class.h"
#include "ack_nack_maker.h"
#include "data_can_sender.h"

#define DEBUG_OUT false
#include "debug_std_out.h"


namespace GazEpsProtocolImp
{

    class RegParamsClass
    {
    public:
        RegParamsClass(GazEpsProtocol::User *epsObjPtr)
        {
            this->epsObjPtr = epsObjPtr;
        }
        ~RegParamsClass(){}

        bool getRegParam1Data(Data &data, u8 &dlc)
        {
            bool res = false;

            ProtocolData prData;

            // запрос текущего положения рулевого колеса
            CurrentWheelPosition =
                ConvertWheelPositionFromF32ToU16
                    (epsObjPtr->getSteeringWheelPosition(), maxWheelPosition);

            // запрос текущей скорости поворота рулевого колеса
            CurrentTurnSpeed =
                ConvertTurnedSpeedFromF32ToU8
                    (epsObjPtr->getSteeringWheelSpeed(), maxTurnSpeed );

            workMode = (u8)epsObjPtr->getMode();

            prData.insertDataInArray<u32>(CurrentWheelPosition, 0, 11);
            prData.insertDataInArray<u32>(workMode, 11, 1);
            prData.insertDataInArray<u32>(CurrentTurnSpeed, 16, 8);

            data = prData.getDataBytes();

            dlc = 8;

            res = true;

            return res;
        }

        void getRegParam2Data(Data &data, u8 &dlc)
        {
            ProtocolData prData;

            prData = ProtocolData(epsObjPtr->getPidTermsPosition());

            data = prData.getDataBytes();
            dlc = 8;
        }

        void getRegParam3Data(Data &data, u8 &dlc)
        {
            ProtocolData prData;

            prData = ProtocolData(epsObjPtr->getPidTermsSpeed());

            data = prData.getDataBytes();
            dlc = 8;
        }

    private:
        GazEpsProtocol::User *epsObjPtr;

        u32 CurrentWheelPosition;
        u8 CurrentTurnSpeed;
        u8 workMode;

        const u16 maxWheelPosition = 2000;
        const u8 maxTurnSpeed = 100;

        // преобразование из Float в относительных единицах (-1.0 - 1.0)
        // в UINT16(0 - maxVal)
        u16 ConvertWheelPositionFromF32ToU16(f32 val, u16 maxVal)
        {
            f32 fl_shift = maxVal/2;

            f32 tmp = (val + 1) * fl_shift;

            return (u16)tmp;
        }

        // преобразование скорости поворота руля из Float(0.0 - 1.0)
        // к uint8(0 - 100)
        u8 ConvertTurnedSpeedFromF32ToU8(f32 val, u8 maxVal)
        {
            val = val * maxVal;
            return (u8)val;
        }

    };

    class RegParamMakerClass
    {
    public:
        RegParamMakerClass()
        {
            isDataToSend = false;
        }
        ~RegParamMakerClass(){}

        bool init(GazEpsProtocol::User *epsObjPtr)
        {
            this->epsObjPtr = epsObjPtr;
        }

        bool HandleData(u32 pgn, u8 pgnSumm)
        {
            bool res = false;

#if DEBUG_OUT
    debugPrintText("RegParamMakerClass.HandleData(u32 pgn, u8 pgnSumm)");
    debugPrintTextHexValue<u32>("RegParamMakerClass.pgn = ", pgn);
    debugPrintTextHexValue<u16>("RegParamMakerClass.pgnSumm = ", pgnSumm);
#endif

            pf = (pgn>>8) & 0xFF;
            ge = pgn & 0xFF;
            regParam_n = 0; // номер начального регистра с которого отправлять

            // PF рег парама F8
            if( pf == PF )
            {
                // проверка правильности данных о регистре
                if(ge >= Abase_EUR)
                {
                    // вычисление начального RegParam с которого передавать
                    regParam_n = ge - Abase_EUR + 1;

                    // номер регистра в диапазоне запрашиваемых
                    if(regParam_n <= Na)
                    {
                        // Проверка если количество запрашиваемых регистров
                        // больше максимального количества регистров
                        if( (pgnSumm + regParam_n) > Na )
                        {
                            this->pgnSumm = Na - (regParam_n - 1);
//                            this->pgnSumm = Na;
                        }
                        else
                        {
                            this->pgnSumm = pgnSumm;
                        }
                        res = true;
                        isDataToSend = true;
                    }
                }
            }

#if DEBUG_OUT
    debugPrintTextHexValue<u16>("RegParamMakerClass.isDataToSend = ", isDataToSend);
    debugPrintTextHexValue<u16>("RegParamMakerClass.pgnSumm = ", this->pgnSumm);
#endif

            return res;
        }

        void QueryAllRegisters()
        {
            regParam_n = 1;
            pgnSumm = Na;
            isDataToSend = true;
        }

        u8 getRegParamMaxNumber() const
        {
            return Na;
        }

        // TODO: доработать или удалить
        s8 getregCtrl_PS(u8 psNum)
        {
            s8 res = -1;

            switch(psNum)
            {

            }

            return res;
        }

        bool pgnIsRight(u32 pgn)
        {
            if( ((pgn>>8) & 0xFF) == PF )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool IsDataToSend()const
        {
            return isDataToSend;
        }

        u8 getPgnSumm()const
        {
            return pgnSumm;
        }


        bool getDataToSend(u32 &id, Data &data, u8 &dlc)
        {
            RegParamsClass reg = RegParamsClass(epsObjPtr);
            CanIdClass canIdObj;

            if(isDataToSend)
            {
                switch(regParam_n)
                {
                case 1:

                    canIdObj = CanIdClass(PRIOR_LO, PF, Abase_EUR, budAddr);
                    id = canIdObj.getIdAsU32();
                    reg.getRegParam1Data(data, dlc);
                    break;
                case 2:
#if DEBUG_OUT
    debugPrintTextHexValue<u16>("regParam_n = ", regParam_n);
#endif
                    canIdObj = CanIdClass(PRIOR_LO, PF, Abase_EUR+1, budAddr);
                    id = canIdObj.getIdAsU32();
                    reg.getRegParam2Data(data, dlc);
                    break;
                case 3:
#if DEBUG_OUT
    debugPrintTextHexValue<u16>("regParam_n = ", regParam_n);
#endif
                    canIdObj = CanIdClass(PRIOR_LO, PF, Abase_EUR+2, budAddr);
                    id = canIdObj.getIdAsU32();
                    reg.getRegParam3Data(data, dlc);
                    break;
                default:
                    break;
                }

                //if(regParam_n < Na)
                if(regParam_n < pgnSumm)
                {
                    regParam_n++;
                    return true;
                }
                else
                {
                    isDataToSend = false;
                }
            }

            return isDataToSend;
        }



    private:
        GazEpsProtocol::User *epsObjPtr;

        const u8 budAddr = 0x87;

        // количество регистров в ЭУР
        // максимальное количество в соответствии с протоколом может быть = 8
        const u8 Na = 3;

        const u8 PF = 0xF8;
        // адреса устройств
//        const u8 Abase_BUD = 0x20;
        const u8 Abase_EUR = 0x88;

        u8 pf; //
        u8 ge; //
        u8 regParam_n; //!< начальный регистр для передачи
        u8 pgnSumm; //!< кол-во запрашиваемых регистров телеметрии

        bool isDataToSend;

        void FillRegParam1(u32 &id, Data &data, u8 &dlc)
        {

        }
    };

    class MessageList
    {
    public:
        MessageList(){}
        ~MessageList(){}

    private:
        Message *msgPtr;

    };

// ----------------------------------------------------------------------------



    class SyncParamHandlerClass : public ParentHandlerClass
    {
    public:
        SyncParamHandlerClass(){}
        SyncParamHandlerClass(ParentHandlerClass *prevObjPtr){}

// TODO: удалить после проверки
//        SyncParamHandlerClass() : ParentHandlerClass()
//        {
//        }
//        SyncParamHandlerClass(ParentHandlerClass *prevObjPtr):
//            ParentHandlerClass(prevObjPtr) {}
        ~SyncParamHandlerClass() {}


        virtual void init(DataCanSender *dataCanSenderPtr,
                GazEpsProtocol::User *epsObjPtr)
        {
            this->dataCanSenderPtr = dataCanSenderPtr;
            this->epsObjPtr = epsObjPtr;

            regParamObj.init(epsObjPtr);
        }

        virtual bool setData(u32 id, const Data &data, u8 dlc)
        {
            CanIdClass canIdObj = CanIdClass(id);

            // не является запросом RegControl
            if( (canIdObj.getPfField() & PF_SYNC_PARAM) != PF_SYNC_PARAM)
            {
                return false;
            }

            if(dlc == 0) // не содержится поле данных
            {
                // TODO: нужно передать последовательно все регистры
                regParamObj.QueryAllRegisters();

                if(regParamObj.IsDataToSend() == true)
                {
                    regParamObj.getDataToSend(_id, _data, _dlc);
                    Message tempMsg = Message();
                    tempMsg.id = CanIdClass(_id);
                    tempMsg.data = ProtocolData(_data);
                    tempMsg.dlc = _dlc;

                    dataCanSenderPtr->SendData(&tempMsg);
                }
            }
            // неправильный размер поля данных
            else if( dlc != syncParamDataDlc )
            {
#                // нет описания повеления в этой ситуации
                // возможно нужно ответить NACK
                AckNackMaker nack = AckNackMaker();
                nack.getAckNack(_id, _data, _dlc, canIdObj.getPgnAsU32(), true);
                Message tempMsg = Message();
                tempMsg.id = CanIdClass(_id);
                tempMsg.data = ProtocolData(_data);
                tempMsg.dlc = _dlc;
                dataCanSenderPtr->SendData(&tempMsg);
            }
            else
            {
                DecodeData(pgn, pgnSumm, data);

                if( regParamObj.pgnIsRight(pgn) == false ) // неправильный PGN
                {
                    // ответ - NACK
                    AckNackMaker nack;
                    nack.getAckNack(_id,
                            _data,
                            _dlc,
                            canIdObj.getPgnAsU32(),
                            true);
                    Message tempMsg = Message();
                    tempMsg.id = CanIdClass(_id);
                    tempMsg.data = ProtocolData(_data);
                    tempMsg.dlc = _dlc;
                    dataCanSenderPtr->SendData(&tempMsg);
                }
                else // ответ нужным параметром
                {
                    regParamObj.HandleData(pgn, pgnSumm);

                    Message msg;
                    u8 msgCnt = 0;

// TODO: заполняется массив данных для отправки нескольких сообщений
//                    while(regParamObj.IsDataToSend() == true)
//                    {
//                        regParamObj.getDataToSend(_id, _data, _dlc);
//
//                        msg.id.CanIdClass(id);
//                        msg.data = _data;
//                        msg.dlc = _dlc;
//
//                        regParamArray[msgCnt++] = msg;
//                    }

                    if(regParamObj.IsDataToSend() == true)
                    {
                        regParamObj.getDataToSend(_id, _data, _dlc);
                        Message tempMsg = Message();
                        tempMsg.id = CanIdClass(_id);
                        tempMsg.data = ProtocolData(_data);
                        tempMsg.dlc = _dlc;

                        dataCanSenderPtr->SendData(&tempMsg);
                    }
                }
            }

            return true;
        }

        //! расшифровка поля данных
        void DecodeData(u32 &_pgn, u8 &_pgnSumm, const Data &data)
        {
            dataObj.setDataBytes(data);

            dataObj.extractDataFromArray<u32>(_pgn,pgnShift,pgnBitsLength);
            dataObj.extractDataFromArray<u8>
                (_pgnSumm, pgnSummShift, pgnSummBitsLength);
        }

        // TODO: доделать отправку нескольких сообщений
        virtual bool CheckSendingData()
        {
            Message tempMsg = Message();

            u32 tempId = 0x12345678;
            Data tempData;
            u8 tempDlc = 8;

            if(regParamObj.IsDataToSend() == true)
            {
                regParamObj.getDataToSend(_id, _data, _dlc);
                Message tempMsg = Message();
                tempMsg.id = CanIdClass(_id);
                tempMsg.data = ProtocolData(_data);
                tempMsg.dlc = _dlc;

                dataCanSenderPtr->SendData(&tempMsg);
            }
        }

    private:
        DataCanSender *dataCanSenderPtr;
        GazEpsProtocol::User *epsObjPtr;

        u32 _id;
        Data _data;
        u8 _dlc;

        //! Длина в байтах поля данных Reg Control
        const u8 syncParamDataDlc = 4;

        u32 pgn;

        const u8 pgnShift = 0;
        const u8 pgnBitsLength = 24;

        u8 pgnSumm;
        const u8 pgnSummShift = 24;
        const u8 pgnSummBitsLength = 8;

        ProtocolData dataObj;

        RegParamMakerClass regParamObj;

//        cmn::array<Message, regParamObj.getRegParamMaxNumber()> regParamArray;
typedef cmn::array< Message, 3 > regParamArray;


    };

}


#endif /* REG_CONTROL_HANDLER_CLASS_H_ */

