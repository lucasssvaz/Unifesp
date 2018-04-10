#include <stdio.h>
#include <stdlib.h>

int *CountingSort (int *Queue, long int Elements){
	int min, max, i, range, *Counting;
	int *Aux;
	max = Queue[0];
	min = Queue[0];

	for (i=0;i<Elements;i++){
		if (Queue[i]>max){
			max = Queue[i];
		} else if (Queue[i]<min){
			min = Queue[i];
		}
	}

	range = max-min+1;

	if (min < 0){
		for (i=0;i<Elements;i++){
			Queue[i]+=min;
		}
	}
	else {
		for (i=0;i<Elements;i++){
			Queue[i]-=min;
		}
	}

	Counting = (int *) malloc(range*sizeof(int));

	for (i=0;i<Elements;i++){
		Counting[Queue[i]]++;
	}

	for (i=1;i<range;i++){
		Counting[i]+=(Counting[i-1]);
	}

	Aux = (int *) malloc(Elements*sizeof(int));

	for (i=Elements-1;i>=0;i--){
		Aux[Counting[Queue[i]]-1]=Queue[i];
		Counting[Queue[i]]--;
	}

	if (min < 0){
		for (i=0;i<Elements;i++){
			Aux[i]-=min;
			Queue[i]=Aux[i];
		}
	}
	else {
		for (i=0;i<Elements;i++){
			Aux[i]+=min;
			Queue[i]=Aux[i];
		}
	}

	free(Aux);
	free(Counting);

	return Queue;
}

int main(){
	long int Elements;
	int *Queue, i;

	scanf("%li",&Elements);

	Queue = (int *) malloc(Elements*sizeof(int));

	for (i=0;i<Elements;i++){
		scanf("%d",&Queue[i]);
	}

	Queue = CountingSort(Queue,Elements);

	for (i=0;i<Elements;i++){
		printf("%d ",Queue[i]);
	}

	return 0;
}
