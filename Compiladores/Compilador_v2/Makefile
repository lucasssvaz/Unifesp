all: clean scanner parser obj exec
.PHONY : all

clean:
	rm -f lex.yy.c cms.tab.c cms.tab.h out.txt Compiler *.o *.output

scanner:
	flex cms.l

parser:
	bison -v -d cms.y

obj:
	gcc -Wall -c *.c -O2

exec:
	gcc -Wall -g -o Compiler *.o -ly -O2
