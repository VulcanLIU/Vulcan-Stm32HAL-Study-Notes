#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "main.h"

void ADC_init(void);
void ADC_begin();
void ADC2_Init(void);
void ADC2_Begin(void);

void ADC_IRQHandler(void);

extern uint32_t ADC_Value;

#ifdef __cplusplus
}
#endif
#endif 
