#include "IIC.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "math.h"

#include "MPU_Updata.h"

#define Sample_size 200//������У׼�������Ĵ�С

//float pitch,roll,yaw; 		    //ŷ����
//short aacx,aacy,aacz;			//���ٶȴ�����ԭʼ����
//short gyrox,gyroy,gyroz;		//������ԭʼ����
//float temp;					    //�¶�

struct IMU_t IMU_data; // IMU���ݽṹ��
//�ڲ�����
void calculate_slope_and_intercept(float *y, int num_points, float threshold, float *slope, float *intercept);
void Gyroscope_calibration(void);
//����
float x_[Sample_size];//T.T��Ҫ̫���ˣ�̫ռ�ڴ��ˣ��������Σ������ٸ�
float y_[Sample_size];
float z_[Sample_size];
		
void mpu6050_Init()
{
	MPU_Init();
	mpu_dmp_init();
//	if(MPU_Init()==0&&mpu_dmp_init()==0)
//	{

//	}
}

void mpu6050_updata()
{
	//ȡֵ
	MPU_Get_Accelerometer(&IMU_data.accel[0],&IMU_data.accel[1], &IMU_data.accel[2]);		//�õ����ٶȴ���������
    MPU_Get_Gyroscope(&IMU_data.gyro[0], &IMU_data.gyro[1],&IMU_data.gyro[2]);		//�õ�����������
    IMU_data.temp = MPU_Get_Temperature();						//�õ��¶���Ϣ

//	while(mpu_dmp_get_data(&IMU_data.angle.pitch, &IMU_data.angle.roll, &IMU_data.angle.yaw)); 
	mpu_dmp_get_data(&IMU_data.angle.pitch, &IMU_data.angle.roll, &IMU_data.angle.yaw);
	//У׼
	Gyroscope_calibration();//У׼ƫ��ֵ
}

/*
�����ǽ�׼������������������Ʈ����
*/
int flag = 0;//��־λ
void Gyroscope_calibration()
{
	if(flag ==0)//��֤��γ���ֻ����һ��
	{
		//����
		for (int i = 0; i < Sample_size;i++)
		{
			x_[i] = IMU_data.angle.pitch;
			y_[i] = IMU_data.angle.yaw;
			z_[i] = IMU_data.angle.roll;
		}
		//����
		calculate_slope_and_intercept(x_,Sample_size, 0.5f,&IMU_data.calibration.slope[0],&IMU_data.calibration.intercept[0]);
		calculate_slope_and_intercept(y_,Sample_size, 0.5f,&IMU_data.calibration.slope[1],&IMU_data.calibration.intercept[1]);
		calculate_slope_and_intercept(z_,Sample_size, 0.5f,&IMU_data.calibration.slope[2],&IMU_data.calibration.intercept[2]);	

			//У׼1�����ؾ�
		IMU_data.angle.pitch -= IMU_data.calibration.intercept[0];
		IMU_data.angle.yaw  -= IMU_data.calibration.intercept[1];
		IMU_data.angle.roll -= IMU_data.calibration.intercept[2];
		flag = 1;//flag��1����γ���Ͳ���������
	}

	//У׼2����б��
	IMU_data.angle.pitch -= IMU_data.calibration.slope[0];
	IMU_data.angle.yaw -= IMU_data.calibration.slope[1];
	IMU_data.angle.roll -= IMU_data.calibration.slope[2];
}
/*
//����
	����һ�����ݶ�Ԫһ�η��̵�б�ʸ��ؾ�
//����ֵ
	*y��Ҫ���������
	threshold����Ч���ݵ���ֵ�����¼�ֵ��
	num_points�����ݵ�����
//���ֵ
	slope��б��
	intercept���ؾ�
*/
void calculate_slope_and_intercept(float *y, int num_points, float threshold, float *slope, float *intercept)   
{    
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;    
    int valid_points = 0; // ��¼��Ч�������������Ϊint����  
    
    for (int i = 0; i < num_points; i++)   
    {    
        float current_y = y[i];    
        if (fabs(current_y) <= threshold) // ���yֵ�Ƿ�С�ڻ������ֵ  
        {   
            float x = i + 1; // ����x�Ǵ�1��ʼ����������  
            sum_x += x;  
            sum_y += current_y;  
            sum_xy += x * current_y;  
            sum_x2 += x * x;  
            valid_points++; // ������Ч��ļ���  
        }    
    }    
    if (valid_points < 2) // ����Ƿ����㹻����Ч��������б�ʺͽؾ�  
    {    
        // ���û���㹻����Ч�㣬���޷�����б�ʺͽؾ�  
        *slope = 1; 
        *intercept = 0;  
        return;  
    }    
    
    // ʹ����С���˷���ʽ����б�ʺͽؾ࣬ע���ֹ������  
    float denominator = valid_points * sum_x2 - sum_x * sum_x;  
    if (denominator == 0) 
	{  
        *intercept = 0;  
    } 
	else 
	{  
        *slope = (valid_points * sum_xy - sum_x * sum_y) / denominator;  
        *intercept = (sum_y * sum_x2 - sum_x * sum_xy) / (denominator * valid_points);
        // ����ʹ�þ�ֵ��ʽ: *intercept = (sum_y / valid_points) - (*slope * (sum_x / valid_points));  
    }  
}

