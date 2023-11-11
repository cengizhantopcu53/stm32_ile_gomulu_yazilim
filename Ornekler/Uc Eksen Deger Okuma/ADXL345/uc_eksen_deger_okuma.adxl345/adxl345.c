#include "adxl345.h"

#define PI 3.14159265359
#define SCALE_FACTOR 128

uint8_t myDatas[6];

struct Adxl_Data
{
	float RAWaccelX,RAWaccelY,RAWaccelZ;
	float Ax, Ay, Az;
	float AccelRoll, AccelPitch;
	float Roll, Pitch;
}Adxl345;

void ADXL345_ScanAdress(void)
{
	for(int i=0; i<=255; i++)
	{
		if(HAL_I2C_IsDeviceReady(ADXL345_I2C, i, 1, 10) == HAL_OK)
			break;
	}
}

void ADXL345_Init(void)
{
	ADXL345_Read(DEVID_ID, 1);
	ADXL345_Write(POWER_CTL, 0);
	ADXL345_Write(POWER_CTL, 0x08);        //Measure Bit SET
	ADXL345_Write(DATA_FORMAT, 0x01);      //Range Bit +-4g
	ADXL345_Offset(0x00, 0x00, 0x00);
}

void ADXL345_Write(uint8_t rRegister, uint8_t value)
{
	uint8_t data[2] = {0};
	data[0] = rRegister;
	data[1] = value;

	HAL_I2C_Master_Transmit(ADXL345_I2C, ADXL345_ADDRESS, data, 2, 100);
}

void ADXL345_Read(uint8_t rRegister, uint8_t numberOfBytes)
{
	HAL_I2C_Mem_Read(ADXL345_I2C, ADXL345_ADDRESS, rRegister, 1, myDatas, numberOfBytes, 100);
}

void ADXL345_AccelRead(void)
{
	ADXL345_Read(DATAX0, 6);

	Adxl345.RAWaccelX= (myDatas[1] << 8) | myDatas[0];
	Adxl345.RAWaccelY= (myDatas[3] << 8) | myDatas[2];
	Adxl345.RAWaccelZ= (myDatas[5] << 8) | myDatas[4];

	Adxl345.Ax = Adxl345.RAWaccelX/128;
	Adxl345.Ay = Adxl345.RAWaccelY/128;
	Adxl345.Az = Adxl345.RAWaccelZ/128;

	Adxl345.AccelRoll = atan(Adxl345.Ay / sqrt(pow(Adxl345.Ax, 2) + pow(Adxl345.Az, 2))) * 180 / PI;
	Adxl345.AccelPitch = atan(-1 * Adxl345.Ax / sqrt(pow(Adxl345.Ay, 2) + pow(Adxl345.Az, 2))) * 180 / PI;

	//Low-pass filter
	Adxl345.Roll = 0.94 * Adxl345.Roll + 0.06 * Adxl345.AccelRoll;
	Adxl345.Pitch = 0.94 * Adxl345.Pitch + 0.06 * Adxl345.AccelPitch;
}

void ADXL345_Offset(int8_t ofs_x, int8_t ofs_y, int8_t ofs_z)
{
	ADXL345_Write(OFSX, (uint8_t) ofs_x);
	ADXL345_Write(OFSY, (uint8_t) ofs_y);
	ADXL345_Write(OFSZ, (uint8_t) ofs_z);
}













