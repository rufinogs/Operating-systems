#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    int i = 1;
    while (i <= atoi(argv[1]))
    {
        kill(atoi(argv[2]),SIGUSR1);
        ++i;
    }
    kill(atoi(argv[2]),SIGUSR2);

}