/*******************
 * 
 * 外设初始化文件
 * 
 /******************/

#ifndef __PERIPHERAL_INIT__
#define __PERIPHERAL_INIT__

#include "stm32f1xx_hal.h"

/******** I2C初始化 *********/

extern I2C_HandleTypeDef hi2c1;

void I2C_Init(I2C_TypeDef *instance);

#endif