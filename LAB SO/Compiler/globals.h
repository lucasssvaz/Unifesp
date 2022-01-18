#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



#ifndef YYPARSER


#include "parser.tab.h"


#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 8

extern FILE* source; 
extern FILE* listing; 
extern FILE* code;
extern FILE* codeinter;
extern FILE* acode;
extern FILE* bcode;

extern int lineno; 


typedef int TokenType;

typedef enum{  stmtK, expK/*, declK */} NodeKind;
typedef enum{  ifK, whileK, assignK, returnK } StmtKind;
typedef enum{	opK, constK, idK, varDeclK, funDeclK,ativK, typeK, vectorK, paramK } ExpKind;
//typedef enum{  varK, funK, varVecK, vecParamK, paramK } DeclKind;

/* ExpType is used for type checking */
typedef enum{  Void, Integer, booleanK  } ExpType;

typedef enum {INTTYPE, VOIDTYPE, NULLL} dataTypes;
typedef enum {VAR, FUN, CALL, VET} IDTypes;


#define MAXCHILDREN 3


typedef struct treeNode
{ 
   struct treeNode * child[MAXCHILDREN];
   struct treeNode * sibling;
   int flag;
   int lineno;
   int size;
   int add;
   int already_seem;
   NodeKind nodekind;
   union { StmtKind stmt; ExpKind exp;} kind;
   union {  TokenType op;
            int val;
            char * name; } attr;
   char * idname;
   char *  scope;
   char * idtype;
   char * datatype;
   int vet;
   int declared;
   int params;
   ExpType type; /* for type checking of exps */

} TreeNode;


extern int EchoSource;

extern int TraceScan;

extern int TraceParse;

extern int TraceAnalyze;

extern int TraceCode;

extern int Error; 
#endif
