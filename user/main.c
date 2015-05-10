/*	
	*管教分配:
		PA1			INT
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
		angleY[1]					摆杆与竖直方向夹角
		AccData[3]				
		GyroData[3]				
		SetZeroPoint_Flag		设置零点 标志位
	*算法说明: 
		中断置使能位
		主函数读数据, 处理数据, 驱动电机
	*作者:
		海璃
	*时间:
		2015/5/10
	*进度:
		YES: 
		NO:	添加KalmanFilter 尚未调试（精度待确认）
			Acc低通滤波未调试
			考虑到电机的转动频率是100Hz以上，因此我采用加速度计的低通滤波(DLPF)为98Hz, 
		可以有效滤掉电机振动带来的影响, 结合平滑滤波效果应该不错.(已加，待加电机测试)
			
	*NONO:
		TIM3(100ms)读取数据（使用Tim2作延时函数），结果停在delay函数中的while中
			
*/
#include "main.h"

int main(){

	/* 初始化 */
	usart2_init();			//串口2初始化
	delay_init();			//延时初始化
	IIC_Init();				//软件模拟IIC初始化
	MPU6050_initialize();	//初始化MPU6050

	TIM3ch1_ITInit();		//定时解算初始化10ms
	SetZeroPoint();			//设置零漂移点
	StepMotor_IOconf();		//步进电机管脚配置
	StepMotor_init();		//初始化步进电机(确认初始稳定时角度)
	
	ad_init();				//电位器ad初始化
	TIM4_Init(72,50000);	//50ms定时计算摆杆角速度
	
	
	//		用手推动摆杆至一个角度 θ （ θ 在 45o～60o间） ，调整平板角度，在
	//	平板中心稳定叠放 8 枚 1 元硬币，见图 2；启动后放开摆杆让其自由
	//	摆动。在摆杆摆动过程中，要求控制平板状态使硬币在摆杆的 5 个摆
	//	动周期中不从平板上滑落，并保持叠放状态。根据平板上非保持叠放
	//	状态及滑落的硬币数计算成绩。
	//
	while(3){
		cal_angle();
	}
	return 1;
}










/*	Task 1
	//		控制电机使平板可以随着摆杆的摆动而旋转（3~5 周），摆杆摆一个周
	//	期，平板旋转一周（360o），偏差绝对值不大于45°。
	//	
	while(1){
		static uint8_t state = 0;
		AD_angleY[1] = voltage_to_de();
		//printf("AD_angleY %f\n",AD_angleY[1]);
		if(state == 0){
			state = 1;
			while(AD_angleY[1]>0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(180, 1);
			}
			while(AD_angleY[1]<0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(360, 1);
			}
		}
		else if(state == 1){
			state = 0;
			while(AD_angleY[1]>0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(180, 1);
			}
			while(AD_angleY[1]<0){
				AD_angleY[1] = voltage_to_de();
				StepMotor_move(0, 1);
			}
		}
	}
*/

/*	Task 2
	//		在平板上粘贴一张画有一组间距为 1cm 平行线的打印纸。用手推动摆
	//	杆至一个角度 θ （ θ 在 30o～45o间） ，调整平板角度，在平板中心稳
	//	定放置一枚 1 元硬币（人民币） ；启动后放开摆杆让其自由摆动。在摆
	//	杆摆动过程中，要求控制平板状态，使硬币在 5 个摆动周期中不从平
	//	板上滑落，并尽量少滑离平板的中心位置。
	//
	Task2_Exti_Config();
	while(2){
		cal_angle();
		AcculateMotorMoveAngle();
	}
*/







/*	以防丢步的电机驱动方法
	while(1){
		float buff_angle,buff_angel_int;
		buff_angle += AcculateMotorMoveAngle();
		buff_angel_int = (int) buff_angle;
		buff_angle -= buff_angel_int;
		StepMotor_move(buff_angel_int,1);
	}	
*/
	
/*	检测某一段程序在片上的实际运行时间
	TIM1ch1_ITInit();
	while(1){
		TIM_Cmd(TIM1,ENABLE);
		loop_i = TIM_GetCounter(TIM1);
		
		***   需测运行时间的函数体   ****
		
		loop_i = TIM_GetCounter(TIM1) - loop_i;
		printf("\n %dus\n",loop_i);
	}
*/
	
/*	解算角度
	while(1){
		//StepMotor_move(0);
		if(ReceiveDataEn == 1){
			ReceiveDataEn = 0;
			MPU6050GyroRead(GyroData);
			MPU6050AccRead(AccData);
			//printf("GyroData X=%d,Y=%d,Z=%d\n",GyroData[0],GyroData[1],GyroData[2]);
			cal_GyroAngleY();
			cal_AccAngleY();
			KalmanFilter_Y(S_FLOAT_AccAngle.AngleY, S_FLOAT_GyroAngle.AngleX);
			printf("angleY[1] = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY[1],S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleX);
		}
		//StepMotor_move(20);
		//printf("angleY[1] = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY[1],S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleX);
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
