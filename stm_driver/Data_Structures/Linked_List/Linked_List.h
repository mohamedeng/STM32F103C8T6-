/*
 * Linked_List.h
 *
 *  Created on: Jan 22, 2023
 *      Author: Mohamed Mahmoud Abdo
 */

#ifndef DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_H_
#define DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_H_


typedef struct Linked_ListNode{

	void* Ptr_value;
	struct Linked_ListNode* Ptr_node;


}Linked_ListNode;



typedef struct {

	Linked_ListNode HeadOfLinkedList;
	Linked_ListNode TailOfLinkedList;
	u64 SizeOfList;
	Types Data_Type;
}Linked_List_Struct;

void Linked_List_Struct_init(Linked_List_Struct* Linked_List, Types Data_Type);

void Linked_List_Struct_AddToTheTail(Linked_List_Struct* Linked_List,void* Ptr_Data);

void Linked_List_Struct_AddToTheHead(Linked_List_Struct* Linked_List,void* Ptr_Data);

void* Linked_List_Struct_Getdata(Linked_List_Struct* Linked_List,u16 index);

void Linked_List_Struct_Setdata(Linked_List_Struct* Linked_List,u16 index, void* Ptr_New_DataValue);



#endif /* DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_H_ */
