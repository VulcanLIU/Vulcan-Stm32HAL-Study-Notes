#ifndef __tim_H
#define __tim_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

//TIM初始化
void MX_TIM1_Init(void);
void MX_TIM1_OC_Init(void);
void TIM1_UP_TIM10_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif