#include "mpu6050.h"

extern float Ax, Ay, Az;
extern float Gx, Gy, Gz;

uint8_t Data;

int16_t RAWgyroX,RAWgyroY,RAWgyroZ;
int16_t RAWaccelX,RAWaccelY,RAWaccelZ;

void MPU6050_ScanAdress(void)
{
	for(int i=0; i<=255; i++)
	{
		if(HAL_I2C_IsDeviceReady(MPU6050_I2C, i, 1, 10) == HAL_OK)
			break;
	}
}

void MPU6050_Init(void)
{
	uint8_t Check;
	HAL_I2C_Mem_Read (MPU6050_I2C, MPU6050_ADRESS, MPU_REG_WHO_AM_I, 1, &Check, 1, 100);

	if (Check == 0x68){
		MPU6050_PowerOn();
		MPU6050_Sampling();
		MPU6050_GyroScale(FS_250);
		MPU6050_AccelScale(AFS_2G);
	}
}

void MPU6050_PowerOn(void)
{
	Data = 0x00;
	HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_PWR_MGMT_1, 1, &Data, 1, 100);
}

void MPU6050_Sampling(void)
{
	Data = 0x07;
	HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_SMPLRT_DIV, 1, &Data, 1, 100);
}

void MPU6050_GyroScale(fs_sel scale)
{
	Data = 0x00 | (scale << 3);
	HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_GYRO_CONFIG, 1, &Data, 1, 100);
}

void MPU6050_AccelScale(afs_sel scale)
{
	Data = 0x00 | (scale << 3);
	HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_ACCEL_CONFIG, 1, &Data, 1, 100);
}

void MPU6050_GyroRead(void)
{
	uint8_t gyroData[6];
	HAL_I2C_Mem_Read(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_GYRO_XOUT_H, 1, gyroData, 6, 100);

	RAWgyroX = (uint16_t) (gyroData[0] << 8 | gyroData[1]);
	RAWgyroY = (uint16_t) (gyroData[2] << 8 | gyroData[3]);
	RAWgyroZ = (uint16_t) (gyroData[4] << 8 | gyroData[5]);

	Gx = RAWgyroX/131.0;
	Gy = RAWgyroY/131.0;
	Gz = RAWgyroZ/131.0;
}

void MPU6050_AccelRead(void)
{
	uint8_t accelData[6];
	HAL_I2C_Mem_Read(MPU6050_I2C, MPU6050_ADRESS, MPU_REG_ACCEL_XOUT_H, 1, accelData, 6, 100);

	RAWaccelX = (uint16_t) (accelData[0] << 8 | accelData[1]);
	RAWaccelY = (uint16_t) (accelData[2] << 8 | accelData[3]);
	RAWaccelZ = (uint16_t) (accelData[4] << 8 | accelData[5]);

	Ax = RAWaccelX/16384.0;
	Ay = RAWaccelY/16384.0;
	Az = RAWaccelZ/16384.0;
}

