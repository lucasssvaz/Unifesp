#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	float x,y,S,act;
}Neuron;

typedef struct {
  int Node, Links;
}Degree;

#define DELTA_T 0.01

void swap(Degree *xp, Degree *yp){
    Degree temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(Degree arr[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j].Links < arr[min_idx].Links)
            min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

int main()
{

  int nNeurons, nActive, Selection, Graph;
  char CallPlot[1000];
  FILE *file_output, *file_input; 

  printf("Number of neurons:\n");
  scanf("%d",&nNeurons);
  printf("Number of active neurons:\n");
  scanf("%d",&nActive);
  printf("Selection of active neurons: 1-Random, 2-Guided\n");
  scanf("%d",&Selection);
  printf("Graph type: 1-Regular, 2-Random, 3-Barabasi\n");
  scanf("%d",&Graph);

  int count=nNeurons/25;

  switch (Graph){
    case (1):
        file_output = fopen("plot_Regular.dat", "w");
        file_input = fopen("G_Regular.dat", "r");
        snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Neurons\';set xlabel \'Time\';set ylabel \'X\'; plot for [col=2:%d] \'plot_Regular.dat\' using 1:col with lines notitle\"", count+1);
        break;
    case (2):
        file_output = fopen("plot_Random.dat", "w");
        file_input = fopen("G_Random.dat", "r");
        snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Neurons\';set xlabel \'Time\';set ylabel \'X\'; plot for [col=2:%d] \'plot_Random.dat\' using 1:col with lines notitle\"", count+1);
        break;
    case (3):
        file_output = fopen("plot_Barabasi.dat", "w");
        file_input = fopen("G_Barabasi.dat", "r");
        snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Neurons\';set xlabel \'Time\';set ylabel \'X\'; plot for [col=2:%d] \'plot_Barabasi.dat\' using 1:col with lines notitle\"", count+1);
        break;
  }

  float Time=0;
  int i, j, **Matrix = (int **)calloc(nNeurons,sizeof(int *)), H, aux;
  Degree *Connections = (Degree *)calloc(nNeurons,sizeof(Degree));
  Neuron *Network = (Neuron *)calloc(nNeurons,sizeof(Neuron));

  srand((unsigned)time(NULL));

  for(i=0; i < nNeurons; i++){
    Matrix[i] = (int *)calloc(nNeurons,sizeof(int));
    for(j = 0; j < nNeurons; j++) {
    	Matrix[i][j]=0;
    	if (!fscanf(file_input, "%d", &Matrix[i][j])) 
    	    break; 
    	}
  }

  for (i=0;i<nNeurons;i++){
  	Network[i].x=(1.0*(rand()%100000001)/100000000)*4 - 2;
  	Network[i].y=(1.0*(rand()%100000001)/100000000)*4;
  	Network[i].act=-0.02;
  	Network[i].S=0;
    Connections[i].Node=i;
    for (j=0;j<nNeurons;j++){
      if (Matrix[i][j]==1) Connections[i].Links++;
    }
  }

  if (Selection==1){
    for (i=0;i<nActive;i++){
      do{
        aux = rand()%nNeurons;
      }while (Network[aux].act==0.2);
      Network[aux].act=0.2;
    }
  } else {
    selectionSort(Connections,nNeurons);
    for (i=0;i<nActive;i++){
      Network[Connections[i].Node].act=0.2;
    }
  }

  while (Time<=1000){

  	for(i=0;i<nNeurons;i++){
  		Network[i].S=0;
  		H=0;
  		for(j=0;j<nNeurons;j++){
  			if (Matrix[i][j]==1){
  				if (Network[j].x-0.5>=0){
  					H=1;
  				}
  				Network[i].S+=0.1*H;
  			}
  		}

  	}

    fprintf(file_output,"%f ",Time);

  	for (i=0;i<nNeurons;i++){
  		Network[i].x+=((3*Network[i].x)-(pow(Network[i].x,3))+(2)-(Network[i].y)+(Network[i].act)+(Network[i].S))*DELTA_T;
  		Network[i].y+=(0.02*(6.0*(1+tanh(1.0*Network[i].x/0.1))-Network[i].y))*DELTA_T;
      if (i%25==0){
        fprintf(file_output,"%f ",Network[i].x);
      } 
  	}

    fprintf(file_output,"\n");

  	Time+=DELTA_T;
  }

  system(CallPlot);
  printf("Done!\n");
  fclose(file_output);
  return 0;
}
