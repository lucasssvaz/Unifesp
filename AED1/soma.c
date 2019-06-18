#include <stdio.h>

int main()
{
	int dividendo, divisor, quociente, resto, soma; //declara variaveis
	scanf("%d %d",&dividendo, &divisor); //le numeros
	quociente = dividendo/divisor; //realiza divisao
	resto = dividendo % divisor; //pega modulo
	soma = quociente + resto; //soma quociente com modulo
	printf ("%d",soma); //escreve soma

    return 0;
}