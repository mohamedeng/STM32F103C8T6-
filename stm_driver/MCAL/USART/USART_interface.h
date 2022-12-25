/*
 * USART_interface.h
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

#include "USART_private.h"
#include "USART_CONFIG.h"

/*
 *
 *
 *
 *
 */


void USART_INIT(
		USART_ID* USART,u32 BaudRate,u8 DataWidth, u8 StopBit,
		USART_Parity_CONTROL_ID Parity_Enable,Parity_selection_ID Parity_selection,
		USART_TransferDirection_ID TransferDirection,u8 HardwareFlowControl,USART_OVER_SAMPLE_ID oversampling
		);
void USART_void_SETBAUDRATE(USART_ID* USART,u16 USART_BAUDRATE);

void USART_void_TRANSMIT_BYTE(USART_ID* USART,u16 DATA);

void USART_void_TRANSMIT_STRING(USART_ID* USART,u8* STRING);

u16 USART_u16_NON_BLOCKING_RECEIVE_BYTE(USART_ID* USART);

u16 USART_u16_BLOCKING_RECEIVE_BYTE(USART_ID* USART);



#endif /* MCAL_USART_USART_INTERFACE_H_ */
