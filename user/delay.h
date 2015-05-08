#include "stm32f30x.h"

void delay_init(void);
void delay_ms(__IO uint32_t msTime);
void delay_us(__IO uint32_t usTime);
void TimingDelay_Decrement(void);
static __IO uint32_t TimingDelay;
