#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "main.h" //HAL���ļ�����

extern UART_HandleTypeDef huart2;//����USART2��HAL��ṹ��
extern UART_HandleTypeDef huart1;

#define USART2_REC_LEN  200//����USART2�������ֽ���

extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�ΪУ���
extern uint8_t rec_tra_data[1];
extern uint16_t USART2_RX_STA;//����״̬���
extern uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���


void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart);//�����жϻص���������

#endif 
