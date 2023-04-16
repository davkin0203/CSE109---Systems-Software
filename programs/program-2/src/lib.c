#include <stdio.h>
#include <stdlib.h>
#include "../include/linkedlist.h"

void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	printf("\nList: \n\n\t"); 
	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}

// Initialize an empty list
void initList(List* list_pointer){
	list_pointer->head = NULL; // head set to NULL 
	list_pointer->tail = NULL; // tail set to NULL
	return; 
}

// Create node containing item, return reference of it.
Node* createNode(void* item){
	Node* node = (Node*) malloc(sizeof(Node)); // allocating memory for a node
	if(node == NULL){ // if the new node can't be stored in memory, return NULL which means it failed
		return NULL;
	}
	node->item = item; // setting the item the node is pointer to to item
	node->next = NULL; // setting the next node equal to NULL
	return node; // returning the newly created node
}

// Insert new item at the end of list.
int insertAtTail(List* list_pointer, void* item){
	Node* node;
	if((node = (Node*) createNode(item)) == NULL){
		return 1; // could not allocate memory
	}
	// 2 different cases
	if(list_pointer->head == NULL){ // if the head pointer is NULL, aka the linkedlist is NULL
		list_pointer->head = node; // set the head of the list to the new node
		list_pointer->tail = node; // set the head of the list to the new node
	} else {
		Node* tail_node = list_pointer->head; // creating new node for the updated tail of the list
		while(tail_node->next != NULL){ // iterating through the list until it's NULL
			tail_node = (Node*) tail_node->next; // setting the tail_node to next
		}
		tail_node->next = (struct Node*) node; // setting the list tail to the new node
		list_pointer->tail = node;
	}
	return 0;
}

// Insert item at start of the list.
int insertAtHead(List* list_pointer, void* item){
	Node* node;
	if((node = (Node*) createNode(item)) == NULL){
		return 1; // could not allocate memory
	}
	// 2 cases
	if(list_pointer->head == NULL){ // if head of the list is null
		list_pointer->head = node; // then the head becomes the new node
		list_pointer->tail = node; // tail becomes the new node as well
	} else {
		node->next = (struct Node*) list_pointer->head; // setting node's next to the current head 
		list_pointer->head = node; // setting list head to the node
	}
	return 0;
}

// Insert item at a specified index.
int insertAtIndex(List* list_pointer, int index, void* item){
	Node* node;
	if((node = (Node*) createNode(item)) == NULL){
		return 1; // could not allocate memory
	}

	if(size(list_pointer) <= index || list_pointer->head == NULL || index < 0){ // if no room for node return 1 or index out of bounds
		return 1;
	}

	if(index == 0){ // if index is 0 then 2 cases
		if(list_pointer->head == NULL){ // if head is NULL then set the head to the new node
			list_pointer->head = node;
			list_pointer->tail = node;
		} else { // else just move the current head over and set head to new node
			node->next = (struct Node*) list_pointer->head;
			list_pointer->head = node;
		}
		return 0;
	}

	int currIndex = 0;
	Node* temp = list_pointer->head; // setting temp node for iterating through the list
	while((currIndex < index - 1) && temp->next != NULL){ 
		temp = (Node*) temp->next; // iterating to next val
		currIndex++; // iterating the count
	}

	node->next = temp->next; // inserting node right after the specified index, thus pushing the node in front of it
	temp->next = (struct Node*) node; 

	return 0;
}

// Remove item from the end of list and return a reference to it
void* removeTail(List* list_pointer){
	if(list_pointer->head == NULL || list_pointer == NULL){ // means it's an empty list
		return NULL;
	}else if((Node*)list_pointer->head == (Node*)list_pointer->tail){ // list head is the only element in the list
		void* ref = list_pointer->head->item; // create ref
		free(list_pointer->head); // free the head
		list_pointer->head = NULL; // set head to NULL
		list_pointer->tail = NULL; // set head to NULL
		return ref;
	}

	Node* temp = list_pointer->head;
	while((Node*)temp->next != (Node*)list_pointer->tail){ // iterate to second to last element
		temp = (Node*)temp->next; 
	}

	// temp is second to last element
	void* ref = list_pointer->tail->item; // accessing item of tail
	free(list_pointer->tail); // free up memory used by the tail
	temp->next = NULL; // setting next element of temp to NULL
	list_pointer->tail = temp; // setting temp to the list tail

	return ref;
}

// Remove item from start of list and return a reference to it
void* removeHead(List* list_pointer){
	if(list_pointer->head == NULL || list_pointer == NULL){ // if the head is NULL then return NULL
		return NULL;
	} else if(list_pointer->head->next == NULL){ // if head is only element in the list
		void* ref = list_pointer->head->item; // extract item from the head
		free(list_pointer->head); // free the head
		list_pointer->head == NULL; // set head to NULL
		list_pointer->tail == NULL; // set tail to NULL
		return ref;
	}
	
	void* ref = list_pointer->head->item; // extract item from the head
	Node* oldHead = list_pointer->head; // assign head to a new node so the new head can be assigned
	list_pointer->head = (Node*) oldHead->next; // assign the head to the next node from the oldHead
	if(list_pointer->head->next == NULL){ // if head is only node in the list
		list_pointer->tail = list_pointer->head; // set the tail equal to the head
	}
	free(oldHead); // free the oldHead

	return ref;
}

// Remove item at a specified index and return a reference to it
void* removeAtIndex(List* list_pointer, int index){
	if(index < 0 || list_pointer->head == NULL || size(list_pointer) <= index){ // out of bounds or empty
		return NULL;
	}else if(index == 0){ // if they want the head
		void* ref = list_pointer->head->item; // extract item from the head
		Node* oldHead = list_pointer->head; // create node for oldHead
		list_pointer->head = (Node*) oldHead->next; // assigned new head one node next from oldHead
		if(list_pointer->head->next == NULL){ // if head is only node in the list
			list_pointer->tail = list_pointer->head; // set the tail equal to the head
		}
		free(oldHead); // free memory from oldHead

		return ref;
	}

	int currIndex = 0;
	Node* temp = list_pointer->head; // initialize new node for temp
	while(temp->next != NULL && (currIndex < index - 1)){ // while the next node is not NULL and the currIndex is less than index minus 1
													// want index - 1 because we want the node right before the desired node
		temp = (Node*) temp->next; // iterating through the list
		currIndex++; // iterating currIndex
	}

	if(temp == NULL){ // if the index is greater than the currIndex then return NULL because out of bounds
		return NULL;
	}

	Node* tbd = (Node*) temp->next; // create new node for the one that's about to be deleted (tbd = 'to be deleted')
	void* ref = tbd->item; // extract item from the next node from tbd
	temp->next = tbd->next; // linking the nodes on either side of the deleted item
	free(tbd); // freeing memory allocated for the deleted node

	return ref;
}

// Return item at index
void* itemAtIndex(List* list_pointer, int index){
	if(index < 0 || index >= size(list_pointer) || list_pointer->head == NULL){ // if index is less than 0 return NULL because out of bounds
		return NULL;
	}

	int currIndex = 0;
	Node* temp = list_pointer->head; // creating temperory node to access the item
	while(temp->next != NULL && currIndex < index){ // iterating through the nodes and making sure not to go over index
		temp = (Node*) temp->next; // iterating to next node
		currIndex++; // iterating currIndex count
	}

	void* ref = temp->item; // accessing the item at desired index then returning it

	return ref;
}

// Return true if the list contains the given item at least once, false otherwise.
bool contains(List* list_pointer, void* item){
	if(list_pointer->head == NULL){ // empty list return NULL
		return NULL;
	}

	Node* temp = list_pointer->head; // temp node which will be the node where the value is stored
	if(temp->item == item){ // initial check for first item at the head
		return true;
	}
	while(temp->next != NULL){ // iterating through the nodes
		temp = (Node*) temp->next; // goes to next node
		if(temp->item == item){ // if the item is equal return truee
			return true;
		}
	}

	return false;
}

// Returns the size of the list, measured in nodes.
int size(List* list_pointer){
	int size = 0; // intializing counter
	if(list_pointer->head == NULL || list_pointer == NULL){ // empty list
		return 0;
	}

	Node* temp = list_pointer->head; // temp node which is used to iterate through the list
	if(temp != NULL){ // if the head is not NULL iterate size
		size++;
	}
	while(temp->next != NULL){ // while the node is not NULL
		temp = (Node*)temp->next; // going to next node
		size++; // iterating size variable
	}

	return size;
}

// Print List
void printList(List* list_pointer);
