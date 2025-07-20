// �ļ�����ʱ�䣺2024/12/1
// ���ߣ��
// ��˾���������
// �Ա����������������RYDZ
// ��;˵�����ó�������STM32F10xϵ��΢��������ʵ�ֱ�������PID���ơ�

#include "pid.h"

//pid�������ú���
void pid_set(pid_t *PidSet,float p_set,float i_set,float d_set,float lim_out_set,float lim_i_outset)//PID����
{
  PidSet->p = p_set;   PidSet->i = i_set;   PidSet->d = d_set;

  PidSet->lim_out = lim_out_set;   PidSet->lim_i_out = lim_i_outset;//�����ø�ֵ
}

// �򵥾���ֵ����
// ���ܣ�����a�ľ���ֵ
// ������float a - ���������
// ����ֵ��float - ����ֵ�ľ���ֵ
float myabs(float a)
{       
    float temp;
    if(a < 0)  temp = -a;  
    else temp = a;
    return temp;
}


// PID���ƺ���
// ���ܣ����ݱ��������ٶȺ�Ŀ���ٶȣ�����PWM���ֵ�Կ��Ƶ���ٶ�

float pid_cal(pid_t *PidGoal,float Now,float Set)
{ PidGoal->set = Set;
  PidGoal->err_last = PidGoal->err;
  PidGoal->err = Set - Now;//�������
  PidGoal->diff=PidGoal->err-PidGoal->err_last;
   
  PidGoal->p_out = PidGoal->p * PidGoal->err;
	if(PidGoal->i != 0)
		PidGoal->i_out += PidGoal->i * PidGoal->err;
  PidGoal->d_out = PidGoal->d *PidGoal->diff ;//pid����
  
  
  if(myabs(PidGoal->i_out) > PidGoal->lim_i_out)//��ֹ���ֹ���
  {
    if(PidGoal->i_out < 0)
      PidGoal->i_out = -PidGoal->lim_i_out;
    else
      PidGoal->i_out = PidGoal->lim_i_out;
  }
	
  PidGoal->total_out = PidGoal->p_out + PidGoal->i_out + PidGoal->d_out;//�����ܺ����  

	if(myabs(PidGoal->total_out) > PidGoal->lim_out)//��ֹ�ܺ͹���
  {
    if(PidGoal->total_out < 0)
      PidGoal->total_out = -PidGoal->lim_out;
    else
      PidGoal->total_out = PidGoal->lim_out;
  }
	
  return PidGoal->total_out;

}
