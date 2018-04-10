#include <stdio.h>
#include <stdlib.h>

int digit (int num,int Pos){
    int dig;

    if (Pos==0){
        dig = (num)%10;
    } else if (Pos==1){
            dig = (num/10)%10;
    } else {
        dig = num/100;
    }

    return dig;
}

void CountingSort (int *Queue, long int Elements, int Pos){
	int i, *Counting;
	int *Aux;

	Aux = (int *) calloc(Elements,sizeof(int));

	Counting = (int *) calloc(10,sizeof(int));

	for (i=0;i<Elements;i++){
		Counting[digit(Queue[i],Pos)]++;
	}

	for (i=1;i<10;i++){
		Counting[i]+=(Counting[i-1]);
	}

	for (i=Elements-1;i>=0;i--){
		Aux[Counting[(digit(Queue[i],Pos))]-1]=Queue[i];
		Counting[digit(Queue[i],Pos)]--;
	}

	for (i=0;i<Elements;i++){
		Queue[i]=Aux[i];
	}

	return;
}

void RadixSort (int *Queue, long int Elements){
	int i;

	for (i=0; i<3; i++){
		CountingSort(Queue,Elements,i);
	}

	return;
}


int main(){
	long int Elements;
	int i;
	int *Queue;

	scanf("%li",&Elements);

	Queue = (int *) calloc(Elements,sizeof(int));

	for (i=0;i<Elements;i++){
		scanf("%d",&Queue[i]);
	}

	RadixSort(Queue,Elements);

	for (i=0;i<Elements;i++){
		printf("%d ",Queue[i]);
	}

    free(Queue);
	return 0;
}
