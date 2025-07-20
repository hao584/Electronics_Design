/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h"
#include "RGB.h"
#include "KEY.h"
#include "bsp_OLED.h"
#include "Motor.h" 
#include "Encoder.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int   Actual_Speed=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t rec_tra_data[1]; // 锟斤拷锟斤拷一锟斤拷锟斤拷锟介，锟斤拷锟节达拷沤锟斤拷蘸头锟斤拷偷锟斤拷锟斤拷锟?
uint8_t Bluetooth_rec_tra_data[1]; // 锟斤拷锟斤拷一锟斤拷锟斤拷锟介，锟斤拷锟节达拷沤锟斤拷蘸头锟斤拷偷锟斤拷锟斤拷锟?
char Temp_chr[100];
pid_t moterB_pid ;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM8_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	Motor_Init();
  Key_Init (); 
	
	
  HAL_UART_Transmit(&huart1, "Hello World", sizeof("Hello World")-1, 0XFFFF); 
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&rec_tra_data, 1);
	
  HAL_UART_Transmit(&huart2, "Hello Bluetooth", sizeof("Hello Bluetooth")-1, 0XFFFF);
  HAL_UART_Receive_IT(&huart2, (uint8_t *)&Bluetooth_rec_tra_data, 1); 
	
  Encoder_Init();	
	pid_set(&moterB_pid, 0.68, 0.2, 0.0, 100, 10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		MotorB_Speed(pid_cal(&moterB_pid,GetMotorSpeed(1),0));
    sprintf(Temp_chr,"A:%f",GetMotorSpeed(1));
		OLED_String(1,16,Temp_chr,16);	 
	  HAL_Delay(20);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  // 锟斤拷榇拷锟斤拷UART锟斤拷锟斤拷欠锟轿猦uart1锟斤拷锟斤拷锟角凤拷锟斤拷USART1锟斤拷锟叫讹拷
  if (huart == &huart1) 
  {
    // 锟斤拷锟斤拷锟経SART1锟斤拷锟叫断ｏ拷锟津将斤拷锟秸碉拷锟斤拷锟斤拷锟捷凤拷锟酵伙拷去
    // 锟斤拷锟斤拷锟斤拷锟絩ec_tra_data锟斤拷一锟斤拷全锟街憋拷锟斤拷锟斤拷锟斤拷锟节存储锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷
    HAL_UART_Transmit(&huart1, (uint8_t *)rec_tra_data, 1, 0xffff); 
    
    // 锟劫次匡拷锟斤拷锟斤拷锟节斤拷锟斤拷锟叫断ｏ拷准锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟街斤拷
    // 锟斤拷锟斤拷锟斤拷锟矫筹拷时时锟斤拷为0xffff锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷没锟叫斤拷锟秸碉拷锟斤拷锟捷ｏ拷锟斤拷锟叫断诧拷锟结触锟斤拷
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rec_tra_data, 1); 
  }
	
	
  // 锟斤拷榇拷锟斤拷UART锟斤拷锟斤拷欠锟轿猦uart2锟斤拷锟斤拷锟角凤拷锟斤拷USART2锟斤拷锟叫讹拷
  if (huart == &huart2) 
  {
    // 锟斤拷锟斤拷锟経SART2锟斤拷锟叫断ｏ拷锟津将斤拷锟秸碉拷锟斤拷锟斤拷锟捷凤拷锟酵伙拷去
    // 锟斤拷锟斤拷锟斤拷锟紹luetooth_rec_tra_data锟斤拷一锟斤拷全锟街憋拷锟斤拷锟斤拷锟斤拷锟节存储锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷
    HAL_UART_Transmit(&huart2, (uint8_t *)Bluetooth_rec_tra_data, 1, 0xffff); 
    
    // 锟劫次匡拷锟斤拷锟斤拷锟节斤拷锟斤拷锟叫断ｏ拷准锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟街斤拷
    // 锟斤拷锟斤拷锟斤拷锟矫筹拷时时锟斤拷为0xffff锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷没锟叫斤拷锟秸碉拷锟斤拷锟捷ｏ拷锟斤拷锟叫断诧拷锟结触锟斤拷
    HAL_UART_Receive_IT(&huart2, (uint8_t *)&Bluetooth_rec_tra_data, 1); 
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
