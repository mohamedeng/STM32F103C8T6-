/*
 * RTOS_private.h
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */

#ifndef OS_RTOS_RTOS_PRIVATE_H_
#define OS_RTOS_RTOS_PRIVATE_H_


#define MAX_NUMBER_OF_TASKS 20




typedef enum {TASK_READY,TASK_SUSPEND}TASK_STATE_ID;

typedef struct {

	void (*TASK_Handler)(void);
	u8 periodicity;
	TASK_STATE_ID TASK_STATE;

}RTOS_TASK;


typedef struct
{
	RTOS_TASK SYSTICK_TASKS [MAX_NUMBER_OF_TASKS];
	u64 TASK_TIMING [MAX_NUMBER_OF_TASKS];


}
RTOS_SYSTEM;






#endif /* OS_RTOS_RTOS_PRIVATE_H_ */
