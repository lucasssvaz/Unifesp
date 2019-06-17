#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int nNeurons;

  printf("Number of neurons:\n");
  scanf("%d",&nNeurons);

  FILE* file_regular = fopen("G_Regular.dat", "w");
  FILE* file_random = fopen("G_Random.dat", "w");
  FILE* file_barabasi = fopen("G_Barabasi.dat", "w");
  int i,j, **Regular, **Random, **Barabasi, *Barabasi_Edges, nEdges_Nodes=2, a;

  Regular = (int **) calloc(nNeurons,sizeof(int *));
  Random = (int **) calloc(nNeurons,sizeof(int *));
  Barabasi = (int **) calloc(nNeurons,sizeof(int *));

  srand((unsigned)time(NULL));

  //======================================================================================================================
  
  for (i=0;i<nNeurons;i++){
    Regular[i] = (int *)malloc(nNeurons*sizeof(int));
    Random[i] = (int *)malloc(nNeurons*sizeof(int));
    Barabasi[i] = (int *)malloc(nNeurons*sizeof(int));
    for (j=0;j<nNeurons;j++){
      Regular[i][j]=0;
      Random[i][j]=0;
      Barabasi[i][j]=0;
    }
  }

  //====================================================================================================================== REGULAR
  
  for (i=0;i<nNeurons;i++){
    Regular[i][(i+1)%nNeurons]=1;
    Regular[(i+1)%nNeurons][i]=1;
  }

  for (i=0;i<nNeurons;i++){
    for (j=0;j<nNeurons;j++){
      fprintf(file_regular, "%d ",Regular[i][j]);
    }
    fprintf(file_regular,"\n");
  }

  //====================================================================================================================== RANDOM
  
  for (i=0;i<nNeurons;i++){
    do{
      a = rand()%nNeurons;
    } while (Random[i][a]!=0 && a==i);
    Random[a][i]=1;
    Random[i][a]=1;
  }

  for (i=0;i<nNeurons;i++){
    for (j=0;j<nNeurons;j++){
      fprintf(file_random, "%d ",Random[i][j]);
    }
    fprintf(file_random,"\n");
  }
  
  //====================================================================================================================== BARABASI
  
  Barabasi_Edges = (int *)calloc(nEdges_Nodes,sizeof(int));
  do{
    a = rand()%nNeurons;
  }while(a==0);
  Barabasi[a][0]=1;
  Barabasi[0][a]=1;
  Barabasi_Edges[0]=a;
  Barabasi_Edges[1]=0;
  
  for (i=1;i<nNeurons;i++){
    do{
      a = Barabasi_Edges[rand()%nEdges_Nodes];
    } while (Barabasi[a][i]!=0 && a==i);
    Barabasi[a][i]=1;
    Barabasi[i][a]=1;
    nEdges_Nodes+=2;
    Barabasi_Edges = (int *)realloc(Barabasi_Edges,nEdges_Nodes*sizeof(int));
    Barabasi_Edges[nEdges_Nodes-1]=i;
    Barabasi_Edges[nEdges_Nodes-2]=i;
  }

  for (i=0;i<nNeurons;i++){
    for (j=0;j<nNeurons;j++){
      fprintf(file_barabasi, "%d ",Barabasi[i][j]);
    }
    fprintf(file_barabasi,"\n");
  }

  //======================================================================================================================

  fclose(file_regular);
  fclose(file_random);
  fclose(file_barabasi);
  return 0;
}
