#include "tim.h"

void MX_TIM1_Init(void)
{
    //
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

    //开时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    
    //初始化时基单元
    //时钟源
    LL_TIM_SetClockSource(TIM1,LL_TIM_CLOCKSOURCE_INTERNAL);

    //配置CR1寄存器
    LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERDIRECTION_UP);

    //时基单元三寄存器
    LL_TIM_SetAutoReload(TIM1,1000);
    LL_TIM_SetRepetitionCounter(TIM1,1);
    LL_TIM_SetPrescaler(TIM1,180);
    
    //生成更新事件使三寄存器值进入影子寄存器中
    LL_TIM_GenerateEvent_UPDATE(TIM1);

    //使能ARR预装载
    LL_TIM_EnableARRPreload(TIM1);
    
    //中断
    LL_TIM_EnableIT_UPDATE(TIM1);
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 1));

    //开始计数
    LL_TIM_EnableCounter(TIM1);
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    if(LL_TIM_IsActiveFlag_UPDATE(TIM1))
    {
        a++;
    }
}