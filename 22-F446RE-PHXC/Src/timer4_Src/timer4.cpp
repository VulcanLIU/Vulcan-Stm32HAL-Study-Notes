#include "timer4.h"

Timer4 timer4;

Timer4::Timer4(/* args */)
{
}

Timer4::~Timer4()
{
}

void Timer4::init()
{
    //开外设时钟
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

    //配置外设
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Autoreload = 99;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Prescaler = 45;
    LL_TIM_Init(TIM4, &TIM_InitStruct);

    //开启中断
    LL_TIM_EnableIT_UPDATE(TIM4);
    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, NVIC_EncodePriority(0, 2, 1));
}

void Timer4::attachInterrupt(void (*userFunc)(void))
{
    this->intFunc = userFunc;
}

void Timer4::begin()
{
    LL_TIM_EnableCounter(TIM4);
}

void TIM4_IRQHandler()
{
    timer4.intFunc();
    LL_TIM_ClearFlag_UPDATE(TIM4);
}

void nothing() {}