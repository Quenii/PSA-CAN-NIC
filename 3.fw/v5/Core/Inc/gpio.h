/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
//---------------------------------------------------------------------------
//LED定义区域
#define LED_WORK_ON()    	WORK_LED_GPIO_Port->ODR |= WORK_LED_Pin
#define LED_WORK_OFF()  	WORK_LED_GPIO_Port->ODR &= ~WORK_LED_Pin

#define USB_EN_ON()     	USB_EN_GPIO_Port->ODR |= USB_EN_Pin 
#define USB_EN_OFF()  		USB_EN_GPIO_Port->ODR &= ~USB_EN_Pin 

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//OUTPUT定义区域
#define OUTPUT_HC4051_CS1_H()     	HC4051_CS1_GPIO_Port->ODR |= HC4051_CS1_Pin 
#define OUTPUT_HC4051_CS1_L()  		HC4051_CS1_GPIO_Port->ODR &= ~HC4051_CS1_Pin 
#define OUTPUT_HC4051_CS2_H()     	HC4051_CS2_GPIO_Port->ODR |= HC4051_CS2_Pin 
#define OUTPUT_HC4051_CS2_L()  		HC4051_CS2_GPIO_Port->ODR &= ~HC4051_CS2_Pin 
#define OUTPUT_HC4051_CS3_H()     	HC4051_CS3_GPIO_Port->ODR |= HC4051_CS3_Pin 
#define OUTPUT_HC4051_CS3_L()  		HC4051_CS3_GPIO_Port->ODR &= ~HC4051_CS3_Pin 
#define OUTPUT_HC4051_CS4_H()     	HC4051_CS4_GPIO_Port->ODR |= HC4051_CS4_Pin 
#define OUTPUT_HC4051_CS4_L()  		HC4051_CS4_GPIO_Port->ODR &= ~HC4051_CS4_Pin 
#define OUTPUT_HC4051_CS5_H()     	HC4051_CS5_GPIO_Port->ODR |= HC4051_CS5_Pin 
#define OUTPUT_HC4051_CS5_L()  		HC4051_CS5_GPIO_Port->ODR &= ~HC4051_CS5_Pin 
#define OUTPUT_HC4051_CS6_H()     	HC4051_CS6_GPIO_Port->ODR |= HC4051_CS6_Pin 
#define OUTPUT_HC4051_CS6_L()  		HC4051_CS6_GPIO_Port->ODR &= ~HC4051_CS6_Pin 
#define OUTPUT_HC4051_CS7_H()     	HC4051_CS7_GPIO_Port->ODR |= HC4051_CS7_Pin 
#define OUTPUT_HC4051_CS7_L()  		HC4051_CS7_GPIO_Port->ODR &= ~HC4051_CS7_Pin 
#define OUTPUT_HC4051_OUTS0_H()     OUTS0_GPIO_Port->ODR |= OUTS0_Pin 
#define OUTPUT_HC4051_OUTS0_L()  	OUTS0_GPIO_Port->ODR &= ~OUTS0_Pin 
#define OUTPUT_HC4051_OUTS1_H()     OUTS1_GPIO_Port->ODR |= OUTS1_Pin 
#define OUTPUT_HC4051_OUTS1_L()  	OUTS1_GPIO_Port->ODR &= ~OUTS1_Pin 
#define OUTPUT_HC4051_OUTS2_H()     OUTS2_GPIO_Port->ODR |= OUTS2_Pin
#define OUTPUT_HC4051_OUTS2_L()  	OUTS2_GPIO_Port->ODR &= ~OUTS2_Pin 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//INPUT定义区域
#define INPUT_HC4052_OUTS0_H()     	ADS0_GPIO_Port->ODR |= ADS0_Pin 
#define INPUT_HC4052_OUTS0_L()  	ADS0_GPIO_Port->ODR &= ~ADS0_Pin 
#define INPUT_HC4052_OUTS1_H()     	ADS1_GPIO_Port->ODR |= ADS1_Pin 
#define INPUT_HC4052_OUTS1_L()  	ADS1_GPIO_Port->ODR &= ~ADS1_Pin 
//---------------------------------------------------------------------------

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void SHUCHU_SAOMIAO(uint8_t com);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

