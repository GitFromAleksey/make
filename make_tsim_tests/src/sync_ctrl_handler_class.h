/*
 * sync_ctrl_class.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: user1
 */

#ifndef SYNC_CTRL_CLASS_H_
#define SYNC_CTRL_CLASS_H_

#include "types.h"
#include "array.h"
#include "can_dl.h"
#include "const.h"
#include "can_message.h"
#include "parent_handler_class.h"
#include "gaz_eps_protocol.h"

namespace GazEpsProtocolImp
{
    class AbstractRegCtrlProcessor
    {
    public:

        AbstractRegCtrlProcessor()
        {
            this->epsObjPtr = nullptr;
        };

        AbstractRegCtrlProcessor(GazEpsProtocol::User *epsPtr)
        {
            this->epsObjPtr = epsPtr;
        };

        //! Проверка ID для REG_CTRL_n
        //!
        //! @param[in] id ID для сравнения
        //! \returns true, если ID совпадает, и false - если нет
        virtual bool compareId(CanIdClass &id) = 0;

        //! Проверка данных сообщения REG_CTRL_n
        //!
        //! @param[in] data Данные сообщения для анализа
        //! \returns false, если данные неверные, true - если верные
        virtual bool validateData(const ProtocolData &data) = 0;

        //! Применить полученные данные для управления
        virtual void applyData() = 0;

        GazEpsProtocol::User *epsObjPtr;
    };

    class RegCtrl1Processor : AbstractRegCtrlProcessor
    {
    public:

        RegCtrl1Processor()
        {
            wheelPosition = 0;
            wheelSpeed = 0;
        }

        RegCtrl1Processor(GazEpsProtocol::User *epsPtr) :
            AbstractRegCtrlProcessor(epsPtr)
        {
            RegCtrl1Processor();
        }

        virtual bool compareId(CanIdClass &id)
        {
            if(id.getPfField() == REGCTRL1_PF)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        virtual bool validateData(const ProtocolData &data)
        {
            // TODO: в протоколе указаны специальные значения - 2047 и 255
            // "не применять команду". Неясно пока, как и зачем их обрабатывать

            data.extractDataFromArray<u16>(wheelPosition, 0, 11);
            data.extractDataFromArray<u8>(wheelSpeed, 16, 8);

            if((wheelPosition <= 2000) &&
                    (wheelSpeed <= 100))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        virtual void applyData()
        {
            f32 posValue;
            posValue = (f32)wheelPosition;
            posValue -= 1000.0;
            posValue /= 1000;

            this->epsObjPtr->setSteeringWheelPositionRef(posValue);

            f32 speedValue;
            speedValue = (f32)wheelSpeed;
            speedValue /= 100;

            this->epsObjPtr->setSteeringWheelSpeedLimit(speedValue);
        }

    private:
        u16 wheelPosition;
        u8 wheelSpeed;
    };

    class RegCtrl2Processor : AbstractRegCtrlProcessor
    {
    public:

        RegCtrl2Processor()
        {
            termsWord = 0;
        }

        RegCtrl2Processor(GazEpsProtocol::User *epsPtr) :
            AbstractRegCtrlProcessor(epsPtr)
        {
            RegCtrl2Processor();
        }

        virtual bool compareId(CanIdClass &id)
        {
            if(id.getPfField() == REGCTRL2_PF)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! Проверка данных сообщения REG_CTRL_2
        virtual bool validateData(const ProtocolData &data)
        {
            //! это параметры ПИД-регулятора, они всегда верные!
            termsWord = unpackData(data.getDataBytes());
            return true;
        }

        virtual void applyData()
        {
            this->epsObjPtr->setPidTermsPosition(termsWord);
        }

    private:
        u64 termsWord;
    };

    class RegCtrl3Processor : AbstractRegCtrlProcessor
    {
    public:

        RegCtrl3Processor()
        {
            termsWord = 0;
        }

        RegCtrl3Processor(GazEpsProtocol::User *epsPtr) :
            AbstractRegCtrlProcessor(epsPtr)
        {
            RegCtrl2Processor();
        }

        virtual bool compareId(CanIdClass &id)
        {
            if(id.getPfField() == REGCTRL3_PF)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //! Проверка данных сообщения REG_CTRL_3
        virtual bool validateData(const ProtocolData &data)
        {
            //! это параметры ПИД-регулятора, они всегда верные!
            termsWord = unpackData(data.getDataBytes());
            return true;
        }

        virtual void applyData()
        {
            this->epsObjPtr->setPidTermsSpeed(termsWord);
        }

    private:
        u64 termsWord;
    };

// ---*---*---*---*---*---*---*---*---*---*---*---*---*---*---

    class SyncCtrlHandlerClass : public ParentHandlerClass
    {
    public:
        SyncCtrlHandlerClass() : ParentHandlerClass()
        {
            isRegCtrlReceived = false;
            storedMsg = Message();
            msg = Message();

            this->dataCanSenderPtr = nullptr;
            this->epsObjPtr = nullptr;
            nack.init(nullptr, nullptr);
        }

        SyncCtrlHandlerClass(DataCanSender *canSender,
                GazEpsProtocol::User *epsObject) :
                    ParentHandlerClass()
        {
            isRegCtrlReceived = false;
            isSyncCtrlReceived = false;
            storedMsg = Message();
            msg = Message();

            this->dataCanSenderPtr = canSender;
            this->epsObjPtr = epsObject;
            nack.init(canSender, epsObject);
        }



        ~SyncCtrlHandlerClass(){}

        virtual void init(DataCanSender *dataCanSenderPtr,
                GazEpsProtocol::User *epsObjPtr)
        {
            nack.init(dataCanSenderPtr, epsObjPtr);

            this->dataCanSenderPtr = dataCanSenderPtr;
            this->epsObjPtr = epsObjPtr;

            regCtrl1Processor = RegCtrl1Processor(epsObjPtr);
            regCtrl2Processor = RegCtrl2Processor(epsObjPtr);
            regCtrl3Processor = RegCtrl3Processor(epsObjPtr);

            u8 processors = 0;
            processorsArray[processors++] =
                    (AbstractRegCtrlProcessor*)&regCtrl1Processor;
            processorsArray[processors++] =
                    (AbstractRegCtrlProcessor*)&regCtrl2Processor;
            processorsArray[processors++] =
                    (AbstractRegCtrlProcessor*)&regCtrl3Processor;
        }

        bool IsSyncCtrlReceived()
        {
            bool res = isSyncCtrlReceived;

            isSyncCtrlReceived = false;

            return res;
        }

        virtual bool setData(u32 id, const Data &data, u8 dlc)
        {
            msg.id = CanIdClass(id);
            msg.data = ProtocolData(data);
            msg.dlc = dlc;

            if(msg.id.getPfField() == PF_SYNC_CTRL)
            {
                // Принят SYNC_CTRL
                processSyncCtrl();

                isSyncCtrlReceived = true;

                return true;
            }

            if((msg.id.getPfField() >= REGCTRL1_PF) &&
                    (msg.id.getPfField() <
                            (REGCTRL1_PF + kRegCtrlTotalNumber)))
            {
                // Принят REG_CTRL
                if(msg.dlc == REGCTRL1_DATA_SIZE)
                {
                    // DLC правильная
                    this->storedMsg.id = CanIdClass(id);
                    this->storedMsg.data.setDataBytes(data);
                    this->storedMsg.dlc = dlc;

                    isRegCtrlReceived = true;
                    return true;
                }
            }

            // Принято что-то другое
            return false;
        }

        virtual bool CheckSendingData()
        {
            return false;
        }

    private:
        DataCanSender *dataCanSenderPtr;
        GazEpsProtocol::User *epsObjPtr;

        //! Массив с указателями на обработчики разных REG_CTRL
        AbstractRegCtrlProcessor *processorsArray[3];

        AckNackMaker nack;

        RegCtrl1Processor regCtrl1Processor;
        RegCtrl2Processor regCtrl2Processor;
        RegCtrl3Processor regCtrl3Processor;

        //! Общее количество регистров управления
        static const u8 kRegCtrlTotalNumber = 3;

        Message msg;
        Message storedMsg;

        bool isRegCtrlReceived;
        bool isSyncCtrlReceived;

        //! Обработать полученное сообщение SYNC_CTRL
        void processSyncCtrl()
        {
            //! SYNC_CTRL обрабатывается только в режиме ДУ
            if (epsObjPtr->getMode() ==
                    GazEpsProtocol::User::Mode::REMOTE_CONTROL)
            {
                // Если сохранены данные, готовые к применению
                if (isRegCtrlReceived)
                {
                    // Снять флаг, т.к. сейчас данные будут обработаны
                    isRegCtrlReceived = false;

                    for(u8 i = 0; i < kRegCtrlTotalNumber; i++)
                    {
                        // Поиск обработчика для сохраненных данных
                        if(processorsArray[i]->compareId(storedMsg.id))
                        {
                            // Найден обработчик; передать данные на проверку
                            if(processorsArray[i]->validateData(storedMsg.data))
                            {
                                // Данные верны; применить данные
                                processorsArray[i]->applyData();
                            }
                            else
                            {
                                // данные неверны
                                nack.SendNack(msg.id.getPgnAsU32());
                            }
                            // Остановить поиск обработчика
                            break;
                        }
                    }
                }
                else
                {
                    // SYNC_CTRL пришел, а REG_CTRL не приходил
                    nack.SendNack(msg.id.getPgnAsU32());
                }
            }
            else
            {
                // SYNC_CTRL принят не в режиме ДУ/WORKING/REMOTE_CONTROL
                nack.SendNack(msg.id.getPgnAsU32());
            }
        }
    };
}

#endif /* SYNC_CTRL_CLASS_H_ */
