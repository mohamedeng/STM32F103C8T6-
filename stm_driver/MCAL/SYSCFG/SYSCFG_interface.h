/*
 * SYSCFG_interface.h
 *
 *  Created on: Aug 29, 2022
 *      Author: hp
 */

#ifndef MCAL_SYSCFG_SYSCFG_INTERFACE_H_
#define MCAL_SYSCFG_SYSCFG_INTERFACE_H_

#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "SYSCFG_private.h"
#include "MCAL/RCC/RCC_interface.h"


void SYSCFG_External_INT_CONFIG(u32 EXTI_LineNumber,u32 EXTI_PIN_TYPE);





#endif /* MCAL_SYSCFG_SYSCFG_INTERFACE_H_ */
