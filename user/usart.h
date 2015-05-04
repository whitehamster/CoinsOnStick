#include "stm32f30x.h"

#define BUFFER_SIZE  2 //DMA每次读取数据个数
extern uint16_t DstBuffer[];

void usart2_init(void);
uint8_t usart2_received(uint16_t * RxDATA);
void display_received(void);
void Usart2Received_DMA1start(void);
