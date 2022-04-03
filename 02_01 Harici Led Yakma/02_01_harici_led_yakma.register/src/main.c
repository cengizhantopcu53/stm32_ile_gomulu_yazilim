#include "stm32f4xx.h"

void RCC_Config(void)
{
	RCC->CR &= ~(1 << 0);                //HSION
	RCC->CR |= 1 << 16;                  //HSEON
	while(!(RCC->CR & (1 << 17)));       //HSERDY
	RCC->CR |= 1 << 19;                  //CSSON
	RCC->CFGR = 0x00000000;
	RCC->PLLCFGR |= (1 << 22);           //PLLSRC
	RCC->PLLCFGR |= (4 << 0);            //PLLM 4
	RCC->PLLCFGR |= (168 << 6);          //PLLN 168
	RCC->CR |= 1 << 24;                  //PLLON
	while(!(RCC->CR & (1 << 25)));       //PLLRDY
	RCC->CFGR &= ~(1 << 0);
	RCC->CFGR |= (1 << 1);               //SW
	while(!(RCC->CR & (1 << 1)));        //SWS
}

void GPIO_Config(void)
{
	RCC->AHB1ENR |= (1 << 3);            //D clock enable

	//output mode
	GPIOD->MODER |= 1 << 24;          //PD12
	GPIOD->MODER &= ~(1 << 25);
	GPIOD->MODER |= 1 << 26;          //PD13
	GPIOD->MODER &= ~(1 << 27);
	GPIOD->MODER |= 1 << 28;          //PD14
    GPIOD->MODER &= ~(1 << 29);
    GPIOD->MODER |= 1 << 30;          //PD15
    GPIOD->MODER &= ~(1 << 31);

    //GPIOD->OSPEEDR |= 1 << 24;
    //GPIOD->OSPEEDR |= 1 << 25;
    //GPIOD->OSPEEDR |= 1 << 26;
    //GPIOD->OSPEEDR |= 1 << 27;
    //GPIOD->OSPEEDR |= 1 << 28;
    //GPIOD->OSPEEDR |= 1 << 29;
    //GPIOD->OSPEEDR |= 1 << 30;
    //GPIOD->OSPEEDR |= 1 << 31;
    GPIOD->OSPEEDR |= 0xFF000000;     //Very high speed
    //GPIOD ->OSPEEDR |= FF << 24;
}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();

	GPIO_Config();

  while (1)
  {
	  //set
	  GPIOD->ODR |= 1 << 12;
	  GPIOD->ODR |= 1 << 13;
	  GPIOD->ODR |= 1 << 14;
	  GPIOD->ODR |= 1 << 15;

	  for(int i=0; i<1680000; i++);

	  //reset
	  GPIOD->ODR |= ~(1 << 12);
	  GPIOD->ODR |= ~(1 << 13);
	  GPIOD->ODR |= ~(1 << 14);
	  GPIOD->ODR |= ~(1 << 15);

	  for(int i=0; i<1680000; i++);
  }
}
