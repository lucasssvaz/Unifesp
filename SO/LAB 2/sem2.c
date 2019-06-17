//
//	Sistemas Operacionais - Lab 1
//		Lucas Saavedra Vaz
//			120503
//
//============================================================================================================================= DECLARATIONS

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define X_COUNT 2
#define Y_COUNT 2
#define ROOM_SIZE 20

sem_t Room_Sem, Mutex_X, Mutex_Y, Available_Sem;

int qntX = 0, qntY = 0;

//============================================================================================================================= FUNCTIONS

void *X_Func(void *args){
	int pid = *(int *)args;
	while(1){

		sem_wait(&Mutex_X);
		qntX++;
		if (qntX == 1)
			sem_wait(&Available_Sem);
		sem_wait(&Room_Sem);
		sem_post(&Mutex_X);

		printf("X[%d]: Joined the Room.\n", pid);
		fflush(stdout);

		sem_wait(&Mutex_X);
		qntX--;
		if (qntX == 0){
			printf("X[%d]: %sLast one inside.%s\n", pid, ANSI_COLOR_RED, ANSI_COLOR_RESET);
			fflush(stdout);
			sem_post(&Available_Sem);
		}
		sem_post(&Room_Sem);
		sem_post(&Mutex_X);

		printf("X[%d]: Left the Room.\n", pid);
		fflush(stdout);
	}
}

//--------------------------------------------

void *Y_Func(void *args){
	int pid = *(int *)args;
	while(1){

		sem_wait(&Mutex_Y);
		qntY++;
		if (qntY == 1)
			sem_wait(&Available_Sem);
		sem_wait(&Room_Sem);
		sem_post(&Mutex_Y);

		printf("Y[%d]: Joined the Room.\n", pid);
		fflush(stdout);

		sem_wait(&Mutex_Y);
		qntY--;
		if (qntY == 0){
			printf("Y[%d]: %sLast one inside.%s\n", pid, ANSI_COLOR_RED, ANSI_COLOR_RESET);
			fflush(stdout);
			sem_post(&Available_Sem);
		}
		sem_post(&Room_Sem);
		sem_post(&Mutex_Y);

		printf("Y[%d]: Left the Room.\n", pid);
		fflush(stdout);
	}
}

//============================================================================================================================= MAIN

int main(int argc, char **argv){
	int i = 0;

	pthread_t Group_X[X_COUNT], Group_Y[Y_COUNT];
	int Id_X[X_COUNT], Id_Y[Y_COUNT];

	srand(time(NULL));

	sem_init(&Room_Sem, 0, ROOM_SIZE);
	sem_init(&Mutex_X, 0, 1);
	sem_init(&Mutex_Y, 0, 1);
	sem_init(&Available_Sem, 0, 1);

	for (i=0; i<X_COUNT; i++){
		Id_X[i] = i;
		pthread_create(&Group_X[i], NULL, X_Func, &Id_X[i]);
	}

	for (i=0; i<Y_COUNT; i++){
		Id_Y[i] = i;
		pthread_create(&Group_Y[i], NULL, Y_Func, &Id_Y[i]);
	}

	for (i=0; i<X_COUNT; i++){
		pthread_join(Group_X[i], NULL);
	}

	for (i=0; i<Y_COUNT; i++){
		pthread_join(Group_Y[i], NULL);
	}

	return 0;
}