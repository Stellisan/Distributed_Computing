#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "TCB.h"

struct q_element{
	struct q_element *pPrev, *pNext;
	int iValue;
	TCB_t *TCB;
};

typedef struct q_element q_element;

struct q_element* newQueue()
{
	struct q_element *queue = NULL;
	return queue;
}

struct q_element* newItem()
{
	struct q_element *new_item = (struct q_element*)malloc(sizeof(struct q_element));
	if(new_item == NULL)
	{
		printf("Error: Failed to create the q element");
		errno = ENOMEM;
		return NULL;
	}
	new_item->pPrev = new_item;
	new_item->pNext = new_item;
	return new_item;
}

void AddQueue(struct q_element **head, struct q_element *item)
{
	struct q_element *temp = *head;
	
	if(*head == NULL)
	{
		*head = item;
		return;
	}
	
	while(temp->pNext != *head)
	{
		temp = temp->pNext;
	}

	item->pNext = *head;
	item->pPrev = temp;
	temp->pNext = item;
	(*head)->pPrev = item;
}

struct q_element* DelQueue(struct q_element **head)
{
	struct q_element *back = *head;
	struct q_element *deleted_element = *head;

	if(*head == NULL)
	{
		printf("Error: The queue is empty \n");
		errno = EPERM;
		return NULL;
	}

	if((*head)->pNext == *head)
	{
		*head = NULL;
		return deleted_element;
	}

	while(back->pNext != *head)
	{
		back = back->pNext;
	}

	*head = (*head)->pNext;
	(*head)->pPrev = back;
	back->pNext = *head;
	deleted_element->pNext = NULL;
	deleted_element->pPrev = NULL;
	return deleted_element;
}

void FreeItem(struct q_element *item)
{
	if(item != NULL)
	{
		free(item);
		item = NULL;
	}
}