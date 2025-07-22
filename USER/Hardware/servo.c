#include "servo.h"
#include "tim.h"

//用得调用
void servo_set_angle(float angle1,float angle2)
{
    /*
		t = 0.5ms——————-舵机会转到 0 °
		t = 1.0ms——————-舵机会转到 45°
		t = 1.5ms——————-舵机会转到 90°
		t = 2.0ms——————-舵机会转到 135°
		t = 2.5ms——————-舵机会转到 180°

	*/
    int pulse_width1 = angle1 * 2000 / 180 + 500;
    int compare_value1 = pulse_width1 * 2000 / 20000;
	int pulse_width2 = angle2 * 2000 / 180 + 500;
    int compare_value2 = pulse_width2 * 2000 / 20000;

    __HAL_TIM_SET_COMPARE(SERVO_TIM,SERVO_CHANNEL1,compare_value1);
	__HAL_TIM_SET_COMPARE(SERVO_TIM,SERVO_CHANNEL2,compare_value2);
	
}