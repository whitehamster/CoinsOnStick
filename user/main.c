/*	
	*管教分配:
		PA1			TI
		PA.4	paulse
		PA.5	direction
		PB6			SCL
		PB7			SDA
	*算法说明: 
		中断读数据 转电机(开环控制)
	*作者:
		海璃
	*时间:
		2015/5/4
	*进度:
		YES: 
		NO:  read_anglez()	
*/

#include "main.h"
int main(){
	double text = 0;
	
	usart2_init();			//串口2初始化
	delay_init();			//滴答延时初始化
	IIC_Init();				//软件模拟IIC初始化
	MPU6050_initialize();	//初始化MPU6050
	EXTI1_Config();			//中断初始化
//	StepMotor_IOconf();
//	delay_ms(5);
//	StepMotor_init();		//初始化步进电机(确认初始稳定时角度)
//	TIM2ch1_ITInit();		//10ms
	
	
	
	
	//检测是否成功握手
	while(!MPU6050_testConnection()){
		printf("NO DEVINCE!");
		delay_ms(2000);
	}
	while(1){
		
		
	}
	return 1;
	
	
	
/*	测Z轴角速度零漂
	while(1){
		uint8_t loop_i = 0;
		int16_t gyroData[3] = {0};
		int16_t gyro_z = {0};
		int32_t sum_z = 0;
		for(loop_i=0;loop_i<100;loop_i++){
			MPU6050GyroRead(gyroData);
			sum_z += gyroData[2];
		}
		gyro_z = sum_z/100.0;
		printf("GyroData\tX %.2f`\tY %.2f`\tZ %.2f`\t\n",gyroData[0]/16.4,gyroData[1]/16.4,gyro_z/16.4);
		sum_z = 0;
		loop_i=0;
		delay_ms(100);
	}
*/	
	
	
	
	
	

	
	
	
/*	串口部分
	//发送内部数据
	while(1){  
		printf("\n%d s\t passed!",time++);
		delay_ms(1000);
	} 
	//处理由串口接受到的数据
	while(1){
		Usart2Received_DMA1start();
		for(loop_i=0;loop_i<8;loop_i++){
			printf("%c\t",DstBuffer[loop_i]);
		}
		delay_ms(1000);
		printf("\nwait for the next putin :\n");
	}
*/

}


