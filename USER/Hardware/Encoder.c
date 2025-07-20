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
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

    // 初始化每个电机的上一次计数器和时间戳
    for (int i = 0; i < MOTOR_NUM; i++) {
        last_time[i] = HAL_GetTick();
        switch (i) {
            case 0: last_count[i] = __HAL_TIM_GET_COUNTER(&htim5); break;
            case 1: last_count[i] = __HAL_TIM_GET_COUNTER(&htim3); break;
            case 2: last_count[i] = __HAL_TIM_GET_COUNTER(&htim4); break;
            case 3: last_count[i] = __HAL_TIM_GET_COUNTER(&htim1); break;
            default: break;
        }
    }
}

/**
  * @brief  获取电机A的实际速度。
  * @param  无。
  * @retval int: 返回电机A的实际速度值。
  */
int MotorA_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim5); // 读取定时器5的计数器值
	__HAL_TIM_SetCounter(&htim5 , 0);//清空计数值
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5) == 0) // 检查定时器5是否向上计数
    {
        ActualSpeed = ActualSpeed; // 如果是向上计数，速度为正
    }
    else
    {
        ActualSpeed = -ActualSpeed; // 如果是向下计数，速度为负
    }
		
    return ActualSpeed; // 返回电机A的实际速度
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
  * @brief  获取电机D的实际速度。
  * @param  无。
  * @retval int: 返回电机D的实际速度值。
  */
int MotorD_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim1); // 读取定时器1的计数器值
		__HAL_TIM_SetCounter(&htim1 , 0);//清空计数值
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1) == 0) // 检查定时器1是否向上计数
    {
        ActualSpeed = ActualSpeed; // 如果是向上计数，速度为正
    }
    else
    {
        ActualSpeed = -ActualSpeed; // 如果是向下计数，速度为负
    }
    return ActualSpeed; // 返回电机D的实际速度
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
        case 0: htim = &htim5; break;
        case 1: htim = &htim3; break;
        case 2: htim = &htim4; break;
        case 3: htim = &htim1; break;
        default: return 0.0f;
    }

    // 获取当前计数和时间
    int32_t current_count = __HAL_TIM_GET_COUNTER(htim);
    uint32_t current_time = HAL_GetTick();

    // 计算脉冲增量（处理计数器溢出）
    int32_t pulse_diff = current_count - last_count[motor_id];
    // 注意：如果计数器是16位，且可能溢出，这里需要做溢出修正（假设定时器是16位，计数范围0-65535）
    // 32位计数器的溢出问题较复杂，这里暂不考虑，因为STM32的定时器通常是16位
    // 对于16位定时器，当计数超过65535或低于0时，会重新计数，因此我们需要处理这种情况
    // 如果脉冲差超过0x8000（即32768），则说明发生了向下溢出（反向旋转且计数从0跳到65535）
    // 如果脉冲差小于-0x8000，则说明发生了向上溢出（正向旋转且计数从65535跳到0）
    // 注意：这里假设定时器是递增计数，且编码器模式会自动处理方向（计数可以增加或减少）
    // 由于编码器模式下，定时器可以递增或递减计数，所以脉冲差直接相减即可，不需要处理溢出，因为定时器是16位有符号数（实际是16位无符号，但转换为32位后做差）
    // 但是，如果脉冲差很大（超过16位的正负范围），我们可以通过以下方式修正：
    // 如果脉冲差 > 32767，则 pulse_diff -= 65536;
    // 如果脉冲差 < -32768，则 pulse_diff += 65536;
    // 但是，由于编码器模式下，两次读取之间不可能有超过32767个脉冲（因为时间间隔很短），所以通常不需要处理，但为了安全，可以加上
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
