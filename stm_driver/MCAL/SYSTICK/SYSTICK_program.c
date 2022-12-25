/*
 * SYSTICK_program.c
 *
 *  Created on: Aug 31, 2022
 *      Author: hp
 */

#include "SYSTICK_interface.h"

u64 TICK_COUNT = 0;

static void (*EVENT_HANDLER)(void) = {0};


void SYSTICK_void_INIT(SYSTICK_CLKSOURCE_ID SYSTICK_CLKSOURCE)
{
	SYSTICK_REGS->STK_VAL = 1;

	switch (SYSTICK_CLKSOURCE)
	{

	case SYSTICK_AHB_over8:
		SET_BIT(SYSTICK_REGS->STK_CTRL,2);
		break;
	case SYSTICK_AHB:
		CLR_BIT(SYSTICK_REGS->STK_CTRL,2);
		break;
	}


}

void SYSTICK_void_SET_VALUE(u32 START_count_value)
{

	SYSTICK_REGS->STK_LOAD = START_count_value;

}


void SYSTICK_void_Delay_ms(u32 delay_value)//1
{
	u32 START_count_value = delay_value*(1000.0/AHB1_CLOCK_SOURCE);
	SYSTICK_REGS->STK_VAL = 1;
	SYSTICK_void_SET_VALUE(START_count_value);
	CLR_BIT(SYSTICK_REGS->STK_CTRL,16);
	SET_BIT(SYSTICK_REGS->STK_CTRL,0);
	while(GET_BIT(SYSTICK_REGS->STK_CTRL,16) == 0);
	//{SET_BIT(SYSTICK_REGS->STK_CTRL,0);}
	SYSTICK_REGS->STK_VAL = 1;
	//CLR_BIT(SYSTICK_REGS->STK_CTRL,0);

}


void SYSTICK_void_ENABLE_INT(void(*EVENT_FUNC)(void),u32 START_count_value)
{

	CLR_BIT(SYSTICK_REGS->STK_CTRL,0);
	SYSTICK_void_SET_VALUE(START_count_value);

	SET_BIT(SYSTICK_REGS->STK_CTRL,1);
	SET_BIT(SYSTICK_REGS->STK_CTRL,0);
	EVENT_HANDLER = EVENT_FUNC;

}

u64 SYSTICK_u32_GET_TICKS()
{

	return TICK_COUNT;

}


u64 SYSTICK_u32_GET_TIME_us()

	{


	return TICK_COUNT*(1000000.0/AHB1_CLOCK_SOURCE) ;

	}


void SysTick_Handler()
{

	TICK_COUNT++ ;

	SYSTICK_REGS->STK_VAL = 1;

	if(EVENT_HANDLER == 0)
			return;

	EVENT_HANDLER();

}



