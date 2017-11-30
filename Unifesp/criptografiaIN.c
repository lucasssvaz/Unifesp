#include <stdio.h>

void LeABC ( int *a , int *b , int * c );
void Calcula_XY ( int b , int c , int *x , int * y );
void Calcula_QR ( int a , int b , int *q , int * r );
int Calcula_Z ( int q , int r );
int Calcula_P ( int x , int y , int z );
int Calcula_S ( int m , int p , int q , int r , int x , int y );

//==================================================================== MAIN

int main(){
    int M,A,B,C,X,Y,Z,P,Q,R,S;

    scanf("%d",&M);

    LeABC(&A,&B,&C);
    Calcula_XY(B,C,&X,&Y);
	Calcula_QR(A,B,&Q,&R);
	Z=Calcula_Z(Q,R);

    return 0;
}

//==================================================================== LeABC

void LeABC ( int *a , int *b , int * c ){
    scanf("%d %d %d",a,b,c);
}

//==================================================================== EhPrimo

int EhPrimo (int n)
{
    int i, primo = 1;

    for (i=n-1; i>=2; i--)
    {
        if (!(n%i))
            primo = 0;
    }

	return primo;
}

//==================================================================== Calcula_XY

void Calcula_XY ( int b , int c , int *x , int * y ){
    int i, resto, num1, num2, mdc;
    resto=1;
    mdc=0;
    *x=b+1;
    i=1;
    do{
        num1=c+i;
        num2=*x;
        do{
            resto = num1 % num2;
            num1 = num2;
            num2 = resto;
        }while (resto!=0);
        mdc=num1;
        if (mdc!=1)
            i+=1;
    }while (mdc!=1);
    *y=c+i;
}

//===================================================================== Calcula_QR

void Calcula_QR ( int a , int b , int *q , int * r ){
	if (a>b){
		*q=a/b;
		*r=1+(a%b);
	} else if (a<b){
		*q=b/a;
		*r=1+(b%a);
	} else{
		*q=20*a;
		*r=5;
	}
}

//===================================================================== Calcula_Z

int Calcula_Z ( int q , int r ){
	int min,z,i;
	i=
	if (q>=r){
		min=r;
	} else {
		min=q;
	}

	do{

	}while(EhPrimo(i)==0);


	return z;
}
