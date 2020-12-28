#include "Joystick.h"

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
void init(ADC_TypeDef *ADCx,uint32_t HORIZON_CHANNEL,uint32_t VERTICAL_CHANNEL)
{
    //打开外设时钟
    

    //选择触发源
    LL_ADC_REG_SetTriggerSource(ADCx,LL_ADC_REG_TRIG_SOFTWARE);
    //选择预分配器
    LL_ADC_SetCommonClock(ADC123_COMMON,LL_ADC_CLOCK_SYNC_PCLK_DIV4);
    //常规组注册通道
    LL_ADC_REG_SetSequencerRanks(ADCx,LL_ADC_REG_RANK_1,HORIZON_CHANNEL);
    LL_ADC_REG_SetSequencerRanks(ADCx,LL_ADC_REG_RANK_2,VERTICAL_CHANNEL);
    //选择为扫描模式&扫描长度
    LL_ADC_REG_SetSequencerLength(ADCx,LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS);
    LL_ADC_SetSequencersScanMode(ADCx,LL_ADC_SEQ_SCAN_ENABLE);
    //设为连续模式
    LL_ADC_REG_SetContinuousMode(ADCx,LL_ADC_REG_CONV_CONTINUOUS);
    //设置采样时间
    LL_ADC_SetChannelSamplingTime(ADCx,HORIZON_CHANNEL,LL_ADC_SAMPLINGTIME_3CYCLES);
    LL_ADC_SetChannelSamplingTime(ADCx,VERTICAL_CHANNEL,LL_ADC_SAMPLINGTIME_3CYCLES);
    //设置分辨率
    LL_ADC_SetResolution(ADCx,LL_ADC_RESOLUTION_8B);
    //启动adc
    LL_ADC_Enable(ADCx);
}