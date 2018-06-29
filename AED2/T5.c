#include <stdlib.h>
#include <stdio.h>

#define INF 9999

typedef struct {
	int *Array;
	int Start, End, Size, Max;
} TQueue;

void Pathfinder (int Origin,int Destiny,int N,int **Matrix,int *Visited,int *Distance){
	int i, j, nVisited=0, minDist, minNode;

    Visited[Origin]=1;
    Distance[Origin]=0;
    nVisited++;

    while (nVisited<N){

    	minDist=INF;

        for (i=0;i<N;i++){
        	if (Visited[i]==0 && Distance[i]<minDist){
        		minDist=Distance[i];
        		minNode=i;
        	}
        }

        Visited[minNode]=1;

        for (i=0;i<N;i++){
            if (minDist+Matrix[minNode][i]<Distance[i] && Visited[i]==0){
                Distance[i]=minDist+Matrix[minNode][i];
            }
        }

        nVisited++;

    }

    return;
}

int main(){
	int **Matrix, N, M, C, K, j, i, u, v, p, *Visited, *Distance;

	scanf("%d %d %d %d",&N,&M,&C,&K);

	Matrix = (int **)calloc(N,sizeof(int *));

	for(i=0;i<N;i++){
		Matrix[i] = (int *)calloc(N,sizeof(int));
	}

	for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            Matrix[i][j]=INF;
        }
	}

	for(i=0;i<M;i++){
		scanf("%d %d %d",&u,&v,&p);
		if (v==(u+1) || u>=C)
			Matrix[u][v]=p;
		if (u == (v+1) || v>=C)
			Matrix[v][u]=p;
	}

	Visited = (int *)calloc(N,sizeof(int));
	Distance = (int *)calloc(N,sizeof(int));

	for (i=0;i<N;i++){
		Distance[i] = Matrix[K][i];
	}

	Pathfinder(K,C-1,N,Matrix,Visited,Distance);

	printf("%d\n",Distance[C-1]);

	free(Visited);
	free(Distance);

	return 0;
}
