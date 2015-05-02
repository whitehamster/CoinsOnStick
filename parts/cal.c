#include "cal.h"
#include "main.h"

s16 mpu6050_date[6];
float mpu[6];
float vn;
float a;

//处理需要用到的数据
void real_date_calculate(void)
{
	mpu[0] = (float)mpu6050_date[0] / 16384;  //向心加速度
	mpu[1] = (float)mpu6050_date[1] / 16384;  //切向加速度
	mpu[5] = ((float)mpu6050_date[4] / 32.8f)*(3.1415926f/180); //切向角速度单位为弧度
}

//角度a计算
void stick_a_calculate(void)
{
	float an,gn;
	an = mpu[5]*mpu[5]*STICK_LENGTH; //an=w^2*r
	gn = mpu[0]-an;
	a = acos(gn)*180/3.1415926f;
}

//线速度v计算
void stick_v_calculate(void)
{
	vn = mpu[5]*STICK_LENGTH;
}
