#ifndef __ENCODER_H // ���__MOTOR_H���Ƿ�δ���壬�Է�ֹͷ�ļ����ظ�����
#define __ENCODER_H // ����__MOTOR_H��

#include "main.h" // ������ͷ�ļ������а�����MCUϵ�к�HAL�������

void Encoder_Init(void);
int MotorB_ActualSpeed(void);
int MotorC_ActualSpeed(void);
float GetMotorSpeed(uint8_t motor_id);


#endif // __MOTOR_H
