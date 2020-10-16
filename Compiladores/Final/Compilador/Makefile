all: clear scanner parser obj exec
.PHONY : all

clear:
	rm -f lex.yy.c cms.tab.c cms.tab.h out.txt valgrind-out.txt Compiler *.o *.output *.tm

scanner:
	flex cms.l

parser:
	bison -v -d cms.y

obj:
	gcc -Wall -Wextra -g -c *.c 

exec:
	gcc -Wall -Wextra -g -o Compiler *.o  -lm

gdb: all
	gdb --args Compiler sort.cms

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./Compiler sort.cms
