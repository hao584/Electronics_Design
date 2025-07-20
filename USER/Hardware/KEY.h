#ifndef __KEY_H // ���û�ж���_KEY_H�꣬�����ִ�����´���
#define __KEY_H // ����_KEY_H�꣬��ֹͷ�ļ����ظ�����

#include "main.h" // ������ͷ�ļ������а�����MCUϵ�к�HAL�������

#define SIZE_OF_WAIT 5 // ���������С��Ҫ����������Щ��

#define KEY_1 0
#define KEY_2 1
#define KEY_3 2

#define IF_KEY_PRESSED_1  (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
#define IF_KEY_PRESSED_2  (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
#define IF_KEY_PRESSED_3  (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)

// ����ȫ�ֱ�������Щ�����������ļ��ж��壨������main.c��

extern int Key1_Num; // ����һ��ȫ�ֱ���Key1_Num�����ڼ�¼����1�����µĴ���
extern int Key2_Num; // ����һ��ȫ�ֱ���Key2_Num�����ڼ�¼����2�����µĴ���
extern int Key3_Num; // ����һ��ȫ�ֱ���Key3_Num�����ڼ�¼����3�����µĴ���

// ����Get_KeyNum�������ú������ڻ�ȡ�������
void Get_KeyNum(void); // ����Get_KeyNum���������ڼ�ⰴ�����²�����ȫ�ֱ�������
void Key_Init ();

#endif // __KEY_H
