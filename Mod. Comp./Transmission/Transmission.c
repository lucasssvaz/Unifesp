#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// "SEI(D/RS)" Susceptible -> Exposed -> Infected -> (Dead / Recovered -> Susceptible)

typedef struct {
    int Status, Imn; //Infec: 0 = Sus, 1 = Exp, 2 = Inf, 3 = Rec, 4 = Dead
    float Life, Timer, Age, Base;
} Node;

typedef struct {
    int Node, Links;
} Degree;

#define DELTA_T 1

void swap(Degree *xp, Degree *yp) {
    Degree temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(Degree arr[], int n) {
    int i, j, min_idx;
    for (i=0; i<n-1; i++) {
        min_idx = i;
        for (j=i+1; j<n; j++)
            if (arr[j].Links < arr[min_idx].Links)
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

float Base_Calc(float x) {
    if (x>=0 && x<0.8) {
        return 93.75*x + 90;
    } else if (x>=0.8 && x<70) {
        return 100 - (85/(1+pow((x-0.8)/3,3.2)));
    } else {
        return 25 + 75*(1-(exp(x-75))/((exp(x-75))+1));
    }
}

int main(){

    int nNodes, nActive, Selection, Graph, nImmune, Sel_Immune;
    float Infec, Prob;
    char CallPlot[1000];
    FILE *file_output, *file_input;

    printf("Number of nodes:\n");
    scanf("%d",&nNodes);
    printf("Number of infected nodes:\n");
    scanf("%d",&nActive);
    printf("Selection of active nodes: 1-Random, 2-Guided\n");
    scanf("%d",&Selection);
    printf("Number of immune nodes:\n");
    scanf("%d",&nImmune);
    printf("Selection of immune nodes: 1-Random, 2-Guided\n");
    scanf("%d",&Sel_Immune);
    printf("Disease infectivity (0.0-1.0)\n");
    scanf("%f",&Infec);

    file_output = fopen("plot_Barabasi.dat", "w");
    file_input = fopen("G_Barabasi.dat", "r");
    snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Neurons\';set xlabel \'Time\';set ylabel \'X\'; plot for [col=2:%d] \'plot_Barabasi.dat\' using 1:col with lines notitle\"", count+1);


    float C;
    int Time, i, j, **Matrix = (int **)calloc(nNodes,sizeof(int *)), aux;
    Degree *Connections = (Degree *)calloc(nNodes,sizeof(Degree));
    Node *Network = (Node *)calloc(nNodes,sizeof(Node));

    srand((unsigned)time(NULL));

    for(i=0; i < nNodes; i++) {
        Matrix[i] = (int *)calloc(nNodes,sizeof(int));
        for(j = 0; j < nNodes; j++) {
            Matrix[i][j]=0;
            if (!fscanf(file_input, "%d", &Matrix[i][j]))
                break;
        }
    }

    for (i=0; i<nNodes; i++) {
        Network[i].Life = 100;
        Network[i].Timer = 0;
        Network[i].Age = (1.0*(rand()%101)/100)*80;
        Network[i].Base = 1.0*Base_Calc(Network[i].Age)/100;
        Network[i].Status = 0;

        Connections[i].Node=i;
        for (j=0; j<nNodes; j++) {
            if (Matrix[i][j]!=0) Connections[i].Links++;
        }
    }

    selectionSort(Connections,nNodes);

    if (Sel_Immune==1) {
        for (i=0; i<nImmune; i++) {
            do {
                aux = rand()%nNodes;
            } while (Network[aux].Imn == 1);
            Network[aux].Imn = 1;
        }
    } else {
        for (i=0; i<nImmune; i++) {
            Network[Connections[i].Node].Imn = 1;
        }
    }

    if (Selection==1) {
        for (i=0; i<nActive; i++) {
            do {
                aux = rand()%nNodes;
            } while (Network[aux].Status == 1);
            Network[aux].Status = 1;
        }
    } else {
        for (i=0; i<nActive; i++) {
            Network[Connections[i].Node].Status = 1;
        }
    }

    while (Time<=1000000) {

        for (i=0;i<nNodes;i++){
                if(Network[i].Status == 1 || Network[i].Status == 3) {
                    Network[i].Timer+=DELTA_T;
                }

                if(Network[i].Status == 2) {
                    Network[i].Timer+=DELTA_T;
                }

                if (Network[i].Status == 2){

                }

                if (Network[i].Timer>=20) {
                    Network[i].Timer = 0;
                    if (Network[i].Status == 1) {
                        Network[i].Status = 2;
                    } else {
                        Network[i].Status = 0;
                    }
                }


        }




        for(i=0; i<nNodes; i++) {
            if (Network[i].Status != 4) {
                Prob = 1;

                for(j=0; j<nNodes; j++) {
                    C = 0;
                    if (Matrix[i][j]!=0) {
                        if (Network[j].Status==1) C = 0.8;
                        else if (Network[j].Status==2) C = 1;
                        Prob*=1-(Infec*C*sin(((-1.0/20000)*pow(Matrix[i][j],2)+0.01*Matrix[i][j])*M_PI)*(Network[i].Base+1))/2;
                    }
                }
                if((rand()%10001)/10000>=Prob) {
                    Network[i].Status = 1;
                }
            }

            fprintf(file_output,"%f %d",Time,Network[i].Status);

            fprintf(file_output,"\n");

            Time+=DELTA_T;
        }

    }

    system(CallPlot);
    printf("Done!\n");
    fclose(file_input);
    fclose(file_output);
    return 0;
}
