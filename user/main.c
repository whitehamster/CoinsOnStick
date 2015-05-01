#include "main.h"


s16 mpu6050_date[6];

float mpu[5];

int main(){

	usart2_init();
	delay_init();
	MPU6050_I2C_Init();
	MPU6050_Initialize();
	
	printf("start\n");
	
	while(1)
	{ 
		mpu[0] = (float)mpu6050_date[0] / 16384;
		mpu[1] = (float)mpu6050_date[1] / 16384;
		mpu[2] = (float)mpu6050_date[2] / 16384;
		printf("%f,%f,%f,%d,%d,%d\n",mpu[0],mpu[1],mpu[2],mpu6050_date[3],mpu6050_date[4],mpu6050_date[5]);
	} 
  
	return 0;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (unsigned char) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	return (ch);
}
