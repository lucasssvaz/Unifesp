#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  FILE* file_regular = fopen("G_Regular.dat", "w");
  FILE* file_random = fopen("G_Random.dat", "w");
  FILE* file_barabasi = fopen("G_Barabasi.dat", "w");
  int i,j, Regular[500][500], Random[500][500], Barabasi[500][500], *Barabasi_Edges, nEdges_Nodes=2, a, b;

  srand((unsigned)time(NULL));

  for (i=0;i<500;i++){
    for (j=0;j<500;j++){
      Regular[i][j]=0;
      Random[i][j]=0;
      Barabasi[i][j]=0;
    }
  }

  for (i=0;i<500;i++){
    Regular[i][(i+1)%500]=1;
    Regular[(i+1)%500][i]=1;
  }

  for (i=0;i<500;i++){
    for (j=0;j<500;j++){
      fprintf(file_regular, "%d ",Regular[i][j]);
    }
    fprintf(file_regular,"\n");
  }

  for (i=0;i<499;i++){
    a = rand()%500;
    b = rand()%500;
    while (Random[a][b]!=0){
      a = rand()%500;
      b = rand()%500;
    }
    Random[a][b]=1;
    Random[b][a]=1;
  }

  for (i=0;i<500;i++){
    for (j=0;j<500;j++){
      fprintf(file_random, "%d ",Random[i][j]);
    }
    fprintf(file_random,"\n");
  }


  fclose(file_regular);
  fclose(file_random);
  fclose(file_barabasi);
  return 0;
}