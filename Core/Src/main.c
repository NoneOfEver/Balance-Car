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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "MPU6050.h"
#include "oled.h"
#include "stdio.h"
#include "Encoder.h"
#include "delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
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
uint8_t reciveData[50];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(200);
  OLED_Init();

  HAL_UARTEx_ReceiveToIdle_DMA(&huart1,reciveData,sizeof(reciveData));
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);
  
  MyMPU_Init();
  HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //CapturePulseNods();
    if(mpu_dmp_get_data(&Pitch,&Roll,&Yaw)==0)
    { 
      temp=MPU_Get_Temperature();								//得到温度�?
      MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加�?�度传感器数�?
      MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到�?螺仪数据
      sprintf(Pitch_out, "%.2f", Pitch);
      sprintf(Roll_out, "%.2f", Roll);
      sprintf(Yaw_out, "%.2f", Yaw);
      
    }
    OLED_NewFrame();
    OLED_PrintLabeledASCIIString(1, 1, "speed:",speed_out, &afont12x6, OLED_COLOR_NORMAL);  
		OLED_PrintLabeledASCIIString(1,11,"Pitch:",Pitch_out,&afont12x6,OLED_COLOR_NORMAL);
		OLED_PrintLabeledASCIIString(1,21,"Roll:",Roll_out,&afont12x6,OLED_COLOR_NORMAL);
		OLED_PrintLabeledASCIIString(1,31,"Yaw:",Yaw_out,&afont12x6,OLED_COLOR_NORMAL);
    OLED_ShowFrame();


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
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
  if(huart==&huart1)
  {
    HAL_UART_Transmit_DMA(&huart1,reciveData,Size);

    if(reciveData[0]==0xAA)
    {
      if(reciveData[1]==Size)
      {
        uint8_t sum=0;
        for(int i=0;i<Size-1;i++)
        {
          sum+=reciveData[i];
        }
        if(sum==reciveData[Size-1])
        {
          for(int i=2;i<Size-1;i++)
          {
            
            if(reciveData[i]==0x01)//姝ｈ�???
            {
              moveForward();
              controlSpeed(30);
            }
            else if(reciveData[i]==0x02)//宸﹁疆鍙嶈浆
            {
              HAL_GPIO_WritePin(AIN_1_GPIO_Port,AIN_1_Pin,GPIO_PIN_RESET);
              HAL_GPIO_WritePin(AIN_2_GPIO_Port,AIN_2_Pin,GPIO_PIN_SET);
            }
            else if(reciveData[i]==0x03)//鍋滄�???
            {
              HAL_GPIO_WritePin(AIN_1_GPIO_Port,AIN_1_Pin,GPIO_PIN_RESET);
              HAL_GPIO_WritePin(AIN_2_GPIO_Port,AIN_2_Pin,GPIO_PIN_RESET);
            
            }
          }
        }
      }
    }

    HAL_UARTEx_ReceiveToIdle_DMA(&huart1,reciveData,sizeof(reciveData));
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);

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
