#ifndef __RGB_H // ���û�ж���__RGB_H�������ִ�����´���
#define __RGB_H // ����__RGB_H����ֹͷ�ļ����ظ�����


// �����������ɫLED�Ƶĺ�
#define Left_Red_On  						HAL_GPIO_WritePin(Left_Red_GPIO_Port,Left_Red_Pin,GPIO_PIN_RESET); // ������ɫLED��
#define Left_Red_Off  					HAL_GPIO_WritePin(Left_Red_GPIO_Port,Left_Red_Pin,GPIO_PIN_SET); // �ر�����ɫLED��

// ������������ɫLED�Ƶĺ�
#define Left_Green_On  					HAL_GPIO_WritePin(Left_Green_GPIO_Port,Left_Green_Pin,GPIO_PIN_RESET); // �������ɫLED��
#define Left_Green_Off  				HAL_GPIO_WritePin(Left_Green_GPIO_Port,Left_Green_Pin,GPIO_PIN_SET); // �ر������ɫLED��

// ������������ɫLED�Ƶĺ�
#define Left_Blue_On  					HAL_GPIO_WritePin(Left_Blue_GPIO_Port,Left_Blue_Pin,GPIO_PIN_RESET); // �������ɫLED��
#define Left_Blue_Off  					HAL_GPIO_WritePin(Left_Blue_GPIO_Port,Left_Blue_Pin,GPIO_PIN_SET); // �ر������ɫLED��


// ��������Ҳ��ɫLED�Ƶĺ�
#define Right_Red_On  						HAL_GPIO_WritePin(Right_Red_GPIO_Port,Right_Red_Pin,GPIO_PIN_RESET); // ���Ҳ��ɫLED��
#define Right_Red_Off  						HAL_GPIO_WritePin(Right_Red_GPIO_Port,Right_Red_Pin,GPIO_PIN_SET); // �ر��Ҳ��ɫLED��

// ��������Ҳ���ɫLED�Ƶĺ�
#define Right_Green_On  					HAL_GPIO_WritePin(Right_Green_GPIO_Port,Right_Green_Pin,GPIO_PIN_RESET); // ���Ҳ���ɫLED��
#define Right_Green_Off  					HAL_GPIO_WritePin(Right_Green_GPIO_Port,Right_Green_Pin,GPIO_PIN_SET); // �ر��Ҳ���ɫLED��

// ��������Ҳ���ɫLED�Ƶĺ�
#define Right_Blue_On  						HAL_GPIO_WritePin(Right_Blue_GPIO_Port,Right_Blue_Pin,GPIO_PIN_RESET); // ���Ҳ���ɫLED��
#define Right_Blue_Off  					HAL_GPIO_WritePin(Right_Blue_GPIO_Port,Right_Blue_Pin,GPIO_PIN_SET); // �ر��Ҳ���ɫLED��

#endif // ����__RGB_H�Ķ���
