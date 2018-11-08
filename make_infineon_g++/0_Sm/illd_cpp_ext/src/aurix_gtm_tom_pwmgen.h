#if !defined(AURIX_GTM_TOM_PWMGEN_H_)
#   define AURIX_GTM_TOM_PWMGEN_H_

#   include "aurix.h"
#   include "IfxGtm_Tom_Pwm.h"
#   include "IfxGtm_Trig.h"

//#############################################################################
//
//            /|
//          /  |
//        /    |
//      /      |
//    /        |
// |/          |/
//  ___     ___
//     |___|
//    cm1 cm0
//#############################################################################

class PwmGenerator
{
public:
    struct SysConf
    {
        IfxGtm_Tom_Ch_ClkSrc chClk;
        Aurix::Gtm::Dtm::Ctrl::Clk dtmClk;
        u32 clk_Hz;
        u32 pwmFreq_Hz;
        f32 deadTime_s;
        Aurix::Gtm::Dtm::ChCtrl2::Polarity pol[2];
        IfxGtm_Tom_ToutMap *pin[3][2];
        IfxGtm_Tom_Ch periodCh;
        Ifx_Priority periodIsrPrio;
    };
    //-------------------------------------------------------------------------
    bool init(const SysConf &sysConf)
    {
        bool res = true;

        Ifx_GTM *gtm = &MODULE_GTM;
        // todo check all pin for the same TOM
        IfxGtm_Tom tomN = sysConf.pin[0][0]->tom;
        Ifx_GTM_TOM *tom = &gtm->TOM[tomN];
        dtm = tomN == IfxGtm_Tom_0 ? &gtm->DTM1 : &gtm->DTM5;
        //.....................................................................
        // TOM period channel
        _tgc = IfxGtm_Tom_Ch_getTgcPointer(tom, sysConf.periodCh <= 7 ? 0 : 1);
        perCh = initPwmCh
                (
                    tom,
                    sysConf.periodCh,
                    sysConf.chClk,
                    IfxGtm_Tom_Ch_OutputTrigger_generate
                );
        setPeriod(sysConf.clk_Hz / sysConf.pwmFreq_Hz);
        setPeriodTrigger(1);
        //.....................................................................
        { // Interrupts
            Ifx_GTM_TOM_CH_IRQ_EN en;
            en.U = perCh->IRQ_EN.U;
            // Disable all to change mode
            perCh->IRQ_EN.U = 0;
            perCh->IRQ_MODE.B.IRQ_MODE = IfxGtm_IrqMode_pulseNotify;
            perCh->IRQ_EN.U = en.U;
            en.B.CCU0TC_IRQ_EN = false;
            en.B.CCU1TC_IRQ_EN = true;
            perCh->IRQ_EN.U = en.U;

            volatile Ifx_SRC_SRCR *src =
                IfxGtm_Tom_Ch_getSrcPointer(gtm, tomN, sysConf.periodCh);
            IfxSrc_init(src, IfxSrc_Tos_cpu0, sysConf.periodIsrPrio);
            IfxSrc_enable(src);

        }
        //.....................................................................
        { // DTM
            using namespace Aurix::Gtm::Dtm;
            {
                Ifx_GTM_DTM_CTRL v;
                v.U = 0;
                v.B.CLK_SEL = (u32)sysConf.dtmClk;
                v.B.UPD_MODE = (u32)Ctrl::UpdateMode::async;
                dtm->CTRL.U = v.U;
            }
            {
                Ifx_GTM_DTM_CH_CTRL1 v;
                v.U = 0;
                dtm->CH_CTRL1.U = v.U;
            }
            {
                Ifx_GTM_DTM_CH_CTRL2 v;
                v.U = 0;
                v.B.POL0_0 = v.B.POL0_1 = v.B.POL0_2 = (u32)sysConf.pol[0];
                v.B.POL1_0 = v.B.POL1_1 = v.B.POL1_2 = (u32)sysConf.pol[1];
                v.B.DT0_0 = v.B.DT0_1 = v.B.DT0_2 = true;
                v.B.DT1_0 = v.B.DT1_1 = v.B.DT1_2 = true;
                dtm->CH_CTRL2.U = v.U;
            }
            setDeadTime(sysConf.deadTime_s * sysConf.clk_Hz);
        }
        //.....................................................................
        // PWM channels
        for (u32 i = 0; i < 3; i++)
        {
            pwmChN[i] = sysConf.pin[i][0]->channel;
            pwmCh[i] =  initPwmCh
                        (
                            tom,
                            pwmChN[i],
                            sysConf.chClk,
                            IfxGtm_Tom_Ch_OutputTrigger_forward
                        );
            for (u32 j = 0; j < 2; j++)
            {
                IfxGtm_PinMap_setTomTout
                (
                    sysConf.pin[i][j],
                    IfxPort_OutputMode_pushPull,
                    IfxPort_PadDriver_cmosAutomotiveSpeed1
                );
            }
        }
        _outputsEnabled = true;

        return res;
    }
    //-------------------------------------------------------------------------
    u32 period() const {return _period;}
    void setPeriod(u32 p) {perCh->SR0.U = _period = p;}
    void setPeriodTrigger(u32 v) {perCh->SR1.U = v;}
    //-------------------------------------------------------------------------
    Ifx_GTM_TOM_TGC *tgc() const {return _tgc;}
    //-------------------------------------------------------------------------
    void setDeadTime(u16 rise, u16 fall)
    {
        for (u32 i = 0; i < 3; i++)
        {
            Ifx_GTM_DTM_DTV_CH v;
            v.U = 0;
            v.B.RELRISE = rise;
            v.B.RELFALL = fall;
            dtm->DTV_CH[i].U = v.U;
        }
    }
    //-------------------------------------------------------------------------
    void setDeadTime(u16 dt) {setDeadTime(dt, dt);}
    //-------------------------------------------------------------------------
    // UM[24.6.3.3]:
    //  - CM0 defines the edge to SL value, CM1 defines the edge to !SL;
    //  - if CM0 = CM1, the output is 100% SL (CM0 has higher priority);
    //  - if CM0 = 0 and CM1 = MAX, the output is 100% SL (while CN0 counts
    //    from 0 to MAX - 1 and is then reset by trigger).
    template <typename T>
    void setDuty(T *v)
    {
        for (u32 i = 0; i < 3; i++)
        {
            u32 cm0;
            u32 cm1;
            if (v[i] == 0)
            { // out = !SL
                cm0 = -1;
                cm1 = 0;
            }
            else if (v[i] >= _period)
            { // out = SL
                cm0 = 0;
                cm1 = -1;
            }
            else
            {
                cm1 = v[i] / 2;
                cm0 = _period - (v[i] - cm1);
            }
            setPwm(i, cm0, cm1);
        }
    }
    //-------------------------------------------------------------------------
    void setDuty(u32 v1, u32 v2, u32 v3) {u32 v[] = {v1, v2, v3}; setDuty(v);}
    //-------------------------------------------------------------------------
    template <typename T>
    void setDuty(T *c1, T *c2)
    {
        for (u32 i = 0; i < 3; i++)
        {
            u32 cm0;
            u32 cm1;
            u32 v = c1[i] + c2[i];
            if (v == 0)
            { // out = !SL
                cm0 = -1;
                cm1 = 0;
            }
            else if (v >= _period)
            { // out = SL
                cm0 = 0;
                cm1 = -1;
            }
            else
            {
                cm1 = c1[i];
                cm0 = _period - 1 - c2[i];
                // без -1: при cm0 == _period на выходе уровень SL
            }
            setPwm(i, cm0, cm1);
        }
    }
    //-------------------------------------------------------------------------
    // todo !!! ѕроверить выходные уровни при отключении (двигатель клинит).
    void enableOutputs(bool cmd = true)
    {
        for (u32 i = 0; i < 3; i++)
        {
            IfxGtm_Tom_Tgc_enableChannelOutput(_tgc, pwmChN[i], cmd, false);
        }
        _outputsEnabled = cmd;
    }
    //-------------------------------------------------------------------------
    bool isOutputsEnabled() const {return _outputsEnabled;}
    //-------------------------------------------------------------------------
DEBUG_PUBLIC(private):
    Ifx_GTM_TOM_TGC *_tgc;
    Ifx_GTM_DTM *dtm;
    Ifx_GTM_TOM_CH *perCh;
    Ifx_GTM_TOM_CH *pwmCh[3];
    IfxGtm_Tom_Ch pwmChN[3];
    bool _outputsEnabled;
    u32 _period;
    u32 cmp[3][2];
    //-------------------------------------------------------------------------
    Ifx_GTM_TOM_CH *initPwmCh
    (
        Ifx_GTM_TOM *tom,
        IfxGtm_Tom_Ch ch,
        IfxGtm_Tom_Ch_ClkSrc clk,
        IfxGtm_Tom_Ch_OutputTrigger outTrg
    )
    {
        Ifx_GTM_TOM_CH *p = IfxGtm_Tom_Ch_getChannelPointer(tom, ch);
        Ifx_GTM_TOM_CH_CTRL ctrl;
        ctrl.U = p->CTRL.U;
        ctrl.B.CLK_SRC_SR = clk;
        ctrl.B.SL = 1;
        ctrl.B.TRIGOUT = outTrg;
        if (outTrg == IfxGtm_Tom_Ch_OutputTrigger_forward)
        {
            ctrl.B.RST_CCU0 = IfxGtm_Tom_Ch_ResetEvent_onTrigger;
        }
        p->CTRL.U = ctrl.U;
        p->SR0.U = -1;
        p->SR1.U = 0;
        IfxGtm_Tom_Tgc_enableChannelUpdate(_tgc, ch, true);
        IfxGtm_Tom_Tgc_setChannelForceUpdate(_tgc, ch, true, true);
        IfxGtm_Tom_Tgc_enableChannel(_tgc, ch, true, false);
        IfxGtm_Tom_Tgc_enableChannelOutput(_tgc, ch, true, false);
        return p;
    }
    //-------------------------------------------------------------------------
    void setPwm(u32 i, u32 cm0, u32 cm1)
    {
        pwmCh[i]->SR0.U = cmp[i][1] = cm0;
        pwmCh[i]->SR1.U = cmp[i][0] = cm1;
    }
};
//#############################################################################

#endif  // AURIX_GTM_TOM_PWMGEN_H_
