#include <stdio.h>
#include <stdlib.h>

#define DELTA 1

int Verify_Frontiers(int *Chords, int Size_Ch, int *Frontier, int Size_Sc){

	int i, j;
	int *Count = (int *) calloc(Size_Ch,sizeof(int));

	for (i = 0; i < Size_Ch; i++){
		if (i == Size_Ch-1){
			if (Chords[i] >= Frontier[i] && Chords[i] < (Frontier[0]+Size_Sc)){
				Count[i]++;
			}
		} else if (Chords[i] >= Frontier[i] && Chords[i] < Frontier[i+1]){
			Count[i]++;
		}
	
	}

	for (i = 0; i < Size_Ch; i++){
		if (Count[i] != 1)
			return 0;
	}

	return 1;

}


int main (){

	int i;
	int Size_Ch, Size_Sc, *Chords;
	int Res = 0, Inc;
	int *Frontier, *Frontier_E;

	scanf("%d %d",&Size_Sc,&Size_Ch);

	Chords = (int *) calloc(Size_Ch, sizeof(int));
	Frontier = (int *) calloc(Size_Ch, sizeof(int));
	Frontier_E = (int *) calloc(Size_Ch, sizeof(int));

	for(i = 0; i < Size_Ch; i++){
		scanf("%d",&Chords[i]);
	}

	Inc = Size_Sc/Size_Ch;

	for(i = 1; i < Size_Ch; i++){
		Frontier_E[i] = Frontier[i] = Frontier[i-1] + Inc;
	}

	int Max_D = Frontier[1];
	int Max_E = Frontier[Size_Ch-1];

	while (Frontier[0] < Max_D){

		if (Res = Verify_Frontiers(Chords, Size_Ch, Frontier, Size_Sc))
			break;

		for(i = 0; i < Size_Ch; i++){
			Frontier[i] = (Frontier[i] + DELTA);
		}

	}

	do {

		if (Res = Verify_Frontiers(Chords, Size_Ch, Frontier, Size_Sc))
			break;

		if (Frontier[0] == 0){
			Frontier[0] = Size_Sc;
		}

		for(i = 0; i < Size_Ch; i++){
			Frontier[i] = (Frontier[i] - DELTA);
		}

	} while (Frontier[0] > Max_E);



	Res ? printf("S\n") : printf("N\n");
	free (Chords);
	free (Frontier);

	return 0;
}