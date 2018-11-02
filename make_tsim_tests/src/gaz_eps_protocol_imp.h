#if !defined(GAZ_EPS_PROTOCOL_IMP_H_)
#define GAZ_EPS_PROTOCOL_IMP_H_

#include "can_dl.h"
#include "can_message.h"
#include "const.h"
#include "gaz_eps_protocol.h"


#include "request_class.h"
#include "sync_ctrl_handler_class.h"
#include "control_handler_class.h"
#include "reg_control_handler.h"
#include "parent_handler_class.h"
#include "sync_param_handler_class.h"

#define DEBUG_LOG false

namespace GazEpsProtocolImp
{

    template < class Time >
    class ProtocolLayer: public CanDL::User
    {
    public:
    	ProtocolLayer()
        {
//    	    requestHandlerObj = RequestHandlerClass();
        }
    	~ProtocolLayer() {}

        // TODO: доделать. Сделать проаерку нулевых указателей
    	void init(CanDL::Layer *canObjPtr, GazEpsProtocol::User *epsObjPtr)
        {
    	    t_dlConfirm = Time::current();
    	    t_SyncCtrl = Time::current();

    	    if(canObjPtr)
    	    {
    	        this->canObjPtr = canObjPtr;
    	        // return true;
    	    }
    	    else
    	    {
    	        // return false;
    	    }
    	    if(epsObjPtr)
    	    {
    	        this->epsObjPtr = epsObjPtr;
    	        // return true;
    	    }
    	    else
    	    {
    	        // return false;
    	    }

    		dataSenderObj.init( canObjPtr );

    		requestHandlerObj.init(&dataSenderObj, epsObjPtr);
    		syncCtrlHandleObj.init(&dataSenderObj, epsObjPtr);
    		controlHandlerObj.init(&dataSenderObj, epsObjPtr);
    		syncParamHandlerObj.init(&dataSenderObj, epsObjPtr);

    		classPtrArray[handlersCnt++] = &requestHandlerObj;
    		classPtrArray[handlersCnt++] = &controlHandlerObj;
    		classPtrArray[handlersCnt++] = &syncParamHandlerObj;
    		classPtrArray[handlersCnt++] = &syncCtrlHandleObj;

    		errMkr.init(&dataSenderObj, epsObjPtr);

        }

		void timeUpdate(void)
		{
		    errMkr.checkForNewErrors();

		    typename Time::Type t = Time::current();

            if( syncCtrlHandleObj.IsSyncCtrlReceived() )
            {
                t_SyncCtrl = t;
            }
            else
            {
                // 1000 мс
                if (t - t_SyncCtrl > Time::ticks(1.0f))
                {
                    errMkr.SendErrors(1);
                    // потеря управления
                    epsObjPtr->goToNormalMode(); // переход в местный режим
                }
            }

			// таймаут на зависание передатчика
			if(dataSenderObj.dataIsSent() == false)
			{
			    t_dlConfirm = t;
			}
			else // не было подтверждения отправки данных
			{
			    if (t - t_dlConfirm > Time::ticks(0.01f))
			    {
			        // отправка запроса на сброс передатчика
	                canObjPtr->dlBreakRequest();
                    // перевод ЭУР в режим местного управления
                    epsObjPtr->goToNormalMode();
			    }
			}

		}

        //\brief вызывается из объекта CAN при приёме данных по Rx
        virtual void dlIndication(u32 id, const Data &data, u8 dlc)
        {
            if( dataSenderObj.dataIsSent() == true ) return;

        	Message msg = Message();
        	msg.id = CanIdClass(id);
        	msg.data = ProtocolData(data);
        	msg.dlc = dlc;

        	if( msg.id.ValidateId(MCM_ID))
        	{
        	    for(u8 i = 0; i < handlersCnt; i++)
            	{
            	    // TODO: рефакторинг метода
            		classPtrArray[i]->setData(msg.id.getIdAsU32(),
            		        msg.data.getDataBytes(), msg.dlc);
            	}
        	}
        }

        // вызывается из объекта CAN при событии отправки данных Tx
        virtual void dlConfirm()
        {
        	dataSenderObj.dlConfirmReset();

//        	t_dlConfirm = Time::current();

//        	controlHandlerObj.CheckSendingData();

            for(u8 i = 0; i < handlersCnt; i++)
            {
                classPtrArray[i]->CheckSendingData();
            }

        }

        // вызов отмены передачи
        void BreakRequest(void)
        {
        	canObjPtr->dlBreakRequest();
        }


    private:

        DataCanSender dataSenderObj;

        CanIdClass canIdObj;

        ParentHandlerClass *classPtrArray[4];

        ErrorsMaker errMkr;

        u8 handlersCnt = 0;
        RequestHandlerClass requestHandlerObj;
        ControlHandlerClass controlHandlerObj;
        SyncCtrlHandlerClass syncCtrlHandleObj;
        SyncParamHandlerClass syncParamHandlerObj;

        //! указатель на объект CAN
        CanDL::Layer *canObjPtr;
        //! указатель на объект ЭУР
        GazEpsProtocol::User *epsObjPtr;

        // TODO: таймаут ожидания команды управления
        typename Time::Type t_SyncCtrl;
        // TODO: таймаут ожидания подтверждения отправки сообщения
        typename Time::Type t_dlConfirm;

        // TODO: вставить константы в соответствующий класс
        const u16 maxWheelPosition = 2000;
        const u8 maxTurnSpeed = 100;

		// преобразование из UINT16(0 - maxVal) во Float в относительных
        // единицах (-1.0 - 1.0)
        // TODO: вставить в соответствующий класс
//		f32 ConvertWheelPositionFromU16ToF32(u16 val, u16 maxVal)
//		{
//			f32 fl_val = val;
//			f32 fl_shift = maxVal/2;
//			f32 res;
//
//			res = (fl_val - 1000) / 1000;
//
//			return res;
//		}

		// преобразование из Float в относительных единицах (-1.0 - 1.0)
		// в UINT16(0 - maxVal)
		// TODO: вставить в соответствующий класс
//		u16 ConvertWheelPositionFromF32ToU16(f32 val, u16 maxVal)
//		{
//			f32 fl_shift = maxVal/2;
//
//			f32 tmp = (val + 1) * fl_shift;
//
//			return (u16)tmp;
//		}

		// преобразование скорости поворота руля из uint8(0 - 100)
		//к Float(0.0 - 1.0)
		// TODO: вставить в соответствующий класс
//		f32 ConvertTurnedSpeedFromU8ToF32(u8 val, u8 maxVal)
//		{
//			f32 fl_val = val;
//			f32 fl_max_val = maxVal;
//
//			f32 res = fl_val / fl_max_val;
//
//			return res;
//		}

		// преобразование скорости поворота руля из Float(0.0 - 1.0)
		// к uint8(0 - 100)
		// TODO: вставить в соответствующий класс

//		u8 ConvertTurnedSpeedFromF32ToU8(f32 val, u8 maxVal)
//		{
//			val = val * maxVal;
//			return (u8)val;
//		}

    };
}

#endif // GAZ_EPS_PROTOCOL_IMP_H_

