#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIM_OCInitStruct; 

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;  
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; 
}

int main(void)
{
	config();
  while (1)
  {
	  // PD12
	  TIM_OCInitStruct.TIM_Pulse = 2499;	
	  TIM_OC1Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);	
	  // PD13
	  TIM_OCInitStruct.TIM_Pulse = 4999;	
	  TIM_OC2Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);	

	  // PD14
	  TIM_OCInitStruct.TIM_Pulse = 7499;	
	  TIM_OC3Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);	

	  // PD15
	  TIM_OCInitStruct.TIM_Pulse = 9999;	
	  TIM_OC4Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  }
}