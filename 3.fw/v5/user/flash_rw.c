#include "stdint.h"
#include "string.h"

#include "stm32f7xx_hal.h"

#include "flash_rw.h"
#include "system.h"

uint32_t flash_sector_buf[SECTOR_LEN];

/* Private variables ---------------------------------------------------------*/
uint32_t FirstSector = 0, NbOfSectors = 0;
uint32_t Address = 0, SECTORError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;
/*Variable used for Erase procedure*/

void MEM_If_Init_FS(void) {
	HAL_FLASH_Unlock();     
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |\
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR| FLASH_FLAG_ERSERR);  
}
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;
  }
  else
  {
    sector = FLASH_SECTOR_7;
  }
 
  return sector;
}

uint16_t MEM_If_Erase_FS(uint32_t start_Add,uint32_t end_Add){    
	uint32_t SectorError = 0;    
	/* Get the 1st sector to erase */
	MEM_If_Init_FS();
	FirstSector = GetSector(start_Add);
	/* Get the number of sector to erase from 1st sector*/
	NbOfSectors = GetSector(end_Add) - FirstSector + 1;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase	  = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector		  = FirstSector;
	EraseInitStruct.NbSectors	  = NbOfSectors;
	EraseInitStruct.VoltageRange  = VOLTAGE_RANGE_3;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
    {   
  	return (SectorError);   
 	}     
	return (0);   
}

void read_flash_address(uint32_t sector_addr)
{
	uint32_t *addr = (uint32_t *)(sector_addr);
    for(int i =0; i < SECTOR_LEN; i++)
    {
        flash_sector_buf[i] = *(addr+i);
    }
}

void write_flash_address(uint32_t sector_addr)
{
	uint32_t i = 0; 	
	MEM_If_Erase_FS(sector_addr,(sector_addr+SECTOR_LEN));	
	for(i = 0; i < SECTOR_LEN; i++){		
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)(sector_addr+(i<<2)),flash_sector_buf[i]) == HAL_OK)		
		{
		
		}		  
	}	
	HAL_FLASH_Lock();
}

void flash_init_para(void){
	flash_sector_buf[0] = 3000;
	flash_sector_buf[1] = 100;
	flash_sector_buf[2] = 1000;
	flash_sector_buf[3] = 60;
	
	flash_sector_buf[4] = 0x30333031;
	flash_sector_buf[5] = 0x30333031;
	flash_sector_buf[6] = 0x35393137;
	flash_sector_buf[7] = 0x31303031;
	flash_sector_buf[8] = 0x00003430;
}


void flash_read_para(void){
	read_flash_address(FLASH_SAVE_ADDRESS);
	if(flash_sector_buf[0] == 0xffffffff){
		//重新初始化
		flash_init_para();
		write_flash_address(FLASH_SAVE_ADDRESS);
	}
	system_parameter_load(flash_sector_buf);
}

void flash_write_para(void){
	write_flash_address(FLASH_SAVE_ADDRESS);
	system_parameter_load(flash_sector_buf);
}

