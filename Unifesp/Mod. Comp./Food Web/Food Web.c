#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

#define FILE_NAME "plot.dat"
#define DELTA_T 0.01

int main()
{
  FILE* file_ptr = fopen(FILE_NAME, "w");
  FILE* file_input = fopen("inputC.txt", "r");
  float Time=0, Coef[6][6]={0}, Population[6], DeltaPop[6];
  int K, i, j;
  char CallPlot[1000];

  /* Grass = 0 |  */

  enum Pop {Grass,Rabbit,Insect,Lizard,Cobra,Bird};

  K=100;

  for(i=0;i<6;i++){
    for (j=0;j<6;j++){
        fscanf(file_input,"%f",&Coef[i][j]);
    }
  }
  for (j=0;j<6;j++){
        fscanf(file_input,"%f",&Population[j]);
  }

  fprintf(file_ptr,"#                                           Food Web                                          #\n");

  for (i=0;i<6;i++){
    fprintf(file_ptr, "#     ");
    for (j=0;j<6;j++){
      fprintf(file_ptr, "%f ",Coef[i][j]);
    }
    fprintf(file_ptr, "     #\n");
  }

  fprintf(file_ptr,"#    Time       |        Grass        |       Rabbit       |        Insect        |        Lizard        |        Cobra        |        Bird        #\n");
  fprintf(file_ptr,"   %f         %.10f          %.10f           %.10f             %.10f             %.10f           %.10f   \n",Time,Population[Grass],Population[Rabbit],Population[Insect],Population[Lizard],Population[Cobra],Population[Bird]);

  while (Time<1000*52){
    DeltaPop[Grass] = (Coef[Grass][Grass]*Population[Grass]*(1-(1.0*Population[Grass]/K)+(Coef[Grass][Rabbit]*Population[Rabbit])+(Coef[Grass][Insect]*Population[Insect])))*DELTA_T;

    DeltaPop[Rabbit] = (Population[Rabbit]*((Coef[Rabbit][Grass]*Population[Grass])+(Coef[Rabbit][Rabbit])+(Coef[Rabbit][Cobra]*Population[Cobra])+(Coef[Rabbit][Insect]*Population[Insect])))*DELTA_T;

    DeltaPop[Insect] = (Population[Insect]*((Coef[Insect][Grass]*Population[Grass])+(Coef[Insect][Insect])+(Coef[Insect][Rabbit]*Population[Rabbit])+(Coef[Insect][Lizard]*Population[Lizard])+(Coef[Insect][Bird]*Population[Bird])))*DELTA_T;

    DeltaPop[Lizard] = (Population[Lizard]*((Coef[Lizard][Insect]*Population[Insect])+(Coef[Lizard][Lizard])))*DELTA_T;

    DeltaPop[Cobra] = (Population[Cobra]*((Coef[Cobra][Bird]*Population[Bird])+(Coef[Cobra][Cobra])+(Coef[Cobra][Rabbit]*Population[Rabbit])))*DELTA_T;

    DeltaPop[Bird] = (Population[Bird]*((Coef[Bird][Insect]*Population[Insect])+(Coef[Bird][Bird])+(Coef[Bird][Cobra]*Population[Cobra])))*DELTA_T;


    for (i=0;i<6;i++){
      Population[i]+=DeltaPop[i];
      if (Population[i]<=0){
        Population[i]=0;
      }
    }


    Time+=DELTA_T;

    fprintf(file_ptr,"   %f         %.10f          %.10f           %.10f             %.10f             %.10f           %.10f   \n",Time,Population[Grass],Population[Rabbit],Population[Insect],Population[Lizard],Population[Cobra],Population[Bird]);

  }

  snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Population\';set xlabel \'Time\';set ylabel \'Population\'; set logscale y; set yrange [0.1:1000];plot \'plot.dat\' using 1:2 title \'Grass\' with line lt -1 lw 2 lc rgb \'green\', \\\n \'plot.dat\' using 1:3 title \'Rabbit\' with line lt -1 lw 2 lc rgb \'brown\', \\\n \'plot.dat\' using 1:4 title \'Insect\' with line lt -1 lw 2 lc rgb \'black\', \\\n \'plot.dat\' using 1:5 title \'Lizard\' with line lt -1 lw 2 lc rgb \'orange\', \\\n \'plot.dat\' using 1:6 title \'Cobra\' with line lt -1 lw 2 lc rgb \'blue\', \\\n \'plot.dat\' using 1:7 title \'Bird\' with line lt -1 lw 2 lc rgb \'yellow\'\"");

  system(CallPlot);
  printf("Done!\n");
  fclose(file_ptr);
  return 0;
}
