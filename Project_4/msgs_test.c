#define GNU_SOURCE
#include <unistd.h>
#include "msgs.h"
#include <stdio.h>

/*
* Group members: 
* 1. Sanjay Arivazhagan; ASURITE ID: 1217643921; sarivazh@asu.edu 
* 2. Sethu Manickam; ASURITE ID: 1218452066; smanick4@asu.edu
*/

int server_ctr = 0; /* Server IDs from 0 to 2 */			  
int active_port = 0;
int client_ctr = 3; /* Client IDs from 3 to 99 */

/*
*  Function Name: server_side
*  Parameters: None
*  Return: Void
*  Description: Thread function for servers. It will check
*		if any client has sent a message and the message is changed
*		and sent back to the client.
*/
void server_side() {
	int msg[10];
	int id = (++server_ctr)%100;

	while(1) {		
		printf("\n-----------------------------------------------------------------------------------\n");

		Receive(&port_arr[id], msg);
		printf ("At Server No. : %d -> Client ID: %d sent the message\n", id, msg[0]);

		printf ("At Server No. : %d -> Doubling and Increment the values in the message", id);
		for(int i=1;i<10;i++)
			msg[i]= 2*msg[i]+1;

		printf ("\nAt Server No. : %d -> Replying to Client ID: %d\n", id, msg[0]);
		Send(&port_arr[msg[0]], msg);
		printf ("Message sent from Server to Client!\n MESSAGE \t");

		printf("\n-----------------------------------------------------------------------------------\n\n");

		sleep(3);
	}
}

/*
*  Function Name: client_side
*  Parameters: None
*  Return: Void
*  Description: Thread function for clients. It will generate a message.
*		The message will be sent to the server and then it will recieve
*		the changed message from the server.
*/ 
void client_side() {
	int stack_ptr;
	int msg[10];
	int id = (++client_ctr)%100;

	while(1) {
		stack_ptr = active_port;
		active_port = (active_port+1) % server_ctr;

	    	printf("\n-----------------------------------------------------------------------------------\n");

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

	    	printf("\n-----------------------------------------------------------------------------------\n\n");
		sleep(2);
	}
}

// Main function
int main() {
	port_setup();

	printf("\n-----------------------------------------------------------------------------------\n\n");
	printf("Using 3 ports for Servers\n");
	for(int i=0; i<3; i++)
		start_thread(server_side);

	printf("Using 97 ports for Clients\n");	
	for(int i=3; i<100;i++)
		start_thread(client_side);

	printf("\n-----------------------------------------------------------------------------------\n\n");
	
	run();

	while(1) {
	    sleep(10);
	}
}
