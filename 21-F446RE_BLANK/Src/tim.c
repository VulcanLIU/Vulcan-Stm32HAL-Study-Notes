#include "tim.h"

void TIM8_OC_Init(void)
{
    //GPIO使能
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Alternate = LL_GPIO_AF_3;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    //开GPIO时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    //开时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);

    //设置时钟源
    LL_TIM_SetClockSource(TIM8, LL_TIM_CLOCKSOURCE_INTERNAL);

    //设置分频器
    LL_TIM_SetPrescaler(TIM8, 90-1);
    //设置自动重装载值
    LL_TIM_SetAutoReload(TIM8, 2000-1);
    //使能自动重载预装载
    LL_TIM_EnableARRPreload(TIM8);
    //设置计数方式
    LL_TIM_SetCounterMode(TIM8, LL_TIM_COUNTERMODE_UP);
    //设置重复计数器
    LL_TIM_SetRepetitionCounter(TIM8, 0);

    //设置CH1比较值
    LL_TIM_OC_SetCompareCH1(TIM8, 20);
    //设置捕获/比较通道模式
    LL_TIM_OC_SetMode(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    //使能CH1比较值预装载
    LL_TIM_OC_EnablePreload(TIM8, LL_TIM_CHANNEL_CH1);
    //设置输出极性
    LL_TIM_OC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH1N, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
    //使能主输出
    LL_TIM_EnableAllOutputs(TIM8);
    //使能通道输出
    LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM8, LL_TIM_CHANNEL_CH1N);

    //启动TIM8
    LL_TIM_EnableCounter(TIM8);
}