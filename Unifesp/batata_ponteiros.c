#include <stdio.h>
#include <stdlib.h>

//======================================================================================================= STRUCT

typedef struct {
  char Nome[20];
} Item;

typedef struct SCelula *Apontador;

typedef struct SCelula {
  Item Cont;
  Apontador Prox;
} Celula_Item;

typedef struct {
  int Tamanho;
  Apontador Inicio, Fim;
} Lista;

//======================================================================================================= FUNCTIONS

void Lista_Inicia(Lista *Lista){
  Lista->Inicio=NULL;
  Lista->Fim=NULL;
  Lista->Tamanho=0;
}

//-------------------------------------------------------

int Lista_Vazia(Lista *Lista){
  if(Lista->Tamanho==0)
    return 1;
  else
    return 0;
}

//-------------------------------------------------------

int Lista_Tamanho(Lista *Lista){
  return Lista->Tamanho;
}

//-------------------------------------------------------

int Lista_Insere(Lista *Lista, int Pos){
  int i;
  Apontador In, Aux;
  In = (Apontador) malloc(sizeof(Celula_Item));
  scanf("%s",In->Cont.Nome);
  if (In == NULL)
    return 0;
  else if (Lista_Tamanho(Lista)==0){
    Lista->Inicio=In;
    Lista->Fim=In;
    Lista->Tamanho=1;
    return 1;
  } else if (Pos==1){
      In->Prox=Lista->Inicio;
      Lista->Inicio=In;
      Lista->Tamanho++;
    return 1;
  } else if(Pos>Lista->Tamanho){
    Aux=Lista->Inicio;
    for (i=0;i<Lista->Tamanho-1;i++){
      Aux=Aux->Prox;
    }
    Aux->Prox=In;
    Lista->Fim=In;
    Lista->Tamanho++;
    return 1;
  } else{
    for (i=0;i<Pos-1;i++){
      Aux=Aux->Prox;
    }
    In->Prox=Aux->Prox;
    Aux->Prox=In;
    Lista->Tamanho++;
    return 1;
  }
}

//-------------------------------------------------------

int Lista_Retira(Lista *Lista, int Pos, Item *Out){
  int i;
  Apontador Aux, Aux2;
  if (Lista_Tamanho(Lista)==0)
    return 0;
  else if (Lista_Tamanho(Lista)==1){
    Aux=Lista->Inicio;
    *Out=Aux->Cont;
    free(Aux);
    Lista->Inicio=NULL;
    Lista->Fim=NULL;
    Lista->Tamanho--;
    return 1;
  } else if (Pos==1){
    Aux=Lista->Inicio;
    Lista->Inicio=Lista->Inicio->Prox;
    *Out=Aux->Cont;
    free(Aux);
    Lista->Tamanho--;
    return 1;
  } else if (Pos>=Lista_Tamanho(Lista)) {
    Aux=Lista->Inicio;
    for (i=0;i<Lista_Tamanho(Lista)-2;i++){
      Aux=Aux->Prox;
    }
    Lista->Fim=Aux;
    Aux=Aux->Prox;
    *Out=Aux->Cont;
    free(Aux);
    Lista->Fim->Prox=NULL;
    Lista->Tamanho--;
    return 1;
  } else {
    Aux=Lista->Inicio;
    for (i=0;i<Pos-2;i++){
        Aux=Aux->Prox;
    }
    Aux2=Aux->Prox->Prox;
    *Out=Aux->Prox->Cont;
    free(Aux->Prox);
    Aux->Prox=Aux2;
    Lista->Tamanho--;
    return 1;
  }
}

//-------------------------------------------------------

void Jogo(){
  int Child_N, K, i, Out=1;
  Item *IO;
  Lista *Batata;
  IO = (Item *) malloc(sizeof(Item));
  Batata = (Lista *) malloc(sizeof(Lista));

  scanf("%d %d", &Child_N, &K);
  Lista_Inicia(Batata);

  for (i=0;i<Child_N;i++){
    Lista_Insere(Batata,i+1);
  }

  while (Lista_Tamanho(Batata)>0) {
  for (i=0;i<K;i++){
    if(Out>Lista_Tamanho(Batata)){
        Out=1;
    }
    Out++;
    if(Out>Lista_Tamanho(Batata)){
        Out=1;
    }
  }

    Lista_Retira(Batata,Out,IO);
    printf("%s\n", IO->Nome);
  }
}

//======================================================================================================= MAIN

int main(){

  Jogo();

  return 0;
}
