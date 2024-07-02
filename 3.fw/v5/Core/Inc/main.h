/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f7xx_hal.h"

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
#define AD2_Pin GPIO_PIN_0
#define AD2_GPIO_Port GPIOC
#define AD1_Pin GPIO_PIN_1
#define AD1_GPIO_Port GPIOC
#define ADS0_Pin GPIO_PIN_2
#define ADS0_GPIO_Port GPIOC
#define ADS1_Pin GPIO_PIN_3
#define ADS1_GPIO_Port GPIOC
#define AD3_Pin GPIO_PIN_0
#define AD3_GPIO_Port GPIOA
#define AD4_Pin GPIO_PIN_1
#define AD4_GPIO_Port GPIOA
#define AD5_Pin GPIO_PIN_2
#define AD5_GPIO_Port GPIOA
#define AD6_Pin GPIO_PIN_3
#define AD6_GPIO_Port GPIOA
#define DAC_FD_Pin GPIO_PIN_4
#define DAC_FD_GPIO_Port GPIOA
#define DRIVE_Pin GPIO_PIN_5
#define DRIVE_GPIO_Port GPIOA
#define AD7_Pin GPIO_PIN_6
#define AD7_GPIO_Port GPIOA
#define AD8_Pin GPIO_PIN_7
#define AD8_GPIO_Port GPIOA
#define AD9_Pin GPIO_PIN_4
#define AD9_GPIO_Port GPIOC
#define AD10_Pin GPIO_PIN_5
#define AD10_GPIO_Port GPIOC
#define AD11_Pin GPIO_PIN_0
#define AD11_GPIO_Port GPIOB
#define WORK_LED_Pin GPIO_PIN_12
#define WORK_LED_GPIO_Port GPIOB
#define USB_EN_Pin GPIO_PIN_13
#define USB_EN_GPIO_Port GPIOB
#define HC4051_CS7_Pin GPIO_PIN_15
#define HC4051_CS7_GPIO_Port GPIOA
#define HC4051_CS6_Pin GPIO_PIN_10
#define HC4051_CS6_GPIO_Port GPIOC
#define HC4051_CS5_Pin GPIO_PIN_11
#define HC4051_CS5_GPIO_Port GPIOC
#define HC4051_CS4_Pin GPIO_PIN_12
#define HC4051_CS4_GPIO_Port GPIOC
#define OUTS0_Pin GPIO_PIN_3
#define OUTS0_GPIO_Port GPIOB
#define OUTS1_Pin GPIO_PIN_4
#define OUTS1_GPIO_Port GPIOB
#define OUTS2_Pin GPIO_PIN_5
#define OUTS2_GPIO_Port GPIOB
#define HC4051_CS1_Pin GPIO_PIN_6
#define HC4051_CS1_GPIO_Port GPIOB
#define HC4051_CS2_Pin GPIO_PIN_7
#define HC4051_CS2_GPIO_Port GPIOB
#define HC4051_CS3_Pin GPIO_PIN_8
#define HC4051_CS3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
