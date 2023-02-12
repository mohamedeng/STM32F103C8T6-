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
u8 EXTI_u8_GetPending_LINE_INT(EXTI_LineNumber_ID EXTI_LineNumber);



void EXTI0_IRQHandler();
void EXTI1_IRQHandler();
void EXTI2_IRQHandler();
void EXTI3_IRQHandler();
void EXTI4_IRQHandler();
void EXTI9_5_IRQHandler();
void EXTI15_10_IRQHandler();
void EXTI16_PVD_IRQHandler();
void EXTI17_RTC_Alarm_IRQHandler();
void EXTI18_OTG_FS_WKUP_IRQHandler();
void EXTI22_RTC_WKUP_IRQHandler();




#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
