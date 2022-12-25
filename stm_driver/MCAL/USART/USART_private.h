/*
 * USART_private.h
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */

#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_


#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#define TC 6


#define USART_MAX_BLOUCKING_TIME 200

#define RXNE 5

#define USART_Word_length_BIT 12
#define USART_Word_length 8
#define PCE 10
#define PS 9

#define UE 13
#define OVER8 16

#define USART_TE_BIT 3
#define USART_RE_BIT 2

#define USART_STOPBIT_BIT 12

typedef enum {USART_Parity_EVEN ,USART_Parity_ODD}Parity_selection_ID;
typedef enum {USART_TX,USART_RX,USART_TX_RX}USART_TransferDirection_ID;
typedef enum {USART_Parity_Disable,USART_Parity_Enable}USART_Parity_CONTROL_ID;
typedef enum{USART_OVER_SAMPLE_16,USART_OVER_SAMPLE_8}USART_OVER_SAMPLE_ID;


#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((u32)((((u64)(_PCLK_))*25U)/(4U*((u64)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((u32)((((u64)(_PCLK_))*25U)/(2U*((u64)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U) + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))




typedef struct {

	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;

	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;

	u32 USART_GTPR;

} USART_ID;


#define USART1_REGS ((USART_ID*)(0x40011000))
#define USART2_REGS ((USART_ID*)(0x40004400))

#define USART6_REGS ((USART_ID*)(0x40011400))





#endif /* MCAL_USART_USART_PRIVATE_H_ */
