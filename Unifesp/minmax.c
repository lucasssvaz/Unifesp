#include <stdio.h>
#define SIZE 101

int FindMM (int linhas, int colunas,int mat[SIZE][SIZE],int *MMi, int *MMj)
{
    int MinMax=0, MenorNro,i,j;
    
    MenorNro=mat[0][0];    
    *MMi=0;
    *MMj=0;
    
    for (i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            if (mat[i][j]<=MenorNro){
                MenorNro=mat[i][j];
                *MMi=i;
            }
        }
    }

    for (j=0;j<colunas;j++){
        if (mat[*MMi][j]>=MinMax){
            MinMax=mat[*MMi][j];
            *MMj=j;
        }
    }
    return MinMax;
}

int main(){

    int linhas, colunas, mat[SIZE][SIZE], i,j,MMi,MMj,MM;

    scanf("%d %d",&linhas,&colunas);

    for (i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    MM=FindMM(linhas,colunas,mat,&MMi,&MMj);

    printf("%d %d %d",MMi,MMj,MM);

    return 0;

}