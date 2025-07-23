#ifndef __ENCODER_H // 检查__MOTOR_H宏是否未定义，以防止头文件被重复包含
#define __ENCODER_H // 定义__MOTOR_H宏

#include "main.h" // 包含主头文件，其中包含了MCU系列和HAL库的配置

void Encoder_Init(void);
int MotorB_ActualSpeed(void);
int MotorC_ActualSpeed(void);
float GetMotorSpeed(uint8_t motor_id);


#endif // __MOTOR_H
