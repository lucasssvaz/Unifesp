#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int nProblems;
  char name[50];
} student;


void orderProblems(student* list, int nElements){
  int i, j, menor;
  student Aux;

  for (i=0;i<nElements-1;i++){
    menor=i;
    for (j=i+1;j<nElements;j++){
      if (list[j].nProblems<list[menor].nProblems){
        menor=j;
      }
    }
    Aux=list[i];
    list[i]=list[menor];
    list[menor]=Aux;
  }
}


int main(){
  int i, nElements, failed=0;
  student* studentsList;

  scanf("%d",&nElements);

  studentsList = (student*) malloc (nElements*sizeof(student));

  for (i=0;i<nElements;i++){
    scanf("%s %d",studentsList[i].name,&studentsList[i].nProblems);
  }

  orderProblems(studentsList,nElements);

  for (i=1;studentsList[i-1].nProblems==studentsList[i].nProblems;i++){
    if(strcmp(studentsList[failed].name,studentsList[i].name)<0){
      failed=i;
    }
  }


  printf("%s\n",studentsList[failed].name);


}
