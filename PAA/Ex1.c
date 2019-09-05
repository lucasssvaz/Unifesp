#include <stdio.h>
#include <stdlib.h>

#define DELTA 0.5

int main (){

	int i;
	int Size_Ch, Size_Sc, *Chords;
	int Res = 0, Inc;
	float *Frontier;
	int Count;

	scanf("%d %d",&Size_Sc,&Size_Ch);

	Chords = (int *) calloc(Size_Ch, sizeof(int));
	Frontier = (float *) calloc(Size_Ch, sizeof(float));

	for(i = 0; i < Size_Ch; i++){
		scanf("%d",&Chords[i]);
	}

	Inc = Size_Sc/Size_Ch;

	for(i = 1; i < Size_Ch; i++){
		Frontier[i] = Frontier[i-1] + Inc;
	}

	float Max = Frontier[1];

	while (Frontier[0] < Max){

		Count = 0;

		for(i = 0; i < Size_Ch; i++){
			if (i != Size_Ch-1){
				if (Chords[i] >= Frontier[i] && Chords[i] < Frontier[i+1]){
					Count++;
				} else {
					break;
				}
			} else {
				if (Chords[i] >= Frontier[i] && Chords[i] < (Frontier[0] + Size_Sc)){
					Count++;
				}
			}
		}

		if (Count == Size_Ch){
			Res = 1;
			break;
		}

		for(i = 0; i < Size_Ch; i++){
			Frontier[i] = (Frontier[i] + DELTA);
		}

	}

	Res ? printf("S\n") : printf("N\n");
	free (Chords);
	free (Frontier);

	return 0;
}

