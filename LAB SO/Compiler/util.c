#include "globals.h"
#include "symtab.h"
#include "util.h"
#include "intercode.h"

FILE * intercode;

void printType( TokenType token ){
    switch (token){
        case SOM: fprintf(intercode, "SOM");   break;
        case SUB: fprintf(intercode, "SUB");   break;
        case MUL: fprintf(intercode, "MUL");   break;
        case DIV: fprintf(intercode, "DIV");   break;
        case LT: fprintf(intercode, "LT"); break;
        case LTE: fprintf(intercode, "LTE"); break;
        case GT: fprintf(intercode, "GT"); break;
        case GTE: fprintf(intercode, "GTE"); break;
        case CMP: fprintf(intercode, "CMP"); break;
        case DIF: fprintf(intercode, "DIF"); break;
  }
}

void printToken( TokenType token, const char* tokenString )
{ 
  switch (token)
  { 
    case NUM: fprintf(listing, "Numero: %s\n",tokenString); break;
    case ID:  fprintf(listing, "ID: %s\n",tokenString);  break;

    case SOM: fprintf(listing, "+\n");   break;
    case SUB: fprintf(listing, "-\n");   break;
    case MUL: fprintf(listing, "*\n");   break;
    case DIV: fprintf(listing, "/\n");   break;
    case ATRIBUI: fprintf(listing, " =\n");  break;

    case VIR: fprintf(listing, ",\n"); break;
    case PV: fprintf(listing, "; \n"); break;

    case APR: fprintf(listing, "(\n");   break;
    case FPR: fprintf(listing, ")\n");   break;
    case ACO: fprintf(listing, "[\n");   break;
    case FCO: fprintf(listing, "]\n");   break;
    case ACH: fprintf(listing, " {\n");   break;
    case FCH: fprintf(listing, "}\n");   break;

    case ENDFILE: fprintf(listing, "EOF\n"); break;
    case ERR: fprintf(listing, "Erro: %s\n ",tokenString);  break;

    case IF: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;
    case ELSE: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;
    case INT: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;
    case RET: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;
    case VOID: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;
    case WHILE: fprintf(listing, "Palavra Reservada: %s\n",tokenString); break;

    case LT: fprintf(listing, "<\n"); break;
    case LTE: fprintf(listing, "<=\n"); break;
    case GT: fprintf(listing, ">\n"); break;
    case GTE: fprintf(listing, ">=\n"); break;
    case CMP: fprintf(listing, "==\n"); break;
    case DIF: fprintf(listing, "!=\n"); break;
    default: 
    fprintf(listing,"Token Inválido: %d\n",token);
  }
}


TreeNode * newStmtNode(StmtKind kind)
{ 
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(listing,"Erro de falta de memoria na linha %d\n",lineno);
    else 
    {
        for (i=0;i<MAXCHILDREN;i++) 
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = stmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}


TreeNode * newExpNode(ExpKind kind)
{ 
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(listing,"Erro de falta de memoria na linha %d\n",lineno);
    else 
    {
        for (i=0;i<MAXCHILDREN;i++) 
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = expK;
        t->kind.exp = kind; 
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}

/*TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = declK;
    t->kind.decl = kind;
    t->lineno = lineno;
    t->type = VOID;
  }
  return t;
}*/

char * copyString(char * s)
{ 
    int n;
    char * t;
    if (s==NULL) 
        return NULL;
    n = strlen(s)+1;
    t = malloc(n);
    if (t==NULL)
        fprintf(listing,"Erro de falta de memoria na linha %d\n",lineno);
    else 
        strcpy(t,s);
    return t;
}

static int indentno = 0;


#define INDENT indentno+=4
#define UNINDENT indentno-=4


static void printSpaces(void)
{ 
  int i;
    for (i=0;i<indentno;i++)
      fprintf(listing," ");
}


void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==stmtK)
    { switch (tree->kind.stmt) {
        case ifK:
            fprintf(listing,"If\n");
            break;
        case assignK:
            fprintf(listing,"Assign\n");
            break;
        case whileK:
            fprintf(listing,"While\n");
            break;       
        case returnK:
            fprintf(listing, "Return\n");
            break;        

        default:
            fprintf(listing,"Unknown StmtNode kind\n");
            break;
      }
    }
    else if (tree->nodekind==expK)
    { switch (tree->kind.exp) {
        case opK:
            fprintf(listing,"Operation: ");
            printToken(tree->attr.op,"\0");
            break;
        case constK:
            fprintf(listing,"Constant: %d\n",tree->attr.val);
            break;
        case idK:
            fprintf(listing,"Id: %s\n",tree->attr.name);
            break;
        case varDeclK:
           fprintf(listing,"Var: %s\n",tree->attr.name);
           break;
        case funDeclK:
            fprintf(listing,"Func: %s\n",tree->attr.name);
            break;
        case ativK:
            fprintf(listing,"Call to Function: %s\n",tree->attr.name);
            break;
		case typeK:
            fprintf(listing,"Type %s\n",tree->attr.name);
            break;
        case paramK:
           fprintf(listing,"Id: %s\n",tree->attr.name);
           break; 
        case vectorK:
          fprintf(listing, "Vetor: %s\n", tree->attr.name);
	        break;

        default:
            fprintf(listing,"Unknown ExpNode kind\n");
            break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

