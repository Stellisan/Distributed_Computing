#include "q.h"

TCB_t* ReadyQ = NULL;
TCB_t* Curr_Thread;
int thread_counter = 0;

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

void run()

{	// real code
	Curr_Thread = DelQueue(&ReadyQ);
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

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