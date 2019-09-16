#include <stdio.h>
#include <stdlib.h>

int main (){

	int i;
	int Size_Ch, Size_Sc, *Chords;
	int Res = 1, F_Size;
	int Dist_D, Dist_E;

	scanf("%d %d",&Size_Sc,&Size_Ch);

	Chords = (int *) calloc(Size_Ch, sizeof(int));

	for(i = 0; i < Size_Ch; i++){
		scanf("%d",&Chords[i]);
	}

	F_Size = Size_Sc/Size_Ch;

	//Dist_E >= F_Size - Dist_D

	for (i = 0; i<Size_Ch; i++){
		if (i == Size_Ch-1){
			Dist_E = Chords[i] - Chords[i-1];
			Dist_D = (Chords[0] + Size_Sc) - Chords[i];
			if (Dist_E + Dist_D <= F_Size){
				Res = 0;
				break;
			}
		} else if (i == 0){
			Dist_E = (Chords[i]+Size_Sc)-Chords[Size_Ch-1];
			Dist_D = Chords[i+1]-Chords[i];
			if (Dist_E + Dist_D <= F_Size){
				Res = 0;
				break;
			}
		} else {
			Dist_E = Chords[i]-Chords[i-1];
			Dist_D = Chords[i+1]-Chords[i];
			if (Dist_E + Dist_D <= F_Size){
				Res = 0;
				break;
			}
		}

	}

	Res ? printf("S\n") : printf("N\n");
	free (Chords);

	return 0;
}
