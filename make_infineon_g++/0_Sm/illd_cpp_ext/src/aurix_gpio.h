#if !defined(AURIX_GPIO_H)
#define AURIX_GPIO_H

#include "IfxPort.h"
#include "types.h"

namespace Aurix
{
    namespace Gpio
    {
        enum class InputMode
        {
            undefined = IfxPort_InputMode_undefined,
            noPullDevice = IfxPort_InputMode_noPullDevice,
            pullDown = IfxPort_InputMode_pullDown,
            pullUp = IfxPort_InputMode_pullUp
        };

        enum class Mode
        {
            inputNoPullDevice = IfxPort_Mode_inputNoPullDevice,
            inputPullDown = IfxPort_Mode_inputPullDown,
            inputPullUp = IfxPort_Mode_inputPullUp,
            outputPushPullGeneral = IfxPort_Mode_outputPushPullGeneral,
            outputPushPullAlt1 = IfxPort_Mode_outputPushPullAlt1,
            outputPushPullAlt2 = IfxPort_Mode_outputPushPullAlt2,
            outputPushPullAlt3 = IfxPort_Mode_outputPushPullAlt3,
            outputPushPullAlt4 = IfxPort_Mode_outputPushPullAlt4,
            outputPushPullAlt5 = IfxPort_Mode_outputPushPullAlt5,
            outputPushPullAlt6 = IfxPort_Mode_outputPushPullAlt6,
            outputPushPullAlt7 = IfxPort_Mode_outputPushPullAlt7,
            outputOpenDrainGeneral = IfxPort_Mode_outputOpenDrainGeneral,
            outputOpenDrainAlt1 = IfxPort_Mode_outputOpenDrainAlt1,
            outputOpenDrainAlt2 = IfxPort_Mode_outputOpenDrainAlt2,
            outputOpenDrainAlt3 = IfxPort_Mode_outputOpenDrainAlt3,
            outputOpenDrainAlt4 = IfxPort_Mode_outputOpenDrainAlt4,
            outputOpenDrainAlt5 = IfxPort_Mode_outputOpenDrainAlt5,
            outputOpenDrainAlt6 = IfxPort_Mode_outputOpenDrainAlt6,
            outputOpenDrainAlt7 = IfxPort_Mode_outputOpenDrainAlt7
        };

        enum class OutputIdx
        {
            general = IfxPort_OutputIdx_general,
            alt1 = IfxPort_OutputIdx_alt1,
            alt2 = IfxPort_OutputIdx_alt2,
            alt3 = IfxPort_OutputIdx_alt3,
            alt4 = IfxPort_OutputIdx_alt4,
            alt5 = IfxPort_OutputIdx_alt5,
            alt6 = IfxPort_OutputIdx_alt6,
            alt7 = IfxPort_OutputIdx_alt7
        };

        enum class OutputMode
        {
            pushPull = IfxPort_OutputMode_pushPull,
            openDrain = IfxPort_OutputMode_openDrain
        };

        enum class PadDriver
        {
            cmosAutomotiveSpeed1 = IfxPort_PadDriver_cmosAutomotiveSpeed1,
            cmosAutomotiveSpeed2 = IfxPort_PadDriver_cmosAutomotiveSpeed2,
            cmosAutomotiveSpeed3 = IfxPort_PadDriver_cmosAutomotiveSpeed3,
            cmosAutomotiveSpeed4 = IfxPort_PadDriver_cmosAutomotiveSpeed4,
            ttlSpeed1 = IfxPort_PadDriver_ttlSpeed1,
            ttlSpeed2 = IfxPort_PadDriver_ttlSpeed2,
            ttlSpeed3 = IfxPort_PadDriver_ttlSpeed3,
            ttlSpeed4 = IfxPort_PadDriver_ttlSpeed4
        };

        enum class State
        {
            notChanged = IfxPort_State_notChanged,
            high = IfxPort_State_high,
            low = IfxPort_State_low,
            toggled = IfxPort_State_toggled
        };

        class Line
        {
        public:
            Ifx_P *portReg;
            u8 pinIndex;

            Line(Ifx_P *p, u8 i) :
                    portReg(p), pinIndex(i)
            {
            }

            bool isHigh()
            {
                return static_cast<bool>(IfxPort_getPinState(portReg, pinIndex));
            }
            void setHigh()
            {
                IfxPort_setPinHigh(portReg, pinIndex);
            }
            void setLow()
            {
                IfxPort_setPinLow(portReg, pinIndex);
            }

            void setInputMode(InputMode mode)
            {
                IfxPort_setPinModeInput(portReg, pinIndex,
                        static_cast<IfxPort_InputMode>(mode));
            }

            void setOutputMode(OutputMode mode, OutputIdx index)
            {
                IfxPort_setPinModeOutput(portReg, pinIndex,
                        static_cast<IfxPort_OutputMode>(mode),
                        static_cast<IfxPort_OutputIdx>(index));
            }

            void setState(State action)
            {
                IfxPort_setPinState(portReg, pinIndex,
                        static_cast<IfxPort_State>(action));
            }

            void toggle()
            {
                IfxPort_togglePin(portReg, pinIndex);
            }

            bool disableEmergencyStop()
            {
                return static_cast<bool>(IfxPort_disableEmergencyStop(portReg,
                        pinIndex));
            }

            bool enableEmergencyStop()
            {
                return static_cast<bool>(IfxPort_enableEmergencyStop(portReg,
                        pinIndex));
            }

            void setMode(Mode mode)
            {
                IfxPort_setPinMode(portReg, pinIndex,
                        static_cast<IfxPort_Mode>(mode));
            }

            void setPadDriver(PadDriver padDriver)
            {
                IfxPort_setPinPadDriver(portReg, pinIndex,
                        static_cast<IfxPort_PadDriver>(padDriver));
            }

            void resetESR()
            {
                IfxPort_resetESR(portReg, pinIndex);
            }

            void setESR()
            {
                IfxPort_setESR(portReg, pinIndex);
            }
        };

        class Port
        {
        public:
            Ifx_P *portReg;

            Port(Ifx_P *p) :
                    portReg(p)
            {
            }

            u32 getGroupState(u8 pinIndex, u16 mask)
            {
                return IfxPort_getGroupState(portReg, pinIndex, mask);
            }

            void setGroupState(u8 pinIndex, u16 mask, u16 data)
            {
                IfxPort_setGroupState(portReg, pinIndex, mask, data);
            }

            s32 getIndex()
            {
                return IfxPort_getIndex(portReg);
            }

            void setGroupModeInput(u8 pinIndex, u16 mask,
                    IfxPort_InputMode mode)
            {
                IfxPort_setGroupModeInput(portReg, pinIndex, mask, mode);
            }

            void setGroupModeInput(u8 pinIndex, u16 mask, InputMode mode)
            {
                setGroupModeInput(pinIndex, mask,
                        static_cast<IfxPort_InputMode>(mode));
            }

            void setGroupModeOutput(u8 pinIndex, u16 mask,
                    IfxPort_OutputMode mode, IfxPort_OutputIdx index)
            {
                IfxPort_setGroupModeOutput(portReg, pinIndex, mask, mode,
                        index);
            }

            void setGroupModeOutput(u8 pinIndex, u16 mask, OutputMode mode,
                    OutputIdx index)
            {
                setGroupModeOutput(pinIndex, mask,
                        static_cast<IfxPort_OutputMode>(mode),
                        static_cast<IfxPort_OutputIdx>(index));
            }

            void setGroupPadDriver(u8 pinIndex, u16 mask,
                    IfxPort_PadDriver padDriver)
            {
                IfxPort_setGroupPadDriver(portReg, pinIndex, mask, padDriver);
            }

            void setGroupPadDriver(u8 pinIndex, u16 mask, PadDriver padDriver)
            {
                setGroupPadDriver(pinIndex, mask,
                        static_cast<IfxPort_PadDriver>(padDriver));
            }
        };
    }
}

#endif /* AURIX_GPIO_H */
