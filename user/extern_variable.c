/*
	��������ȫ�ֱ���
*/
#include "extern_variable.h"

float angleY = 0;
uint8_t buffer[14] = {0u};//ʹ��MPU6050�⺯��ʱ������ݴ���
uint8_t ReceiveDataEn = 0u;
int16_t GyroData[3] = {0};//������ԭʼ���ݼĴ���
int16_t AccData[3] = {0};//���ٶȼ�ԭʼ���ݼĴ���
uint8_t SetZeroPoint_Flag = 0u;
float AccAngleY_ZeroPoint = 0.0;
float GyroAngleY_ZeroPoint = 0.0;

S_FLOAT_Angle S_FLOAT_AccAngle ={0};//���ٶȼƽ���õ��ĽǶ�ֵ
S_FLOAT_Angle S_FLOAT_GyroAngle ={0};//�����ǽ���õ��ĽǶ�ֵ
