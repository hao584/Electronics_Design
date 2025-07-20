#ifndef __BSP_OLED_H
#define __BSP_OLED_H 

#include "stm32f1xx_hal.h"             // HAL库的寄存器定义 
#include "main.h"














/*****************************************************************************
 ** 声明全局函数
****************************************************************************/
void OLED_Init(void);                                                   // 初始化
void OLED_Refresh(void);                                                // 更新显存到OLED
void OLED_DisplayTurn(uint8_t i);                                       // 显示方向水平反转
void OLED_Display(uint8_t sw);                                          // 显示电源开关
void OLED_Clear(void);                                                  // 清屏
void OLED_Line(uint16_t  x1, uint16_t  y1, uint16_t  x2, uint16_t  y2); // 画线
void OLED_Circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);        // 画圆
void OLED_String(uint16_t x, uint16_t y, char *pFont, uint8_t size);    // 显示中英文字符号
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);   // 显示汉字(字模数据在font.h)

#endif

