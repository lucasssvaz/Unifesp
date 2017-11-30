#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 1000
//======================================================================================================= STRUCT

typedef struct {
  char Nome[20];
} Item;

typedef struct {
  int Inicio, Fim;
  Item Item[INPUT_MAX];
} Lista;

//======================================================================================================= FUNCTIONS

void Lista_Inicia(Lista *Lista){
  Lista->Inicio=-1;
  Lista->Fim=-1;
}

//-------------------------------------------------------

int Lista_Vazia(Lista *Lista){
  if(Lista->Inicio==-1)
    return 1;
  else
    return 0;
}

//-------------------------------------------------------

int Lista_Tamanho(Lista *Lista){
  if (Lista_Vazia(Lista))
    return 0;
  else
    return Lista->Fim+1;
}

//-------------------------------------------------------

int Lista_Insere(Lista *Lista, int Pos, Item In){
  int i;
  if (Lista_Tamanho(Lista)==INPUT_MAX)
    return 0;
  else if (Lista_Tamanho(Lista)!=0){
    for (i=Pos-1;i<Lista->Fim;i++) {
      Lista->Item[i+1]=Lista->Item[i];
    }
    Lista->Item[Pos-1]=In;
    Lista->Fim++;
    return 1;
  } else {
      Lista->Inicio=0;
      Lista->Fim=0;
      Lista->Item[0]=In;
    return 1;
  }
}

//-------------------------------------------------------

int Lista_Retira(Lista *Lista, int Pos, Item *Out){
  int i;
  if (Lista_Tamanho(Lista)==0)
    return 0;
  else if (Lista_Tamanho(Lista)!=1){
    *Out=Lista->Item[Pos-1];
    for (i=Pos-1;i<Lista->Fim;i++){
      Lista->Item[i]=Lista->Item[i+1];
    }
    Lista->Fim--;
    return 1;
  } else {
    *Out=Lista->Item[Pos-1];
    Lista->Inicio=-1;
    Lista->Fim=-1;
    return 1;
  }
}

//-------------------------------------------------------

void Jogo(){
  int Child_N, K, i, Out=1, aux;
  Item *IO;
  Lista *Batata;
  IO = (Item *) malloc(sizeof(Item));
  Batata = (Lista *) malloc(sizeof(Lista));

  scanf("%d %d", &Child_N, &K);
  Lista_Inicia(Batata);

  for (i=0;i<Child_N;i++){
    scanf("%s", IO->Nome);
    Lista_Insere(Batata,i+1,*IO);
  }

  while (Lista_Tamanho(Batata)>0) {
  aux=Lista_Tamanho(Batata);
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
