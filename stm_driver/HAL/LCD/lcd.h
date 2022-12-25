#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include "lcd_private.h"

void LCD_void_EPIN_PULSE(LCD_ID* LCD);



LCD_ID LCD_LCD_ID_INIT(LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE,GPIO_ID* GPIO_PORT_DATA, u8* DPINS_NUMEBER,GPIO_ID* GPIO_PORT_CMD,u8* CPINS_NUMEBER);
void LCD8bit_void_INIT(LCD_ID* LCD);
void LCD4bit_void_INIT(LCD_ID* LCD);
void LCD_void_custom_char (LCD_ID* LCD,u8 loc,u8 *msg);
void LCD_void_cmd(LCD_ID* LCD,u8 cmd);

void LCD_void_Cursorpos(LCD_ID* LCD,u8 row,u8 coulm);
void LCD_void_char(LCD_ID* LCD,u8 chars);
void LCD_void_clear(LCD_ID* LCD);
void LCD_void_delete(LCD_ID* LCD,u8 number_of_chars_to_delete);
void LCD_void_string(LCD_ID* LCD,u8* string);
void LCD_void_string_pos(LCD_ID* LCD,u8 row,u8 coulm,u8* string);

#endif
