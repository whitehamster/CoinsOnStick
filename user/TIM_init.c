#include "TIM_init.h"
#include "usart.h"



/* ������������ʱ��֮�� */
void TIM1ch1_ITInit(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //��ʱ��
    
    TIM_DeInit(TIM1);

    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1,TIM_FLAG_Update);

    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM1,DISABLE);
  
}	

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
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //�����ʱ��2�жϱ�־
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��2�����ж�

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}

/*
	*ÿ10ms����һ���ж�
	
*/
void TIM3ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//ʹ�ܶ�ʱ��3ʱ��
	
	//ʱ����ʼ��
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 10000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�Ӽ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* Enable the TIM3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            //TIM3_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //ռ��ʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //�����ʱ��3�жϱ�־
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��3�����ж�

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	printf("TIM3ch1_ITInit OK\n");
}

uint8_t flag_50ms;
void TIM4_Init(char clock,int Preiod)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //��ʱ��
    
    TIM_DeInit(TIM4);

    TIM_TimeBaseStructure.TIM_Period = Preiod;
    TIM_TimeBaseStructure.TIM_Prescaler = clock-1;//��ʱ1ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
	
	/* Enable the TIM4 gloabal Interrupt */

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}	
