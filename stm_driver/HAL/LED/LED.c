/*
 * LED.c
 *
 *  Created on: Sep 8, 2022
 *      Author: hp
 */



#include "LED.h"



LED_ID LED_LED_ID_INIT(GPIO_ID* LED_GPIO,u8 LED_PIN)

{
	GPIO_void_PIN_MODE(LED_GPIO, LED_PIN, GPIO_OUTPUT_PUSHPULL);
	LED_ID LED = {LED_GPIO,LED_PIN};


	return LED;
}



void LED_void_TURN_ON(LED_ID* LED)
{


	GPIO_void_PIN_WRITE(LED->LED_GPIO, LED->LED_PIN, GPIO_HIGH_VALUE);




}


void LED_void_TURN_OFF(LED_ID* LED)

{



	GPIO_void_PIN_WRITE(LED->LED_GPIO, LED->LED_PIN, GPIO_LOW_VALUE);

}
