#include "msgs.h"
#include<stdio.h>

int server_ctr = 0; /* Server IDs from 0 to 2 */			  
int active_port = 0;
int client_ctr = 3; /* Client IDs from 3 to 99 */

int main() {
	port_setup();
	printf("Using 3 ports for Servers\n");
	for(int i=0; i<3; i++)
		start_thread(server_side);
	printf("Using 97 ports for Clients\n");	
	for(int i=3; i<100;i++)
		start_thread(client_side);
	run();
	while(1) {
	    sleep(1);
	}
}

void server_side() {
    int msg[10];
	int id = (++server_ctr)%100;
	while(1) {
		Receive(&port_arr[id], msg);
		printf ("At Server No. : %d -> Client ID: %d sent the message\n", id, msg[0]);
		printf ("At Server No. : %d -> Doing some operations on messages", id);
		for(int i=1;i<10;i++)
			msg[i]= 2*msg[i]+1;
		printf ("\nAt Server No. : %d -> Replying to Client ID: %d\n", id, msg[0]);
		Send(&port_arr[msg[0]], msg);
		printf ("Message sent from Server to Client!\n MESSAGE \t");
		sleep(1);
	}
}

void client_side() {
	int stack_ptr;
	int msg[10];
	int id = (++client_ctr)%100;
	while(1) {
		stack_ptr = active_port;
		active_port = (active_port+1) % server_ctr;
		printf("\nClient ID: %d -> Generating message to pass to Server\n",id);
		msg[0] = id;
		for (int i=1;i<10;i++)
			msg[i] = i;
		printf("Client ID: %d -> Message generated is as follows: \n",id);	
		for (int i=0;i<10;i++)
			printf("%d\t ",msg[i]);
		printf("\nClient ID: %d -> Message being sent to Server ID: %d", id, stack_ptr);
		Send(&port_arr[stack_ptr],msg);
		printf("\nClient ID: %d -> Message sent to Server successfully", id);
		printf("\nClient ID: %d -> Attempting to receive message from Server with ID: %d", id, stack_ptr);
		Receive(&port_arr[id],msg);
		printf("\nClient ID: %d -> Message received from Server ID: %d", id, stack_ptr);
		printf("\nClient ID: %d -> The message received is as follows: \n MESSAGE \t",id,stack_ptr);
		for (int i=0; i<10; i++)
			printf("%d\t",msg[i]);
	    printf("\n\n");
	}
}