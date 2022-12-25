/*
 * NTC_THERMISTOR.h
 *
 *  Created on: Nov 5, 2022
 *      Author: hp
 */

#ifndef HAL_NTC_THERMISTOR_NTC_THERMISTOR_H_
#define HAL_NTC_THERMISTOR_NTC_THERMISTOR_H_



#include "LIB/STM_CONFIG.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/DELAY.h"

#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"

#define NTC_VCC 3.3

typedef struct
{
	GPIO_ID* THERMISTOR_PORT;
	u8 THERMISTOR_PIN;
	u32 B_value;
	u32 INIT_TEMP_K;
	u32 INIT_NTC_RES;
	u32 Series_RES_VALUE;
	u32 CALCULATED_RES;
}NTC_THERMISTOR_ID;


NTC_THERMISTOR_ID NTC_THERMISTOR_INIT(GPIO_ID* THERMISTOR_PORT,u8 THERMISTOR_PIN,u32 B_value,u32 INIT_TEMP_K,u32 INIT_NTC_RES,u32 Series_RES_VALUE);

u32 NTC_THERMISTOR_u32_GET_TEMP(NTC_THERMISTOR_ID* NTC_THERMISTOR);



#endif /* HAL_NTC_THERMISTOR_NTC_THERMISTOR_H_ */
