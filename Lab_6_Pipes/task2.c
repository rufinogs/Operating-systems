#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
int main(){
char string1[]="String for pipe I/O now we are trying to go over the buffer";
char buff[32];

    if ((mkfifo("pipe1",0777)) != 0) {
        printf("Unable to create a fifo; errno=%d\n",errno);
        exit(1);                     /* Print error message and return */
    }


    
    if (fork() == 0) {
        /* child program */
        int fd= open("pipe1",O_WRONLY);
        if(fd==-1){
            return 1;
        }
        write(fd,string1,strlen(string1)); /*Write to pipe*/
        close(fd);
    }
    else {
        /* parent program */
        int fd= open("pipe1",O_RDONLY);
            if(fd==-1){
                return 1;
            }
        read(fd,buff,strlen(string1)); /* Read from pipe */
        printf("parent read %s from the child program\n",buff);
        close(fd);
    }



}