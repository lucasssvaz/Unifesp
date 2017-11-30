#include <stdio.h>
#include <stdlib.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  int Id;
  Pointer Left, Right;
} Node;

typedef struct {
  Pointer Root;
} Tree;

//============================================================================================================

void Tree_Initialize(Tree *Tree){
  Tree->Root=NULL;
}

Node *Tree_Constructor(int *PreOrder,int *InOrder,int InLeftIndex,int InRightIndex,int Elements){
  static int PreIndex = 0;
  int i;
  Node *CurrentNode=NULL;
  int TreeRoot;
  if (PreIndex<Elements){
    TreeRoot=PreOrder[PreIndex];
  } else {
    return NULL;
  }
  for (i=InLeftIndex;i<=InRightIndex;i++){
    if (TreeRoot==InOrder[i]){
      CurrentNode=(Node *)malloc(sizeof(Node));
      CurrentNode->Id=TreeRoot;
      PreIndex++;
      if ((i-1)>=InLeftIndex){
        CurrentNode->Left=Tree_Constructor(PreOrder,InOrder,InLeftIndex,i-1,Elements);
      } else{
        CurrentNode->Left=NULL;
      }
      if ((i+1)<=InRightIndex){
        CurrentNode->Right=Tree_Constructor(PreOrder,InOrder,i+1,InRightIndex,Elements);
      } else{
        CurrentNode->Right=NULL;
      }
    }
  }
  return CurrentNode;
}

void Tree_Build(Tree *Tree,int *PreOrder,int *InOrder,int Elements){
  int LeftIndex,RightIndex;
  LeftIndex=0;
  RightIndex=Elements-1;
  Tree->Root=Tree_Constructor(PreOrder,InOrder,LeftIndex,RightIndex,Elements);
}

void Tree_Print(Node *Root){
  if (Root==NULL){
    return;
  }
  Tree_Print(Root->Left);
  Tree_Print(Root->Right);
  printf("%d\n",Root->Id);
}

//============================================================================================================

int main(){
  int i,j,Elements,*PreOrder,*InOrder;
  Tree *NewTree;

  NewTree=(Tree *)malloc(sizeof(Tree));
  Tree_Initialize(NewTree);

  scanf("%d",&Elements);

  PreOrder=(int *)calloc(Elements,sizeof(int));
  InOrder=(int *)calloc(Elements,sizeof(int));

  for (i=0;i<Elements;i++){
    scanf("%d",&PreOrder[i]);
  }
  for (i=0;i<Elements;i++){
    scanf("%d",&InOrder[i]);
  }

  Tree_Build(NewTree,PreOrder,InOrder,Elements);

  Tree_Print(NewTree->Root);

  return 0;
}
