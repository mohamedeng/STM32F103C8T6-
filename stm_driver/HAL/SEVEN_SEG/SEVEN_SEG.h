/*
 * SEVEN_SEG.h
 *
 *  Created on: Aug 7, 2022
 *      Author: hp
 */

#ifndef HAL_SEVEN_SEG_SEVEN_SEG_H_
#define HAL_SEVEN_SEG_SEVEN_SEG_H_

#include <stdlib.h>
#include "LIB/DELAY.h"
#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"




typedef enum {CATHODE_SEVENSEG,ANODE_SEVENSEG}SEVENSEG_TYPE_ID;

typedef struct {

	GPIO_ID* SEVENSEG_GPIO_PORT;
	u8* SEVENSEG_PINS;
	SEVENSEG_TYPE_ID SEVENSEG_TYPE;


}
SEVENSEG_ID;



SEVENSEG_ID SEVENSEG_SEVENSEG_ID_INIT(GPIO_ID* GPIO_PORT,u8* SEVENSEG_PINS,SEVENSEG_TYPE_ID SEVENSEG_TYPE);

void SEVENSEG_void_WRITE(SEVENSEG_ID* SEVENSEG,u8 number);


#endif /* HAL_SEVEN_SEG_SEVEN_SEG_H_ */
