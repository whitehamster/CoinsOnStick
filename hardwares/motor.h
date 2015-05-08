#ifndef __MOTOT_H
#define __MOTOT_H
#include "stm32f30x.h"

//IO口操作宏定义
#define BitBand_ADDR(addr)	(*((volatile unsigned long *)(addr)))
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x48000014
//输出, s为 0~1, n取 0~31
#define PAout(n,s)		(s?(BitBand_ADDR(GPIOA_ODR_Addr)|=(1<<n)):(BitBand_ADDR(GPIOA_ODR_Addr)&=(~(1<<n))))

#define TOSTEP (1.8/8)

extern float Angle_pre; //先前角度
extern uint8_t SetZeroPoint_Flag;//设置零点 标志位
extern float Angle_ZeroPoint;//零点偏移点
void StepMotor_init(void);
void StepMotor_IOconf(void);
void StepMotor_move(float Angle_now);
void SetZeroPoint(void);//设置零点
float AcculateMotorMoveAngle(void);//计算电机需转角度值
#endif
