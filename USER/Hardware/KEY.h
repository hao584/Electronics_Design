#ifndef __KEY_H // 如果没有定义_KEY_H宏，则继续执行以下代码
#define __KEY_H // 定义_KEY_H宏，防止头文件被重复包含

#include "main.h" // 包含主头文件，其中包含了MCU系列和HAL库的配置

#define SIZE_OF_WAIT 5 // 消抖数组大小，要大于上面那些数

#define KEY_1 0
#define KEY_2 1
#define KEY_3 2

#define IF_KEY_PRESSED_1  (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
#define IF_KEY_PRESSED_2  (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
#define IF_KEY_PRESSED_3  (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)

// 声明全局变量，这些变量在其他文件中定义（可能是main.c）

extern int Key1_Num; // 声明一个全局变量Key1_Num，用于记录按键1被按下的次数
extern int Key2_Num; // 声明一个全局变量Key2_Num，用于记录按键2被按下的次数
extern int Key3_Num; // 声明一个全局变量Key3_Num，用于记录按键3被按下的次数

// 声明Get_KeyNum函数，该函数用于获取按键编号
void Get_KeyNum(void); // 声明Get_KeyNum函数，用于检测按键按下并更新全局变量计数
void Key_Init ();

#endif // __KEY_H
