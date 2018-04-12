#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int racer;
	int key;
} item;

int order(item* list, int nElements){
  int i, j;
  item Aux;
  int Changes=0;

  for (i=0;i<nElements-1;i++){
    for (j=1;j<nElements-i;j++){
      if (list[j-1].key>list[j].key){
      	Changes++;
        Aux=list[j-1];
        list[j-1]=list[j];
        list[j]=Aux;
      }
    }
  }
  return Changes;
}

int main()
{
	int nRacers, *finishPos, i, j;
	item *startPos;


	scanf("%d",&nRacers);

	startPos = (item *)calloc(nRacers,sizeof(item));
	finishPos = (int *)calloc(nRacers,sizeof(int));

	for(i=0;i<nRacers;i++){
		scanf("%d",&startPos[i].racer);
	}
	for(i=0;i<nRacers;i++){
		scanf("%d",&finishPos[i]);
	}

	for (i=0;i<nRacers;i++){
		for (j=0;j<nRacers;j++){
			if (finishPos[i]==startPos[j].racer){
				startPos[j].key=i;
			}
		}
	}

	printf("%d",order(startPos,nRacers));

	return 0;
}