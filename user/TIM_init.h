#ifndef __TIM_init_H
#define __TIM_init_H
#include "stm32f30x.h"


#define CyclePWM                1500   //36M/(1500/2)=48KHZ=20.83us
extern uint16_t capture;

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM1_Int_Init(u16 arr,u16 psc);
void TIM2ch1_ITInit(void);

#endif
