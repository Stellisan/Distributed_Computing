#include "q.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
* Used init_TCB() function as given by Dr. Dasgupta in Project 2 Instructions
*/

TCB_t *ready_queue = NULL;
TCB_t *this_thread = NULL;
const int STACK_SIZE = 8192;
int ctr = 0;

/*
* Function Name: start_thread
* Parameters: void(*function)(void)
* Return type: void
*/
void start_thread (void(*function)(void)) {
	void *stack =  malloc(STACK_SIZE);
	TCB_t *tcb =  malloc(sizeof(TCB_t));
	init_TCB (tcb, function, stack, STACK_SIZE);
	tcb->thread_id = ++ctr;
	printf("\nThread ID of new initialized thread:\t%d\n", tcb -> thread_id);
	add_queue (&ready_queue, tcb);
}

/*
* Function Name: run
* Parameters: No parameters
* Return type: void
*/
void run() {
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(ready_queue -> context));
}

/*
* Function Name: yield
* Parameters: No parameters
* Return type: void
*/
void yield() {
  	this_thread = delete_queue(&ready_queue);
  	add_queue(&ready_queue, this_thread);
  	swapcontext(&(this_thread -> context), &(ready_queue -> context));
	printf ("\nAfter yield(), thread ID:\t%d\n", this_thread -> thread_id);
}