/*
	*待解决: 
			采样率问题 void MPU6050_initialize(void)
			
*/







#include "MPU6050.h"
#include "iic.h"
#include "delay.h"
#include "usart.h"
#include <math.h>
uint8_t buffer[14] = {0};
double angleY = 0;

/**************************实现函数********************************************
*函数原型:		double read_angleY(void)
*功　　能:	    计算与初始Y轴的夹角, 并返回该值 (double) angleY
*******************************************************************************/
double read_angleY(void)
{
	int16_t GyroData[3] = {0};
	int16_t AccData[3] = {0};
	int16_t acc_Y = 0;//沿Y正方向加速度
	int16_t w_Z = 0;//绕Z轴角速度
	double angleY = 0;
	printf("into read_angleY");
	MPU6050GyroRead(GyroData);
	MPU6050AccRead(AccData);
	printf("get data");
	w_Z = (GyroData[2]/Gyro1000scale_JD)-gyro_zOFFSET;
	acc_Y = AccData[1]/Acc1000scale_JD;
	angleY = acos(((w_Z*w_Z*StickLength)-acc_Y)/MPU6050_ONE_G);//arccos{[(w_Z^2)*r-a_Y]/g}
	printf("GyroData\tY %.2lf`\n",angleY);
	return angleY;
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
/**************************实现函数********************************************
*函数原型:		void MPU6050_initialize(void)
*功　　能:	    初始化 	MPU6050 以进入可用状态。
*******************************************************************************/
void MPU6050_initialize(void) {
	IICwriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x80);      //唤醒
    delay_ms(50);
    IICwriteByte(devAddr, MPU6050_RA_SMPLRT_DIV, 0x00);      //SMPLRT_DIV    -- SMPLRT_DIV = 0  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
	IICwriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x03);      //PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0;不睡觉，不循环，使能温度传感器。 CLKSEL 3 (PLL with Z Gyro reference)
	IICwriteByte(devAddr, MPU6050_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 1 << 4 | 0 << 3 | 0 << 2 | 1 << 1 | 0 << 0);		//interrupt status bits are cleared on any read operation
	IICwriteByte(devAddr, MPU6050_RA_INT_ENABLE, 1<<0);		//interupt occurs when data is ready. 
	IICwriteByte(devAddr, MPU6050_RA_CONFIG, MPU6050_DLPF_BW_42);  //EXT_SYNC_SET 0 (disable input pin for data sync) ; default DLPF_CFG = 0 => ACC bandwidth = 260Hz  GYRO bandwidth = 256Hz)
	IICwriteByte(devAddr, MPU6050_RA_GYRO_CONFIG, 0x00);      //FS_SEL = 0: Full scale set to 250 deg/sec
    IICwriteByte(devAddr, MPU6050_RA_ACCEL_CONFIG, 1 << 3);//Full scale set to 4g
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


