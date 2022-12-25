/*
 * DC_MOTOR.c
 *
 * Created: 7/27/2022 6:41:35 AM
 *  Author: hp
 */ 
#include "DC_MOTOR.h"

DC_MOTOR_ID DCMOTOR_void_INIT(GPIO_ID* DCMOTOR_PORT,u8 PIN1,u8 PIN2,u8 ENPIN)
{
	DC_MOTOR_ID DC_MOTOR = {DCMOTOR_PORT,PIN1,PIN2,ENPIN};

	GPIO_void_PIN_MODE(DC_MOTOR.DCMOTOR_PORT,DC_MOTOR.DC_MOTOR_EN, GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(DC_MOTOR.DCMOTOR_PORT,DC_MOTOR.PIN1, GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(DC_MOTOR.DCMOTOR_PORT,DC_MOTOR.PIN2, GPIO_OUTPUT_PUSHPULL);

	return DC_MOTOR;
}

void DCMOTOR_void_MOVE(DC_MOTOR_ID* DC_MOTOR,u8 DIRECTION)
{
	if (DIRECTION )
	{

		GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN1, GPIO_HIGH_VALUE);
		GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN2, GPIO_LOW_VALUE);
		return;	
	}
	
	GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN1, GPIO_LOW_VALUE);
	GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN2, GPIO_HIGH_VALUE);
	
}


void DCMOTOR_void_STOP(DC_MOTOR_ID* DC_MOTOR)
{
	GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN1, GPIO_LOW_VALUE);
	GPIO_void_PIN_WRITE(DC_MOTOR->DCMOTOR_PORT, DC_MOTOR->PIN2, GPIO_LOW_VALUE);
}
