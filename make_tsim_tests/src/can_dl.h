#if !defined(CAN_DL_H_)
#define CAN_DL_H_

#include "types.h"
#include "array.h"
#include "utils.h"

namespace CanDL
{
    class Layer
    {
    public:
        virtual ~Layer()
        {
        }
        virtual bool dlRequest(u32 id, const Data &data, u8 dlc) = 0;
        virtual void dlBreakRequest() = 0;
    };

    class User
    {
    public:
        virtual ~User()
        {
        }
        virtual void dlIndication(u32 id, const Data &data, u8 dlc) = 0;
        virtual void dlConfirm() = 0;
    };

}

#endif // CAN_DL_H_
