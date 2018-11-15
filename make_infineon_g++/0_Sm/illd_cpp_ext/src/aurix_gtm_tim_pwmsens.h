#if !defined(AURIX_GTM_TIM_PWM_SENSOR_H)
#   define AURIX_GTM_TIM_PWM_SENSOR_H

#   include "aurix_gtm_tim.h"

//#############################################################################

class PwmSensor
{
public:
    enum class State
    {
        ok = 0,
        stuckLow,
        stuckHigh,
        badCarrierTooSlow,
        badCarrierTooFast,
        badDutyMin,
        badDutyMax,
        badConf
    };
    //-------------------------------------------------------------------------
    struct SysConf
    {
        IfxGtm_Tim_TinMap *map;
        Aurix::Gtm::Tim::Clk clk;
        Aurix::Gtm::Tim::FiltClk filtClk;
        Aurix::Gtm::Tim::Clk toClk;
        u32 clk_Hz;
        u32 filtClk_Hz;
        u32 toClk_Hz;
        Ifx_Priority isrPrio;
    };
    //-------------------------------------------------------------------------
    struct Conf
    {
        u16 pwmFreqRange[2];
        u16 timeoutRatio;
        u16 reserved;
        f32 edgeFiltTime;
        f32 pwmDutyRange[2];
        f32 pwmDutyOffset;
        f32 outputGain;
    };
    //-------------------------------------------------------------------------
    bool init(const Conf &conf_, const SysConf &sysConf)
    {
        bool res = true;
        map = sysConf.map;
        u8 *ptim = (u8 *)&MODULE_GTM.TIM[map->tim];
        u32 i_ch = u32(map->channel) * (sizeof(Ifx_GTM_TIM) / 8);
        p_hw = (Ifx_GTM_TIM_CH *)(ptim + i_ch);

        _conf = conf_;
        res = res
            && _conf.pwmFreqRange[0] < _conf.pwmFreqRange[1]
            && _conf.pwmDutyRange[0] < _conf.pwmDutyRange[1]
            && _conf.pwmDutyOffset > _conf.pwmDutyRange[0]
            && _conf.pwmDutyOffset < _conf.pwmDutyRange[1];
        if (res)
        {
            periodRange[0] = sysConf.clk_Hz / _conf.pwmFreqRange[1];
            periodRange[1] = sysConf.clk_Hz / _conf.pwmFreqRange[0];
            res = hwInit(sysConf);
        }
        _state = res ? State::ok : State::badConf;
        resetOutput();

        return res;
    }
    //-------------------------------------------------------------------------
    void onNewVal()
    {
        if (p_hw->IRQ_NOTIFY.B.TODET)
        {
            Ifx_GTM_TIM_CH_IRQ_NOTIFY flag;
            flag.U = 0;
            flag.B.TODET = true;
            flag.B.NEWVAL = true;
            p_hw->IRQ_NOTIFY.U = flag.U;
            resetOutput();
            _state = pinState() ? State::stuckHigh : State::stuckLow;
        }
        else
        {
            // UM[24.5.4.1]:
            // ...the acknowledge for reading out data is performed by a read
            // access to the register GPR0. Thus, register GPR1 should be read
            // always before GPR0.
            _period = p_hw->GPR1.B.GPR1;
            _pulse = p_hw->GPR0.B.GPR0;
            if (_period < periodRange[0])
            {
                _state = State::badCarrierTooFast;
            }
            else if (_period > periodRange[1])
            {
                _state = State::badCarrierTooSlow;
            }
            else
            {
                f32 v = f32(_pulse) / f32(_period);
                if (v < _conf.pwmDutyRange[0])
                {
                    _state = State::badDutyMin;
                }
                else if (v > _conf.pwmDutyRange[1])
                {
                    _state = State::badDutyMax;
                }
                {
                    _state = State::ok;
                    _duty = v;
                    _output[1] = _output[0];
                    _output[0] = _conf.outputGain * (v - _conf.pwmDutyOffset);
                }
            }
        }
    }
    //-------------------------------------------------------------------------
    u32 pulse() const {return _pulse;}
    u32 period() const {return _period;}
    f32 dutyFactor() const {return _duty;}
    f32 dutyOffset() const {return _conf.pwmDutyOffset;}
    f32 output() const {return _output[0];}
    f32 outputPrev() const {return _output[1];}
    State state() const {return _state;}
    bool isValid() const {return _state == State::ok;}
    //-------------------------------------------------------------------------
    bool pinState() const
    {
        const IfxPort_Pin &pin = map->pin;
        return IfxPort_getPinState(pin.port, pin.pinIndex);
    }
    //-------------------------------------------------------------------------
DEBUG_PUBLIC(private):
    IfxGtm_Tim_TinMap *map;
    Ifx_GTM_TIM_CH *p_hw;
    Conf _conf;
    u32 periodRange[2];
    u32 _pulse;
    u32 _period;
    f32 _duty;
    f32 _output[2];
    State _state;
    //-------------------------------------------------------------------------
    bool hwInit(const SysConf &sysConf)
    {
        using namespace Aurix::Gtm::Tim;
        {
            Ifx_GTM_TIM_CH_CTRL cfg;
            cfg.U = 0;
            cfg.B.TIM_EN = true;
            cfg.B.TIM_MODE = (u32)Mode::pwmMeasurement;
            cfg.B.OSM = false;
            cfg.B.CICTRL = (u32)InpCtrl::useThis;
            cfg.B.TBU0x_SEL = 0;
            u32 inp = (u32)GprxInp::cnt;
            u32 e_inp = inp >> (u32)GprxInp::__e_sh__;
            cfg.B.EGPR0_SEL = e_inp;
            cfg.B.GPR0_SEL = inp;
            cfg.B.EGPR1_SEL = e_inp;
            cfg.B.GPR1_SEL = inp;
            cfg.B.CNTS_SEL = (u32)CntsInp::cnt;
            cfg.B.DSL = 1;
            cfg.B.ISL = 0;
            cfg.B.ECNT_RESET = 0;
            cfg.B.FLT_EN = true;
            cfg.B.FLT_CNT_FRQ = (u32)sysConf.filtClk;
            cfg.B.EXT_CAP_EN = false;
            cfg.B.FLT_MODE_RE = true;
            cfg.B.FLT_CTR_RE = (u32)FiltCountMode::upDown;
            cfg.B.FLT_MODE_FE = true;
            cfg.B.FLT_CTR_FE = (u32)FiltCountMode::upDown;
            cfg.B.CLK_SEL = (u32)sysConf.clk;
            cfg.B.FR_ECNT_OFL = (u32)EdgeCntOverflowBits::full;
            cfg.B.TOCTRL = (u32)TimeoutCtrl::bothEdges;

            p_hw->CTRL.U = cfg.U;
        }
        //.....................................................................
        {
            Ifx_GTM_TIM_CH_TDUV cfg;
            cfg.U = 0;
            u32 to;
            u32 f = _conf.pwmFreqRange[0];
            if (f)
            {
                to = _conf.timeoutRatio * sysConf.toClk_Hz / f;
                if (to > U8_MAX) to = U8_MAX;
            }
            else
            {
                to = U8_MAX;
            }
            cfg.B.TOV = to;
            cfg.B.TCS = (u32)sysConf.toClk;
            p_hw->TDUV.U = cfg.U;
        }
        //.....................................................................
        {
            u32 dt = u32(_conf.edgeFiltTime * sysConf.filtClk_Hz);
            p_hw->FLT_RE.U = p_hw->FLT_FE.U = dt;
        }
        //.....................................................................
        {
            Ifx_GTM_TIM_CH_IRQ_MODE cfg;
            cfg.U = 0;
            cfg.B.IRQ_MODE = IfxGtm_IrqMode_pulseNotify;
            p_hw->IRQ_MODE.U = cfg.U;
        }
        //.....................................................................
        {
            Ifx_GTM_TIM_CH_IRQ_EN cfg;
            cfg.U = 0;
            cfg.B.NEWVAL_IRQ_EN = true;
            cfg.B.TODET_IRQ_EN = true;
            p_hw->IRQ_EN.U = cfg.U;
        }
        //.....................................................................
        {
            volatile Ifx_SRC_SRCR *irqSrc =
                &MODULE_SRC.GTM.GTM[0].TIM[map->tim][map->channel];
            IfxSrc_init(irqSrc, IfxSrc_Tos_cpu0, sysConf.isrPrio);
            IfxSrc_enable(irqSrc);
        }
        //.....................................................................
        IfxGtm_PinMap_setTimTin(map, IfxPort_InputMode_noPullDevice);
        //.....................................................................
        return true;
    }
    //-------------------------------------------------------------------------
    void resetOutput()
    {
        _duty = _conf.pwmDutyOffset;
        _output[0] = _output[1] = 0;
    }
};
//#############################################################################

#endif  // AURIX_GTM_TIM_PWM_SENSOR_H
