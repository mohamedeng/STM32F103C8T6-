/*
 * NVIC_program.c
 *
 *  Created on: Aug 27, 2022
 *      Author: mohamed mahmoud abdo
 */

#include "NVIC_interface.h"



void NVIC_EnableINT(INT_Type INT)
{


	CLR_BIT(AIRCR,10);


	if(INT > 84 || INT < 0)
		return;

	NVIC_REGS->ISER[(INT/32)] = (1<<(INT%32));



}

void NVIC_DisableINT(INT_Type INT)
{

	if(INT > 84 || INT < 0)
		return;

	NVIC_REGS->ICER[(INT/32)] = (1<<(INT%32));


}

void NVIC_SetPendingINT(INT_Type INT)
{

	if(INT > 84 || INT < 0)
		return;

	NVIC_REGS->ISPR[(INT/32)] = (1<<(INT%32));


}

void NVIC_ClearPendingINT(INT_Type INT)
{

	if(INT > 84 || INT < 0)
		return;

	NVIC_REGS->ICPR[(INT/32)] = (1<<(INT%32));

}

u32 NVIC_GetPendingINT(INT_Type INT)
{

	if(INT > 84 || INT < 0)
		return 0;

	return GET_BIT(NVIC_REGS->ISPR[(INT/32)], (INT%32));


}

void NVIC_SetPriority(INT_Type INT, u32 priority)
{

	if(INT > 84 || INT < 0)
		return;

	NVIC_REGS->IPR[(INT/4)] = (priority<<((INT%4)*4));


}

u32 NVIC_Get_Group_Priority(INT_Type INT)
{





}
