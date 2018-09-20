    #include <stdio.h>
    #include <stdlib.h>
     
    int order(int* seq, int nElements){
      int i, j;
      int Aux, Op = 0;
     
      for (i=0;i<nElements-1;i++){
        for (j=1;j<nElements-i;j++){
          if (seq[j-1]>seq[j]){
              Op++;
            Aux=seq[j-1];
            seq[j-1]=seq[j];
            seq[j]=Aux;
          }
        }
      }
      return Op;
    }
     
     
    int main(){
      int i, nElements;
      int* seq;
     
      scanf("%d",&nElements);
     
      seq = (int*) malloc (nElements*sizeof(int));
     
      for (i=0;i<nElements;i++){
        scanf("%d",&seq[i]);
      }
     
      order(seq,nElements)%2 ? printf("Marcelo") : printf("Carlos");
     
    }
