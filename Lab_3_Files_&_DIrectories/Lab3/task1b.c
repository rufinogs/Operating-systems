/*
 * task1b.c
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
#include<stdio.h>    
#include<stdlib.h>
    
int cp(FILE *fp){
	    
    int max = 25;
    char ch, source_file[max], target_file[max];
    
    FILE *source, *target;    
    
    printf("Enter name of file to copy\n");
    gets(source_file);    
    
    source = fopen(source_file, "r");
    
        if( source == NULL )
        {
            printf("Press any key to exit...\n");
            exit(1);
        }
    
    printf("Enter name of target file\n");
    
    gets(target_file);
    
    target = fopen(target_file, "w");
    
    if( target == NULL )
    {
        fclose(source);        
        printf("Press any key to exit...\n");        
        exit(EXIT_FAILURE);
    }    
    
    while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, target);
        
        printf("File copied successfully.\n");        
        fclose(source);        
        fclose(target);
        
        return 0;
}

int main(){
	
	FILE *fp;
	
	cp(fp);
}
