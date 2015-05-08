#include "TIM_init.h"


/*
	*ÿ1us����һ���ж�
	
*/
void TIM2ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 	//ʹ�ܶ�ʱ��2ʱ��
	
	//ʱ����ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�Ӽ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     //ռ��ʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //�����ʱ��2�жϱ�־
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��2�����ж�

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}

/*
	*ÿ1ms����һ���ж�
	
*/
void TIM3ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//ʹ�ܶ�ʱ��3ʱ��
	
	//ʱ����ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 1000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�Ӽ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* Enable the TIM3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            //TIM3_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //ռ��ʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //�����ʱ��3�жϱ�־
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��3�����ж�

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}

