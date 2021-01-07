#ifndef __BLINK_H
#define __BLINK_H

#include "stm32f4xx.h"
#include "peripheral.h"

#ifdef __cplusplus
extern "C"
{
#endif
    void TIM1_BRK_TIM9_IRQHandler(void);

    class Blink
    {
    private:
        /* data */
        void TIM_init();
        void GPIO_init();

    public:
        Blink(void);
        ~Blink();
        void init();
        void begin();
    };

#ifdef __cplusplus
}
#endif
extern Blink blink;

#endif