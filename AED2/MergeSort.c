#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int Id, For, Against, Points;
} Team;

void merge(Team *Classification, int Start, int Finish);
void sort(Team *Classification, int Start, int Finish);

void sort(Team *Classification, int Start, int Finish){
	int Middle, Length;

	if (Start==Finish){
		return;
	}

	Length = Finish-Start+1;
	Middle = (Start+Finish)/2;
	sort(Classification, Start, Middle);
	sort(Classification, Middle+1, Finish);
	merge(Classification, Start, Finish);
	return;
}

void merge (Team *Classification,int Start,int Finish){
	Team *Aux;
	int i=0, j=0, k=0;
	float Avg_i, Avg_j;
	Aux = (Team *) malloc((Finish-Start+1)*sizeof(Team));

	for (i=Start;i<=(Start+Finish)/2;i++){
		Aux[i-Start]=Classification[i];
	}
	j=Finish-Start;
	for (i=((Start+Finish)/2)+1;i<=Finish;i++){
		Aux[j]=Classification[i];
		j--;
	}

	k=Start;
	i=0;
	j=Finish-Start;
	while (i<=j){
		if (Aux[i].Against>0){
			Avg_i=1.0*Aux[i].For/Aux[i].Against;
		} else{
			Avg_i=1.0*Aux[i].For;
		}
		if (Aux[j].Against>0){
			Avg_j=1.0*Aux[j].For/Aux[j].Against;
		} else{
			Avg_j=1.0*Aux[j].For;
		}


		if(Aux[i].Points>Aux[j].Points){
			Classification[k]=Aux[i];
			k++;
			i++;
		} else if (Aux[i].Points<Aux[j].Points){
			Classification[k]=Aux[j];
			k++;
			j--;
		} else if (Avg_i>Avg_j){
			Classification[k]=Aux[i];
			k++;
			i++;
		} else if (Avg_i<Avg_j){
			Classification[k]=Aux[j];
			k++;
			j--;
		} else if (Aux[i].For>Aux[j].For){
			Classification[k]=Aux[i];
			k++;
			i++;
		} else if (Aux[i].For<Aux[j].For){
			Classification[k]=Aux[j];
			k++;
			j--;
		} else if (Aux[i].Id<Aux[j].Id){
			Classification[k]=Aux[i];
			k++;
			i++;
		} else {
			Classification[k]=Aux[j];
			k++;
			j--;
		}
	}
	free(Aux);
	return;
}

int main(){
	int Elements, i, T1_Id, T1_Score, T2_Id, T2_Score;
	Team *Classification;

	scanf("%d",&Elements);

	Classification = (Team *) malloc(Elements*sizeof(Team));

	for (i=1;i<Elements+1;i++){
		Classification[i-1].Id=i;
		Classification[i-1].For=0;
		Classification[i-1].Against=0;
		Classification[i-1].Points=0;
	}


	for (i=0;i<Elements*(Elements-1)/2;i++){
		scanf("%d %d %d %d", &T1_Id, &T1_Score, &T2_Id, &T2_Score);
		if (T1_Score>T2_Score){
			Classification[T1_Id-1].Points+=2;
			Classification[T2_Id-1].Points+=1;
		} else {
			Classification[T2_Id-1].Points+=2;
			Classification[T1_Id-1].Points+=1;
		}
		Classification[T1_Id-1].For+=T1_Score;
		Classification[T1_Id-1].Against+=T2_Score;
		Classification[T2_Id-1].For+=T2_Score;
		Classification[T2_Id-1].Against+=T1_Score;
	}

	sort (Classification,0,Elements-1);

	for (i=0;i<Elements;i++){
		printf("%d ",Classification[i].Id);
	}

	free (Classification);
	return 0;
}
