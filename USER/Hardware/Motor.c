#include "Motor.h" // 包含电机控制相关的头文件
#include "tim.h"   // 包含定时器配置相关的头文件

/**
  * @brief  设置电机A的速度。
  * @param  Speed: 电机A的速度值，正数表示正转，负数表示反转，0表示停止。
  * @retval 无。
  */
void MotorA_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);   // 电机A正转
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET); // 停止电机A反转
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, -Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET); // 停止电机A正转
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);   // 电机A反转
    }
}

/**
  * @brief  设置电机B的速度。
  * @param  Speed: 电机B的速度值，正数表示正转，负数表示反转，0表示停止。
  * @retval 无。
  */
void MotorB_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);   // 电机B正转
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET); // 停止电机B反转
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, -Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET); // 停止电机B正转
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);   // 电机B反转
    }
}

/**
  * @brief  设置电机C的速度。
  * @param  Speed: 电机C的速度值，正数表示正转，负数表示反转，0表示停止。
  * @retval 无。
  */
void MotorC_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_SET);   // 电机C正转
        HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_RESET); // 停止电机C反转
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, -Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_RESET); // 停止电机C正转
        HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_SET);   // 电机C反转
    }
}

/**
  * @brief  设置电机D的速度。
  * @param  Speed: 电机D的速度值，正数表示正转，负数表示反转，0表示停止。
  * @retval 无。
  */
void MotorD_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);   // 电机D正转
        HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_SET); // 停止电机D反转
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, -Speed); // 设置PWM占空比，控制速度
        HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_SET); // 停止电机D正转
        HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_RESET);   // 电机D反转
    }
}

/**
  * @brief  初始化四个电机的PWM通道，并设置初始速度为0。
  * @param  无。
  * @retval 无。
  */
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1); // 启动PWM通道1
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2); // 启动PWM通道2
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3); // 启动PWM通道3
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4); // 启动PWM通道4
    MotorA_Speed(0); // 初始化电机A速度为0
    MotorB_Speed(0); // 初始化电机B速度为0
    MotorC_Speed(0); // 初始化电机C速度为0
    MotorD_Speed(0); // 初始化电机D速度为0
}
