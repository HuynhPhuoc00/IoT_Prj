/*
 * MPU6050.h
 *
 *  Created on: May 2, 2025
 *      Author: Administrator
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f411.h"

#define MPU6050_ADDR 0x68

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

void MPU_Init(I2C_RegDef_t *pI2Cx);
void MPU_Read(I2C_RegDef_t *pI2Cx, uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size);
void MPU_Write(I2C_RegDef_t *pI2Cx, uint8_t Address, uint8_t Reg, uint8_t Data);
void MPU6050_Read_Accel(I2C_RegDef_t *pI2Cx);

#endif /* INC_MPU6050_H_ */
