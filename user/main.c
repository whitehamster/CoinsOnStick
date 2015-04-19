#include "main.h"

int main(){
	usart2_init();
	delay_init();
	while(1)  
	{  
		printf("test");
		delay_ms(1000);
	} 
  
	while(1);
	return 0;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (unsigned char) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	return (ch);
}
