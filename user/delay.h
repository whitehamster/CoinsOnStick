#ifndef __delay_h
#define __delay_h

	#include "stm32f30x.h"

	static __IO uint32_t TimingDelay;

	void delay_init(void);
	void delay_ms(__IO uint32_t msTime);
	void delay_us(__IO uint32_t usTime);
	void TimingDelay_Decrement(void);

#endif