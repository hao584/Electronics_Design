#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f1xx.h"

#define SERVO_TIM &htim2
#define SERVO_CHANNEL1 TIM_CHANNEL_1
#define SERVO_CHANNEL2 TIM_CHANNEL_2

void servo_set_angle(float angle1,float angle2);

#endif