/*
 * KEY_PAD.h
 *
 * Created: 7/24/2022 6:56:22 AM
 *  Author: mohamed mahmoud abdo
 */ 


#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#include <stdlib.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STM_CONFIG.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/GPIO/GPIO_private.h"



typedef struct {
	GPIO_ID* PORT_adress_coloms;
	GPIO_ID* PORT_adress_rows;
	u8* pin_coloms;
	u8* pin_rows ;
	u8 num_colom;
	u8 num_row;
	u8* key_pad_array;

	
	
	
	}KEYPAD_ID;
	
/*
input example:

{
	{0,1,2},
	{3,4,5},
	{6,7,8},
	{9,10,11},
}

*/	
	
	
KEYPAD_ID KEYPAD_KEYPAD_ID_INIT(GPIO_ID* PORT_adress_coloms,u8* pin_coloms,GPIO_ID* PORT_adress_rows,u8* pin_rows ,u8 num_coloms,u8 num_rows,u8 key_pad_array[num_coloms][num_rows]);

u8 KEYPAD_u8_GET_INPUT(KEYPAD_ID* KEYPAD);
void KEYPAD_GETSTR(KEYPAD_ID* KEYPAD,u8* str);


#endif /* KEY_PAD_H_ */
