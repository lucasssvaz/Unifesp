#include <stdio.h>
#include <string.h>

int palin(char arr[]){
	int i, palindrome=1, tam;
	tam = strlen(arr);
	
	for (i=0;i<tam;i++){
		if (arr[i]!= arr[tam-i-1]){
			palindrome=0;
		}
	}
	return palindrome;
}

int main () {
	char arr[2001];
	scanf("%s",arr);
	
	if (palin(arr)){
		printf("sim");
	} else{
		printf("nao");
	}
	
	return 0;
}