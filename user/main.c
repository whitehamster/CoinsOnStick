#include "main.h"

static s16 acc[6];

int main(){
	usart2_init();
	delay_init();
	printf("%d",12);
	MPU6050_I2C_Init();
	printf("%d",34);
	MPU6050_Initialize();
	printf("%d",MPU6050_TestConnection());
	
	while(1)
	{ 
		MPU6050_GetRawAccelGyro(&acc[0]);
		printf("%d,%d,%d\n",acc[0],acc[1],acc[2]);
		delay_ms(50);
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
