#include "TCB.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
* Used init_TCB() function as given by Dr. Dasgupta in Project 2 Instructions
*/

/*
* Function Name: init_queue
* Parameters: TCB_t **head
* Return type: void
* Description: Function to return a initialize queue of TCB_t's
*/
void init_queue(TCB_t **head) {
	*head = NULL;
}

/*
* Function Name: add_queue
* Parameters: TCB_t **head, TCB_t *item
* Return type: void
* Description: Function to add an element to queue
*/
void add_queue(TCB_t **head, TCB_t *item) {
	if(*head == NULL) {
		*head = item;
		(*head) -> next = *head;
		(*head) -> prev = *head;
		
	} else {
		(*head)->prev->next = item;
		item->prev = (*head)->prev;
		(*head)->prev = item;
		item->next = *head;
	}
}

/*
* Function Name: delete_queue
* Parameters: TCB_t **head
* Return type: TCB_t *
* Description: Function to delete an element from queue, and return deleted element
*/
TCB_t * delete_queue(TCB_t **head) {
	TCB_t *deleted_element = *head;
	if((*head) == NULL) {
		return NULL;
	}
	if((*head) -> next == *head) {
		*head = NULL;
	} else {
		*head = (*head) -> next;
		deleted_element -> prev -> next = *head;
		(*head) -> prev = deleted_element -> prev;
	}
	return deleted_element;
}
