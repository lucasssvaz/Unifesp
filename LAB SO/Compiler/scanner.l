%option noyywrap

%{

#include "globals.h"
#include "util.h"
#include "scan.h"

char tokenString[MAXTOKENLEN+1];
extern int yylex(void);


%}

DIGITO [0-9]
LETRA [a-zA-Z]
whitespace  [ \t\r]+

%%
{whitespace}    	{           }

"+"			    	{return SOM;}
"-"			    	{return SUB;}
"*"			    	{return MUL;}
"/"			    	{return DIV;}
"="			    	{return ATRIBUI;}

","			    	{return VIR;}
";"			    	{return PV;}

"("			    	{return APR;}
")"			    	{return FPR;}
"["				{return ACO;}
"]"				{return FCO;}
"{"				{return ACH;}
"}"				{return FCH;} 

"/*"				{ char c;
				  while(1){
					c = input();
					if(c==EOF) break;
					if(c=='\n') lineno++;
					if(c=='*'){
						c = input();
						if(c=='/') break;
						}
					}	
				}	
			
\n			        {lineno++;}
"if"				{return IF;}
"else"				{return ELSE;}
"int"				{return INT;}
"return"			{return RET;}
"void"				{return VOID;}
"while"				{return WHILE;}

"<"				    {return LT;}
"<="				{return LTE;}
">"			    	{return GT;}
">="				{return GTE;}
"=="				{return CMP;}
"!="				{return DIF;}

{DIGITO}+			{return NUM;}
{LETRA}+			{return ID;}
.			        {return ERR;}
%%

TokenType getToken(void){
    static int firstTime = TRUE;
    TokenType currentToken;
    if(firstTime){
        firstTime = FALSE;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(tokenString,yytext,MAXTOKENLEN);
    if(TraceScan){
        fprintf(listing,"\t%d: ",lineno);
        printToken(currentToken,tokenString);
    }
    return currentToken;
}



