#ifndef __extern_variable_h
#define __extern_variable_h

	#include "stdint.h"
	
	
	
	/* * * 传感器 * * */
	//标志位
	volatile extern uint8_t 	MPU6050_I2CData_Ready;		//mpu6050读取完成标志,=1表示读取完成
	extern uint8_t ReceiveDataEn;	//接受MPU6050数据使能
	extern uint8_t SetZeroPoint_Flag;//设置零点 标志位
	//寄存器
	extern uint8_t buffer[14];	//暂存器
	extern int16_t GyroData[3];	//陀螺仪原始数据 MPU6050GyroRead()
	extern int16_t AccData[3];	//加速度计原始数据 MPU6050AccRead()
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
	extern float angleY;		//杆与竖直方向夹角(deg) 此处应命名为angleX即X轴倾斜度，因历史原因，故保留该变量名
	
	/* * * 电机 * * */
	extern float Angle_pre; //先前角度
#endif
