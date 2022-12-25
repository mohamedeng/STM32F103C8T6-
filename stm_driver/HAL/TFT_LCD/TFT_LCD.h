/*
 * TFT_LCD.h
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */

#ifndef HAL_TFT_LCD_TFT_LCD_H_
#define HAL_TFT_LCD_TFT_LCD_H_

#include <stdlib.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STM_CONFIG.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"


#define TFT_LCD_NOP 				0x00
#define TFT_LCD_SOFTREST 			0x01
#define TFT_LCD_Display_Status 		0x09
#define TFT_LCD_SLEEPIN 			0x10
#define TFT_LCD_SLEEPOUT 			0x11
#define TFT_LCD_DisplayON 			0x29
#define TFT_LCD_DisplayOFF 			0x28
#define TFT_LCD_CONTARST 			0xc5
#define TFT_LCD_PIXELFORMAT 		0x3A

#define TFT_LCD_MemoryAccessControl 0x36
#define TFT_LCD_MemoryWrite 		0x2C
#define TFT_LCD_MemoryREAD 		0x2C

#define TFT_LCD_ColumnAddressSet 	0x2A
#define TFT_LCD_PageAddressSet 		0x2B


typedef enum {TFT_LCD_FONT8,TFT_LCD_FONT12,TFT_LCD_FONT16,TFT_LCD_FONT20,TFT_LCD_FONT24}FONT_SIZE_ID;

typedef struct
{

	GPIO_ID** 	TFT_LCD_DATAGPIOS;
	u8* 		TFT_LCD_DATAPINS;

	GPIO_ID** 	TFT_LCD_CMDGPIOS;// RST, CS, RS, WR, RD
	u8 TFT_LCD_RST;
	u8 TFT_LCD_CS;// to send data set 1 , send comand set 0
	u8 TFT_LCD_RS;
	u8 TFT_LCD_WR;
	u8 TFT_LCD_RD;


	u16 TFT_LCD_high;
	u16 TFT_LCD_width;

}TFT_LCD_ID;





TFT_LCD_ID TFT_LCD_void_INIT(GPIO_ID** TFT_LCD_DATAGPIOS,u8* TFT_LCD_DATAPINS,GPIO_ID** TFT_LCD_CMDGPIOS,u8* LCD_CMDPINS);

void TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD_ID* TFT_LCD,u8 DATA);


void TFT_LCD_void_CMD(TFT_LCD_ID* TFT_LCD,u8 COMMAND);

void TFT_LCD_void_DATA(TFT_LCD_ID* TFT_LCD,u8 DATA);


void TFT_LCD_void_WRITE_PIXEL(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 RGB_CODE);

void TFT_LCD_void_SET_CURSOR(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2);

void TFT_LCD_void_DRAW_LINE(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2,u16 RGB_CODE);

void TFT_LCD_void_DRAW_RECT(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2,u16 RGB_CODE);

void TFT_LCD_void_DRAW_CIRCLE(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 radius,u16 RGB_CODE);

void TFT_LCD_void_DRAW_POINT(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 RGB_CODE);

void TFT_LCD_void_CHAR_WRITE(TFT_LCD_ID* TFT_LCD,u8 CHAR,u16 XPOS,u16 YPOS,FONT_SIZE_ID FONT_SIZE,u16 RGB_CODE_FONT,u16 RGB_CODE_BACKGROUND);

void TFT_LCD_void_STRING_WRITE(TFT_LCD_ID* TFT_LCD,u8* STR,u16 XPOS,u16 YPOS,FONT_SIZE_ID FONT_SIZE,u16 RGB_CODE_FONT,u16 RGB_CODE_BACKGROUND);

void TFT_LCD_void_SET_BACKGROUND(TFT_LCD_ID* TFT_LCD,u16 RGB_CODE);
#endif /* HAL_TFT_LCD_TFT_LCD_H_ */