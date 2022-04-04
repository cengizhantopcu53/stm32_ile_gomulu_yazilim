#include "stm32f4xx.h"

uint8_t adc;
uint8_t adc1[8];

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
	RCC->AHB1ENR |= 0x00000001;          //A clock enable

    GPIOA->MODER |= 0x00000003;          //PA0 Analog mode
    GPIOA->OSPEEDR |= 0x00000003;        //Very high speed
}

void ADC_Config(void)
{
	RCC->APB2ENR |= 0x00000100;          //ADC1

	ADC1->CR1 |= 1 << 8;                 //SCAN
	ADC1->CR1 |= 0 << 24;                //RES 12-bit
	ADC1->CR2 |= 1 << 0;                 //ADON
	ADC1->CR2 |= 1 << 1;                 //CONT
	ADC1->CR2 |= 1 << 8;                 //DMA
	ADC1->CR2 |= 1 << 9;                 //DDS
	ADC1->CR2 |= 1 << 10;                //EOCS
	ADC1->CR2 |= 1 << 30;                //SWSTART
	ADC1->SMPR2 |= 0x00000003;           //SMP0 56 cycles
	ADC1->SQR1 |= 0 << 20;               //1 conversion
	ADC1->SQR3 |= 0 << 0;                //SQ1
	ADC->CCR |= 0x00010000;              //ADCPRE 4
}

void DMA_Config(void)
{
	RCC->AHB1ENR |= 0x00400000;          //DMA2

	while((DMA2_Stream4->CR & 0x00000001) == 1);
	DMA2_Stream4->PAR |= (uint8_t) &ADC1->DR;            //PAR Peripheral address
	DMA2_Stream4->M0AR |= (uint8_t) &adc1;              //M0A Memory 0 address
	DMA2_Stream4->CR |= 0 << 6;                          //DIR
	DMA2_Stream4->CR |= 1 << 8;                          //CIRC
	DMA2_Stream4->CR |= 0 << 9;                          //PINC
	DMA2_Stream4->CR |= 1 << 10;
	DMA2_Stream4->CR |= 2 << 11;                         //PSIZE Word (32-bit)
	DMA2_Stream4->CR |= 2 << 13;                         //MSIZE Word (32-bit)
	DMA2_Stream4->CR |= 3 << 16;                         //PL
	DMA2_Stream4->CR |= 0 << 25;                         //CHSEL
	DMA2_Stream4->NDTR |= 1;                             //NDT
	DMA2_Stream4->FCR |= 0 << 1;                         //FTH 1/2 full FIFO
	DMA2_Stream4->CR |= 1 << 0;                          //EN Stream enabled
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	DMA_Config();
	//ADC1->CR2 |= ADC_CR2_SWSTART;
	ADC1->CR2 |= 0x40000000;

  while (1)
  {

  }
}
