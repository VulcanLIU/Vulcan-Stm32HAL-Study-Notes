#ifndef __HC08_H
#define __HC08_H

#include "peripheral.h"

#define kp_buffer_header 0xA1
#define ki_buffer_header 0xA2
#define kd_buffer_header 0xA3
#define Target_Angle_buffer_header 0xA4 

#ifdef __cplusplus
extern "C"
{
#endif

    class HC08
    {
    private:
        /* data */
        uint8_t receive_buffer[3] = {0, 0, 0};
        float kp = 0;
        float ki = 0;
        float kd = 0;
        float Target_Angle = 0;

    public:
        HC08(/* args */);
        ~HC08();

        void begin();
        void USART_init();
        void gpio_init();
        void DMA_init();

        void send(float pitch, float speed);

        float getKp();
        float getKi();
        float getKd();
        float getTarget_Angle();

        void buffer_process();
    };

    void DMA1_Stream1_IRQHandler();

    extern HC08 hc08;

#ifdef __cplusplus
}
#endif

#endif