/*
	定义所有全局变量
*/
#include "extern_variable.h"

float angleY[2] = {0};
uint8_t buffer[14] = {0u};//使用MPU6050库函数时所需的暂存器
uint8_t ReceiveDataEn = 0u;
int16_t GyroData[3] = {0};//陀螺仪原始数据寄存器
int16_t AccData[3] = {0};//加速度计原始数据寄存器
uint8_t SetZeroPoint_Flag = 0u;
float AD_angleY[2] = {0};

S_FLOAT_Angle S_FLOAT_AccAngle ={0};//加速度计结算得到的角度值
S_FLOAT_Angle S_FLOAT_GyroAngle ={0};//陀螺仪结算得到的角度值
