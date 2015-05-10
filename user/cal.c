#ifndef ARM_MATH_CM4
#define ARM_MATH_CM4
#endif

#include "stm32f30x.h"
#include "cal.h"
#include "MPU6050.h"
#include "usart.h"
#include "extern_variable.h"
#include "arm_math.h"
#include "adc.h"



/*
	*功能	卡尔曼滤波
	*使用全局变量
			S_FLOAT_GyroAngle.AngleY(deg)
			S_FLOAT_AccAngle.AngleY(deg)
	*输入	Accel(加速度计解算的角度)
			Gyro(陀螺仪解算的角度)
*/
float Q_angle = 0.001;  
float Q_gyro  = 0.003;
float R_angle = 0.5;
float dt      = 0.01;//dt为kalman滤波器采样时间;
char  C_0     = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 }, \
				   { 0, 1 } };
void KalmanFilter_Y(float Accel,float Gyro) 	
{
//	LowerFilter(S_FLOAT_AccAngle.AngleY);//低通滤波(加速度计)
	
	angleY[1] += (Gyro - Q_bias) * dt; //先验估计
	
	Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3] = Q_gyro;
	
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - angleY[1];	//zk-先验估计
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	angleY[1] += K_0 * Angle_err;	 //后验估计
	Q_bias += K_1 * Angle_err;	 //后验估计
	S_FLOAT_GyroAngle.AngleX  = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
}

/* 
	*功能	程序判断滤波（低通滤波器） 
	*使用全局变量
			HistoryAcc_Y[2]
	*输入	加速度计结算出的角度
	*输出	滤波后加速度计结算出的角度
*/
#define D 0.01
float HistoryAcc_Y[2]={0};//须在第一次用该函数前赋HistoryAcc_Y[1]
float LowerFilter(float Acc_Y)
{
	float NewAcc_Y;
	
	NewAcc_Y = Acc_Y;
	if((NewAcc_Y-HistoryAcc_Y[1]>D)||(HistoryAcc_Y[1]-NewAcc_Y>D)){
		NewAcc_Y = 2*HistoryAcc_Y[1]-HistoryAcc_Y[0];
	}
	HistoryAcc_Y[0] = HistoryAcc_Y[1];
	HistoryAcc_Y[1] = NewAcc_Y;
	return NewAcc_Y;
}
/* 
	*功能	初始化低通滤波器 
	*使用条件
			使用加速度计原始数据计算得第一次数据之后cal_AccAngleY()
*/
void LowerFilter_init(void)
{
	HistoryAcc_Y[1] = S_FLOAT_AccAngle.AngleY;
}
/*
	*功能	借用加速度计原始数据计算与竖直方向的夹角(反正弦)
	*使用条件
			读取得第一次数据之后
	*使用全局变量
			S_FLOAT_AccAngle.AngleY(deg)
			S_FLOAT_AccAngle.ZeroPointY(deg)
	*输出	S_FLOAT_AccAngle.AngleY(deg)
*/
float cal_AccAngleY(void)
{
	float acc_Y = 0;//沿Y正方向加速度(g)
	
	//printf("into cal_AccAngleY\n");
	acc_Y = (AccData[1]/Acc4scale_JD)-S_FLOAT_AccAngle.ZeroPointY;
	S_FLOAT_AccAngle.AngleY = (asin(acc_Y)/TORAD);//arcsin(acc_Y/g)*(180/3.14159)
	//printf("原始数据：%d\n", AccData[1]);
	//printf("Zero = %f\tcal_AccAngleY\tY %.2f`acc_Y = %f\n",S_FLOAT_AccAngle.ZeroPointY, S_FLOAT_AccAngle.AngleY, acc_Y);
	
	return S_FLOAT_AccAngle.AngleY;
}
/*
	*功能	借用陀螺仪原始数据计算与竖直方向的夹角(积分)
	*使用条件
			读取得第一次数据之后
	*使用全局变量
			S_FLOAT_GyroAngle.AngleX(deg)
			S_FLOAT_GyroAngle.ZeroPointX(deg)
	*输出	S_FLOAT_GyroAngle.AngleX(deg)
	*疑问	
*/
float cal_GyroAngleY(void)
{
	float w_X = 0;//绕x轴正方向角速度(deg/s)
	const float dt = 0.01;
	//printf("into cal_GyroAngleY\n");
	printf("原始数据 ： %d\n",GyroData[0]);
	w_X = (GyroData[0]/Gyro250scale_JD-S_FLOAT_GyroAngle.ZeroPointX);//
	printf("w_X = %f\n",w_X);
	S_FLOAT_GyroAngle.AngleX += w_X*dt;//AngleY = AngleY + w_X*dt
	printf("cal_GyroAngleY\tY %.2f`\t 零漂 = %f\n",S_FLOAT_GyroAngle.AngleX, S_FLOAT_GyroAngle.ZeroPointX);
	
	return S_FLOAT_GyroAngle.AngleX;
}
/* 设置零漂点 */
void SetZeroPoint(void)
{
	uint8_t loop_i = 0;
	int32_t sum = 0;
	
	for(loop_i=0;loop_i<100;loop_i++){
		if((loop_i>=0)&&(loop_i<10)){
			MPU6050GyroRead(GyroData);
		}
		else if((loop_i>=10)&&(loop_i<100)){
			MPU6050GyroRead(GyroData);
			S_FLOAT_GyroAngle.ZeroPointX = GyroData[0]/Gyro250scale_JD;//角速度零漂（deg/s）
			sum += S_FLOAT_GyroAngle.ZeroPointX;
		}
	}
	S_FLOAT_GyroAngle.ZeroPointX = sum/90.0;
	sum = 0;
	loop_i=0;
	//printf("S_FLOAT_GyroAngle.ZeroPointX = %.2f\n",S_FLOAT_GyroAngle.ZeroPointX);
	
	for(loop_i=0;loop_i<100;loop_i++){
		if((loop_i>=0)&&(loop_i<10)){
			MPU6050AccRead(AccData);
		}
		else if((loop_i>=10)&&(loop_i<100)){
			MPU6050AccRead(AccData);
			S_FLOAT_AccAngle.ZeroPointY = AccData[1]/Acc4scale_JD;//加速度零漂（g）
			sum += S_FLOAT_AccAngle.ZeroPointY;
		}
	}
	S_FLOAT_AccAngle.ZeroPointY = sum/90.0;
	sum = 0;
	loop_i=0;
	//printf("S_FLOAT_AccAngle.ZeroPointY = %.2f\n",S_FLOAT_AccAngle.ZeroPointY);
}

/*
	*功能	算出电机需转角度值, 并返回
	*使用条件
			无
	*使用全局变量
			GyroData[2]
			angleY
	*输入	无
	*输出	(float) AngleToMove
*/
extern uint8_t flag_50ms ;
extern int start_flag;
float AcculateMotorMoveAngle(void)
{
	float AngleToMove = 0;//电机需转弧度值（rad）
	float adc_w = 0;//杆角速度(deg/s)
	
	if(flag_50ms == 1){
		adc_w = (AD_angleY[1]-AD_angleY[0])/0.05f ;
		printf("angleY=%f,w=%f\n",AD_angleY[1],adc_w);
		flag_50ms = 0;
	}
	/* Task 2 */
//	if(start_flag == 0){
//		if(adc_w <= 2){
//			StepMotor_move((int)(AD_angleY[1]), 1);
//			//printf("%f,%f,%f\n",g_angleY*180/3.1415926f,a_angleY,angleY);
//		}
//	}
//	else{
//		if(adc_w >= 2){
//		StepMotor_move(0.0f, 1);
//		}
//	}
	AngleToMove = asin( (MPU6050_ONE_G*sin(AD_angleY[1]*TORAD))/				\
						sqrt((MPU6050_ONE_G*MPU6050_ONE_G)+((adc_w*TORAD*adc_w*TORAD*StickLength)*(adc_w*TORAD*adc_w*TORAD*StickLength+2*MPU6050_ONE_G*cos(AD_angleY[1]*TORAD)))) );
					/* AlPhe = arcsin{ g*sin(angleY)/sqrt[g^2+(w^2 * r)*((w^2 * r)+2g*cos(angleY))] } */
	printf("RadToMove=%f\n",AngleToMove/TORAD);
	return (AngleToMove/TORAD);
}

/*
	*功能	角度值原始数据IIC获取(约需1.890ms)
	*全局变量
			GyroData[3]
			AccData[3]
			AD_angleY[2]
			S_FLOAT_AccAngle.AngleY
			S_FLOAT_GyroAngle.AngleX
			angleY[2]
	*
*/
void cal_angle(void)
{
	if(ReceiveDataEn == 1){
		ReceiveDataEn = 0;
		MPU6050GyroRead(GyroData);
		MPU6050AccRead(AccData);
		//printf("GyroData X=%d,Y=%d,Z=%d\n",GyroData[0],GyroData[1],GyroData[2]);
		//printf("angleY[1] = %f\t AccAngle = %f\t GyroAngle = %f\n",angleY[1],S_FLOAT_AccAngle.AngleY,S_FLOAT_GyroAngle.AngleX);
	}
	AD_angleY[0] = AD_angleY[1];
	AD_angleY[1] = voltage_to_de();
}
