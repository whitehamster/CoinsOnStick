#ifndef __extern_variable_h
#define __extern_variable_h

	#include "stdint.h"
	
	
	
	/* * * ������ * * */
	//��־λ
	volatile extern uint8_t 	MPU6050_I2CData_Ready;		//mpu6050��ȡ��ɱ�־,=1��ʾ��ȡ���
	extern uint8_t ReceiveDataEn;	//����MPU6050����ʹ��
	extern uint8_t SetZeroPoint_Flag;//������� ��־λ
	//�Ĵ���
	extern uint8_t buffer[14];	//�ݴ���
	extern int16_t GyroData[3];	//������ԭʼ���� MPU6050GyroRead()
	extern int16_t AccData[3];	//���ٶȼ�ԭʼ���� MPU6050AccRead()
	typedef struct
	{
		float AngleX;
		float AngleY;
		float AngleZ;
		float ZeroPointX;
		float ZeroPointY;
		float ZeroPointZ;
	}S_FLOAT_Angle;
	extern S_FLOAT_Angle S_FLOAT_AccAngle;
	extern S_FLOAT_Angle S_FLOAT_GyroAngle;
	extern float angleY;		//������ֱ����н�(deg) �˴�Ӧ����ΪangleX��X����б�ȣ�����ʷԭ�򣬹ʱ����ñ�����
	
	/* * * ��� * * */
	extern float Angle_pre; //��ǰ�Ƕ�
#endif
