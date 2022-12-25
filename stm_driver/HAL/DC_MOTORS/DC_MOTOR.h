/*
 * DC_MOTOR.h
 *
 * Created: 7/27/2022 6:41:21 AM
 *  Author: hp
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include <stdlib.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STM_CONFIG.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"

typedef struct 
{
	GPIO_ID* DCMOTOR_PORT;
	u8 PIN1;
	u8 PIN2;
	u8 DC_MOTOR_EN;

	} DC_MOTOR_ID;


DC_MOTOR_ID DCMOTOR_void_INIT(GPIO_ID* DCMOTOR_PORT,u8 PIN1,u8 PIN2,u8 ENPIN);

void DCMOTOR_void_MOVE(DC_MOTOR_ID* DC_MOTOR,u8 DIRECTION);

void DCMOTOR_void_STOP(DC_MOTOR_ID* DC_MOTOR);



#endif /* DC_MOTOR_H_ */
