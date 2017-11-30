#include <stdio.h>

int main(){

	double PorPartidas, PorVitorias, PorEmpates, PorDerrotas;
	int Contador,Saldo, MaiorDerrota, MaiorVitoria, QntPartidas, GolsFeitos, GolsSofridos, Vitorias, Empates, Derrotas,QntGolsFeitos,QntGolsSofridos;

	Contador=0;
	GolsFeitos=0;
	GolsSofridos=0;
	Vitorias=0;
	Empates=0;
	Derrotas=0;
	QntGolsFeitos=0;
	QntGolsSofridos=0;
	MaiorDerrota=0;
	MaiorVitoria=0;
	Saldo=0;
	PorPartidas=0;
	PorVitorias=0;
	PorEmpates=0;
	PorDerrotas=0;

	scanf("%d",&QntPartidas);

	do{
        Contador++;
	    scanf("%d",&GolsFeitos);
	    if (GolsFeitos>=0){
            scanf("%d",&GolsSofridos);
            QntGolsFeitos=QntGolsFeitos+GolsFeitos;
            QntGolsSofridos=QntGolsSofridos+GolsSofridos;

            if (GolsFeitos>GolsSofridos){
                Vitorias++;
                if(GolsFeitos>MaiorVitoria)
                    MaiorVitoria=GolsFeitos;
            }
            else{
                 if(GolsFeitos<GolsSofridos){
                    Derrotas++;
                    if(GolsSofridos>MaiorDerrota)
                        MaiorDerrota=GolsSofridos;
                 }
                 else{
                     Empates++;
                 }
            }
         }
	}while(GolsFeitos>=0 && Contador!=QntPartidas);

	Contador=Contador-1;
	
	if(QntPartidas==1)
        Contador=1;
	
	Saldo=QntGolsFeitos-QntGolsSofridos;
	PorPartidas=100.0*Contador/QntPartidas;
	PorVitorias=100.0*Vitorias/Contador;
	PorEmpates=100.0*Empates/Contador;
	PorDerrotas=100.0*Derrotas/Contador;

    printf("%lf\n%lf\n%lf\n%lf\n",PorPartidas,PorVitorias,PorEmpates,PorDerrotas);
    printf("%d\n",Saldo);

    if(Derrotas==0){
        printf("Nao houve derrotas.\n");
    }
    else{
        printf("%d\n",MaiorDerrota);
    }

        if(Vitorias==0){
        printf("Nao houve vitorias.\n");
    }
    else{
        printf("%d\n",MaiorVitoria);
    }


    return 0;
}
