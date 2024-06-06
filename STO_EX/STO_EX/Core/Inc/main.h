/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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
#define SD_DETECT_Pin GPIO_PIN_4
#define SD_DETECT_GPIO_Port GPIOC
#define CHOICE_SW_Pin GPIO_PIN_0
#define CHOICE_SW_GPIO_Port GPIOB
#define CHOICE_SW_EXTI_IRQn EXTI0_IRQn
#define CHOICE_LED_Pin GPIO_PIN_1
#define CHOICE_LED_GPIO_Port GPIOB
#define SWITCH_SW_Pin GPIO_PIN_2
#define SWITCH_SW_GPIO_Port GPIOB
#define SWITCH_SW_EXTI_IRQn EXTI2_IRQn
#define SWITCH_LED_Pin GPIO_PIN_10
#define SWITCH_LED_GPIO_Port GPIOB
#define ALARM_Pin GPIO_PIN_12
#define ALARM_GPIO_Port GPIOB
#define LED_SERWIS_Pin GPIO_PIN_13
#define LED_SERWIS_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_8
#define LED_RED_GPIO_Port GPIOC
#define GAS1_OK_Pin GPIO_PIN_10
#define GAS1_OK_GPIO_Port GPIOC
#define GAS1_Pin GPIO_PIN_11
#define GAS1_GPIO_Port GPIOC
#define GAS2_OK_Pin GPIO_PIN_12
#define GAS2_OK_GPIO_Port GPIOC
#define GAS2_Pin GPIO_PIN_2
#define GAS2_GPIO_Port GPIOD
#define GAS3_OK_Pin GPIO_PIN_3
#define GAS3_OK_GPIO_Port GPIOB
#define GAS3_Pin GPIO_PIN_4
#define GAS3_GPIO_Port GPIOB
#define GAS4_OK_Pin GPIO_PIN_5
#define GAS4_OK_GPIO_Port GPIOB
#define GAS4_Pin GPIO_PIN_6
#define GAS4_GPIO_Port GPIOB
#define SERWIS_IN_Pin GPIO_PIN_7
#define SERWIS_IN_GPIO_Port GPIOB
#define LOW_BAT_Pin GPIO_PIN_9
#define LOW_BAT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
