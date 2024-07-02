/*****************************************************************************
* filename
* SHEZHI.c
*
*
* 描述
* 这个文件实现主程序相关功能函数.
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
#include "SYSTEM.h"
#include "usb_order.h"
#include "flash_rw.h"
#include "tim.h"
#include "dac.h"
#include "gpio.h"
#include "sensor.h"

system_data_struct system_data;
system_para_struct system_para;

void delay_1us (void) __attribute__((section(".ARM.__at_0x08007700")));

//------------------------------------------------------------------
void delay_1us(void){
	uint8_t i;
	for(i=0;i<45;i++){
	}
}
//------------------------------------------------------------------
	
//------------------------------------------------------------------
void delay_10us(void){
	uint16_t i;
	for(i=0;i<690;i++){
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void delay_100us(void){
	uint16_t i;
	for(i=0;i<7165;i++){
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void delay_1ms(void){
	uint8_t i;
	for(i=0;i<10;i++){
		delay_100us();
	}
}
//------------------------------------------------------------------
	
//------------------------------------------------------------------
void delay_us(uint16_t us){
	uint16_t i;
	for(i=0;i<us;i++){
		delay_1us();
	}
}
//------------------------------------------------------------------	

//------------------------------------------------------------------
void delay_ms(uint16_t ms){
	uint16_t i;
	for(i=0;i<ms;i++){
		delay_1ms();
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void system_parameter_load(uint32_t *buff){
	uint32_t i;
	for(i =0;i<(sizeof(system_para.buff_board)>>2);i++){
		system_para.buff_board[i] = *buff++;
	}
	for(i =0;i<(sizeof(system_para.buff_user)>>2);i++){
		system_para.buff_user[i] = *buff++;
	}
	if((system_para.buff_board[0] < 4096)&&(system_para.buff_board[0] >0)){
		system_data.static_pa_value = system_para.buff_board[0];
	}
	if((system_para.buff_board[1] < 4096)&&(system_para.buff_board[1] >0)){
		system_data.static_minus_value= system_para.buff_board[1];
	}
	if((system_para.buff_board[2] < 4096)&&(system_para.buff_board[2] >0)){
		system_data.dynamic_pa_value= system_para.buff_board[2];
	}
	if((system_para.buff_board[3] < 4096)&&(system_para.buff_board[3] >0)){
		system_data.dynamic_minus_value= system_para.buff_board[3];
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void system_parameter_write(uint32_t *buff){
	uint32_t i;
	for(i =0;i<(sizeof(system_para.buff_board)>>2);i++){
		*buff++ = system_para.buff_board[i];
	}
	for(i =0;i<(sizeof(system_para.buff_user)>>2);i++){
		*buff++ = system_para.buff_user[i];
	}
}
//------------------------------------------------------------------

//---------------------------------------------------------------------------
void system_init(void){

	flash_read_para();
	DAC_SET_VALUE(DAC_VOLTAGE_DRIVE_OUT,system_data.static_pa_value);
	DAC_SET_VALUE(DAC_NOISE_CUT,system_data.static_minus_value);
	LED_WORK_ON();
	HAL_TIM_Base_Start_IT(&htim2);
	//打开指示灯，并采集一帧数据
	system_data.send_mode = SYSTEM_RL_SEND;
	SENSOR_Get_Pressure(USB_SEND_BUFF2);	
}
//---------------------------------------------------------------------------

//------------------------------------------------------------------
void system_run(void){
	USB_DY();
}
//------------------------------------------------------------------


/********************************************************************
					GPIO_HAL.c的程序到此结束。
*********************************************************************/
