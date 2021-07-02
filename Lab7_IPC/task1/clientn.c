 /*
 * client.c
 * 
 * Copyright 2021 rufino <rufino@rufino>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/*
 * client.c: Client program
 *           to demonstrate interprocess commnuication
 *           with System V message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/server_queue"
#define PROJECT_ID 'M'

struct message_text {
    int qid;
    char buf [200];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv)
{
    key_t server_queue_key;
    int server_qid, myqid;
    int id;
    struct message my_message, return_message;
    
    printf("Enter an id for the Client: ");  
    
    // reads and stores input
    scanf("%d", &id);


    // create my client queue for receiving messages from server
    if ((myqid = msgget (IPC_PRIVATE, 0660)) == -1) {
        perror ("msgget: myqid");
        exit (1);
    }

    if ((server_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((server_qid = msgget (server_queue_key, 0)) == -1) {
        perror ("msgget: server_qid");
        exit (1);
    }

    my_message.message_type = 1;
    my_message.message_text.qid = myqid;
    
    strcpy(my_message.message_text.buf, "Connection");
    
    if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1){
		perror ("client: error in connection");
		exit (1);
	}
    
    switch (fork()) {
		case -1 :
			perror("pipe");
			exit(1);
		case 0: 
			printf("\nThe client %d has written\n\n", id);
			while (fgets (my_message.message_text.buf, 198, stdin)) {
				
				// remove newline from string
				int length = strlen (my_message.message_text.buf);
				
				if (my_message.message_text.buf [length - 1] == '\n')
					my_message.message_text.buf [length - 1] = '\0';
					
				// send message to server
				if (msgsnd (server_qid, &my_message, sizeof (struct message_text), 0) == -1){
					perror ("client: msgsnd");
					exit (1);
				}
			}
			exit(0);
		default:
			do {
				// read response from server
				if (msgrcv (myqid, &return_message, sizeof (struct message_text), 0, IPC_NOWAIT) != -1) {
					printf("%s\n", return_message.message_text.buf);
				}
			} while (1);
			wait(0);
		
	}
	
    printf ("Client: bye\n");

	return 0;
}
