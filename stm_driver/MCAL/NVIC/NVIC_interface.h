/*
 * NVIC_interface.h
 *
 *  Created on: Aug 27, 2022
 *      Author: hp
 */

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

#include "NVIC_private.h"

void NVIC_EnableINT(INT_Type INT);

void NVIC_DisableINT(INT_Type INT);

void NVIC_SetPendingINT(INT_Type INT);

void NVIC_ClearPendingINT(INT_Type INT);

u32 NVIC_GetPendingINT(INT_Type INT);

void NVIC_SetPriority(INT_Type INT, u32 priority);

u32 NVIC_Get_Group_Priority(INT_Type INT);


#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
