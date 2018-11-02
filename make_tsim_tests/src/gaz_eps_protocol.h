#if !defined(GAZ_EPS_PROTOCOL_H_)
#define GAZ_EPS_PROTOCOL_H_

#include "types.h"
#include "utils.h"

namespace GazEpsProtocol
{

    //! \brief Интерфейсный класс для пользователя протокола
    //! Диаграмма состояний пользователя, исходя из документации:
    //! \dot
    //! digraph app_state {
    //!     SC [label="SELFCONTROL\nсамодиагностика"]
    //!     R  [label = "READY"]
    //!     NR [label = "NOT_READY", color=red]
    //!     W  [label = "WORKING"]
    //!     Е  [label = "TECHMODE"]
    //!     START -> SC
    //!     SC -> R [label="OK"]
    //!     SC -> NR [label="Fail"]
    //!     R -> W [label="control fame"]
    //!     R -> NR [label="error"]
    //!     W -> NR [label="error"]
    //!     NR -> W [label="control fame"]
    //! }
    //! \enddot
    //! Диаграмма состояний пользователя:
    //! \dot
    //! digraph app_state {
    //!     SD [label="предстартовая диагностика"]
    //!     RC  [label = "REMOTE_CONTROL"]
    //!     N [label = "NORMAL"]
    //!     F  [label = "FAILURE", color=red]
    //!     START -> SD
    //!     SD -> N
    //!     SD -> F [label="неисправность", color=red]
    //!     F -> N [label="восстановление", color=green]
    //!     N -> F [label="неисправность", color=red]
    //!     RC -> F [label="неисправность", color=red]
    //!     RC -> N [label="команда control"]
    //!     RC -> N [label="потеря управления"]
    //!     N -> RC [label="команда control"]
    //! }
    //! \enddot

    //! failure
    class User
    {
    public:
        struct Mode
        {
            typedef enum
            {
                NORMAL, REMOTE_CONTROL, FAILURE
            } Enum;
        };
        virtual ~User()
        {
        }
        virtual void goToNormalMode() = 0;
        virtual void goToRemoteControlMode() = 0;
        virtual Mode::Enum getMode() = 0;
        //! \brief сбрасывает флаг ошибки
        //! \return если False, флаг не поддерживается
        virtual void clearError(u8 code) = 0;
        virtual void clearAllErrors() = 0;
        //! \brief Получает флаги ошибок
        //! \note Если количество флагов выходит за диапазон,
        //! то флаги отбрасываются
        virtual u64 getErrorMask()=0;

        virtual void clearWarning(u8 code) = 0;
        virtual void clearAllWarnings() = 0;
        virtual u64 getWarningMask()=0;

        //! \brief Устанавливает уставку положения
        //! \param[in] pos уставка положения (-1.0...1.0)
        virtual void setSteeringWheelPositionRef(f32 pos) = 0;

        //! \brief Возвращает текущее положение
        //! \return текущее положение  (-1.0...1.0)
        virtual f32 getSteeringWheelPosition() = 0;

        //! \brief Устанавливает ограничение скорости
        //! \param[in] speed ограничение скорости (0...1.0)
        virtual void setSteeringWheelSpeedLimit(f32 speed) = 0;

        //! \brief Возвращает текущую скорость
        //! \return текущая скорость (0...1.0)
        virtual f32 getSteeringWheelSpeed() = 0;

        virtual void getVersion(u8 &major, u8 &minor,
        		u16 &revision, u32 &checksum) = 0;

        //! \brief Возвращает текущие коэффициенты ПИ-регулятора положения
        //! \return байты 0, 1 - предельная уставка скорости в формате 2^16
//! \return байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
        //! \return байт 4 - степенной показатель Qp
//! \return байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
        //! \return байт 7 - степенной показатель Qi
        virtual u64 getPidTermsPosition() = 0;

        //! \brief Возвращает текущие коэффициенты ПИ-регулятора скорости
        //! \return байты 0, 1 - предельная уставка момента в формате 2^16
//! \return байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
        //! \return байт 4 - степенной показатель Qp
//! \return байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
        //! \return байт 7 - степенной показатель Qi
        virtual u64 getPidTermsSpeed() = 0;

        //! \brief Устанавливает коэффициенты ПИ-регулятора положения
        //! Байты 0, 1 - предельная уставка скорости в формате 2^16
        //! Байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
        //! Байт 4 - степенной показатель Qp
        //! Байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
        //! Байт 7 - степенной показатель Qi
        virtual void setPidTermsPosition(u64 positionTerms) = 0;

        //! \brief Устанавливает коэффициенты ПИ-регулятора скорости
        //! Байты 0, 1 - предельная уставка момента в формате 2^16
        //! Байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
        //! Байт 4 - степенной показатель Qp
        //! Байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
        //! Байт 7 - степенной показатель Qi
        virtual void setPidTermsSpeed(u64 speedTerms) = 0;
    };

}

#endif // GAZ_EPS_PROTOCOL_H_
