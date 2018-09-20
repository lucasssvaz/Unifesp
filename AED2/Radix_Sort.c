    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    int digit (char *str,int Pos){
        int dig;
     
        if (str[Pos] == 32){
            dig = 0;
        } else {
            dig = str[Pos] - 96;
        }
     
        return dig;
    }
     
    void CountingSort (char **Queue, long int Elements, int Pos){
        int i, *Counting;
        char **Aux;
     
        Aux = (char **) calloc(Elements,sizeof(char *));
     
        Counting = (int *) calloc(27,sizeof(int));
     
        for (i=0;i<Elements;i++){
            Aux[i] = (char *) calloc(15,sizeof(char));
            Counting[digit(Queue[i],Pos)]++;
        }
     
        for (i=1;i<27;i++){
            Counting[i]+=(Counting[i-1]);
        }
     
        for (i=0;i<27;i++)
            printf("%d ",Counting[i]);
     
        printf("\n");
     
        for (i=Elements-1;i>=0;i--){
            strcpy(Aux[Counting[(digit(Queue[i],Pos))]-1],Queue[i]);
            Counting[digit(Queue[i],Pos)]--;
        }
     
        for (i=0;i<Elements;i++){
            strcpy(Queue[i],Aux[i]);
        }
     
        return;
    }
     
    void RadixSort (char **Queue, long int Elements, int max){
        int i;
     
     
        for (i=max-1; i>=0; i--){
            CountingSort(Queue,Elements,i);
        }
     
        return;
    }
     
     
    int main(){
        long int Elements;
        int i, j, max,p,m;
        char **Names, Temp_Name[15];
     
        scanf("%li",&Elements);
     
        Names = (char **)calloc(Elements,sizeof(char*));
     
        max = 0;
     
        for (i=0;i<Elements;i++){
            Names[i] = (char *)calloc(15,sizeof(char));
            scanf("%s",Temp_Name);
     
            if (strlen(Temp_Name) > max)
                max = strlen(Temp_Name);
     
            if (strlen(Temp_Name) != 15){
                for(j = strlen(Temp_Name); j < 15; j++){
                    Temp_Name[j] = 32;
                }
            }
     
            for (j=0;j<15;j++){
                if (Temp_Name[j] <= 90 && Temp_Name[j] >= 65){
                    Temp_Name[j] += 32;
                }
            }
     
            strcpy(Names[i],Temp_Name);
        }
     
        RadixSort(Names,Elements,max);
     
        scanf("%d %d\n",&p,&m);
     
        for (i=p-1;i<p+m-1;i++){
            puts(Names[i]);
        }
     
        free(Names);
        return 0;
    }
