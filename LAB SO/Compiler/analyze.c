#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include <stdio.h>

char* escopo = "global";

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"typeError em %s na linha %d: %s\n", t->attr.name, t->lineno, message);
  Error = TRUE;
}

void UpdateScope(TreeNode * t)
{
  if (t->child[0] != NULL && t->child[0]->kind.exp == funDeclK) 
  escopo = t->child[0]->attr.name;
}

// contador
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *) ){ 

	if (t != NULL)
 	{ 
		UpdateScope(t);
		preProc(t);
    	{ 
	  		int i;
	        for (i=0; i < MAXCHILDREN; i++)
        		traverse(t->child[i], preProc, postProc);
    	}
		if(t->child[0]!= NULL && t->child[0]->kind.exp == funDeclK) 
			escopo = "global";
    	postProc(t);
    	traverse(t->sibling, preProc, postProc);
  	}
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t){ 
	if (t==NULL) 
		return;
  	else 
		return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t){ 
	
	switch (t->nodekind)
    { 

		case stmtK: 		
			if(t->kind.stmt == assignK){
				if (st_lookup(t->child[0]->attr.name) == -1){
					fprintf(listing,"Linha %d - Erro: A variavel %s nao foi declarada.\n", t->lineno, t->child[0]->attr.name);
					Error = TRUE;
				}
			else
				st_insert(t->child[0]->attr.name,t->lineno,0,escopo,INTTYPE,VAR,t->vet);
			t->child[0]->add = 1;
      		}
      		break;
      case expK:
        switch(t->kind.exp){
        	case typeK:
				if(t->child[0] != NULL){
					switch (t->child[0]->kind.exp){
						case varDeclK:
							if (st_lookup(t->attr.name) == -1) /* não encontrado na tabela, inserir*/
								st_insert(t->child[0]->attr.name,t->lineno,location++, escopo, INTTYPE, VAR, t->vet);
							else /* encontrado na tabela, verificar escopo */
								st_insert(t->child[0]->attr.name,t->lineno,0, escopo, INTTYPE, VAR, t->vet);
							break;
						case funDeclK:
							if (st_lookup(t->attr.name) == -1){
								st_insert(t->child[0]->attr.name,t->lineno,location++, "global",t->child[0]->type,FUN, t->vet);}
							else /* encontrado na tabela, verificar escopo */
								fprintf(listing,"Linha %d - Erro: Multiplas declaracoes da funcao %s.\n", t->lineno, t->child[0]->attr.name);
							break;
						default:
							break;
					}
				}
				break;
			case paramK:
				st_insert(t->attr.name, t->lineno, location++, escopo, INTTYPE, VAR, t->vet);
				break;
			case vectorK:
				st_insert(t->attr.name, t->lineno, 0, escopo, INTTYPE, VAR, t->vet);
				break;
			case idK:
				if(t->add != 1){
					if (st_lookup(t->attr.name) == -1){
						fprintf(listing,"Linha %d - Erro: A variavel %s nao foi declarada.\n", t->lineno, t->attr.name);
						Error = TRUE;
					}
					else {
						st_insert(t->attr.name,t->lineno,0,escopo,INTTYPE,FUN, t->vet);
					}
				}
				break;
			case ativK: 
			if (st_lookup(t->attr.name) == -1 && strcmp(t->attr.name, "input")!=0 && strcmp(t->attr.name, "output")!=0 && strcmp(t->attr.name, "recuperaPC")!=0 && strcmp(t->attr.name, "HDtoMI")!=0
				&& strcmp(t->attr.name, "enderecoBase")!=0 && strcmp(t->attr.name, "storeReg")!=0&& strcmp(t->attr.name, "loadReg")!=0 && strcmp(t->attr.name, "setandoPC")!=0
				&& strcmp(t->attr.name, "inputDoContexto")!=0 && strcmp(t->attr.name, "outputDoContexto")!=0 && strcmp(t->attr.name, "execucaoDoProcesso")!=0 && strcmp(t->attr.name, "pegaInterrupcao")!=0)
			{   
				fprintf(listing,"Linha %d - Erro: A funcao %s nao foi declarada.\n", t->lineno, t->attr.name);
				st_insert(t->attr.name,t->lineno,0,escopo,NULLL,CALL, t->vet);
				Error = TRUE;
			}
			else {
				st_insert(t->attr.name,t->lineno,0,escopo,NULLL,CALL, t->vet);
			}
				break;
			default:
				break;
      }
  }
}

void buildSymtab(TreeNode * syntaxTree){ 
  //st_insert("input",0,location++, "global", "function", "integer"); // specification
  //st_insert("output",0,location++, "global", "function", "void"); // specification 
  traverse(syntaxTree,insertNode,nullProc); 
  main_search();
  typeCheck(syntaxTree);
  if (TraceAnalyze)
  { 
    fprintf(listing,"\nTabela de Simbolos:\n\n");
    printSymTab(listing);
  }
}

static void checkNode(TreeNode * t){
 switch (t->nodekind)
  { 
   case expK:
      switch (t->kind.exp)
      { 
        case opK:
        	if (((t->child[0]->kind.exp == ativK) &&( getFunType(t->child[0]->attr.name)) == VOIDTYPE) ||
              ((t->child[1]->kind.exp == ativK) && (getFunType(t->child[1]->attr.name) == VOIDTYPE)))
                typeError(t->child[0],"Ativação de funcao do tipo void");
			break;

        default:
        	break;
      }
      break;
    case stmtK:
      switch (t->kind.stmt)
      { 
        case assignK:
          if (t->child[1]->kind.exp == ativK && getFunType(t->child[1]->attr.name) == VOIDTYPE)
            typeError(t->child[0],"Funcao com retorno void nao pode ser atribuido");
          break;
        default:
        break;
      }
    break;
    default:
    break;
  }
}

void typeCheck(TreeNode * syntaxTree){ 
    traverse(syntaxTree,nullProc,checkNode);
}
