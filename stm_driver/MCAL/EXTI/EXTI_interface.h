/*
 * EXTI_interface.h
 *
 *  Created on: Aug 27, 2022
 *      Author: hp
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

#include "EXTI_private.h"


//void EXTI_void_INIT(EXTI_LineNumber_ID EXTI_LineNumber ,TRIGGER_TYPE_ID TRIGGER_TYPE,(void *EVENT_FUNC)(void));
void EXTI_void_ENABLE_INT(EXTI_LineNumber_ID EXTI_LineNumber,EXTI_PIN_TYPE_ID EXTI_PIN_TYPE,EXTI_TRIGGER_TYPE_ID TRIGGER_TYPE,void (*EVENT_FUNC)(void));
void EXTI_void_DISABLE_INT(EXTI_LineNumber_ID EXTI_LineNumber);
void EXTI_void_TRIGGER_TYPE(EXTI_LineNumber_ID EXTI_LineNumber ,EXTI_TRIGGER_TYPE_ID TRIGGER_TYPE);


void EXTI15_10_IRQHandler();



#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
