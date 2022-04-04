#include "stm32f4xx.h"

uint8_t adc_value;

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
	RCC->AHB1ENR |= 0x00000001;          //A clock enable

    GPIOA->MODER |= 0x00000003;          //PA0 Analog mode
    GPIOA->OSPEEDR |= 0xFF000000;        //Very high speed
}

void ADC_Config(void)
{
	RCC->APB2ENR |= 0x00000100;          //ADC1

	ADC1->CR1 |= 0x02000000;             //RES 8-bit
	ADC1->CR2 |= 0x00000001;             //ADON
	ADC1->SMPR2 |= 0x00000003;           //SMP0 56 cycles
	ADC->CCR |= 0x00010000;              //ADCPRE 4
}

uint8_t Read_ADC()
{
	uint8_t value;

	ADC1->CR2 |= 0x40000000;             //SWSTART
	while(!(ADC1->SR & 0x00000002));     //EOC

	value=ADC1->DR;                      //DATA
	return value;
}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	GPIO_Config();
	ADC_Config();

  while (1)
  {
	  adc_value = Read_ADC();
  }
}
