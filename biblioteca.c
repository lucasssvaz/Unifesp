#include <stdio.h>
#define N_NOME 200
#define N_ALUNOS 50
#define N_LIVROS 100
#define N_EMPRESTIMOS 250

typedef struct{
	int RA;
	int idade;
	char nome[N_NOME];
} f_aluno;

typedef struct{
	int codigo;
	char titulo[N_NOME];
	char autor[N_NOME];
} f_livro;

typedef struct{
	int retirada;
	int devolucao;
	int RA_retirada;
	int cod;
} f_emprestimo;
//-------------------------------------------------------------------------------------
void readData(f_aluno aluno[], f_livro livro[]){
	int i;
	for (i=0; i<N_ALUNOS; i++){
	scanf("%d %s %d", &aluno[i].RA, &aluno[i].nome, &aluno[i].idade);
	}
	
	for (i=0; i<N_LIVROS; i++){
	scanf("%d %s %s", &livro[i].codigo, &livro[i].titulo, &livro[i].autor);
	}
}
//-------------------------------------------------------------------------------------
int main(){
f_aluno aluno[N_ALUNOS];
f_livro livro[N_LIVROS];
f_emprestimo emprestimo[N_EMPRESTIMOS];
int i, j, k, done, consultas, consulta_tipo, emprestados=0, atual_RA, atual_cod, atual_retirada, atual_devolucao;
	
for (i=0;i<N_EMPRESTIMOS;i++){
    emprestimo[i].RA_retirada=-1;
    emprestimo[i].retirada=0;
    emprestimo[i].devolucao=0;
    emprestimo[i].cod=0;
}
readData(aluno,livro);
scanf("%d",&consultas);

for (j=0; j<consultas; j++){
	scanf("%d",&consulta_tipo);
	if (consulta_tipo==1){
		emprestados++;
		scanf("%d %d %d %d",&atual_RA,&atual_cod,&atual_retirada,&atual_devolucao);
        done=0;
        i=0;
        do{
		if(emprestimo[i].RA_retirada==-1){
                	emprestimo[i].cod=atual_cod;
			emprestimo[i].retirada=atual_retirada;
			emprestimo[i].devolucao=atual_devolucao;
			emprestimo[i].RA_retirada=atual_RA;
			done=1;
		    } else{
	    	    i++;
		    }
        }while(done!=1);
	}else if (consulta_tipo==2){
		emprestados--;
		scanf("%d %d",&atual_RA,&atual_cod);
		for (i=0; i<N_EMPRESTIMOS; i++){
			if (atual_cod==emprestimo[i].cod && emprestimo[i].RA_retirada==atual_RA){
				emprestimo[i].RA_retirada=-1;
				emprestimo[i].retirada=0;
				emprestimo[i].devolucao=0;
				emprestimo[i].cod=0;
			}
		}
	}else if (consulta_tipo==3){
		scanf("%d",&atual_RA);
		for (i=0; i<N_ALUNOS; i++){
			if (atual_RA==aluno[i].RA){
				printf ("%s %d\n", aluno[i].nome, aluno[i].idade);
			}
		}
		for (i=0; i<N_EMPRESTIMOS; i++){
			if (atual_RA==emprestimo[i].RA_retirada){
				printf ("%d %d\n", emprestimo[i].retirada, emprestimo[i].devolucao);
			    for (k=0;k<N_LIVROS;k++){
			        if (emprestimo[i].cod==livro[k].codigo)
			         printf("%s %s\n",livro[k].titulo, livro[k].autor);
			    }
			}
		}
	}else { //4
		printf("%d\n",emprestados);
	}
}
return 0;
}
