#include "exti.h"
#include "delay.h" 
#include "gpio.h" 
#include "timer.h" 

extern int n_uart;
extern int n;
extern int n_x;
extern int n_y;
extern int n_z;
extern int n_tmp;
extern int n_x_tmp;
extern int n_y_tmp;
extern int n_z_tmp;

extern int size;
extern int retrans_flag;
extern int exti_flag;
extern int start_flag; 

extern char str[10];

int n_exti = 0;
int x_l_flag = 0;
int y_l_flag = 0;
int z_l_flag = 0;

void EXTIX_Init(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource8);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	//If the limit is activated, the X axis will stop
	delay_ms(20);
	if((X_L1 == 1) && !exti_flag)
	{
		if(!x_l_flag)
		{
			n_exti++;
			x_l_flag = 1;
		}
		
		X = 0;
		TIM_SetCounter(TIM9, 0);
		TIM_Cmd(TIM9, DISABLE);
		//I fthe X axis is the last activated, then begin to rotate to "zero" point
		if((n_exti == 3) && x_l_flag)
		{
			exti_flag = 1;
			
			TIM_SetCounter(TIM6, 0);
			TIM_Cmd(TIM6, DISABLE);
			TIM_SetCounter(TIM9, 0);
			TIM_Cmd(TIM9, DISABLE);
			TIM_SetCounter(TIM10, 0);
			TIM_Cmd(TIM10, DISABLE);
			TIM_SetCounter(TIM11, 0);
			TIM_Cmd(TIM11, DISABLE);
			
			X_D = 1;
			Y_D = 1;
			Z_D = 1;
			n = n_tmp = 4500;
			n_x = n_x_tmp = 4500;
			n_y = n_y_tmp = 4500;
			n_z = n_z_tmp = 4500;
			
			start_flag = 1;
			
			TIM_Cmd(TIM6, ENABLE);
			TIM_Cmd(TIM9, ENABLE);
			TIM_Cmd(TIM10, ENABLE);
			TIM_Cmd(TIM11, ENABLE);
		}
	}
	//If the limit is activated during the rotate, the process will be terminated
	//else if((X_L1 == 1) && exti_flag)
	//{
	//	;
		//System_Init();
		//stop all, clear all variables, reset all flags and send error info to the computer
	//}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	//If the limit is activated, the X axis will stop
	delay_ms(20);
	if((Y_L1 == 1) && !exti_flag)
	{
		if(!y_l_flag)
		{
			n_exti++;
			y_l_flag = 1;
		}
		
		Y = 0;
		TIM_SetCounter(TIM10, 0);
		TIM_Cmd(TIM10, DISABLE);
		//I fthe X axis is the last activated, then begin to rotate to "zero" point
		if((n_exti == 3) && y_l_flag)
		{
			exti_flag = 1;
			
			TIM_SetCounter(TIM6, 0);
			TIM_Cmd(TIM6, DISABLE);
			TIM_SetCounter(TIM9, 0);
			TIM_Cmd(TIM9, DISABLE);
			TIM_SetCounter(TIM10, 0);
			TIM_Cmd(TIM10, DISABLE);
			TIM_SetCounter(TIM11, 0);
			TIM_Cmd(TIM11, DISABLE);

			X_D = 1;
			Y_D = 1;
			Z_D = 1;
			n = n_tmp = 4500;
			n_x = n_x_tmp = 4500;
			n_y = n_y_tmp = 4500;
			n_z = n_z_tmp = 4500;
			
			start_flag = 1;
			
			TIM_Cmd(TIM6, ENABLE);
			TIM_Cmd(TIM9, ENABLE);
			TIM_Cmd(TIM10, ENABLE);
			TIM_Cmd(TIM11, ENABLE);
		}
	}
	//If the limit is activated during the rotate, the process will be terminated
	//else if((Y_L1 == 1) && exti_flag)
	//{
	//	;
		//System_Init();
		//stop all, clear all variables, reset all flags and send error info to the computer
	//}
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{	
	//If the limit is activated, the X axis will stop
	delay_ms(20);
	if((Z_L1 == 1) && !exti_flag)
	{
		if(!z_l_flag)
		{
			n_exti++;
			z_l_flag = 1;
		}
		
		Z = 0;
		TIM_SetCounter(TIM11, 0);
		TIM_Cmd(TIM11, DISABLE);
		//I fthe X axis is the last activated, then begin to rotate to "zero" point
		if((n_exti == 3) && z_l_flag)
		{
			exti_flag = 1;
			TIM_SetCounter(TIM6, 0);
			TIM_Cmd(TIM6, DISABLE);
			TIM_SetCounter(TIM9, 0);
			TIM_Cmd(TIM9, DISABLE);
			TIM_SetCounter(TIM10, 0);
			TIM_Cmd(TIM10, DISABLE);
			TIM_SetCounter(TIM11, 0);
			TIM_Cmd(TIM11, DISABLE);
			
			X_D = 1;
			Y_D = 1;
			Z_D = 1;
			n = n_tmp = 4500;
			n_x = n_x_tmp = 4500;
			n_y = n_y_tmp = 4500;
			n_z = n_z_tmp = 4500;
			
			start_flag = 1;
			
			TIM_Cmd(TIM6, ENABLE);
			TIM_Cmd(TIM9, ENABLE);
			TIM_Cmd(TIM10, ENABLE);
			TIM_Cmd(TIM11, ENABLE);
		}
	}
	//If the limit is activated during the rotate, the process will be terminated
	//else if((Z_L1 == 1) && exti_flag)
	//{
	//	;
		//System_Init();
		//stop all, clear all variables, reset all flags and send error info to the computer
	//}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

//The X_L2, Y_L2, Z_L2 will not work until the position data arrives
void EXTI9_5_IRQHandler(void)
{
	if(exti_flag)
	{
		if(EXTI_GetFlagStatus(EXTI_Line6) == SET)
		{
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
		else if(EXTI_GetFlagStatus(EXTI_Line7) == SET)
		{
			EXTI_ClearITPendingBit(EXTI_Line7);
		}
		else if(EXTI_GetFlagStatus(EXTI_Line8) == SET)
		{
			EXTI_ClearITPendingBit(EXTI_Line8);
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}
}

void System_Init()
{
	TIM_Cmd(TIM6, DISABLE);
	TIM_Cmd(TIM7, DISABLE);
	TIM_Cmd(TIM9, DISABLE);
	TIM_Cmd(TIM10, DISABLE);
	TIM_Cmd(TIM11, DISABLE);
		
	n_uart = 0;
	n = 0;
	n_x = 0;
	n_y = 0;
	n_z = 0;
	n_tmp = 0;
  n_x_tmp = 0;
	n_y_tmp = 0;
	n_z_tmp = 0;

	size = 0;
	retrans_flag = 1;
	exti_flag = 1;
}









