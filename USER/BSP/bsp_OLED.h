#ifndef __BSP_OLED_H
#define __BSP_OLED_H 

#include "stm32f1xx_hal.h"             // HAL��ļĴ������� 
#include "main.h"














/*****************************************************************************
 ** ����ȫ�ֺ���
****************************************************************************/
void OLED_Init(void);                                                   // ��ʼ��
void OLED_Refresh(void);                                                // �����Դ浽OLED
void OLED_DisplayTurn(uint8_t i);                                       // ��ʾ����ˮƽ��ת
void OLED_Display(uint8_t sw);                                          // ��ʾ��Դ����
void OLED_Clear(void);                                                  // ����
void OLED_Line(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2); // ����
void OLED_Circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);        // ��Բ
void OLED_String(uint16_t x, uint16_t y, char *pFont, uint8_t size);    // ��ʾ��Ӣ���ַ���
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);   // ��ʾ����(��ģ������font.h)

#endif

