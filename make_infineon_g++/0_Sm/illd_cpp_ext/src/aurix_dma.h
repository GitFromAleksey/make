#if !defined(AURIX_DMA_H_)
#define AURIX_DMA_H_

#include "IfxDma_Dma.h"
#include "types.h"

namespace Aurix
{
    namespace Dma
    {
        class Channel
        {
        public:
            Ifx_DMA *dma;
            IfxDma_ChannelId channelId;

            Channel(Ifx_DMA *p, IfxDma_ChannelId i) :
                    dma(p), channelId(i)
            {
            }

            bool isReset()
            {
                return static_cast<bool>(IfxDma_isChannelReset(dma, channelId));
            }

            void reset()
            {
                IfxDma_resetChannel(dma, channelId);
            }

            void clearTransactionRequestLost()
            {
                IfxDma_clearChannelTransactionRequestLost(dma, channelId);
            }

            void disableTransaction()
            {
                IfxDma_disableChannelTransaction(dma, channelId);
            }

            void disableTransactionLostError()
            {
                IfxDma_disableChannelTransactionLostError(dma, channelId);
            }

            void enableTransaction()
            {
                IfxDma_enableChannelTransaction(dma, channelId);
            }

            void enableTransactionLostError()
            {
                IfxDma_enableChannelTransactionLostError(dma, channelId);
            }

            bool getTransactionRequestLost()
            {
                return static_cast<bool>(IfxDma_getChannelTransactionRequestLost(
                        dma, channelId));
            }

            bool isTransactionEnabled()
            {
                return static_cast<bool>(IfxDma_isChannelTransactionEnabled(dma,
                        channelId));
            }

            bool isTransactionPending()
            {
                return static_cast<bool>(IfxDma_isChannelTransactionPending(dma,
                        channelId));
            }

            void startTransaction()
            {
                IfxDma_startChannelTransaction(dma, channelId);
            }

            u32 getDestinationAddress()
            {
                return IfxDma_getChannelDestinationAddress(dma, channelId);
            }

            u32 getSourceAddress()
            {
                return IfxDma_getChannelSourceAddress(dma, channelId);
            }

            u32 getTransferCount()
            {
                return IfxDma_getChannelTransferCount(dma, channelId);
            }

            void setBlockMode(IfxDma_ChannelMove blockMode)
            {
                IfxDma_setChannelBlockMode(dma, channelId, blockMode);
            }

            void setContinuousMode()
            {
                IfxDma_setChannelContinuousMode(dma, channelId);
            }

            void setDestinationAddress(void *address)
            {
                IfxDma_setChannelDestinationAddress(dma, channelId, address);
            }

            void setDestinationIncrementStep(
                    IfxDma_ChannelIncrementStep incStep,
                    IfxDma_ChannelIncrementDirection direction,
                    IfxDma_ChannelIncrementCircular size)
            {
                IfxDma_setChannelDestinationIncrementStep(dma, channelId,
                        incStep, direction, size);
            }

            void setMoveSize(IfxDma_ChannelMoveSize moveSize)
            {
                IfxDma_setChannelMoveSize(dma, channelId, moveSize);
            }

            void setShadow(IfxDma_ChannelShadow shadow)
            {
                IfxDma_setChannelShadow(dma, channelId, shadow);
            }

            void setSingleMode()
            {
                IfxDma_setChannelSingleMode(dma, channelId);
            }

            void setSingleTransaction()
            {
                IfxDma_setChannelSingleTransaction(dma, channelId);
            }

            void setSingleTransfer()
            {
                IfxDma_setChannelSingleTransfer(dma, channelId);
            }

            void setSourceAddress(const void *address)
            {
                IfxDma_setChannelSourceAddress(dma, channelId, address);
            }

            void setSourceIncrementStep(IfxDma_ChannelIncrementStep incStep,
                    IfxDma_ChannelIncrementDirection direction,
                    IfxDma_ChannelIncrementCircular size)
            {
                IfxDma_setChannelSourceIncrementStep(dma, channelId, incStep,
                        direction, size);
            }

            void setTransferCount(u32 transferCount)
            {
                IfxDma_setChannelTransferCount(dma, channelId, transferCount);
            }

            void writeShadowDisable()
            {
                IfxDma_writeChannelShadowDisable(dma, channelId);
            }

            void writeShadowEnable()
            {
                IfxDma_writeChannelShadowEnable(dma, channelId);
            }

            void clearHalt()
            {
                IfxDma_clearChannelHalt(dma, channelId);
            }

            bool getHalt()
            {
                return static_cast<bool>(IfxDma_getChannelHalt(dma, channelId));
            }

            void setHalt()
            {
                IfxDma_setChannelHalt(dma, channelId);
            }

            bool getDoubleBufferRead()
            {
                return static_cast<bool>(IfxDma_getDoubleBufferRead(dma,
                        channelId));
            }

            bool getDoubleBufferSelection()
            {
                return static_cast<bool>(IfxDma_getDoubleBufferSelection(dma,
                        channelId));
            }

            void keepDoubleBufferActive()
            {
                IfxDma_keepDoubleBufferActive(dma, channelId);
            }

            void switchDoubleBuffer()
            {
                IfxDma_switchDoubleBuffer(dma, channelId);
            }

            void clearInterrupt()
            {
                IfxDma_clearChannelInterrupt(dma, channelId);
            }

            void disableInterrupt()
            {
                IfxDma_disableChannelInterrupt(dma, channelId);
            }

            void enableInterrupt()
            {
                IfxDma_enableChannelInterrupt(dma, channelId);
            }

            bool getAndClearInterrupt()
            {
                return static_cast<bool>(IfxDma_getAndClearChannelInterrupt(dma,
                        channelId));
            }

            bool getAndClearPatternDetectionInterrupt()
            {
                return static_cast<bool>(IfxDma_getAndClearChannelPatternDetectionInterrupt(
                        dma, channelId));
            }

            bool getAndClearWrapDestinationBufferInterrupt()
            {
                return static_cast<bool>(IfxDma_getAndClearChannelWrapDestinationBufferInterrupt(
                        dma, channelId));
            }

            bool getAndClearWrapSourceBufferInterrupt()
            {
                return static_cast<bool>(IfxDma_getAndClearChannelWrapSourceBufferInterrupt(
                        dma, channelId));
            }

            bool getInterrupt()
            {
                return static_cast<bool>(IfxDma_getChannelInterrupt(dma,
                        channelId));
            }

            bool getPatternDetectionOldValue()
            {
                return static_cast<bool>(IfxDma_getChannelPatternDetectionOldValue(
                        dma, channelId));
            }

            volatile Ifx_SRC_SRCR *getSrcPointer()
            {
                return IfxDma_getSrcPointer(dma, channelId);
            }

            void setInterruptServiceRequest()
            {
                IfxDma_setChannelInterruptServiceRequest(dma, channelId);
            }
        };

        class Module
        {
        public:
            Ifx_DMA *dma;

            Module(Ifx_DMA *p) :
                    dma(p)
            {
            }

            static IfxDma_ChannelIncrementCircular getCircularRangeCode(
                    u16 range)
            {
                return IfxDma_getCircularRangeCode(range);
            }

            void setSleepMode(IfxDma_SleepMode mode)
            {
                IfxDma_setSleepMode(dma, mode);
            }

            void clearErrorFlags(u32 mask)
            {
                IfxDma_clearErrorFlags(dma, IfxDma_MoveEngine::IfxDma_MoveEngine_0, mask);
            }

            void disableMoveEngineDestinationError()
            {
                IfxDma_disableMoveEngineDestinationError(dma, IfxDma_MoveEngine::IfxDma_MoveEngine_0);
            }

            void disableMoveEngineSourceError()
            {
                IfxDma_disableMoveEngineSourceError(dma, IfxDma_MoveEngine::IfxDma_MoveEngine_0);
            }

            void enableMoveEngineDestinationError()
            {
                IfxDma_enableMoveEngineDestinationError(dma,
                        IfxDma_MoveEngine::IfxDma_MoveEngine_0);
            }

            void enableMoveEngineSourceError()
            {
                IfxDma_enableMoveEngineSourceError(dma, IfxDma_MoveEngine::IfxDma_MoveEngine_0);
            }

            u32 getErrorFlags()
            {
                return IfxDma_getErrorFlags(dma, IfxDma_MoveEngine::IfxDma_MoveEngine_0);
            }

            u32 IfxDma_getTimestamp()
            {
                return IfxDma_getTimestamp();
            }
        };

    }
}
#endif /* AURIX_DMA_H */
