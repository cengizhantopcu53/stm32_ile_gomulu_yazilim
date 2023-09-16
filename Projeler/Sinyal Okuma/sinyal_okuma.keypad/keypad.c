#include "keypad.h"

static Keypad_WiresTypeDef KeypadStruct;
static uint8_t OutPositions[4];

static char *Keypad_keys[16] =
{
	"1",
	"2",
	"3",
	"A",
	"4",
	"5",
	"6",
	"B",
	"7",
	"8",
	"9",
	"C",
	"*",
	"0",
	"#",
	"D"
};

void Keypad4x4_Init(Keypad_WiresTypeDef  *KeypadWiringStruct)
{
	KeypadStruct = *KeypadWiringStruct;

	Keypad4x4_FindPins_positions();

	KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
	KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
	KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);
	KeypadStruct.OUT3_Port->OTYPER |= (1UL << OutPositions[3]);

	HAL_GPIO_WritePin(KeypadStruct.OUT0_Port, KeypadStruct.OUT0pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KeypadStruct.OUT1_Port, KeypadStruct.OUT1pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KeypadStruct.OUT2_Port, KeypadStruct.OUT2pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KeypadStruct.OUT3_Port, KeypadStruct.OUT3pin, GPIO_PIN_SET);
}

static void Keypad4x4_FindPins_positions(void)
{
	uint8_t idx=0;
	for(idx=0; idx<16; idx++)
	{
		if(((KeypadStruct.OUT0pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[0] = idx;
		}
		if(((KeypadStruct.OUT1pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[1] = idx;
		}
		if(((KeypadStruct.OUT2pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[2] = idx;
		}
		if(((KeypadStruct.OUT3pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[3] = idx;
		}
	}
}

static void Keypad4x4_ChangeColomn(uint8_t colNum_0_to_3)
{
	if(colNum_0_to_3==0)
	{
		KeypadStruct.OUT0_Port->OTYPER &= ~(1UL << OutPositions[0]);

		KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
		KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);
		KeypadStruct.OUT3_Port->OTYPER |= (1UL << OutPositions[3]);
	}
	else if(colNum_0_to_3==1)
	{
		KeypadStruct.OUT1_Port->OTYPER &= ~(1UL << OutPositions[1]);

		KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
		KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);
		KeypadStruct.OUT3_Port->OTYPER |= (1UL << OutPositions[3]);
	}
	else if(colNum_0_to_3==2)
	{
		KeypadStruct.OUT2_Port->OTYPER &= ~(1UL << OutPositions[2]);

		KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
		KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
		KeypadStruct.OUT3_Port->OTYPER |= (1UL << OutPositions[3]);
	}
	else if(colNum_0_to_3==3)
	{
		KeypadStruct.OUT3_Port->OTYPER &= ~(1UL << OutPositions[3]);

		KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
		KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
		KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);
	}
}

void Keypad4x4_ReadKeypad(bool keys[16])
{
	Keypad4x4_ChangeColomn(0);
	keys[0] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[4] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[8] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[12] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

	Keypad4x4_ChangeColomn(1);
	keys[1] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[5] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[9] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[13] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

	Keypad4x4_ChangeColomn(2);
	keys[2] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[6] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[10] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[14] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

	Keypad4x4_ChangeColomn(3);
	keys[3] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[7] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[11] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[15] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);
}

char* Keypad4x4_GetChar(uint8_t keypadSw)
{
	return Keypad_keys[keypadSw];
}



