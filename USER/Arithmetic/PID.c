// 文件创建时间：2024/12/1
// 作者：李工
// 公司：荣洋电子
// 淘宝店铺名：荣洋电子RYDZ
// 用途说明：该程序用于STM32F10x系列微控制器，实现编码电机的PID控制。

#include "pid.h"

//pid参数设置函数
void pid_set(pid_t *PidSet,float p_set,float i_set,float d_set,float lim_out_set,float lim_i_outset)//PID设置
{
  PidSet->p = p_set;   PidSet->i = i_set;   PidSet->d = d_set;

  PidSet->lim_out = lim_out_set;   PidSet->lim_i_out = lim_i_outset;//将设置赋值
}

// 简单绝对值函数
// 功能：计算a的绝对值
// 参数：float a - 输入的整数
// 返回值：float - 输入值的绝对值
float myabs(float a)
{       
    float temp;
    if(a < 0)  temp = -a;  
    else temp = a;
    return temp;
}


// PID控制函数
// 功能：根据编码电机的速度和目标速度，计算PWM输出值以控制电机速度

float pid_cal(pid_t *PidGoal,float Now,float Set)
{ PidGoal->set = Set;
  PidGoal->err_last = PidGoal->err;
  PidGoal->err = Set - Now;//计算误差
  PidGoal->diff=PidGoal->err-PidGoal->err_last;
   
  PidGoal->p_out = PidGoal->p * PidGoal->err;
	if(PidGoal->i != 0)
		PidGoal->i_out += PidGoal->i * PidGoal->err;
  PidGoal->d_out = PidGoal->d *PidGoal->diff ;//pid运算
  
  
  if(myabs(PidGoal->i_out) > PidGoal->lim_i_out)//防止积分过大
  {
    if(PidGoal->i_out < 0)
      PidGoal->i_out = -PidGoal->lim_i_out;
    else
      PidGoal->i_out = PidGoal->lim_i_out;
  }
	
  PidGoal->total_out = PidGoal->p_out + PidGoal->i_out + PidGoal->d_out;//计算总和输出  

	if(myabs(PidGoal->total_out) > PidGoal->lim_out)//防止总和过大
  {
    if(PidGoal->total_out < 0)
      PidGoal->total_out = -PidGoal->lim_out;
    else
      PidGoal->total_out = PidGoal->lim_out;
  }
	
  return PidGoal->total_out;

}
