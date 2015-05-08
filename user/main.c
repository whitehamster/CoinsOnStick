/*	
	*管教分配:
		PA1			TI
		PA.4		paulse
		PA.5		direction
		PB6			SCL
		PB7			SDA
	*全局变量
		EndOfTransfer			DMA传送完成标志位
		DstBuffer[BUFFER_SIZE]	DMA接受数据寄存器RAM
		TimingDelay				延时预载值寄存器
		ReceiveDataEn			接收MPU6050数据使能
		Angle_pre				先前电机(平板)角度寄存器
		buffer[14]				IIC读取MPU6050数据暂存器
		angleY					摆杆与竖直方向夹角
		AccData[3]				
		GyroData[3]				
		SetZeroPoint_Flag		设置零点 标志位
	*算法说明: 
		中断置使能位
		主函数读数据, 处理数据, 驱动电机
	*作者:
		海璃
	*时间:
		2015/5/5
	*进度:
		YES: 
		NO:	DMP_Routing(); w不对
			修改 IICwriteBits() 尚未调试
*/
//待理解语录: 考虑到电机的转动频率是100Hz以上，因此我采用加速度计的低通滤波(DLPF)为98Hz, 
//            可以有效滤掉电机振动带来的影响, 结合平滑滤波效果应该不错.

#include "main.h"

	




int main(){
	/* 初始化 */
	usart2_init();			//串口2初始化
	delay_init();			//延时初始化
	
	IIC_Init();				//软件模拟IIC初始化
	MPU6050_initialize();	//初始化MPU6050
	MPU6050_DMP_Initialize();
	EXTI1_Config();			//中断初始化( 须在DMP初始化之后配置 )
	SetZeroPoint();			//等待DMP零点设置成功
	
	StepMotor_IOconf();		//步进电机管脚配置
	StepMotor_init();		//初始化步进电机(确认初始稳定时角度)
	
	while(1){
		angleY = Q_ANGLE.Yaw-Angle_ZeroPoint;
		//printf("angleY = %f\n",angleY);
		StepMotor_move(AcculateMotorMoveAngle());// 转动电机 
	}
	return 1;
}





//		printf("Q_ANGLE.Yaw = %f\n",Q_ANGLE.Yaw);
//		printf("DMP_DATA.dmp_gyroz = %f\n",DMP_DATA.dmp_gyroz);














	
/*
	//检测是否成功握手
	while(!MPU6050_testConnection()){
		printf("NO DEVINCE!");
		delay_ms(2000);
	}
*/
	
/*	测Z轴角速度零漂
	while(1){
		uint8_t loop_i = 0;
		int16_t gyro_z = {0};
		int32_t sum_z = 0;
		for(loop_i=0;loop_i<100;loop_i++){
			MPU6050GyroRead(gyroData);
			sum_z += gyroData[2];
		}
		gyro_z = sum_z/100.0;
		printf("GyroData\tX %.2f`\tY %.2f`\tZ %.2f`\t\n",gyroData[0]/16.4,gyroData[1]/16.4,gyro_z/16.4);
		sum_z = 0;
		loop_i=0;
		delay_ms(100);
	}
*/	

/*	串口部分
	//发送内部数据
	while(1){  
		printf("\n%d s\t passed!",time++);
		delay_ms(1000);
	} 
	//处理由串口接受到的数据
	while(1){
		Usart2Received_DMA1start();
		for(loop_i=0;loop_i<8;loop_i++){
			printf("%c\t",DstBuffer[loop_i]);
		}
		delay_ms(1000);
		printf("\nwait for the next putin :\n");
	}
*/
