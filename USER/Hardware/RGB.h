#ifndef __RGB_H // 如果没有定义__RGB_H，则继续执行以下代码
#define __RGB_H // 定义__RGB_H，防止头文件被重复包含


// 定义控制左侧红色LED灯的宏
#define Left_Red_On  						HAL_GPIO_WritePin(Left_Red_GPIO_Port,Left_Red_Pin,GPIO_PIN_RESET); // 打开左侧红色LED灯
#define Left_Red_Off  					HAL_GPIO_WritePin(Left_Red_GPIO_Port,Left_Red_Pin,GPIO_PIN_SET); // 关闭左侧红色LED灯

// 定义控制左侧绿色LED灯的宏
#define Left_Green_On  					HAL_GPIO_WritePin(Left_Green_GPIO_Port,Left_Green_Pin,GPIO_PIN_RESET); // 打开左侧绿色LED灯
#define Left_Green_Off  				HAL_GPIO_WritePin(Left_Green_GPIO_Port,Left_Green_Pin,GPIO_PIN_SET); // 关闭左侧绿色LED灯

// 定义控制左侧蓝色LED灯的宏
#define Left_Blue_On  					HAL_GPIO_WritePin(Left_Blue_GPIO_Port,Left_Blue_Pin,GPIO_PIN_RESET); // 打开左侧蓝色LED灯
#define Left_Blue_Off  					HAL_GPIO_WritePin(Left_Blue_GPIO_Port,Left_Blue_Pin,GPIO_PIN_SET); // 关闭左侧蓝色LED灯


// 定义控制右侧红色LED灯的宏
#define Right_Red_On  						HAL_GPIO_WritePin(Right_Red_GPIO_Port,Right_Red_Pin,GPIO_PIN_RESET); // 打开右侧红色LED灯
#define Right_Red_Off  						HAL_GPIO_WritePin(Right_Red_GPIO_Port,Right_Red_Pin,GPIO_PIN_SET); // 关闭右侧红色LED灯

// 定义控制右侧绿色LED灯的宏
#define Right_Green_On  					HAL_GPIO_WritePin(Right_Green_GPIO_Port,Right_Green_Pin,GPIO_PIN_RESET); // 打开右侧绿色LED灯
#define Right_Green_Off  					HAL_GPIO_WritePin(Right_Green_GPIO_Port,Right_Green_Pin,GPIO_PIN_SET); // 关闭右侧绿色LED灯

// 定义控制右侧蓝色LED灯的宏
#define Right_Blue_On  						HAL_GPIO_WritePin(Right_Blue_GPIO_Port,Right_Blue_Pin,GPIO_PIN_RESET); // 打开右侧蓝色LED灯
#define Right_Blue_Off  					HAL_GPIO_WritePin(Right_Blue_GPIO_Port,Right_Blue_Pin,GPIO_PIN_SET); // 关闭右侧蓝色LED灯

#endif // 结束__RGB_H的定义
