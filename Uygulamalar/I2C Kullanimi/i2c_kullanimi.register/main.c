#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i = 0;
uint8_t m_address = 0x4E, TCS_W_ADDRESS = 0xD0;

void RCC_Config()
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

void GPIO_Config()
{
	RCC->AHB1ENR  |=0x00000003;	         //A, B clock enable

	GPIOB->MODER  |=0x00A00000;	         //PB10, PB11 Alternate Function Mode
	GPIOB->AFR[1] |=0x00004400;          //I2C2 AFRH10, AFRH11
	GPIOB->OTYPER |=0x00000C00;          //Output open-drain
}

void I2C_Config()
{
	RCC->APB1ENR |= 0x00400000;		       //I2C2EN
	I2C2->CR2 |= 0x0008; 			           //8MHz 
	I2C2->CCR |= 0x0028; 			           //100kHz
	I2C2->TRISE |= 9;				             //Maximum rise time
	I2C2->CR1 |= 0x0001; 			           //Peripheral enable
}

void I2C_Write(uint8_t address, uint8_t data)
{
	I2C2->CR1 |= 0x0100; 		                  //Start Generation
	while(!(I2C2->SR1 & 0x0001));             //Start bit
	I2C2->DR = 0x4E; 	   		                  //Slave adres
	while(!(I2C2->SR1 & 0x0002));             //Received address matched
  while(!(I2C2->SR2 & 0x0001));             //Master Mod
	//I2C2->DR = address;		                  
	while(!(I2C2->SR2 & 0x0080));             //Data Register empty
	I2C2->DR = data;			                    
	while(!(I2C2->SR1 & 0x0080));             //Data byte transfer succeeded
	while(!(I2C2->SR1 & 0x0004));             
	I2C2->CR1 |= 0x0200;                      //Stop Generation
}

void delay(uint32_t time)
{
	while(time--);
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	I2C_Config();

  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  i++;
		  delay(6300000);
	  }

	  switch(i)
	  {
	  case 0:
		  I2C_Write(m_address, 0x00);
		  break;
	  case 1:
		  I2C_Write(m_address, 0x01);
		  break;
	  case 2:
		  I2C_Write(m_address, 0x02);
		  break;
	  case 3:
		  I2C_Write(m_address, 0x04);
		  break;
	  case 4:
		  I2C_Write(m_address, 0x08);
		  break;
	  case 5:
		  I2C_Write(m_address, 0x10);
		  break;
	  case 6:
		  I2C_Write(m_address, 0x20);
		  break;
	  case 7:
		  I2C_Write(m_address, 0x40);
		  break;
	  case 8:
		  I2C_Write(m_address, 0x80);
		  break;
	  default:
		  i=0;
		  break;
	  }
  }
}