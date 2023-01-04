#include "stm32f4xx.h"

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
	RCC->CFGR |= 0x00000000;             //HPRE AHB 1
	RCC->CFGR |= 0x00001400;             //PPRE1 APB1 4
	RCC->CFGR |= 0x00008000;             //PPRE2 APB2 2
	RCC->CIR |= 0x00080000;              //HSERDYC
	RCC->CIR |= 0x00800000;              //CSSC
}

void GPIO_Config(void)
{
	RCC->AHB1ENR |= 0x00000002;            //B clock enable

    GPIOB->MODER |= 0x00A00000;            //PA10, PA11 Alternate function mode
    GPIOB->AFR[1] |= 7 << 8 | 7 << 12;     //USART3 AFRH10, AFRH11
}

void USART_Config(void)
{
	RCC->APB1ENR |= 1 << 18;               //USART3EN


}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART_Config();

  while (1)
  {

  }
}
