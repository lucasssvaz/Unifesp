#include <stdio.h>
#include <stdlib.h>

int main(){
	int N,D,i,j,Mat_I,Mat_J;
	int **Adj, *QuantE, *QuantS;
	
	scanf("%d %d",&N,&D);
	
	QuantE = (int *)calloc(N,sizeof(int));
	QuantS = (int *)calloc(N,sizeof(int));
	
	
	Adj =(int **) calloc(N,sizeof(int *));
	for (i=0;i<N;i++){
		Adj[i] =(int *) calloc(N,sizeof(int));
	}

	for (i=0;i<D;i++){
		scanf("%d %d",&Mat_I,&Mat_J);
		Adj[Mat_I-1][Mat_J-1]=1;
		QuantE[Mat_I-1]++;
		QuantS[Mat_J-1]++;
	}
	
	for (i=0;i<N;i++){
		printf ("%d %d %d",i+1,QuantS[i],QuantE[i]);
		if (QuantE[i]!=0){
			for (j=0;j<N;j++){
				if (Adj[i][j]==1){
					printf(" %d",j+1);
				}
			}
		}
		printf("\n");
	}
	
	return 0;
}
