#include "Motor.h" // �������������ص�ͷ�ļ�
#include "tim.h"   // ������ʱ��������ص�ͷ�ļ�

/**
  * @brief  ���õ��A���ٶȡ�
  * @param  Speed: ���A���ٶ�ֵ��������ʾ��ת��������ʾ��ת��0��ʾֹͣ��
  * @retval �ޡ�
  */
void MotorA_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);   // ���A��ת
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET); // ֹͣ���A��ת
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, -Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET); // ֹͣ���A��ת
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);   // ���A��ת
    }
}

/**
  * @brief  ���õ��B���ٶȡ�
  * @param  Speed: ���B���ٶ�ֵ��������ʾ��ת��������ʾ��ת��0��ʾֹͣ��
  * @retval �ޡ�
  */
void MotorB_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);   // ���B��ת
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET); // ֹͣ���B��ת
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, -Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET); // ֹͣ���B��ת
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);   // ���B��ת
    }
}

/**
  * @brief  ���õ��C���ٶȡ�
  * @param  Speed: ���C���ٶ�ֵ��������ʾ��ת��������ʾ��ת��0��ʾֹͣ��
  * @retval �ޡ�
  */
void MotorC_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_SET);   // ���C��ת
        HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_RESET); // ֹͣ���C��ת
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, -Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(CIN1_GPIO_Port, CIN1_Pin, GPIO_PIN_RESET); // ֹͣ���C��ת
        HAL_GPIO_WritePin(CIN2_GPIO_Port, CIN2_Pin, GPIO_PIN_SET);   // ���C��ת
    }
}

/**
  * @brief  ���õ��D���ٶȡ�
  * @param  Speed: ���D���ٶ�ֵ��������ʾ��ת��������ʾ��ת��0��ʾֹͣ��
  * @retval �ޡ�
  */
void MotorD_Speed(float Speed)
{
    if(Speed >= 0)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_RESET);   // ���D��ת
        HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_SET); // ֹͣ���D��ת
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, -Speed); // ����PWMռ�ձȣ������ٶ�
        HAL_GPIO_WritePin(DIN1_GPIO_Port, DIN1_Pin, GPIO_PIN_SET); // ֹͣ���D��ת
        HAL_GPIO_WritePin(DIN2_GPIO_Port, DIN2_Pin, GPIO_PIN_RESET);   // ���D��ת
    }
}

/**
  * @brief  ��ʼ���ĸ������PWMͨ���������ó�ʼ�ٶ�Ϊ0��
  * @param  �ޡ�
  * @retval �ޡ�
  */
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1); // ����PWMͨ��1
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2); // ����PWMͨ��2
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3); // ����PWMͨ��3
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4); // ����PWMͨ��4
    MotorA_Speed(0); // ��ʼ�����A�ٶ�Ϊ0
    MotorB_Speed(0); // ��ʼ�����B�ٶ�Ϊ0
    MotorC_Speed(0); // ��ʼ�����C�ٶ�Ϊ0
    MotorD_Speed(0); // ��ʼ�����D�ٶ�Ϊ0
}
