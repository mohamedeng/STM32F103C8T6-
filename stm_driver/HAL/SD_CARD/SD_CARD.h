/*
 * SD_CARD.h
 *
 *  Created on: Nov 18, 2022
 *      Author: hp
 */

#ifndef HAL_SD_CARD_SD_CARD_H_
#define HAL_SD_CARD_SD_CARD_H_

#include "LIB/STM_CONFIG.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/DELAY.h"


#include "MCAL/SPI/SPI_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/RCC/RCC_interface.h"

#include "Data_Structures/Stack/Stack.h"

#include "SD_CARD_INFO.h"



#define SD_CARD_MOSI 0
#define SD_CARD_MISO 1
#define SD_CARD_SCK 2
#define SD_CARD_CS 3
#define SD_CARD_ERROR_LOG_ARRAY_SIZE 10

#define SD_CARD_TIME_OUT 200

typedef enum{SD_CARD_MMC_VER3,SD_CARD_VER1,SD_CARD_VER2_BYTE_ADRESS,SD_CARD_VER2_BLOCK_ADRESS}SD_CARD_VERSION_TYPE;

typedef struct{
	SPI_PER SD_CARD_SPI;
	GPIO_ID* SD_CARD_MOSI_POR;u8 SD_CARD_MOSI_PIN;
	GPIO_ID* SD_CARD_MISO_PORT;u8 SD_CARD_MISO_PIN;
	GPIO_ID* SD_CARD_SCK_PORT;u8 SD_CARD_SCK_PIN;
	GPIO_ID* SD_CARD_CS_PORT;u8 SD_CARD_CS_PIN;
	Stack_Struct HW_ErrorStack;
	u8 HW_ErrorCount;
	SD_CARD_VERSION_TYPE SD_CARD_VERSION;
}SD_CARD_ID;


SD_CARD_ID SD_CARD_INIT(
		SPI_PER SPI_PER_NUMER,
		GPIO_ID** SD_CARD_PORTS,u8* SD_CARD_PINS);

void SD_CARD_void_SEND_COMMAND(SD_CARD_ID* SD_CARD,SD_CARD_COMMANDS SD_CARD_COMMAND,u32 ARGUMENT);

void SD_CARD_PUSH_ERROR(SD_CARD_ID* SD_CARD,u8 ERROR);

void SD_CARD_ENABLE_CS(SD_CARD_ID* SD_CARD);
void SD_CARD_DISABLE_CS(SD_CARD_ID* SD_CARD);
void SD_CARD_void_SPI_SEND(SD_CARD_ID* SD_CARD,u8 DATA);
u8 SD_CARD_u8_SPI_RECEIVE(SD_CARD_ID* SD_CARD);
u8 SD_CARD_u8_RES_WAIT(SD_CARD_ID* SD_CARD,u32* value_Expected,u8 value_Expected_count,u32 TIME_OUT);
void SD_CARD_void_WAIT(SD_CARD_ID* SD_CAR,u32 TIME_OUT);
u8 SD_CARD_u8_READ_BLOCK(SD_CARD_ID* SD_CARD,u32 LBA,u8 BLOCK_ARRAY[512]);



#endif /* HAL_SD_CARD_SD_CARD_H_ */
