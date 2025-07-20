#ifndef __MOTOR_H // 检查__MOTOR_H宏是否未定义，以防止头文件被重复包含
#define __MOTOR_H // 定义__MOTOR_H宏

#include "main.h" // 包含主头文件，其中包含了MCU系列和HAL库的配置

void MotorA_Speed(float Speed);
void MotorB_Speed(float Speed);
void MotorC_Speed(float Speed);
void MotorD_Speed(float Speed);
void Motor_Init(void);



#endif // __MOTOR_H
