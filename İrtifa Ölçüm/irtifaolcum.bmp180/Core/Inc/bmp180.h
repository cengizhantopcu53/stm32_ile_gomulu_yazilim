/*
 * bmp180.h
 *
 *  Created on: Apr 25, 2022
 *      Author: cengi
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

//Device W/R Register Address
#define BMP180_DEVICE_WRITE_REGISTER_ADDRESS 0xEE
#define BMP180_DEVICE_READ_REGISTER_ADDRESS 0xEF

//Calibration Value Length
#define BMP180_CALIBRATION_VALUE_LENGTH 22

//Calibration Address Start
#define BMP180_CALIBRATION_ADDRESS_START 0xAA

//Standard Atmospheric Pressure
#define atmPress 101325

void BMP180_Init(void);
void BMP180_Get_Calibration_Value(void);
void BMP180_Get_Uncompensated_Temperature(void);
float BMP180_Get_Temperature(void);
void BMP180_Get_Uncompensated_Pressure(void);
float BMP180_Get_Pressure(void);
float BMP180_Get_Altitude(void);

#endif /* INC_BMP180_H_ */
