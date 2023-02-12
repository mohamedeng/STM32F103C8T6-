/*
 * Stack.h
 *
 *  Created on: Jan 22, 2023
 *      Author: hp
 */

#ifndef DATA_STRUCTURES_STACK_STACK_H_
#define DATA_STRUCTURES_STACK_STACK_H_

#include "LIB/STD_TYPES.h"

typedef struct
{
	u64 index;
	u64 max_size;
	void* Ptr_Array;
	Types Data_Type;


}Stack_Struct;

void  Stack_Struct_init(Stack_Struct* Stack,u32 Stack_Size,Types Data_Type);
void Stack_Struct_Push(Stack_Struct* Stack,void* Ptr_Element);
void Stack_Struct_GetLast(Stack_Struct* Stack,void* Ptr_ElementHolder);

void Stack_Struct_Pull(Stack_Struct* Stack);
void Stack_Struct_Free(Stack_Struct* Stack);
void Stack_Struct_Flush(Stack_Struct* Stack);


#endif /* DATA_STRUCTURES_STACK_STACK_H_ */
