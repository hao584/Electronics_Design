#ifndef __KEY_H // ���û�ж���_KEY_H�꣬�����ִ�����´���
#define __KEY_H // ����_KEY_H�꣬��ֹͷ�ļ����ظ�����

#include "main.h"
#include "stdbool.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


struct keys
{
	unsigned char judge_sta;
	bool key_sta;
	bool press;
	unsigned char key_time;
	bool long_press;
};



#endif // __KEY_H
