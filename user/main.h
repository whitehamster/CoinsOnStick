#ifndef _main_H_
#define _main_H_

#define __FPU_PRESENT 1

#ifndef  __TARGET_FPU_VFP 
#define __TARGET_FPU_VFP
#endif

#ifndef  ARM_MATH_CM4 
#define ARM_MATH_CM4
#endif

#include "stm32f30x.h"
#include "stm32f30x_it.h"
#include "usart.h"
#include "delay.h"
#include "mpu6050.h"
#include <stdio.h>
#include "arm_math.h"
#include "cal.h"
#include "tim.h"
#include "exti.h"
//#include <math.h>

#endif
