/*
 * KEY_PAD.c
 *
 * Created: 7/24/2022 6:56:33 AM
 *  Author: mohamed mahmoud abdo
 */
#include "KEY_PAD.h"

KEYPAD_ID KEYPAD_KEYPAD_ID_INIT(GPIO_ID* PORT_adress_coloms,u8* pin_coloms,GPIO_ID* PORT_adress_rows,u8* pin_rows ,u8 num_coloms,u8 num_rows,u8 key_pad_array[num_coloms][num_rows])
{

	for (int i=0;i<num_coloms;i++)
	{
		GPIO_void_PIN_MODE(PORT_adress_coloms,pin_coloms[i],GPIO_INPUT_PULLDOWN);
	}

	for (int i = 0;i<num_rows;i++)
	{

		GPIO_void_PIN_MODE(PORT_adress_rows,pin_rows[i],GPIO_OUTPUT_PUSHPULL);

	}

	KEYPAD_ID KEYPAD = {PORT_adress_coloms,PORT_adress_rows,pin_coloms,pin_rows,num_coloms,num_rows,(u8*)key_pad_array};
	
	
	return KEYPAD;
}

u8 KEYPAD_u8_GET_INPUT(KEYPAD_ID* KEYPAD)
{
	u8 pressed_key = 0;

	u8 value =0;

	for (int i = 0;i<KEYPAD->num_row;i++)
	{
		
		GPIO_void_PIN_WRITE(KEYPAD->PORT_adress_rows, KEYPAD->pin_rows[i], GPIO_HIGH_VALUE);

		for (int k = 0;k<KEYPAD->num_colom;k++)
		{
			value = GPIO_u8_PIN_READ(KEYPAD->PORT_adress_coloms,KEYPAD->pin_coloms[k]);

			if (value != 0)
			{
					pressed_key = KEYPAD->key_pad_array[k * KEYPAD->num_colom + i];
					
			}
		
						
		}

		GPIO_void_PIN_WRITE(KEYPAD->PORT_adress_rows,KEYPAD->pin_rows[i] ,GPIO_LOW_VALUE);
	}

	return pressed_key;
	

	
}
	
void KEYPAD_GETSTR(KEYPAD_ID* KEYPAD,u8* str)
{
	str[0] = KEYPAD_u8_GET_INPUT(KEYPAD);
}


/* example code


u8 pin_colom[4] = {0,1,2,3};
u8 pin_row[4] = {4,5,6,7};


	u8 pad_array [4][4]= {
			{'1','2','3','A'},
			{'4','5','6','B'},
			{'7','8','9','C'},
			{'*','0','#','D'}
	};

KEYPAD_ID KEYPAD = KEYPAD_KEYPAD_ID_INIT(GPIOA_REGS, pin_colom, GPIOA_REGS, pin_row, 4, 4, pad_array);



*/
