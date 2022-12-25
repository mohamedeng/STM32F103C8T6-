
#include "GPIO_interface.h"
#include "GPIO_private.h"


void GPIO_void_PIN_MODE (GPIO_ID* GPIO,u8 PIN,GPIO_STATE_ID GPIO_STATE)
{


	if (PIN >15)
		return;


	switch(GPIO_STATE)
	{

	case GPIO_INPUT:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_INPUT_PULLDOWN:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_INPUT_PULLUP:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_ANALOGINPUT:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_OUTPUT_PUSHPULL:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_OUTPUT_PUSHPULLUP:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));


		break;

	case GPIO_OUTPUT_PUSHPULLDOWN:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_OUTPUT_OPENDRAIN:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_OUTPUT_OPENDRAINUP:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_OUTPUT_OPENDRAINDOWN:

		SET_BIT(GPIO->GPIO_MODER,(PIN*2));
		CLR_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));


		break;

	case GPIO_AF_PUSHPULL:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));


		break;

	case GPIO_AF_PUSHPULLUP:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_AF_PUSHPULLDOWN:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_AF_OPENDRAIN:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_AF_OPENDRAINUP:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		SET_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	case GPIO_AF_OPENDRAINDOWN:

		CLR_BIT(GPIO->GPIO_MODER,(PIN*2));
		SET_BIT(GPIO->GPIO_MODER,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_OTYPER,PIN);

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		CLR_BIT(GPIO->GPIO_PUPDR,(PIN*2));
		SET_BIT(GPIO->GPIO_PUPDR,(PIN*2+1));

		break;

	}

}

void GPIO_void_PIN_WRITE(GPIO_ID* GPIO,u8 PIN , GPIO_VALUE_ID GPIO_VALUE)
{
	if (PIN > 15)
		return;

	switch (GPIO_VALUE)

	{
	case GPIO_LOW_VALUE:

		GPIO->GPIO_BSRR = (0x01<<(PIN+16));

		break;

	case GPIO_HIGH_VALUE:

		GPIO->GPIO_BSRR = (0x01<<(PIN));

		break;

	}
}

void GPIO_void_PIN_SETSPEED(GPIO_ID* GPIO,u8 PIN ,GPIO_SPEED_ID GPIO_SPEED)
{

	if(PIN > 15)
		return ;

	switch (GPIO_SPEED)

	{
	case GPIO_LOW_SPEED:

		CLR_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		break;

	case GPIO_MEDIUM_SPEED:

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		CLR_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		break;

	case GPIO_HIGH_SPEED:

		CLR_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		break;

	case GPIO_VERYHIGH_SPEED:

		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2));
		SET_BIT(GPIO->GPIO_OSPEEDR,(PIN*2+1));

		break;


	}




}

u8 GPIO_u8_PIN_READ(GPIO_ID* GPIO,u8 PIN)
{
	if(PIN > 15)
		return 15;

	return GET_BIT(GPIO->GPIO_IDR,PIN);

}




void GPIO_void_AF_MODE(GPIO_ID* GPIO,u8 PIN,GPIO_AF_TYPE_ID GPIO_AF_TYPE)
{
	if(PIN>7)
		GPIO->GPIOs_AFRH |= GPIO_AF_TYPE<<((PIN-8)*4);
	else
		GPIO->GPIOs_AFRL |= (GPIO_AF_TYPE<<(PIN*4));

}

