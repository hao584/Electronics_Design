#ifndef __PID_H
#define __PID_H
#include "stm32f1xx_hal.h"

typedef struct // PID控制数据结构体
{
  float p, i, d;                        // 比例，积分，微分
  float set, err, err_last;             // 设置值，误差值，上次的误差值
  float diff;                           // 误差微分
  float p_out, i_out, d_out, total_out; // 比例，积分，微分的输出和总输出
  float lim_i_out, lim_out;             // 输出积分限制，总输出限制
} pid_t;

void pid_set(pid_t *PidSet, float p_set, float i_set, float d_set, float lim_out_set, float lim_i_outset); // PID设置
float pid_cal(pid_t *PidGoal, float Now, float Set);                                                       // PID计算
float myabs(float a);     //绝对值函数
#endif
