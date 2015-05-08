#include "delay.h"
#include "TIM_init.h"

void delay_init(void){
	TIM2ch1_ITInit();		//1us
}

void delay_us(__IO uint32_t usTime){ 
	NVIC_DisableIRQ(EXTI1_IRQn);
	TimingDelay = usTime;
	while(TimingDelay != 0);
	NVIC_EnableIRQ(EXTI1_IRQn);
}  
								   
void delay_ms(__IO uint32_t msTime){
	while(msTime != 0){
		delay_us(1000);
		msTime--;
	}
}
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}
