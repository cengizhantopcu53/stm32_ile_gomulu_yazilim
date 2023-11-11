#ifndef ADXL345_H_
#define ADXL345_H_

#include "stdint.h"
#include "math.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

extern  I2C_HandleTypeDef hi2c1;
#define ADXL345_I2C &hi2c1

#define ADXL345_ADDRESS 0xA6    	//ALT ADDRESS is GND, 7 bit address is 0x53, 8 bit address 0x53<<1 = 0xA6

#define DEVID_ID			0x00
#define THRESH_TAP			0x1D
#define OFSX 			    0x1E
#define OFSY 				0x0F
#define OFSZ 				0x20
#define DUR 				0x21
#define Latent 				0x22
#define Window 				0x23
#define THRESH_ACT			0x24
#define THRESH_INACT		0x25
#define TIME_INACT			0x26
#define ACT_INACT_CTL		0x27
#define THRESH_FF			0x28
#define TIME_FF 			0x29
#define TAP_AXES			0x2A
#define ACT_TAP_STATUS		0x2B
#define BW_RATE 			0x2C
#define POWER_CTL			0x2D
#define INT_ENABLE			0x2E
#define INT_MAP 			0x2F
#define INT_SOURCE			0x30
#define DATA_FORMAT			0x31
#define DATAX0   			0x32
#define DATAX1   			0x33
#define DATAY0   			0x34
#define DATAY1   			0x35
#define DATAZ0   			0x36
#define DATAZ1   			0x37
#define FIFO_CTL  			0x38
#define FIFO_STATUS  		0x39

void ADXL345_ScanAdress(void);
void ADXL345_Init(void);
void ADXL345_Write(uint8_t rRegister, uint8_t value);
void ADXL345_Read(uint8_t rRegister, uint8_t numberOfBytes);
void ADXL345_AccelRead(void);
void ADXL345_Offset(int8_t ofs_x, int8_t ofs_y, int8_t ofs_z);

#endif /* ADXL345_H_ */
