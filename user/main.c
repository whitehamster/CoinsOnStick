#include "main.h"
#include "usart.h"

int main(){
	usart2_init();
	while(1)  
	{  
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, 'A'); 
	}  
  
	while(1);
	return 0;
}
