#ifndef __MPU_UPDATA_H
#define __MPU_UPDATA_H

struct IMU_t
{
	short gyro[3];  // 陀螺仪原始数据
	short accel[3]; //加速度传感器原始数据
	float temp;//温度

	struct//欧拉角校准error
	{
		float intercept[3];
		float slope[3];
	}calibration;

	struct
	{
		float pitch, yaw, roll; //欧拉角
	}angle;
};
//extern float pitch,roll,yaw; 		    //欧拉角
//extern short aacx,aacy,aacz;			//加速度传感器原始数据
//extern short gyrox,gyroy,gyroz;			//陀螺仪原始数据
//extern float temp;					    //温度

//外部调用
extern struct IMU_t IMU_data;
void mpu6050_Init(void);
void mpu6050_updata(void);

#endif
