#include <stdlib.h>
#include <errno.h>

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not generate intermediate code */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "intercode.h"

#endif
#endif
#endif

#include "assemblycode.h"
#include "binarycode.h"

/* allocate global variables */
int progloc = 0;
int lineno = 0;
FILE * source;
FILE * listing;
FILE * codeinter;
FILE * acode;
FILE * bcode;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;

int Error = FALSE;

int main( int argc, char * argv[] ){ 
	TreeNode * syntaxTree;
	QuadList Quads;
	AssemblyCode codehead;
	char pgm[120]; /* source code file name */

	if (argc != 3)
	{ 
		fprintf(stderr,"Usage: %s <filename> <id>\n",argv[0]);
		exit(1);
	}

	char *p;
	errno = 0;
	progloc = (int) strtol(argv[2], &p, 10);
	if (*p != '\0' || errno != 0)
	{
		fprintf(stderr, "Invalid ID. Aborting.\n");
		exit(1);
	}

	strcpy(pgm,argv[1]);

	if (strchr (pgm, '.') == NULL)
		strcat(pgm,".cm");
	
	source = fopen(pgm,"r");
	if (source==NULL)
	{ 
		fprintf(stderr,"Arquivo %s nao encontrado\n",pgm);
		exit(1);
	}
	listing = stdout; /* send listing to screen */
	fprintf(listing,"\nCompilacao C-: %s\n",pgm);
	codeinter = fopen("codintermediario.txt","w+");
	acode = fopen("codassembly.txt","w+");
	bcode = fopen("bincode.txt","w+");
#if NO_PARSE
	while (getToken()!=ENDFILE);
#else
	syntaxTree = parse();
	if (TraceParse) 
	{
		fprintf(listing,"\nArvore Sintatica:\n");
		printTree(syntaxTree);
	}
#if !NO_ANALYZE
	if (! Error)
	{ 
		if (TraceAnalyze) fprintf(listing,"\nConstruindo Tabela de Simbolos...\n");
		buildSymtab(syntaxTree);
		if (TraceAnalyze) fprintf(listing,"\nChecando Tipos...\n");
		typeCheck(syntaxTree);
		if (TraceAnalyze) fprintf(listing,"\nChecagem de Tipo Concluida\n");
	}
#if !NO_CODE
	if(!Error)
	{
		if (codeinter == NULL)
		{ printf("Nao foi possivel abrir \"codintermediario.txt\"\n");
			exit(1);
		}
		fprintf(codeinter, "\nCodigo Intermediario do %s:\n\n", pgm);
		if (TraceCode) fprintf(listing,"\nConstruindo Codigo Intermediario...\n");
		Quads = GenInterCode(syntaxTree);
		if (TraceCode) fprintf(listing,"\nCodigo Intermediario Concluido\n");
		fclose(codeinter);
		fprintf(acode, "\nCodigo Assembly do %s:\n\n", pgm);
		if (TraceCode) fprintf(listing,"\nConstruindo Codigo Assembly...\n");
		codehead = GenAssembly(Quads);
		if (TraceCode) fprintf(listing,"\nCodigo Assembly Concluido\n");
		if (TraceCode) fprintf(listing,"\nConstruindo Codigo Binario...\n");
		GenBinary(codehead,getSize());
		if (TraceCode) fprintf(listing,"\nCodigo Binario Concluido\n");
		fclose(acode);
		fclose(bcode);
	}
	
#endif
#endif
#endif
	fclose(source);
	return 0;
}

