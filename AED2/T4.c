#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXDIG 8

struct TNode {
	int Item;
	struct TNode *Left, *Right;
};

typedef struct TNode Node;

typedef struct{
	Node *Root;
} Trie;

int GetDigit(int num, int dig){
	int digit;

	digit = (num/(int)pow(2,dig))%2;

	return digit;
}

int Binary(int num){
    if (num == 0)
        return 0;
    else
        return (num%2 + 10*Binary(num/2));
}

Trie *Trie_Create(){
	Trie *Tree = (Trie *) malloc(sizeof(Trie));
	Tree->Root = (Node *) calloc(1,sizeof(Node));
	Tree->Root->Item = -1;

	return Tree;
}

int Trie_Search(Trie *Tree, int Key){
	int dig = 0, Search = 0, aux;
	Node *CurrentNode = Tree->Root;

	do{
		if (CurrentNode == NULL)
			break;

		if (CurrentNode->Item!=-1){
			Search = 1;
			for (dig=dig;dig<=MAXDIG;dig++){
				if (GetDigit(Key,dig) != GetDigit(CurrentNode->Item,dig)){
					Search=0;
					break;
				}
			}
			break;
		}

		aux = GetDigit(Key,dig);

		if (aux == 0)
			CurrentNode = CurrentNode->Left;
		else
			CurrentNode = CurrentNode->Right;

		dig++;

	}while (1);

	return Search;
}

void Trie_Insert(Trie *Tree, int Key, int Value){
	int dig = 0, aux, Hold;
	Node *CurrentNode;

	CurrentNode = Tree->Root;

	do{

		aux = GetDigit(Key,dig);

		if (aux){
            if (CurrentNode->Right == NULL){
                CurrentNode->Right = (Node *) calloc(1,sizeof(Node));
                CurrentNode->Right->Item = Key;
                break;
            }

            if (CurrentNode->Right->Item!=-1){
                Hold = CurrentNode->Right->Item;
                CurrentNode->Right->Item=-1;
                while(GetDigit(Key,dig)==GetDigit(Hold,dig)){
                    if(GetDigit(Key,dig)==0){
                        CurrentNode->Right->Left = (Node *) calloc(1,sizeof(Node));
                        CurrentNode = CurrentNode->Right;
                    } else {
                        CurrentNode->Right->Right = (Node *) calloc(1,sizeof(Node));
                        CurrentNode = CurrentNode->Right;
                    }
                    dig++;
                }
                if (GetDigit(Key,dig)==0){
                    CurrentNode->Left = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Left->Item = Key;
                    CurrentNode->Right = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Right->Item = Hold;
                } else {
                    CurrentNode->Right = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Right->Item = Key;
                    CurrentNode->Left = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Left->Item = Hold;
                }
                break;
            }
        } else {
            if (CurrentNode->Left == NULL){
                CurrentNode->Left = (Node *) calloc(1,sizeof(Node));
                CurrentNode->Left->Item = Key;
                break;
            }

            if (CurrentNode->Left->Item!=-1){
                Hold = CurrentNode->Left->Item;
                CurrentNode->Left->Item=-1;
                while(GetDigit(Key,dig)==GetDigit(Hold,dig)){
                    if(GetDigit(Key,dig)==0){
                        CurrentNode->Left->Left = (Node *) calloc(1,sizeof(Node));
                        CurrentNode = CurrentNode->Left;
                    } else {
                        CurrentNode->Left->Right = (Node *) calloc(1,sizeof(Node));
                        CurrentNode = CurrentNode->Left;
                    }
                    dig++;
                }
                if (GetDigit(Key,dig)==0){
                    CurrentNode->Left = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Left->Item = Key;
                    CurrentNode->Right = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Right->Item = Hold;
                } else {
                    CurrentNode->Right = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Right->Item = Key;
                    CurrentNode->Left = (Node *) calloc(1,sizeof(Node));
                    CurrentNode->Left->Item = Hold;
                }
                break;
            }
        }

		if (aux == 0)
			CurrentNode = CurrentNode->Left;
		else
			CurrentNode = CurrentNode->Right;

		dig++;

	}while (1);



	return;
}

int BinaryToDecimal(int n){
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0){
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

void Trie_Print(Node *Root){
	if (Root==NULL){
        printf("()");
		return;
  	}

    if (Root->Item!=-1 && Root->Item!=0)
        printf("(C%d",BinaryToDecimal(Root->Item));
    else
        printf("(");

  	Trie_Print(Root->Left);
  	Trie_Print(Root->Right);
  	printf(")");
}

int main(){
	int nElements, i, num;
	char flow[10000];
	int bin;
	Trie *TTree = Trie_Create();

	scanf("%d",&nElements);

	for(i=0;i<nElements;i++){
		scanf("%d",&num);
		bin = Binary(num);
		if (Trie_Search(TTree,bin)==0){
			Trie_Insert(TTree,bin);
		}
	}

	scanf("%s",&flow);
	bin = Binary(num);
	if (Trie_Search(TTree,bin)==0){
		Trie_Insert(TTree,bin);
	}

	Trie_Print(TTree->Root);

	return 0;
}
