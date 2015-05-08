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
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //�����ʱ��3�жϱ�־
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��3�����ж�

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}

///************************************************************
//*��������:void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
//*��    ��:TIM3 PWM���ֳ�ʼ�� 
//*˵    ��: PA.6 PWM1 	PA.7 PWM2	PB.0 PWM3	PB.1 PWM4
//*�������:arr���Զ���װֵ
//          psc��ʱ��Ԥ��Ƶ��
//*�������:��
//*************************************************************/
//void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
//{  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//ʹ�ܶ�ʱ��3ʱ��
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA| RCC_AHBPeriph_GPIOB, ENABLE);  //ʹ��GPIO����ʱ��
// 
//	//���ø�����Ϊ���������������,���TIM3 CH1-CH4��PWM���岨��
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6| GPIO_PinSource7, GPIO_AF_2);//T3 - PWM1/PWM2/PWM3/PWM4��������
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0| GPIO_PinSource1, GPIO_AF_2);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	//ʱ����ʼ��
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�Ӽ���
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//	
//	//��ʼ��TIM3 Channel1 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_Pulse = T3CCR1_Val;                     //�û����嶨ʱ������
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  										  //����Tָ���Ĳ�����ʼ������TIM3 OC1
//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);              //�ر�Ԥ����Ĵ���
//	//��ʼ��TIM3 Channel2 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_Pulse = T3CCR2_Val;                     //�û����嶨ʱ������
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  										  //����Tָ���Ĳ�����ʼ������TIM3 OC2
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);              //�ر�Ԥ����Ĵ���
//	//��ʼ��TIM3 Channel3 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_Pulse = T3CCR3_Val;                     //�û����嶨ʱ������
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  										  //����Tָ���Ĳ�����ʼ������TIM3 OC3
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);              //�ر�Ԥ����Ĵ���
//	//��ʼ��TIM3 Channel4 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_Pulse = T3CCR4_Val;                     //�û����嶨ʱ������
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  										  //����Tָ���Ĳ�����ʼ������TIM3 OC4
//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);              //�ر�Ԥ����Ĵ���
//	

//	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
//	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //�����ʱ��3�жϱ�־
//	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //ʹ�ܶ�ʱ��3�����ж�
//}

///************************************************************
//*��������:void TIM1_Int_Init(uint16_t arr,uint16_t psc)
//*��    ��:TIM1 ��ʱ��1��ʼ�� 
//*�������:arr= �Զ���װ�ؼĴ������ڵ�ֵ
//		  psc= ʱ��Ƶ��Ԥ��Ƶֵ
//*�������:��
//*************************************************************/
//void TIM1_Int_Init(uint16_t arr,uint16_t psc)
//{  
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ�ܶ�ʱ��1ʱ��

//	//��ʼ��TIM1
//	TIM_TimeBaseStructure.TIM_Period = arr; 					//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = psc; 					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�ظ���������
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 			//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

//	//����Ƚ�ʱ��ģʽ����TIM1 CC3ͨ��
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;				//ѡ������Ƚ�ʱ��ģʽ
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//���״̬ʹ��
//	TIM_OCInitStructure.TIM_Pulse = TIM1CCR3_Val;                	//���ô�װ�벶��ȽϼĴ���������ֵ,2M/500=4Khz=250us
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);                     	//��ʼ���Ƚ��ж�3
//	
//	/* Enable the TIM1 UP Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;            //TIM1_CC_IRQn   TIM1_UP_IRQn
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //ռ��ʽ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //�����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update); //����������жϱ�־
//	TIM_ITConfig(TIM1,TIM_IT_CC3, ENABLE);//��ʱ��1��CC3�ж�ʹ��
//	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
//}


