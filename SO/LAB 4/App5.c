#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t Sem1, Sem2, Sem3;

void *Thread_A (void *args)
{

	printf("Thread A: Waiting for Resource 1...\n");

	sem_wait(&Sem1);

	printf("Thread A: Resource 1 allocated.\n");

	usleep(50000);

	printf("Thread A: Waiting for Resource 2...\n");

	sem_wait(&Sem2);

	printf("Thread A: Resource 2 allocated.\n");

	usleep(50000);

	sem_post(&Sem2);

	printf("Thread A: Resource 2 freed.\n");

	usleep(500000);

	sem_post(&Sem1);

	printf("Thread A: Resource 1 freed.\n");

	return NULL;

}

void *Thread_B (void *args)
{

	printf("Thread B: Waiting for Resource 2...\n");

	sem_wait(&Sem2);

	printf("Thread B: Resource 2 allocated.\n");

	usleep(50000);

	printf("Thread B: Waiting for Resource 3...\n");

	sem_wait(&Sem3);

	printf("Thread B: Resource 3 allocated.\n");

	usleep(50000);

	sem_post(&Sem3);

	printf("Thread B: Resource 3 freed.\n");

	usleep(500000);

	sem_post(&Sem2);

	printf("Thread B: Resource 2 freed.\n");

	return NULL;
	
}

void *Thread_C (void *args)
{

	printf("Thread C: Waiting for Resource 3...\n");

	sem_wait(&Sem3);

	printf("Thread C: Resource 3 allocated.\n");

	usleep(50000);

	printf("Thread C: Waiting for Resource 1...\n");

	sem_wait(&Sem1);

	printf("Thread C: Resource 3 allocated.\n");

	sem_post(&Sem3);

	printf("Thread C: Resource 3 freed.\n");

	return NULL;
	
}


int main() {
	
	pthread_t T1, T2, T3;

	sem_init(&Sem1, 0, 1);
	sem_init(&Sem2, 0, 1);
	sem_init(&Sem3, 0, 1);

	pthread_create(&T1, NULL, Thread_A, NULL);
	pthread_create(&T2, NULL, Thread_B, NULL);
	pthread_create(&T3, NULL, Thread_C, NULL);

	pthread_join(T1, NULL);
	pthread_join(T2, NULL);
	pthread_join(T3, NULL);

	printf("Done\n");

	return 0;
}