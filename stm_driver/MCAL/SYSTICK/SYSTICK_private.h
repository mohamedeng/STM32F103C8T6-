/*
 * SYSTICK_private.h
 *
 *  Created on: Aug 31, 2022
 *      Author: hp
 */

#ifndef MCAL_SYSTICK_SYSTICK_PRIVATE_H_
#define MCAL_SYSTICK_SYSTICK_PRIVATE_H_


#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


typedef enum {SYSTICK_AHB_over8,SYSTICK_AHB}SYSTICK_CLKSOURCE_ID;

typedef enum {SYSTICK_ENABLE_INT,SYSTICK_DISABLE_INT}SYSTICK_INT_E_ID;


typedef struct {

	u32 STK_CTRL;

	u32 STK_LOAD;

	u32 STK_VAL;

	u32 STK_CALIB;



}SYSTICK_ID;


#define SYSTICK_REGS ((SYSTICK_ID*)(0xE000E010))

#endif /* MCAL_SYSTICK_SYSTICK_PRIVATE_H_ */
