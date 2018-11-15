/**
 * \file IfxQspi_SpiMaster.c
 * \brief QSPI SPIMASTER details
 *
 * \version iLLD_1_0_1_3_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxQspi_SpiMaster.h"

/** \addtogroup IfxLld_Qspi_SpiMaster_Channel
 * \{ */

/******************************************************************************/
/*-----------------------Private Function Prototypes--------------------------*/
/******************************************************************************/

/** \brief Gets current active channel
 * \param handle Module handle
 * \return current active channel
 */
IFX_STATIC IfxQspi_SpiMaster_Channel *IfxQspi_SpiMaster_activeChannel(IfxQspi_SpiMaster *handle);

/** \} */

/** \addtogroup IfxLld_Qspi_SpiMaster_Support
 * \{ */

/******************************************************************************/
/*-----------------------Private Function Prototypes--------------------------*/
/******************************************************************************/

/** \brief Active the SLSO pin.
 * \param chHandle Module Channel handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_activateSlso(IfxQspi_SpiMaster_Channel *chHandle);

/** \brief Deactive the SLSO pin.
 * \param chHandle Module Channel handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_deactivateSlso(IfxQspi_SpiMaster_Channel *chHandle);

/** \brief Locks the transfer and gets the current status of it.
 * \param handle Module handle
 * \return SpiIf_Status_ok if sending is done otherwise SpiIf_Status_busy.
 */
IFX_STATIC SpiIf_Status IfxQspi_SpiMaster_lock(IfxQspi_SpiMaster *handle);

/** \brief Reads data from the Rx FIFO
 * \param chHandle Module Channel handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_read(IfxQspi_SpiMaster_Channel *chHandle);

/** \brief Unlocks the transfers
 * \param handle Module handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_unlock(IfxQspi_SpiMaster *handle);

/** \brief Writes data into the Tx FIFO
 * \param chHandle Module Channel handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_write(IfxQspi_SpiMaster_Channel *chHandle);

/** \brief Writes Long/xxl data into the Tx FIFO
 * \param chHandle Module Channel handle
 * \return None
 */
IFX_STATIC void IfxQspi_SpiMaster_writeLong(IfxQspi_SpiMaster_Channel *chHandle);

/** \} */

/** \addtogroup IfxLld_Qspi_SpiMaster_DataStructures
 * \{ */

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/** \brief dummy variable where recived data is placed
 */
IFX_STATIC uint32           IfxQspi_SpiMaster_dummyRxValue = 0;

/** \brief dummy value to be transmitted
 */
IFX_STATIC IFX_CONST uint32 IfxQspi_SpiMaster_dummyTxValue = ~0;

/** \} */

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

IFX_STATIC void IfxQspi_SpiMaster_activateSlso(IfxQspi_SpiMaster_Channel *chHandle)
{
    IfxPort_State action = (chHandle->slsoActiveState == Ifx_ActiveState_low) ? IfxPort_State_low : IfxPort_State_high;
    IfxPort_setPinState(chHandle->slso.port, chHandle->slso.pinIndex, action);
}


IFX_STATIC IfxQspi_SpiMaster_Channel *IfxQspi_SpiMaster_activeChannel(IfxQspi_SpiMaster *handle)
{
    return (IfxQspi_SpiMaster_Channel *)handle->base.activeChannel;
}


IFX_STATIC void IfxQspi_SpiMaster_deactivateSlso(IfxQspi_SpiMaster_Channel *chHandle)
{
    IfxPort_State action = (chHandle->slsoActiveState == Ifx_ActiveState_low) ? IfxPort_State_high : IfxPort_State_low;
    IfxPort_setPinState(chHandle->slso.port, chHandle->slso.pinIndex, action);
}


SpiIf_Status IfxQspi_SpiMaster_exchange(IfxQspi_SpiMaster_Channel *chHandle, const void *src, void *dest, Ifx_SizeT count)
{
    IfxQspi_SpiMaster *handle = (IfxQspi_SpiMaster *)chHandle->base.driver;
    SpiIf_Status       status = IfxQspi_SpiMaster_lock(handle);

    if (status == SpiIf_Status_ok)
    {
        /* initiate transfer when resource is free */
        handle->base.activeChannel      = &chHandle->base;
        chHandle->base.flags.onTransfer = 1;
        chHandle->base.tx.data          = (void *)src;
        chHandle->base.tx.remaining     = count;
        chHandle->firstWrite            = TRUE;
        chHandle->base.rx.data          = dest;
        chHandle->base.rx.remaining     = count;

        if (chHandle->activateSlso != NULL_PTR)
        {
            chHandle->activateSlso(chHandle);
        }

        if ((chHandle->mode == IfxQspi_SpiMaster_Mode_long) ||
            (chHandle->mode == IfxQspi_SpiMaster_Mode_longContinuous))
        {
            IfxQspi_SpiMaster_writeLong((IfxQspi_SpiMaster_Channel *)chHandle);
        }
        else if (chHandle->mode == IfxQspi_SpiMaster_Mode_xxl)
        {
            handle->qspi->XXLCON.B.XDL = count - 1;
            IfxQspi_SpiMaster_writeLong((IfxQspi_SpiMaster_Channel *)chHandle);
        }
        else
        {
            /* chHandle->mode == IfxQspi_SpiMaster_Mode_ShortCont*/
            chHandle->base.txHandler(handle->base.activeChannel);
        }
    }

    return status;
}


SpiIf_ChConfig IfxQspi_SpiMaster_getChannelConfig(IfxQspi_SpiMaster_Channel *chHandle)
{
    {
        SpiIf_ChConfig     chConfig;
        IfxQspi_SpiMaster *handle  = (IfxQspi_SpiMaster *)chHandle->base.driver->driver;
        Ifx_QSPI          *qspiSFR = handle->qspi;
        Ifx_QSPI_ECON      econ;
        econ.U                        = qspiSFR->ECON[chHandle->channelId % 8].U;

        chConfig.baudrate             = IfxQspi_calcRealBaudrate(qspiSFR, chHandle->channelId % 8);
        chConfig.driver               = chHandle->base.driver;
        chConfig.errorChecks.baudrate = 0;
        chConfig.errorChecks.phase    = 0;
        chConfig.errorChecks.receive  = 0;
        chConfig.errorChecks.reserved = 0;
        chConfig.errorChecks.transmit = 0;
        chConfig.mode.autoCS          = (chHandle->activateSlso == NULL_PTR) && (chHandle->deactivateSlso == NULL_PTR);
        chConfig.mode.clockPolarity   = econ.B.CPOL == 0 ? SpiIf_ClockPolarity_idleLow : SpiIf_ClockPolarity_idleHigh;
        chConfig.mode.csActiveLevel   = chHandle->slsoActiveState;
        chConfig.mode.csInactiveDelay = chHandle->bacon.B.IDLE;
        chConfig.mode.csLeadDelay     = chHandle->bacon.B.LEAD;
        chConfig.mode.csTrailDelay    = chHandle->bacon.B.TRAIL;
        chConfig.mode.dataHeading     = chHandle->bacon.B.MSB == 0 ? SpiIf_DataHeading_lsbFirst : SpiIf_DataHeading_msbFirst;
        chConfig.mode.dataWidth       = chHandle->bacon.B.DL + 1;
        chConfig.mode.enabled         = 0;
        chConfig.mode.loopback        = qspiSFR->GLOBALCON.B.LB;
        chConfig.mode.parityCheck     = econ.B.PAREN;
        chConfig.mode.parityMode      = chHandle->bacon.B.PARTYP == 0 ? Ifx_ParityMode_even : Ifx_ParityMode_odd;
        chConfig.mode.shiftClock      = econ.B.CPH == 1 ? SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge : SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;

        return chConfig;
    }
}


SpiIf_Status IfxQspi_SpiMaster_getStatus(IfxQspi_SpiMaster_Channel *chHandle)
{
    SpiIf_Status status = SpiIf_Status_ok;

    if ((chHandle->base.flags.onTransfer != 0) || (chHandle->base.driver->sending != 0))
    {
        status = SpiIf_Status_busy;
    }

    return status;
}


SpiIf_Status IfxQspi_SpiMaster_initChannel(IfxQspi_SpiMaster_Channel *chHandle, const IfxQspi_SpiMaster_ChannelConfig *chConfig)
{
    IfxQspi_SpiMaster *handle  = chConfig->base.driver->driver;
    Ifx_QSPI          *qspiSFR = handle->qspi;

    chHandle->base.driver           = chConfig->base.driver;
    chHandle->base.flags.onTransfer = FALSE;
    chHandle->channelBasedCs        = chConfig->channelBasedCs;
    chHandle->mode                  = chConfig->mode;

    //Loop back configuration.
    uint32                          loopback = chConfig->base.mode.loopback;
    qspiSFR->GLOBALCON.B.LB = loopback;

    /* chip-select output pin */
    const IfxQspi_SpiMaster_Output *slso = &(chConfig->sls.output);

    if ((loopback == 1) && (slso->pin == NULL_PTR)) /* if loopback is enabled && no pin is specified */
    {
        chHandle->channelId = (IfxQspi_ChannelId)0; /* select 0 as default, if not specified */
    }
    else /* not loop back - pin must be configured */
    {
        chHandle->channelId = (IfxQspi_ChannelId)chConfig->sls.output.pin->slsoNr;
    }

    uint8 cs = chHandle->channelId % 8;

    {
        if (handle->maximumBaudrate < chConfig->base.baudrate)
        {
            IFX_ASSERT(IFX_VERBOSE_LEVEL_WARNING, FALSE);    /* desired channel Baud Rate > Maximum module Baud Rate */
        }

        qspiSFR->ECON[cs].U = IfxQspi_calculateExtendedConfigurationValue(qspiSFR, cs, &chConfig->base);
        chHandle->bacon.U   = IfxQspi_calculateBasicConfigurationValue(qspiSFR, chHandle->channelId, &chConfig->base.mode, chConfig->base.baudrate);

        {   /* QSPI chip-select line */
            uint32 mask = 1U << chHandle->channelId;
            uint32 oen  = mask << 16;
            uint32 aol  = (((chConfig->base.mode.csActiveLevel == Ifx_ActiveState_low) ? 0 : 1) << chHandle->channelId);
            __ldmst(&qspiSFR->SSOC.U, (mask | (mask << 16)), (aol | oen));
        }
    }
    chHandle->base.baudrate = IfxQspi_calcRealBaudrate(qspiSFR, (chHandle->bacon.B.CS & 0x7U));

    /* Select the chip select activate and de-activate functions */
    if (slso->pin == NULL_PTR)
    {
        chHandle->activateSlso   = NULL_PTR;
        chHandle->deactivateSlso = NULL_PTR;
    }
    else
    {
        chHandle->slso            = slso->pin->pin;
        chHandle->slsoActiveState = chConfig->base.mode.csActiveLevel;

        if (!chConfig->base.mode.autoCS)
        {
            chHandle->activateSlso   = &IfxQspi_SpiMaster_activateSlso;
            chHandle->deactivateSlso = &IfxQspi_SpiMaster_deactivateSlso;

            /** - Override the SLSO manually as general-purpose output */
            chHandle->deactivateSlso(chHandle);
            IfxQspi_initSlso(slso->pin, chConfig->sls.output.mode, chConfig->sls.output.driver, IfxPort_OutputIdx_general);
        }
        else
        {
            chHandle->activateSlso   = NULL_PTR;
            chHandle->deactivateSlso = NULL_PTR;
            IfxQspi_initSlso(slso->pin, chConfig->sls.output.mode, chConfig->sls.output.driver, slso->pin->select);
        }
    }

    chHandle->dataWidth      = chConfig->base.mode.dataWidth;
    chHandle->base.txHandler = (TxRxHandler) & IfxQspi_SpiMaster_write;
    chHandle->base.rxHandler = (TxRxHandler) & IfxQspi_SpiMaster_read;

    if (handle->dma.useDma)
    {
        Ifx_DMA *dmaSFR = &MODULE_DMA;
        IfxDma_setChannelDestinationAddress(dmaSFR, handle->dma.txDmaChannelId, (uint32 *)&qspiSFR->DATAENTRY[cs].U);
    }

    return SpiIf_Status_ok;
}


void IfxQspi_SpiMaster_initChannelConfig(IfxQspi_SpiMaster_ChannelConfig *chConfig, IfxQspi_SpiMaster *handle)
{
    SpiIf_initChannelConfig(&chConfig->base, &handle->base);
    chConfig->sls.output.pin    = NULL_PTR;
    chConfig->sls.output.mode   = IfxPort_OutputMode_pushPull;
    chConfig->sls.output.driver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    chConfig->sls.input.pin     = NULL_PTR;
    chConfig->sls.input.mode    = IfxPort_InputMode_noPullDevice;
    chConfig->channelBasedCs    = IfxQspi_SpiMaster_ChannelBasedCs_disabled;
    chConfig->mode              = IfxQspi_SpiMaster_Mode_shortContinuous;
}


void IfxQspi_SpiMaster_initModule(IfxQspi_SpiMaster *handle, const IfxQspi_SpiMaster_Config *config)
{
    Ifx_QSPI *qspiSFR = config->qspi;

    Ifx_DMA  *dmaSFR  = &MODULE_DMA;

    /* handle.base must be at offset 0 to be compatible with the standard interface SscIf */
    {
        uint16 password = IfxScuWdt_getCpuWatchdogPassword();
        IfxScuWdt_clearCpuEndinit(password);
        IfxQspi_setEnableModuleRequest(qspiSFR);
        IfxQspi_setSleepMode(qspiSFR, (config->allowSleepMode != FALSE) ? IfxQspi_SleepMode_enable : IfxQspi_SleepMode_disable);
        IfxScuWdt_setCpuEndinit(password);
    }

    {                                                        /* Configure GLOBAL, Note: at the moment default values for GLOBAL */
        Ifx_QSPI_GLOBALCON globalcon;
        globalcon.U        = 0;
        globalcon.B.TQ     = IfxQspi_calculateTimeQuantumLength(qspiSFR, config->base.maximumBaudrate);
        globalcon.B.EXPECT = IfxQspi_ExpectTimeout_2097152;  /* 2^(EXPECT+6) : timeout for expect phase in Tqspi */
        //globalcon.B.LB      = 0 ;                             /* 0 : disable loop-back w*/
        //globalcon.B.DEL0    = 0;                             /* 0 : disable delayed mode for SLSO 0 */
        //globalcon.B.STROBE  = 0;                             /* (STROBE+1) : strobe delay for SLSO 0 in Tq */
        //globalcon.B.SRF     = 0;                             /* 0 : disable stop-on-RXFIFO full feature */
        //globalcon.B.STIP    = 0;                             /* 0 : MRST = 0 when QSPI is deselected in slave mode */
        //globalcon.B.EN      = 0;                             /* 0 : PAUSE requested, 1 : RUN requested */
        globalcon.B.MS       = IfxQspi_Mode_master;            /* select master mode */
        globalcon.B.AREN     = (config->pauseOnBaudrateSpikeErrors != FALSE) ? 1U : 0U;
        globalcon.B.RESETS   = 1;
        qspiSFR->GLOBALCON.U = globalcon.U;
    }

    {   /* Configure interrupt requests */
        Ifx_QSPI_GLOBALCON1 globalcon1;
        globalcon1.U           = 0;
        //TODO: globalcon1.B.ERRORENS;
        globalcon1.B.TXEN      = (config->base.txPriority > 0) || (config->dma.useDma);
        globalcon1.B.RXEN      = (config->base.rxPriority > 0) || (config->dma.useDma);
        globalcon1.B.TXFIFOINT = config->txFifoThreshold;
        globalcon1.B.RXFIFOINT = config->rxFifoThreshold;
        globalcon1.B.TXFM      = config->txFifoMode;
        globalcon1.B.RXFM      = config->rxFifoMode;

        qspiSFR->GLOBALCON1.U  = globalcon1.U;
    }

    /* Configure I/O pins for master mode */
    const IfxQspi_SpiMaster_Pins *pins = config->pins;

    if (pins != NULL_PTR)
    {
        const IfxQspi_Sclk_Out *sclkOut = pins->sclk;

        if (sclkOut != NULL_PTR)
        {
            IfxQspi_initSclkOutPin(sclkOut, pins->sclkMode, pins->pinDriver);
        }

        const IfxQspi_Mtsr_Out *mtsrOut = pins->mtsr;

        if (mtsrOut != NULL_PTR)
        {
            IfxQspi_initMtsrOutPin(mtsrOut, pins->mtsrMode, pins->pinDriver);
        }

        const IfxQspi_Mrst_In *mrstIn = pins->mrst;

        if (mrstIn != NULL_PTR)
        {
            IfxQspi_initMrstInPinWithPadLevel(mrstIn, pins->mrstMode, pins->pinDriver);
        }
    }

    handle->qspi                     = qspiSFR;
    handle->base.driver              = handle;
    handle->base.sending             = 0U;
    handle->base.activeChannel       = NULL_PTR;

    handle->base.functions.exchange  = (SpiIf_Exchange) & IfxQspi_SpiMaster_exchange;
    handle->base.functions.getStatus = (SpiIf_GetStatus) & IfxQspi_SpiMaster_getStatus;

    if (config->dma.useDma)
    {
        handle->base.functions.onTx = (SpiIf_OnEvent) & IfxQspi_SpiMaster_isrDmaTransmit;
        handle->base.functions.onRx = (SpiIf_OnEvent) & IfxQspi_SpiMaster_isrDmaReceive;
    }
    else
    {
        handle->base.functions.onTx = (SpiIf_OnEvent) & IfxQspi_SpiMaster_isrTransmit;
        handle->base.functions.onRx = (SpiIf_OnEvent) & IfxQspi_SpiMaster_isrReceive;
    }

    handle->base.functions.onError = (SpiIf_OnEvent) & IfxQspi_SpiMaster_isrError;

    if (config->dma.useDma)
    {
        handle->dma.useDma = TRUE;
        IfxDma_Dma               dma;
        IfxDma_Dma_createModuleHandle(&dma, dmaSFR);

        IfxDma_Dma_ChannelConfig dmaCfg;
        IfxDma_Dma_initChannelConfig(&dmaCfg, &dma);

        {
            handle->dma.txDmaChannelId     = config->dma.txDmaChannelId;
            dmaCfg.channelId               = handle->dma.txDmaChannelId;
            dmaCfg.hardwareRequestEnabled  = FALSE; // will be triggered from FFT service request
            dmaCfg.channelInterruptEnabled = TRUE;  // trigger interrupt after transaction

            // source address and transfer count will be configured during runtime
            dmaCfg.sourceAddress               = 0;
            dmaCfg.sourceAddressCircularRange  = IfxDma_ChannelIncrementCircular_none;
            dmaCfg.sourceCircularBufferEnabled = FALSE;
            dmaCfg.transferCount               = 0;
            dmaCfg.moveSize                    = IfxDma_ChannelMoveSize_8bit;

            // destination address is fixed; use circular mode to stay at this address for each move
            dmaCfg.destinationAddress               = (uint32)&qspiSFR->DATAENTRY[0].U;
            dmaCfg.destinationAddressCircularRange  = IfxDma_ChannelIncrementCircular_none;
            dmaCfg.destinationCircularBufferEnabled = TRUE;

            dmaCfg.requestMode                      = IfxDma_ChannelRequestMode_oneTransferPerRequest;
            dmaCfg.operationMode                    = IfxDma_ChannelOperationMode_single;
            dmaCfg.blockMode                        = IfxDma_ChannelMove_1;

            // initialize interrupt for tx
            dmaCfg.channelInterruptTypeOfService = config->base.isrProvider;
            dmaCfg.channelInterruptPriority      = config->base.txPriority;

            IfxDma_Dma_initChannel(&handle->dma.txDmaChannel, &dmaCfg);
        }

        {
            handle->dma.rxDmaChannelId     = config->dma.rxDmaChannelId;
            dmaCfg.channelId               = handle->dma.rxDmaChannelId;
            dmaCfg.hardwareRequestEnabled  = FALSE; // will be triggered from qspi service request
            dmaCfg.channelInterruptEnabled = TRUE;  // trigger interrupt after transaction

            // source address is fixed; use circular mode to stay at this address for each move
            dmaCfg.sourceAddress               = (uint32)&qspiSFR->RXEXIT.U;
            dmaCfg.sourceAddressCircularRange  = IfxDma_ChannelIncrementCircular_none;
            dmaCfg.sourceCircularBufferEnabled = TRUE;

            // destination address and transfer count will be configured during runtime
            dmaCfg.destinationAddress               = 0;
            dmaCfg.destinationAddressCircularRange  = IfxDma_ChannelIncrementCircular_none;
            dmaCfg.destinationCircularBufferEnabled = FALSE;
            dmaCfg.transferCount                    = 0;

            dmaCfg.requestMode                      = IfxDma_ChannelRequestMode_oneTransferPerRequest;
            dmaCfg.operationMode                    = IfxDma_ChannelOperationMode_single;
            dmaCfg.moveSize                         = IfxDma_ChannelMoveSize_8bit;
            dmaCfg.blockMode                        = IfxDma_ChannelMove_1;

            // initialize interrupt for rx
            dmaCfg.channelInterruptTypeOfService = config->base.isrProvider;
            dmaCfg.channelInterruptPriority      = config->base.rxPriority;

            IfxDma_Dma_initChannel(&handle->dma.rxDmaChannel, &dmaCfg);
        }
    }

    /* Qspi interrupt configuration */
    {
        IfxQspi_clearAllEventFlags(qspiSFR);

        if (handle->dma.useDma)
        {
            volatile Ifx_SRC_SRCR *src = IfxQspi_getTransmitSrc(qspiSFR);
            IfxSrc_init(src, IfxSrc_Tos_dma, (Ifx_Priority)config->dma.txDmaChannelId);
            IfxSrc_enable(src);

            src = IfxQspi_getReceiveSrc(qspiSFR);
            IfxSrc_init(src, IfxSrc_Tos_dma, (Ifx_Priority)config->dma.rxDmaChannelId);
            IfxSrc_enable(src);
        }
        else
        {
            if (config->base.txPriority != 0)
            {
                volatile Ifx_SRC_SRCR *src = IfxQspi_getTransmitSrc(qspiSFR);
                IfxSrc_init(src, config->base.isrProvider, config->base.txPriority);
                IfxSrc_enable(src);
            }

            if (config->base.rxPriority != 0)
            {
                volatile Ifx_SRC_SRCR *src = IfxQspi_getReceiveSrc(qspiSFR);
                IfxSrc_init(src, config->base.isrProvider, config->base.rxPriority);
                IfxSrc_enable(src);
            }

            if (config->base.erPriority != 0)
            {
                volatile Ifx_SRC_SRCR *src = IfxQspi_getErrorSrc(qspiSFR);
                IfxSrc_init(src, config->base.isrProvider, config->base.erPriority);
                IfxSrc_enable(src);
            }
        }
    }

    IfxQspi_run(qspiSFR);
}


void IfxQspi_SpiMaster_initModuleConfig(IfxQspi_SpiMaster_Config *config, Ifx_QSPI *qspi)
{
    SpiIf_initConfig(&config->base);
    config->qspi                       = qspi;
    config->allowSleepMode             = FALSE;
    config->pauseOnBaudrateSpikeErrors = FALSE,
    config->pauseRunTransition         = IfxQspi_PauseRunTransition_pause;
    config->txFifoThreshold            = IfxQspi_TxFifoInt_1;
    config->rxFifoThreshold            = IfxQspi_RxFifoInt_0;
    config->txFifoMode                 = IfxQspi_FifoMode_combinedMove;
    config->rxFifoMode                 = IfxQspi_FifoMode_combinedMove;
    config->pins                       = NULL_PTR;
    config->dma.rxDmaChannelId         = IfxDma_ChannelId_none;
    config->dma.txDmaChannelId         = IfxDma_ChannelId_none;
    config->dma.useDma                 = FALSE;
}


void IfxQspi_SpiMaster_isrDmaReceive(IfxQspi_SpiMaster *qspiHandle)
{
    Ifx_DMA                   *dmaSFR         = &MODULE_DMA;
    IfxDma_ChannelId           rxDmaChannelId = qspiHandle->dma.rxDmaChannelId;
    IfxQspi_SpiMaster_Channel *chHandle       = IfxQspi_SpiMaster_activeChannel(qspiHandle);

    if (IfxDma_getAndClearChannelInterrupt(dmaSFR, rxDmaChannelId))
    {
        if (chHandle->deactivateSlso != NULL_PTR)
        {
            chHandle->deactivateSlso(chHandle);
        }

        chHandle->base.flags.onTransfer = 0;
        IfxQspi_SpiMaster_unlock((IfxQspi_SpiMaster *)chHandle->base.driver);
    }

    IfxDma_getAndClearChannelPatternDetectionInterrupt(dmaSFR, rxDmaChannelId);
}


void IfxQspi_SpiMaster_isrDmaTransmit(IfxQspi_SpiMaster *qspiHandle)
{
    IfxQspi_SpiMaster_Channel *chHandle       = IfxQspi_SpiMaster_activeChannel(qspiHandle);
    Ifx_DMA                   *dmaSFR         = &MODULE_DMA;
    IfxDma_ChannelId           txDmaChannelId = qspiHandle->dma.txDmaChannelId;
    Ifx_QSPI                  *qspiSFR        = qspiHandle->qspi;
    SpiIf_Job                 *job            = &chHandle->base.tx;

    if (IfxDma_getAndClearChannelPatternDetectionInterrupt(dmaSFR, txDmaChannelId))
    {
        // DMA_TC.031 workaround ..
        IfxDma_getAndClearChannelInterrupt(dmaSFR, txDmaChannelId);
    }
    else if ((chHandle->mode == IfxQspi_SpiMaster_Mode_long) ||
             (chHandle->mode == IfxQspi_SpiMaster_Mode_longContinuous))
    {
        IfxDma_getAndClearChannelInterrupt(dmaSFR, txDmaChannelId);
        IfxDma_disableChannelTransaction(dmaSFR, txDmaChannelId);
    }
    else if (chHandle->mode == IfxQspi_SpiMaster_Mode_xxl)
    {
        IfxDma_getAndClearChannelInterrupt(dmaSFR, txDmaChannelId);
        IfxDma_disableChannelTransaction(dmaSFR, txDmaChannelId);
    }
    else if (IfxDma_getAndClearChannelInterrupt(dmaSFR, txDmaChannelId) && (job->remaining > 1))
    {
        IfxDma_clearChannelInterrupt(dmaSFR, txDmaChannelId);
        IfxDma_disableChannelTransaction(dmaSFR, txDmaChannelId);

        if (job->data == NULL_PTR)
        {
            IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
            IfxQspi_writeTransmitFifo(qspiSFR, ~0);
        }
        else
        {
            IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);

            if (chHandle->dataWidth <= 8)
            {
                IfxQspi_writeTransmitFifo(qspiSFR, ((uint8 *)job->data)[job->remaining - 1]);
            }
            else if (chHandle->dataWidth <= 16)
            {
                IfxQspi_writeTransmitFifo(qspiSFR, ((uint16 *)job->data)[job->remaining - 1]);
            }
            else
            {
                IfxQspi_writeTransmitFifo(qspiSFR, ((uint32 *)job->data)[job->remaining - 1]);
            }
        }
    }
}


void IfxQspi_SpiMaster_isrError(IfxQspi_SpiMaster *handle)
{
    Ifx_QSPI                  *qspiSFR    = handle->qspi;
    uint16                     errorFlags = IfxQspi_getErrorFlags(qspiSFR);
    IfxQspi_clearAllEventFlags(qspiSFR);
    IfxQspi_SpiMaster_Channel *chHandle   = IfxQspi_SpiMaster_activeChannel(handle);
    Ifx_DMA                   *dmaSFR     = &MODULE_DMA;

    /* store all the flags in the variable */

    if ((errorFlags & IfxQspi_Error_parity) == 1)
    {
        chHandle->errorFlags.parityError = 1;
    }

    if ((errorFlags & IfxQspi_Error_configuration) == 1)
    {
        chHandle->errorFlags.configurationError = 1;
    }

    if ((errorFlags & IfxQspi_Error_baudrate) == 1)
    {
        chHandle->errorFlags.baudrateError = 1;
    }

    if ((errorFlags & IfxQspi_Error_expectTimeout) == 1)
    {
        chHandle->errorFlags.expectTimeoutError = 1;
    }

    if ((errorFlags & IfxQspi_Error_txfifoOverflow) == 1)
    {
        chHandle->errorFlags.txFifoOverflowError = 1;
    }

    if ((errorFlags & IfxQspi_Error_txfifoUnderflow) == 1)
    {
        chHandle->errorFlags.txFifoUnderflowError = 1;
    }

    if ((errorFlags & IfxQspi_Error_rxfifoOverflow) == 1)
    {
        chHandle->errorFlags.rxFifoOverflowError = 1;
    }

    if ((errorFlags & IfxQspi_Error_rxfifoUnderflow) == 1)
    {
        chHandle->errorFlags.rxFifoUnderflowError = 1;
    }

    if (errorFlags)
    {
        if (chHandle->deactivateSlso != NULL_PTR)
        {
            chHandle->deactivateSlso(chHandle);
        }

        chHandle->base.flags.onTransfer = 0;
        IfxQspi_SpiMaster_unlock((IfxQspi_SpiMaster *)chHandle->base.driver);
    }

    if (handle->dma.useDma)
    {
        IfxDma_getAndClearChannelInterrupt(dmaSFR, handle->dma.rxDmaChannelId);
        IfxDma_getAndClearChannelInterrupt(dmaSFR, handle->dma.txDmaChannelId);
    }
}


IfxQspi_PhaseTransitionEvent IfxQspi_SpiMaster_isrPhaseTransition(IfxQspi_SpiMaster *handle)
{
    Ifx_QSPI                    *qspiSFR = handle->qspi;
    IfxQspi_PhaseTransitionEvent ptEvent = 0;

    if (qspiSFR->STATUS.B.PT1F)
    {
        qspiSFR->FLAGSCLEAR.B.PT1C = 1;
        ptEvent                    = qspiSFR->GLOBALCON1.B.PT1; //
    }
    else if (qspiSFR->STATUS.B.PT2F)
    {
        qspiSFR->FLAGSCLEAR.B.PT2C = 1;
        ptEvent                    = qspiSFR->GLOBALCON1.B.PT2; //
    }

    return ptEvent;
}


void IfxQspi_SpiMaster_isrReceive(IfxQspi_SpiMaster *handle)
{
    IfxQspi_SpiMaster_Channel *chHandle = IfxQspi_SpiMaster_activeChannel(handle);
    chHandle->base.rxHandler(&chHandle->base);
    handle->base.rxCount++;
}


void IfxQspi_SpiMaster_isrTransmit(IfxQspi_SpiMaster *handle)
{
    IfxQspi_SpiMaster_Channel *chHandle = IfxQspi_SpiMaster_activeChannel(handle);
    chHandle->base.txHandler(&chHandle->base);
    handle->base.txCount++;
}


IfxQspi_PhaseTransitionEvent IfxQspi_SpiMaster_isrUserDefined(IfxQspi_SpiMaster *handle)
{
    Ifx_QSPI                    *qspiSFR = handle->qspi;
    IfxQspi_PhaseTransitionEvent ptEvent = 0;

    if (qspiSFR->STATUS.B.USRF)
    {
        qspiSFR->FLAGSCLEAR.B.USRC = 1;
        ptEvent                    = qspiSFR->GLOBALCON1.B.PT1; //
    }

    return ptEvent;
}


IFX_STATIC SpiIf_Status IfxQspi_SpiMaster_lock(IfxQspi_SpiMaster *handle)
{
    sint32 sending = __swap((void *)&handle->base.sending, 1UL);
    return (sending == 0) ? SpiIf_Status_ok : SpiIf_Status_busy;
}


void IfxQspi_SpiMaster_packLongModeBuffer(IfxQspi_SpiMaster_Channel *chHandle, void *data, uint32 *longFifoBuffer, Ifx_SizeT dataLength)
{
    int     i;
    boolean isFirst = 0;
    uint8  *src     = (uint8 *)data;
    uint32  baconDL;

    baconDL = 16;

    if (chHandle->mode == IfxQspi_SpiMaster_Mode_longContinuous)
    {
        chHandle->bacon.B.BYTE = 1;
        chHandle->bacon.B.LAST = 0;
    }
    else if (chHandle->mode == IfxQspi_SpiMaster_Mode_long)
    {
        chHandle->bacon.B.BYTE = 1;
        chHandle->bacon.B.LAST = 1;
    }
    else
    {
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, IFX_ASSERT_FEATURE_NOT_IMPLEMENTED);
    }

    while (dataLength > 0)
    {
        if (dataLength <= 16)
        {
            baconDL                = dataLength;
            chHandle->bacon.B.LAST = 1;
        }

        dataLength -= (Ifx_SizeT)baconDL;

        /* FILL BACON */
        if (isFirst == 0)
        {
            isFirst = 1;
        }
        else
        {
            chHandle->bacon.B.DL = baconDL - 1;
            *longFifoBuffer      = chHandle->bacon.U;
            longFifoBuffer++;
        }

        for (i = 0; i < baconDL / 4; i++)
        {
            *longFifoBuffer = *((uint32 *)src);
            longFifoBuffer++;
            src            += 4;
        }

        /* Copy Last bytes */
        switch (baconDL % 4)
        {
        case 1:
            *longFifoBuffer = *src;
            break;
        case 2:
            *longFifoBuffer = *src | (*(src + 1) << 8);
            break;
        case 3:
            *longFifoBuffer = *src | (*(src + 1) << 8) | (*(src + 2) << 16);
            break;
        }
    }
}


IFX_STATIC void IfxQspi_SpiMaster_read(IfxQspi_SpiMaster_Channel *chHandle)
{
    IfxQspi_SpiMaster *handle  = chHandle->base.driver->driver;
    Ifx_QSPI          *qspiSFR = handle->qspi;
    SpiIf_Job         *job     = &chHandle->base.rx;

    Ifx_SizeT          count   = (Ifx_SizeT)IfxQspi_getReceiveFifoLevel(qspiSFR);
    count = __min(job->remaining, count);

    if (job->data == NULL_PTR)
    {
        // no data should be buffered: do dummy reads
        int i;

        for (i = 0; i < count; ++i)
        {
            IfxQspi_readReceiveFifo(qspiSFR);
        }
    }
    else
    {
        if (chHandle->dataWidth <= 8)
        {
            IfxQspi_read8(qspiSFR, job->data, count);
            job->data = &(((uint8 *)job->data)[count]);
        }
        else if (chHandle->dataWidth <= 16)
        {
            IfxQspi_read16(qspiSFR, job->data, count);
            job->data = &(((uint16 *)job->data)[count]);
        }
        else
        {
            IfxQspi_read32(qspiSFR, job->data, count);
            job->data = &(((uint32 *)job->data)[count]);
        }
    }

    job->remaining = job->remaining - count;

    if (job->remaining == 0)
    {
        if (chHandle->deactivateSlso != NULL_PTR)
        {
            chHandle->deactivateSlso(chHandle);
        }

        chHandle->base.flags.onTransfer = 0;
        IfxQspi_SpiMaster_unlock((IfxQspi_SpiMaster *)chHandle->base.driver);
    }
}


SpiIf_Status IfxQspi_SpiMaster_setChannelBaudrate(IfxQspi_SpiMaster_Channel *chHandle, float32 baudrate)
{
    {
        IfxQspi_SpiMaster *handle  = (IfxQspi_SpiMaster *)chHandle->base.driver->driver;
        Ifx_QSPI          *qspiSFR = handle->qspi;
        SpiIf_ChConfig     chConfig;
        chConfig                = IfxQspi_SpiMaster_getChannelConfig(chHandle);
        chConfig.baudrate       = baudrate;
        uint8              cs = chHandle->channelId % 8;
        qspiSFR->ECON[cs].U     = IfxQspi_calculateExtendedConfigurationValue(qspiSFR, cs, &chConfig);
        chHandle->bacon.U       = IfxQspi_calculateBasicConfigurationValue(qspiSFR, chHandle->channelId, &chConfig.mode, chConfig.baudrate);
        chHandle->base.baudrate = IfxQspi_calcRealBaudrate(qspiSFR, cs);
        return SpiIf_Status_ok;
    }
}


IFX_STATIC void IfxQspi_SpiMaster_unlock(IfxQspi_SpiMaster *handle)
{
    handle->base.sending = 0UL;
}


IFX_STATIC void IfxQspi_SpiMaster_write(IfxQspi_SpiMaster_Channel *chHandle)
{
    SpiIf_Job         *job    = &chHandle->base.tx;
    IfxQspi_SpiMaster *handle = chHandle->base.driver->driver;

    if (handle->dma.useDma)
    {
        Ifx_DMA               *dmaSFR         = &MODULE_DMA;

        Ifx_QSPI              *qspiSFR        = handle->qspi;
        volatile Ifx_SRC_SRCR *src            = IfxQspi_getTransmitSrc(qspiSFR);

        IfxDma_ChannelId       txDmaChannelId = handle->dma.txDmaChannelId;
        IfxDma_ChannelId       rxDmaChannelId = handle->dma.rxDmaChannelId;

        boolean                interruptState = IfxCpu_disableInterrupts();

        if (job->remaining > 1)
        {
            IfxDma_setChannelTransferCount(dmaSFR, txDmaChannelId, job->remaining - 1);

            if (chHandle->dataWidth <= 8)
            {
                IfxDma_setChannelMoveSize(dmaSFR, txDmaChannelId, IfxDma_ChannelMoveSize_8bit);
            }
            else if (chHandle->dataWidth <= 16)
            {
                IfxDma_setChannelMoveSize(dmaSFR, txDmaChannelId, IfxDma_ChannelMoveSize_16bit);
            }
            else
            {
                IfxDma_setChannelMoveSize(dmaSFR, txDmaChannelId, IfxDma_ChannelMoveSize_32bit);
            }

            if (job->data == NULL_PTR)
            {
                IfxDma_setChannelSourceAddress(dmaSFR, txDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &IfxQspi_SpiMaster_dummyTxValue));
                IfxDma_setChannelSourceIncrementStep(dmaSFR, txDmaChannelId, IfxDma_ChannelIncrementStep_1,
                    IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_4);
                /* need to enable circular buffering to avoid increment higher than 4 bytes */
                /* we must do this direct why we don't have function for this */
                dmaSFR->CH[txDmaChannelId].ADICR.B.SCBE = TRUE;
            }
            else
            {
                IfxDma_setChannelSourceAddress(dmaSFR, txDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), job->data));
                IfxDma_setChannelSourceIncrementStep(dmaSFR, txDmaChannelId, IfxDma_ChannelIncrementStep_1,
                    IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);
                /* maybe circular buffering was enabled by other call, we disable the circular buffering */
                /* we must do this direct why we don't have function for this */
                dmaSFR->CH[txDmaChannelId].ADICR.B.SCBE = FALSE;
            }

            IfxDma_setChannelDestinationAddress(dmaSFR, txDmaChannelId, (void *)&qspiSFR->DATAENTRY[0].U);
            IfxDma_setChannelDestinationIncrementStep(dmaSFR, txDmaChannelId, IfxDma_ChannelIncrementStep_1,
                IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);

            IfxDma_clearChannelInterrupt(dmaSFR, txDmaChannelId);
        }

        /* Receive config */
        IfxDma_setChannelTransferCount(dmaSFR, rxDmaChannelId, job->remaining);

        if (chHandle->dataWidth <= 8)
        {
            IfxDma_setChannelMoveSize(dmaSFR, rxDmaChannelId, IfxDma_ChannelMoveSize_8bit);
        }
        else if (chHandle->dataWidth <= 16)
        {
            IfxDma_setChannelMoveSize(dmaSFR, rxDmaChannelId, IfxDma_ChannelMoveSize_16bit);
        }
        else
        {
            IfxDma_setChannelMoveSize(dmaSFR, rxDmaChannelId, IfxDma_ChannelMoveSize_32bit);
        }

        if (chHandle->base.rx.data == NULL_PTR)
        {
            IfxDma_setChannelDestinationAddress(dmaSFR, rxDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &IfxQspi_SpiMaster_dummyRxValue));
            IfxDma_setChannelDestinationIncrementStep(dmaSFR, rxDmaChannelId, IfxDma_ChannelIncrementStep_1,
                IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_4);
            /* need to enable circular buffering to avoid increment higher than 4 bytes */
            /* we must do this direct why we don't have function for this */
            dmaSFR->CH[rxDmaChannelId].ADICR.B.DCBE = TRUE;
        }
        else
        {
            IfxDma_setChannelDestinationAddress(dmaSFR, rxDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), chHandle->base.rx.data));
            IfxDma_setChannelDestinationIncrementStep(dmaSFR, rxDmaChannelId, IfxDma_ChannelIncrementStep_1,
                IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);
            /* maybe circular buffering was enabled by other call, we disable the circular buffering */
            /* we must do this direct why we don't have function for this */
            dmaSFR->CH[rxDmaChannelId].ADICR.B.DCBE = FALSE;
        }

        IfxDma_clearChannelInterrupt(dmaSFR, rxDmaChannelId);
        IfxQspi_clearAllEventFlags(qspiSFR);
        src = IfxQspi_getTransmitSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        src = IfxQspi_getReceiveSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        src = IfxQspi_getErrorSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        IfxDma_clearChannelInterrupt(dmaSFR, rxDmaChannelId);
        IfxDma_enableChannelTransaction(dmaSFR, rxDmaChannelId);

        if (job->remaining > 1)
        {
            IfxDma_clearChannelInterrupt(dmaSFR, txDmaChannelId);
            IfxDma_enableChannelTransaction(dmaSFR, txDmaChannelId);

            if (chHandle->channelBasedCs == IfxQspi_SpiMaster_ChannelBasedCs_disabled)
            {
                IfxQspi_writeBasicConfigurationBeginStream(qspiSFR, chHandle->bacon.U);
            }
            else
            {
                IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
            }
        }
        else
        {
            if (job->data == NULL_PTR)
            {
                IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                IfxQspi_writeTransmitFifo(qspiSFR, ~0);
            }
            else
            {
                IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);

                if (chHandle->dataWidth <= 8)
                {
                    IfxQspi_writeTransmitFifo(qspiSFR, ((uint8 *)job->data)[job->remaining - 1]);
                }
                else if (chHandle->dataWidth <= 16)
                {
                    IfxQspi_writeTransmitFifo(qspiSFR, ((uint16 *)job->data)[job->remaining - 1]);
                }
                else
                {
                    IfxQspi_writeTransmitFifo(qspiSFR, ((uint32 *)job->data)[job->remaining - 1]);
                }
            }
        }

        IfxCpu_restoreInterrupts(interruptState);
    }
    else
    {
        if (job->remaining > 0)
        {
            IfxQspi_SpiMaster *handle  = chHandle->base.driver->driver;
            Ifx_QSPI          *qspiSFR = handle->qspi;
            uint8              cs      = chHandle->bacon.B.CS;

            // following operation must be atomic (FIXME actually, we would only have to stall the Tx interrupt)
            boolean            interruptState = IfxCpu_disableInterrupts();
            Ifx_SizeT          count          = (Ifx_SizeT)(IFXQSPI_HWFIFO_DEPTH - 1 - IfxQspi_getTransmitFifoLevel(qspiSFR)); // -1, since BACON allocates one FIFO entry
            count = __min(job->remaining, count);

            if (count > 0)
            {
                job->remaining = job->remaining - count;

                // push BACON into FIFO before first data word
                if (chHandle->firstWrite == TRUE)
                {
                    chHandle->firstWrite = FALSE;

                    if (chHandle->channelBasedCs == IfxQspi_SpiMaster_ChannelBasedCs_disabled)
                    {
                        IfxQspi_writeBasicConfigurationBeginStream(qspiSFR, chHandle->bacon.U);
                    }
                    else
                    {
                        IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                    }
                }

                // we have to push another BACON into FIFO before the last data word
                boolean lastWrite = job->remaining == 0;

                if (job->data == NULL_PTR)
                {
                    // no data should be sent (only received): send all-1
                    int i;

                    if (lastWrite)
                    {
                        for (i = 0; i < count - 1; ++i)
                        {
                            IfxQspi_writeTransmitFifo(qspiSFR, ~0);
                        }

                        IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                        IfxQspi_writeTransmitFifo(qspiSFR, ~0);
                    }
                    else
                    {
                        for (i = 0; i < count; ++i)
                        {
                            IfxQspi_writeTransmitFifo(qspiSFR, ~0);
                        }
                    }
                }
                else
                {
                    if (chHandle->dataWidth <= 8)
                    {
                        if (lastWrite)
                        {
                            if (count >= 2)
                            {
                                IfxQspi_write8(qspiSFR, cs, job->data, count - 1);
                            }

                            IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                            IfxQspi_writeTransmitFifo(qspiSFR, ((uint8 *)job->data)[count - 1]);
                        }
                        else
                        {
                            IfxQspi_write8(qspiSFR, cs, job->data, count);
                        }

                        job->data = &(((uint8 *)job->data)[count]);
                    }
                    else if (chHandle->dataWidth <= 16)
                    {
                        if (lastWrite)
                        {
                            if (count >= 2)
                            {
                                IfxQspi_write16(qspiSFR, cs, job->data, count - 1);
                            }

                            IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                            IfxQspi_writeTransmitFifo(qspiSFR, ((uint16 *)job->data)[count - 1]);
                        }
                        else
                        {
                            IfxQspi_write16(qspiSFR, cs, job->data, count);
                            job->data = &(((uint16 *)job->data)[count]);
                        }
                    }
                    else
                    {
                        if (lastWrite)
                        {
                            if (count >= 2)
                            {
                                IfxQspi_write32(qspiSFR, cs, job->data, count - 1);
                            }

                            IfxQspi_writeBasicConfigurationEndStream(qspiSFR, chHandle->bacon.U);
                            IfxQspi_writeTransmitFifo(qspiSFR, ((uint32 *)job->data)[count - 1]);
                        }
                        else
                        {
                            IfxQspi_write32(qspiSFR, cs, job->data, count);
                            job->data = &(((uint32 *)job->data)[count]);
                        }
                    }
                }
            }

            IfxCpu_restoreInterrupts(interruptState);
        }
    }
}


IFX_STATIC void IfxQspi_SpiMaster_writeLong(IfxQspi_SpiMaster_Channel *chHandle)
{
    SpiIf_Job         *job      = &chHandle->base.tx;
    IfxQspi_SpiMaster *handle   = chHandle->base.driver->driver;
    uint8              fifosize = IFXQSPI_FIFO32BITSIZE(job->remaining);

    if (chHandle->mode != IfxQspi_SpiMaster_Mode_xxl)
    {
        fifosize = fifosize + IFXQSPI_BACONSIZE(job->remaining) - 1;       // combining this line and above doesn't work
    }

    if (handle->dma.useDma)
    {
        Ifx_DMA               *dmaSFR         = &MODULE_DMA;

        Ifx_QSPI              *qspiSFR        = handle->qspi;
        volatile Ifx_SRC_SRCR *src            = IfxQspi_getTransmitSrc(qspiSFR);

        IfxDma_ChannelId       txDmaChannelId = handle->dma.txDmaChannelId;
        IfxDma_ChannelId       rxDmaChannelId = handle->dma.rxDmaChannelId;

        boolean                interruptState = IfxCpu_disableInterrupts();

        {
            IfxDma_setChannelTransferCount(dmaSFR, txDmaChannelId, fifosize);

            IfxDma_setChannelMoveSize(dmaSFR, txDmaChannelId, IfxDma_ChannelMoveSize_32bit);

            {
                IfxDma_setChannelSourceAddress(dmaSFR, txDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), job->data));
                IfxDma_setChannelSourceIncrementStep(dmaSFR, txDmaChannelId, IfxDma_ChannelIncrementStep_1,
                    IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);
                /* maybe circular buffering was enabled by other call, we disable the circular buffering */
                /* we must do this direct why we don't have function for this */
                dmaSFR->CH[txDmaChannelId].ADICR.B.SCBE = FALSE;

                if (chHandle->mode != IfxQspi_SpiMaster_Mode_xxl)
                {
                    IfxDma_setChannelDestinationAddress(dmaSFR, txDmaChannelId, (uint32 *)&qspiSFR->MIXENTRY.U);
                    IfxDma_setChannelDestinationIncrementStep(dmaSFR, txDmaChannelId, IfxDma_ChannelIncrementStep_1,
                        IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);
                }
            }

            IfxDma_clearChannelInterrupt(dmaSFR, txDmaChannelId);
        }

        /* Receive config */
        IfxDma_setChannelTransferCount(dmaSFR, rxDmaChannelId, IFXQSPI_FIFO32BITSIZE(job->remaining));
        IfxDma_setChannelMoveSize(dmaSFR, rxDmaChannelId, IfxDma_ChannelMoveSize_32bit);

        if (chHandle->base.rx.data == NULL_PTR)
        {
            IfxDma_setChannelDestinationAddress(dmaSFR, rxDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &IfxQspi_SpiMaster_dummyRxValue));
            IfxDma_setChannelDestinationIncrementStep(dmaSFR, rxDmaChannelId, IfxDma_ChannelIncrementStep_1,
                IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_4);
            /* need to enable circular buffering to avoid increment higher than 4 bytes */
            /* we must do this direct why we don't have function for this */
            dmaSFR->CH[rxDmaChannelId].ADICR.B.DCBE = TRUE;
        }
        else
        {
            IfxDma_setChannelDestinationAddress(dmaSFR, rxDmaChannelId, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), chHandle->base.rx.data));
            IfxDma_setChannelDestinationIncrementStep(dmaSFR, rxDmaChannelId, IfxDma_ChannelIncrementStep_1,
                IfxDma_ChannelIncrementDirection_positive, IfxDma_ChannelIncrementCircular_none);
            /* maybe circular buffering was enabled by other call, we disable the circular buffering */
            /* we must do this direct why we don't have function for this */
            dmaSFR->CH[rxDmaChannelId].ADICR.B.DCBE = FALSE;
        }

        IfxDma_clearChannelInterrupt(dmaSFR, rxDmaChannelId);
        IfxQspi_clearAllEventFlags(qspiSFR);
        src = IfxQspi_getTransmitSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        src = IfxQspi_getReceiveSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        src = IfxQspi_getErrorSrc(qspiSFR);
        IfxSrc_clearRequest(src);
        IfxDma_clearChannelInterrupt(dmaSFR, rxDmaChannelId);
        IfxDma_enableChannelTransaction(dmaSFR, rxDmaChannelId);

        if (chHandle->mode == IfxQspi_SpiMaster_Mode_longContinuous)
        {
            (job->remaining >= 16) ? (chHandle->bacon.B.DL = 16 - 1) : (chHandle->bacon.B.DL = job->remaining - 1);
            (job->remaining >= 16) ? (chHandle->bacon.B.LAST = 0) : (chHandle->bacon.B.LAST = 1);
            chHandle->bacon.B.BYTE = 1;
        }
        else if (chHandle->mode == IfxQspi_SpiMaster_Mode_long)
        {
            (job->remaining >= 16) ? (chHandle->bacon.B.DL = 16 - 1) : (chHandle->bacon.B.DL = job->remaining - 1);
            chHandle->bacon.B.LAST = 1;
            chHandle->bacon.B.BYTE = 1;
        }
        else
        {
            chHandle->bacon.B.LAST = 1;
            chHandle->bacon.B.BYTE = 1;
            chHandle->bacon.B.DL   = 0;
        }

        {
            IfxDma_clearChannelInterrupt(dmaSFR, txDmaChannelId);
            IfxDma_enableChannelTransaction(dmaSFR, txDmaChannelId);
        }

        if (chHandle->mode != IfxQspi_SpiMaster_Mode_xxl)
        {
            qspiSFR->MIXENTRY.U = chHandle->bacon.U;
        }
        else
        {
            qspiSFR->BACONENTRY.U = chHandle->bacon.U;
        }

        IfxCpu_restoreInterrupts(interruptState);
    }
    else
    {
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, IFX_ASSERT_FEATURE_NOT_IMPLEMENTED);
    }
}
