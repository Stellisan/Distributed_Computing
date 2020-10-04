#include "q.h"

q_element* ReadyQ = NULL;
TCB_t* Curr_Thread;
int thread_counter = 0;

void start_thread(void (*function)(void))
{
	void *stack = malloc(8192);

	if(ReadyQ == NULL)
		ReadyQ = newQueue();

	TCB_t* c = (TCB_t*)malloc(sizeof(TCB_t));
	init_TCB(c, function, stack, 8192);
	c->thread_id = ++thread_counter;
	q_element* item = newItem();
	item->TCB = c;
	AddQueue(&ReadyQ, item);
}

void run()

{	// real code
	Curr_Thread = DelQueue(&ReadyQ)->TCB;
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield()
{
	TCB_t* Prev_Thread;
	q_element* item = newItem();
	item->TCB = Curr_Thread;
	AddQueue(&ReadyQ, item);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(&ReadyQ)->TCB;
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}