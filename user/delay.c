#include "delay.h"

void delay_init(void){
	//����ʱ��ԴΪAHB=72MHz
	/*
		Counting down to zero to asserts the SysTick exception request
		====>1���ж�/1us
	*/
	//Ԥװ��ֵ72
	//��װ��ֵ������ֹ��
	//�����ж�ʱ��Ϊ8000000 / 1000000 = 8                    --------------------
	while(SysTick_Config(SystemCoreClock / 1000000))
		;
}

void delay_us(__IO uint32_t usTime){ //------------------------------------
  TimingDelay = usTime;

  while(TimingDelay != 0);
}  
								   
void delay_ms(__IO uint32_t msTime){
	while(msTime != 0){
		delay_us(1000);
		msTime--;
	}
}

void TimingDelay_Decrement(void) //---------------------------------------
{
  if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}
