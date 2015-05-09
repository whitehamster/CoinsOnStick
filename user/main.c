/*	
	*�̷ܽ���:
		PA1			TI
		PA.4		paulse
		PA.5		direction
		PB6			SCL
		PB7			SDA
	*ȫ�ֱ���
		EndOfTransfer			DMA������ɱ�־λ
		DstBuffer[BUFFER_SIZE]	DMA�������ݼĴ���RAM
		TimingDelay				��ʱԤ��ֵ�Ĵ���
		ReceiveDataEn			����MPU6050����ʹ��
		Angle_pre				��ǰ���(ƽ��)�ǶȼĴ���
		buffer[14]				IIC��ȡMPU6050�����ݴ���
		angleY					�ڸ�����ֱ����н�
		AccData[3]				
		GyroData[3]				
		SetZeroPoint_Flag		������� ��־λ
	*�㷨˵��: 
		�ж���ʹ��λ
		������������, ��������, �������
	*����:
		����
	*ʱ��:
		2015/5/5
	*����:
		YES: 
		NO:	���KalmanFilter ��δ���ԣ����ȴ�ȷ�ϣ�
			Acc��ͨ�˲�δ����
			���ǵ������ת��Ƶ����100Hz���ϣ�����Ҳ��ü��ٶȼƵĵ�ͨ�˲�(DLPF)Ϊ98Hz, 
		������Ч�˵�����񶯴�����Ӱ��, ���ƽ���˲�Ч��Ӧ�ò���.(�Ѽӣ����ӵ������)
			
			
	*NONO:
		TIM3(100ms)��ȡ���ݣ�ʹ��Tim2����ʱ�����������ͣ��delay�����е�while��
			
*/


#include "main.h"

	




int main(){
	/* ��ʼ�� */
	usart2_init();			//����2��ʼ��
	delay_init();			//��ʱ��ʼ��
	IIC_Init();				//���ģ��IIC��ʼ��
	MPU6050_initialize();	//��ʼ��MPU6050
//	EXTI1_Config();			//�жϳ�ʼ��
	/*�Լ��ٶȼƽ���ĽǶȽ��еĴ���*/
//	delay_ms(15);
//	cal_AccAngleY();		
//	LowerFilter_init();		
//	LowerFilter(S_FLOAT_AccAngle.AngleY);//��ͨ�˲�(���ٶȼ�)
	TIM3ch1_ITInit();		//��ʱ�����ʼ��
	SetZeroPoint();			//������Ư�Ƶ�
//	StepMotor_IOconf();		//��������ܽ�����
//	StepMotor_init();		//��ʼ���������(ȷ�ϳ�ʼ�ȶ�ʱ�Ƕ�)
	
	while(1){
		/*����Ƕ�*/
		if(ReceiveDataEn == 1){
			ReceiveDataEn = 0;
			MPU6050GyroRead(GyroData);
			MPU6050AccRead(AccData);
			//printf("GyroData X=%d,Y=%d,Z=%d\n",GyroData[0],GyroData[1],GyroData[2]);
			cal_GyroAngleY();
			cal_AccAngleY();
			KalmanFilter_Y(S_FLOAT_AccAngle.AngleY, S_FLOAT_GyroAngle.AngleZ);
			//printf("angleY = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY,S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleZ);
		}
		
		

	}
	return 1;
}

//		angleY = Q_ANGLE.Yaw-Angle_ZeroPoint;
//		//printf("angleY = %f\n",angleY);
//		StepMotor_move(AcculateMotorMoveAngle());// ת����� 
//		printf("Q_ANGLE.Yaw = %f\n",Q_ANGLE.Yaw);
//		printf("DMP_DATA.dmp_gyroz = %f\n",DMP_DATA.dmp_gyroz);














	
/*
	//����Ƿ�ɹ�����
	while(!MPU6050_testConnection()){
		printf("NO DEVINCE!");
		delay_ms(2000);
	}
*/
	
/*	��Z����ٶ���Ư
	while(1){
		uint8_t loop_i = 0;
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
