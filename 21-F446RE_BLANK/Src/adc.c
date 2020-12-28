#include "adc.h"

uint32_t ADC_Value = 0;

void ADC_init(void)
{
    /*配置GPIO*/
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*开启外设时钟*/
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV4);
    /*设置分辨率*/
    LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

    /*通道设置*/
    /*设置触发源*/
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

    /*规则通道转换长度*/
    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_3CYCLES);
    /*设置连续方式*/
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);

    /*设置对齐方式*/
    LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

    /*中断*/
    LL_ADC_DisableIT_EOCS(ADC1);
    LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
}

void ADC_begin()
{
    /*ADC上电*/
    LL_ADC_Enable(ADC1);

    /*ADC软件触发*/
    LL_ADC_REG_StartConversionSWStart(ADC1);
}
void ADC2_Init(void)
{
    //开ADC2外设时钟
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);

    //开ADCCLK时钟
    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC2), LL_ADC_CLOCK_SYNC_PCLK_DIV4);

    //选择触发源
    LL_ADC_REG_SetTriggerSource(ADC2, LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_INJ_SetTriggerSource(ADC2, LL_ADC_INJ_TRIG_SOFTWARE);

    //扫描模式
    LL_ADC_SetSequencersScanMode(ADC2, LL_ADC_SEQ_SCAN_ENABLE);
    //注册通道
    LL_ADC_REG_SetSequencerLength(ADC2, LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS);
    LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);
    LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_3CYCLES);
    LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_1);
    LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_3CYCLES);
    //连续模式
    LL_ADC_REG_SetContinuousMode(ADC2, LL_ADC_REG_CONV_CONTINUOUS);

    //配置GPIO
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //DAC参数设置
    LL_ADC_SetResolution(ADC2, LL_ADC_RESOLUTION_8B);
    //对齐方式
    LL_ADC_SetDataAlignment(ADC2, LL_ADC_DATA_ALIGN_RIGHT);

    //使能转换结束中断
    LL_ADC_EnableIT_EOCS(ADC2);
    //设置中断优先级
    NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC2_Begin(void)
{
    /*ADC上电*/
    LL_ADC_Enable(ADC2);

    /*ADC软件触发*/
    LL_ADC_REG_StartConversionSWStart(ADC2);
}

void ADC_IRQHandler()
{
    ADC_Value = LL_ADC_REG_ReadConversionData8(ADC2);
}