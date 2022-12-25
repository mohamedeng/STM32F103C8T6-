/*
 * RTOS_program.c
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */


#include "RTOS_interface.h"


RTOS_SYSTEM SYSTEM  = {0};



u8 RTOS_u8_CREATE_TASK(void (*TASK_Handler)(void),u64 periodicity,u8 Priority,u16 FRIST_DELAY,TASK_STATE_ID TASK_STATE)
{
	u8 l_error = 0;

	if (MAX_NUMBER_OF_TASKS < Priority)
	{
		l_error =  1;
	}

	else
	{
		if(SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler == 0 )
		{
			SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler = TASK_Handler;
			SYSTEM.SYSTICK_TASKS[Priority].periodicity = periodicity;
			SYSTEM.SYSTICK_TASKS[Priority].TASK_STATE = TASK_STATE;
			SYSTEM.TASK_TIMING[Priority] = FRIST_DELAY;

		}

		else
		{
			l_error =  2;
		}
	}



	return l_error;
}


void RTOS_void_SCHDULER(void)
{

	for(int i  = 0; i < MAX_NUMBER_OF_TASKS;i++)
	{

		if(SYSTEM.SYSTICK_TASKS[i].TASK_Handler != 0 && SYSTEM.SYSTICK_TASKS[i].TASK_STATE == TASK_READY)
		{

			if(SYSTEM.TASK_TIMING[i] == 0)
			{
				SYSTEM.SYSTICK_TASKS[i].TASK_Handler();
				SYSTEM.TASK_TIMING[i] = SYSTEM.SYSTICK_TASKS[i].periodicity;

			}

			else
			{
				SYSTEM.TASK_TIMING[i]--;
			}

		}


	}


	return ;

}

u8 RTOS_u8_DELETE_TASK(u8 Priority)
{
	u8 l_error = 0;
	if(SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler != 0)
	{
		SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler = 0;
	}
	else
	{
		l_error = 1;
	}

	return l_error;

}


u8 RTOS_u8_TASK_SUSPEND(u8 Priority)
{

	u8 l_error = 0;
	if(SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler != 0)
	{
		SYSTEM.SYSTICK_TASKS[Priority].TASK_STATE = TASK_SUSPEND;
	}
	else
	{
		l_error = 1;
	}

	return l_error;
}


u8 RTOS_u8_TASK_RUN(u8 Priority)
{


	u8 l_error = 0;
	if(SYSTEM.SYSTICK_TASKS[Priority].TASK_Handler != 0)
	{
		SYSTEM.SYSTICK_TASKS[Priority].TASK_STATE = TASK_READY;
	}
	else
	{
		l_error = 1;
	}

	return l_error;


}

u8 RTOS_u8_START_OS(u32 TICK_TIME)
{

	SYSTICK_void_ENABLE_INT(RTOS_void_SCHDULER,TICK_TIME);

	return 0;
}


