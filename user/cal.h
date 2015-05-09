#ifndef __cal_h
#define __cal_h
	
	#define StickLength			1.5f			//´ý²â(Ã×)
	#define MPU6050_ONE_G		9.80665f
	#define TORAD				(3.14159/180.0f)// 0.01745 rad/deg
	#define Gyro250scale_JD	(32768.0/250.0f)// 131.1 LSB/(deg/sec)
	#define Acc4scale_JD		(32768.0/4.0f)	// 8192 LSB/g
	
	
	void LowerFilter_init(void);
	float LowerFilter(float Acc_Y);
	float cal_AccAngleY(void);
	float cal_GyroAngleY(void);
	void KalmanFilter_Y(float Accel,float Gyro);
	void SetZeroPoint(void);
	void cal_angle(void);
#endif