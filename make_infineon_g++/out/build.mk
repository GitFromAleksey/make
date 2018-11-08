.PHONY: all clean 

all: ../out/int2str.o ../out/aurix.o ../out/IfxAsclin_Asc.o ../out/IfxAsclin_Lin.o ../out/IfxAsclin_Spi.o ../out/IfxAsclin.o ../out/IfxCcu6_Icu.o ../out/IfxCcu6_PwmBc.o ../out/IfxCcu6_PwmHl.o ../out/IfxCcu6.o ../out/IfxCcu6_Timer.o ../out/IfxCcu6_TimerWithTrigger.o ../out/IfxCcu6_TPwm.o ../out/IfxCpu_CStart0.o ../out/IfxCpu_Irq.o ../out/IfxCpu.o ../out/IfxCpu_Trap.o ../out/IfxDma_Dma.o ../out/IfxDma.o ../out/IfxDts_Dts.o ../out/IfxDts.o ../out/IfxEray_Eray.o ../out/IfxEray.o ../out/IfxEth_Phy_Pef7071.o ../out/IfxEth.o ../out/IfxFlash.o ../out/IfxGpt12_IncrEnc.o ../out/IfxGpt12.o ../out/IfxGtm.o ../out/IfxGtm_Cmu.o ../out/IfxGtm_Dpll.o ../out/IfxGtm_Tbu.o ../out/IfxGtm_Tim.o ../out/IfxGtm_Tom.o ../out/IfxGtm_Tim_In.o ../out/IfxGtm_Tom_Pwm.o ../out/IfxGtm_Tom_PwmHl.o ../out/IfxGtm_Tom_Timer.o ../out/IfxGtm_Trig.o ../out/IfxMtu.o ../out/IfxMultican_Can.o ../out/IfxMultican.o ../out/IfxPort_Io.o ../out/IfxPort.o ../out/IfxQspi_SpiMaster.o ../out/IfxQspi_SpiSlave.o ../out/IfxQspi.o ../out/IfxScuCcu.o ../out/IfxScuEru.o ../out/IfxScuWdt.o ../out/IfxSent_Sent.o ../out/IfxSent.o ../out/IfxSmu.o ../out/IfxSrc.o ../out/IfxStm.o ../out/IfxStm_Timer.o ../out/IfxVadc_Adc.o ../out/IfxVadc.o ../out/IfxAsclin_cfg.o ../out/IfxCcu6_cfg.o ../out/IfxCpu_cfg.o ../out/IfxDma_cfg.o ../out/IfxEray_cfg.o ../out/IfxFlash_cfg.o ../out/IfxGtm_cfg.o ../out/IfxMtu_cfg.o ../out/IfxMultican_cfg.o ../out/IfxPort_cfg.o ../out/IfxQspi_cfg.o ../out/IfxScu_cfg.o ../out/IfxSent_cfg.o ../out/IfxSmu_cfg.o ../out/IfxSrc_cfg.o ../out/IfxStm_cfg.o ../out/IfxVadc_cfg.o ../out/Ifx_CircularBuffer.asm.o ../out/Ifx_CircularBuffer.o ../out/Ifx_Fifo.o ../out/Ifx_InternalMux.o ../out/IfxAsclin_PinMap.o ../out/IfxCcu6_PinMap.o ../out/IfxEray_PinMap.o ../out/IfxEth_PinMap.o ../out/IfxGpt12_PinMap.o ../out/IfxGtm_PinMap.o ../out/IfxMultican_PinMap.o ../out/IfxPort_PinMap.o ../out/IfxQspi_PinMap.o ../out/IfxScu_PinMap.o ../out/IfxSent_PinMap.o ../out/IfxSmu_PinMap.o ../out/IfxVadc_PinMap.o ../out/CompilerDcc.o ../out/CompilerGnuc.o ../out/CompilerTasking.o ../out/SpiIf.o ../out/IfxStdIf_DPipe.o ../out/IfxStdIf_Pos.o ../out/IfxStdIf_PwmHl.o ../out/IfxStdIf_Timer.o ../out/Assert.o ../out/Bsp.o ../out/Ifx_Console.o ../out/Ifx_Shell.o ../out/Ifx_GlobalResources.o ../out/Ifx_AngleTrkF32.o ../out/Ifx_Cf32.o ../out/Ifx_Crc.o ../out/Ifx_FftF32.o ../out/Ifx_FftF32_BitReverseTable.o ../out/Ifx_FftF32_TwiddleTable.o ../out/Ifx_IntegralF32.o ../out/Ifx_LowPassPt1F32.o ../out/Ifx_LutAtan2F32.o ../out/Ifx_LutAtan2F32_Table.o ../out/Ifx_LutLinearF32.o ../out/Ifx_LutLSincosF32.o ../out/Ifx_LutSincosF32.o ../out/Ifx_LutSincosF32_Table.o ../out/Ifx_RampF32.o ../out/Ifx_WndF32_BlackmanHarrisTable.o ../out/Ifx_WndF32_HannTable.o ../out/Ifx_DateTime.o ../out/IfxTlf35584_Driver.o ../out/IfxTlf35584_Hal.o ../out/IfxTlf35584_If.o ../out/IfxTlf35584.o ../out/IfxTlf35584_cfg.o ../out/IfxTlf35584_regdef.o ../out/tlf35584.o ../out/factorial.o ../out/hello.o ../out/main.o
	tricore-g++ -mcpu=tc23xx -Wl,-Map,../out/artifacts/HelloTSim.map -Wl,--extmap="a" -Wl,--gc-sections -o ../out/artifacts/HelloTSim.elf ../out/int2str.o ../out/aurix.o ../out/IfxAsclin_Asc.o ../out/IfxAsclin_Lin.o ../out/IfxAsclin_Spi.o ../out/IfxAsclin.o ../out/IfxCcu6_Icu.o ../out/IfxCcu6_PwmBc.o ../out/IfxCcu6_PwmHl.o ../out/IfxCcu6.o ../out/IfxCcu6_Timer.o ../out/IfxCcu6_TimerWithTrigger.o ../out/IfxCcu6_TPwm.o ../out/IfxCpu_CStart0.o ../out/IfxCpu_Irq.o ../out/IfxCpu.o ../out/IfxCpu_Trap.o ../out/IfxDma_Dma.o ../out/IfxDma.o ../out/IfxDts_Dts.o ../out/IfxDts.o ../out/IfxEray_Eray.o ../out/IfxEray.o ../out/IfxEth_Phy_Pef7071.o ../out/IfxEth.o ../out/IfxFlash.o ../out/IfxGpt12_IncrEnc.o ../out/IfxGpt12.o ../out/IfxGtm.o ../out/IfxGtm_Cmu.o ../out/IfxGtm_Dpll.o ../out/IfxGtm_Tbu.o ../out/IfxGtm_Tim.o ../out/IfxGtm_Tom.o ../out/IfxGtm_Tim_In.o ../out/IfxGtm_Tom_Pwm.o ../out/IfxGtm_Tom_PwmHl.o ../out/IfxGtm_Tom_Timer.o ../out/IfxGtm_Trig.o ../out/IfxMtu.o ../out/IfxMultican_Can.o ../out/IfxMultican.o ../out/IfxPort_Io.o ../out/IfxPort.o ../out/IfxQspi_SpiMaster.o ../out/IfxQspi_SpiSlave.o ../out/IfxQspi.o ../out/IfxScuCcu.o ../out/IfxScuEru.o ../out/IfxScuWdt.o ../out/IfxSent_Sent.o ../out/IfxSent.o ../out/IfxSmu.o ../out/IfxSrc.o ../out/IfxStm.o ../out/IfxStm_Timer.o ../out/IfxVadc_Adc.o ../out/IfxVadc.o ../out/IfxAsclin_cfg.o ../out/IfxCcu6_cfg.o ../out/IfxCpu_cfg.o ../out/IfxDma_cfg.o ../out/IfxEray_cfg.o ../out/IfxFlash_cfg.o ../out/IfxGtm_cfg.o ../out/IfxMtu_cfg.o ../out/IfxMultican_cfg.o ../out/IfxPort_cfg.o ../out/IfxQspi_cfg.o ../out/IfxScu_cfg.o ../out/IfxSent_cfg.o ../out/IfxSmu_cfg.o ../out/IfxSrc_cfg.o ../out/IfxStm_cfg.o ../out/IfxVadc_cfg.o ../out/Ifx_CircularBuffer.asm.o ../out/Ifx_CircularBuffer.o ../out/Ifx_Fifo.o ../out/Ifx_InternalMux.o ../out/IfxAsclin_PinMap.o ../out/IfxCcu6_PinMap.o ../out/IfxEray_PinMap.o ../out/IfxEth_PinMap.o ../out/IfxGpt12_PinMap.o ../out/IfxGtm_PinMap.o ../out/IfxMultican_PinMap.o ../out/IfxPort_PinMap.o ../out/IfxQspi_PinMap.o ../out/IfxScu_PinMap.o ../out/IfxSent_PinMap.o ../out/IfxSmu_PinMap.o ../out/IfxVadc_PinMap.o ../out/CompilerDcc.o ../out/CompilerGnuc.o ../out/CompilerTasking.o ../out/SpiIf.o ../out/IfxStdIf_DPipe.o ../out/IfxStdIf_Pos.o ../out/IfxStdIf_PwmHl.o ../out/IfxStdIf_Timer.o ../out/Assert.o ../out/Bsp.o ../out/Ifx_Console.o ../out/Ifx_Shell.o ../out/Ifx_GlobalResources.o ../out/Ifx_AngleTrkF32.o ../out/Ifx_Cf32.o ../out/Ifx_Crc.o ../out/Ifx_FftF32.o ../out/Ifx_FftF32_BitReverseTable.o ../out/Ifx_FftF32_TwiddleTable.o ../out/Ifx_IntegralF32.o ../out/Ifx_LowPassPt1F32.o ../out/Ifx_LutAtan2F32.o ../out/Ifx_LutAtan2F32_Table.o ../out/Ifx_LutLinearF32.o ../out/Ifx_LutLSincosF32.o ../out/Ifx_LutSincosF32.o ../out/Ifx_LutSincosF32_Table.o ../out/Ifx_RampF32.o ../out/Ifx_WndF32_BlackmanHarrisTable.o ../out/Ifx_WndF32_HannTable.o ../out/Ifx_DateTime.o ../out/IfxTlf35584_Driver.o ../out/IfxTlf35584_Hal.o ../out/IfxTlf35584_If.o ../out/IfxTlf35584.o ../out/IfxTlf35584_cfg.o ../out/IfxTlf35584_regdef.o ../out/tlf35584.o ../out/factorial.o ../out/hello.o ../out/main.o

../out/Assert.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Bsp/Assert.c ../out/Assert.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Assert.o -MMD -MP -MF ../out/Assert.Td @../out/inc.opt -c -o ../out/Assert.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Bsp/Assert.c
	@mv -f ../out/Assert.Td ../out/Assert.d && touch ../out/Assert.o

../out/Bsp.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Bsp/Bsp.c ../out/Bsp.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Bsp.o -MMD -MP -MF ../out/Bsp.Td @../out/inc.opt -c -o ../out/Bsp.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Bsp/Bsp.c
	@mv -f ../out/Bsp.Td ../out/Bsp.d && touch ../out/Bsp.o

../out/CompilerDcc.o: ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerDcc.c ../out/CompilerDcc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/CompilerDcc.o -MMD -MP -MF ../out/CompilerDcc.Td @../out/inc.opt -c -o ../out/CompilerDcc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerDcc.c
	@mv -f ../out/CompilerDcc.Td ../out/CompilerDcc.d && touch ../out/CompilerDcc.o

../out/CompilerGnuc.o: ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGnuc.c ../out/CompilerGnuc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/CompilerGnuc.o -MMD -MP -MF ../out/CompilerGnuc.Td @../out/inc.opt -c -o ../out/CompilerGnuc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGnuc.c
	@mv -f ../out/CompilerGnuc.Td ../out/CompilerGnuc.d && touch ../out/CompilerGnuc.o

../out/CompilerTasking.o: ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerTasking.c ../out/CompilerTasking.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/CompilerTasking.o -MMD -MP -MF ../out/CompilerTasking.Td @../out/inc.opt -c -o ../out/CompilerTasking.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerTasking.c
	@mv -f ../out/CompilerTasking.Td ../out/CompilerTasking.d && touch ../out/CompilerTasking.o

../out/IfxAsclin.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Std/IfxAsclin.c ../out/IfxAsclin.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin.o -MMD -MP -MF ../out/IfxAsclin.Td @../out/inc.opt -c -o ../out/IfxAsclin.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Std/IfxAsclin.c
	@mv -f ../out/IfxAsclin.Td ../out/IfxAsclin.d && touch ../out/IfxAsclin.o

../out/IfxAsclin_Asc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Asc/IfxAsclin_Asc.c ../out/IfxAsclin_Asc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin_Asc.o -MMD -MP -MF ../out/IfxAsclin_Asc.Td @../out/inc.opt -c -o ../out/IfxAsclin_Asc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Asc/IfxAsclin_Asc.c
	@mv -f ../out/IfxAsclin_Asc.Td ../out/IfxAsclin_Asc.d && touch ../out/IfxAsclin_Asc.o

../out/IfxAsclin_Lin.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Lin/IfxAsclin_Lin.c ../out/IfxAsclin_Lin.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin_Lin.o -MMD -MP -MF ../out/IfxAsclin_Lin.Td @../out/inc.opt -c -o ../out/IfxAsclin_Lin.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Lin/IfxAsclin_Lin.c
	@mv -f ../out/IfxAsclin_Lin.Td ../out/IfxAsclin_Lin.d && touch ../out/IfxAsclin_Lin.o

../out/IfxAsclin_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxAsclin_PinMap.c ../out/IfxAsclin_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin_PinMap.o -MMD -MP -MF ../out/IfxAsclin_PinMap.Td @../out/inc.opt -c -o ../out/IfxAsclin_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxAsclin_PinMap.c
	@mv -f ../out/IfxAsclin_PinMap.Td ../out/IfxAsclin_PinMap.d && touch ../out/IfxAsclin_PinMap.o

../out/IfxAsclin_Spi.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Spi/IfxAsclin_Spi.c ../out/IfxAsclin_Spi.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin_Spi.o -MMD -MP -MF ../out/IfxAsclin_Spi.Td @../out/inc.opt -c -o ../out/IfxAsclin_Spi.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Asclin/Spi/IfxAsclin_Spi.c
	@mv -f ../out/IfxAsclin_Spi.Td ../out/IfxAsclin_Spi.d && touch ../out/IfxAsclin_Spi.o

../out/IfxAsclin_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxAsclin_cfg.c ../out/IfxAsclin_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxAsclin_cfg.o -MMD -MP -MF ../out/IfxAsclin_cfg.Td @../out/inc.opt -c -o ../out/IfxAsclin_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxAsclin_cfg.c
	@mv -f ../out/IfxAsclin_cfg.Td ../out/IfxAsclin_cfg.d && touch ../out/IfxAsclin_cfg.o

../out/IfxCcu6.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Std/IfxCcu6.c ../out/IfxCcu6.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6.o -MMD -MP -MF ../out/IfxCcu6.Td @../out/inc.opt -c -o ../out/IfxCcu6.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Std/IfxCcu6.c
	@mv -f ../out/IfxCcu6.Td ../out/IfxCcu6.d && touch ../out/IfxCcu6.o

../out/IfxCcu6_Icu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Icu/IfxCcu6_Icu.c ../out/IfxCcu6_Icu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_Icu.o -MMD -MP -MF ../out/IfxCcu6_Icu.Td @../out/inc.opt -c -o ../out/IfxCcu6_Icu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Icu/IfxCcu6_Icu.c
	@mv -f ../out/IfxCcu6_Icu.Td ../out/IfxCcu6_Icu.d && touch ../out/IfxCcu6_Icu.o

../out/IfxCcu6_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxCcu6_PinMap.c ../out/IfxCcu6_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_PinMap.o -MMD -MP -MF ../out/IfxCcu6_PinMap.Td @../out/inc.opt -c -o ../out/IfxCcu6_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxCcu6_PinMap.c
	@mv -f ../out/IfxCcu6_PinMap.Td ../out/IfxCcu6_PinMap.d && touch ../out/IfxCcu6_PinMap.o

../out/IfxCcu6_PwmBc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.c ../out/IfxCcu6_PwmBc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_PwmBc.o -MMD -MP -MF ../out/IfxCcu6_PwmBc.Td @../out/inc.opt -c -o ../out/IfxCcu6_PwmBc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.c
	@mv -f ../out/IfxCcu6_PwmBc.Td ../out/IfxCcu6_PwmBc.d && touch ../out/IfxCcu6_PwmBc.o

../out/IfxCcu6_PwmHl.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/PwmHl/IfxCcu6_PwmHl.c ../out/IfxCcu6_PwmHl.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_PwmHl.o -MMD -MP -MF ../out/IfxCcu6_PwmHl.Td @../out/inc.opt -c -o ../out/IfxCcu6_PwmHl.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/PwmHl/IfxCcu6_PwmHl.c
	@mv -f ../out/IfxCcu6_PwmHl.Td ../out/IfxCcu6_PwmHl.d && touch ../out/IfxCcu6_PwmHl.o

../out/IfxCcu6_TPwm.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/TPwm/IfxCcu6_TPwm.c ../out/IfxCcu6_TPwm.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_TPwm.o -MMD -MP -MF ../out/IfxCcu6_TPwm.Td @../out/inc.opt -c -o ../out/IfxCcu6_TPwm.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/TPwm/IfxCcu6_TPwm.c
	@mv -f ../out/IfxCcu6_TPwm.Td ../out/IfxCcu6_TPwm.d && touch ../out/IfxCcu6_TPwm.o

../out/IfxCcu6_Timer.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Timer/IfxCcu6_Timer.c ../out/IfxCcu6_Timer.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_Timer.o -MMD -MP -MF ../out/IfxCcu6_Timer.Td @../out/inc.opt -c -o ../out/IfxCcu6_Timer.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/Timer/IfxCcu6_Timer.c
	@mv -f ../out/IfxCcu6_Timer.Td ../out/IfxCcu6_Timer.d && touch ../out/IfxCcu6_Timer.o

../out/IfxCcu6_TimerWithTrigger.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/TimerWithTrigger/IfxCcu6_TimerWithTrigger.c ../out/IfxCcu6_TimerWithTrigger.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_TimerWithTrigger.o -MMD -MP -MF ../out/IfxCcu6_TimerWithTrigger.Td @../out/inc.opt -c -o ../out/IfxCcu6_TimerWithTrigger.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Ccu6/TimerWithTrigger/IfxCcu6_TimerWithTrigger.c
	@mv -f ../out/IfxCcu6_TimerWithTrigger.Td ../out/IfxCcu6_TimerWithTrigger.d && touch ../out/IfxCcu6_TimerWithTrigger.o

../out/IfxCcu6_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxCcu6_cfg.c ../out/IfxCcu6_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCcu6_cfg.o -MMD -MP -MF ../out/IfxCcu6_cfg.Td @../out/inc.opt -c -o ../out/IfxCcu6_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxCcu6_cfg.c
	@mv -f ../out/IfxCcu6_cfg.Td ../out/IfxCcu6_cfg.d && touch ../out/IfxCcu6_cfg.o

../out/IfxCpu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Std/IfxCpu.c ../out/IfxCpu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCpu.o -MMD -MP -MF ../out/IfxCpu.Td @../out/inc.opt -c -o ../out/IfxCpu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Std/IfxCpu.c
	@mv -f ../out/IfxCpu.Td ../out/IfxCpu.d && touch ../out/IfxCpu.o

../out/IfxCpu_CStart0.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/CStart/IfxCpu_CStart0.c ../out/IfxCpu_CStart0.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCpu_CStart0.o -MMD -MP -MF ../out/IfxCpu_CStart0.Td @../out/inc.opt -c -o ../out/IfxCpu_CStart0.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/CStart/IfxCpu_CStart0.c
	@mv -f ../out/IfxCpu_CStart0.Td ../out/IfxCpu_CStart0.d && touch ../out/IfxCpu_CStart0.o

../out/IfxCpu_Irq.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Irq/IfxCpu_Irq.c ../out/IfxCpu_Irq.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCpu_Irq.o -MMD -MP -MF ../out/IfxCpu_Irq.Td @../out/inc.opt -c -o ../out/IfxCpu_Irq.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Irq/IfxCpu_Irq.c
	@mv -f ../out/IfxCpu_Irq.Td ../out/IfxCpu_Irq.d && touch ../out/IfxCpu_Irq.o

../out/IfxCpu_Trap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Trap/IfxCpu_Trap.c ../out/IfxCpu_Trap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCpu_Trap.o -MMD -MP -MF ../out/IfxCpu_Trap.Td @../out/inc.opt -c -o ../out/IfxCpu_Trap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Trap/IfxCpu_Trap.c
	@mv -f ../out/IfxCpu_Trap.Td ../out/IfxCpu_Trap.d && touch ../out/IfxCpu_Trap.o

../out/IfxCpu_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxCpu_cfg.c ../out/IfxCpu_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxCpu_cfg.o -MMD -MP -MF ../out/IfxCpu_cfg.Td @../out/inc.opt -c -o ../out/IfxCpu_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxCpu_cfg.c
	@mv -f ../out/IfxCpu_cfg.Td ../out/IfxCpu_cfg.d && touch ../out/IfxCpu_cfg.o

../out/IfxDma.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dma/Std/IfxDma.c ../out/IfxDma.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxDma.o -MMD -MP -MF ../out/IfxDma.Td @../out/inc.opt -c -o ../out/IfxDma.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dma/Std/IfxDma.c
	@mv -f ../out/IfxDma.Td ../out/IfxDma.d && touch ../out/IfxDma.o

../out/IfxDma_Dma.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dma/Dma/IfxDma_Dma.c ../out/IfxDma_Dma.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxDma_Dma.o -MMD -MP -MF ../out/IfxDma_Dma.Td @../out/inc.opt -c -o ../out/IfxDma_Dma.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dma/Dma/IfxDma_Dma.c
	@mv -f ../out/IfxDma_Dma.Td ../out/IfxDma_Dma.d && touch ../out/IfxDma_Dma.o

../out/IfxDma_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxDma_cfg.c ../out/IfxDma_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxDma_cfg.o -MMD -MP -MF ../out/IfxDma_cfg.Td @../out/inc.opt -c -o ../out/IfxDma_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxDma_cfg.c
	@mv -f ../out/IfxDma_cfg.Td ../out/IfxDma_cfg.d && touch ../out/IfxDma_cfg.o

../out/IfxDts.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dts/Std/IfxDts.c ../out/IfxDts.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxDts.o -MMD -MP -MF ../out/IfxDts.Td @../out/inc.opt -c -o ../out/IfxDts.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dts/Std/IfxDts.c
	@mv -f ../out/IfxDts.Td ../out/IfxDts.d && touch ../out/IfxDts.o

../out/IfxDts_Dts.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dts/Dts/IfxDts_Dts.c ../out/IfxDts_Dts.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxDts_Dts.o -MMD -MP -MF ../out/IfxDts_Dts.Td @../out/inc.opt -c -o ../out/IfxDts_Dts.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Dts/Dts/IfxDts_Dts.c
	@mv -f ../out/IfxDts_Dts.Td ../out/IfxDts_Dts.d && touch ../out/IfxDts_Dts.o

../out/IfxEray.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eray/Std/IfxEray.c ../out/IfxEray.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEray.o -MMD -MP -MF ../out/IfxEray.Td @../out/inc.opt -c -o ../out/IfxEray.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eray/Std/IfxEray.c
	@mv -f ../out/IfxEray.Td ../out/IfxEray.d && touch ../out/IfxEray.o

../out/IfxEray_Eray.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eray/Eray/IfxEray_Eray.c ../out/IfxEray_Eray.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEray_Eray.o -MMD -MP -MF ../out/IfxEray_Eray.Td @../out/inc.opt -c -o ../out/IfxEray_Eray.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eray/Eray/IfxEray_Eray.c
	@mv -f ../out/IfxEray_Eray.Td ../out/IfxEray_Eray.d && touch ../out/IfxEray_Eray.o

../out/IfxEray_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxEray_PinMap.c ../out/IfxEray_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEray_PinMap.o -MMD -MP -MF ../out/IfxEray_PinMap.Td @../out/inc.opt -c -o ../out/IfxEray_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxEray_PinMap.c
	@mv -f ../out/IfxEray_PinMap.Td ../out/IfxEray_PinMap.d && touch ../out/IfxEray_PinMap.o

../out/IfxEray_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxEray_cfg.c ../out/IfxEray_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEray_cfg.o -MMD -MP -MF ../out/IfxEray_cfg.Td @../out/inc.opt -c -o ../out/IfxEray_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxEray_cfg.c
	@mv -f ../out/IfxEray_cfg.Td ../out/IfxEray_cfg.d && touch ../out/IfxEray_cfg.o

../out/IfxEth.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eth/Std/IfxEth.c ../out/IfxEth.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEth.o -MMD -MP -MF ../out/IfxEth.Td @../out/inc.opt -c -o ../out/IfxEth.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eth/Std/IfxEth.c
	@mv -f ../out/IfxEth.Td ../out/IfxEth.d && touch ../out/IfxEth.o

../out/IfxEth_Phy_Pef7071.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eth/Phy_Pef7071/IfxEth_Phy_Pef7071.c ../out/IfxEth_Phy_Pef7071.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEth_Phy_Pef7071.o -MMD -MP -MF ../out/IfxEth_Phy_Pef7071.Td @../out/inc.opt -c -o ../out/IfxEth_Phy_Pef7071.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Eth/Phy_Pef7071/IfxEth_Phy_Pef7071.c
	@mv -f ../out/IfxEth_Phy_Pef7071.Td ../out/IfxEth_Phy_Pef7071.d && touch ../out/IfxEth_Phy_Pef7071.o

../out/IfxEth_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxEth_PinMap.c ../out/IfxEth_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxEth_PinMap.o -MMD -MP -MF ../out/IfxEth_PinMap.Td @../out/inc.opt -c -o ../out/IfxEth_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxEth_PinMap.c
	@mv -f ../out/IfxEth_PinMap.Td ../out/IfxEth_PinMap.d && touch ../out/IfxEth_PinMap.o

../out/IfxFlash.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Flash/Std/IfxFlash.c ../out/IfxFlash.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxFlash.o -MMD -MP -MF ../out/IfxFlash.Td @../out/inc.opt -c -o ../out/IfxFlash.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Flash/Std/IfxFlash.c
	@mv -f ../out/IfxFlash.Td ../out/IfxFlash.d && touch ../out/IfxFlash.o

../out/IfxFlash_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxFlash_cfg.c ../out/IfxFlash_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxFlash_cfg.o -MMD -MP -MF ../out/IfxFlash_cfg.Td @../out/inc.opt -c -o ../out/IfxFlash_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxFlash_cfg.c
	@mv -f ../out/IfxFlash_cfg.Td ../out/IfxFlash_cfg.d && touch ../out/IfxFlash_cfg.o

../out/IfxGpt12.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gpt12/Std/IfxGpt12.c ../out/IfxGpt12.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGpt12.o -MMD -MP -MF ../out/IfxGpt12.Td @../out/inc.opt -c -o ../out/IfxGpt12.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gpt12/Std/IfxGpt12.c
	@mv -f ../out/IfxGpt12.Td ../out/IfxGpt12.d && touch ../out/IfxGpt12.o

../out/IfxGpt12_IncrEnc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gpt12/IncrEnc/IfxGpt12_IncrEnc.c ../out/IfxGpt12_IncrEnc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGpt12_IncrEnc.o -MMD -MP -MF ../out/IfxGpt12_IncrEnc.Td @../out/inc.opt -c -o ../out/IfxGpt12_IncrEnc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gpt12/IncrEnc/IfxGpt12_IncrEnc.c
	@mv -f ../out/IfxGpt12_IncrEnc.Td ../out/IfxGpt12_IncrEnc.d && touch ../out/IfxGpt12_IncrEnc.o

../out/IfxGpt12_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxGpt12_PinMap.c ../out/IfxGpt12_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGpt12_PinMap.o -MMD -MP -MF ../out/IfxGpt12_PinMap.Td @../out/inc.opt -c -o ../out/IfxGpt12_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxGpt12_PinMap.c
	@mv -f ../out/IfxGpt12_PinMap.Td ../out/IfxGpt12_PinMap.d && touch ../out/IfxGpt12_PinMap.o

../out/IfxGtm.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm.c ../out/IfxGtm.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm.o -MMD -MP -MF ../out/IfxGtm.Td @../out/inc.opt -c -o ../out/IfxGtm.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm.c
	@mv -f ../out/IfxGtm.Td ../out/IfxGtm.d && touch ../out/IfxGtm.o

../out/IfxGtm_Cmu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Cmu.c ../out/IfxGtm_Cmu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Cmu.o -MMD -MP -MF ../out/IfxGtm_Cmu.Td @../out/inc.opt -c -o ../out/IfxGtm_Cmu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Cmu.c
	@mv -f ../out/IfxGtm_Cmu.Td ../out/IfxGtm_Cmu.d && touch ../out/IfxGtm_Cmu.o

../out/IfxGtm_Dpll.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Dpll.c ../out/IfxGtm_Dpll.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Dpll.o -MMD -MP -MF ../out/IfxGtm_Dpll.Td @../out/inc.opt -c -o ../out/IfxGtm_Dpll.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Dpll.c
	@mv -f ../out/IfxGtm_Dpll.Td ../out/IfxGtm_Dpll.d && touch ../out/IfxGtm_Dpll.o

../out/IfxGtm_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxGtm_PinMap.c ../out/IfxGtm_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_PinMap.o -MMD -MP -MF ../out/IfxGtm_PinMap.Td @../out/inc.opt -c -o ../out/IfxGtm_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxGtm_PinMap.c
	@mv -f ../out/IfxGtm_PinMap.Td ../out/IfxGtm_PinMap.d && touch ../out/IfxGtm_PinMap.o

../out/IfxGtm_Tbu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tbu.c ../out/IfxGtm_Tbu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tbu.o -MMD -MP -MF ../out/IfxGtm_Tbu.Td @../out/inc.opt -c -o ../out/IfxGtm_Tbu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tbu.c
	@mv -f ../out/IfxGtm_Tbu.Td ../out/IfxGtm_Tbu.d && touch ../out/IfxGtm_Tbu.o

../out/IfxGtm_Tim.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tim.c ../out/IfxGtm_Tim.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tim.o -MMD -MP -MF ../out/IfxGtm_Tim.Td @../out/inc.opt -c -o ../out/IfxGtm_Tim.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tim.c
	@mv -f ../out/IfxGtm_Tim.Td ../out/IfxGtm_Tim.d && touch ../out/IfxGtm_Tim.o

../out/IfxGtm_Tim_In.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tim/In/IfxGtm_Tim_In.c ../out/IfxGtm_Tim_In.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tim_In.o -MMD -MP -MF ../out/IfxGtm_Tim_In.Td @../out/inc.opt -c -o ../out/IfxGtm_Tim_In.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tim/In/IfxGtm_Tim_In.c
	@mv -f ../out/IfxGtm_Tim_In.Td ../out/IfxGtm_Tim_In.d && touch ../out/IfxGtm_Tim_In.o

../out/IfxGtm_Tom.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tom.c ../out/IfxGtm_Tom.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tom.o -MMD -MP -MF ../out/IfxGtm_Tom.Td @../out/inc.opt -c -o ../out/IfxGtm_Tom.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Std/IfxGtm_Tom.c
	@mv -f ../out/IfxGtm_Tom.Td ../out/IfxGtm_Tom.d && touch ../out/IfxGtm_Tom.o

../out/IfxGtm_Tom_Pwm.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/Pwm/IfxGtm_Tom_Pwm.c ../out/IfxGtm_Tom_Pwm.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tom_Pwm.o -MMD -MP -MF ../out/IfxGtm_Tom_Pwm.Td @../out/inc.opt -c -o ../out/IfxGtm_Tom_Pwm.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/Pwm/IfxGtm_Tom_Pwm.c
	@mv -f ../out/IfxGtm_Tom_Pwm.Td ../out/IfxGtm_Tom_Pwm.d && touch ../out/IfxGtm_Tom_Pwm.o

../out/IfxGtm_Tom_PwmHl.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.c ../out/IfxGtm_Tom_PwmHl.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tom_PwmHl.o -MMD -MP -MF ../out/IfxGtm_Tom_PwmHl.Td @../out/inc.opt -c -o ../out/IfxGtm_Tom_PwmHl.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.c
	@mv -f ../out/IfxGtm_Tom_PwmHl.Td ../out/IfxGtm_Tom_PwmHl.d && touch ../out/IfxGtm_Tom_PwmHl.o

../out/IfxGtm_Tom_Timer.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.c ../out/IfxGtm_Tom_Timer.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Tom_Timer.o -MMD -MP -MF ../out/IfxGtm_Tom_Timer.Td @../out/inc.opt -c -o ../out/IfxGtm_Tom_Timer.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Tom/Timer/IfxGtm_Tom_Timer.c
	@mv -f ../out/IfxGtm_Tom_Timer.Td ../out/IfxGtm_Tom_Timer.d && touch ../out/IfxGtm_Tom_Timer.o

../out/IfxGtm_Trig.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Trig/IfxGtm_Trig.c ../out/IfxGtm_Trig.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_Trig.o -MMD -MP -MF ../out/IfxGtm_Trig.Td @../out/inc.opt -c -o ../out/IfxGtm_Trig.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Gtm/Trig/IfxGtm_Trig.c
	@mv -f ../out/IfxGtm_Trig.Td ../out/IfxGtm_Trig.d && touch ../out/IfxGtm_Trig.o

../out/IfxGtm_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxGtm_cfg.c ../out/IfxGtm_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxGtm_cfg.o -MMD -MP -MF ../out/IfxGtm_cfg.Td @../out/inc.opt -c -o ../out/IfxGtm_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxGtm_cfg.c
	@mv -f ../out/IfxGtm_cfg.Td ../out/IfxGtm_cfg.d && touch ../out/IfxGtm_cfg.o

../out/IfxMtu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Mtu/Std/IfxMtu.c ../out/IfxMtu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMtu.o -MMD -MP -MF ../out/IfxMtu.Td @../out/inc.opt -c -o ../out/IfxMtu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Mtu/Std/IfxMtu.c
	@mv -f ../out/IfxMtu.Td ../out/IfxMtu.d && touch ../out/IfxMtu.o

../out/IfxMtu_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxMtu_cfg.c ../out/IfxMtu_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMtu_cfg.o -MMD -MP -MF ../out/IfxMtu_cfg.Td @../out/inc.opt -c -o ../out/IfxMtu_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxMtu_cfg.c
	@mv -f ../out/IfxMtu_cfg.Td ../out/IfxMtu_cfg.d && touch ../out/IfxMtu_cfg.o

../out/IfxMultican.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Multican/Std/IfxMultican.c ../out/IfxMultican.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMultican.o -MMD -MP -MF ../out/IfxMultican.Td @../out/inc.opt -c -o ../out/IfxMultican.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Multican/Std/IfxMultican.c
	@mv -f ../out/IfxMultican.Td ../out/IfxMultican.d && touch ../out/IfxMultican.o

../out/IfxMultican_Can.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Multican/Can/IfxMultican_Can.c ../out/IfxMultican_Can.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMultican_Can.o -MMD -MP -MF ../out/IfxMultican_Can.Td @../out/inc.opt -c -o ../out/IfxMultican_Can.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Multican/Can/IfxMultican_Can.c
	@mv -f ../out/IfxMultican_Can.Td ../out/IfxMultican_Can.d && touch ../out/IfxMultican_Can.o

../out/IfxMultican_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxMultican_PinMap.c ../out/IfxMultican_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMultican_PinMap.o -MMD -MP -MF ../out/IfxMultican_PinMap.Td @../out/inc.opt -c -o ../out/IfxMultican_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxMultican_PinMap.c
	@mv -f ../out/IfxMultican_PinMap.Td ../out/IfxMultican_PinMap.d && touch ../out/IfxMultican_PinMap.o

../out/IfxMultican_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxMultican_cfg.c ../out/IfxMultican_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxMultican_cfg.o -MMD -MP -MF ../out/IfxMultican_cfg.Td @../out/inc.opt -c -o ../out/IfxMultican_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxMultican_cfg.c
	@mv -f ../out/IfxMultican_cfg.Td ../out/IfxMultican_cfg.d && touch ../out/IfxMultican_cfg.o

../out/IfxPort.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Port/Std/IfxPort.c ../out/IfxPort.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxPort.o -MMD -MP -MF ../out/IfxPort.Td @../out/inc.opt -c -o ../out/IfxPort.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Port/Std/IfxPort.c
	@mv -f ../out/IfxPort.Td ../out/IfxPort.d && touch ../out/IfxPort.o

../out/IfxPort_Io.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Port/Io/IfxPort_Io.c ../out/IfxPort_Io.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxPort_Io.o -MMD -MP -MF ../out/IfxPort_Io.Td @../out/inc.opt -c -o ../out/IfxPort_Io.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Port/Io/IfxPort_Io.c
	@mv -f ../out/IfxPort_Io.Td ../out/IfxPort_Io.d && touch ../out/IfxPort_Io.o

../out/IfxPort_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxPort_PinMap.c ../out/IfxPort_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxPort_PinMap.o -MMD -MP -MF ../out/IfxPort_PinMap.Td @../out/inc.opt -c -o ../out/IfxPort_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxPort_PinMap.c
	@mv -f ../out/IfxPort_PinMap.Td ../out/IfxPort_PinMap.d && touch ../out/IfxPort_PinMap.o

../out/IfxPort_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxPort_cfg.c ../out/IfxPort_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxPort_cfg.o -MMD -MP -MF ../out/IfxPort_cfg.Td @../out/inc.opt -c -o ../out/IfxPort_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxPort_cfg.c
	@mv -f ../out/IfxPort_cfg.Td ../out/IfxPort_cfg.d && touch ../out/IfxPort_cfg.o

../out/IfxQspi.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/Std/IfxQspi.c ../out/IfxQspi.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxQspi.o -MMD -MP -MF ../out/IfxQspi.Td @../out/inc.opt -c -o ../out/IfxQspi.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/Std/IfxQspi.c
	@mv -f ../out/IfxQspi.Td ../out/IfxQspi.d && touch ../out/IfxQspi.o

../out/IfxQspi_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxQspi_PinMap.c ../out/IfxQspi_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxQspi_PinMap.o -MMD -MP -MF ../out/IfxQspi_PinMap.Td @../out/inc.opt -c -o ../out/IfxQspi_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxQspi_PinMap.c
	@mv -f ../out/IfxQspi_PinMap.Td ../out/IfxQspi_PinMap.d && touch ../out/IfxQspi_PinMap.o

../out/IfxQspi_SpiMaster.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/SpiMaster/IfxQspi_SpiMaster.c ../out/IfxQspi_SpiMaster.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxQspi_SpiMaster.o -MMD -MP -MF ../out/IfxQspi_SpiMaster.Td @../out/inc.opt -c -o ../out/IfxQspi_SpiMaster.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/SpiMaster/IfxQspi_SpiMaster.c
	@mv -f ../out/IfxQspi_SpiMaster.Td ../out/IfxQspi_SpiMaster.d && touch ../out/IfxQspi_SpiMaster.o

../out/IfxQspi_SpiSlave.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.c ../out/IfxQspi_SpiSlave.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxQspi_SpiSlave.o -MMD -MP -MF ../out/IfxQspi_SpiSlave.Td @../out/inc.opt -c -o ../out/IfxQspi_SpiSlave.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Qspi/SpiSlave/IfxQspi_SpiSlave.c
	@mv -f ../out/IfxQspi_SpiSlave.Td ../out/IfxQspi_SpiSlave.d && touch ../out/IfxQspi_SpiSlave.o

../out/IfxQspi_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxQspi_cfg.c ../out/IfxQspi_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxQspi_cfg.o -MMD -MP -MF ../out/IfxQspi_cfg.Td @../out/inc.opt -c -o ../out/IfxQspi_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxQspi_cfg.c
	@mv -f ../out/IfxQspi_cfg.Td ../out/IfxQspi_cfg.d && touch ../out/IfxQspi_cfg.o

../out/IfxScuCcu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuCcu.c ../out/IfxScuCcu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxScuCcu.o -MMD -MP -MF ../out/IfxScuCcu.Td @../out/inc.opt -c -o ../out/IfxScuCcu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuCcu.c
	@mv -f ../out/IfxScuCcu.Td ../out/IfxScuCcu.d && touch ../out/IfxScuCcu.o

../out/IfxScuEru.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuEru.c ../out/IfxScuEru.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxScuEru.o -MMD -MP -MF ../out/IfxScuEru.Td @../out/inc.opt -c -o ../out/IfxScuEru.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuEru.c
	@mv -f ../out/IfxScuEru.Td ../out/IfxScuEru.d && touch ../out/IfxScuEru.o

../out/IfxScuWdt.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuWdt.c ../out/IfxScuWdt.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxScuWdt.o -MMD -MP -MF ../out/IfxScuWdt.Td @../out/inc.opt -c -o ../out/IfxScuWdt.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Scu/Std/IfxScuWdt.c
	@mv -f ../out/IfxScuWdt.Td ../out/IfxScuWdt.d && touch ../out/IfxScuWdt.o

../out/IfxScu_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxScu_PinMap.c ../out/IfxScu_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxScu_PinMap.o -MMD -MP -MF ../out/IfxScu_PinMap.Td @../out/inc.opt -c -o ../out/IfxScu_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxScu_PinMap.c
	@mv -f ../out/IfxScu_PinMap.Td ../out/IfxScu_PinMap.d && touch ../out/IfxScu_PinMap.o

../out/IfxScu_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxScu_cfg.c ../out/IfxScu_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxScu_cfg.o -MMD -MP -MF ../out/IfxScu_cfg.Td @../out/inc.opt -c -o ../out/IfxScu_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxScu_cfg.c
	@mv -f ../out/IfxScu_cfg.Td ../out/IfxScu_cfg.d && touch ../out/IfxScu_cfg.o

../out/IfxSent.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Sent/Std/IfxSent.c ../out/IfxSent.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSent.o -MMD -MP -MF ../out/IfxSent.Td @../out/inc.opt -c -o ../out/IfxSent.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Sent/Std/IfxSent.c
	@mv -f ../out/IfxSent.Td ../out/IfxSent.d && touch ../out/IfxSent.o

../out/IfxSent_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxSent_PinMap.c ../out/IfxSent_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSent_PinMap.o -MMD -MP -MF ../out/IfxSent_PinMap.Td @../out/inc.opt -c -o ../out/IfxSent_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxSent_PinMap.c
	@mv -f ../out/IfxSent_PinMap.Td ../out/IfxSent_PinMap.d && touch ../out/IfxSent_PinMap.o

../out/IfxSent_Sent.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Sent/Sent/IfxSent_Sent.c ../out/IfxSent_Sent.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSent_Sent.o -MMD -MP -MF ../out/IfxSent_Sent.Td @../out/inc.opt -c -o ../out/IfxSent_Sent.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Sent/Sent/IfxSent_Sent.c
	@mv -f ../out/IfxSent_Sent.Td ../out/IfxSent_Sent.d && touch ../out/IfxSent_Sent.o

../out/IfxSent_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSent_cfg.c ../out/IfxSent_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSent_cfg.o -MMD -MP -MF ../out/IfxSent_cfg.Td @../out/inc.opt -c -o ../out/IfxSent_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSent_cfg.c
	@mv -f ../out/IfxSent_cfg.Td ../out/IfxSent_cfg.d && touch ../out/IfxSent_cfg.o

../out/IfxSmu.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Smu/Std/IfxSmu.c ../out/IfxSmu.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSmu.o -MMD -MP -MF ../out/IfxSmu.Td @../out/inc.opt -c -o ../out/IfxSmu.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Smu/Std/IfxSmu.c
	@mv -f ../out/IfxSmu.Td ../out/IfxSmu.d && touch ../out/IfxSmu.o

../out/IfxSmu_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxSmu_PinMap.c ../out/IfxSmu_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSmu_PinMap.o -MMD -MP -MF ../out/IfxSmu_PinMap.Td @../out/inc.opt -c -o ../out/IfxSmu_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxSmu_PinMap.c
	@mv -f ../out/IfxSmu_PinMap.Td ../out/IfxSmu_PinMap.d && touch ../out/IfxSmu_PinMap.o

../out/IfxSmu_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSmu_cfg.c ../out/IfxSmu_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSmu_cfg.o -MMD -MP -MF ../out/IfxSmu_cfg.Td @../out/inc.opt -c -o ../out/IfxSmu_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSmu_cfg.c
	@mv -f ../out/IfxSmu_cfg.Td ../out/IfxSmu_cfg.d && touch ../out/IfxSmu_cfg.o

../out/IfxSrc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Src/Std/IfxSrc.c ../out/IfxSrc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSrc.o -MMD -MP -MF ../out/IfxSrc.Td @../out/inc.opt -c -o ../out/IfxSrc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Src/Std/IfxSrc.c
	@mv -f ../out/IfxSrc.Td ../out/IfxSrc.d && touch ../out/IfxSrc.o

../out/IfxSrc_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSrc_cfg.c ../out/IfxSrc_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxSrc_cfg.o -MMD -MP -MF ../out/IfxSrc_cfg.Td @../out/inc.opt -c -o ../out/IfxSrc_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxSrc_cfg.c
	@mv -f ../out/IfxSrc_cfg.Td ../out/IfxSrc_cfg.d && touch ../out/IfxSrc_cfg.o

../out/IfxStdIf_DPipe.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.c ../out/IfxStdIf_DPipe.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStdIf_DPipe.o -MMD -MP -MF ../out/IfxStdIf_DPipe.Td @../out/inc.opt -c -o ../out/IfxStdIf_DPipe.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.c
	@mv -f ../out/IfxStdIf_DPipe.Td ../out/IfxStdIf_DPipe.d && touch ../out/IfxStdIf_DPipe.o

../out/IfxStdIf_Pos.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Pos.c ../out/IfxStdIf_Pos.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStdIf_Pos.o -MMD -MP -MF ../out/IfxStdIf_Pos.Td @../out/inc.opt -c -o ../out/IfxStdIf_Pos.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Pos.c
	@mv -f ../out/IfxStdIf_Pos.Td ../out/IfxStdIf_Pos.d && touch ../out/IfxStdIf_Pos.o

../out/IfxStdIf_PwmHl.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.c ../out/IfxStdIf_PwmHl.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStdIf_PwmHl.o -MMD -MP -MF ../out/IfxStdIf_PwmHl.Td @../out/inc.opt -c -o ../out/IfxStdIf_PwmHl.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.c
	@mv -f ../out/IfxStdIf_PwmHl.Td ../out/IfxStdIf_PwmHl.d && touch ../out/IfxStdIf_PwmHl.o

../out/IfxStdIf_Timer.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Timer.c ../out/IfxStdIf_Timer.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStdIf_Timer.o -MMD -MP -MF ../out/IfxStdIf_Timer.Td @../out/inc.opt -c -o ../out/IfxStdIf_Timer.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Timer.c
	@mv -f ../out/IfxStdIf_Timer.Td ../out/IfxStdIf_Timer.d && touch ../out/IfxStdIf_Timer.o

../out/IfxStm.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Stm/Std/IfxStm.c ../out/IfxStm.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStm.o -MMD -MP -MF ../out/IfxStm.Td @../out/inc.opt -c -o ../out/IfxStm.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Stm/Std/IfxStm.c
	@mv -f ../out/IfxStm.Td ../out/IfxStm.d && touch ../out/IfxStm.o

../out/IfxStm_Timer.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Stm/Timer/IfxStm_Timer.c ../out/IfxStm_Timer.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStm_Timer.o -MMD -MP -MF ../out/IfxStm_Timer.Td @../out/inc.opt -c -o ../out/IfxStm_Timer.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Stm/Timer/IfxStm_Timer.c
	@mv -f ../out/IfxStm_Timer.Td ../out/IfxStm_Timer.d && touch ../out/IfxStm_Timer.o

../out/IfxStm_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxStm_cfg.c ../out/IfxStm_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxStm_cfg.o -MMD -MP -MF ../out/IfxStm_cfg.Td @../out/inc.opt -c -o ../out/IfxStm_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxStm_cfg.c
	@mv -f ../out/IfxStm_cfg.Td ../out/IfxStm_cfg.d && touch ../out/IfxStm_cfg.o

../out/IfxTlf35584.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Std/IfxTlf35584.c ../out/IfxTlf35584.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584.o -MMD -MP -MF ../out/IfxTlf35584.Td @../out/inc.opt -c -o ../out/IfxTlf35584.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Std/IfxTlf35584.c
	@mv -f ../out/IfxTlf35584.Td ../out/IfxTlf35584.d && touch ../out/IfxTlf35584.o

../out/IfxTlf35584_Driver.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Driver/IfxTlf35584_Driver.c ../out/IfxTlf35584_Driver.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584_Driver.o -MMD -MP -MF ../out/IfxTlf35584_Driver.Td @../out/inc.opt -c -o ../out/IfxTlf35584_Driver.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Driver/IfxTlf35584_Driver.c
	@mv -f ../out/IfxTlf35584_Driver.Td ../out/IfxTlf35584_Driver.d && touch ../out/IfxTlf35584_Driver.o

../out/IfxTlf35584_Hal.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Hal/IfxTlf35584_Hal.c ../out/IfxTlf35584_Hal.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584_Hal.o -MMD -MP -MF ../out/IfxTlf35584_Hal.Td @../out/inc.opt -c -o ../out/IfxTlf35584_Hal.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/Hal/IfxTlf35584_Hal.c
	@mv -f ../out/IfxTlf35584_Hal.Td ../out/IfxTlf35584_Hal.d && touch ../out/IfxTlf35584_Hal.o

../out/IfxTlf35584_If.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/If/IfxTlf35584_If.c ../out/IfxTlf35584_If.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584_If.o -MMD -MP -MF ../out/IfxTlf35584_If.Td @../out/inc.opt -c -o ../out/IfxTlf35584_If.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/If/IfxTlf35584_If.c
	@mv -f ../out/IfxTlf35584_If.Td ../out/IfxTlf35584_If.d && touch ../out/IfxTlf35584_If.o

../out/IfxTlf35584_cfg.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/_Impl/IfxTlf35584_cfg.c ../out/IfxTlf35584_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584_cfg.o -MMD -MP -MF ../out/IfxTlf35584_cfg.Td @../out/inc.opt -c -o ../out/IfxTlf35584_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/_Impl/IfxTlf35584_cfg.c
	@mv -f ../out/IfxTlf35584_cfg.Td ../out/IfxTlf35584_cfg.d && touch ../out/IfxTlf35584_cfg.o

../out/IfxTlf35584_regdef.o: ../0_Sm/tlf35584_cpp/sm/tlf35584/src/_Reg/IfxTlf35584_regdef.c ../out/IfxTlf35584_regdef.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxTlf35584_regdef.o -MMD -MP -MF ../out/IfxTlf35584_regdef.Td @../out/inc.opt -c -o ../out/IfxTlf35584_regdef.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/sm/tlf35584/src/_Reg/IfxTlf35584_regdef.c
	@mv -f ../out/IfxTlf35584_regdef.Td ../out/IfxTlf35584_regdef.d && touch ../out/IfxTlf35584_regdef.o

../out/IfxVadc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Vadc/Std/IfxVadc.c ../out/IfxVadc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxVadc.o -MMD -MP -MF ../out/IfxVadc.Td @../out/inc.opt -c -o ../out/IfxVadc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Vadc/Std/IfxVadc.c
	@mv -f ../out/IfxVadc.Td ../out/IfxVadc.d && touch ../out/IfxVadc.o

../out/IfxVadc_Adc.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Vadc/Adc/IfxVadc_Adc.c ../out/IfxVadc_Adc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxVadc_Adc.o -MMD -MP -MF ../out/IfxVadc_Adc.Td @../out/inc.opt -c -o ../out/IfxVadc_Adc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/Vadc/Adc/IfxVadc_Adc.c
	@mv -f ../out/IfxVadc_Adc.Td ../out/IfxVadc_Adc.d && touch ../out/IfxVadc_Adc.o

../out/IfxVadc_PinMap.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxVadc_PinMap.c ../out/IfxVadc_PinMap.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxVadc_PinMap.o -MMD -MP -MF ../out/IfxVadc_PinMap.Td @../out/inc.opt -c -o ../out/IfxVadc_PinMap.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_PinMap/IfxVadc_PinMap.c
	@mv -f ../out/IfxVadc_PinMap.Td ../out/IfxVadc_PinMap.d && touch ../out/IfxVadc_PinMap.o

../out/IfxVadc_cfg.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxVadc_cfg.c ../out/IfxVadc_cfg.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/IfxVadc_cfg.o -MMD -MP -MF ../out/IfxVadc_cfg.Td @../out/inc.opt -c -o ../out/IfxVadc_cfg.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxVadc_cfg.c
	@mv -f ../out/IfxVadc_cfg.Td ../out/IfxVadc_cfg.d && touch ../out/IfxVadc_cfg.o

../out/Ifx_AngleTrkF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_AngleTrkF32.c ../out/Ifx_AngleTrkF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_AngleTrkF32.o -MMD -MP -MF ../out/Ifx_AngleTrkF32.Td @../out/inc.opt -c -o ../out/Ifx_AngleTrkF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_AngleTrkF32.c
	@mv -f ../out/Ifx_AngleTrkF32.Td ../out/Ifx_AngleTrkF32.d && touch ../out/Ifx_AngleTrkF32.o

../out/Ifx_Cf32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Cf32.c ../out/Ifx_Cf32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_Cf32.o -MMD -MP -MF ../out/Ifx_Cf32.Td @../out/inc.opt -c -o ../out/Ifx_Cf32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Cf32.c
	@mv -f ../out/Ifx_Cf32.Td ../out/Ifx_Cf32.d && touch ../out/Ifx_Cf32.o

../out/Ifx_CircularBuffer.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.c ../out/Ifx_CircularBuffer.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_CircularBuffer.o -MMD -MP -MF ../out/Ifx_CircularBuffer.Td @../out/inc.opt -c -o ../out/Ifx_CircularBuffer.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.c
	@mv -f ../out/Ifx_CircularBuffer.Td ../out/Ifx_CircularBuffer.d && touch ../out/Ifx_CircularBuffer.o

../out/Ifx_CircularBuffer.asm.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.c ../out/Ifx_CircularBuffer.asm.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_CircularBuffer.asm.o -MMD -MP -MF ../out/Ifx_CircularBuffer.asm.Td @../out/inc.opt -c -o ../out/Ifx_CircularBuffer.asm.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_CircularBuffer.asm.c
	@mv -f ../out/Ifx_CircularBuffer.asm.Td ../out/Ifx_CircularBuffer.asm.d && touch ../out/Ifx_CircularBuffer.asm.o

../out/Ifx_Console.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Comm/Ifx_Console.c ../out/Ifx_Console.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_Console.o -MMD -MP -MF ../out/Ifx_Console.Td @../out/inc.opt -c -o ../out/Ifx_Console.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Comm/Ifx_Console.c
	@mv -f ../out/Ifx_Console.Td ../out/Ifx_Console.d && touch ../out/Ifx_Console.o

../out/Ifx_Crc.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Crc.c ../out/Ifx_Crc.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_Crc.o -MMD -MP -MF ../out/Ifx_Crc.Td @../out/inc.opt -c -o ../out/Ifx_Crc.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Crc.c
	@mv -f ../out/Ifx_Crc.Td ../out/Ifx_Crc.d && touch ../out/Ifx_Crc.o

../out/Ifx_DateTime.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.c ../out/Ifx_DateTime.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_DateTime.o -MMD -MP -MF ../out/Ifx_DateTime.Td @../out/inc.opt -c -o ../out/Ifx_DateTime.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.c
	@mv -f ../out/Ifx_DateTime.Td ../out/Ifx_DateTime.d && touch ../out/Ifx_DateTime.o

../out/Ifx_FftF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32.c ../out/Ifx_FftF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_FftF32.o -MMD -MP -MF ../out/Ifx_FftF32.Td @../out/inc.opt -c -o ../out/Ifx_FftF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32.c
	@mv -f ../out/Ifx_FftF32.Td ../out/Ifx_FftF32.d && touch ../out/Ifx_FftF32.o

../out/Ifx_FftF32_BitReverseTable.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_BitReverseTable.c ../out/Ifx_FftF32_BitReverseTable.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_FftF32_BitReverseTable.o -MMD -MP -MF ../out/Ifx_FftF32_BitReverseTable.Td @../out/inc.opt -c -o ../out/Ifx_FftF32_BitReverseTable.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_BitReverseTable.c
	@mv -f ../out/Ifx_FftF32_BitReverseTable.Td ../out/Ifx_FftF32_BitReverseTable.d && touch ../out/Ifx_FftF32_BitReverseTable.o

../out/Ifx_FftF32_TwiddleTable.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_TwiddleTable.c ../out/Ifx_FftF32_TwiddleTable.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_FftF32_TwiddleTable.o -MMD -MP -MF ../out/Ifx_FftF32_TwiddleTable.Td @../out/inc.opt -c -o ../out/Ifx_FftF32_TwiddleTable.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_TwiddleTable.c
	@mv -f ../out/Ifx_FftF32_TwiddleTable.Td ../out/Ifx_FftF32_TwiddleTable.d && touch ../out/Ifx_FftF32_TwiddleTable.o

../out/Ifx_Fifo.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_Fifo.c ../out/Ifx_Fifo.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_Fifo.o -MMD -MP -MF ../out/Ifx_Fifo.Td @../out/inc.opt -c -o ../out/Ifx_Fifo.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/DataHandling/Ifx_Fifo.c
	@mv -f ../out/Ifx_Fifo.Td ../out/Ifx_Fifo.d && touch ../out/Ifx_Fifo.o

../out/Ifx_GlobalResources.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/General/Ifx_GlobalResources.c ../out/Ifx_GlobalResources.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_GlobalResources.o -MMD -MP -MF ../out/Ifx_GlobalResources.Td @../out/inc.opt -c -o ../out/Ifx_GlobalResources.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/General/Ifx_GlobalResources.c
	@mv -f ../out/Ifx_GlobalResources.Td ../out/Ifx_GlobalResources.d && touch ../out/Ifx_GlobalResources.o

../out/Ifx_IntegralF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_IntegralF32.c ../out/Ifx_IntegralF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_IntegralF32.o -MMD -MP -MF ../out/Ifx_IntegralF32.Td @../out/inc.opt -c -o ../out/Ifx_IntegralF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_IntegralF32.c
	@mv -f ../out/Ifx_IntegralF32.Td ../out/Ifx_IntegralF32.d && touch ../out/Ifx_IntegralF32.o

../out/Ifx_InternalMux.o: ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/InternalMux/Ifx_InternalMux.c ../out/Ifx_InternalMux.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_InternalMux.o -MMD -MP -MF ../out/Ifx_InternalMux.Td @../out/inc.opt -c -o ../out/Ifx_InternalMux.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/iLLD/TC23A/Tricore/_Lib/InternalMux/Ifx_InternalMux.c
	@mv -f ../out/Ifx_InternalMux.Td ../out/Ifx_InternalMux.d && touch ../out/Ifx_InternalMux.o

../out/Ifx_LowPassPt1F32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LowPassPt1F32.c ../out/Ifx_LowPassPt1F32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LowPassPt1F32.o -MMD -MP -MF ../out/Ifx_LowPassPt1F32.Td @../out/inc.opt -c -o ../out/Ifx_LowPassPt1F32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LowPassPt1F32.c
	@mv -f ../out/Ifx_LowPassPt1F32.Td ../out/Ifx_LowPassPt1F32.d && touch ../out/Ifx_LowPassPt1F32.o

../out/Ifx_LutAtan2F32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32.c ../out/Ifx_LutAtan2F32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutAtan2F32.o -MMD -MP -MF ../out/Ifx_LutAtan2F32.Td @../out/inc.opt -c -o ../out/Ifx_LutAtan2F32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32.c
	@mv -f ../out/Ifx_LutAtan2F32.Td ../out/Ifx_LutAtan2F32.d && touch ../out/Ifx_LutAtan2F32.o

../out/Ifx_LutAtan2F32_Table.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32_Table.c ../out/Ifx_LutAtan2F32_Table.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutAtan2F32_Table.o -MMD -MP -MF ../out/Ifx_LutAtan2F32_Table.Td @../out/inc.opt -c -o ../out/Ifx_LutAtan2F32_Table.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32_Table.c
	@mv -f ../out/Ifx_LutAtan2F32_Table.Td ../out/Ifx_LutAtan2F32_Table.d && touch ../out/Ifx_LutAtan2F32_Table.o

../out/Ifx_LutLSincosF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLSincosF32.c ../out/Ifx_LutLSincosF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutLSincosF32.o -MMD -MP -MF ../out/Ifx_LutLSincosF32.Td @../out/inc.opt -c -o ../out/Ifx_LutLSincosF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLSincosF32.c
	@mv -f ../out/Ifx_LutLSincosF32.Td ../out/Ifx_LutLSincosF32.d && touch ../out/Ifx_LutLSincosF32.o

../out/Ifx_LutLinearF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLinearF32.c ../out/Ifx_LutLinearF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutLinearF32.o -MMD -MP -MF ../out/Ifx_LutLinearF32.Td @../out/inc.opt -c -o ../out/Ifx_LutLinearF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLinearF32.c
	@mv -f ../out/Ifx_LutLinearF32.Td ../out/Ifx_LutLinearF32.d && touch ../out/Ifx_LutLinearF32.o

../out/Ifx_LutSincosF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32.c ../out/Ifx_LutSincosF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutSincosF32.o -MMD -MP -MF ../out/Ifx_LutSincosF32.Td @../out/inc.opt -c -o ../out/Ifx_LutSincosF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32.c
	@mv -f ../out/Ifx_LutSincosF32.Td ../out/Ifx_LutSincosF32.d && touch ../out/Ifx_LutSincosF32.o

../out/Ifx_LutSincosF32_Table.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32_Table.c ../out/Ifx_LutSincosF32_Table.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_LutSincosF32_Table.o -MMD -MP -MF ../out/Ifx_LutSincosF32_Table.Td @../out/inc.opt -c -o ../out/Ifx_LutSincosF32_Table.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32_Table.c
	@mv -f ../out/Ifx_LutSincosF32_Table.Td ../out/Ifx_LutSincosF32_Table.d && touch ../out/Ifx_LutSincosF32_Table.o

../out/Ifx_RampF32.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_RampF32.c ../out/Ifx_RampF32.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_RampF32.o -MMD -MP -MF ../out/Ifx_RampF32.Td @../out/inc.opt -c -o ../out/Ifx_RampF32.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_RampF32.c
	@mv -f ../out/Ifx_RampF32.Td ../out/Ifx_RampF32.d && touch ../out/Ifx_RampF32.o

../out/Ifx_Shell.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.c ../out/Ifx_Shell.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_Shell.o -MMD -MP -MF ../out/Ifx_Shell.Td @../out/inc.opt -c -o ../out/Ifx_Shell.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Comm/Ifx_Shell.c
	@mv -f ../out/Ifx_Shell.Td ../out/Ifx_Shell.d && touch ../out/Ifx_Shell.o

../out/Ifx_WndF32_BlackmanHarrisTable.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.c ../out/Ifx_WndF32_BlackmanHarrisTable.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_WndF32_BlackmanHarrisTable.o -MMD -MP -MF ../out/Ifx_WndF32_BlackmanHarrisTable.Td @../out/inc.opt -c -o ../out/Ifx_WndF32_BlackmanHarrisTable.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.c
	@mv -f ../out/Ifx_WndF32_BlackmanHarrisTable.Td ../out/Ifx_WndF32_BlackmanHarrisTable.d && touch ../out/Ifx_WndF32_BlackmanHarrisTable.o

../out/Ifx_WndF32_HannTable.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_HannTable.c ../out/Ifx_WndF32_HannTable.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/Ifx_WndF32_HannTable.o -MMD -MP -MF ../out/Ifx_WndF32_HannTable.Td @../out/inc.opt -c -o ../out/Ifx_WndF32_HannTable.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_HannTable.c
	@mv -f ../out/Ifx_WndF32_HannTable.Td ../out/Ifx_WndF32_HannTable.d && touch ../out/Ifx_WndF32_HannTable.o

../out/SpiIf.o: ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/If/SpiIf.c ../out/SpiIf.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/SpiIf.o -MMD -MP -MF ../out/SpiIf.Td @../out/inc.opt -c -o ../out/SpiIf.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_tc23a/Src/BaseSw/Service/CpuGeneric/If/SpiIf.c
	@mv -f ../out/SpiIf.Td ../out/SpiIf.d && touch ../out/SpiIf.o

../out/aurix.o: ../0_Sm/illd_cpp_ext/src/aurix.cpp ../out/aurix.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/aurix.o -MMD -MP -MF ../out/aurix.Td @../out/inc.opt -c -o ../out/aurix.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/illd_cpp_ext/src/aurix.cpp
	@mv -f ../out/aurix.Td ../out/aurix.d && touch ../out/aurix.o

../out/factorial.o: ../src/factorial.cpp ../out/factorial.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/factorial.o -MMD -MP -MF ../out/factorial.Td @../out/inc.opt -c -o ../out/factorial.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/factorial.cpp
	@mv -f ../out/factorial.Td ../out/factorial.d && touch ../out/factorial.o

../out/hello.o: ../src/hello.cpp ../out/hello.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/hello.o -MMD -MP -MF ../out/hello.Td @../out/inc.opt -c -o ../out/hello.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/hello.cpp
	@mv -f ../out/hello.Td ../out/hello.d && touch ../out/hello.o

../out/int2str.o: ../0_Sm/common/src/int2str.cpp ../out/int2str.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/int2str.o -MMD -MP -MF ../out/int2str.Td @../out/inc.opt -c -o ../out/int2str.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/common/src/int2str.cpp
	@mv -f ../out/int2str.Td ../out/int2str.d && touch ../out/int2str.o

../out/main.o: ../src/main.cpp ../out/main.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/main.o -MMD -MP -MF ../out/main.Td @../out/inc.opt -c -o ../out/main.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/main.cpp
	@mv -f ../out/main.Td ../out/main.d && touch ../out/main.o

../out/tlf35584.o: ../0_Sm/tlf35584_cpp/src/tlf35584.cpp ../out/tlf35584.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/tlf35584.o -MMD -MP -MF ../out/tlf35584.Td @../out/inc.opt -c -o ../out/tlf35584.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../0_Sm/tlf35584_cpp/src/tlf35584.cpp
	@mv -f ../out/tlf35584.Td ../out/tlf35584.d && touch ../out/tlf35584.o

../out/%.d: ;
.PRECIOUS: ../out/%.d
include $(wildcard ../out/*.d)

clean:
	rm -rf ../out/*.o
	rm -rf ../out/*.d