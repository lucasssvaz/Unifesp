#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXDIG 8

typedef struct{
	char Sym;
	long Bin;
} Encode;

int Search(Encode *Table, int zzz, long Bin){
	int i, index = -1;

	for(i=0;i<zzz;i++){
		if (Bin == Table[i].Bin){
			index = i;
			break;
		}
	}

	return index;
}

int main(){
    long b;
	int nElements, i, j, aux, Src, zzz;
	char flow[10000], piece[10000],a;
	Encode *Table;

	scanf("%d",&nElements);

    zzz = nElements;

	Table = (Encode *)calloc(nElements,sizeof(Encode));

	for (i=0;i<zzz;i++){
		Table[i].Sym = '\0';
		Table[i].Bin = -1;
	}

	for (i=0;i<zzz;i++){
		scanf("%s %li",&a,&b);
		Table[i].Sym = a;
		Table[i].Bin = b;
	}

	scanf("%s",flow);

	i = 0;

	while(flow[i]!='\0'){
		for(j=0;j+i<zzz;j++){
			strncpy(piece,flow+i,j+1);
			piece[j+1]='\0';
			aux = atol(piece);
			Src = Search(Table,zzz,aux);
			if (Src>=0){
				printf("%c",Table[Src].Sym);
				i+=j+1;
				break;
			}
		}

	}

	return 0;
}
