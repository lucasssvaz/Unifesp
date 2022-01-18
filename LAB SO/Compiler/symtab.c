#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#define SIZE 211
#define SHIFT 4


static int hash (char* key)
{ 
    int temp = 0;
    int i = 0;
    while (key[i] != '\0')
    { 
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

typedef struct LineListRec
{ 
  int lineno;
  struct LineListRec * next;
    
} * LineList;

typedef struct BucketListRec
{ 
  char* name;
  dataTypes Dtype;
  IDTypes Itype;
  char* scope;
  LineList lines;
  int memloc ; 
  int vet; 
  struct BucketListRec * next;
     
} * BucketList;

static BucketList hashTable[SIZE];

void st_insert( char * name, int lineno, int loc, char* scope, 
		dataTypes DType, IDTypes IType, int vet)
{ 
 
    int h = hash(name);
    BucketList l =  hashTable[h];
    while ((l != NULL) && (strcmp(name,l->name) != 0) && (strcmp(scope,l->scope) != 0)) 
            l = l->next;
    if (l == NULL || (loc != 0 && l->scope != scope && l->Itype != FUN)) /* variable not yet in table */
    { 
        l = (BucketList) malloc(sizeof(struct BucketListRec));
        l->name = name;
        l->lines = (LineList) malloc(sizeof(struct LineListRec));
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->scope = scope;
        l->Itype = IType;
        l->Dtype = DType;
        l->next = hashTable[h];
        hashTable[h] = l; 
    }
    
    else if (l->Itype == FUN && IType == VAR){
      fprintf(listing, "Linha %d - Erro: Nome da variavel %s já utilizada como nome de função.\n", lineno, name);
      Error = TRUE;
    }
    else if (l->scope == scope && loc != 0){
      fprintf(listing, "Linha %d - Erro: Variavel %s já declarada neste scope.\n", lineno, name);
      Error = TRUE;
    }
    else if (l->scope != scope && (strcmp(l->scope, "global") != 0)){
      while ((l != NULL)){
        if ((strcmp(l->scope, "global") == 0) && ((strcmp(name, l->name) == 0))){
          LineList t = l->lines;
          while (t->next != NULL)
            t = t->next;
          t->next = (LineList)malloc(sizeof(struct LineListRec));
          t->next->lineno = lineno;
          t->next->next = NULL;
          break;
        }
        l = l->next;
      }
      if (l == NULL && IType == VAR){
        fprintf(listing, "Linha %d - Erro: Variavel %s não declarada neste scope.\n", lineno, name);
        Error = TRUE;
      }
    }
    else if (l == NULL && IType == CALL){
      fprintf(listing, "Linha %d - Erro: Função %s não declarada neste scope.\n", lineno, name);
      Error = TRUE;
    }

    else if (loc == 0){
      LineList t = l->lines;
      while (t->next != NULL)
        t = t->next;
      t->next = (LineList)malloc(sizeof(struct LineListRec));
      t->next->lineno = lineno;
      t->next->next = NULL;
    }
} 

int st_lookup (char* name)
{ 
  int h = hash(name);	
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
        l = l->next;
  if (l == NULL) 
      return -1;
  else 
      return l->memloc;
}

dataTypes getFunType(char *nome)
{
  int h = hash(nome);
  BucketList l = hashTable[h];
  while ((l != NULL) && (strcmp(nome, l->name) != 0))
    l = l->next;

  if (l == NULL)
    return -1;
  else
    return l->Dtype;
}

void main_search()
{
  int h = hash("main");
  BucketList l = hashTable[h];
  while ((l != NULL) && ((strcmp("main", l->name) != 0 || l->Itype == VAR)))
    l = l->next;
  if (l == NULL){
    fprintf(listing, "Erro: Função main não declarada\n");
    Error = TRUE;
  }
}


void printSymTab(FILE * listing)
{ int i;
  fprintf(listing, "Variable Name  Escopo  Tipo ID  Tipo Dado  Numero Linha\n");
  fprintf(listing, "-------------  ------  -------  ---------  ------------\n");
  for (i=0;i<SIZE;++i){ 
    if (hashTable[i] != NULL){ 
    BucketList l = hashTable[i];
      while (l != NULL){ 
        LineList t = l->lines;
        fprintf(listing,"%-14s  ",l->name);
		    fprintf(listing,"%-6s  ",l->scope);
        char *id, *data;
        switch (l->Itype)
        {
        case VAR:
          id = "var";
          break;
        case FUN:
          id = "fun";
          break;
        case CALL:
          id = "call";
          break;
        case VET:
          id = "vet";
          break;
        default:
          break;
        }
        switch (l->Dtype)
        {
        case INTTYPE:
          data = "INT";
          break;
        case VOIDTYPE:
          data = "VOID";
          break;
        case NULLL:
          data = "null";
          break;
        default:
          break;
        }
        fprintf(listing, "%-7s  ", id);
        fprintf(listing, "%-8s  ", data);	
        while (t != NULL){ 
          fprintf(listing,"%3d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
