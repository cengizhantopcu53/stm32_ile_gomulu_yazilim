#include "stm32f4xx.h"

int i=0;

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

void DAC1_Config(void)
{
	RCC->APB1ENR |= 0x20000000;          //DACEN
	RCC->AHB1ENR |= 0x00000001;          //A clock enable

	DAC->CR |= 0x00000001;               //DAC channel1 enabled
	DAC->SWTRIGR |= 0x00000000;          //Software trigger disabled
	DAC->DHR12R1 |= 0x00000000;          //DAC channel1 12-bit right-aligned data
}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	DAC1_Config();

  while (1)
  {
	  for(;i<4096; i++)
	  {
		  DAC->DHR12R1 |= i;
		  delay(16800);
	  }
	  i=0;
  }
}
