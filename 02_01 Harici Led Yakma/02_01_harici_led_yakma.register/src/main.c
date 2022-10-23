#include "stm32f4xx.h"

/*
extern uint32_t SystemCoreClock;

uint32_t systemClock;
*/


void RCC_Config(void)
{
	/*
	//RCC->CR &= 0x00000083;             //RESET

	RCC->CR &= ~(1 << 0);                //HSION
	RCC->CR |= 1 << 16;                  //HSEON
	while(!(RCC->CR & (1 << 17)));       //HSERDY
	RCC->CR |= 1 << 19;                  //CSSON
	RCC->CFGR = 0x00000000;
	RCC->PLLCFGR |= (1 << 22);           //PLLSRC
	//RCC->PLLCFGR &= ~(1 << 0);         //PLLM0 0
	//RCC->PLLCFGR &= ~(1 << 1);         //PLLM1 0
	//RCC->PLLCFGR |= (1 << 2);          //PLLM2 1
	//RCC->PLLCFGR &= ~(1 << 3);         //PLLM3 0
	//RCC->PLLCFGR &= ~(1 << 4);         //PLLM4 0
	//RCC->PLLCFGR &= ~(1 << 5);         //PLLM5 0
	RCC->PLLCFGR |= (4 << 0);            //PLLM 4
	RCC->PLLCFGR |= (168 << 6);          //PLLN 168
	//RCC->PLLCFGR &= ~(1 << 16);        //PLLP1 0
	//RCC->PLLCFGR &= ~(1 << 17);        //PLLP2 0

	RCC->CR |= 1 << 24;                  //PLLON
	while(!(RCC->CR & (1 << 25)));       //PLLRDY

	RCC->CFGR &= ~(1 << 0);
	RCC->CFGR |= (1 << 1);               //SW

	while(!(RCC->CR & (1 << 1)));       //SWS
	*/

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
	//systemClock=SystemCoreClock;      //168 000 000

	//RCC_DeInit();                     //HSI ON PLL OFF

	//SystemCoreClockUpdate();
	//systemClock=SystemCoreClock;      //16 000 000

	RCC_Config();
	SystemCoreClockUpdate();
	//systemClock=SystemCoreClock;        //168 000 000

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

