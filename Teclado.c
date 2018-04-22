#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 50001
//======================================================================================================= STRUCT

typedef struct {
  char Letra;
} Item;

typedef struct SCelula *Apontador;

typedef struct SCelula {
  Item Cont;
  Apontador Prox, Ant;
} Celula_Item;

typedef struct {
  int Tamanho;
  Apontador Inicio;
} Lista;

//======================================================================================================= FUNCTIONS

void Lista_Inicia(Lista *Lista){
  Lista->Inicio=NULL;
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

int Lista_Insere(Lista *Lista, int Pos, Item In){
  int i;
  Apontador Aux, Celula;
  Aux=Lista->Inicio;
  Celula = (Apontador) malloc(sizeof(Celula_Item));
  Celula->Cont=In;
  if (Celula == NULL)
    return 0;
  else if (Lista_Tamanho(Lista)==0){
    Lista->Inicio=Celula;
    Lista->Tamanho=1;
    return 1;
  } else if (Lista_Tamanho(Lista)==1){
      Celula->Prox=Lista->Inicio;
      Celula->Ant=Lista->Inicio;
      Lista->Inicio->Prox=Celula;
      Lista->Inicio->Ant=Celula;
      Lista->Tamanho++;
      if (Pos==0){
        Lista->Inicio=Celula;
      }
    return 1;
  } else if (Pos==0){
    Aux=Lista->Inicio->Ant;
    Lista->Inicio->Ant=Celula;
    Aux->Prox=Celula;
    Celula->Ant=Aux;
    Celula->Prox=Lista->Inicio;
    Lista->Tamanho++;
    Lista->Inicio=Celula;
    return 1;
  } else{
    for (i=0;i<Pos-1;i++){
      Aux=Aux->Prox;
    }
    Celula->Prox=Aux->Prox;
    Aux->Prox->Ant=Celula;
    Aux->Prox=Celula;
    Celula->Ant=Aux;
    Lista->Tamanho++;
    if (Pos==0){
      Lista->Inicio=Celula;
    }
    return 1;
  }
}

//-------------------------------------------------------

int Lista_Retira(Lista *Lista, int Pos, Item *Out){
  int i;
  Apontador Aux, Aux2;
  Aux=Lista->Inicio;
  if (Lista_Tamanho(Lista)==0)
    return 0;
  else if (Lista_Tamanho(Lista)==1){
    Aux=Lista->Inicio;
    *Out=Aux->Cont;
    free(Aux);
    Lista->Inicio=NULL;
    Lista->Tamanho--;
    return 1;
  } else if (Pos==0){
    Aux=Lista->Inicio->Ant;
    Lista->Inicio=Lista->Inicio->Prox;
    *Out=Aux->Prox->Cont;
    free(Aux->Prox);
    Aux->Prox=Lista->Inicio;
    Lista->Inicio->Ant=Aux;
    if (Lista_Tamanho(Lista)==2){
        Lista->Inicio->Prox=NULL;
        Lista->Inicio->Ant=NULL;
    }
    Lista->Tamanho--;
    return 1;
  } else if (Lista_Tamanho(Lista)==2){
    Aux=Lista->Inicio;
    if (Pos==1)
    Aux=Aux->Prox;
    *Out=Aux->Cont;
    Aux->Prox->Prox=NULL;
    Aux->Prox->Ant=NULL;
    free(Aux);
    Lista->Tamanho--;
  } else {
    for (i=0;i<Pos-1;i++){
        Aux=Aux->Prox;
    }
    Aux2=Aux->Prox->Prox;
    *Out=Aux->Prox->Cont;
    free(Aux->Prox);
    Aux2->Ant=Aux;
    Aux->Prox=Aux2;
    Lista->Tamanho--;
    return 1;
  }
}

//======================================================================================================= MAIN

int main(){
  char Input[INPUT_MAX];
  Apontador Aux;
  int ProxChar=0, i, tam;
  Item *IO;
  Lista *Output;

  IO = (Item *)malloc(sizeof(Item));
  Output = (Lista *)malloc(sizeof(Lista));

  Lista_Inicia(Output);
  gets(Input);
  tam=strlen(Input);

  for (i=0;i<tam;i++){
    switch (Input[i]) {
      case '[':
        ProxChar=0;
        break;
      case ']':
        ProxChar=Lista_Tamanho(Output);
        break;
      case '-':
        if (ProxChar!=0){
        ProxChar--;
          Lista_Retira(Output,ProxChar,IO);
        }
        break;
      case '<':
        if (ProxChar!=0){
          ProxChar--;
        }
        break;
      case '>':
        if (ProxChar<=Lista_Tamanho(Output)-1){
          ProxChar++;
        }
        break;
      default:
        IO->Letra=Input[i];
        Lista_Insere(Output,ProxChar,*IO);
        ProxChar++;
        break;
    }
  }

  Aux=Output->Inicio;
  for (i=0;i<Lista_Tamanho(Output);i++){
    printf("%c", Aux->Cont.Letra);
    Aux=Aux->Prox;
  }

  return 0;
}
