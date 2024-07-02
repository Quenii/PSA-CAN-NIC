/*****************************************************************************
* filename
* CHUANGANQI.c
*
*
* 描述
* 这个文件实现主程序相关功能函数.
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
#include "stm32f7xx_hal.h"
#include "sensor.h"
#include "SYSTEM.h"
#include "gpio.h"
#include "adc.h"
#include "dac.h"
#include "USB_ORDER.h"


/******************************************************************
函数名称:GetPowerMag()
函数功能:计算各次谐波幅值
参数说明:
备　　注:先将lBufOutArray分解成实部(X)和虚部(Y)，然后计算幅值(sqrt(X*X+Y*Y)
作　　者:博客园 依旧淡然（http://www.cnblogs.com/menlsh/）
*******************************************************************/
__align(4) uint8_t SENSOR_SAMPLE_BUFF[ADC_USED_CHANNEL<<2]; 

uint8_t test_adc =0;
//------------------------------------------------------------------
void SENSOR_CAIJI(uint8_t *buf){
	uint16_t timeout = 0;
	//采集1行大约66us delay 10 3 3 3;4ms for one frame 20230213
	//采集1行大约110us delay 50 3 3 3;6ms for one frame 20230213
	// first 11 channels
	INPUT_HC4052_OUTS0_L();
	INPUT_HC4052_OUTS1_L();
	delay_us(50);  
	system_data.SENSOR_SAMPLE_OVER = 0;
	ADC_Start_DMA((uint32_t *)buf,ADC_USED_CHANNEL);
	while((system_data.SENSOR_SAMPLE_OVER == 0)&&(timeout++ < 250)){
		//等待采集完成
	}
	//second 11 channels
	INPUT_HC4052_OUTS0_H();
	INPUT_HC4052_OUTS1_L();
	delay_us(3); 
	system_data.SENSOR_SAMPLE_OVER = 0;
	timeout = 0;
	ADC_Start_DMA((uint32_t *)(buf + 11),ADC_USED_CHANNEL);
	while((system_data.SENSOR_SAMPLE_OVER == 0)&&(timeout++ < 250)){
		//等待采集完成
	}
	//third 11 channels
	INPUT_HC4052_OUTS0_L();
	INPUT_HC4052_OUTS1_H();
	delay_us(3); 
	system_data.SENSOR_SAMPLE_OVER = 0;
	timeout = 0;
	ADC_Start_DMA((uint32_t *)(buf + (22)),ADC_USED_CHANNEL);
	while((system_data.SENSOR_SAMPLE_OVER == 0)&&(timeout++ < 250)){
		//等待采集完成
	}
	//forth 11 channels
	INPUT_HC4052_OUTS0_H();
	INPUT_HC4052_OUTS1_H();
	delay_us(3); 
	system_data.SENSOR_SAMPLE_OVER = 0;
	timeout = 0;
	ADC_Start_DMA((uint32_t *)(buf + (33)),ADC_USED_CHANNEL);
	while((system_data.SENSOR_SAMPLE_OVER == 0)&&(timeout++ < 250)){
		//等待采集完成
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
uint16_t SENSOR_FILL_HL(uint8_t *buf,uint8_t* dat,uint16_t len,uint8_t row){	
	uint8_t i;
	uint8_t pianyi= SENSOR_SAMPLE_LIN - 1;
	for(i=0;i<SENSOR_SAMPLE_LIN;i++){
		if(dat[i] > 0){
			buf[len++] = row; 
			buf[len++] = pianyi - i;
			buf[len++] =  dat[i];
		}
	}
	return len;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
uint16_t SENSOR_FILL_2288(uint8_t *buf,uint8_t* dat,uint16_t len,uint8_t column){	
	uint8_t i;//,val;	
	uint8_t pianyi= SENSOR_SAMPLE_LIN - 1;
	uint8_t *wr = buf+column+SENSOR_2288_Pianyi; 
	//当前的指针
	for(i=0;i<SENSOR_SAMPLE_LIN;i++){
		//buf[len++] =  dat[pianyi -i];
		*wr =  dat[pianyi -i];
		wr += SENSOR_SAMPLE_COM;
		len++;
	}
	return len;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
uint16_t SENSOR_Get_Pressure(uint8_t *buf){
	//close all line
	//buf 数据区域  sys_id  ID  cycle 每次采集帧数 code 功能码
	uint8_t i,sum;//这个方式10ms采集1帧图像
	uint16_t data_len = 0;
	buf[data_len++] = 0xff; // len 2
	buf[data_len++] = 0; // len 1
	buf[data_len++] = 0xff; // 同步头	
	buf[data_len++] = 0; // len 2
	buf[data_len++] = 0; // len 1
	buf[data_len++] = 0; // 3个字节的长度
	buf[data_len++] = SYSTEM_READ_DATA; //读取数据指令码
	buf[data_len++] = system_data.send_mode; //发送模式
	if(system_data.send_mode == SYSTEM_RL_SEND){
		for(i=1;i<53;i++){
			SHUCHU_SAOMIAO(i);	 //消耗时间1.5us
			//输出1行
			SENSOR_CAIJI(&SENSOR_SAMPLE_BUFF[0]);
			data_len = SENSOR_FILL_HL(buf,&SENSOR_SAMPLE_BUFF[0],data_len,(i-1));
		}
		SHUCHU_SAOMIAO(0);
	}
	else{
		for(i=1;i<53;i++){
			SHUCHU_SAOMIAO(i);	 //消耗时间1.5us
			//输出1行
			SENSOR_CAIJI(&SENSOR_SAMPLE_BUFF[0]);
			data_len = SENSOR_FILL_2288(buf,&SENSOR_SAMPLE_BUFF[0],data_len,(i-1));
		}
		SHUCHU_SAOMIAO(0);

	}
	//close all line
	buf[data_len++] = sum; // sum cal

	buf[4] = data_len/256;
	buf[5] = data_len%256;
	buf[data_len - 1] = usb_order_cal_sum(buf,(data_len-1)); // sum cal
	//data length
  	return data_len;
}
//------------------------------------------------------------------

/********************************************************************
					CHUANGANQI.c的程序到此结束。
*********************************************************************/

