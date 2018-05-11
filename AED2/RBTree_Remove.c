#include <stdlib.h>
#include <stdio.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  int Id;
  Pointer Left, Right, Father;
  int Colour;
} Node;

typedef struct {
  Pointer Root;
} Tree;

//==================================================================================================

void Tree_Initialize(Tree *Queue){
	Queue->Root=NULL;
	return;
}

Node *NodeSuc(Node *No){
	Node *CurrentNode=No;

	while (CurrentNode->Left!=NULL){
		CurrentNode=CurrentNode->Left;
	}

	return CurrentNode;
}

int BlackHeight(Node *No){
	int BH=0;
	Node *CurrentNode=No;

	while(CurrentNode!=NULL){
		if (CurrentNode->Colour==0){
			BH++;
		}
		CurrentNode=CurrentNode->Right;
	}

	return BH;
}

void SwapColours(Node *No){
	if (No->Colour==0){
		No->Colour=1;
		if (No->Right!=NULL)
			No->Right->Colour=0;
		if (No->Left!=NULL)
			No->Left->Colour=0;
	} else {
		No->Colour=0;
		if (No->Right!=NULL)
			No->Right->Colour=1;
		if (No->Left!=NULL)
			No->Left->Colour=1;
	}
}

void Rotate_Right(Tree *Queue,Node **No){
	Node *pB;

	pB = (*No)->Left;

	(*No)->Left = pB->Right;
	if (pB->Right != NULL)
		pB->Right->Father=(*No);
	pB->Father=(*No)->Father;
	if ((*No)->Father==NULL)
		Queue->Root=pB;
	else
		if ((*No)==(*No)->Father->Right)
			(*No)->Father->Right=pB;
		else
			(*No)->Father->Left=pB;
	pB->Right = *No;
	(*No)->Father = pB;

	return;
}

void Rotate_Left(Tree *Queue,Node **No){
	Node *pB;

	pB = (*No)->Right;

	(*No)->Right = pB->Left;
	if (pB->Left != NULL)
		pB->Left->Father=(*No);
	pB->Father=(*No)->Father;
	if ((*No)->Father==NULL)
		Queue->Root=pB;
	else
		if ((*No)==(*No)->Father->Left)
			(*No)->Father->Left=pB;
		else
			(*No)->Father->Right=pB;
	pB->Left = *No;
	(*No)->Father = pB;

	return;
}

void RecInsertion(Node *CurrentNode,Node *Item){
	if (Item->Id<=CurrentNode->Id){
		if (CurrentNode->Left==NULL){
			Item->Father=CurrentNode;
			CurrentNode->Left=Item;
		} else {
			RecInsertion(CurrentNode->Left,Item);
		}
	} else {
		if (CurrentNode->Right==NULL){
			Item->Father=CurrentNode;
			CurrentNode->Right=Item;
		} else {
			RecInsertion(CurrentNode->Right,Item);
		}
	}
	return;
}

Node *Tree_Search(Tree *Queue, int Item){
	Node *CurrentNode, *CurrentFather, *SearchFather=NULL;

	if (Queue->Root==NULL){
		return SearchFather;
	}

	CurrentFather = Queue->Root;

	if (Item==CurrentFather->Id){
		return CurrentFather;
	}

	CurrentNode = Queue->Root->Left;

	while (CurrentNode!=NULL){
		if (Item==CurrentNode->Id){
			SearchFather = CurrentFather;
			CurrentNode=NULL;
		} else {
			if (Item<CurrentNode->Id){
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
		if (Item==CurrentNode->Id){
			SearchFather = CurrentFather;
			CurrentNode=NULL;
		} else {
			if (Item<CurrentNode->Id){
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

void Tree_Print(Node *Root){
	char Colour;

	if (Root==NULL){
        printf("()");
		return;
  	}

  	if (Root->Colour==0){
  		Colour='N';
  	} else {
  		Colour='R';
  	}

  	printf("(%c%d",Colour,Root->Id);
  	Tree_Print(Root->Left);
  	Tree_Print(Root->Right);
  	printf(")");
}

void IsRBT(Tree *Queue,Node *No){
	Node *Grand, *Uncle=NULL, *Father=No->Father;

	if (Father==NULL)
        return;

	if (Father->Father!=NULL){
		Grand=No->Father->Father;
		if (Grand->Left==Father){
			Uncle=Grand->Right;
		} else {
			Uncle=Grand->Left;
		}
	}

	if (Father->Colour==0){ //father black
		return;
	} else if (Uncle!=NULL){
		if (Uncle->Colour==1){  //father red and uncle red
			SwapColours(Grand);
			IsRBT(Queue,Grand);
			return;
		} else {
			if ((Grand->Left==Father)&&(Father->Left)==No){ //LL
				Rotate_Right(Queue,&Grand);
				SwapColours(Father);
				return;
			} else if ((Grand->Left==Father)&&(Father->Right)==No){ //LR
				Rotate_Left(Queue,&Father);
				Rotate_Right(Queue,&Grand);
				SwapColours(No);
				return;
			} else if ((Grand->Right==Father)&&(Father->Left)==No){ //RL
				Rotate_Right(Queue,&Father);
				Rotate_Left(Queue,&Grand);
				SwapColours(No);
				return;
			} else { //RR
				Rotate_Left(Queue,&Grand);
				SwapColours(Father);
				return;
			}
		}
	} else { //father red and uncle black
		if ((Grand->Left==Father)&&(Father->Left)==No){ //LL
			Rotate_Right(Queue,&Grand);
			SwapColours(Father);
			return;
		} else if ((Grand->Left==Father)&&(Father->Right)==No){ //LR
			Rotate_Left(Queue,&Father);
			Rotate_Right(Queue,&Grand);
			SwapColours(No);
			return;
		} else if ((Grand->Right==Father)&&(Father->Left)==No){ //RL
			Rotate_Right(Queue,&Father);
			Rotate_Left(Queue,&Grand);
			SwapColours(No);
			return;
		} else { //RR
			Rotate_Left(Queue,&Grand);
			SwapColours(Father);
			return;
		}
	}
}

void Tree_Insert(Tree *Queue, int Item){
	Node *Aux = (Node *) malloc(sizeof(Node));
	Aux->Id=Item;
	Aux->Colour=1;
	Aux->Left=NULL;
	Aux->Right=NULL;
	Aux->Father=NULL;

	if (Queue->Root==NULL){
		Queue->Root=Aux;
		Queue->Root->Colour=0;
		return;
	}

	RecInsertion(Queue->Root,Aux);

	IsRBT(Queue,Aux);

	Queue->Root->Colour=0;

	return;
}

Node *Tree_BuilderRec(char *String){
	static int i = 0;
	Node *Aux=NULL;
	i++;
	if (String[i]=='N'){
		Aux = (Node *)malloc(sizeof(Node));
		Aux->Colour=0;
		i++;
		Aux->Id = String[i] - '0';
		i++;
		Aux->Left=Tree_BuilderRec(String);
		Aux->Right=Tree_BuilderRec(String);
		Aux->Father=NULL;


	} else if (String[i]=='R'){
		Aux = (Node *)malloc(sizeof(Node));
		Aux->Colour=1;
		i++;
		Aux->Id = String[i] - '0';
		i++;
		Aux->Left=Tree_BuilderRec(String);
		Aux->Right=Tree_BuilderRec(String);
		Aux->Father=NULL;
	}
	i++;
	return Aux;
}

void Fix_Father(Node *CurrentNode, Node *Father){
	if (CurrentNode==NULL){
		return;
	}

	CurrentNode->Father=Father;

	Fix_Father(CurrentNode->Left,CurrentNode);
	Fix_Father(CurrentNode->Right,CurrentNode);

	return;
}

void Tree_Builder(Tree *Queue, char *String){

	Queue->Root=Tree_BuilderRec(String);
	Fix_Father(Queue->Root,NULL);

	return;
}

void Tree_Remove(Tree *Queue, Node *Rem){
	Node *Father, *Sub, *Sib;


    if (Rem->Left == NULL){
        Father = Rem->Father;
        Sub = Rem->Right;
        if (Father->Left == Rem){
        	Father->Left = Rem->Right;
        	Father->Left->Father = Father;
        	free(Rem);
        	return;
        } else {
        	Father->Right = Rem->Right;
        	Father->Right->Father = Father;
        	free(Rem);
        	return;
        }

    }
    else if (Rem->Right == NULL){
    	if (Father)
        Father = Rem->Father;
        Sub = Rem->Left;
        if (Sub!=NULL){
        	if (Sub->Colour==1 || Rem->Colour==1){
        		if (Father->Left == Rem){
        			Sub->Colour=0;
        			Father->Left = Rem->Left;
        			Father->Left->Father = Father;
        			free(Rem);
        			return;
        		} else {
        			Sub->Colour=0;
        			Father->Right = Rem->Left;
        			Father->Right->Father = Father;
        			free(Rem);
        			return;
        		}
        	}else {

        	}	
        } else {

        }
    }

    Father = NodeSuc(Rem->Right);
    Rem->Id = Father->Id;
    Tree_Remove(Queue,Father);

    return;
}

//==================================================================================================

int main(){
	Tree *Queue = (Tree *) malloc(sizeof(Tree));
	Node *Search;
	int i, N;
	char String[10000];

	Tree_Initialize(Queue);

	scanf("%s",String);

	Tree_Builder(Queue,String);

	scanf("%d",&N);

	Search = Tree_Search(Queue,N);

	if (Search!=NULL){

	}

	Tree_Print(Queue->Root);

	return 0;
}
