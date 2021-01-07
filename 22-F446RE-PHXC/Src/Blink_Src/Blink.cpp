#include "Blink.h"

Blink blink;

Blink::Blink(void)
{
}

Blink::~Blink()
{
}

void Blink::init()
{
    //GPIO初始化
    GPIO_init();
    //TIM初始化
    TIM_init();
}

void Blink::begin()
{
    //启动定时器
    LL_TIM_EnableCounter(TIM9);
}

void Blink::TIM_init()
{
    //打开时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);

    //时基三单元
    LL_TIM_SetPrescaler(TIM9, 18000);
    LL_TIM_SetAutoReload(TIM9, 400);
    LL_TIM_SetCounterMode(TIM9, LL_TIM_COUNTERDIRECTION_UP);

    //使能自动重载预装载
    LL_TIM_EnableARRPreload(TIM9);

    //数据更新
    //LL_TIM_EnableUpdateEvent(TIM9);

    //使能中断
    LL_TIM_EnableIT_UPDATE(TIM9);
    HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 1, 1);
    NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
}

void Blink::GPIO_init()
{
    //开启时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    //配置GPIO
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    //写GPIO初始状态
    LL_GPIO_WriteOutputPort(GPIOC, LL_GPIO_PIN_0);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM9))
    {
        LL_GPIO_TogglePin(GPIOC, ~LL_GPIO_PIN_0);
        LL_TIM_ClearFlag_UPDATE(TIM9);
    }
}
