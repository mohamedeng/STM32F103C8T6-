


#include "Stack.h"


void  Stack_Struct_init(Stack_Struct* Stack,u32 Stack_Size,Types Data_Type)
{
	if(Stack_Size == 0)
	{
		return ;
	}
	switch(Data_Type)
	{
	case u8_Type:

		Stack->Ptr_Array = malloc( sizeof(u8) * Stack_Size );
		break;

	case u16_Type:
		Stack->Ptr_Array = malloc( sizeof( u16 ) * Stack_Size );
		break;

	case u32_Type:
		Stack->Ptr_Array = malloc( sizeof( u32 ) * Stack_Size);
		break;

	case u64_Type:
		Stack->Ptr_Array = malloc( sizeof( u64 ) * Stack_Size);
		break;

	case s8_Type:
		Stack->Ptr_Array = malloc( sizeof( s8 ) * Stack_Size);
		break;

	case s16_Type:
		Stack->Ptr_Array = malloc( sizeof( s16 ) * Stack_Size);
		break;

	case s32_Type:
		Stack->Ptr_Array = malloc( sizeof( s32 ) * Stack_Size);
		break;

	case s64_Type:
		Stack->Ptr_Array = malloc( sizeof( 64 ) * Stack_Size);
		break;

	case f32_Type:
		Stack->Ptr_Array = malloc( sizeof( f32 ) * Stack_Size);
		break;

	case d64_Type:
		Stack->Ptr_Array = malloc( sizeof( d64 ) * Stack_Size);
		break;

	}

	Stack->Data_Type = Data_Type;
	Stack->max_size = Stack_Size;
	Stack->index = 0;

}


void Stack_Struct_Push(Stack_Struct* Stack,void* Ptr_Element)
{
	if(Stack->index == Stack->max_size) // the Stack is full
	{
		return ;
	}

	switch(Stack->Data_Type)
	{
	case u8_Type:

		((u8*)Stack->Ptr_Array)[Stack->index] = *((u8*)Ptr_Element);
		break;

	case u16_Type:
		((u16*)Stack->Ptr_Array)[Stack->index] = *((u16*)Ptr_Element);
		break;



	case u32_Type:
		((u32*)Stack->Ptr_Array)[Stack->index] = *((u32*)Ptr_Element);
		break;

	case u64_Type:
		((u64*)Stack->Ptr_Array)[Stack->index] = *((u64*)Ptr_Element);
		break;

	case s8_Type:
		((s8*)Stack->Ptr_Array)[Stack->index] = *((s8*)Ptr_Element);
		break;

	case s16_Type:
		((s16*)Stack->Ptr_Array)[Stack->index] = *((s16*)Ptr_Element);
		break;

	case s32_Type:
		((s32*)Stack->Ptr_Array)[Stack->index] = *((s32*)Ptr_Element);
		break;

	case s64_Type:
		((s64*)Stack->Ptr_Array)[Stack->index] = *((s64*)Ptr_Element);
		break;

	case f32_Type:
		((f32*)Stack->Ptr_Array)[Stack->index] = *((f32*)Ptr_Element);
		break;

	case d64_Type:
		((d64*)Stack->Ptr_Array)[Stack->index] = *((d64*)Ptr_Element);
		break;

	}

	Stack->index++;


}
void Stack_Struct_Pull(Stack_Struct* Stack)
{
	if(Stack->index == 0) // stack is empty
	{
		return ;
	}
	Stack->index--;

}

void Stack_Struct_GetLast(Stack_Struct* Stack,void* Ptr_ElementHolder)
{

	switch(Stack->Data_Type)
	{
	case u8_Type:

		Ptr_ElementHolder = ((u8*)Stack->Ptr_Array)+Stack->index;
		break;

	case u16_Type:
		Ptr_ElementHolder = ((u16*)Stack->Ptr_Array)+Stack->index;
		break;



	case u32_Type:
		Ptr_ElementHolder = ((u32*)Stack->Ptr_Array)+Stack->index;
		break;

	case u64_Type:
		Ptr_ElementHolder = ((u64*)Stack->Ptr_Array)+Stack->index;
		break;

	case s8_Type:
		Ptr_ElementHolder = ((s8*)Stack->Ptr_Array)+Stack->index;
		break;

	case s16_Type:
		Ptr_ElementHolder = ((s16*)Stack->Ptr_Array)+Stack->index;
		break;

	case s32_Type:
		Ptr_ElementHolder = ((s32*)Stack->Ptr_Array)+Stack->index;
		break;

	case s64_Type:
		Ptr_ElementHolder = ((s64*)Stack->Ptr_Array)+Stack->index;
		break;

	case f32_Type:
		Ptr_ElementHolder = ((f32*)Stack->Ptr_Array)+Stack->index;
		break;

	case d64_Type:
		Ptr_ElementHolder = ((d64*)Stack->Ptr_Array)+Stack->index;
		break;

	}



}

void Stack_Struct_Free(Stack_Struct* Stack)
{

	free(Stack->Ptr_Array);


}

void Stack_Struct_Flush(Stack_Struct* Stack)
{
	Stack->index = 0;

}



