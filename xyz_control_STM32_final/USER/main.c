#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "gpio.h"
#include "exti.h"


int main(void)
{
	delay_init(72);
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1); //AHB1 = 72
	RCC_PCLK1Config(RCC_HCLK_Div16);	 //APB1 = 72 / 16
	RCC_PCLK2Config(RCC_HCLK_Div16);	 //APB2 = 72 / 16
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Input_Init();
	Output_Init();
	
	EXTIX_Init();
	
	USART1_Config();			//PB6->TX PB7->RX
	USART1_NVIC_Config(0x03, 0x02);

	TIM6_Config(1000, 9);
	TIM7_Config(1000, 9);
	TIM9_Config(1000, 9);
	TIM10_Config(1000, 9);
	TIM11_Config(1000, 9);
	
	TIM6_NVIC_Config(0x00, 0x02);
	TIM7_NVIC_Config(0x00, 0x02);
	TIM9_NVIC_Config(0x00, 0x02);
	TIM10_NVIC_Config(0x00, 0x02);
	TIM11_NVIC_Config(0x00, 0x02);
	
	while(1)
	{
		;
	}
}
