#include "threads.h"
#include <unistd.h>

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
*/

int global = 0;

void fun1()
{
	while(1)
	{
		printf("Function 1.... global = %d\n\n",++global);
		sleep(1);
		yield();
	}
}

void fun2()
{
	while(1)
	{
		printf("Function 2.... global = %d\n\n",++global);
		sleep(1);
		yield();
	}
}

void fun3()
{
	while(1)
	{
		printf("Function 3.... global = %d\n\n",++global);
		sleep(1);
		yield();
	}
}

int main(void)
{
	start_thread(fun1);
	start_thread(fun3);
	start_thread(fun2);
	run();
	return 1;
}
