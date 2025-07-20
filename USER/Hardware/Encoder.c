#include "Encoder.h" // ������������ص�ͷ�ļ�
#include "tim.h"     // ������ʱ����ص�ͷ�ļ�

// ����������
#define MOTOR_NUM 4

// ȫ�ֱ������洢��һ�εļ�����ֵ��ʱ���
static int32_t last_count[MOTOR_NUM] = {0};
static uint32_t last_time[MOTOR_NUM] = {0};


/**
  * @brief ��ʼ����������ʱ��������¼��ʼֵ
  */
void Encoder_Init(void) {
    // ������������ʱ��������ʵ��Ӳ�����ӣ��������ĸ���ʱ��Ϊ����
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

    // ��ʼ��ÿ���������һ�μ�������ʱ���
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
  * @brief  ��ȡ���A��ʵ���ٶȡ�
  * @param  �ޡ�
  * @retval int: ���ص��A��ʵ���ٶ�ֵ��
  */
int MotorA_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim5); // ��ȡ��ʱ��5�ļ�����ֵ
	__HAL_TIM_SetCounter(&htim5 , 0);//��ռ���ֵ
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5) == 0) // ��鶨ʱ��5�Ƿ����ϼ���
    {
        ActualSpeed = ActualSpeed; // ��������ϼ������ٶ�Ϊ��
    }
    else
    {
        ActualSpeed = -ActualSpeed; // ��������¼������ٶ�Ϊ��
    }
		
    return ActualSpeed; // ���ص��A��ʵ���ٶ�
}

/**
  * @brief  ��ȡ���B��ʵ���ٶȡ�
  * @param  �ޡ�
  * @retval int: ���ص��B��ʵ���ٶ�ֵ��
  */
int MotorB_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim3); // ��ȡ��ʱ��3�ļ�����ֵ
		__HAL_TIM_SetCounter(&htim3 , 0);//��ռ���ֵ
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3) == 0) // ��鶨ʱ��3�Ƿ����ϼ���
    {
        ActualSpeed = ActualSpeed; // ��������ϼ������ٶ�Ϊ��
    }
    else
    {
        ActualSpeed = -ActualSpeed; // ��������¼������ٶ�Ϊ��
    }
    return ActualSpeed; // ���ص��B��ʵ���ٶ�
}

/**
  * @brief  ��ȡ���C��ʵ���ٶȡ�
  * @param  �ޡ�
  * @retval int: ���ص��C��ʵ���ٶ�ֵ��
  */
int MotorC_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim4); // ��ȡ��ʱ��4�ļ�����ֵ
		__HAL_TIM_SetCounter(&htim4 , 0);//��ռ���ֵ
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4) == 0) // ��鶨ʱ��4�Ƿ����ϼ���
    {
        ActualSpeed = ActualSpeed; // ��������ϼ������ٶ�Ϊ��
    }
    else
    {
        ActualSpeed = -ActualSpeed; // ��������¼������ٶ�Ϊ��
    }
    return ActualSpeed; // ���ص��C��ʵ���ٶ�
}

/**
  * @brief  ��ȡ���D��ʵ���ٶȡ�
  * @param  �ޡ�
  * @retval int: ���ص��D��ʵ���ٶ�ֵ��
  */
int MotorD_ActualSpeed(void)
{	
    int ActualSpeed = 0;    
    ActualSpeed = __HAL_TIM_GET_COUNTER(&htim1); // ��ȡ��ʱ��1�ļ�����ֵ
		__HAL_TIM_SetCounter(&htim1 , 0);//��ռ���ֵ
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1) == 0) // ��鶨ʱ��1�Ƿ����ϼ���
    {
        ActualSpeed = ActualSpeed; // ��������ϼ������ٶ�Ϊ��
    }
    else
    {
        ActualSpeed = -ActualSpeed; // ��������¼������ٶ�Ϊ��
    }
    return ActualSpeed; // ���ص��D��ʵ���ٶ�
}



/**
  * @brief ��ȡ����ٶ�
  * @param motor_id: ���ID��0-3�ֱ��Ӧ�ĸ���ʱ����
  * @param ppr: ������ÿת�����������Ǽ��ٱȺ��ֵ������������תһȦ����������
  * @retval ���ת�٣�RPM��
  */
float GetMotorSpeed(uint8_t motor_id) {
    if (motor_id >= MOTOR_NUM) {
        return 0.0f; // ����ĵ��ID
    }

    TIM_HandleTypeDef* htim = NULL;
    switch (motor_id) {
        case 0: htim = &htim5; break;
        case 1: htim = &htim3; break;
        case 2: htim = &htim4; break;
        case 3: htim = &htim1; break;
        default: return 0.0f;
    }

    // ��ȡ��ǰ������ʱ��
    int32_t current_count = __HAL_TIM_GET_COUNTER(htim);
    uint32_t current_time = HAL_GetTick();

    // ����������������������������
    int32_t pulse_diff = current_count - last_count[motor_id];
    // ע�⣺�����������16λ���ҿ��������������Ҫ��������������趨ʱ����16λ��������Χ0-65535��
    // 32λ���������������ϸ��ӣ������ݲ����ǣ���ΪSTM32�Ķ�ʱ��ͨ����16λ
    // ����16λ��ʱ��������������65535�����0ʱ�������¼��������������Ҫ�����������
    // ���������0x8000����32768������˵�����������������������ת�Ҽ�����0����65535��
    // ��������С��-0x8000����˵�����������������������ת�Ҽ�����65535����0��
    // ע�⣺������趨ʱ���ǵ����������ұ�����ģʽ���Զ������򣨼����������ӻ���٣�
    // ���ڱ�����ģʽ�£���ʱ�����Ե�����ݼ����������������ֱ��������ɣ�����Ҫ�����������Ϊ��ʱ����16λ�з�������ʵ����16λ�޷��ţ���ת��Ϊ32λ�����
    // ���ǣ���������ܴ󣨳���16λ��������Χ�������ǿ���ͨ�����·�ʽ������
    // �������� > 32767���� pulse_diff -= 65536;
    // �������� < -32768���� pulse_diff += 65536;
    // ���ǣ����ڱ�����ģʽ�£����ζ�ȡ֮�䲻�����г���32767�����壨��Ϊʱ�����̣ܶ�������ͨ������Ҫ������Ϊ�˰�ȫ�����Լ���
    if (pulse_diff > 32767) {
        pulse_diff -= 65536;
    } else if (pulse_diff < -32768) {
        pulse_diff += 65536;
    }

    // ����ʱ���룩
    float time_diff = (current_time - last_time[motor_id]) / 1000.0f;

    // ������һ�μ�¼
    last_count[motor_id] = current_count;
    last_time[motor_id] = current_time;

    // �������0
    if (time_diff < 0.0001f) {
        return 0.0f;
    }

    // ����ת�� RPM = (�������� / ʱ���) * (60��/����) / (ÿת������ * 4)
    // ����4����Ϊ��������ģʽ�£�ÿ��������4�����أ������غ��½��ض��������������ÿ�����ڵ�����������4
    float rpm = (pulse_diff / time_diff) * 60.0f / (330.0 * 4.0f);

    return rpm;
}
