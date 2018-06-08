#include <stdlib.h>
#include <stdio.h>

void DFS(int Node,int N,int **Matrix,int *Visited){
	int i;

	Visited[Node]=1;
	for(i=0;i<N;i++){
		if(Matrix[Node][i]==1 && Visited[i]==0){
			DFS(i,N,Matrix,Visited);
		}
	}
}

int main(){
	int **Matrix, N, M, j, i, u, v, p, *Visited, Valid = 1;

	scanf("%d %d",&N,&M);

	Matrix = (int **)calloc(N,sizeof(int *));

	for(i=0;i<N;i++){
		Matrix[i] = (int *)calloc(N,sizeof(int));
	}

	for(i=0;i<M;i++){
		scanf("%d %d %d",&u,&v,&p);
		if (p==1){
			Matrix[u-1][v-1]=1;
		} else {
			Matrix[u-1][v-1]=1;
			Matrix[v-1][u-1]=1;
		}
	}

	for(i=0;i<N;i++){
		Visited = (int *)calloc(N,sizeof(int));
		DFS(i,N,Matrix,Visited);
		for (j=0;j<N;j++){
			if (Visited[j]==0) Valid=0;
		}
		free(Visited);
	}

	printf("%d\n",Valid);

	return 0;
}