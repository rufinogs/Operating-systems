/*
 * task1b2.c
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

int cp(FILE *fp){
	
	// Variables
	int max = 25;
    char source_file[max], target_file[max];
    
    char *cpArr;
    FILE *fpSourceFile, *fpTargetFile;
    

	printf("Enter name of file to copy\n");
	gets(source_file);

	fpSourceFile = fopen(source_file, "r");

	// We obtain The Size Of bits Of The Source File
	fseek(fpSourceFile, 0, SEEK_END); // We Go To The End Of The File 
	cpArr = (char *)malloc(sizeof(*cpArr) * ftell(fpSourceFile)); // We Create An Array At That Size
	fseek(fpSourceFile, 0, SEEK_SET); // We Return The Cursor To The Start

	// We Read From The Source File - "Copy"
	fread(&cpArr, sizeof(cpArr), 1, fpSourceFile);
	
	printf("Enter name of target file\n");
	
	gets(target_file);
	
	fpTargetFile = fopen(target_file, "w");

	// we Write To The Target File - "Paste"
	fwrite(&cpArr, sizeof(cpArr), 1, fpTargetFile);

	// We Close The Files
	fclose(fpSourceFile);
	fclose(fpTargetFile);

	// We Free The Used Memory
	free(cpArr);
	
	printf("File copied successfully.\n"); 
}

int main(){
	
	FILE *fp;
	
	cp(fp);
	
	}
