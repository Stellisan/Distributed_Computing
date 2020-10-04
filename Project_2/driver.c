#include "q.h"

int main()
{
	struct q_element *head;
	printf("Creating a new q\n");
	head = newQueue();
	printf("Adding a new item with value 1\n");
	struct q_element *item = newItem();
	item->iValue = 1;
	AddQueue(&head, item);
	item = newItem();
	printf("Adding a new item with value 2\n");
	item->iValue = 2;
	AddQueue(&head, item);
	item = DelQueue(&head);
	printf("Deleted_Value = %d\n",item->iValue);
	FreeItem(item);
	item = DelQueue(&head);
	printf("Deleted_Value = %d\n",item->iValue);
	FreeItem(item);
	item = DelQueue(&head);
	FreeItem(item);
	if(item == NULL)
		printf("No elements\n");
	return 1;
}