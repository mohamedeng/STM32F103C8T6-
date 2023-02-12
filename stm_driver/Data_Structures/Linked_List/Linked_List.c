/*
 * Linked_List.c
 *
 *  Created on: Jan 22, 2023
 *      Author: mohamed mahmoud abdo
 */

#include "LIB/STD_TYPES.h"
#include "Linked_List.h"

void Linked_List_Struct_init(Linked_List_Struct* Linked_List, Types Data_Type);

void Linked_List_Struct_AddToTheTail(Linked_List_Struct* Linked_List,void* Ptr_Data);

void Linked_List_Struct_AddToTheHead(Linked_List_Struct* Linked_List,void* Ptr_Data);

void* Linked_List_Struct_Getdata(Linked_List_Struct* Linked_List,u16 index);

void Linked_List_Struct_Setdata(Linked_List_Struct* Linked_List,u16 index, void* Ptr_New_DataValue);



