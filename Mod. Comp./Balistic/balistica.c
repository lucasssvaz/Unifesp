#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FILE_NAME "plot.dat"
#define DELTA_T 0.01

int main()
{
  FILE* file_ptr = fopen(FILE_NAME, "w");
  float V0,G,Theta,M,K,Rad,Vx,Vy,Sx,Sy,Ec,Time;
  int Collision;
  char CallPlot[500];

  printf("Initial Velocity (M/S):\n");
  scanf("%f",&V0);
  printf("Gravity (Absolute value) (M/S^2):\n");
  scanf("%f",&G);
  printf("Initial Height (Meters):\n");
  scanf("%f",&Sy);
  printf("Initial Distance (Meters):\n");
  scanf("%f",&Sx);
  printf("Launch Angle (Degrees):\n");
  scanf("%f",&Theta);
  printf("Projectile Mass (Kg):\n");
  scanf("%f",&M);
  printf("Drag Coefficient:\n");
  scanf("%f",&K);
  printf("Enter \'1\' for elastic collision and \'2\' for inelastic collision:\n");
  scanf("%d",&Collision);

  Rad=(M_PI*Theta)/180;

  Vx=V0*cos(Rad);
  Vy=V0*sin(Rad);
  Ec=M*V0*V0/2;

  fprintf(file_ptr,"#                                           Drag Simulation                                          #\n");
  fprintf(file_ptr,"#| V0 = %f | G = %f | Sx0 = %f | Sy0 = %f | Theta = %f | M = %f | K = %f | Collision = %d |#\n",V0,G,Sx,Sy,Theta,M,K,Collision);
  fprintf(file_ptr,"######################################################################################################\n");
  fprintf(file_ptr,"# |     Sx     |     Sy     |     Vx     |     Vy     |     Ec     |     Time     | #\n");

  snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Trajectory using V0=%.3f,G=%.3f,Sx0=%.3f,H0=%.3f,Theta=%.3f,M=%.3f,K=%.3f,Collision=%.0d (Rounded)\';set xlabel \'Meters\';set ylabel \'Meters\';plot \'plot.dat\' using 1:2 with line lt -1 lw 2 lc rgb \'red\'\"",V0,G,Sx,Sy,Theta,M,K,Collision); //340 chars

  while (((abs(Vy)>=0.001)||(Vx>=0.001))&&(Time<=10)){

  	if (Sy<0){
  	  Sy=0;
  	  if (Collision == 1){  //elastic
  	    Vy=-Vy;
  	  } else{
  	    Vy=0;
  	    Vx=0;
        Ec=0;
  	  }
  	}

    fprintf(file_ptr,"     %f   %f     %f   %f   %f    %f\n",Sx,Sy,Vx,Vy,Ec,Time);

    Vx=Vx+(-K/M*Vx)*DELTA_T;
    Vy=Vy+(-G-K/M*Vy)*DELTA_T;
    Time+=DELTA_T;

    Sx=Sx+Vx*DELTA_T;
    Sy=Sy+Vy*DELTA_T;

    Ec=M*sqrt(pow(Vx,2)+pow(Vy,2))*sqrt(pow(Vx,2)+pow(Vy,2))/2;
  }

  system(CallPlot);
  printf("Done!\n");
  fclose(file_ptr);
  return 0;
}
