#include "Stepper.h"

Stepper Stepper_left(TIM1, LL_TIM_CHANNEL_CH3);
Stepper Stepper_right(TIM2, LL_TIM_CHANNEL_CH2);

Stepper::Stepper(TIM_TypeDef *TIMx, uint32_t Channel)
{
    this->TIMx = TIMx;
    this->Channel = Channel;
}

Stepper::~Stepper()
{
}

void Stepper::init()
{
    //开定时器外设时钟
    if (TIMx == TIM1)
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
        //设置预分频器
        LL_TIM_SetPrescaler(TIMx, 9000);
        TIMx_freq = 90000000;
        TIMx_prescaler = 9000;
    }

    if (TIMx == TIM2)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
        //设置预分频器
        LL_TIM_SetPrescaler(TIMx, 4500);
        TIMx_freq = 45000000;
        TIMx_prescaler = 4500;
    }

    //定时器选择时钟源
    LL_TIM_SetClockSource(TIMx, LL_TIM_CLOCKSOURCE_INTERNAL);

    //设置自动重载寄存器
    LL_TIM_SetAutoReload(TIMx, 2000 - 1);
    //设置计数方向
    LL_TIM_SetCounterMode(TIMx, LL_TIM_COUNTERMODE_CENTER_UP);
    //使能自动重载预装载
    LL_TIM_EnableARRPreload(TIMx);

    if (Channel == LL_TIM_CHANNEL_CH3 || Channel == LL_TIM_CHANNEL_CH3N)
    {
        //设置比较值
        LL_TIM_OC_SetCompareCH3(TIMx, 1000 - 1);
        //设置成PWM模式
        LL_TIM_OC_SetMode(TIMx, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);

        //设置捕获/比较寄存器值
        LL_TIM_OC_EnablePreload(TIMx, LL_TIM_CHANNEL_CH3);
    }

    if (Channel == LL_TIM_CHANNEL_CH2 || Channel == LL_TIM_CHANNEL_CH2N)
    {
        //设置比较值
        LL_TIM_OC_SetCompareCH2(TIMx, 1000 - 1);
        //设置成PWM模式
        LL_TIM_OC_SetMode(TIMx, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);

        //设置捕获/比较寄存器值
        LL_TIM_OC_EnablePreload(TIMx, LL_TIM_CHANNEL_CH2);
    }

    //设置输出极性
    LL_TIM_OC_SetPolarity(TIMx, Channel, LL_TIM_OCPOLARITY_HIGH);
    //使能输出
    LL_TIM_EnableAllOutputs(TIMx);
    LL_TIM_CC_EnableChannel(TIMx, Channel);

    //GPIO初始化
    gpio_init();
}

void Stepper::gpio_init()
{
    if (TIMx == TIM1)
    {
        //开启GPIO时钟
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

        //GPIO选为AF
        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
        LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

    if (TIMx == TIM2)
    {
        //开启GPIO时钟
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

        //GPIO选为AF
        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

void Stepper::begin()
{
    LL_TIM_EnableCounter(TIMx);
}

void Stepper::stop()
{
    LL_TIM_DisableCounter(TIMx);
}

void Stepper::setDirection(DIRCTION dir)
{
    if (dir == POS)
    {
        if (TIMx == TIM1)
        {
            LL_GPIO_WriteOutputPort(GPIOB, LL_GPIO_ReadOutputPort(GPIOB) & (~LL_GPIO_PIN_4));
        }
        if (TIMx == TIM2)
        {
            LL_GPIO_WriteOutputPort(GPIOB, LL_GPIO_ReadOutputPort(GPIOB) & (~LL_GPIO_PIN_10));
        }
    }
    if (dir == INV)
    {
        if (TIMx == TIM1)
        {
            LL_GPIO_WriteOutputPort(GPIOB, LL_GPIO_ReadOutputPort(GPIOB) | (LL_GPIO_PIN_4));
        }
        if (TIMx == TIM2)
        {
            LL_GPIO_WriteOutputPort(GPIOB, LL_GPIO_ReadOutputPort(GPIOB) | (LL_GPIO_PIN_10));
        }
    }
}

void Stepper::setFreq(uint16_t freq)
{
    uint16_t ARR_t = TIMx_freq / TIMx_prescaler / freq;
    uint16_t CCR_t = ARR_t * 0.5;

    LL_TIM_SetAutoReload(TIMx, ARR_t);
    if (Channel == LL_TIM_CHANNEL_CH3)
    {
        LL_TIM_OC_SetCompareCH3(TIMx, CCR_t);
    }
    if (Channel == LL_TIM_CHANNEL_CH2)
    {
        LL_TIM_OC_SetCompareCH2(TIMx, CCR_t);
    }
}

/**
 * @brief 设置转速
 * 
 * @param speed 转速-单位（度/秒）
 */
void Stepper::setSpeed(float speed)
{
    //判断速度方向
    DIRCTION _dir = POS;
    if (speed != abs(speed))
    {
        _dir = INV;
        speed = abs(speed);
    }
    setDirection(_dir);

    //速度限幅
    if (speed > 1800)
        speed = 1800;
    if (speed < 180)
        speed = 180;

    //将速度转化为定时器频率
    uint16_t _freq = speed / 1.8;
    setFreq(_freq);
}