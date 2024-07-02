#ifndef __USB_ORDER_H__
#define __USB_ORDER_H__

//the head file define
#include "stm32f7xx_hal.h"
//---------------------------------------------------------------------------
/*
//网络版本无APP名称和密码
*/
#define USB_RESEND_CYCLE 10
#define PACKET_MAX_SIZE 16384

#define SYSTEM_STATIC_MODEL 1
#define SYSTEM_DYNAMIC_MODEL 2

#define SYSTEM_2288_SEND 1
#define SYSTEM_RL_SEND 2

#define SYSTEM_SET_WORK_MODEL 0x01
#define SYSTEM_READ_DATA 0x10
	
#define SYSTEM_GET_PARA   0xA0
#define SYSTEM_SET_PARA   0xF0


#define SYSTEM_USER_GET_PARA   0xA1
#define SYSTEM_USER_SET_PARA   0xF1
#define SYSTEM_WRITE_PARA   0xF2

#define SYSTEM_TEST   0x00


extern uint8_t USB_SEND_BUFF1[PACKET_MAX_SIZE];
extern uint8_t USB_SEND_BUFF2[PACKET_MAX_SIZE];

//---------------------------------------------------------------------------
void USB_DY(void);
uint8_t usb_order_cal_sum(uint8_t *dat,uint16_t length);
//---------------------------------------------------------------------------
#endif

