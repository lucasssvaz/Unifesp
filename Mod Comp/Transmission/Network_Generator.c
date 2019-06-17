#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
  int nNodes, Degree;

  printf("Number of nodes:\n");
  scanf("%d",&nNodes);
  printf("Average Degree (power of 2):\n");
  scanf("%d",&Degree);

  FILE* file_barabasi = fopen("G_Barabasi.dat", "w");
  int i,j, **Barabasi, *Barabasi_Edges, nEdges_Nodes=2, a, aux;

  Barabasi = (int **) calloc(nNodes,sizeof(int *));

  srand((unsigned)time(NULL));

  //======================================================================================================================
  
  for (i=0;i<nNodes;i++){
    Barabasi[i] = (int *)malloc(nNodes*sizeof(int));
    for (j=0;j<nNodes;j++){
      Barabasi[i][j]=0;
    }
  }
  //====================================================================================================================== BARABASI
  
  Barabasi_Edges = (int *)calloc(nEdges_Nodes,sizeof(int));
  do{
    a = rand()%nNodes;
  }while(a==0);
  aux = 1+(rand()%100);
  Barabasi[a][0] = aux;
  Barabasi[0][a] = aux;
  Barabasi_Edges[0] = a;
  Barabasi_Edges[1] = 0;
  
  for (i=1;i<nNodes;i++){
    for(j=0;j<(log2(Degree));j++){
      do{
        a = Barabasi_Edges[rand()%nEdges_Nodes];
      } while (Barabasi[a][i]!=0 && a==i);
      aux = 1+(rand()%100);
      Barabasi[a][i] = aux;
      Barabasi[i][a] = aux;
      nEdges_Nodes+=2;
      Barabasi_Edges = (int *)realloc(Barabasi_Edges,nEdges_Nodes*sizeof(int));
      Barabasi_Edges[nEdges_Nodes-1]=i;
      Barabasi_Edges[nEdges_Nodes-2]=i;
    }
  }

  for (i=0;i<nNodes;i++){
    for (j=0;j<nNodes;j++){
      fprintf(file_barabasi, "%d ",Barabasi[i][j]);
    }
    fprintf(file_barabasi,"\n");
  }

  //======================================================================================================================

  fclose(file_barabasi);
  return 0;
}
