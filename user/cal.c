#include "stm32f30x.h"
#include "cal.h"
#include "MPU6050.h"
#include "usart.h"
#include "extern_variable.h"
#include <math.h>




/*
	*����	�������˲�
	*ʹ��ȫ�ֱ���
			S_FLOAT_GyroAngle.AngleY(deg)
			S_FLOAT_AccAngle.AngleY(deg)
	*����	Accel(���ٶȼƽ���ĽǶ�)
			Gyro(�����ǽ���ĽǶ�)
*/
void KalmanFilter_Y(float Accel,float Gyro) 	
{
	float Q_angle = 0.001;  
	float Q_gyro  = 0.003;
	float R_angle = 0.5;
	float dt      = 0.01;//dtΪkalman�˲�������ʱ��;
	char  C_0     = 1;
	float Q_bias, Angle_err;
	float PCt_0, PCt_1, E;
	float K_0, K_1, t_0, t_1;
	float Pdot[4] ={0,0,0,0};
	float PP[2][2] = { { 1, 0 }, \
					   { 0, 1 } };
	
//	LowerFilter(S_FLOAT_AccAngle.AngleY);//��ͨ�˲�(���ٶȼ�)
	
	angleY += (Gyro - Q_bias) * dt; //�������
	
	Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3] = Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - angleY;	//zk-�������
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	angleY += K_0 * Angle_err;	 //�������
	Q_bias += K_1 * Angle_err;	 //�������
	S_FLOAT_GyroAngle.AngleZ  = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
}

/* 
	*����	�����ж��˲�����ͨ�˲����� 
	*ʹ��ȫ�ֱ���
			HistoryAcc_Y[2]
	*����	���ٶȼƽ�����ĽǶ�
	*���	�˲�����ٶȼƽ�����ĽǶ�
*/
#define D 0.01
float HistoryAcc_Y[2]={0};//���ڵ�һ���øú���ǰ��HistoryAcc_Y[1]
float LowerFilter(float Acc_Y)
{
	float NewAcc_Y;
	
	NewAcc_Y = Acc_Y;
	if((NewAcc_Y-HistoryAcc_Y[1]>D)||(HistoryAcc_Y[1]-NewAcc_Y>D)){
		NewAcc_Y = 2*HistoryAcc_Y[1]-HistoryAcc_Y[0];
	}
	HistoryAcc_Y[0] = HistoryAcc_Y[1];
	HistoryAcc_Y[1] = NewAcc_Y;
	return NewAcc_Y;
}

/* 
	*����	��ʼ����ͨ�˲��� 
	*ʹ������
			ʹ�ü��ٶȼ�ԭʼ���ݼ���õ�һ������֮��cal_AccAngleY()
*/
void LowerFilter_init(void)
{
	HistoryAcc_Y[1] = S_FLOAT_AccAngle.AngleY;
}
/*
	*����	���ü��ٶȼ�ԭʼ���ݼ�������ֱ����ļн�(������)
	*ʹ������
			��ȡ�õ�һ������֮��
	*ʹ��ȫ�ֱ���
			S_FLOAT_AccAngle.AngleY(deg)
	*���	S_FLOAT_AccAngle.AngleY(deg)
*/
float cal_AccAngleY(void)
{
	float acc_Y = 0;//��Y��������ٶ�(g)
	
	//printf("into cal_AccAngleY\n");
	acc_Y = AccData[1]/Acc4scale_JD;
	S_FLOAT_AccAngle.AngleY = asin(acc_Y)/TORAD;//arcsin(acc_Y/g)*(180/3.14159)
	//printf("cal_AccAngleY\tY %.2f`\n",S_FLOAT_AccAngle.AngleY);
	
	return S_FLOAT_AccAngle.AngleY;
}
/*
	*����	����������ԭʼ���ݼ�������ֱ����ļн�(����)
	*ʹ������
			��ȡ�õ�һ������֮��
	*ʹ��ȫ�ֱ���
			S_FLOAT_GyroAngle.AngleZ(deg)
	*���	S_FLOAT_GyroAngle.AngleZ(deg)
*/
float cal_GyroAngleY(void)
{
	float w_Z = 0;//��z����������ٶ�(deg/s)
	const float dt = 0.01;
	//printf("into cal_GyroAngleY\n");
	w_Z = (GyroData[2]/Gyro250scale_JD-S_FLOAT_GyroAngle.ZeroPointZ);
	S_FLOAT_GyroAngle.AngleZ += w_Z*dt;//AngleY = AngleY + w_Z*dt
	//printf("cal_GyroAngleY\tY %.2f`\n",S_FLOAT_GyroAngle.AngleZ);
	
	return S_FLOAT_GyroAngle.AngleZ;
}



///*
//	*����	��������ת�Ƕ�ֵ, ������
//	*ʹ������
//			��
//	*ʹ��ȫ�ֱ���
//			GyroData[2]
//			angleY
//	*����	��
//	*���	(float) AngleToMove
//*/
//float AcculateMotorMoveAngle(void)
//{
//	float AngleToMove = 0;//�����ת�Ƕ�ֵ
//	float w_Z = 0;//��Z����ٶ�(rad/s)
//	
//	w_Z = ((GyroData[2]/Gyro250scale_JD)-AccAngleY_ZeroPoint)*TORAD;
//	AngleToMove = asin( (MPU6050_ONE_G*sin(angleY))/				\
//						sqrt((MPU6050_ONE_G*MPU6050_ONE_G)+((w_Z*w_Z*StickLength)*(w_Z*w_Z*StickLength+2*MPU6050_ONE_G*cos(angleY)))) );
//					/* AlPhe = arcsin{ g*sin(angleY)/sqrt[g^2+(w^2 * r)*((w^2 * r)+2g*cos(angleY))] } */
//	return (AngleToMove);
//}
