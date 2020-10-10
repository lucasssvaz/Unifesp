#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t Sem1 , Sem2;

void *Thread_A (void *args)
{

	printf("Thread A: Waiting for Resource 2...\n");

	sem_wait(&Sem2);

	printf("Thread A: Resource 2 allocated.\n");

	usleep(50000);

	printf("Thread A: Waiting for Resource 1...\n");

	sem_wait(&Sem1);

	printf("Thread A: Resource 1 allocated.\n");

	return NULL;

}

void *Thread_B (void *args)
{

	printf("Thread B: Waiting for Resource 1...\n");

	sem_wait(&Sem1);

	printf("Thread B: Resource 1 allocated.\n");

	usleep(50000);

	printf("Thread B: Waiting for Resource 2...\n");

	sem_wait(&Sem2);

	printf("Thread B: Resource 2 allocated.\n");

	return NULL;
	
}


int main() {
	
	pthread_t T1, T2;
	int Id[2];

	sem_init(&Sem1, 0, 1);
	sem_init(&Sem2, 0, 1);

	Id[0] = 0;
	pthread_create(&T1, NULL, Thread_A, &Id[0]);

	Id[1] = 1;
	pthread_create(&T2, NULL, Thread_B, &Id[1]);

	pthread_join(T1, NULL);
	pthread_join(T2, NULL);

	printf("Done\n");

	return 0;
}