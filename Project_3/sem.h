#include "threads.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
* Used init_TCB() function as given by Dr. Dasgupta in Project 2 Instructions
*/
typedef struct Semaphore_t {
 	int count;
 	TCB_t *sem_queue;
} semaphore_t;

/*
* Function Name: CreateSem
* Parameters: int InputValue
* Return type: semaphore_t*
* Description: Creates the semaphore and initializes the struct and returns it.
*/
semaphore_t* CreateSem(int InputValue) {
 	semaphore_t *sem = malloc(sizeof(semaphore_t));
 	sem -> count = InputValue;
 	sem -> sem_queue = NULL;
 	return sem;
}

/*
* Function Name: P
* Parameters: semaphore_t * sem
* Return type: void
* Description: Decrements count.
*/
void P(semaphore_t * sem) {
	--(sem -> count);
	if(sem -> count < 0) {
		TCB_t* this_thread = delete_queue(&ready_queue);
		add_queue(&(sem -> sem_queue), this_thread);
		swapcontext(&(sem -> sem_queue -> prev -> context), &(ready_queue->context));
	}
}

/*
* Function Name: V
* Parameters: semaphore_t * sem
* Return type: void
* Description: Increments count.
*/
void V(semaphore_t * sem) {
	++(sem->count);
	if(sem -> count <= 0) {
	 	add_queue(&ready_queue, delete_queue(&(sem -> sem_queue)));
	}
	yield();
}
