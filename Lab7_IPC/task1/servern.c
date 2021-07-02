/*
 * server.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/server_queue"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660

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
    key_t client_queue_key;
    int qid;
    struct message message;
    int Id[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;

    if ((client_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }  

    if ((qid = msgget (client_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror ("msgget");
        exit (1);
    }

    printf ("Server: now I'm Running\n");
    
     printf ("Waiting for connections.....\n\n");

    while (1) {
        // read the incoming message
        if (msgrcv (qid, &message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("msgrcv"); //raising the error
            exit (1);
        }
        
        if (!strcmp(message.message_text.buf, "Connection")){	
			printf("%d Connected\n", message.message_text.qid);
			
			Id[i] = message.message_text.qid;
			i++;
			
			int client_qid = message.message_text.qid;
			message.message_text.qid = qid;
			
			if (msgsnd (client_qid, &message, sizeof (struct message_text), 0) == -1) {  
				perror ("msgget");
				exit (1);
			}
		} else {
		
			//Here we receive the messague
			printf ("Server: message received from. %d\n", message.message_text.qid);
				
			int client_qid = message.message_text.qid;
			message.message_text.qid = qid;
			
			for (int j = 0; Id[j] != -1; j++) {
				if (Id[j] != client_qid) {
					if (msgsnd (Id[j], &message, sizeof (struct message_text), 0) == -1) {  
						perror ("msgget");
						exit (1);
					 }	
				}   
					
			}	
		
			printf ("Server: response sent to clients.\n");
		}
		 
    }
}

