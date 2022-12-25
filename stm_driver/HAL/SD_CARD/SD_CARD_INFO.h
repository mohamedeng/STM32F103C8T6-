/*
 * SD_CARD_INFO.h
 *
 *  Created on: Nov 18, 2022
 *      Author: hp
 */

#ifndef HAL_SD_CARD_SD_CARD_INFO_H_
#define HAL_SD_CARD_SD_CARD_INFO_H_

#include "LIB/STM_CONFIG.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/DELAY.h"

typedef enum{
/** GO_IDLE_STATE - init card in spi mode if CS low */
	CMD0 = 0X00,
/** SEND_IF_COND - verify SD Memory Card interface operating condition.*/
	 CMD8 = 0X08,
	/** SEND_CSD - read the Card Specific Data (CSD register) */
	 CMD9 = 0X09,
	/** SEND_CID - read the card identification information (CID register) */
	 CMD10 = 0X0A,
	/** SEND_STATUS - read the card status register */
	 CMD13 = 0X0D,

	 CMD16 = 0X0F,
	/** READ_BLOCK - read a single data block from the card */
	 CMD17 = 0X11,
	/** WRITE_BLOCK - write a single data block to the card */
	 CMD24 = 0X18,
	/** WRITE_MULTIPLE_BLOCK - write blocks of data until a STOP_TRANSMISSION */
	 CMD25 = 0X19,
	/** ERASE_WR_BLK_START - sets the address of the first block to be erased */
	 CMD32 = 0X20,
	/** ERASE_WR_BLK_END - sets the address of the last block of the continuous
		range to be erased*/
	 CMD33 = 0X21,
	/** ERASE - erase all previously selected blocks */
	 CMD38 = 0X26,
	/** APP_CMD - escape for application specific command */
	 CMD55 = 0X37,
	/** READ_OCR - read the OCR register of a card */
	 CMD58 = 0X3A,
	/** SET_WR_BLK_ERASE_COUNT - Set the number of write blocks to be
		 pre-erased before writing */
	 ACMD23 = 0X17,
	/** SD_SEND_OP_COMD - Sends host capacity support information and
		activates the card's initialization process */
	 ACMD41 = 0X29,
}SD_CARD_COMMANDS;
//------------------------------------------------------------------------------
/** status for card in the ready state */
#define  R1_READY_STATE  0X00
/** status for card in the idle state */
#define  R1_IDLE_STATE  0X01
/** status bit for illegal command */
#define  R1_ILLEGAL_COMMAND 0X04
/** start data token for read or write single block*/
#define  DATA_START_BLOCK  0XFE
/** stop token for write multiple blocks*/
#define  STOP_TRAN_TOKEN  0XFD
/** start data token for write multiple blocks*/
#define  WRITE_MULTIPLE_TOKEN 0XFC
/** mask for data response tokens after a write block operation */
#define  DATA_RES_MASK 0X1F
/** write data accepted token */
#define  DATA_RES_ACCEPTED 0X05

#define  R1_READY_STATE_ERROR 1

#define R1_WAIT_ERROR 0xF1

#define  R7_ERROR 0xF2

#define SD_CARD_CMD17_DATA_TOKEN_ERROR 1


#endif /* HAL_SD_CARD_SD_CARD_INFO_H_ */
