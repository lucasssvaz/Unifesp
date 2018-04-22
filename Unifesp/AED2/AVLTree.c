#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Cell *Pointer;

typedef struct Cell{
  int Id;
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

void Tree_Insert(Tree *Queue, int Item){
	Node *CurrentNode, *Aux = (Node *) malloc(sizeof(Node));
	Aux->Id=Item;
	Aux->BF=0;
	Aux->Left=NULL;
	Aux->Right=NULL;

	if (Queue->Root==NULL){
		Queue->Root=Aux;
		return;
	}

	CurrentNode = Queue->Root;

	while (CurrentNode!=NULL){
		if (Item<=CurrentNode->Id){
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

void Tree_Remove(Tree *Queue, Node *Father, int Item){
    Node *Aux, *CurrentNode=Father, *Percorre;
    int dir=0, no;

    if (Item==Queue->Root->Id){
        if (Queue->Root->Left==NULL&&Queue->Root->Right==NULL){
            free(Queue->Root);
            Queue->Root=NULL;
            Tree_BF(Queue->Root);
            Fix_AVL(Queue,&(Queue->Root));
            return;
        } else if ((Queue->Root->Left==NULL)^(Queue->Root->Right==NULL)){
            if (Queue->Root->Left==NULL){
                CurrentNode=Queue->Root->Right;
            } else {
                CurrentNode=Queue->Root->Left;
            }
            free(Queue->Root);
            Queue->Root=CurrentNode;
            Tree_BF(Queue->Root);
            Fix_AVL(Queue,&(Queue->Root));
            return;
        } else {

            Aux=Father->Right;
            if (Aux->Left!=NULL){
                CurrentNode = Aux;
                Aux = Aux->Left;
            }
            while(Aux->Left!=NULL){
                CurrentNode = Aux;
                Aux=Aux->Left;
            }
            if (CurrentNode->Left==Aux){
                no=CurrentNode->Left->Id;
                Queue->Root->Id = no;
                if (Aux->Left==NULL&&Aux->Right==NULL){
                    free(Aux);
                    CurrentNode->Left=NULL;
                    Tree_BF(Queue->Root);
                    Fix_AVL(Queue,&(Queue->Root));
                    return;
                    }
                    else if ((Aux->Left==NULL)^(Aux->Right==NULL)){
                    CurrentNode->Right=Aux->Right;
                    free(Aux);
                    Tree_BF(Queue->Root);
                    Fix_AVL(Queue,&(Queue->Root));
                    return;
                }
            } else if (CurrentNode->Right==Aux){
                no=CurrentNode->Right->Id;
                Queue->Root->Id = no;
                if (Aux->Left==NULL&&Aux->Right==NULL){
                    free(Aux);
                    CurrentNode->Right=NULL;
                    Tree_BF(Queue->Root);
                    Fix_AVL(Queue,&(Queue->Root));
                    return;
                }

                else if ((Aux->Left==NULL)^(Aux->Right==NULL)){
                    CurrentNode->Right=Aux->Right;
                    free(Aux);
                    Tree_BF(Queue->Root);
                    Fix_AVL(Queue,&(Queue->Root));
                    return;
                }
            }

            Tree_BF(Queue->Root);
            Fix_AVL(Queue,&(Queue->Root));
            return;
        }

    } else {

        if (Father->Left!=NULL){
            if (Father->Left->Id==Item){
                Aux = Father->Left;
                dir=-1;
            } else{
                Aux = Father->Right;
                dir=1;
            }
        } else {
            Aux = Father->Right;
            dir=1;
        }


        if (Aux->Left==NULL&&Aux->Right==NULL){
            free(Aux);
            if (dir == -1){
                Father->Left=NULL;
            } else {
                Father->Right=NULL;
            }
            Tree_BF(Queue->Root);
            Fix_AVL(Queue,&(Queue->Root));
            return;
        }

        else if ((Aux->Left==NULL)^(Aux->Right==NULL)){
            if (Aux->Left==NULL){
                if (dir==-1){
                    Father->Left=Aux->Right;
                } else {
                    Father->Right=Aux->Right;
                }} else {
                if (dir==-1){
                    Father->Left=Aux->Left;
                } else {
                    Father->Right=Aux->Left;
                }}
                free(Aux);
                Tree_BF(Queue->Root);
                Fix_AVL(Queue,&(Queue->Root));
                return;
            }

            else {

                if (dir==-1){
                    CurrentNode=Father->Left;
                    Percorre=Father->Left->Right;
                    if (Percorre->Left!=NULL){
                        CurrentNode = Percorre;
                        Percorre = Percorre->Left;
                    }
                    while(Percorre->Left!=NULL){
                        CurrentNode = Percorre;
                        Percorre=Percorre->Left;
                    }
                    Father->Left->Id = Percorre->Id;
                    if (CurrentNode->Left==Percorre){
                        free(CurrentNode->Left);
                        CurrentNode->Left=NULL;
                        Tree_BF(Queue->Root);
                        Fix_AVL(Queue,&(Queue->Root));
                        return;
                    } else if (CurrentNode->Right==Percorre){
                        free(CurrentNode->Right);
                        CurrentNode->Right=NULL;
                        Tree_BF(Queue->Root);
                        Fix_AVL(Queue,&(Queue->Root));
                        return;
                    }
                } else {
                    CurrentNode=Father->Right;
                    Percorre=Father->Right->Right;
                    if (Percorre->Left!=NULL){
                        CurrentNode = Percorre;
                        Percorre = Percorre->Left;
                    }
                    while(Percorre->Left!=NULL){
                        CurrentNode = Percorre;
                        Percorre=Percorre->Left;
                    }
                    Father->Right->Id = Percorre->Id;
                    if (CurrentNode->Left==Percorre){
                        free(CurrentNode->Left);
                        CurrentNode->Left=NULL;
                        Tree_BF(Queue->Root);
                        Fix_AVL(Queue,&(Queue->Root));
                        return;
                    } else if (CurrentNode->Right==Percorre){
                        free(CurrentNode->Right);
                        CurrentNode->Right=NULL;
                        Tree_BF(Queue->Root);
                        Fix_AVL(Queue,&(Queue->Root));
                        return;
                    }

                }
            }
        }
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
	if (Root==NULL){
        printf("()");
		return;
  	}

  	printf("(C%d",Root->Id);
  	Tree_Print(Root->Left);
  	Tree_Print(Root->Right);
  	printf(")");
}

//==================================================================================================

int main(){
	int n, nElements, i;
	Tree *Queue;
	Node *Search;

	Queue = (Tree *) malloc(sizeof(Tree));

	scanf("%d",&nElements);

	Tree_Initialize(Queue);

	for (i = 0;i<nElements;i++){
		scanf("%d",&n);

		Search = Tree_Search(Queue,n);

		if (Search==NULL){
            Tree_Insert(Queue,n);
        }
	}

	scanf("%d",&n);

	Search = Tree_Search(Queue,n);

	if (Search==NULL){
        Tree_Insert(Queue,n);
	} else {
        Tree_Remove(Queue,Search,n);
	}

	Tree_Print(Queue->Root);

	return 0;
}
