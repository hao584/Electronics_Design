#include "KEY.h" // 包含按键相关的头文件，其中定义了与按键相关的宏和函数原型


 
// 定义全局变量，用于记录每个按键被按下的次数
int Key1_Num ; // 记录按键1被按下的次数
int Key2_Num ; // 记录按键2被按下的次数
int Key3_Num ; // 记录按键3被按下的次数
int16_t wait_time[SIZE_OF_WAIT] = {0}; // 按键消抖用时间

//按键初始化
void Key_Init ()
{
	Key1_Num = 0;
	Key2_Num = 0;
	Key3_Num = 0;

}

//按键消抖
uint8_t Wait(uint8_t key)
{
    if (wait_time[key] >= 2)
    {
        wait_time[key]--;
        return 0;
    }
    else if ((wait_time[key] == 0) || (wait_time[key] == 1))
    {
        wait_time[key]--;
        return 1;
    }
    else
    {
        return 0;
    }
}

void SetWait(uint8_t key)
{
    wait_time[key] = 200;
}


// 定义一个函数，用于获取按键编号
void Get_KeyNum(void) 
{
    // 检测按键1是否被按下
    if (IF_KEY_PRESSED_1 || Wait(KEY_1)) // 读取与按键1相关联的GPIO引脚状态
    {
        if (Wait(KEY_1)) // 消抖结束触发
        {
					Key1_Num++; // 按键被按下并释放后，增加按键1的计数
        }
        
        if (IF_KEY_PRESSED_1)
            SetWait(KEY_1);
    }

    // 检测按键2是否被按下
     if (IF_KEY_PRESSED_2 || Wait(KEY_2)) // 读取与按键1相关联的GPIO引脚状态
    {
        if (Wait(KEY_2)) // 消抖结束触发
        {
					Key2_Num++; // 按键被按下并释放后，增加按键1的计数
        }
        
        if (IF_KEY_PRESSED_2)
            SetWait(KEY_2);
    }

    // 检测按键3是否被按下
     if (IF_KEY_PRESSED_3 || Wait(KEY_3)) // 读取与按键1相关联的GPIO引脚状态
    {
        if (Wait(KEY_3)) // 消抖结束触发
        {
					Key3_Num++; // 按键被按下并释放后，增加按键1的计数
        }
        
        if (IF_KEY_PRESSED_3)
            SetWait(KEY_3);
    }
}
