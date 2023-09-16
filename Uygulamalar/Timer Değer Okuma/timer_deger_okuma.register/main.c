#include "stm32f4xx.h"

uint16_t count = 0;

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

void TIM_Config(void)
{
	RCC->APB1ENR |= 0x00000001;          //TIM2EN

	TIM2->CR1 |= 0 << 4;                 //DIR Counter used as up counter
	TIM2->CR1 |= 0 << 5;                 //CMS Edge-aligned mode
	TIM2->CR1 |= 0 << 8;                 //tDTS = tCK_INT 84MHz
	TIM2->SMCR |= 0 << 0;                //SMS Slave mode disabled
	TIM2->EGR |= 1 << 0;                 //UG Update generation
	TIM2->PSC |= 41999;                  //PSC Prescaler value
	TIM2->ARR |= 1999;                   //ARR Auto-reload value
	TIM2->CR1 |= 1 << 0;                 //CEN Counter enabled
}

int main(void)
{
	RCC_Config();
	TIM_Config();

  while (1)
  {
	  count = TIM2->CNT;

  }
}
