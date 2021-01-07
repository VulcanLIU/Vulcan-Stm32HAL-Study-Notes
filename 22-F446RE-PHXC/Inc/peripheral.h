/**
 * @file peripheral.h
 * @author your name (you@domain.com)
 * @brief 包含所有平衡小车使用的外设头文件
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __PERIPHERAL_H
#define __PERIPHERAL_H

#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_tim.h"

/****GY25-USART1****/
//RX->PB7
//TX->PB6

/****摇杆-ADC1****/
//水平通道->PA0
//竖直通道->PA1
//按键->PC4

/****运行状态指示灯-TIM9****/
//阳极->PC0
//阴极->PC1



#endif