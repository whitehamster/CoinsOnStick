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
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		    //清除定时器3中断标志
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //使能定时器3更新中断

	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}

///************************************************************
//*函数名称:void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
//*功    能:TIM3 PWM部分初始化 
//*说    明: PA.6 PWM1 	PA.7 PWM2	PB.0 PWM3	PB.1 PWM4
//*输入参数:arr：自动重装值
//          psc：时钟预分频数
//*输出参数:无
//*************************************************************/
//void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
//{  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 	//使能定时器3时钟
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA| RCC_AHBPeriph_GPIOB, ENABLE);  //使能GPIO外设时钟
// 
//	//设置该引脚为复用推挽输出功能,输出TIM3 CH1-CH4的PWM脉冲波形
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6| GPIO_PinSource7, GPIO_AF_2);//T3 - PWM1/PWM2/PWM3/PWM4引脚配置
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0| GPIO_PinSource1, GPIO_AF_2);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	//时基初始化
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = psc; 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //加计数
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//	
//	//初始化TIM3 Channel1 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //选择定时器模式:TIM脉冲宽度调制模式
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_Pulse = T3CCR1_Val;                     //用户定义定时的周期
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  										  //根据T指定的参数初始化外设TIM3 OC1
//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);              //关闭预载入寄存器
//	//初始化TIM3 Channel2 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //选择定时器模式:TIM脉冲宽度调制模式
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_Pulse = T3CCR2_Val;                     //用户定义定时的周期
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  										  //根据T指定的参数初始化外设TIM3 OC2
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);              //关闭预载入寄存器
//	//初始化TIM3 Channel3 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //选择定时器模式:TIM脉冲宽度调制模式
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_Pulse = T3CCR3_Val;                     //用户定义定时的周期
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  										  //根据T指定的参数初始化外设TIM3 OC3
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);              //关闭预载入寄存器
//	//初始化TIM3 Channel4 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						  //选择定时器模式:TIM脉冲宽度调制模式
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_Pulse = T3CCR4_Val;                     //用户定义定时的周期
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  										  //根据T指定的参数初始化外设TIM3 OC4
//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);              //关闭预载入寄存器
//	

//	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
//	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		    //清除定时器3中断标志
//	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //使能定时器3更新中断
//}

///************************************************************
//*函数名称:void TIM1_Int_Init(uint16_t arr,uint16_t psc)
//*功    能:TIM1 定时器1初始化 
//*输入参数:arr= 自动重装载寄存器周期的值
//		  psc= 时钟频率预分频值
//*输出参数:无
//*************************************************************/
//void TIM1_Int_Init(uint16_t arr,uint16_t psc)
//{  
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能定时器1时钟

//	//初始化TIM1
//	TIM_TimeBaseStructure.TIM_Period = arr; 					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = psc; 					//设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数清零
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 			//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//	//输出比较时间模式配置TIM1 CC3通道
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;				//选择输出比较时间模式
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//输出状态使能
//	TIM_OCInitStructure.TIM_Pulse = TIM1CCR3_Val;                	//设置待装入捕获比较寄存器的脉冲值,2M/500=4Khz=250us
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);                     	//初始化比较中断3
//	
//	/* Enable the TIM1 UP Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;            //TIM1_CC_IRQn   TIM1_UP_IRQn
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //占先式优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //副优先级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除上升沿中断标志
//	TIM_ITConfig(TIM1,TIM_IT_CC3, ENABLE);//定时器1的CC3中断使能
//	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
//}


