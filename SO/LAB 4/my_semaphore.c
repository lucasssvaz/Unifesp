#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <dlfcn.h>

typedef struct Cell{
	short IsProcess;
	short Connected;
	int MaxConnections;
} Node;

typedef struct ${
	int N_Nodes;
	Node *Nodes;
} Graph;

int (*_sem_wait)(sem_t *) = NULL;
int (*_sem_post)(sem_t *) = NULL;
int (*_sem_init)(sem_t *, int, unsigned int) = NULL;
int (*_sem_getvalue)(sem_t *, int *) = NULL;

Graph *G = NULL;

void Graph_Initialization(){
	int i;
	G->Nodes = (Node *) calloc (1, sizeof(Node));
}

int sem_wait(sem_t *sem) {

	int r;
	if (!_sem_wait) {
		_sem_wait = dlsym(RTLD_NEXT, "sem_wait");
	}


	r = _sem_wait(sem);


	return(r);
}

int sem_post(sem_t *sem) {

	int r;
	if (!_sem_post) {
		_sem_post = dlsym(RTLD_NEXT, "sem_post");
	}

	
	r = _sem_post(sem);
	return(r);
}

int sem_init(sem_t *sem, int pshared, unsigned int value){

	int r;
	if (!_sem_init) {
		_sem_init = dlsym(RTLD_NEXT, "sem_init");
	}

	
	r = _sem_init(sem, pshared, value);
	return(r);
}

int sem_getvalue(sem_t *sem, int *sval){

	int r;
	if (!_sem_getvalue) {
		_sem_getvalue = dlsym(RTLD_NEXT, "sem_getvalue");
	}

	
	r = _sem_getvalue(sem, sval);
	return(r);
}