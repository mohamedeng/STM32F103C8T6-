/*
 * USART_program.c
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */


#include "LIB/STM_CONFIG.h"
#include "USART_CONFIG.h"
#include "USART_interface.h"

void USART_INIT(
		USART_ID* USART,u32 BaudRate,u8 DataWidth, u8 StopBit,
		USART_Parity_CONTROL_ID Parity_Enable,Parity_selection_ID Parity_selection,
		USART_TransferDirection_ID TransferDirection,u8 HardwareFlowControl,USART_OVER_SAMPLE_ID oversampling
		)
{
	USART->USART_CR1 = 0;

	USART->USART_CR1 |= (oversampling<<OVER8);
	switch(oversampling)
	{
	case USART_OVER_SAMPLE_16: USART->USART_BRR = UART_BRR_SAMPLING16(APB2_CLOCK_SOURCE,BaudRate);break;
	case USART_OVER_SAMPLE_8: USART->USART_BRR = UART_BRR_SAMPLING8(APB2_CLOCK_SOURCE,BaudRate);break;

	}

	if (DataWidth == 9)
	{
		USART->USART_CR1 |= (0x1<<USART_Word_length_BIT) ;
	}

	if(Parity_Enable == USART_Parity_Enable)
	{
		USART->USART_CR1 |= (USART_Parity_Enable<<PCE) | (Parity_selection<<PS); //enable Parity and choose the type

	}

	switch(TransferDirection)
	{
	case USART_TX: USART->USART_CR1 |= (0x1<<USART_TE_BIT)  ;break;
	case USART_RX: USART->USART_CR1 |= (0x1<<USART_RE_BIT)  ;break;
	case USART_TX_RX: USART->USART_CR1 |= (0x1<<USART_TE_BIT) | (0x1<<USART_RE_BIT) ;break;

	}

	USART->USART_CR2 |= (StopBit<<USART_STOPBIT_BIT);

	USART->USART_CR1 |= (0x1<<UE);


}

void USART_void_SETBAUDRATE(USART_ID* USART,u16 USART_BAUDRATE)
{
	USART_OVER_SAMPLE_ID oversampling ;
	if(GET_BIT(USART->USART_CR1,OVER8))
	{
		oversampling = USART_OVER_SAMPLE_8;
	}
	else
	{
		oversampling = USART_OVER_SAMPLE_16;
	}

	switch(oversampling)
	{
	case USART_OVER_SAMPLE_16: USART->USART_BRR = UART_BRR_SAMPLING16(APB2_CLOCK_SOURCE,USART_BAUDRATE);break;
	case USART_OVER_SAMPLE_8: USART->USART_BRR = UART_BRR_SAMPLING8(APB2_CLOCK_SOURCE,USART_BAUDRATE);break;

	}

}


void USART_void_TRANSMIT_BYTE(USART_ID* USART,u16 DATA)
{
	while(GET_BIT(USART->USART_SR,7) == 0);
	USART->USART_DR = DATA;
	while(GET_BIT(USART->USART_SR,TC) == 0);
	CLR_BIT(USART->USART_SR,TC);



}

void USART_void_TRANSMIT_STRING(USART_ID* USART,u8* STRING)
{
	u8 l_counter = 0;

	while(STRING[l_counter] != '\0')
	{

		USART_void_TRANSMIT_BYTE(USART,STRING[l_counter]);
		l_counter++;

	}


}


u16 USART_u16_NON_BLOCKING_RECEIVE_BYTE(USART_ID* USART)
{

	u8 l_error_data = 255;
	u8 l_counter = 0;
	u8 l_returnValue = 0;

	while(GET_BIT(USART->USART_SR,RXNE) == 0 && l_counter<USART_MAX_BLOUCKING_TIME)
	{
		l_counter++;
	}

	if(l_counter == USART_MAX_BLOUCKING_TIME)
	{
		return l_error_data;
	}

	l_returnValue = USART->USART_DR;

	return l_returnValue;



}

u16 USART_u16_BLOCKING_RECEIVE_BYTE(USART_ID* USART)
{


	u8 l_returnValue = 0;

	while(GET_BIT(USART->USART_SR,RXNE) == 0);

	l_returnValue = USART->USART_DR;

	return l_returnValue;

}
