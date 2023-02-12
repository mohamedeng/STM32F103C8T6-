/*
 * EXTI_program.c
 *
 *  Created on: Aug 27, 2022
 *      Author: hp
 */

#include "EXTI_interface.h"
#include "EXTI_private.h"


#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/SYSCFG/SYSCFG_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/NVIC/NVIC_interface.h"
static void (* EVENT_HANDLER[23])(void)= {0};


void EXTI_void_ENABLE_INT(EXTI_LineNumber_ID EXTI_LineNumber ,EXTI_PIN_TYPE_ID EXTI_PIN_TYPE,EXTI_TRIGGER_TYPE_ID TRIGGER_TYPE,void (*EVENT_FUNC)(void))
{

	SYSCFG_External_INT_CONFIG(EXTI_LineNumber,EXTI_PIN_TYPE); // select the source input for the EXTI interrupt



	switch (TRIGGER_TYPE)
	{

	case EXTI_Rising:
		SET_BIT(EXTI_REGS->EXTI_RTSR,EXTI_LineNumber);

		break;

	case EXTI_Falling:
		SET_BIT(EXTI_REGS->EXTI_FTSR,EXTI_LineNumber);
		break;
	case EXTI_AnyChange:
		SET_BIT(EXTI_REGS->EXTI_FTSR,EXTI_LineNumber);
		SET_BIT(EXTI_REGS->EXTI_RTSR,EXTI_LineNumber);

		break;

	}


	SET_BIT(EXTI_REGS->EXTI_IMR,EXTI_LineNumber);
	SET_BIT(EXTI_REGS->EXTI_EMR,EXTI_LineNumber);
	EVENT_HANDLER[EXTI_LineNumber] = EVENT_FUNC;


	if(EXTI_LineNumber < 5)
	{

		NVIC_EnableINT(EXTI_LineNumber+6);

	}
	else if(EXTI_LineNumber < 10)
	{
		NVIC_EnableINT(23);
	}
	else
	{
		NVIC_EnableINT(40);
	}



}
void EXTI_void_DISABLE_INT(EXTI_LineNumber_ID EXTI_LineNumber)
{
	CLR_BIT(EXTI_REGS->EXTI_IMR,EXTI_LineNumber);


}
void EXTI_void_TRIGGER_TYPE(EXTI_LineNumber_ID EXTI_LineNumber ,EXTI_TRIGGER_TYPE_ID TRIGGER_TYPE)
{

	switch (TRIGGER_TYPE)
	{

	case EXTI_Rising:
		SET_BIT(EXTI_REGS->EXTI_RTSR,EXTI_LineNumber);

		break;

	case EXTI_Falling:
		SET_BIT(EXTI_REGS->EXTI_FTSR,EXTI_LineNumber);
		break;
	case EXTI_AnyChange:
		SET_BIT(EXTI_REGS->EXTI_FTSR,EXTI_LineNumber);
		SET_BIT(EXTI_REGS->EXTI_RTSR,EXTI_LineNumber);

		break;

	}


}


u8 EXTI_u8_GetPending_LINE_INT(EXTI_LineNumber_ID EXTI_LineNumber)
{
	return GET_BIT(EXTI_REGS->EXTI_PR,EXTI_LineNumber);

}



void EXTI0_IRQHandler()
{
	if(EVENT_HANDLER[0] == 0)
		return;
	EVENT_HANDLER[0]();
	SET_BIT(EXTI_REGS->EXTI_PR,0);

}
void EXTI1_IRQHandler()
{
	if(EVENT_HANDLER[1] == 0)
		return;
	EVENT_HANDLER[1]();
	SET_BIT(EXTI_REGS->EXTI_PR,1);

}
void EXTI2_IRQHandler()
{
	if(EVENT_HANDLER[2] == 0)
		return;
	EVENT_HANDLER[2]();
	SET_BIT(EXTI_REGS->EXTI_PR,2);

}
void EXTI3_IRQHandler()
{
	if(EVENT_HANDLER[3] == 0)
		return;
	EVENT_HANDLER[3]();
	SET_BIT(EXTI_REGS->EXTI_PR,3);

}
void EXTI4_IRQHandler()
{
	if(EVENT_HANDLER[4] == 0)
		return;
	EVENT_HANDLER[4]();
	SET_BIT(EXTI_REGS->EXTI_PR,4);

}

void EXTI9_5_IRQHandler()
{

	if(GET_BIT(EXTI_REGS->EXTI_PR,5) == 1)
	{
		if(EVENT_HANDLER[5] == 0)
			return;
		EVENT_HANDLER[5]();
		SET_BIT(EXTI_REGS->EXTI_PR,5);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,6) == 1)
	{
		if(EVENT_HANDLER[6] == 0)
			return;
		EVENT_HANDLER[6]();
		SET_BIT(EXTI_REGS->EXTI_PR,6);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,7) == 1)
	{
		if(EVENT_HANDLER[7] == 0)
			return;
		EVENT_HANDLER[7]();
		SET_BIT(EXTI_REGS->EXTI_PR,7);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,8) == 1)
	{
		if(EVENT_HANDLER[8] == 0)
			return;
		EVENT_HANDLER[8]();
		SET_BIT(EXTI_REGS->EXTI_PR,8);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,9) == 1)
	{
		if(EVENT_HANDLER[9] == 0)
			return;
		EVENT_HANDLER[9]();
		SET_BIT(EXTI_REGS->EXTI_PR,9);
	}


}


void EXTI15_10_IRQHandler()
{

	if(GET_BIT(EXTI_REGS->EXTI_PR,10) == 1)
	{
		if(EVENT_HANDLER[10] == 0)
			return;
		EVENT_HANDLER[10]();
		SET_BIT(EXTI_REGS->EXTI_PR,10);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,11) == 1)
	{
		if(EVENT_HANDLER[11] == 0)
			return;
		EVENT_HANDLER[11]();
		SET_BIT(EXTI_REGS->EXTI_PR,11);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,12) == 1)
	{
		if(EVENT_HANDLER[12] == 0)
			return;
		EVENT_HANDLER[12]();
		SET_BIT(EXTI_REGS->EXTI_PR,12);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,13) == 1)
	{
		if(EVENT_HANDLER[13] == 0)
			return;
		EVENT_HANDLER[13]();
		SET_BIT(EXTI_REGS->EXTI_PR,13);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,14) == 1)
	{
		if(EVENT_HANDLER[14] == 0)
			return;
		EVENT_HANDLER[14]();
		SET_BIT(EXTI_REGS->EXTI_PR,14);
	}

	if(GET_BIT(EXTI_REGS->EXTI_PR,15) == 1)
	{
		if(EVENT_HANDLER[15] == 0)
		{
			SET_BIT(EXTI_REGS->EXTI_PR,15);
			return;
		}

		EVENT_HANDLER[15]();
		SET_BIT(EXTI_REGS->EXTI_PR,15);
		return;
	}


}
void EXTI16_PVD_IRQHandler()
{
	if(EVENT_HANDLER[16] == 0)
		return;
	EVENT_HANDLER[16]();
	SET_BIT(EXTI_REGS->EXTI_PR,16);

}

void EXTI17_RTC_Alarm_IRQHandler()
{
	if(EVENT_HANDLER[17] == 0)
		return;
	EVENT_HANDLER[17]();
	SET_BIT(EXTI_REGS->EXTI_PR,17);

}

void EXTI18_OTG_FS_WKUP_IRQHandler()
{
	if(EVENT_HANDLER[18] == 0)
		return;
	EVENT_HANDLER[18]();
	SET_BIT(EXTI_REGS->EXTI_PR,18);

}


void EXTI22_RTC_WKUP_IRQHandler()

{
	if(EVENT_HANDLER[22] == 0)
		return;
	EVENT_HANDLER[22]();
	SET_BIT(EXTI_REGS->EXTI_PR,22);

}

