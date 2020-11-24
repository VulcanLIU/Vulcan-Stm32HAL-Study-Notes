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
    LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);

    //配置CR1寄存器
    LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERDIRECTION_UP);

    //时基单元三寄存器
    LL_TIM_SetAutoReload(TIM1, 1000);
    LL_TIM_SetRepetitionCounter(TIM1, 1);
    LL_TIM_SetPrescaler(TIM1, 180);

    //生成更新事件使三寄存器值进入影子寄存器中
    LL_TIM_GenerateEvent_UPDATE(TIM1);

    //使能ARR预装载
    LL_TIM_EnableARRPreload(TIM1);

    //中断
    LL_TIM_EnableIT_UPDATE(TIM1);
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 1));
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    //开始计数
    LL_TIM_EnableCounter(TIM1);
}

void MX_TIM1_OC_Init(void)
{
    // LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};
    // //开启外设时钟
    // LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

    // //选择时钟源
    // LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);

    // //赋值控制器
    // LL_TIM_EnableARRPreload(TIM1);
    // LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERDIRECTION_UP);

    // //赋值时基单元
    // LL_TIM_SetPrescaler(TIM1, 180);
    // LL_TIM_SetAutoReload(TIM1, 1000);
    // LL_TIM_SetRepetitionCounter(TIM1, 1);

    // //生成更新事件使三寄存器值进入影子寄存器中
    // LL_TIM_GenerateEvent_UPDATE(TIM1);

    // //初始化比较匹配单元
    // LL_TIM_OC_SetMode(TIM1, TIM_CHANNEL_1, LL_TIM_OCMODE_TOGGLE);
    // LL_TIM_OC_SetCompareCH1(TIM1, 300);                                        //设置通道1比较值
    // LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCIDLESTATE_HIGH); //空闲状态极性
    // LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCIDLESTATE_LOW);
    // LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH); //匹配状态电平
    // LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCPOLARITY_HIGH);
    // LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1); //使能比较寄存器预装载
    // LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1); //使能通道输出
    // LL_TIM_SetOffStates(TIM1,LL_TIM_OSSI_ENABLE,LL_TIM_OSSR_ENABLE);
    // LL_TIM_EnableAllOutputs(TIM1);

    // //中断
    // LL_TIM_EnableIT_CC1(TIM1);
    // NVIC_SetPriority(TIM1_CC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
    // NVIC_EnableIRQ(TIM1_CC_IRQn);

    // //配置GPIO
    // LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    // GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    // GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    // GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    // GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    // LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    // //开启GPIOA时钟
    // LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    // //开启计数器计数
    // LL_TIM_EnableCounter(TIM1);

      LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
  LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

  /* TIM1 interrupt Init */
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

  TIM_InitStruct.Prescaler = 84;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 200;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM1, &TIM_InitStruct);
  LL_TIM_EnableARRPreload(TIM1);
  LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_TOGGLE;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 100;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
  LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH1);
  LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM1);
  TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
  TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
  TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct.DeadTime = 0;
  TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
  TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
  LL_TIM_BDTR_Init(TIM1, &TIM_BDTRInitStruct);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    /**TIM1 GPIO Configuration    
    PA8     ------> TIM1_CH1 
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM1))
    {
        LL_TIM_ClearFlag_UPDATE(TIM1);
        a++;
    }
}

void TIM1_CC_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_CC1(TIM1))
    {
        LL_TIM_ClearFlag_CC1(TIM1);
        a++;
    }
}