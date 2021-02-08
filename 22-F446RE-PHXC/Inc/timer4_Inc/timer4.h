#ifndef __TIMER4_H
#define __TIMER4_H

#include "peripheral.h"

typedef void (*voidFuncPtr)(void);

#ifdef __cplusplus
extern "C"
{
#endif

    void TIM4_IRQHandler();
    void nothing();

    class Timer4
    {
    private:
        
    public:
        volatile voidFuncPtr intFunc = nothing;
        Timer4(/* args */);
        ~Timer4();
        void init();
        void attachInterrupt(void (*userFunc)(void));
        void begin();
    };

    extern Timer4 timer4;

#ifdef __cplusplus
}
#endif

#endif