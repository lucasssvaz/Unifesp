#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  char Name[15];
  int *Year;
  int Size;
  Pointer Left, Right;
  int BF;
} Node;

typedef struct {
  Pointer Root;
} Tree;

//==================================================================================================

int max(int a, int b){
	if (a>=b){
		return a;
	} else {
		return b;
	}
}

void Tree_Initialize(Tree *Queue){
  Queue->Root=NULL;
}

int Node_Height(Node *No){
	if (No==NULL)
		return -1;
	else
		return max(Node_Height(No->Left),Node_Height(No->Right))+1;
}

void Tree_BF(Node *No){

  if (No==NULL){
    return;
  }

  	Tree_BF(No->Left);
  	Tree_BF(No->Right);
	No->BF=Node_Height(No->Left)-Node_Height(No->Right);

	return;
}

void Rotate_LL(Node **No){
	Node *pB;

	pB = (*No)->Left;
	(*No)->Left = pB->Right;
	pB->Right = *No;
	*No = pB;

	return;
}

void Rotate_RR(Node **No){
	Node *pB;

	pB = (*No)->Right;
	(*No)->Right = pB->Left;
	pB->Left = *No;
	*No = pB;

	return;
}

void Rotate_LR(Node **No){
	Node *pB, *pC;

	pB = (*No)->Left;
	pC = pB->Right;
	pB->Right = pC->Left;
	pC->Left = pB;
	(*No)->Left = pC->Right;
	pC->Right = *No;
	*No = pC;

	return;
}

void Rotate_RL(Node **No){
	Node *pB, *pC;

	pB = (*No)->Right;
	pC = pB->Left;
	pB->Left = pC->Right;
	pC->Right = pB;
	(*No)->Right = pC->Left;
	pC->Left = *No;
	*No = pC;

	return;
}


void Fix_AVL(Tree *Queue, Node **No){
	if (*No==NULL){
    	return;
  	}

  	Fix_AVL(Queue,&((*No)->Left));
  	Fix_AVL(Queue,&((*No)->Right));

  	if(abs((*No)->BF)>1){
  		if ((*No)->BF>0){
  			if((*No)->Left->BF>0){
  				Rotate_LL(No);
  			} else {
  				Rotate_LR(No);
  			}
  		} else {
  			if ((*No)->Right->BF>0){
  				Rotate_RL(No);
  			} else {
  				Rotate_RR(No);
  			}
  		}
  		Tree_BF(Queue->Root);
  	}

  	return;
}

void Tree_Insert(Tree *Queue, char Item[15], int Ano){
	Node *CurrentNode, *Aux = (Node *) malloc(sizeof(Node));
	strcpy(Aux->Name,Item);
	Aux->BF=0;
	Aux->Size=1;
	Aux->Year = (int*) malloc(sizeof(int));
	Aux->Year[0] = Ano;
	Aux->Left=NULL;
	Aux->Right=NULL;

	if (Queue->Root==NULL){
		Queue->Root=Aux;
		return;
	}

	CurrentNode = Queue->Root;

	while (CurrentNode!=NULL){
		if (strcmp(Item,CurrentNode->Name)<=0){
			if (CurrentNode->Left==NULL){
				CurrentNode->Left=Aux;
				CurrentNode=NULL;
			} else {
				CurrentNode=CurrentNode->Left;
			}
		} else {
			if (CurrentNode->Right==NULL){
				CurrentNode->Right=Aux;
				CurrentNode=NULL;
			} else {
				CurrentNode=CurrentNode->Right;
			}
		}
	}

	Tree_BF(Queue->Root);

	Fix_AVL(Queue,&(Queue->Root));

	return;
}

Node *Tree_Search(Tree *Queue, char Item[15]){
	Node *CurrentNode, *CurrentFather, *SearchFather=NULL;

	if (Queue->Root==NULL){
		return SearchFather;
	}

	CurrentFather = Queue->Root;

	if (strcmp(Item,CurrentFather->Name)==0){
		return CurrentFather;
	}

	CurrentNode = Queue->Root->Left;

	while (CurrentNode!=NULL){
		if (strcmp(Item,CurrentNode->Name)==0){
			SearchFather = CurrentFather;
			CurrentNode=NULL;
		} else {
			if (strcmp(Item,CurrentNode->Name)<0){
				CurrentFather=CurrentNode;
				CurrentNode=CurrentNode->Left;
			} else {
				CurrentFather=CurrentNode;
				CurrentNode=CurrentNode->Right;
			}
		}
	}

	CurrentFather = Queue->Root;
	CurrentNode = Queue->Root->Right;

	while (CurrentNode!=NULL && SearchFather==NULL){
		if (strcmp(Item,CurrentNode->Name)==0){
			SearchFather = CurrentFather;
			CurrentNode=NULL;
		} else {
			if (strcmp(Item,CurrentNode->Name)<0){
				CurrentFather=CurrentNode;
				CurrentNode=CurrentNode->Left;
			} else {
				CurrentFather=CurrentNode;
				CurrentNode=CurrentNode->Right;
			}
		}
	}

	return SearchFather;
}

//==================================================================================================

int main(){
	int Ano, i, n;
	char Nome[15];
	Tree *Queue;
	Node *Search;

	Queue = (Tree *) malloc(sizeof(Tree));

	Tree_Initialize(Queue);

	do{
		scanf("%d",&n);
		
		switch (n){
				
			case 1:
				scanf("%s %d",Nome,&Ano);
				Search = Tree_Search(Queue,Nome);
				if (Search==NULL){
					Tree_Insert(Queue,Nome,Ano);
				} else {
					Search->Size++;
					Search->Year = (int *) realloc(Search->Year,Search->Size);
					Search->Year[(Search->Size)-1] = Ano;
				}
				break;
				
			case 2:
				scanf("%s",Nome);
				Search = Tree_Search(Queue,Nome);
				if (Search==NULL){
					printf("0\n");
				} else {
					printf("%d ",Node_Height(Search)+1);
					for (i = 0; i <= Search->Size; i++){
						printf("%d ",Search->Year[i]);
					}
					printf("\n");
				}
				break;
		}

		
	} while (n!=0);

	return 0;
}