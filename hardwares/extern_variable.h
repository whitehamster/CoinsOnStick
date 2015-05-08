#ifndef __extern_variable_h
#define __extern_variable_h

#include "stm32f30x.h"
volatile extern uint8_t 	MPU6050_I2CData_Ready;		//mpu6050��ȡ��ɱ�־,=1��ʾ��ȡ���

         
//������
typedef struct int16_xyz
{
    int16_t X;
    int16_t Y;
    int16_t Z;
}S_INT16_XYZ;


typedef union 
{
    int16_t D[3];
    S_INT16_XYZ V;
    
}U_INT16_XYZ;
typedef struct float_angle
{
    float Roll;
    float Pitch;
    float Yaw;
}S_FLOAT_ANGLE;
#endif
