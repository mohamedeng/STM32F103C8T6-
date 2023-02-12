/*
 * SPI_program.c
 *
 *  Created on: Oct 13, 2022
 *      Author: hp
 */

#include "SPI_private.h"
#include "SPI_interface.h"
#include "SPI_CONFIG.h"

void SPI_INIT(SPI_PER SPI_PER_NUMER,
		SPI_MASTER_SLAVE_MODE_ID SPI_MASTER_SLAVE_MODE,
		SPI_MODE_ID SPI_MODE,
		SPI_BAUD_RATE_FACTOR_ID SPI_FACTOR,
		SPI_FRAME_SIZE_ID SPI_FRAME_SIZE,
		SPI_Frame_format_ID Frame_format)
{
	SPI_ID* SPI= (SPI_ID*)(SPI_PER_NUMER);

	SPI->SPI_CR1 |= (SPI_FRAME_SIZE<<DFF);
	SPI->SPI_CR1 |= (Frame_format<<LSBFIRST);
	SPI->SPI_CR1 |= (SPI_FACTOR<<BR);// BAUD_RATE_FACTOR
	if(SPI_MASTER_SLAVE_MODE)
	SET_BIT(SPI->SPI_CR1,SPI_SLAVE_MASTER_BIT);


	switch(SPI_MODE)
	{

	case SPI_MODE0:

		CLR_BIT(SPI->SPI_CR1,1);
		CLR_BIT(SPI->SPI_CR1,0);

		break;

	case SPI_MODE1:

		CLR_BIT(SPI->SPI_CR1,1);
		SET_BIT(SPI->SPI_CR1,0);
			break;

	case SPI_MODE2:

		SET_BIT(SPI->SPI_CR1,1);
		CLR_BIT(SPI->SPI_CR1,0);
			break;

	case SPI_MODE3:

		SET_BIT(SPI->SPI_CR1,1);
		SET_BIT(SPI->SPI_CR1,0);
			break;

	}

	SET_BIT(SPI->SPI_CR1,SSM);
	SET_BIT(SPI->SPI_CR1,SSI);

	SET_BIT(SPI->SPI_CR1,SPI_ENABLE_BIT);

}

void SPI_void_SETMODE(SPI_PER SPI_PER_NUMER,SPI_MODE_ID SPI_MODE)
{
	SPI_ID* SPI= (SPI_ID*)(SPI_PER_NUMER);

	switch(SPI_MODE)
	{

	case SPI_MODE0:

		CLR_BIT(SPI->SPI_CR1,1);
		CLR_BIT(SPI->SPI_CR1,0);

		break;

	case SPI_MODE1:

		CLR_BIT(SPI->SPI_CR1,1);
		SET_BIT(SPI->SPI_CR1,0);
			break;

	case SPI_MODE2:

		SET_BIT(SPI->SPI_CR1,1);
		CLR_BIT(SPI->SPI_CR1,0);
			break;

	case SPI_MODE3:

		SET_BIT(SPI->SPI_CR1,1);
		SET_BIT(SPI->SPI_CR1,0);
			break;

	}




}

void SPI_void_SETBAUDRATE(SPI_PER SPI_PER_NUMER,SPI_BAUD_RATE_FACTOR_ID SPI_FACTOR)
{

	SPI_ID* SPI = (SPI_ID*)(SPI_PER_NUMER);
	SPI->SPI_DR = 0xFF;
	volatile u8 temp = SPI->SPI_DR;
	// wait for rx = 1 ,tx = 1 ,busy = 0 flags
	while(GET_BIT(SPI->SPI_SR,1) == 0);
	while(GET_BIT(SPI->SPI_SR,7) == 1);
	// diable spi
	//CLR_BIT(SPI->SPI_CR1,SPI_ENABLE_BIT);
	// change baudrate
	SPI->SPI_CR1 &= BAUD_RATE_BITMASK;
	SPI->SPI_CR1 |= (SPI_FACTOR<<BR);
	CLR_BIT(SPI->SPI_CR1,10);
	//SET_BIT(SPI->SPI_CR1,SPI_ENABLE_BIT);
	temp = SPI->SPI_DR;
}


u8 SPI_void_GETBAUDRATE(SPI_PER SPI_PER_NUMER)
{
	SPI_ID* SPI = (SPI_ID*)(SPI_PER_NUMER);
	return (((SPI->SPI_CR1) & (~BAUD_RATE_BITMASK))>>3);

}

void SPI_void_TRANSMIT_BYTE(SPI_PER SPI_PER_NUMER,u16 DATA)
{

	SPI_ID* SPI = (SPI_ID*)(SPI_PER_NUMER);

	while(GET_BIT(SPI->SPI_SR,1) == 0);
	SPI->SPI_DR = DATA;
	while(GET_BIT(SPI->SPI_SR,1) == 0);
	while(GET_BIT(SPI->SPI_SR,7) == 1);
	volatile u8 temp = SPI->SPI_DR;
//	temp = SPI->SPI_SR;


}

void SPI_void_TRANSMIT_STRING(SPI_PER SPI_PER_NUMER,u8* DATA)
{
	int counter = 0;
	while(DATA[counter] != '\0')
	{

		SPI_void_TRANSMIT_BYTE(SPI_PER_NUMER,DATA[counter]);
		counter++;

	}

}



u16 SPI_u16_RECEIVE_BYTE(SPI_PER SPI_PER_NUMER)
{
	SPI_ID* SPI= (SPI_ID*)(SPI_PER_NUMER);

	while(GET_BIT(SPI->SPI_SR,7) == 1);
	SPI->SPI_DR = 0x00;
	while(GET_BIT(SPI->SPI_SR,0) == 0);
	u8 value_to_return = SPI->SPI_DR;
	return value_to_return;
}

u16 SPI_u16_RECEIVE_BYTE_TX_CONTROL(SPI_PER SPI_PER_NUMER,u8 VALUE_ON_THE_TX)
{
	SPI_ID* SPI= (SPI_ID*)(SPI_PER_NUMER);
	SPI->SPI_DR = VALUE_ON_THE_TX;
	while(GET_BIT(SPI->SPI_SR,7) == 1);

	return SPI->SPI_DR;
}


