#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **CountingSort (char **Queue, long int Elements, int Pos){
	int min, max, i, range, *Counting;
	char **Aux;

	Aux = (char **) calloc(Elements,sizeof(char *));
	for (i=0;i<Elements;i++){
		Aux[i] = (char *) calloc(4,sizeof(char));
	}

	max = Queue[0][Pos]-'0';
	min = Queue[0][Pos]-'0';

	for (i=0;i<Elements;i++){
		if (Queue[i][Pos]-'0'>max){
			max = Queue[i][Pos]-'0';
		} else if (Queue[i][Pos]-'0'<min){
			min = Queue[i][Pos]-'0';
		}
	}

	range = max-min+1;

	for (i=0;i<Elements;i++){
			Queue[i][Pos]=Queue[i][Pos]-min;
	}


	Counting = (int *) calloc(range,sizeof(int));

	for (i=0;i<Elements;i++){
		Counting[Queue[i][Pos]-'0']++;
	}

	for (i=1;i<range;i++){
		Counting[i]+=(Counting[i-1]);
	}

	for (i=Elements-1;i>=0;i--){
		Aux[Counting[(Queue[i][Pos]-'0')]-1]=Queue[i];
		Counting[Queue[i][Pos]-'0']--;
	}

	for (i=0;i<Elements;i++){
        Aux[i][Pos]+=min;
		Queue[i]=Aux[i];
	}


	free(Aux);
	free(Counting);

	return Queue;
}

char **RadixSort (char **Queue, long int Elements){
	int i;

	for (i=2; i>=0; i--){
		Queue=CountingSort(Queue,Elements,i);
	}

	return Queue;
}


int main(){
	long int Elements;
	int i, numInt, Aux;
	char **Queue, numStr[4];

	scanf("%li",&Elements);

	Queue = (char **) calloc(Elements,sizeof(char *));

	for (i=0;i<Elements;i++){
		Queue[i]= (char *) calloc(4,sizeof(char));
	}

	for (i=0;i<Elements;i++){
		scanf("%d",&numInt);
		if (numInt < 100){
			snprintf(numStr,sizeof(numStr),"0%d",numInt);
		} else {
			snprintf(numStr,sizeof(numStr),"%d",numInt);
		}
		strcpy(Queue[i],numStr);
	}

	Queue=RadixSort(Queue,Elements);

	for (i=0;i<Elements;i++){
        Aux = atoi(Queue[i]);
		printf("%d ",Aux);
	}

	return 0;
}
