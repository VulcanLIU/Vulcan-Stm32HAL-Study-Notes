#ifndef __GY25_H
#define __GY25_H

#include "peripheral.h"
#include "RingBuffer.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void USART1_IRQHandler(void);

    class GY25
    {
    private:
        USART_TypeDef *USARTx;
        IRQn_Type USARTx_IRQn;

    public:
        float YPR[3];
        unsigned char Re_buf[8], counter = 0;
        unsigned char sign = 0;

        GY25(USART_TypeDef *USARTx, IRQn_Type USARTx_IRQn);
        ~GY25();
        void begin();
        void USART_begin();
        void USART_gpio_init();
        void USART_send(uint8_t data);
        void autoMode();
        void autoModeASCII();
        void singleMode();
        void correctPitchRow();
        void correctYaw();
        void refresh();
    };

    extern GY25 gy25;

#ifdef __cplusplus
}
#endif

#endif