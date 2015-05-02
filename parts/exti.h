#ifndef _exti_H_
#define _exti_H_

#include "stm32f30x.h"
#include "mpu6050.h"

#define MPU6050_INT_Line EXTI_Line0

void MPU6050_Exti_Config(void);

#endif
