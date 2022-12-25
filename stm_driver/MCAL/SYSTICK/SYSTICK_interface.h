/*
 * SYSTICK_interface.h
 *
 *  Created on: Aug 31, 2022
 *      Author: hp
 */

#ifndef MCAL_SYSTICK_SYSTICK_INTERFACE_H_
#define MCAL_SYSTICK_SYSTICK_INTERFACE_H_

#include "SYSTICK_private.h"

void SYSTICK_void_INIT(SYSTICK_CLKSOURCE_ID SYSTICK_CLKSOURCE);

void SYSTICK_void_Delay_ms(u32 delay_value);

u64 SYSTICK_u32_GET_TICKS();

u64 SYSTICK_u32_GET_TIME_us();

void SYSTICK_void_SET_VALUE(u32 START_count_value);

void SYSTICK_void_ENABLE_INT(void(*EVENT_FUNC)(void),u32 START_count_value);






#endif /* MCAL_SYSTICK_SYSTICK_INTERFACE_H_ */
