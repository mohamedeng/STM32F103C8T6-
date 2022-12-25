/*
 * lcd_private.h
 *
 *  Created on: Aug 17, 2022
 *      Author: hp
 */

#ifndef HAL_LCD_PRIVATE_H_
#define HAL_LCD_PRIVATE_H_

#include <stdint.h>
#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "LIB/DELAY.h"


typedef GPIO_ID LCD_GPIO_ID;

typedef enum {LCD_4BIT,LCD_8BIT,LCD4line_4BIT,LCD4line_8BIT }LCD_DISPLAY_MODE_ID;
typedef enum {LCD_CMD,LCD_DATA}LCD_DATABUSWRITE_MODE_ID;



typedef struct {
	LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE;
	LCD_GPIO_ID* GPIO_PORT_DATA;
	u8* DPINS_NUMEBER;
	LCD_GPIO_ID* GPIO_PORT_CMD;
	u8 RS_PIN;
	u8 RW_PIN;
	u8 EN_PIN;
	u8 Column_pointer;
	u8 Row_pointer;
	u8 MAX_CHARS_PERLINE;
}
	LCD_ID;


#endif /* HAL_LCD_PRIVATE_H_ */
