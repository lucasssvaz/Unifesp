#include <stdlib.h>
#include <stdio.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  int Key, Priority;
  Pointer Left, Right;
} Node;

typedef struct {
  Pointer Root;
} Treap;

//==================================================================================================

void Treap_Initialize(Treap *Queue){
	Queue->Root=NULL;
	return;
}

Node *Rotate_Right(Node **No){
	Node *pB, *pC;

	pB = (*No)->Left;
	pC = pB->Right;

	pB->Right = *No;
	(*No)->Left = pC;

	return pB;
}

Node *Rotate_Left(Node **No){
	Node *pB, *pC;

	pB = (*No)->Right;
	pC = pB->Left;

	pB->Left = *No;
	(*No)->Right = pC;

	return pB;
}

Node *Treap_Insert(Node *CurrentNode, Node *Item){

	if (CurrentNode==NULL){
		return Item;
	}

	if (Item->Key<=CurrentNode->Key){
		CurrentNode->Left = Treap_Insert(CurrentNode->Left,Item);
		if (CurrentNode->Left->Priority > CurrentNode->Priority){
            CurrentNode = Rotate_Right(&CurrentNode);
		}
	} else {
		CurrentNode->Right = Treap_Insert(CurrentNode->Right,Item);
		if (CurrentNode->Right->Priority > CurrentNode->Priority){
            CurrentNode = Rotate_Left(&CurrentNode);
		}
	}
	return CurrentNode;
}

void Treap_Print(Node *CurrentNode){

	if (CurrentNode!=NULL)
    	{
    		printf("(");
    	    Treap_Print(CurrentNode->Left);
    	    printf("%d/%d",CurrentNode->Key,CurrentNode->Priority);
    	    Treap_Print(CurrentNode->Right);
    	    printf(")");
    	}

	return;
}

//==================================================================================================

int main(){

	Treap *Queue = (Treap *) malloc(sizeof(Treap));
	Node *Search, *NewNode;
	int nNodes, Key, Priority;

	Treap_Initialize(Queue);

	do{
		scanf("%d/%d",&Key,&Priority);
		if (Key!=-1 && Priority!=-1){
			nNodes++;
			NewNode = (Node *)calloc(1,sizeof(Node));
			NewNode->Priority = Priority;
			NewNode->Key = Key;
			Queue->Root = Treap_Insert(Queue->Root,NewNode);
			NewNode = NULL;
		}
	} while (Key!=-1 && Priority!=-1);

	Treap_Print(Queue->Root);
	printf("\n");

	return 0;
}