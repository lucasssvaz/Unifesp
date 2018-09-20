#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Num;
    int V;
} Candidato;

typedef struct {
    int V1,V2,V3;
} Voto;

void InsertionSort(Candidato* Cand, int C){
    int i, j;
    Candidato Aux;

    for (i=1;i<C;i++){
        Aux=Cand[i];
        for (j=i-1;(j>=0)&&(Aux.V > Cand[j].V);j--){
            Cand[j+1]=Cand[j];
        }
        Cand[j+1]=Aux;
    }
}


int main() {

    int V, C, i, Pri, Seg, Ter, Val = 0, C1, C2;
    float R;
    Candidato* Cand;
    Voto* Votos;

    scanf("%d %d", &V, &C);
    
    Votos = (Voto*) calloc(V,sizeof(Voto));
    Cand = (Candidato*) calloc(C,sizeof(Candidato));
    
    for (i=0;i<C;i++)
        Cand[i].Num = i+1;
        
    for (i=0;i<V;i++){
    
        scanf("%d %d %d", &Pri, &Seg, &Ter);
        Votos[i].V1 = Pri;
        Votos[i].V2 = Seg;
        Votos[i].V3 = Ter;
        
        if ((Pri > 0 && Pri <= C)){
            Val++;
            Cand[Pri-1].V++;
        }
    }
    
    InsertionSort(Cand,C);
    
    R =  100.0 * Cand[0].V / Val;
    
    if (Val) {
        printf("%d %.2f\n", Cand[0].Num , R);
    } else {
        printf("0\n");
        return 0;
    }   
    
    if (R < 50.0){
        C1 = Cand[0].Num;
        C2 = Cand[1].Num;
        
        Cand[0].V = 0;
        Cand[1].V = 0;
        
        Val = 0;
        
        for (i=0;i<V;i++){
        
            if ((Votos[i].V1 == C1) || (Votos[i].V1 == C2)){
                Val++;
                Votos[i].V1 == C1 ? Cand[0].V++ : Cand[1].V++;
                } else if ((Votos[i].V2 == C1) || (Votos[i].V2 == C2)){
                    Val++;
                    Votos[i].V2 == C1 ? Cand[0].V++ : Cand[1].V++;
                        } else if ((Votos[i].V3 == C1) || (Votos[i].V3 == C2)){
                            Val++;
                            Votos[i].V3 == C1 ? Cand[0].V++ : Cand[1].V++;
                        }
        }
        
        InsertionSort(Cand,2);
        
        if (Cand[0].V == Cand[1].V){
            (Cand[0].Num > Cand[1].Num) ? (Cand[0] = Cand[1]) : (Cand[1] = Cand[0]);
        }
        
        printf("%d %.2f\n", Cand[0].Num , 100.0 * Cand[0].V / Val);
        
    }
    
    return 0;
}
