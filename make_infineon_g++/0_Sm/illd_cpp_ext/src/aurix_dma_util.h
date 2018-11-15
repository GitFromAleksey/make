#if !defined(DEBUG_DMA_H_)
#	define DEBUG_DMA_H_

#include "IfxDma_Dma.h"

#include "aurix_gpio.h"


class DmaRegSet
{
public:
    void init(IfxDma_ChannelId dmaChN, u32 addr, u32 v)
    {
        regValue = v;
        IfxDma_Dma_Config dmaConfig;
        IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);
        // initialize module
        IfxDma_Dma dma;
        IfxDma_Dma_initModule(&dma, &dmaConfig);

        // construct the channel configuration
        IfxDma_Dma_ChannelConfig config;
        IfxDma_Dma_initChannelConfig(&config, &dma);
        config.channelId = dmaChN;
        config.sourceAddress = reinterpret_cast<u32>(&regValue);
        config.destinationAddress = addr;
        //config.shadowAddress = config.sourceAddress;
        config.transferCount = 1;
        config.operationMode = IfxDma_ChannelOperationMode_continuous;
        config.moveSize = IfxDma_ChannelMoveSize_32bit;
        config.busPriority = IfxDma_ChannelBusPriority_high;
        config.hardwareRequestEnabled = true;
        config.sourceAddressCircularRange =
                IfxDma_ChannelIncrementCircular_none;
        config.destinationAddressCircularRange =
                IfxDma_ChannelIncrementCircular_none;
        //config.shadowControl = IfxDma_ChannelShadow_srcDirectWrite; //IfxDma_ChannelShadow_none;
        config.destinationCircularBufferEnabled = true;
        config.sourceCircularBufferEnabled = true;

        IfxDma_Dma_initChannel(&channel, &config);
    }
private:
    IfxDma_Dma_Channel channel;
    u32 regValue;
};


class DmaPinToggle :public DmaRegSet
{
public:
    void init(IfxDma_ChannelId dmaChN, Aurix::Gpio::Line *p)
    {
        static_cast<DmaRegSet *>(this)->init(
            dmaChN,
            reinterpret_cast<u32>(&p->portReg->OMR),
            (u32)IfxPort_State_toggled << p->pinIndex);
    }
};

//template<u8 size, typename T>
//class DmaDoubleBuffer
//{
//public:
//    T buf[2][size];
//    void init(IfxDma_ChannelId dmaChN, u32 src)
//    {
//        IfxDma_Dma_Config dmaConfig;
//        IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);
//        // initialize module
//        IfxDma_Dma dma;
//        IfxDma_Dma_initModule(&dma, &dmaConfig);
//
//        // construct the channel configuration
//        IfxDma_Dma_ChannelConfig config;
//        IfxDma_Dma_initChannelConfig(&config, &dma);
//        config.channelId = dmaChN;
//        config.sourceAddress = src;
//        config.destinationAddress = reinterpret_cast<u32>(&buf[0][0]);
//        config.shadowAddress = reinterpret_cast<u32>(&buf[1][0]);
//        config.transferCount = size;
//        config.operationMode = IfxDma_ChannelOperationMode_continuous;
//        config.moveSize = IfxDma_ChannelMoveSize_32bit;
//        config.busPriority = IfxDma_ChannelBusPriority_medium;
//        config.hardwareRequestEnabled = true;
//        config.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
//        config.shadowControl = IfxDma_ChannelShadow_doubleDestinationBufferingHwSwSwitch;
//        config.sourceCircularBufferEnabled = true;
//
//        IfxDma_Dma_initChannel(&ch, &config);
//    }
//    u8 redyBufferIndex()
//    {
//        Ifx_DMA_CH_CHCSR s;
//        s.U = ch.channel->CHCSR.U;
//        return s.B.TCOUNT ? !s.B.BUFFER : s.B.BUFFER;
//    }
//    void switchBuffer(u8 rb)
//    {
//        // переключение адресов происходит аппаратно
//        if (rb == 0)
//        {
//            ch.channel->DADR.U = reinterpret_cast<u32>(&buf[0][0]);
//        }
//        else
//        {
//            ch.channel->SHADR.U = reinterpret_cast<u32>(&buf[1][0]);
//        }
//        clearFrozen();
//    }
//    void switchBuffer()
//    {
//        u8 rb = redyBufferIndex();
//        switchBuffer(rb);
//    }
//    bool isFrozen()
//    {
//        return ch.channel->CHCSR.B.FROZEN;
//    }
//    void clearFrozen()
//    {
//        ch.channel->CHCSR.B.FROZEN = 0;
//    }
//    IfxDma_Dma_Channel ch;
//private:
//};

#endif  // DEBUG_DMA_H_
