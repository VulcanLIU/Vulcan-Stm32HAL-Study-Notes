#include "Joystick.h"
#include "stm32f4xx_ll_gpio.h"

Joystick joystick;

Joystick::Joystick(/* args */)
{
}

Joystick::~Joystick()
{
}

/**
 * @brief 摇杆的ADC初始化函数
 * 
 * @param ADCx 使用的ADC对象
 * @param HORIZON_CHANNEL 水平摇杆对应的ADC通道
 * @param VERTICAL_CHANNEL 竖直摇杆对应的ADC通道
 */
void Joystick::ADC_init(ADC_TypeDef *ADCx, uint32_t _HORIZON_CHANNEL, uint32_t _VERTICAL_CHANNEL)
{
    //打开外设时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

    //打开ADC的GPIO
    ADC_gpio_init();

    //选择触发源
    LL_ADC_REG_SetTriggerSource(ADCx, LL_ADC_REG_TRIG_SOFTWARE);
    //选择预分配器
    LL_ADC_SetCommonClock(ADC123_COMMON, LL_ADC_CLOCK_SYNC_PCLK_DIV4);
    //常规组注册通道
    LL_ADC_REG_SetSequencerRanks(ADCx, LL_ADC_REG_RANK_1, HORIZON_CHANNEL);
    LL_ADC_REG_SetSequencerRanks(ADCx, LL_ADC_REG_RANK_2, VERTICAL_CHANNEL);
    //选择为扫描模式&扫描长度
    LL_ADC_REG_SetSequencerLength(ADCx, LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS);
    LL_ADC_SetSequencersScanMode(ADCx, LL_ADC_SEQ_SCAN_ENABLE);
    //设为连续模式
    LL_ADC_REG_SetContinuousMode(ADCx, LL_ADC_REG_CONV_CONTINUOUS);
    //设置采样时间
    LL_ADC_SetChannelSamplingTime(ADCx, HORIZON_CHANNEL, LL_ADC_SAMPLINGTIME_3CYCLES);
    LL_ADC_SetChannelSamplingTime(ADCx, VERTICAL_CHANNEL, LL_ADC_SAMPLINGTIME_3CYCLES);
    //设置分辨率
    LL_ADC_SetResolution(ADCx, LL_ADC_RESOLUTION_8B);

    //开启DMA
    DMA_init();
    //启动adc
    LL_ADC_Enable(ADCx);

    //打开按键GPIO
}

void Joystick::ADC_gpio_init()
{
    //初始化GPIO
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //打开GPIOA的时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
}

void Joystick::DMA_init()
{
    //开启DMA时钟
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

    //打开ADC1的DMA请求
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

    //配置DMA2
    //配置外设地址
    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t)(&ADC1->DR);
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;

    //配置数据流方向
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.NbData = 2 * ADC_VALUE_BUFFER_LENGTH;
    DMA_InitStruct.Mode = LL_DMA_MODE_CIRCULAR;

    //配置FIFO
    DMA_InitStruct.FIFOMode = LL_DMA_FIFOMODE_ENABLE;
    DMA_InitStruct.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_FULL;

    //配置存储器地址
    DMA_InitStruct.MemoryOrM2MDstAddress = (uint32_t)ADC_VALUE_buffer;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;

    //通道选择
    DMA_InitStruct.Channel = LL_DMA_CHANNEL_0;

    //优先级
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;

    //初始化DMA
    LL_DMA_Init(DMA2, LL_DMA_STREAM_0, &DMA_InitStruct);

    //中断配置
    //使能外设中断
    //LL_DMA_EnableIT_TC(DMA1,LL_DMA_STREAM_0);
    //设置优先级
    //NVIC_SetPriority(DMA2_Stream0_IRQn,NVIC_EncodePriority(0, 1, 1));
    //使能NVIC中断
    //NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    //开启DMA数据流
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
}

void Joystick::EXTI_init()
{

    EXTI_gpio_init();
    //开SYSCFG时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    //选择中断线
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE4);
  
    //EXTI外设寄存器配置
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_4);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4);

    //在NVIC中注册中断
    NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(0, 1, 1));
    NVIC_EnableIRQ(EXTI4_IRQn);
}

void Joystick::EXTI_gpio_init()
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    //配置GPIO_下拉
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void Joystick::ADC_begin(ADC_TypeDef *ADCx)
{
    //开启软件连续转换
    LL_ADC_REG_StartConversionSWStart(ADCx);
}

void Joystick::init()
{
    //摇杆ADC初始化
    ADC_init(ADC_INSTANCE, HORIZON_CHANNEL, VERTICAL_CHANNEL);
    //摇杆外部中断EXTI初始化
    EXTI_init();
}

void Joystick::begin()
{
    //摇杆ADC启动
    ADC_begin(ADC_INSTANCE);
}

void EXTI4_IRQHandler(void)
{
    joystick.Clicked = true;
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
    asm("nop");
}