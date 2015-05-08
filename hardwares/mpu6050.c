/*
	*待解决: 
			采样率问题 void MPU6050_initialize(void)	
*/
#include "MPU6050.h"
#include "iic.h"
#include "delay.h"
#include "usart.h"
#include "extern_variable.h"

//初始化
void MPU6050_initialize(void) {
	IICwriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x80);     	//唤醒
    delay_ms(50);
    IICwriteByte(devAddr, MPU6050_RA_SMPLRT_DIV, 0x01);      	//Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
	IICwriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x03);      	//CLKSEL 3 (PLL with Z Gyro reference)
	IICwriteByte(devAddr, MPU6050_RA_INT_PIN_CFG, (1<<4));		//interrupt status bits are cleared on any read operation
	IICwriteByte(devAddr, MPU6050_RA_INT_ENABLE, (1<<0));		//interrupt occurs when data is ready. 
	IICwriteByte(devAddr, MPU6050_RA_CONFIG, 0x02);				//ACC bandwidth = 94Hz  GYRO bandwidth = 98Hz)
	IICwriteByte(devAddr, MPU6050_RA_GYRO_CONFIG, 0x00);		//Full scale set to 250 deg/sec
    IICwriteByte(devAddr, MPU6050_RA_ACCEL_CONFIG, 1 << 3);		//Full scale set to 4g
	printf("MPU6050_initialized\n");
}
//读加速度
void MPU6050AccRead(int16_t *accData)
{
    uint8_t buf[6];

    IICreadBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 6, buf);
    accData[0] = (int16_t)((buf[0] << 8) | buf[1]);
    accData[1] = (int16_t)((buf[2] << 8) | buf[3]);
    accData[2] = (int16_t)((buf[4] << 8) | buf[5]);
}
//读角速度
void MPU6050GyroRead(int16_t *gyroData)
{
    uint8_t buf[6];

    IICreadBytes(devAddr, MPU6050_RA_GYRO_XOUT_H, 6, buf);
    gyroData[0] = (int16_t)((buf[0] << 8) | buf[1]) ;
    gyroData[1] = (int16_t)((buf[2] << 8) | buf[3]) ;
    gyroData[2] = (int16_t)((buf[4] << 8) | buf[5]) ;
}






/**************************实现函数********************************************
*函数原型:		uint8_tMPU6050_getDeviceID(void)
*功　　能:	    读取  MPU6050 WHO_AM_I 标识	 将返回 0x68
*******************************************************************************/
uint8_t MPU6050_getDeviceID(void)
{
    IICreadBytes(devAddr, MPU6050_RA_WHO_AM_I, 1, buffer);
    return buffer[0];
}
/**************************实现函数********************************************
*函数原型:		uint8_tMPU6050_testConnection(void)
*功　　能:	    检测MPU6050 是否已经连接
*******************************************************************************/
uint8_t MPU6050_testConnection(void) {
	if(MPU6050_getDeviceID() == 0x68)  //0b01101000;
		return 1;
	else return 0;
}
/**************************实现函数********************************************
*函数原型:		void MPU6050_Check()
*功　　能:	  检测IIC总线上的MPU6050是否存在
*******************************************************************************/
void MPU6050_Check(void) 
{ 
  switch(MPU6050_testConnection())
  {
    case 0: printf("未检测到MPU6050...\r\n");
      break;
    case 1: printf("已检测到MPU6050...\r\n");
      break;
  }
} 



