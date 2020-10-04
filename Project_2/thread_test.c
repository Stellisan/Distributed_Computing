#include "threads.h"
#include <unistd.h>

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