#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

typedef struct
{
	GPIO_TypeDef* IN0_Port;
	GPIO_TypeDef* IN1_Port;
	GPIO_TypeDef* IN2_Port;
	GPIO_TypeDef* IN3_Port;
	GPIO_TypeDef* OUT0_Port;
	GPIO_TypeDef* OUT1_Port;
	GPIO_TypeDef* OUT2_Port;
	GPIO_TypeDef* OUT3_Port;

	uint16_t	IN0pin;
	uint16_t	IN1pin;
	uint16_t	IN2pin;
	uint16_t	IN3pin;
	uint16_t	OUT0pin;
	uint16_t	OUT1pin;
	uint16_t	OUT2pin;
	uint16_t	OUT3pin;

}Keypad_WiresTypeDef;

void Keypad4x4_Init(Keypad_WiresTypeDef  *KeypadWiringStruct);
static void Keypad4x4_FindPins_positions(void);
static void Keypad4x4_ChangeColomn(uint8_t colNum_0_to_3);
void Keypad4x4_ReadKeypad(bool keys[16]);
char* Keypad4x4_GetChar(uint8_t keypadSw);

#endif /* KEYPAD_H_ */
