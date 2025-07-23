#ifndef __KEY_H // 如果没有定义_KEY_H宏，则继续执行以下代码
#define __KEY_H // 定义_KEY_H宏，防止头文件被重复包含

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
