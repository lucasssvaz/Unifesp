#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int *Array;
	int Start, End, Size, Max;
} TQueue;

TQueue *Queue_Create(int N){
	TQueue *Queue = (TQueue *) calloc(1,sizeof(TQueue));
	Queue->Start = -1;
	Queue->End = -1;
	Queue->Size = 0;
	Queue->Max = N;
	Queue->Array = (int *) calloc(N,sizeof(int));
	
	return Queue;
}

void Queue_Insert (TQueue *Queue,int Node){
	if (Queue->Size == 0){
		Queue->Array[0] = Node;
		Queue->Start = 0;
		Queue->End = 0;
		Queue->Size = 1;
	} else {
		Queue->End = (Queue->End++)%(Queue->Max);
		Queue->Array[Queue->End] = Node;
		Queue->Size++;
	}
}

int Queue_Remove (TQueue *Queue){
	int aux = 0;
	
	if (Queue->Size==0)
		return -1;
	
	if (Queue->Size==1){
		aux = Queue->Array[Queue->Start];
		Queue->Array[Queue->Start] = 0;
		Queue->Start = -1;
		Queue->End = -1;
		Queue->Size--;
	} else {
		aux = Queue->Array[Queue->Start];
		Queue->Array[Queue->Start] = 0;
		Queue->Start = (Queue->Start++)%(Queue->Max);
		Queue->Size--;
	}
	
	return aux;
}

int Queue_Next(TQueue *Queue){
    return Queue->Array[Queue->Start];
}

void BFS (int Node,int N,int **Matrix,int *Visited){
	TQueue *Queue = Queue_Create(N);
	int i, j, Aux;
	
    Visited[Node]=1;
    Queue_Insert(Queue,Node);
    while (Queue->Size!=0){
        Aux = Queue_Next(Queue);
        for (i=0;i<N;i++){
            if (Matrix[Aux][i]==1 && Visited[i]==0){
                Visited[i] = 1;
                Queue_Insert(Queue,i);
            }
        }
        Queue_Remove(Queue);
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
		BFS(i,N,Matrix,Visited);
		for (j=0;j<N;j++){
			if (Visited[j]==0) Valid=0;
		}
		free(Visited);
	}

	printf("%d\n",Valid);

	return 0;
}

