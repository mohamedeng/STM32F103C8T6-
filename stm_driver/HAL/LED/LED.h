/*
 * LED.h
 *
 *  Created on: Sep 8, 2022
 *      Author: hp
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_


#include "LIB/DELAY.h"
#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/GPIO/GPIO_interface.h"


typedef struct

{

	GPIO_ID* LED_GPIO;
	u8 LED_PIN;

}LED_ID;



LED_ID LED_LED_ID_INIT(GPIO_ID* LED_GPIO,u8 LED_PIN);



void LED_void_TURN_ON(LED_ID* LED);


void LED_void_TURN_OFF(LED_ID* LED);



#endif /* HAL_LED_LED_H_ */
