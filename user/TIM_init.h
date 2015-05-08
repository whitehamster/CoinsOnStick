#ifndef __TIM_init_H
#define __TIM_init_H
#include "stm32f30x.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM1_Int_Init(u16 arr,u16 psc);
void TIM2ch1_ITInit(void);
void TIM3ch1_ITInit(void);
#endif
