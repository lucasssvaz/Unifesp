#include <stdio.h>
#define SIZE 101
//=========================================================
int Mmagico(int num,int mat[SIZE][SIZE]){

int i,j,soma, Magico, SomaMagico;

soma=0;
SomaMagico=0;
Magico=1;

for(j=0;j<num;j++)
    SomaMagico=SomaMagico+mat[0][j];

for (i=0;i<num;i++){
    soma=0;
    for(j=0;j<num;j++){
        soma=soma+mat[i][j];
        }
    if (soma!=SomaMagico){
            Magico=0;
    }
}

for (i=0;i<num;i++){
    soma=0;
    for(j=0;j<num;j++){
        soma=soma+mat[j][i];
    }
    if (soma!=SomaMagico){
            Magico=0;
    }
}

soma=0;

for(j=0;j<num;j++){
    soma=soma+mat[j][j];
}

if (soma!=SomaMagico){
    Magico=0;
}

soma=0;

for (i=0;i<num;i++){
    soma=soma+mat[num-i-1][i];
    }
if (soma!=SomaMagico){
            Magico=0;
}

if (Magico==1)
    return SomaMagico;
else
    return Magico;
}

//============================================================

int main(){

int num, mat[SIZE][SIZE],i,j;

scanf("%d",&num);

for (i=0;i<num;i++){
    for(j=0;j<num;j++){
        scanf("%d",&mat[i][j]);
    }
}

printf("%d",Mmagico(num,mat));

return 0;
}