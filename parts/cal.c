#include "cal.h"
#include "main.h"

s16 mpu6050_date[6];
float mpu[6];
float vn;
float a;

//������Ҫ�õ�������
void real_date_calculate(void)
{
	mpu[0] = (float)mpu6050_date[0] / 16384;  //���ļ��ٶ�
	mpu[1] = (float)mpu6050_date[1] / 16384;  //������ٶ�
	mpu[5] = ((float)mpu6050_date[4] / 32.8f)*(3.1415926f/180); //������ٶȵ�λΪ����
}

//�Ƕ�a����
void stick_a_calculate(void)
{
	float an,gn;
	an = mpu[5]*mpu[5]*STICK_LENGTH; //an=w^2*r
	gn = mpu[0]-an;
	a = acos(gn)*180/3.1415926f;
}

//���ٶ�v����
void stick_v_calculate(void)
{
	vn = mpu[5]*STICK_LENGTH;
}
