#include "stm32f4xx.h"

int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void RCC_Config(void)
{
	RCC->CR |= 0x00030000;               //HSEON,HSERDY
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

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();

	GPIO_Config();

  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  while(GPIOA->IDR & 0x00000001);
		  delay(1680000);

		  count++;
	  }
	  if(count %2 == 0)
		  GPIOD->ODR |= 0x00000000;
	  else
		  GPIOD->ODR |= 0x0000F000;
  }
}
