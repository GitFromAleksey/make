#ifndef SRC_CAN_MESSAGE_H_
#define SRC_CAN_MESSAGE_H_

#include "types.h"
#include "array.h"
#include "utils.h"
#include "const.h"

#include <iostream>
using namespace std;

namespace GazEpsProtocolImp
{

    //! структура CAN ID
    struct CanIdStruct
    {
        u8 priority	: 3;	//!< приоритет 0-7. 0 - наименьший
        u8 reserved	: 1;
        u8 DP		: 1;	//!< Data Page страница данных
        //! Source Address - адрес устройства, которое передало сообщение
        u8 SA;

        J1939PGN pgn;
        CanIdStruct()
        {
            priority = 0;
            reserved = 0;
            DP = 0;
            SA = 0;
            J1939PGN pgn = J1939PGN();
        }
    };

    class CanIdClass
    {
    public:

        //! Конструктор без аргументов - CAN ID заполняется нулями
        CanIdClass()
        {
            canIdStruct = CanIdStruct();
        }

        //! Конструктор, принимающий 32-битное представление ID
        CanIdClass(u32 id)
        {
            // Вызов конструктора по умолчанию (инициализация нулями)
            CanIdClass();

            setPriorityField((id >> 26) &	0x00000007);
            setReservedField((id >> 25) &	0x00000001);
            setDpField((id >> 24) &			0x00000001);
            setPfField((id >> 16) &			0x000000FF);
            setPsField((id >> 8) &			0x000000FF);
            setSaField(id &					0x000000FF);
        }

        //! Конструктор, собирающий ID из параметров
        CanIdClass(u8 priority, u8 pf, u8 ps, u8 sa)
        {
            // Вызов конструктора по умолчанию (инициализация нулями)
            CanIdClass();

            setPriorityField(priority);
            setReservedField(0);
            setDpField(0);
            setPfField(pf);
            setPsField(ps);
            setSaField(sa);
        }

        ~CanIdClass(){}

        bool ValidateId(u8 budAddr)
        {
            bool result = false;

            // Поле приоритета от 0 до 7
            if(getPriorityField() <= 7)
            {
                // Поле Reserved должно быть равным нулю
                if(getReservedField() == 0)
                {
                    // В протоколе используется страница 0
                    if(getDpField() == 0)
                    {
                        // Если хотя бы одно из полей PF и PS не равно нулю
                        if(getPfField() || getPsField())
                        {
                            // Проверка адреса
                            if(getSaField() == budAddr)
                            {
                                result = true;
                            }
                        }
                    }
                }
            }
            return result;
        }

        u8 getPriorityField(void)
        {
            return canIdStruct.priority;
        }

        u8 getReservedField(void)
        {
            return canIdStruct.reserved;
        }

        u8 getDpField(void)
        {
            return canIdStruct.DP;
        }

        u8 getPfField(void)
        {
            return canIdStruct.pgn.pf;
        }

        u8 getPsField(void)
        {
            return canIdStruct.pgn.ps;
        }

        u8 getSaField(void)
        {
            return canIdStruct.SA;
        }

        void setPriorityField(u8 priority)
        {
            canIdStruct.priority = priority;
        }

        void setReservedField(u8 reserved)
        {
            canIdStruct.reserved = reserved;
        }

        void setDpField(u8 dataPage)
        {
            canIdStruct.DP = dataPage;
        }

        void setPfField(u8 pf)
        {
            canIdStruct.pgn.pf = pf;
        }

        void setPsField(u8 ps)
        {
            canIdStruct.pgn.ps = ps;
        }

        void setSaField(u8 sa)
        {
            canIdStruct.SA = sa;
        }

        u32 getPgnAsU32(void)
        {
            return canIdStruct.pgn.getAsU32();
        }

        u32 getIdAsU32()
        {
            u32 retId = 0;
            retId |= ((u32)getPriorityField() << 26);
            retId |= ((u32)getReservedField() << 25);
            retId |= ((u32)getDpField() << 24);
            retId |= ((u32)getPfField() << 16);
            retId |= ((u32)getPsField() << 8);
            retId |= getSaField();
            return retId;
        }

    private:
        CanIdStruct canIdStruct;
    };


    //! Класс данных, принимаемых в составе пакета CAN
    class ProtocolData
    {
    public:

        //! Конструктор с 64-битным словом
        ProtocolData(u64 dataWord)
        {
            setDataBytesByWord(dataWord);
        }

        //! Конструктор с массивом
        ProtocolData(Data dataBytesArray)
        {
            setDataBytes(dataBytesArray);
        }

        //! Конструктор по умолчанию без аргументов
        ProtocolData()
        {
            setDataBytesByWord(0);
        }

        //! \brief Метод записывает в Data произвольные данные так,
        //! как если бы она представлялась одним 64-битным словом
        //!
        //! TODO: переделать без использования 64-битных слов
        template <typename T>
        bool insertDataInArray(T newData, u8 shift, u8 bitLen)
        {
            if (shift >= (dataSize * 8))
            {
                // Сдвиг больше, чем длина всех данных
                return true;
            }

            u64 temp = unpackData(dataBytes);
            u64 mask = 0;
            for (u8 i = 0; i < bitLen; i++)
            {
                mask |= 1 << i;
            }

            // Заполнение нулями тех битов, на место
            // которых должны быть вписаны новые
            temp &= ~(mask << shift);
            temp |= ((u64)newData & mask) << shift;

            dataBytes = packData(temp, dataSize);
            return false;
        }

        //! \brief Метод извлекает данные из Data с определённым сдвигом
        //!
        //! TODO: переделать без использования 64-битных слов
        template <typename T>
        bool extractDataFromArray(T &data, u8 shift, u8 bitLen) const
        {
            if (bitLen > (sizeof(T) * 8)    ||
                    bitLen > 64)
            {
                // Длина запрошенных данных превышает максимум,
                // либо данные такой длины не поместятся в целевую переменную
                return false;
            }

            data = 0;

            u64 temp = unpackData(dataBytes);
            u64 mask = 0;
            for (u8 i = 0; i < bitLen; i++)
            {
                mask |= 1 << i;
            }

            data = (temp >> shift) & mask;
            return true;
        }

        //! Выводит в консоль список байтов, в десятичном виде
        void print()
        {
            for( u8 i = 0; i <= 7; i++)
            {
                cout    << "Data byte " << (int)i << ": "
                        << (int)dataBytes[i] << endl;
            }
        }

        //! Заполнение массива 64-битным словом
        void setDataBytesByWord(u64 dataWord)
        {
            for( u8 i = 0; i <= 7; i++)
            {
                dataBytes[i] = dataWord >> (i * 8);
            }
        }

        void setDataBytes(Data dataBytes)
        {
            this->dataBytes = dataBytes;
        }

        Data getDataBytes() const
        {
            return this->dataBytes;
        }

    private:
        Data dataBytes;
    };

    struct Message
    {
        CanIdClass id;
        ProtocolData data;
        u8 dlc;

        Message()
        {
            id = CanIdClass();
            data = ProtocolData();
            dlc = 0;
        }
    };

}

#endif /* SRC_CAN_MESSAGE_H_ */
