#include "bluetooth.h"
#include <string.h>

uint8_t USART2_RX_BUF[USART2_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.
uint16_t USART2_RX_STA=0;//����״̬���//bit15��������ɱ�־��bit14~0�����յ�����Ч�ֽ���Ŀ
uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//�����жϻص�����
{

     if (huart == &huart1) //���Ӵ����ն�
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)rec_tra_data, 1, 0xffff); 
    
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rec_tra_data, 1); 
  }
  
    if(huart ==&huart2)
    {
        if((USART2_RX_STA&0x8000)==0)//����δ���
        {
            if(USART2_NewData==0x5A)//���յ���0x5A
            {
				USART2_RX_STA = 0;
//				memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
            }
            else
            {
                   USART2_RX_BUF[USART2_RX_STA&0X7FFF]=USART2_NewData; //���յ������ݷ������飬
                   USART2_RX_STA++;  //���ݳ��ȼ�����1
                   if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����

            }
        }
        HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //��Ϊÿִ����һ���жϻص������Ὣ�����жϹ��ܹرգ����������Ҫ�ٿ��������ж�


    }
}