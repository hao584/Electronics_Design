/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MPU6050_SCL_Pin GPIO_PIN_2
#define MPU6050_SCL_GPIO_Port GPIOE
#define MPU6050_SDA_Pin GPIO_PIN_3
#define MPU6050_SDA_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_1
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_3
#define KEY3_GPIO_Port GPIOC
#define IR_X1_Pin GPIO_PIN_4
#define IR_X1_GPIO_Port GPIOA
#define IR_X2_Pin GPIO_PIN_5
#define IR_X2_GPIO_Port GPIOA
#define IR_X3_Pin GPIO_PIN_4
#define IR_X3_GPIO_Port GPIOC
#define IR_X4_Pin GPIO_PIN_5
#define IR_X4_GPIO_Port GPIOC
#define IR_X5_Pin GPIO_PIN_0
#define IR_X5_GPIO_Port GPIOB
#define IR_X6_Pin GPIO_PIN_1
#define IR_X6_GPIO_Port GPIOB
#define IR_X7_Pin GPIO_PIN_7
#define IR_X7_GPIO_Port GPIOE
#define IR_X8_Pin GPIO_PIN_8
#define IR_X8_GPIO_Port GPIOE
#define CIN1_Pin GPIO_PIN_13
#define CIN1_GPIO_Port GPIOB
#define DIN1_Pin GPIO_PIN_14
#define DIN1_GPIO_Port GPIOB
#define DIN2_Pin GPIO_PIN_15
#define DIN2_GPIO_Port GPIOB
#define Right_Red_Pin GPIO_PIN_8
#define Right_Red_GPIO_Port GPIOD
#define Right_Blue_Pin GPIO_PIN_9
#define Right_Blue_GPIO_Port GPIOD
#define Right_Green_Pin GPIO_PIN_11
#define Right_Green_GPIO_Port GPIOD
#define Left_Blue_Pin GPIO_PIN_0
#define Left_Blue_GPIO_Port GPIOD
#define Left_Red_Pin GPIO_PIN_1
#define Left_Red_GPIO_Port GPIOD
#define Left_Green_Pin GPIO_PIN_3
#define Left_Green_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_6
#define AIN2_GPIO_Port GPIOD
#define AIN1_Pin GPIO_PIN_7
#define AIN1_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_4
#define BIN1_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_5
#define BIN2_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_8
#define OLED_SDA_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_9
#define OLED_SCL_GPIO_Port GPIOB
#define CIN2_Pin GPIO_PIN_0
#define CIN2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
