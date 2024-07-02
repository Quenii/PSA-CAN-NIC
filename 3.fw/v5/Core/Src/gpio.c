/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ADS0_Pin|ADS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, WORK_LED_Pin|HC4051_CS1_Pin|HC4051_CS2_Pin|HC4051_CS3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, USB_EN_Pin|OUTS0_Pin|OUTS1_Pin|OUTS2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HC4051_CS7_GPIO_Port, HC4051_CS7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, HC4051_CS6_Pin|HC4051_CS5_Pin|HC4051_CS4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = ADS0_Pin|ADS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = WORK_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(WORK_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = USB_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = HC4051_CS7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(HC4051_CS7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = HC4051_CS6_Pin|HC4051_CS5_Pin|HC4051_CS4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = OUTS0_Pin|OUTS1_Pin|HC4051_CS1_Pin|HC4051_CS2_Pin
                          |HC4051_CS3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = OUTS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(OUTS2_GPIO_Port, &GPIO_InitStruct);

  /**/
  HAL_I2CEx_EnableFastModePlus(SYSCFG_PMC_I2C_PB6_FMP);

  /**/
  HAL_I2CEx_EnableFastModePlus(SYSCFG_PMC_I2C_PB7_FMP);

  /**/
  HAL_I2CEx_EnableFastModePlus(SYSCFG_PMC_I2C_PB8_FMP);

}

/* USER CODE BEGIN 2 */
//---------------------------------------------------------------------------
void SHUCHU_CS(uint8_t yn){
	switch(yn){
		case 0:
			OUTPUT_HC4051_OUTS0_L();
			OUTPUT_HC4051_OUTS1_L();
			OUTPUT_HC4051_OUTS2_L();
		break;
		case 1:
			OUTPUT_HC4051_OUTS0_H();
			OUTPUT_HC4051_OUTS1_L();
			OUTPUT_HC4051_OUTS2_L();
		break;
		case 2:
			OUTPUT_HC4051_OUTS0_L();
			OUTPUT_HC4051_OUTS1_H();
			OUTPUT_HC4051_OUTS2_L();
		break;
		case 3:
			OUTPUT_HC4051_OUTS0_H();
			OUTPUT_HC4051_OUTS1_H();
			OUTPUT_HC4051_OUTS2_L();
		break;
		case 4:
			OUTPUT_HC4051_OUTS0_L();
			OUTPUT_HC4051_OUTS1_L();
			OUTPUT_HC4051_OUTS2_H();
		break;
		case 5:
			OUTPUT_HC4051_OUTS0_H();
			OUTPUT_HC4051_OUTS1_L();
			OUTPUT_HC4051_OUTS2_H();
		break;
		case 6:
			OUTPUT_HC4051_OUTS0_L();
			OUTPUT_HC4051_OUTS1_H();
			OUTPUT_HC4051_OUTS2_H();
		break;
		case 7:
			OUTPUT_HC4051_OUTS0_H();
			OUTPUT_HC4051_OUTS1_H();
			OUTPUT_HC4051_OUTS2_H();
		break;
		default:
		break;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void SHUCHU_SAOMIAO(uint8_t com){
	uint8_t cs,yn;
	//com 从1-52共52个com线扫描，如果参数为0代表都不输出
	if(com == 0){
		OUTPUT_HC4051_CS1_H();
		OUTPUT_HC4051_CS2_H();
		OUTPUT_HC4051_CS3_H();
		OUTPUT_HC4051_CS4_H();
		OUTPUT_HC4051_CS5_H();
		OUTPUT_HC4051_CS6_H();
		OUTPUT_HC4051_CS7_H();
	}
	else if(com < 53){
		com--;//方便输出扫描线
		cs = com/8;
		yn = com%8;
		OUTPUT_HC4051_CS1_H();
		OUTPUT_HC4051_CS2_H();
		OUTPUT_HC4051_CS3_H();
		OUTPUT_HC4051_CS4_H();
		OUTPUT_HC4051_CS5_H();
		OUTPUT_HC4051_CS6_H();
		OUTPUT_HC4051_CS7_H();
		SHUCHU_CS(yn);
		switch(cs){
			case 0:
				OUTPUT_HC4051_CS1_L();
			break;
			case 1:
				OUTPUT_HC4051_CS2_L();
			break;
			case 2:
				OUTPUT_HC4051_CS3_L();
			break;
			case 3:
				OUTPUT_HC4051_CS4_L();
			break;
			case 4:
				OUTPUT_HC4051_CS5_L();
			break;
			case 5:
				OUTPUT_HC4051_CS6_L();
			break;
			case 6:
				OUTPUT_HC4051_CS7_L();
			break;
			default:
			break;
		}
	}	
}
//---------------------------------------------------------------------------

/* USER CODE END 2 */
