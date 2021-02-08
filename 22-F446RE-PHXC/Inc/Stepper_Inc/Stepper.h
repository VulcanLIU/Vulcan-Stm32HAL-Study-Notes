#ifndef __STEPPER_H
#define __STEPPER_H

#include "peripheral.h"
#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

    enum DIRCTION
    {
        POS,
        INV
    };

    class Stepper
    {
    private:
        /* data */
        uint16_t TIMx_prescaler = 0;
        uint32_t TIMx_freq = 0;
        TIM_TypeDef *TIMx;
        uint32_t Channel;
        float speed;

    public:
        Stepper(TIM_TypeDef *TIMx, uint32_t Channel);
        ~Stepper();
        void init();
        void gpio_init();
        void begin();
        void stop();

        void setDirection(DIRCTION dir);
        void setFreq(uint16_t freq);
        void setSpeed(float speed);

        float getSpeed();
    };

    extern Stepper Stepper_left;
    extern Stepper Stepper_right;

#ifdef __cplusplus
}
#endif

#endif