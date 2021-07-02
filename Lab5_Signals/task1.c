#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void fun_handler(int signo){
    switch(signo){
        case SIGUSR1:
        printf("Signal SIGUSR1\n");
        break;
        case SIGTERM:
        printf("Signal SIGTERM\n");
        break;
        case SIGINT:
        printf("Signal SIGINT\n");
        break;
        case SIGTSTP:
        printf("Signal SIGTSTP\n");
        break;


    }
}


int main(int argc, char *argv[])
{
if(atoi(argv[1])==0){
    //First version

    //execute the functions when recieve the signal
    signal(SIGUSR1,fun_handler);
    signal(SIGTERM,fun_handler);
    signal(SIGINT,fun_handler);
    signal(SIGTSTP,fun_handler);

    //SEND SIGNALS TO THE CALLING PROCESS
    raise(SIGUSR1);
    raise(SIGTERM);
    raise(SIGINT);
    raise(SIGTSTP);
}
else{

    //Second Version
    struct sigaction act;
	act.sa_handler = &fun_handler;
    act.sa_flags= SA_RESTART;

    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);
    
//SEND SIGNALS TO THE CALLING PROCESS
    raise(SIGUSR1);
    raise(SIGTERM);
    raise(SIGINT);
    raise(SIGTSTP);
}



}
