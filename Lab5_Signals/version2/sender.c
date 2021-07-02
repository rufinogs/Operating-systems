#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void fun_handler(int signo){
 
}


int main(int argc, char *argv[])
{
    signal(SIGUSR1,fun_handler);
    signal(SIGUSR2,fun_handler);
    for(int i=1;i<=atoi(argv[1]);i++){
          kill(atoi(argv[2]),SIGUSR1);  
          pause();
    }
    kill(atoi(argv[2]),SIGUSR2);
    return 0;
}

