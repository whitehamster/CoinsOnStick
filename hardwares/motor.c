/*	
	*�̷ܽ���:
			PA.4	paulse
			PA.5	direction
	*�㷨˵��: 
		
	*����:
		����
	*ʱ��:
		2015/5/4
	*����:
		YES: 
		NO:  
*/



#include "motor.h"
#include "MPU6050.h"
#include "delay.h"
#include "usart.h"
#include <math.h>

double Angle_pre = 0;

/*
	*����	���������ʼ��
	*ʹ������
			�ⲿ�жϼ�⺯�� EXTI0_Config() ��ʼ�����5ms��
	*�����ⲿ���������
			(double)angleY
	*����	
			��
	*���	
			��
*/
void StepMotor_init()
{
	double Angle_now;
	Angle_now = angleY;
	Angle_pre = Angle_now;
	printf("Angle_now = angleY = 0\n");
}
/*
	*����	�����������
	*����
			��ǰ�Ƕ�	Angle_pre
	*����	
			��Ҫ��Ƕ�	(double)Angle_now
	*���	
			��
*/
void StepMotor_move(double Angle_now)
{
	double AngleToMove = 0;
	double StepToMove = 0;
	if(Angle_now != Angle_pre){
		AngleToMove = Angle_now - Angle_pre;
		if(AngleToMove < 0.0){
			PAout(5,1);		//��ת
		}
		else if(AngleToMove > 0.0){
			PAout(5,0);		//��ת
		}
		StepToMove = fabs(AngleToMove/STEP);
		for(;StepToMove>0;StepToMove--){
			PAout(4,0);
			delay_ms(2);
			PAout(4,1);
			delay_ms(2);
			PAout(4,0);
		}
		Angle_pre = Angle_now;
	}
}
/*
	*����	�ܽ�����
			PA.2	paulse
			PA.3	direction
	*����	��
	*���	��
*/
void StepMotor_IOconf(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* PA.4 PA.5	�������50MHz */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

