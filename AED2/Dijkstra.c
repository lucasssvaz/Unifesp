#include <stdlib.h>
#include <stdio.h>

#define INF 9999

typedef struct {
	int *Array;
	int Start, End, Size, Max;
} TQueue;

void Pathfinder (int Origin,int Destiny,int N,int **Matrix,int *Visited,int *Distance){
	int i, nVisited=0, minDist, minNode;

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

    printf("%d\n",Distance[Destiny]);

    return;
}

int main(){
	int **Matrix, N, M, j, i, u, v, p, *Visited, *Distance;

	scanf("%d %d",&N,&M);

	N+=2;

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
		Matrix[u][v]=p;
		Matrix[v][u]=p;
	}

	Visited = (int *)calloc(N,sizeof(int));
	Distance = (int *)calloc(N,sizeof(int));

	for (i=0;i<N;i++){
		Distance[i] = Matrix[0][i];
	}

	Pathfinder(0,N-1,N,Matrix,Visited,Distance);

	free(Visited);
	free(Distance);

	return 0;
}