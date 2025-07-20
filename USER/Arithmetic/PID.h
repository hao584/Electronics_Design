#ifndef __PID_H
#define __PID_H
#include "stm32f1xx_hal.h"

typedef struct // PID�������ݽṹ��
{
  float p, i, d;                        // ���������֣�΢��
  float set, err, err_last;             // ����ֵ�����ֵ���ϴε����ֵ
  float diff;                           // ���΢��
  float p_out, i_out, d_out, total_out; // ���������֣�΢�ֵ�����������
  float lim_i_out, lim_out;             // ����������ƣ����������
} pid_t;

void pid_set(pid_t *PidSet, float p_set, float i_set, float d_set, float lim_out_set, float lim_i_outset); // PID����
float pid_cal(pid_t *PidGoal, float Now, float Set);                                                       // PID����
float myabs(float a);     //����ֵ����
#endif
