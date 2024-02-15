/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define RightEncoderA_Pin GPIO_PIN_2
#define RightEncoderA_GPIO_Port GPIOA
#define RightEncoderB_Pin GPIO_PIN_3
#define RightEncoderB_GPIO_Port GPIOA
#define AIN_1_Pin GPIO_PIN_4
#define AIN_1_GPIO_Port GPIOA
#define AIN_2_Pin GPIO_PIN_5
#define AIN_2_GPIO_Port GPIOA
#define BIN_1_Pin GPIO_PIN_6
#define BIN_1_GPIO_Port GPIOA
#define BIN_2_Pin GPIO_PIN_7
#define BIN_2_GPIO_Port GPIOA
#define rightPWM_B_Pin GPIO_PIN_0
#define rightPWM_B_GPIO_Port GPIOB
#define leftPWM_A_Pin GPIO_PIN_1
#define leftPWM_A_GPIO_Port GPIOB
#define MPU_SCL_Pin GPIO_PIN_10
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_SDA_Pin GPIO_PIN_11
#define MPU_SDA_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_12
#define LED_RED_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_13
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_14
#define LED_BLUE_GPIO_Port GPIOB
#define MCU_BT_TX_Pin GPIO_PIN_9
#define MCU_BT_TX_GPIO_Port GPIOA
#define MCU_BT_RX_Pin GPIO_PIN_10
#define MCU_BT_RX_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB
#define LeftEncoderB_Pin GPIO_PIN_8
#define LeftEncoderB_GPIO_Port GPIOB
#define LeftEncoderA_Pin GPIO_PIN_9
#define LeftEncoderA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
