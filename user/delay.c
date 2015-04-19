#include "delay.h"

void delay_init(void){
	//设置中断时间为8000000 / 1000000 = 8
	SysTick_Config(SystemCoreClock / 1000000);
}

void delay_us(__IO uint32_t usTime){ 
  TimingDelay = usTime;

  while(TimingDelay != 0);
}  
								   
void delay_ms(__IO uint32_t msTime){
	while(msTime != 0){
		delay_us(1000);
		msTime -= 1;
	}
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
