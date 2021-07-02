/*
 * task1a.c
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

int main(void)
{
	int x;
	int i;
	FILE *fp;
	char ch [400];
	
	//We open the FILE
	fp = fopen("file.txt", "w+");
	printf("Introduce the size (it will be in Bytes) of the file you want and press ENTER: \n");
	scanf("%d",&i);
	fseek(fp, i , SEEK_SET);
	fputc('\0', fp);
	
	//printf("Introduce the size of the file you want: \n");
	//scanf("%",i);
	

	if(fp == NULL) {
		printf("Error!");   
		exit(1);             
    }
	
	//Introduce some data in the FILE
	//printf("Enter data... (if you click on ENTER or SPACE you will finish writting): \n");
	//scanf("%s",ch);
	//fprintf(fp,"%s", ch);
    
	
    // closing the file pointer
    fclose(fp);

	return 0;
}

