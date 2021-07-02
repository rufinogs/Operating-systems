#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int x=0;
void fun_handler(int signo){
    printf("Signal Sigusr2 received\n");
    printf("You received %d\n",x);
    printf("SIGNALS SIGUSR1");
}

void sighand(int signo)
{
    printf("Signal sigusr1 received");
    x=x+1;
}


int main(int argc, char *argv[])
{
    struct sigaction info, newhandler;
    newhandler.sa_handler=&sighand;
    sigemptyset(&(newhandler.sa_mask));
    newhandler.sa_flags=0;
    sigaction(SIGUSR1,&newhandler,&info);

    struct sigaction info2, newhandler2;
    newhandler2.sa_handler=&fun_handler;
    sigemptyset(&(newhandler2.sa_mask));
    newhandler2.sa_flags=0;
    sigaction(SIGUSR2,&newhandler2,&info2);


    while(1){
        printf("Here I am my PID is %d\n",getpid());
        sleep(1);
    }
}


