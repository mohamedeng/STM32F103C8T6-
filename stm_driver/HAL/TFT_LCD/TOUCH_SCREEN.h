/*
 * TOUCH_SCREEN.h
 *
 *  Created on: Sep 17, 2022
 *      Author: hp
 */

#ifndef HAL_TFT_LCD_TOUCH_SCREEN_H_
#define HAL_TFT_LCD_TOUCH_SCREEN_H_

#include <stdlib.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STM_CONFIG.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"
#include "MCAL/ADC/ADC_interface.h"



#define XP 0
#define YP 1
#define XM 2
#define YM 3
#define NUMSAMPLES 10
// need to test it frist
#define x_min_calibration 450
#define y_min_calibration 270
#define x_max_calibration 3590
#define y_max_calibration 3720

typedef struct
{

	GPIO_ID** Touch_PORTS;
	u8* 	  Touch_PINS; // xp yp xm ym // lcd_d0 ,lcd_d1 , lcd_rs , lcd_cs
	u16 rxplate;
	u16 HIGH;
	u16 WIDTH;


}TUOCH_SCREEN_ID;


typedef struct
{
	u16 x;
	u16 y;
	u16 z;


}TUOCH_POINT_ID;


TUOCH_SCREEN_ID TUOCH_SCREEN_INIT(GPIO_ID** Touch_PORTS,u8* Touch_PINS,u16 rxplate,u16 high,u16 width);

TUOCH_POINT_ID TUOCH_SCREEN_GET_POINT(TUOCH_SCREEN_ID* TUOCH_SCREEN);



#endif /* HAL_TFT_LCD_TOUCH_SCREEN_H_ */
