#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	float x,y,S,act;
}Neuron;

#define FILE_NAME "plot_Regular.dat"
#define DELTA_T 0.01

int main()
{
  FILE* file_output = fopen(FILE_NAME, "w");
  FILE* file_input = fopen("G_Regular.dat", "r");
  float Time=0;
  int i, j, Matrix[500][500], H;
  Neuron *Network = (Neuron *)calloc(500,sizeof(Neuron));
  char CallPlot[1000];

  srand((unsigned)time(NULL));

  for(i=0; i < 500; i++){
    for(j = 0; j < 500; j++) {
    	Matrix[i][j]=0;
    	if (!fscanf(file_input, "%d", &Matrix[i][j])) 
    	    break; 
    	}
  }

  fprintf(file_output,"#                                           Neuron                                          #\n");
  //fprintf(file_output,"Time ");

  for (i=0;i<500;i++){
  	Network[i].x=(1.0*(rand()%1000001)/1000000)*4 - 2;
  	Network[i].y=(1.0*(rand()%1000001)/1000000)*4;
  	Network[i].act=0.2;
  	Network[i].S=0;
    //fprintf(file_output,"Neuron%d ",i+1);
  }

  fprintf(file_output,"\n");

  while (Time<=10){

  	for(i=0;i<500;i++){
  		Network[i].S=0;
  		H=0;
  		for(j=0;j<500;j++){
  			if (Matrix[i][j]==1){
  				if (Network[j].x-0.5>=0){
  					H=1;
  				}
  				Network[i].S+=0.1*H;
  			}
  		}

  	}

    fprintf(file_output,"%f ",Time);

  	for (i=0;i<500;i++){
  		Network[i].x+=(3*Network[i].x)-(pow(Network[i].x,3))+2-(Network[i].y)+(Network[i].act)+(Network[i].S);
  		Network[i].y+=0.02*(6.0*(1+tanh(Network[i].x/0.1))-Network[i].y);
      fprintf(file_output,"%f ",Network[i].x);
  	}

    fprintf(file_output,"\n");

  	Time+=DELTA_T;
  }
  

  snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Neurons\';set xlabel \'Time\';set ylabel \'X\'; plot for [col=1:500] \'plot.dat\' using 0:col with lines title columnheader\"");

  system(CallPlot);
  printf("Done!\n");
  fclose(file_output);
  return 0;
}
