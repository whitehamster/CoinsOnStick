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
#include "cal.h"
#include "MPU6050.h"
#include "extern_variable.h"
#include "math.h"





/*
	*����	���������ʼ��
	*ʹ������
			�ⲿ�жϼ�⺯�� EXTI0_Config() ��ʼ�����5ms��
	*�����ⲿ���������
			(float)angleY
	*����	
			��
	*���	
			��
*/
float Angle_pre = 0;
void StepMotor_init(void)
{
	float Angle_now;
	
	Angle_now = 0;
	Angle_pre = Angle_now;
	//printf("Angle_now = angleY\n");
}

/*
	*����	�����������(���þ���������ת)
	*����
			��ǰ�Ƕ�	Angle_pre
	*����	
			��Ҫ��Ƕ�	(float)Angle_now
	*���	
			��
*/
void StepMotor_move(float Angle_now)
{
	float AngleToMove = 0.0;
	float StepToMove = 0.0;
	
	//printf("Angle_pre = %f\n",Angle_pre);
	if(Angle_now != Angle_pre){
		AngleToMove = Angle_now - Angle_pre;
		if(AngleToMove < 0.0f){
			PAout(5,0);		//��ת
		}
		else if(AngleToMove > 0.0){
			PAout(5,1);		//��ת
		}
		StepToMove = fabs(AngleToMove/TOSTEP);
		for(;StepToMove>2;StepToMove--){
			PAout(4,1);
			delay_us(500);
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

///*
//	*����	������Ư��
//*/

//void SetZeroPoint(void)
//{
//	float Q_ANGLE_temp[4] = {0};
//	uint8_t i = 0;
//	//printf("into SetZeroPoint\n");
//	while(1){
//		SetZeroPoint_Flag = 0;
//		while(SetZeroPoint_Flag == 0){
//			//printf("Q_ANGLE.Yaw = %f\n",Q_ANGLE.Yaw);
//		}
//		if(i==0){
//			Q_ANGLE_temp[0] = Q_ANGLE.Yaw;
//		}
//		else if(i==9){
//			Q_ANGLE_temp[1] = Q_ANGLE.Yaw;
//		}
//		else if(i==19){
//			Q_ANGLE_temp[2] = Q_ANGLE.Yaw;
//		}
//		else if(i==29){
//			Q_ANGLE_temp[3] = Q_ANGLE.Yaw;
//		}
//		i++;
//		if(i==30){
//			if((fabs(Q_ANGLE_temp[0]-Q_ANGLE_temp[1]) < 0.4)		\
//			&&(fabs(Q_ANGLE_temp[2]-Q_ANGLE_temp[3]) < 0.4)){
//				Angle_ZeroPoint = Q_ANGLE_temp[3];
//				break;
//			}
//			else{
//				i = 0;
//			}
//		}
//	}
//}
