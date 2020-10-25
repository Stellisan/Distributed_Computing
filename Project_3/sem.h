#include "threads.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
* Used init_TCB() function as given by Dr. Dasgupta in Project 2 Instructions
*/

Semaphore_t* CreateSem(int InputValue) {
 	semaphore_t *sem = malloc(sizeof(semaphore_t));
 	sem -> count = InputValue;
 	sem -> sem_queue = NULL;
 	return sem;
}

void P(Semaphore_t * sem) {
	sem -> --counter;
	if(sem -> counter < 0) {
		TCB_t* this_thread = delete_queue(&ready_queue);
		AddQ(&(sem -> sem_queue), this_thread);
		swapcontext(&(sem -> sem_queue -> prev -> context), &(ready_queue->context));
	}
}

void V(Semaphore_t * sem) {
	sem -> ++counter;
	if(sem -> counter <= 0) {
	 	AddQ(&ready_queue, delete_queue(&(sem -> sem_queue)));
	}
	yield();
}

typedef struct Semaphore_t {
 	int counter;
 	TCB_t *sem_queue;
} semaphore_t;