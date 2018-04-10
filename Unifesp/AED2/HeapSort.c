#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
	char Name[20];
	int Grade;
	int Pos;
} Student;

void BuildHeap(Student *NewQueue, int nStudents);
void RedoHeap(Student *NewQueue, int nStudents, int Index);
void HeapSort(Student *NewQueue, int nStudents);

void RedoHeap(Student *NewQueue, int nStudents, int Index){
	int i = Index, Biggest=0;
	Student Aux;

	Aux=NewQueue[Index];

	while (2*i+1<=nStudents-1){

		if (2*i+2<=nStudents-1){
			if ((NewQueue[2*i+1].Grade>Aux.Grade)&&(NewQueue[2*i+1].Grade>NewQueue[2*i+2].Grade)){
				NewQueue[i]=NewQueue[2*i+1];
				i=2*i+1;
			} else if ((NewQueue[2*i+2].Grade>Aux.Grade)&&(NewQueue[2*i+2].Grade>NewQueue[2*i+1].Grade)){
				NewQueue[i]=NewQueue[2*i+2];
				i=2*i+2;
			} else if ((NewQueue[2*i+2].Grade>Aux.Grade)&&(NewQueue[2*i+2].Grade==NewQueue[2*i+1].Grade)){
				if (NewQueue[2*i+1].Pos<NewQueue[2*i+2].Pos){
					NewQueue[i]=NewQueue[2*i+1];
					i=2*i+1;
				} else {
					NewQueue[i]=NewQueue[2*i+2];
					i=2*i+2;
				}
			} else if ((NewQueue[2*i+1].Grade==Aux.Grade)&&(NewQueue[2*i+1].Pos<Aux.Pos)){
				NewQueue[i]=NewQueue[2*i+1];
				i=2*i+1;
			} else if ((NewQueue[2*i+2].Grade==Aux.Grade)&&(NewQueue[2*i+2].Pos<Aux.Pos)){
				NewQueue[i]=NewQueue[2*i+2];
				i=2*i+2;
			} else{
				break;
			}
		} else {
			if (NewQueue[2*i+1].Grade>Aux.Grade){
				NewQueue[i]=NewQueue[2*i+1];
				i=2*i+1;
			} else {
				break;
			}
		}
	}
	NewQueue[i]=Aux;
	return;
}

void BuildHeap(Student *NewQueue, int nStudents){

	int i, Leaves_Start = ceil(1.0*nStudents/2);

	for (i=Leaves_Start-1;i>=0;i--){
		RedoHeap(NewQueue, nStudents, i);
	}

	return;
}

void HeapSort (Student *NewQueue, int nStudents){
	Student Aux;
	int i;

	BuildHeap(NewQueue,nStudents);

	for (i=nStudents-1;i>0;i--){
		Aux=NewQueue[0];
		NewQueue[0]=NewQueue[i];
		NewQueue[i]=Aux;
		RedoHeap(NewQueue,i,0);
	}

	return;
}

int main(){
	char Name[20];
	int nStudents, i, Grade;
	Student *Queue, *NewQueue;

	scanf("%d",&nStudents);
	Queue = (Student *) calloc(nStudents,sizeof(Student));
	NewQueue = (Student *) calloc(nStudents,sizeof(Student));

	for (i=0;i<nStudents;i++){
		scanf("%s %d",Name,&Grade);
		strcpy(Queue[i].Name,Name);
		Queue[i].Grade=Grade;
		strcpy(NewQueue[i].Name,Name);
		NewQueue[i].Grade=Grade;
		Queue[i].Pos=i;
		NewQueue[i].Pos=i;
	}

	HeapSort(NewQueue,nStudents);

	for (i=0;i<nStudents;i++){
		if (strcmp(Queue[i].Name,NewQueue[nStudents-i-1].Name)==0){
			printf("%s\n", Queue[i].Name);
		}
	}

	free(Queue);
	free(NewQueue);
	return 0;
}