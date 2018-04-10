#include <stdio.h>
#include <stdlib.h>

void Create(int *vet,int *size){
	int i, n=1;

	while (n>=0){
		scanf("%d",&n);
		if (n!=-1){
			(*size)++;
			vet = (int *)realloc(vet,(*size)*sizeof(int));
			vet[(*size)-1]=n;			
		}
	}
	return;
}

int Search(int *vet,int size, int n){
	int i;

	for (i=0;i<size;i++){
		if (n==vet[i]){
			return i;
		}
	}
	return -1;
}

void Insert(int *vet, int *size, int n){
	vet = (int *)realloc(vet,((*size)++)*sizeof(int));
	vet[(*size)-1]=n;

	return;
}

void Remove(int *vet, int *size, int index){
	int i;

	for(i=index+1;i<(*size)-1;i++){
		vet[i-1]=vet[i];
	}

	vet = (int *) realloc(vet,((*size)--)*sizeof(int));

	return;
}

int main(){
	int size=0, n, i=0, index=-1;
	int *vet = (int *)calloc(1,sizeof(int));

	Create(vet,&size);

	scanf("%d",&n);

	index = Search(vet,size,n);

	if (index<0){
		Insert(vet,&size,n);
	} else{
		Remove(vet,&size,index);
	}

	printf("%d\n",size);


	free(vet);
	return 0;
}