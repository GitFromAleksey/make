#if !defined(TLF35584_H)
#   define TLF35584_H

#   include "IfxTlf35584.h"
#   include "IfxTlf35584_Driver.h"
#   include "IfxQspi_SpiMaster.h"

#   include "tlf35584_cfg.h"

//#############################################################################

#if    !defined(ISR_PRIO_TX) \
    || !defined(ISR_PRIO_RX) \
    || !defined(ISR_PRIO_ERR) \
    || !defined(ISR_PRIO_GROUP_TX) \
    || !defined(ISR_PRIO_GROUP_RX) \
    || !defined(ISR_PRIO_GROUP_ERR)
#   error "TLF35584: Specify ISR priorities!"
#endif

//#############################################################################

class Tlf35584
{
public:
    void init()
    {
        initSpi();
        initSpiChannel();
        initDriver();
    }
    //-------------------------------------------------------------------------
    bool goToNormal()
    {
        return  IfxTlf35584_Driver_goToNormal
                (
                    &tlf35584_driver, true, true, true, true, TimeConst_1s
                );
    }
    //-------------------------------------------------------------------------
    void goSleep()
    {
        Ifx_TLF35584_DEVCTRL devctrl;

        IfxTlf35584_Driver_disableCache(&tlf35584_driver);
        IfxTlf35584_Driver_setStateRequest
        (
            &tlf35584_driver,
            IfxTlf35584_State_standby,
            false, false, false, false,
            &devctrl
        );
        IfxTlf35584_Driver_setStateRequestN(&tlf35584_driver, devctrl);
    }
    //-------------------------------------------------------------------------
    void reset(u8 sleepTicks = 1)
    {
        IfxTlf35584_Driver_writeRegister
        (
            &tlf35584_driver,
            u32(&MODULE_TLF35584.DEVCFG0),
            (1 << 7)
        );
        IfxTlf35584_Driver_writeRegister
        (
            &tlf35584_driver,
            u32(&MODULE_TLF35584.WKTIMCFG0),
            sleepTicks
        );
        goSleep();
    }
    //-------------------------------------------------------------------------
    bool readWakeupStatus(u8 *data)
    {
        return IfxTlf35584_Driver_readRegister(
            &tlf35584_driver,
            u32(&MODULE_TLF35584.WKSF),
            data);
    }
    //-------------------------------------------------------------------------
    IfxQspi_SpiMaster *spi() {return &_spi;}
    //-------------------------------------------------------------------------
private:
    IfxQspi_SpiMaster _spi;
    IfxQspi_SpiMaster_Channel spiChannel;
    IfxTlf35584_Driver tlf35584_driver;
    //-------------------------------------------------------------------------
    void initSpi()
    {
        IfxQspi_SpiMaster_Config spiConfig;
        IfxQspi_SpiMaster_Pins spiPins;
#   if defined(CONF_PCB_10P0P2)
        spiPins.sclk = &IfxQspi0_SCLK_P20_11_OUT;
        spiPins.mtsr = &IfxQspi0_MTSR_P20_14_OUT;
        spiPins.mrst = &IfxQspi0_MRSTA_P20_12_IN;
#   else
        spiPins.sclk = &IfxQspi2_SCLK_P15_3_OUT;
        spiPins.mtsr = &IfxQspi2_MTSR_P15_5_OUT;
        spiPins.mrst = &IfxQspi2_MRSTE_P15_2_IN;
#   endif
        spiPins.sclkMode = IfxPort_OutputMode_pushPull;
        spiPins.mtsrMode = IfxPort_OutputMode_pushPull;
        spiPins.mrstMode = IfxPort_InputMode_noPullDevice;
        spiPins.pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;

        IfxQspi_SpiMaster_initModuleConfig
        (
            &spiConfig,
#   if defined(CONF_PCB_10P0P2)
            &MODULE_QSPI0
#   else
            &MODULE_QSPI2
#   endif
        );
        spiConfig.base.rxPriority = ISR_PRIO_SUPPLY_QSPI_RX;
        spiConfig.base.txPriority = ISR_PRIO_SUPPLY_QSPI_TX;
        spiConfig.base.erPriority = ISR_PRIO_SUPPLY_QSPI_ERR;
        spiConfig.base.bufferSize = 0;
        spiConfig.base.buffer = NULL_PTR;
        spiConfig.base.maximumBaudrate = 50.0e6;
        spiConfig.pins = &spiPins;
        IfxQspi_SpiMaster_initModule(&_spi, &spiConfig);
    }
    //-------------------------------------------------------------------------
    void initSpiChannel()
    {
        IfxQspi_SpiMaster_ChannelConfig conf;
        IfxQspi_SpiMaster_initChannelConfig(&conf, &_spi);

        conf.base.baudrate = 1e6;  //10e6;
        SpiIf_ChMode &m = conf.base.mode;
        m.enabled = true;
        m.autoCS = 1;
        m.loopback = false;
        m.clockPolarity = SpiIf_ClockPolarity_idleLow;
        m.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;
        m.dataHeading = SpiIf_DataHeading_msbFirst;
        m.dataWidth = 16;
        m.csActiveLevel = Ifx_ActiveState_low;
        m.csLeadDelay = SpiIf_SlsoTiming_2;
        m.csTrailDelay = SpiIf_SlsoTiming_1;
        m.csInactiveDelay = SpiIf_SlsoTiming_7;
        m.parityCheck = false;  // FIXME use HW parity
        m.parityMode = Ifx_ParityMode_even;
        conf.base.errorChecks.baudrate = false;
        conf.base.errorChecks.phase = false;
        conf.base.errorChecks.receive = false;
        conf.base.errorChecks.transmit = false;

#   if defined(CONF_PCB_10P0P2)
        conf.sls.output.pin = &IfxQspi0_SLSO2_P20_13_OUT;
#   else
        conf.sls.output.pin = &IfxQspi2_SLSO5_P15_1_OUT;
#   endif
        conf.sls.output.mode = IfxPort_OutputMode_pushPull;
        conf.sls.output.driver = IfxPort_PadDriver_cmosAutomotiveSpeed1;

        IfxQspi_SpiMaster_initChannel(&spiChannel, &conf);
    }
    //-------------------------------------------------------------------------
    bool initDriver()
    {
        bool result = true;

        IfxTlf35584_Config conf;
        IfxTlf35584_Driver_initConfig(&conf);
        conf.channel = &spiChannel.base;

        { // TLF35584 interrupt on ESR1
            uint16 endinit_pw;
            // Set ESR1 as input, page 502
            // input no pull up/down FIXME check/request iLLD API
            MODULE_SCU.IOCR.B.PC0 = 0;
            // ESR1 generates an NMI thought the SCU (Trap).
            // See UM TC27x C "7.2.4 NMI Trap Generation"
            // The trap is generated to all CPUs but handled by CPU1.

            // Clear the trap status flag before enabling to avoid
            // unintended traps.
            MODULE_SCU.TRAPCLR.B.ESR1T = 1;

            endinit_pw = IfxScuWdt_getCpuWatchdogPassword();
            IfxScuWdt_clearCpuEndinit(endinit_pw);
            // Enable Trap for ESR1
            MODULE_SCU.TRAPDIS.B.ESR1T = 0;
            IfxScuWdt_setCpuEndinit(endinit_pw);
        }

#   if defined(CONF_PCB_10P0P2)
        conf.wdi = (IfxPort_Pin){&MODULE_P20, 10};
#   else
        conf.wdi = (IfxPort_Pin){&MODULE_P21, 2};
#   endif
        // FIXME make this configurable?
        // conf.watchdogCycleTime = IfxTlf35584_WatchdogCycleTime_100us;
        conf.watchdogCycleTime = IfxTlf35584_WatchdogCycleTime_1ms;
        conf.windowWatchdog.enabled = false;
        conf.windowWatchdog.useWdiPin = true;
        conf.windowWatchdog.openWindowTime = 1;
        conf.windowWatchdog.closeWindowTime = 1;
        conf.functionalWatchdog.enabled = false;
        conf.functionalWatchdog.heartbeatTimerPeriod = 1;
        conf.functionalWatchdog.servicePeriod = 1;
        conf.errEnabled = false;
        result = IfxTlf35584_Driver_init(&tlf35584_driver, &conf) && result;

        // FIXME add support for SSx
        // Go to normal mode before timeout
        // TLF35584 INIT timer timeout tINIT=550ms min
        // To stop the INIT timer, 3 conditions are required:
        // - Valid SPI communication received from µC
        // - Watchdog(s) serviced once according to default configuration or
        //   according to reconfiguration
        // - ERR monitoring serviced properly (minimum 3 periods provided) or
        //   configured to be OFF

        // Data sheet says wait min 60us for the configuration change
        // to take effect.
        // FIXME required? FIXME Feedback: why such long delay?
        wait(TimeConst_10us * 6);

        result = goToNormal() && result;

        return result;
    }
};

//#############################################################################

extern Tlf35584 tlf35584;

//#############################################################################

#endif  // TLF35584_H
