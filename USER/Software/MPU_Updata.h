#ifndef __MPU_UPDATA_H
#define __MPU_UPDATA_H

struct IMU_t
{
	short gyro[3];  // ������ԭʼ����
	short accel[3]; //���ٶȴ�����ԭʼ����
	float temp;//�¶�

	struct//ŷ����У׼error
	{
		float intercept[3];
		float slope[3];
	}calibration;

	struct
	{
		float pitch, yaw, roll; //ŷ����
	}angle;
};
//extern float pitch,roll,yaw; 		    //ŷ����
//extern short aacx,aacy,aacz;			//���ٶȴ�����ԭʼ����
//extern short gyrox,gyroy,gyroz;			//������ԭʼ����
//extern float temp;					    //�¶�

//�ⲿ����
extern struct IMU_t IMU_data;
void mpu6050_Init(void);
void mpu6050_updata(void);

#endif
