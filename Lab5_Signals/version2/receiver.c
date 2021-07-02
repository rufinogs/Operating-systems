#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int x;
void handler(int signum,siginfo_t *info, void *context){
    static int counter=0;
    pid_t pid=info->si_pid;
    switch (signum){
        case SIGUSR1:
            counter++;
            kill(pid,SIGUSR1);
            break;
        case SIGUSR2:
            printf("I´ve received %d Signals\n",counter);
            counter=0;
            break;
    }
}


int main(int argc, char *argv[])
{
    struct sigaction action;
    action.sa_flags=SA_SIGINFO;
    action.sa_sigaction=handler;

    sigaction(SIGUSR1,&action,NULL);
    sigaction(SIGUSR2,&action,NULL);
}