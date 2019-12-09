%{
    #define YYPARSER /* distinguishes Yacc output from other code files */
   
    #include "globals.h"
    #include "util.h"
    #include "scan.h"
    #include "parse.h"

    #define YYSTYPE TreeNode *
    static TreeNode * savedTree;   
    static int yylex(void);
    int yerror(char* message);
    void defScope(TreeNode* t, char* scope);
%}

%token IF ELSE WHILE INT VOID RETURN
%token NUM ID
%token ASSIGN EQ NE LT LTE GT GTE PLUS MINUS TIMES OVER LPAR RPAR LBRK RBRK LBRC RBRC COMMA SEMI
%token ERROR ENDFILE

%% 

program            :   list_declaration
                          { savedTree = $1; }
                    ;
list_declaration    :   list_declaration declaration
                        { YYSTYPE t = $1;
                          if(t != NULL)
		   	  			  { while(t->sibling != NULL)
                               t = t->sibling;
                            t->sibling = $2;
                            $$ = $1; }
                            else $$ = $2;
                        }
                    |  declaration
                          { $$ = $1; }
                    ;
declaration         :  var_declaration
                          { $$ = $1; }
                    |  fun_declaration
                         { $$ = $1; }
                    ;
var_declaration     :   INT ident SEMI
                        { $$ = newExpNode(TypeK);
                          $$->type = Integer;
                          $$->attr.name = "integer";
                          $$->child[0] = $2;
                          $2->nodekind = StmtK;
                          $2->kind.stmt = VariableK;
						  $2->type = Integer;
                        }
                    |   INT ident LBRK num RBRK SEMI
                        { $$ = newExpNode(TypeK);
                          $$->type = Integer;
                          $$->attr.name = "integer";
                          $$->child[0] = $2;
                          $2->nodekind = StmtK;
                          $2->kind.stmt = VariableK;
						  $2->type = Integer; 
                          $2->attr.len = $4->attr.val;
                        }
                    ;
fun_declaration     :   INT ident LPAR params RPAR compound_decl
                        { $$ = newExpNode(TypeK);
                          $$->type = Integer;
                          $$->attr.name = "integer";
                          $$->child[0] = $2;
                          $2->child[0] = $4;
                          $2->child[1] = $6;
                          $2->nodekind = StmtK;
                          $2->kind.stmt = FunctionK;
						  $2->type = Integer;
						  $4->type = Integer;
						  defScope($2->child[0], $2->attr.name);
						  defScope($2->child[1], $2->attr.name);
                        }
                    |   VOID ident LPAR params RPAR compound_decl
                        { $$ = newExpNode(TypeK);
                          $$->type = Void;
                          $$->attr.name = "void";
                          $$->child[0] = $2;
                          $2->child[0] = $4;
                          $2->child[1] = $6;
                          $2->nodekind = StmtK;
                          $2->kind.stmt = FunctionK;
						  defScope($2->child[0], $2->attr.name);
						  defScope($2->child[1], $2->attr.name);
                        }
                    ;
params              :   param_list
                          { $$ = $1; }
                    |   VOID
                        { $$ = newExpNode(TypeK);
           				  $$->attr.name = "void";
						}
                    ;
param_list          :   param_list COMMA param
                        { YYSTYPE t = $1;
                          if(t != NULL)
						  { while(t->sibling != NULL)
                                t = t->sibling;
                            t->sibling = $3;
                            $$ = $1; }
                            else $$ = $3;
                        }
                    |   param
                        { $$ = $1; }
                    ;
param               :   INT ident
                        { $$ = newExpNode(TypeK);
					      $2->nodekind = StmtK;
                          $2->kind.stmt = VariableK;
                          $$->type = Integer;
						  $2->type = Integer;
                          $$->attr.name = "integer";
                          $$->child[0] = $2;
                        }
                    |   INT ident LBRK RBRK
                        { $$ = newExpNode(TypeK);
						  $2->nodekind = StmtK;
                          $2->kind.stmt = VariableK;
                          $$->type = Integer;
                          $$->attr.name = "integer";
                          $$->child[0] = $2;
						  $2->type = Integer;
                        }
                    ;
compound_decl       :   LBRC local_declarations statement_list RBRC
                        { YYSTYPE t = $2;
                          if(t != NULL)
						  { while(t->sibling != NULL)
                              t = t->sibling;
                            t->sibling = $3;
                            $$ = $2; }
                            else $$ = $3;
                        }
                    |   LBRC local_declarations RBRC
                          { $$ = $2; }
                    |   LBRC statement_list RBRC
                          { $$ = $2; }
                    |   LBRC RBRC
                          {	}
                    ;
local_declarations  :   local_declarations var_declaration
                        { YYSTYPE t = $1;
                          if(t != NULL)
						  { while(t->sibling != NULL)
                              t = t->sibling;
                            t->sibling = $2;
                            $$ = $1; }
                            else $$ = $2;
                        }
                   |    var_declaration
                          { $$ = $1; }
                    ;
statement_list      :   statement_list statement
                        { YYSTYPE t = $1;
                          if(t != NULL)
					      { while(t->sibling != NULL)
                              t = t->sibling;
                            t->sibling = $2;
                            $$ = $1; }
                           else $$ = $2;
                        }
                    |   statement
                        { $$ = $1; }
                    ;
statement           :   expression_decl
                          { $$ = $1; }
                    |   compound_decl
                          { $$ = $1; }
                    |   selection_decl
                          { $$ = $1; }
                    |   iterator_decl
                          { $$ = $1; }
                    |   return_decl
                          { $$ = $1; }
                    ;
expression_decl     :   expression SEMI 
                          { $$ = $1; }
                    |   SEMI
                          { }
                    ;
selection_decl      :   IF LPAR expression RPAR statement 
                        { $$ = newStmtNode(IfK);
                          $$->child[0] = $3;
                          $$->child[1] = $5;
                        }
                    |   IF LPAR expression RPAR statement ELSE statement
                        { $$ = newStmtNode(IfK);
                          $$->child[0] = $3;
                          $$->child[1] = $5;
                          $$->child[2] = $7;
                        }
                    ;
iterator_decl       :   WHILE LPAR expression RPAR statement
                        { $$ = newStmtNode(WhileK);
                          $$->child[0] = $3;
                          $$->child[1] = $5;
                        }
                   ;
return_decl        :   RETURN SEMI
                       { $$ = newStmtNode(ReturnK);
						 $$->type = Void;
                       }
                   |   RETURN expression SEMI
                       { $$ = newStmtNode(ReturnK);
                         $$->child[0] = $2;
                       }
                   ;
expression         :   var ASSIGN expression
                       { $$ = newStmtNode(AssignK);
                         $$->child[0] = $1;
                         $$->child[1] = $3;
                       }
                   |   simple_expression
                        { $$ = $1; }
                   ;
var                :   ident
                        { $$ = $1; }
                   |   ident LBRK expression RBRK
                       { $$ = $1;
                         $$->child[0] = $3;
                         $$->kind.exp = VectorK;
						 $$->type = Integer;
                       }
                    ;
simple_expression   : sum_expression relational sum_expression
                       { $$ = $2;
                         $$->child[0] = $1;
                         $$->child[1] = $3;
                       }
                    |  sum_expression
                        { $$ = $1; }
                    ;
relational          :  EQ
                       { $$ = newExpNode(OpK);
                         $$->attr.op = EQ;  
						 $$->type = Boolean;                          
                       }
                    |  NE
                       { $$ = newExpNode(OpK);
                         $$->attr.op = NE;
						 $$->type = Boolean;                            
                       }
                    |  LT
                       { $$ = newExpNode(OpK);
                         $$->attr.op = LT;                            
						 $$->type = Boolean;
                       }
                    |  LTE
                       { $$ = newExpNode(OpK);
                         $$->attr.op = LTE;                            
						 $$->type = Boolean;
                       }
                    |  GT
                       { $$ = newExpNode(OpK);
                         $$->attr.op = GT;                            
						 $$->type = Boolean;
                       }
                    |  GTE
                       { $$ = newExpNode(OpK);
                         $$->attr.op = GTE;                            
						 $$->type = Boolean;
                       }
                    ;
sum_expression      :  sum_expression sum term
                       { $$ = $2;
                         $$->child[0] = $1;
                         $$->child[1] = $3;
                       }
                    |  term
                        { $$ = $1; }
                    ;
sum                 :  PLUS
                       { $$ = newExpNode(OpK);
                         $$->attr.op = PLUS;                            
                       }
                    |  MINUS
                       { $$ = newExpNode(OpK);
                         $$->attr.op = MINUS;                            
                       }
                    ;
term                :  term mult factor
                       { $$ = $2;
                         $$->child[0] = $1;
                         $$->child[1] = $3;
                       }
                   |   factor
                        { $$ = $1;}
                    ;
mult                :  TIMES
                       { $$ = newExpNode(OpK);
                         $$->attr.op = TIMES;                            
                       }
                   |   OVER
                       { $$ = newExpNode(OpK);
                         $$->attr.op = OVER;                            
                       }
                    ;
factor              :  LPAR expression RPAR
                        { $$ = $2; }
                   |   var
                        { $$ = $1; }
                   |   activation
                        { $$ = $1; }
                   |   num
                        { $$ = $1; }
                    ;
activation          :  ident LPAR arg_list RPAR
                       { $$ = $1;
                         $$->child[0] = $3;
                         $$->nodekind = StmtK;
                         $$->kind.stmt = CallK;
                       }
                    |  ident LPAR RPAR
					   { $$ = $1;
                         $$->nodekind = StmtK;
                         $$->kind.stmt = CallK;
                       }
                       
                    ;
arg_list            :  arg_list COMMA expression
                       { YYSTYPE t = $1;
                         if(t != NULL)
						 { while(t->sibling != NULL)
                             t = t->sibling;
                           t->sibling = $3;
                           $$ = $1; }
                           else $$ = $3;
                        }
                    |   expression
                          { $$ = $1; }
                    ;
ident               :   ID
                        { $$ = newExpNode(IdK);
                          $$->attr.name = copyString(tokenString);
                        }
                    ;
num                 :   NUM
                        { $$ = newExpNode(ConstK);
                          $$->attr.val = atoi(tokenString);
						  $$->type = Integer;
					    }
                    ;

%%

int yyerror(char* message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}