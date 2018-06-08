#include <stdlib.h>
#include <stdio.h>

typedef struct TItem{
	int Key;
	struct TItem *Next;
} Item;

typedef struct {
	Item **Index;
	int TableSize, nItems;
} HashTable;

HashTable *Hash_Create(int TableSize){
	int i;
	HashTable *Table = (HashTable *) malloc(sizeof(HashTable));

	Table->TableSize = TableSize;
	Table->nItems = 0;
	Table->Index = (Item **) malloc(TableSize*sizeof(Item *));

	for (i=0;i<TableSize;i++){
		Table->Index[i] = NULL;
	}

	return Table;
}

int Hash_Code(HashTable *Table, int Key){
	int index;

	index = Key % Table->TableSize;

	return index;
}

void Hash_Insert(HashTable *Table, int Key){
	int index;
	Item **CurrentItem, *Aux;
	Aux = (Item *) calloc(1,sizeof(Item));
	Aux->Key = Key;

	index = Hash_Code(Table, Key);

	CurrentItem = &(Table->Index[index]);

	if (*CurrentItem == NULL){
		*CurrentItem = Aux;
		Table->nItems++;
		return;
	}

	while ((*CurrentItem)->Next!=NULL){
		CurrentItem = &((*CurrentItem)->Next);
	}

	(*CurrentItem)->Next=Aux;
	Table->nItems++;

	return;
}

void Hash_Remove(HashTable *Table, int Key){
	int index;
	Item **CurrentItem, **Aux;

	index = Hash_Code(Table, Key);

	CurrentItem = &(Table->Index[index]);

	if ((*CurrentItem)->Key == Key){
		Table->Index[index] = Table->Index[index]->Next;
		free(*CurrentItem);
		Table->nItems--;
		return;
	}

	while ((*CurrentItem)->Next->Key!=Key){
		CurrentItem = &((*CurrentItem)->Next);
	}

	Aux = &((*CurrentItem)->Next);
	(*CurrentItem)->Next=(*Aux)->Next;
	free(*Aux);
	Table->nItems--;

	return;
}

int Hash_Search(HashTable *Table, int Key){
	int Search = 0, index;
	Item *CurrentItem;

	index = Hash_Code(Table, Key);

	CurrentItem = Table->Index[index];

	if (CurrentItem == NULL) return Search;

	if (CurrentItem->Key == Key){
		Search = 1;
		return Search;
	}

	while (CurrentItem->Key!=Key && CurrentItem->Next!=NULL){
		CurrentItem = CurrentItem->Next;
	}

	if (CurrentItem->Key == Key) Search = 1;

	return Search;
}

void Hash_Print(HashTable *Table){
	int i;
	Item *CurrentItem;

	for (i=0;i<Table->TableSize;i++){
		printf("[%d] ",i);
		CurrentItem = Table->Index[i];
		while (CurrentItem!=NULL){
			printf("%d ",CurrentItem->Key);
			CurrentItem = CurrentItem->Next;
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
		if (Hash_Search(Table,Scan)==0){
			Hash_Insert(Table,Scan);
		}
	}

	scanf("%d",&Scan);

	if (Hash_Search(Table,Scan)==0){
		Hash_Insert(Table,Scan);
	} else {
		Hash_Remove(Table,Scan);
	}

	Hash_Print(Table);

	return 0;
}
