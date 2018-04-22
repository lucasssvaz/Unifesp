#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *Create(int *vet,int *size){
	int n=1;

	while (n>=0){
		scanf("%d",&n);
		if (n!=-1){
			(*size)++;
			vet = (int *)realloc(vet,(*size)*sizeof(int));
			vet[(*size)-1]=n;
		}
	}
	return vet;
}

int Search(int *vet,int start, int end, int n){
	int mid, index=-1, aux1, aux2, size;

	size = end - start + 1;
	mid = (start + end)/2;

	if (end<start)
		return -1;

	if (n==vet[mid]){
		index = mid;
	}

	aux1 = Search (vet, start, mid-1, n);
	aux2 = Search (vet, mid+1, end, n);

	if (aux1!=-1)
		index=aux1;
	if (aux2!=-1)
		index=aux2;

	return index;
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
	int size=0, n, index=-1;
	int *vet = (int *)calloc(1,sizeof(int));

	vet = Create(vet,&size);

	scanf("%d",&n);

	index = Search(vet,0,size-1,n);

	if (index<0){
		Insert(vet,&size,n);
	} else{
		Remove(vet,&size,index);
	}

	printf("%d\n",size);


	free(vet);
	return 0;
}