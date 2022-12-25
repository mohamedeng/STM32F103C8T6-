/*
 * RTOS_interface.h
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */

#ifndef OS_RTOS_RTOS_INTERFACE_H_
#define OS_RTOS_RTOS_INTERFACE_H_

#include "LIB/STM_CONFIG.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/DELAY.h"
#include "RTOS_private.h"

#include "MCAL/SYSTICK/SYSTICK_interface.h"

u8 RTOS_u8_CREATE_TASK(void (*TASK_Handler)(void),u64 periodicity,u8 Priority,u16 FRIST_DELAY,TASK_STATE_ID TASK_STATE);
u8 RTOS_u8_SCHDULER(void);
u8 RTOS_u8_DELETE_TASK(u8 Priority);
u8 RTOS_u8_START_OS();
u8 RTOS_u8_TASK_RUN(u8 Priority);
u8 RTOS_u8_TASK_SUSPEND(u8 Priority);

#endif /* OS_RTOS_RTOS_INTERFACE_H_ */
