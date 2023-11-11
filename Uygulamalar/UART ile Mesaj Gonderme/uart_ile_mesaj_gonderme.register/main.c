#include "stm32f4xx.h"
#include "string.h"

char Rx_Buff[100];
int i=0;

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

	USART3->BRR |= 0x1117;                 //BaudRate 9600
	USART3->CR1 |= (1 << 2);               //Receiver Enable
	USART3->CR1 |= (1 << 3);               //Transmitter Enable
	USART3->CR1 |= (1 << 5);               //RXNE Interrupt Enable
	USART3->CR1 |= (0 << 10);              //Parity Control Disabled
	USART3->CR1 |= (0 << 12);              //Word Length 8 Data Bits
	USART3->CR2 |= (0 << 12);              //1 Stop bit
	USART3->CR1 |= (1 << 13);              //USART Enable
}

void NVIC_Config(void)
{
	NVIC->ISER[1] |= (1 <<7 )              //Interrupt Set Enable Register
}

USART_IRQHandler()
{
	volatile int Str;
	Str= USART3->DR;
	i++;
}

void Send_Char(char message)
{
	while(!(USART3->SR & 1 << 7));
	USART3->DR=message;
}

void Send_Message(char *Str)
{
	while(*Str){
		Send_Char(*Str);
		Str;
	}
}

int BRR(double baud)
{
	double decimal = (42*1000000)/(baud*16);

	int Mantissa = (int)decimal;
	int Fraction = ceil((decimal-Mantissa)*16);

	return ((Mantissa << 4) + Fraction);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	USART_Config();
	NVIC_Config();

  while (1)
  {
		Send_Message("Hello World \n");
		for(int i=0; i<1000000; i++);
  }
}
