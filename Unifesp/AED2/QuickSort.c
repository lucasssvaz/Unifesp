#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char Name[20];
	char Color[20];
	char SSize[2];
} Shirt;

void Partition(Shirt *Queue, int Start, int Finish){
	int i, j;
	Shirt Aux;

	if (Finish<=Start){
		return;
	}

	i = Start-1;

	for (j=Start;j<Finish;j++){
		if (strcmp(Queue[j].Color,Queue[Finish].Color)<0){
			i++;
			Aux=Queue[i];
			Queue[i]=Queue[j];
			Queue[j]=Aux;
		} else if (strcmp(Queue[j].Color,Queue[Finish].Color)==0){
			if (((Queue[j].SSize[0]=='P')&&((Queue[Finish].SSize[0]=='M')||(Queue[Finish].SSize[0]=='G')))||((Queue[j].SSize[0]=='M')&&(Queue[Finish].SSize[0]=='G'))){
				i++;
				Aux=Queue[i];
				Queue[i]=Queue[j];
				Queue[j]=Aux;
			} else if (((Queue[j].SSize[0]=='P')&&(Queue[Finish].SSize[0]=='P'))||((Queue[j].SSize[0]=='M')&&(Queue[Finish].SSize[0]=='M'))||((Queue[j].SSize[0]=='G')&&(Queue[Finish].SSize[0]=='G'))){
				if (strcmp(Queue[j].Name,Queue[Finish].Name)<0){
					i++;
					Aux=Queue[i];
					Queue[i]=Queue[j];
					Queue[j]=Aux;
				}
			}
		}
	}
	Aux=Queue[i+1];
	Queue[i+1]=Queue[j];
	Queue[j]=Aux;

	Partition(Queue,Start,i);
	Partition(Queue,i+2,Finish);

	return;
}

void QuickSort(Shirt *Queue, int nShirts){
	int Start, Finish;
	Start=0;
	Finish=nShirts-1;

	Partition(Queue,Start,Finish);

	return;
}

int main(){
	char Name[20], Color[20];
	char SSize[2];
	int i, nShirts;
	Shirt *Queue;

	scanf("%d",&nShirts);
	Queue = (Shirt *) calloc(nShirts,sizeof(Shirt));

	for (i=0;i<nShirts;i++){
		scanf("%s %s %s",Name,Color,SSize);
		strcpy(Queue[i].Name,Name);
		strcpy(Queue[i].Color,Color);
		strcpy(Queue[i].SSize,SSize);
	}

	QuickSort(Queue,nShirts);

	for (i=0;i<nShirts;i++){
		printf("%s %c %s\n",Queue[i].Color,Queue[i].SSize[0],Queue[i].Name);
	}

	free(Queue);
	return 0;
}
