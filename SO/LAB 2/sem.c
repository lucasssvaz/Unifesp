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

#define X_COUNT 5
#define Y_COUNT 5
#define ROOM_SIZE 20

sem_t Room_Sem, X_Sem, Y_Sem, Available_Sem;

//============================================================================================================================= FUNCTIONS

void *X_Func(void *args){
	int pid = *(int *)args;
	int qntX, qntY, qntA;
	while(1){
		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("X[%d]: trying to enter room... X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		sem_wait(&Room_Sem);
		if (qntX == X_COUNT)
			sem_wait(&Available_Sem);
		sem_wait(&X_Sem);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("X[%d]: Joined the Room. X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		//usleep(rand()%500000);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("X[%d]: Leaving the room... X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		
		sem_getvalue(&X_Sem, &qntX);
		if (qntX == X_COUNT-1)
			sem_post(&Available_Sem);
		sem_post(&X_Sem);
		sem_post(&Room_Sem);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("X[%d]: Left the Room. X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);
	}
}

//--------------------------------------------

void *Y_Func(void *args){
	int pid = *(int *)args;
	int qntX, qntY, qntA;
	while(1){
		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("Y[%d]: trying to enter room... X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		sem_wait(&Room_Sem);
		if (qntY == Y_COUNT)
			sem_wait(&Available_Sem);
		sem_wait(&Y_Sem);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("Y[%d]: Joined the Room. X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		//usleep(rand()%1000000);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("Y[%d]: Leaving the room... X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
		fflush(stdout);

		sem_getvalue(&Y_Sem, &qntY);
		if (qntY == Y_COUNT-1)
			sem_post(&Available_Sem);
		sem_post(&Y_Sem);
		sem_post(&Room_Sem);

		sem_getvalue(&X_Sem, &qntX);
		sem_getvalue(&Y_Sem, &qntY);
		sem_getvalue(&Available_Sem, &qntA);
		printf("Y[%d]: Left the Room. X_Sem = %d, Y_Sem = %d, Available_Sem = %d\n", pid, qntX, qntY, qntA);
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
	sem_init(&X_Sem, 0, X_COUNT);
	sem_init(&Y_Sem, 0, Y_COUNT);
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