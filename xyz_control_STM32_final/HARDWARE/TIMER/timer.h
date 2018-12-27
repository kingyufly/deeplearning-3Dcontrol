#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "gpio.h"
#include "string.h"

void TIM6_Config(uint32_t Period, uint32_t Prescaler);
void TIM7_Config(uint32_t Period, uint32_t Prescaler);
void TIM9_Config(uint32_t Period, uint32_t Prescaler);
void TIM10_Config(uint32_t Period, uint32_t Prescaler);
void TIM11_Config(uint32_t Period, uint32_t Prescaler);

void TIM6_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);
void TIM7_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);
void TIM9_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);
void TIM10_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);
void TIM11_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);

#endif
