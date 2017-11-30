#include <stdio.h>
#define TOT 201
#define MAX 101

void Inter(int M,int A[],int N,int B[],int *P,int C[]){
    int assist,i,j, igual;
    
    igual=0;
    C[0]=A[0];
    *P=1;
    for (j=0;j<M;j++){
	    for (i=0;i<*P;i++){
		    if(A[j]==C[i]){
                igual=1;
            }
            if (igual!=1){
                C[*P]=A[j];
                *P+=1;
            }
            igual=0;
	    }
    }
}

int main(){

    int A[MAX], B[MAX], C[TOT], M, N, P, i, soma;
//============================================
    scanf("%d",&M);
    for (i=0;i<M;i++){
    		scanf("%d",&A[i]);
    	}

    scanf("%d",&N);
    for (i=0;i<N;i++){
    		scanf("%d",&B[i]);
    	}
//============================================
soma=0;

Inter(M,A,N,B,&P,C);

for (i=0; i<P; i++){
    soma+=C[i];
}

    printf("%d\n",soma);

return 0;

}