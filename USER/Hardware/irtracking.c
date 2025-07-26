#include "irtracking.h"
#include "stdio.h"  // 用于printf

uint8_t TrackN;
// 读取8路传感器数据 
void Read_Track_DATA(uint8_t* arr) //读取数据
 {
    uint8_t n = 0;//计数器
    uint8_t strackarr[8] = {0};//存储8个传感器的原始数据
    static uint8_t last_track = 0;//存储上一次的赛道数据
    uint8_t current_track = 0;//存储当前赛道数据
    // 读取 8 位数据
    strackarr[0] = HAL_GPIO_ReadPin(IR_X1_GPIO_Port, IR_X1_Pin);
    strackarr[1] = HAL_GPIO_ReadPin(IR_X2_GPIO_Port, IR_X2_Pin);
    strackarr[2] = HAL_GPIO_ReadPin(IR_X3_GPIO_Port, IR_X3_Pin);
    strackarr[3] = HAL_GPIO_ReadPin(IR_X4_GPIO_Port, IR_X4_Pin);
    strackarr[4] = HAL_GPIO_ReadPin(IR_X5_GPIO_Port, IR_X5_Pin);
    strackarr[5] = HAL_GPIO_ReadPin(IR_X6_GPIO_Port, IR_X6_Pin);
    strackarr[6] = HAL_GPIO_ReadPin(IR_X7_GPIO_Port, IR_X7_Pin);
    strackarr[7] = HAL_GPIO_ReadPin(IR_X8_GPIO_Port, IR_X8_Pin);
    // 将 8 位数据转换为整数
    current_track = strackarr[7] + strackarr[6]*2 + strackarr[5]*4 + strackarr[4]*8 +
                    strackarr[3]*16 + strackarr[2]*32 + strackarr[1]*64 + strackarr[0]*128;
    // 简单均值滤波
    TrackN = (uint8_t)((current_track + last_track) / 2); //将当前赛道数据与上一次赛道数据求均值
    last_track = current_track;//更新上一次赛道数据
    *arr = TrackN;//将赛道数据存储到传入的数组中
}

float Track_Err() 
	{
    float Err;
    switch (TrackN) 
			{
        case 0xe7: Err = 0; break;      // 正中间
        case 0xcf: Err = 3.5; break;    // 右侧小偏差 - 减小值使转向更平缓
        case 0x9f: Err = 5.0; break;    // 右侧中等偏差
        case 0x3f: Err = 6.0; break;    // 右侧大偏差 - 增大值使转向更果断
        case 0xf3: Err = -3.5; break;   // 左侧小偏差 - 减小值使转向更平缓
        case 0xf9: Err = -5.0; break;   // 左侧中等偏差
        case 0xfc: Err = -6.0; break;   // 左侧大偏差 - 增大值使转向更果断
        case 0xef: Err = 2.0; break;    // 右侧轻微偏差
        case 0xdf: Err = 3.0; break;    // 右侧中小偏差
        case 0xbf: Err = 3.5; break;    // 右侧中小偏差
        case 0x7f: Err = 7.0; break;    // 右侧极大偏差 - 大幅增大值
        case 0xf7: Err = -2.0; break;   // 左侧轻微偏差
        case 0xfb: Err = -3.0; break;   // 左侧中小偏差
        case 0xfd: Err = -4.5; break;   // 左侧中偏差
        case 0xfe: Err = -7.0; break;   // 左侧极大偏差 - 大幅增大值
        case 0x1f: Err = 8.0; break;    // 右侧极限偏差 - 特别大的值
        case 0xf8: Err = -3.0; break;   // 左侧中小偏差
        case 0x8f: Err = 9.0; break;    // 右侧极限偏差 - 特别大的值
        default: Err = 0; break;        // 未定义情况
    }
    
//    // 状态修正逻辑保持不变
//    if (car_state == 0x1012 || car_state == 0x1013) 
//			{
//        if (Err <= 0) Err = 0;  // 仅允许正误差（右转弯）
//    } else if (car_state == 0x1022 || car_state == 0x1023) 
//			{
//        if (Err >= 0) Err = 0;  // 仅允许负误差（左转弯）
//    }
    
    return Err;
}

// 打印传感器数据
// void printf_IR_IO_Data(void) {
//     static uint8_t x1, x2, x3, x4, x5, x6, x7, x8;
//     track_deal_four(&x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
//     printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", x1, x2, x3, x4, x5, x6, x7, x8);
// }
