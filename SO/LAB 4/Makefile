all: clear obj exec
.PHONY : all

clear:
	rm -f *.out *.so

obj:
	gcc -Wall -Wextra -shared -g -o my_semaphore.so my_semaphore.c -ldl -fPIC

exec:
	gcc -Wall -Wextra -g -o App.out App.c -lpthread -lm

run:
	LD_PRELOAD=./my_semaphore.so ./App.out