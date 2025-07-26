#include "irtracking.h"
#include "stdio.h"  // ����printf

uint8_t TrackN;
// ��ȡ8·���������� 
void Read_Track_DATA(uint8_t* arr) //��ȡ����
 {
    uint8_t n = 0;//������
    uint8_t strackarr[8] = {0};//�洢8����������ԭʼ����
    static uint8_t last_track = 0;//�洢��һ�ε���������
    uint8_t current_track = 0;//�洢��ǰ��������
    // ��ȡ 8 λ����
    strackarr[0] = HAL_GPIO_ReadPin(IR_X1_GPIO_Port, IR_X1_Pin);
    strackarr[1] = HAL_GPIO_ReadPin(IR_X2_GPIO_Port, IR_X2_Pin);
    strackarr[2] = HAL_GPIO_ReadPin(IR_X3_GPIO_Port, IR_X3_Pin);
    strackarr[3] = HAL_GPIO_ReadPin(IR_X4_GPIO_Port, IR_X4_Pin);
    strackarr[4] = HAL_GPIO_ReadPin(IR_X5_GPIO_Port, IR_X5_Pin);
    strackarr[5] = HAL_GPIO_ReadPin(IR_X6_GPIO_Port, IR_X6_Pin);
    strackarr[6] = HAL_GPIO_ReadPin(IR_X7_GPIO_Port, IR_X7_Pin);
    strackarr[7] = HAL_GPIO_ReadPin(IR_X8_GPIO_Port, IR_X8_Pin);
    // �� 8 λ����ת��Ϊ����
    current_track = strackarr[7] + strackarr[6]*2 + strackarr[5]*4 + strackarr[4]*8 +
                    strackarr[3]*16 + strackarr[2]*32 + strackarr[1]*64 + strackarr[0]*128;
    // �򵥾�ֵ�˲�
    TrackN = (uint8_t)((current_track + last_track) / 2); //����ǰ������������һ�������������ֵ
    last_track = current_track;//������һ����������
    *arr = TrackN;//���������ݴ洢�������������
}

float Track_Err() 
	{
    float Err;
    switch (TrackN) 
			{
        case 0xe7: Err = 0; break;      // ���м�
        case 0xcf: Err = 3.5; break;    // �Ҳ�Сƫ�� - ��Сֵʹת���ƽ��
        case 0x9f: Err = 5.0; break;    // �Ҳ��е�ƫ��
        case 0x3f: Err = 6.0; break;    // �Ҳ��ƫ�� - ����ֵʹת�������
        case 0xf3: Err = -3.5; break;   // ���Сƫ�� - ��Сֵʹת���ƽ��
        case 0xf9: Err = -5.0; break;   // ����е�ƫ��
        case 0xfc: Err = -6.0; break;   // ����ƫ�� - ����ֵʹת�������
        case 0xef: Err = 2.0; break;    // �Ҳ���΢ƫ��
        case 0xdf: Err = 3.0; break;    // �Ҳ���Сƫ��
        case 0xbf: Err = 3.5; break;    // �Ҳ���Сƫ��
        case 0x7f: Err = 7.0; break;    // �Ҳ༫��ƫ�� - �������ֵ
        case 0xf7: Err = -2.0; break;   // �����΢ƫ��
        case 0xfb: Err = -3.0; break;   // �����Сƫ��
        case 0xfd: Err = -4.5; break;   // �����ƫ��
        case 0xfe: Err = -7.0; break;   // ��༫��ƫ�� - �������ֵ
        case 0x1f: Err = 8.0; break;    // �Ҳ༫��ƫ�� - �ر���ֵ
        case 0xf8: Err = -3.0; break;   // �����Сƫ��
        case 0x8f: Err = 9.0; break;    // �Ҳ༫��ƫ�� - �ر���ֵ
        default: Err = 0; break;        // δ�������
    }
    
//    // ״̬�����߼����ֲ���
//    if (car_state == 0x1012 || car_state == 0x1013) 
//			{
//        if (Err <= 0) Err = 0;  // ������������ת�䣩
//    } else if (car_state == 0x1022 || car_state == 0x1023) 
//			{
//        if (Err >= 0) Err = 0;  // ����������ת�䣩
//    }
    
    return Err;
}

// ��ӡ����������
// void printf_IR_IO_Data(void) {
//     static uint8_t x1, x2, x3, x4, x5, x6, x7, x8;
//     track_deal_four(&x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
//     printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", x1, x2, x3, x4, x5, x6, x7, x8);
// }
