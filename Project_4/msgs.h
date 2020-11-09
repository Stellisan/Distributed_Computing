#include "sem.h"

typedef struct port_struct{
	int start, end;
	int msg_handler [10][10];
	semaphore_t mutex, full, empty;
}port_struct;

port_struct port_arr[100];

void port_setup() {
    int index=0;
	while(index<=100){
	    port_arr[index].full = *CreateSem(0);
		port_arr[index].empty = *CreateSem(10);
		port_arr[index].mutex = *CreateSem(1);
		port_arr[index].start = 0;
		port_arr[index].end = 0;
        index++;
	}
}

void Receive(port_struct *port_arr, int *msg) {
	P(&(port_arr->full));
	P(&(port_arr->mutex));
	int index = 0;
    while(index<=100){
		msg[index]= port_arr->msg_handler[port_arr->end][index];
		index++;
	}
	port_arr->end = ++(port_arr->end);
	port_arr->end = (port_arr->end)%10;
	V(&(port_arr->mutex));
	V(&(port_arr->empty));
}

void Send(port_struct *port_arr, int *msg) {
	P(&(port_arr->empty));
	P(&(port_arr->mutex));
	int index = 0;
	while(index<10) {
	    port_arr->msg_handler[port_arr->start][index] = msg[index];
	    index++;
	}
	port_arr->start = ++(port_arr->start);
	port_arr->start = (port_arr->start)%10;
	V(&(port_arr->mutex));
	V(&(port_arr->full));
}