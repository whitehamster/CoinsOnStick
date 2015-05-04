#include "usart.h"
#include "delay.h"
#include "stdio.h"
uint16_t DstBuffer[BUFFER_SIZE] = {0};
__IO uint32_t EndOfTransfer = 0;
	
//PA.2 Tx	PA.3 Rx
void usart2_init(void){
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 
	//Enable clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//--------------
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
                                                          
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2,GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3,GPIO_AF_7);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure); 
	
	USART_Cmd(USART2, ENABLE); 
}

void Usart2Received_DMA1start(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	const uint32_t SrcBuffer = 0x40004424; //寄存器地址(USARTx_RDR)
							
	/* DMA1 channel6 configuration ---------------------------------------------*/
	/* Enable DMA1 clock --------------------------------------------------------*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel6); //通道6===USART2_Rx
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SrcBuffer; //外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DstBuffer; //内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设到内存
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE; //重载值, 数据传输总数量 8个
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址自动移位失能
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址自动移位使能
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);

	/* Enable DMA1 Channel6 Transfer Complete interrupt */
	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE); //传送完成中断

	/* Enable DMA1 channel6 IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
	/* Enable DMA1 Channel6 transfer */
	DMA_Cmd(DMA1_Channel6, ENABLE);

	/* Wait the end of transmission */
	while (EndOfTransfer == 0)
		;
	EndOfTransfer = 0;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (unsigned char) ch);//------------
	while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET)
		;
	return (ch);
}
