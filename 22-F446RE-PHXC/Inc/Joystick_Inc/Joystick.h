#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "peripheral.h"

#define HORIZON_CHANNEL_INDEX 0
#define VERTICAL_CHANNEL_INDEX 1

class Joystick
{
private:
    uint16_t ADC_VALUE_buffer[10][2] = {{0,0}};//保存ADC近10次ADC转换值
public:
    Joystick(/* args */);
    ~Joystick();
    void init(ADC_TypeDef *ADCx,uint32_t HORIZON_CHANNEL,uint32_t VERTICAL_CHANNEL);
    uint16_t get_horizon_value();
    uint16_t 
};

#endif