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
	RCC->AHB1ENR |= 0x00000008;                                     //D clock enable

    GPIOD->MODER |= 2 << 24 | 2 << 26 | 2 << 28 | 2 << 30;          //PD12, PD13, PD14, PD15
    GPIOD->AFR[1] |= 2 << 16 | 2 << 20 | 2 << 24 | 2 << 28;         //TIM4 AFRH12, AFRH13, AFRH14, AFRH15
    GPIOD->OTYPER |= 0x00000000;                                    //Output push-pull
    GPIOD->OSPEEDR |= 0xFF000000;                                   //Very high speed
    GPIOD->PUPDR |= 0x00000000;                                     //No pull-up, pull-down
}

void TIM_Config(void)
{
	RCC->APB1ENR |= 0x00000004;                           //TIM4EN

	TIM4->CR1 |= 0 << 4;                                  //DIR Counter used as up counter
	TIM4->CR1 |= 0 << 5;                                  //CMS Edge-aligned mode
	TIM4->CR1 |= 0 << 8;                                  //tDTS = tCK_INT 84MHz
	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;    //Capture/Compare selected output, PWM mode 1 (1 & 2)
	TIM4->CCMR2 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;    //output, PWM mode 1 selected (3 & 4)
	TIM4->CCER |= 1 << 0 | 1 << 4 | 1 << 8 | 1 << 12;     //output enable (1, 2, 3 & 4 )
	TIM4->PSC |= 41999;                                   //PSC Prescaler value
	TIM4->ARR |= 1999;                                    //ARR Auto-reload value
	TIM4->CCR1 |= 500;                                    //PD12
	TIM4->CCR2 |= 1000;                                   //PD13
	TIM4->CCR3 |= 1500;                                   //PD14
	TIM4->CCR4 |= 1999;                                   //PD15
	TIM4->CR1 |= 1 << 0;                                  //CEN Counter enabled
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();

  while (1)
  {

  }
}
