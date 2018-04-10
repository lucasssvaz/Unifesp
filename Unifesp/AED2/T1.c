#include <stdlib.h>
#include <stdio.h>

void BubbleSort(int* list, int Elements){
  int i=0, j=0, swap=0;
  int Aux;

  for (i=0;i<Elements-1;i++){
  	swap=0;
    for (j=Elements-1;j>=i;j--){
      if (list[j-1]>list[j]){
        Aux=list[j-1];
        list[j-1]=list[j];
        list[j]=Aux;
        swap++;
      }
    }
    if(swap==0){
    	break;
    }
  }
}

int *ReverseSort(int Elements,int Iterations,int *SPI){
	int i=0, j=0;
	int Aux, *Original;

	Original = (int *)calloc(Elements,sizeof(int));

	for (i=1;i<=Elements;i++){
		Original[i-1]=i;
	}

	for (i=Elements-2;i>=0;i--){
		for (j=i;j<Elements-1&&SPI[i]>0;j++){
	    	if (Original[j+1]>Original[j]){
	    	Aux=Original[j+1];
	    	Original[j+1]=Original[j];
	    	Original[j]=Aux;
	    	SPI[i]--;
	    	}
		}
	}


	return Original;
}

int main (){
	long int Elements, Iterations;
	int i;
	int *Original;

	scanf("%li %li",&Elements,&Iterations);

	int *SPI = (int *)calloc(Elements-1,sizeof(int));

	for (i=0;i<Iterations;i++){
		scanf("%d",&SPI[i]);
	}


	Original = ReverseSort(Elements,Iterations,SPI);

	for (i=0;i<Elements;i++){
		printf("%d ",Original[i]);
	}

	free(Original);
	return 0;
}
