%{

    #define YYPARSER    
    #include "globals.h"
    #include "util.h"
    #include "scan.h"
    #include "parse.h"

    #define YYSTYPE TreeNode *
    static TreeNode * savedTree;   
    static int yylex(void);
    int yyerror(char* msg);
    char *scope = "Global";
    char * idtype = "";
    char * datatype = "";
    static char *savedname;
    int flag = 0;
    int params = 0;
    
%}


%token IF ELSE WHILE RET INT VOID
%right INT
%token ATRIBUI CMP DIF LT LTE GT GTE SOM SUB MUL DIV APR FPR ACO FCO ACH FCH VIR PV
%token ID NUM
%token ERR ENDFILE

%nonassoc FPR
%nonassoc ELSE

%%

programa: declaracao_lista
        {
            savedTree = $1;
        }        
    ;
declaracao_lista: declaracao_lista declaracao
        {
            YYSTYPE t = $1;
            if(t != NULL){
                while(t->sibling != NULL)
                    t = t->sibling;
                t->sibling = $2;
                $$ = $1;
            }
            else
                $$ = $2;
        }
    | declaracao
        {
            $$ = $1;
        }
	;
declaracao: var_declaracao
        {
            $$ = $1;
        }
    | fun_declaracao
        {
            $$ = $1;
            scope= "Global";
        }
    ;

id: ID
    {
        $$ = newExpNode(idK);
        $$->attr.name = copyString(tokenString);
        savedname = copyString(tokenString);
        $$->scope = scope;
        if(flag ==  1){
            scope= savedname;
            flag = 0;
        }
    }
    ;
num: NUM
    {
        $$ = newExpNode(constK);
        $$->attr.val= atoi(tokenString);
        $$->type= INTTYPE;
    }
    ;

var_declaracao: INT id PV
        {
            $$= newExpNode(typeK);
            $$->attr.name= "INT";
            $$->size= 0;
            $$->child[0]= $2;
            $$->scope= scope;

            $2->kind.exp= varDeclK;
            $2->type= INTTYPE;
        }
    | INT id ACO num FCO PV
        {
            $$= newExpNode(typeK);
            $$->attr.name= "INT";
            $$->child[0]= $2;
            $$->scope= scope;

            $2->kind.exp= varDeclK;
            $2->size= $4->attr.val;
            $2->type= INTTYPE;
        }
    | ERR {yyerrok;}
    ;
fun_declaracao: INT id APR params FPR composto_decl
        {
            $$= newExpNode(typeK);
            $$->attr.name= "INT";
            $$->child[0]= $2;
            $$->scope= scope;

            $2->kind.exp= funDeclK;
            $2->lineno= $$->lineno;
            $2->type= INTTYPE;
            $2->child[0]= $4;
            $2->child[1]= $6;
            flag= 1;              
        }
    | VOID id APR params FPR composto_decl
        {
            $$= newExpNode(typeK);
            $$->attr.name= "VOID";
            $$->child[0]= $2;
            $$->scope= scope;

            $2->type= VOIDTYPE;
            $2->kind.exp= funDeclK;
            $2->lineno= $$->lineno;
            $2->child[0]= $4;
            $2->child[1]= $6;
            flag= 1;
        }
    ;
params: param_lista
        {
            $$ = $1;
        }
    | VOID
        {
            $$= newExpNode(typeK);
            $$->attr.name= "VOID";
            $$->size= 0;
            $$->child[0]= NULL;
        }
    ;
param_lista: param_lista VIR param
        {
            YYSTYPE t = $1;
            if(t != NULL){
                while(t->sibling != NULL)
                t = t->sibling;
                t->sibling = $3;
                $$ = $1;
            }
            else
                $$ = $3;
        }

	| param
        {
            $$ = $1;
        }
	;
param: tipo_especificador id

        {
            $$= $1;
            $$->child[0]= $2;
            $$->scope= scope;
            $$->size= 0;
            flag= 0;

            $2->kind.exp= paramK;
        }
    | tipo_especificador id ACO FCO
        {
            $$= $1;
            $$->child[0]= $2;
            $$->scope= scope;
            $$->size= 0;
            flag= 0;

            $2->kind.exp = paramK; 
        }
    ;

tipo_especificador: INT
        {
            $$ = newExpNode(typeK);
            $$->attr.name = "INT";
            $$->type = INTTYPE;
            $$->size = 1;
        }
    | VOID
        {
            $$ = newExpNode(typeK);
            $$->attr.name = "VOID";
            $$->type = INTTYPE;
            $$->size = 1;
        }
    ;

composto_decl: ACH local_declaracoes statement_lista FCH
        {
            YYSTYPE t = $2;
            if(t != NULL){
                while(t->sibling != NULL)
                    t= t->sibling;
                t->sibling= $3;
                $$ = $2;
            }
            else
                $$ = $3;
        }
    |   ACH statement_lista FCH
        {
            $$ = $2;
        }
    |   ACH local_declaracoes FCH
        {
            $$ = $2;
        }
    |   ACH FCH
        {

        }
    ;
local_declaracoes: local_declaracoes var_declaracao
        {
            YYSTYPE t = $1;
            if(t != NULL){
                while(t->sibling != NULL)
                    t= t->sibling;
                t->sibling= $2;
                $$ = $1;
            }
            else
                $$ = $2;
        }
    | var_declaracao
        {
            $$ = $1;
        }
    ;
statement_lista: statement_lista statement
        {
            YYSTYPE t = $1;
            if(t != NULL){
                while(t->sibling != NULL)
                    t= t->sibling;
                t->sibling= $2;
                $$ = $1;
            }
            else
                $$ = $2;
        }
    | statement
        {
            $$ = $1;
        }
    ;
statement: expressao_decl
        {
            $$ = $1;
        }
    | composto_decl
        {
            $$ = $1;
        }
    | selecao_decl
        {
            $$ = $1;
        }
    | iteracao_decl
        {
            $$ = $1;
        }
    | retorno_decl
        {
            $$ = $1;
        }
    ;
expressao_decl: expressao PV
        {
            $$ = $1;
        }
    | PV
        {
            
        }
    | error {yyerrok;}
    ;
selecao_decl: IF APR expressao FPR statement
        {
            $$ = newStmtNode(ifK);
            $$->child[0]= $3;
            $$->child[1]= $5;
            $$->scope = $3->scope;
        }
	| IF APR expressao FPR statement ELSE statement
        {
            $$ = newStmtNode(ifK);
            $$->child[0]= $3;
            $$->child[1]= $5;
            $$->child[2]= $7;
            $$->scope = $3->scope;
        }
    ;
iteracao_decl: WHILE APR expressao FPR statement
        {
            $$ = newStmtNode(whileK);
            $$->child[0]= $3;
            $$->child[1]= $5;
            $$->scope = $3->scope;
        }
    ;
retorno_decl: RET PV
        {
            $$ = newStmtNode(returnK);
        }
	| RET expressao PV
        {
            $$ = newStmtNode(returnK);
            $$->child[0] = $2;
        }
	;
expressao: var ATRIBUI expressao
        {
            $$ = newStmtNode(assignK);
            $$->attr.name= $1->attr.name;
            $$->scope = scope;
            $$->child[0]= $1;
            $$->child[1]= $3;
        }
    | simples_expressao
        {
            $$ = $1;
        }
	;
var: id
        {
            $$ = $1;
        }
    | id ACO expressao FCO
        {
            $$ = $1;
            // $$ = newExpNode(vectorK);
            $$->attr.name = $1->attr.name;
            $$->child[0] = $3;
            
        }
	;
simples_expressao: soma_expressao relacional soma_expressao
        {
            $$ = $2;
            $$->child[0]= $1;
            $$->child[1]= $3;
            $$->scope = scope;
        }
    | soma_expressao
        {
            $$ = $1;
        }
    	;
relacional: LTE
        {
            $$ = newExpNode(opK);
            $$->attr.op= LTE;
        }
	| LT
        {
            $$ = newExpNode(opK);
            $$->attr.op= LT;
        }
	| GT
        {
            $$ = newExpNode(opK);
            $$->attr.op= GT;
        }
	| GTE
        {
            $$ = newExpNode(opK);
            $$->attr.op= GTE;
        }
	| CMP
        {
            $$ = newExpNode(opK);
            $$->attr.op= CMP;
        }
	| DIF
        {
            $$ = newExpNode(opK);
            $$->attr.op= DIF;
        }
	;
soma_expressao: soma_expressao soma termo
        {
            $$ = $2;
            $$->child[0]= $1;
            $$->child[1]= $3;
            $$->scope = scope;
        }
	| termo
        {
            $$ = $1;
        }
    ;
soma: SOM
        {
            $$ = newExpNode(opK);
            $$->attr.op= SOM;    
        }
	| SUB
        {
            $$ = newExpNode(opK);
            $$->attr.op= SUB;    
        }
	;
termo: termo mult fator
        {
            $$ = $2;
            $$->scope = scope;
            $$->child[0]= $1;
            $$->child[1]= $3;
        }
	| fator
        {
            $$ = $1;
        }
	;
mult: MUL
        {
            $$ = newExpNode(opK);
            $$->attr.op= MUL;    
        }	
    | DIV
        {
            $$ = newExpNode(opK);
            $$->attr.op= DIV;    
        }
	;
fator: APR expressao FPR
        {
            $$ = $2;
        }
	| var
        {
            $$ = $1;
        }
	| ativacao
        {
            $$ = $1;
            params = 0;
        }
	| num
        {
            $$ = $1;
        }
	;
ativacao: id APR arg_lista FPR
        {
            $$ = newExpNode(ativK);
            $$->attr.name = $1->attr.name;
            $$->scope = scope;
            $$->child[0] = $3;
            $$->params = params;    
        }
    | id APR FPR
        {
            $$ = newExpNode(ativK);
            $$->attr.name = $1->attr.name;
            $$->scope = scope;
            $$->params = params;
        }
        ;
arg_lista: arg_lista VIR expressao
        {
            YYSTYPE t = $1;
            if(t != NULL){
                while(t->sibling != NULL)
                    t= t->sibling;
                t->sibling= $3;
                params++;
                $$ = $1;
            }
            else
                $$ = $3;
        }
    | expressao
        {
            params++;
            $$ = $1;
        }
	;
   

%%

static int yylex(void){
    return getToken(); 
}

int yyerror(char* msg){
    fprintf(listing,"Erro Sintatico na linha %d: %s\n",lineno,msg);
    fprintf(listing,"Token Atual: ");
    printToken(yychar,tokenString);
    Error = TRUE;
    exit(1);
    return 0;
}

TreeNode * parse(void){
    yyparse();
    return savedTree;
}