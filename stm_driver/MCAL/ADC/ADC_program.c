/*
 * ADC_program.c
 *
 *  Created on: Sep 3, 2022
 *      Author: hp
 */



static void(*EVENT_HANDLER)(void) = {0};

#include "LIB/DELAY.h"
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "ADC_interface.h"



void ADC_void_INIT(ADC_CHANNEL_ID* ADC_CHANNELS,u8 NUMBER_OF_CHANNELS)
{
	RCC_void_ENABLE_PERCLK(RCC_ADC1);

	for(int i = 0; i<NUMBER_OF_CHANNELS;i++)
	{

		if (ADC_CHANNELS[i] > 9)
			break;

		if(ADC_CHANNELS[i] < 8)
			GPIO_void_PIN_MODE(GPIOA_REGS, ADC_CHANNELS[i], GPIO_ANALOGINPUT);

		if(ADC_CHANNELS[i] > 7)
			GPIO_void_PIN_MODE(GPIOB_REGS, ADC_CHANNELS[i]-8, GPIO_ANALOGINPUT);

	}

	SET_BIT(ADC_REGS->ADC_CR2,0);
	Delay_ms(200);


}


u32 ADC_u32_ANALOG_REGULAR_SingleRead_BLOCKING(ADC_CHANNEL_ID CHANNEL)
{

	if(CHANNEL > 9)
		return 51;

	u16 result;

	//ADC_REGS->ADC_SMPR2 |= (7<<24);
	ADC_REGS->ADC_SQR1 &= ~(15<<20);

	ADC_REGS->ADC_SQR3 |= (CHANNEL);


	SET_BIT(ADC_REGS->ADC_CR2,30);

	while(GET_BIT(ADC_REGS->ADC_SR,1)==0);
	result = ADC_REGS->ADC_DR;
	CLR_BIT(ADC_REGS->ADC_SR,1);
	if(GET_BIT(ADC_REGS->ADC_SR,5) == 1)
		return 50;

	ADC_REGS->ADC_SQR3 = 0;

	return result;

}


u32 ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING(ADC_CHANNEL_ID CHANNEL,u32* result_return_var)
{

	u16 error;
	u32 l_block = 0;

	if(CHANNEL > 9)
		error = 1;


	//ADC_REGS->ADC_SMPR2 |= (7<<24);
	ADC_REGS->ADC_SQR1 &= ~(15<<20);

	ADC_REGS->ADC_SQR3 |= (CHANNEL);


	SET_BIT(ADC_REGS->ADC_CR2,30);

	while(GET_BIT(ADC_REGS->ADC_SR,1)==0 && l_block!= ADC_MAX_BLOUCKING_TIME ){l_block++;}

	if(l_block == ADC_MAX_BLOUCKING_TIME)
	{
		error = 2;
	}

	*result_return_var = ADC_REGS->ADC_DR;

	CLR_BIT(ADC_REGS->ADC_SR,1);
	if(GET_BIT(ADC_REGS->ADC_SR,5) == 1)
		error = 3;


	ADC_REGS->ADC_SQR3 = 0;

	return error;

}



void ADC_ENABLE_INT(void(* EVENT_FUNC)(void))
{
	EVENT_HANDLER = EVENT_FUNC;
	SET_BIT(ADC_REGS->ADC_CR1,5);

}

void ADC_DISABLE_INT()
{
	EVENT_HANDLER = 0;
	CLR_BIT(ADC_REGS->ADC_CR1,5);


}



void ADC_IRQHandler()
{

	if(EVENT_HANDLER ==0)
		return;


	EVENT_HANDLER();

}

