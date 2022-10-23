/*
 * bmp180.c
 *
 *  Created on: Apr 25, 2022
 *      Author: cengi
 */

#include "bmp180.h"
#include "math.h"

//Calibration Value
short AC1 = 0;
short AC2 = 0;
short AC3 = 0;
unsigned short AC4 = 0;
unsigned short AC5 = 0;
unsigned short AC6 = 0;
short B1 = 0;
short B2 = 0;
short MB = 0;
short MC = 0;
short MD = 0;

//Calculate Value
long UT = 0;
long UP = 0;
long X1 = 0;
long X2 = 0;
long X3 = 0;
long B3 = 0;
long B5 = 0;
unsigned long B4 = 0;
long B6 = 0;
unsigned long B7 = 0;

long Temp = 0;
long Press = 0;

void BMP180_Init(void)
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 1, 100000) != HAL_OK)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

	BMP180_Get_Calibration_Value();
}

void BMP180_Get_Calibration_Value(void)
{
	uint8_t Calib_Buff[BMP180_CALIBRATION_VALUE_LENGTH] = {0};

	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_READ_REGISTER_ADDRESS, BMP180_CALIBRATION_ADDRESS_START, 1, Calib_Buff, BMP180_CALIBRATION_VALUE_LENGTH, 100);

	AC1 = ((Calib_Buff[0] << 8) | Calib_Buff[1]);
	AC2 = ((Calib_Buff[2] << 8) | Calib_Buff[3]);
	AC3 = ((Calib_Buff[4] << 8) | Calib_Buff[5]);
	AC4 = ((Calib_Buff[6] << 8) | Calib_Buff[7]);
	AC5 = ((Calib_Buff[8] << 8) | Calib_Buff[9]);
	AC6 = ((Calib_Buff[10] << 8) | Calib_Buff[11]);
	B1 = ((Calib_Buff[12] << 8) | Calib_Buff[13]);
	B2 = ((Calib_Buff[14] << 8) | Calib_Buff[15]);
	MB = ((Calib_Buff[16] << 8) | Calib_Buff[17]);
	MC = ((Calib_Buff[18] << 8) | Calib_Buff[19]);
	MD = ((Calib_Buff[20] << 8) | Calib_Buff[21]);
}

void BMP180_Get_Uncompensated_Temperature(void)
{
	uint8_t datatowrite = 0x2E;
	HAL_I2C_Mem_Write(&hi2c1, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
	HAL_Delay(5);

	uint8_t datatoread[2] = {0};
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_READ_REGISTER_ADDRESS, 0xF6, 1, datatoread, 2, 1000);
	UT = ((datatoread[0] << 8) | datatoread[1]);
}

float BMP180_Get_Temperature(void)
{
	BMP180_Get_Uncompensated_Temperature();

	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));

	B5 = X1+X2;
	Temp = (B5+8)/(pow(2,4));
	return Temp*0.1;
}


void BMP180_Get_Uncompensated_Pressure(void)
{
	short oss = 3;
	uint8_t datatowrite = 0x34 | (oss << 6);
	HAL_I2C_Mem_Write(&hi2c1, BMP180_DEVICE_WRITE_REGISTER_ADDRESS, 0xF4, 1, &datatowrite, 1, 1000);
	switch (oss)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	uint8_t datatoread[3] = {0};
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_READ_REGISTER_ADDRESS, 0xF6, 1, datatoread, 3, 1000);
	UP = (((datatoread[0] << 16) | (datatoread[1] << 8) | datatoread[2]) >> (8-oss));
}

float BMP180_Get_Pressure(void)
{
	BMP180_Get_Uncompensated_Pressure();

	short oss = 3;
	B6 = B5-4000;
	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
	X2 = AC2*B6/(pow(2,11));
	X3 = X1+X2;
	B3 = (((AC1*4+X3)<<oss)+2)/4;
	X1 = AC3*B6/pow(2,13);
	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
	X3 = ((X1+X2)+2)/pow(2,2);
	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
	B7 = ((unsigned long)UP-B3)*(50000>>oss);
	if (B7<0x80000000) Press = (B7*2)/B4;
	else Press = (B7/B4)*2;
	X1 = (Press/(pow(2,8)))*(Press/(pow(2,8)));
	X1 = (X1*3038)/(pow(2,16));
	X2 = (-7357*Press)/(pow(2,16));
	Press = Press + (X1+X2+3791)/(pow(2,4));
	return Press;
}

float BMP180_Get_Altitude(void)
{
	BMP180_Get_Pressure();

	return 44330*(1-(pow(((float)Press/(float)atmPress), 0.19029495718)));
}

