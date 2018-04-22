#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INPUT_MAX 32768

//------------------------------------------------STRUCT-------------------------------------------------------------

typedef struct
{
  int Id, Forca_Inicial, Forca_Atual;
} Item;

//------------------------------------------------------

typedef struct
 {
  Item Item[INPUT_MAX];
  int Inicio, Fim;
  int Lutadores_Max;
} Fila;

//-----------------------------------------------FUNCTIONS--------------------------------------------------------------

void Fila_Inicia(Fila *Fila) {
  Fila->Inicio=-1;
  Fila->Fim=-1;
}

//------------------------------------------------------

int Fila_Tamanho(Fila *Fila){
    if(Fila->Inicio <= Fila->Fim && Fila->Inicio != -1){
      return Fila->Fim - Fila->Inicio + 1;
    } else if(Fila->Inicio != -1){
      return INPUT_MAX - abs(Fila->Inicio - Fila->Fim) + 1;
    } else{
      return 0;
    }
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

int Fila_Colocar(Fila *Fila, Item In){
  if (Fila_Tamanho(Fila)==Fila->Lutadores_Max){
    return 0;
  } else {
    if (Fila_Tamanho(Fila)==0){
      Fila->Inicio=0;
      Fila->Fim=0;
      Fila->Item[0]=In;
    } else if ((Fila->Fim+1) >= (Fila->Lutadores_Max)){
      Fila->Fim=0;
      Fila->Item[0]=In;
    } else {
      Fila->Fim=Fila->Fim+1;
      Fila->Item[Fila->Fim]=In;
    }
    return 1;
  }
}

//------------------------------------------------------

int Fila_Retirar(Fila *Fila, Item *Out){
  if (Fila_Vazia(Fila)){
    return 0;
  } else if (Fila_Tamanho(Fila)==1){
    *Out=Fila->Item[Fila->Inicio];
    Fila->Item[Fila->Inicio].Id=0;
    Fila->Item[Fila->Inicio].Forca_Atual=0;
    Fila->Item[Fila->Inicio].Forca_Inicial=0;
    Fila->Inicio=-1;
    Fila->Fim=-1;
    return 1;
  } else {
    *Out=Fila->Item[Fila->Inicio];
    Fila->Item[Fila->Inicio].Id=0;
    Fila->Item[Fila->Inicio].Forca_Atual=0;
    Fila->Item[Fila->Inicio].Forca_Inicial=0;
    if ((Fila->Inicio+1) >= (Fila->Lutadores_Max)){
      Fila->Inicio=0;
    } else {
      Fila->Inicio++;
    return 1;
    }
  }
}

//-----------------------------------------------------MAIN------------------------------------------------------------

int main(){

  int Recover, Ordem, i, Forca;
  Fila *Fila_Lutadores;
  Item *Item_Subject1, *Item_Subject2;
  Fila_Lutadores=(Fila *) malloc(sizeof(Fila));
  Item_Subject1=(Item *) malloc(sizeof(Item));
  Item_Subject2=(Item *) malloc(sizeof(Item));

//------------------------------------------------------

  Fila_Inicia(Fila_Lutadores);
  scanf("%d %d", &Ordem, &Recover);
  Fila_Lutadores->Lutadores_Max=pow(2,Ordem);

//------------------------------------------------------

  for (i=0;i<Fila_Lutadores->Lutadores_Max;i++){
    scanf("%d", &Forca);
    Item_Subject1->Id=i+1;
    Item_Subject1->Forca_Inicial=Forca;
    Item_Subject1->Forca_Atual=Forca;
    Fila_Colocar(Fila_Lutadores, *Item_Subject1);

  }
    i=Fila_Tamanho(Fila_Lutadores);
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
      Fila_Colocar(Fila_Lutadores,*Item_Subject1);
    } else{
      Item_Subject2->Forca_Atual=Item_Subject2->Forca_Atual-Item_Subject1->Forca_Atual;
      Fila_Colocar(Fila_Lutadores,*Item_Subject2);
    }
  }
  i = Fila_Lutadores->Inicio;
  printf("%d\n", Fila_Lutadores->Item[i].Id);
  return 0;
}
