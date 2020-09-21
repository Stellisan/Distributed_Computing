#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
*/

semaphore_t rlock,wlock; // Semaphores for read and write
int wc = 0; // Count for writing thread

/*
* Function Name: enter_write
* Parameters: None
* Return type: Void
* Description: Function to lock the critical region of the thread function
*/
void enter_write()
{
	P(&wlock);
	wc++;
	printf("Thread %d started\t",wc);
}

/*
* Function Name: exit_write
* Parameters: None
* Return type: Void
* Description: Checks if all the three threads have completed incrementing
* the array values and then unlocking the read function in main thread
*/
void exit_write()
{
	printf("Thread %d exiting\n",wc);
	if(wc == 3)
	{
		V(&rlock);
		wc = 0;
	}
	V(&wlock);
}

/*
* Function Name: write_array
* Parameters: int *a -- pointer to the array element
* Return type: Void
* Description: Thread function to increment the element in the array
*/
void write_array(int *a)
{
	int ID;

	while(1){
		enter_write();
		*a = *a+1;			
		exit_write();
		sleep(1);
  	}
}

void main()
{
	int a[3] = {0, 0, 0}; // Initializing array of shared variables
	
	init_sem(&wlock,1); // Write lock
	init_sem(&rlock,0); // Read Lock

	start_thread(write_array,a); // Creating thread_1
	start_thread(write_array,a+1); // Creating thread_2
	start_thread(write_array,a+2); // Creating thread_3

	printf("\n");

	while(1){
		P(&rlock);
		printf("Reader Entry");
		printf("\n\nFrom Main Thread:\na[0] = %d, a[1] = %d, a[2] = %d\n\n",a[0],a[1],a[2]);
		printf("Reader Exit\n\n");
	}
}

