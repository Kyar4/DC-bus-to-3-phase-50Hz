/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BUILDIN_Pin GPIO_PIN_13
#define LED_BUILDIN_GPIO_Port GPIOC
#define PWM_U_L_Pin GPIO_PIN_13
#define PWM_U_L_GPIO_Port GPIOB
#define PWM_V_L_Pin GPIO_PIN_14
#define PWM_V_L_GPIO_Port GPIOB
#define PWM_W_L_Pin GPIO_PIN_15
#define PWM_W_L_GPIO_Port GPIOB
#define PWM_U_H_Pin GPIO_PIN_8
#define PWM_U_H_GPIO_Port GPIOA
#define PWM_V_H_Pin GPIO_PIN_9
#define PWM_V_H_GPIO_Port GPIOA
#define PWM_W_H_Pin GPIO_PIN_10
#define PWM_W_H_GPIO_Port GPIOA
#define SD_Signal_Pin GPIO_PIN_11
#define SD_Signal_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
