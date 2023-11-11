	#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

extern  I2C_HandleTypeDef hi2c1;
#define MPU6050_I2C &hi2c1

#define MPU6050_ADRESS 0xD0 		//AD0 is GND, 7 bit address is 0x68, 8 bit address 0x68<<1 = 0xD0
									//AD0 is VCC, 7 bit address is 0x69, 8 bit address 0x69<<1 = 0xD2

#define MPU_REG_SELF_TEST_X	        0x0D
#define MPU_REG_SELF_TEST_Y			0x0E
#define MPU_REG_SELF_TEST_Z			0x0F
#define MPU_REG_SELF_TEST_A			0x10
#define MPU_REG_SMPLRT_DIV			0x19
#define MPU_REG_CONFIG				0x1A
#define MPU_REG_GYRO_CONFIG			0x1B
#define MPU_REG_ACCEL_CONFIG		0x1C
#define MPU_REG_ACCEL_XOUT_H		0x3B
#define MPU_REG_ACCEL_XOUT_L		0x3C
#define MPU_REG_ACCEL_YOUT_H		0x3D
#define MPU_REG_ACCEL_YOUT_L		0x3E
#define MPU_REG_ACCEL_ZOUT_H		0x3F
#define MPU_REG_ACCEL_ZOUT_L		0x40
#define MPU_REG_ACCEL_TEMP_OUT_H 	0x41
#define MPU_REG_ACCEL_TEMP_OUT_L	0x42
#define MPU_REG_GYRO_XOUT_H			0x43
#define MPU_REG_GYRO_XOUT_L			0x44
#define MPU_REG_GYRO_YOUT_H			0x45
#define MPU_REG_GYRO_YOUT_L			0x46
#define MPU_REG_GYRO_ZOUT_H			0x47
#define MPU_REG_GYRO_ZOUT_L			0x48
#define MPU_REG_USER_CTRL			0x6A
#define MPU_REG_PWR_MGMT_1			0x6B
#define MPU_REG_PWR_MGMT_2			0x6C
#define MPU_REG_FIFO_COUNTH 		0x72
#define MPU_REG_FIFO_COUNTL 		0x73
#define MPU_REG_FIFO_R_W			0x74
#define MPU_REG_WHO_AM_I			0x75

typedef enum {
	FS_250 = 0,
	FS_500 = 1,
	FS_1000 = 2,
	FS_2000 = 3
}fs_sel;

typedef enum {
	AFS_2G = 0,
	AFS_4G = 1,
	AFS_8G = 2,
	AFS_16G = 3
}afs_sel;

void MPU6050_ScanAdress(void);
void MPU6050_Init(void);
void MPU6050_PowerOn(void);
void MPU6050_Sampling(void);
void MPU6050_GyroScale(fs_sel scale);
void MPU6050_AccelScale(afs_sel scale);
void MPU6050_GyroRead(void);
void MPU6050_AccelRead(void);

#endif /* INC_MPU6050_H_ */
