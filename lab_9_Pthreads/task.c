#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include "sys/stat.h"
#include "time.h"
#include <stdint.h>
#include <ftw.h>

int probability;

//TASK 2
int task2a(DIR* dir){
    while ((rand() % 100 + 1)>probability){
        struct stat info;
        if (dir == NULL){
            return 1;
        }

        struct dirent* entity;
        entity=readdir(dir);
        while(entity !=NULL){
            if (!stat(entity->d_name,&info))
            {
                if (S_ISREG(info.st_mode))
                { 
                printf("File Name:              %s\n",entity->d_name); 
                printf("File Size:              %ld bytes\n",info.st_size);
                printf("Last Access:            %ld. \n",info.st_atime);
                }
                }
            entity=readdir(dir);
        }

        closedir(dir);
    }
    return 0;

}


// Procedure to display the time
void *show_time(void *arg){
    int type = *(int*)arg;
    int i = 1;
    while ((rand() % 100 + 1)>probability){
        time_t t;   
        time(&t);
        printf("\n Pthread %d : This program has been writeen at (date and time): %s", type,ctime(&t));
        i++;
    }
}

//Procedure to show the users
void *show_users(void *arg){
    int n = *(int*)arg;
    int i = 1;
    while ((rand() % 100 + 1)>probability){
        printf("Pthread %d: , Loop_number:%d, Users:\n",n,i);
        system("w");
        i++;
    }
}


//Procedure to show the content
void *show_content(void *arg){
    int n = *(int*)arg;
    int i = 1;
    while ((rand() % 100 + 1)>probability){
        printf("Pthread %d: , Loop_number:%d, Directory_content:\n",n,i);
        system("ls");
        i++;
    }
}


//Procedure to display the resources
void *show_resources(void *arg){
    int n = *(int*)arg;
    int i = 1;
    while ((rand() % 100 + 1)>probability){
        printf("Pthread %d: , Loop_number:%d, Resources_file:\n",n,i);
        system("ps aux");
        i++;
    }
}



int main(int argc, char *argv[]){
	//first argument (number of threads)
    int x = atoi(argv[1]); 
    //second argument (probability)
    probability= atoi(argv[2]);
    //We create the number of threads due to the First argument
    pthread_t threads[x];
    
    for (long int i = 0; i < x; i++){
		
        int num = rand() %(3 + 1); //random case between the 4 values
        switch (num)
        {
        case 0:
            pthread_create(&threads[i],NULL,show_time,(void *)&i);
            break;
        
        case 1:
            pthread_create(&threads[i],NULL,show_users,(void *)&i);
            break;
        
        case 2:
            pthread_create(&threads[i],NULL,show_resources,(void *)&i);
            break;
        
        case 3:
            pthread_create(&threads[i],NULL,show_content,(void *)&i);
            break;
        
        default:
            break;
        }
    }
	
	// Here all the threads are joined
	
    for (int i = 0; i < x; i++){
        pthread_join(threads[i],NULL);
        printf("Thread %d has finished\n", i + 1);
    }
    return 0;
}
