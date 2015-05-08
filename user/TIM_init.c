#include "TIM_init.h"


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
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //清除定时器2中断标志
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //使能定时器2更新中断

	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}

/*
	*每1ms触发一次中断
	
*/
void TIM3ch1_ITInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//使能定时器3时钟
	
	//时基初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 1000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //加计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* Enable the TIM3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            //TIM3_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //占先式优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //清除定时器3中断标志
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //使能定时器3更新中断

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

