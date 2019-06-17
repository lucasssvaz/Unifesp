#include <stdio.h>
#include <stdlib.h>

int main()
{

  char CallPlot[1000];
  FILE *file_input, *file_output;

  file_input = fopen("G_Barabasi.dat", "r");
  file_output = fopen("test_Barabasi.dat", "w");

  int i, j, **Matrix = (int **)calloc(1000,sizeof(int *)), Aux[1000];

  for(i=0; i < 1000; i++){
    Matrix[i] = (int *)calloc(1000,sizeof(int));
    Aux[i]=0;
    for(j = 0; j < 1000; j++) {
    	Matrix[i][j]=0;
    	if (!fscanf(file_input, "%d", &Matrix[i][j])) 
    	    break; 
    	}
  }

  for (i=0;i<1000;i++){
    for(j=0;j<1000;j++){
      if (Matrix[i][j]!=0){
        Aux[i]++;
      }
    }
    fprintf(file_output,"%d ",Aux[i]);
  }

  fclose(file_input);
  fclose(file_output);
  printf("Done!\n");
  return 0;
}
