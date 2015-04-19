#include "main.h"

int main(){
	usart2_init();
	delay_init();
	while(1)  
	{  
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, 'A'); 
		delay_ms(1000);
	} 
  
	while(1);
	return 0;
}
