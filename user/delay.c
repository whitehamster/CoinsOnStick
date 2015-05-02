#ifndef _delay_H_
#define _delay_H_

#include "delay.h"

void delay_init(void){
	//设置中断时间为72000000 / 1000000 = 72
  SysTick_Config(72000000 / 1000000);
}

void delay_us(__IO uint32_t usTime){ 
  TimingDelay = usTime;

  while(TimingDelay != 0);
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
#endif
