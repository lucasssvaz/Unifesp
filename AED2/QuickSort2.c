#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char Name[15];
	int Age, Pos;
} Person;

void Partition(Person *Queue, int Start, int Finish){
	int i, j;
	Person Aux;

	if (Finish<=Start){
		return;
	}

	i = Start-1;

	for (j=Start;j<Finish;j++){
		if (Queue[j].Age <= Queue[Finish].Age){
			i++;
			Aux=Queue[i];
			Queue[i]=Queue[j];
			Queue[j]=Aux;
		}
	}
	
	Aux=Queue[i+1];
	Queue[i+1]=Queue[j];
	Queue[j]=Aux;

	Partition(Queue,Start,i);
	Partition(Queue,i+2,Finish);

	return;
}

void QuickSort(Person *Queue, int N){
	int Start, Finish;
	Start=0;
	Finish=N-1;

	Partition(Queue,Start,Finish);

	return;
}

int main(){

	int Stable = 1, N, i, Input2, Print_N, Print_I;
	char Input1[15];
	
	scanf("%d",&N);

	Person* Seq = (Person*) calloc(N,sizeof(Person));
	
	for (i=0; i<N; i++){
		scanf("%s %d",Input1,&Input2);
		Seq[i].Age = Input2;
		Seq[i].Pos = i;
		strcpy(Seq[i].Name,Input1);
	}
	
	QuickSort(Seq,N);

	scanf("%d %d",&Print_I,&Print_N);
	
	for (i=0; i<N; i++){
		if ((Seq[i].Age == Seq[i+1].Age) && (Seq[i].Pos > Seq[i+1].Pos))
			Stable = 0;
	}
	
	Stable ? printf("yes\n") : printf("no\n");
	
	for (i=0; i<Print_N; i++){
		printf("%s %d\n",Seq[Print_I+i-1].Name,Seq[Print_I+i-1].Age);
	}

	return 0;
}
