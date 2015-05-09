#ifndef __MOTOT_H
#define __MOTOT_H
#include "stm32f30x.h"

//IO口操作宏定义
#define BitBand_ADDR(addr)	(*((volatile unsigned long *)(addr)))
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x48000014
//输出, s为 0~1, n取 0~31
#define PAout(n,s)		(s?(BitBand_ADDR(GPIOA_ODR_Addr)|=(1<<n)):(BitBand_ADDR(GPIOA_ODR_Addr)&=(~(1<<n))))

#define TOSTEP (1.8/2)


void StepMotor_init(void);
void StepMotor_IOconf(void);
void StepMotor_move(float Angle_now, uint8_t ms);
void SetZeroPoint(void);//设置零点
float AcculateMotorMoveAngle(void);//计算电机需转角度值
#endif
