#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// "SEI(D/RS)" Susceptible -> Exposed -> Infected -> (Dead / Recovered -> Susceptible)

typedef struct {
    int Status, Timer, Imn; //Infec: 0 = Sus, 1 = Exp, 2 = Inf, 3 = Rec, 4 = Dead
    float Life, Age, Base;
} Node;

typedef struct {
    int Node, Links;
} Degree;

#define DELTA_T 1

//==================================================================================================================

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
            if (arr[j].Links > arr[min_idx].Links)
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

float Base_Calc(float x) {
    if (x>=0 && x<0.8) {
        return (93.75/100)*x + 0.90;
    } else if (x>=0.8 && x<70) {
        return 1 - (1.0*85/(100*(1+pow((x-0.8)/3,3.2))));
    } else {
        return 0.25 + 0.75*(1-(exp(x-75))/((exp(x-75))+1));
    }
}

//==================================================================================================================

int main(){

    int nNodes, nActive, Selection, Graph, nImmune, Sel_Immune, nDead = 0, nInf = 0, nExp, nCured = 0, nSus, Start;
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
    
    Start = nActive;
//---------------------------------------------------------------------------

    float C,S,R,p1,p2,p3,l,m,n;
    int i, j, **Matrix = (int **)calloc(nNodes,sizeof(int *)), aux;
    int count;
    unsigned int Time = 0;
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

    nSus = nNodes - nActive - nImmune;
    nExp = nActive;


    for (i=0; i<nNodes; i++) {
        Network[i].Life = 100;
        Network[i].Timer = 0;
        Network[i].Age = (1.0*(rand()%101)/100)*80;
        Network[i].Base = 1.0*Base_Calc(Network[i].Age);
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
            } while (Network[aux].Status == 1 || Network[aux].Imn == 1);
            Network[aux].Status = 1;
        }
    } else {
        for (i=0; i<nActive; i++) {
            if (Network[Connections[i].Node].Imn == 0)
                Network[Connections[i].Node].Status = 1;
            else
                nActive++;
        }
    }

//---------------------------------------------------------------------------

    p1 = -0.75*Infec+1;
    p2 = -0.85*Infec+1;
    p3 = -1.00*Infec+1;

    l = -(-p1+2*p2-p3)/5000;
    m = (-p1+4*p2-3*p3)/100;
    n = p3;

    fprintf(file_output,"Time Dead Infected Exposed Cured Susceptible Immune\n");

    while (Time<=10000) {

        for (i=0;i<nNodes;i++){
                if(Network[i].Status == 1 || Network[i].Status == 2 || Network[i].Status == 3) {
                    Network[i].Timer+=DELTA_T;
                }

                //printf("%d %d ",i,Network[i].Status);

                if (Network[i].Life < 100 && Network[i].Status != 2 && Network[i].Status != 4){
                    Network[i].Life+=0.5;
                }


                if (Network[i].Timer >= 200 && (Network[i].Status == 1 || Network[i].Status == 3)) {
                    Network[i].Timer = 0;
                    if (Network[i].Status == 1) {
                        Network[i].Status = 2;
                        nExp--;
                        nInf++;
                        //printf("INFECTADO ");

                    } else {
                        Network[i].Status = 0;
                        //printf("SAUDAVEL ");
                        nCured--;
                        nSus++;
                    }
                }

                if (Network[i].Status == 2){
                    Network[i].Life-=1;
                    if (Network[i].Life <= 0) {
                        Network[i].Timer = 0;
                        Network[i].Status = 4;
                        //printf("MORTO ");
                        nDead++;
                        nInf--;
                    } else {
                        Prob = (3.0/400000*pow(Network[i].Timer,2))+(9.0/4000*Network[i].Timer)+(1.0/20);
                        if (1.0*(rand()%(RAND_MAX))/RAND_MAX <= Prob){
                            Prob = (l*pow(Network[i].Life,2)) + (m*Network[i].Life) + n;
                            if (1.0*(rand()%(RAND_MAX))/RAND_MAX <= Prob){
                                Network[i].Timer = 0;
                                Network[i].Status = 3;
                                //printf("CURADO ");
                                nInf--;
                                nCured++;
                            }
                        }
                   }
                }
                //printf("%d %f\n",Network[i].Timer,Network[i].Life );
        }




        for(i=0; i<nNodes; i++) {
            if (Network[i].Status == 0 && Network[i].Imn == 0) {
                Prob = 1;

                for(j=0; j<nNodes; j++) {
                    C = 0;
                    if (Matrix[i][j]!=0) {
                        if (Network[j].Status==1){
                            C = 0.8;
                        }
                        else if (Network[j].Status==2) {
                            C = 1;
                        } else if (Network[j].Status==4){
                            C = 0.1;
                        }
                        S = ((-1.0/20000)*pow(Matrix[i][j],2)+0.01*Matrix[i][j]);
                        R = (((1.0*(rand()%101)/100)/4)+0.75);

                        Prob*=1-((Infec*C*sin(R*S*M_PI)*(Network[i].Base+1))/2);
                        
                    }
                }
                if(1.0*(rand()%(RAND_MAX))/RAND_MAX>=Prob) {
                    //printf("DOENTE\n");
                    nSus--;
                    nExp++;
                    Network[i].Status = 1;
                }
            }

        }

        fprintf(file_output,"%u ",Time);
            
        fprintf(file_output,"%d %d %d %d %d %d ",nDead, nInf, nExp, nCured, nSus, nImmune);

        fprintf(file_output,"\n");
            

        Time+=DELTA_T;
    
    }

    //---------------------------------------------------------------------------

    snprintf(CallPlot,sizeof(CallPlot),"gnuplot -p -e \"set terminal x11 enhanced background rgb \'grey\';set key outside; set key center top;set title \'Infec = %f, Start Infected = %d, Immune = %d, Sel = %s,%s\';set xlabel \'Time\';set yrange[0:2000];set ylabel \'Status\'; plot for [col=2:8] \'plot_Barabasi.dat\' using 1:col with lines title columnheader\"",Infec,Start,nImmune,Selection==1 ? "Random" : "Guided",Sel_Immune==1 ? "Random" : "Guided");
    system(CallPlot);
    printf("Done!\n");
    fclose(file_input);
    fclose(file_output);
    return 0;
}
