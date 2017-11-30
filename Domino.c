#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 7
//======================================================================================================= STRUCT

typedef struct SGraph *Pointer;

typedef struct {
  int Inicio, Fim;
  Pointer Item[INPUT_MAX];
} Lista;

typedef struct SGraph{
  int Id;
  Lista *Pares;
} Graph;

//======================================================================================================= FUNCTIONS

void Lista_Inicia(Graph *Graph){
  int i;
  Graph->Pares->Inicio=0;
  Graph->Pares->Fim=INPUT_MAX-1;
  for (i=0;i<INPUT_MAX;i++){
    Graph->Pares->Item[i]=NULL;
  }
}

//-------------------------------------------------------

void Grafo_Insere(Graph *Grafo, int Pos, Graph *In){
  Grafo->Pares->Item[Pos]=In;
  Grafo->Pares->Item[Pos]->Pares->Item[Grafo->Id]=Grafo;
}

//-------------------------------------------------------

Pointer Grafo_Retira(Graph *Grafo, int Pos){
    Graph *Out;
    if (Grafo==NULL){
      return NULL;
    }
    Out=Grafo->Pares->Item[Pos];
    Grafo->Pares->Item[Pos]->Pares->Item[Grafo->Id]=NULL;
    Grafo->Pares->Item[Pos]=NULL;
    return Out;
}

//-------------------------------------------------------

void Domino_Percorre(Graph *Start){
  int i;
  Graph *Aux=NULL;

  if (Start==NULL)
    return;

  if(Start->Pares->Item[Start->Id]!=NULL){
    Aux=Grafo_Retira(Start,Start->Id);
  } else {
    for (i=INPUT_MAX;i>0;i--){
      if (Start->Pares->Item[i]!=NULL){
        Aux=Start->Pares->Item[i];
      }
    }
    }
    Aux=Grafo_Retira(Start,Aux->Id);
    Domino_Percorre(Aux);

}

//-------------------------------------------------------

int Domino_Possivel(Graph **P){
    int Possivel=1,i,j,cont=0;
    Graph *Start=NULL,*Start2=NULL;

    for (i=INPUT_MAX;i>0;i--){
      if(P[i]->Pares->Item[i]!=NULL)
        Start=P[i]->Pares->Item[i];
    }
    if (Start==NULL){
      while (Start==NULL){
        for(i=0;i<INPUT_MAX;i++){
          for (j=0;j<INPUT_MAX;j++){
            Start=P[i]->Pares->Item[j];
          }
        }
      }
    }

    Start2=Start;

    Domino_Percorre(Start);
    Domino_Percorre(Start2);

    for (i=0;i<INPUT_MAX;i++){
      for (j=0;j<INPUT_MAX;j++){
        if (P[i]->Pares->Item[j]!=NULL){
          cont++;
        }
      }
    }

    if (cont!=0)
      Possivel=0;

    return Possivel;
}

//======================================================================================================= MAIN

int main(){

  int i=0,N,P0,P1;
  Graph *P[INPUT_MAX];

  for (i=0;i<INPUT_MAX;i++){
    P[i]=(Graph *)malloc(sizeof(Graph));
    Lista_Inicia(P[i]);
    P[i]->Id=i;
  }

  scanf("%d",&N);
  for (i=0;i<N;i++){
    scanf("%d %d",&P0,&P1);
    Grafo_Insere(P[P0],P1,P[P1]);
  }

  printf("%d\n",Domino_Possivel(P));


  return 0;
}
