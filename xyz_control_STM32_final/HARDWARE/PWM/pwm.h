#ifndef _PWM_H
#define _PWM_H

#include "sys.h"

void TIM1_GPIO_Config(void);
void TIM1_Config(uint32_t Period, uint32_t Prescaler);
void TIM3_Config(uint32_t Period, uint32_t Prescaler);
void TIM3_GPIO_Config(void);

#endif
