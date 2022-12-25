/*
 * BUTTON.h
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */

#ifndef HAL_BUTTON_BUTTON_H_
#define HAL_BUTTON_BUTTON_H_

#include <stdlib.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STM_CONFIG.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"

typedef struct
{

	GPIO_ID* BUTTON_GPIO;
	u8 BUTTON_PIN;


}BUTTON_ID;



BUTTON_ID BUTTON_BUTTON_ID_INIT(GPIO_ID* BUTTON_GPIO,u8 BUTTON_PIN);


u8 BUTTON_u8_GET_INPUT(BUTTON_ID* BUTTON);

u8 BUTTON_u8_WAIT(BUTTON_ID* BUTTON);






#endif /* HAL_BUTTON_BUTTON_H_ */
