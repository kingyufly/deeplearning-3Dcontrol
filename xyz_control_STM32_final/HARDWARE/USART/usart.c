#include "usart.h"
#include "delay.h"
#include "gpio.h"

//External variables from TIM
extern int n_uart;
extern int n;
extern int n_x;
extern int n_y;
extern int n_z;
extern int n_tmp;
extern int n_x_tmp;
extern int n_y_tmp;
extern int n_z_tmp;

extern int start_flag;
extern int pause_flag;
//Receive buffer, to store the data from the UART
char Recv_buf[19];

//Variables to store the parameters of the three step motors
char x[4];
char y[4];
char z[4];
char x_d;
char y_d;
char z_d;

//Variable to store the temp value
char str[10];
int size = 0;
int X_status = 0;
int Y_status = 0;
int Z_status = 0;
int X_D_status = 0;
int Y_D_status = 0;
int Z_D_status = 0;

//flags
int retrans_flag = 1;
int exti_flag = 1;
	
void USART1_NVIC_Config(uint8_t PreemptionPriority, uint8_t SubPriority){
  NVIC_InitTypeDef NVIC_InitStructure;
    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        
  NVIC_Init(&NVIC_InitStructure);
}

void USART1_GPIO_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;
    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
  //PB6->TX  PB7->RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
}

void USART1_Config(void){
	USART_InitTypeDef USART_InitStructure;
	USART1_GPIO_Config();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART1,&USART_InitStructure);   
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
  USART_Cmd(USART1,ENABLE);  
}

void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		Recv_buf[size] = USART_ReceiveData(USART1);
		
		if(size == 0)
		{
			n_uart = 0;
			TIM_Cmd(TIM7, ENABLE);		
		}
		size++;
		
		if((size == 19) && (n_uart <= 10) && (Recv_buf[17] == '\r') && (Recv_buf[18] == '\n'))
		{
			retrans_flag = 0;
			TIM_Cmd(TIM7, DISABLE);
			
			//If it is the first time, the stepper should all rotate to the original point
			//and then rotate to the "zero" point
			if(strncmp(Recv_buf, "STARTSTARTSTARTST\r\n", 19) == 0)
			{
				start_flag = 1;
				exti_flag = 0;
				
				n = n_tmp = 20000;
				n_x = n_x_tmp = 20000;
				n_y	= n_y_tmp = 20000;
				n_z = n_z_tmp = 20000;
				X_D = 0;
				Y_D = 0;
				Z_D = 0;				
				
				TIM_Cmd(TIM6, ENABLE);
				TIM_Cmd(TIM9, ENABLE);
				TIM_Cmd(TIM10, ENABLE);
				TIM_Cmd(TIM11, ENABLE);
			}
			//If the operation need to be paused, the current value of the rotate will be record 
			//This part should be achieved in the timer part
			else if(strncmp(Recv_buf, "PAUSEPAUSEPAUSEPA\r\n", 19) == 0)
			{	
				pause_flag = 1;
				//TIM_Cmd(TIM6, DISABLE);
				//TIM_Cmd(TIM9, DISABLE);
				//TIM_Cmd(TIM10, DISABLE);
				//TIM_Cmd(TIM11, DISABLE);
				//X_status = X;
				//Y_status = Y;
				//Z_status = Z;
				//X_D_status = X_D;
		    //Y_D_status = Y_D;
				//Z_D_status = Z_D;
				
				//X = 0;
				//Y = 0;
				//Z = 0;
				//X_D = 0;
				//Y_D = 0;
				//Z_D = 0;
				
				
				retrans_flag = 1;
			}
			//Afrer the pause, if it needs resume the operation, the rest of the rotate value will be restored
			//This part should be achieved in the timer part
			else if(strncmp(Recv_buf, "RESUMERESUMERESUM\r\n", 19) == 0)
			{
				pause_flag = 0;
				
				X_D = X_D_status;
		    Y_D = Y_D_status;
				Z_D = Z_D_status;
				X = X_status;
				Y = Y_status;
				Z = Z_status;		
				
				TIM_Cmd(TIM6, ENABLE);
				TIM_Cmd(TIM9, ENABLE);
				TIM_Cmd(TIM10, ENABLE);
				TIM_Cmd(TIM11, ENABLE);
				
				retrans_flag = 0;
			}
			else if(strncmp(Recv_buf, "STOPSTOPSTOPSTOPS\r\n", 19) == 0)
			{		
				X = 0;
				Y = 0;
				Z = 0;
				
				X_D = 0;
				Y_D = 0;
				Z_D = 0;
				
				start_flag = 0;
				TIM_SetCounter(TIM6, 0);
				TIM_Cmd(TIM6, DISABLE);
				TIM_SetCounter(TIM9, 0);
				TIM_Cmd(TIM9, DISABLE);
				TIM_SetCounter(TIM10, 0);
				TIM_Cmd(TIM10, DISABLE);
				TIM_SetCounter(TIM11, 0);
				TIM_Cmd(TIM11, DISABLE);
			}
			//In other cases, the received data will be the value of ratation
			else
			{

				//Get the value of the rotation
				for(int i = 1; i < 5; i++)
				{
					x[i - 1] = Recv_buf[i];
					y[i - 1] = Recv_buf[i + 6];
					z[i - 1] = Recv_buf[i + 12];
				}	
				
				n_x = n_x_tmp = (x[0]-48)*1000 + (x[1]-48)*100 + (x[2]-48)*10 + (x[3]-48);
				n_y = n_y_tmp = (y[0]-48)*1000 + (y[1]-48)*100 + (y[2]-48)*10 + (y[3]-48);
				n_z = n_z_tmp = (z[0]-48)*1000 + (z[1]-48)*100 + (z[2]-48)*10 + (z[3]-48);
			
				USART_SendData(USART1, (char)(48 + n_x/1000%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_x/100%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_x/10%100));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_x%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				
				USART_SendData(USART1, ';');
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				
				USART_SendData(USART1, (char)(48 + n_y/1000%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_y/100%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_y/10%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_y%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
					
				USART_SendData(USART1, ';');
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
					
				USART_SendData(USART1, (char)(48 + n_z/1000%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_z/100%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_z/10%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_z%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
					
				if(n_x >= n_y)
				{
					n = n_tmp = n_x;
				}
				else
				{
					n = n_tmp = n_y;
				}
				
				if(n >= n_z)
				{
					;
				}
				else
				{
					n = n_tmp = n_z;
				}
				
				n++;
				n_tmp = n;
				
				USART_SendData(USART1, ';');
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
					
				USART_SendData(USART1, (char)(48 + n_tmp/1000%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_tmp/100%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_tmp/10%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				USART_SendData(USART1, (char)(48 + n_tmp%10));
					while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
				
				//Get the direction of the rotation
				x_d = Recv_buf[0];
				y_d = Recv_buf[6];
				z_d = Recv_buf[12];
				
				if(x_d == '+')
				{
				  X_D = 0;
				}
				else if(x_d == '-')
				{
					X_D = 1;
				}
				else
				{
					;
				}
				
				if(y_d == '+')
				{
				  Y_D = 0;
				}
				else if(y_d == '-')
				{
					Y_D = 1;
				}
				else
				{
					;
				}
				
				if(z_d == '+')
				{
				  Z_D = 0;
				}
				else if(z_d == '-')
				{
					Z_D = 1;
				}
				else
				{
					;
				}
				start_flag = 1;
				TIM_Cmd(TIM6, ENABLE);
				TIM_Cmd(TIM9, ENABLE);
				TIM_Cmd(TIM10, ENABLE);
				TIM_Cmd(TIM11, ENABLE);
				/////////////////////////////////////
				//Confirm that the stepper finishes the work
				//This part should be moved to the timer.
			}
			for(int i = 0; i < sizeof(Recv_buf); i++)
				Recv_buf[i] = '\0';
			size = 0;
			n_uart = 0;
		}
		else
			;
	}
}
