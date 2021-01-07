#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "peripheral.h"

#define ADC_INSTANCE ADC1

#define HORIZON_CHANNEL LL_ADC_CHANNEL_1
#define VERTICAL_CHANNEL LL_ADC_CHANNEL_0

#define HORIZON_CHANNEL_INDEX 0
#define VERTICAL_CHANNEL_INDEX 1

#define ADC_VALUE_BUFFER_LENGTH 10

#ifdef __cplusplus
extern "C"
{
#endif

    void EXTI4_IRQHandler();

    class Joystick
    {
    private:
        LL_DMA_InitTypeDef DMA_InitStruct = {0}; //ADC使用的DMA初始化

        /*外设初始化*/
        //摇杆ADC初始化
        void ADC_init(ADC_TypeDef *ADCx, uint32_t _HORIZON_CHANNEL, uint32_t _VERTICAL_CHANNEL);
        void ADC_gpio_init();
        void DMA_init();
        //摇杆外部中断EXTI初始化
        void EXTI_init();
        void EXTI_gpio_init();

        /*外设启动*/
        void ADC_begin(ADC_TypeDef *ADCx);

    public:
        Joystick(/* args */);
        ~Joystick();

        uint16_t ADC_VALUE_buffer[ADC_VALUE_BUFFER_LENGTH] = {0}; //保存ADC近10次ADC转换值
        bool Clicked = false;
        void init();
        void begin();
    };

    extern Joystick joystick;

#ifdef __cplusplus
}
#endif

#endif