#ifndef _SYSTEM_H_
#define _SYSTEM_H_
/*****************************************************************************
* filename
* lcd.h
*
*
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
///---------------------------------------------------------------------------
#include "Stm32f723xx.h"
#include "stm32f7xx_hal.h"

//the head file define
//---------------------------------------------------------------------------
#define ADC_USED_CHANNEL 11
#define SENSOR_SAMPLE_COM 52
#define SENSOR_SAMPLE_LIN 44
#define SENSOR_2288_Pianyi 8
#define SENSOR_SAMPLE_FRAME SENSOR_SAMPLE_COM*SENSOR_SAMPLE_LIN

//---------------------------------------------------------------------------
typedef struct
{
	uint32_t buff_board[16];	

	uint32_t  buff_user[20000];
} system_para_struct;

typedef struct
{
	uint8_t SENSOR_SAMPLE_OVER;
	uint8_t buff_used;
	uint8_t send_mode;

	uint16_t static_pa_value;
	uint16_t static_minus_value;

	uint16_t dynamic_pa_value;
	uint16_t dynamic_minus_value;
	
	uint32_t rec_num;
	uint32_t send_num;
} system_data_struct;

extern system_data_struct system_data;
extern system_para_struct system_para;

//---------------------------------------------------------------------------
void delay_1us(void);
void delay_10us(void);
void delay_100us(void);
void delay_1ms(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

void system_parameter_load(uint32_t *buff);
void system_parameter_write(uint32_t *buff);
void system_init(void);
void system_run(void);
//-----------------------------------------------------------------------
#endif
/********************************************************************
					SYSTEM.h的程序到此结束。
*********************************************************************/
