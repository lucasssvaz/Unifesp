#include <stdio.h>
#include <stdlib.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  int Id;
  Pointer Sons, Brothers;
} Node;

typedef struct {
  Pointer Root;
} Tree;

//============================================================================================================

void Tree_Initialize(Tree *Tree){
  Tree->Root=NULL;
}

void Tree_Search(Node *Root, int Id, Node **Add){
  if (Root==NULL){
    return;
  }
  if (Root->Id==Id){
    *Add=Root;
  }
  Tree_Search(Root->Sons,Id,Add);
  Tree_Search(Root->Brothers,Id,Add);
}

void Tree_Print(Node *Root){
    Node *auxF, *auxI;
  if (Root==NULL){
    return;
  }
  auxF=Root->Sons;
auxI=Root->Brothers;
  printf("(%d",Root->Id);
  Tree_Print(auxF);
  printf(")");
  Tree_Print(auxI);
}

//============================================================================================================

int main(){

  Node *NewNode,*Aux=NULL;
  int N,M,i,Father,Son;
  Tree *Dynasty;

  Dynasty=(Tree *)malloc(sizeof(Tree));
  Tree_Initialize(Dynasty);

  scanf("%d %d",&N,&M);

  NewNode=(Pointer)malloc(sizeof(Node));
  NewNode->Id=1;
  NewNode->Sons=NULL;
  NewNode->Brothers=NULL;
  Dynasty->Root=NewNode;

  for (i=0;i<M;i++){
    scanf("%d %d",&Father,&Son);
    Tree_Search(Dynasty->Root,Father,&Aux);
    if(Aux->Sons!=NULL){
    Aux=Aux->Sons;
    while (Aux->Brothers!=NULL){
        Aux=Aux->Brothers;
    }
    NewNode=(Pointer)malloc(sizeof(Node));
    NewNode->Id=Son;
    NewNode->Sons=NULL;
    NewNode->Brothers=NULL;
    Aux->Brothers=NewNode;
    } else{
    NewNode=(Pointer)malloc(sizeof(Node));
    NewNode->Id=Son;
    NewNode->Sons=NULL;
    NewNode->Brothers=NULL;
    Aux->Sons=NewNode;
    }
  }
  Tree_Print(Dynasty->Root);

  return 0;
}
