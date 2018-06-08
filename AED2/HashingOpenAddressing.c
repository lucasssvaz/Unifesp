#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int *Index;
	int TableSize, nItems;
} HashTable;

HashTable *Hash_Create(int TableSize){
	int i;
	HashTable *Table = (HashTable *) malloc(sizeof(HashTable));

	Table->TableSize = TableSize;
	Table->nItems = 0;
	Table->Index = (int *) malloc(TableSize*sizeof(int));

	for (i=0;i<TableSize;i++){
		Table->Index[i] = -1;
	}

	return Table;
}

int Hash_Code(HashTable *Table, int Key){
	int index;

	index = Key % Table->TableSize;

	return index;
}

void Hash_Insert(HashTable *Table, int Key){
	int index, i=0;

	do{
		index = Hash_Code(Table, Key+i);
		i++;
	} while (Table->Index[index]!=-1 && i-1<Table->TableSize);
	
	if (i-1>=Table->TableSize) return;

	Table->Index[index] = Key;
	Table->nItems++;
}

int Hash_Search(HashTable *Table, int Key){
	int Search = 0, i;
	
	for (i=0;i<Table->TableSize;i++){
		if (Table->Index[i]==Key){
			Search = 1;
			break;
		}
	}

	return Search;
}

void Hash_Print(HashTable *Table){
	int i;

	for (i=0;i<Table->TableSize;i++){
		printf("[%d] ",i);
		if (Table->Index[i] != -1){
			printf("%d",Table->Index[i]);
		}
		printf("\n");
	}

	return;
}

int main(){
	int TableSize, nElements, Scan, i;
	HashTable *Table;

	scanf("%d %d",&TableSize,&nElements);

	Table = Hash_Create(TableSize);

	for (i=0;i<nElements;i++){
		scanf("%d",&Scan);
		if (Hash_Search(Table,Scan)==0 && TableSize>Table->nItems){
			Hash_Insert(Table,Scan);
		}
	}

	scanf("%d",&Scan);

	if (Hash_Search(Table,Scan)==0 && TableSize>Table->nItems){
		Hash_Insert(Table,Scan);
	}

	Hash_Print(Table);

	return 0;
}