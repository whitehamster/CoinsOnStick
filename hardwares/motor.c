/*	
	*管教分配:
			PA.4	paulse
			PA.5	direction
	*算法说明: 
		
	*作者:
		海璃
	*时间:
		2015/5/4
	*进度:
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
	*功能	步进电机初始化
	*使用条件
			外部中断检测函数 EXTI0_Config() 初始化完成5ms后
	*调用外部函数或变量
			(double)angleY
	*输入	
			无
	*输出	
			无
*/
void StepMotor_init()
{
	double Angle_now;
	Angle_now = angleY;
	Angle_pre = Angle_now;
	printf("Angle_now = angleY = 0\n");
}
/*
	*功能	步进电机驱动
	*常量
			先前角度	Angle_pre
	*输入	
			现要求角度	(double)Angle_now
	*输出	
			无
*/
void StepMotor_move(double Angle_now)
{
	double AngleToMove = 0;
	double StepToMove = 0;
	if(Angle_now != Angle_pre){
		AngleToMove = Angle_now - Angle_pre;
		if(AngleToMove < 0.0){
			PAout(5,1);		//正转
		}
		else if(AngleToMove > 0.0){
			PAout(5,0);		//反转
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
	*功能	管教配置
			PA.2	paulse
			PA.3	direction
	*输入	无
	*输出	无
*/
void StepMotor_IOconf(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* PA.4 PA.5	推挽输出50MHz */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

