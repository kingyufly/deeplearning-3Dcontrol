#ifndef _USART_H
#define _USART_H

#include "sys.h"
#include "stdlib.h"
#include "string.h"

void USART1_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority);
void USART1_GPIO_Config(void);
void USART1_Config(void);

#endif
