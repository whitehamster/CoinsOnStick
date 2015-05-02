#include "main.h"

int main(){

	usart2_init();
	delay_init();
	MPU6050_I2C_Init();
	MPU6050_Initialize();
	MPU6050_Exti_Config();
	TIM3_Init(72,10000);
	
	printf("start\n");
	
	while(1)
	{ 

	} 
  
	return 0;
}

