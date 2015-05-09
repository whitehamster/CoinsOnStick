#include "TIM_init.h"
#include "usart.h"



/* 测量函数运行时长之用 */
void TIM1ch1_ITInit(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //打开时钟
    
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
	*每1us触发一次中断
	
*/
void TIM2ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 	//使能定时器2时钟
	
	//时基初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //加计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     //占先式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //清除定时器2中断标志
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //使能定时器2更新中断

	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}

/*
	*每10ms触发一次中断
	
*/
void TIM3ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//使能定时器3时钟
	
	//时基初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 10000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //加计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* Enable the TIM3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            //TIM3_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //占先式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //清除定时器3中断标志
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //使能定时器3更新中断

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	printf("TIM3ch1_ITInit OK\n");
}

uint8_t flag_50ms;
void TIM4_Init(char clock,int Preiod)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //打开时钟
    
    TIM_DeInit(TIM4);

    TIM_TimeBaseStructure.TIM_Period = Preiod;
    TIM_TimeBaseStructure.TIM_Prescaler = clock-1;//定时1ms
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
