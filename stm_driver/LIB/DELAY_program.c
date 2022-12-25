#include "DELAY.h"

void Delay_ms (u32 delay_value)
{
	for(u32 i = 0 ; i<1000*delay_value ; i++ ) asm("NOP");
}
