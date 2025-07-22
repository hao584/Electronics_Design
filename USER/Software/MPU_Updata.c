#include "IIC.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "math.h"

#include "MPU_Updata.h"

#define Sample_size 200//陀螺仪校准的样本的大小

//float pitch,roll,yaw; 		    //欧拉角
//short aacx,aacy,aacz;			//加速度传感器原始数据
//short gyrox,gyroy,gyroz;		//陀螺仪原始数据
//float temp;					    //温度

struct IMU_t IMU_data; // IMU数据结构体
//内部调用
void calculate_slope_and_intercept(float *y, int num_points, float threshold, float *slope, float *intercept);
void Gyroscope_calibration(void);
//样本
float x_[Sample_size];//T.T不要太大了，太占内存了，这是粑粑，后面再改
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
	//取值
	MPU_Get_Accelerometer(&IMU_data.accel[0],&IMU_data.accel[1], &IMU_data.accel[2]);		//得到加速度传感器数据
    MPU_Get_Gyroscope(&IMU_data.gyro[0], &IMU_data.gyro[1],&IMU_data.gyro[2]);		//得到陀螺仪数据
    IMU_data.temp = MPU_Get_Temperature();						//得到温度信息

//	while(mpu_dmp_get_data(&IMU_data.angle.pitch, &IMU_data.angle.roll, &IMU_data.angle.yaw)); 
	mpu_dmp_get_data(&IMU_data.angle.pitch, &IMU_data.angle.roll, &IMU_data.angle.yaw);
	//校准
	Gyroscope_calibration();//校准偏移值
}

/*
陀螺仪教准函数，缓解陀螺仪零飘问题
*/
int flag = 0;//标志位
void Gyroscope_calibration()
{
	if(flag ==0)//保证这段程序只运行一次
	{
		//采样
		for (int i = 0; i < Sample_size;i++)
		{
			x_[i] = IMU_data.angle.pitch;
			y_[i] = IMU_data.angle.yaw;
			z_[i] = IMU_data.angle.roll;
		}
		//计算
		calculate_slope_and_intercept(x_,Sample_size, 0.5f,&IMU_data.calibration.slope[0],&IMU_data.calibration.intercept[0]);
		calculate_slope_and_intercept(y_,Sample_size, 0.5f,&IMU_data.calibration.slope[1],&IMU_data.calibration.intercept[1]);
		calculate_slope_and_intercept(z_,Sample_size, 0.5f,&IMU_data.calibration.slope[2],&IMU_data.calibration.intercept[2]);	

			//校准1减掉截距
		IMU_data.angle.pitch -= IMU_data.calibration.intercept[0];
		IMU_data.angle.yaw  -= IMU_data.calibration.intercept[1];
		IMU_data.angle.roll -= IMU_data.calibration.intercept[2];
		flag = 1;//flag赋1后这段程序就不再运行了
	}

	//校准2减掉斜率
	IMU_data.angle.pitch -= IMU_data.calibration.slope[0];
	IMU_data.angle.yaw -= IMU_data.calibration.slope[1];
	IMU_data.angle.roll -= IMU_data.calibration.slope[2];
}
/*
//功能
	计算一组数据二元一次方程的斜率跟截距
//输入值
	*y：要计算的数据
	threshold：有效数据的阈值（上下极值）
	num_points：数据的总数
//输出值
	slope：斜率
	intercept：截距
*/
void calculate_slope_and_intercept(float *y, int num_points, float threshold, float *slope, float *intercept)   
{    
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;    
    int valid_points = 0; // 记录有效点的数量，修正为int类型  
    
    for (int i = 0; i < num_points; i++)   
    {    
        float current_y = y[i];    
        if (fabs(current_y) <= threshold) // 检查y值是否小于或等于阈值  
        {   
            float x = i + 1; // 假设x是从1开始的连续整数  
            sum_x += x;  
            sum_y += current_y;  
            sum_xy += x * current_y;  
            sum_x2 += x * x;  
            valid_points++; // 增加有效点的计数  
        }    
    }    
    if (valid_points < 2) // 检查是否有足够的有效点来计算斜率和截距  
    {    
        // 如果没有足够的有效点，则无法计算斜率和截距  
        *slope = 1; 
        *intercept = 0;  
        return;  
    }    
    
    // 使用最小二乘法公式计算斜率和截距，注意防止除以零  
    float denominator = valid_points * sum_x2 - sum_x * sum_x;  
    if (denominator == 0) 
	{  
        *intercept = 0;  
    } 
	else 
	{  
        *slope = (valid_points * sum_xy - sum_x * sum_y) / denominator;  
        *intercept = (sum_y * sum_x2 - sum_x * sum_xy) / (denominator * valid_points);
        // 或者使用均值公式: *intercept = (sum_y / valid_points) - (*slope * (sum_x / valid_points));  
    }  
}

