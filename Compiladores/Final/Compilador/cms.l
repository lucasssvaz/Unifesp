%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
static int yylex(void);
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%option noyywrap
%option nounput

%%

"else"          {return ELSE;}
"if"            {return IF;}
"int"		        {return INT;}
"return"	      {return RETURN;}
"void"		      {return VOID;}
"while"		      {return WHILE;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"<"             {return LT;}
"<="		        {return LTE;}
">"		          {return GT;}
">="		        {return GTE;}
"=="            {return EQ;}
"!="	       	  {return NE;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","		          {return COMMA;}
"("             {return LPAR;}
")"             {return RPAR;}
"["		          {return LBRK;}
"]"		          {return RBRK;}
"{"		          {return LBRC;}
"}"		          {return RBRC;}
"/*"            { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
  		              if (c == '*') 
                    { 
		                  if(input() == '/') break;
		                }		
                  } while (1);
                }
{identifier}    {return ID;}
{number}        {return NUM;}
{newline}       {lineno++;}
{whitespace}    {         }
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

