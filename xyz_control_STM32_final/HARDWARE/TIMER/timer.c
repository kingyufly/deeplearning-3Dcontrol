#include "timer.h"
#include "delay.h"

extern char Recv_buf[13];
extern int size;
extern char str[10];
extern int retrans_flag;
extern int n_exti;
extern int x_l_flag;
extern int y_l_flag;
extern int z_l_flag;

extern int X_status;
extern int Y_status;
extern int Z_status;
extern int X_D_status;
extern int Y_D_status;
extern int Z_D_status;

int n_uart = 0;

int n = 0;
int n_x = 0;
int n_y = 0;
int n_z = 0;
int n_tmp = 0;
int n_x_tmp = 0;
int n_y_tmp = 0;
int n_z_tmp = 0;
int pause_flag = 0;

int start_flag = 0;

void TIM6_Config(uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = Period - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM6, DISABLE);
}

void TIM7_Config(uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = Period - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, DISABLE);
}

void TIM9_Config(uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = Period - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM9, DISABLE);
}

void TIM10_Config(uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = Period - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM10, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM10, DISABLE);
}

void TIM11_Config(uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = Period - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM11, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM11, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM11, DISABLE);
}

void TIM6_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM7_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM9_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM10_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM11_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET && (start_flag == 1))
  {			
		if(n_tmp != 0)
		{
			n_tmp--;
		}
		else
		{
			TIM_SetCounter(TIM6, 0);
			TIM_Cmd(TIM6, DISABLE);
			TIM_SetCounter(TIM9, 0);
			TIM_Cmd(TIM9, DISABLE);
			TIM_SetCounter(TIM10, 0);
			TIM_Cmd(TIM10, DISABLE);
			TIM_SetCounter(TIM11, 0);
			TIM_Cmd(TIM11, DISABLE);
			
			X = 0;
			Y = 0;
			Z = 0;
			
			X_D = 0;
			Y_D = 0;
			Z_D = 0;
			
			n_exti = 0;
			x_l_flag = 0;
			y_l_flag = 0;
			z_l_flag = 0;
			
			delay_ms(1000);
			strcpy(str, "OK\r\n\0");
			for(int i = 0; i < strlen(str); i++)
			{
				USART_SendData(USART1, str[i]);
				while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
			}
		}	
		
		if(pause_flag)
		{
			TIM_Cmd(TIM6, DISABLE);
		}
  }
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET && start_flag)
  {
		n_uart++;
		if(n_uart > 10 && (size != 19))
		{
			TIM_Cmd(TIM7, DISABLE);
			
			if(retrans_flag)
			{
				strcpy(str, "RE\r\n");
				for(int i = 0; i < strlen(str); i++)
				{
					USART_SendData(USART1, str[i]);
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				}
			}
				
			for(int i = 0; i < sizeof(Recv_buf); i++)
				Recv_buf[i] = '\0';
			size = 0;
			n_uart = 0;
		}
		else
			;
  }
  TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM9, TIM_IT_Update) == SET) && start_flag)
  {
		if(n_x_tmp != 0)
		{
			X = !X;
			n_x_tmp--;
		}
		else
		{
			X = 0;
			TIM_SetCounter(TIM9, 0);
			TIM_Cmd(TIM9, DISABLE);
		}
		
		if(pause_flag)
		{
			TIM_Cmd(TIM9, DISABLE);
			X_status = X;
			X_D_status = X_D;
				
			X = 0;
			X_D = 0;
		}
  }
  TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM10, TIM_IT_Update) == SET) && start_flag)
  {
		if(n_y_tmp != 0)
		{
			Y = !Y;
			n_y_tmp--;
		}
		else
		{
			Y = 0;
			TIM_SetCounter(TIM10, 0);
			TIM_Cmd(TIM10, DISABLE);
		}
		
		if(pause_flag)
		{
			TIM_Cmd(TIM10, DISABLE);
			Y_status = Y;
			Y_D_status = Y_D;
				
			Y = 0;
			Y_D = 0;
		}
  }
  TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	if((TIM_GetITStatus(TIM11, TIM_IT_Update) == SET) && start_flag)
  {
		if(n_z_tmp != 0)
		{
			Z = !Z;
			n_z_tmp--;
		}
		else
		{
			Z = 0;
			TIM_SetCounter(TIM11, 0);
			TIM_Cmd(TIM11, DISABLE);
		}
		
		if(pause_flag)
		{
			TIM_Cmd(TIM11, DISABLE);
			Z_status = Z;
			Z_D_status = Z_D;
				
			Z = 0;
			Z_D = 0;
		}
  }
  TIM_ClearITPendingBit(TIM11, TIM_IT_Update);
}
