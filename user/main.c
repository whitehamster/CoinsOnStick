/*	
	*�̷ܽ���:
		PA1			TI
		PA.4	paulse
		PA.5	direction
		PB6			SCL
		PB7			SDA
	*�㷨˵��: 
		�ж϶����� ת���(��������)
	*����:
		����
	*ʱ��:
		2015/5/4
	*����:
		YES: 
		NO:  read_anglez()	
*/

#include "main.h"
int main(){
	double text = 0;
	
	usart2_init();			//����2��ʼ��
	delay_init();			//�δ���ʱ��ʼ��
	IIC_Init();				//���ģ��IIC��ʼ��
	MPU6050_initialize();	//��ʼ��MPU6050
	EXTI1_Config();			//�жϳ�ʼ��
//	StepMotor_IOconf();
//	delay_ms(5);
//	StepMotor_init();		//��ʼ���������(ȷ�ϳ�ʼ�ȶ�ʱ�Ƕ�)
//	TIM2ch1_ITInit();		//10ms
	
	
	
	
	//����Ƿ�ɹ�����
	while(!MPU6050_testConnection()){
		printf("NO DEVINCE!");
		delay_ms(2000);
	}
	while(1){
		
		
	}
	return 1;
	
	
	
/*	��Z����ٶ���Ư
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
	
	
	
	
	

	
	
	
/*	���ڲ���
	//�����ڲ�����
	while(1){  
		printf("\n%d s\t passed!",time++);
		delay_ms(1000);
	} 
	//�����ɴ��ڽ��ܵ�������
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


