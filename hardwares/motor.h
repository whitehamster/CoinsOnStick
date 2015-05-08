#ifndef __MOTOT_H
#define __MOTOT_H
#include "stm32f30x.h"

//IO�ڲ����궨��
#define BitBand_ADDR(addr)	(*((volatile unsigned long *)(addr)))
#define GPIOA_ODR_Addr    (GPIOA_BASE+0x14) //0x48000014
//���, sΪ 0~1, nȡ 0~31
#define PAout(n,s)		(s?(BitBand_ADDR(GPIOA_ODR_Addr)|=(1<<n)):(BitBand_ADDR(GPIOA_ODR_Addr)&=(~(1<<n))))

#define TOSTEP (1.8/8)

extern float Angle_pre; //��ǰ�Ƕ�
extern uint8_t SetZeroPoint_Flag;//������� ��־λ
extern float Angle_ZeroPoint;//���ƫ�Ƶ�
void StepMotor_init(void);
void StepMotor_IOconf(void);
void StepMotor_move(float Angle_now);
void SetZeroPoint(void);//�������
float AcculateMotorMoveAngle(void);//��������ת�Ƕ�ֵ
#endif
