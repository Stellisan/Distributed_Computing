#include <stdio.h>
#include <stdlib.h>
#include "monitor.h"

monitor_t rw_lock;
monitor_cond_t r_cond, w_cond;

int  rwc = 0, wc = 0, wwc = 0, rc = 0, global_ID = 0;

void reader_entry()
{
	monitor_entry(&rw_lock);
	if (wc > 0 || wwc > 0) {
	    rwc++;
            monitor_wait(&rw_lock, &r_cond);
	    rwc--;	
	}
	rc++;
	monitor_exit(&rw_lock);
}

void reader_exit()
{
	monitor_entry(&rw_lock);
	rc--;
	while(wwc > 0)
	{
		monitor_signal(&rw_lock, &w_cond);
		wwc--;
	}
	monitor_exit(&rw_lock);
}

void writer_entry()
{
	monitor_entry(&rw_lock);
	if (rc > 0) {
	    wwc++;
            monitor_wait(&rw_lock, &w_cond);
	    wwc--;		
	}
	wc++;
        monitor_exit(&rw_lock);
}

void writer_exit()
{
	monitor_entry(&rw_lock);
	wc--;
	if (wc == 0) {
		monitor_signal(&rw_lock, &r_cond);
	}
        monitor_exit(&rw_lock);
}

void write_array(int *a)
{
	int ID;
	monitor_entry(&rw_lock); ID = global_ID++; monitor_exit(&rw_lock);
	while(1){
		writer_entry();
		printf("In thread %d	",ID);
		*a = *a+1;	
		sleep(1);		
		writer_exit();
		sleep(1);
  	}
}

void main()
{
	int a[3] = {0, 0, 0};
	int idx = 0;
	
	init_monitor(&rw_lock);
	init_monitor_cond(&r_cond);
	init_monitor_cond(&w_cond);

	start_thread(write_array,a);
	idx++;
	start_thread(write_array,a+1);
	idx++;
	start_thread(write_array,a+2);

	printf("\n");

	while(1){
		reader_entry();
		printf("\n\nFrom Main Thread:\na[0] = %d, a[1] = %d, a[2] = %d\n\n",a[0],a[1],a[2]);
		reader_exit();
		sleep(2);
	}
}