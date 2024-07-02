#include "USB_ORDER.h"
#include "usbd_cdc_if.h"
#include "sensor.h"
#include "dac.h"
#include "system.h"
#include "flash_rw.h"
#include "gpio.h"

//---------------------------------------------------------------------------

__align(4) uint8_t USB_REC_BUFF[2048];
__align(4) uint8_t USB_SEND_BUFF1[PACKET_MAX_SIZE];
__align(4) uint8_t USB_SEND_BUFF2[PACKET_MAX_SIZE];


uint8_t baotou[3] = {0xff,0x00,0xff}; //Э���ͷ
const uint8_t xieyima_addr = 6;  //Э�������ڵ�λ��
uint32_t USB_REC_LENGTH = 2048;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void usb_send_data(uint8_t *dat,uint16_t len){
	uint8_t resend = 0;
	while((CDC_Transmit_HS(dat,len) != USBD_OK)&&(resend++ < USB_RESEND_CYCLE)){
		HAL_Delay(1);
	}
	if(resend < USB_RESEND_CYCLE){
		system_data.send_num++;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void usb_order_sample(){
	//dynamic sample
	if(system_data.buff_used == 0){
		//200 us ,ϵͳ�Զ�����
		usb_send_data(USB_SEND_BUFF2,((USB_SEND_BUFF2[4]<<8)|(USB_SEND_BUFF2[5]))); 
		SENSOR_Get_Pressure(USB_SEND_BUFF1);
		system_data.buff_used = 1;
	}
	else{
		//200 us ,ϵͳ�Զ�����
		usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
		SENSOR_Get_Pressure(USB_SEND_BUFF2);
		system_data.buff_used = 0;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void usb_set_mode(uint8_t work,uint8_t fasong){
	if(work == SYSTEM_STATIC_MODEL)
	{ //��̬����ģʽ
		DAC_SET_VALUE(DAC_VOLTAGE_DRIVE_OUT,system_data.static_pa_value);
		DAC_SET_VALUE(DAC_NOISE_CUT,system_data.static_minus_value);
	}
	else{
		//��̬����ģʽ
		DAC_SET_VALUE(DAC_VOLTAGE_DRIVE_OUT,system_data.dynamic_pa_value);
		DAC_SET_VALUE(DAC_NOISE_CUT,system_data.dynamic_minus_value);
	}

	system_data.send_mode = fasong; //����ģʽ

	//���²ɼ�һ֡����
	SENSOR_Get_Pressure(USB_SEND_BUFF1);
	system_data.buff_used = 1;
}
//---------------------------------------------------------------------------
//�������ص��������
//---------------------------------------------------------------------------
void usb_fill_package(uint8_t *buff,uint8_t *data,uint16_t len){
	uint16_t length = 6;
	memcpy(buff,baotou,sizeof(baotou));
	memcpy(buff+length,data,len);
	length += len;
	length++;
	buff[4] = length/256;
	buff[5] = length%256;
	buff[length-1] = usb_order_cal_sum(buff,length-1);	
}
//---------------------------------------------------------------------------
//��ȡ�������������
//buff Ϊ���ͻ�������data Ϊ ������Ҫ���ƵĻ����������� len�ĳ��ȣ�Ȼ���flash_sector_buf��addr_start��ʼ����data_len������
//---------------------------------------------------------------------------
void usb_fill_para_package(uint8_t *buff,uint8_t *data,uint16_t len,uint16_t addr_start,uint16_t data_len){
	uint16_t length = 6;
	uint8_t *para_start;
	memcpy(buff,baotou,sizeof(baotou));
	memcpy(buff+length,data,len);
	length += len;
	//���������
	para_start = (uint8_t *)flash_sector_buf;
	para_start += addr_start;
	memcpy(buff+length,para_start,data_len);	
	length += data_len;
	//У���
	length++;
	buff[4] = length/256;
	buff[5] = length%256;
	buff[length-1] = usb_order_cal_sum(buff,length-1);	
}
//---------------------------------------------------------------------------
//��ȡ������ַ���������
//---------------------------------------------------------------------------
void usb_fill_addr_package(uint8_t *buff,uint8_t *data,uint16_t len){
	uint32_t length = 6;
	uint32_t addr;
	uint8_t *buff_start = buff;
	memcpy(buff,baotou,sizeof(baotou));
	memcpy(buff+length,data,len);
	length += len;
	buff += length;
	//���������
	*buff++ = 0x00;//
	*buff++ = 0x00;//board addr start
	addr = sizeof(system_para.buff_board) - 1;
	*buff++ = addr/256;//
	*buff++ = addr%256;//board addr end
	addr = sizeof(system_para.buff_board);
	*buff++ = addr/256;//
	*buff++ = addr%256;//user buff addr start
	addr = sizeof(system_para.buff_board) + sizeof(system_para.buff_user) - 1;
	*buff++ = addr/256;//
	*buff++ = addr%256;//user buff addr end
	length += 9;
	//У���
	length++;
	buff_start[4] = length/256;
	buff_start[5] = length%256;
	buff_start[length-1] = usb_order_cal_sum(buff_start,length-1);	
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void usb_order_Func(uint8_t *dat){
	uint8_t *buff; 
	uint32_t data_addr_start = 0;
	uint32_t data_length = 0;
	uint8_t order = *dat;
	switch(order){
		case SYSTEM_SET_WORK_MODEL:
			//���ù���ģʽ
			usb_set_mode(dat[1],dat[2]); 
			usb_fill_package(USB_SEND_BUFF1,dat,3);
			usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
		break;
		case SYSTEM_GET_PARA:
			//��ѹ�������
			data_addr_start = 0x00;
			data_length = 0x24; // 16���ֽڵĲ�����20���ֽڵ����к�
			usb_fill_para_package(USB_SEND_BUFF1,dat,1,data_addr_start,data_length);	
			usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
		break;
		case SYSTEM_SET_PARA:
			//дѹ�������
			data_addr_start = 0x00;
			data_length = 0x24; // 16���ֽڵĲ�����20���ֽڵ����к�
			if((data_addr_start + data_length)  <= sizeof(system_para.buff_board)){
				buff = (uint8_t *)flash_sector_buf;
				buff += data_addr_start;
				memcpy(buff,dat+1,data_length);
				flash_write_para();
				usb_fill_package(USB_SEND_BUFF1,dat,38); //ֻ���Ϳ�ʼ��ַ�ͳ���
				usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
			}
		break;
		case SYSTEM_READ_DATA:
			//��ȡ�ɼ�����
			usb_order_sample();
		break;
		case SYSTEM_USER_GET_PARA:
			//��ȡ������������ָ��
			data_addr_start = sizeof(system_para.buff_board) + (((dat[1]<<8) | dat[2]) << 2);
			data_length = ((dat[3]<<8) | dat[4])<<2;
			if((data_addr_start >= sizeof(system_para.buff_board))&&((data_addr_start + data_length)  <= sizeof(system_para))){
				usb_fill_para_package(USB_SEND_BUFF1,dat,5,data_addr_start,data_length); 	
				usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
			}
		break;
		case SYSTEM_USER_SET_PARA:
			//д��������������ָ��
			data_addr_start = sizeof(system_para.buff_board) + (((dat[1]<<8) | dat[2]) << 2);
			data_length = ((dat[3]<<8) | dat[4]) << 2;
			if((data_addr_start >= sizeof(system_para.buff_board))&&((data_addr_start + data_length)  <= sizeof(system_para))){
				buff = (uint8_t *)flash_sector_buf;
				buff += data_addr_start;
				memcpy(buff,dat+5,data_length);
				usb_fill_package(USB_SEND_BUFF1,dat,5); //ֻ���Ϳ�ʼ��ַ�ͳ���
				usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
			}
		break;

		case SYSTEM_WRITE_PARA:
			//ȷ��д��������������ָ��
			flash_write_para();
			usb_fill_package(USB_SEND_BUFF1,dat,1); 
			usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
		break;
		case SYSTEM_TEST:
			usb_fill_package(USB_SEND_BUFF1,dat,1); 
			usb_send_data(USB_SEND_BUFF1,((USB_SEND_BUFF1[4]<<8)|(USB_SEND_BUFF1[5])));
		break;
		default:
		break;
		}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
uint8_t usb_order_cal_sum(uint8_t *dat,uint16_t length){
 	uint8_t sum = 0;
	uint16_t i;
	for(i=0;i<(length);i++){
		sum += *dat++;
	}
	return sum;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
uint8_t usb_order_check_sum(uint8_t *dat,uint16_t length){
 	uint8_t sum = usb_order_cal_sum(dat,(length - 1));
	if(sum == dat[length - 1]){
		return USBD_OK;
	}
	else{
		return USBD_FAIL;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
uint8_t calDataJiaoyan(uint8_t *buff){
	uint8_t ret = USBD_OK;
	uint8_t *buff_start = buff;
	uint16_t data_length;
	for(uint8_t i=0;i<sizeof(baotou);i++)
	{
		if(*buff++ != baotou[i])
		{
			ret = USBD_FAIL;
		}
	}
	if(ret == USBD_FAIL){ //��ͷ����ʧ��
		*buff_start = 0; //
		return ret;
	}
	data_length = ((buff[1]<<8) | buff[2]);
	ret = usb_order_check_sum(buff_start,data_length); //��У��
	*buff_start = 0; //
	return ret;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void USB_DY(void){
	if(USBD_Interface_fops_HS.Receive((uint8_t *)USB_REC_BUFF,(uint32_t *)(&USB_REC_LENGTH)) == USBD_OK){	
		if(USB_REC_BUFF[0] == baotou[0]){
			if(calDataJiaoyan(&USB_REC_BUFF[0]) == USBD_OK){
				//new order
				system_data.rec_num++;
				usb_order_Func((uint8_t *)&USB_REC_BUFF[xieyima_addr]); //ȥ����ͷ�����ݳ��ȵ���������
			}	
		}
	}
			
}
//---------------------------------------------------------------------------


