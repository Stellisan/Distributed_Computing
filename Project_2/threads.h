#include "q.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
*/

TCB_t* ReadyQ = NULL;
TCB_t* Curr_Thread;
int thread_counter = 0;

/*
* Function Name: start_thread
* Parameters: *function
* Return type: void
* Description: Function to initialize queue of TCB_ts
*/
void start_thread(void (*function)(void))
{
	void *stack = malloc(8192);
	TCB_t* item = newItem();
	if(ReadyQ == NULL)
		ReadyQ = newQueue();
	init_TCB(item, function, stack, 8192);
	item->thread_id = ++thread_counter;
	AddQueue(&ReadyQ, item);
}

/*
* Function Name: run
* Parameters: None
* Return type: void
* Description: Function to run the threads, get and switch context
*/
void run()
{	// real code
	Curr_Thread = DelQueue(&ReadyQ);
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

/*
* Function Name: yield
* Parameters: None
* Return type: void
* Description: Function to push and pop threads and switch context
*/
void yield()
{
	TCB_t* Prev_Thread;
	TCB_t* item = newItem();
	item = Curr_Thread;
	AddQueue(&ReadyQ, item);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(&ReadyQ);
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}
