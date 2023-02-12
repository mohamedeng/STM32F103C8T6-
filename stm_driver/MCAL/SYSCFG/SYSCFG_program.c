/*
 * SYSCFG_program.c
 *
 *  Created on: Aug 29, 2022
 *      Author: hp
 */

#include "SYSCFG_interface.h"



void SYSCFG_External_INT_CONFIG(u32 EXTI_LineNumber,u32 EXTI_PIN_TYPE)
{
	RCC_void_ENABLE_PERCLK(RCC_SYSCFG);
	SYSCFG_REGS->SYSCFG_EXTICR[EXTI_LineNumber/4] = (EXTI_PIN_TYPE<<(EXTI_LineNumber%4)*4);

}
