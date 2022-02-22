#Requires: build-essential flex bison libbison-dev
#Run:
#	make
#	./Compiler <Filename>

all: tokenizer parser build

tokenizer:
	flex scanner.l

parser:
	bison -d parser.y

build:
	cc -c *.c -fno-builtin-exp -Wno-implicit-function-declaration -ggdb -O0
	cc *.o -ly -o Compiler -fno-builtin-exp -ggdb -O0

clean:
	rm -f Compiler lex.yy.c *.o parser.tab.*
