#ifndef _adc_H_
#define _adc_H_

#include "stm32f30x.h"
#include "main.h"

#define ZERO_M90 2731
#define ZERO_90  510

uint16_t adc_get_avg(void);
float voltage_to_de(void);
uint16_t adc_get(void);
void ad_init(void);

#endif
