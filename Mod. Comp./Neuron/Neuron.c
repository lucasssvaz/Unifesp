#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FILE_NAME "plot.dat"
#define DELTA_T 0.01

int main()
{
  FILE* file_ptr = fopen(FILE_NAME, "w");
  float Time=0;
  int i, ;
  char CallPlot[1000];

  fprintf(file_ptr,"#                                           Neuron                                          #\n");

  while (Time<=1000){

  	Time+=DELTA_T;
  }
  

  snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Population\';set xlabel \'Time\';set ylabel \'Population\'; set logscale y; set yrange [0.1:1000];plot \'plot.dat\' using 1:2 title \'Grass\' with line lt -1 lw 2 lc rgb \'green\', \\\n \'plot.dat\' using 1:3 title \'Rabbit\' with line lt -1 lw 2 lc rgb \'brown\', \\\n \'plot.dat\' using 1:4 title \'Insect\' with line lt -1 lw 2 lc rgb \'black\', \\\n \'plot.dat\' using 1:5 title \'Lizard\' with line lt -1 lw 2 lc rgb \'orange\', \\\n \'plot.dat\' using 1:6 title \'Cobra\' with line lt -1 lw 2 lc rgb \'blue\', \\\n \'plot.dat\' using 1:7 title \'Bird\' with line lt -1 lw 2 lc rgb \'yellow\'\"");

  system(CallPlot);
  printf("Done!\n");
  fclose(file_ptr);
  return 0;
}
