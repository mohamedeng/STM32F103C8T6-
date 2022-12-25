/*
 * SEVEN_SEG.c
 *
 *  Created on: Aug 7, 2022
 *      Author: hp
 */

#include "SEVEN_SEG.h"

SEVENSEG_ID SEVENSEG_SEVENSEG_ID_INIT(GPIO_ID* GPIO_PORT,u8* SEVENSEG_PINS,SEVENSEG_TYPE_ID SEVENSEG_TYPE)
{
  // must be array of 9 first 8 is a,b,c,d,e,f,g,cp the nine is controlpin

  for(int i = 0; i<8;i++)
  {
	  GPIO_void_PIN_MODE(GPIO_PORT,SEVENSEG_PINS[i],GPIO_OUTPUT_PUSHPULL);

    }

  SEVENSEG_ID SEVENSEG = {GPIO_PORT,SEVENSEG_PINS,SEVENSEG_TYPE};

  return SEVENSEG;
 }


void SEVENSEG_void_WRITE(SEVENSEG_ID* SEVENSEG,u8 number)
{
  if (number >9 || number < 0)
	  return ;

  u8 bit_to_Write;

  const u8 digits[] = {
    //gfedcba
    0b0111111,  // 0
    0b0000110,  // 1
    0b1011011,  // 2
    0b1001111,  // 3
    0b1100110,  // 4
    0b1101101,  // 5
    0b1111101,  // 6
    0b0100111,  // 7
    0b1111111,  // 8
    0b1101111   // 9
  };

  if(SEVENSEG->SEVENSEG_TYPE)
  {
	  GPIO_void_PIN_WRITE(SEVENSEG->SEVENSEG_GPIO_PORT, SEVENSEG->SEVENSEG_PINS[8], GPIO_HIGH_VALUE);

  for(int i = 0 ;i< 8 ; i++)
  {
    bit_to_Write = (~(digits[number]>>i)&1);

    GPIO_void_PIN_WRITE(SEVENSEG->SEVENSEG_GPIO_PORT, SEVENSEG->SEVENSEG_PINS[i], bit_to_Write);
    }


    }
   else
   {

	   GPIO_void_PIN_WRITE(SEVENSEG->SEVENSEG_GPIO_PORT, SEVENSEG->SEVENSEG_PINS[8], GPIO_LOW_VALUE);

  for(int i = 0 ;i< 8 ; i++)
	   {
		bit_to_Write = ((digits[number]>>i)&1);

		GPIO_void_PIN_WRITE(SEVENSEG->SEVENSEG_GPIO_PORT, SEVENSEG->SEVENSEG_PINS[i], bit_to_Write);
		}

    }

  }

