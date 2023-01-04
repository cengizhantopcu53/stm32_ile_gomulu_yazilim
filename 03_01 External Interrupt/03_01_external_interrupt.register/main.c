#include "stm32f4xx.h"

void delay(uint32_t time)
{
	while(time--);
}

void RCC_Config(void)
{
	RCC->CR |= 0x00010000;               //HSEON
	while(!(RCC->CR & 0x00020000));      //HSERDY
	RCC->CR |= 0x00080000;               //CSSON
	RCC->CFGR = 0x00000000;
	RCC->PLLCFGR |= 0x00400000;          //PLLSRC
	RCC->PLLCFGR |= 0x00000004;          //PLLM 4
	RCC->PLLCFGR |= 0x00002A00;          //PLLN 168
	RCC->PLLCFGR |= 0x00000000;          //PLLP 2
	RCC->CR |= 0x01000000;               //PLLON
	while(!(RCC->CR & 0x02000000));      //PLLRDY
	RCC->CFGR |= 0x00000001;             //SW
	while(!(RCC->CR & 0x00000001));      //SWS
}

void GPIO_Config(void)
{
	RCC->AHB1ENR |= 0x00000009;          //A, D clock enable

    GPIOD->MODER |= 0x55000000;         //PD12, PD13, PD14, PD15
    GPIOD->OTYPER |= 0x00000000;        //Output push-pull
    GPIOD->OSPEEDR |= 0xFF000000;       //Very high speed
    GPIOD->PUPDR |= 0x00000000;         //No pull-up, pull-down
}

void EXTI_Config(void)
{
	RCC->APB2ENR |= 0x00004000;          //SYSCGFEN

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI0_IRQn, 2);

	EXTI->EMR |= 0x00000007;
	EXTI->RTSR |= 0x00000007;

	SYSCFG->EXTICR[0] = 0x00000000;
}

void EXT0_IRQHandler()
{
	if(EXTI->PR & 0x00000001)
	{
		GPIOD->ODR |= 0x00001000;
		delay(33600000);
	}
	EXTI->PR = 0x00000001;
}

void EXT1_IRQHandler()
{
	if(EXTI->PR & 0x00000002)
	{
		GPIOD->ODR |= 0x00002000;
		delay(33600000);
	}
	EXTI->PR = 0x00000002;
}

void EXT2_IRQHandler()
{
	if(EXTI->PR & 0x00000004)
	{
		GPIOD->ODR |= 0x00004000;
		delay(33600000);
	}
	EXTI->PR = 0x00000004;
}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	GPIO_Config();
	EXTI_Config();

  while (1)
  {
	  GPIOD->ODR |= 0x0000F000;
  }
}
