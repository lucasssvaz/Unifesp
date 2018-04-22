#include <stdlib.h>
#include <stdio.h>

int main(){ 

//------------------------------------------------------------------------------------------- ALOCAÇÃO DE MEMÓRIA

	int i, j, nro_unidades=0, cod_atual=0, alunos_atual=0, RA_atual=0, cap_bloco=0, min;
	int **campus, *alunos_max, *alunos_presentes, *cod_campus, *aux;

	scanf("%d",&nro_unidades);

	cod_campus = (int *) malloc(nro_unidades * sizeof(int));
	alunos_max = (int *) malloc(nro_unidades * sizeof(int));
	alunos_presentes = (int *) malloc(nro_unidades * sizeof(int));

	campus = (int **) malloc(nro_unidades * sizeof(int *));

//------------------------------------------------------------------------------------------ LEITURA DO TOTAL DE ALUNOS E INICIALIZAÇÃO DE VETORES
	
	for (i=0; i<nro_unidades; i++){
		scanf("%d %d",&cod_atual,&alunos_atual);
		cod_campus[i]=cod_atual;
		alunos_max[i]=alunos_atual;
		campus[i]= (int *) malloc(sizeof(int));
		alunos_presentes[i]=0;
	}

	scanf("%d",&cap_bloco);

//------------------------------------------------------------------------------------------ LEITURA ALUNOS PRESENTES	
	
	while(cod_atual!=-1){
		scanf("%d", &cod_atual);
		if (cod_atual!=-1){
            scanf("%d", &RA_atual);
            for (i=0;i<nro_unidades;i++){
                if (cod_campus[i]==cod_atual){
                    campus[i][alunos_presentes[i]]=RA_atual;
                    alunos_presentes[i]++;
                    aux=realloc(campus[i], sizeof(int) * (alunos_presentes[i]+1));
                    if (aux!=NULL){
                        campus[i]=aux;
                    aux=NULL;
                    }
                }
            }
        }
	}

//-------------------------------------------------------------------------------------------------------- ACHAR A MENOR TAXA DE PARTICIPAÇÃO
	
	min=0;
	for (i=1;i<nro_unidades;i++){
		if(1.0*alunos_presentes[i]/alunos_max[i]<=1.0*alunos_presentes[min]/alunos_max[min]){
			min=i;
		}
	}

//--------------------------------------------------------------------------------------------------------- IMPRIMIR LISTA DE ALUNOS PARTICIPANTES DO PIOR CAMPUS
	
	for (i=0;i<nro_unidades;i++){
		if(1.0*alunos_presentes[i]/alunos_max[i]==1.0*alunos_presentes[min]/alunos_max[min]){
			printf("%d\n", cod_campus[i]);
			for(j=0;j<alunos_presentes[i];j++){
				printf("%d\n",campus[i][j]);
			}
		}
	}

//--------------------------------------------------------------------------------------------------------- LIMPEZA DE MEMÓRIA

	for (i=0;i<nro_unidades;i++){
		free(campus[i]);
		campus[i]=NULL;
	}
	free(campus);
	campus=NULL;
	free(cod_campus);
	cod_campus=NULL;
	free(alunos_max);
	alunos_max=NULL;
	free(alunos_presentes);
	alunos_presentes=NULL;

	return 0;
}
