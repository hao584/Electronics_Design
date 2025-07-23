#include "Encoder.h" // 包含编码器相关的头文件
#include "tim.h"     // 包含定时器相关的头文件

// 定义电机数量
#define MOTOR_NUM 4

// 全局变量：存储上一次的计数器值和时间戳
static int32_t last_count[MOTOR_NUM] = {0};
static uint32_t last_time[MOTOR_NUM] = {0};


/**
  * @brief 初始化编码器定时器，并记录初始值
  */
void Encoder_Init(void) {
    // 启动编码器定时器（根据实际硬件连接，这里以四个定时器为例）
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    // 初始化每个电机的上一次计数器和时间戳
    for (int i = 0; i < MOTOR_NUM; i++) {
        last_time[i] = HAL_GetTick();
        switch (i) {
            case 0: last_count[i] = __HAL_TIM_GET_COUNTER(&htim3); break;
            case 1: last_count[i] = __HAL_TIM_GET_COUNTER(&htim4); break;
            default: break;
        }
    }
}


/**
  * @brief  获取电机B的实际速度。
  * @param  无。
  * @retval int: 返回电机B的实际速度值。
  */
int MotorB_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim3); // 读取定时器3的计数器值
		__HAL_TIM_SetCounter(&htim3 , 0);//清空计数值
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3) == 0) // 检查定时器3是否向上计数
    {
        ActualSpeed = ActualSpeed; // 如果是向上计数，速度为正
    }
    else
    {
        ActualSpeed = -ActualSpeed; // 如果是向下计数，速度为负
    }
    return ActualSpeed; // 返回电机B的实际速度
}

/**
  * @brief  获取电机C的实际速度。
  * @param  无。
  * @retval int: 返回电机C的实际速度值。
  */
int MotorC_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim4); // 读取定时器4的计数器值
		__HAL_TIM_SetCounter(&htim4 , 0);//清空计数值
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4) == 0) // 检查定时器4是否向上计数
    {
        ActualSpeed = ActualSpeed; // 如果是向上计数，速度为正
    }
    else
    {
        ActualSpeed = -ActualSpeed; // 如果是向下计数，速度为负
    }
    return ActualSpeed; // 返回电机C的实际速度
}



/**
  * @brief 获取电机速度
  * @param motor_id: 电机ID（0-3分别对应四个定时器）
  * @param ppr: 编码器每转脉冲数（考虑减速比后的值，即电机输出轴转一圈的脉冲数）
  * @retval 电机转速（RPM）
  */
float GetMotorSpeed(uint8_t motor_id) {
    if (motor_id >= MOTOR_NUM) {
        return 0.0f; // 错误的电机ID
    }

    TIM_HandleTypeDef* htim = NULL;
    switch (motor_id) {
        case 0: htim = &htim3; break;
        case 1: htim = &htim4; break;
        default: return 0.0f;
    }

    // 获取当前计数和时间
    int32_t current_count = __HAL_TIM_GET_COUNTER(htim);
    uint32_t current_time = HAL_GetTick();

    // 计算脉冲增量（处理计数器溢出）
    int32_t pulse_diff = current_count - last_count[motor_id];
    if (pulse_diff > 32767) {
        pulse_diff -= 65536;
    } else if (pulse_diff < -32768) {
        pulse_diff += 65536;
    }

    // 计算时间差（秒）
    float time_diff = (current_time - last_time[motor_id]) / 1000.0f;

    // 更新上一次记录
    last_count[motor_id] = current_count;
    last_time[motor_id] = current_time;

    // 避免除以0
    if (time_diff < 0.0001f) {
        return 0.0f;
    }

    // 计算转速 RPM = (脉冲增量 / 时间差) * (60秒/分钟) / (每转脉冲数 * 4)
    // 乘以4是因为正交编码模式下，每个周期有4个边沿（上升沿和下降沿都会计数），所以每个周期的脉冲数乘以4
    float rpm = (pulse_diff / time_diff) * 60.0f / (330.0 * 4.0f);

    return rpm;
}
