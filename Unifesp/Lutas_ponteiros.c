#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//------------------------------------------------STRUCT-------------------------------------------------------------

typedef struct
{
  int Id, Forca_Inicial, Forca_Atual;
} Item;

//------------------------------------------------------

typedef struct SCelula *Apontador;

//------------------------------------------------------

typedef struct SCelula
{
  Item Cont;
  Apontador Prox;
} Celula_Item;

//------------------------------------------------------

typedef struct Fila
 {
  Apontador Inicio, Fim;
  int Tamanho;
} Fila;

//-----------------------------------------------FUNCTIONS--------------------------------------------------------------

void Fila_Inicia(Fila *Fila) {
  Fila->Inicio=NULL;
  Fila->Fim=NULL;
  Fila->Tamanho=0;
}

//------------------------------------------------------

int Fila_Tamanho(Fila *Fila){
  return Fila->Tamanho;
}

//------------------------------------------------------

int Fila_Vazia(Fila *Fila){
  if (Fila_Tamanho(Fila) > 0){
    return 0;
  } else {
    return 1;
  }
}

//------------------------------------------------------

int Fila_Colocar(Fila *Fila, Apontador In){
  if (Fila_Tamanho(Fila)==0){
      Fila->Inicio=In;
      Fila->Fim=In;
      Fila->Tamanho=1;
  } else{
    Fila->Fim->Prox=In;
    Fila->Fim=In;
    Fila->Tamanho++;
    return 1;
  }
}

//------------------------------------------------------

int Fila_Retirar(Fila *Fila, Item *Out){
  Apontador Aux;
  if (Fila_Vazia(Fila)){
    return 0;
  }
  if (Fila_Tamanho(Fila)==1){
    Aux=Fila->Inicio;
    Fila->Inicio=NULL;
    Fila->Fim=NULL;
    Fila->Tamanho=0;
    *Out=Aux->Cont;
    free(Aux);
    return 1;
  }
  if (Fila_Tamanho(Fila)>1) {
    Aux=Fila->Inicio;
    Fila->Inicio=Fila->Inicio->Prox;
    *Out=Aux->Cont;
    Fila->Tamanho--;
    free(Aux);
    return 1;
    }
}

//-----------------------------------------------------MAIN------------------------------------------------------------

int main(){

  int Recover, Ordem, i, Forca;
  Fila *Fila_Lutadores;
  Item *Item_Subject1, *Item_Subject2;
  Apontador Item_In;
  Fila_Lutadores=(Fila *) malloc(sizeof(Fila));
  Item_Subject1=(Item *) malloc(sizeof(Item));
  Item_Subject2=(Item *) malloc(sizeof(Item));

//------------------------------------------------------

  Fila_Inicia(Fila_Lutadores);
  scanf("%d %d", &Ordem, &Recover);

//------------------------------------------------------

  for (i=0;i<pow(2,Ordem);i++){
    scanf("%d", &Forca);
    Item_Subject1->Id=i+1;
    Item_Subject1->Forca_Inicial=Forca;
    Item_Subject1->Forca_Atual=Forca;
    Item_In = (Apontador) malloc(sizeof(Celula_Item));
    Item_In->Prox=NULL;
    Item_In->Cont=*Item_Subject1;
    Fila_Colocar(Fila_Lutadores, Item_In);

  }
//------------------------------------------------------
  while (Fila_Tamanho(Fila_Lutadores)>1){
    Fila_Retirar(Fila_Lutadores,Item_Subject1);
    Fila_Retirar(Fila_Lutadores,Item_Subject2);

    if ((Item_Subject1->Forca_Atual+Recover)>(Item_Subject1->Forca_Inicial)){
      Item_Subject1->Forca_Atual=Item_Subject1->Forca_Inicial;
    } else {
      Item_Subject1->Forca_Atual=Item_Subject1->Forca_Atual+Recover;
    }

    if ((Item_Subject2->Forca_Atual+Recover)>(Item_Subject2->Forca_Inicial)){
      Item_Subject2->Forca_Atual=Item_Subject2->Forca_Inicial;
    } else {
      Item_Subject2->Forca_Atual=Item_Subject2->Forca_Atual+Recover;
    }

    if (Item_Subject1->Forca_Atual>=Item_Subject2->Forca_Atual){
      Item_Subject1->Forca_Atual=Item_Subject1->Forca_Atual-Item_Subject2->Forca_Atual;
      Item_In = (Apontador) malloc(sizeof(Celula_Item));
      Item_In->Prox=NULL;
      Item_In->Cont=*Item_Subject1;
      Fila_Colocar(Fila_Lutadores, Item_In);
    } else{
      Item_Subject2->Forca_Atual=Item_Subject2->Forca_Atual-Item_Subject1->Forca_Atual;
      Item_In = (Apontador) malloc(sizeof(Celula_Item));
      Item_In->Prox=NULL;
      Item_In->Cont=*Item_Subject2;
      Fila_Colocar(Fila_Lutadores, Item_In);
    }
  }
  printf("%d\n", Fila_Lutadores->Inicio->Cont.Id);
  free(Fila_Lutadores->Inicio);
  free(Fila_Lutadores);
  return 0;
}
