#ifndef __MOTOT_H
#define __MOTOT_H
#include "stm32f30x.h"

//IO口操作宏定义
#define BitBand_ADDR(addr)	(*((volatile unsigned long *)(addr)))
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x48000014
//输出, s为 0~1, n取 0~31
#define PAout(n,s)		(s?(BitBand_ADDR(GPIOA_ODR_Addr)|=(1<<n)):(BitBand_ADDR(GPIOA_ODR_Addr)&=(~(1<<n))))

#define STEP (1.8/8)

extern double Angle_pre; //先前角度

void StepMotor_init();
void StepMotor_IOconf(void);
void StepMotor_move(double Angle_now);
#endif
