#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	int, while, if, return, void, else
*/

void verify_buf (char *buffer){
	
	int i = 0;
	
	if ((strcmp(buffer,"int") == 0) || (strcmp(buffer,"while") == 0) || (strcmp(buffer,"if") == 0) || (strcmp(buffer,"return") == 0) || (strcmp(buffer,"void") == 0)) {
		while (buffer[i] != '\0'){
			buffer[i] = buffer[i] - 32;
			i++;
		}
	} else {
		buffer[0] = 'I';
		buffer[1] = 'D';
		buffer[2] = '\0';
	}
	return;
}

int main(){

	FILE *out_file, *in_file;
	
	char C, buffer[256] = "";
	int len;
		
	in_file = fopen("sort.txt","r");
	out_file = fopen("SORT.txt","w+");
	
	if (in_file == NULL || out_file == NULL) {
		printf("File Desc Error");
		exit(-1);
	}
	
	C = getc(in_file);
	
	do{
		if (((C >= 48) && (C <= 57)) || ((C >= 65) && (C <= 90)) || ((C >= 97) && (C <= 122))){
		
			len = strlen(buffer);
			buffer[len] = C;
			buffer[len+1] = '\0';
		
		} else{
			if (strlen(buffer) > 0){
				verify_buf(buffer);
				fputs(buffer, out_file);
				buffer[0] = '\0';
			}
			putc(C, out_file);
		}
		
		C = getc(in_file);
				
	} while (C != EOF);

	return 0;
}
