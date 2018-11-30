#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct TNode {
	short nR;
	int Values[2];
	struct TNode* Pointers[3];
} Node;

Node* Node_Create(int Data){
	Node* Aux = (Node*) calloc(1,sizeof(Node));
	Aux->nR = 1;
	Aux->Values[0] = Data;
	return Aux;
}

Node* Tree_Search(Node* Root, int Num){
	int i=0;
	Node* Goto;
	
	if (Root == NULL){
		return NULL;
	}
	
	int N = Root->nR;
	
	while(i<N){
		if (Root->Values[i] == Num){
			return Root;
		} else if (Num < Root->Values[i]) {
			return Tree_Search(Root->Pointers[i],Num);
		}	
		i++;	
	}	
	return Tree_Search(Root->Pointers[i],Num);
}

int main(){
	int Op, Num;
	
	setlocale(LC_ALL, "");
	
	do{
		printf("Escolha a operação desejada:\n\n1 - Buscar\n2 - Inserir\n3 - Remover\n-1 - Sair\n\nSua Escolha: ");
		scanf("%d",&Op);
		printf("\n");
		if (Op>=1 && Op<=3){
			printf("Digite o número a ser utilizado:\n");
			scanf("%d",&Num);
			printf("\n");
		}
		switch (Op){
			case -1:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				printf("Operação Inválida\n\n");
				break;
		}
	
	} while (Op!=-1);

	return 0;
}
