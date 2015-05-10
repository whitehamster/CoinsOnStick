/*	
	*�̷ܽ���:
		PA1			INT
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
		angleY[1]					�ڸ�����ֱ����н�
		AccData[3]				
		GyroData[3]				
		SetZeroPoint_Flag		������� ��־λ
	*�㷨˵��: 
		�ж���ʹ��λ
		������������, ��������, �������
	*����:
		����
	*ʱ��:
		2015/5/10
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

	TIM3ch1_ITInit();		//��ʱ�����ʼ��10ms
	SetZeroPoint();			//������Ư�Ƶ�
	StepMotor_IOconf();		//��������ܽ�����
	StepMotor_init();		//��ʼ���������(ȷ�ϳ�ʼ�ȶ�ʱ�Ƕ�)
	
	ad_init();				//��λ��ad��ʼ��
	TIM4_Init(72,50000);	//50ms��ʱ����ڸ˽��ٶ�
	
	
	//		�����ƶ��ڸ���һ���Ƕ� �� �� �� �� 45o��60o�䣩 ������ƽ��Ƕȣ���
	//	ƽ�������ȶ����� 8 ö 1 ԪӲ�ң���ͼ 2��������ſ��ڸ���������
	//	�ڶ����ڰڸ˰ڶ������У�Ҫ�����ƽ��״̬ʹӲ���ڰڸ˵� 5 ����
	//	�������в���ƽ���ϻ��䣬�����ֵ���״̬������ƽ���ϷǱ��ֵ���
	//	״̬�������Ӳ��������ɼ���
	//
	while(3){
		cal_angle();
	}
	return 1;
}










/*	Task 1
	//		���Ƶ��ʹƽ��������Űڸ˵İڶ�����ת��3~5 �ܣ����ڸ˰�һ����
	//	�ڣ�ƽ����תһ�ܣ�360o����ƫ�����ֵ������45�㡣
	//	
	while(1){
		static uint8_t state = 0;
		AD_angleY[1] = voltage_to_de();
		//printf("AD_angleY %f\n",AD_angleY[1]);
		if(state == 0){
			state = 1;
			while(AD_angleY[1]>0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(180, 1);
			}
			while(AD_angleY[1]<0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(360, 1);
			}
		}
		else if(state == 1){
			state = 0;
			while(AD_angleY[1]>0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(180, 1);
			}
			while(AD_angleY[1]<0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(0, 1);
			}
		}
	}
*/

/*	Task 2
	//		��ƽ����ճ��һ�Ż���һ����Ϊ 1cm ƽ���ߵĴ�ӡֽ�������ƶ���
	//	����һ���Ƕ� �� �� �� �� 30o��45o�䣩 ������ƽ��Ƕȣ���ƽ��������
	//	������һö 1 ԪӲ�ң�����ң� ��������ſ��ڸ��������ɰڶ����ڰ�
	//	�˰ڶ������У�Ҫ�����ƽ��״̬��ʹӲ���� 5 ���ڶ������в���ƽ
	//	���ϻ��䣬�������ٻ���ƽ�������λ�á�
	//
	Task2_Exti_Config();
	while(2){
		cal_angle();
		AcculateMotorMoveAngle();
	}
*/







/*	�Է������ĵ����������
	while(1){
		float buff_angle,buff_angel_int;
		buff_angle += AcculateMotorMoveAngle();
		buff_angel_int = (int) buff_angle;
		buff_angle -= buff_angel_int;
		StepMotor_move(buff_angel_int,1);
	}	
*/
	
/*	���ĳһ�γ�����Ƭ�ϵ�ʵ������ʱ��
	TIM1ch1_ITInit();
	while(1){
		TIM_Cmd(TIM1,ENABLE);
		loop_i = TIM_GetCounter(TIM1);
		
		***   �������ʱ��ĺ�����   ****
		
		loop_i = TIM_GetCounter(TIM1) - loop_i;
		printf("\n %dus\n",loop_i);
	}
*/
	
/*	����Ƕ�
	while(1){
		//StepMotor_move(0);
		if(ReceiveDataEn == 1){
			ReceiveDataEn = 0;
			MPU6050GyroRead(GyroData);
			MPU6050AccRead(AccData);
			//printf("GyroData X=%d,Y=%d,Z=%d\n",GyroData[0],GyroData[1],GyroData[2]);
			cal_GyroAngleY();
			cal_AccAngleY();
			KalmanFilter_Y(S_FLOAT_AccAngle.AngleY, S_FLOAT_GyroAngle.AngleX);
			printf("angleY[1] = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY[1],S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleX);
		}
		//StepMotor_move(20);
		//printf("angleY[1] = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY[1],S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleX);
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
